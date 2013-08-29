#ifndef IONFLUX_GEOUTILS_ACCEPT3
#define IONFLUX_GEOUTILS_ACCEPT3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Accept3.hpp                     Vector mapping: Accept (header).
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
#include "geoutils/Vector3Mapping.hpp"
#include "ifmapping/constants.hpp"
#include "ifmapping/Mapping.hpp"
#include "geoutils/Vector3Mapping.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

/// Class information for class Accept3.
class Accept3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Accept3ClassInfo();
		/// Destructor.
		virtual ~Accept3ClassInfo();
};

/** Vector mapping: Accept.
 * \ingroup geoutils
 *
 * Abstract base class for vector mappings that obtain a 3-element vector 
 * from a source mapping by using the accept method to make sure the vector
 * satisfies some condition. This means the source mapping is called up to 
 * \c maxIters times to provide a vector that satisfies the condition. If 
 * the method does not yield a suitable vector, an exception is thrown.
 */
class Accept3
: public Ionflux::GeoUtils::Mapping::Vector3Mapping
{
	private:
		
	protected:
		/// Maximum iterations.
		unsigned int maxIters;
		/// Source mapping.
		Ionflux::GeoUtils::Mapping::Vector3Mapping* source;
		
	public:
		/// Class information instance.
		static const Accept3ClassInfo accept3ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Accept3 object.
		 */
		Accept3();
		
		/** Constructor.
		 *
		 * Construct new Accept3 object.
		 *
		 * \param other Other object.
		 */
		Accept3(const Ionflux::GeoUtils::Mapping::Accept3& other);
		
		/** Constructor.
		 *
		 * Construct new Accept3 object.
		 *
		 * \param initSource Source mapping.
		 * \param initMaxIters Maximum iterations.
		 */
		Accept3(Ionflux::GeoUtils::Mapping::Vector3Mapping* initSource, 
		Ionflux::Mapping::MappingValue initMaxIters = 
		Ionflux::Mapping::MAX_ITERATIONS);
		
		/** Destructor.
		 *
		 * Destruct Accept3 object.
		 */
		virtual ~Accept3();
		
		/** Evaluate the mapping.
		 *
		 * Evaluate the mapping with the specified parameter.
		 *
		 * \param value Value.
		 *
		 * \return Mapped value.
		 */
		virtual Ionflux::GeoUtils::Vector3 call(Ionflux::Mapping::MappingValue 
		value) const;
		
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
		 */
		virtual bool checkCondition(const Ionflux::GeoUtils::Vector3& v) const = 
		0;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Mapping::Accept3& operator=(const 
		Ionflux::GeoUtils::Mapping::Accept3& other);
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Mapping::Accept3* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
		/** Get maximum iterations.
		 *
		 * \return Current value of maximum iterations.
		 */
		virtual unsigned int getMaxIters() const;
		
		/** Set maximum iterations.
		 *
		 * Set new value of maximum iterations.
		 *
		 * \param newMaxIters New value of maximum iterations.
		 */
		virtual void setMaxIters(unsigned int newMaxIters);
		
		/** Get source mapping.
		 *
		 * \return Current value of source mapping.
		 */
		virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* getSource() const;
		
		/** Set source mapping.
		 *
		 * Set new value of source mapping.
		 *
		 * \param newSource New value of source mapping.
		 */
		virtual void setSource(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
		newSource);
};

}

}

}

/** \file Accept3.hpp
 * \brief Vector mapping: Accept (header).
 */
#endif
