/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SVGShapeStyleSource.cpp         SVG shape style source (implementation).
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

#include "geoutils/SVGShapeStyleSource.hpp"
#include <sys/time.h>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

SVGShapeStyleSourceClassInfo::SVGShapeStyleSourceClassInfo()
{
	name = "SVGShapeStyleSource";
	desc = "SVG shape style source";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

SVGShapeStyleSourceClassInfo::~SVGShapeStyleSourceClassInfo()
{
}

// run-time type information instance constants
const SVGShapeStyleSourceClassInfo SVGShapeStyleSource::sVGShapeStyleSourceClassInfo;
const Ionflux::ObjectBase::IFClassInfo* SVGShapeStyleSource::CLASS_INFO = &SVGShapeStyleSource::sVGShapeStyleSourceClassInfo;

SVGShapeStyleSource::SVGShapeStyleSource()
: defaultStyle(Ionflux::GeoUtils::DEFAULT_SHAPE_STYLE)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

SVGShapeStyleSource::SVGShapeStyleSource(const Ionflux::GeoUtils::SVGShapeStyleSource& other)
: defaultStyle(Ionflux::GeoUtils::DEFAULT_SHAPE_STYLE)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

SVGShapeStyleSource::~SVGShapeStyleSource()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::GeoUtils::SVGShapeStyle* SVGShapeStyleSource::getStyle(const 
std::string& elementID)
{
	// TODO: Implementation.
	return &defaultStyle;
}

std::string SVGShapeStyleSource::getString() const
{
	ostringstream status;
	status << getClassName();
	return status.str();
}

void SVGShapeStyleSource::setDefaultStyle(const 
Ionflux::GeoUtils::SVGShapeStyle& newDefaultStyle)
{
	defaultStyle = newDefaultStyle;
}

Ionflux::GeoUtils::SVGShapeStyle SVGShapeStyleSource::getDefaultStyle() 
const
{
    return defaultStyle;
}

Ionflux::GeoUtils::SVGShapeStyleSource& 
SVGShapeStyleSource::operator=(const 
Ionflux::GeoUtils::SVGShapeStyleSource& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::GeoUtils::SVGShapeStyleSource* SVGShapeStyleSource::copy() const
{
    SVGShapeStyleSource* newSVGShapeStyleSource = create();
    *newSVGShapeStyleSource = *this;
    return newSVGShapeStyleSource;
}

Ionflux::GeoUtils::SVGShapeStyleSource* 
SVGShapeStyleSource::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<SVGShapeStyleSource*>(other);
}

Ionflux::GeoUtils::SVGShapeStyleSource* 
SVGShapeStyleSource::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    SVGShapeStyleSource* newObject = new SVGShapeStyleSource();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int SVGShapeStyleSource::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file SVGShapeStyleSource.cpp
 * \brief SVG shape style source implementation.
 */
