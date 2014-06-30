/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Split.cpp                       Axis split (implementation).
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

#include "geoutils/Split.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

SplitClassInfo::SplitClassInfo()
{
	name = "Split";
	desc = "Axis split";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

SplitClassInfo::~SplitClassInfo()
{
}

// run-time type information instance constants
const SplitClassInfo Split::splitClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Split::CLASS_INFO = &Split::splitClassInfo;

Split::Split()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Split::Split(const Ionflux::GeoUtils::Split& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Split::Split(Ionflux::GeoUtils::AxisID initAxis, double initS)
: axis(initAxis), s(initS)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Split::~Split()
{
	// TODO: Nothing ATM. ;-)
}

std::string Split::getString() const
{
	ostringstream state;
	state << getClassName() << "[" << axis << ", " << s << "]";
	return state.str();
}

void Split::setAxis(Ionflux::GeoUtils::AxisID newAxis)
{
	axis = newAxis;
}

Ionflux::GeoUtils::AxisID Split::getAxis() const
{
    return axis;
}

void Split::setS(double newS)
{
	s = newS;
}

double Split::getS() const
{
    return s;
}

Ionflux::GeoUtils::Split& Split::operator=(const Ionflux::GeoUtils::Split& 
other)
{
if (this == &other)
    return *this;
setAxis(other.getAxis());
setS(other.getS());
	return *this;
}

Ionflux::GeoUtils::Split* Split::copy() const
{
    Split* newSplit = create();
    *newSplit = *this;
    return newSplit;
}

Ionflux::GeoUtils::Split* Split::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Split*>(other);
}

Ionflux::GeoUtils::Split* Split::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Split* newObject = new Split();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Split::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Split.cpp
 * \brief Axis split implementation.
 */
