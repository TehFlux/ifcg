/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * RootFinder.cpp                  Root finder (implementation).
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

#include "ifmapping/RootFinder.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <sstream>
#include "ifmapping/utils.hpp"
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

RootFinderClassInfo::RootFinderClassInfo()
{
	name = "RootFinder";
	desc = "Root finder";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

RootFinderClassInfo::~RootFinderClassInfo()
{
}

// run-time type information instance constants
const RootFinderClassInfo RootFinder::rootFinderClassInfo;
const Ionflux::ObjectBase::IFClassInfo* RootFinder::CLASS_INFO = &RootFinder::rootFinderClassInfo;

RootFinder::RootFinder()
: func(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

RootFinder::RootFinder(const Ionflux::Mapping::RootFinder& other)
: func(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

RootFinder::~RootFinder()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
RootFinder::compareSigns(Ionflux::Mapping::MappingValue a, 
Ionflux::Mapping::MappingValue b) const
{
	if (Ionflux::Mapping::sign((*func)(a)) 
	    == Ionflux::Mapping::sign((*func)(b)))
	    return 0.;
	return 1.;
}

void RootFinder::findStartIntervals(Ionflux::Mapping::RangeVector& target, 
unsigned int samples, Ionflux::Mapping::MappingValue a, 
Ionflux::Mapping::MappingValue b) const
{
	if (samples < 2)
	    // Need at least two samples.
	    samples = 2;
	Ionflux::Mapping::MappingValue d = (b - a) / (samples - 1);
	Ionflux::Mapping::Sample cs0;
	Ionflux::Mapping::Sample cs1;
	for (unsigned int i = 0; i < (samples - 1); i++)
	{
	    cs0 = func->sample(a + i * d);
	    cs1 = func->sample(a + (i + 1) * d);
	    if (cs0.s != cs1.s)
	    {
	        Ionflux::Mapping::Range r0;
	        r0.lower = cs0.x;
	        r0.upper = cs1.x;
	        target.push_back(r0);
	    }
	}
}

Ionflux::Mapping::Range RootFinder::findStartInterval(unsigned int samples,
Ionflux::Mapping::MappingValue a, Ionflux::Mapping::MappingValue b) const
{
	if (samples % 2 == 0)
	    // Need an odd number of samples.
	    samples++;
	Ionflux::Mapping::MappingValue d = (b - a) / samples;
	Ionflux::Mapping::Sample negSample;
	Ionflux::Mapping::Sample posSample;
	Ionflux::Mapping::Sample cs0;
	Ionflux::Mapping::Sample cs1;
	negSample.valid = false;
	posSample.valid = false;
	for (unsigned int i = 0; i < samples / 2; i++)
	{
	    cs0 = func->sample(a + i * d);
	    cs1 = func->sample(b - i * d);
	    // Try to update the negative sample.
	    if (cs0.s < 0.)
	        Ionflux::Mapping::updateSample(cs0, 
	            negSample, posSample);
	    if (cs1.s < 0.)
	        Ionflux::Mapping::updateSample(cs1, 
	            negSample, posSample);
	    // Try to update the positive sample.
	    if (cs0.s > 0.)
	        Ionflux::Mapping::updateSample(cs0, 
	            posSample, negSample);
	    if (cs1.s > 0.)
	        Ionflux::Mapping::updateSample(cs1, 
	            posSample, negSample);
	}
	Ionflux::Mapping::Range result;
	if (!posSample.valid || !negSample.valid)
	{
	    ostringstream message;
	    message << "Could not find a suitable start interval " 
	        << "(a = " << a << ", b = " << b << ", f(a) = " 
	        << (*func)(a) << ", f(b) = " << (*func)(b) 
	        << ", samples = " << samples << ").";
	    throw Ionflux::Mapping::MappingError(message.str());
	}
	Ionflux::Mapping::MappingValue x0 = negSample.x;
	Ionflux::Mapping::MappingValue x1 = posSample.x;
	if (x0 < x1)
	{
	    result.lower = x0;
	    result.upper = x1;
	} else
	{
	    result.lower = x1;
	    result.upper = x0;
	}
	return result;
}

Ionflux::Mapping::MappingValue 
RootFinder::operator()(Ionflux::Mapping::MappingValue a, 
Ionflux::Mapping::MappingValue b, Ionflux::Mapping::MappingValue delta) 
const
{
	// TODO: Implementation.
	return findRoot(a, b, delta);;
}

std::string RootFinder::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

void RootFinder::setFunc(Ionflux::Mapping::Mapping* newFunc)
{
	if (func == newFunc)
		return;
    if (newFunc != 0)
        addLocalRef(newFunc);
	if (func != 0)
		removeLocalRef(func);
	func = newFunc;
}

Ionflux::Mapping::Mapping* RootFinder::getFunc() const
{
	return func;
}

Ionflux::Mapping::RootFinder& RootFinder::operator=(const 
Ionflux::Mapping::RootFinder& other)
{
    setFunc(other.func);
	return *this;
}

Ionflux::Mapping::RootFinder* 
RootFinder::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<RootFinder*>(other);
}

}

}

/** \file RootFinder.cpp
 * \brief Root finder implementation.
 */
