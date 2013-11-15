/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Point.cpp                       Point (implementation).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFMapping - Ionflux Mapping Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFMapping - Ionflux Mapping Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "ifmapping/Point.hpp"
#include <sstream>
#include "ifmapping/MappingError.hpp"
#include "ifmapping/utils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

PointClassInfo::PointClassInfo()
{
	name = "Point";
	desc = "Point";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

PointClassInfo::~PointClassInfo()
{
}

// public member constants
const Ionflux::Mapping::Point Point::ORIGIN = Ionflux::Mapping::Point(0., 0., 0.);
const Ionflux::Mapping::Point Point::DEFAULT_STD_DEV = Ionflux::Mapping::Point(1., 1., 1.);
const Ionflux::Mapping::Point Point::ONES = Ionflux::Mapping::Point(1., 1., 1.);

// run-time type information instance constants
const PointClassInfo Point::pointClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Point::CLASS_INFO = &Point::pointClassInfo;

Point::Point()
: x(0.), y(0.), z(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Point::Point(const Ionflux::Mapping::Point& other)
: x(0.), y(0.), z(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Point::Point(Ionflux::Mapping::MappingValue initX, 
Ionflux::Mapping::MappingValue initY, Ionflux::Mapping::MappingValue initZ)
: x(initX), y(initY), z(initZ)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Point::Point(const Ionflux::ObjectBase::DoubleVector& initCoords)
: x(0.), y(0.), z(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setCoords(initCoords);
}

Point::~Point()
{
	// TODO: Nothing ATM. ;-)
}

void Point::setCoords(const Ionflux::ObjectBase::DoubleVector& newCoords)
{
	if (newCoords.size() == 0)
	    return;
	if (newCoords.size() >= 3)
	    z = newCoords[2];
	if (newCoords.size() >= 2)
	    y = newCoords[1];
	x = newCoords[0];
}

void Point::getCoords(Ionflux::ObjectBase::DoubleVector& target) const
{
	target.clear();
	target.push_back(x);
	target.push_back(y);
	target.push_back(z);
}

Ionflux::Mapping::MappingValue Point::getCoord(int index) const
{
	// TODO: Implementation.
	return (*this)[index];;
}

void Point::setCoord(int index, Ionflux::Mapping::MappingValue value)
{
	if ((index < 0) || (index > 3))
	{
	    ostringstream message;
	    message << "Index out of range: " << index;
	    throw MappingError(message.str());
	}
	if (index == 0)
	    x = value;
	else 
	if (index == 1)
	    y = value;
}

Ionflux::Mapping::Point Point::interpolate(const Ionflux::Mapping::Point& 
other, Ionflux::Mapping::MappingValue t) const
{
	Point result;
	result.x = (other.x - x) * t + x;
	result.y = (other.y - y) * t + y;
	result.z = (other.z - z) * t + z;
	return result;
}

Ionflux::Mapping::Point Point::operator+(const Ionflux::Mapping::Point& 
other) const
{
	Point result(other.x + x, other.y + y, other.z + z);
	return result;
}

Ionflux::Mapping::Point Point::operator*(const Ionflux::Mapping::Point& 
other) const
{
	Point result(other.x * x, other.y * y, other.z * z);
	return result;
}

bool Point::operator==(const Ionflux::Mapping::Point& other) const
{
	if (!((x == other.x) && (y == other.y) && (z == other.z)))
	        return false;
	return true;
}

bool Point::operator!=(const Ionflux::Mapping::Point& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

Ionflux::Mapping::MappingValue Point::operator[](int index) const
{
	if ((index < 0) || (index > 3))
	{
	    ostringstream message;
	    message << "Index out of range: " << index;
	    throw MappingError(message.str());
	}
	Ionflux::Mapping::MappingValue result;
	if (index == 0)
	    result = x;
	if (index == 1)
	    result = y;
	if (index == 2)
	    result = z;
	return result;
}

Ionflux::Mapping::Point Point::getRandom()
{
	// TODO: Implementation.
	return Point(getRandomDouble(), getRandomDouble(), getRandomDouble());
}

Ionflux::Mapping::Point Point::getRandomNorm(const Ionflux::Mapping::Point&
mean, const Ionflux::Mapping::Point& stdDev)
{
	// TODO: Implementation.
	return Point(Ionflux::Mapping::getRandomNorm(mean.x, stdDev.x), Ionflux::Mapping::getRandomNorm(mean.y, stdDev.y), Ionflux::Mapping::getRandomNorm(mean.z, stdDev.z));
}

std::string Point::getString() const
{
	ostringstream state;
	state << getClassName() << "[" << x << ", " << y << ", " << z << "]";
	return state.str();
}

void Point::setX(Ionflux::Mapping::MappingValue newX)
{
	x = newX;
}

Ionflux::Mapping::MappingValue Point::getX() const
{
    return x;
}

void Point::setY(Ionflux::Mapping::MappingValue newY)
{
	y = newY;
}

Ionflux::Mapping::MappingValue Point::getY() const
{
    return y;
}

void Point::setZ(Ionflux::Mapping::MappingValue newZ)
{
	z = newZ;
}

Ionflux::Mapping::MappingValue Point::getZ() const
{
    return z;
}

Ionflux::Mapping::Point& Point::operator=(const Ionflux::Mapping::Point& 
other)
{
    x = other.x;
    y = other.y;
    z = other.z;
	return *this;
}

Ionflux::Mapping::Point* Point::copy() const
{
    Point* newPoint = create();
    *newPoint = *this;
    return newPoint;
}

Ionflux::Mapping::Point* Point::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Point*>(other);
}

Ionflux::Mapping::Point* Point::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Point* newObject = new Point();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file Point.cpp
 * \brief Point implementation.
 */
