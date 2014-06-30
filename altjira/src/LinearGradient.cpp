/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * LinearGradient.cpp              Linear gradient (implementation).
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

#include "altjira/LinearGradient.hpp"
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

LinearGradientClassInfo::LinearGradientClassInfo()
{
	name = "LinearGradient";
	desc = "Linear gradient";
	baseClassInfo.push_back(Ionflux::Altjira::Gradient::CLASS_INFO);
}

LinearGradientClassInfo::~LinearGradientClassInfo()
{
}

// run-time type information instance constants
const LinearGradientClassInfo LinearGradient::linearGradientClassInfo;
const Ionflux::ObjectBase::IFClassInfo* LinearGradient::CLASS_INFO = &LinearGradient::linearGradientClassInfo;

LinearGradient::LinearGradient()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

LinearGradient::LinearGradient(const Ionflux::Altjira::LinearGradient& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

LinearGradient::LinearGradient(double x0, double y0, double x1, double y1)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	init(x0, y0, x1, y1);
}

LinearGradient::~LinearGradient()
{
	// TODO: Nothing ATM. ;-)
}

void LinearGradient::init(double x0, double y0, double x1, double y1)
{
	Pattern::clear();
	pattern = cairo_pattern_create_linear(x0, y0, x1, y1);
	if (cairo_pattern_status(pattern) != CAIRO_STATUS_SUCCESS)
	{
	    cairo_pattern_destroy(pattern);
	    pattern = 0;
	    throw AltjiraError("[LinearGradient::init] " 
	        "Could not create pattern!");
	}
}

Ionflux::Altjira::LinearGradient* LinearGradient::create(double x0, double 
y0, double x1, double y1)
{
	LinearGradient* result = create();
	result->init(x0, y0, x1, y1);
	return result;
}

Ionflux::Altjira::LinearGradient& LinearGradient::operator=(const 
Ionflux::Altjira::LinearGradient& other)
{
    Ionflux::Altjira::Pattern::operator=(other);
	return *this;
}

Ionflux::Altjira::LinearGradient* LinearGradient::copy() const
{
    LinearGradient* newLinearGradient = create();
    *newLinearGradient = *this;
    return newLinearGradient;
}

Ionflux::Altjira::LinearGradient* 
LinearGradient::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<LinearGradient*>(other);
}

Ionflux::Altjira::LinearGradient* 
LinearGradient::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    LinearGradient* newObject = new LinearGradient();
    if (newObject == 0)
    {
        throw AltjiraError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int LinearGradient::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file LinearGradient.cpp
 * \brief Linear gradient implementation.
 */
