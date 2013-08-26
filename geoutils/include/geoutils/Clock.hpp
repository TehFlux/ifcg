#ifndef IONFLUX_GEOUTILS_CLOCK
#define IONFLUX_GEOUTILS_CLOCK
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Clock.hpp                       Clock (header).
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
#include "geoutils/utils.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Clock.
class ClockClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ClockClassInfo();
		/// Destructor.
		virtual ~ClockClassInfo();
};

/** Clock.
 * \ingroup geoutils
 *
 * An object that can be used to measure elapsed time.
 */
class Clock
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Start time.
		double startTime;
		/// Stop time.
		double stopTime;
		/// Elapsed time.
		double elapsedTime;
		
	public:
		/// Class information instance.
		static const ClockClassInfo clockClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Clock object.
		 */
		Clock();
		
		/** Constructor.
		 *
		 * Construct new Clock object.
		 *
		 * \param other Other object.
		 */
		Clock(const Ionflux::GeoUtils::Clock& other);
		
		/** Destructor.
		 *
		 * Destruct Clock object.
		 */
		virtual ~Clock();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Get current time.
		 *
		 * Get the current time value in seconds.
		 *
		 * \return Current time value.
		 */
		virtual double getCurrentTime();
		
		/** Start clock.
		 *
		 * Start the clock.
		 *
		 * \return Start time of the clock in seconds.
		 */
		virtual double start();
		
		/** Stop clock.
		 *
		 * Stop the clock.
		 *
		 * \return Stop time of the clock in seconds.
		 */
		virtual double stop();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Clock& operator=(const 
		Ionflux::GeoUtils::Clock& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Clock* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Clock* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		
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
		static Ionflux::GeoUtils::Clock* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get start time.
		 *
		 * \return Current value of start time.
		 */
		virtual double getStartTime() const;
		
		/** Set start time.
		 *
		 * Set new value of start time.
		 *
		 * \param newStartTime New value of start time.
		 */
		virtual void setStartTime(double newStartTime);
		
		/** Get stop time.
		 *
		 * \return Current value of stop time.
		 */
		virtual double getStopTime() const;
		
		/** Set stop time.
		 *
		 * Set new value of stop time.
		 *
		 * \param newStopTime New value of stop time.
		 */
		virtual void setStopTime(double newStopTime);
		
		/** Get elapsed time.
		 *
		 * \return Current value of elapsed time.
		 */
		virtual double getElapsedTime() const;
};

}

}

/** \file Clock.hpp
 * \brief Clock (header).
 */
#endif
