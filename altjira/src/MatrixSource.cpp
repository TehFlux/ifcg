/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * MatrixSource.cpp                Matrix pixel source (implementation).
 * =========================================================================
 * 
 * This file is part of Altjira - Ionflux' Image Processing Library.
 * 
 * Altjira - Ionflux' Image Processing Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
 * 
 * Altjira - Ionflux' Image Processing Library is distributed in the hope 
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Altjira - Ionflux' Image Processing Library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "altjira/MatrixSource.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "altjira/utils.hpp"
#include "altjira/imageutils.hpp"
#include "altjira/AltjiraError.hpp"
#include "altjira/Color.hpp"

namespace Ionflux
{

namespace Altjira
{

MatrixSourceClassInfo::MatrixSourceClassInfo()
{
	name = "MatrixSource";
	desc = "Matrix pixel source";
	baseClassInfo.push_back(Ionflux::Altjira::PixelSource::CLASS_INFO);
}

MatrixSourceClassInfo::~MatrixSourceClassInfo()
{
}

// run-time type information instance constants
const MatrixSourceClassInfo MatrixSource::matrixSourceClassInfo;
const Ionflux::ObjectBase::IFClassInfo* MatrixSource::CLASS_INFO = &MatrixSource::matrixSourceClassInfo;

MatrixSource::MatrixSource()
: matrixC0(nullptr), matrixC1(nullptr), matrixC2(nullptr), matrixAlpha(nullptr), width(Ionflux::Altjira::EXTENT_INFINITE), height(Ionflux::Altjira::EXTENT_INFINITE)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	defaultColor.space = Color::SPACE_HSV;
	defaultColor.c0 = 0.;
	defaultColor.c1 = 0.;
	defaultColor.c2 = 0.;
	defaultColor.alpha = 1.;
}

MatrixSource::MatrixSource(const Ionflux::Altjira::MatrixSource& other)
: matrixC0(nullptr), matrixC1(nullptr), matrixC2(nullptr), matrixAlpha(nullptr), width(Ionflux::Altjira::EXTENT_INFINITE), height(Ionflux::Altjira::EXTENT_INFINITE)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

MatrixSource::MatrixSource(unsigned int initWidth, unsigned int initHeight,
Ionflux::Mapping::Matrix* initMatrixC0, Ionflux::Mapping::Matrix* 
initMatrixC1, Ionflux::Mapping::Matrix* initMatrixC2, 
Ionflux::Mapping::Matrix* initMatrixAlpha, const Ionflux::Altjira::Color& 
initDefaultColor, Ionflux::Altjira::ColorSpace initColorSpace)
: matrixC0(nullptr), matrixC1(nullptr), matrixC2(nullptr), 
matrixAlpha(nullptr), width(initWidth), height(initHeight)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setMatrixC0(initMatrixC0);
	setMatrixC1(initMatrixC1);
	setMatrixC2(initMatrixC2);
	setMatrixAlpha(initMatrixAlpha);
	setDefaultColor(initDefaultColor, initColorSpace);
}

MatrixSource::~MatrixSource()
{
	// TODO: Nothing ATM. ;-)
}

void MatrixSource::setDefaultColor(const Ionflux::Altjira::Color& color, 
Ionflux::Altjira::ColorSpace newColorSpace)
{
	FloatColor fc;
	if (newColorSpace != Color::SPACE_UNDEFINED)
	    fc.space = newColorSpace;
	else
	    fc.space = defaultColor.space;
	color.getFloatColor(fc);
	defaultColor = fc;
}

bool MatrixSource::getPixel(unsigned int x, unsigned int y, 
Ionflux::Altjira::ByteColor& color) const
{
	FloatColor fc;
	fc.space = color.space;
	getPixel(x, y, fc);
	floatToByte(fc, color);
	return true;
}

bool MatrixSource::getPixel(unsigned int x, unsigned int y, 
Ionflux::Altjira::FloatColor& color) const
{
	if ((width != EXTENT_INFINITE) && (x >= width))
	    throw AltjiraError("Index (x) out of bounds.");
	if ((height != EXTENT_INFINITE) && (y >= height))
	    throw AltjiraError("Index (y) out of bounds.");
	FloatColor result;
	result = defaultColor;
	if (matrixC0 != 0)
	{
	    if (matrixC0->isWithinBounds(y, x))
	        result.c0 = matrixC0->v(y, x);
	}
	if (matrixC1 != 0)
	{
	    if (matrixC1->isWithinBounds(y, x))
	        result.c1 = matrixC1->v(y, x);
	}
	if (matrixC2 != 0)
	{
	    if (matrixC2->isWithinBounds(y, x))
	        result.c2 = matrixC2->v(y, x);
	}
	if (matrixAlpha != 0)
	{
	    if (matrixAlpha->isWithinBounds(y, x))
	        result.alpha = matrixAlpha->v(y, x);
	}
	toColorSpace(result, color.space);
	color = result;
	return true;
}

bool MatrixSource::getPixel(unsigned int x, unsigned int y, 
Ionflux::Altjira::Color& color) const
{
	FloatColor fc;
	fc.space = Color::SPACE_RGB;
	getPixel(x, y, fc);
	color.setFromFloatColor(fc);
	return true;
}

void MatrixSource::setDefaultColor(const Ionflux::Altjira::FloatColor& 
newDefaultColor)
{
	defaultColor = newDefaultColor;
}

Ionflux::Altjira::FloatColor MatrixSource::getDefaultColor() const
{
	return defaultColor;
}

void MatrixSource::setColorSpace(Ionflux::Altjira::ColorSpace 
newColorSpace)
{
	if (newColorSpace == defaultColor.space)
	    return;
	toColorSpace(defaultColor, newColorSpace);
}

Ionflux::Altjira::ColorSpace MatrixSource::getColorSpace() const
{
	return defaultColor.space;
}

void MatrixSource::setMatrixC0(Ionflux::Mapping::Matrix* newMatrixC0)
{
	if (matrixC0 == newMatrixC0)
		return;
	if (newMatrixC0 != 0)
		addLocalRef(newMatrixC0);
	if (matrixC0 != 0)
		removeLocalRef(matrixC0);
	matrixC0 = newMatrixC0;
}

Ionflux::Mapping::Matrix* MatrixSource::getMatrixC0() const
{
	return matrixC0;
}

void MatrixSource::setMatrixC1(Ionflux::Mapping::Matrix* newMatrixC1)
{
	if (matrixC1 == newMatrixC1)
		return;
	if (newMatrixC1 != 0)
		addLocalRef(newMatrixC1);
	if (matrixC1 != 0)
		removeLocalRef(matrixC1);
	matrixC1 = newMatrixC1;
}

Ionflux::Mapping::Matrix* MatrixSource::getMatrixC1() const
{
	return matrixC1;
}

void MatrixSource::setMatrixC2(Ionflux::Mapping::Matrix* newMatrixC2)
{
	if (matrixC2 == newMatrixC2)
		return;
	if (newMatrixC2 != 0)
		addLocalRef(newMatrixC2);
	if (matrixC2 != 0)
		removeLocalRef(matrixC2);
	matrixC2 = newMatrixC2;
}

Ionflux::Mapping::Matrix* MatrixSource::getMatrixC2() const
{
	return matrixC2;
}

void MatrixSource::setMatrixAlpha(Ionflux::Mapping::Matrix* newMatrixAlpha)
{
	if (matrixAlpha == newMatrixAlpha)
		return;
	if (newMatrixAlpha != 0)
		addLocalRef(newMatrixAlpha);
	if (matrixAlpha != 0)
		removeLocalRef(matrixAlpha);
	matrixAlpha = newMatrixAlpha;
}

Ionflux::Mapping::Matrix* MatrixSource::getMatrixAlpha() const
{
	return matrixAlpha;
}

void MatrixSource::setWidth(unsigned int newWidth)
{
	width = newWidth;
}

unsigned int MatrixSource::getWidth() const
{
	return width;
}

void MatrixSource::setHeight(unsigned int newHeight)
{
	height = newHeight;
}

unsigned int MatrixSource::getHeight() const
{
	return height;
}

Ionflux::Altjira::MatrixSource& MatrixSource::operator=(const 
Ionflux::Altjira::MatrixSource& other)
{
	if (this == &other)
	    return *this;
	defaultColor = other.defaultColor;
	width = other.width;
	height = other.height;
	setMatrixC0(other.getMatrixC0());
	setMatrixC1(other.getMatrixC1());
	setMatrixC2(other.getMatrixC2());
	setMatrixAlpha(other.getMatrixAlpha());
	return *this;
}

Ionflux::Altjira::MatrixSource* MatrixSource::copy() const
{
	MatrixSource* newMatrixSource = create();
	*newMatrixSource = *this;
	return newMatrixSource;
}

Ionflux::Altjira::MatrixSource* 
MatrixSource::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<MatrixSource*>(other);
}

Ionflux::Altjira::MatrixSource* 
MatrixSource::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    MatrixSource* newObject = new MatrixSource();
    if (newObject == 0)
    {
        throw AltjiraError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Altjira::MatrixSource* MatrixSource::create(unsigned int 
initWidth, unsigned int initHeight, Ionflux::Mapping::Matrix* initMatrixC0,
Ionflux::Mapping::Matrix* initMatrixC1, Ionflux::Mapping::Matrix* 
initMatrixC2, Ionflux::Mapping::Matrix* initMatrixAlpha, const 
Ionflux::Altjira::Color& initDefaultColor, Ionflux::Altjira::ColorSpace 
initColorSpace, Ionflux::ObjectBase::IFObject* parentObject)
{
    MatrixSource* newObject = new MatrixSource(initWidth, initHeight, 
    initMatrixC0, initMatrixC1, initMatrixC2, initMatrixAlpha, 
    initDefaultColor, initColorSpace);
    if (newObject == 0)
    {
        throw AltjiraError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int MatrixSource::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file MatrixSource.cpp
 * \brief Matrix pixel source implementation.
 */
