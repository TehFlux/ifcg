/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polynomial.cpp                  Polynomial mapping (implementation).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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

#include "ifmapping/Polynomial.hpp"
#include <sstream>
#include "ifmapping/utils.hpp"
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

PolynomialClassInfo::PolynomialClassInfo()
{
	name = "Polynomial";
	desc = "Polynomial mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

PolynomialClassInfo::~PolynomialClassInfo()
{
}

// run-time type information instance constants
const PolynomialClassInfo Polynomial::polynomialClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Polynomial::CLASS_INFO = &Polynomial::polynomialClassInfo;

Polynomial::Polynomial()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Polynomial::Polynomial(const Ionflux::Mapping::Polynomial& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Polynomial::Polynomial(const Ionflux::Mapping::MappingValueVector& 
initCoefficients, Ionflux::Mapping::MappingValue initScale, 
Ionflux::Mapping::MappingValue initOffset, Ionflux::Mapping::Mapping* 
initFunc)
: ChainableMapping(initFunc, initScale, initOffset)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	coefficients = initCoefficients;
}

Polynomial::~Polynomial()
{
	clearCoefficients();
	// TODO: Nothing ATM. ;-)
}

void Polynomial::addCoefficients(const 
Ionflux::Mapping::MappingValueVector& newCoefficients)
{
	for (MappingValueVector::const_iterator i = 
	    newCoefficients.begin(); i != newCoefficients.end(); i++)
	    addCoefficient(*i);
}

std::string Polynomial::getString() const
{
	ostringstream status;
	status << getClassName() << "[";
	if (func != 0)
	    status << func->getString();
	else
	    status << "<none>";
	status << "; " << scale << ", " << offset << "; ";
	bool e0 = true;
	for (MappingValueVector::const_iterator i = coefficients.begin(); 
	    i != coefficients.end(); i++)
	{
	    if (!e0)
	        status << ", ";
	    else
	        e0 = false;
	    status << *i;
	}
	status << "; ";
	return status.str();
}

Ionflux::Mapping::MappingValue 
Polynomial::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	Ionflux::Mapping::MappingValue result = 0.;
	for (int i = coefficients.size() - 1; i >= 0; i--)
	    result = value * result + coefficients[i];
	return result;
}

unsigned int Polynomial::getNumCoefficients() const
{
    return coefficients.size();
}

Ionflux::Mapping::MappingValue Polynomial::getCoefficient(unsigned int 
elementIndex) const
{
    if (elementIndex < coefficients.size())
		return coefficients[elementIndex];
	return 0;
}

int Polynomial::findCoefficient(Ionflux::Mapping::MappingValue needle, 
unsigned int occurence) const
{
    bool found = false;
	Ionflux::Mapping::MappingValue currentCoefficient = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < coefficients.size()))
	{
		currentCoefficient = coefficients[i];
		if (currentCoefficient == needle)
        {
            if (occurence == 1)
			    found = true;
            else
                occurence--;
		} else
			i++;
	}
	if (found)
        return i;
	return -1;
}

std::vector<Ionflux::Mapping::MappingValue>& Polynomial::getCoefficients()
{
    return coefficients;
}

void Polynomial::addCoefficient(Ionflux::Mapping::MappingValue addElement)
{
	coefficients.push_back(addElement);
}

void Polynomial::removeCoefficient(Ionflux::Mapping::MappingValue 
removeElement)
{
    bool found = false;
	Ionflux::Mapping::MappingValue currentCoefficient = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < coefficients.size()))
	{
		currentCoefficient = coefficients[i];
		if (currentCoefficient == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		coefficients.erase(coefficients.begin() + i);
	}
}

void Polynomial::removeCoefficientIndex(unsigned int removeIndex)
{
    if (removeIndex > coefficients.size())
        return;
    coefficients.erase(coefficients.begin() + removeIndex);
}

void Polynomial::clearCoefficients()
{
    coefficients.clear();
}

Ionflux::Mapping::Polynomial& Polynomial::operator=(const 
Ionflux::Mapping::Polynomial& other)
{
    ChainableMapping::operator=(other);
    coefficients = other.coefficients;
	return *this;
}

Ionflux::Mapping::Polynomial* Polynomial::copy() const
{
    Polynomial* newPolynomial = create();
    *newPolynomial = *this;
    return newPolynomial;
}

Ionflux::Mapping::Polynomial* 
Polynomial::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Polynomial*>(other);
}

Ionflux::Mapping::Polynomial* 
Polynomial::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Polynomial* newObject = new Polynomial();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Polynomial::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Polynomial.cpp
 * \brief Polynomial mapping implementation.
 */
