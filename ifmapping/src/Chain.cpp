/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Chain.cpp                       Chain mapping (implementation).
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

#include "ifmapping/Chain.hpp"
#include <sstream>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

ChainClassInfo::ChainClassInfo()
{
	name = "Chain";
	desc = "Chain mapping";
}

ChainClassInfo::~ChainClassInfo()
{
}

// run-time type information instance constants
const ChainClassInfo Chain::chainClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Chain::CLASS_INFO = &Chain::chainClassInfo;

Chain::Chain()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Chain::Chain(const Ionflux::Mapping::Chain& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Chain::Chain(const Ionflux::Mapping::MappingVector& initFuncs)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	for (MappingVector::const_iterator i = initFuncs.begin(); 
	    i != initFuncs.end(); i++)
	    addFunc(*i);
}

Chain::~Chain()
{
	clearFuncs();
	// TODO: Nothing ATM. ;-)
}

std::string Chain::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

Ionflux::Mapping::MappingValue Chain::call(Ionflux::Mapping::MappingValue 
value) const
{
	Ionflux::Mapping::MappingValue result = 1.;
	for (MappingVector::const_reverse_iterator i = funcs.rbegin(); 
	    i != funcs.rend(); i++)
	    result = (*(*i))(result);
	return result;
}

unsigned int Chain::getNumFuncs() const
{
    return funcs.size();
}

Ionflux::Mapping::Mapping* Chain::getFunc(unsigned int elementIndex) const
{
    if (elementIndex < funcs.size())
		return funcs[elementIndex];
	return 0;
}

int Chain::findFunc(Ionflux::Mapping::Mapping* needle, unsigned int 
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

std::vector<Ionflux::Mapping::Mapping*>& Chain::getFuncs()
{
    return funcs;
}

void Chain::addFunc(Ionflux::Mapping::Mapping* addElement)
{
	addLocalRef(addElement);
	funcs.push_back(addElement);
}

void Chain::removeFunc(Ionflux::Mapping::Mapping* removeElement)
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

void Chain::removeFuncIndex(unsigned int removeIndex)
{
    if (removeIndex > funcs.size())
        return;
	Ionflux::Mapping::Mapping* e0 = funcs[removeIndex];
    funcs.erase(funcs.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void Chain::clearFuncs()
{
    std::vector<Ionflux::Mapping::Mapping*>::iterator i;
	for (i = funcs.begin(); i != funcs.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	funcs.clear();
}

Ionflux::Mapping::Chain& Chain::operator=(const Ionflux::Mapping::Chain& 
other)
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

Ionflux::Mapping::Chain* Chain::copy() const
{
    Chain* newChain = create();
    *newChain = *this;
    return newChain;
}

Ionflux::Mapping::Chain* Chain::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Chain*>(other);
}

Ionflux::Mapping::Chain* Chain::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Chain* newObject = new Chain();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Chain::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Chain.cpp
 * \brief Chain mapping implementation.
 */
