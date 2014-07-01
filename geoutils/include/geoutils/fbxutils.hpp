#ifndef IONFLUX_GEOUTILS_FBX_UTILS
#define IONFLUX_GEOUTILS_FBX_UTILS
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * fbxutils.hpp                FBX utility functions.
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

#include <string>
#include "geoutils/fbxtypes.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Get a string representation for a node attribute type.
std::string getFBXNodeAttributeTypeString(
    Ionflux::GeoUtils::FBXNodeAttributeType attrType);

}

}

/** \file fbxutils.hpp
 * \brief FBX utility functions (header).
 */
#endif
