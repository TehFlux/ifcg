/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Clone.cpp                       Transform node: Clone (implementation).
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

#include "geoutils/Clone.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

CloneClassInfo::CloneClassInfo()
{
	name = "Clone";
	desc = "Transform node: Clone";
}

CloneClassInfo::~CloneClassInfo()
{
}

// public member constants
const unsigned int Clone::INPUT_SOURCE = 0;
const unsigned int Clone::OUTPUT_FIRST = 0;
const unsigned int Clone::DEFAULT_NUM_CLONES = 2;

// run-time type information instance constants
const CloneClassInfo Clone::cloneClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Clone::CLASS_INFO = &Clone::cloneClassInfo;

Clone::Clone()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Clone::Clone(const Ionflux::GeoUtils::TransformNodes::Clone& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Clone::Clone(unsigned int initNumClones, const 
Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID), numClones(initNumClones)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Clone::~Clone()
{
	// TODO: Nothing ATM. ;-)
}

void Clone::process()
{
	if (inputCache.size() < 1)
	    throw GeoUtilsError("Input cache is empty.");
	clearInputGroups();
	TransformableGroup* g0 = inputCache[0];
	// Clone the input group.
	for (unsigned int j = 0; j < numClones; j++)
	    addOutput(&(g0->duplicate()));
	/* <---- DEBUG ----- //
	ostringstream message;
	message << "updateCounter = " << updateCounter << ", added " 
	    << outputs.size() << " output groups.";
	log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	// <---- DEBUG ----- */
}

std::string Clone::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << id << "; " 
	    << numClones << "]";
	return status.str();
}

void Clone::setNumClones(unsigned int newNumClones)
{
	numClones = newNumClones;
}

unsigned int Clone::getNumClones() const
{
    return numClones;
}

Ionflux::GeoUtils::TransformNodes::Clone& Clone::operator=(const 
Ionflux::GeoUtils::TransformNodes::Clone& other)
{
    TransformNode::operator=(other);
    numClones = other.numClones;
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Clone* Clone::copy() const
{
    Clone* newClone = create();
    *newClone = *this;
    return newClone;
}

Ionflux::GeoUtils::TransformNodes::Clone* 
Clone::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Clone*>(other);
}

Ionflux::GeoUtils::TransformNodes::Clone* 
Clone::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Clone* newObject = new Clone();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

}

/** \file Clone.cpp
 * \brief Transform node: Clone implementation.
 */
