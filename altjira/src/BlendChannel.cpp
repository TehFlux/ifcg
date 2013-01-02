/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BlendChannel.cpp                Color blender (Channel) 
 * (implementation).
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

#include "altjira/BlendChannel.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "altjira/utils.hpp"
#include "altjira/imageutils.hpp"
#include "altjira/lut_mult.hpp"
#include "altjira/lut_add.hpp"
#include "altjira/lut_sub.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Altjira
{

BlendChannelClassInfo::BlendChannelClassInfo()
{
	name = "BlendChannel";
	desc = "Color blender (Channel)";
	baseClassInfo.push_back(Ionflux::Altjira::ColorBlender::CLASS_INFO);
}

BlendChannelClassInfo::~BlendChannelClassInfo()
{
}

// run-time type information instance constants
const BlendChannelClassInfo BlendChannel::blendChannelClassInfo;
const Ionflux::ObjectBase::IFClassInfo* BlendChannel::CLASS_INFO = &BlendChannel::blendChannelClassInfo;

BlendChannel::BlendChannel()
: Ionflux::Altjira::ColorBlender(Ionflux::Altjira::Color::BLACK, Ionflux::Altjira::Color::WHITE, 1., 0.), srcFunc(0), destFunc(0), srcChannel(Ionflux::Altjira::CH_VALUE), destChannel(Ionflux::Altjira::CH_VALUE), srcSpace(Ionflux::Altjira::Color::SPACE_UNDEFINED), destSpace(Ionflux::Altjira::Color::SPACE_UNDEFINED)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

BlendChannel::BlendChannel(const Ionflux::Altjira::BlendChannel& other)
: Ionflux::Altjira::ColorBlender(Ionflux::Altjira::Color::BLACK, Ionflux::Altjira::Color::WHITE, 1., 0.), srcFunc(0), destFunc(0), srcChannel(Ionflux::Altjira::CH_VALUE), destChannel(Ionflux::Altjira::CH_VALUE), srcSpace(Ionflux::Altjira::Color::SPACE_UNDEFINED), destSpace(Ionflux::Altjira::Color::SPACE_UNDEFINED)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

BlendChannel::BlendChannel(const Ionflux::Altjira::Color& initColor0, const
Ionflux::Altjira::Color& initColor1, double initSourceOpacity, double 
initTargetOpacity, Ionflux::Altjira::ChannelID initSrcChannel, 
Ionflux::Altjira::ChannelID initDestChannel, Ionflux::Altjira::ColorSpace 
initSrcSpace, Ionflux::Altjira::ColorSpace initDestSpace, 
Ionflux::Mapping::Mapping* initSrcFunc, Ionflux::Mapping::Mapping* 
initDestFunc)
: Ionflux::Altjira::ColorBlender(initColor0, initColor1, initSourceOpacity,
initTargetOpacity), srcFunc(initSrcFunc), destFunc(initDestFunc), 
srcChannel(initSrcChannel), destChannel(initDestChannel), 
srcSpace(initSrcSpace), destSpace(initDestSpace)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initSrcFunc != 0)
	    setSrcFunc(initSrcFunc);
	if (initDestFunc != 0)
	    setDestFunc(initDestFunc);
}

BlendChannel::~BlendChannel()
{
	// TODO: Nothing ATM. ;-)
}

void BlendChannel::blend(Ionflux::Altjira::FloatColor& target, const 
Ionflux::Altjira::FloatColor& newColor0, const 
Ionflux::Altjira::FloatColor& newColor1, double newSourceOpacity, double 
newTargetOpacity) const
{
	/* <---- DEBUG ----- //
	ostringstream message;
	// ----- DEBUG ----> */
	// Determine color spaces.
	ColorSpace ssp = getColorSpaceForChannel(srcChannel, srcSpace);
	ColorSpace dsp = getColorSpaceForChannel(destChannel, destSpace);
	// Determine source and destination values.
	FloatColor sc;
	FloatColor dc;
	Ionflux::Altjira::copy(newColor0, sc);
	Ionflux::Altjira::copy(newColor1, dc);
	toColorSpace(sc, ssp);
	toColorSpace(dc, dsp);
	FloatColorValue sv = getComponent(sc, srcChannel);
	FloatColorValue dv = getComponent(dc, destChannel);
	if (srcFunc != 0)
	    sv = (*srcFunc)(sv);
	if (destFunc != 0)
	    dv = (*destFunc)(dv);
	// Perform the blending.
	setComponent(dc, destChannel, 
	    newSourceOpacity * sv + newTargetOpacity * dv);
	clamp(dc);
	ColorSpace tsp = target.space;
	Ionflux::Altjira::copy(dc, target);
	toColorSpace(target, tsp);
}

void BlendChannel::blend(Ionflux::Altjira::ByteColor& target, const 
Ionflux::Altjira::ByteColor& newColor0, const Ionflux::Altjira::ByteColor& 
newColor1, const Ionflux::Altjira::ByteColorValue& newSourceOpacity, const 
Ionflux::Altjira::ByteColorValue& newTargetOpacity) const
{
	// Unoptimized version uses the float implementation.
	FloatColor sc;
	FloatColor dc;
	FloatColor tc;
	tc.space = target.space;
	byteToFloat(newColor0, sc);
	byteToFloat(newColor1, dc);
	blend(tc, sc, dc, byteToFloat(newSourceOpacity), 
	    byteToFloat(newTargetOpacity));
	floatToByte(tc, target);
}

void BlendChannel::setSrcFunc(Ionflux::Mapping::Mapping* newSrcFunc)
{
	if (srcFunc == newSrcFunc)
		return;
    if (newSrcFunc != 0)
        addLocalRef(newSrcFunc);
	if (srcFunc != 0)
		removeLocalRef(srcFunc);
	srcFunc = newSrcFunc;
}

Ionflux::Mapping::Mapping* BlendChannel::getSrcFunc() const
{
	return srcFunc;
}

void BlendChannel::setDestFunc(Ionflux::Mapping::Mapping* newDestFunc)
{
	if (destFunc == newDestFunc)
		return;
    if (newDestFunc != 0)
        addLocalRef(newDestFunc);
	if (destFunc != 0)
		removeLocalRef(destFunc);
	destFunc = newDestFunc;
}

Ionflux::Mapping::Mapping* BlendChannel::getDestFunc() const
{
	return destFunc;
}

void BlendChannel::setSrcChannel(Ionflux::Altjira::ChannelID newSrcChannel)
{
	srcChannel = newSrcChannel;
}

Ionflux::Altjira::ChannelID BlendChannel::getSrcChannel() const
{
	return srcChannel;
}

void BlendChannel::setDestChannel(Ionflux::Altjira::ChannelID 
newDestChannel)
{
	destChannel = newDestChannel;
}

Ionflux::Altjira::ChannelID BlendChannel::getDestChannel() const
{
	return destChannel;
}

void BlendChannel::setSrcSpace(Ionflux::Altjira::ColorSpace newSrcSpace)
{
	srcSpace = newSrcSpace;
}

Ionflux::Altjira::ColorSpace BlendChannel::getSrcSpace() const
{
	return srcSpace;
}

void BlendChannel::setDestSpace(Ionflux::Altjira::ColorSpace newDestSpace)
{
	destSpace = newDestSpace;
}

Ionflux::Altjira::ColorSpace BlendChannel::getDestSpace() const
{
	return destSpace;
}

Ionflux::Altjira::BlendChannel& BlendChannel::operator=(const 
Ionflux::Altjira::BlendChannel& other)
{
    if (this == &other)
        return *this;
	return *this;
}

Ionflux::Altjira::BlendChannel* BlendChannel::copy() const
{
    BlendChannel* newBlendChannel = create();
    *newBlendChannel = *this;
    return newBlendChannel;
}

Ionflux::Altjira::BlendChannel* 
BlendChannel::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    BlendChannel* newObject = new BlendChannel();
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

/** \file BlendChannel.cpp
 * \brief Color blender (Channel) implementation.
 */
