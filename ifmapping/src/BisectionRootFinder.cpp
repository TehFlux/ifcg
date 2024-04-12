/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BisectionRootFinder.cpp         Bisection root finder (implementation).
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

#include "ifmapping/BisectionRootFinder.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <sstream>
#include <cmath>
#include "ifmapping/utils.hpp"
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

BisectionRootFinderClassInfo::BisectionRootFinderClassInfo()
{
	name = "BisectionRootFinder";
	desc = "Bisection root finder";
}

BisectionRootFinderClassInfo::~BisectionRootFinderClassInfo()
{
}

// run-time type information instance constants
const BisectionRootFinderClassInfo BisectionRootFinder::bisectionRootFinderClassInfo;
const Ionflux::ObjectBase::IFClassInfo* BisectionRootFinder::CLASS_INFO = &BisectionRootFinder::bisectionRootFinderClassInfo;

BisectionRootFinder::BisectionRootFinder()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

BisectionRootFinder::BisectionRootFinder(const Ionflux::Mapping::BisectionRootFinder& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

BisectionRootFinder::~BisectionRootFinder()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
BisectionRootFinder::findRoot(Ionflux::Mapping::MappingValue a, 
Ionflux::Mapping::MappingValue b, Ionflux::Mapping::MappingValue delta) 
const
{
	// TODO: Implementation.
	return findRoot(a, b, delta, 101);
}

Ionflux::Mapping::MappingValue 
BisectionRootFinder::findRoot(Ionflux::Mapping::MappingValue a, 
Ionflux::Mapping::MappingValue b, Ionflux::Mapping::MappingValue delta, 
unsigned int samples) const
{
	// <---- DEBUG ----- //
	ostringstream message;
	// <---- DEBUG ----- */
	if (compareSigns(a, b) == 0)
	{
	    // <---- DEBUG ----- //
	    message << "Start interval edge values must have opposite " 
	        << "signs. Trying to find a suitable interval (sign(f(a)) = " 
	        << Ionflux::Mapping::sign((*func)(a)) << ", sign(f(b)) = " 
	        << Ionflux::Mapping::sign((*func)(b)) << ").";
	    log(IFLogMessage(message.str(), VL_DEBUG, this, "findRoot"));
	    // <---- DEBUG ----- */
	    Range r0 = findStartInterval(samples, a, b);
	    a = r0.lower;
	    b = r0.upper;
	}
	if ((*func)(a) == 0.)
	    return a;
	if ((*func)(b) == 0.)
	    return b;
	Ionflux::Mapping::MappingValue m = 0.5 * (a + b);
	if (fabs(b - a) < delta)
	    return m;
	if ((*func)(m) == 0.)
	    return m;
	if (compareSigns(a, m) != 0)
	    return findRoot(a, m, delta, samples);
	else
	if (compareSigns(m, b) != 0)
	    return findRoot(m, b, delta, samples);
	message.str("");
	message << "None of the current arguments yields a valid "
	    " interval for the next iteration (a = " << a << ", m = " 
	    << m << ", b = " << b << ", func(a) = " << (*func)(a) 
	    << ", func(m) = " << (*func)(m) << ", func(b) = " 
	    << (*func)(b) << ")";
	throw MappingError(message.str());
	return 0;
}

std::string BisectionRootFinder::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

Ionflux::Mapping::BisectionRootFinder& BisectionRootFinder::operator=(const
Ionflux::Mapping::BisectionRootFinder& other)
{
if (this == &other)
    return *this;
    return *this;
}

Ionflux::Mapping::BisectionRootFinder* BisectionRootFinder::copy() const
{
    BisectionRootFinder* newBisectionRootFinder = create();
    *newBisectionRootFinder = *this;
    return newBisectionRootFinder;
}

Ionflux::Mapping::BisectionRootFinder* 
BisectionRootFinder::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<BisectionRootFinder*>(other);
}

Ionflux::Mapping::BisectionRootFinder* 
BisectionRootFinder::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    BisectionRootFinder* newObject = new BisectionRootFinder();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int BisectionRootFinder::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file BisectionRootFinder.cpp
 * \brief Bisection root finder implementation.
 */
