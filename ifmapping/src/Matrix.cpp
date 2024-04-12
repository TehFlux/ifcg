/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix.cpp                      Matrix (implementation).
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

#include "ifmapping/Matrix.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "ifmapping/MappingError.hpp"

using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

MatrixClassInfo::MatrixClassInfo()
{
	name = "Matrix";
	desc = "Matrix";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

MatrixClassInfo::~MatrixClassInfo()
{
}

// run-time type information instance constants
const MatrixClassInfo Matrix::matrixClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Matrix::CLASS_INFO = &Matrix::matrixClassInfo;

Matrix::Matrix()
: values(0), numRows(0), numCols(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Matrix::Matrix(const Ionflux::Mapping::Matrix& other)
: values(0), numRows(0), numCols(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Matrix::Matrix(unsigned int initNumRows, unsigned int initNumCols, const 
Ionflux::ObjectBase::DoubleVector* const initValues)
: values(0), numRows(initNumRows), numCols(initNumCols)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	init(initNumRows, initNumCols);
	if (initValues != nullptr)
		setValues(*initValues);
}

Matrix::~Matrix()
{
	if (values != 0)
	    delete values;
	values = 0;
}

void Matrix::allocate(unsigned int newNumRows, unsigned int newNumCols)
{
	// Default to the current number of rows/cols.
	if(newNumRows == 0)
	    newNumRows = numRows;
	if(newNumCols == 0)
	    newNumCols = numCols;
	// Default to square matrix.
	if(newNumCols == 0)
	    newNumCols = newNumRows;
	unsigned int newSize = newNumRows * newNumCols;
	unsigned int size = numRows * numCols;
	numRows = newNumRows;
	numCols = newNumCols;
	if ((values != 0) 
	    && (newSize == size))
	    // Buffer can be reused.
	    return;
	if (values != 0)
	    delete values;
	values = 0;
	size = newSize;
	if (size == 0)
	    // Empty matrix.
	    return;
	values = new double[size];
	if (values == 0)
	    throw MappingError("Could not allocate value buffer.");
}

void Matrix::init(unsigned int newNumRows, unsigned int newNumCols)
{
	allocate(newNumRows, newNumCols);
	for (unsigned int i = 0; i < numRows; i++)
	    for (unsigned int j = 0; j < numCols; j++)
	        values[i * numCols + j] = 0.;
}

void Matrix::setValue(unsigned int row, unsigned int col, double v)
{
	if ((row >= numRows) 
	    || (col >= numCols))
	{
	    std::ostringstream status;
	    status << "[Matrix::setValue] "
	        "Index out of bounds: (" << row << ", " << col << ") "
	        "(size = (" << numRows << ", " << numCols << "))";
	    throw MappingError(status.str());
	}
	values[row * numCols + col] = v;
}

void Matrix::setValues(const Ionflux::ObjectBase::DoubleVector newValues)
{
	unsigned int numValues = newValues.size();
	unsigned int i = 0;
	unsigned int k = 0;
	while ((k < numValues) && (i < numRows))
	{
		unsigned int j = 0;
		while ((k < numValues) && (j < numCols))
		{
			values[i * numCols + j] = newValues[k];
			k++;
			j++;
		}
		i++;
	}
}

void Matrix::getValues(Ionflux::ObjectBase::DoubleVector& target)
{
	for (unsigned int i = 0; i < numRows; i++)
		for (unsigned int j = 0; j < numCols; j++)
			target.push_back(values[i * numCols + j]);
}

double Matrix::getValue(unsigned int row, unsigned int col) const
{
	if ((row >= numRows) 
	    || (col >= numCols))
	    throw MappingError("Index out of bounds.");
	return values[row * numCols + col];
}

void Matrix::getRow(unsigned int row, Ionflux::ObjectBase::DoubleVector& 
target) const
{
	if (row >= numRows) 
	    throw MappingError("Row index out of bounds.");
	for (unsigned int i = 0; i < numCols; i++)
		target.push_back(values[row * numCols + i]);
}

void Matrix::getCol(unsigned int col, Ionflux::ObjectBase::DoubleVector& 
target) const
{
	if (col >= numCols) 
	    throw MappingError("Column index out of bounds.");
	for (unsigned int i = 0; i < numRows; i++)
		target.push_back(values[i * numCols + col]);
}

double Matrix::v(unsigned int row, unsigned int col) const
{
	// TODO: Implementation.
	return getValue(row, col);
}

void Matrix::normalize()
{
	double sum = 0.;
	for (unsigned int i = 0; i < numRows; i++)
	    for (unsigned int j = 0; j < numCols; j++)
	        sum += values[i * numCols + j];
	for (unsigned int i = 0; i < numRows; i++)
	    for (unsigned int j = 0; j < numCols; j++)
	    {
	        double v0 = values[i * numCols + j] / sum;
	        values[i * numCols + j] = v0;
	    }
}

void Matrix::rescale()
{
	double vMin = 0.;
	double vMax = 0.;
	bool first = false;
	for (unsigned int i = 0; i < numRows; i++)
	    for (unsigned int j = 0; j < numCols; j++)
	    {
	        double v = values[i * numCols + j];
	        if (first)
	        {
	            vMin = v;
	            vMax = v;
	            first = false;
	        } else
	        {
	            if (v < vMin)
	                vMin = v;
	            if (v > vMax)
	                vMax = v;
	        }
	    }
	for (unsigned int i = 0; i < numRows; i++)
	    for (unsigned int j = 0; j < numCols; j++)
	    {
	        double v0 = (values[i * numCols + j] - vMin) / (vMax - vMin);
	        values[i * numCols + j] = v0;
	    }
}

void Matrix::setGaussian(double stdDev)
{
	double x0 = 0.5 * numCols;
	double y0 = 0.5 * numRows;
	if (stdDev == 0.)
	    stdDev = fmax(0.3 * x0, 0.3 * y0);
	double var = stdDev * stdDev;
	for (unsigned int i = 0; i < numRows; i++)
	    for (unsigned int j = 0; j < numCols; j++)
	    {
	        double x = (static_cast<double>(j) - x0) + 0.5;
	        double y = (static_cast<double>(i) - y0) + 0.5;
	        double f = ::exp(-(x * x + y * y) / (2. * var));
	        values[i * numCols + j] = f;
	    }
	normalize();
}

void Matrix::setInversePower(double exponent, double falloff)
{
	double x0 = 0.5 * numCols;
	double y0 = 0.5 * numRows;
	double c = (::pow(1. / falloff, 1. / exponent) - 1.) / fmax(x0, y0);
	for (unsigned int i = 0; i < numRows; i++)
	    for (unsigned int j = 0; j < numCols; j++)
	    {
	        double x = (static_cast<double>(j) - x0) + 0.5;
	        double y = (static_cast<double>(i) - y0) + 0.5;
	        double f = 1. / ::pow(c * ::sqrt(x * x + y * y) + 1., exponent);
	        values[i * numCols + j] = f;
	    }
	normalize();
}

bool Matrix::operator==(const Ionflux::Mapping::Matrix& other) const
{
	if ((other.numRows != numRows) 
	    || (other.numCols != numCols))
	    return false;
	for (unsigned int i = 0; i < numRows; i++)
	    for (unsigned int j = 0; j < numCols; j++)
	        if (values[i * numCols + j] != other.values[i * numCols + j])
	            return false;
	return true;
}

bool Matrix::operator!=(const Ionflux::Mapping::Matrix& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

std::string Matrix::getString() const
{
	std::ostringstream state;
	state << getClassName() << "[";
	for (unsigned int i = 0; i < numRows; i++)
	{
	    if (i > 0)
	        state << ", ";
	    state << "[";
	    for (unsigned int j = 0; j < numCols; j++)
	    {
	        if (j > 0)
	            state << ", ";
	        state << values[i * numCols + j];
	    }
	    state << "]";
	}
	state << "]";
	return state.str();
}

unsigned int Matrix::getNumRows() const
{
    return numRows;
}

unsigned int Matrix::getNumCols() const
{
    return numCols;
}

Ionflux::Mapping::Matrix& Matrix::operator=(const Ionflux::Mapping::Matrix&
other)
{
    if (values == other.values)
    	return *this;
    allocate(other.numRows, other.numCols);
    for (unsigned int i = 0; i < numRows; i++)
    	for (unsigned int j = 0; j < numCols; j++)
    		values[i * numCols + j] = other.values[i * numCols + j];
    return *this;
}

Ionflux::Mapping::Matrix* Matrix::copy() const
{
    Matrix* newMatrix = create();
    *newMatrix = *this;
    return newMatrix;
}

Ionflux::Mapping::Matrix* Matrix::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Matrix*>(other);
}

Ionflux::Mapping::Matrix* Matrix::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Matrix* newObject = new Matrix();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Mapping::Matrix* Matrix::create(unsigned int initNumRows, unsigned
int initNumCols, const Ionflux::ObjectBase::DoubleVector* const initValues,
Ionflux::ObjectBase::IFObject* parentObject)
{
    Matrix* newObject = new Matrix(initNumRows, initNumCols, initValues);
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Matrix::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Matrix.cpp
 * \brief Matrix implementation.
 */
