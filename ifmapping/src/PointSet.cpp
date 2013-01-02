/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PointSet.cpp                    Point set (implementation).
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

#include "ifmapping/PointSet.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <sstream>
#include "ifmapping/utils.hpp"
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

PointSetClassInfo::PointSetClassInfo()
{
	name = "PointSet";
	desc = "Point set";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

PointSetClassInfo::~PointSetClassInfo()
{
}

// run-time type information instance constants
const PointSetClassInfo PointSet::pointSetClassInfo;
const Ionflux::ObjectBase::IFClassInfo* PointSet::CLASS_INFO = &PointSet::pointSetClassInfo;

PointSet::PointSet()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

PointSet::PointSet(const Ionflux::Mapping::PointSet& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

PointSet::PointSet(const Ionflux::Mapping::PointVector& initPoints)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addPoints(initPoints);
}

PointSet::~PointSet()
{
	clearPoints();
	// TODO: Nothing ATM. ;-)
}

void PointSet::addPoints(const Ionflux::Mapping::PointVector& newPoints)
{
	for (PointVector::const_iterator i = newPoints.begin(); 
	    i != newPoints.end(); i++)
	    addPoint(*i);
}

void PointSet::addPoints(const Ionflux::Mapping::PointSet& other)
{
	for (unsigned int i = 0; i < other.points.size(); i++)
	    addPoint(other.points[i]);
}

std::string PointSet::getString() const
{
	ostringstream status;
	status << getClassName();
	return status.str();
}

unsigned int PointSet::getNumPoints() const
{
    return points.size();
}

Ionflux::Mapping::Point* PointSet::getPoint(unsigned int elementIndex) 
const
{
    if (elementIndex < points.size())
		return points[elementIndex];
	return 0;
}

int PointSet::findPoint(Ionflux::Mapping::Point* needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::Mapping::Point* currentPoint = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < points.size()))
	{
		currentPoint = points[i];
		if (currentPoint == needle)
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

std::vector<Ionflux::Mapping::Point*>& PointSet::getPoints()
{
    return points;
}

void PointSet::addPoint(Ionflux::Mapping::Point* addElement)
{
	addLocalRef(addElement);
	points.push_back(addElement);
}

void PointSet::removePoint(Ionflux::Mapping::Point* removeElement)
{
    bool found = false;
	Ionflux::Mapping::Point* currentPoint = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < points.size()))
	{
		currentPoint = points[i];
		if (currentPoint == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		points.erase(points.begin() + i);
		if (currentPoint != 0)
			removeLocalRef(currentPoint);
	}
}

void PointSet::removePointIndex(unsigned int removeIndex)
{
    if (removeIndex > points.size())
        return;
	Ionflux::Mapping::Point* e0 = points[removeIndex];
    points.erase(points.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void PointSet::clearPoints()
{
    std::vector<Ionflux::Mapping::Point*>::iterator i;
	for (i = points.begin(); i != points.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	points.clear();
}

Ionflux::Mapping::PointSet& PointSet::operator=(const 
Ionflux::Mapping::PointSet& other)
{
    PointVector v0;
    for (unsigned int i = 0; i < other.points.size(); i++)
    {
        Point* p0 = other.points[i];
        if (p0 != 0)
            v0.push_back(new Point(*p0));
        else
            v0.push_back(0);
    }
    clearPoints();
    addPoints(v0);
	return *this;
}

Ionflux::Mapping::PointSet* PointSet::copy() const
{
    PointSet* newPointSet = create();
    *newPointSet = *this;
    return newPointSet;
}

Ionflux::Mapping::PointSet* PointSet::upcast(Ionflux::ObjectBase::IFObject*
other)
{
    return dynamic_cast<PointSet*>(other);
}

Ionflux::Mapping::PointSet* PointSet::create(Ionflux::ObjectBase::IFObject*
parentObject)
{
    PointSet* newObject = new PointSet();
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

/** \file PointSet.cpp
 * \brief Point set implementation.
 */
