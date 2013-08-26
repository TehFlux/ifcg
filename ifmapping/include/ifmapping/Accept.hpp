#ifndef IONFLUX_MAPPING_ACCEPT
#define IONFLUX_MAPPING_ACCEPT
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Accept.hpp                      Accept method mapping (header).
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
#include "ifmapping/constants.hpp"
#include "ifmapping/ChainableMapping.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class Accept.
class AcceptClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		AcceptClassInfo();
		/// Destructor.
		virtual ~AcceptClassInfo();
};

/** Accept method mapping.
 * \ingroup ifmapping
 *
 * A mapping that obtains a value from its source mapping using the accept 
 * method to make sure the value is within the target range. This means the
 * source mapping is called up to \c maxIters times to provide a value 
 * within the range. If the method does not yield a value within the range,
 * an exception is thrown.
 */
class Accept
: public Ionflux::Mapping::ChainableMapping
{
	private:
		
	protected:
		/// Maximum iterations.
		unsigned int maxIters;
		/// Acceptable range.
		Ionflux::Mapping::Range acceptRange;
		
	public:
		/// Class information instance.
		static const AcceptClassInfo acceptClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Accept object.
		 */
		Accept();
		
		/** Constructor.
		 *
		 * Construct new Accept object.
		 *
		 * \param other Other object.
		 */
		Accept(const Ionflux::Mapping::Accept& other);
		
		/** Constructor.
		 *
		 * Construct new Accept object.
		 *
		 * \param initFunc Source mapping.
		 * \param initMaxIters Maximum iterations.
		 * \param initScale Scale factor.
		 * \param initOffset Offset.
		 */
		Accept(Ionflux::Mapping::Mapping* initFunc, unsigned int initMaxIters = 
		MAX_ITERATIONS, Ionflux::Mapping::MappingValue initScale = 1., 
		Ionflux::Mapping::MappingValue initOffset = 0.);
		
		/** Destructor.
		 *
		 * Destruct Accept object.
		 */
		virtual ~Accept();
		
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
		
		/** Call the mapping.
		 *
		 * Calls the mapping using the conventions for chainable mappings. 
		 * This means callWithParam() is called with the parameter if no 
		 * source function has been set. Otherwise, callWithParam() is called 
		 * with the result of calling the source mapping with the parameter.
		 *
		 * \param value Value.
		 *
		 * \return Mapped value.
		 */
		virtual Ionflux::Mapping::MappingValue 
		call(Ionflux::Mapping::MappingValue value) const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Mapping::Accept& operator=(const 
		Ionflux::Mapping::Accept& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::Accept* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::Accept* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::Mapping::Accept* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
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
		
		/** Get acceptable range.
		 *
		 * \return Current value of acceptable range.
		 */
		virtual Ionflux::Mapping::Range getAcceptRange() const;
		
		/** Set acceptable range.
		 *
		 * Set new value of acceptable range.
		 *
		 * \param newAcceptRange New value of acceptable range.
		 */
		virtual void setAcceptRange(const Ionflux::Mapping::Range& 
		newAcceptRange);
};

}

}

/** \file Accept.hpp
 * \brief Accept method mapping (header).
 */
#endif
