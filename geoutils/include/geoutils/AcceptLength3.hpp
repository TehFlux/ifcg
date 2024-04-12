#ifndef IONFLUX_GEOUTILS_ACCEPTLENGTH3
#define IONFLUX_GEOUTILS_ACCEPTLENGTH3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * AcceptLength3.hpp               Vector mapping: Accept length (header).
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

#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Range.hpp"
#include "geoutils/Accept3.hpp"
#include "geoutils/Accept3.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

/// Class information for class AcceptLength3.
class AcceptLength3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		AcceptLength3ClassInfo();
		/// Destructor.
		virtual ~AcceptLength3ClassInfo();
};

/** Vector mapping: Accept length.
 * \ingroup geoutils
 *
 * A vector mapping that accepts a vector from its source mapping if its 
 * length is within the specified range.
 */
class AcceptLength3
: public Ionflux::GeoUtils::Mapping::Accept3
{
	private:
		
	protected:
		/// Acceptable length range.
		Ionflux::GeoUtils::Range lengthRange;
		
	public:
		/// Default acceptable length range.
		static const Ionflux::GeoUtils::Range DEFAULT_LENGTH_RANGE;
		/// Class information instance.
		static const AcceptLength3ClassInfo acceptLength3ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new AcceptLength3 object.
		 */
		AcceptLength3();
		
		/** Constructor.
		 *
		 * Construct new AcceptLength3 object.
		 *
		 * \param other Other object.
		 */
		AcceptLength3(const Ionflux::GeoUtils::Mapping::AcceptLength3& other);
		
		/** Constructor.
		 *
		 * Construct new AcceptLength3 object.
		 *
		 * \param initSource Source mapping.
		 * \param initLengthRange Acceptable length range.
		 * \param initMaxIters Maximum iterations.
		 */
		AcceptLength3(Ionflux::GeoUtils::Mapping::Vector3Mapping* initSource, 
		const Ionflux::GeoUtils::Range& initLengthRange = DEFAULT_LENGTH_RANGE, 
		Ionflux::Mapping::MappingValue initMaxIters = 
		Ionflux::Mapping::MAX_ITERATIONS);
		
		/** Destructor.
		 *
		 * Destruct AcceptLength3 object.
		 */
		virtual ~AcceptLength3();
		
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
		virtual Ionflux::GeoUtils::Mapping::AcceptLength3& operator=(const 
		Ionflux::GeoUtils::Mapping::AcceptLength3& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Mapping::AcceptLength3* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Mapping::AcceptLength3* 
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
		static Ionflux::GeoUtils::Mapping::AcceptLength3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get acceptable length range.
		 *
		 * \return Current value of acceptable length range.
		 */
		virtual Ionflux::GeoUtils::Range getLengthRange() const;
		
		/** Set acceptable length range.
		 *
		 * Set new value of acceptable length range.
		 *
		 * \param newLengthRange New value of acceptable length range.
		 */
		virtual void setLengthRange(const Ionflux::GeoUtils::Range& 
		newLengthRange);
};

}

}

}

/** \file AcceptLength3.hpp
 * \brief Vector mapping: Accept length (header).
 */
#endif
