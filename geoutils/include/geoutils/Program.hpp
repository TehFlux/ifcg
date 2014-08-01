#ifndef IONFLUX_GEOUTILS_PROGRAM
#define IONFLUX_GEOUTILS_PROGRAM
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Program.hpp                     Program (OpenGL) (header).
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

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "altjira/ColorSet.hpp"
#include "geoutils/types.hpp"
#include "geoutils/gltypes.hpp"
#include "geoutils/constants.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Matrix3;
class Matrix4;
class VectorSet;

/// Class information for class Program.
class ProgramClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ProgramClassInfo();
		/// Destructor.
		virtual ~ProgramClassInfo();
};

/** Program (OpenGL).
 * \ingroup cg
 *
 * An OpenGL program. This can be used to manage vertex and fragment 
 * shaders.
 */
class Program
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Fragment shader source.
		std::string vertexShaderSource;
		/// Fragment shader source.
		std::string fragmentShaderSource;
		/// Vertex shader implementation.
		GLuint vertexShaderImpl;
		/// Fragment shader implementation.
		GLuint fragmentShaderImpl;
		/// Program implementation.
		GLuint programImpl;
		
		/** Set vertex shader implementation.
		 *
		 * Set new value of vertex shader implementation.
		 *
		 * \param newVertexShaderImpl New value of vertex shader implementation.
		 */
		virtual void setVertexShaderImpl(GLuint newVertexShaderImpl);
		
		/** Set fragment shader implementation.
		 *
		 * Set new value of fragment shader implementation.
		 *
		 * \param newFragmentShaderImpl New value of fragment shader 
		 * implementation.
		 */
		virtual void setFragmentShaderImpl(GLuint newFragmentShaderImpl);
		
		/** Set program implementation.
		 *
		 * Set new value of program implementation.
		 *
		 * \param newProgramImpl New value of program implementation.
		 */
		virtual void setProgramImpl(GLuint newProgramImpl);
		
	public:
		/// Buffer size for info logs.
		static const int INFO_LOG_BUFFER_SIZE;
		/// Default vertex shader.
		static const std::string DEFAULT_VERTEX_SHADER;
		/// Fragmet shader: flat color.
		static const std::string FRAGMENT_SHADER_FLAT_COLOR;
		/// Class information instance.
		static const ProgramClassInfo programClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Program object.
		 */
		Program();
		
		/** Constructor.
		 *
		 * Construct new Program object.
		 *
		 * \param other Other object.
		 */
		Program(const Ionflux::GeoUtils::Program& other);
		
		/** Constructor.
		 *
		 * Construct new Program object.
		 *
		 * \param initVertexShaderSource Vertex shader source.
		 * \param initFragmentShaderSource Fragment shader source.
		 */
		Program(const std::string& initVertexShaderSource, const std::string& 
		initFragmentShaderSource = FRAGMENT_SHADER_FLAT_COLOR);
		
		/** Destructor.
		 *
		 * Destruct Program object.
		 */
		virtual ~Program();
		
		/** Clean up.
		 *
		 * Clean up state maintained by the program.
		 */
		virtual void cleanup();
		
		/** Initialize.
		 *
		 * Initialize the program.
		 */
		virtual void init();
		
		/** Use program.
		 *
		 * Use this program.
		 */
		virtual void use();
		
		/** Set uniform (4x4 matrix).
		 *
		 * Set the uniform with the specified name within the default uniform 
		 * block to the specified value.
		 *
		 * \param name Uniform name.
		 * \param value Value.
		 */
		virtual void setUniform(const std::string& name, const 
		Ionflux::GeoUtils::Matrix4& value);
		
		/** Set uniform (3x3 matrix).
		 *
		 * Set the uniform with the specified name within the default uniform 
		 * block to the specified value.
		 *
		 * \param name Uniform name.
		 * \param value Value.
		 */
		virtual void setUniform(const std::string& name, const 
		Ionflux::GeoUtils::Matrix3& value);
		
		/** Set uniform (vector set).
		 *
		 * Set the uniform with the specified name within the default uniform 
		 * block to the specified value.
		 *
		 * \param name Uniform name.
		 * \param value Value.
		 */
		virtual void setUniform(const std::string& name, const 
		Ionflux::GeoUtils::VectorSet& value);
		
		/** Set uniform (color set).
		 *
		 * Set the uniform with the specified name within the default uniform 
		 * block to the specified value.
		 *
		 * \param name Uniform name.
		 * \param value Value.
		 */
		virtual void setUniform(const std::string& name, const 
		Ionflux::Altjira::ColorSet& value);
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Get OpenGL shader info log.
		 *
		 * Get the shader info log for an OpenGL shader.
		 *
		 * \param shader OpenGL shader.
		 *
		 * \return Shader info log.
		 */
		static std::string getOpenGLShaderInfoLog(GLuint shader);
		
		/** Get OpenGL program info log.
		 *
		 * Get the program info log for an OpenGL program.
		 *
		 * \param program OpenGL program.
		 *
		 * \return Program info log.
		 */
		static std::string getOpenGLProgramInfoLog(GLuint program);
		
		/** Create OpenGL shader.
		 *
		 * Create an OpenGL shader.
		 *
		 * \param source Shader source.
		 * \param type Shader type.
		 * \param shaderID Shader ID.
		 *
		 * \return OpenGL shader.
		 */
		static GLuint createOpenGLShader(const std::string& source, GLenum type, 
		const std::string& shaderID = "<unnamed>");
		
		/** Get maximum number of uniform components.
		 *
		 * Get the maximum number of vertex shader uniform components.
		 *
		 * \return maximum number of uniform components.
		 */
		static unsigned int getOpenGLMaxVertexUniformComponents();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Program& operator=(const 
		Ionflux::GeoUtils::Program& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Program* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Program* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::GeoUtils::Program* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Program object.
		 *
		 * \param initVertexShaderSource Vertex shader source.
		 * \param initFragmentShaderSource Fragment shader source.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Program* create(const std::string& 
		initVertexShaderSource, const std::string& initFragmentShaderSource = 
		FRAGMENT_SHADER_FLAT_COLOR, Ionflux::ObjectBase::IFObject* parentObject =
		0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get fragment shader source.
		 *
		 * \return Current value of fragment shader source.
		 */
		virtual std::string getVertexShaderSource() const;
		
		/** Set fragment shader source.
		 *
		 * Set new value of fragment shader source.
		 *
		 * \param newVertexShaderSource New value of fragment shader source.
		 */
		virtual void setVertexShaderSource(const std::string 
		newVertexShaderSource);
		
		/** Get fragment shader source.
		 *
		 * \return Current value of fragment shader source.
		 */
		virtual std::string getFragmentShaderSource() const;
		
		/** Set fragment shader source.
		 *
		 * Set new value of fragment shader source.
		 *
		 * \param newFragmentShaderSource New value of fragment shader source.
		 */
		virtual void setFragmentShaderSource(const std::string 
		newFragmentShaderSource);
		
		/** Get vertex shader implementation.
		 *
		 * \return Current value of vertex shader implementation.
		 */
		virtual GLuint getVertexShaderImpl() const;
		
		/** Get fragment shader implementation.
		 *
		 * \return Current value of fragment shader implementation.
		 */
		virtual GLuint getFragmentShaderImpl() const;
		
		/** Get program implementation.
		 *
		 * \return Current value of program implementation.
		 */
		virtual GLuint getProgramImpl() const;
};

}

}

/** \file Program.hpp
 * \brief Program (OpenGL) (header).
 */
#endif
