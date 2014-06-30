/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Multiply.cpp                    Multiply mapping (implementation).
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

#include "ifmapping/Multiply.hpp"
#include <sstream>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

MultiplyClassInfo::MultiplyClassInfo()
{
	name = "Multiply";
	desc = "Multiply mapping";
}

MultiplyClassInfo::~MultiplyClassInfo()
{
}

// run-time type information instance constants
const MultiplyClassInfo Multiply::multiplyClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Multiply::CLASS_INFO = &Multiply::multiplyClassInfo;

Multiply::Multiply()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Multiply::Multiply(const Ionflux::Mapping::Multiply& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Multiply::Multiply(const Ionflux::Mapping::MappingVector& initFuncs)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	for (MappingVector::const_iterator i = initFuncs.begin(); 
	    i != initFuncs.end(); i++)
	    addFunc(*i);
}

Multiply::~Multiply()
{
	clearFuncs();
	// TODO: Nothing ATM. ;-)
}

std::string Multiply::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

Ionflux::Mapping::MappingValue 
Multiply::call(Ionflux::Mapping::MappingValue value) const
{
	Ionflux::Mapping::MappingValue result = 1.;
	for (MappingVector::const_iterator i = funcs.begin(); 
	    i != funcs.end(); i++)
	    result *= (*(*i))(value);
	return result;
}

unsigned int Multiply::getNumFuncs() const
{
    return funcs.size();
}

Ionflux::Mapping::Mapping* Multiply::getFunc(unsigned int elementIndex) 
const
{
    if (elementIndex < funcs.size())
		return funcs[elementIndex];
	return 0;
}

int Multiply::findFunc(Ionflux::Mapping::Mapping* needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::Mapping::Mapping* currentFunc = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < funcs.size()))
	{
		currentFunc = funcs[i];
		if (currentFunc == needle)
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

std::vector<Ionflux::Mapping::Mapping*>& Multiply::getFuncs()
{
    return funcs;
}

void Multiply::addFunc(Ionflux::Mapping::Mapping* addElement)
{
	addLocalRef(addElement);
	funcs.push_back(addElement);
}

void Multiply::removeFunc(Ionflux::Mapping::Mapping* removeElement)
{
    bool found = false;
	Ionflux::Mapping::Mapping* currentFunc = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < funcs.size()))
	{
		currentFunc = funcs[i];
		if (currentFunc == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		funcs.erase(funcs.begin() + i);
		if (currentFunc != 0)
			removeLocalRef(currentFunc);
	}
}

void Multiply::removeFuncIndex(unsigned int removeIndex)
{
    if (removeIndex > funcs.size())
        return;
	Ionflux::Mapping::Mapping* e0 = funcs[removeIndex];
    funcs.erase(funcs.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void Multiply::clearFuncs()
{
    std::vector<Ionflux::Mapping::Mapping*>::iterator i;
	for (i = funcs.begin(); i != funcs.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	funcs.clear();
}

Ionflux::Mapping::Multiply& Multiply::operator=(const 
Ionflux::Mapping::Multiply& other)
{
    MappingVector v0;
    for (MappingVector::const_iterator i = other.funcs.begin(); 
        i != other.funcs.end(); i++)
    {
        addLocalRef(*i);
        v0.push_back(*i);
    }
    clearFuncs();
    for (MappingVector::const_iterator i = v0.begin(); 
        i != v0.end(); i++)
    {
        addFunc(*i);
        removeLocalRef(*i);
    }
	return *this;
}

Ionflux::Mapping::Multiply* Multiply::copy() const
{
    Multiply* newMultiply = create();
    *newMultiply = *this;
    return newMultiply;
}

Ionflux::Mapping::Multiply* Multiply::upcast(Ionflux::ObjectBase::IFObject*
other)
{
    return dynamic_cast<Multiply*>(other);
}

Ionflux::Mapping::Multiply* Multiply::create(Ionflux::ObjectBase::IFObject*
parentObject)
{
    Multiply* newObject = new Multiply();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Multiply::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Multiply.cpp
 * \brief Multiply mapping implementation.
 */
