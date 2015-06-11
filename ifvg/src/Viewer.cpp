/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Viewer.cpp                      Viewer (implementation).
 * ========================================================================== */

#include "ifvg/Viewer.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "ifvg/utils.hpp"
#include "ifvg/IFVGError.hpp"

using namespace std;

namespace Ionflux
{

namespace VolGfx
{

ViewerClassInfo::ViewerClassInfo()
{
	name = "Viewer";
	desc = "Viewer";
	baseClassInfo.push_back(Ionflux::GeoUtils::Viewer::CLASS_INFO);
}

ViewerClassInfo::~ViewerClassInfo()
{
}

// run-time type information instance constants
const ViewerClassInfo Viewer::viewerClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Viewer::CLASS_INFO = &Viewer::viewerClassInfo;

Viewer::Viewer()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Viewer::Viewer(const Ionflux::VolGfx::Viewer& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Viewer::Viewer(int initWindowPosX, int initWindowPosY, int initWindowWidth,
int initWindowHeight, const std::string& initWindowTitle, const 
Ionflux::Altjira::Color& initClearColor, int initOpenGLVersionMajor, int 
initOpenGLVersionMinor, Ionflux::GeoUtils::OpenGLProfileID 
initOpenGLProfile)
: Ionflux::GeoUtils::Viewer(initWindowPosX, initWindowPosY, 
initWindowWidth, initWindowHeight, initWindowTitle, initClearColor, 
initOpenGLVersionMajor, initOpenGLVersionMinor, initOpenGLProfile)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Viewer::~Viewer()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::VolGfx::Viewer& Viewer::operator=(const Ionflux::VolGfx::Viewer& 
other)
{
    if (this == &other)
        return *this;
	return *this;
}

Ionflux::VolGfx::Viewer* Viewer::copy() const
{
    Viewer* newViewer = create();
    *newViewer = *this;
    return newViewer;
}

Ionflux::VolGfx::Viewer* Viewer::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Viewer*>(other);
}

Ionflux::VolGfx::Viewer* Viewer::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Viewer* newObject = new Viewer();
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::VolGfx::Viewer* Viewer::create(int initWindowPosX, int 
initWindowPosY, int initWindowWidth, int initWindowHeight, const 
std::string& initWindowTitle, const Ionflux::Altjira::Color& 
initClearColor, int initOpenGLVersionMajor, int initOpenGLVersionMinor, 
Ionflux::GeoUtils::OpenGLProfileID initOpenGLProfile, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Viewer* newObject = new Viewer(initWindowPosX, initWindowPosY, 
    initWindowWidth, initWindowHeight, initWindowTitle, initClearColor, 
    initOpenGLVersionMajor, initOpenGLVersionMinor, initOpenGLProfile);
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Viewer::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Viewer.cpp
 * \brief Viewer implementation.
 */
