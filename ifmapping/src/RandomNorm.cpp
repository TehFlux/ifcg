/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * RandomNorm.cpp                  Random mapping (implementation).
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

#include "ifmapping/RandomNorm.hpp"
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

RandomNormClassInfo::RandomNormClassInfo()
{
	name = "RandomNorm";
	desc = "Random mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

RandomNormClassInfo::~RandomNormClassInfo()
{
}

// run-time type information instance constants
const RandomNormClassInfo RandomNorm::randomNormClassInfo;
const Ionflux::ObjectBase::IFClassInfo* RandomNorm::CLASS_INFO = &RandomNorm::randomNormClassInfo;

RandomNorm::RandomNorm()
: mean(0.), stdDev(1.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

RandomNorm::RandomNorm(const Ionflux::Mapping::RandomNorm& other)
: mean(0.), stdDev(1.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

RandomNorm::RandomNorm(Ionflux::Mapping::MappingValue initMean, 
Ionflux::Mapping::MappingValue initStdDev, Ionflux::Mapping::MappingValue 
initScale, Ionflux::Mapping::MappingValue initOffset, 
Ionflux::Mapping::Mapping* initFunc)
: ChainableMapping(initFunc, initScale, initOffset), mean(initMean), 
stdDev(initStdDev)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

RandomNorm::~RandomNorm()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
RandomNorm::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	// TODO: Implementation.
	return getRandomNorm(mean, stdDev);
}

void RandomNorm::setMean(Ionflux::Mapping::MappingValue newMean)
{
	mean = newMean;
}

Ionflux::Mapping::MappingValue RandomNorm::getMean() const
{
	return mean;
}

void RandomNorm::setStdDev(Ionflux::Mapping::MappingValue newStdDev)
{
	stdDev = newStdDev;
}

Ionflux::Mapping::MappingValue RandomNorm::getStdDev() const
{
	return stdDev;
}

Ionflux::Mapping::RandomNorm& RandomNorm::operator=(const 
Ionflux::Mapping::RandomNorm& other)
{
    ChainableMapping::operator=(other);
    mean = other.mean;
    stdDev = other.stdDev;
	return *this;
}

Ionflux::Mapping::RandomNorm* RandomNorm::copy() const
{
    RandomNorm* newRandomNorm = create();
    *newRandomNorm = *this;
    return newRandomNorm;
}

Ionflux::Mapping::RandomNorm* 
RandomNorm::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<RandomNorm*>(other);
}

Ionflux::Mapping::RandomNorm* 
RandomNorm::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    RandomNorm* newObject = new RandomNorm();
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

/** \file RandomNorm.cpp
 * \brief Random mapping implementation.
 */
