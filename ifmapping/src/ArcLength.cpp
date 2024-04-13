/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ArcLength.cpp                   Arc length mapping (implementation).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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

#include "ifmapping/ArcLength.hpp"
#include <sstream>
#include <cmath>
#include "ifmapping/MappingError.hpp"
#include "ifmapping/utils.hpp"
#include "ifobject/IFMMEvent.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

ArcLengthClassInfo::ArcLengthClassInfo()
{
	name = "ArcLength";
	desc = "Arc length mapping";
}

ArcLengthClassInfo::~ArcLengthClassInfo()
{
}

// public member constants
const Ionflux::Mapping::MappingValue ArcLength::DEFAULT_RELATIVE_ERROR = 1e-4;
const unsigned int ArcLength::DEFAULT_MAX_NUM_ITERATIONS = 14;

// run-time type information instance constants
const ArcLengthClassInfo ArcLength::arcLengthClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ArcLength::CLASS_INFO = &ArcLength::arcLengthClassInfo;

ArcLength::ArcLength()
: func(0), offset(0.), scale(1.), refParam(0.), relativeError(DEFAULT_RELATIVE_ERROR), maxNumIterations(DEFAULT_MAX_NUM_ITERATIONS)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	refData->mmDebug = true;
	if (refData->mmDebug)
		handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
			Ionflux::ObjectBase::IFMMEvent::TYPE_CREATE, this));
	// TODO: Nothing ATM. ;-)
}

ArcLength::ArcLength(const Ionflux::Mapping::ArcLength& other)
: func(0), offset(0.), scale(1.), refParam(0.), relativeError(DEFAULT_RELATIVE_ERROR), maxNumIterations(DEFAULT_MAX_NUM_ITERATIONS)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	refData->mmDebug = true;
	if (refData->mmDebug)
		handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
			Ionflux::ObjectBase::IFMMEvent::TYPE_CREATE, this));
	*this = other;
}

ArcLength::ArcLength(Ionflux::Mapping::PointMapping* initFunc, 
Ionflux::Mapping::MappingValue initOffset, Ionflux::Mapping::MappingValue 
initScale, Ionflux::Mapping::MappingValue initRefParam, 
Ionflux::Mapping::MappingValue initRelativeError, 
Ionflux::Mapping::MappingValue initMaxNumIterations)
: func(0), offset(initOffset), scale(initScale), refParam(initRefParam), 
relativeError(initRelativeError), maxNumIterations(initMaxNumIterations)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	refData->mmDebug = true;
	if (refData->mmDebug)
		handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
			Ionflux::ObjectBase::IFMMEvent::TYPE_CREATE, this));
	setFunc(initFunc);
}

ArcLength::~ArcLength()
{
	if (refData->mmDebug)
		handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
			Ionflux::ObjectBase::IFMMEvent::TYPE_DELETE, this));
	// TODO: Nothing ATM. ;-)
}

std::string ArcLength::getValueString() const
{
	ostringstream status;
	if (func != 0)
	    status << (*func);
	else
	    status << "<none>";
	status << "; refParam = " << refParam 
	    << ", relativeError = " << relativeError 
	    << ", maxNumIterations = " << maxNumIterations
	    << ", scale = " << scale << ", offset = " << offset;
	return status.str();
}

Ionflux::Mapping::MappingValue 
ArcLength::call(Ionflux::Mapping::MappingValue value) const
{
	double result = 0.;
	unsigned int numSteps = 3;
	double re0 = 2. * relativeError;
	unsigned int k = 0;
	while ((re0 > relativeError) 
	    && (k < maxNumIterations))
	{
	    double result0 = 0.;
	    double dt = (value - refParam) 
	        / static_cast<double>(numSteps);
	    for (unsigned int i = 0; i < numSteps; i++)
	    {
	        Point p0((*func)(refParam + dt * i));
	        Point p1((*func)(refParam + dt * (i + 1)));
	        result0 += p0.distance(p1);
	    }
	    if (result0 != 0.)
	        re0 = ::fabs(1. - result / result0);
	    else
	        re0 = 0.;
	    result = result0;
	    numSteps *= 2;
	    k++;
	}
	/* <---- DEBUG ----- //
	std::cerr << "[ArcLength::call] DEBUG: "
	    "k = " << k << ", maxNumIterations = " << maxNumIterations 
	    << ", relativeError = " << relativeError << ", re0 = " << re0
	    << std::endl;
	// ----- DEBUG ----> */
	return result * scale + offset;
}

void ArcLength::setFunc(Ionflux::Mapping::PointMapping* newFunc)
{
	if (func == newFunc)
		return;
	if (newFunc != 0)
		addLocalRef(newFunc);
	if (func != 0)
		removeLocalRef(func);
	func = newFunc;
}

Ionflux::Mapping::PointMapping* ArcLength::getFunc() const
{
	return func;
}

void ArcLength::setOffset(Ionflux::Mapping::MappingValue newOffset)
{
	offset = newOffset;
}

Ionflux::Mapping::MappingValue ArcLength::getOffset() const
{
	return offset;
}

void ArcLength::setScale(Ionflux::Mapping::MappingValue newScale)
{
	scale = newScale;
}

Ionflux::Mapping::MappingValue ArcLength::getScale() const
{
	return scale;
}

void ArcLength::setRefParam(Ionflux::Mapping::MappingValue newRefParam)
{
	refParam = newRefParam;
}

Ionflux::Mapping::MappingValue ArcLength::getRefParam() const
{
	return refParam;
}

void ArcLength::setRelativeError(Ionflux::Mapping::MappingValue 
newRelativeError)
{
	relativeError = newRelativeError;
}

Ionflux::Mapping::MappingValue ArcLength::getRelativeError() const
{
	return relativeError;
}

void ArcLength::setMaxNumIterations(unsigned int newMaxNumIterations)
{
	maxNumIterations = newMaxNumIterations;
}

unsigned int ArcLength::getMaxNumIterations() const
{
	return maxNumIterations;
}

Ionflux::Mapping::ArcLength& ArcLength::operator=(const 
Ionflux::Mapping::ArcLength& other)
{
	if (this == &other)
	    return *this;
	setFunc(other.func);
	refParam = other.refParam;
	relativeError = other.relativeError;
	return *this;
}

Ionflux::Mapping::ArcLength* ArcLength::copy() const
{
	ArcLength* newArcLength = create();
	*newArcLength = *this;
	return newArcLength;
}

Ionflux::Mapping::ArcLength* 
ArcLength::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<ArcLength*>(other);
}

Ionflux::Mapping::ArcLength* 
ArcLength::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    ArcLength* newObject = new ArcLength();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Mapping::ArcLength* 
ArcLength::create(Ionflux::Mapping::PointMapping* initFunc, 
Ionflux::Mapping::MappingValue initOffset, Ionflux::Mapping::MappingValue 
initScale, Ionflux::Mapping::MappingValue initRefParam, 
Ionflux::Mapping::MappingValue initRelativeError, 
Ionflux::Mapping::MappingValue initMaxNumIterations, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    ArcLength* newObject = new ArcLength(initFunc, initOffset, initScale, 
    initRefParam, initRelativeError, initMaxNumIterations);
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int ArcLength::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file ArcLength.cpp
 * \brief Arc length mapping implementation.
 */
