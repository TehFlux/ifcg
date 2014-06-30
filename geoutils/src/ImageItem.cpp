/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImageItem.cpp                   Image item (implementation).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * GeoUtils - Ionflux' Geometry Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with GeoUtils - Ionflux' Geometry Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "geoutils/ImageItem.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

ImageItemClassInfo::ImageItemClassInfo()
{
	name = "ImageItem";
	desc = "Image item";
	baseClassInfo.push_back(Ionflux::GeoUtils::BoxBoundsItem::CLASS_INFO);
}

ImageItemClassInfo::~ImageItemClassInfo()
{
}

// public member constants
const Ionflux::GeoUtils::SVGType ImageItem::SOURCE_TYPE_UNDEFINED = 0;
const Ionflux::GeoUtils::SVGType ImageItem::SOURCE_TYPE_FILE = 1;
const Ionflux::GeoUtils::SVGType ImageItem::SOURCE_TYPE_SOURCE = 2;

// run-time type information instance constants
const ImageItemClassInfo ImageItem::imageItemClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ImageItem::CLASS_INFO = &ImageItem::imageItemClassInfo;

ImageItem::ImageItem()
: image(0), imageID(""), sourceType(SOURCE_TYPE_UNDEFINED), blender(0), numUsers(0), source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ImageItem::ImageItem(const Ionflux::GeoUtils::ImageItem& other)
: image(0), imageID(""), sourceType(SOURCE_TYPE_UNDEFINED), blender(0), numUsers(0), source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ImageItem::ImageItem(const std::string& initImageID, 
Ionflux::GeoUtils::ImageSourceType initSourceType, const 
Ionflux::GeoUtils::Vector3& initOffset, Ionflux::Altjira::ColorBlender* 
initBlender, Ionflux::GeoUtils::Image* initImage, 
Ionflux::GeoUtils::ImageSource* initSource)
: image(0), imageID(initImageID), sourceType(initSourceType), blender(0), 
numUsers(0), source(0), offset(initOffset)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setImage(initImage);
	setBlender(initBlender);
	setSource(initSource);
}

ImageItem::~ImageItem()
{
	if (numUsers > 0)
	{
	    std::ostringstream status;
	    status << "Image data is still in use (" << numUsers 
	        << " users left).";
	    log(IFLogMessage(status.str(), VL_WARNING, this, 
	        "~ImageItem"));
	}
}

void ImageItem::clear()
{
	BoxBoundsItem::clear();
	setImage(0);
	setImageID("");
	setSourceType(SOURCE_TYPE_UNDEFINED);
	numUsers = 0;
}

void ImageItem::update()
{
	acquire();
	if (image != 0)
	{
	    Range3 b0 = image->getBounds();
	    bounds.setBounds(b0.getCenter() + offset);
	    bounds.extend(b0.getCenter() + offset - b0.getRadius());
	    bounds.extend(b0.getCenter() + offset + b0.getRadius());
	} else
	    bounds.setBounds(offset);
	updateRadiusAndCenter();
	release();
}

void ImageItem::acquire()
{
	if (numUsers == UINT_MAX)
	    throw GeoUtilsError("[ImageItem::acquire] " 
	        "Overflow in number of users!");
	if (numUsers == 0)
	    load();
	numUsers++;
}

void ImageItem::release()
{
	if (numUsers == 0)
	    throw GeoUtilsError("[ImageItem::release] " 
	        "Attempt to release image data with zero users!");
	numUsers--;
}

void ImageItem::load()
{
	if (sourceType == SOURCE_TYPE_FILE)
	{
	    Image* img0 = Image::create();
	    img0->loadFromFile(imageID);
	    setImage(img0);
	    return;
	}
	if (sourceType == SOURCE_TYPE_SOURCE)
	{
	    if (source == 0)
	        throw GeoUtilsError("[ImageItem::load] " 
	            "Image source not set!");
	    Image* img0 = source->getImage(imageID);
	    setImage(img0);
	    return;
	}
	std::ostringstream status;
	status << "[ImageItem::load] Unknown source type for loading (" 
	    << sourceType << ")!";
	throw GeoUtilsError(status.str());
}

void ImageItem::clearData()
{
	setImage(0);
}

std::string ImageItem::getString() const
{
	ostringstream state;
		state << getClassName() << "[center: " << center.getString() 
	    << ", rVec: " << rVec.getString() << ", itemID: '" << itemID 
	    << "', imageID: '" << imageID << "', sourceType: " 
	    << getSourceTypeString(sourceType) << ", offset: " 
	    << offset << "]";
	return state.str();
}

std::string 
ImageItem::getSourceTypeString(Ionflux::GeoUtils::ImageSourceType 
sourceType)
{
	if (sourceType == SOURCE_TYPE_UNDEFINED)
	    return "<undefined>";
	if (sourceType == SOURCE_TYPE_FILE)
	    return "FILE";
	if (sourceType == SOURCE_TYPE_SOURCE)
	    return "SOURCE";
	return "<unknown>";
}

void ImageItem::setImage(Ionflux::GeoUtils::Image* newImage)
{
	if (image == newImage)
		return;
    if (newImage != 0)
        addLocalRef(newImage);
	if (image != 0)
		removeLocalRef(image);
	image = newImage;
}

Ionflux::GeoUtils::Image* ImageItem::getImage() const
{
    return image;
}

void ImageItem::setImageID(const std::string& newImageID)
{
	imageID = newImageID;
}

std::string ImageItem::getImageID() const
{
    return imageID;
}

void ImageItem::setSourceType(Ionflux::GeoUtils::ImageSourceType 
newSourceType)
{
	sourceType = newSourceType;
}

Ionflux::GeoUtils::ImageSourceType ImageItem::getSourceType() const
{
    return sourceType;
}

void ImageItem::setBlender(Ionflux::Altjira::ColorBlender* newBlender)
{
	if (blender == newBlender)
		return;
    if (newBlender != 0)
        addLocalRef(newBlender);
	if (blender != 0)
		removeLocalRef(blender);
	blender = newBlender;
}

Ionflux::Altjira::ColorBlender* ImageItem::getBlender() const
{
    return blender;
}

void ImageItem::setNumUsers(unsigned int newNumUsers)
{
	numUsers = newNumUsers;
}

unsigned int ImageItem::getNumUsers() const
{
    return numUsers;
}

void ImageItem::setSource(Ionflux::GeoUtils::ImageSource* newSource)
{
	if (source == newSource)
		return;
    if (newSource != 0)
        addLocalRef(newSource);
	if (source != 0)
		removeLocalRef(source);
	source = newSource;
}

Ionflux::GeoUtils::ImageSource* ImageItem::getSource() const
{
    return source;
}

void ImageItem::setOffset(Ionflux::GeoUtils::Vector3 newOffset)
{
	offset = newOffset;
}

Ionflux::GeoUtils::Vector3 ImageItem::getOffset() const
{
    return offset;
}

Ionflux::GeoUtils::ImageItem& ImageItem::operator=(const 
Ionflux::GeoUtils::ImageItem& other)
{
    if (*this == other)
        return *this;
    BoxBoundsItem::operator=(other);
    setImage(other.image);
    setImageID(other.imageID);
    setSourceType(other.sourceType);
    numUsers = other.numUsers;
	return *this;
}

Ionflux::GeoUtils::ImageItem* ImageItem::copy() const
{
    ImageItem* newImageItem = create();
    *newImageItem = *this;
    return newImageItem;
}

Ionflux::GeoUtils::ImageItem* 
ImageItem::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<ImageItem*>(other);
}

Ionflux::GeoUtils::ImageItem* 
ImageItem::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    ImageItem* newObject = new ImageItem();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int ImageItem::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file ImageItem.cpp
 * \brief Image item implementation.
 */
