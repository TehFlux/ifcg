/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BoxBoundsItemCompare.cpp        Box bounds item comparison function 
 * object (implementation).
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

#include "geoutils/BoxBoundsItemCompare.hpp"
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

BoxBoundsItemCompareClassInfo::BoxBoundsItemCompareClassInfo()
{
	name = "BoxBoundsItemCompare";
	desc = "Box bounds item comparison function object";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

BoxBoundsItemCompareClassInfo::~BoxBoundsItemCompareClassInfo()
{
}

// run-time type information instance constants
const BoxBoundsItemCompareClassInfo BoxBoundsItemCompare::boxBoundsItemCompareClassInfo;
const Ionflux::ObjectBase::IFClassInfo* BoxBoundsItemCompare::CLASS_INFO = &BoxBoundsItemCompare::boxBoundsItemCompareClassInfo;

BoxBoundsItemCompare::BoxBoundsItemCompare()
: invert(false), target(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

BoxBoundsItemCompare::BoxBoundsItemCompare(const Ionflux::GeoUtils::BoxBoundsItemCompare& other)
: invert(false), target(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

BoxBoundsItemCompare::BoxBoundsItemCompare(bool initInvert, 
Ionflux::GeoUtils::BoxBoundsItemCompare* initTarget)
: invert(initInvert), target(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initTarget != 0)
	    setTarget(initTarget);
}

BoxBoundsItemCompare::~BoxBoundsItemCompare()
{
	// TODO: Nothing ATM. ;-)
}

std::string BoxBoundsItemCompare::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << invert << "]";
	return status.str();
}

bool BoxBoundsItemCompare::operator()(Ionflux::GeoUtils::BoxBoundsItem* b0,
Ionflux::GeoUtils::BoxBoundsItem* b1)
{
	if (invert)
	    return !compare(*b0, *b1);
	return compare(*b0, *b1);
}

bool BoxBoundsItemCompare::compare(Ionflux::GeoUtils::BoxBoundsItem& b0, 
Ionflux::GeoUtils::BoxBoundsItem& b1)
{
	if (target != 0)
	    return (*target)(&b0, &b1);
	throw GeoUtilsError("[BoxBoundsItemCompare] "
	    "Comparison not implemented and no target function specified.");
	return false;
}

void BoxBoundsItemCompare::setInvert(bool newInvert)
{
	invert = newInvert;
}

bool BoxBoundsItemCompare::getInvert() const
{
	return invert;
}

void 
BoxBoundsItemCompare::setTarget(Ionflux::GeoUtils::BoxBoundsItemCompare* 
newTarget)
{
	target = newTarget;
}

Ionflux::GeoUtils::BoxBoundsItemCompare* BoxBoundsItemCompare::getTarget() 
const
{
	return target;
}

Ionflux::GeoUtils::BoxBoundsItemCompare& 
BoxBoundsItemCompare::operator=(const 
Ionflux::GeoUtils::BoxBoundsItemCompare& other)
{
    invert = other.invert;
    setTarget(other.target);
	return *this;
}

Ionflux::GeoUtils::BoxBoundsItemCompare* BoxBoundsItemCompare::copy() const
{
    BoxBoundsItemCompare* newBoxBoundsItemCompare = create();
    *newBoxBoundsItemCompare = *this;
    return newBoxBoundsItemCompare;
}

Ionflux::GeoUtils::BoxBoundsItemCompare* 
BoxBoundsItemCompare::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<BoxBoundsItemCompare*>(other);
}

Ionflux::GeoUtils::BoxBoundsItemCompare* 
BoxBoundsItemCompare::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    BoxBoundsItemCompare* newObject = new BoxBoundsItemCompare();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file BoxBoundsItemCompare.cpp
 * \brief Box bounds item comparison function object implementation.
 */
