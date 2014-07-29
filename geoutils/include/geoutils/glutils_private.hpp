#ifndef IONFLUX_GEOUTILS_OPENGL_UTILS_PRIVATE
#define IONFLUX_GEOUTILS_OPENGL_UTILS_PRIVATE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * glutils_private.hpp        OpenGL utility functions (private) (header).
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
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "geoutils/gltypes.hpp"
#include "geoutils/glconstants.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/** Get OpenGL buffer usage value.
 *
 * Get an OpenGL buffer usage value.
 *
 * \param usage OpenGL buffer usage ID.
 *
 * \return OpenGL buffer usage value.
 */
GLenum getOpenGLBufferUsage(Ionflux::GeoUtils::BufferUsageID usage);

/** Get OpenGL data type.
 *
 * Get an OpenGL data type.
 *
 * \param dataType OpenGL buffer usage ID.
 *
 * \return OpenGL buffer usage value.
 */
GLenum getOpenGLDataType(Ionflux::GeoUtils::DataTypeID dataType);

/** Get OpenGL primitive.
 *
 * Get an OpenGL primitive.
 *
 * \param primitive Primitive ID.
 *
 * \return OpenGL primitive.
 */
GLenum getOpenGLPrimitive(Ionflux::GeoUtils::PrimitiveID primitive);

}

}

/** \file glutils.hpp
 * \brief OpenGL utility functions (private) (header).
 */
#endif
