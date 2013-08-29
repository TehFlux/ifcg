#ifndef IONFLUX_GEOUTILS_BOXBOUNDSITEMCOMPAREDISTANCEVEC3
#define IONFLUX_GEOUTILS_BOXBOUNDSITEMCOMPAREDISTANCEVEC3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BoxBoundsItemCompareDistanceVec3.hpp  Box bounds item comparison 
 * function object: Distance to point (header).
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
#include "geoutils/BoxBoundsItem.hpp"
#include "geoutils/BoxBoundsItemCompare.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/** Box bounds item comparison function object: Distance to point.
 * \ingroup geoutils
 *
 * A function object that compares box bounds items based on their distance
 * to a reference point, indicated by its coordinate vector.
 */
class BoxBoundsItemCompareDistanceVec3
: public Ionflux::GeoUtils::BoxBoundsItemCompare
{
	private:
		
	protected:
		/// reference.
		Ionflux::GeoUtils::Vector3 reference;
		
	public:
		
		/** Constructor.
		 *
		 * Construct new BoxBoundsItemCompareDistanceVec3 object.
		 */
		BoxBoundsItemCompareDistanceVec3();
		
		/** Constructor.
		 *
		 * Construct new BoxBoundsItemCompareDistanceVec3 object.
		 *
		 * \param other Other object.
		 */
		BoxBoundsItemCompareDistanceVec3(const Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3& other);
		
		/** Constructor.
		 *
		 * Construct new BoxBoundsItemCompareDistanceVec3 object.
		 *
		 * \param initReference reference.
		 * \param initInvert Invert order.
		 */
		BoxBoundsItemCompareDistanceVec3(const Ionflux::GeoUtils::Vector3& 
		initReference, bool initInvert = false);
		
		/** Destructor.
		 *
		 * Destruct BoxBoundsItemCompareDistanceVec3 object.
		 */
		virtual ~BoxBoundsItemCompareDistanceVec3();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Compare box bounds items.
		 *
		 * Compare two box bounds items.
		 *
		 * \param b0 Box bounds item (0).
		 * \param b1 Box bounds item (1).
		 *
		 * \return \c true if the box bounds item p0 goes before the box bounds 
		 * item p1, \c false otherwise.
		 */
		virtual bool compare(Ionflux::GeoUtils::BoxBoundsItem& b0, 
		Ionflux::GeoUtils::BoxBoundsItem& b1);
		
		/** Create comparison function.
		 *
		 * Create a comparison function object.
		 *
		 * \param initReference reference.
		 * \param initInvert Invert order.
		 *
		 * \return New comparison function object.
		 */
		static Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3* create(const 
		Ionflux::GeoUtils::Vector3& initReference, bool initInvert = false);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3& 
		operator=(const Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3& 
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3* copy() 
		const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3* 
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
		static Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get reference.
		 *
		 * \return Current value of reference.
		 */
		virtual Ionflux::GeoUtils::Vector3 getReference() const;
		
		/** Set reference.
		 *
		 * Set new value of reference.
		 *
		 * \param newReference New value of reference.
		 */
		virtual void setReference(const Ionflux::GeoUtils::Vector3& 
		newReference);
};

}

}

/** \file BoxBoundsItemCompareDistanceVec3.hpp
 * \brief Box bounds item comparison function object: Distance to point (header).
 */
#endif
