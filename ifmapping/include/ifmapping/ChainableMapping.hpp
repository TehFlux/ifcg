#ifndef IONFLUX_MAPPING_CHAINABLEMAPPING
#define IONFLUX_MAPPING_CHAINABLEMAPPING
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ChainableMapping.hpp            Chainable mapping (header).
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
#include "ifmapping/Mapping.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class ChainableMapping.
class ChainableMappingClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ChainableMappingClassInfo();
		/// Destructor.
		virtual ~ChainableMappingClassInfo();
};

/** Chainable mapping.
 * \ingroup ifmapping
 *
 * Abstract base class for mappings that are chainable. If the source 
 * mapping is set, a chainable mapping calls the source mapping with the 
 * current parameter and uses the resulting value as its own parameter. If 
 * the source mapping is not specified, the mapping will use the parameter 
 * itself as its parameter. In other words, if M is the chainable mapping, 
 * the result of M(t) is either M(t) or M(F(t) if F is set. An optional 
 * scale factor and offset may be specified. These are used to transform 
 * the parameter before applying the mapping if the source mapping is not 
 * used. The \c resultScale and \c resultOffset factors are used to 
 * transform the resulting value.
 */
class ChainableMapping
: public Ionflux::Mapping::Mapping
{
	private:
		
	protected:
		/// Source mapping.
		Ionflux::Mapping::Mapping* func;
		/// Scale factor.
		Ionflux::Mapping::MappingValue scale;
		/// Offset.
		Ionflux::Mapping::MappingValue offset;
		/// Result scale factor.
		Ionflux::Mapping::MappingValue resultScale;
		/// Result offset.
		Ionflux::Mapping::MappingValue resultOffset;
		
	public:
		/// Class information instance.
		static const ChainableMappingClassInfo chainableMappingClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ChainableMapping object.
		 */
		ChainableMapping();
		
		/** Constructor.
		 *
		 * Construct new ChainableMapping object.
		 *
		 * \param other Other object.
		 */
		ChainableMapping(const Ionflux::Mapping::ChainableMapping& other);
		
		/** Constructor.
		 *
		 * Construct new ChainableMapping object.
		 *
		 * \param initFunc Source mapping.
		 * \param initScale Scale factor.
		 * \param initOffset Offset.
		 * \param initResultScale Result scale factor.
		 * \param initResultOffset Result offset.
		 */
		ChainableMapping(Ionflux::Mapping::Mapping* initFunc, 
		Ionflux::Mapping::MappingValue initScale = 1., 
		Ionflux::Mapping::MappingValue initOffset = 0., 
		Ionflux::Mapping::MappingValue initResultScale = 1., 
		Ionflux::Mapping::MappingValue initResultOffset = 0.);
		
		/** Destructor.
		 *
		 * Destruct ChainableMapping object.
		 */
		virtual ~ChainableMapping();
		
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
		 */
		virtual Ionflux::Mapping::MappingValue 
		callWithParam(Ionflux::Mapping::MappingValue value) const = 0;
		
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
		virtual Ionflux::Mapping::ChainableMapping& operator=(const 
		Ionflux::Mapping::ChainableMapping& other);
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::ChainableMapping* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
		/** Get source mapping.
		 *
		 * \return Current value of source mapping.
		 */
		virtual Ionflux::Mapping::Mapping* getFunc() const;
		
		/** Set source mapping.
		 *
		 * Set new value of source mapping.
		 *
		 * \param newFunc New value of source mapping.
		 */
		virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
		
		/** Get scale factor.
		 *
		 * \return Current value of scale factor.
		 */
		virtual Ionflux::Mapping::MappingValue getScale() const;
		
		/** Set scale factor.
		 *
		 * Set new value of scale factor.
		 *
		 * \param newScale New value of scale factor.
		 */
		virtual void setScale(Ionflux::Mapping::MappingValue newScale);
		
		/** Get offset.
		 *
		 * \return Current value of offset.
		 */
		virtual Ionflux::Mapping::MappingValue getOffset() const;
		
		/** Set offset.
		 *
		 * Set new value of offset.
		 *
		 * \param newOffset New value of offset.
		 */
		virtual void setOffset(Ionflux::Mapping::MappingValue newOffset);
		
		/** Get result scale factor.
		 *
		 * \return Current value of result scale factor.
		 */
		virtual Ionflux::Mapping::MappingValue getResultScale() const;
		
		/** Set result scale factor.
		 *
		 * Set new value of result scale factor.
		 *
		 * \param newResultScale New value of result scale factor.
		 */
		virtual void setResultScale(Ionflux::Mapping::MappingValue 
		newResultScale);
		
		/** Get result offset.
		 *
		 * \return Current value of result offset.
		 */
		virtual Ionflux::Mapping::MappingValue getResultOffset() const;
		
		/** Set result offset.
		 *
		 * Set new value of result offset.
		 *
		 * \param newResultOffset New value of result offset.
		 */
		virtual void setResultOffset(Ionflux::Mapping::MappingValue 
		newResultOffset);
};

}

}

/** \file ChainableMapping.hpp
 * \brief Chainable mapping (header).
 */
#endif
