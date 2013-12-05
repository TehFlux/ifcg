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
#include "ifobject/objectutils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Vertex3.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/TransformableObjectXMLFactory.hpp"

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
: boundsCache(0), deferredTransform(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

TransformableObject::TransformableObject(const Ionflux::GeoUtils::TransformableObject& other)
: boundsCache(0), deferredTransform(0)
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
	if (deferredTransform != 0)
	    deferredTransform->reset();
}

void TransformableObject::clearTransformations()
{
	setDeferredTransform(0);
}

void TransformableObject::clear()
{
	clearTransformations();
}

void TransformableObject::copyTransform(const 
Ionflux::GeoUtils::TransformableObject& other)
{
	if (other.deferredTransform != 0)
	    setDeferredTransform(other.deferredTransform->copy());
	else
	    setDeferredTransform(0);
}

void TransformableObject::onTransformChanged()
{
	// TODO: Implementation.
}

void TransformableObject::onVIChanged()
{
	// TODO: Implementation.
}

bool TransformableObject::checkTransform(double t)
{
	if (deferredTransform == 0)
	    return false;
	bool result = deferredTransform->checkTransform();
	if (result)
	    onTransformChanged();
	return result;
}

bool TransformableObject::checkVI(double t)
{
	if (deferredTransform == 0)
	    return false;
	bool result = deferredTransform->checkVI();
	if (result)
	    onVIChanged();
	return result;
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
	if (deferredTransform == 0)
	    setDeferredTransform(DeferredTransform::create());
	deferredTransform->transform(matrix);
	checkTransform();
	return *this;
}

Ionflux::GeoUtils::TransformableObject& 
TransformableObject::transformVI(const Ionflux::GeoUtils::Matrix4& view, 
const Ionflux::GeoUtils::Matrix4* image)
{
	if (deferredTransform == 0)
	    setDeferredTransform(DeferredTransform::create());
	deferredTransform->transformVI(view, image);
	checkVI();
	return *this;
}

void TransformableObject::applyTransform(bool recursive)
{
	clearTransformations();
}

Ionflux::GeoUtils::Vector3 TransformableObject::getBarycenter()
{
	if (!useTransform() && !useVI())
	    return Vector3::ZERO;
	Vertex3 v0;
	if (useTransform())
	{
	    Matrix4* transformMatrix = Ionflux::ObjectBase::nullPointerCheck(
	        deferredTransform->getTransformMatrix(), this, 
	        "getBarycenter", "Transformation matrix");
	    v0.transform(*transformMatrix);
	}
	if (useVI())
	{
	    Matrix4* viewMatrix = Ionflux::ObjectBase::nullPointerCheck(
	        deferredTransform->getViewMatrix(), this, 
	        "getBarycenter", "View matrix");
	    Matrix4* imageMatrix = deferredTransform->getImageMatrix();
	    v0.transformVI(*viewMatrix, imageMatrix);
	}
	return v0.getVector();;
}

Ionflux::GeoUtils::Range3 TransformableObject::getBounds()
{
	if ((boundsCache == 0) 
	    || transformChanged() 
	    || viChanged())
	    processTransformChange();
	return *boundsCache;
}

bool TransformableObject::useTransform() const
{
	if (deferredTransform == 0)
	    return false;
	return deferredTransform->useTransform();
}

bool TransformableObject::useVI() const
{
	if (deferredTransform == 0)
	    return false;
	return deferredTransform->useVI();
}

bool TransformableObject::transformChanged() const
{
	if (deferredTransform == 0)
	    return false;
	return deferredTransform->transformChanged();
}

bool TransformableObject::viChanged() const
{
	if (deferredTransform == 0)
	    return false;
	return deferredTransform->viChanged();
}

Ionflux::GeoUtils::TransformableObject& TransformableObject::duplicate()
{
	// TODO: Implementation.
	return *copy();
}

Ionflux::GeoUtils::Matrix4* TransformableObject::getTransformMatrix() const
{
	Ionflux::ObjectBase::nullPointerCheck(
	    deferredTransform, this, "getTransformMatrix", 
	    "Deferred transformation");
	Matrix4* m0 = Ionflux::ObjectBase::nullPointerCheck(
	    deferredTransform->getTransformMatrix(), this, 
	    "getTransformMatrix", "Transformation matrix");
	return m0;
}

Ionflux::GeoUtils::Matrix4* TransformableObject::getViewMatrix() const
{
	Ionflux::ObjectBase::nullPointerCheck(
	    deferredTransform, this, "getViewMatrix", 
	    "Deferred transformation");
	Matrix4* m0 = Ionflux::ObjectBase::nullPointerCheck(
	    deferredTransform->getViewMatrix(), this, 
	    "getViewMatrix", "View transformation matrix");
	return m0;
}

Ionflux::GeoUtils::Matrix4* TransformableObject::getImageMatrix() const
{
	Ionflux::ObjectBase::nullPointerCheck(
	    deferredTransform, this, "getImageMatrix", 
	    "Deferred transformation");
	Matrix4* m0 = deferredTransform->getImageMatrix();
	return m0;
}

std::string TransformableObject::getValueString() const
{
	if (!useTransform() && !useVI())
	    return "";
	ostringstream status;
	if (useTransform())
	    status << "T: [" << getTransformMatrix()->getValueString() 
	        << "]";
	if (useVI())
	{
	    if (useTransform())
	        status << ", ";
	    status << "V: [" << getViewMatrix()->getValueString() << "], ";
	    Matrix4* im0 = getImageMatrix();
	    if (im0 != 0)
	        status << "[" << im0->getValueString() << "]";
	    else
	        status << "<none>";
	}
	return status.str();
}

void 
TransformableObject::setDeferredTransform(Ionflux::GeoUtils::DeferredTransform*
newDeferredTransform)
{
	if (deferredTransform == newDeferredTransform)
		return;
    if (newDeferredTransform != 0)
        addLocalRef(newDeferredTransform);
	if (deferredTransform != 0)
		removeLocalRef(deferredTransform);
	deferredTransform = newDeferredTransform;
}

Ionflux::GeoUtils::DeferredTransform* 
TransformableObject::getDeferredTransform() const
{
    return deferredTransform;
}

Ionflux::GeoUtils::TransformableObject& 
TransformableObject::operator=(const 
Ionflux::GeoUtils::TransformableObject& other)
{
    if (this == &other)
        return *this;
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
	std::string iws0 = Ionflux::ObjectBase::getIndent(indentLevel);
	bool haveBCData = false;
	if (d0.str().size() > 0)
	    haveBCData = true;
	bool xcFirst = true;
    if (deferredTransform != 0)
    {
        if (!xcFirst || haveBCData)
            d0 << "\n";
	    d0 << deferredTransform->getXML0(indentLevel, "pname=\"deferred_transform\"");
	    xcFirst = false;
    }
	target = d0.str();
}

void TransformableObject::loadFromXMLFile(const std::string& fileName)
{
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, getXMLElementName());
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
TransformableObject::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::TransformableObjectXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::TransformableObjectXMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 
            IFObject::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file TransformableObject.cpp
 * \brief Transformable object implementation.
 */
