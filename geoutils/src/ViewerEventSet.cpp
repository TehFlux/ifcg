/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ViewerEventSet.cpp              Viewer event set (implementation).
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

#include "geoutils/ViewerEventSet.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/ViewerEvent.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

ViewerEventSetClassInfo::ViewerEventSetClassInfo()
{
	name = "ViewerEventSet";
	desc = "Viewer event set";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

ViewerEventSetClassInfo::~ViewerEventSetClassInfo()
{
}

// run-time type information instance constants
const ViewerEventSetClassInfo ViewerEventSet::viewerEventSetClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ViewerEventSet::CLASS_INFO = &ViewerEventSet::viewerEventSetClassInfo;

ViewerEventSet::ViewerEventSet()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ViewerEventSet::ViewerEventSet(const Ionflux::GeoUtils::ViewerEventSet& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ViewerEventSet::~ViewerEventSet()
{
	clearEvents();
	// TODO: Nothing ATM. ;-)
}

std::string ViewerEventSet::getValueString() const
{
	ostringstream status;
	bool e0 = true;
	for (ViewerEventVector::const_iterator i = events.begin(); 
	    i != events.end(); i++)
	{
	    if (!e0)
	        status << ", ";
	    else
	        e0 = false;
	    status << "(" << (*i)->getValueString() << ")";
	}
	if (events.size() == 0)
	    status << "<none>";
	return status.str();
}

unsigned int ViewerEventSet::getNumEvents() const
{
    return events.size();
}

Ionflux::GeoUtils::ViewerEvent* ViewerEventSet::getEvent(unsigned int 
elementIndex) const
{
    if (elementIndex < events.size())
		return events[elementIndex];
	return 0;
}

int ViewerEventSet::findEvent(Ionflux::GeoUtils::ViewerEvent* needle, 
unsigned int occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::ViewerEvent* currentEvent = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < events.size()))
	{
		currentEvent = events[i];
		if (currentEvent == needle)
        {
            if (occurence == 1)
			    found = true;
            else
                occurence--;
		} else
			i++;
	}
	if (found)
        return i;
	return -1;
}

std::vector<Ionflux::GeoUtils::ViewerEvent*>& ViewerEventSet::getEvents()
{
    return events;
}

void ViewerEventSet::addEvent(Ionflux::GeoUtils::ViewerEvent* addElement)
{
	addLocalRef(addElement);
	events.push_back(addElement);
}

Ionflux::GeoUtils::ViewerEvent* ViewerEventSet::addEvent()
{
	Ionflux::GeoUtils::ViewerEvent* o0 = ViewerEvent::create();
	addEvent(o0);
	return o0;
}

void ViewerEventSet::addEvents(const 
std::vector<Ionflux::GeoUtils::ViewerEvent*>& newEvents)
{
	for (std::vector<Ionflux::GeoUtils::ViewerEvent*>::const_iterator i = newEvents.begin(); 
	    i != newEvents.end(); i++)
	    addEvent(*i);
}

void ViewerEventSet::addEvents(Ionflux::GeoUtils::ViewerEventSet* 
newEvents)
{
	for (unsigned int i = 0; 
	    i < newEvents->getNumEvents(); i++)
	    addEvent(newEvents->getEvent(i));
}

void ViewerEventSet::removeEvent(Ionflux::GeoUtils::ViewerEvent* 
removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::ViewerEvent* currentEvent = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < events.size()))
	{
		currentEvent = events[i];
		if (currentEvent == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		events.erase(events.begin() + i);
		if (currentEvent != 0)
			removeLocalRef(currentEvent);
	}
}

void ViewerEventSet::removeEventIndex(unsigned int removeIndex)
{
    if (removeIndex > events.size())
        return;
	Ionflux::GeoUtils::ViewerEvent* e0 = events[removeIndex];
    events.erase(events.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void ViewerEventSet::clearEvents()
{
    std::vector<Ionflux::GeoUtils::ViewerEvent*>::iterator i;
	for (i = events.begin(); i != events.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	events.clear();
}

Ionflux::GeoUtils::ViewerEventSet& ViewerEventSet::operator=(const 
Ionflux::GeoUtils::ViewerEventSet& other)
{
    if (this == &other)
        return *this;
    ViewerEventVector v0;
    for (ViewerEventVector::const_iterator i = other.events.begin(); 
        i != other.events.end(); i++)
        v0.push_back((*i)->copy());
    clearEvents();
    addEvents(v0);
	return *this;
}

Ionflux::GeoUtils::ViewerEventSet* ViewerEventSet::copy() const
{
    ViewerEventSet* newViewerEventSet = create();
    *newViewerEventSet = *this;
    return newViewerEventSet;
}

Ionflux::GeoUtils::ViewerEventSet* 
ViewerEventSet::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<ViewerEventSet*>(other);
}

Ionflux::GeoUtils::ViewerEventSet* 
ViewerEventSet::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    ViewerEventSet* newObject = new ViewerEventSet();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int ViewerEventSet::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file ViewerEventSet.cpp
 * \brief Viewer event set implementation.
 */
