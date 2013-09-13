/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Source.cpp                      Transform node: Source (implementation).
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

#include "geoutils/Source.hpp"
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

SourceClassInfo::SourceClassInfo()
{
	name = "Source";
	desc = "Transform node: Source";
}

SourceClassInfo::~SourceClassInfo()
{
}

// public member constants
const unsigned int Source::OUTPUT_TARGET = 0;

// run-time type information instance constants
const SourceClassInfo Source::sourceClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Source::CLASS_INFO = &Source::sourceClassInfo;

Source::Source()
: source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Source::Source(const Ionflux::GeoUtils::TransformNodes::Source& other)
: source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Source::Source(Ionflux::GeoUtils::TransformableGroup* initSource, const 
Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID), source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setSource(initSource);
}

Source::~Source()
{
	// TODO: Nothing ATM. ;-)
}

void Source::process()
{
	if (source == 0)
	    return;
	addOutput(&(source->duplicate()));
}

std::string Source::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") << "; ";
	if (source != 0)
	    status << source->getString();
	else
	    status << "<none>";
	status << "]";
	return status.str();
}

void Source::setSource(Ionflux::GeoUtils::TransformableGroup* newSource)
{
	if (source == newSource)
		return;
    if (newSource != 0)
        addLocalRef(newSource);
	if (source != 0)
		removeLocalRef(source);
	source = newSource;
}

Ionflux::GeoUtils::TransformableGroup* Source::getSource() const
{
    return source;
}

Ionflux::GeoUtils::TransformNodes::Source& Source::operator=(const 
Ionflux::GeoUtils::TransformNodes::Source& other)
{
    TransformNode::operator=(other);
    setSource(other.source);
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Source* Source::copy() const
{
    Source* newSource = create();
    *newSource = *this;
    return newSource;
}

Ionflux::GeoUtils::TransformNodes::Source* 
Source::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Source*>(other);
}

Ionflux::GeoUtils::TransformNodes::Source* 
Source::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Source* newObject = new Source();
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

/** \file Source.cpp
 * \brief Transform node: Source implementation.
 */
