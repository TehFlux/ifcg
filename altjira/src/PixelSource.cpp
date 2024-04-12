/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PixelSource.cpp                 Pixel source (implementation).
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

#include "altjira/PixelSource.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "altjira/utils.hpp"

namespace Ionflux
{

namespace Altjira
{

PixelSourceClassInfo::PixelSourceClassInfo()
{
	name = "PixelSource";
	desc = "Pixel source";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

PixelSourceClassInfo::~PixelSourceClassInfo()
{
}

// run-time type information instance constants
const PixelSourceClassInfo PixelSource::pixelSourceClassInfo;
const Ionflux::ObjectBase::IFClassInfo* PixelSource::CLASS_INFO = &PixelSource::pixelSourceClassInfo;

PixelSource::PixelSource()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

PixelSource::PixelSource(const Ionflux::Altjira::PixelSource& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

PixelSource::~PixelSource()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Altjira::PixelSource& PixelSource::operator=(const 
Ionflux::Altjira::PixelSource& other)
{
    if (this == &other)
        return *this;
    return *this;
}

Ionflux::Altjira::PixelSource* 
PixelSource::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<PixelSource*>(other);
}

unsigned int PixelSource::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file PixelSource.cpp
 * \brief Pixel source implementation.
 */
