#ifndef IONFLUX_GEOUTILS_VECTOR3MAPPING
#define IONFLUX_GEOUTILS_VECTOR3MAPPING
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector3Mapping.hpp              Vector mapping (3 elements) (header).
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
#include "geoutils/Vector3.hpp"
#include "ifmapping/types.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

/// Class information for class Vector3Mapping.
class Vector3MappingClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Vector3MappingClassInfo();
		/// Destructor.
		virtual ~Vector3MappingClassInfo();
};

/** Vector mapping (3 elements).
 * \ingroup geoutils
 *
 * Abstract base class for mappings that map a parameter to a vector with 
 * three elements.
 */
class Vector3Mapping
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const Vector3MappingClassInfo vector3MappingClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Vector3Mapping object.
		 */
		Vector3Mapping();
		
		/** Constructor.
		 *
		 * Construct new Vector3Mapping object.
		 *
		 * \param other Other object.
		 */
		Vector3Mapping(const Ionflux::GeoUtils::Mapping::Vector3Mapping& other);
		
		/** Destructor.
		 *
		 * Destruct Vector3Mapping object.
		 */
		virtual ~Vector3Mapping();
		
		/** Evaluate the mapping.
		 *
		 * Evaluate the mapping with the specified parameter.
		 *
		 * \param value Value.
		 *
		 * \return Mapped value.
		 */
		virtual Ionflux::GeoUtils::Vector3 
		operator()(Ionflux::Mapping::MappingValue value) const;
		
		/** Evaluate the mapping.
		 *
		 * Evaluate the mapping with the specified parameter.
		 *
		 * \param value Value.
		 */
		virtual Ionflux::GeoUtils::Vector3 call(Ionflux::Mapping::MappingValue 
		value) const = 0;
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Mapping::Vector3Mapping& operator=(const 
		Ionflux::GeoUtils::Mapping::Vector3Mapping& other);
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Mapping::Vector3Mapping* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
};

}

}

}

/** \file Vector3Mapping.hpp
 * \brief Vector mapping (3 elements) (header).
 */
#endif
