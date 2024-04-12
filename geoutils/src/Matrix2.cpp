/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix2.cpp                     Matrix (2x2) (implementation).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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

#include "geoutils/Matrix2.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/Matrix2XMLFactory.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

Matrix2ClassInfo::Matrix2ClassInfo()
{
	name = "Matrix2";
	desc = "Matrix (2x2)";
}

Matrix2ClassInfo::~Matrix2ClassInfo()
{
}

// public member constants
const unsigned int Matrix2::NUM_ELEMENTS = 4;
const unsigned int Matrix2::NUM_ROWS = 2;
const unsigned int Matrix2::NUM_COLS = 2;
const Ionflux::GeoUtils::Matrix2 Matrix2::ZERO = Ionflux::GeoUtils::Matrix2(0., 0., 0., 0.);
const Ionflux::GeoUtils::Matrix2 Matrix2::UNIT = Ionflux::GeoUtils::Matrix2(1., 0., 0., 1.);

// run-time type information instance constants
const Matrix2ClassInfo Matrix2::matrix2ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Matrix2::CLASS_INFO = &Matrix2::matrix2ClassInfo;

const std::string Matrix2::XML_ELEMENT_NAME = "m2";

Matrix2::Matrix2()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	zero();
}

Matrix2::Matrix2(const Ionflux::GeoUtils::Matrix2& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Matrix2::Matrix2(double initX00, double initX01, double initX10, double 
initX11)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	elements[0] = initX00;
	elements[1] = initX01;
	elements[2] = initX10;
	elements[3] = initX11;
}

Matrix2::Matrix2(const Ionflux::ObjectBase::DoubleVector& initElements0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	Vector::setElements(initElements0);
}

Matrix2::~Matrix2()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::GeoUtils::Matrix2 Matrix2::transpose() const
{
	// TODO: Implementation.
	return Matrix2(elements[0], elements[2], elements[1], elements[3]);
}

Ionflux::GeoUtils::Matrix2 Matrix2::swapColumns() const
{
	// TODO: Implementation.
	return Matrix2(elements[1], elements[0], elements[3], elements[2]);
}

Ionflux::GeoUtils::Vector2 Matrix2::solve(const Ionflux::GeoUtils::Vector2&
v) const
{
	double y11 = elements[0];
	double y12 = elements[1];
	double y21 = elements[2];
	double y22 = elements[3];
	double d = v.getElement(0);
	double e = v.getElement(1);
	Vector2 result;
	if ((y11 != 0.0)
	    && ((y22 * y11 - y12 * y21) != 0.0))
	{
	    double y = (e * y11 - d * y21) / (y22 * y11 - y12 * y21);
	    result.setElement(0, (d - y * y12) / y11);
	    result.setElement(1, y);
	} else
	if ((y12 != 0)
	    && ((y21 * y12 - y11 * y22) != 0.0))
	    result = swapColumns().solve(v).swap();
	else
	if ((y11 != 0.) && (y12 == 0.) && (y21 == 0.) 
	    && (y22 == 0.) && (e == 0))
	{
	    result.setElement(0, d / y11);
	    result.setElement(1, 0.);
	}
	return result;
}

Ionflux::GeoUtils::Matrix2 Matrix2::invert() const
{
	Vector2 x = solve(Vector2::E_X);
	Vector2 y = solve(Vector2::E_Y);
	Matrix2 result;
	result.setC0(x);
	result.setC1(y);
	return result;
}

Ionflux::GeoUtils::Matrix2 Matrix2::operator*(const 
Ionflux::GeoUtils::Matrix2& other) const
{
	Matrix2 result;
	for (unsigned int i = 0; i < 2; i++)
	    for (unsigned int j = 0; j < 2; j++)
	    {
	        double s = 0.0;
	        for (unsigned int k = 0; k < 2; k++)
	            s += elements[2 * i + k] * other.elements[2 * k + j];
	        result.elements[2 * i + j] = s;
	    }
	return result;
}

Ionflux::GeoUtils::Vector2 Matrix2::operator*(const 
Ionflux::GeoUtils::Vector2& v) const
{
	double result[2];
	for (unsigned int i = 0; i < 2; i++)
	{
	    double s = 0.0;
	    for (unsigned int k = 0; k < 2; k++)
	        s += elements[2 * i + k] * v.getElement(k);
	    result[i] = s;
	}
	return Vector2(result[0], result[1]);
}

Ionflux::GeoUtils::Matrix2 Matrix2::operator*(double c) const
{
	Matrix2 result(*this);
	result.multiplyIP(c);
	return result;
}

Ionflux::GeoUtils::Matrix2 Matrix2::operator/(double c) const
{
	Matrix2 result(*this);
	result.divideIP(c);
	return result;
}

unsigned int Matrix2::getNumElements() const
{
	// TODO: Implementation.
	return NUM_ELEMENTS;
}

unsigned int Matrix2::getNumRows() const
{
	// TODO: Implementation.
	return NUM_ROWS;
}

unsigned int Matrix2::getNumCols() const
{
	// TODO: Implementation.
	return NUM_COLS;
}

Ionflux::GeoUtils::Matrix2 Matrix2::scale(double sx, double sy)
{
	// TODO: Implementation.
	return Matrix2(sx, 0., 0., sy);
}

Ionflux::GeoUtils::Matrix2 Matrix2::rotate(double phi)
{
	// TODO: Implementation.
	return Matrix2(::cos(phi), -::sin(phi), ::sin(phi), ::cos(phi));;
}

void Matrix2::setR0(const Ionflux::GeoUtils::Vector2& newR0)
{
	elements[0] = newR0.getX0();
	elements[1] = newR0.getX1();
}

Ionflux::GeoUtils::Vector2 Matrix2::getR0() const
{
	return Vector2(elements[0], elements[1]);
}

void Matrix2::setR1(const Ionflux::GeoUtils::Vector2& newR1)
{
	elements[2] = newR1.getX0();
	elements[3] = newR1.getX1();
}

Ionflux::GeoUtils::Vector2 Matrix2::getR1() const
{
	return Vector2(elements[2], elements[3]);
}

void Matrix2::setC0(const Ionflux::GeoUtils::Vector2& newC0)
{
	elements[0] = newC0.getX0();
	elements[2] = newC0.getX1();
}

Ionflux::GeoUtils::Vector2 Matrix2::getC0() const
{
	return Vector2(elements[0], elements[2]);
}

void Matrix2::setC1(const Ionflux::GeoUtils::Vector2& newC1)
{
	elements[1] = newC1.getX0();
	elements[3] = newC1.getX1();
}

Ionflux::GeoUtils::Vector2 Matrix2::getC1() const
{
	return Vector2(elements[1], elements[3]);
}

Ionflux::GeoUtils::Matrix2& Matrix2::operator=(const 
Ionflux::GeoUtils::Matrix2& other)
{
    if (this == &other)
        return *this;
    Vector::operator=(other);
	return *this;
}

Ionflux::GeoUtils::Matrix2* Matrix2::copy() const
{
    Matrix2* newMatrix2 = create();
    *newMatrix2 = *this;
    return newMatrix2;
}

Ionflux::GeoUtils::Matrix2* Matrix2::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Matrix2*>(other);
}

Ionflux::GeoUtils::Matrix2* Matrix2::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Matrix2* newObject = new Matrix2();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Matrix2* Matrix2::create(double initX00, double initX01,
double initX10, double initX11, Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Matrix2* newObject = new Matrix2(initX00, initX01, initX10, initX11);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Matrix2* Matrix2::create(const 
Ionflux::ObjectBase::DoubleVector& initElements0, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Matrix2* newObject = new Matrix2(initElements0);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Matrix2::getMemSize() const
{
    return sizeof *this;
}

std::string Matrix2::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Matrix2::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::GeoUtils::Matrix::getXMLAttributeData();
	return d0.str();
}

void Matrix2::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::GeoUtils::Matrix::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void Matrix2::loadFromXMLFile(const std::string& fileName, const 
std::string& elementName)
{
	std::string en0(elementName);
	if (en0.size() == 0)
	    en0 = getXMLElementName();
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, en0);
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
Matrix2::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::Matrix2XMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::Matrix2XMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 0;
        bFac = Ionflux::GeoUtils::Matrix::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

Ionflux::GeoUtils::Matrix2 operator*(double c, const 
Ionflux::GeoUtils::Matrix2& m)
{
	// TODO: Implementation.
	return m * c;
}

}

}

/** \file Matrix2.cpp
 * \brief Matrix (2x2) implementation.
 */
