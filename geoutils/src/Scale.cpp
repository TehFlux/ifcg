/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Scale.cpp                       Transform node: Scale (implementation).
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

#include "geoutils/Scale.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "geoutils/GeoUtilsError.hpp"
#include "ifmapping/utils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;
using Ionflux::Mapping::defaultStr;

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

ScaleClassInfo::ScaleClassInfo()
{
	name = "Scale";
	desc = "Transform node: Scale";
}

ScaleClassInfo::~ScaleClassInfo()
{
}

// public member constants
const unsigned int Scale::INPUT_SOURCE = 0;
const unsigned int Scale::OUTPUT_TARGET = 0;

// run-time type information instance constants
const ScaleClassInfo Scale::scaleClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Scale::CLASS_INFO = &Scale::scaleClassInfo;

Scale::Scale()
: scale(1., 1. ,1.), indexFunc(0), distanceFunc(0), centeringMethod(CENTER_ORIGIN), scaleFactor(1.), deltaScaleFactor(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Scale::Scale(const Ionflux::GeoUtils::TransformNodes::Scale& other)
: scale(1., 1. ,1.), indexFunc(0), distanceFunc(0), centeringMethod(CENTER_ORIGIN), scaleFactor(1.), deltaScaleFactor(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Scale::Scale(const Ionflux::GeoUtils::Vector3& initScale, 
Ionflux::GeoUtils::Mapping::Vector3Mapping* initIndexFunc, 
Ionflux::GeoUtils::Mapping::Vector3Mapping* initDistanceFunc, 
Ionflux::GeoUtils::CenteringMethod initCenteringMethod, 
Ionflux::Mapping::MappingValue initScaleFactor, 
Ionflux::Mapping::MappingValue initDeltaScaleFactor, const 
Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID), scale(initScale), indexFunc(0), distanceFunc(0), 
centeringMethod(initCenteringMethod), scaleFactor(initScaleFactor), 
deltaScaleFactor(initDeltaScaleFactor)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setIndexFunc(initIndexFunc);
	setDistanceFunc(initDistanceFunc);
}

Scale::~Scale()
{
	// TODO: Nothing ATM. ;-)
}

void Scale::process()
{
	if (inputCache.size() < 1)
	    throw GeoUtilsError("Input cache is empty.");
	clearInputGroups();
	TransformableGroup* g0 = inputCache[0];
	if ((centeringMethod == CENTER_ORIGIN) 
	    && (indexFunc == 0) 
	    && (distanceFunc == 0))
	    // All elements are scaled uniformly by the scale vector.
	    g0->scale(scaleFactor * scale);
	else
	{
	    /* Since we are going to manipulate the individual elements, 
	       any existing group transformations must be applied first. */
	    g0->applyTransform();
	    Vector3 c0;
	    // Scale elements individually according to the mappings.
	    unsigned int numSourceItems = g0->getNumItems();
	    /* <---- DEBUG ----- //
	    ostringstream message;
	    message << "numSourceItems = " << numSourceItems;
	    log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	    // ----- DEBUG ----> */
	    for (unsigned int i = 0; i < numSourceItems; i++)
	    {
	        TransformableObject* o0 = g0->getItem(i);
	        /* <---- DEBUG ----- //
	        message.str("");
	        message << "Processing item #" << i;
	        log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	        // ----- DEBUG ----> */
	        // Calculate the total scale factor for the element.
	        /* <---- DEBUG ----- //
	        message.str("");
	        message << "scale = " << scale << ", scaleFactor = " << 
	scaleFactor 
	            << ", deltaScaleFactor = " << deltaScaleFactor;
	        log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	        // ----- DEBUG ----> */
	        Vector3 s0(scale);
	        s0 = (scaleFactor + i * deltaScaleFactor) * s0;
	        if (indexFunc != 0)
	        {
	            // Multiply scaling according to index mapping.
	            /* NOTE: Not applying index range at this time since it 
	                     does not really work as expected. */
	            Ionflux::Mapping::MappingValue t = static_cast<double>(i) 
	                / (numSourceItems - 1);
	            Vector3 v0 = (*indexFunc)(t);
	            /* <---- DEBUG ----- //
	            message.str("");
	            message << "indexFunc(" << t << ") = " << v0;
	            log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	            // ----- DEBUG ----> */
	            s0 = s0.multElements(v0);
	        }
	        if (distanceFunc != 0)
	        {
	            // Multiply scaling according to distance mapping.
	            double r0 = o0->getBarycenter().norm();
	            s0 = s0.multElements((*distanceFunc)(r0));
	        }
	        // Determine the center vector.
	        /* <---- DEBUG ----- //
	        log(IFLogMessage("Calculating scaling center...", VL_DEBUG, 
	            this, "process"));
	        // ----- DEBUG ----> */
	        if (centeringMethod == CENTER_BOUNDS)
	            c0 = o0->getBounds().getCenter();
	        else
	        if (centeringMethod == CENTER_BARYCENTER)
	            c0 = o0->getBarycenter();
	        else
	            c0 = Vector3::ZERO;
	        // Scale the object.
	        /* <---- DEBUG ----- //
	        message.str("");
	        message << "Transforming object (s0 = " << s0 << ").";
	        log(IFLogMessage(message.str(), VL_DEBUG, 
	            this, "process"));
	        // ----- DEBUG ----> */
	        o0->translate(c0.flip());
	        o0->scale(s0);
	        o0->translate(c0);
	    }
	}
	addOutput(g0);
}

std::string Scale::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") << "; ";
	if (indexFunc != 0)
	    status << indexFunc->getString();
	else
	    status << "<none>";
	if (distanceFunc != 0)
	    status << ", " << distanceFunc->getString();
	else
	    status << ", <none>";
	status << "]";
	return status.str();
}

void Scale::setScale(const Ionflux::GeoUtils::Vector3& newScale)
{
	scale = newScale;
}

Ionflux::GeoUtils::Vector3 Scale::getScale() const
{
    return scale;
}

void Scale::setIndexFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
newIndexFunc)
{
	if (indexFunc == newIndexFunc)
		return;
    if (newIndexFunc != 0)
        addLocalRef(newIndexFunc);
	if (indexFunc != 0)
		removeLocalRef(indexFunc);
	indexFunc = newIndexFunc;
}

Ionflux::GeoUtils::Mapping::Vector3Mapping* Scale::getIndexFunc() const
{
    return indexFunc;
}

void Scale::setDistanceFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
newDistanceFunc)
{
	if (distanceFunc == newDistanceFunc)
		return;
    if (newDistanceFunc != 0)
        addLocalRef(newDistanceFunc);
	if (distanceFunc != 0)
		removeLocalRef(distanceFunc);
	distanceFunc = newDistanceFunc;
}

Ionflux::GeoUtils::Mapping::Vector3Mapping* Scale::getDistanceFunc() const
{
    return distanceFunc;
}

void Scale::setCenteringMethod(Ionflux::GeoUtils::CenteringMethod 
newCenteringMethod)
{
	centeringMethod = newCenteringMethod;
}

Ionflux::GeoUtils::CenteringMethod Scale::getCenteringMethod() const
{
    return centeringMethod;
}

void Scale::setScaleFactor(Ionflux::Mapping::MappingValue newScaleFactor)
{
	scaleFactor = newScaleFactor;
}

Ionflux::Mapping::MappingValue Scale::getScaleFactor() const
{
    return scaleFactor;
}

void Scale::setDeltaScaleFactor(Ionflux::Mapping::MappingValue 
newDeltaScaleFactor)
{
	deltaScaleFactor = newDeltaScaleFactor;
}

Ionflux::Mapping::MappingValue Scale::getDeltaScaleFactor() const
{
    return deltaScaleFactor;
}

Ionflux::GeoUtils::TransformNodes::Scale& Scale::operator=(const 
Ionflux::GeoUtils::TransformNodes::Scale& other)
{
    TransformNode::operator=(other);
    setIndexFunc(other.indexFunc);
    setDistanceFunc(other.distanceFunc);
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Scale* Scale::copy() const
{
    Scale* newScale = create();
    *newScale = *this;
    return newScale;
}

Ionflux::GeoUtils::TransformNodes::Scale* 
Scale::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Scale*>(other);
}

Ionflux::GeoUtils::TransformNodes::Scale* 
Scale::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Scale* newObject = new Scale();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

void Scale::setParam(Ionflux::ObjectBase::IFParamID paramID, 
Ionflux::Mapping::MappingValue paramValue)
{
    if (paramID == "scaleFactor")
    {
        setScaleFactor(paramValue);
        return;
    }
    if (paramID == "deltaScaleFactor")
    {
        setDeltaScaleFactor(paramValue);
        return;
    }
    throw GeoUtilsError(std::string("Parameter '") 
        + paramID + "' does not exist.");
}

Ionflux::Mapping::MappingValue 
Scale::getParam(Ionflux::ObjectBase::IFParamID paramID)
{
    if (paramID == "scaleFactor")
        return getScaleFactor();
    if (paramID == "deltaScaleFactor")
        return getDeltaScaleFactor();
    throw GeoUtilsError(std::string("Parameter '") 
        + paramID + "' does not exist.");
}

}

}

}

/** \file Scale.cpp
 * \brief Transform node: Scale implementation.
 */
