#ifndef IONFLUX_MAPPING_NOISEMAPPING
#define IONFLUX_MAPPING_NOISEMAPPING
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NoiseMapping.hpp                Noise mapping module (header).
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
#include "ifobject/IFObject.hpp"
#include "noise/module/modulebase.h"

namespace Ionflux
{

namespace Mapping
{

namespace Noise
{

/// Class information for class NoiseMapping.
class NoiseMappingClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		NoiseMappingClassInfo();
		/// Destructor.
		virtual ~NoiseMappingClassInfo();
};

/** Noise mapping module.
 * \ingroup ifmapping
 *
 * A libnoise module that wraps a Mapping. The value resulting from the 
 * module is the result of applying the mapping to the source module. The 
 * optional scale factor and offset are applied to the input value before 
 * the mapping is applied. The \c resultScale and \c resultOffset factors 
 * are applied after the mapping is apllied, before the value is returned 
 * to the caller.
 */
class NoiseMapping
: public Ionflux::ObjectBase::IFObject, public noise::module::Module
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
		static const NoiseMappingClassInfo noiseMappingClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new NoiseMapping object.
		 */
		NoiseMapping();
		
		/** Constructor.
		 *
		 * Construct new NoiseMapping object.
		 *
		 * \param initFunc Source mapping.
		 * \param initScale Scale factor.
		 * \param initOffset Offset.
		 * \param initResultScale Result scale factor.
		 * \param initResultOffset Result offset.
		 */
		NoiseMapping(Ionflux::Mapping::Mapping* initFunc, 
		Ionflux::Mapping::MappingValue initScale = 0.5, 
		Ionflux::Mapping::MappingValue initOffset = 0.5, 
		Ionflux::Mapping::MappingValue initResultScale = 2., 
		Ionflux::Mapping::MappingValue initResultOffset = -1.);
		
		/** Destructor.
		 *
		 * Destruct NoiseMapping object.
		 */
		virtual ~NoiseMapping();
		
		/** Get number of source modules.
		 *
		 * Get the number of source modules.
		 *
		 * \return Number of source modules.
		 */
		virtual int GetSourceModuleCount() const;
		
		/** Get value.
		 *
		 * Get the value resulting from applying the mapping to the result 
		 * value of the source module. Scale and offset are applied to the 
		 * result value of the source module before the mapping is applied.
		 *
		 * \param x X coordinate.
		 * \param y Y coordinate.
		 * \param z Z coordinate.
		 *
		 * \return Mapped result value.
		 */
		virtual double GetValue(double x, double y, double z) const;
		
		/** Set source module.
		 *
		 * Set the source module.
		 *
		 * \param sourceModule Source Module.
		 */
		virtual void SetSourceModule(const noise::module::Module& sourceModule);
		
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
		static Ionflux::Mapping::Noise::NoiseMapping* 
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
		static Ionflux::Mapping::Noise::NoiseMapping* 
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

/** \file NoiseMapping.hpp
 * \brief Noise mapping module (header).
 */
#endif
