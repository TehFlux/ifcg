/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * InverseFalloff.cpp              Inverse falloff mapping 
 * (implementation).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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

#include "ifmapping/InverseFalloff.hpp"
#include <cmath>
#include <sstream>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

InverseFalloffClassInfo::InverseFalloffClassInfo()
{
	name = "InverseFalloff";
	desc = "Inverse falloff mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

InverseFalloffClassInfo::~InverseFalloffClassInfo()
{
}

// run-time type information instance constants
const InverseFalloffClassInfo InverseFalloff::inverseFalloffClassInfo;
const Ionflux::ObjectBase::IFClassInfo* InverseFalloff::CLASS_INFO = &InverseFalloff::inverseFalloffClassInfo;

InverseFalloff::InverseFalloff()
: exponent(1.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

InverseFalloff::InverseFalloff(const Ionflux::Mapping::InverseFalloff& other)
: exponent(1.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

InverseFalloff::InverseFalloff(double initExponent)
: exponent(initExponent)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

InverseFalloff::~InverseFalloff()
{
	// TODO: Nothing ATM. ;-)
}

std::string InverseFalloff::getString() const
{
	ostringstream status;
	status << getClassName() << "[";
	if (func != 0)
	    status << (*func);
	else
	    status << "<none>";
	status << "; " << scale << ", " << offset << "; " << exponent 
	    << "]";
	return status.str();
}

Ionflux::Mapping::MappingValue 
InverseFalloff::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	// TODO: Implementation.
	return 1. / pow(1. + value, exponent);
}

void InverseFalloff::setExponent(Ionflux::Mapping::MappingValue 
newExponent)
{
	exponent = newExponent;
}

Ionflux::Mapping::MappingValue InverseFalloff::getExponent() const
{
    return exponent;
}

Ionflux::Mapping::InverseFalloff& InverseFalloff::operator=(const 
Ionflux::Mapping::InverseFalloff& other)
{
    ChainableMapping::operator=(other);
    exponent = other.exponent;
	return *this;
}

Ionflux::Mapping::InverseFalloff* InverseFalloff::copy() const
{
    InverseFalloff* newInverseFalloff = create();
    *newInverseFalloff = *this;
    return newInverseFalloff;
}

Ionflux::Mapping::InverseFalloff* 
InverseFalloff::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<InverseFalloff*>(other);
}

Ionflux::Mapping::InverseFalloff* 
InverseFalloff::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    InverseFalloff* newObject = new InverseFalloff();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int InverseFalloff::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file InverseFalloff.cpp
 * \brief Inverse falloff mapping implementation.
 */
