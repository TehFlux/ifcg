/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ParamControl.cpp                Parameter control (implementation).
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

#include "geoutils/ParamControl.hpp"
#include <sstream>
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

ParamControlClassInfo::ParamControlClassInfo()
{
	name = "ParamControl";
	desc = "Parameter control";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

ParamControlClassInfo::~ParamControlClassInfo()
{
}

// run-time type information instance constants
const ParamControlClassInfo ParamControl::paramControlClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ParamControl::CLASS_INFO = &ParamControl::paramControlClassInfo;

ParamControl::ParamControl()
: node(0), paramID(""), func(0), coord(COORDINATE_NOT_SET)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ParamControl::ParamControl(const Ionflux::GeoUtils::TransformNodes::ParamControl& other)
: node(0), paramID(""), func(0), coord(COORDINATE_NOT_SET)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ParamControl::ParamControl(Ionflux::GeoUtils::TransformNodes::TransformNode*
initNode, Ionflux::ObjectBase::IFParamID initParamID, 
Ionflux::Mapping::Mapping* initFunc, unsigned int initCoord)
: node(initNode), paramID(initParamID), func(0), coord(initCoord)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setFunc(initFunc);
}

ParamControl::~ParamControl()
{
	// TODO: Nothing ATM. ;-)
}

void ParamControl::call(Ionflux::Mapping::MappingValue value) const
{
	if (func == 0)
	    throw GeoUtilsError("Mapping not set.");
	if (node == 0)
	    throw GeoUtilsError("Node not set.");
	Ionflux::Mapping::MappingValue v0 = (*func)(value);
	node->setParam(paramID, v0);
}

void ParamControl::operator()(Ionflux::Mapping::MappingValue value) const
{
	call(value);
}

std::string ParamControl::getString() const
{
	ostringstream status;
	status << getClassName() << "[";
	if (node != 0)
	    status << (*node);
	else
	    status << "<none>";
	if (func != 0)
	    status << ", " << (*func);
	else
	    status << ", <none>";
	status << ", " << defaultStr(paramID, "<none>") << "]";
	return status.str();
}

void 
ParamControl::setNode(Ionflux::GeoUtils::TransformNodes::TransformNode* 
newNode)
{
	node = newNode;
}

Ionflux::GeoUtils::TransformNodes::TransformNode* ParamControl::getNode() 
const
{
    return node;
}

void ParamControl::setParamID(const Ionflux::ObjectBase::IFParamID& 
newParamID)
{
	paramID = newParamID;
}

Ionflux::ObjectBase::IFParamID ParamControl::getParamID() const
{
    return paramID;
}

void ParamControl::setFunc(Ionflux::Mapping::Mapping* newFunc)
{
	if (func == newFunc)
		return;
    if (newFunc != 0)
        addLocalRef(newFunc);
	if (func != 0)
		removeLocalRef(func);
	func = newFunc;
}

Ionflux::Mapping::Mapping* ParamControl::getFunc() const
{
    return func;
}

void ParamControl::setCoord(unsigned int newCoord)
{
	coord = newCoord;
}

unsigned int ParamControl::getCoord() const
{
    return coord;
}

Ionflux::GeoUtils::TransformNodes::ParamControl& 
ParamControl::operator=(const 
Ionflux::GeoUtils::TransformNodes::ParamControl& other)
{
    node = other.node;
    setFunc(other.func);
    paramID = other.paramID;
	return *this;
}

Ionflux::GeoUtils::TransformNodes::ParamControl* ParamControl::copy() const
{
    ParamControl* newParamControl = create();
    *newParamControl = *this;
    return newParamControl;
}

Ionflux::GeoUtils::TransformNodes::ParamControl* 
ParamControl::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<ParamControl*>(other);
}

Ionflux::GeoUtils::TransformNodes::ParamControl* 
ParamControl::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    ParamControl* newObject = new ParamControl();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int ParamControl::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file ParamControl.cpp
 * \brief Parameter control implementation.
 */
