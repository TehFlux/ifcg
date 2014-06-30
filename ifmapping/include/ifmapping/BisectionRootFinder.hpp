#ifndef IONFLUX_MAPPING_BISECTIONROOTFINDER
#define IONFLUX_MAPPING_BISECTIONROOTFINDER
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BisectionRootFinder.hpp         Bisection root finder (header).
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
#include "ifmapping/RootFinder.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class BisectionRootFinder.
class BisectionRootFinderClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		BisectionRootFinderClassInfo();
		/// Destructor.
		virtual ~BisectionRootFinderClassInfo();
};

/** Bisection root finder.
 * \ingroup ifmapping
 *
 * Finds the root of a function in a specified interval using the bisection
 * method.
 */
class BisectionRootFinder
: public Ionflux::Mapping::RootFinder
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const BisectionRootFinderClassInfo bisectionRootFinderClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new BisectionRootFinder object.
		 */
		BisectionRootFinder();
		
		/** Constructor.
		 *
		 * Construct new BisectionRootFinder object.
		 *
		 * \param other Other object.
		 */
		BisectionRootFinder(const Ionflux::Mapping::BisectionRootFinder& other);
		
		/** Destructor.
		 *
		 * Destruct BisectionRootFinder object.
		 */
		virtual ~BisectionRootFinder();
		
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
		 * \param samples Number of samples.
		 *
		 * \return Root of the function.
		 */
		virtual Ionflux::Mapping::MappingValue 
		findRoot(Ionflux::Mapping::MappingValue a, Ionflux::Mapping::MappingValue
		b, Ionflux::Mapping::MappingValue delta, unsigned int samples) const;
		
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
		virtual Ionflux::Mapping::BisectionRootFinder& operator=(const 
		Ionflux::Mapping::BisectionRootFinder& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::BisectionRootFinder* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::BisectionRootFinder* 
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
		static Ionflux::Mapping::BisectionRootFinder* 
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

/** \file BisectionRootFinder.hpp
 * \brief Bisection root finder (header).
 */
#endif
