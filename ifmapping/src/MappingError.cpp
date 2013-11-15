/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * MappingError.cpp                Mapping error (implementation).
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

#include "ifmapping/MappingError.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

namespace Ionflux
{

namespace Mapping
{

MappingError::MappingError()
{
	// TODO: Nothing ATM. ;-)
}

MappingError::MappingError(const Ionflux::Mapping::MappingError& other)
{
	*this = other;
}

MappingError::MappingError(const std::string& initReason)
: reason(initReason)
{
	// TODO: Nothing ATM. ;-)
}

MappingError::~MappingError() throw()
{
	// TODO: Nothing ATM. ;-)
}

std::string MappingError::getString() const
{
	ostringstream state;
	state << "MappingError[" << reason << "]";
	return state.str();
}

const char* MappingError::what() const throw()
{
	// TODO: Implementation.
	return reason.c_str();
}

void MappingError::setReason(const std::string& newReason)
{
	reason = newReason;
}

std::string MappingError::getReason() const
{
    return reason;
}

Ionflux::Mapping::MappingError& MappingError::operator=(const 
Ionflux::Mapping::MappingError& other)
{
if (this == &other)
    return *this;
setReason(other.getReason());
	return *this;
}

Ionflux::Mapping::MappingError* MappingError::copy() const
{
    MappingError* newMappingError = 
        new MappingError();
    *newMappingError = *this;
    return newMappingError;
}

}

}

/** \file MappingError.cpp
 * \brief Mapping error implementation.
 */
