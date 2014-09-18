#ifndef IONFLUX_GEOUTILS_MATRIX2
#define IONFLUX_GEOUTILS_MATRIX2
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
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
#include "geoutils/Matrix.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class Matrix2XMLFactory;

}

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
		static const Ionflux::GeoUtils::Matrix2 ZERO;
		/// Unit matrix.
		static const Ionflux::GeoUtils::Matrix2 UNIT;
		/// Class information instance.
		static const Matrix2ClassInfo matrix2ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
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
		 * \param initElements0 Element vector.
		 */
		Matrix2(const Ionflux::ObjectBase::DoubleVector& initElements0);
		
		/** Destructor.
		 *
		 * Destruct Matrix2 object.
		 */
		virtual ~Matrix2();
		
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
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Matrix2* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Matrix2* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Matrix2 object.
		 *
		 * \param initX00 Element x00.
		 * \param initX01 Element x01.
		 * \param initX10 Element x10.
		 * \param initX11 Element x11.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Matrix2* create(double initX00, double initX01,
		double initX10, double initX11, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Matrix2 object.
		 *
		 * \param initElements0 Element vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Matrix2* create(const 
		Ionflux::ObjectBase::DoubleVector& initElements0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
        
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
		virtual void loadFromXMLFile(const std::string& fileName);
        
        /** Get XML object factory
		 *
		 * Get the XML object factory singleton for the class.
		 * 
		 * return XML object factory
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		
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
