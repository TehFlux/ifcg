/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BlendSrcOver.cpp                Color blender (SrcOver) 
 * (implementation).
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

#include "altjira/BlendSrcOver.hpp"
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
#include "altjira/AltjiraError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Altjira
{

BlendSrcOverClassInfo::BlendSrcOverClassInfo()
{
	name = "BlendSrcOver";
	desc = "Color blender (SrcOver)";
	baseClassInfo.push_back(Ionflux::Altjira::ColorBlender::CLASS_INFO);
}

BlendSrcOverClassInfo::~BlendSrcOverClassInfo()
{
}

// run-time type information instance constants
const BlendSrcOverClassInfo BlendSrcOver::blendSrcOverClassInfo;
const Ionflux::ObjectBase::IFClassInfo* BlendSrcOver::CLASS_INFO = &BlendSrcOver::blendSrcOverClassInfo;

BlendSrcOver::BlendSrcOver()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

BlendSrcOver::BlendSrcOver(const Ionflux::Altjira::BlendSrcOver& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

BlendSrcOver::BlendSrcOver(const Ionflux::Altjira::Color& initColor0, const
Ionflux::Altjira::Color& initColor1, double initSourceOpacity, double 
initTargetOpacity)
: Ionflux::Altjira::ColorBlender(initColor0, initColor1, initSourceOpacity,
initTargetOpacity)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

BlendSrcOver::~BlendSrcOver()
{
	// TODO: Nothing ATM. ;-)
}

void BlendSrcOver::blend(Ionflux::Altjira::FloatColor& target, const 
Ionflux::Altjira::FloatColor& newColor0, const 
Ionflux::Altjira::FloatColor& newColor1, double newSourceOpacity, double 
newTargetOpacity) const
{
	/* <---- DEBUG ----- //
	ostringstream message;
	// ----- DEBUG ----> */
	// Multiply alpha values by layer opacity.
	FloatColor sc;
	FloatColor dc;
	Ionflux::Altjira::copy(newColor0, sc);
	Ionflux::Altjira::copy(newColor1, dc);
	sc.alpha *= newSourceOpacity;
	dc.alpha *= newTargetOpacity;
	/* <---- DEBUG ----- //
	message.str("");
	message << "s0 = " << s0.getString() << ", d0 = " << d0.getString();
	log(IFLogMessage(message.str(), VL_DEBUG, this, "blend"));
	// ----- DEBUG ----> */
	// Pre-multiply alpha on source and target colors.
	preMultiply(sc);
	preMultiply(dc);
	/* <---- DEBUG ----- //
	message.str("");
	message << "sc0 = " << sc0.getString() << ", dc0 = " << dc0.getString();
	log(IFLogMessage(message.str(), VL_DEBUG, this, "blend"));
	// ----- DEBUG ----> */
	// Perform the blending.
	target.c0 = sc.c0 + dc.c0 * (1. - sc.alpha);
	target.c1 = sc.c1 + dc.c1 * (1. - sc.alpha);
	target.c2 = sc.c2 + dc.c2 * (1. - sc.alpha);
	target.alpha = sc.alpha + dc.alpha - sc.alpha * dc.alpha;
	target.space = Color::SPACE_RGB;
	/* <---- DEBUG ----- //
	message.str("");
	message << "r0 = " << r0.getString();
	log(IFLogMessage(message.str(), VL_DEBUG, this, "blend"));
	// ----- DEBUG ----> */
	divideAlpha(target);
}

void BlendSrcOver::blend(Ionflux::Altjira::ByteColor& target, const 
Ionflux::Altjira::ByteColor& newColor0, const Ionflux::Altjira::ByteColor& 
newColor1, const Ionflux::Altjira::ByteColorValue& newSourceOpacity, const 
Ionflux::Altjira::ByteColorValue& newTargetOpacity) const
{
	/* <---- DEBUG ----- //
	ostringstream message;
	// ----- DEBUG ----> */
	// Multiply alpha values by layer opacity.
	ByteColor sc;
	ByteColor dc;
	Ionflux::Altjira::copy(newColor0, sc);
	Ionflux::Altjira::copy(newColor1, dc);
	sc.alpha = LUT_MULT[256 * sc.alpha + newSourceOpacity];
	dc.alpha = LUT_MULT[256 * dc.alpha + newTargetOpacity];
	/* <---- DEBUG ----- //
	message.str("");
	message << "sc = " << Ionflux::Altjira::getString(sc) << ", dc = " 
	<< Ionflux::Altjira::getString(dc);
	log(IFLogMessage(message.str(), VL_DEBUG, this, "blend"));
	// ----- DEBUG ----> */
	// Pre-multiply alpha on source and target colors.
	preMultiply(sc);
	preMultiply(dc);
	/* <---- DEBUG ----- //
	message.str("");
	message << "sc(p) = " << Ionflux::Altjira::getString(sc) << ", dc(p) = " 
	<< Ionflux::Altjira::getString(dc);
	log(IFLogMessage(message.str(), VL_DEBUG, this, "blend"));
	// ----- DEBUG ----> */
	/* Perform the blending.
	   256 * 255 (alpha = 1.) = 65280. */
	target.c0 = LUT_ADD[256 * sc.c0 + LUT_MULT[ 
	    256 * dc.c0 + LUT_SUB[65280 + sc.alpha]]];
	target.c1 = LUT_ADD[256 * sc.c1 + LUT_MULT[ 
	    256 * dc.c1 + LUT_SUB[65280 + sc.alpha]]];
	target.c2 = LUT_ADD[256 * sc.c2 + LUT_MULT[ 
	    256 * dc.c2 + LUT_SUB[65280 + sc.alpha]]];
	target.alpha = sc.alpha + dc.alpha 
	    - LUT_MULT[256 * sc.alpha + dc.alpha];
	target.space = Color::SPACE_RGB;
	/* <---- DEBUG ----- //
	message.str("");
	message << "target = " << Ionflux::Altjira::getString(target);
	log(IFLogMessage(message.str(), VL_DEBUG, this, "blend"));
	// ----- DEBUG ----> */
	divideAlpha(target);
}

Ionflux::Altjira::BlendSrcOver& BlendSrcOver::operator=(const 
Ionflux::Altjira::BlendSrcOver& other)
{
    color0 = other.color0;
    color1 = other.color1;
    targetOpacity = other.targetOpacity;
    sourceOpacity = other.sourceOpacity;
	return *this;
}

Ionflux::Altjira::BlendSrcOver* BlendSrcOver::copy() const
{
    BlendSrcOver* newBlendSrcOver = create();
    *newBlendSrcOver = *this;
    return newBlendSrcOver;
}

Ionflux::Altjira::BlendSrcOver* 
BlendSrcOver::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<BlendSrcOver*>(other);
}

Ionflux::Altjira::BlendSrcOver* 
BlendSrcOver::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    BlendSrcOver* newObject = new BlendSrcOver();
    if (newObject == 0)
    {
        throw AltjiraError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int BlendSrcOver::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file BlendSrcOver.cpp
 * \brief Color blender (SrcOver) implementation.
 */
