/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PointSample.cpp                 Point sample (implementation).
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

#include "ifmapping/PointSample.hpp"
#include <sstream>
#include "ifmapping/utils.hpp"
#include "ifmapping/MappingError.hpp"
#include "ifobject/IFMMEvent.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "ifmapping/xmlutils.hpp"
#include "ifmapping/xmlio/PointSampleXMLFactory.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

PointSampleClassInfo::PointSampleClassInfo()
{
	name = "PointSample";
	desc = "Point sample";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

PointSampleClassInfo::~PointSampleClassInfo()
{
}

// run-time type information instance constants
const PointSampleClassInfo PointSample::pointSampleClassInfo;
const Ionflux::ObjectBase::IFClassInfo* PointSample::CLASS_INFO = &PointSample::pointSampleClassInfo;

const std::string PointSample::XML_ELEMENT_NAME = "ps";

PointSample::PointSample()
: param(0.), coords(0), arcLength(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
    refData->mmDebug = true;
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_CREATE, this));
	// TODO: Nothing ATM. ;-)
}

PointSample::PointSample(const Ionflux::Mapping::PointSample& other)
: param(0.), coords(0), arcLength(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	refData->mmDebug = true;
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_CREATE, this));
	*this = other;
}

PointSample::PointSample(Ionflux::Mapping::MappingValue initParam, 
Ionflux::Mapping::Point* initCoords, Ionflux::Mapping::MappingValue 
initArcLength)
: param(initParam), coords(0), arcLength(initArcLength)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	refData->mmDebug = true;
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_CREATE, this));
	if (initCoords != 0)
	    setCoords(initCoords);
}

PointSample::~PointSample()
{
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_DELETE, this));
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue 
PointSample::getValue(Ionflux::Mapping::SamplingMode samplingMode)
{
	MappingValue result = 0.;
	if (samplingMode == SAMPLING_MODE_PARAM)
	    result = getParam();
	else
	if (samplingMode == SAMPLING_MODE_ARC_LENGTH)
	    result = getArcLength();
	else
	if ((samplingMode == SAMPLING_MODE_POINT_COORD_X) 
	    || (samplingMode == SAMPLING_MODE_POINT_COORD_Y) 
	    || (samplingMode == SAMPLING_MODE_POINT_COORD_Z))
	{
	    Point* p0 = getCoords();
	    if (p0 != 0)
	    {
	        if (samplingMode == SAMPLING_MODE_POINT_COORD_X)
	            result = p0->getCoord(0);
	        else 
	        if (samplingMode == SAMPLING_MODE_POINT_COORD_Y)
	            result = p0->getCoord(1);
	        else 
	        if (samplingMode == SAMPLING_MODE_POINT_COORD_Z)
	            result = p0->getCoord(2);
	    }
	} else
	{
	    std::ostringstream status;
	    status << "Unknown sampling mode (samplingMode = " 
	        << samplingMode << ")";
	    throw MappingError(getErrorString(status.str(), 
	        "getValue"));
	}
	return result;
}

std::string PointSample::getValueString() const
{
	std::ostringstream status;
	status << param << ", ";
	if (coords != 0)
	    status << "(" << coords->getValueString() << ")";
	else
	    status << "<none>";
	status << ", l = " << arcLength;
	return status.str();
}

void PointSample::setParam(Ionflux::Mapping::MappingValue newParam)
{
	param = newParam;
}

Ionflux::Mapping::MappingValue PointSample::getParam() const
{
    return param;
}

void PointSample::setCoords(Ionflux::Mapping::Point* newCoords)
{
	if (coords == newCoords)
		return;
    if (newCoords != 0)
        addLocalRef(newCoords);
	if (coords != 0)
		removeLocalRef(coords);
	coords = newCoords;
}

Ionflux::Mapping::Point* PointSample::getCoords() const
{
    return coords;
}

void PointSample::setArcLength(Ionflux::Mapping::MappingValue newArcLength)
{
	arcLength = newArcLength;
}

Ionflux::Mapping::MappingValue PointSample::getArcLength() const
{
    return arcLength;
}

Ionflux::Mapping::PointSample& PointSample::operator=(const 
Ionflux::Mapping::PointSample& other)
{
    if (this == &other)
        return *this;
    param = other.param;
    arcLength = other.arcLength;
    if (other.coords != 0)
        setCoords(other.coords->copy());
    else
        setCoords(0);
	return *this;
}

Ionflux::Mapping::PointSample* PointSample::copy() const
{
    PointSample* newPointSample = create();
    *newPointSample = *this;
    return newPointSample;
}

Ionflux::Mapping::PointSample* 
PointSample::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<PointSample*>(other);
}

Ionflux::Mapping::PointSample* 
PointSample::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    PointSample* newObject = new PointSample();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Mapping::PointSample* 
PointSample::create(Ionflux::Mapping::MappingValue initParam, 
Ionflux::Mapping::Point* initCoords, Ionflux::Mapping::MappingValue 
initArcLength, Ionflux::ObjectBase::IFObject* parentObject)
{
    PointSample* newObject = new PointSample(initParam, initCoords, 
    initArcLength);
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int PointSample::getMemSize() const
{
    return sizeof *this;
}

std::string PointSample::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string PointSample::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::ObjectBase::IFObject::getXMLAttributeData();
	if (d0.str().size() > 0)
	    d0 << " ";
	d0 << "t=\"" << param << "\"";
	if (d0.str().size() > 0)
	    d0 << " ";
	d0 << "l=\"" << arcLength << "\"";
	return d0.str();
}

void PointSample::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::ObjectBase::IFObject::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	std::string iws0 = Ionflux::ObjectBase::getIndent(indentLevel);
	bool haveBCData = false;
	if (d0.str().size() > 0)
	    haveBCData = true;
	bool xcFirst = true;
	if (!xcFirst || haveBCData)
	    d0 << "\n";
	target = d0.str();
}

void PointSample::loadFromXMLFile(const std::string& fileName, const 
std::string& elementName)
{
	std::string en0(elementName);
	if (en0.size() == 0)
	    en0 = getXMLElementName();
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, en0);
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
PointSample::getXMLObjectFactory()
{
	static Ionflux::Mapping::XMLUtils::PointSampleXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::Mapping::XMLUtils::PointSampleXMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 
            IFObject::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file PointSample.cpp
 * \brief Point sample implementation.
 */
