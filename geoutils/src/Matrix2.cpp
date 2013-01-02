/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
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

#include "geoutils/Matrix2.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

Matrix2ClassInfo::Matrix2ClassInfo()
{
	name = "Matrix2";
	desc = "Matrix (2x2)";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

Matrix2ClassInfo::~Matrix2ClassInfo()
{
}

// public member constants
const Ionflux::GeoUtils::Matrix2 Matrix2::ZERO = Ionflux::GeoUtils::Matrix2(0., 0., 0., 0.);
const Ionflux::GeoUtils::Matrix2 Matrix2::UNIT = Ionflux::GeoUtils::Matrix2(1., 0., 0., 1.);

// run-time type information instance constants
const Matrix2ClassInfo Matrix2::matrix2ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Matrix2::CLASS_INFO = &Matrix2::matrix2ClassInfo;

Matrix2::Matrix2()
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[4];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	*this = ZERO;
}

Matrix2::Matrix2(const Ionflux::GeoUtils::Matrix2& other)
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[4];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	*this = other;
}

Matrix2::Matrix2(double initX00, double initX01, double initX10, double 
initX11)
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[4];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	elements[0] = initX00;
	elements[1] = initX01;
	elements[2] = initX10;
	elements[3] = initX11;
}

Matrix2::Matrix2(const Ionflux::ObjectBase::DoubleVector& initElements)
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[4];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	setElements(initElements);
}

Matrix2::~Matrix2()
{
	delete[] elements;
}

void Matrix2::setElements(const Ionflux::ObjectBase::DoubleVector& 
newElements)
{
	unsigned int i = 0;
	while ((i < 4) && (i < newElements.size()))
	{
	    elements[i] = newElements[i];
	    i++;
	}
}

void Matrix2::getElements(Ionflux::ObjectBase::DoubleVector& target) const
{
	target.clear();
	for (unsigned int i = 0; i < 4; i++)
	    target.push_back(elements[i]);
}

double Matrix2::getElement(int row, int column) const
{
	if ((row < 0) || (row > 1))
	{
	    ostringstream message;
	    message << "Row index out of range: " << row;
	    throw GeoUtilsError(message.str());
	}
	if ((column < 0) || (column > 1))
	{
	    ostringstream message;
	    message << "Column index out of range: " << column;
	    throw GeoUtilsError(message.str());
	}
	return elements[2 * row + column];;
}

void Matrix2::setElement(int row, int column, double value)
{
	if ((row < 0) || (row > 1))
	{
	    ostringstream message;
	    message << "Row index out of range: " << row;
	    throw GeoUtilsError(message.str());
	}
	if ((column < 0) || (column > 1))
	{
	    ostringstream message;
	    message << "Column index out of range: " << column;
	    throw GeoUtilsError(message.str());
	}
	elements[2 * row + column] = value;
}

bool Matrix2::eq(const Ionflux::GeoUtils::Matrix2& other, double t)
{
	for (unsigned int i = 0; i < 4; i++)
	    if (!Ionflux::GeoUtils::eq(elements[i], other.elements[i], t))
	        return false;
	return true;
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
	    throw GeoUtilsError("Cannot solve 2x2 matrix equation.");
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

bool Matrix2::operator==(const Ionflux::GeoUtils::Matrix2& other) const
{
	for (unsigned int i = 0; i < 4; i++)
	    if (elements[i] != other.elements[i])
	        return false;
	return true;
}

bool Matrix2::operator!=(const Ionflux::GeoUtils::Matrix2& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

Ionflux::GeoUtils::Vector2 Matrix2::operator[](int index) const
{
	if ((index < 0) || (index > 1))
	{
	    ostringstream message;
	    message << "Index out of range: " << index;
	    throw GeoUtilsError(message.str());
	}
	return Vector2(elements[2 * index], elements[2 * index + 1]);
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
	Matrix2 result;
	for (unsigned int i = 0; i < 4; i++)
	    result.elements[i] = elements[i] * c;
	return result;
}

Ionflux::GeoUtils::Matrix2 Matrix2::operator/(double c) const
{
	Matrix2 result;
	for (unsigned int i = 0; i < 4; i++)
	    result.elements[i] = elements[i] / c;
	return result;
}

std::string Matrix2::getString() const
{
	ostringstream state;
	state << getClassName() << "[[" << elements[0] << ", " 
	    << elements[1] << "], [" << elements[2] << ", " 
	    << elements[3] << "]]";
	return state.str();
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
    if ((elements == 0) || (other.elements == 0))
        return *this;
    for (unsigned int i = 0; i < 4; i++)
        elements[i] = other.elements[i];
    return *this;
	return *this;
}

Ionflux::GeoUtils::Matrix2* Matrix2::copy() const
{
    Matrix2* newMatrix2 = 
        new Matrix2();
    *newMatrix2 = *this;
    return newMatrix2;
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
