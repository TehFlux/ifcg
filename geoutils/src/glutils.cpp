/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * glutils.cpp                     OpenGL utility functions.
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
#include <sstream>
#include "geoutils/glutils.hpp"
#include "geoutils/glutils_private.hpp"
#include "geoutils/GeoUtilsError.hpp"

namespace Ionflux
{

namespace GeoUtils
{

std::string getOpenGLProfileString(
    Ionflux::GeoUtils::OpenGLProfileID profile)
{
	if (profile == OPENGL_PROFILE_ANY)
	    return "any";
	if (profile == OPENGL_PROFILE_CORE)
	    return "core";
	if (profile == OPENGL_PROFILE_COMPAT)
	    return "compat";
	return "<unknown>";
}

Ionflux::GeoUtils::OpenGLProfileID getOpenGLProfileFromGLFW(int profile)
{
	if (profile == GLFW_OPENGL_ANY_PROFILE)
	    return OPENGL_PROFILE_ANY;
	if (profile == GLFW_OPENGL_CORE_PROFILE)
	    return OPENGL_PROFILE_CORE;
	if (profile == GLFW_OPENGL_COMPAT_PROFILE)
	    return OPENGL_PROFILE_COMPAT;
	return OPENGL_PROFILE_ANY;
}

int getOpenGLProfileGLFW(Ionflux::GeoUtils::OpenGLProfileID profile)
{
	if (profile == OPENGL_PROFILE_ANY)
	    return GLFW_OPENGL_ANY_PROFILE;
	if (profile == OPENGL_PROFILE_CORE)
	    return GLFW_OPENGL_CORE_PROFILE;
	if (profile == OPENGL_PROFILE_COMPAT)
	    return GLFW_OPENGL_COMPAT_PROFILE;
	return GLFW_OPENGL_ANY_PROFILE;
}

std::string getDataTypeString(Ionflux::GeoUtils::DataTypeID dataType)
{
	if (dataType == DATA_TYPE_FLOAT)
	    return "float";
	if (dataType == DATA_TYPE_UINT)
	    return "uint";
	return "<unknown>";
}

unsigned int getNumElementsPerPrimitive(
    Ionflux::GeoUtils::PrimitiveID primitive)
{
	if (primitive == PRIMITIVE_POINT)
	    return 1;
	if (primitive == PRIMITIVE_LINE)
	    return 2;
	if (primitive == PRIMITIVE_TRIANGLE)
	    return 3;
	std::ostringstream status;
	status << "[getNumElementsPerPrimitive] "
	    "Invalid primitive ID: " << primitive;
	throw GeoUtilsError(status.str());
	return 0;
}

GLenum getOpenGLBufferUsage(Ionflux::GeoUtils::BufferUsageID usage)
{
	if (usage == USAGE_STREAM_DRAW)
	    return GL_STREAM_DRAW;
	if (usage == USAGE_STREAM_READ)
	    return GL_STREAM_READ;
	if (usage == USAGE_STREAM_COPY)
	    return GL_STREAM_COPY;
	if (usage == USAGE_STATIC_DRAW)
	    return GL_STATIC_DRAW;
	if (usage == USAGE_STATIC_READ)
	    return GL_STATIC_READ;
	if (usage == USAGE_STATIC_COPY)
	    return GL_STATIC_COPY;
	if (usage == USAGE_DYNAMIC_DRAW)
	    return GL_DYNAMIC_DRAW;
	if (usage == USAGE_DYNAMIC_READ)
	    return GL_DYNAMIC_READ;
	if (usage == USAGE_DYNAMIC_COPY)
	    return GL_DYNAMIC_COPY;
	std::ostringstream status;
	status << "[getOpenGLBufferUsage] "
	    "Invalid buffer usage ID: " << usage;
	throw GeoUtilsError(status.str());
	return 0;
}

GLenum getOpenGLDataType(Ionflux::GeoUtils::DataTypeID dataType)
{
	if (dataType == DATA_TYPE_FLOAT)
	    return GL_FLOAT;
	if (dataType == DATA_TYPE_UINT)
	    return GL_UNSIGNED_INT;
	std::ostringstream status;
	status << "[getOpenGLDataType] "
	    "Invalid vertex attribute data type ID: " << dataType;
	throw GeoUtilsError(status.str());
	return 0;
}

GLenum getOpenGLPrimitive(Ionflux::GeoUtils::PrimitiveID primitive)
{
	if (primitive == PRIMITIVE_POINT)
	    return GL_POINTS;
	if (primitive == PRIMITIVE_LINE)
	    return GL_LINES;
	if (primitive == PRIMITIVE_TRIANGLE)
	    return GL_TRIANGLES;
	std::ostringstream status;
	status << "[getOpenGLPrimitive] "
	    "Invalid primitive ID: " << primitive;
	throw GeoUtilsError(status.str());
	return 0;
}

}

}

/** \file glutils.cpp
 * \brief OpenGL utility functions.
 */
