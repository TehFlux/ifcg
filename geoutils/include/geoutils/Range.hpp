#ifndef IONFLUX_GEOUTILS_RANGE
#define IONFLUX_GEOUTILS_RANGE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Range.hpp                       Range of values (header).
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

#include "ifobject/types.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Range.
class RangeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		RangeClassInfo();
		/// Destructor.
		virtual ~RangeClassInfo();
};

/** Range of values.
 * \ingroup geoutils
 *
 * A range of values.
 */
class Range
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Minimum value.
		double rMin;
		/// Maximum value.
		double rMax;
		
	public:
		/// Class information instance.
		static const RangeClassInfo rangeClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Range object.
		 */
		Range();
		
		/** Constructor.
		 *
		 * Construct new Range object.
		 *
		 * \param other Other object.
		 */
		Range(const Ionflux::GeoUtils::Range& other);
		
		/** Constructor.
		 *
		 * Construct new Range object.
		 *
		 * \param initRMin Range minimum.
		 * \param initRMax Range maximum.
		 */
		Range(double initRMin, double initRMax);
		
		/** Destructor.
		 *
		 * Destruct Range object.
		 */
		virtual ~Range();
		
		/** Extend range.
		 *
		 * Extend the range to contain the specified value.
		 *
		 * \param value Value.
		 */
		virtual void extend(double value);
		
		/** Get center.
		 *
		 * Get the center of the range.
		 *
		 * \return Center of the range.
		 */
		virtual double getCenter() const;
		
		/** Get radius.
		 *
		 * Get the radius of the range.
		 *
		 * \return Radius of the range.
		 */
		virtual double getRadius() const;
		
		/** Get extent.
		 *
		 * Get the extent of the range.
		 *
		 * \return Extent of the range.
		 */
		virtual double getExtent() const;
		
		/** Get value.
		 *
		 * Get the value inside the range corresponding to the parameter s, 
		 * where s = 0 returns the minimum value and s = 1 returns the maximum
		 * value.
		 *
		 * \param s Parameter.
		 *
		 * \return Value from the range.
		 */
		virtual double getValue(double s) const;
		
		/** Get parameter.
		 *
		 * Get the range parameter corresponding to the value v.
		 *
		 * \param v Value.
		 *
		 * \return Parameter.
		 */
		virtual double getParam(double v) const;
		
		/** Clamp value.
		 *
		 * Clamp the value to the range.
		 *
		 * \param value Value.
		 *
		 * \return Clamped value.
		 */
		virtual double clamp(double value) const;
		
		/** Get value.
		 *
		 * Get the value inside the range corresponding to the parameter s, 
		 * where s = 0 returns the minimum value and s = 1 returns the maximum
		 * value. The result is clamped to the range.
		 *
		 * \param s Parameter.
		 *
		 * \return Clamped value from the range.
		 */
		virtual double getClampedValue(double s) const;
		
		/** Compare ranges.
		 *
		 * Returns RANGE_EQUAL if the ranges are equal within the tolerance, 
		 * i.e. they have the same rMin and rMax values. Returns 
		 * RANGE_OTHER_CONTAINS  if the range on which the method is called is
		 * contained within the other range, and RANGE_FIRST_CONTAINS if the 
		 * other range is contained within the range on which the method is 
		 * called. Returns RANGE_OVERLAP if the ranges overlap. Returns 
		 * RANGE_DISJOINT if the ranges are disjoint.
		 *
		 * \param other Range.
		 * \param t Tolerance.
		 *
		 * \return Result of the comparison.
		 */
		virtual Ionflux::GeoUtils::RangeCompResult compare(const 
		Ionflux::GeoUtils::Range& other, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
		
		/** Range check.
		 *
		 * Check whether the value is contained in the range.
		 *
		 * \param v Value.
		 * \param t Tolerance.
		 *
		 * \return \c true if the value is within the range, \c false otherwise.
		 */
		virtual bool isInRange(double v, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
		
		/** Set bounds.
		 *
		 * Set the bounds of the range.
		 *
		 * \param rMinNew Range minimum.
		 * \param rMaxNew Range maximum.
		 */
		virtual void setBounds(double rMinNew, double rMaxNew);
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Range.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Range& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Range.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Range& other) const;
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Range& operator=(const 
		Ionflux::GeoUtils::Range& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Range* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Range* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Range* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get minimum value.
		 *
		 * \return Current value of minimum value.
		 */
		virtual double getRMin() const;
		
		/** Set minimum value.
		 *
		 * Set new value of minimum value.
		 *
		 * \param newRMin New value of minimum value.
		 */
		virtual void setRMin(double newRMin);
		
		/** Get maximum value.
		 *
		 * \return Current value of maximum value.
		 */
		virtual double getRMax() const;
		
		/** Set maximum value.
		 *
		 * Set new value of maximum value.
		 *
		 * \param newRMax New value of maximum value.
		 */
		virtual void setRMax(double newRMax);
		
		/** Get bounds.
		 *
		 * \return Current value of bounds.
		 */
		virtual Ionflux::ObjectBase::DoubleVector getBounds() const;
		
		/** Set bounds.
		 *
		 * Set new value of bounds.
		 *
		 * \param newBounds New value of bounds.
		 */
		virtual void setBounds(const Ionflux::ObjectBase::DoubleVector& 
		newBounds);
};

}

}

/** \file Range.hpp
 * \brief Range of values (header).
 */
#endif
