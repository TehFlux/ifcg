/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * GeoUtilsError.cpp               GeoUtils error (implementation).
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

#include "geoutils/GeoUtilsError.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

GeoUtilsError::GeoUtilsError()
{
	// TODO: Nothing ATM. ;-)
}

GeoUtilsError::GeoUtilsError(const Ionflux::GeoUtils::GeoUtilsError& other)
{
	*this = other;
}

GeoUtilsError::GeoUtilsError(const std::string& initReason)
: reason(initReason)
{
	// TODO: Nothing ATM. ;-)
}

GeoUtilsError::~GeoUtilsError() throw()
{
	// TODO: Nothing ATM. ;-)
}

std::string GeoUtilsError::getString() const
{
	ostringstream state;
	state << "GeoUtilsError[" << reason << "]";
	return state.str();
}

const char* GeoUtilsError::what() const throw()
{
	// TODO: Implementation.
	return reason.c_str();
}

void GeoUtilsError::setReason(const std::string& newReason)
{
	reason = newReason;
}

std::string GeoUtilsError::getReason() const
{
    return reason;
}

Ionflux::GeoUtils::GeoUtilsError& GeoUtilsError::operator=(const 
Ionflux::GeoUtils::GeoUtilsError& other)
{
if (this == &other)
    return *this;
setReason(other.getReason());
	return *this;
}

Ionflux::GeoUtils::GeoUtilsError* GeoUtilsError::copy() const
{
    GeoUtilsError* newGeoUtilsError = 
        new GeoUtilsError();
    *newGeoUtilsError = *this;
    return newGeoUtilsError;
}

}

}

/** \file GeoUtilsError.cpp
 * \brief GeoUtils error implementation.
 */
