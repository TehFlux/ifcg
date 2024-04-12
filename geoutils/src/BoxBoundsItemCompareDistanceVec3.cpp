/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BoxBoundsItemCompareDistanceVec3.cpp  Box bounds item comparison 
 * function object: Distance to point (implementation).
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

#include "geoutils/BoxBoundsItemCompareDistanceVec3.hpp"
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

BoxBoundsItemCompareDistanceVec3::BoxBoundsItemCompareDistanceVec3()
: Ionflux::GeoUtils::BoxBoundsItemCompare(false), reference(Ionflux::GeoUtils::Vector3::ZERO)
{
	// TODO: Nothing ATM. ;-)
}

BoxBoundsItemCompareDistanceVec3::BoxBoundsItemCompareDistanceVec3(const Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3& other)
: Ionflux::GeoUtils::BoxBoundsItemCompare(false), reference(Ionflux::GeoUtils::Vector3::ZERO)
{
	*this = other;
}

BoxBoundsItemCompareDistanceVec3::BoxBoundsItemCompareDistanceVec3(const 
Ionflux::GeoUtils::Vector3& initReference, bool initInvert)
: Ionflux::GeoUtils::BoxBoundsItemCompare(initInvert), 
reference(initReference)
{
	// TODO: Nothing ATM. ;-)
}

BoxBoundsItemCompareDistanceVec3::~BoxBoundsItemCompareDistanceVec3()
{
	// TODO: Nothing ATM. ;-)
}

std::string BoxBoundsItemCompareDistanceVec3::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << reference.getString() << ", " 
	    << invert << "]";
	return status.str();
}

bool 
BoxBoundsItemCompareDistanceVec3::compare(Ionflux::GeoUtils::BoxBoundsItem&
b0, Ionflux::GeoUtils::BoxBoundsItem& b1)
{
	Vector3 c0 = b0.getCenter();
	Vector3 c1 = b1.getCenter();
	double d0 = ::fabs((c0 - reference).norm());
	double d1 = ::fabs((c1 - reference).norm());
	return d0 < d1;
}

Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3* 
BoxBoundsItemCompareDistanceVec3::create(const Ionflux::GeoUtils::Vector3& 
initReference, bool initInvert)
{
	BoxBoundsItemCompareDistanceVec3* c0 = create();
	c0->setReference(initReference);
	c0->setInvert(initInvert);
	return c0;
}

void BoxBoundsItemCompareDistanceVec3::setReference(const 
Ionflux::GeoUtils::Vector3& newReference)
{
	reference = newReference;
}

Ionflux::GeoUtils::Vector3 BoxBoundsItemCompareDistanceVec3::getReference()
const
{
    return reference;
}

Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3& 
BoxBoundsItemCompareDistanceVec3::operator=(const 
Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3& other)
{
    BoxBoundsItemCompare::operator=(other);
    reference = other.reference;
	return *this;
}

Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3* 
BoxBoundsItemCompareDistanceVec3::copy() const
{
    BoxBoundsItemCompareDistanceVec3* newBoxBoundsItemCompareDistanceVec3 = create();
    *newBoxBoundsItemCompareDistanceVec3 = *this;
    return newBoxBoundsItemCompareDistanceVec3;
}

Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3* 
BoxBoundsItemCompareDistanceVec3::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<BoxBoundsItemCompareDistanceVec3*>(other);
}

Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3* 
BoxBoundsItemCompareDistanceVec3::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    BoxBoundsItemCompareDistanceVec3* newObject = new BoxBoundsItemCompareDistanceVec3();
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

/** \file BoxBoundsItemCompareDistanceVec3.cpp
 * \brief Box bounds item comparison function object: Distance to point implementation.
 */
