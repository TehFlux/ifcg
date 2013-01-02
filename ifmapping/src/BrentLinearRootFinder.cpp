/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BrentLinearRootFinder.cpp       Brent linear root finder 
 * (implementation).
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

#include "ifmapping/BrentLinearRootFinder.hpp"
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

BrentLinearRootFinderClassInfo::BrentLinearRootFinderClassInfo()
{
	name = "BrentLinearRootFinder";
	desc = "Brent linear root finder";
}

BrentLinearRootFinderClassInfo::~BrentLinearRootFinderClassInfo()
{
}

// run-time type information instance constants
const BrentLinearRootFinderClassInfo BrentLinearRootFinder::brentLinearRootFinderClassInfo;
const Ionflux::ObjectBase::IFClassInfo* BrentLinearRootFinder::CLASS_INFO = &BrentLinearRootFinder::brentLinearRootFinderClassInfo;

BrentLinearRootFinder::BrentLinearRootFinder()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

BrentLinearRootFinder::BrentLinearRootFinder(const Ionflux::Mapping::BrentLinearRootFinder& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

BrentLinearRootFinder::~BrentLinearRootFinder()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
BrentLinearRootFinder::findRoot(Ionflux::Mapping::MappingValue a, 
Ionflux::Mapping::MappingValue b, Ionflux::Mapping::MappingValue delta) 
const
{
	// TODO: Implementation.
	return findRoot(a, b, delta, 0.01);
}

Ionflux::Mapping::MappingValue 
BrentLinearRootFinder::findRoot(Ionflux::Mapping::MappingValue a, 
Ionflux::Mapping::MappingValue b, Ionflux::Mapping::MappingValue delta, 
Ionflux::Mapping::MappingValue tr0, unsigned int samples, unsigned int 
maxIters, unsigned int i, bool forceBisection, 
Ionflux::Mapping::MappingValue bPrev) const
{
	/* <---- DEBUG ----- //
	ostringstream message;
	// <---- DEBUG ----- */
	if (i == 0)
	    bPrev = b;
	if (i > maxIters)
	    throw MappingError("Could not find a root with the specified " 
	        "error and maximum iterations.");
	if (compareSigns(a, b) == 0)
	{
	    /* <---- DEBUG ----- //
	    log(IFLogMessage("Start interval edge values must have opposite "
	        "signs. Trying to find a suitable interval.", VL_DEBUG, 
	        this, "findRoot"));
	    // <---- DEBUG ----- */
	    Range r0 = findStartInterval(samples, a, b);
	    a = r0.lower;
	    b = r0.upper;
	}
	Ionflux::Mapping::MappingValue fa = (*func)(a);
	Ionflux::Mapping::MappingValue fb = (*func)(b);
	if (fa == 0.)
	    return a;
	if (fb == 0.)
	    return b;
	Ionflux::Mapping::MappingValue c;
	if (fabs(fa) < fabs(fb))
	{
	    c = a;
	    a = b;
	    b = c;
	}
	if (fabs(fb) <= delta)
	    return b;
	Ionflux::Mapping::MappingValue m = 0.5 * (a + b);
	bool bisection = false;
	Ionflux::Mapping::MappingValue s = (a - b) / (fb - fa) * fa + a;
	Ionflux::Mapping::MappingValue t = (s - b) / (m - b);
	Ionflux::Mapping::MappingValue bn;
	if (forceBisection)
	{
	    bn = m;
	    bisection = true;
	} else 
	{
	    if ((t > 0.) && (t < 1.))
	        bn = s;
	    else
	    {
	        bn = m;
	        bisection = true;
	    }
	}
	Ionflux::Mapping::MappingValue fbn = (*func)(bn);
	Ionflux::Mapping::MappingValue an;
	if (compareSigns(a, bn) != 0)
	    an = a;
	else
	    an = b;
	Ionflux::Mapping::MappingValue fan = (*func)(an);
	if (bisection)
	{
	    if ((tr0 >= fabs(bn - b)) 
	        || (fabs(s - bn) >= 0.5 * fabs(bn - b)))
	        forceBisection = true;
	} else
	{
	    if ((tr0 >= fabs(b - bPrev)) 
	        || (fabs(s - bn) >= 0.5 * fabs(b - bPrev)))
	        forceBisection = true;
	}
	if (compareSigns(an, bn) == 0)
	{
	    ostringstream message;
	    message << "Edge values for next iteration must have " 
	        "different signs. (an = " << an << ", bn = " << bn 
	        << ", fan = " << fan << ", fbn = " << fbn 
	        << ", a = " << a << ", b = " << b << ", fa = " << fa 
	        << ", fb = " << fb << ", m = " << m << ", s = " << s 
	        << ", t = " << t << ")";
	    throw MappingError(message.str());
	}
	/* <---- DEBUG ----- //
	message.str("");
	message << "an = " << an << ", bn = " << bn 
	    << ", fan = " << fan << ", fbn = " << fbn 
	    << ", a = " << a << ", b = " << b << ", fa = " << fa 
	    << ", fb = " << fb << ", m = " << m << ", s = " << s 
	    << ", t = " << t;
	// <---- DEBUG ----- */
	return findRoot(an, bn, delta, tr0, samples, maxIters, i + 1, forceBisection, b);
}

std::string BrentLinearRootFinder::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

Ionflux::Mapping::BrentLinearRootFinder& 
BrentLinearRootFinder::operator=(const 
Ionflux::Mapping::BrentLinearRootFinder& other)
{
	return *this;
}

Ionflux::Mapping::BrentLinearRootFinder* BrentLinearRootFinder::copy() 
const
{
    BrentLinearRootFinder* newBrentLinearRootFinder = create();
    *newBrentLinearRootFinder = *this;
    return newBrentLinearRootFinder;
}

Ionflux::Mapping::BrentLinearRootFinder* 
BrentLinearRootFinder::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<BrentLinearRootFinder*>(other);
}

Ionflux::Mapping::BrentLinearRootFinder* 
BrentLinearRootFinder::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    BrentLinearRootFinder* newObject = new BrentLinearRootFinder();
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

/** \file BrentLinearRootFinder.cpp
 * \brief Brent linear root finder implementation.
 */
