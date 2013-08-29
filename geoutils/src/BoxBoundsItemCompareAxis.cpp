/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BoxBoundsItemCompareAxis.cpp    Box bounds item comparison function 
 * object: Axis coordinate (implementation).
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

#include "geoutils/BoxBoundsItemCompareAxis.hpp"
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

BoxBoundsItemCompareAxis::BoxBoundsItemCompareAxis()
: Ionflux::GeoUtils::BoxBoundsItemCompare(true), axis(Ionflux::GeoUtils::AXIS_Z)
{
	// TODO: Nothing ATM. ;-)
}

BoxBoundsItemCompareAxis::BoxBoundsItemCompareAxis(const Ionflux::GeoUtils::BoxBoundsItemCompareAxis& other)
: Ionflux::GeoUtils::BoxBoundsItemCompare(true), axis(Ionflux::GeoUtils::AXIS_Z)
{
	*this = other;
}

BoxBoundsItemCompareAxis::BoxBoundsItemCompareAxis(Ionflux::GeoUtils::AxisID
initAxis, bool initInvert)
: Ionflux::GeoUtils::BoxBoundsItemCompare(initInvert), axis(initAxis)
{
	// TODO: Nothing ATM. ;-)
}

BoxBoundsItemCompareAxis::~BoxBoundsItemCompareAxis()
{
	// TODO: Nothing ATM. ;-)
}

std::string BoxBoundsItemCompareAxis::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << axisToString(axis) << ", " 
	    << invert << "]";
	return status.str();
}

bool BoxBoundsItemCompareAxis::compare(Ionflux::GeoUtils::BoxBoundsItem& 
b0, Ionflux::GeoUtils::BoxBoundsItem& b1)
{
	Vector3 c0 = b0.getCenter();
	Vector3 c1 = b1.getCenter();
	return c0.getElement(axis) < c1.getElement(axis);
}

Ionflux::GeoUtils::BoxBoundsItemCompareAxis* 
BoxBoundsItemCompareAxis::create(Ionflux::GeoUtils::AxisID initAxis, bool 
initInvert)
{
	BoxBoundsItemCompareAxis* c0 = create();
	c0->setAxis(initAxis);
	c0->setInvert(initInvert);
	return c0;
}

void BoxBoundsItemCompareAxis::setAxis(Ionflux::GeoUtils::AxisID newAxis)
{
	axis = newAxis;
}

Ionflux::GeoUtils::AxisID BoxBoundsItemCompareAxis::getAxis() const
{
	return axis;
}

Ionflux::GeoUtils::BoxBoundsItemCompareAxis& 
BoxBoundsItemCompareAxis::operator=(const 
Ionflux::GeoUtils::BoxBoundsItemCompareAxis& other)
{
    BoxBoundsItemCompare::operator=(other);
    axis = other.axis;
	return *this;
}

Ionflux::GeoUtils::BoxBoundsItemCompareAxis* 
BoxBoundsItemCompareAxis::copy() const
{
    BoxBoundsItemCompareAxis* newBoxBoundsItemCompareAxis = create();
    *newBoxBoundsItemCompareAxis = *this;
    return newBoxBoundsItemCompareAxis;
}

Ionflux::GeoUtils::BoxBoundsItemCompareAxis* 
BoxBoundsItemCompareAxis::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<BoxBoundsItemCompareAxis*>(other);
}

Ionflux::GeoUtils::BoxBoundsItemCompareAxis* 
BoxBoundsItemCompareAxis::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    BoxBoundsItemCompareAxis* newObject = new BoxBoundsItemCompareAxis();
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

/** \file BoxBoundsItemCompareAxis.cpp
 * \brief Box bounds item comparison function object: Axis coordinate implementation.
 */
