/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector4.cpp                     Vector (4 elements) (implementation).
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

#include "geoutils/Vector4.hpp"
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

Vector4ClassInfo::Vector4ClassInfo()
{
	name = "Vector4";
	desc = "Vector (4 elements)";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

Vector4ClassInfo::~Vector4ClassInfo()
{
}

// public member constants
const Ionflux::GeoUtils::Vector4 Vector4::ZERO = Ionflux::GeoUtils::Vector4(0., 0., 0., 0.);
const Ionflux::GeoUtils::Vector4 Vector4::E_X = Ionflux::GeoUtils::Vector4(1., 0., 0., 0.);
const Ionflux::GeoUtils::Vector4 Vector4::E_Y = Ionflux::GeoUtils::Vector4(0., 1., 0., 0.);
const Ionflux::GeoUtils::Vector4 Vector4::E_Z = Ionflux::GeoUtils::Vector4(0., 0., 1., 0.);
const Ionflux::GeoUtils::Vector4 Vector4::E_W = Ionflux::GeoUtils::Vector4(0., 0., 0., 1.);
const Ionflux::GeoUtils::Vector4 Vector4::H_ZERO = Ionflux::GeoUtils::Vector4(0., 0., 0., 1.);
const Ionflux::GeoUtils::Vector4 Vector4::H_E_X = Ionflux::GeoUtils::Vector4(1., 0., 0., 1.);
const Ionflux::GeoUtils::Vector4 Vector4::H_E_Y = Ionflux::GeoUtils::Vector4(0., 1., 0., 1.);
const Ionflux::GeoUtils::Vector4 Vector4::H_E_Z = Ionflux::GeoUtils::Vector4(0., 0., 1., 1.);

// run-time type information instance constants
const Vector4ClassInfo Vector4::vector4ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Vector4::CLASS_INFO = &Vector4::vector4ClassInfo;

Vector4::Vector4()
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[4];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	*this = ZERO;
}

Vector4::Vector4(const Ionflux::GeoUtils::Vector4& other)
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[4];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	*this = other;
}

Vector4::Vector4(double initX0, double initX1, double initX2, double 
initX3)
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[4];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	elements[0] = initX0;
	elements[1] = initX1;
	elements[2] = initX2;
	elements[3] = initX3;\
}

Vector4::Vector4(const Ionflux::ObjectBase::DoubleVector& initElements)
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[4];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	setElements(initElements);
}

Vector4::Vector4(const Ionflux::GeoUtils::Vector2& initElements, double 
initZ, double initW)
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[4];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	setV2(initElements, initZ, initW);
}

Vector4::Vector4(const Ionflux::GeoUtils::Vector3& initElements, double 
initW)
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[4];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	setV3(initElements, initW);
}

Vector4::~Vector4()
{
	delete[] elements;
}

void Vector4::setElements(const Ionflux::ObjectBase::DoubleVector& 
newElements)
{
	unsigned int i = 0;
	while ((i < 4) && (i < newElements.size()))
	{
	    elements[i] = newElements[i];
	    i++;
	}
}

void Vector4::setElements(const Ionflux::GeoUtils::Vector2& newElements)
{
	elements[0] = newElements.getX0();
	elements[1] = newElements.getX1();
}

void Vector4::setElements(const Ionflux::GeoUtils::Vector3& newElements)
{
	elements[0] = newElements.getX0();
	elements[1] = newElements.getX1();
	elements[2] = newElements.getX2();
}

void Vector4::setV2(const Ionflux::GeoUtils::Vector2& newElements, double 
newZ, double newW)
{
	setElements(newElements);
	elements[2] = newZ;
	elements[3] = newW;
}

void Vector4::setV3(const Ionflux::GeoUtils::Vector3& newElements, double 
newW)
{
	setElements(newElements);
	elements[3] = newW;
}

void Vector4::getElements(Ionflux::ObjectBase::DoubleVector& target) const
{
	target.clear();
	for (unsigned int i = 0; i < 4; i++)
	    target.push_back(elements[i]);
}

double Vector4::getElement(int index) const
{
	// TODO: Implementation.
	return (*this)[index];;
}

void Vector4::setElement(int index, double value)
{
	if ((index < 0) || (index > 3))
	{
	    ostringstream message;
	    message << "Index out of range: " << index;
	    throw GeoUtilsError(message.str());
	}
	elements[index] = value;
}

bool Vector4::eq(const Ionflux::GeoUtils::Vector4& other, double t)
{
	for (unsigned int i = 0; i < 4; i++)
	    if (!Ionflux::GeoUtils::eq(elements[i], other.elements[i], t))
	        return false;
	return true;
}

Ionflux::GeoUtils::Vector4 Vector4::flip() const
{
	// TODO: Implementation.
	return Vector4(-elements[0], -elements[1], -elements[2], -elements[3]);
}

double Vector4::norm() const
{
	// TODO: Implementation.
	return ::sqrt((*this) * (*this));
}

Ionflux::GeoUtils::Vector4 Vector4::normalize() const
{
	// TODO: Implementation.
	return (*this) / norm();
}

Ionflux::GeoUtils::Vector4 Vector4::project(const 
Ionflux::GeoUtils::Vector4& other) const
{
	const Vector4& v0 = *this;
	return ((v0 * other) * v0) / (v0 * v0);
}

Ionflux::GeoUtils::Vector4 Vector4::ortho(const Ionflux::GeoUtils::Vector4&
other) const
{
	const Vector4& v0 = *this;
	return other.norm() * (other - v0.project(other)).normalize();
}

Ionflux::GeoUtils::Vector4 Vector4::permute(int px, int py, int pz, int pw)
const
{
	const Vector4& v = *this;
	return Vector4(v[px], v[py], v[pz], v[pw]);
}

Ionflux::GeoUtils::Vector4 Vector4::permute(const 
Ionflux::ObjectBase::IntVector& p) const
{
	if (p.size() < 4)
	    throw GeoUtilsError("Not enough elements in permutation vector.");
	const Vector4& v = *this;
	return Vector4(v[p[0]], v[p[1]], v[p[2]], v[p[3]]);
}

bool Vector4::operator==(const Ionflux::GeoUtils::Vector4& other) const
{
	for (unsigned int i = 0; i < 4; i++)
	    if (elements[i] != other.elements[i])
	        return false;
	return true;
}

bool Vector4::operator!=(const Ionflux::GeoUtils::Vector4& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

double Vector4::operator[](int index) const
{
	if ((index < 0) || (index > 3))
	{
	    ostringstream message;
	    message << "Index out of range: " << index;
	    throw GeoUtilsError(message.str());
	}
	return elements[index];
}

Ionflux::GeoUtils::Vector4 Vector4::operator+(const 
Ionflux::GeoUtils::Vector4& other) const
{
	// TODO: Implementation.
	return Vector4(elements[0] + other.elements[0], 
    elements[1] + other.elements[1], 
    elements[2] + other.elements[2], 
    elements[3] + other.elements[3]);
}

Ionflux::GeoUtils::Vector4 Vector4::operator-(const 
Ionflux::GeoUtils::Vector4& other) const
{
	// TODO: Implementation.
	return Vector4(elements[0] - other.elements[0], 
    elements[1] - other.elements[1], 
    elements[2] - other.elements[2], 
    elements[3] - other.elements[3]);
}

double Vector4::operator*(const Ionflux::GeoUtils::Vector4& other) const
{
	// TODO: Implementation.
	return elements[0] * other.elements[0] + elements[1] * other.elements[1] + elements[2] * other.elements[2] + elements[3] * other.elements[3];
}

Ionflux::GeoUtils::Vector4 Vector4::operator*(double c) const
{
	// TODO: Implementation.
	return Vector4(elements[0] * c, elements[1] * c, elements[2] * c, elements[3] * c);
}

Ionflux::GeoUtils::Vector4 Vector4::operator/(double c) const
{
	// TODO: Implementation.
	return Vector4(elements[0] / c, elements[1] / c, elements[2] / c, elements[3] / c);
}

Ionflux::GeoUtils::Vector2 Vector4::getV2() const
{
	// TODO: Implementation.
	return Vector2(elements[0], elements[1]);
}

Ionflux::GeoUtils::Vector3 Vector4::getV3() const
{
	// TODO: Implementation.
	return Vector3(elements[0], elements[1], elements[2]);
}

std::string Vector4::getString() const
{
	ostringstream state;
	state << getClassName() << "[" << elements[0] << ", " << elements[1] 
	    << ", " << elements[2] << ", " << elements[3] << "]";
	return state.str();
}

Ionflux::GeoUtils::Vector4 Vector4::axis(Ionflux::GeoUtils::AxisID axisID)
{
	if (axisID == AXIS_X)
	    return E_X;
	else
	if (axisID == AXIS_Y)
	    return E_Y;
	else
	if (axisID == AXIS_Z)
	    return E_Z;
	else
	if (axisID == AXIS_W)
	    return E_W;
	else
	{
	    ostringstream status;
	    status << "Invalid axis: " << axisID;
	    throw GeoUtilsError(status.str());
	}
	return ZERO;
}

Ionflux::GeoUtils::Vector4 Vector4::axisH(Ionflux::GeoUtils::AxisID axisID)
{
	if (axisID == AXIS_X)
	    return H_E_X;
	else
	if (axisID == AXIS_Y)
	    return H_E_Y;
	else
	if (axisID == AXIS_Z)
	    return H_E_Z;
	else
	{
	    ostringstream status;
	    status << "Invalid axis: " << axisID;
	    throw GeoUtilsError(status.str());
	}
	return ZERO;
}

void Vector4::setX0(double newX0)
{
	elements[0] = newX0;
}

double Vector4::getX0() const
{
	return elements[0];
}

void Vector4::setX1(double newX1)
{
	elements[1] = newX1;
}

double Vector4::getX1() const
{
	return elements[1];
}

void Vector4::setX2(double newX2)
{
	elements[2] = newX2;
}

double Vector4::getX2() const
{
	return elements[2];
}

void Vector4::setX3(double newX3)
{
	elements[3] = newX3;
}

double Vector4::getX3() const
{
	return elements[3];
}

Ionflux::GeoUtils::Vector4& Vector4::operator=(const 
Ionflux::GeoUtils::Vector4& other)
{
    if ((elements == 0) || (other.elements == 0))
        return *this;
    for (unsigned int i = 0; i < 4; i++)
        elements[i] = other.elements[i];
    return *this;
	return *this;
}

Ionflux::GeoUtils::Vector4* Vector4::copy() const
{
    Vector4* newVector4 = 
        new Vector4();
    *newVector4 = *this;
    return newVector4;
}

Ionflux::GeoUtils::Vector4 operator*(double c, const 
Ionflux::GeoUtils::Vector4& v)
{
	// TODO: Implementation.
	return v * c;
}

}

}

/** \file Vector4.cpp
 * \brief Vector (4 elements) implementation.
 */
