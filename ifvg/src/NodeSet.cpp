/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeSet.cpp                     Node set (implementation).
 * ========================================================================== */

#include "ifvg/NodeSet.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "ifvg/utils.hpp"
#include "ifvg/IFVGError.hpp"
#include "ifvg/Node.hpp"

using namespace std;

namespace Ionflux
{

namespace VolGfx
{

NodeSetClassInfo::NodeSetClassInfo()
{
	name = "NodeSet";
	desc = "Node set";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

NodeSetClassInfo::~NodeSetClassInfo()
{
}

// run-time type information instance constants
const NodeSetClassInfo NodeSet::nodeSetClassInfo;
const Ionflux::ObjectBase::IFClassInfo* NodeSet::CLASS_INFO = &NodeSet::nodeSetClassInfo;

NodeSet::NodeSet()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

NodeSet::NodeSet(const Ionflux::VolGfx::NodeSet& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

NodeSet::~NodeSet()
{
	clearNodes();
	// TODO: Nothing ATM. ;-)
}

std::string NodeSet::getValueString() const
{
	ostringstream status;
	bool e0 = true;
	for (NodeVector::const_iterator i = nodes.begin(); 
	    i != nodes.end(); i++)
	{
	    if (!e0)
	        status << ", ";
	    else
	        e0 = false;
	    status << "(" << (*i)->getValueString() << ")";
	}
	if (nodes.size() == 0)
	    status << "<none>";
	return status.str();
}

unsigned int NodeSet::getNumNodes() const
{
    return nodes.size();
}

Ionflux::VolGfx::Node* NodeSet::getNode(unsigned int elementIndex) const
{
    if (elementIndex < nodes.size())
		return nodes[elementIndex];
	return 0;
}

int NodeSet::findNode(Ionflux::VolGfx::Node* needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::VolGfx::Node* currentNode = 0;
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

std::vector<Ionflux::VolGfx::Node*>& NodeSet::getNodes()
{
    return nodes;
}

void NodeSet::addNode(Ionflux::VolGfx::Node* addElement)
{
	addLocalRef(addElement);
	nodes.push_back(addElement);
}

Ionflux::VolGfx::Node* NodeSet::addNode()
{
	Ionflux::VolGfx::Node* o0 = Node::create();
	addNode(o0);
	return o0;
}

void NodeSet::addNodes(const std::vector<Ionflux::VolGfx::Node*>& newNodes)
{
	for (std::vector<Ionflux::VolGfx::Node*>::const_iterator i = newNodes.begin(); 
	    i != newNodes.end(); i++)
	    addNode(*i);
}

void NodeSet::addNodes(Ionflux::VolGfx::NodeSet* newNodes)
{
	for (unsigned int i = 0; 
	    i < newNodes->getNumNodes(); i++)
	    addNode(newNodes->getNode(i));
}

void NodeSet::removeNode(Ionflux::VolGfx::Node* removeElement)
{
    bool found = false;
	Ionflux::VolGfx::Node* currentNode = 0;
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

void NodeSet::removeNodeIndex(unsigned int removeIndex)
{
    if (removeIndex > nodes.size())
        return;
	Ionflux::VolGfx::Node* e0 = nodes[removeIndex];
    nodes.erase(nodes.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void NodeSet::clearNodes()
{
    std::vector<Ionflux::VolGfx::Node*>::iterator i;
	for (i = nodes.begin(); i != nodes.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	nodes.clear();
}

Ionflux::VolGfx::NodeSet& NodeSet::operator=(const 
Ionflux::VolGfx::NodeSet& other)
{
    if (this == &other)
        return *this;
    NodeVector v0;
    for (NodeVector::const_iterator i = other.nodes.begin(); 
        i != other.nodes.end(); i++)
        v0.push_back((*i)->copy());
    clearNodes();
    addNodes(v0);
	return *this;
}

Ionflux::VolGfx::NodeSet* NodeSet::copy() const
{
    NodeSet* newNodeSet = create();
    *newNodeSet = *this;
    return newNodeSet;
}

Ionflux::VolGfx::NodeSet* NodeSet::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<NodeSet*>(other);
}

Ionflux::VolGfx::NodeSet* NodeSet::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    NodeSet* newObject = new NodeSet();
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int NodeSet::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file NodeSet.cpp
 * \brief Node set implementation.
 */
