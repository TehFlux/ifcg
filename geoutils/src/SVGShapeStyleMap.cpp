/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SVGShapeStyleMap.cpp            SVG shape style map (implementation).
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

#include "geoutils/SVGShapeStyleMap.hpp"
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

SVGShapeStyleMapClassInfo::SVGShapeStyleMapClassInfo()
{
	name = "SVGShapeStyleMap";
	desc = "SVG shape style map";
}

SVGShapeStyleMapClassInfo::~SVGShapeStyleMapClassInfo()
{
}

// run-time type information instance constants
const SVGShapeStyleMapClassInfo SVGShapeStyleMap::sVGShapeStyleMapClassInfo;
const Ionflux::ObjectBase::IFClassInfo* SVGShapeStyleMap::CLASS_INFO = &SVGShapeStyleMap::sVGShapeStyleMapClassInfo;

SVGShapeStyleMap::SVGShapeStyleMap()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

SVGShapeStyleMap::SVGShapeStyleMap(const Ionflux::GeoUtils::SVGShapeStyleMap& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

SVGShapeStyleMap::~SVGShapeStyleMap()
{
	clearStyles();
	// TODO: Nothing ATM. ;-)
}

std::string SVGShapeStyleMap::getString() const
{
	ostringstream status;
	status << getClassName();
	return status.str();
}

unsigned int SVGShapeStyleMap::getNumStyles() const
{
	return styleMap.size();
}

Ionflux::GeoUtils::SVGShapeStyle* SVGShapeStyleMap::getStyle(const 
std::string& elementKey) const
{
	std::map<std::string, Ionflux::GeoUtils::SVGShapeStyle*>::const_iterator i = styleMap.find(elementKey);
	if (i != styleMap.end())
		return (*i).second;
	return 0;
}

std::map<std::string, Ionflux::GeoUtils::SVGShapeStyle*>& 
SVGShapeStyleMap::getStyles()
{
	return styleMap;
}

void SVGShapeStyleMap::addStyle(const std::string& elementKey, 
Ionflux::GeoUtils::SVGShapeStyle* addElement)
{
	Ionflux::GeoUtils::SVGShapeStyle* theStyle = getStyle(elementKey);
	if (theStyle != 0)
		return;
	styleMap[elementKey] = addElement;
}

void SVGShapeStyleMap::removeStyle(const std::string& elementKey)
{
	std::map<std::string, Ionflux::GeoUtils::SVGShapeStyle*>::iterator i = styleMap.find(elementKey);
	if (i != styleMap.end())
	{
		styleMap.erase(i);
	}
}

void SVGShapeStyleMap::clearStyles()
{
	styleMap.clear();
}

Ionflux::GeoUtils::SVGShapeStyleMap& SVGShapeStyleMap::operator=(const 
Ionflux::GeoUtils::SVGShapeStyleMap& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::GeoUtils::SVGShapeStyleMap* SVGShapeStyleMap::copy() const
{
    SVGShapeStyleMap* newSVGShapeStyleMap = create();
    *newSVGShapeStyleMap = *this;
    return newSVGShapeStyleMap;
}

Ionflux::GeoUtils::SVGShapeStyleMap* 
SVGShapeStyleMap::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<SVGShapeStyleMap*>(other);
}

Ionflux::GeoUtils::SVGShapeStyleMap* 
SVGShapeStyleMap::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    SVGShapeStyleMap* newObject = new SVGShapeStyleMap();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int SVGShapeStyleMap::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file SVGShapeStyleMap.cpp
 * \brief SVG shape style map implementation.
 */
