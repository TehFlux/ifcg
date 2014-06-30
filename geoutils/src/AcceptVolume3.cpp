/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * AcceptVolume3.cpp               Vector mapping: Accept volume 
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

#include "geoutils/AcceptVolume3.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Vertex3.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

AcceptVolume3ClassInfo::AcceptVolume3ClassInfo()
{
	name = "AcceptVolume3";
	desc = "Vector mapping: Accept volume";
}

AcceptVolume3ClassInfo::~AcceptVolume3ClassInfo()
{
}

// run-time type information instance constants
const AcceptVolume3ClassInfo AcceptVolume3::acceptVolume3ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* AcceptVolume3::CLASS_INFO = &AcceptVolume3::acceptVolume3ClassInfo;

AcceptVolume3::AcceptVolume3()
: refObject(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

AcceptVolume3::AcceptVolume3(const Ionflux::GeoUtils::Mapping::AcceptVolume3& other)
: refObject(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

AcceptVolume3::AcceptVolume3(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
initSource, Ionflux::GeoUtils::Shape3* initRefObject, 
Ionflux::Mapping::MappingValue initMaxIters)
: Accept3(initSource, initMaxIters), refObject(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setRefObject(initRefObject);
}

AcceptVolume3::~AcceptVolume3()
{
	// TODO: Nothing ATM. ;-)
}

std::string AcceptVolume3::getString() const
{
	ostringstream status;
	status << getClassName() << "[";
	if (source != 0)
	    status << source->getString();
	else
	    status << "<none>";
	status << ", ";
	if (refObject != 0)
	    status << (*refObject);
	else
	    status << "<none>";
	status << "]";
	return status.str();
}

bool AcceptVolume3::checkCondition(const Ionflux::GeoUtils::Vector3& v) 
const
{
	if (refObject == 0)
	    throw GeoUtilsError("Reference object not set.");
	Vertex3 v0(v);
	return refObject->checkVertex(v0);
}

void AcceptVolume3::setRefObject(Ionflux::GeoUtils::Shape3* newRefObject)
{
	if (refObject == newRefObject)
		return;
    if (newRefObject != 0)
        addLocalRef(newRefObject);
	if (refObject != 0)
		removeLocalRef(refObject);
	refObject = newRefObject;
}

Ionflux::GeoUtils::Shape3* AcceptVolume3::getRefObject() const
{
    return refObject;
}

Ionflux::GeoUtils::Mapping::AcceptVolume3& AcceptVolume3::operator=(const 
Ionflux::GeoUtils::Mapping::AcceptVolume3& other)
{
    Accept3::operator=(other);
    setRefObject(other.refObject);
	return *this;
}

Ionflux::GeoUtils::Mapping::AcceptVolume3* AcceptVolume3::copy() const
{
    AcceptVolume3* newAcceptVolume3 = create();
    *newAcceptVolume3 = *this;
    return newAcceptVolume3;
}

Ionflux::GeoUtils::Mapping::AcceptVolume3* 
AcceptVolume3::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<AcceptVolume3*>(other);
}

Ionflux::GeoUtils::Mapping::AcceptVolume3* 
AcceptVolume3::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    AcceptVolume3* newObject = new AcceptVolume3();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int AcceptVolume3::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file AcceptVolume3.cpp
 * \brief Vector mapping: Accept volume implementation.
 */
