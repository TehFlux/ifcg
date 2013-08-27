/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vertex3.cpp                     Vertex (3D) (implementation).
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

#include "geoutils/Vertex3.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/LinearInterpolator.hpp"
#include "geoutils/Plane3.hpp"
#include "geoutils/Vector4.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

Vertex3ClassInfo::Vertex3ClassInfo()
{
	name = "Vertex3";
	desc = "Vertex (3D)";
}

Vertex3ClassInfo::~Vertex3ClassInfo()
{
}

// public member constants
const Ionflux::GeoUtils::Vertex3 Vertex3::ORIGIN = Ionflux::GeoUtils::Vertex3(0., 0., 0.);

// run-time type information instance constants
const Vertex3ClassInfo Vertex3::vertex3ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Vertex3::CLASS_INFO = &Vertex3::vertex3ClassInfo;

const std::string Vertex3::XML_ELEMENT_NAME = "vert3";

Vertex3::Vertex3()
: x(0.), y(0.), z(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Vertex3::Vertex3(const Ionflux::GeoUtils::Vertex3& other)
: x(0.), y(0.), z(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Vertex3::Vertex3(double initX, double initY, double initZ)
: x(initX), y(initY), z(initZ)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Vertex3::Vertex3(const Ionflux::ObjectBase::DoubleVector& initCoords)
: x(0.), y(0.), z(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setCoords(initCoords);
}

Vertex3::Vertex3(const Ionflux::GeoUtils::Vector3& initCoords)
: x(0.), y(0.), z(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setCoords(initCoords);
}

Vertex3::~Vertex3()
{
	// TODO: Nothing ATM. ;-)
}

void Vertex3::setCoords(double newX, double newY, double newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

void Vertex3::setCoords(const Ionflux::ObjectBase::DoubleVector& newCoords)
{
	if (newCoords.size() == 0)
	    return;
	if (newCoords.size() >= 3)
	    z = newCoords[2];
	if (newCoords.size() >= 2)
	    y = newCoords[1];
	x = newCoords[0];
}

void Vertex3::setCoords(const Ionflux::GeoUtils::Vector3& newCoords)
{
	x = newCoords.getX0();
	y = newCoords.getX1();
	z = newCoords.getX2();
}

void Vertex3::getCoords(Ionflux::ObjectBase::DoubleVector& target) const
{
	target.clear();
	target.push_back(x);
	target.push_back(y);
	target.push_back(z);
}

void Vertex3::getCoords(Ionflux::GeoUtils::Vector3& target) const
{
	target.setX0(x);
	target.setX1(y);
	target.setX2(z);
}

double Vertex3::getCoord(int index) const
{
	// TODO: Implementation.
	return (*this)[index];;
}

Ionflux::GeoUtils::Vector3 Vertex3::getVector() const
{
	// TODO: Implementation.
	return Vector3(x, y, z);
}

void Vertex3::setCoord(int index, double value)
{
	if ((index < 0) || (index > 3))
	{
	    ostringstream message;
	    message << "Index out of range: " << index;
	    throw GeoUtilsError(message.str());
	}
	if (index == 0)
	    x = value;
	else 
	if (index == 1)
	    y = value;
}

Ionflux::GeoUtils::Vertex3 Vertex3::interpolate(const 
Ionflux::GeoUtils::Vertex3& other, double t, 
Ionflux::GeoUtils::Interpolator* interpolator) const
{
	Vertex3 result;
	Interpolator* i0 = 0;
	if (interpolator == 0)
	{
	    i0 = new LinearInterpolator();
	    if (i0 == 0)
	        throw GeoUtilsError("Could not allocate object.");
	    interpolator = i0;
	}
	interpolator->setValues(x, other.x);
	result.setX((*interpolator)(t));
	interpolator->setValues(y, other.y);
	result.setY((*interpolator)(t));
	interpolator->setValues(z, other.z);
	result.setZ((*interpolator)(t));
	if (i0 != 0)
	    delete i0;
	return result;
}

double Vertex3::distanceToPlane(const Ionflux::GeoUtils::Plane3& plane) 
const
{
	// TODO: Implementation.
	return getVector().distanceToPlane(plane);
}

bool Vertex3::eq(const Ionflux::GeoUtils::Vertex3& other, double t)
{
	if (!(Ionflux::GeoUtils::eq(x, other.x, t) 
	    && Ionflux::GeoUtils::eq(y, other.y, t) 
	    && Ionflux::GeoUtils::eq(z, other.z, t)))
	        return false;
	return true;
}

bool Vertex3::operator==(const Ionflux::GeoUtils::Vertex3& other) const
{
	if (!((x == other.x) && (y == other.y) && (z == other.z)))
	        return false;
	return true;
}

bool Vertex3::operator!=(const Ionflux::GeoUtils::Vertex3& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

double Vertex3::operator[](int index) const
{
	if ((index < 0) || (index > 3))
	{
	    ostringstream message;
	    message << "Index out of range: " << index;
	    throw GeoUtilsError(message.str());
	}
	double result = 0.;
	if (index == 0)
	    result = x;
	if (index == 1)
	    result = y;
	if (index == 2)
	    result = z;
	return result;
}

Ionflux::GeoUtils::Vertex3& Vertex3::scale(const 
Ionflux::GeoUtils::Vector3& s)
{
	TransformableObject::scale(s);
	return *this;
}

Ionflux::GeoUtils::Vertex3& Vertex3::translate(const 
Ionflux::GeoUtils::Vector3& t)
{
	TransformableObject::translate(t);
	return *this;
}

Ionflux::GeoUtils::Vertex3& Vertex3::rotate(double phi, 
Ionflux::GeoUtils::AxisID axis)
{
	TransformableObject::rotate(phi, axis);
	return *this;
}

Ionflux::GeoUtils::Vertex3& Vertex3::normalize()
{
	TransformableObject::normalize();
	return *this;
}

Ionflux::GeoUtils::Vertex3& 
Vertex3::center(Ionflux::GeoUtils::CenteringMethod method, 
Ionflux::GeoUtils::Vector3* origin)
{
	TransformableObject::center(method, origin);
	return *this;
}

Ionflux::GeoUtils::Vertex3& Vertex3::transform(const 
Ionflux::GeoUtils::Matrix3& matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Vector3 Vertex3::getBarycenter()
{
	// TODO: Implementation.
	return getVector();
}

Ionflux::GeoUtils::Range3 Vertex3::getBounds()
{
	// TODO: Implementation.
	return Range3(getVector());
}

void Vertex3::applyTransform(bool recursive)
{
	if (useTransform)
	{
	    transform(transformMatrix);
	    transformMatrix = Matrix4::UNIT;
	}
	if (useVI)
	{
	    transformVI(viewMatrix, &imageMatrix);
	    viewMatrix = Matrix4::UNIT;
	    imageMatrix = Matrix4::UNIT;
	}
}

Ionflux::GeoUtils::Vertex3& Vertex3::transform(const 
Ionflux::GeoUtils::Matrix4& matrix)
{
	Vector4 t0(getVector());
	t0 = matrix * t0;
	setCoords(t0.getV3());
	return *this;
}

Ionflux::GeoUtils::Vertex3& Vertex3::transformVI(const 
Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4* image)
{
	Vector4 t0(getVector());
	t0 = view * t0;
	t0 = t0 / t0[3];
	if (image != 0)
	    t0 = (*image) * t0;
	setCoords(t0.getV3());
	return *this;
}

Ionflux::GeoUtils::Vertex3& Vertex3::duplicate()
{
	Vertex3* result = new Vertex3(*this);
	if (result == 0)
	    throw GeoUtilsError("Could not allocate object.");
	return *result;
}

std::string Vertex3::getValueString() const
{
	ostringstream status;
	status << x << ", " << y << ", " << z;
	if (!useTransform && !useVI)
	    return status.str();
	status << "; ";
	if (useTransform)
	    status << transformMatrix;
	if (useVI)
	{
	    if (useTransform)
	        status << ", ";
	    status << viewMatrix << ", " << imageMatrix;
	}
	return status.str();
}

std::string Vertex3::getXMLData_legacy() const
{
	ostringstream d0;
	d0 << x << "," << y << "," << z;
	return d0.str();
}

std::string Vertex3::getXML_legacy() const
{
	ostringstream d0;
	d0 << "<v3 d=\"" << getXMLData_legacy() << "\" />";
	return d0.str();
}

void Vertex3::setX(double newX)
{
	x = newX;
}

double Vertex3::getX() const
{
	return x;
}

void Vertex3::setY(double newY)
{
	y = newY;
}

double Vertex3::getY() const
{
	return y;
}

void Vertex3::setZ(double newZ)
{
	z = newZ;
}

double Vertex3::getZ() const
{
	return z;
}

Ionflux::GeoUtils::Vertex3& Vertex3::operator=(const 
Ionflux::GeoUtils::Vertex3& other)
{
    TransformableObject::operator=(other);
    x = other.x;
    y = other.y;
    z = other.z;
	return *this;
}

Ionflux::GeoUtils::Vertex3* Vertex3::copy() const
{
    Vertex3* newVertex3 = create();
    *newVertex3 = *this;
    return newVertex3;
}

Ionflux::GeoUtils::Vertex3* Vertex3::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Vertex3*>(other);
}

Ionflux::GeoUtils::Vertex3* Vertex3::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Vertex3* newObject = new Vertex3();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vertex3* Vertex3::create(double initX, double initY, 
double initZ, Ionflux::ObjectBase::IFObject* parentObject)
{
    Vertex3* newObject = new Vertex3(initX, initY, initZ);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vertex3* Vertex3::create(const 
Ionflux::ObjectBase::DoubleVector& initCoords, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Vertex3* newObject = new Vertex3(initCoords);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vertex3* Vertex3::create(const 
Ionflux::GeoUtils::Vector3& initCoords, Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Vertex3* newObject = new Vertex3(initCoords);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

std::string Vertex3::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Vertex3::getXMLAttributeData() const
{
	std::string a0(Ionflux::GeoUtils::TransformableObject::getXMLAttributeData());
	std::ostringstream d0;
	if (a0.size() > 0)
	    d0 << a0 << " ";
	d0 << "x=\"" << x << "\"";
	d0 << " " << "y=\"" << y << "\"";
	d0 << " " << "z=\"" << z << "\"";
	return d0.str();
}

void Vertex3::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::GeoUtils::TransformableObject::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

}

}

/** \file Vertex3.cpp
 * \brief Vertex (3D) implementation.
 */
