/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Constant.cpp                    Constant mapping (implementation).
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

#include "ifmapping/Constant.hpp"
#include <sstream>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

ConstantClassInfo::ConstantClassInfo()
{
	name = "Constant";
	desc = "Constant mapping";
}

ConstantClassInfo::~ConstantClassInfo()
{
}

// run-time type information instance constants
const ConstantClassInfo Constant::constantClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Constant::CLASS_INFO = &Constant::constantClassInfo;

Constant::Constant()
: constValue(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Constant::Constant(const Ionflux::Mapping::Constant& other)
: constValue(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Constant::Constant(Ionflux::Mapping::MappingValue initConstValue)
: constValue(initConstValue)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Constant::~Constant()
{
	// TODO: Nothing ATM. ;-)
}

std::string Constant::getString() const
{
	ostringstream state;
	state << getClassName() << "[" << constValue << "]";
	return state.str();
}

Ionflux::Mapping::MappingValue 
Constant::call(Ionflux::Mapping::MappingValue value) const
{
	// TODO: Implementation.
	return constValue;
}

Ionflux::Mapping::Constant* Constant::create(Ionflux::Mapping::MappingValue
initConstValue)
{
	Constant* m0 = create();
	m0->setConstValue(initConstValue);
	return m0;
}

void Constant::setConstValue(Ionflux::Mapping::MappingValue newConstValue)
{
	constValue = newConstValue;
}

Ionflux::Mapping::MappingValue Constant::getConstValue() const
{
    return constValue;
}

Ionflux::Mapping::Constant& Constant::operator=(const 
Ionflux::Mapping::Constant& other)
{
    constValue = other.constValue;
	return *this;
}

Ionflux::Mapping::Constant* Constant::copy() const
{
    Constant* newConstant = create();
    *newConstant = *this;
    return newConstant;
}

Ionflux::Mapping::Constant* Constant::upcast(Ionflux::ObjectBase::IFObject*
other)
{
    return dynamic_cast<Constant*>(other);
}

Ionflux::Mapping::Constant* Constant::create(Ionflux::ObjectBase::IFObject*
parentObject)
{
    Constant* newObject = new Constant();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Constant::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Constant.cpp
 * \brief Constant mapping implementation.
 */
