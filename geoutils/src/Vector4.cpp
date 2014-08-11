/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
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
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/Vector4XMLFactory.hpp"

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
	baseClassInfo.push_back(Ionflux::GeoUtils::Vector::CLASS_INFO);
}

Vector4ClassInfo::~Vector4ClassInfo()
{
}

// public member constants
const unsigned int Vector4::NUM_ELEMENTS = 4;
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

const std::string Vector4::XML_ELEMENT_NAME = "v4";

Vector4::Vector4()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	zero();
}

Vector4::Vector4(const Ionflux::GeoUtils::Vector4& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Vector4::Vector4(double initX0, double initX1, double initX2, double 
initX3)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	elements[0] = initX0;
	elements[1] = initX1;
	elements[2] = initX2;
	elements[3] = initX3;
}

Vector4::Vector4(const Ionflux::ObjectBase::DoubleVector& initElements0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	Vector::setElements(initElements0);
}

Vector4::Vector4(const Ionflux::GeoUtils::Vector& initElements0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	setElements(initElements0);
}

Vector4::Vector4(const Ionflux::GeoUtils::Vector2& initElements0, double 
initZ, double initW)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	setV2(initElements0, initZ, initW);
}

Vector4::Vector4(const Ionflux::GeoUtils::Vector3& initElements0, double 
initW)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	setV3(initElements0, initW);
}

Vector4::~Vector4()
{
	// TODO: Nothing ATM. ;-)
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

void Vector4::setElements(const Ionflux::GeoUtils::Vector& other, unsigned 
int sourceOffset, unsigned int targetOffset)
{
	Vector::setElements(other, sourceOffset, targetOffset);
}

void Vector4::setElements(double x0, double x1, double x2, double x3)
{
	Vector::setElements(x0, x1, x2, x3);
}

void Vector4::setV3(const Ionflux::GeoUtils::Vector3& newElements, double 
newW)
{
	setElements(newElements);
	elements[3] = newW;
}

Ionflux::GeoUtils::Vector4 Vector4::flip() const
{
	Vector4 result(*this);
	result.flipIP();
	return result;
}

Ionflux::GeoUtils::Vector4 Vector4::normalize() const
{
	Vector4 result(*this);
	result.normalizeIP();
	return result;
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

double Vector4::angle(const Ionflux::GeoUtils::Vector4& other) const
{
	const Vector4& v0 = *this;
	double t = (v0 * other) / (v0.norm() * other.norm());
	if (t < -1.)
	    t = -1.;
	else
	if (t > 1.)
	    t = 1.;
	return ::acos(t);
}

Ionflux::GeoUtils::Vector4 Vector4::slerp(const Ionflux::GeoUtils::Vector4&
other, double t) const
{
	double phi0 = angle(other);
	Vector4 v0(ortho(other));
	double phi1 = t * phi0;
	Vector4 result(::sin(phi1) * v0 + ::cos(phi1) * (*this));
	return result;
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
	if (p.size() < NUM_ELEMENTS)
	{
	    std::ostringstream status;
	    status << "Not enough elements in permutation vector (p.size = " 
	        << p.size() << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "permute"));
	}
	const Vector4& v = *this;
	return Vector4(v[p[0]], v[p[1]], v[p[2]], v[p[3]]);
}

Ionflux::GeoUtils::Vector4 Vector4::operator+(const 
Ionflux::GeoUtils::Vector4& other) const
{
	Vector4 result(*this);
	result.addIP(other);
	return result;
}

Ionflux::GeoUtils::Vector4 Vector4::operator-(const 
Ionflux::GeoUtils::Vector4& other) const
{
	Vector4 result(*this);
	result.subtractIP(other);
	return result;
}

double Vector4::operator*(const Ionflux::GeoUtils::Vector4& other) const
{
	// TODO: Implementation.
	return dot(other);
}

Ionflux::GeoUtils::Vector4 Vector4::operator*(double c) const
{
	Vector4 result(*this);
	result.multiplyIP(c);
	return result;
}

Ionflux::GeoUtils::Vector4 Vector4::operator/(double c) const
{
	Vector4 result(*this);
	result.divideIP(c);
	return result;
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

unsigned int Vector4::getNumElements() const
{
	// TODO: Implementation.
	return NUM_ELEMENTS;
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
	    status << "[Vector4::axis] "
	        "Invalid axis: " << axisID;
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
	    status << "[Vector4::axisH] "
	        "Invalid axis: " << axisID;
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
    if (this == &other)
        return *this;
    Vector::operator=(other);
	return *this;
}

Ionflux::GeoUtils::Vector4* Vector4::copy() const
{
    Vector4* newVector4 = create();
    *newVector4 = *this;
    return newVector4;
}

Ionflux::GeoUtils::Vector4* Vector4::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Vector4*>(other);
}

Ionflux::GeoUtils::Vector4* Vector4::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Vector4* newObject = new Vector4();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vector4* Vector4::create(double initX0, double initX1, 
double initX2, double initX3, Ionflux::ObjectBase::IFObject* parentObject)
{
    Vector4* newObject = new Vector4(initX0, initX1, initX2, initX3);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vector4* Vector4::create(const 
Ionflux::ObjectBase::DoubleVector& initElements0, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Vector4* newObject = new Vector4(initElements0);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vector4* Vector4::create(const 
Ionflux::GeoUtils::Vector& initElements0, Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Vector4* newObject = new Vector4(initElements0);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vector4* Vector4::create(const 
Ionflux::GeoUtils::Vector2& initElements0, double initZ, double initW, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Vector4* newObject = new Vector4(initElements0, initZ, initW);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vector4* Vector4::create(const 
Ionflux::GeoUtils::Vector3& initElements0, double initW, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Vector4* newObject = new Vector4(initElements0, initW);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Vector4::getMemSize() const
{
    return sizeof *this;
}

std::string Vector4::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Vector4::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::GeoUtils::Vector::getXMLAttributeData();
	return d0.str();
}

void Vector4::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::GeoUtils::Vector::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void Vector4::loadFromXMLFile(const std::string& fileName)
{
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, getXMLElementName());
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
Vector4::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::Vector4XMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::Vector4XMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 0;
        bFac = Ionflux::GeoUtils::Vector::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
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
