/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PointCoord.cpp                  Point coordinate mapping 
 * (implementation).
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

#include "ifmapping/PointCoord.hpp"
#include <sstream>
#include "ifmapping/MappingError.hpp"
#include "ifmapping/utils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

PointCoordClassInfo::PointCoordClassInfo()
{
	name = "PointCoord";
	desc = "Point coordinate mapping";
}

PointCoordClassInfo::~PointCoordClassInfo()
{
}

// run-time type information instance constants
const PointCoordClassInfo PointCoord::pointCoordClassInfo;
const Ionflux::ObjectBase::IFClassInfo* PointCoord::CLASS_INFO = &PointCoord::pointCoordClassInfo;

PointCoord::PointCoord()
: func(0), coord(Ionflux::Mapping::C_X), offset(0.), scale(1.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

PointCoord::PointCoord(const Ionflux::Mapping::PointCoord& other)
: func(0), coord(Ionflux::Mapping::C_X), offset(0.), scale(1.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

PointCoord::PointCoord(Ionflux::Mapping::PointMapping* initFunc, 
Ionflux::Mapping::CoordinateID initCoord, Ionflux::Mapping::MappingValue 
initOffset, Ionflux::Mapping::MappingValue initScale)
: func(0), coord(initCoord), offset(initOffset), scale(initScale)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setFunc(initFunc);
}

PointCoord::~PointCoord()
{
	// TODO: Nothing ATM. ;-)
}

std::string PointCoord::getValueString() const
{
	ostringstream status;
	if (func != 0)
	    status << (*func);
	else
	    status << "<none>";
	status << "; " << coordToString(coord) << ", scale = " 
	    << scale << ", offset = " << offset;
	return status.str();
}

Ionflux::Mapping::MappingValue 
PointCoord::call(Ionflux::Mapping::MappingValue value) const
{
	Point p0 = (*func)(value);
	Ionflux::Mapping::MappingValue result;
	if (coord == Ionflux::Mapping::C_X)
	    result = p0.getX();
	else
	if (coord == Ionflux::Mapping::C_Y)
	    result = p0.getY();
	else
	    result = p0.getZ();
	return result * scale + offset;
}

void PointCoord::setFunc(Ionflux::Mapping::PointMapping* newFunc)
{
	if (func == newFunc)
		return;
    if (newFunc != 0)
        addLocalRef(newFunc);
	if (func != 0)
		removeLocalRef(func);
	func = newFunc;
}

Ionflux::Mapping::PointMapping* PointCoord::getFunc() const
{
    return func;
}

void PointCoord::setCoord(Ionflux::Mapping::CoordinateID newCoord)
{
	coord = newCoord;
}

Ionflux::Mapping::CoordinateID PointCoord::getCoord() const
{
    return coord;
}

void PointCoord::setOffset(Ionflux::Mapping::MappingValue newOffset)
{
	offset = newOffset;
}

Ionflux::Mapping::MappingValue PointCoord::getOffset() const
{
    return offset;
}

void PointCoord::setScale(Ionflux::Mapping::MappingValue newScale)
{
	scale = newScale;
}

Ionflux::Mapping::MappingValue PointCoord::getScale() const
{
    return scale;
}

Ionflux::Mapping::PointCoord& PointCoord::operator=(const 
Ionflux::Mapping::PointCoord& other)
{
    setFunc(other.func);
    coord = other.coord;
    offset = other.offset;
	return *this;
}

Ionflux::Mapping::PointCoord* PointCoord::copy() const
{
    PointCoord* newPointCoord = create();
    *newPointCoord = *this;
    return newPointCoord;
}

Ionflux::Mapping::PointCoord* 
PointCoord::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<PointCoord*>(other);
}

Ionflux::Mapping::PointCoord* 
PointCoord::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    PointCoord* newObject = new PointCoord();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Mapping::PointCoord* 
PointCoord::create(Ionflux::Mapping::PointMapping* initFunc, 
Ionflux::Mapping::CoordinateID initCoord, Ionflux::Mapping::MappingValue 
initOffset, Ionflux::Mapping::MappingValue initScale, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    PointCoord* newObject = new PointCoord(initFunc, initCoord, initOffset,
    initScale);
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int PointCoord::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file PointCoord.cpp
 * \brief Point coordinate mapping implementation.
 */
