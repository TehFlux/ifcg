#ifndef IONFLUX_MAPPING_CONSTANTS
#define IONFLUX_MAPPING_CONSTANTS
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2009 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * constants.hpp                     Constants (header).
 * =========================================================================
 *
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFMapping - Ionflux Mapping Library is distributed in the hope 
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFMapping - Ionflux Mapping Library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include <string>
#include "ifmapping/types.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Coordinate ID: X.
const Ionflux::Mapping::CoordinateID C_X = 0;
/// Coordinate ID: Y.
const Ionflux::Mapping::CoordinateID C_Y = 1;
/// Coordinate ID: Z.
const Ionflux::Mapping::CoordinateID C_Z = 2;

/// Default clamp range.
const Ionflux::Mapping::Range DEFAULT_CLAMP_RANGE = { 0., 1. };

/// Default maximum number of iterations.
const unsigned int MAX_ITERATIONS = 10000;

/// Default tolerance.
const Ionflux::Mapping::MappingValue DEFAULT_TOLERANCE = 1e-6;

}

}

/** \file constants.hpp
 * \brief Constants (header).
 */
#endif
