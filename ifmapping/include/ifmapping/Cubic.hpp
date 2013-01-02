#ifndef IONFLUX_MAPPING_CUBIC
#define IONFLUX_MAPPING_CUBIC
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Cubic.hpp                       Cubic mapping (header).
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
#include "ifmapping/Linear.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class Cubic.
class CubicClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		CubicClassInfo();
		/// Destructor.
		virtual ~CubicClassInfo();
};

/** Cubic mapping.
 * \ingroup ifmapping
 *
 * A mapping from a parameter to a cubic S-curve interpolation of two 
 * values. The lower interpolation value corresponds to a parameter value 
 * of 0, the upper interpolation value corresponds to a parameter value of 
 * 1.
 */
class Cubic
: public Ionflux::Mapping::Linear
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const CubicClassInfo cubicClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Cubic object.
		 */
		Cubic();
		
		/** Constructor.
		 *
		 * Construct new Cubic object.
		 *
		 * \param other Other object.
		 */
		Cubic(const Ionflux::Mapping::Cubic& other);
		
		/** Constructor.
		 *
		 * Construct new Cubic object.
		 *
		 * \param initLower Lower interpolation value.
		 * \param initUpper Upper interpolation value.
		 */
		Cubic(Ionflux::Mapping::MappingValue initLower, 
		Ionflux::Mapping::MappingValue initUpper);
		
		/** Destructor.
		 *
		 * Destruct Cubic object.
		 */
		virtual ~Cubic();
		
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
		virtual Ionflux::Mapping::Cubic& operator=(const Ionflux::Mapping::Cubic&
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::Cubic* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::Cubic* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::Mapping::Cubic* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

}

}

/** \file Cubic.hpp
 * \brief Cubic mapping (header).
 */
#endif
