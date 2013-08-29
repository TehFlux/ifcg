#ifndef IONFLUX_GEOUTILS_POLYGON3COMPAREAXIS
#define IONFLUX_GEOUTILS_POLYGON3COMPAREAXIS
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polygon3CompareAxis.hpp         Polygon comparison function object: Axis
 * coordinate (header).
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
#include "geoutils/Polygon3.hpp"
#include "geoutils/Polygon3Compare.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Polygon3CompareAxis.
class Polygon3CompareAxisClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Polygon3CompareAxisClassInfo();
		/// Destructor.
		virtual ~Polygon3CompareAxisClassInfo();
};

/** Polygon comparison function object: Axis coordinate.
 * \ingroup geoutils
 *
 * A function object that compares polygons based on a coordinate of their 
 * barycenter.
 */
class Polygon3CompareAxis
: public Ionflux::GeoUtils::Polygon3Compare
{
	private:
		
	protected:
		/// Axis.
		Ionflux::GeoUtils::AxisID axis;
		
	public:
		/// Class information instance.
		static const Polygon3CompareAxisClassInfo polygon3CompareAxisClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Polygon3CompareAxis object.
		 */
		Polygon3CompareAxis();
		
		/** Constructor.
		 *
		 * Construct new Polygon3CompareAxis object.
		 *
		 * \param other Other object.
		 */
		Polygon3CompareAxis(const Ionflux::GeoUtils::Polygon3CompareAxis& other);
		
		/** Constructor.
		 *
		 * Construct new Polygon3CompareAxis object.
		 *
		 * \param initAxis Axis.
		 * \param initInvert Invert order.
		 */
		Polygon3CompareAxis(Ionflux::GeoUtils::AxisID initAxis, bool initInvert =
		true);
		
		/** Destructor.
		 *
		 * Destruct Polygon3CompareAxis object.
		 */
		virtual ~Polygon3CompareAxis();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Compare polygons.
		 *
		 * Compare two polygons.
		 *
		 * \param p0 Polygon (0).
		 * \param p1 Polygon (1).
		 *
		 * \return \c true if the polygon p0 goes before the polygon p1, \c false
		 * otherwise.
		 */
		virtual bool compare(Ionflux::GeoUtils::Polygon3& p0, 
		Ionflux::GeoUtils::Polygon3& p1);
		
		/** Create comparison function.
		 *
		 * Create a comparison function object.
		 *
		 * \param initAxis Axis.
		 * \param initInvert Invert order.
		 *
		 * \return New comparison function object.
		 */
		static Ionflux::GeoUtils::Polygon3CompareAxis* 
		create(Ionflux::GeoUtils::AxisID initAxis, bool initInvert = true);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Polygon3CompareAxis& operator=(const 
		Ionflux::GeoUtils::Polygon3CompareAxis& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Polygon3CompareAxis* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Polygon3CompareAxis* 
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
		static Ionflux::GeoUtils::Polygon3CompareAxis* 
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

/** \file Polygon3CompareAxis.hpp
 * \brief Polygon comparison function object: Axis coordinate (header).
 */
#endif
