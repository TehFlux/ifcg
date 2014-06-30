/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Power.cpp                       Power mapping (implementation).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFMapping - Ionflux Mapping Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFMapping - Ionflux Mapping Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "ifmapping/Power.hpp"
#include <cmath>
#include <sstream>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

PowerClassInfo::PowerClassInfo()
{
	name = "Power";
	desc = "Power mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

PowerClassInfo::~PowerClassInfo()
{
}

// run-time type information instance constants
const PowerClassInfo Power::powerClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Power::CLASS_INFO = &Power::powerClassInfo;

Power::Power()
: exponent(1)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Power::Power(const Ionflux::Mapping::Power& other)
: exponent(1)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Power::Power(int initExponent, Ionflux::Mapping::MappingValue initScale, 
Ionflux::Mapping::MappingValue initOffset, Ionflux::Mapping::Mapping* 
initFunc)
: ChainableMapping(initFunc, initScale, initOffset), exponent(initExponent)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Power::~Power()
{
	// TODO: Nothing ATM. ;-)
}

std::string Power::getString() const
{
	ostringstream state;
	state << getClassName() << "[" << exponent << "]";
	return state.str();
}

Ionflux::Mapping::MappingValue 
Power::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	Ionflux::Mapping::MappingValue result = 1.;
	unsigned int e0 = exponent;
	if (e0 < 0)
	    e0 *= -1;
	for (unsigned int i = 0; i < e0; i++)
	    result *= value;
	if (exponent < 0)
	    return 1. / result;
	return result;
}

void Power::setExponent(int newExponent)
{
	exponent = newExponent;
}

int Power::getExponent() const
{
    return exponent;
}

Ionflux::Mapping::Power& Power::operator=(const Ionflux::Mapping::Power& 
other)
{
    ChainableMapping::operator=(other);
    exponent = other.exponent;
	return *this;
}

Ionflux::Mapping::Power* Power::copy() const
{
    Power* newPower = create();
    *newPower = *this;
    return newPower;
}

Ionflux::Mapping::Power* Power::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Power*>(other);
}

Ionflux::Mapping::Power* Power::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Power* newObject = new Power();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Power::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Power.cpp
 * \brief Power mapping implementation.
 */
