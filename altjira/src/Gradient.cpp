/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Gradient.cpp                    Gradient (implementation).
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

#include "altjira/Gradient.hpp"
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

GradientClassInfo::GradientClassInfo()
{
	name = "Gradient";
	desc = "Gradient";
	baseClassInfo.push_back(Ionflux::Altjira::Pattern::CLASS_INFO);
}

GradientClassInfo::~GradientClassInfo()
{
}

// run-time type information instance constants
const GradientClassInfo Gradient::gradientClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Gradient::CLASS_INFO = &Gradient::gradientClassInfo;

Gradient::Gradient()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Gradient::Gradient(const Ionflux::Altjira::Gradient& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Gradient::~Gradient()
{
	// TODO: Nothing ATM. ;-)
}

void Gradient::addColorStop(double offset, const Ionflux::Altjira::Color& 
color)
{
	if (pattern == 0)
	    throw AltjiraError("[Gradient::addColorStop] " 
	        "Pattern is null!");
	cairo_pattern_add_color_stop_rgba(pattern, offset, color.getRed(), 
	    color.getGreen(), color.getBlue(), color.getAlpha());
}

unsigned int Gradient::getNumColorStops() const
{
	if (pattern == 0)
	    throw AltjiraError("[Gradient::getNumColorStops] " 
	        "Pattern is null!");
	int numColorStops = 0;
	cairo_pattern_get_color_stop_count(pattern, &numColorStops);
	if (cairo_pattern_get_color_stop_count(pattern, &numColorStops) 
	    != CAIRO_STATUS_SUCCESS)
	    throw AltjiraError("[Gradient::getNumColorStops] " 
	        "Pattern is not a gradient!");
	return static_cast<unsigned int>(numColorStops);
}

void Gradient::setFromColorBand(Ionflux::Altjira::ColorBand& colorBand, 
Ionflux::Mapping::Mapping* sampleFunc, unsigned int numSamples)
{
	if (pattern == 0)
	    throw AltjiraError("[Gradient::setFromColorBand] " 
	        "Pattern is null!");
	/* <---- DEBUG ----- //
	std::ostringstream status;
	// ----- DEBUG ----> */
	if (sampleFunc == 0)
	{
	    // Use color stops from the color band.
	    for (unsigned int i = 0; i < colorBand.getNumColorStops(); i++)
	    {
	        ColorStop cs0 = colorBand.getColorStop(i);
	        cairo_pattern_add_color_stop_rgba(pattern, cs0.param, 
	            cs0.color.getRed(), cs0.color.getGreen(), cs0.color.getBlue(),
	
            cs0.color.getAlpha());
	    }
	} else
	{
	    // Sample the color band.
	    if (numSamples < 2)
	        throw AltjiraError("[Gradient::setFromColorBand] "
	            "Number of samples must be at least 2.");
	    double x = 0;
	    double dx = 1. / (numSamples - 1);
	    for (unsigned int i = 0; i < numSamples; i++)
	    {
	        Ionflux::Mapping::MappingValue t0 = (*sampleFunc)(x);
	        Color c0 = colorBand(t0);
	        /* <---- DEBUG ----- //
	        status.str("");
	        status << "x = " << x << ", t0 = " << t0 << ", c0 = " << c0;
	        log(IFLogMessage(status.str(), VL_DEBUG, this, 
	            "setFromColorBand"));
	        // ----- DEBUG ----> */
	        cairo_pattern_add_color_stop_rgba(pattern, x, 
	            c0.getRed(), c0.getGreen(), c0.getBlue(), c0.getAlpha());
	        x += dx;
	    }
	}
}

std::string Gradient::getString() const
{
	ostringstream state;
	state << getClassName() << "[";
	if (pattern != 0)
	{
	    unsigned int numCs = getNumColorStops();
	    for (unsigned int i = 0; i < numCs; i++)
	    {
	        if (i > 0)
	            state << ", ";
	        double offset = 0.;
	        FloatColor c0;
	        cairo_pattern_get_color_stop_rgba(pattern, i, &offset, &(c0.c0), 
	            &(c0.c1), &(c0.c2), &(c0.alpha));
	        state << "[" << offset << ": (" << c0.c0 << ", "<< c0.c1 
	            << ", " << c0.c2 << ", "<< c0.alpha << ")]";
	    }
	}
	state << "]";
	return state.str();
}

Ionflux::Altjira::Gradient& Gradient::operator=(const 
Ionflux::Altjira::Gradient& other)
{
    Ionflux::Altjira::Pattern::operator=(other);
	return *this;
}

Ionflux::Altjira::Gradient* Gradient::copy() const
{
    Gradient* newGradient = create();
    *newGradient = *this;
    return newGradient;
}

Ionflux::Altjira::Gradient* Gradient::upcast(Ionflux::ObjectBase::IFObject*
other)
{
    return dynamic_cast<Gradient*>(other);
}

Ionflux::Altjira::Gradient* Gradient::create(Ionflux::ObjectBase::IFObject*
parentObject)
{
    Gradient* newObject = new Gradient();
    if (newObject == 0)
    {
        throw AltjiraError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Gradient::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Gradient.cpp
 * \brief Gradient implementation.
 */
