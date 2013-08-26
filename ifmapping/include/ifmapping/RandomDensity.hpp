#ifndef IONFLUX_MAPPING_RANDOMDENSITY
#define IONFLUX_MAPPING_RANDOMDENSITY
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * RandomDensity.hpp               Random mapping (header).
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

/// Class information for class RandomDensity.
class RandomDensityClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		RandomDensityClassInfo();
		/// Destructor.
		virtual ~RandomDensityClassInfo();
};

/** Random mapping.
 * \ingroup ifmapping
 *
 * A mapping from a parameter to a random value. The density function of 
 * the distribution to be used can be specified as a mapping that maps the 
 * interval [0...1] to the interval [0...1]. If no density function is 
 * specified, an uniform distribution is used. Since the process for 
 * finding a suitable value is iterative, it is possible to specify a 
 * maximum number of iterations. An exception is thrown if the maximum 
 * number of iterations is exceeded. The actual value of the parameter is 
 * not relevant to the result.
 */
class RandomDensity
: public Ionflux::Mapping::ChainableMapping
{
	private:
		
	protected:
		/// Maximum iterations.
		unsigned int maxIters;
		
	public:
		/// Class information instance.
		static const RandomDensityClassInfo randomDensityClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new RandomDensity object.
		 */
		RandomDensity();
		
		/** Constructor.
		 *
		 * Construct new RandomDensity object.
		 *
		 * \param other Other object.
		 */
		RandomDensity(const Ionflux::Mapping::RandomDensity& other);
		
		/** Constructor.
		 *
		 * Construct new RandomDensity object.
		 *
		 * \param initFunc Source mapping.
		 * \param initMaxIters Maximum iterations.
		 * \param initScale Scale factor.
		 * \param initOffset Offset.
		 */
		RandomDensity(Ionflux::Mapping::Mapping* initFunc, 
		Ionflux::Mapping::MappingValue initMaxIters = MAX_ITERATIONS, 
		Ionflux::Mapping::MappingValue initScale = 1., 
		Ionflux::Mapping::MappingValue initOffset = 0.);
		
		/** Destructor.
		 *
		 * Destruct RandomDensity object.
		 */
		virtual ~RandomDensity();
		
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
		virtual Ionflux::Mapping::RandomDensity& operator=(const 
		Ionflux::Mapping::RandomDensity& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::RandomDensity* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::RandomDensity* 
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
		static Ionflux::Mapping::RandomDensity* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
};

}

}

/** \file RandomDensity.hpp
 * \brief Random mapping (header).
 */
#endif
