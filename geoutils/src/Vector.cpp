/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector.cpp                      Vector (implementation).
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

#include "geoutils/Vector.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/utils.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "geoutils/xmlutils.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

VectorClassInfo::VectorClassInfo()
{
	name = "Vector";
	desc = "Vector";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

VectorClassInfo::~VectorClassInfo()
{
}

// public member constants
const unsigned int Vector::NUM_ELEMENTS = 0;

// run-time type information instance constants
const VectorClassInfo Vector::vectorClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Vector::CLASS_INFO = &Vector::vectorClassInfo;

const std::string Vector::XML_ELEMENT_NAME = "v";

Vector::Vector()
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Vector::Vector(const Ionflux::GeoUtils::Vector& other)
: elements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Vector::~Vector()
{
	if (elements != 0)
	    delete[] elements;
	elements = 0;
}

void Vector::initElements()
{
	if (elements == 0)
	{
	    unsigned int tNumElements = getNumElements();
	    /* <---- DEBUG ----- //
	    std::cerr << "[Vector::initElements] "
	        "Allocating " << tNumElements << " elements." << std::endl;
	    // ----- DEBUG ----> */
	    elements = new double[tNumElements];
	    if (elements == 0)
	        throw GeoUtilsError(getErrorString(
	            "Could not allocate element vector.", "initElements"));
	}
}

void Vector::zero()
{
	if (elements == 0)
	    initElements();
	unsigned int numElements = getNumElements();
	for (unsigned int i = 0; i < numElements; i++)
	    elements[i] = 0.;
}

void Vector::setElements(const Ionflux::ObjectBase::DoubleVector& 
newElements)
{
	unsigned int numElements = getNumElements();
	unsigned int i = 0;
	while ((i < numElements) 
	    && (i < newElements.size()))
	{
	    elements[i] = newElements[i];
	    i++;
	}
}

void Vector::getElements(Ionflux::ObjectBase::DoubleVector& target) const
{
	target.clear();
	unsigned int numElements = getNumElements();
	for (unsigned int i = 0; i < numElements; i++)
	    target.push_back(elements[i]);
}

double Vector::getElement(unsigned int index) const
{
	// TODO: Implementation.
	return (*this)[index];;
}

void Vector::setElement(unsigned int index, double value)
{
	unsigned int numElements = getNumElements();
	if (index >= numElements)
	{
	    std::ostringstream status;
	    status << "Index out of range: " << index;
	    throw GeoUtilsError(getErrorString(status.str(), "setElement"));
	}
	elements[index] = value;
}

bool Vector::eq(const Ionflux::GeoUtils::Vector& other, double t) const
{
	unsigned int numElements = getNumElements();
	for (unsigned int i = 0; i < numElements; i++)
	    if (!Ionflux::GeoUtils::eq(elements[i], other.elements[i], t))
	        return false;
	return true;
}

double Vector::dot(const Ionflux::GeoUtils::Vector& other) const
{
	unsigned int numElements = getNumElements();
	unsigned int oNumElements = other.getNumElements();
	if (numElements != oNumElements)
	{
	    std::ostringstream status;
	    status << "Vector size mismatch (numElements = " << numElements 
	        << ", other.numElements = " << oNumElements << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "dot"));
	}
	double result = 0.;
	for (unsigned int i = 0; i < numElements; i++)
	    result += (elements[i] * other.elements[i]);
	return result;
}

double Vector::norm() const
{
	unsigned int numElements = getNumElements();
	double result = 0.;
	for (unsigned int i = 0; i < numElements; i++)
	    result += (elements[i] * elements[i]);
	return ::sqrt(result);
}

Ionflux::GeoUtils::Vector& Vector::normalizeIP()
{
	// TODO: Implementation.
	return divideIP(norm());
}

Ionflux::GeoUtils::Vector& Vector::multiplyIP(double c)
{
	unsigned int numElements = getNumElements();
	for (unsigned int i = 0; i < numElements; i++)
	    elements[i] = c * elements[i];
	return *this;
}

Ionflux::GeoUtils::Vector& Vector::divideIP(double c)
{
	unsigned int numElements = getNumElements();
	for (unsigned int i = 0; i < numElements; i++)
	    elements[i] = elements[i] / c;
	return *this;
}

Ionflux::GeoUtils::Vector& Vector::flipIP()
{
	unsigned int numElements = getNumElements();
	for (unsigned int i = 0; i < numElements; i++)
	    elements[i] = -elements[i];
	return *this;
}

Ionflux::GeoUtils::Vector& Vector::multiplyIP(const 
Ionflux::GeoUtils::Vector& other)
{
	unsigned int numElements = getNumElements();
	unsigned int oNumElements = other.getNumElements();
	if (numElements != oNumElements)
	{
	    std::ostringstream status;
	    status << "Vector size mismatch (numElements = " << numElements 
	        << ", other.numElements = " << oNumElements << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "multiplyIP"));
	}
	for (unsigned int i = 0; i < numElements; i++)
	    elements[i] = elements[i] * other.elements[i];
	return *this;
}

Ionflux::GeoUtils::Vector& Vector::subtractIP(const 
Ionflux::GeoUtils::Vector& other)
{
	unsigned int numElements = getNumElements();
	unsigned int oNumElements = other.getNumElements();
	if (numElements != oNumElements)
	{
	    std::ostringstream status;
	    status << "Vector size mismatch (numElements = " << numElements 
	        << ", other.numElements = " << oNumElements << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "subtractIP"));
	}
	for (unsigned int i = 0; i < numElements; i++)
	    elements[i] = elements[i] - other.elements[i];
	return *this;
}

Ionflux::GeoUtils::Vector& Vector::addIP(const Ionflux::GeoUtils::Vector& 
other)
{
	unsigned int numElements = getNumElements();
	unsigned int oNumElements = other.getNumElements();
	if (numElements != oNumElements)
	{
	    std::ostringstream status;
	    status << "Vector size mismatch (numElements = " << numElements 
	        << ", other.numElements = " << oNumElements << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "addIP"));
	}
	for (unsigned int i = 0; i < numElements; i++)
	    elements[i] = elements[i] + other.elements[i];
	return *this;
}

bool Vector::operator==(const Ionflux::GeoUtils::Vector& other) const
{
	unsigned int numElements = getNumElements();
	for (unsigned int i = 0; i < numElements; i++)
	{
	    if (elements[i] != other.elements[i])
	        return false;
	}
	return true;
}

bool Vector::operator!=(const Ionflux::GeoUtils::Vector& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

double Vector::operator[](unsigned int index) const
{
	unsigned int numElements = getNumElements();
	if ((index < 0) 
	    || (index > numElements))
	{
	    std::ostringstream status;
	    status << "Index out of range: " << index;
	    throw GeoUtilsError(getErrorString(status.str(), "setElement"));
	}
	return elements[index];
}

double Vector::operator*(const Ionflux::GeoUtils::Vector& other) const
{
	// TODO: Implementation.
	return dot(other);
}

std::string Vector::getValueString() const
{
	std::ostringstream status;
	unsigned int numElements = getNumElements();
	bool e0 = true;
	for (unsigned int i = 0; i < numElements; i++)
	{
	    if (!e0)
	        status << ", ";
	    else
	        e0 = false;
	    status << elements[i];
	}
	return status.str();
}

unsigned int Vector::getNumElements() const
{
	// TODO: Implementation.
	return NUM_ELEMENTS;
}

Ionflux::GeoUtils::Vector& Vector::operator=(const 
Ionflux::GeoUtils::Vector& other)
{
    if (this == &other)
        return *this;
    unsigned int tNumElements = getNumElements();
    unsigned int oNumElements = other.getNumElements();
    /* <---- DEBUG ----- //
    std::cerr << "[Vector::operator=] "
        "tNumElements = " << tNumElements << ", oNumElements = " 
        << oNumElements << std::endl;
    // ----- DEBUG ----> */
    initElements();
    unsigned int i = 0;
    while (i < tNumElements)
    {
        if (i < oNumElements)
            elements[i] = other.elements[i];
        else
            elements[i] = 0.;
        i++;
    }
	return *this;
}

Ionflux::GeoUtils::Vector* Vector::copy() const
{
    Vector* newVector = create();
    *newVector = *this;
    return newVector;
}

Ionflux::GeoUtils::Vector* Vector::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Vector*>(other);
}

Ionflux::GeoUtils::Vector* Vector::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Vector* newObject = new Vector();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

std::string Vector::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Vector::getXMLAttributeData() const
{
    std::string a0(Ionflux::ObjectBase::IFObject::getXMLAttributeData());
    std::ostringstream d0;
    if (a0.size() > 0)
        d0 << a0 << " ";
    d0 << "d=\"";
    unsigned int numElements = getNumElements();
    bool e0 = true;
    for (unsigned int i = 0; i < numElements; i++)
    {
        if (!e0)
            d0 << Ionflux::ObjectBase::DEFAULT_COORD_SEPARATOR;
        else
            e0 = false;
        d0 << elements[i];
    }
    d0 << "\"";
    return d0.str();
}

void Vector::getXMLChildData(std::string& target, unsigned int indentLevel)
const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::ObjectBase::IFObject::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void Vector::loadFromXMLFile(const std::string& fileName)
{
	std::string data;
	Ionflux::ObjectBase::readFile(fileName, data);
	/* <---- DEBUG ----- //
	std::cerr << "[Vector::loadFromXMLFile] data = " << data 
	    << std::endl;
	// <---- DEBUG ----- */
	Ionflux::GeoUtils::XMLUtils::getVector(data, *this);
}

}

}

/** \file Vector.cpp
 * \brief Vector implementation.
 */
