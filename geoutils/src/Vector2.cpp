/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
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
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

Vector2ClassInfo::~Vector2ClassInfo()
{
}

// public member constants
const Ionflux::GeoUtils::Vector2 Vector2::ZERO = Ionflux::GeoUtils::Vector2(0., 0.);
const Ionflux::GeoUtils::Vector2 Vector2::E_X = Ionflux::GeoUtils::Vector2(1., 0.);
const Ionflux::GeoUtils::Vector2 Vector2::E_Y = Ionflux::GeoUtils::Vector2(0., 1.);

// run-time type information instance constants
const Vector2ClassInfo Vector2::vector2ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Vector2::CLASS_INFO = &Vector2::vector2ClassInfo;

Vector2::Vector2()
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[2];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	*this = ZERO;
}

Vector2::Vector2(const Ionflux::GeoUtils::Vector2& other)
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[2];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	*this = other;
}

Vector2::Vector2(double initX0, double initX1)
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[2];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	elements[0] = initX0;
	elements[1] = initX1;
}

Vector2::Vector2(const Ionflux::ObjectBase::DoubleVector& initElements)
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[2];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	setElements(initElements);
}

Vector2::~Vector2()
{
	delete[] elements;
}

void Vector2::setElements(const Ionflux::ObjectBase::DoubleVector& 
newElements)
{
	unsigned int i = 0;
	while ((i < 2) && (i < newElements.size()))
	{
	    elements[i] = newElements[i];
	    i++;
	}
}

void Vector2::setElements(double newX0, double newX1)
{
	elements[0] = newX0;
	elements[1] = newX1;
}

void Vector2::getElements(Ionflux::ObjectBase::DoubleVector& target) const
{
	target.clear();
	for (unsigned int i = 0; i < 2; i++)
	    target.push_back(elements[i]);
}

double Vector2::getElement(int index) const
{
	// TODO: Implementation.
	return (*this)[index];;
}

void Vector2::setElement(int index, double value)
{
	if ((index < 0) || (index > 2))
	{
	    ostringstream message;
	    message << "Index out of range: " << index;
	    throw GeoUtilsError(message.str());
	}
	elements[index] = value;
}

bool Vector2::eq(const Ionflux::GeoUtils::Vector2& other, double t)
{
	for (unsigned int i = 0; i < 2; i++)
	    if (!Ionflux::GeoUtils::eq(elements[i], other.elements[i], t))
	        return false;
	return true;
}

Ionflux::GeoUtils::Vector2 Vector2::flip() const
{
	// TODO: Implementation.
	return Vector2(-elements[0], -elements[1]);
}

double Vector2::norm() const
{
	// TODO: Implementation.
	return ::sqrt((*this) * (*this));
}

Ionflux::GeoUtils::Vector2 Vector2::normalize() const
{
	// TODO: Implementation.
	return (*this) / norm();
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

bool Vector2::operator==(const Ionflux::GeoUtils::Vector2& other) const
{
	for (unsigned int i = 0; i < 2; i++)
	    if (elements[i] != other.elements[i])
	        return false;
	return true;
}

bool Vector2::operator!=(const Ionflux::GeoUtils::Vector2& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

double Vector2::operator[](int index) const
{
	if ((index < 0) || (index > 2))
	{
	    ostringstream message;
	    message << "Index out of range: " << index;
	    throw GeoUtilsError(message.str());
	}
	return elements[index];
}

Ionflux::GeoUtils::Vector2 Vector2::operator+(const 
Ionflux::GeoUtils::Vector2& other) const
{
	// TODO: Implementation.
	return Vector2(elements[0] + other.elements[0], 
    elements[1] + other.elements[1]);
}

Ionflux::GeoUtils::Vector2 Vector2::operator-(const 
Ionflux::GeoUtils::Vector2& other) const
{
	// TODO: Implementation.
	return Vector2(elements[0] - other.elements[0], 
    elements[1] - other.elements[1]);
}

double Vector2::operator*(const Ionflux::GeoUtils::Vector2& other) const
{
	// TODO: Implementation.
	return elements[0] * other.elements[0] + elements[1] * other.elements[1];
}

Ionflux::GeoUtils::Vector2 Vector2::operator*(double c) const
{
	// TODO: Implementation.
	return Vector2(elements[0] * c, elements[1] * c);
}

Ionflux::GeoUtils::Vector2 Vector2::operator/(double c) const
{
	// TODO: Implementation.
	return Vector2(elements[0] / c, elements[1] / c);
}

std::string Vector2::getString() const
{
	ostringstream state;
	state << getClassName() << "[" << elements[0] << ", " << elements[1] 
	    << "]";
	return state.str();
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
	    ostringstream status;
	    status << "Invalid axis: " << axisID;
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
    if ((elements == 0) || (other.elements == 0))
        return *this;
    for (unsigned int i = 0; i < 2; i++)
        elements[i] = other.elements[i];
    return *this;
	return *this;
}

Ionflux::GeoUtils::Vector2* Vector2::copy() const
{
    Vector2* newVector2 = 
        new Vector2();
    *newVector2 = *this;
    return newVector2;
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
