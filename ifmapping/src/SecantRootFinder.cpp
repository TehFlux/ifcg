/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SecantRootFinder.cpp            Secant root finder (implementation).
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

#include "ifmapping/SecantRootFinder.hpp"
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

SecantRootFinderClassInfo::SecantRootFinderClassInfo()
{
	name = "SecantRootFinder";
	desc = "Secant root finder";
}

SecantRootFinderClassInfo::~SecantRootFinderClassInfo()
{
}

// run-time type information instance constants
const SecantRootFinderClassInfo SecantRootFinder::secantRootFinderClassInfo;
const Ionflux::ObjectBase::IFClassInfo* SecantRootFinder::CLASS_INFO = &SecantRootFinder::secantRootFinderClassInfo;

SecantRootFinder::SecantRootFinder()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

SecantRootFinder::SecantRootFinder(const Ionflux::Mapping::SecantRootFinder& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

SecantRootFinder::~SecantRootFinder()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
SecantRootFinder::findRoot(Ionflux::Mapping::MappingValue a, 
Ionflux::Mapping::MappingValue b, Ionflux::Mapping::MappingValue delta) 
const
{
	// TODO: Implementation.
	return findRoot(a, b, delta, 100, 0);
}

Ionflux::Mapping::MappingValue 
SecantRootFinder::findRoot(Ionflux::Mapping::MappingValue a, 
Ionflux::Mapping::MappingValue b, Ionflux::Mapping::MappingValue delta, 
unsigned int maxIters, unsigned int i) const
{
	if (i > maxIters)
	    throw MappingError("Could not find a root with the specified " 
	        "error and maximum iterations.");
	Ionflux::Mapping::MappingValue fa = (*func)(a);
	Ionflux::Mapping::MappingValue fb = (*func)(b);
	Ionflux::Mapping::MappingValue m = (a - b) / (fb - fa) * fa + a;
	if (fabs(fb) <= delta)
	    return m;
	if ((*func)(m) == 0.)
	    return m;
	return findRoot(b, m, delta, maxIters, i + 1);
}

std::string SecantRootFinder::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

Ionflux::Mapping::SecantRootFinder& SecantRootFinder::operator=(const 
Ionflux::Mapping::SecantRootFinder& other)
{
if (this == &other)
    return *this;
    return *this;
}

Ionflux::Mapping::SecantRootFinder* SecantRootFinder::copy() const
{
    SecantRootFinder* newSecantRootFinder = create();
    *newSecantRootFinder = *this;
    return newSecantRootFinder;
}

Ionflux::Mapping::SecantRootFinder* 
SecantRootFinder::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<SecantRootFinder*>(other);
}

Ionflux::Mapping::SecantRootFinder* 
SecantRootFinder::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    SecantRootFinder* newObject = new SecantRootFinder();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int SecantRootFinder::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file SecantRootFinder.cpp
 * \brief Secant root finder implementation.
 */
