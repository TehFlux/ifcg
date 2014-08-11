/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NFaceSet.cpp                    N-face set (implementation).
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

#include "geoutils/NFaceSet.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/NFace.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

NFaceSetClassInfo::NFaceSetClassInfo()
{
	name = "NFaceSet";
	desc = "N-face set";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

NFaceSetClassInfo::~NFaceSetClassInfo()
{
}

// run-time type information instance constants
const NFaceSetClassInfo NFaceSet::nFaceSetClassInfo;
const Ionflux::ObjectBase::IFClassInfo* NFaceSet::CLASS_INFO = &NFaceSet::nFaceSetClassInfo;

NFaceSet::NFaceSet()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

NFaceSet::NFaceSet(const Ionflux::GeoUtils::NFaceSet& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

NFaceSet::~NFaceSet()
{
	clearNFaces();
	// TODO: Nothing ATM. ;-)
}

bool NFaceSet::isTriSet() const
{
	unsigned int numNFaces = getNumNFaces();
	unsigned int i = 0;
	while (i < numNFaces)
	{
	    NFace* cnf = getNFace(i);
	    if (cnf != 0)
	    {
	        if (!cnf->isTri())
	            return false;
	    }
	    i++;
	}
	return true;
}

bool NFaceSet::isQuadSet() const
{
	unsigned int numNFaces = getNumNFaces();
	unsigned int i = 0;
	while (i < numNFaces)
	{
	    NFace* cnf = getNFace(i);
	    if (cnf != 0)
	    {
	        if (!cnf->isQuad())
	            return false;
	    }
	    i++;
	}
	return true;
}

bool NFaceSet::isEdgeSet() const
{
	unsigned int numNFaces = getNumNFaces();
	unsigned int i = 0;
	while (i < numNFaces)
	{
	    NFace* cnf = getNFace(i);
	    if (cnf != 0)
	    {
	        if (!cnf->isEdge())
	            return false;
	    }
	    i++;
	}
	return true;
}

std::string NFaceSet::getValueString() const
{
	ostringstream status;
	bool e0 = true;
	for (NFaceVector::const_iterator i = nfaces.begin(); 
	    i != nfaces.end(); i++)
	{
	    if (!e0)
	        status << ", ";
	    else
	        e0 = false;
	    status << "(" << (*i)->getValueString() << ")";
	}
	if (nfaces.size() == 0)
	    status << "<none>";
	return status.str();
}

unsigned int NFaceSet::getNumNFaces() const
{
    return nfaces.size();
}

Ionflux::GeoUtils::NFace* NFaceSet::getNFace(unsigned int elementIndex) 
const
{
    if (elementIndex < nfaces.size())
		return nfaces[elementIndex];
	return 0;
}

int NFaceSet::findNFace(Ionflux::GeoUtils::NFace* needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::NFace* currentNFace = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < nfaces.size()))
	{
		currentNFace = nfaces[i];
		if (currentNFace == needle)
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

std::vector<Ionflux::GeoUtils::NFace*>& NFaceSet::getNFaces()
{
    return nfaces;
}

void NFaceSet::addNFace(Ionflux::GeoUtils::NFace* addElement)
{
	addLocalRef(addElement);
	nfaces.push_back(addElement);
}

Ionflux::GeoUtils::NFace* NFaceSet::addNFace()
{
	Ionflux::GeoUtils::NFace* o0 = NFace::create();
	addNFace(o0);
	return o0;
}

void NFaceSet::addNFaces(const std::vector<Ionflux::GeoUtils::NFace*>& 
newNFaces)
{
	for (std::vector<Ionflux::GeoUtils::NFace*>::const_iterator i = newNFaces.begin(); 
	    i != newNFaces.end(); i++)
	    addNFace(*i);
}

void NFaceSet::addNFaces(Ionflux::GeoUtils::NFaceSet* newNFaces)
{
	for (unsigned int i = 0; 
	    i < newNFaces->getNumNFaces(); i++)
	    addNFace(newNFaces->getNFace(i));
}

void NFaceSet::removeNFace(Ionflux::GeoUtils::NFace* removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::NFace* currentNFace = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < nfaces.size()))
	{
		currentNFace = nfaces[i];
		if (currentNFace == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		nfaces.erase(nfaces.begin() + i);
		if (currentNFace != 0)
			removeLocalRef(currentNFace);
	}
}

void NFaceSet::removeNFaceIndex(unsigned int removeIndex)
{
    if (removeIndex > nfaces.size())
        return;
	Ionflux::GeoUtils::NFace* e0 = nfaces[removeIndex];
    nfaces.erase(nfaces.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void NFaceSet::clearNFaces()
{
    std::vector<Ionflux::GeoUtils::NFace*>::iterator i;
	for (i = nfaces.begin(); i != nfaces.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	nfaces.clear();
}

Ionflux::GeoUtils::NFaceSet& NFaceSet::operator=(const 
Ionflux::GeoUtils::NFaceSet& other)
{
    if (this == &other)
        return *this;
    NFaceVector v0;
    for (NFaceVector::const_iterator i = other.nfaces.begin(); 
        i != other.nfaces.end(); i++)
        v0.push_back((*i)->copy());
    clearNFaces();
    addNFaces(v0);
	return *this;
}

Ionflux::GeoUtils::NFaceSet* NFaceSet::copy() const
{
    NFaceSet* newNFaceSet = create();
    *newNFaceSet = *this;
    return newNFaceSet;
}

Ionflux::GeoUtils::NFaceSet* 
NFaceSet::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<NFaceSet*>(other);
}

Ionflux::GeoUtils::NFaceSet* 
NFaceSet::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    NFaceSet* newObject = new NFaceSet();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int NFaceSet::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file NFaceSet.cpp
 * \brief N-face set implementation.
 */
