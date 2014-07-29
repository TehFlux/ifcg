#ifndef IONFLUX_GEOUTILS_OPENGL_CONSTANTS
#define IONFLUX_GEOUTILS_OPENGL_CONSTANTS
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * glconstants.hpp               Constant definitions (GeoUtils/GL).
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
#include <climits>
#include "geoutils/gltypes.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// OpenGL profile: any.
const Ionflux::GeoUtils::OpenGLProfileID OPENGL_PROFILE_ANY = 0;
/// OpenGL profile: core.
const Ionflux::GeoUtils::OpenGLProfileID OPENGL_PROFILE_CORE = 1;
/// OpenGL profile: compatibility.
const Ionflux::GeoUtils::OpenGLProfileID OPENGL_PROFILE_COMPAT = 2;

/// Data type ID: float.
const Ionflux::GeoUtils::DataTypeID DATA_TYPE_FLOAT = 0;
/// Data type ID: unsigned integer.
const Ionflux::GeoUtils::DataTypeID DATA_TYPE_UINT = 1;

/// OpenGL buffer usage ID: stream draw.
const Ionflux::GeoUtils::BufferUsageID USAGE_STREAM_DRAW = 0;
/// OpenGL buffer usage ID: stream read.
const Ionflux::GeoUtils::BufferUsageID USAGE_STREAM_READ = 1;
/// OpenGL buffer usage ID: stream copy.
const Ionflux::GeoUtils::BufferUsageID USAGE_STREAM_COPY = 2;
/// OpenGL buffer usage ID: static draw.
const Ionflux::GeoUtils::BufferUsageID USAGE_STATIC_DRAW = 3;
/// OpenGL buffer usage ID: static read.
const Ionflux::GeoUtils::BufferUsageID USAGE_STATIC_READ = 4;
/// OpenGL buffer usage ID: static copy.
const Ionflux::GeoUtils::BufferUsageID USAGE_STATIC_COPY = 5;
/// OpenGL buffer usage ID: dynamic draw.
const Ionflux::GeoUtils::BufferUsageID USAGE_DYNAMIC_DRAW = 6;
/// OpenGL buffer usage ID: dynamic read.
const Ionflux::GeoUtils::BufferUsageID USAGE_DYNAMIC_READ = 7;
/// OpenGL buffer usage ID: dynamic copy.
const Ionflux::GeoUtils::BufferUsageID USAGE_DYNAMIC_COPY = 8;

/// OpenGL primitive ID: point.
const Ionflux::GeoUtils::PrimitiveID PRIMITIVE_POINT = 0;
/// OpenGL primitive ID: line.
const Ionflux::GeoUtils::PrimitiveID PRIMITIVE_LINE = 1;
/// OpenGL primitive ID: triangle.
const Ionflux::GeoUtils::PrimitiveID PRIMITIVE_TRIANGLE = 2;

}

}

/** \file glconstants.hpp
 * \brief GeoUtils/GL constants (header).
 */
#endif
