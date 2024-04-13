/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Random.cpp                      Random mapping (implementation).
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

#include "ifmapping/Random.hpp"
#include <cmath>
#include <sstream>
#include "ifmapping/utils.hpp"
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

RandomClassInfo::RandomClassInfo()
{
	name = "Random";
	desc = "Random mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

RandomClassInfo::~RandomClassInfo()
{
}

// run-time type information instance constants
const RandomClassInfo Random::randomClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Random::CLASS_INFO = &Random::randomClassInfo;

Random::Random()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Random::Random(const Ionflux::Mapping::Random& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Random::Random(Ionflux::Mapping::MappingValue initScale, 
Ionflux::Mapping::MappingValue initOffset, Ionflux::Mapping::Mapping* 
initFunc)
: ChainableMapping(initFunc, initScale, initOffset)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Random::~Random()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
Random::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	// TODO: Implementation.
	return getRandomDouble();
}

Ionflux::Mapping::Random& Random::operator=(const Ionflux::Mapping::Random&
other)
{
	ChainableMapping::operator=(other);
	return *this;
}

Ionflux::Mapping::Random* Random::copy() const
{
	Random* newRandom = create();
	*newRandom = *this;
	return newRandom;
}

Ionflux::Mapping::Random* Random::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Random*>(other);
}

Ionflux::Mapping::Random* Random::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Random* newObject = new Random();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Random::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Random.cpp
 * \brief Random mapping implementation.
 */
