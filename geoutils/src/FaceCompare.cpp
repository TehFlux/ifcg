/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FaceCompare.cpp                 Face comparison function object 
 * (implementation).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * GeoUtils - Ionflux' Geometry Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with GeoUtils - Ionflux' Geometry Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "geoutils/FaceCompare.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

FaceCompareClassInfo::FaceCompareClassInfo()
{
	name = "FaceCompare";
	desc = "Face comparison function object";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

FaceCompareClassInfo::~FaceCompareClassInfo()
{
}

// run-time type information instance constants
const FaceCompareClassInfo FaceCompare::faceCompareClassInfo;
const Ionflux::ObjectBase::IFClassInfo* FaceCompare::CLASS_INFO = &FaceCompare::faceCompareClassInfo;

FaceCompare::FaceCompare()
: invert(false), target(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

FaceCompare::FaceCompare(const Ionflux::GeoUtils::FaceCompare& other)
: invert(false), target(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

FaceCompare::FaceCompare(bool initInvert, Ionflux::GeoUtils::FaceCompare* 
initTarget)
: invert(initInvert), target(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initTarget != 0)
	    setTarget(initTarget);
}

FaceCompare::~FaceCompare()
{
	// TODO: Nothing ATM. ;-)
}

std::string FaceCompare::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << invert << "]";
	return status.str();
}

bool FaceCompare::operator()(Ionflux::GeoUtils::Face* f0, 
Ionflux::GeoUtils::Face* f1)
{
	if (invert)
	    return !compare(*f0, *f1);
	return compare(*f0, *f1);
}

bool FaceCompare::compare(Ionflux::GeoUtils::Face& f0, 
Ionflux::GeoUtils::Face& f1)
{
	if (target != 0)
	    return (*target)(&f0, &f1);
	throw GeoUtilsError("Comparison not implemented and no target "
	    "function specified.");
	return false;
}

void FaceCompare::setInvert(bool newInvert)
{
	invert = newInvert;
}

bool FaceCompare::getInvert() const
{
    return invert;
}

void FaceCompare::setTarget(Ionflux::GeoUtils::FaceCompare* newTarget)
{
	target = newTarget;
}

Ionflux::GeoUtils::FaceCompare* FaceCompare::getTarget() const
{
    return target;
}

Ionflux::GeoUtils::FaceCompare& FaceCompare::operator=(const 
Ionflux::GeoUtils::FaceCompare& other)
{
    invert = other.invert;
    setTarget(other.target);
	return *this;
}

Ionflux::GeoUtils::FaceCompare* FaceCompare::copy() const
{
    FaceCompare* newFaceCompare = create();
    *newFaceCompare = *this;
    return newFaceCompare;
}

Ionflux::GeoUtils::FaceCompare* 
FaceCompare::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<FaceCompare*>(other);
}

Ionflux::GeoUtils::FaceCompare* 
FaceCompare::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    FaceCompare* newObject = new FaceCompare();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int FaceCompare::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file FaceCompare.cpp
 * \brief Face comparison function object implementation.
 */
