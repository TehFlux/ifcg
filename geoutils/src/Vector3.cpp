/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector3.cpp                     Vector (3 elements) (implementation).
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

#include "geoutils/Vector3.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/utils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Plane3.hpp"
#include "geoutils/Range.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/Vector3XMLFactory.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

Vector3ClassInfo::Vector3ClassInfo()
{
	name = "Vector3";
	desc = "Vector (3 elements)";
	baseClassInfo.push_back(Ionflux::GeoUtils::Vector::CLASS_INFO);
}

Vector3ClassInfo::~Vector3ClassInfo()
{
}

// public member constants
const unsigned int Vector3::NUM_ELEMENTS = 3;
const Ionflux::GeoUtils::Vector3 Vector3::ZERO = Ionflux::GeoUtils::Vector3(0., 0., 0.);
const Ionflux::GeoUtils::Vector3 Vector3::E_X = Ionflux::GeoUtils::Vector3(1., 0., 0.);
const Ionflux::GeoUtils::Vector3 Vector3::E_Y = Ionflux::GeoUtils::Vector3(0., 1., 0.);
const Ionflux::GeoUtils::Vector3 Vector3::E_Z = Ionflux::GeoUtils::Vector3(0., 0., 1.);
const Ionflux::GeoUtils::Vector3 Vector3::E_SUM = Ionflux::GeoUtils::Vector3(1., 1., 1.);

// run-time type information instance constants
const Vector3ClassInfo Vector3::vector3ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Vector3::CLASS_INFO = &Vector3::vector3ClassInfo;

const std::string Vector3::XML_ELEMENT_NAME = "v3";

Vector3::Vector3()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	zero();
}

Vector3::Vector3(const Ionflux::GeoUtils::Vector3& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Vector3::Vector3(double initX0, double initX1, double initX2)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	elements[0] = initX0;
	elements[1] = initX1;
	elements[2] = initX2;
}

Vector3::Vector3(const Ionflux::ObjectBase::DoubleVector& initElements0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	Vector::setElements(initElements0);
}

Vector3::Vector3(const Ionflux::GeoUtils::Vector& initElements0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	setElements(initElements0);
}

Vector3::Vector3(const Ionflux::GeoUtils::Vector2& initElements0, double 
initZ)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	setV2(initElements0, initZ);
}

Vector3::Vector3(const Ionflux::Mapping::Point& initElements0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	setElements(initElements0);
}

Vector3::~Vector3()
{
	// TODO: Nothing ATM. ;-)
}

void Vector3::setElements(double newX0, double newX1, double newX2)
{
	elements[0] = newX0;
	elements[1] = newX1;
	elements[2] = newX2;
}

void Vector3::setElements(const Ionflux::GeoUtils::Vector2& newElements)
{
	elements[0] = newElements.getX0();
	elements[1] = newElements.getX1();
}

void Vector3::setElements(const Ionflux::GeoUtils::Vector& other, unsigned 
int sourceOffset, unsigned int targetOffset)
{
	Vector::setElements(other, sourceOffset, targetOffset);
}

void Vector3::setV2(const Ionflux::GeoUtils::Vector2& newElements, double 
newZ)
{
	setElements(newElements);
	elements[2] = newZ;
}

void Vector3::setElements(const Ionflux::Mapping::Point& newElements)
{
	elements[0] = newElements.getX();
	elements[1] = newElements.getY();
	elements[2] = newElements.getZ();
}

void Vector3::setElements(const Ionflux::ObjectBase::DoubleVector& 
newElements)
{
	Vector::setElements(newElements);
}

Ionflux::GeoUtils::Vector3 Vector3::flip() const
{
	Vector3 result(*this);
	result.flipIP();
	return result;
}

Ionflux::GeoUtils::Vector3 Vector3::normalize() const
{
	Vector3 result(*this);
	result.normalizeIP();
	return result;
}

Ionflux::GeoUtils::Vector3 Vector3::cross(const Ionflux::GeoUtils::Vector3&
other) const
{
	double x0 = elements[0];
	double x1 = elements[1];
	double x2 = elements[2];
	double y0 = other.elements[0];
	double y1 = other.elements[1];
	double y2 = other.elements[2];
	return Vector3(x1 * y2 - x2 * y1, 
    x2 * y0 - x0 * y2, 
    x0 * y1 - x1 * y0);
}

Ionflux::GeoUtils::Vector3 Vector3::project(const 
Ionflux::GeoUtils::Vector3& other) const
{
	const Vector3& v0 = *this;
	return ((v0 * other) * v0) / (v0 * v0);
}

Ionflux::GeoUtils::Vector3 Vector3::ortho(const Ionflux::GeoUtils::Vector3&
other) const
{
	const Vector3& v0 = *this;
	return other.norm() * (other - v0.project(other)).normalize();
}

Ionflux::GeoUtils::Vector3 Vector3::ortho() const
{
	const int V3_P[] = { 0, 1, 2, 1, 0, 2, 2, 1, 0 };
	int p = 0;
	if (elements[V3_P[p]] == 0)
	{
	    p += 3;
	    if (elements[V3_P[p]] == 0)
	    {
	        p += 3;
	        if (elements[V3_P[p]] == 0)
	            return Vector3(0., 0., 0.);
	    }
	}
	Vector3 t0(-elements[V3_P[p + 1]], elements[V3_P[p]], 0);
	return Vector3(t0.elements[V3_P[p]], t0.elements[V3_P[p + 1]], t0.elements[V3_P[p + 2]]);
}

double Vector3::angleCos(const Ionflux::GeoUtils::Vector3& other) const
{
	const Vector3& v0 = *this;
	double t = (v0 * other) / (v0.norm() * other.norm());
	if (t < -1.)
	    t = -1.;
	else
	if (t > 1.)
	    t = 1.;
	return t;
}

double Vector3::angle(const Ionflux::GeoUtils::Vector3& other) const
{
	// TODO: Implementation.
	return ::acos(angleCos(other));
}

double Vector3::angle(const Ionflux::GeoUtils::Vector3& other, const 
Ionflux::GeoUtils::Vector3& axis0, double t) const
{
	Vector3 pv0(axis0.ortho(*this));
	Vector3 pv1(axis0.ortho(other));
	pv0.normalizeIP();
	pv1.normalizeIP();
	Vector3 ov0(pv0.cross(pv1));
	double sign0 = 1.;
	if (Ionflux::GeoUtils::lt(ov0.dot(axis0), 0., t))
	    sign0 = -1.;
	return sign0 * pv0.angle(pv1);
}

Ionflux::GeoUtils::Vector3 Vector3::slerp(const Ionflux::GeoUtils::Vector3&
other, double t) const
{
	double phi0 = angle(other);
	Vector3 v0(ortho(other));
	double phi1 = t * phi0;
	Vector3 result(::sin(phi1) * v0 + ::cos(phi1) * (*this));
	return result;
}

Ionflux::GeoUtils::Vector3 Vector3::permute(int px, int py, int pz) const
{
	const Vector3& v = *this;
	return Vector3(v[px], v[py], v[pz]);
}

Ionflux::GeoUtils::Vector3 Vector3::permute(const 
Ionflux::ObjectBase::IntVector& p) const
{
	if (p.size() < NUM_ELEMENTS)
	{
	    std::ostringstream status;
	    status << "Not enough elements in permutation vector (p.size = " 
	        << p.size() << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "permute"));
	}
	const Vector3& v = *this;
	return Vector3(v[p[0]], v[p[1]], v[p[2]]);
}

Ionflux::GeoUtils::Vector3 Vector3::multElements(const 
Ionflux::GeoUtils::Vector3& other) const
{
	Vector3 result(*this);
	result.multiplyIP(other);
	return result;
}

Ionflux::GeoUtils::Vector3 Vector3::interpolate(const 
Ionflux::GeoUtils::Vector3& other, double t) const
{
	// TODO: Implementation.
	return t * (*this) + (1. - t) * other;
}

Ionflux::GeoUtils::AxisTriple Vector3::getAxisOrder() const
{
	AxisTriple result;
	result.a0 = AXIS_X;
	result.a1 = AXIS_Y;
	result.a2 = AXIS_Z;
	if (elements[AXIS_Y] > elements[AXIS_X])
	{
	    result.a0 = AXIS_Y;
	    result.a1 = AXIS_X;
	}
	if (elements[result.a2] > elements[result.a0])
	{
	    AxisID t0 = result.a2;
	    result.a2 = result.a1;
	    result.a1 = result.a0;
	    result.a0 = t0;
	}
	if (elements[result.a2] > elements[result.a1])
	{
	    AxisID t0 = result.a1;
	    result.a1 = result.a2;
	    result.a2 = t0;
	}
	return result;
}

Ionflux::GeoUtils::Vector3 Vector3::operator+(const 
Ionflux::GeoUtils::Vector3& other) const
{
	Vector3 result(*this);
	result.addIP(other);
	return result;
}

Ionflux::GeoUtils::Vector3 Vector3::operator-(const 
Ionflux::GeoUtils::Vector3& other) const
{
	Vector3 result(*this);
	result.subtractIP(other);
	return result;
}

double Vector3::operator*(const Ionflux::GeoUtils::Vector3& other) const
{
	// TODO: Implementation.
	return dot(other);
}

Ionflux::GeoUtils::Vector3 Vector3::operator*(double c) const
{
	Vector3 result(*this);
	result.multiplyIP(c);
	return result;
}

Ionflux::GeoUtils::Vector3 Vector3::operator/(double c) const
{
	Vector3 result(*this);
	result.divideIP(c);
	return result;
}

Ionflux::GeoUtils::Vector3& Vector3::operator+=(const 
Ionflux::GeoUtils::Vector3& other)
{
	addIP(other);
	return *this;
}

Ionflux::GeoUtils::Vector3& Vector3::operator-=(const 
Ionflux::GeoUtils::Vector3& other)
{
	subtractIP(other);
	return *this;
}

int Vector3::findElement(double v, double t) const
{
	int k = 0;
	bool found = false;
	while (!found 
	    && (k < 3))
	{
	    double c = elements[k];
	    if (Ionflux::GeoUtils::eq(c, v, t))
	        found = true;
	    else
	        k++;
	}
	if (found)
	    return k;
	return -1;
}

int Vector3::findMatchingElements(const Ionflux::GeoUtils::Vector3& other, 
Ionflux::ObjectBase::DoubleVector& target, const Ionflux::GeoUtils::Range* 
range, double t)
{
	target.clear();
	for (unsigned int i = 0; i < 3; i++)
	{
	    double c = elements[i];
	    if ((range == 0) 
	        || (range->isInRange(c, t)))
	    {
	        if (other.findElement(c, t) >= 0)
	            target.push_back(c);
	    }
	}
	return target.size();
}

Ionflux::GeoUtils::Vector2 Vector3::getV2() const
{
	// TODO: Implementation.
	return Vector2(elements[0], elements[1]);
}

Ionflux::Mapping::Point Vector3::getPoint() const
{
	// TODO: Implementation.
	return Ionflux::Mapping::Point(
    elements[0], elements[1], elements[2]);
}

double Vector3::distanceToPlane(const Ionflux::GeoUtils::Plane3& plane) 
const
{
	// TODO: Implementation.
	return (*this - plane.getP()) * plane.getNormal();
}

unsigned int Vector3::getNumElements() const
{
	// TODO: Implementation.
	return NUM_ELEMENTS;
}

Ionflux::GeoUtils::Vector3 Vector3::axis(Ionflux::GeoUtils::AxisID axisID)
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
	{
	    ostringstream status;
	    status << "[Vector3::axis] "
	        "Invalid axis: " << axisID;
	    throw GeoUtilsError(status.str());
	}
	return ZERO;
}

void Vector3::getOtherAxes(Ionflux::GeoUtils::AxisID axisID, 
Ionflux::GeoUtils::Vector3& axis0, Ionflux::GeoUtils::Vector3& axis1)
{
	if (axisID == AXIS_X)
	{
	    axis0 = E_Y;
	    axis1 = E_Z;
	} else
	if (axisID == AXIS_Y)
	{
	    axis0 = E_Z;
	    axis1 = E_X;
	} else
	if (axisID == AXIS_Z)
	{
	    axis0 = E_X;
	    axis1 = E_Y;
	} else
	{
	    ostringstream status;
	    status << "[Vector3::getOtherAxes] "
	        "Invalid axis: " << axisID;
	    throw GeoUtilsError(status.str());
	}
}

void Vector3::setX0(double newX0)
{
	elements[0] = newX0;
}

double Vector3::getX0() const
{
	return elements[0];
}

void Vector3::setX1(double newX1)
{
	elements[1] = newX1;
}

double Vector3::getX1() const
{
	return elements[1];
}

void Vector3::setX2(double newX2)
{
	elements[2] = newX2;
}

double Vector3::getX2() const
{
	return elements[2];
}

Ionflux::GeoUtils::Vector3& Vector3::operator=(const 
Ionflux::GeoUtils::Vector3& other)
{
    if (this == &other)
        return *this;
    Vector::operator=(other);
	return *this;
}

Ionflux::GeoUtils::Vector3* Vector3::copy() const
{
    Vector3* newVector3 = create();
    *newVector3 = *this;
    return newVector3;
}

Ionflux::GeoUtils::Vector3* Vector3::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Vector3*>(other);
}

Ionflux::GeoUtils::Vector3* Vector3::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Vector3* newObject = new Vector3();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vector3* Vector3::create(double initX0, double initX1, 
double initX2, Ionflux::ObjectBase::IFObject* parentObject)
{
    Vector3* newObject = new Vector3(initX0, initX1, initX2);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vector3* Vector3::create(const 
Ionflux::ObjectBase::DoubleVector& initElements0, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Vector3* newObject = new Vector3(initElements0);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vector3* Vector3::create(const 
Ionflux::GeoUtils::Vector& initElements0, Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Vector3* newObject = new Vector3(initElements0);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vector3* Vector3::create(const 
Ionflux::GeoUtils::Vector2& initElements0, double initZ, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Vector3* newObject = new Vector3(initElements0, initZ);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vector3* Vector3::create(const Ionflux::Mapping::Point& 
initElements0, Ionflux::ObjectBase::IFObject* parentObject)
{
    Vector3* newObject = new Vector3(initElements0);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Vector3::getMemSize() const
{
    return sizeof *this;
}

std::string Vector3::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Vector3::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::GeoUtils::Vector::getXMLAttributeData();
	return d0.str();
}

void Vector3::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::GeoUtils::Vector::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void Vector3::loadFromXMLFile(const std::string& fileName, const 
std::string& elementName)
{
	std::string en0(elementName);
	if (en0.size() == 0)
	    en0 = getXMLElementName();
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, en0);
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
Vector3::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::Vector3XMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::Vector3XMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 0;
        bFac = Ionflux::GeoUtils::Vector::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

Ionflux::GeoUtils::Vector3 operator*(double c, const 
Ionflux::GeoUtils::Vector3& v)
{
	// TODO: Implementation.
	return v * c;
}

}

}

/** \file Vector3.cpp
 * \brief Vector (3 elements) implementation.
 */
