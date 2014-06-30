/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NoiseMap.cpp                    Noise map (implementation).
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

#include "altjira/NoiseMap.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "altjira/AltjiraError.hpp"
#include "ifmapping/NoiseMapTransform.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Altjira
{

namespace Noise
{

NoiseMapClassInfo::NoiseMapClassInfo()
{
	name = "NoiseMap";
	desc = "Noise map";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

NoiseMapClassInfo::~NoiseMapClassInfo()
{
}

// run-time type information instance constants
const NoiseMapClassInfo NoiseMap::noiseMapClassInfo;
const Ionflux::ObjectBase::IFClassInfo* NoiseMap::CLASS_INFO = &NoiseMap::noiseMapClassInfo;

NoiseMap::NoiseMap()
: noiseMap(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

NoiseMap::NoiseMap(const Ionflux::Altjira::Noise::NoiseMap& other)
: noiseMap(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

NoiseMap::NoiseMap(noise::utils::NoiseMap* initNoiseMap)
: noiseMap(initNoiseMap)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

NoiseMap::~NoiseMap()
{
	noiseMap = 0;
}

Ionflux::Mapping::Range NoiseMap::getRange()
{
	if (noiseMap == 0)
	    throw AltjiraError("[NoiseMap::getRange] "
	    "Noise map not set!");
	Ionflux::Mapping::Range result;
	result.lower = 0.;
	result.upper = 0.;
	int width = noiseMap->GetWidth();
	int height = noiseMap->GetHeight();
	int stride = noiseMap->GetStride();
	float* data = noiseMap->GetSlabPtr();
	for (int y = 0; y < height; y++)
	    for (int x = 0; x < width; x++)
	    {
	        float* cur = data + y * stride + x;
	        if ((x == 0) && (y == 0))
	        {
	            result.lower = *cur;
	            result.upper = *cur;
	        } else
	        {
	            if (*cur < result.lower)
	                result.lower = *cur;
	            if (*cur > result.upper)
	                result.upper = *cur;
	        }
	    }
	return result;
}

void NoiseMap::rescale(const Ionflux::Mapping::Range& range)
{
	if (noiseMap == 0)
	    throw AltjiraError("[NoiseMap::getRange] "
	    "Noise map not set!");
	Ionflux::Mapping::Range r0 = getRange();
	double scale = (range.upper - range.lower) / (r0.upper - r0.lower);
	transform(-r0.lower, 1., range.lower, scale);
}

void NoiseMap::transform(double offsetIn, double scaleIn, double offsetOut,
double scaleOut, Ionflux::Mapping::Mapping* func)
{
	if (noiseMap == 0)
	    throw AltjiraError("[NoiseMap::getRange] "
	    "Noise map not set!");
	Ionflux::Mapping::Noise::NoiseMapTransform nt(func, 
	    scaleIn, offsetIn, scaleOut, offsetOut);
	nt.transform(*noiseMap);
}

void NoiseMap::render(Ionflux::Altjira::Image& image, 
Ionflux::Altjira::ColorBand* colors)
{
	if (noiseMap == 0)
	    throw AltjiraError("[NoiseMap::render] "
	        "Noise map not set!");
	int width = noiseMap->GetWidth();
	int height = noiseMap->GetHeight();
	if ((image.getWidth() != static_cast<unsigned int>(width)) 
	    || (image.getHeight() != static_cast<unsigned int>(height)))
	{
	    ostringstream status;
	    status << "[NoiseMap::render] Image size differs from "
	        "noise map size (should be " << width << "x" << height 
	        << ")!";
	    throw AltjiraError(status.str());
	}
	int stride = noiseMap->GetStride();
	float* data = noiseMap->GetSlabPtr();
	FloatColor tc;
	tc.space = Color::SPACE_RGB;
	for (int y = 0; y < height; y++)
	    for (int x = 0; x < width; x++)
	    {
	        float* cur = data + y * stride + x;
	        if (colors == 0)
	        {
	            tc.c0 = *cur;
	            tc.c1 = *cur;
	            tc.c2 = *cur;
	            tc.alpha = 1.;
	        } else
	            colors->eval(*cur, tc);
	        clamp(tc);
	        image.setPixel(x, y, tc);
	    }
}

std::string NoiseMap::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

void NoiseMap::setNoiseMap(noise::utils::NoiseMap* newNoiseMap)
{
	noiseMap = newNoiseMap;
}

noise::utils::NoiseMap* NoiseMap::getNoiseMap() const
{
    return noiseMap;
}

Ionflux::Altjira::Noise::NoiseMap& NoiseMap::operator=(const 
Ionflux::Altjira::Noise::NoiseMap& other)
{
    noiseMap = other.noiseMap;
	return *this;
}

Ionflux::Altjira::Noise::NoiseMap* NoiseMap::copy() const
{
    NoiseMap* newNoiseMap = create();
    *newNoiseMap = *this;
    return newNoiseMap;
}

Ionflux::Altjira::Noise::NoiseMap* 
NoiseMap::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<NoiseMap*>(other);
}

Ionflux::Altjira::Noise::NoiseMap* 
NoiseMap::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    NoiseMap* newObject = new NoiseMap();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int NoiseMap::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file NoiseMap.cpp
 * \brief Noise map implementation.
 */
