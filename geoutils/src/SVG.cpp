/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SVG.cpp                         SVG (implementation).
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

#include "geoutils/SVG.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <librsvg/rsvg.h>
#include <librsvg/rsvg-cairo.h>
#include "geoutils/Polygon3.hpp"
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

SVGClassInfo::SVGClassInfo()
{
	name = "SVG";
	desc = "SVG";
	baseClassInfo.push_back(Ionflux::GeoUtils::TransformableObject::CLASS_INFO);
}

SVGClassInfo::~SVGClassInfo()
{
}

// public member constants
const Ionflux::GeoUtils::SVGType SVG::TYPE_UNDEFINED = 0;
const Ionflux::GeoUtils::SVGType SVG::TYPE_FILE = 1;
const Ionflux::GeoUtils::SVGType SVG::TYPE_DATA = 2;

// run-time type information instance constants
const SVGClassInfo SVG::sVGClassInfo;
const Ionflux::ObjectBase::IFClassInfo* SVG::CLASS_INFO = &SVG::sVGClassInfo;

SVG::SVG()
: type(TYPE_UNDEFINED)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

SVG::SVG(const Ionflux::GeoUtils::SVG& other)
: type(TYPE_UNDEFINED)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

SVG::SVG(const std::string& initSource, Ionflux::GeoUtils::SVGType 
initType)
: source(initSource), type(initType)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

SVG::~SVG()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::GeoUtils::Range3 SVG::getSVGBounds()
{
	Range3 result;
	result.setBounds(Vector3::ZERO);
	if (type == TYPE_UNDEFINED)
	    throw GeoUtilsError("[SVG::getSVGBounds] "
	        "Cannot determine bounds for undefined SVG source!");
	g_type_init();
	RsvgHandle* rsvg0 = 0;
	if (type == TYPE_DATA)
	    rsvg0 = rsvg_handle_new_from_data(
	        reinterpret_cast<const guint8*>(source.c_str()), 
	        source.size(), 0);
	else
	if (type == TYPE_FILE)
	    rsvg0 = rsvg_handle_new_from_file(
	        reinterpret_cast<const gchar*>(source.c_str()), 0);
	else
	{
	    std::ostringstream status;
	    status << "[SVG::getSVGBounds] Unknown SVG source type (" 
	        << type << ")!";
	    throw GeoUtilsError(status.str());
	}
	if (rsvg0 == 0)
	{
	    throw GeoUtilsError("[SVG::getSVGBounds] "
	        "Could not create RSVG handle!");
	}
	RsvgDimensionData dd0;
	rsvg_handle_get_dimensions(rsvg0, &dd0);
	result.extend(Vector3(dd0.width, dd0.height, 0.));
	g_object_unref(rsvg0);
	return result;
}

void SVG::recalculateBounds()
{
	TransformableObject::recalculateBounds();
	if (!useTransform && !useVI)
	{
	    *boundsCache = getSVGBounds();
	    return;
	}
	// Adjust for transformation.
	/* TODO: Set bounds cache to transformed SVG bounds.
	         (This is unfortunately not trivial. For now, we just use 
	          a box polygon and apply the transformation. \) */
	Range3 b0 = getSVGBounds();
	Polygon3* p0 = Polygon3::square();
	/* The polygon is created in the XZ-plane by default, but we need it 
	   to be in the XY-plane. */
	p0->rotate(0.5 * M_PI, AXIS_X);
	// Transform the polygon to match the bounds of the SVG.
	p0->scale(Vector3(2. * b0.getX().getRadius(), 
	    2. * b0.getY().getRadius(), 1.));
	p0->translate(b0.getCenter());
	// Apply the transformations.
	if (useTransform)
	    p0->transform(transformMatrix);
	// NOTE: VI transform is not supported for SVG objects.
	p0->applyTransform();
	*boundsCache = p0->getBounds();
	delete p0;
}

Ionflux::GeoUtils::Vector3 SVG::getBarycenter()
{
	if (boundsCache == 0)
	    recalculateBounds();
	return boundsCache->getCenter();
}

Ionflux::GeoUtils::SVG& SVG::duplicate()
{
	// TODO: Implementation.
	return *copy();
}

std::string SVG::getString() const
{
	ostringstream status;
	status << getClassName();
	if (type == TYPE_FILE)
	    status << "[" << source << "]";
	return status.str();
}

void SVG::setSource(const std::string& newSource)
{
	source = newSource;
}

std::string SVG::getSource() const
{
	return source;
}

void SVG::setType(Ionflux::GeoUtils::SVGType newType)
{
	type = newType;
}

Ionflux::GeoUtils::SVGType SVG::getType() const
{
	return type;
}

Ionflux::GeoUtils::SVG& SVG::operator=(const Ionflux::GeoUtils::SVG& other)
{
    TransformableObject::operator=(other);
    source = other.source;
    type = other.type;
	return *this;
}

Ionflux::GeoUtils::SVG* SVG::copy() const
{
    SVG* newSVG = create();
    *newSVG = *this;
    return newSVG;
}

Ionflux::GeoUtils::SVG* SVG::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<SVG*>(other);
}

Ionflux::GeoUtils::SVG* SVG::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    SVG* newObject = new SVG();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file SVG.cpp
 * \brief SVG implementation.
 */
