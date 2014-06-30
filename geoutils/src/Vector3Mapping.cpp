/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector3Mapping.cpp              Vector mapping (3 elements) 
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

#include "geoutils/Vector3Mapping.hpp"
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

Vector3MappingClassInfo::Vector3MappingClassInfo()
{
	name = "Vector3Mapping";
	desc = "Vector mapping (3 elements)";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

Vector3MappingClassInfo::~Vector3MappingClassInfo()
{
}

// run-time type information instance constants
const Vector3MappingClassInfo Vector3Mapping::vector3MappingClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Vector3Mapping::CLASS_INFO = &Vector3Mapping::vector3MappingClassInfo;

Vector3Mapping::Vector3Mapping()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Vector3Mapping::Vector3Mapping(const Ionflux::GeoUtils::Mapping::Vector3Mapping& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Vector3Mapping::~Vector3Mapping()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::GeoUtils::Vector3 
Vector3Mapping::operator()(Ionflux::Mapping::MappingValue value) const
{
	// TODO: Implementation.
	return call(value);;
}

std::string Vector3Mapping::getString() const
{
	ostringstream status;
	status << getClassName();
	return status.str();
}

Ionflux::GeoUtils::Mapping::Vector3Mapping& Vector3Mapping::operator=(const
Ionflux::GeoUtils::Mapping::Vector3Mapping& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::GeoUtils::Mapping::Vector3Mapping* 
Vector3Mapping::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Vector3Mapping*>(other);
}

unsigned int Vector3Mapping::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file Vector3Mapping.cpp
 * \brief Vector mapping (3 elements) implementation.
 */
