/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Program.cpp                     Program (OpenGL) (implementation).
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

#include "geoutils/Program.hpp"
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "geoutils/Matrix3.hpp"
#include "geoutils/Matrix4.hpp"
#include "geoutils/GeoUtilsError.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

ProgramClassInfo::ProgramClassInfo()
{
	name = "Program";
	desc = "Program (OpenGL)";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

ProgramClassInfo::~ProgramClassInfo()
{
}

// public member constants
const int Program::INFO_LOG_BUFFER_SIZE = 10000;
const std::string Program::DEFAULT_VERTEX_SHADER = "#version 330\n"
"uniform mat4 ifvgMVPMatrix;\n"
"uniform mat3 ifvgNormalMatrix;\n"
"layout(location = 0) in vec3 ifvgVertex;\n"
"layout(location = 1) in vec4 ifvgColor;\n"
"layout(location = 2) in vec3 ifvgNormal;\n"
"layout(location = 3) in vec4 ifvgMultiTexCoord0;\n"
"smooth out vec4 color;\n"
"smooth out vec3 normal;\n"
"smooth out vec4 texCoord0;\n"
"void main()\n"
"{\n"
"    color = ifvgColor;\n"
"    normal = ifvgNormalMatrix * ifvgNormal;\n"
"    texCoord0 = ifvgMultiTexCoord0;\n"
"    gl_Position = ifvgMVPMatrix * vec4(ifvgVertex, 1);\n"
"}\n";;
const std::string Program::FRAGMENT_SHADER_FLAT_COLOR = "#version 330\n"
"in vec4 color;\n"
"layout(location = 0) out vec4 fragData;\n"
"void main()\n"
"{\n"
"    fragData = color;\n"
"}\n";

// run-time type information instance constants
const ProgramClassInfo Program::programClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Program::CLASS_INFO = &Program::programClassInfo;

Program::Program()
: vertexShaderSource(DEFAULT_VERTEX_SHADER), fragmentShaderSource(FRAGMENT_SHADER_FLAT_COLOR), vertexShaderImpl(0), fragmentShaderImpl(0), programImpl(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Program::Program(const Ionflux::GeoUtils::Program& other)
: vertexShaderSource(DEFAULT_VERTEX_SHADER), fragmentShaderSource(FRAGMENT_SHADER_FLAT_COLOR), vertexShaderImpl(0), fragmentShaderImpl(0), programImpl(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Program::Program(const std::string& initVertexShaderSource, const 
std::string& initFragmentShaderSource)
: vertexShaderSource(DEFAULT_VERTEX_SHADER), 
fragmentShaderSource(initFragmentShaderSource), vertexShaderImpl(0), 
fragmentShaderImpl(0), programImpl(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Program::~Program()
{
	cleanup();
}

void Program::cleanup()
{
	if (programImpl != 0)
	{
	    glDeleteProgram(programImpl);
	    programImpl = 0;
	}
	if (vertexShaderImpl != 0)
	{
	    glDeleteShader(vertexShaderImpl);
	    vertexShaderImpl = 0;
	}
	if (fragmentShaderImpl != 0)
	{
	    glDeleteShader(fragmentShaderImpl);
	    fragmentShaderImpl = 0;
	}
}

void Program::init()
{
	// vertex shader
	if (vertexShaderSource.size() > 0)
	{
	    if (vertexShaderImpl != 0)
	    {
	        if (programImpl != 0)
	            glDetachShader(programImpl, vertexShaderImpl);
	        glDeleteShader(vertexShaderImpl);
	    }
	    vertexShaderImpl = createOpenGLShader(vertexShaderSource, 
	        GL_VERTEX_SHADER, "vertex");
	}
	// fragment shader
	if (fragmentShaderSource.size() > 0)
	{
	    if (fragmentShaderImpl != 0)
	    {
	        if (programImpl != 0)
	            glDetachShader(programImpl, fragmentShaderImpl);
	        glDeleteShader(fragmentShaderImpl);
	    }
	    fragmentShaderImpl = createOpenGLShader(fragmentShaderSource, 
	        GL_FRAGMENT_SHADER, "fragment");
	}
	// program
	// <---- DEBUG ----- //
	std::cerr << "[Program::init] "
	    "Initializing program..." << std::endl;
	// ----- DEBUG ----> */
	if (programImpl != 0)
	    glDeleteProgram(programImpl);
	programImpl = glCreateProgram();
	if (programImpl == 0)
	{
	    throw GeoUtilsError(getErrorString("Could not create program.", 
	        "init"));
	}
	glAttachShader(programImpl, vertexShaderImpl);
	glAttachShader(programImpl, fragmentShaderImpl);
	// <---- DEBUG ----- //
	std::cerr << "[Program::init] "
	    "Linking program..." << std::endl;
	// ----- DEBUG ----> */
	glLinkProgram(programImpl);
	int result = GL_FALSE;
	glGetProgramiv(programImpl, GL_LINK_STATUS, &result);
	if (result != GL_TRUE)
	{
	    std::ostringstream status;
	    status << "Could not link program: " 
	        << std::endl << getOpenGLProgramInfoLog(programImpl);
	    glDeleteProgram(programImpl);
	    throw GeoUtilsError(getErrorString(status.str(), "init"));
	}
}

void Program::use()
{
	if (programImpl == 0)
	    throw GeoUtilsError(getErrorString("Program not set.", "use"));
	glUseProgram(programImpl);
}

void Program::setUniform(const std::string& name, const 
Ionflux::GeoUtils::Matrix4& value)
{
	if (programImpl == 0)
	    throw GeoUtilsError(getErrorString("Program not set.", "setUniform"));
	int ul0 = glGetUniformLocation(programImpl, name.c_str());
	if (ul0 == -1)
	{
	    std::ostringstream status;
	    status << "Name does not exist within default "
	        "uniform block: '" << name << "'.";
	    throw GeoUtilsError(getErrorString(status.str(), "setUniform"));
	}
	// <---- DEBUG ----- //
	std::cerr << "[Program::setUniform] DEBUG: "
	    << "Setting uniform '" << name << "' = " << value.getString() 
	    << std::endl;
	// ----- DEBUG ----> */
	int n0 = value.getNumElements();
	GLfloat* v0 = new GLfloat[n0];
	Ionflux::ObjectBase::nullPointerCheck(v0, this, 
	    "setUniform", "Value buffer");
	for (int i = 0; i < n0; i++)
	    v0[i] = value.getElement(i);
	glUniformMatrix4fv(ul0, 1, GL_FALSE, v0);
	delete[] v0;
	if (glGetError() == GL_INVALID_OPERATION)
	{
	    std::ostringstream status;
	    status << "Type mismatch for uniform within default block '" 
	        << name << "'.";
	    throw GeoUtilsError(getErrorString(status.str(), "setUniform"));
	}
}

void Program::setUniform(const std::string& name, const 
Ionflux::GeoUtils::Matrix3& value)
{
	if (programImpl == 0)
	    throw GeoUtilsError(getErrorString("Program not set.", "setUniform"));
	int ul0 = glGetUniformLocation(programImpl, name.c_str());
	if (ul0 == -1)
	{
	    std::ostringstream status;
	    status << "Name does not exist within default "
	        "uniform block: '" << name << "'.";
	    throw GeoUtilsError(getErrorString(status.str(), "setUniform"));
	}
	// <---- DEBUG ----- //
	std::cerr << "[Program::setUniform] DEBUG: "
	    << "Setting uniform '" << name << "' = " << value.getString() 
	    << std::endl;
	// ----- DEBUG ----> */
	int n0 = value.getNumElements();
	GLfloat* v0 = new GLfloat[n0];
	Ionflux::ObjectBase::nullPointerCheck(v0, this, 
	    "setUniform", "Value buffer");
	for (int i = 0; i < n0; i++)
	    v0[i] = value.getElement(i);
	glUniformMatrix3fv(ul0, 1, GL_FALSE, v0);
	delete[] v0;
	if (glGetError() == GL_INVALID_OPERATION)
	{
	    std::ostringstream status;
	    status << "Type mismatch for uniform within default block '" 
	        << name << "'.";
	    throw GeoUtilsError(getErrorString(status.str(), "setUniform"));
	}
}

std::string Program::getValueString() const
{
	std::ostringstream status;
	status << "shaders: ";
	if (vertexShaderSource.size() > 0)
	    status << "vertex";
	else
	    status << "<none>";
	status << ", ";
	if (fragmentShaderSource.size() > 0)
	    status << "fragment";
	else
	    status << "<none>";
	return status.str();
}

std::string Program::getOpenGLShaderInfoLog(GLuint shader)
{
	char* cb0 = new char[INFO_LOG_BUFFER_SIZE];
	Ionflux::ObjectBase::nullPointerCheck(cb0, 
	    "Program::getOpenGLShaderInfoLog", "Buffer");
	glGetShaderInfoLog(shader, INFO_LOG_BUFFER_SIZE, 0, cb0);
	std::string result(cb0);
	delete[] cb0;
	return result;
}

std::string Program::getOpenGLProgramInfoLog(GLuint program)
{
	char* cb0 = new char[INFO_LOG_BUFFER_SIZE];
	Ionflux::ObjectBase::nullPointerCheck(cb0, 
	    "Program::getOpenProgramInfoLog", "Buffer");
	glGetProgramInfoLog(program, INFO_LOG_BUFFER_SIZE, 0, cb0);
	std::string result(cb0);
	delete[] cb0;
	return result;
}

GLuint Program::createOpenGLShader(const std::string& source, GLenum type, 
const std::string& shaderID)
{
	if (source.size() == 0)
	{
	    std::ostringstream status;
	    status << "[Program::createOpenGLShader] " 
	        "Shader source not set for shader '" << shaderID << "'.";
	    throw GeoUtilsError(status.str());
	}
	GLuint shader = 0;
	// <---- DEBUG ----- //
	std::cerr << "[Program::createOpenGLShader] "
	    "Initializing shader '" << shaderID << "'... " << std::endl;
	// ----- DEBUG ----> */
	// <---- DEBUG ----- //
	std::cerr << "[Program::createOpenGLShader] "
	    "Source for shader '" << shaderID << "': " << std::endl 
	    << source << std::endl;
	// ----- DEBUG ----> */
	shader = glCreateShader(type);
	if (shader == 0)
	{
	    std::ostringstream status;
	    status << "[Program::createOpenGLShader] "
	        "Could not create shader '" << shaderID << "'.";
	    throw GeoUtilsError(status.str());
	}
	const char* c0 = source.c_str();
	glShaderSource(shader, 1, &c0, 0);
	// <---- DEBUG ----- //
	std::cerr << "[Program::createOpenGLShader] "
	    "Compiling shader '" << shaderID << "'..." << std::endl;
	// ----- DEBUG ----> */
	glCompileShader(shader);
	int result = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE)
	{
	    std::ostringstream status;
	    status << "[Program::createOpenGLShader] "
	        "Could not compile shader '" << shaderID << "': " 
	        << std::endl << getOpenGLShaderInfoLog(shader);
	    glDeleteShader(shader);
	    throw GeoUtilsError(status.str());
	}
	return shader;
}

void Program::setVertexShaderSource(const std::string 
newVertexShaderSource)
{
	vertexShaderSource = newVertexShaderSource;
}

std::string Program::getVertexShaderSource() const
{
    return vertexShaderSource;
}

void Program::setFragmentShaderSource(const std::string 
newFragmentShaderSource)
{
	fragmentShaderSource = newFragmentShaderSource;
}

std::string Program::getFragmentShaderSource() const
{
    return fragmentShaderSource;
}

void Program::setVertexShaderImpl(GLuint newVertexShaderImpl)
{
	vertexShaderImpl = newVertexShaderImpl;
}

GLuint Program::getVertexShaderImpl() const
{
    return vertexShaderImpl;
}

void Program::setFragmentShaderImpl(GLuint newFragmentShaderImpl)
{
	fragmentShaderImpl = newFragmentShaderImpl;
}

GLuint Program::getFragmentShaderImpl() const
{
    return fragmentShaderImpl;
}

void Program::setProgramImpl(GLuint newProgramImpl)
{
	programImpl = newProgramImpl;
}

GLuint Program::getProgramImpl() const
{
    return programImpl;
}

Ionflux::GeoUtils::Program& Program::operator=(const 
Ionflux::GeoUtils::Program& other)
{
    if (this == &other)
        return *this;
    setVertexShaderSource(other.vertexShaderSource);
    setFragmentShaderSource(other.fragmentShaderSource);
	return *this;
}

Ionflux::GeoUtils::Program* Program::copy() const
{
    Program* newProgram = create();
    *newProgram = *this;
    return newProgram;
}

Ionflux::GeoUtils::Program* Program::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Program*>(other);
}

Ionflux::GeoUtils::Program* Program::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Program* newObject = new Program();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Program* Program::create(const std::string& 
initVertexShaderSource, const std::string& initFragmentShaderSource, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Program* newObject = new Program(initVertexShaderSource, 
    initFragmentShaderSource);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Program::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Program.cpp
 * \brief Program (OpenGL) implementation.
 */
