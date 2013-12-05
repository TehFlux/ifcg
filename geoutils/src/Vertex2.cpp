/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vertex2.cpp                     Vertex (2D) (implementation).
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

#include "geoutils/Vertex2.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/LinearInterpolator.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/Vertex2XMLFactory.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

Vertex2ClassInfo::Vertex2ClassInfo()
{
	name = "Vertex2";
	desc = "Vertex (2D)";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

Vertex2ClassInfo::~Vertex2ClassInfo()
{
}

// public member constants
const Ionflux::GeoUtils::Vertex2 Vertex2::ORIGIN = Ionflux::GeoUtils::Vertex2(0., 0.);

// run-time type information instance constants
const Vertex2ClassInfo Vertex2::vertex2ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Vertex2::CLASS_INFO = &Vertex2::vertex2ClassInfo;

const std::string Vertex2::XML_ELEMENT_NAME = "vert2";

Vertex2::Vertex2()
: x(0.), y(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Vertex2::Vertex2(const Ionflux::GeoUtils::Vertex2& other)
: x(0.), y(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Vertex2::Vertex2(double initX, double initY)
: x(initX), y(initY)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Vertex2::Vertex2(const Ionflux::ObjectBase::DoubleVector& initCoords)
: x(0.), y(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setCoords(initCoords);
}

Vertex2::Vertex2(const Ionflux::GeoUtils::Vector2& initCoords)
: x(0.), y(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setCoords(initCoords);
}

Vertex2::~Vertex2()
{
	// TODO: Nothing ATM. ;-)
}

void Vertex2::setCoords(const Ionflux::ObjectBase::DoubleVector& newCoords)
{
	if (newCoords.size() == 0)
	    return;
	if (newCoords.size() >= 2)
	    y = newCoords[1];
	x = newCoords[0];
}

void Vertex2::setCoords(const Ionflux::GeoUtils::Vector2& newCoords)
{
	x = newCoords.getX0();
	y = newCoords.getX1();
}

void Vertex2::getCoords(Ionflux::ObjectBase::DoubleVector& target) const
{
	target.clear();
	target.push_back(x);
	target.push_back(y);
}

void Vertex2::getCoords(Ionflux::GeoUtils::Vector2& target) const
{
	target.setX0(x);
	target.setX1(y);
}

double Vertex2::getCoord(int index) const
{
	// TODO: Implementation.
	return (*this)[index];;
}

Ionflux::GeoUtils::Vector2 Vertex2::getVector() const
{
	// TODO: Implementation.
	return Vector2(x, y);
}

void Vertex2::setCoord(int index, double value)
{
	if ((index < 0) || (index > 2))
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

Ionflux::GeoUtils::Vertex2 Vertex2::interpolate(const 
Ionflux::GeoUtils::Vertex2& other, double t, 
Ionflux::GeoUtils::Interpolator* interpolator) const
{
	Vertex2 result;
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
	if (i0 != 0)
	    delete i0;
	return result;
}

bool Vertex2::eq(const Ionflux::GeoUtils::Vertex2& other, double t)
{
	if (!(Ionflux::GeoUtils::eq(x, other.x, t) 
	    && Ionflux::GeoUtils::eq(y, other.y, t)))
	        return false;
	return true;
}

bool Vertex2::operator==(const Ionflux::GeoUtils::Vertex2& other) const
{
	if (!((x == other.x) && (y == other.y)))
	        return false;
	return true;
}

bool Vertex2::operator!=(const Ionflux::GeoUtils::Vertex2& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

double Vertex2::operator[](int index) const
{
	if ((index < 0) || (index > 2))
	{
	    ostringstream message;
	    message << "Index out of range: " << index;
	    throw GeoUtilsError(message.str());
	}
	double result = 0;
	if (index == 0)
	    result = x;
	if (index == 1)
	    result = y;
	return result;
}

std::string Vertex2::getString() const
{
	ostringstream state;
	state << getClassName() << "[" << x << ", " << y << "]";
	return state.str();
}

void Vertex2::setX(double newX)
{
	x = newX;
}

double Vertex2::getX() const
{
    return x;
}

void Vertex2::setY(double newY)
{
	y = newY;
}

double Vertex2::getY() const
{
    return y;
}

Ionflux::GeoUtils::Vertex2& Vertex2::operator=(const 
Ionflux::GeoUtils::Vertex2& other)
{
    if (this == &other)
        return *this;
    x = other.x;
    y = other.y;
	return *this;
}

Ionflux::GeoUtils::Vertex2* Vertex2::copy() const
{
    Vertex2* newVertex2 = create();
    *newVertex2 = *this;
    return newVertex2;
}

Ionflux::GeoUtils::Vertex2* Vertex2::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Vertex2*>(other);
}

Ionflux::GeoUtils::Vertex2* Vertex2::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Vertex2* newObject = new Vertex2();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vertex2* Vertex2::create(double initX, double initY, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Vertex2* newObject = new Vertex2(initX, initY);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vertex2* Vertex2::create(const 
Ionflux::ObjectBase::DoubleVector& initCoords, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Vertex2* newObject = new Vertex2(initCoords);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Vertex2* Vertex2::create(const 
Ionflux::GeoUtils::Vector2& initCoords, Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Vertex2* newObject = new Vertex2(initCoords);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

std::string Vertex2::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Vertex2::getXMLAttributeData() const
{
	std::string a0(Ionflux::ObjectBase::IFObject::getXMLAttributeData());
	std::ostringstream d0;
	if (a0.size() > 0)
	    d0 << a0 << " ";
	d0 << "x=\"" << x << "\"";
	d0 << " " << "y=\"" << y << "\"";
	return d0.str();
}

void Vertex2::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::ObjectBase::IFObject::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void Vertex2::loadFromXMLFile(const std::string& fileName)
{
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, getXMLElementName());
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
Vertex2::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::Vertex2XMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::Vertex2XMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 
            IFObject::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file Vertex2.cpp
 * \brief Vertex (2D) implementation.
 */
