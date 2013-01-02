/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BlendMultiply.cpp               Color blender (Multiply) 
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

#include "altjira/BlendMultiply.hpp"
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

BlendMultiplyClassInfo::BlendMultiplyClassInfo()
{
	name = "BlendMultiply";
	desc = "Color blender (Multiply)";
	baseClassInfo.push_back(Ionflux::Altjira::ColorBlender::CLASS_INFO);
}

BlendMultiplyClassInfo::~BlendMultiplyClassInfo()
{
}

// run-time type information instance constants
const BlendMultiplyClassInfo BlendMultiply::blendMultiplyClassInfo;
const Ionflux::ObjectBase::IFClassInfo* BlendMultiply::CLASS_INFO = &BlendMultiply::blendMultiplyClassInfo;

BlendMultiply::BlendMultiply()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

BlendMultiply::BlendMultiply(const Ionflux::Altjira::BlendMultiply& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

BlendMultiply::BlendMultiply(const Ionflux::Altjira::Color& initColor0, 
const Ionflux::Altjira::Color& initColor1, double initSourceOpacity, double
initTargetOpacity)
: Ionflux::Altjira::ColorBlender(initColor0, initColor1, initSourceOpacity,
initTargetOpacity)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

BlendMultiply::~BlendMultiply()
{
	// TODO: Nothing ATM. ;-)
}

void BlendMultiply::blend(Ionflux::Altjira::FloatColor& target, const 
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
	target.c0 = sc.c0 * dc.c0 + sc.c0 * (1. - dc.alpha) 
	    + dc.c0 * (1. - sc.alpha);
	target.c1 = sc.c1 * dc.c1 + sc.c1 * (1. - dc.alpha) 
	    + dc.c1 * (1. - sc.alpha);
	target.c2 = sc.c2 * dc.c2 + sc.c2 * (1. - dc.alpha) 
	    + dc.c2 * (1. - sc.alpha);
	target.alpha = sc.alpha + dc.alpha - sc.alpha * dc.alpha;
	target.space = Color::SPACE_RGB;
	/* <---- DEBUG ----- //
	message.str("");
	message << "r0 = " << r0.getString();
	log(IFLogMessage(message.str(), VL_DEBUG, this, "blend"));
	// ----- DEBUG ----> */
	divideAlpha(target);
}

void BlendMultiply::blend(Ionflux::Altjira::ByteColor& target, const 
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
	target.c0 = lutAdd(lutAdd(lutMult(sc.c0, dc.c0), lutMult(sc.c0, 
	    lutSub(255, dc.alpha))), lutMult(dc.c0, 
	        lutSub(255, sc.alpha)));
	target.c1 = lutAdd(lutAdd(lutMult(sc.c1, dc.c1), lutMult(sc.c1, 
	    lutSub(255, dc.alpha))), lutMult(dc.c1, 
	        lutSub(255, sc.alpha)));
	target.c2 = lutAdd(lutAdd(lutMult(sc.c2, dc.c2), lutMult(sc.c2, 
	    lutSub(255, dc.alpha))), lutMult(dc.c2, 
	        lutSub(255, sc.alpha)));
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

Ionflux::Altjira::BlendMultiply& BlendMultiply::operator=(const 
Ionflux::Altjira::BlendMultiply& other)
{
    color0 = other.color0;
    color1 = other.color1;
    targetOpacity = other.targetOpacity;
    sourceOpacity = other.sourceOpacity;
	return *this;
}

Ionflux::Altjira::BlendMultiply* BlendMultiply::copy() const
{
    BlendMultiply* newBlendMultiply = create();
    *newBlendMultiply = *this;
    return newBlendMultiply;
}

Ionflux::Altjira::BlendMultiply* 
BlendMultiply::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<BlendMultiply*>(other);
}

Ionflux::Altjira::BlendMultiply* 
BlendMultiply::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    BlendMultiply* newObject = new BlendMultiply();
    if (newObject == 0)
    {
        throw AltjiraError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file BlendMultiply.cpp
 * \brief Color blender (Multiply) implementation.
 */
