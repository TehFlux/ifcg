/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Normalize.cpp                   Transform node: Normalize 
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

#include "geoutils/Normalize.hpp"
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

NormalizeClassInfo::NormalizeClassInfo()
{
	name = "Normalize";
	desc = "Transform node: Normalize";
}

NormalizeClassInfo::~NormalizeClassInfo()
{
}

// public member constants
const unsigned int Normalize::INPUT_SOURCE = 0;
const unsigned int Normalize::OUTPUT_TARGET = 0;

// run-time type information instance constants
const NormalizeClassInfo Normalize::normalizeClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Normalize::CLASS_INFO = &Normalize::normalizeClassInfo;

Normalize::Normalize()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Normalize::Normalize(const Ionflux::GeoUtils::TransformNodes::Normalize& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Normalize::Normalize(const Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Normalize::~Normalize()
{
	// TODO: Nothing ATM. ;-)
}

void Normalize::process()
{
	if (inputCache.size() < 1)
	    throw GeoUtilsError("Input cache is empty.");
	clearInputGroups();
	TransformableGroup* g0 = inputCache[0];
	/* Since we are going to manipulate the individual elements, 
	   any existing group transformations must be applied first. */
	g0->applyTransform();
	unsigned int numSourceItems = g0->getNumItems();
	for (unsigned int i = 0; i < numSourceItems; i++)
	{
	    TransformableObject* o0 = g0->getItem(i);
	    // Normalize the object.
	    o0->normalize();
	}
	addOutput(g0);
}

std::string Normalize::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") << "]";
	return status.str();
}

Ionflux::GeoUtils::TransformNodes::Normalize& Normalize::operator=(const 
Ionflux::GeoUtils::TransformNodes::Normalize& other)
{
    TransformNode::operator=(other);
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Normalize* Normalize::copy() const
{
    Normalize* newNormalize = create();
    *newNormalize = *this;
    return newNormalize;
}

Ionflux::GeoUtils::TransformNodes::Normalize* 
Normalize::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Normalize*>(other);
}

Ionflux::GeoUtils::TransformNodes::Normalize* 
Normalize::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Normalize* newObject = new Normalize();
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

/** \file Normalize.cpp
 * \brief Transform node: Normalize implementation.
 */
