/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FaceCompareAxis.cpp             Face comparison function object: Axis 
 * coordinate (implementation).
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

#include "geoutils/FaceCompareAxis.hpp"
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

FaceCompareAxisClassInfo::FaceCompareAxisClassInfo()
{
	name = "FaceCompareAxis";
	desc = "Face comparison function object: Axis coordinate";
}

FaceCompareAxisClassInfo::~FaceCompareAxisClassInfo()
{
}

// run-time type information instance constants
const FaceCompareAxisClassInfo FaceCompareAxis::faceCompareAxisClassInfo;
const Ionflux::ObjectBase::IFClassInfo* FaceCompareAxis::CLASS_INFO = &FaceCompareAxis::faceCompareAxisClassInfo;

FaceCompareAxis::FaceCompareAxis()
: Ionflux::GeoUtils::FaceCompare(true), axis(Ionflux::GeoUtils::AXIS_Z)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

FaceCompareAxis::FaceCompareAxis(const Ionflux::GeoUtils::FaceCompareAxis& other)
: Ionflux::GeoUtils::FaceCompare(true), axis(Ionflux::GeoUtils::AXIS_Z)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

FaceCompareAxis::FaceCompareAxis(Ionflux::GeoUtils::AxisID initAxis, bool 
initInvert)
: Ionflux::GeoUtils::FaceCompare(initInvert), axis(initAxis)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

FaceCompareAxis::~FaceCompareAxis()
{
	// TODO: Nothing ATM. ;-)
}

std::string FaceCompareAxis::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << axisToString(axis) << ", " 
	    << invert << "]";
	return status.str();
}

bool FaceCompareAxis::compare(Ionflux::GeoUtils::Face& f0, 
Ionflux::GeoUtils::Face& f1)
{
	Vector3 b0 = f0.getBarycenter();
	Vector3 b1 = f1.getBarycenter();
	return b0.getElement(axis) < b1.getElement(axis);
}

Ionflux::GeoUtils::FaceCompareAxis* 
FaceCompareAxis::create(Ionflux::GeoUtils::AxisID initAxis, bool 
initInvert)
{
	FaceCompareAxis* c0 = create();
	c0->setAxis(initAxis);
	c0->setInvert(initInvert);
	return c0;
}

void FaceCompareAxis::setAxis(Ionflux::GeoUtils::AxisID newAxis)
{
	axis = newAxis;
}

Ionflux::GeoUtils::AxisID FaceCompareAxis::getAxis() const
{
    return axis;
}

Ionflux::GeoUtils::FaceCompareAxis& FaceCompareAxis::operator=(const 
Ionflux::GeoUtils::FaceCompareAxis& other)
{
    FaceCompare::operator=(other);
    axis = other.axis;
	return *this;
}

Ionflux::GeoUtils::FaceCompareAxis* FaceCompareAxis::copy() const
{
    FaceCompareAxis* newFaceCompareAxis = create();
    *newFaceCompareAxis = *this;
    return newFaceCompareAxis;
}

Ionflux::GeoUtils::FaceCompareAxis* 
FaceCompareAxis::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<FaceCompareAxis*>(other);
}

Ionflux::GeoUtils::FaceCompareAxis* 
FaceCompareAxis::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    FaceCompareAxis* newObject = new FaceCompareAxis();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int FaceCompareAxis::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file FaceCompareAxis.cpp
 * \brief Face comparison function object: Axis coordinate implementation.
 */
