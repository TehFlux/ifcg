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
#include <cmath>
#include "ifmapping/MappingError.hpp"
#include "ifmapping/utils.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "ifmapping/xmlutils.hpp"
#include "ifmapping/xmlio/PointXMLFactory.hpp"

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

const std::string Point::XML_ELEMENT_NAME = "p";

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

Ionflux::Mapping::Point Point::operator-(const Ionflux::Mapping::Point& 
other) const
{
	Point result(x - other.x, y - other.y, z - other.z);
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

bool Point::eq(const Ionflux::Mapping::Point& other, double t) const
{
	// TODO: Implementation.
	return Ionflux::Mapping::eq(x, other.x, t) 
    && Ionflux::Mapping::eq(y, other.y, t) 
    && Ionflux::Mapping::eq(z, other.z, t);
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

Ionflux::Mapping::MappingValue Point::distance(const 
Ionflux::Mapping::Point& other) const
{
	double result = ::sqrt((x - other.x) * (x - other.x) 
	    + (y - other.y) * (y - other.y) 
	    + (z - other.z) * (z - other.z));
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

std::string Point::getSVGPathData(const Ionflux::Mapping::CoordinateID 
imagePlaneNormal) const
{
	std::ostringstream result;
	bool first = true;
	if (imagePlaneNormal != C_X)
	{
	    result << x;
	    first = false;
	}
	if (imagePlaneNormal != C_Y)
	{
	    if (!first)
	        result << ",";
	    result << y;
	    first = false;
	}
	if (imagePlaneNormal != C_Z)
	{
	    if (!first)
	        result << ",";
	    result << z;
	    first = false;
	}
	return result.str();
}

std::string Point::getValueString() const
{
	std::ostringstream status;
	status << x << ", " << y << ", " << z;
	return status.str();
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
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Mapping::Point* Point::create(Ionflux::Mapping::MappingValue 
initX, Ionflux::Mapping::MappingValue initY, Ionflux::Mapping::MappingValue
initZ, Ionflux::ObjectBase::IFObject* parentObject)
{
    Point* newObject = new Point(initX, initY, initZ);
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Mapping::Point* Point::create(const 
Ionflux::ObjectBase::DoubleVector& initCoords, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Point* newObject = new Point(initCoords);
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Point::getMemSize() const
{
    return sizeof *this;
}

std::string Point::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Point::getXMLAttributeData() const
{
    std::string a0(Ionflux::ObjectBase::IFObject::getXMLAttributeData());
    std::ostringstream d0;
    if (a0.size() > 0)
        d0 << a0 << " ";
    d0 << "d=\"" << x << Ionflux::ObjectBase::DEFAULT_COORD_SEPARATOR 
        << y << Ionflux::ObjectBase::DEFAULT_COORD_SEPARATOR
        << z << "\"";
    return d0.str();
}

void Point::getXMLChildData(std::string& target, unsigned int indentLevel) 
const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::ObjectBase::IFObject::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void Point::loadFromXMLFile(const std::string& fileName, const std::string&
elementName)
{
	std::string en0(elementName);
	if (en0.size() == 0)
	    en0 = getXMLElementName();
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, en0);
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
Point::getXMLObjectFactory()
{
	static Ionflux::Mapping::XMLUtils::PointXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::Mapping::XMLUtils::PointXMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 
            IFObject::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file Point.cpp
 * \brief Point implementation.
 */
