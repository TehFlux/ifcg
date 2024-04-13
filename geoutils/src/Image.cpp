/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Image.cpp                       Image (implementation).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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

#include "geoutils/Image.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <cairo.h>
#include <librsvg/rsvg.h>
#include <librsvg/rsvg-cairo.h>
#include "altjira/utils.hpp"
#include "altjira/imageutils.hpp"
#include "altjira/ImagePattern.hpp"
#include "altjira/BlendSrcOver.hpp"
#include "geoutils/imageutils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Polygon3.hpp"
#include "geoutils/Vertex3.hpp"
#include "geoutils/Vector3.hpp"
#include "geoutils/BoxBoundsItem.hpp"
#include "geoutils/BoundingBox.hpp"
#include "geoutils/Voxel.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;
using namespace Ionflux::Altjira;

namespace Ionflux
{

namespace GeoUtils
{

ImageClassInfo::ImageClassInfo()
{
	name = "Image";
	desc = "Image";
	baseClassInfo.push_back(Ionflux::Altjira::Drawable::CLASS_INFO);
	baseClassInfo.push_back(Ionflux::GeoUtils::TransformableObject::CLASS_INFO);
}

ImageClassInfo::~ImageClassInfo()
{
}

// public member constants
const Ionflux::GeoUtils::Vector3 Image::TANGENT_VECTORS[3][3] = {
    { Ionflux::GeoUtils::Vector3(-1, 1, 0), 
       Ionflux::GeoUtils::Vector3(0, 1, 0), 
       Ionflux::GeoUtils::Vector3(1, 1, 0) }, 
    { Ionflux::GeoUtils::Vector3(-1, 0, 0), 
       Ionflux::GeoUtils::Vector3(0, 0, 0), 
       Ionflux::GeoUtils::Vector3(1, 0, 0) }, 
    { Ionflux::GeoUtils::Vector3(-1, -1, 0), 
       Ionflux::GeoUtils::Vector3(0, -1, 0), 
       Ionflux::GeoUtils::Vector3(1, -1, 0) }
};

// run-time type information instance constants
const ImageClassInfo Image::imageClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Image::CLASS_INFO = &Image::imageClassInfo;

Image::Image()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Image::Image(const Ionflux::GeoUtils::Image& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	Ionflux::Altjira::init();
	*this = other;
}

Image::Image(const std::string& fileName)
: Ionflux::Altjira::Drawable(fileName)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Image::Image(const Ionflux::Altjira::Image& initImage)
: Ionflux::Altjira::Drawable(initImage)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Image::Image(const Ionflux::Altjira::Drawable& initDrawable)
: Ionflux::Altjira::Drawable(initDrawable)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Image::Image(unsigned int initWidth, unsigned int initHeight, bool 
initAlpha, unsigned int initBitsPerSample, Ionflux::Altjira::ColorSpace 
initColorSpace)
: Ionflux::Altjira::Drawable(initWidth, initHeight, initAlpha, 
initBitsPerSample, initColorSpace)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Image::~Image()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::GeoUtils::Range3 Image::getImageBounds()
{
	Range3 result;
	result.setBounds(Vector3::ZERO);
	result.extend(Vector3(width, height, 0.));
	return result;
}

void Image::recalculateBounds()
{
	TransformableObject::recalculateBounds();
	if (!useTransform() && !useVI())
	{
	    *boundsCache = getImageBounds();
	    return;
	}
	// Adjust for transformation.
	/* TODO: Set bounds cache to transformed image bounds.
	         (This is unfortunately not trivial. For now, we just use 
	          a box polygon and apply the transformation. \) */
	Range3 b0 = getImageBounds();
	Polygon3* p0 = Polygon3::square();
	addLocalRef(p0);
	/* The polygon is created in the XZ-plane by default, but we need it 
	   to be in the XY-plane. */
	p0->rotate(0.5 * M_PI, AXIS_X);
	// Transform the polygon to match the bounds of the SVG.
	p0->scale(Vector3(2. * b0.getX().getRadius(), 
	    2. * b0.getY().getRadius(), 1.));
	p0->translate(b0.getCenter());
	// Apply the transformations.
	if (useTransform())
	    p0->transform(*getTransformMatrix());
	// NOTE: VI transform is not supported for SVG objects.
	p0->applyTransform();
	*boundsCache = p0->getBounds();
	removeLocalRef(p0);
}

void Image::drawPolygons(Ionflux::GeoUtils::Polygon3Set& polygons, const 
Ionflux::GeoUtils::SVGShapeStyleVector* styles, Ionflux::GeoUtils::AxisID 
axis, bool closePath, int originX, int originY)
{
	if (!drawingInProgress())
	    throw GeoUtilsError("[Image::renderPolygons] " 
	        "No drawing operation in progress!");
	AxisID oa[2];
	if (axis == AXIS_Y)
	{
	    oa[0] = AXIS_X;
	    oa[1] = AXIS_Z;
	} else
	if (axis == AXIS_X)
	{
	    oa[0] = AXIS_Y;
	    oa[1] = AXIS_Z;
	} else
	if (axis == AXIS_Z)
	{
	    oa[0] = AXIS_X;
	    oa[1] = AXIS_Y;
	} else
	{
	    ostringstream message;
	    message << "[Image::renderPolygons] Invalid axis: " << axis;
	    throw GeoUtilsError(message.str());
	}
	// Set up transformations.
	cairo_save(context);
	cairo_translate(context, 0.5 * width + originX, 0.5 * height + originY);
	cairo_scale(context, 1., -1.);
	// Render the polygons.
	polygons.applyTransform(true);
	unsigned int numStyles = 0;
	if (styles != 0)
	    numStyles = styles->size();
	for (unsigned int i = 0; i < polygons.getNumPolygons(); i++)
	{
	    Polygon3* p0 = polygons.getPolygon(i);
	    /* <---- DEBUG ----- //
	    ostringstream message;
	    message << "Rendering polygon: " << (*p0);
	    log(IFLogMessage(message.str(), VL_DEBUG, this, 
	        "renderPolygons"));
	    // ----- DEBUG ----> */
	    // Create the path.
	    for (unsigned int k = 0; k < p0->getNumVertices(); k++)
	    {
	        Vertex3* v0 = p0->getVertex(k);
	        /* <---- DEBUG ----- //
	        message.str("");
	        message << "Processing vertex: " << (*v0);
	        log(IFLogMessage(message.str(), VL_DEBUG, this, 
	            "renderPolygons"));
	        // ----- DEBUG ----> */
	        double x0 = v0->getCoord(oa[0]);
	        double y0 = v0->getCoord(oa[1]);
	        if (k == 0)
	            cairo_move_to(context, x0, y0);
	        else
	            cairo_line_to(context, x0, y0);
	    }
	    if (closePath)
	        cairo_close_path(context);
	    const SVGShapeStyle* style = &DEFAULT_SHAPE_STYLE;
	    if ((styles != 0) 
	        && (styles->size() > 0))
	        style = (*styles)[i % numStyles];
	    // Fill the path.
	    if ((style->color.size() > 0) 
	        && (style->color != "none"))
	    {
	        Ionflux::Altjira::Color fillColor(style->color);
	        cairo_set_source_rgba(context, fillColor.getRed(), 
	            fillColor.getGreen(), fillColor.getBlue(), 
	            style->fillOpacity);
	        cairo_fill_preserve(context);
	    }
	    if (style->strokeWidth > 0.)
	    {
	        // Stroke the path.
	        Ionflux::Altjira::Color strokeColor(style->strokeColor);
	        cairo_set_source_rgba(context, strokeColor.getRed(), 
	            strokeColor.getGreen(), strokeColor.getBlue(), 
	            style->strokeOpacity);
	        cairo_set_line_width(context, style->strokeWidth);
	        cairo_set_miter_limit(context, style->strokeMiterLimit);
	        cairo_stroke(context);
	    } else
	        cairo_new_path(context);
	}
	cairo_restore(context);
}

void Image::drawSVG(Ionflux::GeoUtils::SVG& svg, int originX, int originY)
{
	if (!drawingInProgress())
	    throw GeoUtilsError("[Image::renderSVG] " 
	        "No drawing operation in progress!");
	cairo_save(context);
	// Set up transformations.
	cairo_translate(context, 0.5 * width + originX, 0.5 * height + originY);
	// Render the SVG.
	RsvgHandle* rsvg0 = 0;
	std::string source = svg.getSource();
	if (svg.getType() == SVG::TYPE_DATA)
	    rsvg0 = rsvg_handle_new_from_data(
	        reinterpret_cast<const guint8*>(source.c_str()), 
	        source.size(), 0);
	else
	if (svg.getType() == SVG::TYPE_FILE)
	    rsvg0 = rsvg_handle_new_from_file(
	        reinterpret_cast<const gchar*>(source.c_str()), 0);
	else
	{
	    std::ostringstream status;
	    status << "[Image::renderSVG] Invalid SVG source type " 
	        "for rendering (" << svg.getType() << ")!";
	    throw GeoUtilsError(status.str());
	}
	if (rsvg0 == 0)
	{
	    throw GeoUtilsError("[Image::renderSVG] "
	        "Could not create RSVG handle!");
	}
	if (svg.checkTransform())
	{
	    // Apply the transformation of the SVG object.
	    const Matrix4* t0 = svg.getTransformMatrix();
	    cairo_matrix_t ct0;
	    cairo_matrix_init(&ct0, 
	        t0->getElement(0, 0), t0->getElement(1, 0), 
	        t0->getElement(0, 1), t0->getElement(1, 1), 
	        t0->getElement(0, 3), t0->getElement(1, 3));
	    cairo_transform(context, &ct0);
	}
	if (!rsvg_handle_render_cairo(rsvg0, context))
	{
	    g_object_unref(rsvg0);
	    throw GeoUtilsError("[Image::renderSVG] "
	        "Could not render SVG to cairo context!");
	}
	g_object_unref(rsvg0);
	cairo_restore(context);
}

void Image::drawImage(Ionflux::GeoUtils::Image* image, int originX, int 
originY)
{
	if (!drawingInProgress())
	    throw GeoUtilsError("[Image::renderSVG] " 
	        "No drawing operation in progress!");
	cairo_save(context);
	// Set up transformations.
	cairo_translate(context, 0.5 * width + originX, 0.5 * height + originY);
	// Render the image.
	addLocalRef(image);
	ImagePattern p0(image, 0, 0);
	if (image->checkTransform())
	{
	    // Apply the transformation of the image object.
	    const Matrix4* t0 = image->getTransformMatrix();
	    cairo_matrix_t ct0;
	    cairo_matrix_init(&ct0, 
	        t0->getElement(0, 0), t0->getElement(1, 0), 
	        t0->getElement(0, 1), t0->getElement(1, 1), 
	        t0->getElement(0, 3), t0->getElement(1, 3));
	    cairo_transform(context, &ct0);
	    /* NOTE: If the source is set at this point, no transformation 
	             is required for the pattern at all. */
	    setSource(p0);
	}
	Range3 r0 = image->getImageBounds();
	cairo_rectangle(context, r0.getX().getRMin(), r0.getY().getRMin(), 
	    2. * r0.getX().getRadius(), 2. * r0.getY().getRadius());
	cairo_fill(context);
	cairo_restore(context);
	removeLocalRef(image);
}

void Image::valueToNormal(Ionflux::Altjira::Image& target, double 
maxHeight) const
{
	if ((target.getWidth() < width) 
	    || (target.getHeight() < height))
	    throw GeoUtilsError("[Image::valueToNormal] "
	        "Target image too small.");
	for (unsigned int x = 0; x < width; x++)
	    for (unsigned int y = 0; y < height; y++)
	    {
	        FloatColor ps;
	        ps.space = Ionflux::Altjira::Color::SPACE_HSV;
	        getPixel(x, y, ps);
	        double v0 = ps.c2;
	        Vector3 r(0., 0., 0.);
	        double v = 0;
	        // check neighbor pixels
	        for (int xs = static_cast<int>(x) - 1; 
	            xs < static_cast<int>(x) + 2; xs++)
	            for (int ys = static_cast<int>(y) - 1; 
	                ys < static_cast<int>(y) + 2; ys++)
	            {
	                if ((xs >= 0) && (xs < static_cast<int>(width)) 
	                    && (ys >= 0) && (ys < static_cast<int>(height)))
	                {
	                    // use neighbor pixel value
	                    getPixel(xs, ys, ps);
	                    v = ps.c2;
	                } else
	                    // use center pixel value
	                    v = v0;
	                if ((xs != static_cast<int>(x)) 
	                    && (ys != static_cast<int>(y)))
	                {
	                    /* neighbor pixel
	                       get the gradient vector
	                       (y needs to be flipped because of image 
	                       coordinates) */
	                    double dx = static_cast<double>(xs) - x;
	                    double dy = y - static_cast<double>(ys);
	                    Vector3 g(dx, dy, (v - v0) * maxHeight);
	                    Vector3 tx(TANGENT_VECTORS[xs - x + 1][y - ys + 1]);
	                    /* <---- DEBUG ----- //
	                    std::cerr << "[Image::valueToNormal] DEBUG: "
	                        "pos = (" << x << ", " << y << "), "
	                        "s = (" << xs << ", " << ys << ") "
	                        "g = " << g.getString() 
	                        << ", tx = " << tx.getString() << std::endl;
	                    // ----- DEBUG ----> */
	                    // calculate the normal vector
	                    Vector3 dn(tx.cross(g));
	                    r += dn;
	                }
	            }
	        Vector3 n((r / 8.).normalize());
	        FloatColor nc;
	        nc.space = Ionflux::Altjira::Color::SPACE_RGB;
	        normalToColor(n, nc);
	        target.setPixel(x, y, nc);
	        /* <---- DEBUG ----- //
	        std::cerr << "[Image::valueToNormal] DEBUG: "
	            "pos = (" << x << ", " << y << ") "
	            "n = " << n.getString() << ", r = " << r.getString() 
	            << ", c = " << Ionflux::Altjira::getString(nc) << std::endl;
	        // ----- DEBUG ----> */
	    }
}

Ionflux::GeoUtils::TransformableObject& Image::scale(const 
Ionflux::GeoUtils::Vector3& s)
{
	TransformableObject::scale(s);
	return *this;
}

Ionflux::GeoUtils::TransformableObject& Image::translate(const 
Ionflux::GeoUtils::Vector3& t)
{
	TransformableObject::translate(t);
	return *this;
}

Ionflux::GeoUtils::TransformableObject& Image::rotate(double phi, 
Ionflux::GeoUtils::AxisID axis)
{
	TransformableObject::rotate(phi, axis);
	return *this;
}

void Image::drawTranslate(double tx, double ty)
{
	Altjira::Drawable::translate(tx, ty);
}

void Image::drawScale(double sx, double sy)
{
	Altjira::Drawable::scale(sx, sy);
}

void Image::drawRotate(double phi)
{
	Altjira::Drawable::rotate(phi);
}

void Image::setDrawingMatrix(const Ionflux::GeoUtils::Matrix4& m)
{
	if (!drawingInProgress())
	    throw GeoUtilsError("[Image::setDrawingMatrix] " 
	        "No drawing operation in progress!");
	cairo_matrix_t ct0;
	cairo_matrix_init(&ct0, 
	    m.getElement(0, 0), m.getElement(1, 0), 
	    m.getElement(0, 1), m.getElement(1, 1), 
	    m.getElement(0, 3), m.getElement(1, 3));
	cairo_transform(context, &ct0);
}

Ionflux::GeoUtils::Vector3 Image::getBarycenter()
{
	if (boundsCache == 0)
	    recalculateBounds();
	return boundsCache->getCenter();
}

Ionflux::GeoUtils::Image& Image::duplicate()
{
	// TODO: Implementation.
	return *copy();
}

std::string Image::getString() const
{
	// TODO: Implementation.
	return Drawable::getString();
}

void Image::getValueMatrix(Ionflux::Mapping::Matrix& target)
{
	target.init(height, width);
	Ionflux::Altjira::ByteColor sc;
	for (unsigned int x = 0; x < width; x++)
	    for (unsigned int y = 0; y < height; y++)
	    {
	        PixelData p = pixels + y * rowStride + x * numChannels;
	        sc.c0 = p[0];
	        sc.c1 = p[1];
	        sc.c2 = p[2];
	        sc.alpha = p[3];
	        sc.space = Ionflux::Altjira::Color::SPACE_RGB;
	        toColorSpace(sc, Ionflux::Altjira::Color::SPACE_HSV);
	        target.setValue(y, x, byteToFloat(sc.c2));
	    }
}

void Image::setValueMatrix(const Ionflux::Mapping::Matrix& m)
{
	Ionflux::Altjira::FloatColor tc0;
	Ionflux::Altjira::ByteColor tc1;
	if ((m.getNumRows() < height) 
	    || (m.getNumCols() < width))
	    throw GeoUtilsError("[Image::setValueMatrix] "
	        "Matrix is too small.");
	for (unsigned int x = 0; x < width; x++)
	    for (unsigned int y = 0; y < height; y++)
	    {
	        double v0 = m.v(y, x);
	        tc0.c0 = 0.;
	        tc0.c1 = 0.;
	        tc0.c2 = v0;
	        tc0.alpha = 1.;
	        tc0.space = Ionflux::Altjira::Color::SPACE_HSV;
	        toRGB(tc0);
	        floatToByte(tc0, tc1);
	        PixelData p = pixels + y * rowStride + x * numChannels;
	        p[0] = tc1.c0;
	        p[1] = tc1.c1;
	        p[2] = tc1.c2;
	        p[3] = tc1.alpha;
	    }
}

void Image::getPixelTree(Ionflux::GeoUtils::BoundingBox* target)
{
	Vector3 o0(0.5, 0.5, 0.);
	    Vector3 i0(Vector3::ZERO);
	for (unsigned int i = 0; i < width; i++)
	    for (unsigned int j = 0; j < height; j++)
	    {
	        i0.setElements(i, j, 0);
	        Voxel* v0 = Voxel::create(i0, 1., o0);
	        target->addItem(v0);
	    }
}

void Image::markPixels(Ionflux::GeoUtils::BoxBoundsItemSet& markPixels, 
const Ionflux::Altjira::Color& color, const Ionflux::Altjira::ColorBlender*
blender)
{
	bool ownBlender = false;
	bool useComp = false;
	if (color.getAlpha() != 1)
	{
	    // use compositing.
	    useComp = true;
	    if (blender == 0)
	    {
	        blender = Ionflux::Altjira::BlendSrcOver::create();
	        ownBlender = true;
	    }
	}
	for (BoxBoundsItemSet::iterator i = markPixels.begin(); 
	    i != markPixels.end(); i++)
	{
	    Voxel* v0 = dynamic_cast<Voxel*>(*i);
	    if (v0 == 0)
	    {
	        std::ostringstream status;
	        status << "[Image::markPixels] "
	            "Item is not a voxel: " << (*i)->getString();
	        throw GeoUtilsError(status.str());
	    }
	    Vector3 pos(v0->getCenter());
	    unsigned int x0 = static_cast<unsigned int>(pos.getX0());
	    unsigned int y0 = static_cast<unsigned int>(pos.getX1());
	    /* <---- DEBUG ----- //
	    std::cerr << "[Image::markPixels] DEBUG: "
	        "marking (" << x0 << ", " << y0 << ")" << std::endl;
	    // ----- DEBUG ----> */
	    ByteColor sc0;
	    sc0.space = Ionflux::Altjira::Color::SPACE_RGB;
	    color.getByteColor(sc0);
	    ByteColor rc0;
	    rc0.space = Ionflux::Altjira::Color::SPACE_RGB;
	    if (!useComp)
	        rc0 = sc0;
	    else
	    {
	        ByteColor tc0;
	        tc0.space = Ionflux::Altjira::Color::SPACE_RGB;
	        getPixel(x0, y0, tc0);
	        blender->blend(rc0, sc0, tc0, 255, 255);
	    }
	    setPixel(x0, y0, rc0);
	}
	if (ownBlender)
	    delete blender;
}

Ionflux::GeoUtils::Image& Image::operator=(const Ionflux::GeoUtils::Image& 
other)
{
	Ionflux::Altjira::Drawable::operator=(other);
	Ionflux::GeoUtils::TransformableObject::operator=(other);
	return *this;
}

Ionflux::GeoUtils::Image* Image::copy() const
{
	Image* newImage = create();
	*newImage = *this;
	return newImage;
}

Ionflux::GeoUtils::Image* Image::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Image*>(other);
}

Ionflux::GeoUtils::Image* Image::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Image* newObject = new Image();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Image::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Image.cpp
 * \brief Image implementation.
 */
