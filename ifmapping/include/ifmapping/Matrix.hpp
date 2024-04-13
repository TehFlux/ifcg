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
 * A matrix of floating point numbers.
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
		 * \param initValues Initial values.
		 */
		Matrix(unsigned int initNumRows, unsigned int initNumCols, const 
		Ionflux::ObjectBase::DoubleVector* const initValues = nullptr);
		
		/** Constructor.
		 *
		 * Construct new Matrix object.
		 *
		 * \param initNumRows Number of rows.
		 * \param initNumCols Number of columns.
		 * \param initV00 Initial value (0).
		 * \param initV01 Initial value (1).
		 * \param initV02 Initial value (2).
		 * \param initV03 Initial value (3).
		 * \param initV04 Initial value (4).
		 * \param initV05 Initial value (5).
		 * \param initV06 Initial value (6).
		 * \param initV07 Initial value (7).
		 * \param initV08 Initial value (8).
		 * \param initV09 Initial value (9).
		 * \param initV10 Initial value (10).
		 * \param initV11 Initial value (11).
		 */
		Matrix(unsigned int initNumRows, unsigned int initNumCols, double 
		initV00, double initV01 = 0., double initV02 = 0., double initV03 = 0., 
		double initV04 = 0., double initV05 = 0., double initV06 = 0., double 
		initV07 = 0., double initV08 = 0., double initV09 = 0., double initV10 = 
		0., double initV11 = 0.);
		
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
		
		/** Check whether indices are within bounds.
		 *
		 * Check whether the specified indices are within bounds of the 
		 * matrix.
		 *
		 * \param row Row.
		 * \param col Column.
		 *
		 * \return \c true if indices are within bounds, \c false otherwise.
		 */
		virtual bool isWithinBounds(unsigned int row, unsigned int col) const;
		
		/** Set value.
		 *
		 * Set the value at the specified position.
		 *
		 * \param row Row.
		 * \param col Column.
		 * \param v Value.
		 */
		virtual void setValue(unsigned int row, unsigned int col, double v);
		
		/** Set values from vector.
		 *
		 * Set values from a vector.
		 *
		 * \param newValues Values.
		 */
		virtual void setValues(const Ionflux::ObjectBase::DoubleVector 
		newValues);
		
		/** Get values.
		 *
		 * Get values.
		 * 
		 * The values will be stored in the \c target vector in row-major 
		 * order.
		 *
		 * \param target Target vector.
		 */
		virtual void getValues(Ionflux::ObjectBase::DoubleVector& target);
		
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
		
		/** Sample matrix columns.
		 *
		 * Sample the matrix columns with the specified number of samples.
		 * 
		 * The resulting column data is stored in the target matrix, which 
		 * should have a number of rows equal to the source matrix, and a 
		 * number of columns equal to the number of samples. If the target 
		 * matrix is not large enough to hold all of the data, the out of 
		 * bounds data will not be added to the matrix.
		 * 
		 * The optional \c sampleOffset can be used to center the samples 
		 * within the index range of matrix columns.
		 *
		 * \param numSamples Number of samples.
		 * \param target Target matrix in which to store the samples.
		 * \param sampleOffset Sample offset.
		 */
		virtual void sampleColumns(unsigned int numSamples, 
		Ionflux::Mapping::Matrix& target, double sampleOffset = 0.5);
		
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
		
		/** Get formatted value string.
		 *
		 * Get a formatted value string representation of the matrix.
		 *
		 * \param precision Precision.
		 * \param fieldWidth Field width.
		 * \param offsetCols Offset (columns).
		 * \param offsetRows Offset (rows).
		 * \param maxNumCols Maximum number of columns to be shown.
		 * \param maxNumRows Maximum number of rows to be shown.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueStringFormatted(unsigned int precision = 3, 
		unsigned int fieldWidth = 8, unsigned int offsetCols = 0, unsigned int 
		offsetRows = 0, unsigned int maxNumCols = 20, unsigned int maxNumRows = 
		20) const;
		
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
        
		/** Create instance.
		 *
		 * Create a new Matrix object.
		 *
		 * \param initNumRows Number of rows.
		 * \param initNumCols Number of columns.
		 * \param initValues Initial values.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Mapping::Matrix* create(unsigned int initNumRows, 
		unsigned int initNumCols, const Ionflux::ObjectBase::DoubleVector* const 
		initValues = nullptr, Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Matrix object.
		 *
		 * \param initNumRows Number of rows.
		 * \param initNumCols Number of columns.
		 * \param initV00 Initial value (0).
		 * \param initV01 Initial value (1).
		 * \param initV02 Initial value (2).
		 * \param initV03 Initial value (3).
		 * \param initV04 Initial value (4).
		 * \param initV05 Initial value (5).
		 * \param initV06 Initial value (6).
		 * \param initV07 Initial value (7).
		 * \param initV08 Initial value (8).
		 * \param initV09 Initial value (9).
		 * \param initV10 Initial value (10).
		 * \param initV11 Initial value (11).
		 * \param parentObject Parent object.
		 */
		static Ionflux::Mapping::Matrix* create(unsigned int initNumRows, 
		unsigned int initNumCols, double initV00, double initV01 = 0., double 
		initV02 = 0., double initV03 = 0., double initV04 = 0., double initV05 = 
		0., double initV06 = 0., double initV07 = 0., double initV08 = 0., double
		initV09 = 0., double initV10 = 0., double initV11 = 0., 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
