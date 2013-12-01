/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix.cpp                      Matrix (implementation).
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
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/utils.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "geoutils/xmlutils.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

MatrixClassInfo::MatrixClassInfo()
{
	name = "Matrix";
	desc = "Matrix";
}

MatrixClassInfo::~MatrixClassInfo()
{
}

// public member constants
const unsigned int Matrix::NUM_ROWS = 0;
const unsigned int Matrix::NUM_COLS = 0;

// run-time type information instance constants
const MatrixClassInfo Matrix::matrixClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Matrix::CLASS_INFO = &Matrix::matrixClassInfo;

const std::string Matrix::XML_ELEMENT_NAME = "m";

Matrix::Matrix()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Matrix::Matrix(const Ionflux::GeoUtils::Matrix& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Matrix::~Matrix()
{
	// TODO: Nothing ATM. ;-)
}

double Matrix::getElement(unsigned int rowIndex, unsigned int colIndex) 
const
{
	unsigned int numRows = getNumRows();
	unsigned int numCols = getNumCols();
	if ((rowIndex >= numRows) 
	    || (colIndex >= numCols))
	{
	    std::ostringstream status;
	    status << "Index out of range: (" << rowIndex << ", " 
	        << colIndex << ")";
	    throw GeoUtilsError(getErrorString(status.str(), "getElement"));
	}
	return (*this)[numCols * rowIndex + colIndex];;
}

void Matrix::setElement(unsigned int rowIndex, unsigned int colIndex, 
double value)
{
	unsigned int numRows = getNumRows();
	unsigned int numCols = getNumCols();
	if ((rowIndex >= numRows) 
	    || (colIndex >= numCols))
	{
	    std::ostringstream status;
	    status << "Index out of range: (" << rowIndex << ", " 
	        << colIndex << ")";
	    throw GeoUtilsError(getErrorString(status.str(), "setElement"));
	}
	Vector::setElement(numCols * rowIndex + colIndex, value);
}

void Matrix::getRow(unsigned int rowIndex, Ionflux::GeoUtils::Vector& 
target) const
{
	unsigned int numRows = getNumRows();
	unsigned int numCols = getNumCols();
	if (rowIndex >= numRows)
	{
	    std::ostringstream status;
	    status << "Index out of range: " << rowIndex;
	    throw GeoUtilsError(getErrorString(status.str(), "getRow"));
	}
	unsigned int offset = rowIndex * numCols;
	for (unsigned i = 0; i < numCols; i++)
	    target.setElement(i, elements[offset + i]);
}

void Matrix::getCol(unsigned int colIndex, Ionflux::GeoUtils::Vector& 
target) const
{
	unsigned int numRows = getNumRows();
	unsigned int numCols = getNumCols();
	if (colIndex >= numCols)
	{
	    std::ostringstream status;
	    status << "Index out of range: " << colIndex;
	    throw GeoUtilsError(getErrorString(status.str(), "getCol"));
	}
	for (unsigned i = 0; i < numRows; i++)
	    target.setElement(i, elements[i * numCols + colIndex]);
}

void Matrix::transposeIP()
{
	unsigned int numRows = getNumRows();
	unsigned int numCols = getNumCols();
	if (numRows != numCols)
	{
	    std::ostringstream status;
	    status << "Cannot transpose non-square matrix (" << numRows 
	        << "x" << numCols << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "transposeIP"));
	}
	/* <---- DEBUG ----- //
	std::cerr << "[Matrix::transposeIP] DEBUG: " 
	    "numRows = " << numRows << ", numCols = " << numCols
	    << std::endl;
	// ----- DEBUG ----> */
	for (unsigned int i = 0; i < numRows; i++)
	{
	    for (unsigned int k = 0; k < i; k++)
	    {
	        unsigned int i0 = i * numCols + k;
	        unsigned int i1 = k * numCols + i;
	        double t0 = elements[i0];
	        /* <---- DEBUG ----- //
	        std::cerr << "[Matrix::transposeIP] DEBUG: " 
	            "swapping (" << i << ", " << k << ") <-> ("
	            << k << ", " << i << "): " << t0 << " <-> " << elements[i1]
	            << std::endl;
	        // ----- DEBUG ----> */
	        elements[i0] = elements[i1];
	        elements[i1] = t0;
	    }
	}
}

double Matrix::trace()
{
	unsigned int numRows = getNumRows();
	unsigned int numCols = getNumCols();
	double result = 0.;
	unsigned int k = 0;
	while ((k < numRows) 
	    && (k < numCols))
	{
	    result += elements[k * numCols + k];
	    k++;
	}
	return result;
}

void Matrix::transform(const Ionflux::GeoUtils::Vector& v, 
Ionflux::GeoUtils::Vector& target)
{
	unsigned int numRows = getNumRows();
	unsigned int numCols = getNumCols();
	unsigned int oNumElements = v.getNumElements();
	unsigned int tNumElements = target.getNumElements();
	if (numCols != oNumElements)
	{
	    std::ostringstream status;
	    status << "Matrix and vector have incompatible dimensions (this: " 
	        << numRows << "x" << numCols << ", other: " 
	        << oNumElements << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "transform"));
	}
	if ((oNumElements != tNumElements) 
	    || (numRows != tNumElements))
	{
	    std::ostringstream status;
	    status << "Matrix and vectors have incompatible dimensions (this: " 
	        << numRows << "x" << numCols << ", other: " 
	        << oNumElements << ", target: "
	        << tNumElements << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "transform"));
	}
	for (unsigned int i = 0; i < tNumElements; i++)
	{
	    double s = 0.;
	    for (unsigned int k = 0; k < numCols; k++)
	    {
	        unsigned int i0 = i * numCols + k;
	        s += (elements[i0] * v.getElement(k));
	    }
	    target.setElement(i, s);
	}
}

void Matrix::multiply(const Ionflux::GeoUtils::Matrix& other, 
Ionflux::GeoUtils::Matrix& target)
{
	unsigned int numRows = getNumRows();
	unsigned int numCols = getNumCols();
	unsigned int oNumRows = other.getNumRows();
	unsigned int oNumCols = other.getNumCols();
	unsigned int tNumRows = target.getNumRows();
	unsigned int tNumCols = target.getNumCols();
	if (numCols != oNumRows)
	{
	    std::ostringstream status;
	    status << "Matrices have incompatible dimensions (this: " 
	        << numRows << "x" << numCols << ", other: " 
	        << oNumRows << "x" << oNumCols << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "multiply"));
	}
	if ((oNumCols != tNumCols) 
	    || (numRows != tNumRows))
	{
	    std::ostringstream status;
	    status << "Matrices have incompatible dimensions (this: " 
	        << numRows << "x" << numCols << ", other: " 
	        << oNumRows << "x" << oNumCols << ", target: "
	        << tNumRows << "x" << tNumCols << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "multiply"));
	}
	for (unsigned int i = 0; i < tNumRows; i++)
	    for (unsigned int k = 0; k < tNumCols; k++)
	    {
	        double s = 0.;
	        for (unsigned int m = 0; m < numCols; m++)
	        {
	            unsigned int i0 = i * numCols + m;
	            unsigned int i1 = m * numCols + k;
	            s += (elements[i0] * other.elements[i1]);
	        }
	        unsigned int i2 = i * tNumCols + k;
	        target.elements[i2] = s;
	    }
}

void Matrix::permuteRowsIP(const Ionflux::GeoUtils::Vector& p)
{
	unsigned int numRows = getNumRows();
	unsigned int numCols = getNumCols();
	unsigned int numP = p.getNumElements();
	if (numP < numRows)
	{
	    std::ostringstream status;
	    status << "Not enough elements in permutation vector "
	        "(numElements = " << numP << ").";
	    throw GeoUtilsError(getErrorString(status.str(), 
	        "permuteRowsIP"));
	}
	Matrix* m0 = copy();
	addLocalRef(m0);
	for (unsigned int i = 0; i < numRows; i++)
	    for (unsigned int k = 0; k < numCols; k++)
	    {
	        unsigned int i0 = i * numCols + k;
	        unsigned int i1 = p[i] * numCols + k;
	        elements[i0] = m0->elements[i1];
	    }
	removeLocalRef(m0);
}

void Matrix::permuteColsIP(const Ionflux::GeoUtils::Vector& p)
{
	unsigned int numRows = getNumRows();
	unsigned int numCols = getNumCols();
	unsigned int numP = p.getNumElements();
	if (numP < numCols)
	{
	    std::ostringstream status;
	    status << "Not enough elements in permutation vector "
	        "(numElements = " << numP << ").";
	    throw GeoUtilsError(getErrorString(status.str(), 
	        "permuteColsIP"));
	}
	Matrix* m0 = copy();
	addLocalRef(m0);
	for (unsigned int i = 0; i < numRows; i++)
	    for (unsigned int k = 0; k < numCols; k++)
	    {
	        unsigned int i0 = i * numCols + k;
	        unsigned int i1 = i * numCols + p[k];
	        elements[i0] = m0->elements[i1];
	    }
	removeLocalRef(m0);
}

std::string Matrix::getValueString() const
{
	std::ostringstream status;
	unsigned int numRows = getNumRows();
	unsigned int numCols = getNumCols();
	bool e0 = true;
	bool e1 = true;
	for (unsigned int i = 0; i < numRows; i++)
	{
	    if (!e0)
	        status << "; ";
	    else
	        e0 = false;
	    status << "(";
	    e1 = true;
	    for (unsigned int k = 0; k < numCols; k++)
	    {
	        if (!e1)
	            status << ", ";
	        else
	            e1 = false;
	        status << elements[i * numCols + k];
	    }
	    status << ")";
	}
	return status.str();
}

unsigned int Matrix::getNumElements() const
{
	// TODO: Implementation.
	return NUM_ELEMENTS;
}

unsigned int Matrix::getNumRows() const
{
	// TODO: Implementation.
	return NUM_ROWS;
}

unsigned int Matrix::getNumCols() const
{
	// TODO: Implementation.
	return NUM_COLS;
}

Ionflux::GeoUtils::Matrix& Matrix::operator=(const 
Ionflux::GeoUtils::Matrix& other)
{
    if (this == &other)
        return *this;
    Vector::operator=(other);
	return *this;
}

Ionflux::GeoUtils::Matrix* Matrix::copy() const
{
    Matrix* newMatrix = create();
    *newMatrix = *this;
    return newMatrix;
}

Ionflux::GeoUtils::Matrix* Matrix::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Matrix*>(other);
}

Ionflux::GeoUtils::Matrix* Matrix::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Matrix* newObject = new Matrix();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

std::string Matrix::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Matrix::getXMLAttributeData() const
{
	std::string a0(Ionflux::GeoUtils::Vector::getXMLAttributeData());
	std::ostringstream d0;
	if (a0.size() > 0)
	    d0 << a0;
	return d0.str();
}

void Matrix::getXMLChildData(std::string& target, unsigned int indentLevel)
const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::GeoUtils::Vector::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void Matrix::loadFromXMLFile(const std::string& fileName)
{
	std::string data;
	Ionflux::ObjectBase::readFile(fileName, data);
	/* <---- DEBUG ----- //
	std::cerr << "[Matrix::loadFromXMLFile] data = " << data 
	    << std::endl;
	// <---- DEBUG ----- */
	Ionflux::GeoUtils::XMLUtils::getMatrix(data, *this);
}

}

}

/** \file Matrix.cpp
 * \brief Matrix implementation.
 */
