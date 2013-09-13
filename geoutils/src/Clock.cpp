/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Clock.cpp                       Clock (implementation).
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

#include "geoutils/Clock.hpp"
#include <sys/time.h>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

ClockClassInfo::ClockClassInfo()
{
	name = "Clock";
	desc = "Clock";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

ClockClassInfo::~ClockClassInfo()
{
}

// run-time type information instance constants
const ClockClassInfo Clock::clockClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Clock::CLASS_INFO = &Clock::clockClassInfo;

Clock::Clock()
: startTime(0.), stopTime(0.), elapsedTime(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Clock::Clock(const Ionflux::GeoUtils::Clock& other)
: startTime(0.), stopTime(0.), elapsedTime(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Clock::~Clock()
{
	// TODO: Nothing ATM. ;-)
}

std::string Clock::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << setprecision(5) 
	    << startTime << ", " << stopTime << ", " << elapsedTime << "]";
	return status.str();
}

double Clock::getCurrentTime()
{
	timeval t0;
	::gettimeofday(&t0, 0);
	return t0.tv_sec + 1e-6 * t0.tv_usec;
}

double Clock::start()
{
	elapsedTime = 0.;
	startTime = getCurrentTime();
	return startTime;
}

double Clock::stop()
{
	stopTime = getCurrentTime();
	elapsedTime = stopTime - startTime;
	return stopTime;
}

void Clock::setStartTime(double newStartTime)
{
	startTime = newStartTime;
}

double Clock::getStartTime() const
{
    return startTime;
}

void Clock::setStopTime(double newStopTime)
{
	stopTime = newStopTime;
}

double Clock::getStopTime() const
{
    return stopTime;
}

double Clock::getElapsedTime() const
{
    return elapsedTime;
}

Ionflux::GeoUtils::Clock& Clock::operator=(const Ionflux::GeoUtils::Clock& 
other)
{
    elapsedTime = other.elapsedTime;
	return *this;
}

Ionflux::GeoUtils::Clock* Clock::copy() const
{
    Clock* newClock = create();
    *newClock = *this;
    return newClock;
}

Ionflux::GeoUtils::Clock* Clock::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Clock*>(other);
}

Ionflux::GeoUtils::Clock* Clock::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Clock* newObject = new Clock();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file Clock.cpp
 * \brief Clock implementation.
 */
