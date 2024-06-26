/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ViewerEvent.cpp                 Viewer event (implementation).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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

#include "geoutils/ViewerEvent.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Viewer.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

ViewerEventClassInfo::ViewerEventClassInfo()
{
	name = "ViewerEvent";
	desc = "Viewer event";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

ViewerEventClassInfo::~ViewerEventClassInfo()
{
}

// public member constants
const Ionflux::GeoUtils::ViewerEventTypeID ViewerEvent::TYPE_NONE = 0;
const Ionflux::GeoUtils::ViewerEventTypeID ViewerEvent::TYPE_KEY = 1;
const Ionflux::GeoUtils::ViewerEventTypeID ViewerEvent::TYPE_WINDOW_SIZE = 2;
const Ionflux::GeoUtils::ViewerEventTypeID ViewerEvent::TYPE_WINDOW_POS = 4;
const Ionflux::GeoUtils::ViewerEventTypeID ViewerEvent::TYPE_WINDOW_CLOSE = 8;
const Ionflux::GeoUtils::ViewerEventTypeID ViewerEvent::TYPE_CURSOR_POS = 16;
const Ionflux::GeoUtils::ViewerEventTypeID ViewerEvent::TYPE_MOUSE_BUTTON = 32;

// run-time type information instance constants
const ViewerEventClassInfo ViewerEvent::viewerEventClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ViewerEvent::CLASS_INFO = &ViewerEvent::viewerEventClassInfo;

ViewerEvent::ViewerEvent()
: viewer(0), eventType(TYPE_NONE), keyCode(0), scanCode(0), action(0), keyMods(0), posX(0), posY(0), mouseButton(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ViewerEvent::ViewerEvent(const Ionflux::GeoUtils::ViewerEvent& other)
: viewer(0), eventType(TYPE_NONE), keyCode(0), scanCode(0), action(0), keyMods(0), posX(0), posY(0), mouseButton(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ViewerEvent::ViewerEvent(Ionflux::GeoUtils::Viewer* initViewer, 
Ionflux::GeoUtils::ViewerEventTypeID initEventType, int initKeyCode, int 
initScanCode, int initAction, int initKeyMods, double initPosX, double 
initPosY, int initMouseButton)
: viewer(initViewer), eventType(initEventType), keyCode(initKeyCode), 
scanCode(initScanCode), action(initAction), keyMods(initKeyMods), 
posX(initPosX), posY(initPosY), mouseButton(initMouseButton)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ViewerEvent::~ViewerEvent()
{
	// TODO: Nothing ATM. ;-)
}

std::string ViewerEvent::getValueString() const
{
	ostringstream status;
	status << getTypeString(eventType);
	status << "; viewer: ";
	if (viewer != 0)
	{
	    std::string id0 = viewer->getID();
	    if (id0.size() == 0)
	        status << viewer;
	    else
	        status << id0;
	} else
	    status << "<none>";
	if (eventType == TYPE_KEY)
	{
	    status << "; key = " << keyCode 
	        << ", scanCode = " << scanCode 
	        << ", action = " << action 
	        << ", mods = " << keyMods;
	} else 
	if (eventType == TYPE_CURSOR_POS)
	{
	    status << "; pos = (" << posX 
	        << ", " << posY << ")";
	} else 
	if (eventType == TYPE_MOUSE_BUTTON)
	{
	    status << "; mouseButton = " << mouseButton 
	        << ", action = " << action 
	        << ", mods = " << keyMods 
	        << ", pos = (" << posX << ", " << posY << ")";
	}
	return status.str();
}

std::string ViewerEvent::getTypeString(Ionflux::GeoUtils::ViewerEventTypeID
eventType)
{
	if (eventType == TYPE_NONE)
	    return "none";
	if (eventType == TYPE_KEY)
	    return "key";
	if (eventType == TYPE_WINDOW_SIZE)
	    return "window_size";
	if (eventType == TYPE_WINDOW_POS)
	    return "window_pos";
	if (eventType == TYPE_WINDOW_CLOSE)
	    return "window_close";
	if (eventType == TYPE_CURSOR_POS)
	    return "cursor_pos";
	if (eventType == TYPE_MOUSE_BUTTON)
	    return "mouse_button";
	return "<unknown>";
}

void ViewerEvent::setViewer(Ionflux::GeoUtils::Viewer* newViewer)
{
	viewer = newViewer;
}

Ionflux::GeoUtils::Viewer* ViewerEvent::getViewer() const
{
    return viewer;
}

void ViewerEvent::setEventType(Ionflux::GeoUtils::ViewerEventTypeID 
newEventType)
{
	eventType = newEventType;
}

Ionflux::GeoUtils::ViewerEventTypeID ViewerEvent::getEventType() const
{
    return eventType;
}

void ViewerEvent::setKeyCode(int newKeyCode)
{
	keyCode = newKeyCode;
}

int ViewerEvent::getKeyCode() const
{
    return keyCode;
}

void ViewerEvent::setScanCode(int newScanCode)
{
	scanCode = newScanCode;
}

int ViewerEvent::getScanCode() const
{
    return scanCode;
}

void ViewerEvent::setAction(int newAction)
{
	action = newAction;
}

int ViewerEvent::getAction() const
{
    return action;
}

void ViewerEvent::setKeyMods(int newKeyMods)
{
	keyMods = newKeyMods;
}

int ViewerEvent::getKeyMods() const
{
    return keyMods;
}

void ViewerEvent::setPosX(double newPosX)
{
	posX = newPosX;
}

double ViewerEvent::getPosX() const
{
    return posX;
}

void ViewerEvent::setPosY(double newPosY)
{
	posY = newPosY;
}

double ViewerEvent::getPosY() const
{
    return posY;
}

void ViewerEvent::setMouseButton(int newMouseButton)
{
	mouseButton = newMouseButton;
}

int ViewerEvent::getMouseButton() const
{
    return mouseButton;
}

Ionflux::GeoUtils::ViewerEvent& ViewerEvent::operator=(const 
Ionflux::GeoUtils::ViewerEvent& other)
{
    if (this == &other)
        return *this;
    setViewer(other.viewer);
    setEventType(other.eventType);
    setKeyCode(other.keyCode);
    setScanCode(other.scanCode);
    setAction(other.action);
    setKeyMods(other.keyMods);
    setPosX(other.posX);
    setPosY(other.posY);
    setMouseButton(other.mouseButton);
	return *this;
}

Ionflux::GeoUtils::ViewerEvent* ViewerEvent::copy() const
{
    ViewerEvent* newViewerEvent = create();
    *newViewerEvent = *this;
    return newViewerEvent;
}

Ionflux::GeoUtils::ViewerEvent* 
ViewerEvent::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<ViewerEvent*>(other);
}

Ionflux::GeoUtils::ViewerEvent* 
ViewerEvent::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    ViewerEvent* newObject = new ViewerEvent();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::ViewerEvent* 
ViewerEvent::create(Ionflux::GeoUtils::Viewer* initViewer, 
Ionflux::GeoUtils::ViewerEventTypeID initEventType, int initKeyCode, int 
initScanCode, int initAction, int initKeyMods, double initPosX, double 
initPosY, int initMouseButton, Ionflux::ObjectBase::IFObject* parentObject)
{
    ViewerEvent* newObject = new ViewerEvent(initViewer, initEventType, 
    initKeyCode, initScanCode, initAction, initKeyMods, initPosX, initPosY,
    initMouseButton);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int ViewerEvent::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file ViewerEvent.cpp
 * \brief Viewer event implementation.
 */
