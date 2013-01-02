/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Accept.cpp                      Accept method mapping (implementation).
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

#include "ifmapping/Accept.hpp"
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

AcceptClassInfo::AcceptClassInfo()
{
	name = "Accept";
	desc = "Accept method mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

AcceptClassInfo::~AcceptClassInfo()
{
}

// run-time type information instance constants
const AcceptClassInfo Accept::acceptClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Accept::CLASS_INFO = &Accept::acceptClassInfo;

Accept::Accept()
: maxIters(MAX_ITERATIONS)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Accept::Accept(const Ionflux::Mapping::Accept& other)
: maxIters(MAX_ITERATIONS)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Accept::Accept(Ionflux::Mapping::Mapping* initFunc, unsigned int 
initMaxIters, Ionflux::Mapping::MappingValue initScale, 
Ionflux::Mapping::MappingValue initOffset)
: ChainableMapping(initFunc, initScale, initOffset), maxIters(initMaxIters)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Accept::~Accept()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
Accept::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	if (func == 0)
	    throw MappingError("Source function not defined.");
	Ionflux::Mapping::MappingValue f0 = (*func)(value);
	unsigned int i = 0;
	while (!isInRange(acceptRange, f0) 
	    && (i <= maxIters))
	{
	    f0 = (*func)(value);
	    i++;
	}
	if (i > maxIters)
	    throw MappingError("Maximum number of iterations exceeded.");
	return f0;
}

Ionflux::Mapping::MappingValue Accept::call(Ionflux::Mapping::MappingValue 
value) const
{
	// TODO: Implementation.
	return callWithParam(value);;
}

void Accept::setMaxIters(unsigned int newMaxIters)
{
	maxIters = newMaxIters;
}

unsigned int Accept::getMaxIters() const
{
	return maxIters;
}

void Accept::setAcceptRange(const Ionflux::Mapping::Range& newAcceptRange)
{
	acceptRange = newAcceptRange;
}

Ionflux::Mapping::Range Accept::getAcceptRange() const
{
	return acceptRange;
}

Ionflux::Mapping::Accept& Accept::operator=(const Ionflux::Mapping::Accept&
other)
{
    ChainableMapping::operator=(other);
    maxIters = other.maxIters;
    acceptRange = other.acceptRange;
	return *this;
}

Ionflux::Mapping::Accept* Accept::copy() const
{
    Accept* newAccept = create();
    *newAccept = *this;
    return newAccept;
}

Ionflux::Mapping::Accept* Accept::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Accept*>(other);
}

Ionflux::Mapping::Accept* Accept::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Accept* newObject = new Accept();
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

/** \file Accept.cpp
 * \brief Accept method mapping implementation.
 */
