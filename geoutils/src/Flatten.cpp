/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Flatten.cpp                     Transform node: Flatten 
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

#include "geoutils/Flatten.hpp"
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

FlattenClassInfo::FlattenClassInfo()
{
	name = "Flatten";
	desc = "Transform node: Flatten";
}

FlattenClassInfo::~FlattenClassInfo()
{
}

// public member constants
const unsigned int Flatten::INPUT_SOURCE = 0;
const unsigned int Flatten::OUTPUT_TARGET = 0;

// run-time type information instance constants
const FlattenClassInfo Flatten::flattenClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Flatten::CLASS_INFO = &Flatten::flattenClassInfo;

Flatten::Flatten()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Flatten::Flatten(const Ionflux::GeoUtils::TransformNodes::Flatten& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Flatten::Flatten(const Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Flatten::~Flatten()
{
	// TODO: Nothing ATM. ;-)
}

void Flatten::process()
{
	if (inputCache.size() < 1)
	    throw GeoUtilsError("Input cache is empty.");
	clearInputGroups();
	TransformableGroup* g0 = inputCache[0];
	g0->flatten();
	addOutput(g0);
}

std::string Flatten::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") << "]";
	return status.str();
}

Ionflux::GeoUtils::TransformNodes::Flatten& Flatten::operator=(const 
Ionflux::GeoUtils::TransformNodes::Flatten& other)
{
    TransformNode::operator=(other);
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Flatten* Flatten::copy() const
{
    Flatten* newFlatten = create();
    *newFlatten = *this;
    return newFlatten;
}

Ionflux::GeoUtils::TransformNodes::Flatten* 
Flatten::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Flatten*>(other);
}

Ionflux::GeoUtils::TransformNodes::Flatten* 
Flatten::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Flatten* newObject = new Flatten();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Flatten::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file Flatten.cpp
 * \brief Transform node: Flatten implementation.
 */
