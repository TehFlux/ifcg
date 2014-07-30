/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix4.cpp                     Matrix (4x4) (implementation).
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

#include "geoutils/Matrix4.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/Matrix4XMLFactory.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

Matrix4ClassInfo::Matrix4ClassInfo()
{
	name = "Matrix4";
	desc = "Matrix (4x4)";
}

Matrix4ClassInfo::~Matrix4ClassInfo()
{
}

// public member constants
const unsigned int Matrix4::NUM_ELEMENTS = 16;
const unsigned int Matrix4::NUM_ROWS = 4;
const unsigned int Matrix4::NUM_COLS = 4;
const Ionflux::GeoUtils::Matrix4 Matrix4::ZERO = Ionflux::GeoUtils::Matrix4(0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.);
const Ionflux::GeoUtils::Matrix4 Matrix4::UNIT = Ionflux::GeoUtils::Matrix4(1., 0., 0., 0., 0., 1., 0., 0., 0., 0., 1., 0., 0., 0., 0., 1.);

// run-time type information instance constants
const Matrix4ClassInfo Matrix4::matrix4ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Matrix4::CLASS_INFO = &Matrix4::matrix4ClassInfo;

const std::string Matrix4::XML_ELEMENT_NAME = "m4";

Matrix4::Matrix4()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	zero();
}

Matrix4::Matrix4(const Ionflux::GeoUtils::Matrix4& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Matrix4::Matrix4(double initX00, double initX01, double initX02, double 
initX03, double initX10, double initX11, double initX12, double initX13, 
double initX20, double initX21, double initX22, double initX23, double 
initX30, double initX31, double initX32, double initX33)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	elements[0] = initX00;
	elements[1] = initX01;
	elements[2] = initX02;
	elements[3] = initX03;
	elements[4] = initX10;
	elements[5] = initX11;
	elements[6] = initX12;
	elements[7] = initX13;
	elements[8] = initX20;
	elements[9] = initX21;
	elements[10] = initX22;
	elements[11] = initX23;
	elements[12] = initX30;
	elements[13] = initX31;
	elements[14] = initX32;
	elements[15] = initX33;
}

Matrix4::Matrix4(const Ionflux::ObjectBase::DoubleVector& initElements0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	Vector::setElements(initElements0);
}

Matrix4::Matrix4(const Ionflux::GeoUtils::Matrix& initElements0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	setElements(initElements0);
}

Matrix4::Matrix4(const Ionflux::GeoUtils::Matrix3& initElements0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initElements();
	setM3x3(initElements0);
}

Matrix4::~Matrix4()
{
	// TODO: Nothing ATM. ;-)
}

void Matrix4::setElements(const Ionflux::GeoUtils::Matrix& other, unsigned 
int sourceRowOffset, unsigned int sourceColOffset, unsigned int 
targetRowOffset, unsigned int targetColOffset)
{
	Matrix::setElements(other);
}

void Matrix4::setM3x3(const Ionflux::GeoUtils::Matrix3& newElements, double
newX33, double newX03, double newX13, double newX23, double newX30, double 
newX31, double newX32)
{
	Matrix::setElements(newElements);
	elements[3] = newX03;
	elements[7] = newX13;
	elements[11] = newX23;
	elements[12] = newX30;
	elements[13] = newX31;
	elements[14] = newX32;
	elements[15] = newX33;
}

Ionflux::GeoUtils::Matrix4 Matrix4::transpose() const
{
	// TODO: Implementation.
	return Matrix4(elements[0], elements[4], elements[8], elements[12], 
    elements[1], elements[5], elements[9], elements[13], 
    elements[2], elements[6], elements[10], elements[14], 
    elements[3], elements[7], elements[11], elements[15]);
}

Ionflux::GeoUtils::Matrix4 Matrix4::permuteColumns(int px, int py, int pz, 
int pw) const
{
	// TODO: Implementation.
	return Matrix4(elements[px], elements[py], elements[pz], elements[pw],
    elements[4 + px], elements[4 + py], elements[4 + pz], elements[4 + pw], 
    elements[8 + px], elements[8 + py], elements[8 + pz], elements[8 + pw], 
    elements[12 + px], elements[12 + py], elements[12 + pz], elements[12 + pw]);
}

Ionflux::GeoUtils::Matrix4 Matrix4::permuteColumns(const 
Ionflux::ObjectBase::IntVector& p) const
{
	if (p.size() < 4)
	    throw GeoUtilsError("Not enough elements in permutation vector.");
	return permuteColumns(p[0], p[1], p[2], p[4]);
}

Ionflux::GeoUtils::Matrix4 Matrix4::permuteRows(int px, int py, int pz, int
pw) const
{
	// TODO: Implementation.
	return Matrix4(elements[4 * px], elements[4 * px + 1], elements[4 * px + 2], elements[px + 3],
    elements[4 * py], elements[4 * py + 1], elements[4 * py + 2], elements[4 * py + 3], 
    elements[4 * pz], elements[4 * pz + 1], elements[4 * pz + 2], elements[4 * pz + 3], 
    elements[4 * pw], elements[4 * pw + 1], elements[4 * pw + 2], elements[4 * pw + 3]);
}

Ionflux::GeoUtils::Matrix4 Matrix4::permuteRows(const 
Ionflux::ObjectBase::IntVector& p) const
{
	if (p.size() < 4)
	    throw GeoUtilsError("Not enough elements in permutation vector.");
	return permuteRows(p[0], p[1], p[2], p[4]);
}

Ionflux::GeoUtils::Vector4 Matrix4::solve(const Ionflux::GeoUtils::Vector4&
v) const
{
	double x11 = elements[0];
	double x12 = elements[1];
	double x13 = elements[2];
	double x14 = elements[3];
	double x21 = elements[4];
	double x22 = elements[5];
	double x23 = elements[6];
	double x24 = elements[7];
	double x31 = elements[8];
	double x32 = elements[9];
	double x33 = elements[10];
	double x34 = elements[11];
	double x41 = elements[12];
	double x42 = elements[13];
	double x43 = elements[14];
	double x44 = elements[15];
	double a = v.getElement(0);
	double b = v.getElement(1);
	double c = v.getElement(2);
	double d = v.getElement(3);
	Vector4 result;
	if (x11 != 0.0)
	{
	    double y11 = (x22 * x11 - x12 * x21) / x11;
	    double y12 = (x23 * x11 - x13 * x21) / x11;
	    double y13 = (x24 * x11 - x14 * x21) / x11;
	    double y21 = (x32 * x11 - x12 * x31) / x11;
	    double y22 = (x33 * x11 - x13 * x31) / x11;
	    double y23 = (x34 * x11 - x14 * x31) / x11;
	    double y31 = (x42 * x11 - x12 * x41) / x11;
	    double y32 = (x43 * x11 - x13 * x41) / x11;
	    double y33 = (x44 * x11 - x14 * x41) / x11;
	    double e = (b * x11 - a * x21) / x11;
	    double f = (c * x11 - a * x31) / x11;
	    double g = (d * x11 - a * x41) / x11;
	    Vector3 r0 = Matrix3(y11, y12, y13, y21, y22, y23, y31, y32, 
	        y33).solve(Vector3(e, f, g));
	    double x = (a - r0[0] * x12 - r0[1] * x13 - r0[2] * x14) / x11;
	    result.setElement(0, x);
	    result.setElement(1, r0.getElement(0));
	    result.setElement(2, r0.getElement(1));
	    result.setElement(3, r0.getElement(2));
	} else
	if (x12 != 0.0)
	    result = permuteColumns(1, 0, 2, 3).solve(v).permute(1, 0, 2, 3);
	else
	if (x13 != 0.0)
	    result = permuteColumns(2, 1, 0, 3).solve(v).permute(2, 1, 0, 3);
	else
	if (x14 != 0.0)
	    result = permuteColumns(3, 1, 2, 0).solve(v).permute(3, 1, 2, 0);
	else
	{
	    std::ostringstream status;
	    status << "Cannot solve 4x4 matrix equation (M = ["
	        << getValueString() << "], v = (" << v.getValueString() 
	        << ")).";
	    throw GeoUtilsError(getErrorString(status.str(), "solve"));
	}
	return result;
}

Ionflux::GeoUtils::Matrix4 Matrix4::invert() const
{
	Vector4 x = solve(Vector4::E_X);
	Vector4 y = solve(Vector4::E_Y);
	Vector4 z = solve(Vector4::E_Z);
	Vector4 w = solve(Vector4::E_W);
	Matrix4 result;
	result.setC0(x);
	result.setC1(y);
	result.setC2(z);
	result.setC3(w);
	return result;
}

Ionflux::GeoUtils::Matrix4& Matrix4::multiplyLeft(const 
Ionflux::GeoUtils::Matrix4& other)
{
	*this = other * (*this);
	return *this;
}

Ionflux::GeoUtils::Matrix4& Matrix4::multiplyRight(const 
Ionflux::GeoUtils::Matrix4& other)
{
	*this = (*this) * other;
	return *this;
}

Ionflux::GeoUtils::Matrix4 Matrix4::operator*(const 
Ionflux::GeoUtils::Matrix4& other) const
{
	Matrix4 result;
	for (unsigned int i = 0; i < 4; i++)
	{
	    for (unsigned int j = 0; j < 4; j++)
	    {
	        double s = 0.0;
	        for (unsigned int k = 0; k < 4; k++)
	            s += elements[4 * i + k] * other.elements[4 * k + j];
	        result.elements[4 * i + j] = s;
	    }
	}
	return result;
}

Ionflux::GeoUtils::Vector4 Matrix4::operator*(const 
Ionflux::GeoUtils::Vector4& v) const
{
	double result[4];
	for (unsigned int i = 0; i < 4; i++)
	{
	    double s = 0.0;
	    for (unsigned int k = 0; k < 4; k++)
	        s += elements[4 * i + k] * v.getElement(k);
	    result[i] = s;
	}
	return Vector4(result[0], result[1], result[2], result[3]);
}

Ionflux::GeoUtils::Matrix4 Matrix4::operator*(double c) const
{
	Matrix4 result(*this);
	result.multiplyIP(c);
	return result;
}

Ionflux::GeoUtils::Matrix4 Matrix4::operator/(double c) const
{
	Matrix4 result(*this);
	result.divideIP(c);
	return result;
}

Ionflux::GeoUtils::Matrix3 Matrix4::getM3x3() const
{
	// TODO: Implementation.
	return Matrix3(elements[0], elements[1], elements[2], elements[4], elements[5], elements[6], elements[8], elements[9], elements[10]);
}

unsigned int Matrix4::getNumElements() const
{
	// TODO: Implementation.
	return NUM_ELEMENTS;
}

unsigned int Matrix4::getNumRows() const
{
	// TODO: Implementation.
	return NUM_ROWS;
}

unsigned int Matrix4::getNumCols() const
{
	// TODO: Implementation.
	return NUM_COLS;
}

Ionflux::GeoUtils::Matrix4 Matrix4::scale(double sx, double sy, double sz, 
double sw)
{
	// TODO: Implementation.
	return Matrix4(sx, 0., 0., 0., 0., sy, 0., 0., 0., 0., sz, 0., 0., 0., 0., sw);
}

Ionflux::GeoUtils::Matrix4 Matrix4::scale(const Ionflux::GeoUtils::Vector3&
s, double sw)
{
	// TODO: Implementation.
	return Matrix4(s.getX0(), 0., 0., 0., 0., s.getX1(), 0., 0., 0., 0., s.getX2(), 0., 0., 0., 0., sw);
}

Ionflux::GeoUtils::Matrix4 Matrix4::scale(const Ionflux::GeoUtils::Vector4&
s)
{
	// TODO: Implementation.
	return Matrix4(s.getX0(), 0., 0., 0., 0., s.getX1(), 0., 0., 0., 0., s.getX2(), 0., 0., 0., 0., s.getX3());
}

Ionflux::GeoUtils::Matrix4 Matrix4::translate(double tx, double ty, double 
tz)
{
	// TODO: Implementation.
	return Matrix4(1., 0., 0., tx, 0., 1., 0., ty, 0., 0., 1., tz, 0., 0., 0., 1.);
}

Ionflux::GeoUtils::Matrix4 Matrix4::translate(const 
Ionflux::GeoUtils::Vector3& t)
{
	// TODO: Implementation.
	return Matrix4(1., 0., 0., t[0], 0., 1., 0., t[1], 0., 0., 1., t[2], 0., 0., 0., 1.);
}

Ionflux::GeoUtils::Matrix4 Matrix4::rotate(double phi, 
Ionflux::GeoUtils::AxisID axis)
{
	if (axis == AXIS_X)
	    return Matrix4(1., 0., 0., 0., 
	        0., ::cos(phi), -::sin(phi), 0., 
	        0., ::sin(phi), ::cos(phi), 0., 
	        0., 0., 0., 1.);
	else
	if (axis == AXIS_Y)
	    return Matrix4(::cos(phi), 0., ::sin(phi), 0., 
	        0., 1., 0., 0., 
	        -::sin(phi), 0., ::cos(phi), 0., 
	        0., 0., 0., 1.);
	else
	if (axis == AXIS_Z)
	    return Matrix4(::cos(phi), -::sin(phi), 0., 0., 
	        ::sin(phi), ::cos(phi), 0., 0., 
	        0., 0., 1., 0., 
	        0., 0., 0., 1.);
	else
	{
	    ostringstream status;
	    status << "Invalid axis: " << axis;
	    throw GeoUtilsError(status.str());
	}
	return ZERO;
}

Ionflux::GeoUtils::Matrix4 Matrix4::swapAxes(Ionflux::GeoUtils::AxisID x, 
Ionflux::GeoUtils::AxisID y, Ionflux::GeoUtils::AxisID z, 
Ionflux::GeoUtils::AxisID w)
{
	// TODO: Implementation.
	return UNIT.permuteColumns(x, y, z, w);
}

Ionflux::GeoUtils::Matrix4 Matrix4::perspective(double d, 
Ionflux::GeoUtils::AxisID depthAxis)
{
	Matrix4 result = UNIT;
	result.setElement(3, depthAxis, 1. / d);
	result.setElement(3, 3, 0.);
	return result;
}

Ionflux::GeoUtils::Matrix4 Matrix4::imageTransform(double screenWidth, 
double screenHeight, double imageWidth, double imageHeight, 
Ionflux::GeoUtils::AxisID upAxis, Ionflux::GeoUtils::AxisID depthAxis, 
Ionflux::GeoUtils::AxisID horizonAxis)
{
	double scale[3];
	scale[depthAxis] = 1.;
	scale[horizonAxis] = imageWidth / screenWidth;
	scale[upAxis] = -imageHeight / screenHeight;
	Matrix4 imageScale = Matrix4::scale(scale[0], scale[1], scale[2]);
	double tr[3];
	tr[depthAxis] = 0.;
	tr[horizonAxis] = 0.5 * imageWidth;
	tr[upAxis] = 0.5 * imageHeight;
	Matrix4 imageTranslate = Matrix4::translate(tr[0], tr[1], tr[2]);
	Matrix4 swapAxes;
	swapAxes.setElement(0, horizonAxis, 1.);
	swapAxes.setElement(1, upAxis, 1.);
	swapAxes.setElement(2, depthAxis, 1.);
	swapAxes.setElement(3, 3., 1.);
	return swapAxes * imageTranslate * imageScale;
}

void Matrix4::setR0(const Ionflux::GeoUtils::Vector4& newR0)
{
	elements[0] = newR0.getX0();
	elements[1] = newR0.getX1();
	elements[2] = newR0.getX2();
	elements[3] = newR0.getX3();
}

Ionflux::GeoUtils::Vector4 Matrix4::getR0() const
{
	return Vector4(elements[0], elements[1], elements[2], elements[3]);
}

void Matrix4::setR1(const Ionflux::GeoUtils::Vector4& newR1)
{
	elements[4] = newR1.getX0();
	elements[5] = newR1.getX1();
	elements[6] = newR1.getX2();
	elements[7] = newR1.getX3();
}

Ionflux::GeoUtils::Vector4 Matrix4::getR1() const
{
	return Vector4(elements[4], elements[5], elements[6], elements[7]);
}

void Matrix4::setR2(const Ionflux::GeoUtils::Vector4& newR2)
{
	elements[8] = newR2.getX0();
	elements[9] = newR2.getX1();
	elements[10] = newR2.getX2();
	elements[11] = newR2.getX3();
}

Ionflux::GeoUtils::Vector4 Matrix4::getR2() const
{
	return Vector4(elements[8], elements[9], elements[10], elements[11]);
}

void Matrix4::setR3(const Ionflux::GeoUtils::Vector4& newR3)
{
	elements[12] = newR3.getX0();
	elements[13] = newR3.getX1();
	elements[14] = newR3.getX2();
	elements[15] = newR3.getX3();
}

Ionflux::GeoUtils::Vector4 Matrix4::getR3() const
{
	return Vector4(elements[12], elements[13], elements[14], elements[15]);
}

void Matrix4::setC0(const Ionflux::GeoUtils::Vector4& newC0)
{
	elements[0] = newC0.getX0();
	elements[4] = newC0.getX1();
	elements[8] = newC0.getX2();
	elements[12] = newC0.getX3();
}

Ionflux::GeoUtils::Vector4 Matrix4::getC0() const
{
	return Vector4(elements[0], elements[4], elements[8], elements[12]);
}

void Matrix4::setC1(const Ionflux::GeoUtils::Vector4& newC1)
{
	elements[1] = newC1.getX0();
	elements[5] = newC1.getX1();
	elements[9] = newC1.getX2();
	elements[13] = newC1.getX3();
}

Ionflux::GeoUtils::Vector4 Matrix4::getC1() const
{
	return Vector4(elements[1], elements[5], elements[9], elements[13]);
}

void Matrix4::setC2(const Ionflux::GeoUtils::Vector4& newC2)
{
	elements[2] = newC2.getX0();
	elements[6] = newC2.getX1();
	elements[10] = newC2.getX2();
	elements[14] = newC2.getX3();
}

Ionflux::GeoUtils::Vector4 Matrix4::getC2() const
{
	return Vector4(elements[2], elements[6], elements[10], elements[14]);
}

void Matrix4::setC3(const Ionflux::GeoUtils::Vector4& newC3)
{
	elements[3] = newC3.getX0();
	elements[7] = newC3.getX1();
	elements[11] = newC3.getX2();
	elements[15] = newC3.getX3();
}

Ionflux::GeoUtils::Vector4 Matrix4::getC3() const
{
	return Vector4(elements[3], elements[7], elements[11], elements[15]);
}

Ionflux::GeoUtils::Matrix4& Matrix4::operator=(const 
Ionflux::GeoUtils::Matrix4& other)
{
    if (this == &other)
        return *this;
    Vector::operator=(other);
	return *this;
}

Ionflux::GeoUtils::Matrix4* Matrix4::copy() const
{
    Matrix4* newMatrix4 = create();
    *newMatrix4 = *this;
    return newMatrix4;
}

Ionflux::GeoUtils::Matrix4* Matrix4::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Matrix4*>(other);
}

Ionflux::GeoUtils::Matrix4* Matrix4::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Matrix4* newObject = new Matrix4();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Matrix4* Matrix4::create(double initX00, double initX01,
double initX02, double initX03, double initX10, double initX11, double 
initX12, double initX13, double initX20, double initX21, double initX22, 
double initX23, double initX30, double initX31, double initX32, double 
initX33, Ionflux::ObjectBase::IFObject* parentObject)
{
    Matrix4* newObject = new Matrix4(initX00, initX01, initX02, initX03, 
    initX10, initX11, initX12, initX13, initX20, initX21, initX22, initX23,
    initX30, initX31, initX32, initX33);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Matrix4* Matrix4::create(const 
Ionflux::ObjectBase::DoubleVector& initElements0, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Matrix4* newObject = new Matrix4(initElements0);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Matrix4* Matrix4::create(const 
Ionflux::GeoUtils::Matrix& initElements0, Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Matrix4* newObject = new Matrix4(initElements0);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Matrix4* Matrix4::create(const 
Ionflux::GeoUtils::Matrix3& initElements0, Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Matrix4* newObject = new Matrix4(initElements0);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Matrix4::getMemSize() const
{
    return sizeof *this;
}

std::string Matrix4::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Matrix4::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::GeoUtils::Matrix::getXMLAttributeData();
	return d0.str();
}

void Matrix4::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::GeoUtils::Matrix::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void Matrix4::loadFromXMLFile(const std::string& fileName)
{
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, getXMLElementName());
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
Matrix4::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::Matrix4XMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::Matrix4XMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 0;
        bFac = Ionflux::GeoUtils::Matrix::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

Ionflux::GeoUtils::Matrix4 operator*(double c, const 
Ionflux::GeoUtils::Matrix4& m)
{
	// TODO: Implementation.
	return m * c;
}

}

}

/** \file Matrix4.cpp
 * \brief Matrix (4x4) implementation.
 */
