#ifndef IONFLUX_MAPPING_NOISEMAPTRANSFORM
#define IONFLUX_MAPPING_NOISEMAPTRANSFORM
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NoiseMapTransform.hpp           Noise map transform (header).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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
#include "noise/noiseutils.h"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Mapping
{

namespace Noise
{

/// Class information for class NoiseMapTransform.
class NoiseMapTransformClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		NoiseMapTransformClassInfo();
		/// Destructor.
		virtual ~NoiseMapTransformClassInfo();
};

/** Noise map transform.
 * \ingroup ifmapping
 *
 * Transform the values in a libnoise noise map by applying the mapping to 
 * each value. The optional scale factor and offset are applied to the 
 * original noise map value before the mapping is applied. The \c 
 * resultScale and \c resultOffset factors are applied after the mapping is
 * apllied, before the value is put back into the noise map.
 */
class NoiseMapTransform
: public Ionflux::ObjectBase::IFObject
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
		static const NoiseMapTransformClassInfo noiseMapTransformClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new NoiseMapTransform object.
		 */
		NoiseMapTransform();
		
		/** Constructor.
		 *
		 * Construct new NoiseMapTransform object.
		 *
		 * \param initFunc Source mapping.
		 * \param initScale Scale factor.
		 * \param initOffset Offset.
		 * \param initResultScale Result scale factor.
		 * \param initResultOffset Result offset.
		 */
		NoiseMapTransform(Ionflux::Mapping::Mapping* initFunc, 
		Ionflux::Mapping::MappingValue initScale = 0.5, 
		Ionflux::Mapping::MappingValue initOffset = 0.5, 
		Ionflux::Mapping::MappingValue initResultScale = 2., 
		Ionflux::Mapping::MappingValue initResultOffset = -1.);
		
		/** Destructor.
		 *
		 * Destruct NoiseMapTransform object.
		 */
		virtual ~NoiseMapTransform();
		
		/** Transform noise map.
		 *
		 * Transform the specified libnoide noise map.
		 *
		 * \param map Noise map.
		 */
		virtual void transform(noise::utils::NoiseMap& map);
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::Noise::NoiseMapTransform* 
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
		static Ionflux::Mapping::Noise::NoiseMapTransform* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
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

}

/** \file NoiseMapTransform.hpp
 * \brief Noise map transform (header).
 */
#endif
