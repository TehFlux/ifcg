/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Object3.cpp                     Object (3D) (implementation).
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

#include "geoutils/Object3.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Mesh.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/Object3XMLFactory.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

Object3ClassInfo::Object3ClassInfo()
{
	name = "Object3";
	desc = "Object (3D)";
}

Object3ClassInfo::~Object3ClassInfo()
{
}

// run-time type information instance constants
const Object3ClassInfo Object3::object3ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Object3::CLASS_INFO = &Object3::object3ClassInfo;

const std::string Object3::XML_ELEMENT_NAME = "object";

Object3::Object3()
: mesh(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Object3::Object3(const Ionflux::GeoUtils::Object3& other)
: mesh(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Object3::Object3(Ionflux::GeoUtils::Mesh* initMesh)
: mesh(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initMesh != 0)
	    setMesh(initMesh);
	update();
}

Object3::~Object3()
{
	// TODO: Nothing ATM. ;-)
}

void Object3::recalculateBounds()
{
	if (mesh == 0)
	    return;
	TransformableObject::recalculateBounds();
	if (!useTransform() && !useVI())
	{
	    *boundsCache = mesh->getBounds();
	    return;
	}
	// Adjust for transformation.
	Object3* o0 = copy();
	addLocalRef(o0);
	o0->applyTransform();
	if (o0->useTransform())
	    throw GeoUtilsError(getErrorString(
	        "Transform matrix still in use after "
	        "applying transformations.", "recalculateBounds"));
	*boundsCache = o0->getBounds();
	removeLocalRef(o0);
}

void Object3::update()
{
	if (mesh == 0)
	    return;
	// Determine the bounds.
	recalculateBounds();
}

void Object3::clear()
{
	setMesh(0);
	TransformableObject::clear();
}

void Object3::applyTransform(bool recursive)
{
	if (mesh == 0)
	{
	    clearTransformations();
	    return;
	}
	if (!useTransform() && !useVI())
	{
	    if (recursive)
	        mesh->applyTransform(recursive);
	    return;
	}
	if (useTransform())
	    mesh->transform(*getTransformMatrix());
	if (useVI())
	    mesh->transformVI(*getViewMatrix(), getImageMatrix());
	if (useTransform() || useVI())
	    mesh->applyTransform(recursive);
	clearTransformations();
}

Ionflux::GeoUtils::Object3& Object3::scale(const 
Ionflux::GeoUtils::Vector3& s)
{
	TransformableObject::scale(s);
	return *this;
}

Ionflux::GeoUtils::Object3& Object3::translate(const 
Ionflux::GeoUtils::Vector3& t)
{
	TransformableObject::translate(t);
	return *this;
}

Ionflux::GeoUtils::Object3& Object3::rotate(double phi, 
Ionflux::GeoUtils::AxisID axis)
{
	TransformableObject::rotate(phi, axis);
	return *this;
}

Ionflux::GeoUtils::Object3& Object3::normalize()
{
	TransformableObject::normalize();
	return *this;
}

Ionflux::GeoUtils::Object3& 
Object3::center(Ionflux::GeoUtils::CenteringMethod method, 
Ionflux::GeoUtils::Vector3* origin)
{
	TransformableObject::center(method, origin);
	return *this;
}

Ionflux::GeoUtils::Object3& Object3::transform(const 
Ionflux::GeoUtils::Matrix3& matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Object3& Object3::transform(const 
Ionflux::GeoUtils::Matrix4& matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Object3& Object3::transformVI(const 
Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4* image)
{
	TransformableObject::transformVI(view, image);
	return *this;
}

std::string Object3::getValueString() const
{
	std::ostringstream status;
	status << "mesh: ";
	if (mesh != 0)
	    status << "[" << mesh->getValueString() << "]";
	else
	    status << "<none>";
	// transformable object data
	std::string ts0(TransformableObject::getValueString());
	if (ts0.size() > 0)
	    status << "; " << ts0;
	return status.str();
}

Ionflux::GeoUtils::Object3& Object3::duplicate()
{
	// TODO: Implementation.
	return *copy();
}

void Object3::setMesh(Ionflux::GeoUtils::Mesh* newMesh)
{
	if (mesh == newMesh)
		return;
    if (newMesh != 0)
        addLocalRef(newMesh);
	if (mesh != 0)
		removeLocalRef(mesh);
	mesh = newMesh;
}

Ionflux::GeoUtils::Mesh* Object3::getMesh() const
{
    return mesh;
}

Ionflux::GeoUtils::Object3& Object3::operator=(const 
Ionflux::GeoUtils::Object3& other)
{
    if (this == &other)
        return *this;
    TransformableObject::operator=(other);
	return *this;
}

Ionflux::GeoUtils::Object3* Object3::copy() const
{
    Object3* newObject3 = create();
    *newObject3 = *this;
    return newObject3;
}

Ionflux::GeoUtils::Object3* Object3::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Object3*>(other);
}

Ionflux::GeoUtils::Object3* Object3::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Object3* newObject = new Object3();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Object3* Object3::create(Ionflux::GeoUtils::Mesh* 
initMesh, Ionflux::ObjectBase::IFObject* parentObject)
{
    Object3* newObject = new Object3(initMesh);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Object3::getMemSize() const
{
    return sizeof *this;
}

std::string Object3::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Object3::getXMLAttributeData() const
{
	std::ostringstream d0;
	return d0.str();
}

void Object3::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string iws0 = Ionflux::ObjectBase::getIndent(indentLevel);
	bool haveBCData = false;
	bool xcFirst = true;
    if (mesh != 0)
    {
        if (!xcFirst || haveBCData)
            d0 << "\n";
	    d0 << mesh->getXML0(indentLevel, "pname=\"mesh\"");
	    xcFirst = false;
    }
	target = d0.str();
}

void Object3::loadFromXMLFile(const std::string& fileName, const 
std::string& elementName)
{
	std::string en0(elementName);
	if (en0.size() == 0)
	    en0 = getXMLElementName();
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, en0);
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
Object3::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::Object3XMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::Object3XMLFactory::create();
        fac0->addRef();
    }
    return fac0;
}

}

}

/** \file Object3.cpp
 * \brief Object (3D) implementation.
 */
