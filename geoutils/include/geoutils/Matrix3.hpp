#ifndef IONFLUX_GEOUTILS_MATRIX3
#define IONFLUX_GEOUTILS_MATRIX3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix3.hpp                     Matrix (3x3) (header).
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
#include "geoutils/Matrix2.hpp"
#include "geoutils/Vector3.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Matrix3.
class Matrix3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Matrix3ClassInfo();
		/// Destructor.
		virtual ~Matrix3ClassInfo();
};

/** Matrix (3x3).
 * \ingroup geoutils
 *
 * A 3x3 matrix.
 */
class Matrix3
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Elements.
		double* elements;
		
	public:
		/// Zero matrix.
		static const Ionflux::GeoUtils::Matrix3 ZERO;
		/// Unit matrix.
		static const Ionflux::GeoUtils::Matrix3 UNIT;
		/// Class information instance.
		static const Matrix3ClassInfo matrix3ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Matrix3 object.
		 */
		Matrix3();
		
		/** Constructor.
		 *
		 * Construct new Matrix3 object.
		 *
		 * \param other Other object.
		 */
		Matrix3(const Ionflux::GeoUtils::Matrix3& other);
		
		/** Constructor.
		 *
		 * Construct new Matrix3 object.
		 *
		 * \param initX00 Element x00.
		 * \param initX01 Element x01.
		 * \param initX02 Element x02.
		 * \param initX10 Element x10.
		 * \param initX11 Element x11.
		 * \param initX12 Element x12.
		 * \param initX20 Element x20.
		 * \param initX21 Element x21.
		 * \param initX22 Element x22.
		 */
		Matrix3(double initX00, double initX01, double initX02, double initX10, 
		double initX11, double initX12, double initX20, double initX21, double 
		initX22);
		
		/** Constructor.
		 *
		 * Construct new Matrix3 object.
		 *
		 * \param initElements Element vector.
		 */
		Matrix3(const Ionflux::ObjectBase::DoubleVector& initElements);
		
		/** Destructor.
		 *
		 * Destruct Matrix3 object.
		 */
		virtual ~Matrix3();
		
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
		virtual bool eq(const Ionflux::GeoUtils::Matrix3& other, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Transpose.
		 *
		 * Transpose the matrix.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix3 transpose() const;
		
		/** Permute columns.
		 *
		 * Permute the columns using the specified permutation of indices.
		 *
		 * \param px Permutation (x).
		 * \param py Permutation (y).
		 * \param pz Permutation (z).
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix3 permuteColumns(int px, int py, int pz)
		const;
		
		/** Permute columns.
		 *
		 * Permute the columns using the specified permutation of indices.
		 *
		 * \param p Permutation.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix3 permuteColumns(const 
		Ionflux::ObjectBase::IntVector& p) const;
		
		/** Solve matrix equation.
		 *
		 * Solve the matrix equation Mx = v.
		 *
		 * \param v Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector3 solve(const 
		Ionflux::GeoUtils::Vector3& v) const;
		
		/** Invert matrix.
		 *
		 * Invert the matrix.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix3 invert() const;
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Matrix.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Matrix3& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Matrix.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Matrix3& other) const;
		
		/** Subscript operator.
		 *
		 * Subscript operator.
		 *
		 * \param index Index.
		 *
		 * \return Row vector with specified index.
		 */
		virtual Ionflux::GeoUtils::Vector3 operator[](int index) const;
		
		/** Multiply matrices.
		 *
		 * Multiply matrices.
		 *
		 * \param other Matrix.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix3 operator*(const 
		Ionflux::GeoUtils::Matrix3& other) const;
		
		/** Transform vector.
		 *
		 * Transform a vector.
		 *
		 * \param v Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector3 operator*(const 
		Ionflux::GeoUtils::Vector3& v) const;
		
		/** Multiply matrix by scalar.
		 *
		 * Multiply matrix by a scalar.
		 *
		 * \param c Scalar factor.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix3 operator*(double c) const;
		
		/** Divide matrix by scalar.
		 *
		 * Divide matrix by a scalar.
		 *
		 * \param c Scalar factor.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix3 operator/(double c) const;
		
		/** Calculate singular value decomposition.
		 *
		 * Calculate the singular value decomposition M = U S V^T of the 
		 * matrix.
		 *
		 * \param u U.
		 * \param s singular values.
		 * \param v V.
		 */
		virtual void svd(Ionflux::GeoUtils::Matrix3& u, 
		Ionflux::GeoUtils::Vector3& s, Ionflux::GeoUtils::Matrix3& v) const;
		
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
		 * \param sz Scale factor (z).
		 *
		 * \return Scale matrix.
		 */
		static Ionflux::GeoUtils::Matrix3 scale(double sx = 1., double sy = 1., 
		double sz = 1.);
		
		/** Create translation matrix.
		 *
		 * Create a translation matrix.
		 *
		 * \param tx Translation distance (x).
		 * \param ty Translation distance (y).
		 *
		 * \return Translation matrix.
		 */
		static Ionflux::GeoUtils::Matrix3 translate(double tx = 0., double ty = 
		0.);
		
		/** Create rotation matrix.
		 *
		 * Create a rotation matrix.
		 *
		 * \param phi Angle.
		 * \param axis Axis.
		 *
		 * \return Rotation matrix.
		 */
		static Ionflux::GeoUtils::Matrix3 rotate(double phi = 0., 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Matrix3& operator=(const 
		Ionflux::GeoUtils::Matrix3& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Matrix3* copy() const;
		
		/** Get row vector (0).
		 *
		 * \return Current value of row vector (0).
		 */
		virtual Ionflux::GeoUtils::Vector3 getR0() const;
		
		/** Set row vector (0).
		 *
		 * Set new value of row vector (0).
		 *
		 * \param newR0 New value of row vector (0).
		 */
		virtual void setR0(const Ionflux::GeoUtils::Vector3& newR0);
		
		/** Get row vector (1).
		 *
		 * \return Current value of row vector (1).
		 */
		virtual Ionflux::GeoUtils::Vector3 getR1() const;
		
		/** Set row vector (1).
		 *
		 * Set new value of row vector (1).
		 *
		 * \param newR1 New value of row vector (1).
		 */
		virtual void setR1(const Ionflux::GeoUtils::Vector3& newR1);
		
		/** Get row vector (2).
		 *
		 * \return Current value of row vector (2).
		 */
		virtual Ionflux::GeoUtils::Vector3 getR2() const;
		
		/** Set row vector (2).
		 *
		 * Set new value of row vector (2).
		 *
		 * \param newR2 New value of row vector (2).
		 */
		virtual void setR2(const Ionflux::GeoUtils::Vector3& newR2);
		
		/** Get column vector (0).
		 *
		 * \return Current value of column vector (0).
		 */
		virtual Ionflux::GeoUtils::Vector3 getC0() const;
		
		/** Set column vector (0).
		 *
		 * Set new value of column vector (0).
		 *
		 * \param newC0 New value of column vector (0).
		 */
		virtual void setC0(const Ionflux::GeoUtils::Vector3& newC0);
		
		/** Get column vector (1).
		 *
		 * \return Current value of column vector (1).
		 */
		virtual Ionflux::GeoUtils::Vector3 getC1() const;
		
		/** Set column vector (1).
		 *
		 * Set new value of column vector (1).
		 *
		 * \param newC1 New value of column vector (1).
		 */
		virtual void setC1(const Ionflux::GeoUtils::Vector3& newC1);
		
		/** Get column vector (2).
		 *
		 * \return Current value of column vector (2).
		 */
		virtual Ionflux::GeoUtils::Vector3 getC2() const;
		
		/** Set column vector (2).
		 *
		 * Set new value of column vector (2).
		 *
		 * \param newC2 New value of column vector (2).
		 */
		virtual void setC2(const Ionflux::GeoUtils::Vector3& newC2);
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
Ionflux::GeoUtils::Matrix3 operator*(double c, const 
Ionflux::GeoUtils::Matrix3& m);

}

}

/** \file Matrix3.hpp
 * \brief Matrix (3x3) (header).
 */
#endif
