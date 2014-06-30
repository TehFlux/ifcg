/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Exp.cpp                         Exponential mapping (implementation).
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

#include "ifmapping/Exp.hpp"
#include <cmath>
#include <sstream>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

ExpClassInfo::ExpClassInfo()
{
	name = "Exp";
	desc = "Exponential mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

ExpClassInfo::~ExpClassInfo()
{
}

// run-time type information instance constants
const ExpClassInfo Exp::expClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Exp::CLASS_INFO = &Exp::expClassInfo;

Exp::Exp()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Exp::Exp(const Ionflux::Mapping::Exp& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Exp::Exp(Ionflux::Mapping::MappingValue initScale, 
Ionflux::Mapping::MappingValue initOffset, Ionflux::Mapping::Mapping* 
initFunc)
: ChainableMapping(initFunc, initScale, initOffset)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Exp::~Exp()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
Exp::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	// TODO: Implementation.
	return exp(value);
}

Ionflux::Mapping::Exp& Exp::operator=(const Ionflux::Mapping::Exp& other)
{
    ChainableMapping::operator=(other);
	return *this;
}

Ionflux::Mapping::Exp* Exp::copy() const
{
    Exp* newExp = create();
    *newExp = *this;
    return newExp;
}

Ionflux::Mapping::Exp* Exp::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Exp*>(other);
}

Ionflux::Mapping::Exp* Exp::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Exp* newObject = new Exp();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Exp::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Exp.cpp
 * \brief Exponential mapping implementation.
 */
