#ifndef IONFLUX_GEOUTILS_VECTOR3
#define IONFLUX_GEOUTILS_VECTOR3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector3.hpp                     Vector (3 elements) (header).
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
#include "geoutils/Vector2.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Plane3;
class Range;

/// Class information for class Vector3.
class Vector3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Vector3ClassInfo();
		/// Destructor.
		virtual ~Vector3ClassInfo();
};

/** Vector (3 elements).
 * \ingroup geoutils
 *
 * A vector in three-dimensional space.
 */
class Vector3
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Elements.
		double* elements;
		
	public:
		/// Zero vector.
		static const Ionflux::GeoUtils::Vector3 ZERO;
		/// Unit vector (X).
		static const Ionflux::GeoUtils::Vector3 E_X;
		/// Unit vector (Y).
		static const Ionflux::GeoUtils::Vector3 E_Y;
		/// Unit vector (Z).
		static const Ionflux::GeoUtils::Vector3 E_Z;
		/// Sum of unit vectors.
		static const Ionflux::GeoUtils::Vector3 E_SUM;
		/// Class information instance.
		static const Vector3ClassInfo vector3ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Vector3 object.
		 */
		Vector3();
		
		/** Constructor.
		 *
		 * Construct new Vector3 object.
		 *
		 * \param other Other object.
		 */
		Vector3(const Ionflux::GeoUtils::Vector3& other);
		
		/** Constructor.
		 *
		 * Construct new Vector3 object.
		 *
		 * \param initX0 Element (X0).
		 * \param initX1 Element (X1).
		 * \param initX2 Element (X2).
		 */
		Vector3(double initX0, double initX1, double initX2);
		
		/** Constructor.
		 *
		 * Construct new Vector3 object.
		 *
		 * \param initElements Element vector.
		 */
		Vector3(const Ionflux::ObjectBase::DoubleVector& initElements);
		
		/** Constructor.
		 *
		 * Construct new Vector3 object.
		 *
		 * \param initElements Element vector.
		 * \param initZ Z coordinate.
		 */
		Vector3(const Ionflux::GeoUtils::Vector2& initElements, double initZ = 
		1.);
		
		/** Destructor.
		 *
		 * Destruct Vector3 object.
		 */
		virtual ~Vector3();
		
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
		 * \param newX2 Element (x2).
		 */
		virtual void setElements(double newX0, double newX1, double newX2);
		
		/** Set elements.
		 *
		 * Set elements from a 2-element vector. The Z-coordinate will be left
		 * alone.
		 *
		 * \param newElements Element vector.
		 */
		virtual void setElements(const Ionflux::GeoUtils::Vector2& newElements);
		
		/** Set elements.
		 *
		 * Set elements from a 2-element vector. The Z-coordinate will be set 
		 * to the optional second parameter (which defaults to 1).
		 *
		 * \param newElements Element vector.
		 * \param newZ Z coordinate.
		 */
		virtual void setV2(const Ionflux::GeoUtils::Vector2& newElements, double 
		newZ = 1.);
		
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
		virtual bool eq(const Ionflux::GeoUtils::Vector3& other, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Flip vector.
		 *
		 * Create a new vector which is equal to the original vector 
		 * multiplied by -1.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector3 flip() const;
		
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
		virtual Ionflux::GeoUtils::Vector3 normalize() const;
		
		/** Cross product.
		 *
		 * Calculate the cross product of the vector and another vector.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector3 cross(const 
		Ionflux::GeoUtils::Vector3& other) const;
		
		/** Projection.
		 *
		 * Calculate the projection of another vector on the vector.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector3 project(const 
		Ionflux::GeoUtils::Vector3& other) const;
		
		/** Orthogonalize vector.
		 *
		 * Rotate the other vector (v1) within the plane defined by the 
		 * original vector (v0) and v1, so it is orthogonal to v0.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector3 ortho(const 
		Ionflux::GeoUtils::Vector3& other) const;
		
		/** Orthogonalize vector.
		 *
		 * Create a vector that is orthogonal to this one.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector3 ortho() const;
		
		/** Calculate angle.
		 *
		 * Calculate the geometric angle between the two vectors.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual double angle(const Ionflux::GeoUtils::Vector3& other) const;
		
		/** Permute vector.
		 *
		 * Permute the vector using the specified permutation of indices.
		 *
		 * \param px Permutation (x).
		 * \param py Permutation (y).
		 * \param pz Permutation (z).
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector3 permute(int px, int py, int pz) const;
		
		/** Permute vector.
		 *
		 * Permute the vector using the specified permutation of indices.
		 *
		 * \param p Permutation.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector3 permute(const 
		Ionflux::ObjectBase::IntVector& p) const;
		
		/** Element-wise multiplication.
		 *
		 * Multiply the vectors element-wise.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector3 multElements(const 
		Ionflux::GeoUtils::Vector3& other) const;
		
		/** Linear interpolation.
		 *
		 * Interpolate the vectors linearly.
		 *
		 * \param other Vector.
		 * \param t Interpolation parameter.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector3 interpolate(const 
		Ionflux::GeoUtils::Vector3& other, double t) const;
		
		/** Get axis order.
		 *
		 * Get the order of the coordinate axes of the vector. The axis with 
		 * the highest absolute coordinate value will be the first in the 
		 * triple, followed by the other ones in descending order.
		 *
		 * \return Triple containing the axes ordered from longest to shortest.
		 */
		virtual Ionflux::GeoUtils::AxisTriple getAxisOrder() const;
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Vector3& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Vector3& other) const;
		
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
		virtual Ionflux::GeoUtils::Vector3 operator+(const 
		Ionflux::GeoUtils::Vector3& other) const;
		
		/** Subtract vectors.
		 *
		 * Subtract vectors.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector3 operator-(const 
		Ionflux::GeoUtils::Vector3& other) const;
		
		/** Multiply vectors.
		 *
		 * Multiply vectors (dot product).
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual double operator*(const Ionflux::GeoUtils::Vector3& other) const;
		
		/** Multiply vector by scalar.
		 *
		 * Multiply vector by a scalar.
		 *
		 * \param c Scalar factor.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector3 operator*(double c) const;
		
		/** Divide vector by scalar.
		 *
		 * Divide vector by a scalar.
		 *
		 * \param c Scalar factor.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector3 operator/(double c) const;
		
		/** Add vectors.
		 *
		 * Add vectors.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector3& operator+=(const 
		Ionflux::GeoUtils::Vector3& other);
		
		/** Add vectors.
		 *
		 * Add vectors.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector3& operator-=(const 
		Ionflux::GeoUtils::Vector3& other);
		
		/** Find elements.
		 *
		 * Find an element with the specified value in the vector.
		 *
		 * \param v value.
		 * \param t Tolerance.
		 *
		 * \return Index of the matching element, or -1 if no element with the 
		 * specified value was found.
		 */
		virtual int findElement(double v, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
		
		/** Find matching elements.
		 *
		 * Find matching elements in the two vectors. If the optional \c range
		 * parameter is specified, only such elements will be considered that 
		 * are within that range.
		 *
		 * \param other Vector.
		 * \param target Where to store the matching elements.
		 * \param range Range for valid values.
		 * \param t Tolerance.
		 *
		 * \return The number of matching elements..
		 */
		virtual int findMatchingElements(const Ionflux::GeoUtils::Vector3& other,
		Ionflux::ObjectBase::DoubleVector& target, const 
		Ionflux::GeoUtils::Range* range = 0, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Create 2-element vector.
		 *
		 * Create a 2-element vector without the Z coordinate
		 *
		 * \return 2-element vector.
		 */
		virtual Ionflux::GeoUtils::Vector2 getV2() const;
		
		/** Calculate distance to plane.
		 *
		 * Returns the distance of the point with coordinates indicated by the
		 * vector to the specified plane.
		 *
		 * \param plane Plane.
		 *
		 * \return Distance to plane.
		 */
		virtual double distanceToPlane(const Ionflux::GeoUtils::Plane3& plane) 
		const;
		
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
		static Ionflux::GeoUtils::Vector3 axis(Ionflux::GeoUtils::AxisID axisID);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Vector3& operator=(const 
		Ionflux::GeoUtils::Vector3& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Vector3* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Vector3* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Vector3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
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
		
		/** Get element x2.
		 *
		 * \return Current value of element x2.
		 */
		virtual double getX2() const;
		
		/** Set element x2.
		 *
		 * Set new value of element x2.
		 *
		 * \param newX2 New value of element x2.
		 */
		virtual void setX2(double newX2);
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
Ionflux::GeoUtils::Vector3 operator*(double c, const 
Ionflux::GeoUtils::Vector3& v);

}

}

/** \file Vector3.hpp
 * \brief Vector (3 elements) (header).
 */
#endif
