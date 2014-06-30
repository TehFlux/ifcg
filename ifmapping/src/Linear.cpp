/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Linear.cpp                      Linear mapping (implementation).
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

#include "ifmapping/Linear.hpp"
#include <sstream>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

LinearClassInfo::LinearClassInfo()
{
	name = "Linear";
	desc = "Linear mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

LinearClassInfo::~LinearClassInfo()
{
}

// run-time type information instance constants
const LinearClassInfo Linear::linearClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Linear::CLASS_INFO = &Linear::linearClassInfo;

Linear::Linear()
: lower(0.), upper(1.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Linear::Linear(const Ionflux::Mapping::Linear& other)
: lower(0.), upper(1.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Linear::Linear(Ionflux::Mapping::MappingValue initLower, 
Ionflux::Mapping::MappingValue initUpper, Ionflux::Mapping::MappingValue 
initScale, Ionflux::Mapping::MappingValue initOffset, 
Ionflux::Mapping::Mapping* initFunc)
: ChainableMapping(initFunc, initScale, initOffset), lower(initLower), 
upper(initUpper)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Linear::~Linear()
{
	// TODO: Nothing ATM. ;-)
}

std::string Linear::getString() const
{
	ostringstream status;
	status << getClassName() << "[";
	if (func != 0)
	    status << func->getString();
	else
	    status << "<none>";
	status << "; " << scale << ", " << offset << "; " 
	    << lower << ", " << upper << "]";
	return status.str();
}

Ionflux::Mapping::MappingValue 
Linear::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	// TODO: Implementation.
	return value * (upper - lower) + lower;
}

Ionflux::Mapping::Linear* Linear::create(Ionflux::Mapping::MappingValue 
initLower, Ionflux::Mapping::MappingValue initUpper)
{
	Linear* m0 = create();
	m0->setLower(initLower);
	m0->setUpper(initUpper);
	return m0;
}

void Linear::setLower(Ionflux::Mapping::MappingValue newLower)
{
	lower = newLower;
}

Ionflux::Mapping::MappingValue Linear::getLower() const
{
    return lower;
}

void Linear::setUpper(Ionflux::Mapping::MappingValue newUpper)
{
	upper = newUpper;
}

Ionflux::Mapping::MappingValue Linear::getUpper() const
{
    return upper;
}

Ionflux::Mapping::Linear& Linear::operator=(const Ionflux::Mapping::Linear&
other)
{
    ChainableMapping::operator=(other);
    lower = other.lower;
    upper = other.upper;
	return *this;
}

Ionflux::Mapping::Linear* Linear::copy() const
{
    Linear* newLinear = create();
    *newLinear = *this;
    return newLinear;
}

Ionflux::Mapping::Linear* Linear::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Linear*>(other);
}

Ionflux::Mapping::Linear* Linear::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Linear* newObject = new Linear();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Linear::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Linear.cpp
 * \brief Linear mapping implementation.
 */
