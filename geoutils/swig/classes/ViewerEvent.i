/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ViewerEvent.i                   Viewer event (interface).
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
#include "geoutils/ViewerEvent.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Viewer;

class ViewerEventClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ViewerEventClassInfo();
        virtual ~ViewerEventClassInfo();
};

class ViewerEvent
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::ViewerEventTypeID TYPE_NONE;
		static const Ionflux::GeoUtils::ViewerEventTypeID TYPE_KEY;
		static const Ionflux::GeoUtils::ViewerEventTypeID TYPE_WINDOW_SIZE;
		static const Ionflux::GeoUtils::ViewerEventTypeID TYPE_WINDOW_POS;
        
        ViewerEvent();
		ViewerEvent(const Ionflux::GeoUtils::ViewerEvent& other);
        ViewerEvent(Ionflux::GeoUtils::Viewer* initViewer, 
        Ionflux::GeoUtils::ViewerEventTypeID initEventType = TYPE_NONE, int
        initKeyCode = 0, int initScanCode = 0, int initKeyAction = 0, int 
        initKeyMods = 0);
        virtual ~ViewerEvent();
        virtual std::string getValueString() const;
        static std::string 
        getTypeString(Ionflux::GeoUtils::ViewerEventTypeID eventType);
		virtual Ionflux::GeoUtils::ViewerEvent* copy() const;
		static Ionflux::GeoUtils::ViewerEvent* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::ViewerEvent* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::ViewerEvent* create(Ionflux::GeoUtils::Viewer* 
		initViewer, Ionflux::GeoUtils::ViewerEventTypeID initEventType = 
		TYPE_NONE, int initKeyCode = 0, int initScanCode = 0, int initKeyAction =
		0, int initKeyMods = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setViewer(Ionflux::GeoUtils::Viewer* newViewer);
        virtual Ionflux::GeoUtils::Viewer* getViewer() const;
        virtual void setEventType(Ionflux::GeoUtils::ViewerEventTypeID 
        newEventType);
        virtual Ionflux::GeoUtils::ViewerEventTypeID getEventType() const;
        virtual void setKeyCode(int newKeyCode);
        virtual int getKeyCode() const;
        virtual void setScanCode(int newScanCode);
        virtual int getScanCode() const;
        virtual void setKeyAction(int newKeyAction);
        virtual int getKeyAction() const;
        virtual void setKeyMods(int newKeyMods);
        virtual int getKeyMods() const;
};

}

}
