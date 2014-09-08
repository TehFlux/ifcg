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
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/VectorXMLFactory.hpp"

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

void Vector::cleanup()
{
	if (elements == 0)
	    return;
	delete[] elements;
	elements = 0;
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

void Vector::setElements(const Ionflux::GeoUtils::Vector& other, unsigned 
int sourceOffset, unsigned int targetOffset)
{
	unsigned int numElements0 = getNumElements();
	unsigned int numElements1 = other.getNumElements();
	unsigned int i = 0;
	while (((i + targetOffset) < numElements0) 
	    && ((i + sourceOffset) < numElements1))
	{
	    elements[i + targetOffset] = 
	        other.elements[i + sourceOffset];
	    i++;
	}
}

void Vector::setElements(double x0, double x1, double x2, double x3, double
x4, double x5, double x6, double x7, double x8, double x9, double x10, 
double x11, double x12)
{
	unsigned int ne0 = getNumElements();
	if (ne0 > 0)
	    setElement(0, x0);
	else
	    return;
	if (ne0 > 1)
	    setElement(1, x1);
	else
	    return;
	if (ne0 > 2)
	    setElement(2, x2);
	else
	    return;
	if (ne0 > 3)
	    setElement(3, x3);
	else
	    return;
	if (ne0 > 4)
	    setElement(4, x4);
	else
	    return;
	if (ne0 > 5)
	    setElement(5, x5);
	else
	    return;
	if (ne0 > 6)
	    setElement(6, x6);
	else
	    return;
	if (ne0 > 7)
	    setElement(7, x7);
	else
	    return;
	if (ne0 > 8)
	    setElement(8, x8);
	else
	    return;
	if (ne0 > 9)
	    setElement(9, x9);
	else
	    return;
	if (ne0 > 10)
	    setElement(10, x10);
	else
	    return;
	if (ne0 > 11)
	    setElement(11, x11);
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
	unsigned int oNumElements = other.getNumElements();
	if (numElements != oNumElements)
	    return false;
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

double Vector::length() const
{
	// TODO: Implementation.
	return norm();
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

Ionflux::GeoUtils::Vector& Vector::roundIP(unsigned int numDecimals)
{
	unsigned int numElements = getNumElements();
	double c0 = ::pow(10., numDecimals);
	for (unsigned int i = 0; i < numElements; i++)
	    elements[i] = ::round(elements[i] * c0) / c0;
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
	    throw GeoUtilsError(getErrorString(status.str(), "operator[]"));
	}
	return elements[index];
}

double Vector::operator*(const Ionflux::GeoUtils::Vector& other) const
{
	// TODO: Implementation.
	return dot(other);
}

unsigned int Vector::getNumElements() const
{
	// TODO: Implementation.
	return NUM_ELEMENTS;
}

void Vector::getElementSigns(Ionflux::ObjectBase::IntVector& target) const
{
	unsigned int numElements0 = getNumElements();
	for (unsigned int i = 0; i < numElements0; i++)
	{
	    if (elements[i] < 0.)
	        target.push_back(-1.);
	    else
	        target.push_back(1.);
	}
}

void Vector::getElementSigns(Ionflux::GeoUtils::Vector& target) const
{
	unsigned int numElements0 = getNumElements();
	unsigned int numElements1 = target.getNumElements();
	unsigned int i = 0;
	while ((i < numElements0) 
	    && (i < numElements1))
	{
	    if (elements[i] < 0.)
	        target.setElement(i, -1.);
	    else
	        target.setElement(i, 1.);
	    i++;
	}
}

std::string Vector::getValueStringF(unsigned int fieldWidth, unsigned int 
precision, const std::string& colSep) const
{
	std::ostringstream status;
	unsigned int numElements0 = getNumElements();
	bool e0 = true;
	for (unsigned int i = 0; i < numElements0; i++)
	{
	    if (!e0)
	        status << colSep;
	    else
	        e0 = false;
	    status << std::setw(fieldWidth) << std::setfill(' ') 
	        << std::setprecision(precision) << right 
	        << elements[i];
	}
	return status.str();
}

std::string Vector::getXMLAttributeDataValueString() const
{
	std::ostringstream status;
	unsigned int numElements = getNumElements();
	bool e0 = true;
	for (unsigned int i = 0; i < numElements; i++)
	{
	    if (!e0)
	        status << ",";
	    else
	        e0 = false;
	    status << elements[i];
	}
	return status.str();
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

unsigned int Vector::getMemSize() const
{
    return sizeof *this;
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
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, getXMLElementName());
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
Vector::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::VectorXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::VectorXMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 
            IFObject::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file Vector.cpp
 * \brief Vector implementation.
 */
