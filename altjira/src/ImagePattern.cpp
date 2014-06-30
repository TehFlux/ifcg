/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImagePattern.cpp                Image pattern (implementation).
 * =========================================================================
 * 
 * This file is part of Altjira - Ionflux' Image Processing Library.
 * 
 * Altjira - Ionflux' Image Processing Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * Altjira - Ionflux' Image Processing Library is distributed in the hope 
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Altjira - Ionflux' Image Processing Library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "altjira/ImagePattern.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "altjira/AltjiraError.hpp"
#include "altjira/utils.hpp"
#include "altjira/imageutils.hpp"
#include "altjira/Image.hpp"
#include "altjira/BlendSrcOver.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;
using namespace Ionflux::Altjira;

namespace Ionflux
{

namespace Altjira
{

ImagePatternClassInfo::ImagePatternClassInfo()
{
	name = "ImagePattern";
	desc = "Image pattern";
	baseClassInfo.push_back(Ionflux::Altjira::Pattern::CLASS_INFO);
}

ImagePatternClassInfo::~ImagePatternClassInfo()
{
}

// run-time type information instance constants
const ImagePatternClassInfo ImagePattern::imagePatternClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ImagePattern::CLASS_INFO = &ImagePattern::imagePatternClassInfo;

ImagePattern::ImagePattern()
: image(0), offsetX(0), offsetY(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ImagePattern::ImagePattern(const Ionflux::Altjira::ImagePattern& other)
: image(0), offsetX(0), offsetY(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ImagePattern::ImagePattern(Ionflux::Altjira::Image* initImage, double 
initOffsetX, double initOffsetY)
: image(0), offsetX(initOffsetX), offsetY(initOffsetY)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setImage(initImage);
}

ImagePattern::~ImagePattern()
{
	clear();
}

void ImagePattern::clear()
{
	Pattern::clear();
	setImage(0);
}

void ImagePattern::update()
{
	if (image == 0)
	    throw AltjiraError("[ImagePattern::update] " 
	        "Image is null!");
	Pattern::clear();
	cairo_surface_t* target = cairo_image_surface_create(
	    CAIRO_FORMAT_ARGB32, image->getWidth(), image->getHeight());
	if (cairo_surface_status(target) != CAIRO_STATUS_SUCCESS)
	{
	    cairo_surface_destroy(target);
	    throw AltjiraError("[ImagePattern::update] "
	        "Could not allocate image surface!");
	}
	compositeToSurface(*image, target);
	pattern = cairo_pattern_create_for_surface(target);
	cairo_surface_destroy(target);
	if (cairo_pattern_status(pattern) != CAIRO_STATUS_SUCCESS)
	{
	    cairo_pattern_destroy(pattern);
	    pattern = 0;
	    throw AltjiraError("[ImagePattern::update] "
	        "Could not create pattern!");
	}
	translate(-offsetX, -offsetY);
}

std::string ImagePattern::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

void ImagePattern::compositeToSurface(Ionflux::Altjira::Image& source, 
cairo_surface_t* target, const Ionflux::Altjira::ColorBlender* blender, 
const Ionflux::Altjira::ImageRect* sourceRect, unsigned int offsetX, 
unsigned int offsetY)
{
	if (target == 0)
	    throw AltjiraError("[ImagePattern::compositeToSurface] " 
	        "Target surface is null!");
	// Set up source rectangle.
	ImageRect sr;
	if (sourceRect == 0)
	{
	    sr.x = 0;
	    sr.y = 0;
	    sr.width = source.getWidth();
	    sr.height = source.getHeight();
	} else
	{
	    sr = *sourceRect;
	    source.clamp(sr);
	}
	// Obtain surface pixel data and do some sanity checks.
	Ionflux::Altjira::PixelData tp = cairo_image_surface_get_data(target);
	if (tp == 0)
	    throw AltjiraError("[ImagePattern::compositeToSurface] "
	        "Could not obtain surface data.");
	unsigned int targetRowStride = cairo_image_surface_get_stride(target);
	int targetWidth = cairo_image_surface_get_width(target);
	int targetHeight = cairo_image_surface_get_height(target);
	cairo_format_t targetFormat = cairo_image_surface_get_format(target);
	if (targetFormat != CAIRO_FORMAT_ARGB32)
	    throw AltjiraError("[ImagePattern::compositeToSurface] "
	        "Unknown target surface format (expected ARGB32).");
	// Set up color blender.
	bool ownBlender = false;
	if (blender == 0)
	{
	    blender = Ionflux::Altjira::BlendSrcOver::create();
	    ownBlender = true;
	}
	// Calculate target area;
	ImageRect tr0;
	tr0.x = 0;
	tr0.y = 0;
	tr0.width = static_cast<unsigned int>(targetWidth);
	tr0.height = static_cast<unsigned int>(targetHeight);
	ImageRect tr;
	tr.x = offsetX;
	tr.y = offsetY;
	tr.width = sr.width;
	tr.height = sr.height;
	tr = intersect(tr, tr0);
	// Composite.
	cairo_surface_flush(target);
	unsigned int srcRowStride = source.getRowStride();
	unsigned int srcNumChannels = source.getNumChannels();
	unsigned int iMax = min(sr.width, tr.width);
	unsigned int jMax = min(sr.height, tr.height);
	PixelData sp = source.getPixels();
	ByteColor sc;
	ByteColor tc;
	ByteColor rc;
	sc.space = Color::SPACE_RGB;
	tc.space = Color::SPACE_RGB;
	rc.space = Color::SPACE_RGB;
	ByteColorValue so = floatToByte(blender->getSourceOpacity());
	ByteColorValue to = floatToByte(blender->getTargetOpacity());
	for (unsigned int i = 0; i < iMax; i++)
	    for (unsigned int j = 0; j < jMax; j++)
	    {
	        PixelData ps = sp + (sr.y + j) * srcRowStride 
	            + (sr.x + i) * srcNumChannels;
	        PixelData pt = tp + (tr.y + j) * targetRowStride 
	            + (tr.x + i) * 4;
	        sc.c0 = ps[0];
	        sc.c1 = ps[1];
	        sc.c2 = ps[2];
	        if (srcNumChannels >= 4)
	            sc.alpha = ps[3];
	        else
	            sc.alpha = 255;
	        Ionflux::ObjectBase::UInt32* p0 = 
	            reinterpret_cast<Ionflux::ObjectBase::UInt32*>(pt);
	        fromUInt(*p0, tc, true);
	        blender->blend(rc, sc, tc, so, to);
	        *p0 = toUInt(rc, true);
	    }
	cairo_surface_mark_dirty(target);
	//cairo_surface_write_to_png(target, "temp/cairotest01.png");
	if (ownBlender)
	    delete blender;
}

void ImagePattern::setImage(Ionflux::Altjira::Image* newImage)
{
	if (image == newImage)
	    return;
	if (newImage != 0)
	    addLocalRef(newImage);
	if (image != 0)
	    removeLocalRef(image);
	image = newImage;
	if (image != 0)
	    update();
	else
	    Pattern::clear();
}

Ionflux::Altjira::Image* ImagePattern::getImage() const
{
    return image;
}

void ImagePattern::setOffsetX(double newOffsetX)
{
	offsetX = newOffsetX;
}

double ImagePattern::getOffsetX() const
{
    return offsetX;
}

void ImagePattern::setOffsetY(double newOffsetY)
{
	offsetY = newOffsetY;
}

double ImagePattern::getOffsetY() const
{
    return offsetY;
}

Ionflux::Altjira::ImagePattern& ImagePattern::operator=(const 
Ionflux::Altjira::ImagePattern& other)
{
    Ionflux::Altjira::Pattern::operator=(other);
    if (image != other.image)
        setImage(other.image);
	return *this;
}

Ionflux::Altjira::ImagePattern* ImagePattern::copy() const
{
    ImagePattern* newImagePattern = create();
    *newImagePattern = *this;
    return newImagePattern;
}

Ionflux::Altjira::ImagePattern* 
ImagePattern::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<ImagePattern*>(other);
}

Ionflux::Altjira::ImagePattern* 
ImagePattern::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    ImagePattern* newObject = new ImagePattern();
    if (newObject == 0)
    {
        throw AltjiraError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int ImagePattern::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file ImagePattern.cpp
 * \brief Image pattern implementation.
 */
