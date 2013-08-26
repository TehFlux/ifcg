#ifndef IONFLUX_GEOUTILS_INTERPOLATOR
#define IONFLUX_GEOUTILS_INTERPOLATOR
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Interpolator.hpp                Interpolator (header).
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

#include "ifobject/types.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Interpolator.
class InterpolatorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		InterpolatorClassInfo();
		/// Destructor.
		virtual ~InterpolatorClassInfo();
};

/** Interpolator.
 * \ingroup geoutils
 *
 * An object that does interpolation between two scalar values.
 */
class Interpolator
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// First value.
		double v0;
		/// Second value.
		double v1;
		
	public:
		/// Class information instance.
		static const InterpolatorClassInfo interpolatorClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Interpolator object.
		 */
		Interpolator();
		
		/** Constructor.
		 *
		 * Construct new Interpolator object.
		 *
		 * \param other Other object.
		 */
		Interpolator(const Ionflux::GeoUtils::Interpolator& other);
		
		/** Constructor.
		 *
		 * Construct new Interpolator object.
		 *
		 * \param initV0 First value.
		 * \param initV1 Second value.
		 */
		Interpolator(double initV0, double initV1);
		
		/** Constructor.
		 *
		 * Construct new Interpolator object.
		 *
		 * \param initValues Value vector.
		 */
		Interpolator(const Ionflux::ObjectBase::DoubleVector& initValues);
		
		/** Destructor.
		 *
		 * Destruct Interpolator object.
		 */
		virtual ~Interpolator();
		
		/** Set values.
		 *
		 * Set values.
		 *
		 * \param newV0 First value.
		 * \param newV1 Second value.
		 */
		virtual void setValues(double newV0, double newV1);
		
		/** Set values.
		 *
		 * Set values from a vector of doubles. If the vector contains fewer 
		 * than the required number of vertex indices, the remaining values 
		 * will be left alone.
		 *
		 * \param newValues Value vector.
		 */
		virtual void setValues(const Ionflux::ObjectBase::DoubleVector& 
		newValues);
		
		/** Get values.
		 *
		 * Store the values in a vector of doubles.
		 *
		 * \param target Target vector.
		 */
		virtual void getValues(Ionflux::ObjectBase::DoubleVector& target) const;
		
		/** Get value.
		 *
		 * Get the value with the specified index.
		 *
		 * \param index Index.
		 *
		 * \return Element at the specified index.
		 */
		virtual double getValue(int index) const;
		
		/** Get values as vector.
		 *
		 * Get the values as a vector.
		 *
		 * \return Vector.
		 */
		virtual Ionflux::ObjectBase::DoubleVector getVector() const;
		
		/** Set value.
		 *
		 * Set the value index with the specified index.
		 *
		 * \param index Index.
		 * \param value Value.
		 */
		virtual void setValue(int index, int value);
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Interpolator.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Interpolator& other) 
		const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Interpolator.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Interpolator& other) 
		const;
		
		/** Subscript operator.
		 *
		 * Subscript operator.
		 *
		 * \param index Index.
		 *
		 * \return Element at specified index.
		 */
		virtual double operator[](int index) const;
		
		/** Interpolate.
		 *
		 * Interpolate the current values using the specified parameter.
		 *
		 * \param t Interpolation parameter.
		 */
		virtual double interpolate(double t = 0.5) const = 0;
		
		/** Interpolate.
		 *
		 * Interpolate the current values using the specified parameter.
		 *
		 * \param t Interpolation parameter.
		 *
		 * \return Interpolated value.
		 */
		virtual double operator()(double t = 0.5) const;
		
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
		virtual Ionflux::GeoUtils::Interpolator& operator=(const 
		Ionflux::GeoUtils::Interpolator& other);
		
		/** Get first value.
		 *
		 * \return Current value of first value.
		 */
		virtual double getV0() const;
		
		/** Set first value.
		 *
		 * Set new value of first value.
		 *
		 * \param newV0 New value of first value.
		 */
		virtual void setV0(double newV0);
		
		/** Get second value.
		 *
		 * \return Current value of second value.
		 */
		virtual double getV1() const;
		
		/** Set second value.
		 *
		 * Set new value of second value.
		 *
		 * \param newV1 New value of second value.
		 */
		virtual void setV1(double newV1);
};

}

}

/** \file Interpolator.hpp
 * \brief Interpolator (header).
 */
#endif
