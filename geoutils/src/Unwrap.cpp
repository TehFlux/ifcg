/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Unwrap.cpp                      Transform node: Unwrap (implementation).
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

#include "geoutils/Unwrap.hpp"
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

UnwrapClassInfo::UnwrapClassInfo()
{
	name = "Unwrap";
	desc = "Transform node: Unwrap";
}

UnwrapClassInfo::~UnwrapClassInfo()
{
}

// public member constants
const unsigned int Unwrap::INPUT_SOURCE = 0;
const unsigned int Unwrap::OUTPUT_FIRST = 0;

// run-time type information instance constants
const UnwrapClassInfo Unwrap::unwrapClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Unwrap::CLASS_INFO = &Unwrap::unwrapClassInfo;

Unwrap::Unwrap()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Unwrap::Unwrap(const Ionflux::GeoUtils::TransformNodes::Unwrap& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Unwrap::Unwrap(const Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Unwrap::~Unwrap()
{
	// TODO: Nothing ATM. ;-)
}

void Unwrap::process()
{
	if (inputCache.size() < 1)
	    throw GeoUtilsError("Input cache is empty.");
	clearInputGroups();
	TransformableGroup* g0 = inputCache[0];
	// Create a group to collect elements which are not groups.
	TransformableGroup* g1 = new TransformableGroup();
	if (g1 == 0)
	    throw GeoUtilsError("Could not allocate object.");
	g1->copyTransform(*g0);
	unsigned int numSourceItems = g0->getNumItems();
	// Process elements from the input group.
	for (unsigned int j = 0; j < numSourceItems; j++)
	{
	    Ionflux::GeoUtils::TransformableObject* it0 = 
	        g0->getItem(j);
	    Ionflux::GeoUtils::TransformableGroup* g2 = 
	        Ionflux::GeoUtils::TransformableGroup::upcast(it0);
	    if (g2 != 0)
	    {
	        // Element is a group. Add it as an output group.
	        addOutput(g2);
	    } else
	    {
	        // Element is not a group. Add it to the collection.
	        g1->addItem(it0);
	    }
	}
	if (g1->getNumItems() > 0)
	    addOutput(g1);
	else
	    // No non-group elements, discard the collection.
	    delete g1;
}

std::string Unwrap::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") << "]";
	return status.str();
}

Ionflux::GeoUtils::TransformNodes::Unwrap& Unwrap::operator=(const 
Ionflux::GeoUtils::TransformNodes::Unwrap& other)
{
    TransformNode::operator=(other);
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Unwrap* Unwrap::copy() const
{
    Unwrap* newUnwrap = create();
    *newUnwrap = *this;
    return newUnwrap;
}

Ionflux::GeoUtils::TransformNodes::Unwrap* 
Unwrap::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Unwrap*>(other);
}

Ionflux::GeoUtils::TransformNodes::Unwrap* 
Unwrap::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Unwrap* newObject = new Unwrap();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Unwrap::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file Unwrap.cpp
 * \brief Transform node: Unwrap implementation.
 */
