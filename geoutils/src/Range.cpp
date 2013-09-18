/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Range.cpp                       Range of values (implementation).
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

#include "geoutils/Range.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

RangeClassInfo::RangeClassInfo()
{
	name = "Range";
	desc = "Range of values";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

RangeClassInfo::~RangeClassInfo()
{
}

// run-time type information instance constants
const RangeClassInfo Range::rangeClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Range::CLASS_INFO = &Range::rangeClassInfo;

Range::Range()
: rMin(0.), rMax(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Range::Range(const Ionflux::GeoUtils::Range& other)
: rMin(0.), rMax(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Range::Range(double initRMin, double initRMax)
: rMin(initRMin), rMax(initRMax)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Range::~Range()
{
	// TODO: Nothing ATM. ;-)
}

void Range::extend(double value)
{
	if (value < rMin)
	    rMin = value;
	if (value > rMax)
	    rMax = value;
}

double Range::getCenter() const
{
	// TODO: Implementation.
	return 0.5 * (rMin + rMax);
}

double Range::getRadius() const
{
	// TODO: Implementation.
	return 0.5 * (rMax - rMin);
}

double Range::getExtent() const
{
	// TODO: Implementation.
	return rMax - rMin;
}

double Range::getValue(double s) const
{
	// TODO: Implementation.
	return rMin + (rMax - rMin) * s;
}

double Range::clamp(double value) const
{
	if (value < rMin)
	    return rMin;
	if (value > rMax)
	    return rMax;
	return value;
}

double Range::getClampedValue(double s) const
{
	// TODO: Implementation.
	return clamp(getValue(s));
}

Ionflux::GeoUtils::RangeCompResult Range::compare(const 
Ionflux::GeoUtils::Range& other, double t) const
{
	if (eq(rMin, other.rMin, t) && eq(rMax, other.rMax, t))
	    return RANGE_EQUAL;
	if (lt(rMax, other.rMin, t) || gt(rMin, other.rMax, t))
	    return RANGE_DISJOINT;
	if (ltOrEq(other.rMin, rMin, t) && gtOrEq(other.rMax, rMax, t))
	    return RANGE_OTHER_CONTAINS;
	if (ltOrEq(rMin, other.rMin, t) && gtOrEq(rMax, other.rMax, t))
	    return RANGE_FIRST_CONTAINS;
	return RANGE_OVERLAP;
}

bool Range::isInRange(double v, double t) const
{
	if (lt(v, rMin, t) || gt(v, rMax, t))
	    return false;
	return true;
}

void Range::setBounds(double rMinNew, double rMaxNew)
{
	rMin = rMinNew;
	rMax = rMaxNew;
}

bool Range::operator==(const Ionflux::GeoUtils::Range& other) const
{
	if (!((rMin == other.rMin) && (rMax == other.rMax)))
	        return false;
	return true;
}

bool Range::operator!=(const Ionflux::GeoUtils::Range& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

std::string Range::getString() const
{
	ostringstream state;
	state << getClassName() << "[" << rMin 
	    << ", " << rMax << "]";
	return state.str();
}

void Range::setRMin(double newRMin)
{
	rMin = newRMin;
}

double Range::getRMin() const
{
    return rMin;
}

void Range::setRMax(double newRMax)
{
	rMax = newRMax;
}

double Range::getRMax() const
{
    return rMax;
}

void Range::setBounds(const Ionflux::ObjectBase::DoubleVector& newBounds)
{
	if (newBounds.size() < 2)
	    throw GeoUtilsError("Not enough elements in bounds vector!");
	rMin = newBounds[0];
	rMax = newBounds[1];
}

Ionflux::ObjectBase::DoubleVector Range::getBounds() const
{
	DoubleVector result;
	result.push_back(rMin);
	result.push_back(rMax);
	return result;
}

Ionflux::GeoUtils::Range& Range::operator=(const Ionflux::GeoUtils::Range& 
other)
{
if (this == &other)
    return *this;
setRMin(other.getRMin());
setRMax(other.getRMax());
	return *this;
}

Ionflux::GeoUtils::Range* Range::copy() const
{
    Range* newRange = create();
    *newRange = *this;
    return newRange;
}

Ionflux::GeoUtils::Range* Range::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Range*>(other);
}

Ionflux::GeoUtils::Range* Range::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Range* newObject = new Range();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file Range.cpp
 * \brief Range of values implementation.
 */
