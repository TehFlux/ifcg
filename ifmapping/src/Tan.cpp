/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Tan.cpp                         Tangent mapping (implementation).
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

#include "ifmapping/Tan.hpp"
#include <cmath>
#include <sstream>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

TanClassInfo::TanClassInfo()
{
	name = "Tan";
	desc = "Tangent mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

TanClassInfo::~TanClassInfo()
{
}

// run-time type information instance constants
const TanClassInfo Tan::tanClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Tan::CLASS_INFO = &Tan::tanClassInfo;

Tan::Tan()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Tan::Tan(const Ionflux::Mapping::Tan& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Tan::Tan(Ionflux::Mapping::MappingValue initScale, 
Ionflux::Mapping::MappingValue initOffset, Ionflux::Mapping::Mapping* 
initFunc)
: ChainableMapping(initFunc, initScale, initOffset)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Tan::~Tan()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
Tan::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	// TODO: Implementation.
	return tan(value);
}

Ionflux::Mapping::Tan& Tan::operator=(const Ionflux::Mapping::Tan& other)
{
    ChainableMapping::operator=(other);
	return *this;
}

Ionflux::Mapping::Tan* Tan::copy() const
{
    Tan* newTan = create();
    *newTan = *this;
    return newTan;
}

Ionflux::Mapping::Tan* Tan::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Tan*>(other);
}

Ionflux::Mapping::Tan* Tan::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Tan* newObject = new Tan();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Tan::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Tan.cpp
 * \brief Tangent mapping implementation.
 */
