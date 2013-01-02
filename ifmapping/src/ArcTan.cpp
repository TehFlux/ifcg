/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ArcTan.cpp                      Arc tangent mapping (implementation).
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

#include "ifmapping/ArcTan.hpp"
#include <cmath>
#include <sstream>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

ArcTanClassInfo::ArcTanClassInfo()
{
	name = "ArcTan";
	desc = "Arc tangent mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

ArcTanClassInfo::~ArcTanClassInfo()
{
}

// run-time type information instance constants
const ArcTanClassInfo ArcTan::arcTanClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ArcTan::CLASS_INFO = &ArcTan::arcTanClassInfo;

ArcTan::ArcTan()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ArcTan::ArcTan(const Ionflux::Mapping::ArcTan& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ArcTan::ArcTan(Ionflux::Mapping::MappingValue initScale, 
Ionflux::Mapping::MappingValue initOffset, Ionflux::Mapping::Mapping* 
initFunc)
: ChainableMapping(initFunc, initScale, initOffset)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ArcTan::~ArcTan()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
ArcTan::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	// TODO: Implementation.
	return atan(value);
}

Ionflux::Mapping::ArcTan& ArcTan::operator=(const Ionflux::Mapping::ArcTan&
other)
{
    ChainableMapping::operator=(other);
	return *this;
}

Ionflux::Mapping::ArcTan* ArcTan::copy() const
{
    ArcTan* newArcTan = create();
    *newArcTan = *this;
    return newArcTan;
}

Ionflux::Mapping::ArcTan* ArcTan::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<ArcTan*>(other);
}

Ionflux::Mapping::ArcTan* ArcTan::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    ArcTan* newObject = new ArcTan();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file ArcTan.cpp
 * \brief Arc tangent mapping implementation.
 */
