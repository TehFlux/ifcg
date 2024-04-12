/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector3MappingSet.cpp           Vector3MappingSet (implementation).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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

#include "geoutils/Vector3MappingSet.hpp"
#include <sstream>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;
using Ionflux::GeoUtils::Mapping::Vector3Mapping;

namespace Ionflux
{

namespace GeoUtils
{

Vector3MappingSetClassInfo::Vector3MappingSetClassInfo()
{
	name = "Vector3MappingSet";
	desc = "Vector3MappingSet";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

Vector3MappingSetClassInfo::~Vector3MappingSetClassInfo()
{
}

// run-time type information instance constants
const Vector3MappingSetClassInfo Vector3MappingSet::vector3MappingSetClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Vector3MappingSet::CLASS_INFO = &Vector3MappingSet::vector3MappingSetClassInfo;

Vector3MappingSet::Vector3MappingSet()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Vector3MappingSet::Vector3MappingSet(const Ionflux::GeoUtils::Vector3MappingSet& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Vector3MappingSet::Vector3MappingSet(const 
Ionflux::GeoUtils::Vector3MappingVector& initMappings)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addMappings(initMappings);
}

Vector3MappingSet::~Vector3MappingSet()
{
	clearMappings();
	// TODO: Nothing ATM. ;-)
}

void Vector3MappingSet::addMappings(const 
Ionflux::GeoUtils::Vector3MappingVector& newMappings)
{
	for (Vector3MappingVector::const_iterator i = newMappings.begin(); 
	    i != newMappings.end(); i++)
	    addMapping(*i);
}

std::string Vector3MappingSet::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

unsigned int Vector3MappingSet::getNumMappings() const
{
    return mappings.size();
}

Ionflux::GeoUtils::Mapping::Vector3Mapping* 
Vector3MappingSet::getMapping(unsigned int elementIndex) const
{
    if (elementIndex < mappings.size())
		return mappings[elementIndex];
	return 0;
}

int 
Vector3MappingSet::findMapping(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
needle, unsigned int occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::Mapping::Vector3Mapping* currentMapping = 0;
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

std::vector<Ionflux::GeoUtils::Mapping::Vector3Mapping*>& 
Vector3MappingSet::getMappings()
{
    return mappings;
}

void 
Vector3MappingSet::addMapping(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
addElement)
{
	addLocalRef(addElement);
	mappings.push_back(addElement);
}

void 
Vector3MappingSet::removeMapping(Ionflux::GeoUtils::Mapping::Vector3Mapping*
removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::Mapping::Vector3Mapping* currentMapping = 0;
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

void Vector3MappingSet::removeMappingIndex(unsigned int removeIndex)
{
    if (removeIndex > mappings.size())
        return;
	Ionflux::GeoUtils::Mapping::Vector3Mapping* e0 = mappings[removeIndex];
    mappings.erase(mappings.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void Vector3MappingSet::clearMappings()
{
    std::vector<Ionflux::GeoUtils::Mapping::Vector3Mapping*>::iterator i;
	for (i = mappings.begin(); i != mappings.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	mappings.clear();
}

Ionflux::GeoUtils::Vector3MappingSet& Vector3MappingSet::operator=(const 
Ionflux::GeoUtils::Vector3MappingSet& other)
{
    Vector3MappingVector v0;
    for (Vector3MappingVector::const_iterator i = other.mappings.begin(); 
        i != other.mappings.end(); i++)
    {
        addLocalRef(*i);
        v0.push_back(*i);
    }
    clearMappings();
    for (Vector3MappingVector::const_iterator i = v0.begin(); 
        i != v0.end(); i++)
    {
        addMapping(*i);
        removeLocalRef(*i);
    }
	return *this;
}

Ionflux::GeoUtils::Vector3MappingSet* Vector3MappingSet::copy() const
{
    Vector3MappingSet* newVector3MappingSet = create();
    *newVector3MappingSet = *this;
    return newVector3MappingSet;
}

Ionflux::GeoUtils::Vector3MappingSet* 
Vector3MappingSet::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Vector3MappingSet*>(other);
}

Ionflux::GeoUtils::Vector3MappingSet* 
Vector3MappingSet::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Vector3MappingSet* newObject = new Vector3MappingSet();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Vector3MappingSet::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Vector3MappingSet.cpp
 * \brief Vector3MappingSet implementation.
 */
