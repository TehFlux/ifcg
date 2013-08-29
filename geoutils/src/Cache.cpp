/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Cache.cpp                       Transform node: Cache (implementation).
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

#include "geoutils/Cache.hpp"
#include "ifobject/IFLogMessage.hpp"
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

CacheClassInfo::CacheClassInfo()
{
	name = "Cache";
	desc = "Transform node: Cache";
}

CacheClassInfo::~CacheClassInfo()
{
}

// public member constants
const unsigned int Cache::INPUT_SOURCE = 0;
const unsigned int Cache::OUTPUT_TARGET = 0;

// run-time type information instance constants
const CacheClassInfo Cache::cacheClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Cache::CLASS_INFO = &Cache::cacheClassInfo;

Cache::Cache()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Cache::Cache(const Ionflux::GeoUtils::TransformNodes::Cache& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Cache::Cache(const Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Cache::~Cache()
{
	// TODO: Nothing ATM. ;-)
}

void Cache::process()
{
	if (inputCache.size() < 1)
	    throw GeoUtilsError("Input cache is empty.");
	clearInputGroups();
	TransformableGroup* g0 = inputCache[0];
	addOutput(&(g0->duplicate()));
}

std::string Cache::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") << "]";
	return status.str();
}

void Cache::cleanup()
{
	// TODO: Implementation.
}

void Cache::update()
{
	if (loopCounter >= loopMax)
	    throw GeoUtilsError("Maximum number of loop iterations exceeded.");
	loopCounter++;
	if (inputCache.size() == 0)
	{
	    /* Do not update the source node unless the input cache has been 
	       cleared. */
	    updateInputs();
	    clearInputGroups();
	}
	/* <---- DEBUG ----- //
	Ionflux::GeoUtils::Clock c0;
	c0.start();
	// ----- DEBUG ----> */
	process();
	/* <---- DEBUG ----- //
	c0.stop();
	std::ostringstream message;
	message << "processing time: " << c0.getElapsedTime() << " secs";
	log(IFLogMessage(message.str(), VL_DEBUG, this, "update"));
	// ----- DEBUG ----> */
	cleanup();
	updateCounter++;
	loopCounter = 0;
	if (debugMode)
	    log(IFLogMessage(getDebugInfo(debugExpand), VL_DEBUG, 
	        this, "update"));
}

Ionflux::GeoUtils::TransformNodes::Cache& Cache::operator=(const 
Ionflux::GeoUtils::TransformNodes::Cache& other)
{
    TransformNode::operator=(other);
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Cache* Cache::copy() const
{
    Cache* newCache = create();
    *newCache = *this;
    return newCache;
}

Ionflux::GeoUtils::TransformNodes::Cache* 
Cache::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Cache*>(other);
}

Ionflux::GeoUtils::TransformNodes::Cache* 
Cache::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Cache* newObject = new Cache();
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

/** \file Cache.cpp
 * \brief Transform node: Cache implementation.
 */
