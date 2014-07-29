#ifndef IONFLUX_GEOUTILS_VIEWEREVENTSET
#define IONFLUX_GEOUTILS_VIEWEREVENTSET
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ViewerEventSet.hpp              Viewer event set (header).
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
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class ViewerEvent;

/// Class information for class ViewerEventSet.
class ViewerEventSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ViewerEventSetClassInfo();
		/// Destructor.
		virtual ~ViewerEventSetClassInfo();
};

/** Viewer event set.
 * \ingroup ifvg
 *
 * An set of viewer events.
 */
class ViewerEventSet
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Vector of viewer events.
		std::vector<Ionflux::GeoUtils::ViewerEvent*> events;
		
	public:
		/// Class information instance.
		static const ViewerEventSetClassInfo viewerEventSetClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ViewerEventSet object.
		 */
		ViewerEventSet();
		
		/** Constructor.
		 *
		 * Construct new ViewerEventSet object.
		 *
		 * \param other Other object.
		 */
		ViewerEventSet(const Ionflux::GeoUtils::ViewerEventSet& other);
		
		/** Destructor.
		 *
		 * Destruct ViewerEventSet object.
		 */
		virtual ~ViewerEventSet();
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::ViewerEventSet& operator=(const 
		Ionflux::GeoUtils::ViewerEventSet& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::ViewerEventSet* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::ViewerEventSet* 
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
		static Ionflux::GeoUtils::ViewerEventSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get number of events.
		 *
		 * \return Number of events.
		 */
		virtual unsigned int getNumEvents() const;
		
		/** Get event.
		 *
		 * Get the event at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Event at specified index.
		 */
		virtual Ionflux::GeoUtils::ViewerEvent* getEvent(unsigned int 
		elementIndex = 0) const;
		
		/** Find event.
		 *
		 * Find the specified occurence of a event.
		 *
		 * \param needle Event to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the event, or -1 if the event cannot be found.
		 */
		virtual int findEvent(Ionflux::GeoUtils::ViewerEvent* needle, unsigned 
		int occurence = 1) const;
        
		/** Get vector of viewer events.
		 *
		 * \return vector of viewer events.
		 */
		virtual std::vector<Ionflux::GeoUtils::ViewerEvent*>& getEvents();
		
		/** Add event.
		 *
		 * Add a event.
		 *
		 * \param addElement Event to be added.
		 */
		virtual void addEvent(Ionflux::GeoUtils::ViewerEvent* addElement);
		
		/** Create event.
		 *
		 * Create a new event which is managed by the event set.
		 *
		 * \return New event.
		 */
		virtual Ionflux::GeoUtils::ViewerEvent* addEvent();
		
		/** Add events.
		 *
		 * Add events from a event vector.
		 *
		 * \param newEvents events.
		 */
		virtual void addEvents(const 
		std::vector<Ionflux::GeoUtils::ViewerEvent*>& newEvents);
		
		/** Add events.
		 *
		 * Add events from a event set.
		 *
		 * \param newEvents events.
		 */
		virtual void addEvents(Ionflux::GeoUtils::ViewerEventSet* newEvents);
		
		/** Remove event.
		 *
		 * Remove a event.
		 *
		 * \param removeElement Event to be removed.
		 */
		virtual void removeEvent(Ionflux::GeoUtils::ViewerEvent* removeElement);
		
		/** Remove event.
		 *
		 * Remove a event.
		 *
		 * \param removeIndex Event to be removed.
		 */
		virtual void removeEventIndex(unsigned int removeIndex);
		
		/** Clear events.
		 *
		 * Clear all events.
		 */
		virtual void clearEvents();
};

}

}

/** \file ViewerEventSet.hpp
 * \brief Viewer event set (header).
 */
#endif
