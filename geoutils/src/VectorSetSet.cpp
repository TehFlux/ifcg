/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * VectorSetSet.cpp                Set of vector sets (implementation).
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

#include "geoutils/VectorSetSet.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/VectorSet.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "geoutils/xmlutils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

VectorSetSetClassInfo::VectorSetSetClassInfo()
{
	name = "VectorSetSet";
	desc = "Set of vector sets";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

VectorSetSetClassInfo::~VectorSetSetClassInfo()
{
}

// run-time type information instance constants
const VectorSetSetClassInfo VectorSetSet::vectorSetSetClassInfo;
const Ionflux::ObjectBase::IFClassInfo* VectorSetSet::CLASS_INFO = &VectorSetSet::vectorSetSetClassInfo;

const std::string VectorSetSet::XML_ELEMENT_NAME = "vectorsetset";

VectorSetSet::VectorSetSet()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

VectorSetSet::VectorSetSet(const Ionflux::GeoUtils::VectorSetSet& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

VectorSetSet::VectorSetSet(Ionflux::GeoUtils::VectorSetVector& 
initVectorSets)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addVectorSets(initVectorSets);
}

VectorSetSet::~VectorSetSet()
{
	clearVectorSets();
	// TODO: Nothing ATM. ;-)
}

bool VectorSetSet::operator==(const Ionflux::GeoUtils::VectorSetSet& other)
const
{
	if (vectorSets.size() != other.vectorSets.size())
	    return false;
	for (unsigned int i = 0; i < vectorSets.size(); i++)
	{
	    VectorSet* vs0 = vectorSets[i];
	    VectorSet* vs1 = other.vectorSets[i];
	    if ((vs0 != 0) && (vs1 != 0))
	    {
	        if (*vs0 != *vs1)
	            return false;
	    } else
	        return false;
	}
	return true;
}

bool VectorSetSet::operator!=(const Ionflux::GeoUtils::VectorSetSet& other)
const
{
	// TODO: Implementation.
	return !(*this == other);
}

std::string VectorSetSet::getValueString() const
{
	ostringstream status;
	bool e0 = true;
	for (VectorSetVector::const_iterator i = vectorSets.begin(); 
	    i != vectorSets.end(); i++)
	{
	    if (!e0)
	        status << ", ";
	    else
	        e0 = false;
	    status << "[" << (*i)->getValueString() << "]";
	}
	if (vectorSets.size() == 0)
	    status << "<none>";
	return status.str();
}

unsigned int VectorSetSet::getNumVectorSets() const
{
    return vectorSets.size();
}

Ionflux::GeoUtils::VectorSet* VectorSetSet::getVectorSet(unsigned int 
elementIndex) const
{
    if (elementIndex < vectorSets.size())
		return vectorSets[elementIndex];
	return 0;
}

int VectorSetSet::findVectorSet(Ionflux::GeoUtils::VectorSet* needle, 
unsigned int occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::VectorSet* currentVectorSet = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < vectorSets.size()))
	{
		currentVectorSet = vectorSets[i];
		if (currentVectorSet == needle)
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

std::vector<Ionflux::GeoUtils::VectorSet*>& VectorSetSet::getVectorSets()
{
    return vectorSets;
}

void VectorSetSet::addVectorSet(Ionflux::GeoUtils::VectorSet* addElement)
{
	addLocalRef(addElement);
	vectorSets.push_back(addElement);
}

Ionflux::GeoUtils::VectorSet* VectorSetSet::addVectorSet()
{
	Ionflux::GeoUtils::VectorSet* o0 = VectorSet::create();
	addVectorSet(o0);
	return o0;
}

void VectorSetSet::addVectorSets(const 
std::vector<Ionflux::GeoUtils::VectorSet*>& newVectorSets)
{
	for (std::vector<Ionflux::GeoUtils::VectorSet*>::const_iterator i = newVectorSets.begin(); 
	    i != newVectorSets.end(); i++)
	    addVectorSet(*i);
}

void VectorSetSet::addVectorSets(Ionflux::GeoUtils::VectorSetSet* 
newVectorSets)
{
	for (unsigned int i = 0; 
	    i < newVectorSets->getNumVectorSets(); i++)
	    addVectorSet(newVectorSets->getVectorSet(i));
}

void VectorSetSet::removeVectorSet(Ionflux::GeoUtils::VectorSet* 
removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::VectorSet* currentVectorSet = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < vectorSets.size()))
	{
		currentVectorSet = vectorSets[i];
		if (currentVectorSet == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		vectorSets.erase(vectorSets.begin() + i);
		if (currentVectorSet != 0)
			removeLocalRef(currentVectorSet);
	}
}

void VectorSetSet::removeVectorSetIndex(unsigned int removeIndex)
{
    if (removeIndex > vectorSets.size())
        return;
	Ionflux::GeoUtils::VectorSet* e0 = vectorSets[removeIndex];
    vectorSets.erase(vectorSets.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void VectorSetSet::clearVectorSets()
{
    std::vector<Ionflux::GeoUtils::VectorSet*>::iterator i;
	for (i = vectorSets.begin(); i != vectorSets.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	vectorSets.clear();
}

Ionflux::GeoUtils::VectorSetSet& VectorSetSet::operator=(const 
Ionflux::GeoUtils::VectorSetSet& other)
{
    if (this == &other)
        return *this;
    VectorSetVector v0;
    for (VectorSetVector::const_iterator i = other.vectorSets.begin(); 
        i != other.vectorSets.end(); i++)
        v0.push_back((*i)->copy());
    clearVectorSets();
    addVectorSets(v0);
	return *this;
}

Ionflux::GeoUtils::VectorSetSet* VectorSetSet::copy() const
{
    VectorSetSet* newVectorSetSet = create();
    *newVectorSetSet = *this;
    return newVectorSetSet;
}

Ionflux::GeoUtils::VectorSetSet* 
VectorSetSet::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<VectorSetSet*>(other);
}

Ionflux::GeoUtils::VectorSetSet* 
VectorSetSet::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    VectorSetSet* newObject = new VectorSetSet();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::VectorSetSet* 
VectorSetSet::create(Ionflux::GeoUtils::VectorSetVector& initVectorSets, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    VectorSetSet* newObject = new VectorSetSet(initVectorSets);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

std::string VectorSetSet::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string VectorSetSet::getXMLAttributeData() const
{
	std::string a0(Ionflux::ObjectBase::IFObject::getXMLAttributeData());
	std::ostringstream d0;
	if (a0.size() > 0)
	    d0 << a0;
	return d0.str();
}

void VectorSetSet::getXMLChildData(std::string& target, unsigned int 
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
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0(vectorSets, "vectorsetvec", "", 
        indentLevel, "pname=\"vector_sets\"");
    xcFirst = false;
	target = d0.str();
}

void VectorSetSet::loadFromXMLFile(const std::string& fileName)
{
	std::string data;
	Ionflux::ObjectBase::readFile(fileName, data);
	// <---- DEBUG ----- //
	std:cerr << "[VectorSetSet::loadFromXMLFile] data = " << data 
	    << std::endl;
	// <---- DEBUG ----- */
	Ionflux::GeoUtils::XMLUtils::getVectorSetSet(data, *this);
}

}

}

/** \file VectorSetSet.cpp
 * \brief Set of vector sets implementation.
 */
