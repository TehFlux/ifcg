#ifndef IONFLUX_GEOUTILS_ACCEPTVOLUME3
#define IONFLUX_GEOUTILS_ACCEPTVOLUME3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * AcceptVolume3.hpp               Vector mapping: Accept volume (header).
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
#include "geoutils/Range.hpp"
#include "geoutils/Accept3.hpp"
#include "geoutils/Object3.hpp"
#include "geoutils/Accept3.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

/// Class information for class AcceptVolume3.
class AcceptVolume3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		AcceptVolume3ClassInfo();
		/// Destructor.
		virtual ~AcceptVolume3ClassInfo();
};

/** Vector mapping: Accept volume.
 * \ingroup geoutils
 *
 * A vector mapping that accepts a vector from its source mapping if the 
 * vector lies within the specified volume.
 */
class AcceptVolume3
: public Ionflux::GeoUtils::Mapping::Accept3
{
	private:
		
	protected:
		/// Reference object.
		Ionflux::GeoUtils::Object3* refObject;
		
	public:
		/// Class information instance.
		static const AcceptVolume3ClassInfo acceptVolume3ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new AcceptVolume3 object.
		 */
		AcceptVolume3();
		
		/** Constructor.
		 *
		 * Construct new AcceptVolume3 object.
		 *
		 * \param other Other object.
		 */
		AcceptVolume3(const Ionflux::GeoUtils::Mapping::AcceptVolume3& other);
		
		/** Constructor.
		 *
		 * Construct new AcceptVolume3 object.
		 *
		 * \param initSource Source mapping.
		 * \param initRefObject Reference object.
		 * \param initMaxIters Maximum iterations.
		 */
		AcceptVolume3(Ionflux::GeoUtils::Mapping::Vector3Mapping* initSource, 
		Ionflux::GeoUtils::Object3* initRefObject, Ionflux::Mapping::MappingValue
		initMaxIters = Ionflux::Mapping::MAX_ITERATIONS);
		
		/** Destructor.
		 *
		 * Destruct AcceptVolume3 object.
		 */
		virtual ~AcceptVolume3();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Check condition.
		 *
		 * Check whether the condition of acceptance is satisfied for the 
		 * specified vector.
		 *
		 * \param v Vector.
		 *
		 * \return \c true if the vector satisfies the condition, \c false 
		 * otherwise.
		 */
		virtual bool checkCondition(const Ionflux::GeoUtils::Vector3& v) const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Mapping::AcceptVolume3& operator=(const 
		Ionflux::GeoUtils::Mapping::AcceptVolume3& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Mapping::AcceptVolume3* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Mapping::AcceptVolume3* 
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
		static Ionflux::GeoUtils::Mapping::AcceptVolume3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get reference object.
		 *
		 * \return Current value of reference object.
		 */
		virtual Ionflux::GeoUtils::Object3* getRefObject() const;
		
		/** Set reference object.
		 *
		 * Set new value of reference object.
		 *
		 * \param newRefObject New value of reference object.
		 */
		virtual void setRefObject(Ionflux::GeoUtils::Object3* newRefObject);
};

}

}

}

/** \file AcceptVolume3.hpp
 * \brief Vector mapping: Accept volume (header).
 */
#endif
