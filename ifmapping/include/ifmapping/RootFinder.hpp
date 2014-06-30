#ifndef IONFLUX_MAPPING_ROOTFINDER
#define IONFLUX_MAPPING_ROOTFINDER
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * RootFinder.hpp                  Root finder (header).
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

namespace Ionflux
{

namespace Mapping
{

/// Class information for class RootFinder.
class RootFinderClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		RootFinderClassInfo();
		/// Destructor.
		virtual ~RootFinderClassInfo();
};

/** Root finder.
 * \ingroup ifmapping
 *
 * Finds the root of a function in a specified interval.
 */
class RootFinder
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Source function.
		Ionflux::Mapping::Mapping* func;
		
	public:
		/// Class information instance.
		static const RootFinderClassInfo rootFinderClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new RootFinder object.
		 */
		RootFinder();
		
		/** Constructor.
		 *
		 * Construct new RootFinder object.
		 *
		 * \param other Other object.
		 */
		RootFinder(const Ionflux::Mapping::RootFinder& other);
		
		/** Destructor.
		 *
		 * Destruct RootFinder object.
		 */
		virtual ~RootFinder();
		
		/** Compare signs of function values.
		 *
		 * Compare the signs of the function values at the specified 
		 * arguments.
		 *
		 * \param a First argument.
		 * \param b Second argument.
		 *
		 * \return 0 if the signs are the same, 1 otherwise.
		 */
		virtual Ionflux::Mapping::MappingValue 
		compareSigns(Ionflux::Mapping::MappingValue a, 
		Ionflux::Mapping::MappingValue b) const;
		
		/** Find start intervals.
		 *
		 * Find start intervals for the root-finding algorithm. This is 
		 * accomplished by subdividing the default interval evenly according 
		 * to the number of samples, evaluating the function on the sample 
		 * points, and then finding two sample points with opposite signs. 
		 * Suitable intervals are added to the target vector.
		 *
		 * \param target Target vector.
		 * \param samples Number of samples.
		 * \param a Lower bound.
		 * \param b Upper bound.
		 */
		virtual void findStartIntervals(Ionflux::Mapping::RangeVector& target, 
		unsigned int samples = 101, Ionflux::Mapping::MappingValue a = 0., 
		Ionflux::Mapping::MappingValue b = 1.) const;
		
		/** Find start interval.
		 *
		 * Find a start interval for the root-finding algorithm. This is 
		 * accomplished by subdividing the default interval evenly according 
		 * to the number of samples, evaluating the function on the sample 
		 * points, and then finding two sample points with opposite signs.
		 *
		 * \param samples Number of samples.
		 * \param a Lower bound.
		 * \param b Upper bound.
		 *
		 * \return Start interval.
		 */
		virtual Ionflux::Mapping::Range findStartInterval(unsigned int samples = 
		101, Ionflux::Mapping::MappingValue a = 0., 
		Ionflux::Mapping::MappingValue b = 1.) const;
		
		/** Call the mapping.
		 *
		 * Calls the mapping with the specified parameter.
		 *
		 * \param a Lower bound.
		 * \param b Upper bound.
		 * \param delta Delta to be used as the abort condition.
		 *
		 * \return Root.
		 */
		virtual Ionflux::Mapping::MappingValue 
		operator()(Ionflux::Mapping::MappingValue a = 0., 
		Ionflux::Mapping::MappingValue b = 0., Ionflux::Mapping::MappingValue 
		delta = 0.0001) const;
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Find root.
		 *
		 * Find a root in the specified interval.
		 *
		 * \param a Lower bound.
		 * \param b Upper bound.
		 * \param delta Delta to be used as the abort condition.
		 */
		virtual Ionflux::Mapping::MappingValue 
		findRoot(Ionflux::Mapping::MappingValue a = 0., 
		Ionflux::Mapping::MappingValue b = 0., Ionflux::Mapping::MappingValue 
		delta = 0.0001) const = 0;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Mapping::RootFinder& operator=(const 
		Ionflux::Mapping::RootFinder& other);
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::RootFinder* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get source function.
		 *
		 * \return Current value of source function.
		 */
		virtual Ionflux::Mapping::Mapping* getFunc() const;
		
		/** Set source function.
		 *
		 * Set new value of source function.
		 *
		 * \param newFunc New value of source function.
		 */
		virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
};

}

}

/** \file RootFinder.hpp
 * \brief Root finder (header).
 */
#endif
