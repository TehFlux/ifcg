/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polygon3Compare.cpp             Polygon comparison function object 
 * (implementation).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * GeoUtils - Ionflux' Geometry Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with GeoUtils - Ionflux' Geometry Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "geoutils/Polygon3Compare.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

Polygon3CompareClassInfo::Polygon3CompareClassInfo()
{
	name = "Polygon3Compare";
	desc = "Polygon comparison function object";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

Polygon3CompareClassInfo::~Polygon3CompareClassInfo()
{
}

// run-time type information instance constants
const Polygon3CompareClassInfo Polygon3Compare::polygon3CompareClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Polygon3Compare::CLASS_INFO = &Polygon3Compare::polygon3CompareClassInfo;

Polygon3Compare::Polygon3Compare()
: invert(false), target(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Polygon3Compare::Polygon3Compare(const Ionflux::GeoUtils::Polygon3Compare& other)
: invert(false), target(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Polygon3Compare::Polygon3Compare(bool initInvert, 
Ionflux::GeoUtils::Polygon3Compare* initTarget)
: invert(initInvert), target(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initTarget != 0)
	    setTarget(initTarget);
}

Polygon3Compare::~Polygon3Compare()
{
	// TODO: Nothing ATM. ;-)
}

std::string Polygon3Compare::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << invert << "]";
	return status.str();
}

bool Polygon3Compare::operator()(Ionflux::GeoUtils::Polygon3* p0, 
Ionflux::GeoUtils::Polygon3* p1)
{
	if (invert)
	    return !compare(*p0, *p1);
	return compare(*p0, *p1);
}

bool Polygon3Compare::compare(Ionflux::GeoUtils::Polygon3& p0, 
Ionflux::GeoUtils::Polygon3& p1)
{
	if (target != 0)
	    return (*target)(&p0, &p1);
	throw GeoUtilsError("Comparison not implemented and no target "
	    "function specified.");
	return false;
}

void Polygon3Compare::setInvert(bool newInvert)
{
	invert = newInvert;
}

bool Polygon3Compare::getInvert() const
{
    return invert;
}

void Polygon3Compare::setTarget(Ionflux::GeoUtils::Polygon3Compare* 
newTarget)
{
	target = newTarget;
}

Ionflux::GeoUtils::Polygon3Compare* Polygon3Compare::getTarget() const
{
    return target;
}

Ionflux::GeoUtils::Polygon3Compare& Polygon3Compare::operator=(const 
Ionflux::GeoUtils::Polygon3Compare& other)
{
    invert = other.invert;
    setTarget(other.target);
	return *this;
}

Ionflux::GeoUtils::Polygon3Compare* Polygon3Compare::copy() const
{
    Polygon3Compare* newPolygon3Compare = create();
    *newPolygon3Compare = *this;
    return newPolygon3Compare;
}

Ionflux::GeoUtils::Polygon3Compare* 
Polygon3Compare::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Polygon3Compare*>(other);
}

Ionflux::GeoUtils::Polygon3Compare* 
Polygon3Compare::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Polygon3Compare* newObject = new Polygon3Compare();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file Polygon3Compare.cpp
 * \brief Polygon comparison function object implementation.
 */
