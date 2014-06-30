/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polygon3CompareAxis.cpp         Polygon comparison function object: Axis
 * coordinate (implementation).
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

#include "geoutils/Polygon3CompareAxis.hpp"
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

Polygon3CompareAxisClassInfo::Polygon3CompareAxisClassInfo()
{
	name = "Polygon3CompareAxis";
	desc = "Polygon comparison function object: Axis coordinate";
}

Polygon3CompareAxisClassInfo::~Polygon3CompareAxisClassInfo()
{
}

// run-time type information instance constants
const Polygon3CompareAxisClassInfo Polygon3CompareAxis::polygon3CompareAxisClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Polygon3CompareAxis::CLASS_INFO = &Polygon3CompareAxis::polygon3CompareAxisClassInfo;

Polygon3CompareAxis::Polygon3CompareAxis()
: Ionflux::GeoUtils::Polygon3Compare(true), axis(Ionflux::GeoUtils::AXIS_Z)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Polygon3CompareAxis::Polygon3CompareAxis(const Ionflux::GeoUtils::Polygon3CompareAxis& other)
: Ionflux::GeoUtils::Polygon3Compare(true), axis(Ionflux::GeoUtils::AXIS_Z)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Polygon3CompareAxis::Polygon3CompareAxis(Ionflux::GeoUtils::AxisID 
initAxis, bool initInvert)
: Ionflux::GeoUtils::Polygon3Compare(initInvert), axis(initAxis)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Polygon3CompareAxis::~Polygon3CompareAxis()
{
	// TODO: Nothing ATM. ;-)
}

std::string Polygon3CompareAxis::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << axisToString(axis) << ", " 
	    << invert << "]";
	return status.str();
}

bool Polygon3CompareAxis::compare(Ionflux::GeoUtils::Polygon3& p0, 
Ionflux::GeoUtils::Polygon3& p1)
{
	Vector3 b0 = p0.getBarycenter();
	Vector3 b1 = p1.getBarycenter();
	return b0.getElement(axis) < b1.getElement(axis);
}

Ionflux::GeoUtils::Polygon3CompareAxis* 
Polygon3CompareAxis::create(Ionflux::GeoUtils::AxisID initAxis, bool 
initInvert)
{
	Polygon3CompareAxis* c0 = create();
	c0->setAxis(initAxis);
	c0->setInvert(initInvert);
	return c0;
}

void Polygon3CompareAxis::setAxis(Ionflux::GeoUtils::AxisID newAxis)
{
	axis = newAxis;
}

Ionflux::GeoUtils::AxisID Polygon3CompareAxis::getAxis() const
{
    return axis;
}

Ionflux::GeoUtils::Polygon3CompareAxis& 
Polygon3CompareAxis::operator=(const 
Ionflux::GeoUtils::Polygon3CompareAxis& other)
{
    Polygon3Compare::operator=(other);
    axis = other.axis;
	return *this;
}

Ionflux::GeoUtils::Polygon3CompareAxis* Polygon3CompareAxis::copy() const
{
    Polygon3CompareAxis* newPolygon3CompareAxis = create();
    *newPolygon3CompareAxis = *this;
    return newPolygon3CompareAxis;
}

Ionflux::GeoUtils::Polygon3CompareAxis* 
Polygon3CompareAxis::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Polygon3CompareAxis*>(other);
}

Ionflux::GeoUtils::Polygon3CompareAxis* 
Polygon3CompareAxis::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Polygon3CompareAxis* newObject = new Polygon3CompareAxis();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Polygon3CompareAxis::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Polygon3CompareAxis.cpp
 * \brief Polygon comparison function object: Axis coordinate implementation.
 */
