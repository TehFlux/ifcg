/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Interpolator.cpp                Interpolator (implementation).
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

#include "geoutils/Interpolator.hpp"
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

InterpolatorClassInfo::InterpolatorClassInfo()
{
	name = "Interpolator";
	desc = "Interpolator";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

InterpolatorClassInfo::~InterpolatorClassInfo()
{
}

// run-time type information instance constants
const InterpolatorClassInfo Interpolator::interpolatorClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Interpolator::CLASS_INFO = &Interpolator::interpolatorClassInfo;

Interpolator::Interpolator()
: v0(0.), v1(1.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Interpolator::Interpolator(const Ionflux::GeoUtils::Interpolator& other)
: v0(0.), v1(1.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Interpolator::Interpolator(double initV0, double initV1)
: v0(initV0), v1(initV1)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Interpolator::Interpolator(const Ionflux::ObjectBase::DoubleVector& 
initValues)
: v0(0), v1(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setValues(initValues);
}

Interpolator::~Interpolator()
{
	// TODO: Nothing ATM. ;-)
}

void Interpolator::setValues(double newV0, double newV1)
{
	v0 = newV0;
	v1 = newV1;
}

void Interpolator::setValues(const Ionflux::ObjectBase::DoubleVector& 
newValues)
{
	if (newValues.size() == 0)
	    return;
	if (newValues.size() >= 2)
	    v1 = newValues[1];
	v0 = newValues[0];
}

void Interpolator::getValues(Ionflux::ObjectBase::DoubleVector& target) 
const
{
	target.clear();
	target.push_back(v0);
	target.push_back(v1);
}

double Interpolator::getValue(int index) const
{
	// TODO: Implementation.
	return (*this)[index];;
}

Ionflux::ObjectBase::DoubleVector Interpolator::getVector() const
{
	DoubleVector result;
	result.push_back(v0);
	result.push_back(v1);
	return result;
}

void Interpolator::setValue(int index, int value)
{
	if ((index < 0) || (index > 2))
	{
	    ostringstream message;
	    message << "Index out of range: " << index;
	    throw GeoUtilsError(message.str());
	}
	if (index == 0)
	    v0 = value;
	else 
	if (index == 1)
	    v1 = value;
}

bool Interpolator::operator==(const Ionflux::GeoUtils::Interpolator& other)
const
{
	if (!((v0 == other.v0) && (v1 == other.v1)))
	        return false;
	return true;
}

bool Interpolator::operator!=(const Ionflux::GeoUtils::Interpolator& other)
const
{
	// TODO: Implementation.
	return !(*this == other);;
}

double Interpolator::operator[](int index) const
{
	if ((index < 0) || (index > 2))
	{
	    ostringstream message;
	    message << "Index out of range: " << index;
	    throw GeoUtilsError(message.str());
	}
	double result = 0.;
	if (index == 0)
	    result = v0;
	if (index == 1)
	    result = v1;
	return result;
}

double Interpolator::operator()(double t) const
{
	// TODO: Implementation.
	return interpolate(t);
}

std::string Interpolator::getString() const
{
	ostringstream state;
	state << getClassName() << "[" << v0 << ", " << v1 << "]";
	return state.str();
}

void Interpolator::setV0(double newV0)
{
	v0 = newV0;
}

double Interpolator::getV0() const
{
	return v0;
}

void Interpolator::setV1(double newV1)
{
	v1 = newV1;
}

double Interpolator::getV1() const
{
	return v1;
}

Ionflux::GeoUtils::Interpolator& Interpolator::operator=(const 
Ionflux::GeoUtils::Interpolator& other)
{
setV0(other.getV0());
setV1(other.getV1());
	return *this;
}

}

}

/** \file Interpolator.cpp
 * \brief Interpolator implementation.
 */
