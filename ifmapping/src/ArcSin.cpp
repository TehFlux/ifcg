/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ArcSin.cpp                      Arc sine mapping (implementation).
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

#include "ifmapping/ArcSin.hpp"
#include <cmath>
#include <sstream>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

ArcSinClassInfo::ArcSinClassInfo()
{
	name = "ArcSin";
	desc = "Arc sine mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

ArcSinClassInfo::~ArcSinClassInfo()
{
}

// run-time type information instance constants
const ArcSinClassInfo ArcSin::arcSinClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ArcSin::CLASS_INFO = &ArcSin::arcSinClassInfo;

ArcSin::ArcSin()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ArcSin::ArcSin(const Ionflux::Mapping::ArcSin& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ArcSin::ArcSin(Ionflux::Mapping::MappingValue initScale, 
Ionflux::Mapping::MappingValue initOffset, Ionflux::Mapping::Mapping* 
initFunc)
: ChainableMapping(initFunc, initScale, initOffset)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ArcSin::~ArcSin()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
ArcSin::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	// TODO: Implementation.
	return asin(value);
}

Ionflux::Mapping::ArcSin& ArcSin::operator=(const Ionflux::Mapping::ArcSin&
other)
{
	ChainableMapping::operator=(other);
	return *this;
}

Ionflux::Mapping::ArcSin* ArcSin::copy() const
{
	ArcSin* newArcSin = create();
	*newArcSin = *this;
	return newArcSin;
}

Ionflux::Mapping::ArcSin* ArcSin::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<ArcSin*>(other);
}

Ionflux::Mapping::ArcSin* ArcSin::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    ArcSin* newObject = new ArcSin();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int ArcSin::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file ArcSin.cpp
 * \brief Arc sine mapping implementation.
 */
