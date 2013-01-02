/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * EvalCoord.cpp                   Evaluate coordinate point mapping 
 * (implementation).
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

#include "ifmapping/EvalCoord.hpp"
#include <sstream>
#include "ifmapping/MappingError.hpp"
#include "ifmapping/utils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

EvalCoordClassInfo::EvalCoordClassInfo()
{
	name = "EvalCoord";
	desc = "Evaluate coordinate point mapping";
}

EvalCoordClassInfo::~EvalCoordClassInfo()
{
}

// run-time type information instance constants
const EvalCoordClassInfo EvalCoord::evalCoordClassInfo;
const Ionflux::ObjectBase::IFClassInfo* EvalCoord::CLASS_INFO = &EvalCoord::evalCoordClassInfo;

EvalCoord::EvalCoord()
: func(0), coord(Ionflux::Mapping::C_X), offset(Ionflux::Mapping::Point::ORIGIN), scale(Ionflux::Mapping::Point::ONES), paramOffset(0.), paramScale(1.), precision(Ionflux::Mapping::PointMapping::DEFAULT_PRECISION)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

EvalCoord::EvalCoord(const Ionflux::Mapping::EvalCoord& other)
: func(0), coord(Ionflux::Mapping::C_X), offset(Ionflux::Mapping::Point::ORIGIN), scale(Ionflux::Mapping::Point::ONES), paramOffset(0.), paramScale(1.), precision(Ionflux::Mapping::PointMapping::DEFAULT_PRECISION)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

EvalCoord::EvalCoord(Ionflux::Mapping::PointMapping* initFunc, 
Ionflux::Mapping::CoordinateID initCoord, Ionflux::Mapping::Point 
initOffset, Ionflux::Mapping::Point initScale, 
Ionflux::Mapping::MappingValue initParamOffset, 
Ionflux::Mapping::MappingValue initParamScale, 
Ionflux::Mapping::MappingValue initPrecision)
: func(0), coord(initCoord), offset(initOffset), scale(initScale), 
paramOffset(initParamOffset), paramScale(initParamScale), 
precision(initPrecision)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setFunc(initFunc);
}

EvalCoord::~EvalCoord()
{
	// TODO: Nothing ATM. ;-)
}

std::string EvalCoord::getString() const
{
	ostringstream status;
	status << getClassName() << "[";
	if (func != 0)
	    status << (*func);
	else
	    status << "<none>";
	status << "; " << coordToString(coord) << ", " << offset << ", " 
	    << scale << ", " << paramScale << ", " << paramOffset << ", " 
	    << precision << "]";
	return status.str();
}

Ionflux::Mapping::Point EvalCoord::call(Ionflux::Mapping::MappingValue 
value)
{
	Point result = func->evalCoord(
	        value * paramScale + paramOffset, coord, precision);
	return result * scale + offset;
}

void EvalCoord::setFunc(Ionflux::Mapping::PointMapping* newFunc)
{
	if (func == newFunc)
		return;
    if (newFunc != 0)
        addLocalRef(newFunc);
	if (func != 0)
		removeLocalRef(func);
	func = newFunc;
}

Ionflux::Mapping::PointMapping* EvalCoord::getFunc() const
{
	return func;
}

void EvalCoord::setCoord(Ionflux::Mapping::CoordinateID newCoord)
{
	coord = newCoord;
}

Ionflux::Mapping::CoordinateID EvalCoord::getCoord() const
{
	return coord;
}

void EvalCoord::setOffset(Ionflux::Mapping::Point newOffset)
{
	offset = newOffset;
}

Ionflux::Mapping::Point EvalCoord::getOffset() const
{
	return offset;
}

void EvalCoord::setScale(Ionflux::Mapping::Point newScale)
{
	scale = newScale;
}

Ionflux::Mapping::Point EvalCoord::getScale() const
{
	return scale;
}

void EvalCoord::setParamOffset(Ionflux::Mapping::MappingValue 
newParamOffset)
{
	paramOffset = newParamOffset;
}

Ionflux::Mapping::MappingValue EvalCoord::getParamOffset() const
{
	return paramOffset;
}

void EvalCoord::setParamScale(Ionflux::Mapping::MappingValue newParamScale)
{
	paramScale = newParamScale;
}

Ionflux::Mapping::MappingValue EvalCoord::getParamScale() const
{
	return paramScale;
}

void EvalCoord::setPrecision(Ionflux::Mapping::MappingValue newPrecision)
{
	precision = newPrecision;
}

Ionflux::Mapping::MappingValue EvalCoord::getPrecision() const
{
	return precision;
}

Ionflux::Mapping::EvalCoord& EvalCoord::operator=(const 
Ionflux::Mapping::EvalCoord& other)
{
    setFunc(other.func);
    coord = other.coord;
    offset = other.offset;
    precision = other.precision;
	return *this;
}

Ionflux::Mapping::EvalCoord* EvalCoord::copy() const
{
    EvalCoord* newEvalCoord = create();
    *newEvalCoord = *this;
    return newEvalCoord;
}

Ionflux::Mapping::EvalCoord* 
EvalCoord::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<EvalCoord*>(other);
}

Ionflux::Mapping::EvalCoord* 
EvalCoord::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    EvalCoord* newObject = new EvalCoord();
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

/** \file EvalCoord.cpp
 * \brief Evaluate coordinate point mapping implementation.
 */
