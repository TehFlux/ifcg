/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Compose3.cpp                    Vector mapping: Compose 
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

#include "geoutils/Compose3.hpp"
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

Compose3ClassInfo::Compose3ClassInfo()
{
	name = "Compose3";
	desc = "Vector mapping: Compose";
}

Compose3ClassInfo::~Compose3ClassInfo()
{
}

// run-time type information instance constants
const Compose3ClassInfo Compose3::compose3ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Compose3::CLASS_INFO = &Compose3::compose3ClassInfo;

Compose3::Compose3()
: funcX0(0), funcX1(0), funcX2(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Compose3::Compose3(const Ionflux::GeoUtils::Mapping::Compose3& other)
: funcX0(0), funcX1(0), funcX2(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Compose3::Compose3(Ionflux::Mapping::Mapping* initFuncX0, 
Ionflux::Mapping::Mapping* initFuncX1, Ionflux::Mapping::Mapping* 
initFuncX2)
: funcX0(0), funcX1(0), funcX2(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setFuncX0(initFuncX0);
	setFuncX1(initFuncX1);
	setFuncX2(initFuncX2);
}

Compose3::~Compose3()
{
	// TODO: Nothing ATM. ;-)
}

void Compose3::setFuncs(Ionflux::Mapping::Mapping* newFuncX0, 
Ionflux::Mapping::Mapping* newFuncX1, Ionflux::Mapping::Mapping* newFuncX2)
{
	setFuncX0(newFuncX0);
	setFuncX1(newFuncX1);
	setFuncX2(newFuncX2);
}

void Compose3::setFuncsEqual(Ionflux::Mapping::Mapping* newFunc)
{
	setFuncX0(newFunc);
	setFuncX1(newFunc);
	setFuncX2(newFunc);
}

Ionflux::GeoUtils::Vector3 Compose3::call(Ionflux::Mapping::MappingValue 
value) const
{
	double x0 = 0.;
	if (funcX0 != 0)
	    x0 = (*funcX0)(value);
	double x1 = x0;
	if (funcX1 != 0)
	    x1 = (*funcX1)(value);
	double x2 = x1;
	if (funcX2 != 0)
	    x2 = (*funcX2)(value);
	return Vector3(x0, x1, x2);
}

std::string Compose3::getString() const
{
	ostringstream status;
	status << getClassName() << "[";
	if (funcX0 != 0)
	    status << funcX0->getString();
	else
	    status << "<none>";
	if (funcX1 != 0)
	    status << ", " << funcX1->getString();
	else
	    status << ", <none>";
	if (funcX2 != 0)
	    status << ", " << funcX2->getString();
	else
	    status << ", <none>";
	status << "]";
	return status.str();
}

void Compose3::setFuncX0(Ionflux::Mapping::Mapping* newFuncX0)
{
	if (funcX0 == newFuncX0)
		return;
    if (newFuncX0 != 0)
        addLocalRef(newFuncX0);
	if (funcX0 != 0)
		removeLocalRef(funcX0);
	funcX0 = newFuncX0;
}

Ionflux::Mapping::Mapping* Compose3::getFuncX0() const
{
    return funcX0;
}

void Compose3::setFuncX1(Ionflux::Mapping::Mapping* newFuncX1)
{
	if (funcX1 == newFuncX1)
		return;
    if (newFuncX1 != 0)
        addLocalRef(newFuncX1);
	if (funcX1 != 0)
		removeLocalRef(funcX1);
	funcX1 = newFuncX1;
}

Ionflux::Mapping::Mapping* Compose3::getFuncX1() const
{
    return funcX1;
}

void Compose3::setFuncX2(Ionflux::Mapping::Mapping* newFuncX2)
{
	if (funcX2 == newFuncX2)
		return;
    if (newFuncX2 != 0)
        addLocalRef(newFuncX2);
	if (funcX2 != 0)
		removeLocalRef(funcX2);
	funcX2 = newFuncX2;
}

Ionflux::Mapping::Mapping* Compose3::getFuncX2() const
{
    return funcX2;
}

Ionflux::GeoUtils::Mapping::Compose3& Compose3::operator=(const 
Ionflux::GeoUtils::Mapping::Compose3& other)
{
    setFuncX0(other.funcX0);
    setFuncX1(other.funcX1);
    setFuncX2(other.funcX2);
	return *this;
}

Ionflux::GeoUtils::Mapping::Compose3* Compose3::copy() const
{
    Compose3* newCompose3 = create();
    *newCompose3 = *this;
    return newCompose3;
}

Ionflux::GeoUtils::Mapping::Compose3* 
Compose3::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Compose3*>(other);
}

Ionflux::GeoUtils::Mapping::Compose3* 
Compose3::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Compose3* newObject = new Compose3();
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

}

/** \file Compose3.cpp
 * \brief Vector mapping: Compose implementation.
 */
