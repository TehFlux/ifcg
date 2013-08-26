#ifndef IONFLUX_GEOUTILS_SPLITSET
#define IONFLUX_GEOUTILS_SPLITSET
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SplitSet.hpp                    Axis split set (header).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * GeoUtils - Ionflux' Geometry Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with GeoUtils - Ionflux' Geometry Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Split.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class SplitSet.
class SplitSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		SplitSetClassInfo();
		/// Destructor.
		virtual ~SplitSetClassInfo();
};

/** Axis split set.
 * \ingroup geoutils
 *
 * A set of axis splits.
 */
class SplitSet
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Split vector.
		std::vector<Ionflux::GeoUtils::Split*> splits;
		
	public:
		/// Class information instance.
		static const SplitSetClassInfo splitSetClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new SplitSet object.
		 */
		SplitSet();
		
		/** Constructor.
		 *
		 * Construct new SplitSet object.
		 *
		 * \param other Other object.
		 */
		SplitSet(const Ionflux::GeoUtils::SplitSet& other);
		
		/** Destructor.
		 *
		 * Destruct SplitSet object.
		 */
		virtual ~SplitSet();
		
		/** Add splits.
		 *
		 * Add a number of splits for the specified axis.
		 *
		 * \param axis Axis.
		 * \param num Number of splits.
		 *
		 * \return Splits that have been added.
		 */
		virtual Ionflux::GeoUtils::SplitVector 
		addSplits(Ionflux::GeoUtils::AxisID axis, unsigned int num = 1);
		
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
		virtual Ionflux::GeoUtils::SplitSet& operator=(const 
		Ionflux::GeoUtils::SplitSet& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::SplitSet* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::SplitSet* upcast(Ionflux::ObjectBase::IFObject*
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
		static Ionflux::GeoUtils::SplitSet* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		
		/** Get number of splits.
		 *
		 * \return Number of splits.
		 */
		virtual unsigned int getNumSplits() const;
		
		/** Get split.
		 *
		 * Get the split at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Split at specified index.
		 */
		virtual Ionflux::GeoUtils::Split* getSplit(unsigned int elementIndex = 0)
		const;
		
		/** Find split.
		 *
		 * Find the specified occurence of a split.
		 *
		 * \param needle Split to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the split, or -1 if the split cannot be found.
		 */
		virtual int findSplit(Ionflux::GeoUtils::Split* needle, unsigned int 
		occurence = 1) const;
        
		/** Get split vector.
		 *
		 * \return split vector.
		 */
		virtual std::vector<Ionflux::GeoUtils::Split*>& getSplits();
		
		/** Add split.
		 *
		 * Add a split.
		 *
		 * \param addElement Split to be added.
		 */
		virtual void addSplit(Ionflux::GeoUtils::Split* addElement);
		
		/** Remove split.
		 *
		 * Remove a split.
		 *
		 * \param removeElement Split to be removed.
		 */
		virtual void removeSplit(Ionflux::GeoUtils::Split* removeElement);
		
		/** Remove split.
		 *
		 * Remove a split.
		 *
		 * \param removeIndex Split to be removed.
		 */
		virtual void removeSplitIndex(unsigned int removeIndex);
		
		/** Clear splits.
		 *
		 * Clear all splits.
		 */
		virtual void clearSplits();
};

}

}

/** \file SplitSet.hpp
 * \brief Axis split set (header).
 */
#endif
