/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * DekkerRootFinder.cpp            Dekker root finder (implementation).
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

#include "ifmapping/DekkerRootFinder.hpp"
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

DekkerRootFinderClassInfo::DekkerRootFinderClassInfo()
{
	name = "DekkerRootFinder";
	desc = "Dekker root finder";
}

DekkerRootFinderClassInfo::~DekkerRootFinderClassInfo()
{
}

// run-time type information instance constants
const DekkerRootFinderClassInfo DekkerRootFinder::dekkerRootFinderClassInfo;
const Ionflux::ObjectBase::IFClassInfo* DekkerRootFinder::CLASS_INFO = &DekkerRootFinder::dekkerRootFinderClassInfo;

DekkerRootFinder::DekkerRootFinder()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

DekkerRootFinder::DekkerRootFinder(const Ionflux::Mapping::DekkerRootFinder& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

DekkerRootFinder::~DekkerRootFinder()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
DekkerRootFinder::findRoot(Ionflux::Mapping::MappingValue a, 
Ionflux::Mapping::MappingValue b, Ionflux::Mapping::MappingValue delta) 
const
{
	// TODO: Implementation.
	return findRoot(a, b, delta, 101);
}

Ionflux::Mapping::MappingValue 
DekkerRootFinder::findRoot(Ionflux::Mapping::MappingValue a, 
Ionflux::Mapping::MappingValue b, Ionflux::Mapping::MappingValue delta, 
unsigned int samples, unsigned int maxIters, unsigned int i) const
{
	/* <---- DEBUG ----- //
	ostringstream message;
	// <---- DEBUG ----- */
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
	Ionflux::Mapping::MappingValue m = 0.5 * (a + b);
	if (fabs(fb) <= delta)
	    return b;
	Ionflux::Mapping::MappingValue s = (a - b) / (fb - fa) * fa + a;
	Ionflux::Mapping::MappingValue t = (s - b) / (m - b);
	Ionflux::Mapping::MappingValue bn;
	if ((t > 0.) && (t < 1.))
	    bn = s;
	else
	    bn = m;
	Ionflux::Mapping::MappingValue fbn = (*func)(bn);
	Ionflux::Mapping::MappingValue an;
	if (compareSigns(a, bn) != 0)
	    an = a;
	else
	    an = b;
	Ionflux::Mapping::MappingValue fan = (*func)(an);
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
	return findRoot(an, bn, delta, samples, maxIters, i + 1);
}

std::string DekkerRootFinder::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

Ionflux::Mapping::DekkerRootFinder& DekkerRootFinder::operator=(const 
Ionflux::Mapping::DekkerRootFinder& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Mapping::DekkerRootFinder* DekkerRootFinder::copy() const
{
    DekkerRootFinder* newDekkerRootFinder = create();
    *newDekkerRootFinder = *this;
    return newDekkerRootFinder;
}

Ionflux::Mapping::DekkerRootFinder* 
DekkerRootFinder::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<DekkerRootFinder*>(other);
}

Ionflux::Mapping::DekkerRootFinder* 
DekkerRootFinder::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    DekkerRootFinder* newObject = new DekkerRootFinder();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int DekkerRootFinder::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file DekkerRootFinder.cpp
 * \brief Dekker root finder implementation.
 */
