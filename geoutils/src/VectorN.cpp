/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * VectorN.cpp                     Vector (N-D) (implementation).
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

#include "geoutils/VectorN.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "ifmapping/Linear.hpp"
#include "ifmapping/Cubic.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/LinearInterpolator.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/VectorNXMLFactory.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

VectorNClassInfo::VectorNClassInfo()
{
	name = "VectorN";
	desc = "Vector (N-D)";
	baseClassInfo.push_back(Ionflux::GeoUtils::Vector::CLASS_INFO);
}

VectorNClassInfo::~VectorNClassInfo()
{
}

// run-time type information instance constants
const VectorNClassInfo VectorN::vectorNClassInfo;
const Ionflux::ObjectBase::IFClassInfo* VectorN::CLASS_INFO = &VectorN::vectorNClassInfo;

const std::string VectorN::XML_ELEMENT_NAME = "vn";

VectorN::VectorN()
: numElements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

VectorN::VectorN(const Ionflux::GeoUtils::VectorN& other)
: numElements(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

VectorN::VectorN(unsigned int initNumElements)
: numElements(initNumElements)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	zero();
}

VectorN::VectorN(unsigned int initNumElements, double x0, double x1, double
x2, double x3, double x4, double x5, double x6, double x7, double x8, 
double x9, double x10, double x11, double x12)
: numElements(initNumElements)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	zero();
	setElements(x0, x1, x2, x3, x4, x5, x6, 
	    x7, x8, x9, x10, x11, x12);
}

VectorN::~VectorN()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::GeoUtils::VectorN VectorN::interpolate(const 
Ionflux::GeoUtils::VectorN& other, double t, 
Ionflux::GeoUtils::Interpolator* interp)
{
	bool ownInterp = false;
	if (interp == 0)
	{
	    ownInterp = true;
	    interp = Ionflux::GeoUtils::LinearInterpolator::create();
	    addLocalRef(interp);
	}
	unsigned int numElements = getNumElements();
	unsigned int oNumElements = other.getNumElements();
	if (numElements > oNumElements)
	{
	    std::ostringstream status;
	    status << "Vector size mismatch (this.numElements = " 
	        << numElements << ", other.numElements = " << oNumElements 
	        << ").";
	    throw GeoUtilsError(getErrorString(status.str(), 
	        "interpolate"));
	}
	VectorN result(numElements);
	for (unsigned int i = 0; i < numElements; i++)
	{
	    interp->setValues(elements[i], other.elements[i]);
	    result.elements[i] = (*interp)(t);
	}
	if (ownInterp)
	    removeLocalRef(interp);
	return result;
}

Ionflux::GeoUtils::VectorN VectorN::operator+(const 
Ionflux::GeoUtils::VectorN& other) const
{
	VectorN result(*this);
	result.addIP(other);
	return result;
}

Ionflux::GeoUtils::VectorN VectorN::operator-(const 
Ionflux::GeoUtils::VectorN& other) const
{
	VectorN result(*this);
	result.subtractIP(other);
	return result;
}

Ionflux::GeoUtils::VectorN VectorN::operator*(double c) const
{
	VectorN result(*this);
	result.multiplyIP(c);
	return result;
}

double VectorN::operator*(const Ionflux::GeoUtils::VectorN& other) const
{
	// TODO: Implementation.
	return dot(other);
}

Ionflux::GeoUtils::VectorN VectorN::operator/(double c) const
{
	VectorN result(*this);
	result.divideIP(c);
	return result;
}

Ionflux::GeoUtils::VectorN* VectorN::sample(const 
Ionflux::Mapping::Mapping& mapping, unsigned int numPoints, double t0, 
double t1)
{
	if (t1 < t0)
	{
	    std::ostringstream status;
	    status << "[Vector::sample] "
	        "Parameter t1 is smaller than parameter t0 (t0 = " << t0 
	        << ", t1 = " << t1 << ").";
	    throw GeoUtilsError(status.str());
	}
	VectorN* result = 0;
	if (numPoints == 1)
	{
	    result = VectorN::create(1, mapping(0.5 * (t1 - t0)));
	    return result;
	}
	result = VectorN::create(numPoints);
	double dt = 1. / (numPoints - 1);
	double t = t0;
	unsigned int k = 0;
	while ((t <= t1) 
	    && (k < numPoints))
	{
	    result->setElement(k, mapping(t));
	    t += dt;
	    k += 1;
	}
	return result;
}

Ionflux::GeoUtils::VectorN* VectorN::linear(unsigned int numPoints, double 
t0, double t1, Ionflux::Mapping::MappingValue lower, 
Ionflux::Mapping::MappingValue upper, Ionflux::Mapping::MappingValue scale,
Ionflux::Mapping::MappingValue offset)
{
	Ionflux::Mapping::Linear m(lower, upper, scale, offset);
	VectorN* result = VectorN::sample(m, numPoints, t0, t1);
	return result;
}

Ionflux::GeoUtils::VectorN* VectorN::cubic(unsigned int numPoints, double 
t0, double t1, Ionflux::Mapping::MappingValue lower, 
Ionflux::Mapping::MappingValue upper)
{
	Ionflux::Mapping::Cubic m(lower, upper);
	VectorN* result = VectorN::sample(m, numPoints, t0, t1);
	return result;
}

void VectorN::setNumElements(unsigned int newNumElements)
{
	numElements = newNumElements;
}

unsigned int VectorN::getNumElements() const
{
    return numElements;
}

Ionflux::GeoUtils::VectorN& VectorN::operator=(const 
Ionflux::GeoUtils::VectorN& other)
{
    if (this == &other)
        return *this;
    unsigned int tNumElements = getNumElements();
    unsigned int oNumElements = other.getNumElements();
    /* <---- DEBUG ----- //
    std::cerr << "[GeoUtils::VectorN::operator=] "
        "tNumElements = " << tNumElements << ", oNumElements = " 
        << oNumElements << std::endl;
    // ----- DEBUG ----> */
    if ((tNumElements != oNumElements)
        && (elements != 0))
    {
        delete[] elements;
        elements = 0;
    }
    numElements = oNumElements;
    Ionflux::GeoUtils::Vector::operator=(other);
	return *this;
}

Ionflux::GeoUtils::VectorN* VectorN::copy() const
{
    VectorN* newVectorN = create();
    *newVectorN = *this;
    return newVectorN;
}

Ionflux::GeoUtils::VectorN* VectorN::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<VectorN*>(other);
}

Ionflux::GeoUtils::VectorN* VectorN::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    VectorN* newObject = new VectorN();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::VectorN* VectorN::create(unsigned int initNumElements, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    VectorN* newObject = new VectorN(initNumElements);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::VectorN* VectorN::create(unsigned int initNumElements, 
double x0, double x1, double x2, double x3, double x4, double x5, double 
x6, double x7, double x8, double x9, double x10, double x11, double x12, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    VectorN* newObject = new VectorN(initNumElements, x0, x1, x2, x3, x4, 
    x5, x6, x7, x8, x9, x10, x11, x12);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int VectorN::getMemSize() const
{
    return sizeof *this;
}

std::string VectorN::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string VectorN::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::GeoUtils::Vector::getXMLAttributeData();
	if (d0.str().size() > 0)
	    d0 << " ";
	d0 << "n=\"" << numElements << "\"";
	return d0.str();
}

void VectorN::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::GeoUtils::Vector::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void VectorN::loadFromXMLFile(const std::string& fileName)
{
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, getXMLElementName());
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
VectorN::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::VectorNXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::VectorNXMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 0;
        bFac = Ionflux::GeoUtils::Vector::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

Ionflux::GeoUtils::VectorN operator*(double c, const 
Ionflux::GeoUtils::VectorN& v)
{
	// TODO: Implementation.
	return v * c;
}

}

}

/** \file VectorN.cpp
 * \brief Vector (N-D) implementation.
 */
