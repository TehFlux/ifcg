#ifndef IONFLUX_MAPPING_LINEAR
#define IONFLUX_MAPPING_LINEAR
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Linear.hpp                      Linear mapping (header).
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

/// Class information for class Linear.
class LinearClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		LinearClassInfo();
		/// Destructor.
		virtual ~LinearClassInfo();
};

/** Linear mapping.
 * \ingroup ifmapping
 *
 * A mapping from a parameter to a linear interpolation of two values. The 
 * lower interpolation value corresponds to a parameter value of 0, the 
 * upper interpolation value corresponds to a parameter value of 1.
 */
class Linear
: public Ionflux::Mapping::ChainableMapping
{
	private:
		
	protected:
		/// Lower interpolation value.
		Ionflux::Mapping::MappingValue lower;
		/// Upper interpolation value.
		Ionflux::Mapping::MappingValue upper;
		
	public:
		/// Class information instance.
		static const LinearClassInfo linearClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Linear object.
		 */
		Linear();
		
		/** Constructor.
		 *
		 * Construct new Linear object.
		 *
		 * \param other Other object.
		 */
		Linear(const Ionflux::Mapping::Linear& other);
		
		/** Constructor.
		 *
		 * Construct new Linear object.
		 *
		 * \param initLower Lower interpolation value.
		 * \param initUpper Upper interpolation value.
		 * \param initScale Scale factor.
		 * \param initOffset Offset.
		 * \param initFunc Source mapping.
		 */
		Linear(Ionflux::Mapping::MappingValue initLower, 
		Ionflux::Mapping::MappingValue initUpper, Ionflux::Mapping::MappingValue 
		initScale = 1., Ionflux::Mapping::MappingValue initOffset = 0., 
		Ionflux::Mapping::Mapping* initFunc = 0);
		
		/** Destructor.
		 *
		 * Destruct Linear object.
		 */
		virtual ~Linear();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
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
		
		/** Create linear mapping.
		 *
		 * Create linear mapping
		 *
		 * \param initLower Lower interpolation value.
		 * \param initUpper Upper interpolation value.
		 *
		 * \return New mapping.
		 */
		static Ionflux::Mapping::Linear* create(Ionflux::Mapping::MappingValue 
		initLower, Ionflux::Mapping::MappingValue initUpper);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Mapping::Linear& operator=(const 
		Ionflux::Mapping::Linear& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::Linear* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::Linear* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::Mapping::Linear* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get lower interpolation value.
		 *
		 * \return Current value of lower interpolation value.
		 */
		virtual Ionflux::Mapping::MappingValue getLower() const;
		
		/** Set lower interpolation value.
		 *
		 * Set new value of lower interpolation value.
		 *
		 * \param newLower New value of lower interpolation value.
		 */
		virtual void setLower(Ionflux::Mapping::MappingValue newLower);
		
		/** Get upper interpolation value.
		 *
		 * \return Current value of upper interpolation value.
		 */
		virtual Ionflux::Mapping::MappingValue getUpper() const;
		
		/** Set upper interpolation value.
		 *
		 * Set new value of upper interpolation value.
		 *
		 * \param newUpper New value of upper interpolation value.
		 */
		virtual void setUpper(Ionflux::Mapping::MappingValue newUpper);
};

}

}

/** \file Linear.hpp
 * \brief Linear mapping (header).
 */
#endif
