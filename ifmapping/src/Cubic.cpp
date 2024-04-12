/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Cubic.cpp                       Cubic mapping (implementation).
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

#include "ifmapping/Cubic.hpp"
#include <sstream>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

CubicClassInfo::CubicClassInfo()
{
	name = "Cubic";
	desc = "Cubic mapping";
}

CubicClassInfo::~CubicClassInfo()
{
}

// run-time type information instance constants
const CubicClassInfo Cubic::cubicClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Cubic::CLASS_INFO = &Cubic::cubicClassInfo;

Cubic::Cubic()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Cubic::Cubic(const Ionflux::Mapping::Cubic& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Cubic::Cubic(Ionflux::Mapping::MappingValue initLower, 
Ionflux::Mapping::MappingValue initUpper)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	lower = initLower;
	upper = initUpper;
}

Cubic::~Cubic()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
Cubic::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	Ionflux::Mapping::MappingValue t2 = value * value;
	Ionflux::Mapping::MappingValue tx = 
	    3. * t2 - 2. * (t2 * value);
	return Linear::callWithParam(tx);
}

Ionflux::Mapping::Cubic& Cubic::operator=(const Ionflux::Mapping::Cubic& 
other)
{
    Linear::operator=(other);
    return *this;
}

Ionflux::Mapping::Cubic* Cubic::copy() const
{
    Cubic* newCubic = create();
    *newCubic = *this;
    return newCubic;
}

Ionflux::Mapping::Cubic* Cubic::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Cubic*>(other);
}

Ionflux::Mapping::Cubic* Cubic::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Cubic* newObject = new Cubic();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Cubic::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Cubic.cpp
 * \brief Cubic mapping implementation.
 */
