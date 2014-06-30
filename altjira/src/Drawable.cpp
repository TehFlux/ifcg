/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Drawable.cpp                    Drawable (implementation).
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

#include "altjira/Drawable.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <pango/pangocairo.h>
#include <librsvg/rsvg.h>
#include <librsvg/rsvg-cairo.h>
#include "altjira/AltjiraError.hpp"
#include "altjira/utils.hpp"
#include "altjira/imageutils.hpp"
#include "altjira/BlendSrcOver.hpp"
#include "altjira/ImagePattern.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;
using namespace Ionflux::Altjira;

namespace Ionflux
{

namespace Altjira
{

DrawableClassInfo::DrawableClassInfo()
{
	name = "Drawable";
	desc = "Drawable";
	baseClassInfo.push_back(Ionflux::Altjira::Image::CLASS_INFO);
}

DrawableClassInfo::~DrawableClassInfo()
{
}

// run-time type information instance constants
const DrawableClassInfo Drawable::drawableClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Drawable::CLASS_INFO = &Drawable::drawableClassInfo;

Drawable::Drawable()
: context(0), surface(0), inProgress(false)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Drawable::Drawable(const Ionflux::Altjira::Drawable& other)
: context(0), surface(0), inProgress(false)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	Ionflux::Altjira::init();
	*this = other;
}

Drawable::Drawable(const std::string& fileName)
: Ionflux::Altjira::Image(fileName), context(0), surface(0), 
inProgress(false)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Drawable::Drawable(const Ionflux::Altjira::Image& initImage)
: Ionflux::Altjira::Image(initImage), context(0), surface(0), 
inProgress(false)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Drawable::Drawable(unsigned int initWidth, unsigned int initHeight, bool 
initAlpha, unsigned int initBitsPerSample, Ionflux::Altjira::ColorSpace 
initColorSpace)
: Ionflux::Altjira::Image(initWidth, initHeight, initAlpha, 
initBitsPerSample, initColorSpace), context(0), surface(0), 
inProgress(false)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Drawable::~Drawable()
{
	discard();
}

void Drawable::transformPattern(Ionflux::Altjira::Pattern& pattern, 
cairo_matrix_t& m)
{
	pattern.transform(m);
}

void Drawable::begin(double originX, double originY)
{
	if (drawingInProgress())
	    throw AltjiraError("[Drawable::begin] " 
	        "Drawing operation in progress!");
	// Just to be sure surface and context are properly cleaned up.
	discard();
	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 
	    width, height);
	if (cairo_surface_status(surface) != CAIRO_STATUS_SUCCESS)
	{
	    cairo_surface_destroy(surface);
	    surface = 0;
	    throw AltjiraError("[Drawable::begin] "
	        "Could not allocate image surface!");
	}
	context = cairo_create(surface);
	if (cairo_status(context) != CAIRO_STATUS_SUCCESS)
	{
	    cairo_destroy(context);
	    context = 0;
	    throw AltjiraError("[Drawable::begin] "
	        "Could not allocate drawing context!");
	}
	inProgress = true;
}

void Drawable::discard()
{
	if (surface != 0)
	{
	    cairo_surface_destroy(surface);
	    surface = 0;
	}
	if (context != 0)
	{
	    cairo_destroy(context);
	    context = 0;
	}
	inProgress = false;
}

void Drawable::finish(const Ionflux::Altjira::ColorBlender* blender)
{
	if (!drawingInProgress())
	    return;
	bool ownBlender = false;
	if (blender == 0)
	{
	    blender = Ionflux::Altjira::BlendSrcOver::create();
	    ownBlender = true;
	}
	unsigned int srcRowStride = cairo_image_surface_get_stride(surface);
	Ionflux::Altjira::PixelData sp = cairo_image_surface_get_data(surface);
	if (sp == 0)
	    throw AltjiraError("[Drawable::finish] "
	        "Could not obtain surface data.");
	PixelData tp = pixels;
	ByteColor sc;
	ByteColor tc;
	ByteColor rc;
	sc.space = Color::SPACE_RGB;
	tc.space = Color::SPACE_RGB;
	rc.space = Color::SPACE_RGB;
	ByteColorValue so = floatToByte(blender->getSourceOpacity());
	ByteColorValue to = floatToByte(blender->getTargetOpacity());
	cairo_surface_flush(surface);
	for (unsigned int i = 0; i < width; i++)
	    for (unsigned int j = 0; j < height; j++)
	    {
	        PixelData ps = sp + j * srcRowStride + i * 4;
	        PixelData pt = tp + j * rowStride + i * numChannels;
	        Ionflux::ObjectBase::UInt32* p0 = 
	            reinterpret_cast<Ionflux::ObjectBase::UInt32*>(ps);
	        fromUInt(*p0, sc, true);
	        tc.c0 = pt[0];
	        tc.c1 = pt[1];
	        tc.c2 = pt[2];
	        if (numChannels >= 4)
	            tc.alpha = pt[3];
	        else
	            tc.alpha = 255;
	        blender->blend(rc, sc, tc, so, to);
	        pt[0] = rc.c0;
	        pt[1] = rc.c1;
	        pt[2] = rc.c2;
	        if (numChannels >= 4)
	            pt[3] = rc.alpha;
	    }
	// cairo_surface_write_to_png(surface, "temp/cairotest01.png");
	if (ownBlender)
	    delete blender;
	discard();
}

void Drawable::save()
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::save] " 
	        "No drawing operation in progress!");
	cairo_save(context);
}

void Drawable::restore()
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::restore] " 
	        "No drawing operation in progress!");
	cairo_restore(context);
}

void Drawable::translate(double tx, double ty)
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::translate] " 
	        "No drawing operation in progress!");
	cairo_translate(context, tx, ty);
}

void Drawable::scale(double sx, double sy)
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::scale] " 
	        "No drawing operation in progress!");
	cairo_scale(context, sx, sy);
}

void Drawable::rotate(double phi)
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::rotate] " 
	        "No drawing operation in progress!");
	cairo_rotate(context, phi);
}

void Drawable::newPath()
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::newPath] " 
	        "No drawing operation in progress!");
	cairo_new_path(context);
}

void Drawable::newSubPath()
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::newSubPath] " 
	        "No drawing operation in progress!");
	cairo_new_sub_path(context);
}

void Drawable::closePath()
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::closePath] " 
	        "No drawing operation in progress!");
	cairo_close_path(context);
}

void Drawable::moveTo(double x, double y)
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::moveTo] " 
	        "No drawing operation in progress!");
	cairo_move_to(context, x, y);
}

void Drawable::lineTo(double x, double y)
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::lineTo] " 
	        "No drawing operation in progress!");
	cairo_line_to(context, x, y);
}

void Drawable::curveTo(double x0, double y0, double x1, double y1, double 
x2, double y2)
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::curveTo] " 
	        "No drawing operation in progress!");
	cairo_curve_to(context, x0, y0, x1, y1, x2, y2);
}

void Drawable::rectangle(double x, double y, double width, double height)
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::rectangle] " 
	        "No drawing operation in progress!");
	cairo_rectangle(context, x, y, width, height);
}

void Drawable::arc(double x, double y, double radius, double phi0, double 
phi1)
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::arc] " 
	        "No drawing operation in progress!");
	cairo_arc(context, x, y, radius, phi0, phi1);
}

void Drawable::setSourceColor(const Ionflux::Altjira::Color& color)
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::setSourceColor] " 
	        "No drawing operation in progress!");
	cairo_set_source_rgba(context, color.getRed(), color.getGreen(), 
	    color.getBlue(), color.getAlpha());
}

void Drawable::setSource(Ionflux::Altjira::Pattern& pattern)
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::setSource] " 
	        "No drawing operation in progress!");
	cairo_set_source(context, pattern.pattern);
}

void Drawable::setSourceImage(Ionflux::Altjira::Image* image, double x, 
double y)
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::setSourceImage] " 
	        "No drawing operation in progress!");
	if (image == 0)
	    throw AltjiraError("[Drawable::setSourceImage] " 
	        "Image is null!");
	ImagePattern p0(image, x, y);
	setSource(p0);
}

void Drawable::setFillRule(Ionflux::Altjira::FillRule fillRule)
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::setFillRule] " 
	        "No drawing operation in progress!");
	cairo_fill_rule_t fr0;
	if (fillRule == FILL_RULE_EVEN_ODD)
	    fr0 = CAIRO_FILL_RULE_EVEN_ODD;
	else
	    fr0 = CAIRO_FILL_RULE_WINDING;
	cairo_set_fill_rule(context, fr0);
}

void Drawable::stroke(double lineWidth, bool preserve)
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::restore] " 
	        "No drawing operation in progress!");
	cairo_set_line_width(context, lineWidth);
	if (!preserve)
	    cairo_stroke(context);
	else
	    cairo_stroke_preserve(context);
}

void Drawable::fillPath(bool preserve)
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::restore] " 
	        "No drawing operation in progress!");
	if (!preserve)
	    cairo_fill(context);
	else
	    cairo_fill_preserve(context);
}

void Drawable::paint()
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::restore] " 
	        "No drawing operation in progress!");
	cairo_paint(context);
}

Ionflux::Altjira::ImageRect Drawable::getTextSize(const std::string& text, 
const std::string& fontDesc, double fontSize) const
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::getTextSize] " 
	        "No drawing operation in progress!");
	ImageRect result;
	PangoLayout* l0 = pango_cairo_create_layout(context);
	pango_layout_set_text(l0, text.c_str(), text.size());
	PangoFontDescription* fd0 = pango_font_description_from_string(
	    fontDesc.c_str());
	pango_font_description_set_absolute_size(fd0, fontSize * PANGO_SCALE);
	pango_layout_set_font_description(l0, fd0);
	pango_cairo_update_layout(context, l0);
	int w = 0;
	int h = 0;
	pango_layout_get_size(l0, &w, &h);
	initRectangle(result, 0., 0., 
	    static_cast<double>(w) / PANGO_SCALE, 
	    static_cast<double>(h) / PANGO_SCALE);
	pango_font_description_free(fd0);
	g_object_unref(l0);
	return result;
}

void Drawable::drawText(double x, double y, const std::string& text, const 
std::string& fontDesc, double fontSize, const Ionflux::Altjira::Color& 
color)
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::getTextSize] " 
	        "No drawing operation in progress!");
	save();
	PangoLayout* l0 = pango_cairo_create_layout(context);
	pango_layout_set_text(l0, text.c_str(), text.size());
	PangoFontDescription* fd0 = pango_font_description_from_string(
	    fontDesc.c_str());
	pango_font_description_set_absolute_size(fd0, fontSize * PANGO_SCALE);
	pango_layout_set_font_description(l0, fd0);
	pango_cairo_update_layout(context, l0);
	moveTo(x, y);
	setSourceColor(color);
	pango_cairo_show_layout(context, l0);
	pango_font_description_free(fd0);
	g_object_unref(l0);
	restore();
}

void Drawable::drawSVG(const std::string& svgData, int originX, int 
originY)
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::drawSVG] " 
	        "No drawing operation in progress!");
	cairo_save(context);
	cairo_translate(context, 0.5 * width + originX, 
	    0.5 * height + originY);
	// Render the SVG.
	//rsvg_init();
	RsvgHandle* rsvg0 = rsvg_handle_new_from_data(
	    reinterpret_cast<const guint8*>(svgData.c_str()), 
	    svgData.size(), 0);
	if (rsvg0 == 0)
	{
	    throw AltjiraError("[Drawable::drawSVG] "
	        "Could not create RSVG handle!");
	}
	if (!rsvg_handle_render_cairo(rsvg0, context))
	{
	    g_object_unref(rsvg0);
	    throw AltjiraError("[Drawable::drawSVG] "
	        "Could not render SVG to cairo context!");
	}
	g_object_unref(rsvg0);
	cairo_restore(context);
}

void Drawable::drawSVGFile(const std::string& svgFileName, int originX, int
originY)
{
	if (!drawingInProgress())
	    throw AltjiraError("[Drawable::drawSVGFile] " 
	        "No drawing operation in progress!");
	cairo_save(context);
	cairo_translate(context, 0.5 * width + originX, 
	    0.5 * height + originY);
	// Render the SVG.
	//rsvg_init();
	RsvgHandle* rsvg0 = rsvg_handle_new_from_file(
	    reinterpret_cast<const gchar*>(svgFileName.c_str()), 0);
	if (rsvg0 == 0)
	{
	    throw AltjiraError("[Drawable::drawSVGFile] "
	        "Could not create RSVG handle!");
	}
	if (!rsvg_handle_render_cairo(rsvg0, context))
	{
	    g_object_unref(rsvg0);
	    throw AltjiraError("[Drawable::drawSVGFile] "
	        "Could not render SVG to cairo context!");
	}
	g_object_unref(rsvg0);
	cairo_restore(context);
}

bool Drawable::drawingInProgress() const
{
	// TODO: Implementation.
	return inProgress;
}

std::string Drawable::getString() const
{
	// TODO: Implementation.
	return Image::getString();
}

Ionflux::Altjira::Drawable& Drawable::operator=(const 
Ionflux::Altjira::Drawable& other)
{
    Ionflux::Altjira::Image::operator=(other);
	return *this;
}

Ionflux::Altjira::Drawable* Drawable::copy() const
{
    Drawable* newDrawable = create();
    *newDrawable = *this;
    return newDrawable;
}

Ionflux::Altjira::Drawable* Drawable::upcast(Ionflux::ObjectBase::IFObject*
other)
{
    return dynamic_cast<Drawable*>(other);
}

Ionflux::Altjira::Drawable* Drawable::create(Ionflux::ObjectBase::IFObject*
parentObject)
{
    Drawable* newObject = new Drawable();
    if (newObject == 0)
    {
        throw AltjiraError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Drawable::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Drawable.cpp
 * \brief Drawable implementation.
 */
