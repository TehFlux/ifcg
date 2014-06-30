/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Merge.cpp                       Transform node: Merge (implementation).
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

#include "geoutils/Merge.hpp"
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

MergeClassInfo::MergeClassInfo()
{
	name = "Merge";
	desc = "Transform node: Merge";
}

MergeClassInfo::~MergeClassInfo()
{
}

// public member constants
const unsigned int Merge::INPUT_FIRST = 0;
const unsigned int Merge::OUTPUT_TARGET = 0;

// run-time type information instance constants
const MergeClassInfo Merge::mergeClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Merge::CLASS_INFO = &Merge::mergeClassInfo;

Merge::Merge()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Merge::Merge(const Ionflux::GeoUtils::TransformNodes::Merge& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Merge::Merge(const Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Merge::~Merge()
{
	// TODO: Nothing ATM. ;-)
}

void Merge::process()
{
	clearInputGroups();
	TransformableGroup* g0 = new TransformableGroup();
	if (g0 == 0)
	    throw GeoUtilsError("Could not allocate object.");
	// Merge elements from input groups.
	/* <---- DEBUG ----- //
	std::ostringstream message;
	message << "Number of input groups: " << inputs.size();
	log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	// ----- DEBUG ----> */
	for (Ionflux::GeoUtils::TransformableGroupVector::iterator i = 
	    inputCache.begin(); i != inputCache.end(); i++)
	{
	    TransformableGroup* o0 = *i;
	    /* Since we are going to extract the elements from the input 
	       groups, the group transformations need to be applied 
	       first. */
	    o0->applyTransform();
	    /* <---- DEBUG ----- //
	    message.str("");
	    message << "Number of elements in group: " << o0->getNumItems();
	    log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	    // ----- DEBUG ----> */
	    for (unsigned int j = 0; j < o0->getNumItems(); j++)
	        g0->addItem(o0->getItem(j));
	}
	addOutput(g0);
}

std::string Merge::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") << "]";
	return status.str();
}

Ionflux::GeoUtils::TransformNodes::Merge& Merge::operator=(const 
Ionflux::GeoUtils::TransformNodes::Merge& other)
{
    TransformNode::operator=(other);
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Merge* Merge::copy() const
{
    Merge* newMerge = create();
    *newMerge = *this;
    return newMerge;
}

Ionflux::GeoUtils::TransformNodes::Merge* 
Merge::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Merge*>(other);
}

Ionflux::GeoUtils::TransformNodes::Merge* 
Merge::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Merge* newObject = new Merge();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Merge::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file Merge.cpp
 * \brief Transform node: Merge implementation.
 */
