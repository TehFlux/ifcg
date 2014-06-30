/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * LinearInterpolator.cpp          Linear interpolator (implementation).
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

#include "geoutils/LinearInterpolator.hpp"
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

LinearInterpolatorClassInfo::LinearInterpolatorClassInfo()
{
	name = "LinearInterpolator";
	desc = "Linear interpolator";
}

LinearInterpolatorClassInfo::~LinearInterpolatorClassInfo()
{
}

// run-time type information instance constants
const LinearInterpolatorClassInfo LinearInterpolator::linearInterpolatorClassInfo;
const Ionflux::ObjectBase::IFClassInfo* LinearInterpolator::CLASS_INFO = &LinearInterpolator::linearInterpolatorClassInfo;

LinearInterpolator::LinearInterpolator()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

LinearInterpolator::LinearInterpolator(const Ionflux::GeoUtils::LinearInterpolator& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

LinearInterpolator::LinearInterpolator(double initV0, double initV1)
: Interpolator(v0, v1)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

LinearInterpolator::LinearInterpolator(const 
Ionflux::ObjectBase::DoubleVector& initValues)
: Interpolator(initValues)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

LinearInterpolator::~LinearInterpolator()
{
	// TODO: Nothing ATM. ;-)
}

double LinearInterpolator::interpolate(double t) const
{
	// TODO: Implementation.
	return (v1 - v0) * t + v0;
}

Ionflux::GeoUtils::LinearInterpolator& LinearInterpolator::operator=(const 
Ionflux::GeoUtils::LinearInterpolator& other)
{
    v0 = other.v0;
    v1 = other.v1;
	return *this;
}

Ionflux::GeoUtils::LinearInterpolator* LinearInterpolator::copy() const
{
    LinearInterpolator* newLinearInterpolator = create();
    *newLinearInterpolator = *this;
    return newLinearInterpolator;
}

Ionflux::GeoUtils::LinearInterpolator* 
LinearInterpolator::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<LinearInterpolator*>(other);
}

Ionflux::GeoUtils::LinearInterpolator* 
LinearInterpolator::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    LinearInterpolator* newObject = new LinearInterpolator();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::LinearInterpolator* LinearInterpolator::create(double 
initV0, double initV1, Ionflux::ObjectBase::IFObject* parentObject)
{
    LinearInterpolator* newObject = new LinearInterpolator(initV0, initV1);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::LinearInterpolator* LinearInterpolator::create(const 
Ionflux::ObjectBase::DoubleVector& initValues, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    LinearInterpolator* newObject = new LinearInterpolator(initValues);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int LinearInterpolator::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file LinearInterpolator.cpp
 * \brief Linear interpolator implementation.
 */
