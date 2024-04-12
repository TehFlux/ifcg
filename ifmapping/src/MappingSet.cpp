/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * MappingSet.cpp                  MappingSet (implementation).
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

#include "ifmapping/MappingSet.hpp"
#include <sstream>
#include "ifmapping/MappingError.hpp"
#include "ifmapping/Mapping.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

MappingSetClassInfo::MappingSetClassInfo()
{
	name = "MappingSet";
	desc = "MappingSet";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

MappingSetClassInfo::~MappingSetClassInfo()
{
}

// run-time type information instance constants
const MappingSetClassInfo MappingSet::mappingSetClassInfo;
const Ionflux::ObjectBase::IFClassInfo* MappingSet::CLASS_INFO = &MappingSet::mappingSetClassInfo;

MappingSet::MappingSet()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

MappingSet::MappingSet(const Ionflux::Mapping::MappingSet& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

MappingSet::MappingSet(const Ionflux::Mapping::MappingVector& initMappings)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addMappings(initMappings);
}

MappingSet::~MappingSet()
{
	clearMappings();
	// TODO: Nothing ATM. ;-)
}

void MappingSet::addMappings(const Ionflux::Mapping::MappingVector& 
newMappings)
{
	for (MappingVector::const_iterator i = newMappings.begin(); 
	    i != newMappings.end(); i++)
	    addMapping(*i);
}

std::string MappingSet::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

unsigned int MappingSet::getNumMappings() const
{
    return mappings.size();
}

Ionflux::Mapping::Mapping* MappingSet::getMapping(unsigned int 
elementIndex) const
{
    if (elementIndex < mappings.size())
		return mappings[elementIndex];
	return 0;
}

int MappingSet::findMapping(Ionflux::Mapping::Mapping* needle, unsigned int
occurence) const
{
    bool found = false;
	Ionflux::Mapping::Mapping* currentMapping = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < mappings.size()))
	{
		currentMapping = mappings[i];
		if (currentMapping == needle)
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

std::vector<Ionflux::Mapping::Mapping*>& MappingSet::getMappings()
{
    return mappings;
}

void MappingSet::addMapping(Ionflux::Mapping::Mapping* addElement)
{
	addLocalRef(addElement);
	mappings.push_back(addElement);
}

void MappingSet::removeMapping(Ionflux::Mapping::Mapping* removeElement)
{
    bool found = false;
	Ionflux::Mapping::Mapping* currentMapping = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < mappings.size()))
	{
		currentMapping = mappings[i];
		if (currentMapping == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		mappings.erase(mappings.begin() + i);
		if (currentMapping != 0)
			removeLocalRef(currentMapping);
	}
}

void MappingSet::removeMappingIndex(unsigned int removeIndex)
{
    if (removeIndex > mappings.size())
        return;
	Ionflux::Mapping::Mapping* e0 = mappings[removeIndex];
    mappings.erase(mappings.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void MappingSet::clearMappings()
{
    std::vector<Ionflux::Mapping::Mapping*>::iterator i;
	for (i = mappings.begin(); i != mappings.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	mappings.clear();
}

Ionflux::Mapping::MappingSet& MappingSet::operator=(const 
Ionflux::Mapping::MappingSet& other)
{
    MappingVector v0;
    for (MappingVector::const_iterator i = other.mappings.begin(); 
        i != other.mappings.end(); i++)
    {
        addLocalRef(*i);
        v0.push_back(*i);
    }
    clearMappings();
    for (MappingVector::const_iterator i = v0.begin(); 
        i != v0.end(); i++)
    {
        addMapping(*i);
        removeLocalRef(*i);
    }
	return *this;
}

Ionflux::Mapping::MappingSet* MappingSet::copy() const
{
    MappingSet* newMappingSet = create();
    *newMappingSet = *this;
    return newMappingSet;
}

Ionflux::Mapping::MappingSet* 
MappingSet::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<MappingSet*>(other);
}

Ionflux::Mapping::MappingSet* 
MappingSet::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    MappingSet* newObject = new MappingSet();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int MappingSet::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file MappingSet.cpp
 * \brief MappingSet implementation.
 */
