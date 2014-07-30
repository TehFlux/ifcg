#ifndef IONFLUX_GEOUTILS_VIEWEREVENT
#define IONFLUX_GEOUTILS_VIEWEREVENT
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ViewerEvent.hpp                 Viewer event (header).
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

#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/gltypes.hpp"
#include "geoutils/glconstants.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Viewer;

/// Class information for class ViewerEvent.
class ViewerEventClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ViewerEventClassInfo();
		/// Destructor.
		virtual ~ViewerEventClassInfo();
};

/** Viewer event.
 * \ingroup ifvg
 *
 * An event that is generated by a viewer instance.
 */
class ViewerEvent
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Viewer.
		Ionflux::GeoUtils::Viewer* viewer;
		/// Event type.
		Ionflux::GeoUtils::ViewerEventTypeID eventType;
		/// Key code.
		int keyCode;
		/// Scan code.
		int scanCode;
		/// Key action.
		int keyAction;
		/// Modifier keys.
		int keyMods;
		
	public:
		/// Event ID: none.
		static const Ionflux::GeoUtils::ViewerEventTypeID TYPE_NONE;
		/// Event ID: key.
		static const Ionflux::GeoUtils::ViewerEventTypeID TYPE_KEY;
		/// Event ID: window size.
		static const Ionflux::GeoUtils::ViewerEventTypeID TYPE_WINDOW_SIZE;
		/// Event ID: window position.
		static const Ionflux::GeoUtils::ViewerEventTypeID TYPE_WINDOW_POS;
		/// Event ID: window close.
		static const Ionflux::GeoUtils::ViewerEventTypeID TYPE_WINDOW_CLOSE;
		/// Class information instance.
		static const ViewerEventClassInfo viewerEventClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ViewerEvent object.
		 */
		ViewerEvent();
		
		/** Constructor.
		 *
		 * Construct new ViewerEvent object.
		 *
		 * \param other Other object.
		 */
		ViewerEvent(const Ionflux::GeoUtils::ViewerEvent& other);
		
		/** Constructor.
		 *
		 * Construct new ViewerEvent object.
		 *
		 * \param initViewer viewer.
		 * \param initEventType event type.
		 * \param initKeyCode key code.
		 * \param initScanCode scan code.
		 * \param initKeyAction key action.
		 * \param initKeyMods modifier keys.
		 */
		ViewerEvent(Ionflux::GeoUtils::Viewer* initViewer, 
		Ionflux::GeoUtils::ViewerEventTypeID initEventType = TYPE_NONE, int 
		initKeyCode = 0, int initScanCode = 0, int initKeyAction = 0, int 
		initKeyMods = 0);
		
		/** Destructor.
		 *
		 * Destruct ViewerEvent object.
		 */
		virtual ~ViewerEvent();
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Get string representation of event type.
		 *
		 * Get a string representation of the specified event type ID.
		 *
		 * \param eventType event type.
		 *
		 * \return String representation.
		 */
		static std::string getTypeString(Ionflux::GeoUtils::ViewerEventTypeID 
		eventType);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::ViewerEvent& operator=(const 
		Ionflux::GeoUtils::ViewerEvent& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::ViewerEvent* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::ViewerEvent* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::GeoUtils::ViewerEvent* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new ViewerEvent object.
		 *
		 * \param initViewer viewer.
		 * \param initEventType event type.
		 * \param initKeyCode key code.
		 * \param initScanCode scan code.
		 * \param initKeyAction key action.
		 * \param initKeyMods modifier keys.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::ViewerEvent* create(Ionflux::GeoUtils::Viewer* 
		initViewer, Ionflux::GeoUtils::ViewerEventTypeID initEventType = 
		TYPE_NONE, int initKeyCode = 0, int initScanCode = 0, int initKeyAction =
		0, int initKeyMods = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get viewer.
		 *
		 * \return Current value of viewer.
		 */
		virtual Ionflux::GeoUtils::Viewer* getViewer() const;
		
		/** Set viewer.
		 *
		 * Set new value of viewer.
		 *
		 * \param newViewer New value of viewer.
		 */
		virtual void setViewer(Ionflux::GeoUtils::Viewer* newViewer);
		
		/** Get event type.
		 *
		 * \return Current value of event type.
		 */
		virtual Ionflux::GeoUtils::ViewerEventTypeID getEventType() const;
		
		/** Set event type.
		 *
		 * Set new value of event type.
		 *
		 * \param newEventType New value of event type.
		 */
		virtual void setEventType(Ionflux::GeoUtils::ViewerEventTypeID 
		newEventType);
		
		/** Get key code.
		 *
		 * \return Current value of key code.
		 */
		virtual int getKeyCode() const;
		
		/** Set key code.
		 *
		 * Set new value of key code.
		 *
		 * \param newKeyCode New value of key code.
		 */
		virtual void setKeyCode(int newKeyCode);
		
		/** Get scan code.
		 *
		 * \return Current value of scan code.
		 */
		virtual int getScanCode() const;
		
		/** Set scan code.
		 *
		 * Set new value of scan code.
		 *
		 * \param newScanCode New value of scan code.
		 */
		virtual void setScanCode(int newScanCode);
		
		/** Get key action.
		 *
		 * \return Current value of key action.
		 */
		virtual int getKeyAction() const;
		
		/** Set key action.
		 *
		 * Set new value of key action.
		 *
		 * \param newKeyAction New value of key action.
		 */
		virtual void setKeyAction(int newKeyAction);
		
		/** Get modifier keys.
		 *
		 * \return Current value of modifier keys.
		 */
		virtual int getKeyMods() const;
		
		/** Set modifier keys.
		 *
		 * Set new value of modifier keys.
		 *
		 * \param newKeyMods New value of modifier keys.
		 */
		virtual void setKeyMods(int newKeyMods);
};

}

}

/** \file ViewerEvent.hpp
 * \brief Viewer event (header).
 */
#endif