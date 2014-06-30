/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Rotate.cpp                      Transform node: Rotate (implementation).
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

#include "geoutils/Rotate.hpp"
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

RotateClassInfo::RotateClassInfo()
{
	name = "Rotate";
	desc = "Transform node: Rotate";
}

RotateClassInfo::~RotateClassInfo()
{
}

// public member constants
const unsigned int Rotate::INPUT_SOURCE = 0;
const unsigned int Rotate::OUTPUT_TARGET = 0;
const Ionflux::GeoUtils::Range Rotate::DEFAULT_ANGLE_RANGE = Ionflux::GeoUtils::Range(0., 2 * M_PI);

// run-time type information instance constants
const RotateClassInfo Rotate::rotateClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Rotate::CLASS_INFO = &Rotate::rotateClassInfo;

Rotate::Rotate()
: axis(Ionflux::GeoUtils::AXIS_Z), angle(0.), deltaAngle(0.), indexFunc(0), distanceFunc(0), indexRange(DEFAULT_ANGLE_RANGE), distanceRange(DEFAULT_ANGLE_RANGE), centeringMethod(CENTER_ORIGIN)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Rotate::Rotate(const Ionflux::GeoUtils::TransformNodes::Rotate& other)
: axis(Ionflux::GeoUtils::AXIS_Z), angle(0.), deltaAngle(0.), indexFunc(0), distanceFunc(0), indexRange(DEFAULT_ANGLE_RANGE), distanceRange(DEFAULT_ANGLE_RANGE), centeringMethod(CENTER_ORIGIN)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Rotate::Rotate(Ionflux::GeoUtils::AxisID initAxis, double initAngle, double
deltaAngle, Ionflux::Mapping::Mapping* initIndexFunc, 
Ionflux::Mapping::Mapping* initDistanceFunc, Ionflux::GeoUtils::Range 
initIndexRange, Ionflux::GeoUtils::Range initDistanceRange, 
Ionflux::GeoUtils::CenteringMethod initCenteringMethod, const 
Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID), axis(initAxis), angle(initAngle), 
deltaAngle(deltaAngle), indexFunc(0), distanceFunc(0), 
indexRange(initIndexRange), distanceRange(initDistanceRange), 
centeringMethod(initCenteringMethod)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setIndexFunc(initIndexFunc);
	setDistanceFunc(initDistanceFunc);
}

Rotate::~Rotate()
{
	// TODO: Nothing ATM. ;-)
}

void Rotate::process()
{
	if (inputCache.size() < 1)
	    throw GeoUtilsError("Input cache is empty.");
	clearInputGroups();
	TransformableGroup* g0 = inputCache[0];
	if ((centeringMethod == CENTER_ORIGIN) 
	    && (indexFunc == 0) 
	    && (distanceFunc == 0))
	    // All elements are rotated uniformly.
	    g0->rotate(angle + updateCounter * deltaAngle, axis);
	else
	{
	    /* Since we are going to manipulate the individual elements, 
	       any existing group transformations must be applied first. */
	    g0->applyTransform();
	    Vector3 c0;
	    // Rotate elements individually according to the mappings.
	    unsigned int numSourceItems = g0->getNumItems();
	    for (unsigned int i = 0; i < numSourceItems; i++)
	    {
	        TransformableObject* o0 = g0->getItem(i);
	        // Calculate the total angle for the element.
	        double phi = angle + updateCounter * deltaAngle;
	        if (indexFunc != 0)
	            // Add angle according to index mapping.
	            phi += indexRange.getClampedValue(
	                (*indexFunc)(static_cast<double>(i) 
	                    / (numSourceItems - 1)));
	        if (distanceFunc != 0)
	        {
	            // Add angle according to distance mapping.
	            double r0 = o0->getBarycenter().norm();
	            phi += distanceRange.getClampedValue((*distanceFunc)(r0));
	        }
	        // Determine the center vector.
	        if (centeringMethod == CENTER_BOUNDS)
	            c0 = o0->getBounds().getCenter();
	        else
	        if (centeringMethod == CENTER_BARYCENTER)
	            c0 = o0->getBarycenter();
	        else
	            c0 = Vector3::ZERO;
	        // Rotate the object around the center.
	        /* <---- DEBUG ----- //
	        std::ostringstream message;
	        message << "phi[" << i << "] = " << phi;
	        log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	        // <---- DEBUG ----- */
	        o0->translate(c0.flip());
	        o0->rotate(phi, axis);
	        o0->translate(c0);
	    }
	}
	/* <---- DEBUG ----- //
	c0.stop();
	transformTime = c0.getElapsedTime();
	std::ostringstream message;
	message << "duplicateTime = " << duplicateTime 
	    << " secs, transformTime = " << transformTime 
	    << " secs";
	log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	// ----- DEBUG ----> */
	addOutput(g0);
}

std::string Rotate::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") << "; " 
	    << Ionflux::GeoUtils::axisToString(axis) << ", " << angle;
	if (indexFunc != 0)
	    status << ", " << indexFunc->getString();
	else
	    status << ", <none>";
	if (distanceFunc != 0)
	    status << ", " << distanceFunc->getString();
	else
	    status << ", <none>";
	status << "]";
	return status.str();
}

void Rotate::setAxis(Ionflux::GeoUtils::AxisID newAxis)
{
	axis = newAxis;
}

Ionflux::GeoUtils::AxisID Rotate::getAxis() const
{
    return axis;
}

void Rotate::setAngle(Ionflux::Mapping::MappingValue newAngle)
{
	angle = newAngle;
}

Ionflux::Mapping::MappingValue Rotate::getAngle() const
{
    return angle;
}

void Rotate::setDeltaAngle(Ionflux::Mapping::MappingValue newDeltaAngle)
{
	deltaAngle = newDeltaAngle;
}

Ionflux::Mapping::MappingValue Rotate::getDeltaAngle() const
{
    return deltaAngle;
}

void Rotate::setIndexFunc(Ionflux::Mapping::Mapping* newIndexFunc)
{
	if (indexFunc == newIndexFunc)
		return;
    if (newIndexFunc != 0)
        addLocalRef(newIndexFunc);
	if (indexFunc != 0)
		removeLocalRef(indexFunc);
	indexFunc = newIndexFunc;
}

Ionflux::Mapping::Mapping* Rotate::getIndexFunc() const
{
    return indexFunc;
}

void Rotate::setDistanceFunc(Ionflux::Mapping::Mapping* newDistanceFunc)
{
	if (distanceFunc == newDistanceFunc)
		return;
    if (newDistanceFunc != 0)
        addLocalRef(newDistanceFunc);
	if (distanceFunc != 0)
		removeLocalRef(distanceFunc);
	distanceFunc = newDistanceFunc;
}

Ionflux::Mapping::Mapping* Rotate::getDistanceFunc() const
{
    return distanceFunc;
}

void Rotate::setIndexRange(const Ionflux::GeoUtils::Range& newIndexRange)
{
	indexRange = newIndexRange;
}

Ionflux::GeoUtils::Range Rotate::getIndexRange() const
{
    return indexRange;
}

void Rotate::setDistanceRange(const Ionflux::GeoUtils::Range& 
newDistanceRange)
{
	distanceRange = newDistanceRange;
}

Ionflux::GeoUtils::Range Rotate::getDistanceRange() const
{
    return distanceRange;
}

void Rotate::setCenteringMethod(Ionflux::GeoUtils::CenteringMethod 
newCenteringMethod)
{
	centeringMethod = newCenteringMethod;
}

Ionflux::GeoUtils::CenteringMethod Rotate::getCenteringMethod() const
{
    return centeringMethod;
}

Ionflux::GeoUtils::TransformNodes::Rotate& Rotate::operator=(const 
Ionflux::GeoUtils::TransformNodes::Rotate& other)
{
    TransformNode::operator=(other);
    axis = other.axis;
    angle = other.angle;
    setIndexFunc(other.indexFunc);
    setDistanceFunc(other.distanceFunc);
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Rotate* Rotate::copy() const
{
    Rotate* newRotate = create();
    *newRotate = *this;
    return newRotate;
}

Ionflux::GeoUtils::TransformNodes::Rotate* 
Rotate::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Rotate*>(other);
}

Ionflux::GeoUtils::TransformNodes::Rotate* 
Rotate::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Rotate* newObject = new Rotate();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Rotate::getMemSize() const
{
    return sizeof *this;
}

void Rotate::setParam(Ionflux::ObjectBase::IFParamID paramID, 
Ionflux::Mapping::MappingValue paramValue)
{
    if (paramID == "angle")
    {
        setAngle(paramValue);
        return;
    }
    if (paramID == "deltaAngle")
    {
        setDeltaAngle(paramValue);
        return;
    }
    throw GeoUtilsError(std::string("Parameter '") 
        + paramID + "' does not exist.");
}

Ionflux::Mapping::MappingValue 
Rotate::getParam(Ionflux::ObjectBase::IFParamID paramID)
{
    if (paramID == "angle")
        return getAngle();
    if (paramID == "deltaAngle")
        return getDeltaAngle();
    throw GeoUtilsError(std::string("Parameter '") 
        + paramID + "' does not exist.");
}

}

}

}

/** \file Rotate.cpp
 * \brief Transform node: Rotate implementation.
 */
