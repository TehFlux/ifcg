#ifndef IONFLUX_GEOUTILS_GL_TYPES
#define IONFLUX_GEOUTILS_GL_TYPES
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * gltypes.hpp                     GL types.
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
#include <vector>

struct GLFWwindow;

namespace Ionflux
{

namespace GeoUtils
{

/// OpenGL data type ID.
typedef int DataTypeID;

/// OpenGL buffer usage ID.
typedef int BufferUsageID;

/// OpenGL primitive ID.
typedef int PrimitiveID;

/// OpenGL profile ID.
typedef int OpenGLProfileID;

class VertexAttribute;

/// Vector of vertex attributes.
typedef std::vector<Ionflux::GeoUtils::VertexAttribute*> 
    VertexAttributeVector;

/// Viewer event type ID.
typedef int ViewerEventTypeID;

class ViewerEvent;

/// Vector of viewer events.
typedef std::vector<Ionflux::GeoUtils::ViewerEvent*> ViewerEventVector;

/// Vertex attribute type ID.
typedef int VertexAttributeTypeID;

}

}

/** \file gltypes.hpp
 * \brief GL types (header).
 */
#endif
