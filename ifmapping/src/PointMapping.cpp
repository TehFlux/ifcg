/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PointMapping.cpp                Point mapping (implementation).
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

#include "ifmapping/PointMapping.hpp"
#include <sstream>
#include "ifmapping/utils.hpp"
#include "ifmapping/PointCoord.hpp"
#include "ifmapping/PointSample.hpp"
#include "ifmapping/ArcLength.hpp"
#include "ifmapping/BrentLinearRootFinder.hpp"
#include "ifmapping/MappingError.hpp"
#include "ifobject/IFMMEvent.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "ifmapping/xmlutils.hpp"
#include "ifmapping/xmlio/PointMappingXMLFactory.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

PointMappingClassInfo::PointMappingClassInfo()
{
	name = "PointMapping";
	desc = "Point mapping";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

PointMappingClassInfo::~PointMappingClassInfo()
{
}

// public member constants
const Ionflux::Mapping::MappingValue PointMapping::DEFAULT_PRECISION = 1e-5;
const Ionflux::Mapping::MappingValue PointMapping::DEFAULT_RELATIVE_ERROR = 1e-4;
const unsigned int PointMapping::DEFAULT_MAX_NUM_ITERATIONS = 14;

// run-time type information instance constants
const PointMappingClassInfo PointMapping::pointMappingClassInfo;
const Ionflux::ObjectBase::IFClassInfo* PointMapping::CLASS_INFO = &PointMapping::pointMappingClassInfo;

const std::string PointMapping::XML_ELEMENT_NAME = "pmap";

PointMapping::PointMapping()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
    refData->mmDebug = true;
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_CREATE, this));
	// TODO: Nothing ATM. ;-)
}

PointMapping::PointMapping(const Ionflux::Mapping::PointMapping& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	refData->mmDebug = true;
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_CREATE, this));
	*this = other;
}

PointMapping::~PointMapping()
{
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_DELETE, this));
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
PointMapping::getParamCoord(Ionflux::Mapping::MappingValue value, 
Ionflux::Mapping::CoordinateID coord, Ionflux::Mapping::MappingValue 
precision)
{
	addRef();
	PointCoord* fc = PointCoord::create(this, coord, -value);
	BrentLinearRootFinder* rf = BrentLinearRootFinder::create();
	addLocalRef(rf);
	rf->setFunc(fc);
	MappingValue t = (*rf)(0. - precision, 1. + precision, precision);
	removeLocalRef(rf);
	removeRef();
	return t;
}

Ionflux::Mapping::Point 
PointMapping::evalCoord(Ionflux::Mapping::MappingValue value, 
Ionflux::Mapping::CoordinateID coord, Ionflux::Mapping::MappingValue 
precision)
{
	Ionflux::Mapping::MappingValue t = getParamCoord(
	    value, coord, precision);
	return call(t);
}

Ionflux::Mapping::MappingValue 
PointMapping::getParamArcLength(Ionflux::Mapping::MappingValue value, 
Ionflux::Mapping::MappingValue relativeError, unsigned int 
maxNumIterations, Ionflux::Mapping::MappingValue precision)
{
	if (value == 0.)
	    return 0.;
	addRef();
	ArcLength* fc = ArcLength::create(
	        this, -value, 1., 0., relativeError, maxNumIterations);
	BrentLinearRootFinder* rf = BrentLinearRootFinder::create();
	addLocalRef(rf);
	rf->setFunc(fc);
	Ionflux::Mapping::MappingValue t = (*rf)(0. - precision, 
	    1. + precision, precision);
	removeLocalRef(rf);
	removeRef();
	return t;
}

Ionflux::Mapping::Point 
PointMapping::evalArcLength(Ionflux::Mapping::MappingValue value, 
Ionflux::Mapping::MappingValue relativeError, unsigned int 
maxNumIterations, Ionflux::Mapping::MappingValue precision)
{
	Ionflux::Mapping::MappingValue t = getParamArcLength(
	    value, relativeError, maxNumIterations, precision);
	return call(t);
}

Ionflux::Mapping::PointSample* 
PointMapping::getSample(Ionflux::Mapping::MappingValue value, bool 
calculateArcLength, Ionflux::Mapping::MappingValue relativeError, unsigned 
int maxNumIterations)
{
	MappingValue l0 = 0.;
	if (calculateArcLength)
	{
	    addRef();
	    ArcLength* fc = ArcLength::create(this, 0., 1., 0., 
	        relativeError, maxNumIterations);
	    addLocalRef(fc);
	    l0 = (*fc)(value);
	    removeLocalRef(fc);
	    removeRef();
	}
	Point* p0 = Point::create();
	*p0 = call(value);
	PointSample* s0 = PointSample::create(value, p0, l0);
	return s0;
}

Ionflux::Mapping::MappingValue 
PointMapping::getArcLength(Ionflux::Mapping::MappingValue value, 
Ionflux::Mapping::MappingValue relativeError, unsigned int 
maxNumIterations)
{
	if (value == 0.)
	    return 0.;
	addRef();
	ArcLength* fc = ArcLength::create(
	    this, 0., 1., 0., relativeError, maxNumIterations);
	addLocalRef(fc);
	MappingValue result = (*fc)(value);
	removeLocalRef(fc);
	removeRef();
	return result;
}

Ionflux::Mapping::Point 
PointMapping::operator()(Ionflux::Mapping::MappingValue value)
{
	// TODO: Implementation.
	return call(value);;
}

Ionflux::Mapping::Point PointMapping::call(Ionflux::Mapping::MappingValue 
value)
{
	// TODO: Implementation.
	return Point();
}

Ionflux::Mapping::PointMapping& PointMapping::operator=(const 
Ionflux::Mapping::PointMapping& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Mapping::PointMapping* PointMapping::copy() const
{
    PointMapping* newPointMapping = create();
    *newPointMapping = *this;
    return newPointMapping;
}

Ionflux::Mapping::PointMapping* 
PointMapping::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<PointMapping*>(other);
}

Ionflux::Mapping::PointMapping* 
PointMapping::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    PointMapping* newObject = new PointMapping();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

std::string PointMapping::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string PointMapping::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::ObjectBase::IFObject::getXMLAttributeData();
	return d0.str();
}

void PointMapping::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::ObjectBase::IFObject::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void PointMapping::loadFromXMLFile(const std::string& fileName)
{
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, getXMLElementName());
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
PointMapping::getXMLObjectFactory()
{
	static Ionflux::Mapping::XMLUtils::PointMappingXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::Mapping::XMLUtils::PointMappingXMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 
            IFObject::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file PointMapping.cpp
 * \brief Point mapping implementation.
 */
