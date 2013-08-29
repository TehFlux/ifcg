/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * AcceptLength3.cpp               Vector mapping: Accept length 
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

#include "geoutils/AcceptLength3.hpp"
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

namespace Mapping
{

AcceptLength3ClassInfo::AcceptLength3ClassInfo()
{
	name = "AcceptLength3";
	desc = "Vector mapping: Accept length";
}

AcceptLength3ClassInfo::~AcceptLength3ClassInfo()
{
}

// public member constants
const Ionflux::GeoUtils::Range AcceptLength3::DEFAULT_LENGTH_RANGE = Ionflux::GeoUtils::Range(0., 1);

// run-time type information instance constants
const AcceptLength3ClassInfo AcceptLength3::acceptLength3ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* AcceptLength3::CLASS_INFO = &AcceptLength3::acceptLength3ClassInfo;

AcceptLength3::AcceptLength3()
: lengthRange(DEFAULT_LENGTH_RANGE)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

AcceptLength3::AcceptLength3(const Ionflux::GeoUtils::Mapping::AcceptLength3& other)
: lengthRange(DEFAULT_LENGTH_RANGE)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

AcceptLength3::AcceptLength3(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
initSource, const Ionflux::GeoUtils::Range& initLengthRange, 
Ionflux::Mapping::MappingValue initMaxIters)
: Accept3(initSource, initMaxIters), lengthRange(initLengthRange)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

AcceptLength3::~AcceptLength3()
{
	// TODO: Nothing ATM. ;-)
}

std::string AcceptLength3::getString() const
{
	ostringstream status;
	status << getClassName() << "[";
	if (source != 0)
	    status << source->getString();
	else
	    status << "<none>";
	status << ", " << maxIters << ", " << lengthRange << "]";
	return status.str();
}

bool AcceptLength3::checkCondition(const Ionflux::GeoUtils::Vector3& v) 
const
{
	if (!lengthRange.isInRange(v.norm()))
	    return false;
	return true;
}

void AcceptLength3::setLengthRange(const Ionflux::GeoUtils::Range& 
newLengthRange)
{
	lengthRange = newLengthRange;
}

Ionflux::GeoUtils::Range AcceptLength3::getLengthRange() const
{
	return lengthRange;
}

Ionflux::GeoUtils::Mapping::AcceptLength3& AcceptLength3::operator=(const 
Ionflux::GeoUtils::Mapping::AcceptLength3& other)
{
    Accept3::operator=(other);
    lengthRange = other.lengthRange;
	return *this;
}

Ionflux::GeoUtils::Mapping::AcceptLength3* AcceptLength3::copy() const
{
    AcceptLength3* newAcceptLength3 = create();
    *newAcceptLength3 = *this;
    return newAcceptLength3;
}

Ionflux::GeoUtils::Mapping::AcceptLength3* 
AcceptLength3::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<AcceptLength3*>(other);
}

Ionflux::GeoUtils::Mapping::AcceptLength3* 
AcceptLength3::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    AcceptLength3* newObject = new AcceptLength3();
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

}

/** \file AcceptLength3.cpp
 * \brief Vector mapping: Accept length implementation.
 */
