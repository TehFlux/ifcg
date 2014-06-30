/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Range3.cpp                      Range of values (3D) (implementation).
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

#include "geoutils/Range3.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

Range3ClassInfo::Range3ClassInfo()
{
	name = "Range3";
	desc = "Range of values (3D)";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

Range3ClassInfo::~Range3ClassInfo()
{
}

// run-time type information instance constants
const Range3ClassInfo Range3::range3ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Range3::CLASS_INFO = &Range3::range3ClassInfo;

Range3::Range3()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Range3::Range3(const Ionflux::GeoUtils::Range3& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Range3::Range3(const Ionflux::GeoUtils::Vector3& initCenter, const 
Ionflux::GeoUtils::Vector3* initRadius)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setBounds(initCenter);
	if (initRadius != 0)
	{
	    extend(initCenter + (*initRadius));
	    extend(initCenter - (*initRadius));
	}
}

Range3::Range3(const Ionflux::GeoUtils::Range& initX, const 
Ionflux::GeoUtils::Range& initY, const Ionflux::GeoUtils::Range& initZ)
: x(initX), y(initY), z(initZ)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Range3::Range3(const Ionflux::GeoUtils::Vector2& rx, const 
Ionflux::GeoUtils::Vector2& ry, const Ionflux::GeoUtils::Vector2& rz)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	x.setRMin(rx[0]);
	x.setRMax(rx[1]);
	y.setRMin(ry[0]);
	y.setRMax(ry[1]);
	z.setRMin(rz[0]);
	z.setRMax(rz[1]);
}

Range3::Range3(double xMin, double xMax, double yMin, double yMax, double 
zMin, double zMax)
: x(xMin, xMax), y(yMin, yMax), z(zMin, zMax)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Range3::~Range3()
{
	// TODO: Nothing ATM. ;-)
}

void Range3::extend(const Ionflux::GeoUtils::Range3& other)
{
	extend(other.getCenter() - other.getRadius());
	extend(other.getCenter() + other.getRadius());
}

void Range3::extend(const Ionflux::GeoUtils::Vector3& v)
{
	x.extend(v[0]);
	y.extend(v[1]);
	z.extend(v[2]);
}

Ionflux::GeoUtils::Vector3 Range3::getCenter() const
{
	// TODO: Implementation.
	return Vector3(x.getCenter(), y.getCenter(), z.getCenter());
}

Ionflux::GeoUtils::Vector3 Range3::getRadius() const
{
	// TODO: Implementation.
	return Vector3(x.getRadius(), y.getRadius(), z.getRadius());
}

Ionflux::GeoUtils::Vector3 Range3::getExtent() const
{
	// TODO: Implementation.
	return Vector3(x.getExtent(), y.getExtent(), z.getExtent());
}

double Range3::getExtent(Ionflux::GeoUtils::AxisID axis) const
{
	if (axis == AXIS_X)
	    return x.getExtent();
	if (axis == AXIS_Y)
	    return y.getExtent();
	if (axis == AXIS_Z)
	    return z.getExtent();
	return 0.;
}

Ionflux::GeoUtils::Vector3 Range3::getValue(const 
Ionflux::GeoUtils::Vector3 v) const
{
	// TODO: Implementation.
	return Vector3(x.getValue(v.getX0()), y.getValue(v.getX1()), z.getValue(v.getX2()));
}

Ionflux::GeoUtils::Vector3 Range3::clamp(const Ionflux::GeoUtils::Vector3 
v) const
{
	// TODO: Implementation.
	return Vector3(x.clamp(v.getX0()), y.clamp(v.getX1()), z.clamp(v.getX2()));
}

Ionflux::GeoUtils::Vector3 Range3::getClampedValue(const 
Ionflux::GeoUtils::Vector3 v) const
{
	// TODO: Implementation.
	return clamp(getValue(v));
}

Ionflux::GeoUtils::Range Range3::getAxisRange(Ionflux::GeoUtils::AxisID 
axis) const
{
	if (axis == AXIS_X)
	    return x;
	if (axis == AXIS_Y)
	    return y;
	if (axis != AXIS_Z)
	{
	    ostringstream message;
	    message << "Invalid axis: " << axis;
	    throw GeoUtilsError(message.str());
	}
	return z;
}

void Range3::setBounds(const Ionflux::GeoUtils::Vector3& v)
{
	x.setBounds(v[0], v[0]);
	y.setBounds(v[1], v[1]);
	z.setBounds(v[2], v[2]);
}

void Range3::setBounds(const Ionflux::GeoUtils::Range3& other)
{
	setBounds(other.getCenter());
	extend(other);
}

Ionflux::GeoUtils::RangeCompResult3 Range3::compare3(const 
Ionflux::GeoUtils::Range3& other, double t) const
{
	RangeCompResult3 result;
	result.x = x.compare(other.x, t);
	result.y = y.compare(other.y, t);
	result.z = z.compare(other.z, t);
	return result;
}

Ionflux::GeoUtils::RangeCompResult Range3::compare(const 
Ionflux::GeoUtils::Range3& other, double t) const
{
	RangeCompResult3 c = compare3(other, t);
	if ((c.x == c.y) && (c.x == c.z))
	    // This covers the equality and disjoint on all axes cases.
	    return c.x;
	/* Check whether the first range contains the other range with equal 
	   ranges in some dimension(s). */
	bool result = true;
	for (int i = 0; i < 3; i++)
	{
	    RangeCompResult v;
	    if (i == 0)
	        v = c.x;
	    else 
	    if (i == 1)
	        v = c.y;
	    else 
	        v = c.z;
	    if (v == RANGE_DISJOINT)
	        // Disjoint on one axis means disjoint ranges.
	        return RANGE_DISJOINT;
	    else
	    if ((v != RANGE_FIRST_CONTAINS) 
	        && (v != RANGE_EQUAL))
	        result = false;
	}
	if (result)
	    return RANGE_FIRST_CONTAINS;
	/* Check whether the other range contains the first range with equal 
	   ranges in some dimension(s). */
	result = true;
	for (int i = 0; i < 3; i++)
	{
	    RangeCompResult v;
	    if (i == 0)
	        v = c.x;
	    else 
	    if (i == 1)
	        v = c.y;
	    else 
	        v = c.z;
	    if ((v != RANGE_OTHER_CONTAINS) 
	        && (v != RANGE_EQUAL))
	    {
	        result = false;
	        break;
	    }
	}
	if (result)
	    return RANGE_OTHER_CONTAINS;
	return RANGE_OVERLAP;
}

bool Range3::isInRange(const Ionflux::GeoUtils::Vector3& v, double t) const
{
	// TODO: Implementation.
	return (x.isInRange(v[0], t) 
    && y.isInRange(v[1], t) 
    && z.isInRange(v[2], t));
}

Ionflux::GeoUtils::AxisTriple Range3::getAxisOrder() const
{
	// TODO: Implementation.
	return getRadius().getAxisOrder();
}

bool Range3::operator==(const Ionflux::GeoUtils::Range3& other) const
{
	if (!((x == other.x) && (y == other.y) && (z == other.z)))
	        return false;
	return true;
}

bool Range3::operator!=(const Ionflux::GeoUtils::Range3& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

std::string Range3::getString() const
{
	ostringstream state;
	state << getClassName() << "[" << x.getString() 
	    << ", " << y.getString() << ", " << z.getString() << "]";
	return state.str();
}

void Range3::setX(const Ionflux::GeoUtils::Range& newX)
{
	x = newX;
}

Ionflux::GeoUtils::Range Range3::getX() const
{
    return x;
}

void Range3::setY(const Ionflux::GeoUtils::Range& newY)
{
	y = newY;
}

Ionflux::GeoUtils::Range Range3::getY() const
{
    return y;
}

void Range3::setZ(const Ionflux::GeoUtils::Range& newZ)
{
	z = newZ;
}

Ionflux::GeoUtils::Range Range3::getZ() const
{
    return z;
}

Ionflux::GeoUtils::Range3& Range3::operator=(const 
Ionflux::GeoUtils::Range3& other)
{
if (this == &other)
    return *this;
setX(other.getX());
setY(other.getY());
setZ(other.getZ());
	return *this;
}

Ionflux::GeoUtils::Range3* Range3::copy() const
{
    Range3* newRange3 = create();
    *newRange3 = *this;
    return newRange3;
}

Ionflux::GeoUtils::Range3* Range3::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Range3*>(other);
}

Ionflux::GeoUtils::Range3* Range3::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Range3* newObject = new Range3();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Range3::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Range3.cpp
 * \brief Range of values (3D) implementation.
 */
