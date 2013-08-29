/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix3.cpp                     Matrix (3x3) (implementation).
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

#include "geoutils/Matrix3.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/gslutils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

Matrix3ClassInfo::Matrix3ClassInfo()
{
	name = "Matrix3";
	desc = "Matrix (3x3)";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

Matrix3ClassInfo::~Matrix3ClassInfo()
{
}

// public member constants
const Ionflux::GeoUtils::Matrix3 Matrix3::ZERO = Ionflux::GeoUtils::Matrix3(0., 0., 0., 0., 0., 0., 0., 0., 0.);
const Ionflux::GeoUtils::Matrix3 Matrix3::UNIT = Ionflux::GeoUtils::Matrix3(1., 0., 0., 0., 1., 0., 0., 0., 1.);

// run-time type information instance constants
const Matrix3ClassInfo Matrix3::matrix3ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Matrix3::CLASS_INFO = &Matrix3::matrix3ClassInfo;

Matrix3::Matrix3()
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[9];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	*this = ZERO;
}

Matrix3::Matrix3(const Ionflux::GeoUtils::Matrix3& other)
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[9];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	*this = other;
}

Matrix3::Matrix3(double initX00, double initX01, double initX02, double 
initX10, double initX11, double initX12, double initX20, double initX21, 
double initX22)
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[9];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	elements[0] = initX00;
	elements[1] = initX01;
	elements[2] = initX02;
	elements[3] = initX10;
	elements[4] = initX11;
	elements[5] = initX12;
	elements[6] = initX20;
	elements[7] = initX21;
	elements[8] = initX22;
}

Matrix3::Matrix3(const Ionflux::ObjectBase::DoubleVector& initElements)
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	elements = new double[9];
	if (elements == 0)
	    throw GeoUtilsError("Could not allocate object.");
	setElements(initElements);
}

Matrix3::~Matrix3()
{
	delete[] elements;
}

void Matrix3::setElements(const Ionflux::ObjectBase::DoubleVector& 
newElements)
{
	unsigned int i = 0;
	while ((i < 9) && (i < newElements.size()))
	{
	    elements[i] = newElements[i];
	    i++;
	}
}

void Matrix3::getElements(Ionflux::ObjectBase::DoubleVector& target) const
{
	target.clear();
	for (unsigned int i = 0; i < 9; i++)
	    target.push_back(elements[i]);
}

double Matrix3::getElement(int row, int column) const
{
	if ((row < 0) || (row > 2))
	{
	    ostringstream message;
	    message << "Row index out of range: " << row;
	    throw GeoUtilsError(message.str());
	}
	if ((column < 0) || (column > 2))
	{
	    ostringstream message;
	    message << "Column index out of range: " << column;
	    throw GeoUtilsError(message.str());
	}
	return elements[3 * row + column];;
}

void Matrix3::setElement(int row, int column, double value)
{
	if ((row < 0) || (row > 2))
	{
	    ostringstream message;
	    message << "Row index out of range: " << row;
	    throw GeoUtilsError(message.str());
	}
	if ((column < 0) || (column > 2))
	{
	    ostringstream message;
	    message << "Column index out of range: " << column;
	    throw GeoUtilsError(message.str());
	}
	elements[3 * row + column] = value;
}

bool Matrix3::eq(const Ionflux::GeoUtils::Matrix3& other, double t)
{
	for (unsigned int i = 0; i < 9; i++)
	    if (!Ionflux::GeoUtils::eq(elements[i], other.elements[i], t))
	        return false;
	return true;
}

Ionflux::GeoUtils::Matrix3 Matrix3::transpose() const
{
	// TODO: Implementation.
	return Matrix3(elements[0], elements[3], elements[6], 
    elements[1], elements[4], elements[7], 
    elements[2], elements[5], elements[8]);
}

Ionflux::GeoUtils::Matrix3 Matrix3::permuteColumns(int px, int py, int pz) 
const
{
	// TODO: Implementation.
	return Matrix3(elements[px], elements[py], elements[pz], 
    elements[3 + px], elements[3 + py], elements[3 + pz], 
    elements[6 + px], elements[6 + py], elements[6 + pz]);
}

Ionflux::GeoUtils::Matrix3 Matrix3::permuteColumns(const 
Ionflux::ObjectBase::IntVector& p) const
{
	if (p.size() < 3)
	    throw GeoUtilsError("Not enough elements in permutation vector.");
	return permuteColumns(p[0], p[1], p[2]);
}

Ionflux::GeoUtils::Vector3 Matrix3::solve(const Ionflux::GeoUtils::Vector3&
v) const
{
	double x11 = elements[0];
	double x12 = elements[1];
	double x13 = elements[2];
	double x21 = elements[3];
	double x22 = elements[4];
	double x23 = elements[5];
	double x31 = elements[6];
	double x32 = elements[7];
	double x33 = elements[8];
	double a = v.getElement(0);
	double b = v.getElement(1);
	double c = v.getElement(2);
	Vector3 result;
	if (x11 != 0.0)
	{
	    double y11 = (x22 * x11 - x12 * x21) / x11;
	    double y12 = (x23 * x11 - x13 * x21) / x11;
	    double y21 = (x32 * x11 - x12 * x31) / x11;
	    double y22 = (x33 * x11 - x13 * x31) / x11;
	    double d = (b * x11 - a * x21) / x11;
	    double e = (c * x11 - a * x31) / x11;
	    Vector2 r0 = Matrix2(y11, y12, y21, y22).solve(Vector2(d, e));
	    double x = (a - r0[0] * x12 - r0[1] * x13) / x11;
	    result.setElement(0, x);
	    result.setElement(1, r0.getElement(0));
	    result.setElement(2, r0.getElement(1));
	} else
	if (x12 != 0.0)
	    result = permuteColumns(1, 0, 2).solve(v).permute(1, 0, 2);
	else
	if (x13 != 0.0)
	    result = permuteColumns(2, 1, 0).solve(v).permute(2, 1, 0);
	else
	    throw GeoUtilsError("Cannot solve 3x3 matrix equation.");
	return result;
}

Ionflux::GeoUtils::Matrix3 Matrix3::invert() const
{
	Vector3 x = solve(Vector3::E_X);
	Vector3 y = solve(Vector3::E_Y);
	Vector3 z = solve(Vector3::E_Z);
	Matrix3 result;
	result.setC0(x);
	result.setC1(y);
	result.setC2(z);
	return result;
}

bool Matrix3::operator==(const Ionflux::GeoUtils::Matrix3& other) const
{
	for (unsigned int i = 0; i < 9; i++)
	    if (elements[i] != other.elements[i])
	        return false;
	return true;
}

bool Matrix3::operator!=(const Ionflux::GeoUtils::Matrix3& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

Ionflux::GeoUtils::Vector3 Matrix3::operator[](int index) const
{
	if ((index < 0) || (index > 2))
	{
	    ostringstream message;
	    message << "Index out of range: " << index;
	    throw GeoUtilsError(message.str());
	}
	return Vector3(elements[3 * index], elements[3 * index + 1], 
    elements[3 * index + 2]);
}

Ionflux::GeoUtils::Matrix3 Matrix3::operator*(const 
Ionflux::GeoUtils::Matrix3& other) const
{
	Matrix3 result;
	for (unsigned int i = 0; i < 3; i++)
	    for (unsigned int j = 0; j < 3; j++)
	    {
	        double s = 0.0;
	        for (unsigned int k = 0; k < 3; k++)
	            s += elements[3 * i + k] * other.elements[3 * k + j];
	        result.elements[3 * i + j] = s;
	    }
	return result;
}

Ionflux::GeoUtils::Vector3 Matrix3::operator*(const 
Ionflux::GeoUtils::Vector3& v) const
{
	double result[3];
	for (unsigned int i = 0; i < 3; i++)
	{
	    double s = 0.0;
	    for (unsigned int k = 0; k < 3; k++)
	        s += elements[3 * i + k] * v.getElement(k);
	    result[i] = s;
	}
	return Vector3(result[0], result[1], result[2]);
}

Ionflux::GeoUtils::Matrix3 Matrix3::operator*(double c) const
{
	Matrix3 result;
	for (unsigned int i = 0; i < 9; i++)
	    result.elements[i] = elements[i] * c;
	return result;
}

Ionflux::GeoUtils::Matrix3 Matrix3::operator/(double c) const
{
	Matrix3 result;
	for (unsigned int i = 0; i < 9; i++)
	    result.elements[i] = elements[i] / c;
	return result;
}

void Matrix3::svd(Ionflux::GeoUtils::Matrix3& u, 
Ionflux::GeoUtils::Vector3& s, Ionflux::GeoUtils::Matrix3& v) const
{
	Ionflux::GeoUtils::svd(*this, u, s, v);
}

std::string Matrix3::getString() const
{
	ostringstream state;
	state << getClassName() << "[[" << elements[0] << ", " 
	    << elements[1] << ", " << elements[2] << "], [" 
	    << elements[3] << ", " << elements[4] << ", " 
	    << elements[5] << "], [" << elements[6] << ", " 
	    << elements[7] << ", " << elements[8] << "]]";
	return state.str();
}

Ionflux::GeoUtils::Matrix3 Matrix3::scale(double sx, double sy, double sz)
{
	// TODO: Implementation.
	return Matrix3(sx, 0., 0., 0., sy, 0., 0., 0., sz);
}

Ionflux::GeoUtils::Matrix3 Matrix3::translate(double tx, double ty)
{
	// TODO: Implementation.
	return Matrix3(1., 0., tx, 0., 1., ty, 0., 0., 1.);
}

Ionflux::GeoUtils::Matrix3 Matrix3::rotate(double phi, 
Ionflux::GeoUtils::AxisID axis)
{
	if (axis == AXIS_X)
	    return Matrix3(1., 0., 0., 
	        0., ::cos(phi), -::sin(phi), 
	        0., ::sin(phi), ::cos(phi));
	else
	if (axis == AXIS_Y)
	    return Matrix3(::cos(phi), 0., ::sin(phi), 
	        0., 1., 0., 
	        -::sin(phi), 0., ::cos(phi));
	else
	if (axis == AXIS_Z)
	    return Matrix3(::cos(phi), -::sin(phi), 0., 
	        ::sin(phi), ::cos(phi), 0., 
	        0., 0., 1.);
	else
	{
	    ostringstream status;
	    status << "Invalid axis: " << axis;
	    throw GeoUtilsError(status.str());
	}
	return ZERO;
}

void Matrix3::setR0(const Ionflux::GeoUtils::Vector3& newR0)
{
	elements[0] = newR0.getX0();
	elements[1] = newR0.getX1();
	elements[2] = newR0.getX2();
}

Ionflux::GeoUtils::Vector3 Matrix3::getR0() const
{
	return Vector3(elements[0], elements[1], elements[2]);
}

void Matrix3::setR1(const Ionflux::GeoUtils::Vector3& newR1)
{
	elements[3] = newR1.getX0();
	elements[4] = newR1.getX1();
	elements[5] = newR1.getX2();
}

Ionflux::GeoUtils::Vector3 Matrix3::getR1() const
{
	return Vector3(elements[3], elements[4], elements[5]);
}

void Matrix3::setR2(const Ionflux::GeoUtils::Vector3& newR2)
{
	elements[6] = newR2.getX0();
	elements[7] = newR2.getX1();
	elements[8] = newR2.getX2();
}

Ionflux::GeoUtils::Vector3 Matrix3::getR2() const
{
	return Vector3(elements[6], elements[7], elements[8]);
}

void Matrix3::setC0(const Ionflux::GeoUtils::Vector3& newC0)
{
	elements[0] = newC0.getX0();
	elements[3] = newC0.getX1();
	elements[6] = newC0.getX2();
}

Ionflux::GeoUtils::Vector3 Matrix3::getC0() const
{
	return Vector3(elements[0], elements[3], elements[6]);
}

void Matrix3::setC1(const Ionflux::GeoUtils::Vector3& newC1)
{
	elements[1] = newC1.getX0();
	elements[4] = newC1.getX1();
	elements[7] = newC1.getX2();
}

Ionflux::GeoUtils::Vector3 Matrix3::getC1() const
{
	return Vector3(elements[1], elements[4], elements[7]);
}

void Matrix3::setC2(const Ionflux::GeoUtils::Vector3& newC2)
{
	elements[2] = newC2.getX0();
	elements[5] = newC2.getX1();
	elements[8] = newC2.getX2();
}

Ionflux::GeoUtils::Vector3 Matrix3::getC2() const
{
	return Vector3(elements[2], elements[5], elements[8]);
}

Ionflux::GeoUtils::Matrix3& Matrix3::operator=(const 
Ionflux::GeoUtils::Matrix3& other)
{
    if ((elements == 0) || (other.elements == 0))
        return *this;
    for (unsigned int i = 0; i < 9; i++)
        elements[i] = other.elements[i];
    return *this;
	return *this;
}

Ionflux::GeoUtils::Matrix3* Matrix3::copy() const
{
    Matrix3* newMatrix3 = 
        new Matrix3();
    *newMatrix3 = *this;
    return newMatrix3;
}

Ionflux::GeoUtils::Matrix3 operator*(double c, const 
Ionflux::GeoUtils::Matrix3& m)
{
	// TODO: Implementation.
	return m * c;
}

}

}

/** \file Matrix3.cpp
 * \brief Matrix (3x3) implementation.
 */
