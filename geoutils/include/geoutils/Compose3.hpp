#ifndef IONFLUX_GEOUTILS_COMPOSE3
#define IONFLUX_GEOUTILS_COMPOSE3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Compose3.hpp                    Vector mapping: Compose (header).
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
#include "ifmapping/Mapping.hpp"
#include "geoutils/Vector3Mapping.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

/// Class information for class Compose3.
class Compose3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Compose3ClassInfo();
		/// Destructor.
		virtual ~Compose3ClassInfo();
};

/** Vector mapping: Compose.
 * \ingroup geoutils
 *
 * Mapping that composes a 3-element vector by calling one mapping per 
 * component.
 */
class Compose3
: public Ionflux::GeoUtils::Mapping::Vector3Mapping
{
	private:
		
	protected:
		/// Component mapping (0).
		Ionflux::Mapping::Mapping* funcX0;
		/// Component mapping (1).
		Ionflux::Mapping::Mapping* funcX1;
		/// Component mapping (2).
		Ionflux::Mapping::Mapping* funcX2;
		
	public:
		/// Class information instance.
		static const Compose3ClassInfo compose3ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Compose3 object.
		 */
		Compose3();
		
		/** Constructor.
		 *
		 * Construct new Compose3 object.
		 *
		 * \param other Other object.
		 */
		Compose3(const Ionflux::GeoUtils::Mapping::Compose3& other);
		
		/** Constructor.
		 *
		 * Construct new Compose3 object.
		 *
		 * \param initFuncX0 Mapping function (X0).
		 * \param initFuncX1 Mapping function (X1).
		 * \param initFuncX2 Mapping function (X2).
		 */
		Compose3(Ionflux::Mapping::Mapping* initFuncX0, 
		Ionflux::Mapping::Mapping* initFuncX1 = 0, Ionflux::Mapping::Mapping* 
		initFuncX2 = 0);
		
		/** Destructor.
		 *
		 * Destruct Compose3 object.
		 */
		virtual ~Compose3();
		
		/** Set component mappings.
		 *
		 * Set the component mappings.
		 *
		 * \param newFuncX0 Component mapping (0).
		 * \param newFuncX1 Component mapping (1).
		 * \param newFuncX2 Component mapping (2).
		 */
		virtual void setFuncs(Ionflux::Mapping::Mapping* newFuncX0 = 0, 
		Ionflux::Mapping::Mapping* newFuncX1 = 0, Ionflux::Mapping::Mapping* 
		newFuncX2 = 0);
		
		/** Set component mappings.
		 *
		 * Set all component mappings to the same mapping.
		 *
		 * \param newFunc Component mapping.
		 */
		virtual void setFuncsEqual(Ionflux::Mapping::Mapping* newFunc = 0);
		
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
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Mapping::Compose3& operator=(const 
		Ionflux::GeoUtils::Mapping::Compose3& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Mapping::Compose3* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Mapping::Compose3* 
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
		static Ionflux::GeoUtils::Mapping::Compose3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get component mapping (0).
		 *
		 * \return Current value of component mapping (0).
		 */
		virtual Ionflux::Mapping::Mapping* getFuncX0() const;
		
		/** Set component mapping (0).
		 *
		 * Set new value of component mapping (0).
		 *
		 * \param newFuncX0 New value of component mapping (0).
		 */
		virtual void setFuncX0(Ionflux::Mapping::Mapping* newFuncX0);
		
		/** Get component mapping (1).
		 *
		 * \return Current value of component mapping (1).
		 */
		virtual Ionflux::Mapping::Mapping* getFuncX1() const;
		
		/** Set component mapping (1).
		 *
		 * Set new value of component mapping (1).
		 *
		 * \param newFuncX1 New value of component mapping (1).
		 */
		virtual void setFuncX1(Ionflux::Mapping::Mapping* newFuncX1);
		
		/** Get component mapping (2).
		 *
		 * \return Current value of component mapping (2).
		 */
		virtual Ionflux::Mapping::Mapping* getFuncX2() const;
		
		/** Set component mapping (2).
		 *
		 * Set new value of component mapping (2).
		 *
		 * \param newFuncX2 New value of component mapping (2).
		 */
		virtual void setFuncX2(Ionflux::Mapping::Mapping* newFuncX2);
};

}

}

}

/** \file Compose3.hpp
 * \brief Vector mapping: Compose (header).
 */
#endif
