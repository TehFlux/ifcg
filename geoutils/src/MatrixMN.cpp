/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * MatrixMN.cpp                    Matrix (NxM) (implementation).
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

#include "geoutils/MatrixMN.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/VectorN.hpp"
#include "geoutils/gslutils.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/MatrixMNXMLFactory.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

MatrixMNClassInfo::MatrixMNClassInfo()
{
	name = "MatrixMN";
	desc = "Matrix (NxM)";
	baseClassInfo.push_back(Ionflux::GeoUtils::Matrix::CLASS_INFO);
}

MatrixMNClassInfo::~MatrixMNClassInfo()
{
}

// run-time type information instance constants
const MatrixMNClassInfo MatrixMN::matrixMNClassInfo;
const Ionflux::ObjectBase::IFClassInfo* MatrixMN::CLASS_INFO = &MatrixMN::matrixMNClassInfo;

const std::string MatrixMN::XML_ELEMENT_NAME = "mmn";

MatrixMN::MatrixMN()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

MatrixMN::MatrixMN(const Ionflux::GeoUtils::MatrixMN& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

MatrixMN::MatrixMN(unsigned int initNumRows, unsigned int initNumCols)
: numRows(initNumRows), numCols(initNumCols)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	zero();
}

MatrixMN::MatrixMN(unsigned int initNumCols, unsigned int initNumRows, 
double x0, double x1, double x2, double x3, double x4, double x5, double 
x6, double x7, double x8, double x9, double x10, double x11, double x12)
: numRows(initNumRows), numCols(initNumCols)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	zero();
	setElements(x0, x1, x2, x3, x4, x5, x6, 
	    x7, x8, x9, x10, x11, x12);
}

MatrixMN::~MatrixMN()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::GeoUtils::MatrixMN MatrixMN::transpose() const
{
	MatrixMN result(*this);
	result.transposeIP();
	return result;
}

void MatrixMN::qrDecomp(Ionflux::GeoUtils::MatrixMN& q, 
Ionflux::GeoUtils::MatrixMN& r) const
{
	Ionflux::GeoUtils::qrDecomp(*this, q, r);
}

Ionflux::GeoUtils::VectorN MatrixMN::solve(const 
Ionflux::GeoUtils::VectorN& b) const
{
	unsigned int numRows0 = getNumRows();
	unsigned int numCols0 = getNumCols();
	Ionflux::GeoUtils::MatrixMN q(numRows0, numRows0);
	Ionflux::GeoUtils::MatrixMN r(numRows0, numCols0);
	Ionflux::GeoUtils::VectorN result(numCols0);
	qrDecomp(q, r);
	Ionflux::GeoUtils::qrSolve(q, r, b, result);
	return result;
}

Ionflux::GeoUtils::MatrixMN MatrixMN::invert() const
{
	unsigned int numRows0 = getNumRows();
	unsigned int numCols0 = getNumCols();
	if (numRows0 != numCols0)
	    throw GeoUtilsError(getErrorString(
	        "Cannot invert non-square matrix.", "invert"));
	Ionflux::GeoUtils::MatrixMN q(numRows0, numRows0);
	Ionflux::GeoUtils::MatrixMN r(numRows0, numRows0);
	qrDecomp(q, r);
	Ionflux::GeoUtils::MatrixMN result(numRows0, numRows0);
	for (unsigned int i = 0; i < numRows0; i++)
	{
	    Ionflux::GeoUtils::VectorN b(numRows0);
	    Ionflux::GeoUtils::VectorN x(numRows0);
	    b.setElement(i, 1.);
	    Ionflux::GeoUtils::qrSolve(q, r, b, x);
	    result.setCol(i, x);
	}
	return result;
}

unsigned int MatrixMN::getNumElements() const
{
	// TODO: Implementation.
	return getNumCols() * getNumRows();
}

void MatrixMN::qrSolve(const Ionflux::GeoUtils::MatrixMN& q, const 
Ionflux::GeoUtils::MatrixMN& r, const Ionflux::GeoUtils::VectorN& b, 
Ionflux::GeoUtils::VectorN& x)
{
	Ionflux::GeoUtils::qrSolve(q, r, b, x);
}

Ionflux::GeoUtils::MatrixMN MatrixMN::operator*(const 
Ionflux::GeoUtils::Matrix& other) const
{
	MatrixMN result(getNumRows(), other.getNumCols());
	other.multiply(*this, result);
	return result;
}

Ionflux::GeoUtils::VectorN MatrixMN::operator*(const 
Ionflux::GeoUtils::VectorN& v) const
{
	VectorN result(v.getNumElements());
	Matrix::transform(v, result);
	return result;
}

void MatrixMN::setNumRows(unsigned int newNumRows)
{
	numRows = newNumRows;
}

unsigned int MatrixMN::getNumRows() const
{
    return numRows;
}

void MatrixMN::setNumCols(unsigned int newNumCols)
{
	numCols = newNumCols;
}

unsigned int MatrixMN::getNumCols() const
{
    return numCols;
}

Ionflux::GeoUtils::MatrixMN& MatrixMN::operator=(const 
Ionflux::GeoUtils::MatrixMN& other)
{
    if (this == &other)
        return *this;
    numRows = other.getNumRows();
    numCols = other.getNumCols();
    Ionflux::GeoUtils::Matrix::operator=(other);
	return *this;
}

Ionflux::GeoUtils::MatrixMN* MatrixMN::copy() const
{
    MatrixMN* newMatrixMN = create();
    *newMatrixMN = *this;
    return newMatrixMN;
}

Ionflux::GeoUtils::MatrixMN* 
MatrixMN::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<MatrixMN*>(other);
}

Ionflux::GeoUtils::MatrixMN* 
MatrixMN::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    MatrixMN* newObject = new MatrixMN();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::MatrixMN* MatrixMN::create(unsigned int initNumRows, 
unsigned int initNumCols, Ionflux::ObjectBase::IFObject* parentObject)
{
    MatrixMN* newObject = new MatrixMN(initNumRows, initNumCols);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::MatrixMN* MatrixMN::create(unsigned int initNumCols, 
unsigned int initNumRows, double x0, double x1, double x2, double x3, 
double x4, double x5, double x6, double x7, double x8, double x9, double 
x10, double x11, double x12, Ionflux::ObjectBase::IFObject* parentObject)
{
    MatrixMN* newObject = new MatrixMN(initNumCols, initNumRows, x0, x1, 
    x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int MatrixMN::getMemSize() const
{
    return sizeof *this;
}

std::string MatrixMN::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string MatrixMN::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::GeoUtils::Matrix::getXMLAttributeData();
	return d0.str();
}

void MatrixMN::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::GeoUtils::Matrix::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void MatrixMN::loadFromXMLFile(const std::string& fileName)
{
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, getXMLElementName());
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
MatrixMN::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::MatrixMNXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::MatrixMNXMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 0;
        bFac = Ionflux::GeoUtils::Matrix::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file MatrixMN.cpp
 * \brief Matrix (NxM) implementation.
 */
