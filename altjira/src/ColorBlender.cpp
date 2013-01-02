/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ColorBlender.cpp                ColorBlender (implementation).
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

#include "altjira/ColorBlender.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "altjira/utils.hpp"
#include "altjira/imageutils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Altjira
{

ColorBlenderClassInfo::ColorBlenderClassInfo()
{
	name = "ColorBlender";
	desc = "ColorBlender";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

ColorBlenderClassInfo::~ColorBlenderClassInfo()
{
}

// run-time type information instance constants
const ColorBlenderClassInfo ColorBlender::colorBlenderClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ColorBlender::CLASS_INFO = &ColorBlender::colorBlenderClassInfo;

ColorBlender::ColorBlender()
: color0(Ionflux::Altjira::Color::BLACK), color1(Ionflux::Altjira::Color::WHITE), sourceOpacity(1.), targetOpacity(1.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ColorBlender::ColorBlender(const Ionflux::Altjira::ColorBlender& other)
: color0(Ionflux::Altjira::Color::BLACK), color1(Ionflux::Altjira::Color::WHITE), sourceOpacity(1.), targetOpacity(1.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ColorBlender::ColorBlender(const Ionflux::Altjira::Color& initColor0, const
Ionflux::Altjira::Color& initColor1, double initSourceOpacity, double 
initTargetOpacity)
: color0(initColor0), color1(initColor1), sourceOpacity(initSourceOpacity),
targetOpacity(initTargetOpacity)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ColorBlender::~ColorBlender()
{
	// TODO: Nothing ATM. ;-)
}

void ColorBlender::blend(Ionflux::Altjira::Color& target, const 
Ionflux::Altjira::Color& newColor0, const Ionflux::Altjira::Color& 
newColor1, double newSourceOpacity, double newTargetOpacity) const
{
	FloatColor s;
	FloatColor d;
	FloatColor t;
	s.space = Color::SPACE_RGB;
	d.space = Color::SPACE_RGB;
	newColor0.getFloatColor(s);
	newColor1.getFloatColor(d);
	blend(t, s, d, newSourceOpacity, newTargetOpacity);
	target.setFromFloatColor(t);
}

void ColorBlender::blend(Ionflux::Altjira::ByteColor& target, const 
Ionflux::Altjira::ByteColor& newColor0, const Ionflux::Altjira::ByteColor& 
newColor1, const Ionflux::Altjira::ByteColorValue& newSourceOpacity, const 
Ionflux::Altjira::ByteColorValue& newTargetOpacity) const
{
	FloatColor s;
	FloatColor d;
	FloatColor t;
	s.space = newColor0.space;
	d.space = newColor1.space;
	byteToFloat(newColor0, s);
	byteToFloat(newColor1, d);
	blend(t, s, d, byteToFloat(newSourceOpacity), 
	    byteToFloat(newTargetOpacity));
	floatToByte(t, target);
}

void ColorBlender::operator()(Ionflux::Altjira::Color& target, const 
Ionflux::Altjira::Color* newColor0, const Ionflux::Altjira::Color* 
newColor1, const double* newSourceOpacity, const double* newTargetOpacity) 
const
{
	if (newColor0 == 0)
	    newColor0 = &color0;
	if (newColor1 == 0)
	    newColor1 = &color1;
	if (newSourceOpacity == 0)
	    newSourceOpacity = &sourceOpacity;
	if (newTargetOpacity == 0)
	    newTargetOpacity = &targetOpacity;
	return blend(target, *newColor0, *newColor1, *newSourceOpacity, *newTargetOpacity);
}

std::string ColorBlender::getString() const
{
	ostringstream state;
	state << getClassName() << "[" << color0.getString() << ", " 
	    << color1.getString() << "; " << sourceOpacity << ", " 
	    << targetOpacity << "]";
	return state.str();
}

void ColorBlender::setColor0(const Ionflux::Altjira::Color& newColor0)
{
	color0 = newColor0;
}

Ionflux::Altjira::Color ColorBlender::getColor0() const
{
	return color0;
}

void ColorBlender::setColor1(const Ionflux::Altjira::Color& newColor1)
{
	color1 = newColor1;
}

Ionflux::Altjira::Color ColorBlender::getColor1() const
{
	return color1;
}

void ColorBlender::setSourceOpacity(double newSourceOpacity)
{
	sourceOpacity = newSourceOpacity;
}

double ColorBlender::getSourceOpacity() const
{
	return sourceOpacity;
}

void ColorBlender::setTargetOpacity(double newTargetOpacity)
{
	targetOpacity = newTargetOpacity;
}

double ColorBlender::getTargetOpacity() const
{
	return targetOpacity;
}

Ionflux::Altjira::ColorBlender& ColorBlender::operator=(const 
Ionflux::Altjira::ColorBlender& other)
{
setColor0(other.getColor0());
setColor1(other.getColor1());
setSourceOpacity(other.getSourceOpacity());
setTargetOpacity(other.getTargetOpacity());
	return *this;
}

}

}

/** \file ColorBlender.cpp
 * \brief ColorBlender implementation.
 */
