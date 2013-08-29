/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BoxBoundsItemCompareDistancePlane3.cpp  Box bounds item comparison 
 * function object: Distance to plane (implementation).
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

#include "geoutils/BoxBoundsItemCompareDistancePlane3.hpp"
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

BoxBoundsItemCompareDistancePlane3::BoxBoundsItemCompareDistancePlane3()
: Ionflux::GeoUtils::BoxBoundsItemCompare(false), reference(Ionflux::GeoUtils::Plane3::XY)
{
	// TODO: Nothing ATM. ;-)
}

BoxBoundsItemCompareDistancePlane3::BoxBoundsItemCompareDistancePlane3(const Ionflux::GeoUtils::BoxBoundsItemCompareDistancePlane3& other)
: Ionflux::GeoUtils::BoxBoundsItemCompare(false), reference(Ionflux::GeoUtils::Plane3::XY)
{
	*this = other;
}

BoxBoundsItemCompareDistancePlane3::BoxBoundsItemCompareDistancePlane3(const
Ionflux::GeoUtils::Plane3& initReference, bool initInvert)
: Ionflux::GeoUtils::BoxBoundsItemCompare(initInvert), 
reference(initReference)
{
	// TODO: Nothing ATM. ;-)
}

BoxBoundsItemCompareDistancePlane3::~BoxBoundsItemCompareDistancePlane3()
{
	// TODO: Nothing ATM. ;-)
}

std::string BoxBoundsItemCompareDistancePlane3::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << reference.getString() << ", " 
	    << invert << "]";
	return status.str();
}

bool 
BoxBoundsItemCompareDistancePlane3::compare(Ionflux::GeoUtils::BoxBoundsItem&
b0, Ionflux::GeoUtils::BoxBoundsItem& b1)
{
	Vector3 c0 = b0.getCenter();
	Vector3 c1 = b1.getCenter();
	double d0 = c0.distanceToPlane(reference);
	double d1 = c1.distanceToPlane(reference);
	return d0 < d1;
}

Ionflux::GeoUtils::BoxBoundsItemCompareDistancePlane3* 
BoxBoundsItemCompareDistancePlane3::create(const Ionflux::GeoUtils::Plane3&
initReference, bool initInvert)
{
	BoxBoundsItemCompareDistancePlane3* c0 = create();
	c0->setReference(initReference);
	c0->setInvert(initInvert);
	return c0;
}

void BoxBoundsItemCompareDistancePlane3::setReference(const 
Ionflux::GeoUtils::Plane3& newReference)
{
	reference = newReference;
}

Ionflux::GeoUtils::Plane3 
BoxBoundsItemCompareDistancePlane3::getReference() const
{
	return reference;
}

Ionflux::GeoUtils::BoxBoundsItemCompareDistancePlane3& 
BoxBoundsItemCompareDistancePlane3::operator=(const 
Ionflux::GeoUtils::BoxBoundsItemCompareDistancePlane3& other)
{
    BoxBoundsItemCompare::operator=(other);
    reference = other.reference;
	return *this;
}

Ionflux::GeoUtils::BoxBoundsItemCompareDistancePlane3* 
BoxBoundsItemCompareDistancePlane3::copy() const
{
    BoxBoundsItemCompareDistancePlane3* newBoxBoundsItemCompareDistancePlane3 = create();
    *newBoxBoundsItemCompareDistancePlane3 = *this;
    return newBoxBoundsItemCompareDistancePlane3;
}

Ionflux::GeoUtils::BoxBoundsItemCompareDistancePlane3* 
BoxBoundsItemCompareDistancePlane3::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<BoxBoundsItemCompareDistancePlane3*>(other);
}

Ionflux::GeoUtils::BoxBoundsItemCompareDistancePlane3* 
BoxBoundsItemCompareDistancePlane3::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    BoxBoundsItemCompareDistancePlane3* newObject = new BoxBoundsItemCompareDistancePlane3();
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

/** \file BoxBoundsItemCompareDistancePlane3.cpp
 * \brief Box bounds item comparison function object: Distance to plane implementation.
 */
