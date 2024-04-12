/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ViewerEventSet.i                Viewer event set (interface).
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
%{
#include "geoutils/ViewerEventSet.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class ViewerEvent;

class ViewerEventSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ViewerEventSetClassInfo();
        virtual ~ViewerEventSetClassInfo();
};

class ViewerEventSet
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        ViewerEventSet();
		ViewerEventSet(const Ionflux::GeoUtils::ViewerEventSet& other);
        virtual ~ViewerEventSet();
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::ViewerEventSet* copy() const;
		static Ionflux::GeoUtils::ViewerEventSet* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::ViewerEventSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;        
        virtual unsigned int getNumEvents() const;
        virtual Ionflux::GeoUtils::ViewerEvent* getEvent(unsigned int 
        elementIndex = 0) const;
		virtual int findEvent(Ionflux::GeoUtils::ViewerEvent* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::ViewerEvent*>& getEvents();
        virtual void addEvent(Ionflux::GeoUtils::ViewerEvent* addElement);
		virtual Ionflux::GeoUtils::ViewerEvent* addEvent();
		virtual void addEvents(std::vector<Ionflux::GeoUtils::ViewerEvent*>& 
		newEvents);
		virtual void addEvents(Ionflux::GeoUtils::ViewerEventSet* newEvents);        
        virtual void removeEvent(Ionflux::GeoUtils::ViewerEvent* 
        removeElement);
		virtual void removeEventIndex(unsigned int removeIndex);
		virtual void clearEvents();
};

}

}
