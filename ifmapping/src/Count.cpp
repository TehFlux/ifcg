/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Count.cpp                       Count mapping (implementation).
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

#include "ifmapping/Count.hpp"
#include <cmath>
#include <sstream>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

CountClassInfo::CountClassInfo()
{
	name = "Count";
	desc = "Count mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

CountClassInfo::~CountClassInfo()
{
}

// run-time type information instance constants
const CountClassInfo Count::countClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Count::CLASS_INFO = &Count::countClassInfo;

Count::Count()
: counterImpl(0), adjustment(1.), modulus(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	counterImpl = new Ionflux::Mapping::MappingValue();
	*counterImpl = 0;
}

Count::Count(const Ionflux::Mapping::Count& other)
: counterImpl(0), adjustment(1.), modulus(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (counterImpl == 0)
	    counterImpl = new Ionflux::Mapping::MappingValue();
	*this = other;
}

Count::Count(Ionflux::Mapping::MappingValue initAdjustment, 
Ionflux::Mapping::MappingValue initCounter, Ionflux::Mapping::MappingValue 
initModulus, Ionflux::Mapping::MappingValue initScale, 
Ionflux::Mapping::MappingValue initOffset, Ionflux::Mapping::Mapping* 
initFunc)
: ChainableMapping(initFunc, initScale, initOffset), counterImpl(0), 
adjustment(initAdjustment), modulus(initModulus)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	counterImpl = new Ionflux::Mapping::MappingValue();
	*counterImpl = initCounter;
}

Count::~Count()
{
	delete counterImpl;
}

Ionflux::Mapping::MappingValue 
Count::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	Ionflux::Mapping::MappingValue current = *counterImpl;
	*counterImpl += adjustment;
	if (modulus != 0.)
	    while (*counterImpl >= modulus)
	        *counterImpl -= modulus;
	return current;
}

void Count::setCounter(Ionflux::Mapping::MappingValue newCounter)
{
	*counterImpl = newCounter;
}

Ionflux::Mapping::MappingValue Count::getCounter() const
{
	return *counterImpl;
}

void Count::setAdjustment(Ionflux::Mapping::MappingValue newAdjustment)
{
	adjustment = newAdjustment;
}

Ionflux::Mapping::MappingValue Count::getAdjustment() const
{
    return adjustment;
}

void Count::setModulus(Ionflux::Mapping::MappingValue newModulus)
{
	modulus = newModulus;
}

Ionflux::Mapping::MappingValue Count::getModulus() const
{
    return modulus;
}

Ionflux::Mapping::Count& Count::operator=(const Ionflux::Mapping::Count& 
other)
{
    ChainableMapping::operator=(other);
    *counterImpl = *other.counterImpl;
    modulus = other.modulus;
    adjustment = other.adjustment;
    return *this;
}

Ionflux::Mapping::Count* Count::copy() const
{
    Count* newCount = create();
    *newCount = *this;
    return newCount;
}

Ionflux::Mapping::Count* Count::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Count*>(other);
}

Ionflux::Mapping::Count* Count::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Count* newObject = new Count();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Count::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Count.cpp
 * \brief Count mapping implementation.
 */
