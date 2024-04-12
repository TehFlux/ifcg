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
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/Vertex3XMLFactory.hpp"
#include "ifobject/objectutils.hpp"
#include "ifobject/serialize.hpp"
#include "ifobject/IFIOContext.hpp"

using Ionflux::ObjectBase::pack;
using Ionflux::ObjectBase::packObj;
using Ionflux::ObjectBase::unpack;
using Ionflux::ObjectBase::unpackObj;

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

const Ionflux::ObjectBase::MagicSyllable Vertex3::MAGIC_SYLLABLE_OBJECT = 0x5645;

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

Vertex3::Vertex3(const Ionflux::GeoUtils::Vector4& initCoords)
: x(0.), y(0.), z(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setCoords(initCoords);
}

Vertex3::Vertex3(const Ionflux::Mapping::Point& initCoords)
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

void Vertex3::setCoords(const Ionflux::GeoUtils::Vector4& newCoords)
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

void Vertex3::setCoords(const Ionflux::Mapping::Point& newCoords)
{
	x = newCoords.getX();
	y = newCoords.getY();
	z = newCoords.getZ();
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
	    throw GeoUtilsError(getErrorString(message.str(), "setCoord"));
	}
	if (index == 0)
	    x = value;
	else 
	if (index == 1)
	    y = value;
	else 
	if (index == 2)
	    z = value;
}

Ionflux::GeoUtils::Vertex3 Vertex3::interpolate(const 
Ionflux::GeoUtils::Vertex3& other, double t, 
Ionflux::GeoUtils::Interpolator* interpolator) const
{
	Vertex3 result;
	Interpolator* i0 = 0;
	if (interpolator == 0)
	{
	    i0 = LinearInterpolator::create();
	    addLocalRef(i0);
	    interpolator = i0;
	}
	interpolator->setValues(x, other.x);
	result.setX((*interpolator)(t));
	interpolator->setValues(y, other.y);
	result.setY((*interpolator)(t));
	interpolator->setValues(z, other.z);
	result.setZ((*interpolator)(t));
	if (i0 != 0)
	    removeLocalRef(i0);
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
	    std::ostringstream message;
	    message << "Index out of range: " << index;
	    throw GeoUtilsError(getErrorString(message.str(), 
	        "operator[]"));
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
	if (useTransform())
	    transform(*getTransformMatrix());
	if (useVI())
	    transformVI(*getViewMatrix(), getImageMatrix());
	clearTransformations();
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
	// TODO: Implementation.
	return *copy();
}

Ionflux::Mapping::Point Vertex3::getPoint() const
{
	// TODO: Implementation.
	return Ionflux::Mapping::Point(x, y, z);
}

std::string Vertex3::getValueString() const
{
	std::ostringstream status;
	status << x << ", " << y << ", " << z;
	// transformable object data
	std::string ts0(TransformableObject::getValueString());
	if (ts0.size() > 0)
	    status << "; " << ts0;
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

bool Vertex3::serialize(std::string& target) const
{
	pack(x, target);
	pack(y, target);
	pack(z, target);
	return true;
}

Ionflux::ObjectBase::DataSize Vertex3::deserialize(const std::string& source, Ionflux::ObjectBase::DataSize offset)
{
	// x
    offset = unpack(source, x, offset);
	if (offset < 0)
	{
        std::ostringstream status;
		status << "[Vertex3::deserialize] "
			"Could not deserialize property 'x'.";
        throw GeoUtilsError(status.str());
	}
	// y
    offset = unpack(source, y, offset);
	if (offset < 0)
	{
        std::ostringstream status;
		status << "[Vertex3::deserialize] "
			"Could not deserialize property 'y'.";
        throw GeoUtilsError(status.str());
	}
	// z
    offset = unpack(source, z, offset);
	if (offset < 0)
	{
        std::ostringstream status;
		status << "[Vertex3::deserialize] "
			"Could not deserialize property 'z'.";
        throw GeoUtilsError(status.str());
	}
	return offset;
}

bool Vertex3::serialize(std::ostream& target, bool addMagicWord) const
{
	if (addMagicWord)
        Ionflux::ObjectBase::pack(getMagicSyllableBase(), 
            getMagicSyllable(), target);
	pack(x, target);
	pack(y, target);
	pack(z, target);
	return true;
}

Ionflux::ObjectBase::DataSize Vertex3::deserialize(std::istream& source, Ionflux::ObjectBase::DataSize offset, bool checkMagicWord)
{
    if (offset != Ionflux::ObjectBase::DATA_SIZE_INVALID)
    {
        source.seekg(offset);
        if (!source.good())
        {
            std::ostringstream status;
            status << "Invalid stream offset: " << offset;
            throw GeoUtilsError(getErrorString(status.str(), "deserialize"));
        }
    }
    if (checkMagicWord)
        Ionflux::ObjectBase::unpackAndCheckMagicWord(source, 
            getMagicSyllableBase(), getMagicSyllable(), 
            Ionflux::ObjectBase::DATA_SIZE_INVALID, 
            this, "deserialize");
	// x
    unpack(source, x);
	// y
    unpack(source, y);
	// z
    unpack(source, z);
	return source.tellg();
}

bool Vertex3::serialize(Ionflux::ObjectBase::IFIOContext& ioCtx, bool addMagicWord) const
{
	std::ostream* os0 = Ionflux::ObjectBase::nullPointerCheck(
	    ioCtx.getOutputStream(), this, "serialize", "Output stream");
    return serialize(*os0, addMagicWord);
}

Ionflux::ObjectBase::DataSize Vertex3::deserialize(Ionflux::ObjectBase::IFIOContext& ioCtx, Ionflux::ObjectBase::DataSize offset, bool checkMagicWord)
{
	std::istream* is0 = Ionflux::ObjectBase::nullPointerCheck(
	    ioCtx.getInputStream(), this, "deserialize", "Input stream");
    return deserialize(*is0, offset, checkMagicWord);
}

Ionflux::ObjectBase::MagicSyllable Vertex3::getMagicSyllable() const
{
    return MAGIC_SYLLABLE_OBJECT;
}

Ionflux::ObjectBase::MagicSyllable Vertex3::getMagicSyllableBase() const
{
    return MAGIC_SYLLABLE_BASE;
}

Ionflux::GeoUtils::Vertex3& Vertex3::operator=(const 
Ionflux::GeoUtils::Vertex3& other)
{
    if (this == &other)
        return *this;
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

Ionflux::GeoUtils::Vertex3* Vertex3::create(const 
Ionflux::GeoUtils::Vector4& initCoords, Ionflux::ObjectBase::IFObject* 
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

Ionflux::GeoUtils::Vertex3* Vertex3::create(const Ionflux::Mapping::Point& 
initCoords, Ionflux::ObjectBase::IFObject* parentObject)
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

unsigned int Vertex3::getMemSize() const
{
    return sizeof *this;
}

std::string Vertex3::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Vertex3::getXMLAttributeData() const
{
    std::string a0(Ionflux::ObjectBase::IFObject::getXMLAttributeData());
    std::ostringstream d0;
    if (a0.size() > 0)
        d0 << a0 << " ";
    d0 << "d=\"" << x << "," << y << "," << z << "\"";
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

void Vertex3::loadFromXMLFile(const std::string& fileName, const 
std::string& elementName)
{
	std::string en0(elementName);
	if (en0.size() == 0)
	    en0 = getXMLElementName();
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, en0);
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
Vertex3::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::Vertex3XMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::Vertex3XMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 0;
        bFac = Ionflux::GeoUtils::TransformableObject::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file Vertex3.cpp
 * \brief Vertex (3D) implementation.
 */
