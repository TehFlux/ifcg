/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TransformableObject.cpp         Transformable object (implementation).
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

#include "geoutils/TransformableObject.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Vertex3.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "geoutils/xmlutils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

TransformableObjectClassInfo::TransformableObjectClassInfo()
{
	name = "TransformableObject";
	desc = "Transformable object";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

TransformableObjectClassInfo::~TransformableObjectClassInfo()
{
}

// run-time type information instance constants
const TransformableObjectClassInfo TransformableObject::transformableObjectClassInfo;
const Ionflux::ObjectBase::IFClassInfo* TransformableObject::CLASS_INFO = &TransformableObject::transformableObjectClassInfo;

const std::string TransformableObject::XML_ELEMENT_NAME = "transformable_object";

TransformableObject::TransformableObject()
: useTransform(false), useVI(false), transformChanged(false), viChanged(false), boundsCache(0), transformMatrix(Ionflux::GeoUtils::Matrix4::UNIT), viewMatrix(Ionflux::GeoUtils::Matrix4::UNIT), imageMatrix(Ionflux::GeoUtils::Matrix4::UNIT), lastTransformMatrix(Ionflux::GeoUtils::Matrix4::UNIT), lastViewMatrix(Ionflux::GeoUtils::Matrix4::UNIT), lastImageMatrix(Ionflux::GeoUtils::Matrix4::UNIT)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

TransformableObject::TransformableObject(const Ionflux::GeoUtils::TransformableObject& other)
: useTransform(false), useVI(false), transformChanged(false), viChanged(false), boundsCache(0), transformMatrix(Ionflux::GeoUtils::Matrix4::UNIT), viewMatrix(Ionflux::GeoUtils::Matrix4::UNIT), imageMatrix(Ionflux::GeoUtils::Matrix4::UNIT), lastTransformMatrix(Ionflux::GeoUtils::Matrix4::UNIT), lastViewMatrix(Ionflux::GeoUtils::Matrix4::UNIT), lastImageMatrix(Ionflux::GeoUtils::Matrix4::UNIT)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

TransformableObject::~TransformableObject()
{
	// TODO: Nothing ATM. ;-)
}

void TransformableObject::recalculateBounds()
{
	if (boundsCache == 0)
	{
	    boundsCache = Range3::create();
	    addLocalRef(boundsCache);
	}
}

void TransformableObject::processTransformChange()
{
	recalculateBounds();
	transformChanged = false;
	viChanged = false;
}

std::string TransformableObject::getValueString() const
{
	if (!useTransform && !useVI)
	    return "";
	ostringstream status;
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

void TransformableObject::copyTransform(const 
Ionflux::GeoUtils::TransformableObject& other)
{
	lastTransformMatrix = transformMatrix;
	lastViewMatrix = viewMatrix;
	lastImageMatrix = imageMatrix;
	transformMatrix = other.transformMatrix;
	viewMatrix = other.viewMatrix;
	imageMatrix = other.imageMatrix;
	checkTransform();
	checkVI();
}

void TransformableObject::onTransformChanged()
{
	transformChanged = true;
}

void TransformableObject::onVIChanged()
{
	viChanged = true;
}

bool TransformableObject::checkTransform(double t)
{
	if (transformMatrix.eq(Matrix4::UNIT, t))
	    useTransform = false;
	else
	{
	    useTransform = true;
	    if (!transformMatrix.eq(lastTransformMatrix, t))
	        onTransformChanged();
	}
	return useTransform;
}

bool TransformableObject::checkVI(double t)
{
	if (viewMatrix.eq(Matrix4::UNIT, t) 
	    && (imageMatrix.eq(Matrix4::UNIT, t)))
	    useVI = false;
	else
	{
	    useVI = true;
	    if (!(viewMatrix.eq(lastViewMatrix, t) 
	        && imageMatrix.eq(lastImageMatrix, t)))
	        onVIChanged();
	}
	return useTransform;
}

Ionflux::GeoUtils::TransformableObject& TransformableObject::scale(const 
Ionflux::GeoUtils::Vector3& s)
{
	Matrix4 s0 = Matrix4::scale(s);
	transform(s0);
	return *this;
}

Ionflux::GeoUtils::TransformableObject& 
TransformableObject::translate(const Ionflux::GeoUtils::Vector3& t)
{
	Matrix4 t0 = Matrix4::translate(t);
	transform(t0);
	return *this;
}

Ionflux::GeoUtils::TransformableObject& TransformableObject::rotate(double 
phi, Ionflux::GeoUtils::AxisID axis)
{
	Matrix4 r0 = Matrix4::rotate(phi, axis);
	transform(r0);
	return *this;
}

Ionflux::GeoUtils::TransformableObject& TransformableObject::normalize()
{
	Range3 bounds = getBounds();
	Vector3 r = bounds.getRadius();
	/* Scale to half the radius vector so the object has unit size 
	   for its largest cross-section. */
	double s = 0.5 / r.norm();
	Vector3 s0(s, s, s);
	scale(s0);
	return *this;
}

Ionflux::GeoUtils::TransformableObject& 
TransformableObject::center(Ionflux::GeoUtils::CenteringMethod method, 
Ionflux::GeoUtils::Vector3* origin)
{
	Vector3 offset;
	if (method == CENTER_BARYCENTER)
	    offset = getBarycenter().flip();
	else
	if (method == CENTER_BOUNDS)
	    offset = getBounds().getCenter().flip();
	if (origin != 0)
	    offset = offset + *origin;
	/* <---- DEBUG ----- //
	std::ostringstream message;
	message << "offset = " << offset;
	log(IFLogMessage(message.str(), VL_DEBUG, this, "center"));
	// ----- DEBUG ----> */
	Matrix4 t0 = Matrix4::translate(offset);
	transform(t0);
	return *this;
}

Ionflux::GeoUtils::TransformableObject& 
TransformableObject::transform(const Ionflux::GeoUtils::Matrix3& matrix)
{
	transform(Matrix4(matrix));
	return *this;
}

Ionflux::GeoUtils::TransformableObject& 
TransformableObject::transform(const Ionflux::GeoUtils::Matrix4& matrix)
{
	lastTransformMatrix = transformMatrix;
	transformMatrix.multiplyLeft(matrix);
	checkTransform();
	return *this;
}

Ionflux::GeoUtils::TransformableObject& 
TransformableObject::transformVI(const Ionflux::GeoUtils::Matrix4& view, 
const Ionflux::GeoUtils::Matrix4* image)
{
	lastViewMatrix = viewMatrix;
	lastImageMatrix = imageMatrix;
	viewMatrix = view;
	if (image != 0)
	    imageMatrix = *image;
	checkVI();
	return *this;
}

void TransformableObject::applyTransform(bool recursive)
{
	// TODO: Implementation.
}

Ionflux::GeoUtils::Vector3 TransformableObject::getBarycenter()
{
	if (!useTransform && !useVI)
	    return Vector3::ZERO;
	Vertex3 v0;
	if (useTransform)
	    v0.transform(transformMatrix);
	if (useVI)
	    v0.transformVI(viewMatrix, &imageMatrix);
	return v0.getVector();;
}

Ionflux::GeoUtils::Range3 TransformableObject::getBounds()
{
	if ((boundsCache == 0) 
	    || transformChanged 
	    || viChanged)
	    processTransformChange();
	return *boundsCache;
}

Ionflux::GeoUtils::TransformableObject& TransformableObject::duplicate()
{
	// TODO: Implementation.
	return *copy();
}

void TransformableObject::setTransformMatrix(const 
Ionflux::GeoUtils::Matrix4& newTransformMatrix)
{
	transformMatrix = newTransformMatrix;
	checkTransform();
}

Ionflux::GeoUtils::Matrix4 TransformableObject::getTransformMatrix() const
{
    return transformMatrix;
}

void TransformableObject::setViewMatrix(const Ionflux::GeoUtils::Matrix4& 
newViewMatrix)
{
	viewMatrix = newViewMatrix;
	checkVI();
}

Ionflux::GeoUtils::Matrix4 TransformableObject::getViewMatrix() const
{
    return viewMatrix;
}

void TransformableObject::setImageMatrix(const Ionflux::GeoUtils::Matrix4& 
newImageMatrix)
{
	imageMatrix = newImageMatrix;
	checkVI();
}

Ionflux::GeoUtils::Matrix4 TransformableObject::getImageMatrix() const
{
    return imageMatrix;
}

void TransformableObject::setLastTransformMatrix(const 
Ionflux::GeoUtils::Matrix4& newLastTransformMatrix)
{
	lastTransformMatrix = newLastTransformMatrix;
}

Ionflux::GeoUtils::Matrix4 TransformableObject::getLastTransformMatrix() 
const
{
    return lastTransformMatrix;
}

void TransformableObject::setLastViewMatrix(const 
Ionflux::GeoUtils::Matrix4& newLastViewMatrix)
{
	lastViewMatrix = newLastViewMatrix;
}

Ionflux::GeoUtils::Matrix4 TransformableObject::getLastViewMatrix() const
{
    return lastViewMatrix;
}

void TransformableObject::setLastImageMatrix(const 
Ionflux::GeoUtils::Matrix4& newLastImageMatrix)
{
	lastImageMatrix = newLastImageMatrix;
}

Ionflux::GeoUtils::Matrix4 TransformableObject::getLastImageMatrix() const
{
    return lastImageMatrix;
}

Ionflux::GeoUtils::TransformableObject& 
TransformableObject::operator=(const 
Ionflux::GeoUtils::TransformableObject& other)
{
    copyTransform(other);
	return *this;
}

Ionflux::GeoUtils::TransformableObject* TransformableObject::copy() const
{
    TransformableObject* newTransformableObject = create();
    *newTransformableObject = *this;
    return newTransformableObject;
}

Ionflux::GeoUtils::TransformableObject* 
TransformableObject::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<TransformableObject*>(other);
}

Ionflux::GeoUtils::TransformableObject* 
TransformableObject::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    TransformableObject* newObject = new TransformableObject();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

std::string TransformableObject::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string TransformableObject::getXMLAttributeData() const
{
	std::string a0(Ionflux::ObjectBase::IFObject::getXMLAttributeData());
	std::ostringstream d0;
	if (a0.size() > 0)
	    d0 << a0;
	return d0.str();
}

void TransformableObject::getXMLChildData(std::string& target, unsigned int
indentLevel) const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::ObjectBase::IFObject::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void TransformableObject::loadFromXMLFile(std::string& fileName)
{
	std::string data;
	Ionflux::ObjectBase::readFile(fileName, data);
	Ionflux::GeoUtils::XMLUtils::getTransformableObject(data, *this);
}

}

}

/** \file TransformableObject.cpp
 * \brief Transformable object implementation.
 */
