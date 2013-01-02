#ifndef IONFLUX_MAPPING_COUNT
#define IONFLUX_MAPPING_COUNT
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Count.hpp                       Count mapping (header).
 * =========================================================================
 *
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFMapping - Ionflux Mapping Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFMapping - Ionflux Mapping Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "ifmapping/types.hpp"
#include "ifmapping/ChainableMapping.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class Count.
class CountClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		CountClassInfo();
		/// Destructor.
		virtual ~CountClassInfo();
};

/** Count mapping.
 * \ingroup ifmapping
 *
 * A mapping that returns a counter value and then increments the counter 
 * by some predefined adjustment value and applies an optional modulus. The
 * actual value of the parameter is not relevant to the result.
 */
class Count
: public Ionflux::Mapping::ChainableMapping
{
	private:
		
	protected:
		/// Counter (implementation).
		Ionflux::Mapping::MappingValue* counterImpl;
		/// Adjustment value.
		Ionflux::Mapping::MappingValue adjustment;
		/// Modulus.
		Ionflux::Mapping::MappingValue modulus;
		
	public:
		/// Class information instance.
		static const CountClassInfo countClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Count object.
		 */
		Count();
		
		/** Constructor.
		 *
		 * Construct new Count object.
		 *
		 * \param other Other object.
		 */
		Count(const Ionflux::Mapping::Count& other);
		
		/** Constructor.
		 *
		 * Construct new Count object.
		 *
		 * \param initAdjustment Adjustment value.
		 * \param initCounter Counter value.
		 * \param initModulus Modulus.
		 * \param initScale Scale factor.
		 * \param initOffset Offset.
		 * \param initFunc Source mapping.
		 */
		Count(Ionflux::Mapping::MappingValue initAdjustment, 
		Ionflux::Mapping::MappingValue initCounter = 0., 
		Ionflux::Mapping::MappingValue initModulus = 0., 
		Ionflux::Mapping::MappingValue initScale = 0., 
		Ionflux::Mapping::MappingValue initOffset = 0., 
		Ionflux::Mapping::Mapping* initFunc = 0);
		
		/** Destructor.
		 *
		 * Destruct Count object.
		 */
		virtual ~Count();
		
		/** Call the mapping.
		 *
		 * Calls the mapping with the specified parameter.
		 *
		 * \param value Value.
		 *
		 * \return Mapped value.
		 */
		virtual Ionflux::Mapping::MappingValue 
		callWithParam(Ionflux::Mapping::MappingValue value) const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Mapping::Count& operator=(const Ionflux::Mapping::Count&
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::Count* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::Count* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::Mapping::Count* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get counter value.
		 *
		 * \return Current value of counter value.
		 */
		virtual Ionflux::Mapping::MappingValue getCounter() const;
		
		/** Set counter value.
		 *
		 * Set new value of counter value.
		 *
		 * \param newCounter New value of counter value.
		 */
		virtual void setCounter(Ionflux::Mapping::MappingValue newCounter);
		
		/** Get adjustment value.
		 *
		 * \return Current value of adjustment value.
		 */
		virtual Ionflux::Mapping::MappingValue getAdjustment() const;
		
		/** Set adjustment value.
		 *
		 * Set new value of adjustment value.
		 *
		 * \param newAdjustment New value of adjustment value.
		 */
		virtual void setAdjustment(Ionflux::Mapping::MappingValue newAdjustment);
		
		/** Get modulus.
		 *
		 * \return Current value of modulus.
		 */
		virtual Ionflux::Mapping::MappingValue getModulus() const;
		
		/** Set modulus.
		 *
		 * Set new value of modulus.
		 *
		 * \param newModulus New value of modulus.
		 */
		virtual void setModulus(Ionflux::Mapping::MappingValue newModulus);
};

}

}

/** \file Count.hpp
 * \brief Count mapping (header).
 */
#endif
