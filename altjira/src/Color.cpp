/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Color.cpp                       Color (implementation).
 * =========================================================================
 * 
 * This file is part of Altjira - Ionflux' Image Processing Library.
 * 
 * Altjira - Ionflux' Image Processing Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
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

#include "altjira/Color.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "ifmapping/utils.hpp"
#include "altjira/utils.hpp"
#include "altjira/imageutils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Altjira
{

ColorClassInfo::ColorClassInfo()
{
	name = "Color";
	desc = "Color";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

ColorClassInfo::~ColorClassInfo()
{
}

// public member constants
const Ionflux::Altjira::Color Color::TRANSPARENT = Ionflux::Altjira::Color(0., 0., 0., 0.);
const Ionflux::Altjira::Color Color::BLACK = Ionflux::Altjira::Color(0., 0., 0., 1.);
const Ionflux::Altjira::Color Color::WHITE = Ionflux::Altjira::Color(1., 1., 1., 1.);
const Ionflux::Altjira::Color Color::GRAY_10 = Ionflux::Altjira::Color(.9, .9, .9, 1.);
const Ionflux::Altjira::Color Color::GRAY_20 = Ionflux::Altjira::Color(.8, .8, .8, 1.);
const Ionflux::Altjira::Color Color::GRAY_30 = Ionflux::Altjira::Color(.7, .7, .7, 1.);
const Ionflux::Altjira::Color Color::GRAY_40 = Ionflux::Altjira::Color(.6, .6, .6, 1.);
const Ionflux::Altjira::Color Color::GRAY_50 = Ionflux::Altjira::Color(.5, .5, .5, 1.);
const Ionflux::Altjira::Color Color::GRAY_60 = Ionflux::Altjira::Color(.4, .4, .4, 1.);
const Ionflux::Altjira::Color Color::GRAY_70 = Ionflux::Altjira::Color(.3, .3, .3, 1.);
const Ionflux::Altjira::Color Color::GRAY_80 = Ionflux::Altjira::Color(.2, .2, .2, 1.);
const Ionflux::Altjira::Color Color::GRAY_90 = Ionflux::Altjira::Color(.1, .1, .1, 1.);
const Ionflux::Altjira::Color Color::RED = Ionflux::Altjira::Color(1., 0., 0., 1.);
const Ionflux::Altjira::Color Color::GREEN = Ionflux::Altjira::Color(0., 1., 0., 1.);
const Ionflux::Altjira::Color Color::BLUE = Ionflux::Altjira::Color(0., 0., 1., 1.);
const Ionflux::Altjira::Color Color::CYAN = Ionflux::Altjira::Color(0., 1., 1., 1.);
const Ionflux::Altjira::Color Color::MAGENTA = Ionflux::Altjira::Color(1., 0., 1., 1.);
const Ionflux::Altjira::Color Color::YELLOW = Ionflux::Altjira::Color(1., 1., 0., 1.);
const Ionflux::Altjira::Color Color::VIOLET = Ionflux::Altjira::Color(0.56, 0., 1., 1.);
const Ionflux::Altjira::Color Color::ORANGE = Ionflux::Altjira::Color(1., 0.5, 0., 1.);
const Ionflux::Altjira::ColorSpace Color::SPACE_UNDEFINED = 0;
const Ionflux::Altjira::ColorSpace Color::SPACE_RGB = 1;
const Ionflux::Altjira::ColorSpace Color::SPACE_HSV = 2;
const Ionflux::Altjira::ColorSpace Color::SPACE_HSL = 3;

// run-time type information instance constants
const ColorClassInfo Color::colorClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Color::CLASS_INFO = &Color::colorClassInfo;

Color::Color()
: red(0.0), green(0.0), blue(0.0), alpha(0.0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Color::Color(const Ionflux::Altjira::Color& other)
: red(0.0), green(0.0), blue(0.0), alpha(0.0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Color::Color(const ByteColor& initColor)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = initColor;
}

Color::Color(const FloatColor& initColor)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = initColor;
}

Color::Color(FloatColorValue initRed, FloatColorValue initGreen, 
FloatColorValue initBlue, FloatColorValue initAlpha)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	red = initRed;
	green = initGreen;
	blue = initBlue;
	alpha = initAlpha;
}

Color::Color(ByteColorValue initRed, ByteColorValue initGreen, 
ByteColorValue initBlue, ByteColorValue initAlpha)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	red = byteToFloat(initRed);
	green = byteToFloat(initGreen);
	blue = byteToFloat(initBlue);
	alpha = byteToFloat(initAlpha);
}

Color::Color(const std::string& hexColor)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setFromHex(hexColor);
}

Color::~Color()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Altjira::Color& Color::setFromHex(const std::string& hexColor)
{
	red = 0.0;
	green = 0.0;
	blue = 0.0;
	alpha = 1.0;
	if ((hexColor.size() < 1)
	    || (hexColor[0] != '#'))
	    return *this;
	if (hexColor.size() >= 3)
	    red = static_cast<double>(
	        strtol(hexColor.substr(1, 2).c_str(), 0, 16)) / 255.;
	if (hexColor.size() >= 5)
	    green = static_cast<double>(
	        strtol(hexColor.substr(3, 2).c_str(), 0, 16)) / 255.;
	if (hexColor.size() >= 7)
	    blue = static_cast<double>(
	        strtol(hexColor.substr(5, 2).c_str(), 0, 16)) / 255.;
	if (hexColor.size() >= 9)
	    alpha = static_cast<double>(
	        strtol(hexColor.substr(7, 2).c_str(), 0, 16)) / 255.;
	return *this;
}

std::string Color::getHex() const
{
	Color target(*this);
	target.clamp();
	std::ostringstream result;
	result << "#";
	result << right << setfill('0') << hex 
	    << setw(2) << static_cast<int>(::round(target.getRed() * 255.))
	    << setw(2) << static_cast<int>(::round(target.getGreen() * 255.))
	    << setw(2) << static_cast<int>(::round(target.getBlue() * 255.))
	    << setw(2) << static_cast<int>(::round(target.getAlpha() * 255.));
	return result.str();
}

Ionflux::Altjira::Color& Color::clampRed(const Ionflux::Mapping::Range& 
range)
{
	red = Ionflux::Mapping::clamp(red, range);
	return *this;
}

Ionflux::Altjira::Color& Color::clampGreen(const Ionflux::Mapping::Range& 
range)
{
	green = Ionflux::Mapping::clamp(green, range);
	return *this;
}

Ionflux::Altjira::Color& Color::clampBlue(const Ionflux::Mapping::Range& 
range)
{
	blue = Ionflux::Mapping::clamp(blue, range);
	return *this;
}

Ionflux::Altjira::Color& Color::clampAlpha(const Ionflux::Mapping::Range& 
range)
{
	alpha = Ionflux::Mapping::clamp(alpha, range);
	return *this;
}

Ionflux::Altjira::Color& Color::clamp(const Ionflux::Mapping::Range& range)
{
	clampRed(range);
	clampGreen(range);
	clampBlue(range);
	clampAlpha(range);
	return *this;
}

Ionflux::Altjira::Color Color::interpolate(const Ionflux::Altjira::Color& 
first, const Ionflux::Altjira::Color& second, double factor)
{
	// TODO: Implementation.
	return Color(first.getRed() + factor * (second.getRed() - first.getRed()), 
        first.getGreen() + factor * (second.getGreen() - first.getGreen()), 
        first.getBlue() + factor * (second.getBlue() - first.getBlue()), 
        first.getAlpha() + factor * (second.getAlpha() - first.getAlpha()));
}

Ionflux::Altjira::Color& Color::setFromFloatColor(const 
Ionflux::Altjira::FloatColor& other)
{
	*this = other;
	return *this;
}

Ionflux::Altjira::Color& 
Color::setComponents(Ionflux::Altjira::FloatColorValue newRed, 
Ionflux::Altjira::FloatColorValue newGreen, 
Ionflux::Altjira::FloatColorValue newBlue, 
Ionflux::Altjira::FloatColorValue newAlpha)
{
	red = newRed;
	green = newGreen;
	blue = newBlue;
	alpha = newAlpha;
	return *this;
}

Ionflux::Altjira::Color& 
Color::setComponents(Ionflux::Altjira::ByteColorValue newRed, 
Ionflux::Altjira::ByteColorValue newGreen, Ionflux::Altjira::ByteColorValue
newBlue, Ionflux::Altjira::ByteColorValue newAlpha)
{
	red = byteToFloat(newRed);
	green = byteToFloat(newGreen);
	blue = byteToFloat(newBlue);
	alpha = byteToFloat(newAlpha);
	return *this;
}

void Color::getFloatColor(Ionflux::Altjira::FloatColor& color) const
{
	ColorSpace ts = color.space;
	color.c0 = red;
	color.c1 = green;
	color.c2 = blue;
	color.alpha = alpha;
	color.space = SPACE_RGB;
	toColorSpace(color, ts);
}

void Color::getByteColor(Ionflux::Altjira::ByteColor& color) const
{
	FloatColor fc;
	fc.space = color.space;
	getFloatColor(fc);
	floatToByte(fc, color);
}

Ionflux::Altjira::Color& Color::setFromByteColor(const 
Ionflux::Altjira::ByteColor& other)
{
	*this = other;
	return *this;
}

void Color::multiply(Ionflux::Altjira::Color& target, double value)
{
	target.red = red * value;
	target.green = green * value;
	target.blue = blue * value;
	target.alpha = alpha;
}

void Color::preMultiply(Ionflux::Altjira::Color& target)
{
	multiply(target, alpha);
}

void Color::divideAlpha(Ionflux::Altjira::Color& target)
{
	multiply(target, 1. / alpha);
}

Ionflux::Altjira::Color& Color::operator=(const 
Ionflux::Altjira::FloatColor& other)
{
	FloatColor fc = other;
	toRGB(fc);
	red = fc.c0;
	green = fc.c1;
	blue = fc.c2;
	alpha = fc.alpha;
	return *this;
}

Ionflux::Altjira::Color& Color::operator=(const 
Ionflux::Altjira::ByteColor& other)
{
	FloatColor fc;
	byteToFloat(other, fc);
	toRGB(fc);
	red = fc.c0;
	green = fc.c1;
	blue = fc.c2;
	alpha = fc.alpha;
	return *this;
}

bool Color::operator==(const Ionflux::Altjira::Color& other) const
{
	// TODO: Implementation.
	return (red == other.getRed())
    && (green == other.getGreen())
    && (blue == other.getBlue())
    && (alpha == other.getAlpha());
}

bool Color::operator!=(const Ionflux::Altjira::Color& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

std::string Color::getValueString() const
{
	std::ostringstream status;
	status << red << ", " << green << ", " << blue << ", " << alpha;
	return status.str();
}

Ionflux::Altjira::Color Color::interpolate(const 
Ionflux::Altjira::ColorPair& colors, double factor)
{
	// TODO: Implementation.
	return Color(colors.first.getRed() 
            + factor * (colors.second.getRed() - colors.first.getRed()), 
        colors.first.getGreen() 
            + factor * (colors.second.getGreen() - colors.first.getGreen()), 
        colors.first.getBlue() 
            + factor * (colors.second.getBlue() - colors.first.getBlue()), 
        colors.first.getAlpha() 
            + factor * (colors.second.getAlpha() - colors.first.getAlpha()));
}

void Color::setRed(double newRed)
{
	red = newRed;
}

double Color::getRed() const
{
    return red;
}

void Color::setGreen(double newGreen)
{
	green = newGreen;
}

double Color::getGreen() const
{
    return green;
}

void Color::setBlue(double newBlue)
{
	blue = newBlue;
}

double Color::getBlue() const
{
    return blue;
}

void Color::setAlpha(double newAlpha)
{
	alpha = newAlpha;
}

double Color::getAlpha() const
{
    return alpha;
}

void Color::setHue(double newHue)
{
	FloatColor fc;
	fc.space = SPACE_HSL;
	getFloatColor(fc);
	fc.c0 = newHue;
	setFromFloatColor(fc);
}

double Color::getHue() const
{
	FloatColor fc;
	fc.space = SPACE_HSL;
	getFloatColor(fc);
	return fc.c0;
}

void Color::setSaturation(double newSaturation)
{
	FloatColor fc;
	fc.space = SPACE_HSL;
	getFloatColor(fc);
	fc.c1 = newSaturation;
	setFromFloatColor(fc);
}

double Color::getSaturation() const
{
	FloatColor fc;
	fc.space = SPACE_HSL;
	getFloatColor(fc);
	return fc.c1;
}

void Color::setLuminance(double newLuminance)
{
	FloatColor fc;
	fc.space = SPACE_HSL;
	getFloatColor(fc);
	fc.c2 = newLuminance;
	setFromFloatColor(fc);
}

double Color::getLuminance() const
{
	FloatColor fc;
	fc.space = SPACE_HSL;
	getFloatColor(fc);
	return fc.c2;
}

Ionflux::Altjira::Color& Color::operator=(const Ionflux::Altjira::Color& 
other)
{
    red = other.red;
    green = other.green;
    blue = other.blue;
    alpha = other.alpha;
	return *this;
}

Ionflux::Altjira::Color* Color::copy() const
{
    Color* newColor = create();
    *newColor = *this;
    return newColor;
}

Ionflux::Altjira::Color* Color::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Color*>(other);
}

Ionflux::Altjira::Color* Color::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Color* newObject = new Color();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file Color.cpp
 * \brief Color implementation.
 */
