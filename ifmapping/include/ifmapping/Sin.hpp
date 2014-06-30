#ifndef IONFLUX_MAPPING_SIN
#define IONFLUX_MAPPING_SIN
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Sin.hpp                         Sine mapping (header).
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

/// Class information for class Sin.
class SinClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		SinClassInfo();
		/// Destructor.
		virtual ~SinClassInfo();
};

/** Sine mapping.
 * \ingroup ifmapping
 *
 * A mapping from a parameter to the sine function value of that parameter.
 */
class Sin
: public Ionflux::Mapping::ChainableMapping
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const SinClassInfo sinClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Sin object.
		 */
		Sin();
		
		/** Constructor.
		 *
		 * Construct new Sin object.
		 *
		 * \param other Other object.
		 */
		Sin(const Ionflux::Mapping::Sin& other);
		
		/** Constructor.
		 *
		 * Construct new Sin object.
		 *
		 * \param initScale Scale factor.
		 * \param initOffset Offset.
		 * \param initFunc Source mapping.
		 */
		Sin(Ionflux::Mapping::MappingValue initScale, 
		Ionflux::Mapping::MappingValue initOffset = 0., 
		Ionflux::Mapping::Mapping* initFunc = 0);
		
		/** Destructor.
		 *
		 * Destruct Sin object.
		 */
		virtual ~Sin();
		
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
		virtual Ionflux::Mapping::Sin& operator=(const Ionflux::Mapping::Sin& 
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::Sin* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::Sin* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::Mapping::Sin* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
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

/** \file Sin.hpp
 * \brief Sine mapping (header).
 */
#endif
