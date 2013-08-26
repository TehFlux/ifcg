#ifndef IONFLUX_GEOUTILS_RANGE3
#define IONFLUX_GEOUTILS_RANGE3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Range3.hpp                      Range of values (3D) (header).
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
#include "geoutils/Range.hpp"
#include "geoutils/Vector2.hpp"
#include "geoutils/Vector3.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Range3.
class Range3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Range3ClassInfo();
		/// Destructor.
		virtual ~Range3ClassInfo();
};

/** Range of values (3D).
 * \ingroup geoutils
 *
 * A range of values in three-dimensional space.
 */
class Range3
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Range (x).
		Ionflux::GeoUtils::Range x;
		/// Range (y).
		Ionflux::GeoUtils::Range y;
		/// Range (z).
		Ionflux::GeoUtils::Range z;
		
	public:
		/// Class information instance.
		static const Range3ClassInfo range3ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Range3 object.
		 */
		Range3();
		
		/** Constructor.
		 *
		 * Construct new Range3 object.
		 *
		 * \param other Other object.
		 */
		Range3(const Ionflux::GeoUtils::Range3& other);
		
		/** Constructor.
		 *
		 * Construct new Range3 object.
		 *
		 * \param initCenter Center vector.
		 * \param initRadius Radius vector.
		 */
		Range3(const Ionflux::GeoUtils::Vector3& initCenter, const 
		Ionflux::GeoUtils::Vector3* initRadius = 0);
		
		/** Constructor.
		 *
		 * Construct new Range3 object.
		 *
		 * \param initX Range (x).
		 * \param initY Range (y).
		 * \param initZ Range (z).
		 */
		Range3(const Ionflux::GeoUtils::Range& initX, const 
		Ionflux::GeoUtils::Range& initY, const Ionflux::GeoUtils::Range& initZ);
		
		/** Constructor.
		 *
		 * Construct new Range3 object.
		 *
		 * \param rx Range (x).
		 * \param ry Range (y).
		 * \param rz Range (z).
		 */
		Range3(const Ionflux::GeoUtils::Vector2& rx, const 
		Ionflux::GeoUtils::Vector2& ry, const Ionflux::GeoUtils::Vector2& rz);
		
		/** Constructor.
		 *
		 * Construct new Range3 object.
		 *
		 * \param xMin Minimum value (X).
		 * \param xMax Maximum value (X).
		 * \param yMin Minimum value (Y).
		 * \param yMax Maximum value (Y).
		 * \param zMin Minimum value (Z).
		 * \param zMax Maximum value (Z).
		 */
		Range3(double xMin, double xMax, double yMin, double yMax, double zMin, 
		double zMax);
		
		/** Destructor.
		 *
		 * Destruct Range3 object.
		 */
		virtual ~Range3();
		
		/** Extend range.
		 *
		 * Extend the range to contain the values from the specified range.
		 *
		 * \param other Range.
		 */
		virtual void extend(const Ionflux::GeoUtils::Range3& other);
		
		/** Extend range.
		 *
		 * Extend the range to contain the values from the specified vector.
		 *
		 * \param v Vector.
		 */
		virtual void extend(const Ionflux::GeoUtils::Vector3& v);
		
		/** Get center.
		 *
		 * Get the center vector of the range.
		 *
		 * \return Center of the range.
		 */
		virtual Ionflux::GeoUtils::Vector3 getCenter() const;
		
		/** Get radius vector.
		 *
		 * Get the radius vector of the range.
		 *
		 * \return Radius vector of the range.
		 */
		virtual Ionflux::GeoUtils::Vector3 getRadius() const;
		
		/** Get extent.
		 *
		 * Get the extent of the range.
		 *
		 * \return Extent of the range.
		 */
		virtual Ionflux::GeoUtils::Vector3 getExtent() const;
		
		/** Get extent.
		 *
		 * Get the extent of the range on the specified axis.
		 *
		 * \param axis Axis.
		 *
		 * \return Extent of the range.
		 */
		virtual double getExtent(Ionflux::GeoUtils::AxisID axis) const;
		
		/** Get value.
		 *
		 * Get the vector inside the range corresponding to the parameter 
		 * vector. For each dimension, s = 0 returns the minimum value and s =
		 * 1 returns the maximum value for that dimension.
		 *
		 * \param v Parameter vector.
		 *
		 * \return Value from the range.
		 */
		virtual Ionflux::GeoUtils::Vector3 getValue(const 
		Ionflux::GeoUtils::Vector3 v) const;
		
		/** Clamp vector.
		 *
		 * Clamp the vector to the range.
		 *
		 * \param v Vector.
		 *
		 * \return Clamped vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 clamp(const Ionflux::GeoUtils::Vector3
		v) const;
		
		/** Get value.
		 *
		 * Get the vector inside the range corresponding to the parameter 
		 * vector. For each dimension, s = 0 returns the minimum value and s =
		 * 1 returns the maximum value for that dimension. The result is 
		 * clamped to the range.
		 *
		 * \param v Vector.
		 *
		 * \return Clamped value from the range.
		 */
		virtual Ionflux::GeoUtils::Vector3 getClampedValue(const 
		Ionflux::GeoUtils::Vector3 v) const;
		
		/** Get range for specified axis.
		 *
		 * Get the range for the specified axis.
		 *
		 * \param axis Axis.
		 *
		 * \return Range.
		 */
		virtual Ionflux::GeoUtils::Range getAxisRange(Ionflux::GeoUtils::AxisID 
		axis) const;
		
		/** Set bounds.
		 *
		 * Set bounds of the range to a single point, as specified by the 
		 * vector.
		 *
		 * \param v Vector.
		 */
		virtual void setBounds(const Ionflux::GeoUtils::Vector3& v);
		
		/** Set bounds.
		 *
		 * Set bounds of the range to the bounds of another range.
		 *
		 * \param other Range.
		 */
		virtual void setBounds(const Ionflux::GeoUtils::Range3& other);
		
		/** Compare ranges (per axis).
		 *
		 * Compares the ranges on each axis separately. See Range3::compare() 
		 * for details on the return values.
		 *
		 * \param other Range.
		 * \param t Tolerance.
		 *
		 * \return Result of the comparison.
		 */
		virtual Ionflux::GeoUtils::RangeCompResult3 compare3(const 
		Ionflux::GeoUtils::Range3& other, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
		
		/** Compare ranges.
		 *
		 * Returns RANGE_EQUAL if the ranges are equal within the tolerance, 
		 * i.e. they have the same rMin and rMax values in each dimension. 
		 * Returns RANGE_OTHER_CONTAINS if the range on which the method is 
		 * called is contained within the other range, and 
		 * RANGE_FIRST_CONTAINS if the other range is contained within the 
		 * range on which the method is called. Returns RANGE_OVERLAP if the 
		 * ranges overlap in some dimension. Returns RANGE_DISJOINT if the 
		 * ranges are disjoint.
		 *
		 * \param other Range.
		 * \param t Tolerance.
		 *
		 * \return Result of the comparison.
		 */
		virtual Ionflux::GeoUtils::RangeCompResult compare(const 
		Ionflux::GeoUtils::Range3& other, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
		
		/** Range check.
		 *
		 * Check whether the vector is contained in the range.
		 *
		 * \param v Vector.
		 * \param t Tolerance.
		 *
		 * \return \c true if the value is within the range, \c false otherwise.
		 */
		virtual bool isInRange(const Ionflux::GeoUtils::Vector3& v, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
		
		/** Get axis order.
		 *
		 * Get the order of the axes of the range. The longest axis will be 
		 * the first in the triple,
		 *
		 * \return Triple containing the axes ordered from longest to shortest.
		 */
		virtual Ionflux::GeoUtils::AxisTriple getAxisOrder() const;
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Range.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Range3& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Range.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Range3& other) const;
		
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
		virtual Ionflux::GeoUtils::Range3& operator=(const 
		Ionflux::GeoUtils::Range3& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Range3* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Range3* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Range3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get range (x).
		 *
		 * \return Current value of range (x).
		 */
		virtual Ionflux::GeoUtils::Range getX() const;
		
		/** Set range (x).
		 *
		 * Set new value of range (x).
		 *
		 * \param newX New value of range (x).
		 */
		virtual void setX(const Ionflux::GeoUtils::Range& newX);
		
		/** Get range (y).
		 *
		 * \return Current value of range (y).
		 */
		virtual Ionflux::GeoUtils::Range getY() const;
		
		/** Set range (y).
		 *
		 * Set new value of range (y).
		 *
		 * \param newY New value of range (y).
		 */
		virtual void setY(const Ionflux::GeoUtils::Range& newY);
		
		/** Get range (z).
		 *
		 * \return Current value of range (z).
		 */
		virtual Ionflux::GeoUtils::Range getZ() const;
		
		/** Set range (z).
		 *
		 * Set new value of range (z).
		 *
		 * \param newZ New value of range (z).
		 */
		virtual void setZ(const Ionflux::GeoUtils::Range& newZ);
};

}

}

/** \file Range3.hpp
 * \brief Range of values (3D) (header).
 */
#endif
