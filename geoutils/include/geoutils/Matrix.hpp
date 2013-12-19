#ifndef IONFLUX_GEOUTILS_MATRIX
#define IONFLUX_GEOUTILS_MATRIX
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix.hpp                      Matrix (header).
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
#include "geoutils/Vector.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class MatrixXMLFactory;

}

/// Class information for class Matrix.
class MatrixClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		MatrixClassInfo();
		/// Destructor.
		virtual ~MatrixClassInfo();
};

/** Matrix.
 * \ingroup geoutils
 *
 * A numeric matrix.
 */
class Matrix
: public Ionflux::GeoUtils::Vector
{
	private:
		
	protected:
		
	public:
		/// Number of rows.
		static const unsigned int NUM_ROWS;
		/// Number of columns.
		static const unsigned int NUM_COLS;
		/// Class information instance.
		static const MatrixClassInfo matrixClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new Matrix object.
		 */
		Matrix();
		
		/** Constructor.
		 *
		 * Construct new Matrix object.
		 *
		 * \param other Other object.
		 */
		Matrix(const Ionflux::GeoUtils::Matrix& other);
		
		/** Destructor.
		 *
		 * Destruct Matrix object.
		 */
		virtual ~Matrix();
		
		/** Get element.
		 *
		 * Get the element at the specified index.
		 *
		 * \param rowIndex Row index.
		 * \param colIndex Column index.
		 *
		 * \return Element at the specified index.
		 */
		virtual double getElement(unsigned int rowIndex, unsigned int colIndex) 
		const;
		
		/** Set element.
		 *
		 * Set the element at the specified index.
		 *
		 * \param index Index.
		 * \param value Value.
		 */
		virtual void setElement(unsigned int index, double value);
		
		/** Set element.
		 *
		 * Set the element at the specified index.
		 *
		 * \param rowIndex Row index.
		 * \param colIndex Column index.
		 * \param value Value.
		 */
		virtual void setElement(unsigned int rowIndex, unsigned int colIndex, 
		double value);
		
		/** Get row vector.
		 *
		 * Get the row vector at the specified index.
		 *
		 * \param rowIndex Row index.
		 * \param target Where to store the vector.
		 */
		virtual void getRow(unsigned int rowIndex, Ionflux::GeoUtils::Vector& 
		target) const;
		
		/** Get column vector.
		 *
		 * Get the column vector at the specified index.
		 *
		 * \param colIndex Column index.
		 * \param target Where to store the vector.
		 */
		virtual void getCol(unsigned int colIndex, Ionflux::GeoUtils::Vector& 
		target) const;
		
		/** Transpose (in-place).
		 *
		 * Transpose the matrix (in-place).
		 */
		virtual void transposeIP();
		
		/** Trace.
		 *
		 * Calculate the trace of the matrix.
		 *
		 * \return Trace of the matrix.
		 */
		virtual double trace() const;
		
		/** Transform.
		 *
		 * Transform a column vector by multiplying the matrix from the left.
		 *
		 * \param v vector.
		 * \param target Where to store the result.
		 */
		virtual void transform(const Ionflux::GeoUtils::Vector& v, 
		Ionflux::GeoUtils::Vector& target);
		
		/** Multiply.
		 *
		 * Multiply the matrix with another matrix.
		 *
		 * \param other Matrix.
		 * \param target Where to store the result.
		 */
		virtual void multiply(const Ionflux::GeoUtils::Matrix& other, 
		Ionflux::GeoUtils::Matrix& target);
		
		/** Permute rows (in-place).
		 *
		 * Permute rows in the matrix (in-place) using the specified 
		 * permutation vector.
		 *
		 * \param p permutation vector.
		 */
		virtual void permuteRowsIP(const Ionflux::GeoUtils::Vector& p);
		
		/** Permute columns (in-place).
		 *
		 * Permute columns in the matrix (in-place) using the specified 
		 * permutation vector.
		 *
		 * \param p permutation vector.
		 */
		virtual void permuteColsIP(const Ionflux::GeoUtils::Vector& p);
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
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
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Matrix& operator=(const 
		Ionflux::GeoUtils::Matrix& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Matrix* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Matrix* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Matrix* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
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
        
        /** Get XML object factory
		 *
		 * Get the XML object factory singleton for the class.
		 *
		 * \param fileName file name
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
};

}

}

/** \file Matrix.hpp
 * \brief Matrix (header).
 */
#endif
