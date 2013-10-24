/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Shape3.cpp                      Shape (3D) (implementation).
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

#include "geoutils/Shape3.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "geoutils/xmlutils.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

Shape3ClassInfo::Shape3ClassInfo()
{
	name = "Shape3";
	desc = "Shape (3D)";
}

Shape3ClassInfo::~Shape3ClassInfo()
{
}

// run-time type information instance constants
const Shape3ClassInfo Shape3::shape3ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Shape3::CLASS_INFO = &Shape3::shape3ClassInfo;

const std::string Shape3::XML_ELEMENT_NAME = "shape3";

Shape3::Shape3()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Shape3::Shape3(const Ionflux::GeoUtils::Shape3& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Shape3::~Shape3()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::GeoUtils::Shape3& Shape3::scale(const Ionflux::GeoUtils::Vector3& 
s)
{
	TransformableObject::scale(s);
	return *this;
}

Ionflux::GeoUtils::Shape3& Shape3::translate(const 
Ionflux::GeoUtils::Vector3& t)
{
	TransformableObject::translate(t);
	return *this;
}

Ionflux::GeoUtils::Shape3& Shape3::rotate(double phi, 
Ionflux::GeoUtils::AxisID axis)
{
	TransformableObject::rotate(phi, axis);
	return *this;
}

Ionflux::GeoUtils::Shape3& Shape3::normalize()
{
	TransformableObject::normalize();
	return *this;
}

Ionflux::GeoUtils::Shape3& 
Shape3::center(Ionflux::GeoUtils::CenteringMethod method, 
Ionflux::GeoUtils::Vector3* origin)
{
	TransformableObject::center(method, origin);
	return *this;
}

Ionflux::GeoUtils::Shape3& Shape3::transform(const 
Ionflux::GeoUtils::Matrix3& matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Shape3& Shape3::transform(const 
Ionflux::GeoUtils::Matrix4& matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Shape3& Shape3::transformVI(const 
Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4* image)
{
	TransformableObject::transformVI(view, image);
	return *this;
}

bool Shape3::checkVertex(const Ionflux::GeoUtils::Vertex3& v, double t) 
const
{
	// TODO: Implementation.
	return false;
}

Ionflux::GeoUtils::Shape3& Shape3::duplicate()
{
	// TODO: Implementation.
	return *copy();
}

Ionflux::GeoUtils::Shape3& Shape3::operator=(const 
Ionflux::GeoUtils::Shape3& other)
{
    TransformableObject::operator=(other);
	return *this;
}

Ionflux::GeoUtils::Shape3* Shape3::copy() const
{
    Shape3* newShape3 = create();
    *newShape3 = *this;
    return newShape3;
}

Ionflux::GeoUtils::Shape3* Shape3::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Shape3*>(other);
}

Ionflux::GeoUtils::Shape3* Shape3::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Shape3* newObject = new Shape3();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

std::string Shape3::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Shape3::getXMLAttributeData() const
{
	std::ostringstream d0;
	return d0.str();
}

void Shape3::getXMLChildData(std::string& target, unsigned int indentLevel)
const
{
	std::ostringstream d0;
	target = d0.str();
}

void Shape3::loadFromXMLFile(const std::string& fileName)
{
	std::string data;
	Ionflux::ObjectBase::readFile(fileName, data);
	// <---- DEBUG ----- //
	std:cerr << "[Shape3::loadFromXMLFile] data = " << data 
	    << std::endl;
	// <---- DEBUG ----- */
	Ionflux::GeoUtils::XMLUtils::getShape3(data, *this);
}

}

}

/** \file Shape3.cpp
 * \brief Shape (3D) implementation.
 */
