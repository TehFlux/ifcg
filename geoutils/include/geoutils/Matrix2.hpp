#ifndef IONFLUX_GEOUTILS_MATRIX2
#define IONFLUX_GEOUTILS_MATRIX2
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix2.hpp                     Matrix (2x2) (header).
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
#include "geoutils/Vector2.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Matrix2.
class Matrix2ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Matrix2ClassInfo();
		/// Destructor.
		virtual ~Matrix2ClassInfo();
};

/** Matrix (2x2).
 * \ingroup geoutils
 *
 * A 2x2 matrix.
 */
class Matrix2
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Elements.
		double* elements;
		
	public:
		/// Zero matrix.
		static const Ionflux::GeoUtils::Matrix2 ZERO;
		/// Unit matrix.
		static const Ionflux::GeoUtils::Matrix2 UNIT;
		/// Class information instance.
		static const Matrix2ClassInfo matrix2ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Matrix2 object.
		 */
		Matrix2();
		
		/** Constructor.
		 *
		 * Construct new Matrix2 object.
		 *
		 * \param other Other object.
		 */
		Matrix2(const Ionflux::GeoUtils::Matrix2& other);
		
		/** Constructor.
		 *
		 * Construct new Matrix2 object.
		 *
		 * \param initX00 Element x00.
		 * \param initX01 Element x01.
		 * \param initX10 Element x10.
		 * \param initX11 Element x11.
		 */
		Matrix2(double initX00, double initX01, double initX10, double initX11);
		
		/** Constructor.
		 *
		 * Construct new Matrix2 object.
		 *
		 * \param initElements Element vector.
		 */
		Matrix2(const Ionflux::ObjectBase::DoubleVector& initElements);
		
		/** Destructor.
		 *
		 * Destruct Matrix2 object.
		 */
		virtual ~Matrix2();
		
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
		
		/** Get elements.
		 *
		 * Store the elements of the matrix in a vector of doubles.
		 *
		 * \param target Target vector.
		 */
		virtual void getElements(Ionflux::ObjectBase::DoubleVector& target) 
		const;
		
		/** Get element.
		 *
		 * Get the element at the specified position.
		 *
		 * \param row Row index.
		 * \param column Column index.
		 *
		 * \return Element at the specified index.
		 */
		virtual double getElement(int row, int column) const;
		
		/** Set element.
		 *
		 * Set the element at the specified index.
		 *
		 * \param row Row index.
		 * \param column Column index.
		 * \param value Value.
		 */
		virtual void setElement(int row, int column, double value);
		
		/** Comparison (with tolerance): equal.
		 *
		 * Compare the matrix with another matrix using the specified 
		 * tolerance.
		 *
		 * \param other Matrix.
		 * \param t Tolerance.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool eq(const Ionflux::GeoUtils::Matrix2& other, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Transpose.
		 *
		 * Transpose the matrix.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix2 transpose() const;
		
		/** Swap columns.
		 *
		 * Swap the columns.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix2 swapColumns() const;
		
		/** Solve matrix equation.
		 *
		 * Solve the matrix equation Mx = v.
		 *
		 * \param v Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 solve(const 
		Ionflux::GeoUtils::Vector2& v) const;
		
		/** Invert matrix.
		 *
		 * Invert the matrix.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix2 invert() const;
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Matrix.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Matrix2& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Matrix.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Matrix2& other) const;
		
		/** Subscript operator.
		 *
		 * Subscript operator.
		 *
		 * \param index Index.
		 *
		 * \return Row vector with specified index.
		 */
		virtual Ionflux::GeoUtils::Vector2 operator[](int index) const;
		
		/** Multiply matrices.
		 *
		 * Multiply matrices.
		 *
		 * \param other Matrix.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix2 operator*(const 
		Ionflux::GeoUtils::Matrix2& other) const;
		
		/** Transform vector.
		 *
		 * Transform a vector.
		 *
		 * \param v Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 operator*(const 
		Ionflux::GeoUtils::Vector2& v) const;
		
		/** Multiply matrix by scalar.
		 *
		 * Multiply matrix by a scalar.
		 *
		 * \param c Scalar factor.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix2 operator*(double c) const;
		
		/** Divide matrix by scalar.
		 *
		 * Divide matrix by a scalar.
		 *
		 * \param c Scalar factor.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix2 operator/(double c) const;
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Create scale matrix.
		 *
		 * Create a scale matrix.
		 *
		 * \param sx Scale factor (x).
		 * \param sy Scale factor (y).
		 *
		 * \return Scale matrix.
		 */
		static Ionflux::GeoUtils::Matrix2 scale(double sx = 1., double sy = 1.);
		
		/** Create rotation matrix.
		 *
		 * Create a rotation matrix.
		 *
		 * \param phi Angle.
		 *
		 * \return Rotation matrix.
		 */
		static Ionflux::GeoUtils::Matrix2 rotate(double phi = 0.);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Matrix2& operator=(const 
		Ionflux::GeoUtils::Matrix2& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Matrix2* copy() const;
		
		/** Get row vector (0).
		 *
		 * \return Current value of row vector (0).
		 */
		virtual Ionflux::GeoUtils::Vector2 getR0() const;
		
		/** Set row vector (0).
		 *
		 * Set new value of row vector (0).
		 *
		 * \param newR0 New value of row vector (0).
		 */
		virtual void setR0(const Ionflux::GeoUtils::Vector2& newR0);
		
		/** Get row vector (1).
		 *
		 * \return Current value of row vector (1).
		 */
		virtual Ionflux::GeoUtils::Vector2 getR1() const;
		
		/** Set row vector (1).
		 *
		 * Set new value of row vector (1).
		 *
		 * \param newR1 New value of row vector (1).
		 */
		virtual void setR1(const Ionflux::GeoUtils::Vector2& newR1);
		
		/** Get column vector (0).
		 *
		 * \return Current value of column vector (0).
		 */
		virtual Ionflux::GeoUtils::Vector2 getC0() const;
		
		/** Set column vector (0).
		 *
		 * Set new value of column vector (0).
		 *
		 * \param newC0 New value of column vector (0).
		 */
		virtual void setC0(const Ionflux::GeoUtils::Vector2& newC0);
		
		/** Get column vector (1).
		 *
		 * \return Current value of column vector (1).
		 */
		virtual Ionflux::GeoUtils::Vector2 getC1() const;
		
		/** Set column vector (1).
		 *
		 * Set new value of column vector (1).
		 *
		 * \param newC1 New value of column vector (1).
		 */
		virtual void setC1(const Ionflux::GeoUtils::Vector2& newC1);
};

/** Multiply matrix by scalar.
 *
 * Multiply matrix by a scalar.
 *
 * \param c Scalar factor.
 * \param m Matrix.
 *
 * \return Result of the calculation.
 */
Ionflux::GeoUtils::Matrix2 operator*(double c, const 
Ionflux::GeoUtils::Matrix2& m);

}

}

/** \file Matrix2.hpp
 * \brief Matrix (2x2) (header).
 */
#endif
