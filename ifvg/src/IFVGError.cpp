/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFVGError.cpp                   IFVG error (implementation).
 * ========================================================================== */

#include "ifvg/IFVGError.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

namespace Ionflux
{

namespace VolGfx
{

IFVGError::IFVGError()
{
	// TODO: Nothing ATM. ;-)
}

IFVGError::IFVGError(const Ionflux::VolGfx::IFVGError& other)
{
	*this = other;
}

IFVGError::IFVGError(const std::string& initReason)
: reason(initReason)
{
	// TODO: Nothing ATM. ;-)
}

IFVGError::~IFVGError() throw()
{
	// TODO: Nothing ATM. ;-)
}

std::string IFVGError::getString() const
{
	ostringstream state;
	state << "IFVGError[" << reason << "]";
	return state.str();
}

const char* IFVGError::what() const throw()
{
	// TODO: Implementation.
	return reason.c_str();
}

void IFVGError::setReason(const std::string& newReason)
{
	reason = newReason;
}

std::string IFVGError::getReason() const
{
    return reason;
}

Ionflux::VolGfx::IFVGError& IFVGError::operator=(const 
Ionflux::VolGfx::IFVGError& other)
{
if (this == &other)
    return *this;
setReason(other.getReason());
	return *this;
}

Ionflux::VolGfx::IFVGError* IFVGError::copy() const
{
    IFVGError* newIFVGError = 
        new IFVGError();
    *newIFVGError = *this;
    return newIFVGError;
}

}

}

/** \file IFVGError.cpp
 * \brief IFVG error implementation.
 */
