#ifndef IONFLUX_GEOUTILS_MATRIXMN
#define IONFLUX_GEOUTILS_MATRIXMN
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * MatrixMN.hpp                    Matrix (NxM) (header).
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

#include "geoutils/Matrix.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class VectorN;

namespace XMLUtils
{

class MatrixMNXMLFactory;

}

/// Class information for class MatrixMN.
class MatrixMNClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		MatrixMNClassInfo();
		/// Destructor.
		virtual ~MatrixMNClassInfo();
};

/** Matrix (NxM).
 * \ingroup ifphysim
 *
 * A NxM numeric matrix.
 */
class MatrixMN
: public Ionflux::GeoUtils::Matrix
{
	private:
		
	protected:
		/// Number of rows.
		unsigned int numRows;
		/// Number of columns.
		unsigned int numCols;
		
	public:
		/// Class information instance.
		static const MatrixMNClassInfo matrixMNClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new MatrixMN object.
		 */
		MatrixMN();
		
		/** Constructor.
		 *
		 * Construct new MatrixMN object.
		 *
		 * \param other Other object.
		 */
		MatrixMN(const Ionflux::GeoUtils::MatrixMN& other);
		
		/** Constructor.
		 *
		 * Construct new MatrixMN object.
		 *
		 * \param initNumRows Number of rows.
		 * \param initNumCols Number of columns.
		 */
		MatrixMN(unsigned int initNumRows, unsigned int initNumCols);
		
		/** Constructor.
		 *
		 * Construct new MatrixMN object.
		 *
		 * \param initNumCols Number of columns.
		 * \param initNumRows Number of columns.
		 * \param x0 element (0).
		 * \param x1 element (1).
		 * \param x2 element (2).
		 * \param x3 element (3).
		 * \param x4 element (4).
		 * \param x5 element (5).
		 * \param x6 element (6).
		 * \param x7 element (7).
		 * \param x8 element (8).
		 * \param x9 element (9).
		 * \param x10 element (10).
		 * \param x11 element (11).
		 * \param x12 element (12).
		 */
		MatrixMN(unsigned int initNumCols, unsigned int initNumRows, double x0, 
		double x1 = 0., double x2 = 0., double x3 = 0., double x4 = 0., double x5
		= 0., double x6 = 0., double x7 = 0., double x8 = 0., double x9 = 0., 
		double x10 = 0., double x11 = 0., double x12 = 0.);
		
		/** Destructor.
		 *
		 * Destruct MatrixMN object.
		 */
		virtual ~MatrixMN();
		
		/** Transpose.
		 *
		 * Transpose the matrix.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::MatrixMN transpose() const;
		
		/** QR decomposition.
		 *
		 * Calculate the QR decomposition M = QR of the matrix.
		 *
		 * \param q Q.
		 * \param r R.
		 */
		virtual void qrDecomp(Ionflux::GeoUtils::MatrixMN& q, 
		Ionflux::GeoUtils::MatrixMN& r) const;
		
		/** Solve.
		 *
		 * Solve the system M x = b, where M is the matrix itself.
		 *
		 * \param b b.
		 *
		 * \return Result of the computation.
		 */
		virtual Ionflux::GeoUtils::VectorN solve(const 
		Ionflux::GeoUtils::VectorN& b) const;
		
		/** Invert.
		 *
		 * Invert the matrix (if possible).
		 *
		 * \return Result of the computation.
		 */
		virtual Ionflux::GeoUtils::MatrixMN invert() const;
		
		/** Get number of elements.
		 *
		 * Get the number of elements in the matrix
		 *
		 * \return Number of elements.
		 */
		virtual unsigned int getNumElements() const;
		
		/** QR solve.
		 *
		 * Solve the system R x = Q^T b.
		 *
		 * \param q Q.
		 * \param r R.
		 * \param b b.
		 * \param x x.
		 */
		static void qrSolve(const Ionflux::GeoUtils::MatrixMN& q, const 
		Ionflux::GeoUtils::MatrixMN& r, const Ionflux::GeoUtils::VectorN& b, 
		Ionflux::GeoUtils::VectorN& x);
		
		/** Multiply matrices.
		 *
		 * Multiply matrices.
		 *
		 * \param other Matrix.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::MatrixMN operator*(const 
		Ionflux::GeoUtils::Matrix& other) const;
		
		/** Transform a vector.
		 *
		 * Transform a vector.
		 *
		 * \param v Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::VectorN operator*(const 
		Ionflux::GeoUtils::VectorN& v) const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::MatrixMN& operator=(const 
		Ionflux::GeoUtils::MatrixMN& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::MatrixMN* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::MatrixMN* upcast(Ionflux::ObjectBase::IFObject*
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
		static Ionflux::GeoUtils::MatrixMN* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new MatrixMN object.
		 *
		 * \param initNumRows Number of rows.
		 * \param initNumCols Number of columns.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::MatrixMN* create(unsigned int initNumRows, 
		unsigned int initNumCols, Ionflux::ObjectBase::IFObject* parentObject = 
		0);
        
		/** Create instance.
		 *
		 * Create a new MatrixMN object.
		 *
		 * \param initNumCols Number of columns.
		 * \param initNumRows Number of columns.
		 * \param x0 element (0).
		 * \param x1 element (1).
		 * \param x2 element (2).
		 * \param x3 element (3).
		 * \param x4 element (4).
		 * \param x5 element (5).
		 * \param x6 element (6).
		 * \param x7 element (7).
		 * \param x8 element (8).
		 * \param x9 element (9).
		 * \param x10 element (10).
		 * \param x11 element (11).
		 * \param x12 element (12).
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::MatrixMN* create(unsigned int initNumCols, 
		unsigned int initNumRows, double x0, double x1 = 0., double x2 = 0., 
		double x3 = 0., double x4 = 0., double x5 = 0., double x6 = 0., double x7
		= 0., double x8 = 0., double x9 = 0., double x10 = 0., double x11 = 0., 
		double x12 = 0., Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
		
		/** Get number of rows.
		 *
		 * \return Current value of number of rows.
		 */
		virtual unsigned int getNumRows() const;
		
		/** Set number of rows.
		 *
		 * Set new value of number of rows.
		 *
		 * \param newNumRows New value of number of rows.
		 */
		virtual void setNumRows(unsigned int newNumRows);
		
		/** Get number of columns.
		 *
		 * \return Current value of number of columns.
		 */
		virtual unsigned int getNumCols() const;
		
		/** Set number of columns.
		 *
		 * Set new value of number of columns.
		 *
		 * \param newNumCols New value of number of columns.
		 */
		virtual void setNumCols(unsigned int newNumCols);
};

}

}

/** \file MatrixMN.hpp
 * \brief Matrix (NxM) (header).
 */
#endif
