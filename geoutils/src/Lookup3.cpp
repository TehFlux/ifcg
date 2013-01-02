/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Lookup3.cpp                     Vector mapping: Lookup (implementation).
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

#include "geoutils/Lookup3.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "ifmapping/utils.hpp"
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;
using Ionflux::GeoUtils::Vector3;

namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

Lookup3ClassInfo::Lookup3ClassInfo()
{
	name = "Lookup3";
	desc = "Vector mapping: Lookup";
}

Lookup3ClassInfo::~Lookup3ClassInfo()
{
}

// public member constants
const unsigned int Lookup3::DEFAULT_NUM_ENTRIES = 100;
const Ionflux::Mapping::Range Lookup3::CLAMP_RANGE = { 0., 1. };

// run-time type information instance constants
const Lookup3ClassInfo Lookup3::lookup3ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Lookup3::CLASS_INFO = &Lookup3::lookup3ClassInfo;

Lookup3::Lookup3()
: source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Lookup3::Lookup3(const Ionflux::GeoUtils::Mapping::Lookup3& other)
: source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Lookup3::Lookup3(Ionflux::GeoUtils::Mapping::Vector3Mapping* initSource, 
unsigned int initNumEntries)
: source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setSource(initSource);
	update(initNumEntries);
}

Lookup3::~Lookup3()
{
	clearEntries();
	// TODO: Nothing ATM. ;-)
}

void Lookup3::update(unsigned int numEntries)
{
	clearEntries();
	if (source == 0)
	    throw GeoUtilsError("Source mapping not defined.");
	if (numEntries == 0)
	    return;
	if (numEntries == 1)
	    addEntry(new Vector3((*source)(0.5)));
	Ionflux::Mapping::MappingValue d = 1. / (numEntries - 1);
	for (unsigned int i = 0; i < numEntries; i++)
	    addEntry(new Vector3((*source)(i * d)));
}

void Lookup3::addEntries(const Ionflux::GeoUtils::Vector3Vector& 
newEntries, unsigned int numEntries)
{
	if (numEntries == 0)
	    numEntries = newEntries.size();
	unsigned int sourceNumEntries = newEntries.size();
	for (unsigned int i = 0; i < numEntries; i++)
	{
	    Vector3* v0 = newEntries[i % sourceNumEntries];
	    if (v0 == 0)
	        throw GeoUtilsError("Source vector is null.");
	    addEntry(new Vector3(*v0));
	}
}

Ionflux::GeoUtils::Vector3 Lookup3::call(Ionflux::Mapping::MappingValue 
value) const
{
	if (entries.size() == 0)
	    throw GeoUtilsError("Lookup table is empty.");
	unsigned int i = static_cast<unsigned int>(
	    Ionflux::Mapping::clamp(value, CLAMP_RANGE) * entries.size());
	if (i >= entries.size())
	    i = entries.size() - 1;
	Vector3* result = entries[i];
	if (result == 0)
	    throw GeoUtilsError("Result vector is null.");
	return *result;
}

std::string Lookup3::getString() const
{
	ostringstream status;
	status << getClassName() << "[";
	if (source != 0)
	    status << source->getString();
	else
	    status << "<none>";
	status << ", " << entries.size() << "]";
	return status.str();
}

unsigned int Lookup3::getNumEntries() const
{
    return entries.size();
}

Ionflux::GeoUtils::Vector3* Lookup3::getEntry(unsigned int elementIndex) 
const
{
    if (elementIndex < entries.size())
		return entries[elementIndex];
	return 0;
}

int Lookup3::findEntry(Ionflux::GeoUtils::Vector3* needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::Vector3* currentEntry = 0;
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

std::vector<Ionflux::GeoUtils::Vector3*>& Lookup3::getEntries()
{
    return entries;
}

void Lookup3::addEntry(Ionflux::GeoUtils::Vector3* addElement)
{
	addLocalRef(addElement);
	entries.push_back(addElement);
}

void Lookup3::removeEntry(Ionflux::GeoUtils::Vector3* removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::Vector3* currentEntry = 0;
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
		if (currentEntry != 0)
			removeLocalRef(currentEntry);
	}
}

void Lookup3::removeEntryIndex(unsigned int removeIndex)
{
    if (removeIndex > entries.size())
        return;
	Ionflux::GeoUtils::Vector3* e0 = entries[removeIndex];
    entries.erase(entries.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void Lookup3::clearEntries()
{
    std::vector<Ionflux::GeoUtils::Vector3*>::iterator i;
	for (i = entries.begin(); i != entries.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	entries.clear();
}

void Lookup3::setSource(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
newSource)
{
	if (source == newSource)
		return;
    if (newSource != 0)
        addLocalRef(newSource);
	if (source != 0)
		removeLocalRef(source);
	source = newSource;
}

Ionflux::GeoUtils::Mapping::Vector3Mapping* Lookup3::getSource() const
{
	return source;
}

Ionflux::GeoUtils::Mapping::Lookup3& Lookup3::operator=(const 
Ionflux::GeoUtils::Mapping::Lookup3& other)
{
    Vector3Mapping::operator=(other);
    setSource(other.source);
    Ionflux::GeoUtils::Vector3Vector v0;
    for (Ionflux::GeoUtils::Vector3Vector::const_iterator i = 
        other.entries.begin(); i != other.entries.end(); i++)
    {
        addLocalRef(*i);
        v0.push_back(*i);
    }
    clearEntries();
    for (Ionflux::GeoUtils::Vector3Vector::iterator i = v0.begin(); 
        i != v0.end(); i++)
    {
        addEntry(*i);
        removeLocalRef(*i);
    }
	return *this;
}

Ionflux::GeoUtils::Mapping::Lookup3* Lookup3::copy() const
{
    Lookup3* newLookup3 = create();
    *newLookup3 = *this;
    return newLookup3;
}

Ionflux::GeoUtils::Mapping::Lookup3* 
Lookup3::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Lookup3*>(other);
}

Ionflux::GeoUtils::Mapping::Lookup3* 
Lookup3::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Lookup3* newObject = new Lookup3();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

}

/** \file Lookup3.cpp
 * \brief Vector mapping: Lookup implementation.
 */
