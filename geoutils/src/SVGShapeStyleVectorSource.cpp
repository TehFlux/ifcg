/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SVGShapeStyleVectorSource.cpp   SVG shape style vector source 
 * (implementation).
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

#include "geoutils/SVGShapeStyleVectorSource.hpp"
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

SVGShapeStyleVectorSourceClassInfo::SVGShapeStyleVectorSourceClassInfo()
{
	name = "SVGShapeStyleVectorSource";
	desc = "SVG shape style vector source";
}

SVGShapeStyleVectorSourceClassInfo::~SVGShapeStyleVectorSourceClassInfo()
{
}

// run-time type information instance constants
const SVGShapeStyleVectorSourceClassInfo SVGShapeStyleVectorSource::sVGShapeStyleVectorSourceClassInfo;
const Ionflux::ObjectBase::IFClassInfo* SVGShapeStyleVectorSource::CLASS_INFO = &SVGShapeStyleVectorSource::sVGShapeStyleVectorSourceClassInfo;

SVGShapeStyleVectorSource::SVGShapeStyleVectorSource()
: currentStyle(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

SVGShapeStyleVectorSource::SVGShapeStyleVectorSource(const Ionflux::GeoUtils::SVGShapeStyleVectorSource& other)
: currentStyle(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

SVGShapeStyleVectorSource::~SVGShapeStyleVectorSource()
{
	clearStyles();
	// TODO: Nothing ATM. ;-)
}

Ionflux::GeoUtils::SVGShapeStyle* SVGShapeStyleVectorSource::getStyle(const
std::string& elementID)
{
	SVGShapeStyle* result = getStyle(currentStyle % styles.size());
	currentStyle++;
	return result;
}

std::string SVGShapeStyleVectorSource::getString() const
{
	ostringstream status;
	status << getClassName();
	return status.str();
}

void SVGShapeStyleVectorSource::setCurrentStyle(unsigned int 
newCurrentStyle)
{
	currentStyle = newCurrentStyle;
}

unsigned int SVGShapeStyleVectorSource::getCurrentStyle() const
{
    return currentStyle;
}

unsigned int SVGShapeStyleVectorSource::getNumStyles() const
{
    return styles.size();
}

Ionflux::GeoUtils::SVGShapeStyle* 
SVGShapeStyleVectorSource::getStyle(unsigned int elementIndex) const
{
    if (elementIndex < styles.size())
		return styles[elementIndex];
	return 0;
}

int SVGShapeStyleVectorSource::findStyle(Ionflux::GeoUtils::SVGShapeStyle* 
needle, unsigned int occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::SVGShapeStyle* currentStyle = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < styles.size()))
	{
		currentStyle = styles[i];
		if (currentStyle == needle)
        {
            if (occurence == 1)
			    found = true;
            else
                occurence--;
		} else
			i++;
	}
	if (found)
        return i;
	return -1;
}

std::vector<Ionflux::GeoUtils::SVGShapeStyle*>& 
SVGShapeStyleVectorSource::getStyles()
{
    return styles;
}

void SVGShapeStyleVectorSource::addStyle(Ionflux::GeoUtils::SVGShapeStyle* 
addElement)
{
	styles.push_back(addElement);
}

void 
SVGShapeStyleVectorSource::removeStyle(Ionflux::GeoUtils::SVGShapeStyle* 
removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::SVGShapeStyle* currentStyle = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < styles.size()))
	{
		currentStyle = styles[i];
		if (currentStyle == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		styles.erase(styles.begin() + i);
	}
}

void SVGShapeStyleVectorSource::removeStyleIndex(unsigned int removeIndex)
{
    if (removeIndex > styles.size())
        return;
    styles.erase(styles.begin() + removeIndex);
}

void SVGShapeStyleVectorSource::clearStyles()
{
    styles.clear();
}

Ionflux::GeoUtils::SVGShapeStyleVectorSource& 
SVGShapeStyleVectorSource::operator=(const 
Ionflux::GeoUtils::SVGShapeStyleVectorSource& other)
{
	return *this;
}

Ionflux::GeoUtils::SVGShapeStyleVectorSource* 
SVGShapeStyleVectorSource::copy() const
{
    SVGShapeStyleVectorSource* newSVGShapeStyleVectorSource = create();
    *newSVGShapeStyleVectorSource = *this;
    return newSVGShapeStyleVectorSource;
}

Ionflux::GeoUtils::SVGShapeStyleVectorSource* 
SVGShapeStyleVectorSource::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<SVGShapeStyleVectorSource*>(other);
}

Ionflux::GeoUtils::SVGShapeStyleVectorSource* 
SVGShapeStyleVectorSource::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    SVGShapeStyleVectorSource* newObject = new SVGShapeStyleVectorSource();
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

/** \file SVGShapeStyleVectorSource.cpp
 * \brief SVG shape style vector source implementation.
 */
