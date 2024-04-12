/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Wrap.cpp                        Transform node: Wrap (implementation).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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

#include "geoutils/Wrap.hpp"
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

WrapClassInfo::WrapClassInfo()
{
	name = "Wrap";
	desc = "Transform node: Wrap";
}

WrapClassInfo::~WrapClassInfo()
{
}

// public member constants
const unsigned int Wrap::INPUT_FIRST = 0;
const unsigned int Wrap::OUTPUT_TARGET = 0;

// run-time type information instance constants
const WrapClassInfo Wrap::wrapClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Wrap::CLASS_INFO = &Wrap::wrapClassInfo;

Wrap::Wrap()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Wrap::Wrap(const Ionflux::GeoUtils::TransformNodes::Wrap& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Wrap::Wrap(const Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Wrap::~Wrap()
{
	// TODO: Nothing ATM. ;-)
}

void Wrap::process()
{
	clearInputGroups();
	TransformableGroup* g0 = new TransformableGroup();
	if (g0 == 0)
	    throw GeoUtilsError("Could not allocate object.");
	// Wrap input groups into output group.
	for (Ionflux::GeoUtils::TransformableGroupVector::iterator i = 
	    inputCache.begin(); i != inputCache.end(); i++)
	    g0->addItem(*i);
	addOutput(g0);
}

std::string Wrap::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") << "]";
	return status.str();
}

Ionflux::GeoUtils::TransformNodes::Wrap& Wrap::operator=(const 
Ionflux::GeoUtils::TransformNodes::Wrap& other)
{
    TransformNode::operator=(other);
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Wrap* Wrap::copy() const
{
    Wrap* newWrap = create();
    *newWrap = *this;
    return newWrap;
}

Ionflux::GeoUtils::TransformNodes::Wrap* 
Wrap::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Wrap*>(other);
}

Ionflux::GeoUtils::TransformNodes::Wrap* 
Wrap::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Wrap* newObject = new Wrap();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Wrap::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file Wrap.cpp
 * \brief Transform node: Wrap implementation.
 */
