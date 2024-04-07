/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * AltjiraError.cpp                Altjira error (implementation).
 * =========================================================================
 * 
 * This file is part of Altjira - Ionflux' Image Processing Library.
 * 
 * Altjira - Ionflux' Image Processing Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
 * 
 * Altjira - Ionflux' Image Processing Library is distributed in the hope 
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Altjira - Ionflux' Image Processing Library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "altjira/AltjiraError.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

namespace Ionflux
{

namespace Altjira
{

AltjiraError::AltjiraError()
{
	// TODO: Nothing ATM. ;-)
}

AltjiraError::AltjiraError(const Ionflux::Altjira::AltjiraError& other)
{
	*this = other;
}

AltjiraError::AltjiraError(const std::string& initReason)
: reason(initReason)
{
	// TODO: Nothing ATM. ;-)
}

AltjiraError::~AltjiraError() throw()
{
	// TODO: Nothing ATM. ;-)
}

std::string AltjiraError::getString() const
{
	ostringstream state;
	state << "AltjiraError[" << reason << "]";
	return state.str();
}

const char* AltjiraError::what() const throw()
{
	// TODO: Implementation.
	return reason.c_str();
}

void AltjiraError::setReason(const std::string& newReason)
{
	reason = newReason;
}

std::string AltjiraError::getReason() const
{
    return reason;
}

Ionflux::Altjira::AltjiraError& AltjiraError::operator=(const 
Ionflux::Altjira::AltjiraError& other)
{
if (this == &other)
    return *this;
setReason(other.getReason());
	return *this;
}

Ionflux::Altjira::AltjiraError* AltjiraError::copy() const
{
    AltjiraError* newAltjiraError = 
        new AltjiraError();
    *newAltjiraError = *this;
    return newAltjiraError;
}

}

}

/** \file AltjiraError.cpp
 * \brief Altjira error implementation.
 */
