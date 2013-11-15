/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NoiseMapTransform.cpp           Noise map transform (implementation).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFMapping - Ionflux Mapping Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFMapping - Ionflux Mapping Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "ifmapping/NoiseMapTransform.hpp"
#include <cmath>
#include <sstream>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

namespace Noise
{

NoiseMapTransformClassInfo::NoiseMapTransformClassInfo()
{
	name = "NoiseMapTransform";
	desc = "Noise map transform";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

NoiseMapTransformClassInfo::~NoiseMapTransformClassInfo()
{
}

// run-time type information instance constants
const NoiseMapTransformClassInfo NoiseMapTransform::noiseMapTransformClassInfo;
const Ionflux::ObjectBase::IFClassInfo* NoiseMapTransform::CLASS_INFO = &NoiseMapTransform::noiseMapTransformClassInfo;

NoiseMapTransform::NoiseMapTransform()
: func(0), scale(0.5), offset(0.5), resultScale(2.), resultOffset(-1.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

NoiseMapTransform::NoiseMapTransform(Ionflux::Mapping::Mapping* initFunc, 
Ionflux::Mapping::MappingValue initScale, Ionflux::Mapping::MappingValue 
initOffset, Ionflux::Mapping::MappingValue initResultScale, 
Ionflux::Mapping::MappingValue initResultOffset)
: func(0), scale(initScale), offset(initOffset), 
resultScale(initResultScale), resultOffset(initResultOffset)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setFunc(initFunc);
}

NoiseMapTransform::~NoiseMapTransform()
{
	// TODO: Nothing ATM. ;-)
}

void NoiseMapTransform::transform(noise::utils::NoiseMap& map)
{
	int width = map.GetWidth();
	int height = map.GetHeight();
	int stride = map.GetStride();
	float* data = map.GetSlabPtr();
	for (int y = 0; y < height; y++)
	    for (int x = 0; x < width; x++)
	    {
	        float* cur = data + y * stride + x;
	        double t0 = scale * (*cur) + offset;
	        if (func != 0)
	            *cur = resultScale * (*func)(t0) + resultOffset;
	        else
	            *cur = resultScale * t0 + resultOffset;
	    }
}

std::string NoiseMapTransform::getString() const
{
	ostringstream status;
	status << getClassName() << "[";
	if (func != 0)
	    status << (*func);
	else
	    status << "<none>";
	status << "; " << scale << ", " << offset << "; " 
	    << resultScale << ", " << resultOffset << "]";
	return status.str();
}

void NoiseMapTransform::setFunc(Ionflux::Mapping::Mapping* newFunc)
{
	if (func == newFunc)
		return;
    if (newFunc != 0)
        addLocalRef(newFunc);
	if (func != 0)
		removeLocalRef(func);
	func = newFunc;
}

Ionflux::Mapping::Mapping* NoiseMapTransform::getFunc() const
{
    return func;
}

void NoiseMapTransform::setScale(Ionflux::Mapping::MappingValue newScale)
{
	scale = newScale;
}

Ionflux::Mapping::MappingValue NoiseMapTransform::getScale() const
{
    return scale;
}

void NoiseMapTransform::setOffset(Ionflux::Mapping::MappingValue newOffset)
{
	offset = newOffset;
}

Ionflux::Mapping::MappingValue NoiseMapTransform::getOffset() const
{
    return offset;
}

void NoiseMapTransform::setResultScale(Ionflux::Mapping::MappingValue 
newResultScale)
{
	resultScale = newResultScale;
}

Ionflux::Mapping::MappingValue NoiseMapTransform::getResultScale() const
{
    return resultScale;
}

void NoiseMapTransform::setResultOffset(Ionflux::Mapping::MappingValue 
newResultOffset)
{
	resultOffset = newResultOffset;
}

Ionflux::Mapping::MappingValue NoiseMapTransform::getResultOffset() const
{
    return resultOffset;
}

Ionflux::Mapping::Noise::NoiseMapTransform* 
NoiseMapTransform::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<NoiseMapTransform*>(other);
}

Ionflux::Mapping::Noise::NoiseMapTransform* 
NoiseMapTransform::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    NoiseMapTransform* newObject = new NoiseMapTransform();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

}

/** \file NoiseMapTransform.cpp
 * \brief Noise map transform implementation.
 */
