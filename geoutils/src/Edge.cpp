/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Edge.cpp                        Polygon edge (implementation).
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

#include "geoutils/Edge.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "geoutils/xmlutils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

EdgeClassInfo::EdgeClassInfo()
{
	name = "Edge";
	desc = "Polygon edge";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

EdgeClassInfo::~EdgeClassInfo()
{
}

// run-time type information instance constants
const EdgeClassInfo Edge::edgeClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Edge::CLASS_INFO = &Edge::edgeClassInfo;

const std::string Edge::XML_ELEMENT_NAME = "edge";

Edge::Edge()
: v0(0), v1(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Edge::Edge(const Ionflux::GeoUtils::Edge& other)
: v0(0), v1(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Edge::Edge(int initV0, int initV1)
: v0(initV0), v1(initV1)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Edge::Edge(const Ionflux::ObjectBase::IntVector& initVertices)
: v0(0), v1(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setVertices(initVertices);
}

Edge::~Edge()
{
	// TODO: Nothing ATM. ;-)
}

void Edge::setVertices(const Ionflux::ObjectBase::IntVector& newVertices)
{
	if (newVertices.size() == 0)
	    return;
	if (newVertices.size() >= 2)
	    v1 = newVertices[1];
	v0 = newVertices[0];
}

void Edge::getVertices(Ionflux::ObjectBase::IntVector& target) const
{
	target.clear();
	target.push_back(v0);
	target.push_back(v1);
}

int Edge::getVertex(int index) const
{
	// TODO: Implementation.
	return (*this)[index];;
}

Ionflux::ObjectBase::IntVector Edge::getVector() const
{
	IntVector result;
	result.push_back(v0);
	result.push_back(v1);
	return result;
}

void Edge::setVertex(int index, int value)
{
	if ((index < 0) || (index > 2))
	{
	    ostringstream message;
	    message << "Index out of range: " << index;
	    throw GeoUtilsError(message.str());
	}
	if (index == 0)
	    v0 = value;
	else 
	if (index == 1)
	    v1 = value;
}

bool Edge::operator==(const Ionflux::GeoUtils::Edge& other) const
{
	if (!((v0 == other.v0) && (v1 == other.v1)))
	        return false;
	return true;
}

bool Edge::operator!=(const Ionflux::GeoUtils::Edge& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

double Edge::operator[](int index) const
{
	if ((index < 0) || (index > 2))
	{
	    ostringstream message;
	    message << "Index out of range: " << index;
	    throw GeoUtilsError(message.str());
	}
	double result = 0.;
	if (index == 0)
	    result = v0;
	if (index == 1)
	    result = v1;
	return result;
}

std::string Edge::getValueString() const
{
	ostringstream status;
	status << v0 << ", " << v1;
	return status.str();
}

void Edge::setV0(int newV0)
{
	v0 = newV0;
}

int Edge::getV0() const
{
    return v0;
}

void Edge::setV1(int newV1)
{
	v1 = newV1;
}

int Edge::getV1() const
{
    return v1;
}

Ionflux::GeoUtils::Edge& Edge::operator=(const Ionflux::GeoUtils::Edge& 
other)
{
    if (this == &other)
        return *this;
    v0 = other.v0;
    v1 = other.v1;
	return *this;
}

Ionflux::GeoUtils::Edge* Edge::copy() const
{
    Edge* newEdge = create();
    *newEdge = *this;
    return newEdge;
}

Ionflux::GeoUtils::Edge* Edge::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Edge*>(other);
}

Ionflux::GeoUtils::Edge* Edge::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Edge* newObject = new Edge();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Edge* Edge::create(int initV0, int initV1, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Edge* newObject = new Edge(initV0, initV1);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Edge* Edge::create(const Ionflux::ObjectBase::IntVector&
initVertices, Ionflux::ObjectBase::IFObject* parentObject)
{
    Edge* newObject = new Edge(initVertices);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

std::string Edge::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Edge::getXMLAttributeData() const
{
	std::string a0(Ionflux::ObjectBase::IFObject::getXMLAttributeData());
	std::ostringstream d0;
	if (a0.size() > 0)
	    d0 << a0 << " ";
	d0 << "v0=\"" << v0 << "\"";
	d0 << " " << "v1=\"" << v1 << "\"";
	return d0.str();
}

void Edge::getXMLChildData(std::string& target, unsigned int indentLevel) 
const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::ObjectBase::IFObject::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void Edge::loadFromXMLFile(const std::string& fileName)
{
	std::string data;
	Ionflux::ObjectBase::readFile(fileName, data);
	/* <---- DEBUG ----- //
	std::cerr << "[Edge::loadFromXMLFile] data = " << data 
	    << std::endl;
	// <---- DEBUG ----- */
	Ionflux::GeoUtils::XMLUtils::getEdge(data, *this);
}

}

}

/** \file Edge.cpp
 * \brief Polygon edge implementation.
 */
