/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SVGImageProperties.cpp          SVG image properties (implementation).
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

#include "geoutils/SVGImageProperties.hpp"
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

SVGImagePropertiesClassInfo::SVGImagePropertiesClassInfo()
{
	name = "SVGImageProperties";
	desc = "SVG image properties";
}

SVGImagePropertiesClassInfo::~SVGImagePropertiesClassInfo()
{
}

// run-time type information instance constants
const SVGImagePropertiesClassInfo SVGImageProperties::sVGImagePropertiesClassInfo;
const Ionflux::ObjectBase::IFClassInfo* SVGImageProperties::CLASS_INFO = &SVGImageProperties::sVGImagePropertiesClassInfo;

SVGImageProperties::SVGImageProperties()
: styleSource(0), svgTemplate(Ionflux::GeoUtils::SVG_TEMPLATE)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setStyleSource(SVGShapeStyleSource::create());
}

SVGImageProperties::SVGImageProperties(const Ionflux::GeoUtils::SVGImageProperties& other)
: styleSource(0), svgTemplate(Ionflux::GeoUtils::SVG_TEMPLATE)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

SVGImageProperties::SVGImageProperties(Ionflux::GeoUtils::SVGShapeStyleSource*
initStyleSource, const std::string& initSVGTemplate)
: styleSource(0), svgTemplate(Ionflux::GeoUtils::SVG_TEMPLATE)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initStyleSource == 0)
	    setStyleSource(SVGShapeStyleSource::create());
	else
	    setStyleSource(initStyleSource);
}

SVGImageProperties::~SVGImageProperties()
{
	// TODO: Nothing ATM. ;-)
}

std::string SVGImageProperties::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << width 
	    << height << ", " << origin << "]";
	return status.str();
}

void 
SVGImageProperties::setStyleSource(Ionflux::GeoUtils::SVGShapeStyleSource* 
newStyleSource)
{
	if (styleSource == newStyleSource)
		return;
    if (newStyleSource != 0)
        addLocalRef(newStyleSource);
	if (styleSource != 0)
		removeLocalRef(styleSource);
	styleSource = newStyleSource;
}

Ionflux::GeoUtils::SVGShapeStyleSource* 
SVGImageProperties::getStyleSource() const
{
    return styleSource;
}

void SVGImageProperties::setSvgTemplate(const std::string& newSvgTemplate)
{
	svgTemplate = newSvgTemplate;
}

std::string SVGImageProperties::getSvgTemplate() const
{
    return svgTemplate;
}

Ionflux::GeoUtils::SVGImageProperties& SVGImageProperties::operator=(const 
Ionflux::GeoUtils::SVGImageProperties& other)
{
    height = other.height;
    width = other.width;
    origin = other.origin;
	return *this;
}

Ionflux::GeoUtils::SVGImageProperties* SVGImageProperties::copy() const
{
    SVGImageProperties* newSVGImageProperties = create();
    *newSVGImageProperties = *this;
    return newSVGImageProperties;
}

Ionflux::GeoUtils::SVGImageProperties* 
SVGImageProperties::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<SVGImageProperties*>(other);
}

Ionflux::GeoUtils::SVGImageProperties* 
SVGImageProperties::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    SVGImageProperties* newObject = new SVGImageProperties();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int SVGImageProperties::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file SVGImageProperties.cpp
 * \brief SVG image properties implementation.
 */
