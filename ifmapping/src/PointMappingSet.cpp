/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PointMappingSet.cpp             PointMappingSet (implementation).
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

#include "ifmapping/PointMappingSet.hpp"
#include <sstream>
#include "ifmapping/MappingError.hpp"
#include "ifmapping/PointMapping.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

PointMappingSetClassInfo::PointMappingSetClassInfo()
{
	name = "PointMappingSet";
	desc = "PointMappingSet";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

PointMappingSetClassInfo::~PointMappingSetClassInfo()
{
}

// run-time type information instance constants
const PointMappingSetClassInfo PointMappingSet::pointMappingSetClassInfo;
const Ionflux::ObjectBase::IFClassInfo* PointMappingSet::CLASS_INFO = &PointMappingSet::pointMappingSetClassInfo;

PointMappingSet::PointMappingSet()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

PointMappingSet::PointMappingSet(const Ionflux::Mapping::PointMappingSet& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

PointMappingSet::PointMappingSet(const 
Ionflux::Mapping::PointMappingVector& initMappings)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addMappings(initMappings);
}

PointMappingSet::~PointMappingSet()
{
	clearMappings();
	// TODO: Nothing ATM. ;-)
}

void PointMappingSet::addMappings(const 
Ionflux::Mapping::PointMappingVector& newMappings)
{
	for (PointMappingVector::const_iterator i = newMappings.begin(); 
	    i != newMappings.end(); i++)
	    addMapping(*i);
}

std::string PointMappingSet::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

unsigned int PointMappingSet::getNumMappings() const
{
    return mappings.size();
}

Ionflux::Mapping::PointMapping* PointMappingSet::getMapping(unsigned int 
elementIndex) const
{
    if (elementIndex < mappings.size())
		return mappings[elementIndex];
	return 0;
}

int PointMappingSet::findMapping(Ionflux::Mapping::PointMapping* needle, 
unsigned int occurence) const
{
    bool found = false;
	Ionflux::Mapping::PointMapping* currentMapping = 0;
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

std::vector<Ionflux::Mapping::PointMapping*>& 
PointMappingSet::getMappings()
{
    return mappings;
}

void PointMappingSet::addMapping(Ionflux::Mapping::PointMapping* 
addElement)
{
	addLocalRef(addElement);
	mappings.push_back(addElement);
}

void PointMappingSet::removeMapping(Ionflux::Mapping::PointMapping* 
removeElement)
{
    bool found = false;
	Ionflux::Mapping::PointMapping* currentMapping = 0;
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

void PointMappingSet::removeMappingIndex(unsigned int removeIndex)
{
    if (removeIndex > mappings.size())
        return;
	Ionflux::Mapping::PointMapping* e0 = mappings[removeIndex];
    mappings.erase(mappings.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void PointMappingSet::clearMappings()
{
    std::vector<Ionflux::Mapping::PointMapping*>::iterator i;
	for (i = mappings.begin(); i != mappings.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	mappings.clear();
}

Ionflux::Mapping::PointMappingSet& PointMappingSet::operator=(const 
Ionflux::Mapping::PointMappingSet& other)
{
    PointMappingVector v0;
    for (PointMappingVector::const_iterator i = other.mappings.begin(); 
        i != other.mappings.end(); i++)
    {
        addLocalRef(*i);
        v0.push_back(*i);
    }
    clearMappings();
    for (PointMappingVector::const_iterator i = v0.begin(); 
        i != v0.end(); i++)
    {
        addMapping(*i);
        removeLocalRef(*i);
    }
	return *this;
}

Ionflux::Mapping::PointMappingSet* PointMappingSet::copy() const
{
    PointMappingSet* newPointMappingSet = create();
    *newPointMappingSet = *this;
    return newPointMappingSet;
}

Ionflux::Mapping::PointMappingSet* 
PointMappingSet::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<PointMappingSet*>(other);
}

Ionflux::Mapping::PointMappingSet* 
PointMappingSet::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    PointMappingSet* newObject = new PointMappingSet();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file PointMappingSet.cpp
 * \brief PointMappingSet implementation.
 */
