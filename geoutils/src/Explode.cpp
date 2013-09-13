/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Explode.cpp                     Transform node: Explode 
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

#include "geoutils/Explode.hpp"
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

ExplodeClassInfo::ExplodeClassInfo()
{
	name = "Explode";
	desc = "Transform node: Explode";
}

ExplodeClassInfo::~ExplodeClassInfo()
{
}

// public member constants
const unsigned int Explode::INPUT_SOURCE = 0;
const unsigned int Explode::OUTPUT_FIRST = 0;
const unsigned int Explode::DEFAULT_ELEMENTS_PER_GROUP = 1;

// run-time type information instance constants
const ExplodeClassInfo Explode::explodeClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Explode::CLASS_INFO = &Explode::explodeClassInfo;

Explode::Explode()
: elementsPerGroup(DEFAULT_ELEMENTS_PER_GROUP)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Explode::Explode(const Ionflux::GeoUtils::TransformNodes::Explode& other)
: elementsPerGroup(DEFAULT_ELEMENTS_PER_GROUP)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Explode::Explode(unsigned int initElementsPerGroup, const 
Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID), elementsPerGroup(initElementsPerGroup)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Explode::~Explode()
{
	// TODO: Nothing ATM. ;-)
}

void Explode::process()
{
	if (inputCache.size() < 1)
	    throw GeoUtilsError("Input cache is empty.");
	clearInputGroups();
	TransformableGroup* g0 = inputCache[0];
	if (elementsPerGroup == 0)
	    throw GeoUtilsError("Elements per group must be positive.");
	TransformableGroup* g1 = new TransformableGroup();
	if (g1 == 0)
	    throw GeoUtilsError("Could not allocate object.");
	g1->copyTransform(*g0);
	unsigned int numSourceItems = g0->getNumItems();
	// Insert elements from the input group to the output groups.
	for (unsigned int j = 0; j < numSourceItems; j++)
	{
	    Ionflux::GeoUtils::TransformableObject* it0 = 
	        g0->getItem(j);
	    g1->addItem(it0);
	    if (g1->getNumItems() == elementsPerGroup)
	    {
	        // Group has the specified number of elements.
	        if (j < (numSourceItems - 1))
	        {
	            // Add the group and create the next one.
	            addOutput(g1);
	            g1 = new TransformableGroup();
	            if (g1 == 0)
	                throw GeoUtilsError("Could not allocate object.");
	            g1->copyTransform(*g0);
	        } else
	        {
	            // This was the last group, add it.
	            addOutput(g1);
	            g1 = 0;
	        }
	    }
	}
	if (g1 != 0)
	    addOutput(g1);
}

std::string Explode::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") << "; " 
	    << elementsPerGroup << "]";
	return status.str();
}

void Explode::setElementsPerGroup(unsigned int newElementsPerGroup)
{
	elementsPerGroup = newElementsPerGroup;
}

unsigned int Explode::getElementsPerGroup() const
{
    return elementsPerGroup;
}

Ionflux::GeoUtils::TransformNodes::Explode& Explode::operator=(const 
Ionflux::GeoUtils::TransformNodes::Explode& other)
{
    TransformNode::operator=(other);
    elementsPerGroup = other.elementsPerGroup;
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Explode* Explode::copy() const
{
    Explode* newExplode = create();
    *newExplode = *this;
    return newExplode;
}

Ionflux::GeoUtils::TransformNodes::Explode* 
Explode::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Explode*>(other);
}

Ionflux::GeoUtils::TransformNodes::Explode* 
Explode::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Explode* newObject = new Explode();
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

/** \file Explode.cpp
 * \brief Transform node: Explode implementation.
 */
