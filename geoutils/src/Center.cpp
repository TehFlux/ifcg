/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Center.cpp                      Transform node: Center (implementation).
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

#include "geoutils/Center.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "ifmapping/utils.hpp"
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;
using Ionflux::Mapping::defaultStr;

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

CenterClassInfo::CenterClassInfo()
{
	name = "Center";
	desc = "Transform node: Center";
}

CenterClassInfo::~CenterClassInfo()
{
}

// public member constants
const unsigned int Center::INPUT_SOURCE = 0;
const unsigned int Center::OUTPUT_TARGET = 0;

// run-time type information instance constants
const CenterClassInfo Center::centerClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Center::CLASS_INFO = &Center::centerClassInfo;

Center::Center()
: origin(GeoUtils::Vector3::ZERO), method(Ionflux::GeoUtils::CENTER_BARYCENTER)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Center::Center(const Ionflux::GeoUtils::TransformNodes::Center& other)
: origin(GeoUtils::Vector3::ZERO), method(Ionflux::GeoUtils::CENTER_BARYCENTER)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Center::Center(Ionflux::GeoUtils::CenteringMethod initMethod, const 
Ionflux::GeoUtils::Vector3& initOrigin, const 
Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID), origin(initOrigin), method(initMethod)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Center::~Center()
{
	// TODO: Nothing ATM. ;-)
}

void Center::process()
{
	if (inputCache.size() < 1)
	    throw GeoUtilsError("Input cache is empty.");
	clearInputGroups();
	TransformableGroup* g0 = inputCache[0];
	/* Since we are going to manipulate the individual elements, 
	   any existing group transformations must be applied first. */
	g0->applyTransform();
	unsigned int numSourceItems = g0->getNumItems();
	/* <---- DEBUG ----- //
	std::ostringstream message;
	message << "numSourceItems = " << numSourceItems;
	log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	// <---- DEBUG ----- */
	/* <---- DEBUG ----- //
	std::ostringstream message;
	message << "Group: barycenter = " << g0->getBarycenter() 
	    << ", bounds.center = " << g0->getBounds().getCenter() 
	    << ", bounds = " << g0->getBounds();
	log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	// <---- DEBUG ----- */
	for (unsigned int i = 0; i < numSourceItems; i++)
	{
	    TransformableObject* o0 = g0->getItem(i);
	    // Center the object.
	    /* <---- DEBUG ----- //
	    message.str("");
	    message << "Item #" << i << ": " << o0->getString();
	    log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	    // <---- DEBUG ----- */
	    o0->center(method, &origin);
	}
	addOutput(g0);
}

std::string Center::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") << "; " 
	    << origin.getString() << ", " 
	    << Ionflux::GeoUtils::centeringMethodToString(method) << "]";
	return status.str();
}

void Center::setOrigin(const Ionflux::GeoUtils::Vector3& newOrigin)
{
	origin = newOrigin;
}

Ionflux::GeoUtils::Vector3 Center::getOrigin() const
{
    return origin;
}

void Center::setMethod(Ionflux::GeoUtils::CenteringMethod newMethod)
{
	method = newMethod;
}

Ionflux::GeoUtils::CenteringMethod Center::getMethod() const
{
    return method;
}

Ionflux::GeoUtils::TransformNodes::Center& Center::operator=(const 
Ionflux::GeoUtils::TransformNodes::Center& other)
{
    TransformNode::operator=(other);
    origin = other.origin;
    method = other.method;
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Center* Center::copy() const
{
    Center* newCenter = create();
    *newCenter = *this;
    return newCenter;
}

Ionflux::GeoUtils::TransformNodes::Center* 
Center::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Center*>(other);
}

Ionflux::GeoUtils::TransformNodes::Center* 
Center::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Center* newObject = new Center();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Center::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file Center.cpp
 * \brief Transform node: Center implementation.
 */
