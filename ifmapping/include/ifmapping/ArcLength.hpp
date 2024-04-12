#ifndef IONFLUX_MAPPING_ARCLENGTH
#define IONFLUX_MAPPING_ARCLENGTH
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ArcLength.hpp                   Arc length mapping (header).
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
#include "ifmapping/constants.hpp"
#include "ifmapping/PointMapping.hpp"
#include "ifmapping/Mapping.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class ArcLength.
class ArcLengthClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ArcLengthClassInfo();
		/// Destructor.
		virtual ~ArcLengthClassInfo();
};

/** Arc length mapping.
 * \ingroup ifmapping
 *
 * Calculates the arc length of a point mapping using a specified reference
 * parameter and relative error.
 */
class ArcLength
: public Ionflux::Mapping::Mapping
{
	private:
		
	protected:
		/// Mapping.
		Ionflux::Mapping::PointMapping* func;
		/// Offset.
		Ionflux::Mapping::MappingValue offset;
		/// Scale.
		Ionflux::Mapping::MappingValue scale;
		/// Reference parameter.
		Ionflux::Mapping::MappingValue refParam;
		/// Relative error.
		Ionflux::Mapping::MappingValue relativeError;
		/// Maximum number of iterations.
		unsigned int maxNumIterations;
		
	public:
		/// Default relative error.
		static const Ionflux::Mapping::MappingValue DEFAULT_RELATIVE_ERROR;
		/// Maximum number of iterations.
		static const unsigned int DEFAULT_MAX_NUM_ITERATIONS;
		/// Class information instance.
		static const ArcLengthClassInfo arcLengthClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ArcLength object.
		 */
		ArcLength();
		
		/** Constructor.
		 *
		 * Construct new ArcLength object.
		 *
		 * \param other Other object.
		 */
		ArcLength(const Ionflux::Mapping::ArcLength& other);
		
		/** Constructor.
		 *
		 * Construct new ArcLength object.
		 *
		 * \param initFunc Mapping.
		 * \param initOffset Offset.
		 * \param initScale Scale.
		 * \param initRefParam Reference parameter.
		 * \param initRelativeError Relative error.
		 * \param initMaxNumIterations Maximum number of iterations.
		 */
		ArcLength(Ionflux::Mapping::PointMapping* initFunc, 
		Ionflux::Mapping::MappingValue initOffset = 0., 
		Ionflux::Mapping::MappingValue initScale = 1., 
		Ionflux::Mapping::MappingValue initRefParam = 0., 
		Ionflux::Mapping::MappingValue initRelativeError = 
		DEFAULT_RELATIVE_ERROR, Ionflux::Mapping::MappingValue 
		initMaxNumIterations = DEFAULT_MAX_NUM_ITERATIONS);
		
		/** Destructor.
		 *
		 * Destruct ArcLength object.
		 */
		virtual ~ArcLength();
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Call the mapping.
		 *
		 * Calls the mapping with the specified parameter.
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
		virtual Ionflux::Mapping::ArcLength& operator=(const 
		Ionflux::Mapping::ArcLength& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::ArcLength* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::ArcLength* upcast(Ionflux::ObjectBase::IFObject*
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
		static Ionflux::Mapping::ArcLength* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new ArcLength object.
		 *
		 * \param initFunc Mapping.
		 * \param initOffset Offset.
		 * \param initScale Scale.
		 * \param initRefParam Reference parameter.
		 * \param initRelativeError Relative error.
		 * \param initMaxNumIterations Maximum number of iterations.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Mapping::ArcLength* 
		create(Ionflux::Mapping::PointMapping* initFunc, 
		Ionflux::Mapping::MappingValue initOffset = 0., 
		Ionflux::Mapping::MappingValue initScale = 1., 
		Ionflux::Mapping::MappingValue initRefParam = 0., 
		Ionflux::Mapping::MappingValue initRelativeError = 
		DEFAULT_RELATIVE_ERROR, Ionflux::Mapping::MappingValue 
		initMaxNumIterations = DEFAULT_MAX_NUM_ITERATIONS, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get mapping.
		 *
		 * \return Current value of mapping.
		 */
		virtual Ionflux::Mapping::PointMapping* getFunc() const;
		
		/** Set mapping.
		 *
		 * Set new value of mapping.
		 *
		 * \param newFunc New value of mapping.
		 */
		virtual void setFunc(Ionflux::Mapping::PointMapping* newFunc);
		
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
		
		/** Get scale.
		 *
		 * \return Current value of scale.
		 */
		virtual Ionflux::Mapping::MappingValue getScale() const;
		
		/** Set scale.
		 *
		 * Set new value of scale.
		 *
		 * \param newScale New value of scale.
		 */
		virtual void setScale(Ionflux::Mapping::MappingValue newScale);
		
		/** Get reference parameter.
		 *
		 * \return Current value of reference parameter.
		 */
		virtual Ionflux::Mapping::MappingValue getRefParam() const;
		
		/** Set reference parameter.
		 *
		 * Set new value of reference parameter.
		 *
		 * \param newRefParam New value of reference parameter.
		 */
		virtual void setRefParam(Ionflux::Mapping::MappingValue newRefParam);
		
		/** Get relative error.
		 *
		 * \return Current value of relative error.
		 */
		virtual Ionflux::Mapping::MappingValue getRelativeError() const;
		
		/** Set relative error.
		 *
		 * Set new value of relative error.
		 *
		 * \param newRelativeError New value of relative error.
		 */
		virtual void setRelativeError(Ionflux::Mapping::MappingValue 
		newRelativeError);
		
		/** Get maximum number of iterations.
		 *
		 * \return Current value of maximum number of iterations.
		 */
		virtual unsigned int getMaxNumIterations() const;
		
		/** Set maximum number of iterations.
		 *
		 * Set new value of maximum number of iterations.
		 *
		 * \param newMaxNumIterations New value of maximum number of iterations.
		 */
		virtual void setMaxNumIterations(unsigned int newMaxNumIterations);
};

}

}

/** \file ArcLength.hpp
 * \brief Arc length mapping (header).
 */
#endif
