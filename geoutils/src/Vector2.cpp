/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector2.cpp                     Vector (2 elements) (implementation).
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

#include "geoutils/Vector2.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/utils.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "geoutils/xmlutils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

Vector2ClassInfo::Vector2ClassInfo()
{
	name = "Vector2";
	desc = "Vector (2 elements)";
	baseClassInfo.push_back(Ionflux::GeoUtils::Vector::CLASS_INFO);
}

Vector2ClassInfo::~Vector2ClassInfo()
{
}

// public member constants
const unsigned int Vector2::NUM_ELEMENTS = 2;
const Ionflux::GeoUtils::Vector2 Vector2::ZERO = Ionflux::GeoUtils::Vector2(0., 0.);
const Ionflux::GeoUtils::Vector2 Vector2::E_X = Ionflux::GeoUtils::Vector2(1., 0.);
const Ionflux::GeoUtils::Vector2 Vector2::E_Y = Ionflux::GeoUtils::Vector2(0., 1.);

// run-time type information instance constants
const Vector2ClassInfo Vector2::vector2ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Vector2::CLASS_INFO = &Vector2::vector2ClassInfo;

const std::string Vector2::XML_ELEMENT_NAME = "v2";

Vector2::Vector2()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	zero();
}

Vector2::Vector2(const Ionflux::GeoUtils::Vector2& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Vector2::Vector2(double initX0, double initX1)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	elements[0] = initX0;
	elements[1] = initX1;
}

Vector2::Vector2(const Ionflux::ObjectBase::DoubleVector& initElements0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	Vector::setElements(initElements0);
}

Vector2::~Vector2()
{
	// TODO: Nothing ATM. ;-)
}

void Vector2::setElements(double newX0, double newX1)
{
	elements[0] = newX0;
	elements[1] = newX1;
}

Ionflux::GeoUtils::Vector2 Vector2::flip() const
{
	Vector2 result(*this);
	result.flipIP();
	return result;
}

Ionflux::GeoUtils::Vector2 Vector2::normalize() const
{
	Vector2 result(*this);
	result.normalizeIP();
	return result;
}

Ionflux::GeoUtils::Vector2 Vector2::project(const 
Ionflux::GeoUtils::Vector2& other) const
{
	const Vector2& v0 = *this;
	return ((v0 * other) * v0) / (v0 * v0);
}

Ionflux::GeoUtils::Vector2 Vector2::ortho(const Ionflux::GeoUtils::Vector2&
other) const
{
	const Vector2& v0 = *this;
	return other.norm() * (other - v0.project(other)).normalize();
}

Ionflux::GeoUtils::Vector2 Vector2::swap() const
{
	// TODO: Implementation.
	return Vector2(elements[1], elements[0]);
}

Ionflux::GeoUtils::Vector2 Vector2::multElements(const 
Ionflux::GeoUtils::Vector2& other) const
{
	Vector2 result(*this);
	result.multiplyIP(other);
	return result;
}

Ionflux::GeoUtils::Vector2 Vector2::operator+(const 
Ionflux::GeoUtils::Vector2& other) const
{
	Vector2 result(*this);
	result.addIP(other);
	return result;
}

Ionflux::GeoUtils::Vector2 Vector2::operator-(const 
Ionflux::GeoUtils::Vector2& other) const
{
	Vector2 result(*this);
	result.subtractIP(other);
	return result;
}

Ionflux::GeoUtils::Vector2 Vector2::operator*(double c) const
{
	Vector2 result(*this);
	result.multiplyIP(c);
	return result;
}

double Vector2::operator*(const Ionflux::GeoUtils::Vector2& other) const
{
	// TODO: Implementation.
	return dot(other);
}

Ionflux::GeoUtils::Vector2 Vector2::operator/(double c) const
{
	Vector2 result(*this);
	result.divideIP(c);
	return result;
}

unsigned int Vector2::getNumElements() const
{
	// TODO: Implementation.
	return NUM_ELEMENTS;
}

Ionflux::GeoUtils::Vector2 Vector2::axis(Ionflux::GeoUtils::AxisID axisID)
{
	if (axisID == AXIS_X)
	    return E_X;
	else
	if (axisID == AXIS_Y)
	    return E_Y;
	else
	{
	    std::ostringstream status;
	    status << "[Vector2::axis] "
	        "Invalid axis: " << axisID;
	    throw GeoUtilsError(status.str());
	}
	return ZERO;
}

void Vector2::setX0(double newX0)
{
	elements[0] = newX0;
}

double Vector2::getX0() const
{
	return elements[0];
}

void Vector2::setX1(double newX1)
{
	elements[1] = newX1;
}

double Vector2::getX1() const
{
	return elements[1];
}

Ionflux::GeoUtils::Vector2& Vector2::operator=(const 
Ionflux::GeoUtils::Vector2& other)
{
    if (this == &other)
        return *this;
    Vector::operator=(other);
	return *this;
}

Ionflux::GeoUtils::Vector2* Vector2::copy() const
{
    Vector2* newVector2 = create();
    *newVector2 = *this;
    return newVector2;
}

Ionflux::GeoUtils::Vector2* Vector2::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Vector2*>(other);
}

Ionflux::GeoUtils::Vector2* Vector2::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Vector2* newObject = new Vector2();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vector2* Vector2::create(double initX0, double initX1, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Vector2* newObject = new Vector2(initX0, initX1);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vector2* Vector2::create(const 
Ionflux::ObjectBase::DoubleVector& initElements0, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Vector2* newObject = new Vector2(initElements0);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

std::string Vector2::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Vector2::getXMLAttributeData() const
{
	std::string a0(Ionflux::GeoUtils::Vector::getXMLAttributeData());
	std::ostringstream d0;
	if (a0.size() > 0)
	    d0 << a0;
	return d0.str();
}

void Vector2::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::GeoUtils::Vector::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void Vector2::loadFromXMLFile(const std::string& fileName)
{
	std::string data;
	Ionflux::ObjectBase::readFile(fileName, data);
	/* <---- DEBUG ----- //
	std::cerr << "[Vector2::loadFromXMLFile] data = " << data 
	    << std::endl;
	// <---- DEBUG ----- */
	Ionflux::GeoUtils::XMLUtils::getVector2(data, *this);
}

Ionflux::GeoUtils::Vector2 operator*(double c, const 
Ionflux::GeoUtils::Vector2& v)
{
	// TODO: Implementation.
	return v * c;
}

}

}

/** \file Vector2.cpp
 * \brief Vector (2 elements) implementation.
 */
