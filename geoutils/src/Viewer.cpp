/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Viewer.cpp                      Viewer (implementation).
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

#include "geoutils/Viewer.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/glutils.hpp"
#include "geoutils/ViewerEvent.hpp"
#include "geoutils/ViewerEventSet.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

ViewerClassInfo::ViewerClassInfo()
{
	name = "Viewer";
	desc = "Viewer";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

ViewerClassInfo::~ViewerClassInfo()
{
}

// static protected member variables
Ionflux::GeoUtils::Viewer* Viewer::instance = 0;

// public member constants
const int Viewer::DEFAULT_WINDOW_POS_X = 0;
const int Viewer::DEFAULT_WINDOW_POS_Y = 0;
const int Viewer::DEFAULT_WINDOW_WIDTH = 1000;
const int Viewer::DEFAULT_WINDOW_HEIGHT = 563;
const std::string Viewer::DEFAULT_WINDOW_TITLE = "Viewer";
const int Viewer::DEFAULT_OPENGL_VERSION_MAJOR = 3;
const int Viewer::DEFAULT_OPENGL_VERSION_MINOR = 3;
const Ionflux::GeoUtils::OpenGLProfileID Viewer::DEFAULT_OPENGL_PROFILE = OPENGL_PROFILE_CORE;
const Ionflux::Altjira::Color Viewer::DEFAULT_CLEAR_COLOR = Ionflux::Altjira::Color::GRAY_60;

// run-time type information instance constants
const ViewerClassInfo Viewer::viewerClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Viewer::CLASS_INFO = &Viewer::viewerClassInfo;

Viewer::Viewer()
: windowImpl(0), windowPosX(DEFAULT_WINDOW_POS_X), windowPosY(DEFAULT_WINDOW_POS_Y), windowWidth(DEFAULT_WINDOW_WIDTH), windowHeight(DEFAULT_WINDOW_HEIGHT), windowTitle(DEFAULT_WINDOW_TITLE), clearColor(DEFAULT_CLEAR_COLOR), openGLVersionMajor(DEFAULT_OPENGL_VERSION_MAJOR), openGLVersionMinor(DEFAULT_OPENGL_VERSION_MINOR), openGLProfile(DEFAULT_OPENGL_PROFILE), shutdownFlag(false), events(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Viewer::Viewer(const Ionflux::GeoUtils::Viewer& other)
: windowImpl(0), windowPosX(DEFAULT_WINDOW_POS_X), windowPosY(DEFAULT_WINDOW_POS_Y), windowWidth(DEFAULT_WINDOW_WIDTH), windowHeight(DEFAULT_WINDOW_HEIGHT), windowTitle(DEFAULT_WINDOW_TITLE), clearColor(DEFAULT_CLEAR_COLOR), openGLVersionMajor(DEFAULT_OPENGL_VERSION_MAJOR), openGLVersionMinor(DEFAULT_OPENGL_VERSION_MINOR), openGLProfile(DEFAULT_OPENGL_PROFILE), shutdownFlag(false), events(0)
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
: windowImpl(0), windowPosX(initWindowPosX), windowPosY(initWindowPosY), 
windowWidth(initWindowWidth), windowHeight(initWindowHeight), 
windowTitle(initWindowTitle), clearColor(initClearColor), 
openGLVersionMajor(initOpenGLVersionMajor), 
openGLVersionMinor(initOpenGLVersionMinor), 
openGLProfile(initOpenGLProfile), shutdownFlag(false), events(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Viewer::~Viewer()
{
	cleanup();
}

void Viewer::init()
{
	// set up error handling
	glfwSetErrorCallback(Viewer::errorHandlerGLFW);
	if (!glfwInit())
	{
	    throw GeoUtilsError(getErrorString(
	        "GLFW initialization failed.", "init"));
	}
	// configure window and context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, 
	    getOpenGLProfileGLFW(openGLProfile));
	// create the window
	windowImpl = glfwCreateWindow(windowWidth, windowHeight, 
	    windowTitle.c_str(), 0, 0);
	if (windowImpl == 0)
	{
	    throw GeoUtilsError(getErrorString(
	        "Could not create GLFW window.", "init"));
	}
	glfwSetWindowUserPointer(windowImpl, this);
	glfwMakeContextCurrent(windowImpl);
	// get OpenGL profile info
	openGLVersionMajor = glfwGetWindowAttrib(windowImpl, 
	    GLFW_CONTEXT_VERSION_MAJOR);
	openGLVersionMinor = glfwGetWindowAttrib(windowImpl, 
	    GLFW_CONTEXT_VERSION_MINOR);
	openGLProfile = getOpenGLProfileFromGLFW(
	    glfwGetWindowAttrib(windowImpl, GLFW_OPENGL_PROFILE));
	// register callbacks
	glfwSetKeyCallback(windowImpl, Viewer::keyHandlerGLFW);
	glfwSetWindowSizeCallback(windowImpl, 
	    Viewer::windowSizeHandlerGLFW);
	glfwSetWindowPosCallback(windowImpl, 
	    Viewer::windowPosHandlerGLFW);
	glfwSetWindowCloseCallback(windowImpl, 
	    Viewer::windowCloseHandlerGLFW);
	gladLoadGLLoader(reinterpret_cast<GLADloadproc>(
	    glfwGetProcAddress));
}

void Viewer::cleanup()
{
	if (windowImpl != 0)
	{
	    glfwSetWindowUserPointer(windowImpl, 0);
	    glfwSetWindowShouldClose(windowImpl, GL_TRUE);
	    glfwDestroyWindow(windowImpl);
	}
	windowImpl = 0;
}

void Viewer::shutdown(bool shutdownNow)
{
	if (shutdownFlag || shutdownNow)
	{
	    cleanup();
	    glfwTerminate();
	} else
	    shutdownFlag = true;
}

void Viewer::clear()
{
	glClearColor(clearColor.getRed(), clearColor.getGreen(), 
	    clearColor.getBlue(), clearColor.getAlpha());
	glClear(GL_COLOR_BUFFER_BIT);
}

void Viewer::closeWindow(bool closeFlag)
{
	Ionflux::ObjectBase::nullPointerCheck(windowImpl, this, 
	    "closeWindow", "Window");
	glfwSetWindowShouldClose(windowImpl, closeFlag);
}

void Viewer::initViewport()
{
	Ionflux::ObjectBase::nullPointerCheck(windowImpl, this, 
	    "initViewport", "Window");
	int fw = 0;
	int fh = 0;
	glfwGetFramebufferSize(windowImpl, &fw, &fh);
	glViewport(0, 0, fw, fh);
}

void Viewer::swapBuffers()
{
	Ionflux::ObjectBase::nullPointerCheck(windowImpl, this, 
	    "swapBuffers", "Window");
	glfwSwapBuffers(windowImpl);
}

void Viewer::pollEvents()
{
	Ionflux::ObjectBase::nullPointerCheck(windowImpl, this, 
	    "pollEvents", "Window");
	if (events == 0)
	    setEvents(ViewerEventSet::create());
	events->clearEvents();
	glfwPollEvents();
}

void Viewer::onKey(int key, int scancode, int action, int mods)
{
	Ionflux::ObjectBase::nullPointerCheck(windowImpl, this, 
	    "onKey", "Window");
	Ionflux::ObjectBase::nullPointerCheck(events, this, 
	    "onKey", "Event set");
	ViewerEvent* e0 = ViewerEvent::create(this, 
	    ViewerEvent::TYPE_KEY, key, scancode, action, mods);
	events->addEvent(e0);
	/* <---- DEBUG ----- //
	if ((key == GLFW_KEY_ESCAPE)
	    && (action == GLFW_PRESS))
	{
	    closeWindow();
	    shutdown(false);
	}
	// ----- DEBUG ----> */
}

void Viewer::onWindowSize(int width, int height)
{
	Ionflux::ObjectBase::nullPointerCheck(events, this, 
	    "onWindowSize", "Event set");
	ViewerEvent* e0 = ViewerEvent::create(this, 
	    ViewerEvent::TYPE_WINDOW_SIZE);
	events->addEvent(e0);
	windowWidth = width;
	windowHeight = height;
	initViewport();
}

void Viewer::onWindowPos(int posX, int posY)
{
	Ionflux::ObjectBase::nullPointerCheck(events, this, 
	    "onWindowPos", "Event set");
	ViewerEvent* e0 = ViewerEvent::create(this, 
	    ViewerEvent::TYPE_WINDOW_POS);
	events->addEvent(e0);
	windowPosX = posX;
	windowPosY = posY;
}

void Viewer::onWindowClose()
{
	Ionflux::ObjectBase::nullPointerCheck(events, this, 
	    "onWindowClose", "Event set");
	ViewerEvent* e0 = ViewerEvent::create(this, 
	    ViewerEvent::TYPE_WINDOW_CLOSE);
	events->addEvent(e0);
}

std::string Viewer::getValueString() const
{
	std::ostringstream status;
	status << "OpenGL " << openGLVersionMajor << "." 
	    << openGLVersionMinor << " (" 
	    << getOpenGLProfileString(openGLProfile) << "); ";
	status << "width = " << windowWidth << ", height = " 
	    << windowHeight << ", title = '" << windowTitle << "'";
	return status.str();
}

Ionflux::GeoUtils::Viewer* Viewer::getInstance()
{
	if (instance != 0)
	    return instance;
	instance = Viewer::create();
	instance->addRef();
	return instance;
}

void Viewer::setInstance(Ionflux::GeoUtils::Viewer* viewer)
{
	if (instance != 0)
	    cleanupInstance();
	instance = viewer;
	instance->addRef();
}

void Viewer::cleanupInstance()
{
	if (instance == 0)
	    return;
	if (instance->getNumRefs() == 0)
	    throw GeoUtilsError("[Viewer::cleanupInstance] "
	        "Viewer has already been cleaned up.");
	instance->removeRef();
	if (instance->getNumRefs() == 0)
	{
	    delete instance;
	    instance = 0;
	}
}

void Viewer::errorHandlerGLFW(int errorCode, const char* description)
{
	std::ostringstream status;
	status << "[Viewer::errorHandler] GLFW error: " << description;
	throw GeoUtilsError(status.str());
}

void Viewer::keyHandlerGLFW(GLFWwindow* window, int key, int scancode, int 
action, int mods)
{
	Ionflux::ObjectBase::nullPointerCheck(window, 
	    "Viewer::keyHandlerGLFW", "Window");
	Viewer* viewer = static_cast<Viewer*>(
	    glfwGetWindowUserPointer(window));
	Ionflux::ObjectBase::nullPointerCheck(viewer, 
	    "Viewer::keyHandlerGLFW", "Viewer");
	viewer->onKey(key, scancode, action, mods);
}

void Viewer::windowSizeHandlerGLFW(GLFWwindow* window, int width, int 
height)
{
	Ionflux::ObjectBase::nullPointerCheck(window, 
	    "Viewer::windowSizeHandlerGLFW", "Window");
	Viewer* viewer = static_cast<Viewer*>(
	    glfwGetWindowUserPointer(window));
	Ionflux::ObjectBase::nullPointerCheck(viewer, 
	    "Viewer::windowSizeHandlerGLFW", "Viewer");
	viewer->onWindowSize(width, height);
}

void Viewer::windowPosHandlerGLFW(GLFWwindow* window, int posX, int posY)
{
	Ionflux::ObjectBase::nullPointerCheck(window, 
	    "Viewer::windowSizeHandlerGLFW", "Window");
	Viewer* viewer = static_cast<Viewer*>(
	    glfwGetWindowUserPointer(window));
	Ionflux::ObjectBase::nullPointerCheck(viewer, 
	    "Viewer::windowSizeHandlerGLFW", "Viewer");
	viewer->onWindowPos(posX, posY);
}

void Viewer::windowCloseHandlerGLFW(GLFWwindow* window)
{
	Ionflux::ObjectBase::nullPointerCheck(window, 
	    "Viewer::windowCloseHandlerGLFW", "Window");
	Viewer* viewer = static_cast<Viewer*>(
	    glfwGetWindowUserPointer(window));
	Ionflux::ObjectBase::nullPointerCheck(viewer, 
	    "Viewer::windowCloseHandlerGLFW", "Viewer");
	viewer->onWindowClose();
}

void Viewer::setWindowImpl(GLFWwindow* newWindowImpl)
{
	windowImpl = newWindowImpl;
}

GLFWwindow* Viewer::getWindowImpl() const
{
    return windowImpl;
}

void Viewer::setWindowPosX(int newWindowPosX)
{
	if (windowImpl != 0)
	    glfwSetWindowPos(windowImpl, newWindowPosX, windowPosY);
	windowPosX = newWindowPosX;
}

int Viewer::getWindowPosX() const
{
    return windowPosX;
}

void Viewer::setWindowPosY(int newWindowPosY)
{
	if (windowImpl != 0)
	    glfwSetWindowPos(windowImpl, windowPosX, newWindowPosY);
	windowPosY = newWindowPosY;
}

int Viewer::getWindowPosY() const
{
    return windowPosY;
}

void Viewer::setWindowWidth(int newWindowWidth)
{
	if (windowImpl != 0)
	    glfwSetWindowSize(windowImpl, newWindowWidth, windowHeight);
	windowWidth = newWindowWidth;
}

int Viewer::getWindowWidth() const
{
    return windowWidth;
}

void Viewer::setWindowHeight(int newWindowHeight)
{
	if (windowImpl != 0)
	    glfwSetWindowSize(windowImpl, windowWidth, newWindowHeight);
	windowHeight = newWindowHeight;
}

int Viewer::getWindowHeight() const
{
    return windowHeight;
}

void Viewer::setWindowTitle(const std::string& newWindowTitle)
{
	if (windowImpl != 0)
	    glfwSetWindowTitle(windowImpl, newWindowTitle.c_str());
	windowTitle = newWindowTitle;
}

std::string Viewer::getWindowTitle() const
{
    return windowTitle;
}

void Viewer::setClearColor(const Ionflux::Altjira::Color& newClearColor)
{
	clearColor = newClearColor;
}

Ionflux::Altjira::Color Viewer::getClearColor() const
{
    return clearColor;
}

void Viewer::setOpenGLVersionMajor(int newOpenGLVersionMajor)
{
	openGLVersionMajor = newOpenGLVersionMajor;
}

int Viewer::getOpenGLVersionMajor() const
{
    return openGLVersionMajor;
}

void Viewer::setOpenGLVersionMinor(int newOpenGLVersionMinor)
{
	openGLVersionMinor = newOpenGLVersionMinor;
}

int Viewer::getOpenGLVersionMinor() const
{
    return openGLVersionMinor;
}

void Viewer::setOpenGLProfile(Ionflux::GeoUtils::OpenGLProfileID 
newOpenGLProfile)
{
	openGLProfile = newOpenGLProfile;
}

Ionflux::GeoUtils::OpenGLProfileID Viewer::getOpenGLProfile() const
{
    return openGLProfile;
}

void Viewer::setShutdownFlag(bool newShutdownFlag)
{
	shutdownFlag = newShutdownFlag;
}

bool Viewer::getShutdownFlag() const
{
    return shutdownFlag;
}

void Viewer::setEvents(Ionflux::GeoUtils::ViewerEventSet* newEvents)
{
	if (events == newEvents)
		return;
    if (newEvents != 0)
        addLocalRef(newEvents);
	if (events != 0)
		removeLocalRef(events);
	events = newEvents;
}

Ionflux::GeoUtils::ViewerEventSet* Viewer::getEvents() const
{
    return events;
}

Ionflux::GeoUtils::Viewer& Viewer::operator=(const 
Ionflux::GeoUtils::Viewer& other)
{
    if (this == &other)
        return *this;
	return *this;
}

Ionflux::GeoUtils::Viewer* Viewer::copy() const
{
    Viewer* newViewer = create();
    *newViewer = *this;
    return newViewer;
}

Ionflux::GeoUtils::Viewer* Viewer::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Viewer*>(other);
}

Ionflux::GeoUtils::Viewer* Viewer::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Viewer* newObject = new Viewer();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Viewer* Viewer::create(int initWindowPosX, int 
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
        throw GeoUtilsError("Could not allocate object");
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
