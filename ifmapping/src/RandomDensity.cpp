/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * RandomDensity.cpp               Random mapping (implementation).
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

#include "ifmapping/RandomDensity.hpp"
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

RandomDensityClassInfo::RandomDensityClassInfo()
{
	name = "RandomDensity";
	desc = "Random mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

RandomDensityClassInfo::~RandomDensityClassInfo()
{
}

// run-time type information instance constants
const RandomDensityClassInfo RandomDensity::randomDensityClassInfo;
const Ionflux::ObjectBase::IFClassInfo* RandomDensity::CLASS_INFO = &RandomDensity::randomDensityClassInfo;

RandomDensity::RandomDensity()
: maxIters(MAX_ITERATIONS)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

RandomDensity::RandomDensity(const Ionflux::Mapping::RandomDensity& other)
: maxIters(MAX_ITERATIONS)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

RandomDensity::RandomDensity(Ionflux::Mapping::Mapping* initFunc, 
Ionflux::Mapping::MappingValue initMaxIters, Ionflux::Mapping::MappingValue
initScale, Ionflux::Mapping::MappingValue initOffset)
: ChainableMapping(initFunc, initScale, initOffset), maxIters(initMaxIters)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

RandomDensity::~RandomDensity()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
RandomDensity::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	if (func == 0)
	    return getRandomDouble();
	Ionflux::Mapping::Point p0 = Point::getRandom();
	Ionflux::Mapping::MappingValue f0 = (*func)(p0.getX());
	unsigned int i = 0;
	while ((p0.getY() > f0) 
	    && (i <= maxIters))
	{
	    p0 = Point::getRandom();
	    f0 = (*func)(p0.getX());
	    i++;
	}
	if (i > maxIters)
	    throw MappingError("Maximum number of iterations exceeded.");
	return p0.getX();
}

Ionflux::Mapping::MappingValue 
RandomDensity::call(Ionflux::Mapping::MappingValue value) const
{
	// TODO: Implementation.
	return callWithParam(value);;
}

void RandomDensity::setMaxIters(unsigned int newMaxIters)
{
	maxIters = newMaxIters;
}

unsigned int RandomDensity::getMaxIters() const
{
    return maxIters;
}

Ionflux::Mapping::RandomDensity& RandomDensity::operator=(const 
Ionflux::Mapping::RandomDensity& other)
{
    ChainableMapping::operator=(other);
    maxIters = other.maxIters;
    return *this;
}

Ionflux::Mapping::RandomDensity* RandomDensity::copy() const
{
    RandomDensity* newRandomDensity = create();
    *newRandomDensity = *this;
    return newRandomDensity;
}

Ionflux::Mapping::RandomDensity* 
RandomDensity::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<RandomDensity*>(other);
}

Ionflux::Mapping::RandomDensity* 
RandomDensity::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    RandomDensity* newObject = new RandomDensity();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int RandomDensity::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file RandomDensity.cpp
 * \brief Random mapping implementation.
 */
