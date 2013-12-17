/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PointMapping.cpp                Point mapping (implementation).
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

#include "ifmapping/PointMapping.hpp"
#include <sstream>
#include "ifmapping/utils.hpp"
#include "ifmapping/PointCoord.hpp"
#include "ifmapping/ArcLength.hpp"
#include "ifmapping/BrentLinearRootFinder.hpp"
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

PointMappingClassInfo::PointMappingClassInfo()
{
	name = "PointMapping";
	desc = "Point mapping";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

PointMappingClassInfo::~PointMappingClassInfo()
{
}

// public member constants
const Ionflux::Mapping::MappingValue PointMapping::DEFAULT_PRECISION = 1e-5;
const Ionflux::Mapping::MappingValue PointMapping::DEFAULT_RELATIVE_ERROR = 1e-4;
const unsigned int PointMapping::DEFAULT_MAX_NUM_ITERATIONS = 14;

// run-time type information instance constants
const PointMappingClassInfo PointMapping::pointMappingClassInfo;
const Ionflux::ObjectBase::IFClassInfo* PointMapping::CLASS_INFO = &PointMapping::pointMappingClassInfo;

PointMapping::PointMapping()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

PointMapping::~PointMapping()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
PointMapping::getParamCoord(Ionflux::Mapping::MappingValue value, 
Ionflux::Mapping::CoordinateID coord, Ionflux::Mapping::MappingValue 
precision)
{
	Ionflux::Mapping::PointCoord* fc = 
	    Ionflux::Mapping::PointCoord::create(this, coord, -value);
	Ionflux::Mapping::BrentLinearRootFinder rf;
	rf.setFunc(fc);
	Ionflux::Mapping::MappingValue t = rf(0. - precision, 
	    1. + precision, precision);
	return t;
}

Ionflux::Mapping::Point 
PointMapping::evalCoord(Ionflux::Mapping::MappingValue value, 
Ionflux::Mapping::CoordinateID coord, Ionflux::Mapping::MappingValue 
precision)
{
	Ionflux::Mapping::MappingValue t = getParamCoord(
	    value, coord, precision);
	return call(t);
}

Ionflux::Mapping::MappingValue 
PointMapping::getParamArcLength(Ionflux::Mapping::MappingValue value, 
Ionflux::Mapping::MappingValue relativeError, 
Ionflux::Mapping::MappingValue maxNumIterations, 
Ionflux::Mapping::MappingValue precision)
{
	Ionflux::Mapping::ArcLength* fc = 
	    Ionflux::Mapping::ArcLength::create(
	        this, -value, 1., 0., relativeError, maxNumIterations);
	Ionflux::Mapping::BrentLinearRootFinder rf;
	rf.setFunc(fc);
	Ionflux::Mapping::MappingValue t = rf(0. - precision, 
	    1. + precision, precision);
	return t;
}

Ionflux::Mapping::Point 
PointMapping::evalArcLength(Ionflux::Mapping::MappingValue value, 
Ionflux::Mapping::MappingValue relativeError, 
Ionflux::Mapping::MappingValue maxNumIterations, 
Ionflux::Mapping::MappingValue precision)
{
	Ionflux::Mapping::MappingValue t = getParamArcLength(
	    value, relativeError, maxNumIterations, precision);
	return call(t);
}

Ionflux::Mapping::Point 
PointMapping::operator()(Ionflux::Mapping::MappingValue value)
{
	// TODO: Implementation.
	return call(value);;
}

Ionflux::Mapping::PointMapping* 
PointMapping::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<PointMapping*>(other);
}

}

}

/** \file PointMapping.cpp
 * \brief Point mapping implementation.
 */
