/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Duplicate.cpp                   Transform node: Duplicate 
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

#include "geoutils/Duplicate.hpp"
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

DuplicateClassInfo::DuplicateClassInfo()
{
	name = "Duplicate";
	desc = "Transform node: Duplicate";
}

DuplicateClassInfo::~DuplicateClassInfo()
{
}

// public member constants
const unsigned int Duplicate::INPUT_SOURCE = 0;
const unsigned int Duplicate::OUTPUT_TARGET = 0;
const unsigned int Duplicate::DEFAULT_NUM_DUPLICATES = 10;
const Ionflux::Mapping::Range Duplicate::CLAMP_RANGE = { 0., 1. };

// run-time type information instance constants
const DuplicateClassInfo Duplicate::duplicateClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Duplicate::CLASS_INFO = &Duplicate::duplicateClassInfo;

Duplicate::Duplicate()
: numDuplicates(DEFAULT_NUM_DUPLICATES), func(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Duplicate::Duplicate(const Ionflux::GeoUtils::TransformNodes::Duplicate& other)
: numDuplicates(DEFAULT_NUM_DUPLICATES), func(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Duplicate::Duplicate(unsigned int initNumDuplicates, 
Ionflux::Mapping::Mapping* initFunc, const Ionflux::ObjectBase::IFObjectID&
nodeID)
: TransformNode(nodeID), numDuplicates(initNumDuplicates), func(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setFunc(initFunc);
}

Duplicate::~Duplicate()
{
	// TODO: Nothing ATM. ;-)
}

void Duplicate::process()
{
	if (inputCache.size() < 1)
	    throw GeoUtilsError("Input cache is empty.");
	clearInputGroups();
	TransformableGroup* g0 = inputCache[0];
	TransformableGroup* g1 = new TransformableGroup();
	if (g1 == 0)
	    throw GeoUtilsError("Could not allocate object.");
	// Keep group transformations.
	g1->copyTransform(*g0);
	unsigned int numSourceItems = g0->getNumItems();
	/* <---- DEBUG ----- //
	ostringstream message;
	message << "numSourceItems = " << numSourceItems 
	    << ", numDuplicates = " << numDuplicates;
	log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	// ----- DEBUG ----> */
	for (unsigned int i = 0; i < numDuplicates; i++)
	{
	    // Determine which item to duplicate.
	    unsigned int k = 0;
	    if ((func == 0) 
	        || (numDuplicates == 1))
	        k = i % numSourceItems;
	    else 
	    {
	        Ionflux::Mapping::MappingValue t = i / (numDuplicates - 1);
	        k = static_cast<unsigned int>(Ionflux::Mapping::clamp(
	            (*func)(t), CLAMP_RANGE) * numSourceItems);
	    }
	    // Create the duplicate.
	    TransformableObject* o0 = g0->getItem(k);
	    g1->addItem(&(o0->duplicate()));
	}
	addOutput(g1);
}

std::string Duplicate::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") << "; " 
	    << numDuplicates << ", ";
	if (func != 0)
	    status << func->getString();
	else
	    status << "<none>";
	status << "]";
	return status.str();
}

void Duplicate::setNumDuplicates(unsigned int newNumDuplicates)
{
	numDuplicates = newNumDuplicates;
}

unsigned int Duplicate::getNumDuplicates() const
{
	return numDuplicates;
}

void Duplicate::setNumDuplicatesParam(Ionflux::Mapping::MappingValue 
newNumDuplicatesParam)
{
	setNumDuplicates(
	    static_cast<unsigned int>(newNumDuplicatesParam));
}

Ionflux::Mapping::MappingValue Duplicate::getNumDuplicatesParam() const
{
	return static_cast<double>(getNumDuplicates());
}

void Duplicate::setFunc(Ionflux::Mapping::Mapping* newFunc)
{
	if (func == newFunc)
		return;
    if (newFunc != 0)
        addLocalRef(newFunc);
	if (func != 0)
		removeLocalRef(func);
	func = newFunc;
}

Ionflux::Mapping::Mapping* Duplicate::getFunc() const
{
	return func;
}

Ionflux::GeoUtils::TransformNodes::Duplicate& Duplicate::operator=(const 
Ionflux::GeoUtils::TransformNodes::Duplicate& other)
{
    TransformNode::operator=(other);
    numDuplicates = other.numDuplicates;
    setFunc(other.func);
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Duplicate* Duplicate::copy() const
{
    Duplicate* newDuplicate = create();
    *newDuplicate = *this;
    return newDuplicate;
}

Ionflux::GeoUtils::TransformNodes::Duplicate* 
Duplicate::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Duplicate*>(other);
}

Ionflux::GeoUtils::TransformNodes::Duplicate* 
Duplicate::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Duplicate* newObject = new Duplicate();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

void Duplicate::setParam(Ionflux::ObjectBase::IFParamID paramID, 
Ionflux::Mapping::MappingValue paramValue)
{
    if (paramID == "numDuplicatesParam")
    {
        setNumDuplicatesParam(paramValue);
        return;
    }
    throw GeoUtilsError(std::string("Parameter '") 
        + paramID + "' does not exist.");
}

Ionflux::Mapping::MappingValue 
Duplicate::getParam(Ionflux::ObjectBase::IFParamID paramID)
{
    if (paramID == "numDuplicatesParam")
        return getNumDuplicatesParam();
    throw GeoUtilsError(std::string("Parameter '") 
        + paramID + "' does not exist.");
}

}

}

}

/** \file Duplicate.cpp
 * \brief Transform node: Duplicate implementation.
 */
