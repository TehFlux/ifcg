/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ChainableMapping.cpp            Chainable mapping (implementation).
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

#include "ifmapping/ChainableMapping.hpp"
#include <sstream>
#include "ifmapping/utils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

ChainableMappingClassInfo::ChainableMappingClassInfo()
{
	name = "ChainableMapping";
	desc = "Chainable mapping";
}

ChainableMappingClassInfo::~ChainableMappingClassInfo()
{
}

// run-time type information instance constants
const ChainableMappingClassInfo ChainableMapping::chainableMappingClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ChainableMapping::CLASS_INFO = &ChainableMapping::chainableMappingClassInfo;

ChainableMapping::ChainableMapping()
: func(0), scale(1.), offset(0.), resultScale(1.), resultOffset(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ChainableMapping::ChainableMapping(const Ionflux::Mapping::ChainableMapping& other)
: func(0), scale(1.), offset(0.), resultScale(1.), resultOffset(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ChainableMapping::ChainableMapping(Ionflux::Mapping::Mapping* initFunc, 
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

ChainableMapping::~ChainableMapping()
{
	// TODO: Nothing ATM. ;-)
}

std::string ChainableMapping::getString() const
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

Ionflux::Mapping::MappingValue 
ChainableMapping::call(Ionflux::Mapping::MappingValue value) const
{
	MappingValue t0 = 0.;
	if (func == 0)
	    t0 = scale * value + offset;
	else
	    t0 = (*func)(value);
	return resultScale * callWithParam(t0) + resultOffset;;
}

void ChainableMapping::setFunc(Ionflux::Mapping::Mapping* newFunc)
{
	if (func == newFunc)
		return;
    if (newFunc != 0)
        addLocalRef(newFunc);
	if (func != 0)
		removeLocalRef(func);
	func = newFunc;
}

Ionflux::Mapping::Mapping* ChainableMapping::getFunc() const
{
	return func;
}

void ChainableMapping::setScale(Ionflux::Mapping::MappingValue newScale)
{
	scale = newScale;
}

Ionflux::Mapping::MappingValue ChainableMapping::getScale() const
{
	return scale;
}

void ChainableMapping::setOffset(Ionflux::Mapping::MappingValue newOffset)
{
	offset = newOffset;
}

Ionflux::Mapping::MappingValue ChainableMapping::getOffset() const
{
	return offset;
}

void ChainableMapping::setResultScale(Ionflux::Mapping::MappingValue 
newResultScale)
{
	resultScale = newResultScale;
}

Ionflux::Mapping::MappingValue ChainableMapping::getResultScale() const
{
	return resultScale;
}

void ChainableMapping::setResultOffset(Ionflux::Mapping::MappingValue 
newResultOffset)
{
	resultOffset = newResultOffset;
}

Ionflux::Mapping::MappingValue ChainableMapping::getResultOffset() const
{
	return resultOffset;
}

Ionflux::Mapping::ChainableMapping& ChainableMapping::operator=(const 
Ionflux::Mapping::ChainableMapping& other)
{
    setFunc(other.func);
    scale = other.scale;
    offset = other.offset;
	return *this;
}

Ionflux::Mapping::ChainableMapping* 
ChainableMapping::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<ChainableMapping*>(other);
}

}

}

/** \file ChainableMapping.cpp
 * \brief Chainable mapping implementation.
 */
