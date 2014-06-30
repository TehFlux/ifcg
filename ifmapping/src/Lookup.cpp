/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Lookup.cpp                      Lookup mapping (implementation).
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

#include "ifmapping/Lookup.hpp"
#include <cmath>
#include <sstream>
#include "ifmapping/utils.hpp"
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

LookupClassInfo::LookupClassInfo()
{
	name = "Lookup";
	desc = "Lookup mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

LookupClassInfo::~LookupClassInfo()
{
}

// public member constants
const unsigned int Lookup::DEFAULT_NUM_ENTRIES = 100;
const Ionflux::Mapping::Range Lookup::CLAMP_RANGE = { 0., 1. };

// run-time type information instance constants
const LookupClassInfo Lookup::lookupClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Lookup::CLASS_INFO = &Lookup::lookupClassInfo;

Lookup::Lookup()
: source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Lookup::Lookup(const Ionflux::Mapping::Lookup& other)
: source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Lookup::Lookup(Ionflux::Mapping::Mapping* initSource, unsigned int 
initNumEntries, Ionflux::Mapping::MappingValue initScale, 
Ionflux::Mapping::MappingValue initOffset, Ionflux::Mapping::Mapping* 
initFunc)
: ChainableMapping(initFunc, initScale, initOffset), source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setSource(source);
	update(initNumEntries);
}

Lookup::Lookup(const Ionflux::Mapping::MappingValueVector& initEntries, 
unsigned int initNumEntries, Ionflux::Mapping::Mapping* initSource, 
Ionflux::Mapping::MappingValue initScale, Ionflux::Mapping::MappingValue 
initOffset, Ionflux::Mapping::Mapping* initFunc)
: ChainableMapping(initFunc, initScale, initOffset), source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addEntries(initEntries, initNumEntries);
	setSource(initSource);
}

Lookup::~Lookup()
{
	clearEntries();
	// TODO: Nothing ATM. ;-)
}

void Lookup::update(unsigned int numEntries)
{
	clearEntries();
	if (source == 0)
	    throw MappingError("Source mapping not defined.");
	if (numEntries == 0)
	    return;
	if (numEntries == 1)
	    addEntry((*source)(0.5));
	Ionflux::Mapping::MappingValue d = 1. / (numEntries - 1);
	for (unsigned int i = 0; i < numEntries; i++)
	    addEntry((*source)(i * d));
}

void Lookup::addEntries(const Ionflux::Mapping::MappingValueVector& 
newEntries, unsigned int numEntries)
{
	if (numEntries == 0)
	    numEntries = newEntries.size();
	unsigned int sourceNumEntries = newEntries.size();
	for (unsigned int i = 0; i < numEntries; i++)
	    addEntry(newEntries[i % sourceNumEntries]);
}

Ionflux::Mapping::MappingValue 
Lookup::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	if (entries.size() == 0)
	    throw MappingError("Lookup table is empty.");
	unsigned int i = static_cast<unsigned int>(
	    Ionflux::Mapping::clamp(value, CLAMP_RANGE) * entries.size());
	if (i >= entries.size())
	    i = entries.size() - 1;
	return entries[i];
}

unsigned int Lookup::getNumEntries() const
{
    return entries.size();
}

Ionflux::Mapping::MappingValue Lookup::getEntry(unsigned int elementIndex) 
const
{
    if (elementIndex < entries.size())
		return entries[elementIndex];
	return 0;
}

int Lookup::findEntry(Ionflux::Mapping::MappingValue needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::Mapping::MappingValue currentEntry = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < entries.size()))
	{
		currentEntry = entries[i];
		if (currentEntry == needle)
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

std::vector<Ionflux::Mapping::MappingValue>& Lookup::getEntries()
{
    return entries;
}

void Lookup::addEntry(Ionflux::Mapping::MappingValue addElement)
{
	entries.push_back(addElement);
}

void Lookup::removeEntry(Ionflux::Mapping::MappingValue removeElement)
{
    bool found = false;
	Ionflux::Mapping::MappingValue currentEntry = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < entries.size()))
	{
		currentEntry = entries[i];
		if (currentEntry == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		entries.erase(entries.begin() + i);
	}
}

void Lookup::removeEntryIndex(unsigned int removeIndex)
{
    if (removeIndex > entries.size())
        return;
    entries.erase(entries.begin() + removeIndex);
}

void Lookup::clearEntries()
{
    entries.clear();
}

void Lookup::setSource(Ionflux::Mapping::Mapping* newSource)
{
	if (source == newSource)
		return;
    if (newSource != 0)
        addLocalRef(newSource);
	if (source != 0)
		removeLocalRef(source);
	source = newSource;
}

Ionflux::Mapping::Mapping* Lookup::getSource() const
{
    return source;
}

Ionflux::Mapping::Lookup& Lookup::operator=(const Ionflux::Mapping::Lookup&
other)
{
    ChainableMapping::operator=(other);
    MappingValueVector v0 = other.entries;
    clearEntries();
    for (Ionflux::Mapping::MappingValueVector::iterator i =  v0.begin(); 
        i != v0.end(); i++)
        addEntry(*i);
    setSource(other.source);
	return *this;
}

Ionflux::Mapping::Lookup* Lookup::copy() const
{
    Lookup* newLookup = create();
    *newLookup = *this;
    return newLookup;
}

Ionflux::Mapping::Lookup* Lookup::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Lookup*>(other);
}

Ionflux::Mapping::Lookup* Lookup::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Lookup* newObject = new Lookup();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Lookup::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Lookup.cpp
 * \brief Lookup mapping implementation.
 */
