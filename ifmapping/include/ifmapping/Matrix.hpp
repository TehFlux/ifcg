#ifndef IONFLUX_MAPPING_MATRIX
#define IONFLUX_MAPPING_MATRIX
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix.hpp                      Matrix (header).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
 * 
 * IFMapping - Ionflux Mapping Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFMapping - Ionflux Mapping Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "ifmapping/types.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Mapping
{

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
 * \ingroup ifmapping
 *
 * A matrix of float numbers.
 */
class Matrix
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Values.
		double* values;
		/// Number of rows.
		unsigned int numRows;
		/// Number of columns.
		unsigned int numCols;
		
		/** Allocate value buffer.
		 *
		 * Allocate the value buffer.
		 *
		 * \param newNumRows Number of rows.
		 * \param newNumCols Number of columns.
		 */
		virtual void allocate(unsigned int newNumRows = 0, unsigned int 
		newNumCols = 0);
		
	public:
		/// Class information instance.
		static const MatrixClassInfo matrixClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
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
		Matrix(const Ionflux::Mapping::Matrix& other);
		
		/** Constructor.
		 *
		 * Construct new Matrix object.
		 *
		 * \param initNumRows Number of rows.
		 * \param initNumCols Number of columns.
		 */
		Matrix(unsigned int initNumRows, unsigned int initNumCols = 0);
		
		/** Destructor.
		 *
		 * Destruct Matrix object.
		 */
		virtual ~Matrix();
		
		/** Initialize.
		 *
		 * Initialize the matrix.
		 *
		 * \param newNumRows Number of rows.
		 * \param newNumCols Number of columns.
		 */
		virtual void init(unsigned int newNumRows = 0, unsigned int newNumCols = 
		0);
		
		/** Set value.
		 *
		 * Set the value at the specified position.
		 *
		 * \param row Row.
		 * \param col Column.
		 * \param v Value.
		 */
		virtual void setValue(unsigned int row, unsigned int col, double v);
		
		/** Get value.
		 *
		 * Get the value at the specified position.
		 *
		 * \param row Row.
		 * \param col Column.
		 *
		 * \return Value at the specified position..
		 */
		virtual double getValue(unsigned int row, unsigned int col) const;
		
		/** Get row.
		 *
		 * Get the specified row of the matrix.
		 * 
		 * The result will be stored in \c target.
		 *
		 * \param row Row index.
		 * \param target Target vector.
		 */
		virtual void getRow(unsigned int row, Ionflux::ObjectBase::DoubleVector& 
		target) const;
		
		/** Get column.
		 *
		 * Get the specified column of the matrix.
		 * 
		 * The result will be stored in \c target.
		 *
		 * \param col Column index.
		 * \param target Target vector.
		 */
		virtual void getCol(unsigned int col, Ionflux::ObjectBase::DoubleVector& 
		target) const;
		
		/** Get value.
		 *
		 * Get the value at the specified position.
		 *
		 * \param row Row.
		 * \param col Column.
		 *
		 * \return Value at the specified position..
		 */
		virtual double v(unsigned int row, unsigned int col) const;
		
		/** Normalize.
		 *
		 * Normalize the values in the matrix.
		 */
		virtual void normalize();
		
		/** Rescale.
		 *
		 * Rescale the values in the matrix to the range [0...1].
		 */
		virtual void rescale();
		
		/** Set matrix to gaussian distribution.
		 *
		 * Set the matrix to a gaussian distribution with the specified 
		 * parameters. If the standard deviation is set to 0, a suitable 
		 * default value will be chosen. The values in the matrix will be 
		 * normalized.
		 *
		 * \param stdDev Standard deviation.
		 */
		virtual void setGaussian(double stdDev = 0.);
		
		/** Set matrix to inverse power distribution.
		 *
		 * Set the matrix to an inverse power distribution with the specified 
		 * parameters. The values in the matrix will be normalized.
		 *
		 * \param exponent Exponent.
		 * \param falloff Falloff at radius.
		 */
		virtual void setInversePower(double exponent = 2., double falloff = 
		0.0001);
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Matrix.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::Mapping::Matrix& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Matrix.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::Mapping::Matrix& other) const;
		
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
		virtual Ionflux::Mapping::Matrix& operator=(const 
		Ionflux::Mapping::Matrix& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::Matrix* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::Matrix* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::Mapping::Matrix* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get number of rows.
		 *
		 * \return Current value of number of rows.
		 */
		virtual unsigned int getNumRows() const;
		
		/** Get number of columns.
		 *
		 * \return Current value of number of columns.
		 */
		virtual unsigned int getNumCols() const;
};

}

}

/** \file Matrix.hpp
 * \brief Matrix (header).
 */
#endif
