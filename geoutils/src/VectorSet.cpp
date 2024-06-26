/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * VectorSet.cpp                   Vector set (implementation).
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

#include "geoutils/VectorSet.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Vector.hpp"
#include "geoutils/MatrixMN.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/VectorSetXMLFactory.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

VectorSetClassInfo::VectorSetClassInfo()
{
	name = "VectorSet";
	desc = "Vector set";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

VectorSetClassInfo::~VectorSetClassInfo()
{
}

// run-time type information instance constants
const VectorSetClassInfo VectorSet::vectorSetClassInfo;
const Ionflux::ObjectBase::IFClassInfo* VectorSet::CLASS_INFO = &VectorSet::vectorSetClassInfo;

const std::string VectorSet::XML_ELEMENT_NAME = "vectorset";

VectorSet::VectorSet()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

VectorSet::VectorSet(const Ionflux::GeoUtils::VectorSet& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

VectorSet::VectorSet(Ionflux::GeoUtils::VectorVector& initVectors)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addVectors(initVectors);
}

VectorSet::~VectorSet()
{
	clearVectors();
	// TODO: Nothing ATM. ;-)
}

void VectorSet::makeOrientationsConsistent(Ionflux::GeoUtils::Vector* 
flipData, double t)
{
	unsigned int numVecs0 = getNumVectors();
	/* Calculate flipping cost for both cases.
	   Cost matrix:
	     column 0: cost if first vector is flipped
	     column 1: cost if first vector is not flipped
	 */
	MatrixMN m0(numVecs0, 2);
	// Total cost for both cases.
	double tc0 = 0.;
	double tc1 = 0.;
	for (unsigned int i = 0; i < numVecs0; i++)
	{
	    Vector* v0 = getVector(i);
	    if (i == 0)
	    {
	        // first vector
	        m0.setElement(i, 0, 0.);
	        m0.setElement(i, 1, 1.);
	        tc1 += 1.;
	    } else 
	    {
	        Vector* v1 = getVector(i - 1);
	        double o0 = v0->dot(*v1);
	        double c0 = m0.getElement(i - 1, 0);
	        double c1 = m0.getElement(i - 1, 1);
	        double vv0 = 0.;
	        double vv1 = 0.;
	        if (lt(o0, 0., t))
	        {
	            /* Default orientation is inconsistent: 
	               either one of the vectors needs to be flipped. */
	            if (c0 == 0.)
	                vv0 = 1.;
	            else
	                vv0 = 0.;
	            if (c1 == 0.)
	                vv1 = 1.;
	            else
	                vv1 = 0.;
	        } else
	        {
	            /* Default orientation is consistent: 
	               flip both of the vectors, or none of them. */
	            if (c0 == 0.)
	                vv0 = 0.;
	            else
	                vv0 = 1.;
	            if (c1 == 0.)
	                vv1 = 0.;
	            else
	                vv1 = 1.;
	        }
	        m0.setElement(i, 0, vv0);
	        m0.setElement(i, 1, vv1);
	        if (vv0 == 1.)
	            tc0 += 1.;
	        if (vv1 == 1.)
	            tc1 += 1.;
	    }
	}
	// Flip vectors according to best case.
	unsigned int col0 = 0;
	if (tc1 < tc0)
	    col0 = 1;
	for (unsigned int i = 0; i < numVecs0; i++)
	{
	    Vector* v0 = getVector(i);
	    if (m0.getElement(i, col0) == 1.)
	        v0->flipIP();
	}
	if (flipData != 0)
	    m0.getCol(col0, *flipData);
}

void VectorSet::getCentroid(Ionflux::GeoUtils::Vector& target) const
{
	unsigned int numVectors0 = getNumVectors();
	for (unsigned int i = 0; i < numVectors0; i++)
	{
	    Vector* v0 = getVector(i);
	    if (v0 != 0)
	        target.addIP(*v0);
	}
	target.multiplyIP(1. / numVectors0);
}

bool VectorSet::operator==(const Ionflux::GeoUtils::VectorSet& other) const
{
	if (vectors.size() != other.vectors.size())
	    return false;
	for (unsigned int i = 0; i < vectors.size(); i++)
	{
	    Vector* v0 = vectors[i];
	    Vector* v1 = other.vectors[i];
	    if ((v0 != 0) && (v1 != 0))
	    {
	        if (*v0 != *v1)
	            return false;
	    } else
	        return false;
	}
	return true;
}

bool VectorSet::operator!=(const Ionflux::GeoUtils::VectorSet& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

std::string VectorSet::getValueStringF(unsigned int fieldWidth, unsigned 
int precision, const std::string& colSep, const std::string& rowSep, const 
std::string& rowPrefix) const
{
	std::ostringstream status;
	unsigned int numVectors0 = getNumVectors();
	bool e0 = true;
	for (unsigned int i = 0; i < numVectors0; i++)
	{
	    Vector* v0 = getVector(i);
	    if (v0 != 0)
	    {
	        if (!e0)
	            status << rowSep;
	        else
	            e0 = false;
	        if (rowPrefix != "")
	            status << rowPrefix;
	        status << v0->getValueStringF(fieldWidth, precision, colSep);
	    }
	}
	return status.str();
}

std::string VectorSet::getValueString() const
{
	ostringstream status;
	bool e0 = true;
	for (VectorVector::const_iterator i = vectors.begin(); 
	    i != vectors.end(); i++)
	{
	    if (!e0)
	        status << ", ";
	    else
	        e0 = false;
	    status << "(" << (*i)->getValueString() << ")";
	}
	if (vectors.size() == 0)
	    status << "<none>";
	return status.str();
}

unsigned int VectorSet::getNumVectors() const
{
    return vectors.size();
}

Ionflux::GeoUtils::Vector* VectorSet::getVector(unsigned int elementIndex) 
const
{
    if (elementIndex < vectors.size())
		return vectors[elementIndex];
	return 0;
}

int VectorSet::findVector(Ionflux::GeoUtils::Vector* needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::Vector* currentVector = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < vectors.size()))
	{
		currentVector = vectors[i];
		if (currentVector == needle)
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

std::vector<Ionflux::GeoUtils::Vector*>& VectorSet::getVectors()
{
    return vectors;
}

void VectorSet::addVector(Ionflux::GeoUtils::Vector* addElement)
{
	addLocalRef(addElement);
	vectors.push_back(addElement);
}

Ionflux::GeoUtils::Vector* VectorSet::addVector()
{
	Ionflux::GeoUtils::Vector* o0 = Vector::create();
	addVector(o0);
	return o0;
}

void VectorSet::addVectors(const std::vector<Ionflux::GeoUtils::Vector*>& 
newVectors)
{
	for (std::vector<Ionflux::GeoUtils::Vector*>::const_iterator i = newVectors.begin(); 
	    i != newVectors.end(); i++)
	    addVector(*i);
}

void VectorSet::addVectors(Ionflux::GeoUtils::VectorSet* newVectors)
{
	for (unsigned int i = 0; 
	    i < newVectors->getNumVectors(); i++)
	    addVector(newVectors->getVector(i));
}

void VectorSet::removeVector(Ionflux::GeoUtils::Vector* removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::Vector* currentVector = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < vectors.size()))
	{
		currentVector = vectors[i];
		if (currentVector == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		vectors.erase(vectors.begin() + i);
		if (currentVector != 0)
			removeLocalRef(currentVector);
	}
}

void VectorSet::removeVectorIndex(unsigned int removeIndex)
{
    if (removeIndex > vectors.size())
        return;
	Ionflux::GeoUtils::Vector* e0 = vectors[removeIndex];
    vectors.erase(vectors.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void VectorSet::clearVectors()
{
    std::vector<Ionflux::GeoUtils::Vector*>::iterator i;
	for (i = vectors.begin(); i != vectors.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	vectors.clear();
}

Ionflux::GeoUtils::VectorSet& VectorSet::operator=(const 
Ionflux::GeoUtils::VectorSet& other)
{
    if (this == &other)
        return *this;
    VectorVector v0;
    for (VectorVector::const_iterator i = other.vectors.begin(); 
        i != other.vectors.end(); i++)
        v0.push_back((*i)->copy());
    clearVectors();
    addVectors(v0);
	return *this;
}

Ionflux::GeoUtils::VectorSet* VectorSet::copy() const
{
    VectorSet* newVectorSet = create();
    *newVectorSet = *this;
    return newVectorSet;
}

Ionflux::GeoUtils::VectorSet* 
VectorSet::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<VectorSet*>(other);
}

Ionflux::GeoUtils::VectorSet* 
VectorSet::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    VectorSet* newObject = new VectorSet();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::VectorSet* 
VectorSet::create(Ionflux::GeoUtils::VectorVector& initVectors, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    VectorSet* newObject = new VectorSet(initVectors);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int VectorSet::getMemSize() const
{
    return sizeof *this;
}

std::string VectorSet::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string VectorSet::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::ObjectBase::IFObject::getXMLAttributeData();
	return d0.str();
}

void VectorSet::getXMLChildData(std::string& target, unsigned int 
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
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0(vectors, "vectorvec", "", 
        indentLevel, "pname=\"vectors\"");
    xcFirst = false;
	target = d0.str();
}

void VectorSet::loadFromXMLFile(const std::string& fileName, const 
std::string& elementName)
{
	std::string en0(elementName);
	if (en0.size() == 0)
	    en0 = getXMLElementName();
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, en0);
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
VectorSet::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::VectorSetXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::VectorSetXMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 
            IFObject::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file VectorSet.cpp
 * \brief Vector set implementation.
 */
