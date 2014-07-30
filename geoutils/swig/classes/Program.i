/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Program.i                       Program (OpenGL) (interface).
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
%{
#include "geoutils/Program.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Matrix3;
class Matrix4;
class VectorSet;

class ProgramClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ProgramClassInfo();
        virtual ~ProgramClassInfo();
};

class Program
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const int INFO_LOG_BUFFER_SIZE;
		static const std::string DEFAULT_VERTEX_SHADER;
		static const std::string FRAGMENT_SHADER_FLAT_COLOR;
        
        Program();
		Program(const Ionflux::GeoUtils::Program& other);
        Program(const std::string& initVertexShaderSource, const 
        std::string& initFragmentShaderSource = 
        FRAGMENT_SHADER_FLAT_COLOR);
        virtual ~Program();
        virtual void cleanup();
        virtual void init();
        virtual void use();
        virtual void setUniform(const std::string& name, const 
        Ionflux::GeoUtils::Matrix4& value);
        virtual void setUniform(const std::string& name, const 
        Ionflux::GeoUtils::Matrix3& value);
        virtual void setUniform(const std::string& name, const 
        Ionflux::GeoUtils::VectorSet& value);
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::Program* copy() const;
		static Ionflux::GeoUtils::Program* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Program* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Program* create(const std::string& 
		initVertexShaderSource, const std::string& initFragmentShaderSource = 
		FRAGMENT_SHADER_FLAT_COLOR, Ionflux::ObjectBase::IFObject* parentObject =
		0);
        virtual void setVertexShaderSource(const std::string 
        newVertexShaderSource);
        virtual std::string getVertexShaderSource() const;
        virtual void setFragmentShaderSource(const std::string 
        newFragmentShaderSource);
        virtual std::string getFragmentShaderSource() const;
        virtual GLuint getVertexShaderImpl() const;
        virtual GLuint getFragmentShaderImpl() const;
        virtual GLuint getProgramImpl() const;
};

}

}
