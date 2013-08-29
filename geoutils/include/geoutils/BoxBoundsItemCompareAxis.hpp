#ifndef IONFLUX_GEOUTILS_BOXBOUNDSITEMCOMPAREAXIS
#define IONFLUX_GEOUTILS_BOXBOUNDSITEMCOMPAREAXIS
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BoxBoundsItemCompareAxis.hpp    Box bounds item comparison function 
 * object: Axis coordinate (header).
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

/** Box bounds item comparison function object: Axis coordinate.
 * \ingroup geoutils
 *
 * A function object that compares box bounds items based on a coordinate 
 * of their center vector.
 */
class BoxBoundsItemCompareAxis
: public Ionflux::GeoUtils::BoxBoundsItemCompare
{
	private:
		
	protected:
		/// Axis.
		Ionflux::GeoUtils::AxisID axis;
		
	public:
		
		/** Constructor.
		 *
		 * Construct new BoxBoundsItemCompareAxis object.
		 */
		BoxBoundsItemCompareAxis();
		
		/** Constructor.
		 *
		 * Construct new BoxBoundsItemCompareAxis object.
		 *
		 * \param other Other object.
		 */
		BoxBoundsItemCompareAxis(const Ionflux::GeoUtils::BoxBoundsItemCompareAxis& other);
		
		/** Constructor.
		 *
		 * Construct new BoxBoundsItemCompareAxis object.
		 *
		 * \param initAxis Axis.
		 * \param initInvert Invert order.
		 */
		BoxBoundsItemCompareAxis(Ionflux::GeoUtils::AxisID initAxis, bool 
		initInvert = true);
		
		/** Destructor.
		 *
		 * Destruct BoxBoundsItemCompareAxis object.
		 */
		virtual ~BoxBoundsItemCompareAxis();
		
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
		 * \param initAxis Axis.
		 * \param initInvert Invert order.
		 *
		 * \return New comparison function object.
		 */
		static Ionflux::GeoUtils::BoxBoundsItemCompareAxis* 
		create(Ionflux::GeoUtils::AxisID initAxis, bool initInvert = true);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::BoxBoundsItemCompareAxis& operator=(const 
		Ionflux::GeoUtils::BoxBoundsItemCompareAxis& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::BoxBoundsItemCompareAxis* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::BoxBoundsItemCompareAxis* 
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
		static Ionflux::GeoUtils::BoxBoundsItemCompareAxis* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get axis.
		 *
		 * \return Current value of axis.
		 */
		virtual Ionflux::GeoUtils::AxisID getAxis() const;
		
		/** Set axis.
		 *
		 * Set new value of axis.
		 *
		 * \param newAxis New value of axis.
		 */
		virtual void setAxis(Ionflux::GeoUtils::AxisID newAxis);
};

}

}

/** \file BoxBoundsItemCompareAxis.hpp
 * \brief Box bounds item comparison function object: Axis coordinate (header).
 */
#endif
