/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FaceData.cpp                    Face data (implementation).
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

#include "geoutils/FaceData.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/VectorSet.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "geoutils/xmlutils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

FaceDataClassInfo::FaceDataClassInfo()
{
	name = "FaceData";
	desc = "Face data";
}

FaceDataClassInfo::~FaceDataClassInfo()
{
}

// public member constants
const Ionflux::GeoUtils::FaceDataTypeID FaceData::TYPE_UNDEFINED = 0;
const Ionflux::GeoUtils::FaceDataTypeID FaceData::TYPE_TEX_COORD = 1;
const Ionflux::GeoUtils::FaceDataTypeID FaceData::TYPE_VERTEX_COLOR = 2;
const Ionflux::GeoUtils::FaceDataTypeID FaceData::TYPE_VERTEX_NORMAL = 3;

// run-time type information instance constants
const FaceDataClassInfo FaceData::faceDataClassInfo;
const Ionflux::ObjectBase::IFClassInfo* FaceData::CLASS_INFO = &FaceData::faceDataClassInfo;

const std::string FaceData::XML_ELEMENT_NAME = "facedata";

FaceData::FaceData()
: dataType(TYPE_UNDEFINED)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

FaceData::FaceData(const Ionflux::GeoUtils::FaceData& other)
: dataType(TYPE_UNDEFINED)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

FaceData::FaceData(Ionflux::GeoUtils::VectorVector& initVectors, 
Ionflux::GeoUtils::FaceDataTypeID initDataType)
: dataType(initDataType)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addVectors(initVectors);
}

FaceData::FaceData(Ionflux::GeoUtils::FaceDataTypeID initDataType)
: dataType(initDataType)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

FaceData::~FaceData()
{
	// TODO: Nothing ATM. ;-)
}

std::string FaceData::getValueString() const
{
	ostringstream status;
	status << getTypeIDString(dataType) << "; [" 
	    << VectorSet::getValueString() << "]";
	return status.str();
}

bool FaceData::hasType(Ionflux::GeoUtils::FaceDataTypeID typeID)
{
	// TODO: Implementation.
	return dataType == typeID;
}

std::string FaceData::getTypeIDString(Ionflux::GeoUtils::FaceDataTypeID 
typeID)
{
	if (typeID == TYPE_UNDEFINED)
	    return "TYPE_UNDEFINED";
	else
	if (typeID == TYPE_TEX_COORD)
	    return "TYPE_TEX_COORD";
	else
	if (typeID == TYPE_VERTEX_COLOR)
	    return "TYPE_VERTEX_COLOR";
	else
	if (typeID == TYPE_VERTEX_NORMAL)
	    return "TYPE_VERTEX_NORMAL";
	return "<unknown>";
}

void FaceData::setDataType(Ionflux::GeoUtils::FaceDataTypeID newDataType)
{
	dataType = newDataType;
}

Ionflux::GeoUtils::FaceDataTypeID FaceData::getDataType() const
{
	return dataType;
}

Ionflux::GeoUtils::FaceData& FaceData::operator=(const 
Ionflux::GeoUtils::FaceData& other)
{
    if (this == &other)
        return *this;
    VectorSet::operator=(other);
    dataType = other.dataType;
	return *this;
}

Ionflux::GeoUtils::FaceData* FaceData::copy() const
{
    FaceData* newFaceData = create();
    *newFaceData = *this;
    return newFaceData;
}

Ionflux::GeoUtils::FaceData* 
FaceData::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<FaceData*>(other);
}

Ionflux::GeoUtils::FaceData* 
FaceData::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    FaceData* newObject = new FaceData();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::FaceData* 
FaceData::create(Ionflux::GeoUtils::VectorVector& initVectors, 
Ionflux::GeoUtils::FaceDataTypeID initDataType, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    FaceData* newObject = new FaceData(initVectors, initDataType);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::FaceData* 
FaceData::create(Ionflux::GeoUtils::FaceDataTypeID initDataType, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    FaceData* newObject = new FaceData(initDataType);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

std::string FaceData::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string FaceData::getXMLAttributeData() const
{
	std::string a0(Ionflux::GeoUtils::VectorSet::getXMLAttributeData());
	std::ostringstream d0;
	if (a0.size() > 0)
	    d0 << a0 << " ";
	d0 << "datatype=\"" << dataType << "\"";
	return d0.str();
}

void FaceData::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::GeoUtils::VectorSet::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void FaceData::loadFromXMLFile(std::string& fileName)
{
	std::string data;
	Ionflux::ObjectBase::readFile(fileName, data);
	Ionflux::GeoUtils::XMLUtils::getFaceData(data, *this);
}

}

}

/** \file FaceData.cpp
 * \brief Face data implementation.
 */
