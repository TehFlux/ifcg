#ifndef IONFLUX_MAPPING_BRENTLINEARROOTFINDER
#define IONFLUX_MAPPING_BRENTLINEARROOTFINDER
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BrentLinearRootFinder.hpp       Brent linear root finder (header).
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
#include "ifmapping/RootFinder.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class BrentLinearRootFinder.
class BrentLinearRootFinderClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		BrentLinearRootFinderClassInfo();
		/// Destructor.
		virtual ~BrentLinearRootFinderClassInfo();
};

/** Brent linear root finder.
 * \ingroup ifmapping
 *
 * Finds the root of a function in a specified interval using Brent's 
 * method with linear interpolation.
 */
class BrentLinearRootFinder
: public Ionflux::Mapping::RootFinder
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const BrentLinearRootFinderClassInfo brentLinearRootFinderClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new BrentLinearRootFinder object.
		 */
		BrentLinearRootFinder();
		
		/** Constructor.
		 *
		 * Construct new BrentLinearRootFinder object.
		 *
		 * \param other Other object.
		 */
		BrentLinearRootFinder(const Ionflux::Mapping::BrentLinearRootFinder& other);
		
		/** Destructor.
		 *
		 * Destruct BrentLinearRootFinder object.
		 */
		virtual ~BrentLinearRootFinder();
		
		/** Find root.
		 *
		 * Find a root in the specified interval.
		 *
		 * \param a Lower bound.
		 * \param b Upper bound.
		 * \param delta Delta to be used as the abort condition.
		 *
		 * \return Root of the function.
		 */
		virtual Ionflux::Mapping::MappingValue 
		findRoot(Ionflux::Mapping::MappingValue a = 0., 
		Ionflux::Mapping::MappingValue b = 0., Ionflux::Mapping::MappingValue 
		delta = 0.0001) const;
		
		/** Find root.
		 *
		 * Find a root in the specified interval.
		 *
		 * \param a Lower bound.
		 * \param b Upper bound.
		 * \param delta Delta to be used as the abort condition.
		 * \param tr0 Threshold for bisection.
		 * \param samples Number of samples.
		 * \param maxIters Maximum number of iterations.
		 * \param i Iteration count.
		 * \param forceBisection Force bisection.
		 * \param bPrev Previous upper bound.
		 *
		 * \return Root of the function.
		 */
		virtual Ionflux::Mapping::MappingValue 
		findRoot(Ionflux::Mapping::MappingValue a, Ionflux::Mapping::MappingValue
		b, Ionflux::Mapping::MappingValue delta, Ionflux::Mapping::MappingValue 
		tr0, unsigned int samples = 101, unsigned int maxIters = 50, unsigned int
		i = 0, bool forceBisection = false, Ionflux::Mapping::MappingValue bPrev 
		= 0.) const;
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Mapping::BrentLinearRootFinder& operator=(const 
		Ionflux::Mapping::BrentLinearRootFinder& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::BrentLinearRootFinder* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::BrentLinearRootFinder* 
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
		static Ionflux::Mapping::BrentLinearRootFinder* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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

/** \file BrentLinearRootFinder.hpp
 * \brief Brent linear root finder (header).
 */
#endif
