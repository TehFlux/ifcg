/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * RadialGradient.cpp              Radial gradient (implementation).
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

#include "altjira/RadialGradient.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "altjira/AltjiraError.hpp"
#include "altjira/utils.hpp"
#include "altjira/imageutils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;
using namespace Ionflux::Altjira;

namespace Ionflux
{

namespace Altjira
{

RadialGradientClassInfo::RadialGradientClassInfo()
{
	name = "RadialGradient";
	desc = "Radial gradient";
	baseClassInfo.push_back(Ionflux::Altjira::Gradient::CLASS_INFO);
}

RadialGradientClassInfo::~RadialGradientClassInfo()
{
}

// run-time type information instance constants
const RadialGradientClassInfo RadialGradient::radialGradientClassInfo;
const Ionflux::ObjectBase::IFClassInfo* RadialGradient::CLASS_INFO = &RadialGradient::radialGradientClassInfo;

RadialGradient::RadialGradient()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

RadialGradient::RadialGradient(const Ionflux::Altjira::RadialGradient& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

RadialGradient::RadialGradient(double cx0, double cy0, double r0, double 
cx1, double cy1, double r1)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	init(cx0, cy0, r0, cx1, cy1, r1);
}

RadialGradient::~RadialGradient()
{
	// TODO: Nothing ATM. ;-)
}

void RadialGradient::init(double cx0, double cy0, double r0, double cx1, 
double cy1, double r1)
{
	Pattern::clear();
	pattern = cairo_pattern_create_radial(cx0, cy0, r0, cx1, cy1, r1);
	if (cairo_pattern_status(pattern) != CAIRO_STATUS_SUCCESS)
	{
	    cairo_pattern_destroy(pattern);
	    pattern = 0;
	    throw AltjiraError("[RadialGradient::init] " 
	        "Could not create pattern!");
	}
}

Ionflux::Altjira::RadialGradient* RadialGradient::create(double cx0, double
cy0, double r0, double cx1, double cy1, double r1)
{
	RadialGradient* result = create();
	result->init(cx0, cy0, r0, cx1, cy1, r1);
	return result;
}

Ionflux::Altjira::RadialGradient& RadialGradient::operator=(const 
Ionflux::Altjira::RadialGradient& other)
{
    Ionflux::Altjira::Pattern::operator=(other);
	return *this;
}

Ionflux::Altjira::RadialGradient* RadialGradient::copy() const
{
    RadialGradient* newRadialGradient = create();
    *newRadialGradient = *this;
    return newRadialGradient;
}

Ionflux::Altjira::RadialGradient* 
RadialGradient::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<RadialGradient*>(other);
}

Ionflux::Altjira::RadialGradient* 
RadialGradient::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    RadialGradient* newObject = new RadialGradient();
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

/** \file RadialGradient.cpp
 * \brief Radial gradient implementation.
 */
