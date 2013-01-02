/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2009 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utils.cpp                     Utility functions (implementation).
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

#include <cmath>
#include <sstream>
#include <cstdlib>
#include "ifmapping/utils.hpp"
#include "altjira/utils.hpp"
#include "altjira/AltjiraError.hpp"
#include "altjira/lut_add.hpp"
#include "altjira/lut_mult.hpp"
#include "altjira/lut_sub.hpp"
#include "altjira/lut_div.hpp"
#include "MersenneTwister.h"

using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Altjira
{

unsigned char floatToByte(double v)
{
    return static_cast<unsigned char>(round(
        255 * Ionflux::Mapping::clamp(v)));
}

double byteToFloat(unsigned char v)
{
    return static_cast<double>(v) / 255.;
}

unsigned char lutAdd(unsigned char x, unsigned char y)
{
    return LUT_ADD[256 * x + y];
}

unsigned char lutMult(unsigned char x, unsigned char y)
{
    return LUT_MULT[256 * x + y];
}

unsigned char lutSub(unsigned char x, unsigned char y)
{
    return LUT_SUB[256 * x + y];
}

unsigned char lutDiv(unsigned char x, unsigned char y)
{
    return LUT_DIV[256 * x + y];
}

Ionflux::Altjira::GIHRankSpec createGIHRankSpec(std::string selection, 
    unsigned int size)
{
    GIHRankSpec r0;
    r0.selection = selection;
    r0.size = size;
    return r0;
}

void initRectangle(Ionflux::Altjira::ImageRect& r, double x, double y, 
    double width, double height)
{
    r.x = x;
    r.y = y;
    r.width = width;
    r.height = height;
}

Ionflux::Altjira::ImageRect intersect(const Ionflux::Altjira::ImageRect& r0, 
    const Ionflux::Altjira::ImageRect& r1)
{
	Ionflux::Mapping::Range xRange = { r1.x, r1.x + r1.width };
	Ionflux::Mapping::Range yRange = { r1.y, r1.y + r1.height };
	ImageRect result;
	result.x = Ionflux::Mapping::clamp(r0.x, xRange);
	result.y = Ionflux::Mapping::clamp(r0.y, yRange);
	unsigned int ex = Ionflux::Mapping::clamp(r0.x + r0.width, xRange);
	unsigned int ey = Ionflux::Mapping::clamp(r0.y + r0.height, yRange);
    result.width = ex - result.x;
    result.height = ey - result.y;
	return result;
}

}

}

/** \file utils.cpp
 * \brief Utility functions (implementation).
 */
