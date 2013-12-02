#ifndef IONFLUX_GEOUTILS_MATRIX3
#define IONFLUX_GEOUTILS_MATRIX3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
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
#include "geoutils/Vector4.hpp"
#include "geoutils/Matrix.hpp"

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
: public Ionflux::GeoUtils::Matrix
{
	private:
		
	protected:
		
	public:
		/// Number of elements.
		static const unsigned int NUM_ELEMENTS;
		/// Number of rows.
		static const unsigned int NUM_ROWS;
		/// Number of columns.
		static const unsigned int NUM_COLS;
		/// Zero matrix.
		static const Ionflux::GeoUtils::Matrix3 ZERO;
		/// Unit matrix.
		static const Ionflux::GeoUtils::Matrix3 UNIT;
		/// Class information instance.
		static const Matrix3ClassInfo matrix3ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
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
		 * \param initElements0 Element vector.
		 */
		Matrix3(const Ionflux::ObjectBase::DoubleVector& initElements0);
		
		/** Destructor.
		 *
		 * Destruct Matrix3 object.
		 */
		virtual ~Matrix3();
		
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
		
		/** Add matrices.
		 *
		 * Add matrices element-wise.
		 *
		 * \param other Matrix.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix3 operator+(const 
		Ionflux::GeoUtils::Matrix3& other) const;
		
		/** Subtract matrices.
		 *
		 * Subtract matrices.
		 *
		 * \param other Matrix.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Matrix3 operator-(const 
		Ionflux::GeoUtils::Matrix3& other) const;
		
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
		
		/** Get rotation axis/angle.
		 *
		 * Get the rotation axis and angle for a rotation matrix. The rotation
		 * axis is stored in the first three elements of the result vector. 
		 * The rotation angle is stored in the fourth element of the result 
		 * vector. If the matrix is not a rotation matrix, the result is 
		 * undefined.
		 *
		 * \return Axis/angle vector.
		 */
		virtual Ionflux::GeoUtils::Vector4 getAxisAngle() const;
		
		/** Get number of elements.
		 *
		 * Get the number of elements in the vector
		 *
		 * \return Number of elements.
		 */
		virtual unsigned int getNumElements() const;
		
		/** Get number of rows.
		 *
		 * Get the number of rows in the matrix
		 *
		 * \return Number of rows.
		 */
		virtual unsigned int getNumRows() const;
		
		/** Get number of columns.
		 *
		 * Get the number of columns in the matrix
		 *
		 * \return Number of columns.
		 */
		virtual unsigned int getNumCols() const;
		
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
		
		/** Create cross-product matrix.
		 *
		 * Create a cross-product matrix for the specified vector.
		 *
		 * \param v Vector.
		 *
		 * \return Cross-product matrix.
		 */
		static Ionflux::GeoUtils::Matrix3 crossProduct(const 
		Ionflux::GeoUtils::Vector3& v);
		
		/** Create rotation matrix.
		 *
		 * Create a rotation matrix for the specified rotation angle and axis.
		 *
		 * \param phi Angle.
		 * \param axis Axis vector.
		 *
		 * \return Rotation matrix.
		 */
		static Ionflux::GeoUtils::Matrix3 rotate(double phi, const 
		Ionflux::GeoUtils::Vector3& axis);
		
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
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Matrix3* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Matrix3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Matrix3 object.
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
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Matrix3* create(double initX00, double initX01,
		double initX02, double initX10, double initX11, double initX12, double 
		initX20, double initX21, double initX22, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Matrix3 object.
		 *
		 * \param initElements0 Element vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Matrix3* create(const 
		Ionflux::ObjectBase::DoubleVector& initElements0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Get XML element name.
		 *
		 * Get the XML element name for the object.
		 *
		 * \return XML element name
		 */
		virtual std::string getXMLElementName() const;
        
		/** Get XML attribute data.
		 *
		 * Get a string containing the XML attributes of the object.
		 *
		 * \return XML attribute data
		 */
		virtual std::string getXMLAttributeData() const;
        
        /** Get XML child data.
		 *
		 * Get the XML child data for the object.
		 *
		 * \param target Where to store the XML data.
		 * \param indentLevel Indentation level.
		 */
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
        
        /** Load from XML file.
		 *
		 * Initialize the object from an XML file.
		 *
		 * \param fileName file name
		 */
		virtual void loadFromXMLFile(const std::string& FileName);
		
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
