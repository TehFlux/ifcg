#ifndef IONFLUX_GEOUTILS_VECTOR2
#define IONFLUX_GEOUTILS_VECTOR2
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector2.hpp                     Vector (2 elements) (header).
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
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Vector2.
class Vector2ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Vector2ClassInfo();
		/// Destructor.
		virtual ~Vector2ClassInfo();
};

/** Vector (2 elements).
 * \ingroup geoutils
 *
 * A vector in two-dimensional space.
 */
class Vector2
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Elements.
		double* elements;
		
	public:
		/// Zero vector.
		static const Ionflux::GeoUtils::Vector2 ZERO;
		/// Unit vector (X).
		static const Ionflux::GeoUtils::Vector2 E_X;
		/// Unit vector (Y).
		static const Ionflux::GeoUtils::Vector2 E_Y;
		/// Class information instance.
		static const Vector2ClassInfo vector2ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Vector2 object.
		 */
		Vector2();
		
		/** Constructor.
		 *
		 * Construct new Vector2 object.
		 *
		 * \param other Other object.
		 */
		Vector2(const Ionflux::GeoUtils::Vector2& other);
		
		/** Constructor.
		 *
		 * Construct new Vector2 object.
		 *
		 * \param initX0 Element (X0).
		 * \param initX1 Element (X1).
		 */
		Vector2(double initX0, double initX1);
		
		/** Constructor.
		 *
		 * Construct new Vector2 object.
		 *
		 * \param initElements Element vector.
		 */
		Vector2(const Ionflux::ObjectBase::DoubleVector& initElements);
		
		/** Destructor.
		 *
		 * Destruct Vector2 object.
		 */
		virtual ~Vector2();
		
		/** Set elements.
		 *
		 * Set elements from a vector of doubles. If the vector contains fewer
		 * than the required number of elements, the remaining elements will 
		 * be left alone.
		 *
		 * \param newElements Element vector.
		 */
		virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
		newElements);
		
		/** Set elements.
		 *
		 * Set elements of the vector.
		 *
		 * \param newX0 Element (x0).
		 * \param newX1 Element (x1).
		 */
		virtual void setElements(double newX0, double newX1);
		
		/** Get elements.
		 *
		 * Store the elements of the vector in a vector of doubles.
		 *
		 * \param target Target vector.
		 */
		virtual void getElements(Ionflux::ObjectBase::DoubleVector& target) 
		const;
		
		/** Get element.
		 *
		 * Get the element at the specified index.
		 *
		 * \param index Index.
		 *
		 * \return Element at the specified index.
		 */
		virtual double getElement(int index) const;
		
		/** Set element.
		 *
		 * Set the element at the specified index.
		 *
		 * \param index Index.
		 * \param value Value.
		 */
		virtual void setElement(int index, double value);
		
		/** Comparison (with tolerance): equal.
		 *
		 * Compare the vector with another vector using the specified 
		 * tolerance.
		 *
		 * \param other Vector.
		 * \param t Tolerance.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool eq(const Ionflux::GeoUtils::Vector2& other, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Flip vector.
		 *
		 * Create a new vector which is equal to the original vector 
		 * multiplied by -1.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 flip() const;
		
		/** Norm.
		 *
		 * Get the norm (length) of the vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual double norm() const;
		
		/** Normalize vector.
		 *
		 * Create a new vector which is equal to the normalized original 
		 * vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 normalize() const;
		
		/** Projection.
		 *
		 * Calculate the projection of another vector on the vector.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 project(const 
		Ionflux::GeoUtils::Vector2& other) const;
		
		/** Orthogonalize vector.
		 *
		 * Rotate the other vector (v1) within the plane defined by the 
		 * original vector (v0) and v1, so it is orthogonal to v0.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 ortho(const 
		Ionflux::GeoUtils::Vector2& other) const;
		
		/** Swap elements.
		 *
		 * Swap the elements of the vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 swap() const;
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Vector2& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Vector2& other) const;
		
		/** Subscript operator.
		 *
		 * Subscript operator.
		 *
		 * \param index Index.
		 *
		 * \return Element at specified index.
		 */
		virtual double operator[](int index) const;
		
		/** Add vectors.
		 *
		 * Add vectors.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 operator+(const 
		Ionflux::GeoUtils::Vector2& other) const;
		
		/** Subtract vectors.
		 *
		 * Subtract vectors.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 operator-(const 
		Ionflux::GeoUtils::Vector2& other) const;
		
		/** Multiply vectors.
		 *
		 * Multiply vectors (dot product).
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual double operator*(const Ionflux::GeoUtils::Vector2& other) const;
		
		/** Multiply vector by scalar.
		 *
		 * Multiply vector by a scalar.
		 *
		 * \param c Scalar factor.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 operator*(double c) const;
		
		/** Divide vector by scalar.
		 *
		 * Divide vector by a scalar.
		 *
		 * \param c Scalar factor.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 operator/(double c) const;
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Get axis direction vector.
		 *
		 * Get the direction vector for the specified axis.
		 *
		 * \param axisID Axis.
		 *
		 * \return Axis direction vector.
		 */
		static Ionflux::GeoUtils::Vector2 axis(Ionflux::GeoUtils::AxisID axisID);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Vector2& operator=(const 
		Ionflux::GeoUtils::Vector2& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Vector2* copy() const;
		
		/** Get element x0.
		 *
		 * \return Current value of element x0.
		 */
		virtual double getX0() const;
		
		/** Set element x0.
		 *
		 * Set new value of element x0.
		 *
		 * \param newX0 New value of element x0.
		 */
		virtual void setX0(double newX0);
		
		/** Get element x1.
		 *
		 * \return Current value of element x1.
		 */
		virtual double getX1() const;
		
		/** Set element x1.
		 *
		 * Set new value of element x1.
		 *
		 * \param newX1 New value of element x1.
		 */
		virtual void setX1(double newX1);
};

/** Multiply vector by scalar.
 *
 * Multiply vector by a scalar.
 *
 * \param c Scalar factor.
 * \param v Vector.
 *
 * \return Result of the calculation.
 */
Ionflux::GeoUtils::Vector2 operator*(double c, const 
Ionflux::GeoUtils::Vector2& v);

}

}

/** \file Vector2.hpp
 * \brief Vector (2 elements) (header).
 */
#endif
