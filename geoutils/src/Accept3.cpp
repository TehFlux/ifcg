/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Accept3.cpp                     Vector mapping: Accept (implementation).
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

#include "geoutils/Accept3.hpp"
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

namespace Mapping
{

Accept3ClassInfo::Accept3ClassInfo()
{
	name = "Accept3";
	desc = "Vector mapping: Accept";
}

Accept3ClassInfo::~Accept3ClassInfo()
{
}

// run-time type information instance constants
const Accept3ClassInfo Accept3::accept3ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Accept3::CLASS_INFO = &Accept3::accept3ClassInfo;

Accept3::Accept3()
: maxIters(Ionflux::Mapping::MAX_ITERATIONS), source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	/* <---- DEBUG ----- //
	numCalls = new unsigned int(0);
	numIterations = new unsigned int(0);
	// ----- DEBUG ----> */
}

Accept3::Accept3(const Ionflux::GeoUtils::Mapping::Accept3& other)
: maxIters(Ionflux::Mapping::MAX_ITERATIONS), source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Accept3::Accept3(Ionflux::GeoUtils::Mapping::Vector3Mapping* initSource, 
Ionflux::Mapping::MappingValue initMaxIters)
: maxIters(Ionflux::Mapping::MAX_ITERATIONS), source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setSource(initSource);
	/* <---- DEBUG ----- //
	numCalls = new unsigned int(0);
	numIterations = new unsigned int(0);
	// ----- DEBUG ----> */
}

Accept3::~Accept3()
{
	/* <---- DEBUG ----- //
	delete numCalls;
	delete numIterations;
	// ----- DEBUG ----> */
}

Ionflux::GeoUtils::Vector3 Accept3::call(Ionflux::Mapping::MappingValue 
value) const
{
	if (source == 0)
	    throw GeoUtilsError("Source function not defined.");
	Ionflux::GeoUtils::Vector3 v0 = (*source)(value);
	unsigned int i = 0;
	while (!checkCondition(v0) 
	    && (i <= maxIters))
	{
	    v0 = (*source)(value);
	    i++;
	}
	/* <---- DEBUG ----- //
	(*numIterations) += i;
	(*numCalls)++;
	// ----- DEBUG ----> */
	if (i > maxIters)
	    throw GeoUtilsError("Maximum number of iterations exceeded.");
	return v0;
}

std::string Accept3::getString() const
{
	ostringstream status;
	status << getClassName() << "[";
	if (source != 0)
	    status << source->getString();
	else
	    status << "<none>";
	status << ", " << maxIters << "]";
	return status.str();
}

void Accept3::setMaxIters(unsigned int newMaxIters)
{
	maxIters = newMaxIters;
}

unsigned int Accept3::getMaxIters() const
{
    return maxIters;
}

void Accept3::setSource(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
newSource)
{
	if (source == newSource)
		return;
    if (newSource != 0)
        addLocalRef(newSource);
	if (source != 0)
		removeLocalRef(source);
	source = newSource;
}

Ionflux::GeoUtils::Mapping::Vector3Mapping* Accept3::getSource() const
{
    return source;
}

Ionflux::GeoUtils::Mapping::Accept3& Accept3::operator=(const 
Ionflux::GeoUtils::Mapping::Accept3& other)
{
    Vector3Mapping::operator=(other);
    setSource(other.source);
	return *this;
}

Ionflux::GeoUtils::Mapping::Accept3* 
Accept3::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Accept3*>(other);
}

}

}

}

/** \file Accept3.cpp
 * \brief Vector mapping: Accept implementation.
 */
