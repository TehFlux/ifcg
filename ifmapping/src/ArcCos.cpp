/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ArcCos.cpp                      Arc cosine mapping (implementation).
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

#include "ifmapping/ArcCos.hpp"
#include <cmath>
#include <sstream>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

ArcCosClassInfo::ArcCosClassInfo()
{
	name = "ArcCos";
	desc = "Arc cosine mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

ArcCosClassInfo::~ArcCosClassInfo()
{
}

// run-time type information instance constants
const ArcCosClassInfo ArcCos::arcCosClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ArcCos::CLASS_INFO = &ArcCos::arcCosClassInfo;

ArcCos::ArcCos()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ArcCos::ArcCos(const Ionflux::Mapping::ArcCos& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ArcCos::ArcCos(Ionflux::Mapping::MappingValue initScale, 
Ionflux::Mapping::MappingValue initOffset, Ionflux::Mapping::Mapping* 
initFunc)
: ChainableMapping(initFunc, initScale, initOffset)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ArcCos::~ArcCos()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
ArcCos::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	// TODO: Implementation.
	return acos(value);
}

Ionflux::Mapping::ArcCos& ArcCos::operator=(const Ionflux::Mapping::ArcCos&
other)
{
	ChainableMapping::operator=(other);
	return *this;
}

Ionflux::Mapping::ArcCos* ArcCos::copy() const
{
	ArcCos* newArcCos = create();
	*newArcCos = *this;
	return newArcCos;
}

Ionflux::Mapping::ArcCos* ArcCos::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<ArcCos*>(other);
}

Ionflux::Mapping::ArcCos* ArcCos::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    ArcCos* newObject = new ArcCos();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int ArcCos::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file ArcCos.cpp
 * \brief Arc cosine mapping implementation.
 */
