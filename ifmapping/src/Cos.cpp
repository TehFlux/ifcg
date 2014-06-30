/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Cos.cpp                         Cosine mapping (implementation).
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

#include "ifmapping/Cos.hpp"
#include <cmath>
#include <sstream>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

CosClassInfo::CosClassInfo()
{
	name = "Cos";
	desc = "Cosine mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

CosClassInfo::~CosClassInfo()
{
}

// run-time type information instance constants
const CosClassInfo Cos::cosClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Cos::CLASS_INFO = &Cos::cosClassInfo;

Cos::Cos()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Cos::Cos(const Ionflux::Mapping::Cos& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Cos::Cos(Ionflux::Mapping::MappingValue initScale, 
Ionflux::Mapping::MappingValue initOffset, Ionflux::Mapping::Mapping* 
initFunc)
: ChainableMapping(initFunc, initScale, initOffset)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Cos::~Cos()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
Cos::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	// TODO: Implementation.
	return cos(value);
}

Ionflux::Mapping::Cos& Cos::operator=(const Ionflux::Mapping::Cos& other)
{
    ChainableMapping::operator=(other);
	return *this;
}

Ionflux::Mapping::Cos* Cos::copy() const
{
    Cos* newCos = create();
    *newCos = *this;
    return newCos;
}

Ionflux::Mapping::Cos* Cos::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Cos*>(other);
}

Ionflux::Mapping::Cos* Cos::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Cos* newObject = new Cos();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Cos::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Cos.cpp
 * \brief Cosine mapping implementation.
 */
