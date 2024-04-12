/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Sin.cpp                         Sine mapping (implementation).
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

#include "ifmapping/Sin.hpp"
#include <cmath>
#include <sstream>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

SinClassInfo::SinClassInfo()
{
	name = "Sin";
	desc = "Sine mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

SinClassInfo::~SinClassInfo()
{
}

// run-time type information instance constants
const SinClassInfo Sin::sinClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Sin::CLASS_INFO = &Sin::sinClassInfo;

Sin::Sin()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Sin::Sin(const Ionflux::Mapping::Sin& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Sin::Sin(Ionflux::Mapping::MappingValue initScale, 
Ionflux::Mapping::MappingValue initOffset, Ionflux::Mapping::Mapping* 
initFunc)
: ChainableMapping(initFunc, initScale, initOffset)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Sin::~Sin()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
Sin::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	// TODO: Implementation.
	return sin(value);
}

Ionflux::Mapping::Sin& Sin::operator=(const Ionflux::Mapping::Sin& other)
{
    ChainableMapping::operator=(other);
	return *this;
}

Ionflux::Mapping::Sin* Sin::copy() const
{
    Sin* newSin = create();
    *newSin = *this;
    return newSin;
}

Ionflux::Mapping::Sin* Sin::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Sin*>(other);
}

Ionflux::Mapping::Sin* Sin::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Sin* newObject = new Sin();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Sin::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Sin.cpp
 * \brief Sine mapping implementation.
 */
