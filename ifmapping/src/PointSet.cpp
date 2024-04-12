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

#include "ifmapping/PointSet.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <sstream>
#include "ifmapping/utils.hpp"
#include "ifmapping/MappingError.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "ifmapping/xmlutils.hpp"
#include "ifmapping/xmlio/PointSetXMLFactory.hpp"

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
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

PointSetClassInfo::~PointSetClassInfo()
{
}

// run-time type information instance constants
const PointSetClassInfo PointSet::pointSetClassInfo;
const Ionflux::ObjectBase::IFClassInfo* PointSet::CLASS_INFO = &PointSet::pointSetClassInfo;

const std::string PointSet::XML_ELEMENT_NAME = "pointset";

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

std::string PointSet::getSVGPathData(const Ionflux::Mapping::CoordinateID 
imagePlaneNormal, unsigned int startIndex, unsigned int numPoints) const
{
	std::ostringstream result;
	bool first = true;
	unsigned int numPoints0 = getNumPoints();
	unsigned int numPoints1 = numPoints;
	if ((numPoints1 == 0) 
	    || (numPoints1 > numPoints0))
	    numPoints1 = numPoints0;
	unsigned int k = startIndex;
	while (k < numPoints1)
	{
	    Point* p0 = getPoint(k);
	    if (p0 != 0)
	    {
	        if (!first)
	            result << " ";
	        result << p0->getSVGPathData(imagePlaneNormal);
	        first = false;
	    }
	    k++;
	}
	return result.str();
}

std::string PointSet::getValueString() const
{
	ostringstream status;
	bool e0 = true;
	for (PointVector::const_iterator i = points.begin(); 
	    i != points.end(); i++)
	{
	    if (!e0)
	        status << ", ";
	    else
	        e0 = false;
	    status << "(" << (*i)->getValueString() << ")";
	}
	if (points.size() == 0)
	    status << "<none>";
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

Ionflux::Mapping::Point* PointSet::addPoint()
{
	Ionflux::Mapping::Point* o0 = Point::create();
	addPoint(o0);
	return o0;
}

void PointSet::addPoints(const std::vector<Ionflux::Mapping::Point*>& 
newPoints)
{
	for (std::vector<Ionflux::Mapping::Point*>::const_iterator i = newPoints.begin(); 
	    i != newPoints.end(); i++)
	    addPoint(*i);
}

void PointSet::addPoints(Ionflux::Mapping::PointSet* newPoints)
{
	for (unsigned int i = 0; 
	    i < newPoints->getNumPoints(); i++)
	    addPoint(newPoints->getPoint(i));
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
            v0.push_back(p0->copy());
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

Ionflux::Mapping::PointSet* PointSet::create(const 
Ionflux::Mapping::PointVector& initPoints, Ionflux::ObjectBase::IFObject* 
parentObject)
{
    PointSet* newObject = new PointSet(initPoints);
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int PointSet::getMemSize() const
{
    return sizeof *this;
}

std::string PointSet::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string PointSet::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::ObjectBase::IFObject::getXMLAttributeData();
	return d0.str();
}

void PointSet::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::ObjectBase::IFObject::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	std::string iws0 = Ionflux::ObjectBase::getIndent(indentLevel);
	bool haveBCData = false;
	if (d0.str().size() > 0)
	    haveBCData = true;
	bool xcFirst = true;
	if (!xcFirst || haveBCData)
	    d0 << "\n";
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0(points, "pointvec", "", 
        indentLevel, "pname=\"points\"");
    xcFirst = false;
	target = d0.str();
}

void PointSet::loadFromXMLFile(const std::string& fileName, const 
std::string& elementName)
{
	std::string en0(elementName);
	if (en0.size() == 0)
	    en0 = getXMLElementName();
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, en0);
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
PointSet::getXMLObjectFactory()
{
	static Ionflux::Mapping::XMLUtils::PointSetXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::Mapping::XMLUtils::PointSetXMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 
            IFObject::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file PointSet.cpp
 * \brief Point set implementation.
 */
