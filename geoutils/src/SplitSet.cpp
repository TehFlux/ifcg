/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SplitSet.cpp                    Axis split set (implementation).
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

#include "geoutils/SplitSet.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

SplitSetClassInfo::SplitSetClassInfo()
{
	name = "SplitSet";
	desc = "Axis split set";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

SplitSetClassInfo::~SplitSetClassInfo()
{
}

// run-time type information instance constants
const SplitSetClassInfo SplitSet::splitSetClassInfo;
const Ionflux::ObjectBase::IFClassInfo* SplitSet::CLASS_INFO = &SplitSet::splitSetClassInfo;

SplitSet::SplitSet()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

SplitSet::SplitSet(const Ionflux::GeoUtils::SplitSet& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

SplitSet::~SplitSet()
{
	clearSplits();
	// TODO: Nothing ATM. ;-)
}

Ionflux::GeoUtils::SplitVector 
SplitSet::addSplits(Ionflux::GeoUtils::AxisID axis, unsigned int num)
{
	double step = 1. / (num + 1.);
	double s = step;
	SplitVector result;
	while (s < 1.)
	{
	    Split* sp0 = new Split(axis, s);
	    if (sp0 == 0)
	        throw GeoUtilsError("Could not allocate object.");
	    addSplit(sp0);
	    result.push_back(sp0);
	    s += step;
	}
	return result;
}

std::string SplitSet::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

unsigned int SplitSet::getNumSplits() const
{
    return splits.size();
}

Ionflux::GeoUtils::Split* SplitSet::getSplit(unsigned int elementIndex) 
const
{
    if (elementIndex < splits.size())
		return splits[elementIndex];
	return 0;
}

int SplitSet::findSplit(Ionflux::GeoUtils::Split* needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::Split* currentSplit = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < splits.size()))
	{
		currentSplit = splits[i];
		if (currentSplit == needle)
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

std::vector<Ionflux::GeoUtils::Split*>& SplitSet::getSplits()
{
    return splits;
}

void SplitSet::addSplit(Ionflux::GeoUtils::Split* addElement)
{
	addLocalRef(addElement);
	splits.push_back(addElement);
}

void SplitSet::removeSplit(Ionflux::GeoUtils::Split* removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::Split* currentSplit = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < splits.size()))
	{
		currentSplit = splits[i];
		if (currentSplit == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		splits.erase(splits.begin() + i);
		if (currentSplit != 0)
			removeLocalRef(currentSplit);
	}
}

void SplitSet::removeSplitIndex(unsigned int removeIndex)
{
    if (removeIndex > splits.size())
        return;
	Ionflux::GeoUtils::Split* e0 = splits[removeIndex];
    splits.erase(splits.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void SplitSet::clearSplits()
{
    std::vector<Ionflux::GeoUtils::Split*>::iterator i;
	for (i = splits.begin(); i != splits.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	splits.clear();
}

Ionflux::GeoUtils::SplitSet& SplitSet::operator=(const 
Ionflux::GeoUtils::SplitSet& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::GeoUtils::SplitSet* SplitSet::copy() const
{
    SplitSet* newSplitSet = create();
    *newSplitSet = *this;
    return newSplitSet;
}

Ionflux::GeoUtils::SplitSet* 
SplitSet::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<SplitSet*>(other);
}

Ionflux::GeoUtils::SplitSet* 
SplitSet::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    SplitSet* newObject = new SplitSet();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int SplitSet::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file SplitSet.cpp
 * \brief Axis split set implementation.
 */
