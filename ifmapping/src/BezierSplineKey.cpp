/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BezierSplineKey.cpp             Bezier spline key (implementation).
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

#include "ifmapping/BezierSplineKey.hpp"
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

BezierSplineKeyClassInfo::BezierSplineKeyClassInfo()
{
	name = "BezierSplineKey";
	desc = "Bezier spline key";
}

BezierSplineKeyClassInfo::~BezierSplineKeyClassInfo()
{
}

// run-time type information instance constants
const BezierSplineKeyClassInfo BezierSplineKey::bezierSplineKeyClassInfo;
const Ionflux::ObjectBase::IFClassInfo* BezierSplineKey::CLASS_INFO = &BezierSplineKey::bezierSplineKeyClassInfo;

BezierSplineKey::BezierSplineKey()
: t(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

BezierSplineKey::BezierSplineKey(const Ionflux::Mapping::BezierSplineKey& other)
: t(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

BezierSplineKey::BezierSplineKey(Ionflux::Mapping::MappingValue initT)
: t(initT)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

BezierSplineKey::BezierSplineKey(const Ionflux::Mapping::BezierSpline& 
initSpline, Ionflux::Mapping::MappingValue initT)
: t(initT)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = initSpline;
}

BezierSplineKey::~BezierSplineKey()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::BezierSplineKey& BezierSplineKey::operator=(const 
Ionflux::Mapping::BezierSpline& other)
{
	BezierSpline::operator=(other);
	return *this;
}

std::string BezierSplineKey::getString() const
{
	ostringstream message;
	message << getClassName() << "[";
	bool e0 = true;
	for (BezierCurveVector::const_iterator i = segments.begin(); 
	    i != segments.end(); i++)
	{
	    if (!e0)
	        message << ", ";
	    else
	        e0 = false;
	    message << (*i)->getString();
	}
	message << "; " << t << "]";
	return message.str();
}

void BezierSplineKey::setT(Ionflux::Mapping::MappingValue newT)
{
	t = newT;
}

Ionflux::Mapping::MappingValue BezierSplineKey::getT() const
{
    return t;
}

Ionflux::Mapping::BezierSplineKey& BezierSplineKey::operator=(const 
Ionflux::Mapping::BezierSplineKey& other)
{
    BezierSpline::operator=(other);
    t = other.t;
    return *this;
}

Ionflux::Mapping::BezierSplineKey* BezierSplineKey::copy() const
{
    BezierSplineKey* newBezierSplineKey = create();
    *newBezierSplineKey = *this;
    return newBezierSplineKey;
}

Ionflux::Mapping::BezierSplineKey* 
BezierSplineKey::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<BezierSplineKey*>(other);
}

Ionflux::Mapping::BezierSplineKey* 
BezierSplineKey::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    BezierSplineKey* newObject = new BezierSplineKey();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int BezierSplineKey::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file BezierSplineKey.cpp
 * \brief Bezier spline key implementation.
 */
