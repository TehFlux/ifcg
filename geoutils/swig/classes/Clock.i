/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Clock.i                         Clock (interface).
 * =========================================================================

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
#include "geoutils/Clock.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class ClockClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ClockClassInfo();
        virtual ~ClockClassInfo();
};

class Clock
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        Clock();
		Clock(const Ionflux::GeoUtils::Clock& other);
        virtual ~Clock();
        virtual std::string getString() const;
        virtual double getCurrentTime();
        virtual double start();
        virtual double stop();
		virtual Ionflux::GeoUtils::Clock* copy() const;
		static Ionflux::GeoUtils::Clock* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Clock* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setStartTime(double newStartTime);
        virtual double getStartTime() const;
        virtual void setStopTime(double newStopTime);
        virtual double getStopTime() const;
        virtual double getElapsedTime() const;
};

}

}
