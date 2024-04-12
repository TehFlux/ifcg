#ifndef IONFLUX_GEOUTILS_ITEMSOURCE
#define IONFLUX_GEOUTILS_ITEMSOURCE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ItemSource.hpp                  Source for items (header).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class BoxBoundsItem;

/// Class information for class ItemSource.
class ItemSourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ItemSourceClassInfo();
		/// Destructor.
		virtual ~ItemSourceClassInfo();
};

/** Source for items.
 * \ingroup geoutils
 *
 * This can be used to restore bounding box hierarchies in which the items 
 * have been replaced by dummy items with only IDs.
 */
class ItemSource
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const ItemSourceClassInfo itemSourceClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ItemSource object.
		 */
		ItemSource();
		
		/** Constructor.
		 *
		 * Construct new ItemSource object.
		 *
		 * \param other Other object.
		 */
		ItemSource(const Ionflux::GeoUtils::ItemSource& other);
		
		/** Destructor.
		 *
		 * Destruct ItemSource object.
		 */
		virtual ~ItemSource();
		
		/** Get item.
		 *
		 * Return the item with the specified ID. Throws an error if no valid 
		 * BoxBoundsItem can be returned. The ItemSource class does not 
		 * provide a usable implementation of this function, so it has to be 
		 * provided in a derived class.
		 *
		 * \param itemID Item ID.
		 */
		virtual Ionflux::GeoUtils::BoxBoundsItem* getItem(const std::string& 
		itemID) = 0;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::ItemSource& operator=(const 
		Ionflux::GeoUtils::ItemSource& other);
		
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

/** \file ItemSource.hpp
 * \brief Source for items (header).
 */
#endif
