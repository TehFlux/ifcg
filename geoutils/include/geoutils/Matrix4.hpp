#ifndef IONFLUX_GEOUTILS_MATRIX4
#define IONFLUX_GEOUTILS_MATRIX4
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix4.hpp                     Matrix (4x4) (header).
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
#include "geoutils/Vector3.hpp"
#include "geoutils/Matrix3.hpp"
#include "geoutils/Vector4.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Matrix4.
class Matrix4ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Matrix4ClassInfo();
		/// Destructor.
		virtual ~Matrix4ClassInfo();
};

/** Matrix (4x4).
 * \ingroup geoutils
 *
 * A 4x4 matrix.
 */
class Matrix4
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Elements.
		double* elements;
		
	public:
		/// Zero matrix.
		static const Ionflux::GeoUtils::Matrix4 ZERO;
		/// Unit matrix.
		static const Ionflux::GeoUtils::Matrix4 UNIT;
		/// Comparison tolerance.
		static const double COMPARE_TOLERANCE;
		/// Class information instance.
		static const Matrix4ClassInfo matrix4ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Matrix4 object.
		 */
		Matrix4();
		
		/** Constructor.
		 *
		 * Construct new Matrix4 object.
		 *
		 * \param other Other object.
		 */
		Matrix4(const Ionflux::GeoUtils::Matrix4& other);
		
		/** Constructor.
		 *
		 * Construct new Matrix4 object.
		 *
		 * \param initX00 Element x00.
		 * \param initX01 Element x01.
		 * \param initX02 Element x02.
		 * \param initX03 Element x03.
		 * \param initX10 Element x10.
		 * \param initX11 Element x11.
		 * \param initX12 Element x12.
		 * \param initX13 Element x13.
		 * \param initX20 Element x20.
		 * \param initX21 Element x21.
		 * \param initX22 Element x22.
		 * \param initX23 Element x23.
		 * \param initX30 Element x30.
		 * \param initX31 Element x31.
		 * \param initX32 Element x32.
		 * \param initX33 Element x33.
		 */
		Matrix4(double initX00, double initX01, double initX02, double initX03, 
		double initX10, double initX11, double initX12, double initX13, double 
		initX20, double initX21, double initX22, double initX23, double initX30, 
		double initX31, double initX32, double initX33);
		
		/** Constructor.
		 *
		 * Construct new Matrix4 object.
		 *
		 * \param initElements Element vector.
		 */
		Matrix4(const Ionflux::ObjectBase::DoubleVector& initElements);
		
		/** Constructor.
		 *
		 * Construct new Matrix4 object.
		 *
		 * \param initElements Element matrix.
		 */
		Matrix4(const Ionflux::GeoUtils::Matrix3& initElements);
		
		/** Destructor.
		 *
		 * Destruct Matrix4 object.
		 */
		virtual ~Matrix4();
		
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
		 * Set elements from a 3x3 matrix. The remaining elements will be left
		 * alone.
		 *
		 * \param newElements Element vector.
		 */
		virtual void setElements(const Ionflux::GeoUtils::Matrix3& newElements);
		
		/** Set elements.
		 *
		 * Set elements from a 3x3 matrix. The remaining elements will be set 
		 * to the optional parameters.
		 *
		 * \param newElements Element vector.
		 * \param newX33 Element x33.
		 * \param newX03 Element x03.
		 * \param newX13 Element x13.
		 * \param newX23 Element x23.
		 * \param newX30 Element x30.
		 * \param newX31 Element x31.
		 * \param newX32 Element x32.
		 */
		virtual void setM3x3(const Ionflux::GeoUtils::Matrix3& newElements, 
		double newX33 = 1., double newX03 = 0., double newX13 = 0., double newX23
		= 0., double newX30 = 0., double newX31 = 0., double newX32 = 0.);
		
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
		virtual bool eq(const Ionflux::GeoUtils::Matrix4& other, double t = 
		COMPARE_TOLERANCE);
		
		/** Transpose.
		 *
		 * Transpose the matrix.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix4 transpose() const;
		
		/** Permute columns.
		 *
		 * Permute the columns using the specified permutation of indices.
		 *
		 * \param px Permutation (x).
		 * \param py Permutation (y).
		 * \param pz Permutation (z).
		 * \param pw Permutation (w).
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix4 permuteColumns(int px, int py, int pz,
		int pw) const;
		
		/** Permute columns.
		 *
		 * Permute the columns using the specified permutation of indices.
		 *
		 * \param p Permutation.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix4 permuteColumns(const 
		Ionflux::ObjectBase::IntVector& p) const;
		
		/** Permute rows.
		 *
		 * Permute the rows using the specified permutation of indices.
		 *
		 * \param px Permutation (x).
		 * \param py Permutation (y).
		 * \param pz Permutation (z).
		 * \param pw Permutation (w).
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix4 permuteRows(int px, int py, int pz, 
		int pw) const;
		
		/** Permute rows.
		 *
		 * Permute the rows using the specified permutation of indices.
		 *
		 * \param p Permutation.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix4 permuteRows(const 
		Ionflux::ObjectBase::IntVector& p) const;
		
		/** Solve matrix equation.
		 *
		 * Solve the matrix equation Mx = v.
		 *
		 * \param v Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector4 solve(const 
		Ionflux::GeoUtils::Vector4& v) const;
		
		/** Invert matrix.
		 *
		 * Invert the matrix.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix4 invert() const;
		
		/** Multiply matrices (left).
		 *
		 * Multiply the specified matrix to the left of the matrix. The result
		 * is stored in the matrix itself.
		 *
		 * \param other Matrix.
		 *
		 * \return The matrix itself.
		 */
		virtual Ionflux::GeoUtils::Matrix4& multiplyLeft(const 
		Ionflux::GeoUtils::Matrix4& other);
		
		/** Multiply matrices (right).
		 *
		 * Multiply the specified matrix to the right of the matrix. The 
		 * result is stored in the matrix itself.
		 *
		 * \param other Matrix.
		 *
		 * \return The matrix itself.
		 */
		virtual Ionflux::GeoUtils::Matrix4& multiplyRight(const 
		Ionflux::GeoUtils::Matrix4& other);
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Matrix.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Matrix4& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Matrix.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Matrix4& other) const;
		
		/** Subscript operator.
		 *
		 * Subscript operator.
		 *
		 * \param index Index.
		 *
		 * \return Row vector with specified index.
		 */
		virtual Ionflux::GeoUtils::Vector4 operator[](int index) const;
		
		/** Multiply matrices.
		 *
		 * Multiply matrices.
		 *
		 * \param other Matrix.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix4 operator*(const 
		Ionflux::GeoUtils::Matrix4& other) const;
		
		/** Transform vector.
		 *
		 * Transform a vector.
		 *
		 * \param v Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector4 operator*(const 
		Ionflux::GeoUtils::Vector4& v) const;
		
		/** Multiply matrix by scalar.
		 *
		 * Multiply matrix by a scalar.
		 *
		 * \param c Scalar factor.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix4 operator*(double c) const;
		
		/** Divide matrix by scalar.
		 *
		 * Divide matrix by a scalar.
		 *
		 * \param c Scalar factor.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix4 operator/(double c) const;
		
		/** Get 3x3 matrix.
		 *
		 * Get the upper left 3x3 matrix.
		 *
		 * \return 3x3 matrix.
		 */
		virtual Ionflux::GeoUtils::Matrix3 getM3x3() const;
		
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
		 * \param sw Scale factor (w).
		 *
		 * \return Scale matrix.
		 */
		static Ionflux::GeoUtils::Matrix4 scale(double sx = 1., double sy = 1., 
		double sz = 1., double sw = 1.);
		
		/** Create scale matrix.
		 *
		 * Create a scale matrix.
		 *
		 * \param s Vector of scale factors.
		 * \param sw Scale factor (w).
		 *
		 * \return Scale matrix.
		 */
		static Ionflux::GeoUtils::Matrix4 scale(const Ionflux::GeoUtils::Vector3&
		s, double sw = 1.);
		
		/** Create scale matrix.
		 *
		 * Create a scale matrix.
		 *
		 * \param s Vector of scale factors.
		 *
		 * \return Scale matrix.
		 */
		static Ionflux::GeoUtils::Matrix4 scale(const Ionflux::GeoUtils::Vector4&
		s);
		
		/** Create translation matrix.
		 *
		 * Create a translation matrix.
		 *
		 * \param tx Translation distance (x).
		 * \param ty Translation distance (y).
		 * \param tz Translation distance (z).
		 *
		 * \return Translation matrix.
		 */
		static Ionflux::GeoUtils::Matrix4 translate(double tx = 0., double ty = 
		0., double tz = 0.);
		
		/** Create translation matrix.
		 *
		 * Create a translation matrix.
		 *
		 * \param t Translation vector.
		 *
		 * \return Translation matrix.
		 */
		static Ionflux::GeoUtils::Matrix4 translate(const 
		Ionflux::GeoUtils::Vector3& t);
		
		/** Create rotation matrix.
		 *
		 * Create a rotation matrix.
		 *
		 * \param phi Angle.
		 * \param axis Axis.
		 *
		 * \return Rotation matrix.
		 */
		static Ionflux::GeoUtils::Matrix4 rotate(double phi = 0., 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
		
		/** Create axis swap matrix.
		 *
		 * Create a matrix that swaps coordinate system axes.
		 *
		 * \param x Axis (x).
		 * \param y Axis (y).
		 * \param z Axis (z).
		 * \param w Axis (w).
		 *
		 * \return Axis swap matrix.
		 */
		static Ionflux::GeoUtils::Matrix4 swapAxes(Ionflux::GeoUtils::AxisID x = 
		Ionflux::GeoUtils::AXIS_X, Ionflux::GeoUtils::AxisID y = 
		Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID z = 
		Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID w = 
		Ionflux::GeoUtils::AXIS_W);
		
		/** Create perspective matrix.
		 *
		 * Create a perspective matrix.
		 *
		 * \param d Perspective factor.
		 * \param depthAxis Depth axis.
		 *
		 * \return Perspective matrix.
		 */
		static Ionflux::GeoUtils::Matrix4 perspective(double d = 1., 
		Ionflux::GeoUtils::AxisID depthAxis = Ionflux::GeoUtils::AXIS_Y);
		
		/** Create image transform matrix.
		 *
		 * Create a matrix which transforms a section of the up/horizon-plane 
		 * (the screen), centered on the depth axis, to the area of an image 
		 * of the specified size. The top left corner of the image has the 
		 * coordinates (0, 0). The positive X direction of the image is to the
		 * right, the positive Y direction is toward the bottom.
		 *
		 * \param screenWidth Screen width.
		 * \param screenHeight Screen height.
		 * \param imageWidth Image width.
		 * \param imageHeight Image height.
		 * \param upAxis Upward pointing axis.
		 * \param depthAxis Depth axis.
		 * \param horizonAxis Horizon axis.
		 *
		 * \return Image transform matrix.
		 */
		static Ionflux::GeoUtils::Matrix4 imageTransform(double screenWidth = 
		1.33, double screenHeight = 1., double imageWidth = 800., double 
		imageHeight = 600., Ionflux::GeoUtils::AxisID upAxis = 
		Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID depthAxis = 
		Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID horizonAxis = 
		Ionflux::GeoUtils::AXIS_X);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Matrix4& operator=(const 
		Ionflux::GeoUtils::Matrix4& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Matrix4* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Matrix4* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Matrix4* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get row vector (0).
		 *
		 * \return Current value of row vector (0).
		 */
		virtual Ionflux::GeoUtils::Vector4 getR0() const;
		
		/** Set row vector (0).
		 *
		 * Set new value of row vector (0).
		 *
		 * \param newR0 New value of row vector (0).
		 */
		virtual void setR0(const Ionflux::GeoUtils::Vector4& newR0);
		
		/** Get row vector (1).
		 *
		 * \return Current value of row vector (1).
		 */
		virtual Ionflux::GeoUtils::Vector4 getR1() const;
		
		/** Set row vector (1).
		 *
		 * Set new value of row vector (1).
		 *
		 * \param newR1 New value of row vector (1).
		 */
		virtual void setR1(const Ionflux::GeoUtils::Vector4& newR1);
		
		/** Get row vector (2).
		 *
		 * \return Current value of row vector (2).
		 */
		virtual Ionflux::GeoUtils::Vector4 getR2() const;
		
		/** Set row vector (2).
		 *
		 * Set new value of row vector (2).
		 *
		 * \param newR2 New value of row vector (2).
		 */
		virtual void setR2(const Ionflux::GeoUtils::Vector4& newR2);
		
		/** Get row vector (3).
		 *
		 * \return Current value of row vector (3).
		 */
		virtual Ionflux::GeoUtils::Vector4 getR3() const;
		
		/** Set row vector (3).
		 *
		 * Set new value of row vector (3).
		 *
		 * \param newR3 New value of row vector (3).
		 */
		virtual void setR3(const Ionflux::GeoUtils::Vector4& newR3);
		
		/** Get column vector (0).
		 *
		 * \return Current value of column vector (0).
		 */
		virtual Ionflux::GeoUtils::Vector4 getC0() const;
		
		/** Set column vector (0).
		 *
		 * Set new value of column vector (0).
		 *
		 * \param newC0 New value of column vector (0).
		 */
		virtual void setC0(const Ionflux::GeoUtils::Vector4& newC0);
		
		/** Get column vector (1).
		 *
		 * \return Current value of column vector (1).
		 */
		virtual Ionflux::GeoUtils::Vector4 getC1() const;
		
		/** Set column vector (1).
		 *
		 * Set new value of column vector (1).
		 *
		 * \param newC1 New value of column vector (1).
		 */
		virtual void setC1(const Ionflux::GeoUtils::Vector4& newC1);
		
		/** Get column vector (2).
		 *
		 * \return Current value of column vector (2).
		 */
		virtual Ionflux::GeoUtils::Vector4 getC2() const;
		
		/** Set column vector (2).
		 *
		 * Set new value of column vector (2).
		 *
		 * \param newC2 New value of column vector (2).
		 */
		virtual void setC2(const Ionflux::GeoUtils::Vector4& newC2);
		
		/** Get column vector (3).
		 *
		 * \return Current value of column vector (3).
		 */
		virtual Ionflux::GeoUtils::Vector4 getC3() const;
		
		/** Set column vector (3).
		 *
		 * Set new value of column vector (3).
		 *
		 * \param newC3 New value of column vector (3).
		 */
		virtual void setC3(const Ionflux::GeoUtils::Vector4& newC3);
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
Ionflux::GeoUtils::Matrix4 operator*(double c, const 
Ionflux::GeoUtils::Matrix4& m);

}

}

/** \file Matrix4.hpp
 * \brief Matrix (4x4) (header).
 */
#endif
