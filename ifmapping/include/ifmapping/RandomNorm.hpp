#ifndef IONFLUX_MAPPING_RANDOMNORM
#define IONFLUX_MAPPING_RANDOMNORM
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * RandomNorm.hpp                  Random mapping (header).
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

/// Class information for class RandomNorm.
class RandomNormClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		RandomNormClassInfo();
		/// Destructor.
		virtual ~RandomNormClassInfo();
};

/** Random mapping.
 * \ingroup ifmapping
 *
 * A mapping from a parameter to a random value drawn from a normal 
 * distribution. The mean and standard deviation of the normal distribution
 * can be set as properties of the object. The actual value of the 
 * parameter is not relevant to the result.
 */
class RandomNorm
: public Ionflux::Mapping::ChainableMapping
{
	private:
		
	protected:
		/// Mean value.
		Ionflux::Mapping::MappingValue mean;
		/// Standard deviation.
		Ionflux::Mapping::MappingValue stdDev;
		
	public:
		/// Class information instance.
		static const RandomNormClassInfo randomNormClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new RandomNorm object.
		 */
		RandomNorm();
		
		/** Constructor.
		 *
		 * Construct new RandomNorm object.
		 *
		 * \param other Other object.
		 */
		RandomNorm(const Ionflux::Mapping::RandomNorm& other);
		
		/** Constructor.
		 *
		 * Construct new RandomNorm object.
		 *
		 * \param initMean Mean value.
		 * \param initStdDev Standard deviation.
		 * \param initScale Scale factor.
		 * \param initOffset Offset.
		 * \param initFunc Source mapping.
		 */
		RandomNorm(Ionflux::Mapping::MappingValue initMean, 
		Ionflux::Mapping::MappingValue initStdDev = 1., 
		Ionflux::Mapping::MappingValue initScale = 1., 
		Ionflux::Mapping::MappingValue initOffset = 0., 
		Ionflux::Mapping::Mapping* initFunc = 0);
		
		/** Destructor.
		 *
		 * Destruct RandomNorm object.
		 */
		virtual ~RandomNorm();
		
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
		virtual Ionflux::Mapping::RandomNorm& operator=(const 
		Ionflux::Mapping::RandomNorm& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::RandomNorm* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::RandomNorm* 
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
		static Ionflux::Mapping::RandomNorm* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get mean value.
		 *
		 * \return Current value of mean value.
		 */
		virtual Ionflux::Mapping::MappingValue getMean() const;
		
		/** Set mean value.
		 *
		 * Set new value of mean value.
		 *
		 * \param newMean New value of mean value.
		 */
		virtual void setMean(Ionflux::Mapping::MappingValue newMean);
		
		/** Get standard deviation.
		 *
		 * \return Current value of standard deviation.
		 */
		virtual Ionflux::Mapping::MappingValue getStdDev() const;
		
		/** Set standard deviation.
		 *
		 * Set new value of standard deviation.
		 *
		 * \param newStdDev New value of standard deviation.
		 */
		virtual void setStdDev(Ionflux::Mapping::MappingValue newStdDev);
};

}

}

/** \file RandomNorm.hpp
 * \brief Random mapping (header).
 */
#endif
