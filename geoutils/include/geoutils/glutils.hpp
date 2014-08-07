#ifndef IONFLUX_GEOUTILS_OPENGL_UTILS
#define IONFLUX_GEOUTILS_OPENGL_UTILS
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * glutils.hpp                     OpenGL utility functions (header).
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
#include "geoutils/gltypes.hpp"
#include "geoutils/glconstants.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/** Get string representation for OpenGL profile.
 *
 * Get a string representation for an OpenGL profile.
 *
 * \param profile OpenGL profile ID.
 *
 * \return String representation.
 */
std::string getOpenGLProfileString(
    Ionflux::GeoUtils::OpenGLProfileID profile);

/** Get OpenGL profile ID.
 *
 * Get an OpenGL profile ID for the specified GLFW OpenGL profile.
 *
 * \param profile GLFW OpenGL profile.
 *
 * \return OpenGL profile ID.
 */
Ionflux::GeoUtils::OpenGLProfileID getOpenGLProfileFromGLFW(int profile);

/** Get OpenGL profile ID (GLFW).
 *
 * Get a GLFW OpenGL profile for the specified OpenGL profile ID.
 *
 * \param profile OpenGL profile ID.
 *
 * \return GLFW OpenGL profile.
 */
int getOpenGLProfileGLFW(Ionflux::GeoUtils::OpenGLProfileID profile);

/** Get data type string.
 *
 * Get a string representation for a vertex attribute data type ID.
 *
 * \param dataType data type.
 *
 * \return String representation.
 */
std::string getDataTypeString(Ionflux::GeoUtils::DataTypeID dataType);

/** Get number of elements per primitive.
 *
 * Get the number of elements per primitive of the specified type.
 *
 * \param primitive Primitive ID.
 *
 * \return Number of elements per primitive.
 */
unsigned int getNumElementsPerPrimitive(
    Ionflux::GeoUtils::PrimitiveID primitive);

/** Enable OpenGL backface culling.
 *
 * Enable OpenGL backface culling.
 *
 * \param enable enable flag
 */
void enableOpenGLBackFaceCulling(bool enable = true);

/** Enable OpenGL depth buffer test.
 *
 * Enable OpenGL depth buffer test.
 *
 * \param enable enable flag
 */
void enableOpenGLDepthBufferTest(bool enable = true);

}

}

/** \file glutils.hpp
 * \brief OpenGL utility functions (header).
 */
#endif
