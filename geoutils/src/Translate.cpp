/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Translate.cpp                   Transform node: Translate 
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

#include "geoutils/Translate.hpp"
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

TranslateClassInfo::TranslateClassInfo()
{
	name = "Translate";
	desc = "Transform node: Translate";
}

TranslateClassInfo::~TranslateClassInfo()
{
}

// public member constants
const unsigned int Translate::INPUT_SOURCE = 0;
const unsigned int Translate::OUTPUT_TARGET = 0;

// run-time type information instance constants
const TranslateClassInfo Translate::translateClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Translate::CLASS_INFO = &Translate::translateClassInfo;

Translate::Translate()
: offset(GeoUtils::Vector3::ZERO), indexFunc(0), distanceFunc(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Translate::Translate(const Ionflux::GeoUtils::TransformNodes::Translate& other)
: offset(GeoUtils::Vector3::ZERO), indexFunc(0), distanceFunc(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Translate::Translate(const Ionflux::GeoUtils::Vector3& initOffset, 
Ionflux::GeoUtils::Mapping::Vector3Mapping* initIndexFunc, 
Ionflux::GeoUtils::Mapping::Vector3Mapping* initDistanceFunc, const 
Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID), offset(initOffset), indexFunc(0), distanceFunc(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setIndexFunc(initIndexFunc);
	setDistanceFunc(initDistanceFunc);
}

Translate::~Translate()
{
	// TODO: Nothing ATM. ;-)
}

void Translate::process()
{
	if (inputCache.size() < 1)
	    throw GeoUtilsError("Input cache is empty.");
	clearInputGroups();
	TransformableGroup* g0 = inputCache[0];
	if ((indexFunc == 0) 
	    && (distanceFunc == 0))
	    // All elements are translated uniformly by the offset vector.
	    g0->translate(offset);
	else
	{
	    /* Since we are going to manipulate the individual elements, 
	       any existing group transformations must be applied first. */
	    g0->applyTransform();
	    // Translate elements individually according to the mappings.
	    unsigned int numSourceItems = g0->getNumItems();
	    for (unsigned int i = 0; i < numSourceItems; i++)
	    {
	        TransformableObject* o0 = g0->getItem(i);
	        // Calculate the total translation for the element.
	        Vector3 v0(offset);
	        if (indexFunc != 0)
	            // Add translation according to index mapping.
	            /* NOTE: Not applying index range at this time since it 
	                     does not really work as expected. */
	            v0 = v0 + (*indexFunc)(static_cast<double>(i) 
	                / (numSourceItems - 1));
	        if (distanceFunc != 0)
	        {
	            // Add translation according to distance mapping.
	            /* NOTE: Not applying distance range at this time since it 
	                     does not really work as expected. */
	            double r0 = o0->getBarycenter().norm();
	            v0 = v0 + (*distanceFunc)(r0);
	        }
	        // Translate the object.
	        o0->translate(v0);
	    }
	}
	addOutput(g0);
}

std::string Translate::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") 
	    << "; " << offset;
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

void Translate::setOffset(const Ionflux::GeoUtils::Vector3& newOffset)
{
	offset = newOffset;
}

Ionflux::GeoUtils::Vector3 Translate::getOffset() const
{
	return offset;
}

void Translate::setIndexFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
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

Ionflux::GeoUtils::Mapping::Vector3Mapping* Translate::getIndexFunc() const
{
	return indexFunc;
}

void Translate::setDistanceFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping*
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

Ionflux::GeoUtils::Mapping::Vector3Mapping* Translate::getDistanceFunc() 
const
{
	return distanceFunc;
}

Ionflux::GeoUtils::TransformNodes::Translate& Translate::operator=(const 
Ionflux::GeoUtils::TransformNodes::Translate& other)
{
    TransformNode::operator=(other);
    setIndexFunc(other.indexFunc);
    setDistanceFunc(other.distanceFunc);
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Translate* Translate::copy() const
{
    Translate* newTranslate = create();
    *newTranslate = *this;
    return newTranslate;
}

Ionflux::GeoUtils::TransformNodes::Translate* 
Translate::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Translate*>(other);
}

Ionflux::GeoUtils::TransformNodes::Translate* 
Translate::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Translate* newObject = new Translate();
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

/** \file Translate.cpp
 * \brief Transform node: Translate implementation.
 */
