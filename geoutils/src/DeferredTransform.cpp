/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * DeferredTransform.cpp           Deferred matrix transformation 
 * (implementation).
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

#include "geoutils/DeferredTransform.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "ifobject/objectutils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Matrix4.hpp"
#include "geoutils/Vector.hpp"
#include "geoutils/VectorSet.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/DeferredTransformXMLFactory.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

DeferredTransformClassInfo::DeferredTransformClassInfo()
{
	name = "DeferredTransform";
	desc = "Deferred matrix transformation";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

DeferredTransformClassInfo::~DeferredTransformClassInfo()
{
}

// public member constants
const double DeferredTransform::COMPARE_TOLERANCE = 1e-6;

// run-time type information instance constants
const DeferredTransformClassInfo DeferredTransform::deferredTransformClassInfo;
const Ionflux::ObjectBase::IFClassInfo* DeferredTransform::CLASS_INFO = &DeferredTransform::deferredTransformClassInfo;

const std::string DeferredTransform::XML_ELEMENT_NAME = "deferred_transform";

DeferredTransform::DeferredTransform()
: transformChangedFlag(false), viChangedFlag(false), useTransformFlag(false), useVIFlag(false), transformMatrix(0), viewMatrix(0), imageMatrix(0), lastTransformMatrix(0), lastViewMatrix(0), lastImageMatrix(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

DeferredTransform::DeferredTransform(const Ionflux::GeoUtils::DeferredTransform& other)
: transformChangedFlag(false), viChangedFlag(false), useTransformFlag(false), useVIFlag(false), transformMatrix(0), viewMatrix(0), imageMatrix(0), lastTransformMatrix(0), lastViewMatrix(0), lastImageMatrix(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

DeferredTransform::~DeferredTransform()
{
	// TODO: Nothing ATM. ;-)
}

void DeferredTransform::resetTransform()
{
	setLastTransformMatrix(transformMatrix);
	transformChangedFlag = false;
}

void DeferredTransform::resetVI()
{
	setLastViewMatrix(viewMatrix);
	setLastImageMatrix(imageMatrix);
	viChangedFlag = false;
}

void DeferredTransform::reset()
{
	resetTransform();
	resetVI();
}

void DeferredTransform::clear()
{
	useTransformFlag = false;
	useVIFlag = false;
	transformChangedFlag = false;
	viChangedFlag = false;
	setTransformMatrix(0);
	setViewMatrix(0);
	setImageMatrix(0);
	setLastTransformMatrix(0);
	setLastViewMatrix(0);
	setLastImageMatrix(0);
}

Ionflux::GeoUtils::DeferredTransform& DeferredTransform::transform(const 
Ionflux::GeoUtils::Matrix4& matrix)
{
	setLastTransformMatrix(transformMatrix);
	if (transformMatrix == 0)
	    setTransformMatrix(Matrix4::UNIT.copy());
	transformMatrix->multiplyLeft(matrix);
	checkTransform();
	return *this;
}

Ionflux::GeoUtils::DeferredTransform& DeferredTransform::transformVI(const 
Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4* image)
{
	setLastViewMatrix(viewMatrix);
	setViewMatrix(view.copy());
	if (image != 0)
	{
	    setLastImageMatrix(imageMatrix);
	    setImageMatrix(image->copy());
	}
	checkVI();
	return *this;
}

bool DeferredTransform::checkTransform(double t)
{
	if (transformMatrix != 0) 
	{
	    if (transformMatrix->eq(Matrix4::UNIT, t))
	        useTransformFlag = false;
	    else
	        useTransformFlag = true;
	    if (lastTransformMatrix != 0)
	    {
	        transformChangedFlag = transformMatrix->eq(
	            *lastTransformMatrix, t);
	    } else
	        transformChangedFlag = true;
	} else
	{
	    useTransformFlag = false;
	    if (lastTransformMatrix != 0)
	        transformChangedFlag = true;
	    else
	        transformChangedFlag = false;
	}
	setLastTransformMatrix(transformMatrix);
	return useTransformFlag;
}

bool DeferredTransform::checkVI(double t)
{
	// Check view matrix.
	if (viewMatrix != 0) 
	{
	    if (viewMatrix->eq(Matrix4::UNIT, t))
	        useVIFlag = false;
	    else
	        useVIFlag = true;
	    if (lastViewMatrix != 0)
	    {
	        viChangedFlag = (!viewMatrix->eq(
	            *lastViewMatrix, t));
	    } else
	        viChangedFlag = true;
	} else
	{
	    useVIFlag = false;
	    if (lastViewMatrix != 0)
	        viChangedFlag = true;
	    else
	        viChangedFlag = false;
	}
	setLastViewMatrix(viewMatrix);
	// Check image matrix.
	if (imageMatrix != 0) 
	{
	    if (!imageMatrix->eq(Matrix4::UNIT, t))
	        useVIFlag = true;
	    if (lastImageMatrix != 0)
	    {
	        viChangedFlag = (viChangedFlag 
	            || (!imageMatrix->eq(*lastImageMatrix, t)));
	    } else
	        viChangedFlag = true;
	} else
	{
	    if (lastImageMatrix != 0)
	        viChangedFlag = true;
	}
	setLastImageMatrix(imageMatrix);
	return useVIFlag;
}

bool DeferredTransform::eq(const Ionflux::GeoUtils::DeferredTransform& 
other, double t) const
{
	bool result = true;
	if ((transformMatrix != 0) 
	    && (other.transformMatrix != 0))
	    result = transformMatrix->eq(*other.transformMatrix, t);
	else
	    result = false;
	if (!result)
	    return false;
	if ((viewMatrix != 0) 
	    && (other.viewMatrix != 0))
	    result = viewMatrix->eq(*other.viewMatrix, t);
	else
	    result = false;
	if (!result)
	    return false;
	if ((imageMatrix != 0) 
	    && (other.imageMatrix != 0))
	    result = imageMatrix->eq(*other.imageMatrix, t);
	else
	    result = false;
	return result;
}

bool DeferredTransform::operator==(const 
Ionflux::GeoUtils::DeferredTransform& other) const
{
	bool result = true;
	if ((transformMatrix != 0) 
	    && (other.transformMatrix != 0))
	    result = (*transformMatrix == *other.transformMatrix);
	else
	    result = false;
	if (!result)
	    return false;
	if ((viewMatrix != 0) 
	    && (other.viewMatrix != 0))
	    result = (*viewMatrix == *other.viewMatrix);
	else
	    result = false;
	if (!result)
	    return false;
	if ((imageMatrix != 0) 
	    && (other.imageMatrix != 0))
	    result = (*imageMatrix == *other.imageMatrix);
	else
	    result = false;
	return result;
}

bool DeferredTransform::operator!=(const 
Ionflux::GeoUtils::DeferredTransform& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

bool DeferredTransform::useTransform() const
{
	// TODO: Implementation.
	return useTransformFlag;
}

bool DeferredTransform::useVI() const
{
	// TODO: Implementation.
	return useVIFlag;
}

bool DeferredTransform::transformChanged() const
{
	// TODO: Implementation.
	return transformChangedFlag;
}

bool DeferredTransform::viChanged() const
{
	// TODO: Implementation.
	return viChangedFlag;
}

bool DeferredTransform::isIdentity() const
{
	if ((transformMatrix == 0) 
	    && (viewMatrix == 0) 
	    && (imageMatrix == 0))
	    return true;
	return useTransformFlag || useVIFlag;
}

void DeferredTransform::applyTransform(const Ionflux::GeoUtils::Vector& v, 
Ionflux::GeoUtils::Vector& target, bool clearTransform)
{
	if (!useTransformFlag
	    || (transformMatrix == 0))
	    target = v;
	else
	    transformMatrix->transform(v, target);
	if (clearTransform)
	{
	    useTransformFlag = false;
	    transformChangedFlag = false;
	    setTransformMatrix(0);
	    setLastTransformMatrix(0);
	}
}

void DeferredTransform::applyVI(const Ionflux::GeoUtils::Vector& v, 
Ionflux::GeoUtils::Vector& target, bool clearTransform)
{
	if (!useVIFlag
	    || ((viewMatrix == 0) 
	        && (imageMatrix == 0)))
	    target = v;
	else
	{
	    if (viewMatrix != 0)
	    {
	        viewMatrix->transform(v, target);
	        target.divideIP(target.getElement(
	            target.getNumElements() - 1));
	    }
	    if (imageMatrix != 0)
	    {
	        Vector* v0 = target.copy();
	        addLocalRef(v0);
	        imageMatrix->transform(target, *v0);
	        target = *v0;
	        removeLocalRef(v0);
	    }
	}
	if (clearTransform)
	{
	    useVIFlag = false;
	    viChangedFlag = false;
	    setViewMatrix(0);
	    setLastViewMatrix(0);
	    setImageMatrix(0);
	    setLastImageMatrix(0);
	}
}

void DeferredTransform::applyTransform(const Ionflux::GeoUtils::VectorSet& 
vectors, Ionflux::GeoUtils::VectorSet& target, bool clearTransform)
{
	if (!useTransformFlag
	    || (transformMatrix == 0))
	    target = vectors;
	else
	{
	    unsigned int numVectors = vectors.getNumVectors();
	    for (unsigned int i = 0; i < numVectors; i++)
	    {
	        Vector* v0 = vectors.getVector(i);
	        Vector* v1 = Ionflux::ObjectBase::nullPointerCheck(v0, this, 
	            "applyTransform", "Vector")->copy();
	        transformMatrix->transform(*v0, *v1);
	        target.addVector(v1);
	    }
	}
	if (clearTransform)
	{
	    useTransformFlag = false;
	    transformChangedFlag = false;
	    setTransformMatrix(0);
	    setLastTransformMatrix(0);
	}
}

void DeferredTransform::applyVI(const Ionflux::GeoUtils::VectorSet& 
vectors, Ionflux::GeoUtils::VectorSet& target, bool clearTransform)
{
	if (!useVIFlag
	    || ((viewMatrix == 0) 
	        && (imageMatrix == 0)))
	    target = vectors;
	else
	{
	    unsigned int numVectors = vectors.getNumVectors();
	    for (unsigned int i = 0; i < numVectors; i++)
	    {
	        Vector* v0 = vectors.getVector(i);
	        Vector* v1 = Ionflux::ObjectBase::nullPointerCheck(v0, this, 
	            "applyTransform", "Vector")->copy();
	        if (viewMatrix != 0)
	        {
	            viewMatrix->transform(*v0, *v1);
	            v1->divideIP(v1->getElement(
	                v1->getNumElements() - 1));
	        }
	        if (imageMatrix != 0)
	        {
	            Vector* v2 = v1->copy();
	            addLocalRef(v2);
	            imageMatrix->transform(*v1, *v2);
	            *v1 = *v2;
	            removeLocalRef(v2);
	        }
	        target.addVector(v1);
	    }
	}
	if (clearTransform)
	{
	    useVIFlag = false;
	    viChangedFlag = false;
	    setViewMatrix(0);
	    setLastViewMatrix(0);
	    setImageMatrix(0);
	    setLastImageMatrix(0);
	}
}

std::string DeferredTransform::getValueString() const
{
	if (isIdentity())
	    return "<Id>";
	std::ostringstream status;
	status << "T: ";
	if (transformMatrix != 0)
	    status << "[" << transformMatrix->getValueString() << "]";
	else
	    status << "<none>";
	status << "; V: ";
	if (viewMatrix != 0)
	    status << "[" << viewMatrix->getValueString() << "]";
	else
	    status << "<none>";
	status << "; I: ";
	if (imageMatrix != 0)
	    status << "[" << imageMatrix->getValueString() << "]";
	else
	    status << "<none>";
	return status.str();
}

void DeferredTransform::setTransformMatrix(Ionflux::GeoUtils::Matrix4* 
newTransformMatrix)
{
	if (transformMatrix == newTransformMatrix)
		return;
    if (newTransformMatrix != 0)
        addLocalRef(newTransformMatrix);
	if (transformMatrix != 0)
		removeLocalRef(transformMatrix);
	transformMatrix = newTransformMatrix;
	checkTransform();
}

Ionflux::GeoUtils::Matrix4* DeferredTransform::getTransformMatrix() const
{
    return transformMatrix;
}

void DeferredTransform::setViewMatrix(Ionflux::GeoUtils::Matrix4* 
newViewMatrix)
{
	if (viewMatrix == newViewMatrix)
		return;
    if (newViewMatrix != 0)
        addLocalRef(newViewMatrix);
	if (viewMatrix != 0)
		removeLocalRef(viewMatrix);
	viewMatrix = newViewMatrix;
	checkVI();
}

Ionflux::GeoUtils::Matrix4* DeferredTransform::getViewMatrix() const
{
    return viewMatrix;
}

void DeferredTransform::setImageMatrix(Ionflux::GeoUtils::Matrix4* 
newImageMatrix)
{
	if (imageMatrix == newImageMatrix)
		return;
    if (newImageMatrix != 0)
        addLocalRef(newImageMatrix);
	if (imageMatrix != 0)
		removeLocalRef(imageMatrix);
	imageMatrix = newImageMatrix;
	checkVI();
}

Ionflux::GeoUtils::Matrix4* DeferredTransform::getImageMatrix() const
{
    return imageMatrix;
}

void DeferredTransform::setLastTransformMatrix(Ionflux::GeoUtils::Matrix4* 
newLastTransformMatrix)
{
	if (lastTransformMatrix == newLastTransformMatrix)
		return;
    if (newLastTransformMatrix != 0)
        addLocalRef(newLastTransformMatrix);
	if (lastTransformMatrix != 0)
		removeLocalRef(lastTransformMatrix);
	lastTransformMatrix = newLastTransformMatrix;
}

Ionflux::GeoUtils::Matrix4* DeferredTransform::getLastTransformMatrix() 
const
{
    return lastTransformMatrix;
}

void DeferredTransform::setLastViewMatrix(Ionflux::GeoUtils::Matrix4* 
newLastViewMatrix)
{
	if (lastViewMatrix == newLastViewMatrix)
		return;
    if (newLastViewMatrix != 0)
        addLocalRef(newLastViewMatrix);
	if (lastViewMatrix != 0)
		removeLocalRef(lastViewMatrix);
	lastViewMatrix = newLastViewMatrix;
}

Ionflux::GeoUtils::Matrix4* DeferredTransform::getLastViewMatrix() const
{
    return lastViewMatrix;
}

void DeferredTransform::setLastImageMatrix(Ionflux::GeoUtils::Matrix4* 
newLastImageMatrix)
{
	if (lastImageMatrix == newLastImageMatrix)
		return;
    if (newLastImageMatrix != 0)
        addLocalRef(newLastImageMatrix);
	if (lastImageMatrix != 0)
		removeLocalRef(lastImageMatrix);
	lastImageMatrix = newLastImageMatrix;
}

Ionflux::GeoUtils::Matrix4* DeferredTransform::getLastImageMatrix() const
{
    return lastImageMatrix;
}

Ionflux::GeoUtils::DeferredTransform& DeferredTransform::operator=(const 
Ionflux::GeoUtils::DeferredTransform& other)
{
    if (this == &other)
        return *this;
    clear();
    if (other.transformMatrix != 0)
        setTransformMatrix(other.transformMatrix->copy());
    if (other.viewMatrix != 0)
        setViewMatrix(other.viewMatrix->copy());
    if (other.imageMatrix != 0)
        setImageMatrix(other.imageMatrix->copy());
	return *this;
}

Ionflux::GeoUtils::DeferredTransform* DeferredTransform::copy() const
{
    DeferredTransform* newDeferredTransform = create();
    *newDeferredTransform = *this;
    return newDeferredTransform;
}

Ionflux::GeoUtils::DeferredTransform* 
DeferredTransform::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<DeferredTransform*>(other);
}

Ionflux::GeoUtils::DeferredTransform* 
DeferredTransform::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    DeferredTransform* newObject = new DeferredTransform();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int DeferredTransform::getMemSize() const
{
    return sizeof *this;
}

std::string DeferredTransform::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string DeferredTransform::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::ObjectBase::IFObject::getXMLAttributeData();
	return d0.str();
}

void DeferredTransform::getXMLChildData(std::string& target, unsigned int 
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
    if (transformMatrix != 0)
    {
        if (!xcFirst || haveBCData)
            d0 << "\n";
	    d0 << transformMatrix->getXML0(indentLevel, "pname=\"transform_matrix\"");
	    xcFirst = false;
    }
    if (viewMatrix != 0)
    {
        if (!xcFirst || haveBCData)
            d0 << "\n";
	    d0 << viewMatrix->getXML0(indentLevel, "pname=\"view_matrix\"");
	    xcFirst = false;
    }
    if (imageMatrix != 0)
    {
        if (!xcFirst || haveBCData)
            d0 << "\n";
	    d0 << imageMatrix->getXML0(indentLevel, "pname=\"image_matrix\"");
	    xcFirst = false;
    }
	target = d0.str();
}

void DeferredTransform::loadFromXMLFile(const std::string& fileName)
{
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, getXMLElementName());
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
DeferredTransform::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::DeferredTransformXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::DeferredTransformXMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 
            IFObject::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file DeferredTransform.cpp
 * \brief Deferred matrix transformation implementation.
 */
