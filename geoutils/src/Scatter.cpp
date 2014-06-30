/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Scatter.cpp                     Transform node: Scatter 
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

#include "geoutils/Scatter.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "ifmapping/utils.hpp"
#include "ifmapping/RandomNorm.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Compose3.hpp"
#include "geoutils/Lookup3.hpp"
#include "geoutils/AcceptVolume3.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;
using namespace Ionflux::Mapping;
using namespace Ionflux::GeoUtils::Mapping;

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

ScatterClassInfo::ScatterClassInfo()
{
	name = "Scatter";
	desc = "Transform node: Scatter";
}

ScatterClassInfo::~ScatterClassInfo()
{
}

// public member constants
const unsigned int Scatter::INPUT_SOURCE = 0;
const unsigned int Scatter::OUTPUT_TARGET = 0;
const unsigned int Scatter::DEFAULT_NUM_LUT_ENTRIES = 100;
const Ionflux::Mapping::Range Scatter::OFFSET_INDEX_RANGE = { 0., 1. };

// run-time type information instance constants
const ScatterClassInfo Scatter::scatterClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Scatter::CLASS_INFO = &Scatter::scatterClassInfo;

Scatter::Scatter()
: offset(GeoUtils::Vector3::ZERO), offsetFunc(0), offsetIndexFunc(0), offsetScale(GeoUtils::Vector3::E_SUM), offsetScaleFactor(1.), offsetDeltaScaleFactor(0.), offsetIndexOffset(0.), offsetIndexScale(1.), elementScale(GeoUtils::Vector3::E_SUM), elementScaleFactor(1.), elementDeltaScaleFactor(0.), elementScaleIndexFunc(0), elementScaleDistanceFunc(0), centeringMethod(CENTER_BARYCENTER)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Scatter::Scatter(const Ionflux::GeoUtils::TransformNodes::Scatter& other)
: offset(GeoUtils::Vector3::ZERO), offsetFunc(0), offsetIndexFunc(0), offsetScale(GeoUtils::Vector3::E_SUM), offsetScaleFactor(1.), offsetDeltaScaleFactor(0.), offsetIndexOffset(0.), offsetIndexScale(1.), elementScale(GeoUtils::Vector3::E_SUM), elementScaleFactor(1.), elementDeltaScaleFactor(0.), elementScaleIndexFunc(0), elementScaleDistanceFunc(0), centeringMethod(CENTER_BARYCENTER)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Scatter::Scatter(const Ionflux::GeoUtils::Vector3& initOffset, 
Ionflux::GeoUtils::Mapping::Vector3Mapping* initOffsetFunc, 
Ionflux::Mapping::Mapping* initOffsetIndexFunc, const 
Ionflux::GeoUtils::Vector3& initOffsetScale, Ionflux::Mapping::MappingValue
initOffsetScaleFactor, Ionflux::Mapping::MappingValue 
initOffsetDeltaScaleFactor, Ionflux::Mapping::MappingValue 
initOffsetIndexOffset, Ionflux::Mapping::MappingValue initOffsetIndexScale,
const Ionflux::GeoUtils::Vector3& initElementScale, 
Ionflux::Mapping::MappingValue initElementScaleFactor, 
Ionflux::Mapping::MappingValue initElementDeltaScaleFactor, 
Ionflux::GeoUtils::Mapping::Vector3Mapping* initElementScaleIndexFunc, 
Ionflux::GeoUtils::Mapping::Vector3Mapping* initElementScaleDistanceFunc, 
Ionflux::GeoUtils::CenteringMethod initCenteringMethod, const 
Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID), offset(initOffset), offsetFunc(0), 
offsetIndexFunc(0), offsetScale(initOffsetScale), 
offsetScaleFactor(initOffsetScaleFactor), 
offsetDeltaScaleFactor(initOffsetDeltaScaleFactor), 
offsetIndexOffset(initOffsetIndexOffset), 
offsetIndexScale(initOffsetIndexScale), elementScale(initElementScale), 
elementScaleFactor(initElementScaleFactor), 
elementDeltaScaleFactor(initElementDeltaScaleFactor), 
elementScaleIndexFunc(0), elementScaleDistanceFunc(0), 
centeringMethod(initCenteringMethod)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setOffsetFunc(initOffsetFunc);
	setOffsetIndexFunc(initOffsetIndexFunc);
	setElementScaleIndexFunc(initElementScaleIndexFunc);
	setElementScaleDistanceFunc(initElementScaleDistanceFunc);
}

Scatter::~Scatter()
{
	// TODO: Nothing ATM. ;-)
}

void Scatter::process()
{
	if (offsetFunc == 0)
	    throw GeoUtilsError("Offset mapping not set.");
	if (inputCache.size() < 1)
	    throw GeoUtilsError("Input cache is empty.");
	clearInputGroups();
	TransformableGroup* g0 = inputCache[0];
	/* Since we are going to manipulate the individual elements, 
	   any existing group transformations must be applied first. */
	g0->applyTransform();
	// Process elements from the input group.
	unsigned int numSourceItems = g0->getNumItems();
	/* <---- DEBUG ----- //
	std::ostringstream message;
	message << "START: Group: barycenter = " << g0->getBarycenter()
	    << ", bounds.center = " << g0->getBounds().getCenter();
	log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	// ----- DEBUG ----> */
	for (unsigned int i = 0; i < numSourceItems; i++)
	{
	    TransformableObject* o0 = g0->getItem(i);
	    /* <---- DEBUG ----- //
	    message.str("");
	    message << "Processing object: " << o0->getClassName() 
	        << " (barycenter = " << o0->getBarycenter() << ")";
	    log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	    // ----- DEBUG ----> */
	    // Calculate the element offset.
	    MappingValue i0 = Ionflux::Mapping::wrap(
	        static_cast<MappingValue>(i) / (numSourceItems - 1.) 
	        * offsetIndexScale + offsetIndexOffset, OFFSET_INDEX_RANGE);
	    if (offsetIndexFunc != 0)
	        i0 = (*offsetIndexFunc)(i0);
	    Vector3 v0((*offsetFunc)(i0));
	    // Scale the offset vector.
	    Vector3 s1((offsetScaleFactor + i * offsetDeltaScaleFactor) 
	        * offsetScale);
	    v0 = offset + v0.multElements(s1);
	    // Translate the object.
	    o0->translate(v0);
	    /* <---- DEBUG ----- //
	    message.str("");
	    message << "After translation: barycenter = " << o0->getBarycenter();
	    log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	    // ----- DEBUG ----> */
	    // Calculate the element scale.
	    Vector3 s0((elementScaleFactor + i * elementDeltaScaleFactor) 
	        * elementScale);
	    if (elementScaleIndexFunc != 0)
	        // Multiply element scaling according to index mapping.
	        s0 = s0.multElements(
	            (*elementScaleIndexFunc)(static_cast<double>(i) 
	                / (numSourceItems - 1)));
	    // Determine the center vector.
	    Vector3 c0;
	    if (centeringMethod == CENTER_BOUNDS)
	        c0 = o0->getBounds().getCenter();
	    else
	    if (centeringMethod == CENTER_BARYCENTER)
	        c0 = o0->getBarycenter();
	    else
	        c0 = Vector3::ZERO;
	    if (elementScaleDistanceFunc != 0)
	    {
	        // Multiply element scaling according to distance mapping.
	        double r0 = c0.norm();
	        s0 = s0.multElements((*elementScaleDistanceFunc)(r0));
	    }
	    /* <---- DEBUG ----- //
	    message.str("");
	    message << "Scaling center: " << c0 << " (v0 = " 
	        << v0 << ", s0 = " << s0 << ", centeringMethod = " 
	        << centeringMethod << ").";
	    log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	    // ----- DEBUG ----> */
	    // Scale the object.
	    o0->translate(c0.flip());
	    /* <---- DEBUG ----- //
	    message.str("");
	    message << "Before scaling: barycenter = " << o0->getBarycenter();
	    log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	    // ----- DEBUG ----> */
	    o0->scale(s0);
	    /* <---- DEBUG ----- //
	    message.str("");
	    message << "After scaling: barycenter = " << o0->getBarycenter();
	    log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	    // ----- DEBUG ----> */
	    o0->translate(c0);
	    /* <---- DEBUG ----- //
	    message.str("");
	    message << "Result: barycenter = " << o0->getBarycenter() 
	        << ", bounds.center = " << o0->getBounds().getCenter() 
	        << ", v0 = " << v0;
	    log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	    // ----- DEBUG ----> */
	}
	/* <---- DEBUG ----- //
	message.str("");
	message << "END: Group: barycenter = " << g0->getBarycenter() 
	    << ", bounds = " << g0->getBounds() << ", bounds.center = " 
	    << g0->getBounds().getCenter();
	log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	// ----- DEBUG ----> */
	addOutput(g0);
}

std::string Scatter::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") << "]";
	return status.str();
}

Ionflux::GeoUtils::Mapping::Vector3Mapping* Scatter::createLUT(unsigned int
numEntries, const Ionflux::GeoUtils::Vector3& stdDev, const 
Ionflux::GeoUtils::Vector3& mean, Ionflux::GeoUtils::Shape3* refObject, 
Ionflux::Mapping::Mapping* sourceFuncX, Ionflux::Mapping::Mapping* 
sourceFuncY, Ionflux::Mapping::Mapping* sourceFuncZ)
{
	// Create default source mappings if necessary.
	RandomNorm* m0 = 0;
	if (sourceFuncX == 0)
	{
	    m0 = RandomNorm::create();
	    m0->setMean(mean.getX0());
	    m0->setStdDev(stdDev.getX0());
	    sourceFuncX = m0;
	}
	if (sourceFuncY == 0)
	{
	    m0 = RandomNorm::create();
	    m0->setMean(mean.getX1());
	    m0->setStdDev(stdDev.getX1());
	    sourceFuncY = m0;
	}
	if (sourceFuncZ == 0)
	{
	    m0 = RandomNorm::create();
	    m0->setMean(mean.getX2());
	    m0->setStdDev(stdDev.getX2());
	    sourceFuncZ = m0;
	}
	// Create the lookup table.
	Compose3* m1 = Compose3::create();
	m1->setFuncX0(sourceFuncX);
	m1->setFuncX1(sourceFuncY);
	m1->setFuncX2(sourceFuncZ);
	Lookup3* result = Lookup3::create();
	if (refObject != 0)
	{
	    // Insert the reference volume check.
	    AcceptVolume3* m2 = AcceptVolume3::create();
	    m2->setRefObject(refObject);
	    m2->setSource(m1);
	    result->setSource(m2);
	} else
	    // Use the source mappings in unmodified form.
	    result->setSource(m1);
	result->update(numEntries);
	return result;
}

void Scatter::setOffset(const Ionflux::GeoUtils::Vector3& newOffset)
{
	offset = newOffset;
}

Ionflux::GeoUtils::Vector3 Scatter::getOffset() const
{
    return offset;
}

void Scatter::setOffsetFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
newOffsetFunc)
{
	if (offsetFunc == newOffsetFunc)
		return;
    if (newOffsetFunc != 0)
        addLocalRef(newOffsetFunc);
	if (offsetFunc != 0)
		removeLocalRef(offsetFunc);
	offsetFunc = newOffsetFunc;
}

Ionflux::GeoUtils::Mapping::Vector3Mapping* Scatter::getOffsetFunc() const
{
    return offsetFunc;
}

void Scatter::setOffsetIndexFunc(Ionflux::Mapping::Mapping* 
newOffsetIndexFunc)
{
	if (offsetIndexFunc == newOffsetIndexFunc)
		return;
    if (newOffsetIndexFunc != 0)
        addLocalRef(newOffsetIndexFunc);
	if (offsetIndexFunc != 0)
		removeLocalRef(offsetIndexFunc);
	offsetIndexFunc = newOffsetIndexFunc;
}

Ionflux::Mapping::Mapping* Scatter::getOffsetIndexFunc() const
{
    return offsetIndexFunc;
}

void Scatter::setOffsetScale(const Ionflux::GeoUtils::Vector3& 
newOffsetScale)
{
	offsetScale = newOffsetScale;
}

Ionflux::GeoUtils::Vector3 Scatter::getOffsetScale() const
{
    return offsetScale;
}

void Scatter::setOffsetScaleFactor(Ionflux::Mapping::MappingValue 
newOffsetScaleFactor)
{
	offsetScaleFactor = newOffsetScaleFactor;
}

Ionflux::Mapping::MappingValue Scatter::getOffsetScaleFactor() const
{
    return offsetScaleFactor;
}

void Scatter::setOffsetDeltaScaleFactor(Ionflux::Mapping::MappingValue 
newOffsetDeltaScaleFactor)
{
	offsetDeltaScaleFactor = newOffsetDeltaScaleFactor;
}

Ionflux::Mapping::MappingValue Scatter::getOffsetDeltaScaleFactor() const
{
    return offsetDeltaScaleFactor;
}

void Scatter::setOffsetIndexOffset(Ionflux::Mapping::MappingValue 
newOffsetIndexOffset)
{
	offsetIndexOffset = newOffsetIndexOffset;
}

Ionflux::Mapping::MappingValue Scatter::getOffsetIndexOffset() const
{
    return offsetIndexOffset;
}

void Scatter::setOffsetIndexScale(Ionflux::Mapping::MappingValue 
newOffsetIndexScale)
{
	offsetIndexScale = newOffsetIndexScale;
}

Ionflux::Mapping::MappingValue Scatter::getOffsetIndexScale() const
{
    return offsetIndexScale;
}

void Scatter::setElementScale(const Ionflux::GeoUtils::Vector3& 
newElementScale)
{
	elementScale = newElementScale;
}

Ionflux::GeoUtils::Vector3 Scatter::getElementScale() const
{
    return elementScale;
}

void Scatter::setElementScaleFactor(Ionflux::Mapping::MappingValue 
newElementScaleFactor)
{
	elementScaleFactor = newElementScaleFactor;
}

Ionflux::Mapping::MappingValue Scatter::getElementScaleFactor() const
{
    return elementScaleFactor;
}

void Scatter::setElementDeltaScaleFactor(Ionflux::Mapping::MappingValue 
newElementDeltaScaleFactor)
{
	elementDeltaScaleFactor = newElementDeltaScaleFactor;
}

Ionflux::Mapping::MappingValue Scatter::getElementDeltaScaleFactor() const
{
    return elementDeltaScaleFactor;
}

void 
Scatter::setElementScaleIndexFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping*
newElementScaleIndexFunc)
{
	if (elementScaleIndexFunc == newElementScaleIndexFunc)
		return;
    if (newElementScaleIndexFunc != 0)
        addLocalRef(newElementScaleIndexFunc);
	if (elementScaleIndexFunc != 0)
		removeLocalRef(elementScaleIndexFunc);
	elementScaleIndexFunc = newElementScaleIndexFunc;
}

Ionflux::GeoUtils::Mapping::Vector3Mapping* 
Scatter::getElementScaleIndexFunc() const
{
    return elementScaleIndexFunc;
}

void 
Scatter::setElementScaleDistanceFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping*
newElementScaleDistanceFunc)
{
	if (elementScaleDistanceFunc == newElementScaleDistanceFunc)
		return;
    if (newElementScaleDistanceFunc != 0)
        addLocalRef(newElementScaleDistanceFunc);
	if (elementScaleDistanceFunc != 0)
		removeLocalRef(elementScaleDistanceFunc);
	elementScaleDistanceFunc = newElementScaleDistanceFunc;
}

Ionflux::GeoUtils::Mapping::Vector3Mapping* 
Scatter::getElementScaleDistanceFunc() const
{
    return elementScaleDistanceFunc;
}

void Scatter::setCenteringMethod(Ionflux::GeoUtils::CenteringMethod 
newCenteringMethod)
{
	centeringMethod = newCenteringMethod;
}

Ionflux::GeoUtils::CenteringMethod Scatter::getCenteringMethod() const
{
    return centeringMethod;
}

Ionflux::GeoUtils::TransformNodes::Scatter& Scatter::operator=(const 
Ionflux::GeoUtils::TransformNodes::Scatter& other)
{
    TransformNode::operator=(other);
    offset = other.offset;
    setOffsetFunc(other.offsetFunc);
    setOffsetIndexFunc(other.offsetIndexFunc);
    offsetScale = other.offsetScale;
    offsetScaleFactor = other.offsetScaleFactor;
    offsetDeltaScaleFactor = other.offsetDeltaScaleFactor;
    offsetIndexOffset = other.offsetIndexOffset;
    offsetIndexScale = other.offsetIndexScale;
    elementScale = other.elementScale;
    elementScaleFactor = other.elementScaleFactor;
    elementDeltaScaleFactor = other.elementDeltaScaleFactor;
    setElementScaleIndexFunc(other.elementScaleIndexFunc);
    setElementScaleDistanceFunc(other.elementScaleDistanceFunc);
    centeringMethod = other.centeringMethod;
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Scatter* Scatter::copy() const
{
    Scatter* newScatter = create();
    *newScatter = *this;
    return newScatter;
}

Ionflux::GeoUtils::TransformNodes::Scatter* 
Scatter::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Scatter*>(other);
}

Ionflux::GeoUtils::TransformNodes::Scatter* 
Scatter::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Scatter* newObject = new Scatter();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Scatter::getMemSize() const
{
    return sizeof *this;
}

void Scatter::setParam(Ionflux::ObjectBase::IFParamID paramID, 
Ionflux::Mapping::MappingValue paramValue)
{
    if (paramID == "offsetScaleFactor")
    {
        setOffsetScaleFactor(paramValue);
        return;
    }
    if (paramID == "offsetDeltaScaleFactor")
    {
        setOffsetDeltaScaleFactor(paramValue);
        return;
    }
    if (paramID == "offsetIndexOffset")
    {
        setOffsetIndexOffset(paramValue);
        return;
    }
    if (paramID == "offsetIndexScale")
    {
        setOffsetIndexScale(paramValue);
        return;
    }
    if (paramID == "elementScaleFactor")
    {
        setElementScaleFactor(paramValue);
        return;
    }
    if (paramID == "elementDeltaScaleFactor")
    {
        setElementDeltaScaleFactor(paramValue);
        return;
    }
    throw GeoUtilsError(std::string("Parameter '") 
        + paramID + "' does not exist.");
}

Ionflux::Mapping::MappingValue 
Scatter::getParam(Ionflux::ObjectBase::IFParamID paramID)
{
    if (paramID == "offsetScaleFactor")
        return getOffsetScaleFactor();
    if (paramID == "offsetDeltaScaleFactor")
        return getOffsetDeltaScaleFactor();
    if (paramID == "offsetIndexOffset")
        return getOffsetIndexOffset();
    if (paramID == "offsetIndexScale")
        return getOffsetIndexScale();
    if (paramID == "elementScaleFactor")
        return getElementScaleFactor();
    if (paramID == "elementDeltaScaleFactor")
        return getElementDeltaScaleFactor();
    throw GeoUtilsError(std::string("Parameter '") 
        + paramID + "' does not exist.");
}

}

}

}

/** \file Scatter.cpp
 * \brief Transform node: Scatter implementation.
 */
