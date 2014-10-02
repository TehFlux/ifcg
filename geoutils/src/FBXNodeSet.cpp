/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FBXNodeSet.cpp                  FBX node set (implementation).
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

#include "geoutils/FBXNodeSet.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "ifobject/objectutils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/FBXNode.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

FBXNodeSetClassInfo::FBXNodeSetClassInfo()
{
	name = "FBXNodeSet";
	desc = "FBX node set";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

FBXNodeSetClassInfo::~FBXNodeSetClassInfo()
{
}

// run-time type information instance constants
const FBXNodeSetClassInfo FBXNodeSet::fBXNodeSetClassInfo;
const Ionflux::ObjectBase::IFClassInfo* FBXNodeSet::CLASS_INFO = &FBXNodeSet::fBXNodeSetClassInfo;

FBXNodeSet::FBXNodeSet()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

FBXNodeSet::FBXNodeSet(const Ionflux::GeoUtils::FBXNodeSet& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

FBXNodeSet::FBXNodeSet(Ionflux::GeoUtils::FBXNodeVector& initNodes)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addNodes(initNodes);
}

FBXNodeSet::~FBXNodeSet()
{
	clearNodes();
	// TODO: Nothing ATM. ;-)
}

unsigned int 
FBXNodeSet::findNodesByAttributeType(Ionflux::GeoUtils::FBXNodeAttributeType
t, Ionflux::GeoUtils::FBXNodeSet& target, bool recursive)
{
	unsigned int n0 = getNumNodes();
	unsigned int numNodes = 0;
	for (unsigned int i = 0; i < n0; i++)
	{
	    FBXNode* cn = getNode(i);
	    if (cn != 0)
	        numNodes += cn->findNodesByAttributeType(t, target, recursive);
	}
	return numNodes;
}

unsigned int FBXNodeSet::getNumNodes() const
{
    return nodes.size();
}

Ionflux::GeoUtils::FBXNode* FBXNodeSet::getNode(unsigned int elementIndex) 
const
{
    if (elementIndex < nodes.size())
		return nodes[elementIndex];
	return 0;
}

int FBXNodeSet::findNode(Ionflux::GeoUtils::FBXNode* needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::FBXNode* currentNode = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < nodes.size()))
	{
		currentNode = nodes[i];
		if (currentNode == needle)
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

std::vector<Ionflux::GeoUtils::FBXNode*>& FBXNodeSet::getNodes()
{
    return nodes;
}

void FBXNodeSet::addNode(Ionflux::GeoUtils::FBXNode* addElement)
{
	addLocalRef(addElement);
	nodes.push_back(addElement);
}

Ionflux::GeoUtils::FBXNode* FBXNodeSet::addNode()
{
	Ionflux::GeoUtils::FBXNode* o0 = FBXNode::create();
	addNode(o0);
	return o0;
}

void FBXNodeSet::addNodes(const std::vector<Ionflux::GeoUtils::FBXNode*>& 
newNodes)
{
	for (std::vector<Ionflux::GeoUtils::FBXNode*>::const_iterator i = newNodes.begin(); 
	    i != newNodes.end(); i++)
	    addNode(*i);
}

void FBXNodeSet::addNodes(Ionflux::GeoUtils::FBXNodeSet* newNodes)
{
	for (unsigned int i = 0; 
	    i < newNodes->getNumNodes(); i++)
	    addNode(newNodes->getNode(i));
}

void FBXNodeSet::removeNode(Ionflux::GeoUtils::FBXNode* removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::FBXNode* currentNode = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < nodes.size()))
	{
		currentNode = nodes[i];
		if (currentNode == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		nodes.erase(nodes.begin() + i);
		if (currentNode != 0)
			removeLocalRef(currentNode);
	}
}

void FBXNodeSet::removeNodeIndex(unsigned int removeIndex)
{
    if (removeIndex > nodes.size())
        return;
	Ionflux::GeoUtils::FBXNode* e0 = nodes[removeIndex];
    nodes.erase(nodes.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void FBXNodeSet::clearNodes()
{
    std::vector<Ionflux::GeoUtils::FBXNode*>::iterator i;
	for (i = nodes.begin(); i != nodes.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	nodes.clear();
}

Ionflux::GeoUtils::FBXNodeSet& FBXNodeSet::operator=(const 
Ionflux::GeoUtils::FBXNodeSet& other)
{
    if (this == &other)
        return *this;
    FBXNodeVector v0;
    for (FBXNodeVector::const_iterator i = other.nodes.begin(); 
        i != other.nodes.end(); i++)
    {
        FBXNode* n0 = Ionflux::ObjectBase::nullPointerCheck(*i, this, 
            "operator=", "FBX node");
        v0.push_back(n0->copy());
    }
    clearNodes();
    addNodes(v0);
	return *this;
}

Ionflux::GeoUtils::FBXNodeSet* FBXNodeSet::copy() const
{
    FBXNodeSet* newFBXNodeSet = create();
    *newFBXNodeSet = *this;
    return newFBXNodeSet;
}

Ionflux::GeoUtils::FBXNodeSet* 
FBXNodeSet::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<FBXNodeSet*>(other);
}

Ionflux::GeoUtils::FBXNodeSet* 
FBXNodeSet::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    FBXNodeSet* newObject = new FBXNodeSet();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::FBXNodeSet* 
FBXNodeSet::create(Ionflux::GeoUtils::FBXNodeVector& initNodes, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    FBXNodeSet* newObject = new FBXNodeSet(initNodes);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int FBXNodeSet::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file FBXNodeSet.cpp
 * \brief FBX node set implementation.
 */
