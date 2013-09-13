/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TransformGraph.cpp              Transform graph (implementation).
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

#include "geoutils/TransformGraph.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cmath>
#include <cstdlib>
#include <climits>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <set>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

TransformGraphClassInfo::TransformGraphClassInfo()
{
	name = "TransformGraph";
	desc = "Transform graph";
}

TransformGraphClassInfo::~TransformGraphClassInfo()
{
}

// public member constants
const unsigned int TransformGraph::NODE_INDEX_LAST = UINT_MAX;

// run-time type information instance constants
const TransformGraphClassInfo TransformGraph::transformGraphClassInfo;
const Ionflux::ObjectBase::IFClassInfo* TransformGraph::CLASS_INFO = &TransformGraph::transformGraphClassInfo;

TransformGraph::TransformGraph()
: source(0), drain(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

TransformGraph::TransformGraph(const Ionflux::GeoUtils::TransformNodes::TransformGraph& other)
: source(0), drain(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

TransformGraph::~TransformGraph()
{
	clearInputs();
	clearOutputs();
	clearConnections();
	clearNodes();
	// TODO: Nothing ATM. ;-)
}

void TransformGraph::process()
{
	/* Nothing to be done here, all processing is done 
	       by the drain node. */
}

void 
TransformGraph::addLinked(Ionflux::GeoUtils::TransformNodes::TransformNode*
newNode)
{
	addNode(newNode);
	std::set<TransformNode*> exclude;
	for (TransformNodeVector::iterator i = nodes.begin(); 
	    i != nodes.end(); i++)
	    exclude.insert(*i);
	TransformNodeVector v0;
	newNode->getLinkedInputs(v0);
	for (TransformNodeVector::iterator i = nodes.begin(); 
	    i != nodes.end(); i++)
	{
	    if (exclude.find(*i) == exclude.end())
	    {
	        // Node does not yet exist with the graph, add it.
	        exclude.insert(*i);
	        addNode(*i);
	    }
	}
}

void TransformGraph::clear()
{
	source = 0;
	drain = 0;
	for (ConnectionVector::iterator i = connections.begin(); 
	    i != connections.end(); i++)
	    if (*i != 0)
	        removeLocalRef(*i);
	connections.clear();
	for (TransformNodeVector::iterator i = nodes.begin(); 
	    i != nodes.end(); i++)
	    if (*i != 0)
	        removeLocalRef(*i);
	nodes.clear();
}

void TransformGraph::addNodes(Ionflux::GeoUtils::TransformNodeVector& 
newNodes)
{
	for (TransformNodeVector::iterator i = newNodes.begin(); 
	    i != newNodes.end(); i++)
	    addNode(*i);
}

Ionflux::GeoUtils::TransformNodes::Connection* 
TransformGraph::findConnection(Ionflux::GeoUtils::TransformNodes::TransformNode*
source, Ionflux::GeoUtils::TransformNodes::TransformNode* target, unsigned 
int outputID, unsigned int inputID, bool connectLater)
{
	if (source == 0)
	    throw GeoUtilsError("Source node is null.");
	if (target == 0)
	    throw GeoUtilsError("Target node is null.");
	TransformNodeVector::iterator i = find(nodes.begin(), 
	    nodes.end(), source);
	if (i == nodes.end())
	    throw GeoUtilsError("Source node is not part of the graph.");
	i = find(nodes.begin(), nodes.end(), target);
	if (i == nodes.end())
	    throw GeoUtilsError("Target node is not part of the graph.");
	Connection* result = 0;
	// This connection is used for comparison.
	Connection c0(source, target, outputID, inputID, true);
	unsigned int k = 0;
	while ((result == 0) 
	    && (k < connections.size()))
	{
	    Connection* c1 = connections[k];
	    if ((c1 != 0) 
	        && ((*c1) == c0))
	        result = c1;
	    k++;
	}
	return result;
}

bool 
TransformGraph::connect(Ionflux::GeoUtils::TransformNodes::TransformNode* 
source, Ionflux::GeoUtils::TransformNodes::TransformNode* target, unsigned 
int outputID, unsigned int inputID, bool connectLater)
{
	if (source == 0)
	    throw GeoUtilsError("Source node is null.");
	if (target == 0)
	    throw GeoUtilsError("Target node is null.");
	TransformNodeVector::iterator i = find(nodes.begin(), 
	    nodes.end(), source);
	if (i == nodes.end())
	    throw GeoUtilsError("Source node is not part of the graph.");
	i = find(nodes.begin(), nodes.end(), target);
	if (i == nodes.end())
	    throw GeoUtilsError("Target node is not part of the graph.");
	Connection* c0 = 0;
	if (inputID == INPUT_NEXT_FREE)
	    // The connection certainly does not exist yet.
	    inputID = target->getNumInputs();
	else
	    // The connection may exist already.
	    c0 = findConnection(source, target, outputID, inputID);
	if (c0 == 0)
	{
	    // Connection does not exist, create it.
	    c0 = new Connection(source, target, outputID, 
	        inputID, true);
	    if (c0 == 0)
	        throw GeoUtilsError("Could not allocate object");
	    /* <---- DEBUG ----- //
	    std::ostringstream message;
	    message << "Adding connection: " << *c0;
	    log(IFLogMessage(message.str(), VL_DEBUG, this, "connect"));
	    // ----- DEBUG ----> */
	    addConnection(c0);
	}
	if (!c0->isConnected())
	    c0->connect();
	return true;
}

bool 
TransformGraph::disconnect(Ionflux::GeoUtils::TransformNodes::TransformNode*
source, Ionflux::GeoUtils::TransformNodes::TransformNode* target, unsigned 
int outputID, unsigned int inputID)
{
	Connection* c0 = findConnection(source, target, outputID, 
	    inputID);
	if (c0 == 0)
	    return false;
	c0->disconnect();
	return true;
}

void TransformGraph::chain(unsigned int first, unsigned int last)
{
	if (last == NODE_INDEX_LAST)
	    last = nodes.size() - 1;
	for (unsigned int i = first; i < last; i++)
	    connect(nodes[i], nodes[i + 1]);
}

void 
TransformGraph::connectRange(Ionflux::GeoUtils::TransformNodes::TransformNode*
source, Ionflux::GeoUtils::TransformNodes::TransformNode* target, unsigned 
int numOutputSlots, unsigned int firstOutputID, unsigned int firstInputID)
{
	if (source == 0)
	    throw GeoUtilsError("Source node is null.");
	if (target == 0)
	    throw GeoUtilsError("Target node is null.");
	unsigned int inputID = firstInputID;
	unsigned int lastOutputID = firstOutputID + numOutputSlots - 1;
	for (unsigned int i = firstOutputID; i <= lastOutputID; i++)
	{
	    connect(source, target, i, inputID, false);
	    if (inputID != INPUT_NEXT_FREE)
	        inputID++;
	}
}

void 
TransformGraph::connectFan(Ionflux::GeoUtils::TransformNodes::TransformNode*
source, Ionflux::GeoUtils::TransformNodes::TransformNode* target, unsigned 
int numInputSlots, unsigned int outputID, unsigned int firstInputID)
{
	if (source == 0)
	    throw GeoUtilsError("Source node is null.");
	if (target == 0)
	    throw GeoUtilsError("Target node is null.");
	unsigned int inputID = firstInputID;
	for (unsigned int i = 0; i < numInputSlots; i++)
	{
	    connect(source, target, outputID, inputID, false);
	    if (inputID != INPUT_NEXT_FREE)
	        inputID++;
	}
}

void TransformGraph::setIO(unsigned int sourceIndex, unsigned int 
drainIndex)
{
	if (sourceIndex == NODE_INDEX_LAST)
	    sourceIndex = nodes.size() - 1;
	if (drainIndex == NODE_INDEX_LAST)
	    drainIndex = nodes.size() - 1;
	if (sourceIndex >= nodes.size())
	{
	    std::ostringstream message;
	    message << "Source node index out of range: " << sourceIndex;
	    throw GeoUtilsError(message.str());
	}
	if (drainIndex >= nodes.size())
	{
	    std::ostringstream message;
	    message << "Drain node index out of range: " << drainIndex;
	    throw GeoUtilsError(message.str());
	}
	source = nodes[sourceIndex];
	drain = nodes[drainIndex];
}

std::string TransformGraph::getString() const
{
	ostringstream status;
	status << getClassName() << "[";
	if (source != 0)
	    status << source->getString();
	else
	    status << "<none>";
	status << ", ";
	if (drain != 0)
	    status << drain->getString();
	else
	    status << "<none>";
	status << "]";
	return status.str();
}

void TransformGraph::addInputs(const 
Ionflux::GeoUtils::InputNodeSpecVector& newInputs)
{
	if (source == 0)
	    throw GeoUtilsError("Source node not set.");
	source->addInputs(newInputs);
}

void 
TransformGraph::getLinkedInputs(Ionflux::GeoUtils::TransformNodeVector& 
target)
{
	if (visited)
	    // There is some loop, return immediately.
	    return;
	if (source == 0)
	    throw GeoUtilsError("Source node not set.");
	source->getLinkedInputs(target);
	visited = false;
}

void TransformGraph::setInput(const 
Ionflux::GeoUtils::TransformNodes::InputNodeSpec& newInput, unsigned int 
inputID)
{
	if (source == 0)
	    throw GeoUtilsError("Source node not set.");
	source->setInput(newInput, inputID);
}

void TransformGraph::update()
{
	if (loopCounter >= loopMax)
	    throw GeoUtilsError("[TransformGraph.update] " 
	        "Maximum number of loop iterations exceeded.");
	loopCounter++;
	if (drain == 0)
	    throw GeoUtilsError("[TransformGraph.update] "
	        "Drain node not set.");
	drain->update();
	updateCounter++;
	loopCounter = 0;
	if (debugMode)
	    log(IFLogMessage(drain->getDebugInfo(debugExpand), VL_DEBUG, 
	        this, "update"));
}

unsigned int TransformGraph::getNumInputs() const
{
    if (source == 0)
        throw GeoUtilsError("Source node not set.");
    return source->getNumInputs();
}

Ionflux::GeoUtils::TransformNodes::InputNodeSpec 
TransformGraph::getInput(unsigned int elementIndex) const
{
    if (source == 0)
        throw GeoUtilsError("Source node not set.");
    return source->getInput(elementIndex);
}

int 
TransformGraph::findInput(Ionflux::GeoUtils::TransformNodes::InputNodeSpec 
needle, unsigned int occurence) const
{
    if (source == 0)
        throw GeoUtilsError("Source node not set.");
    return source->findInput(needle, occurence);
}

std::vector<Ionflux::GeoUtils::TransformNodes::InputNodeSpec>& 
TransformGraph::getInputs()
{
    if (source == 0)
        throw GeoUtilsError("Source node not set.");
    return source->getInputs();
}

void TransformGraph::addInput(const 
Ionflux::GeoUtils::TransformNodes::InputNodeSpec& addElement)
{
    if (source == 0)
        throw GeoUtilsError("Source node not set.");
    return source->addInput(addElement);
}

void TransformGraph::removeInput(const 
Ionflux::GeoUtils::TransformNodes::InputNodeSpec& removeElement)
{
    if (source == 0)
        throw GeoUtilsError("Source node not set.");
    return source->removeInput(removeElement);
}

void TransformGraph::removeInputIndex(unsigned int removeIndex)
{
    if (source == 0)
        throw GeoUtilsError("Source node not set.");
    return source->removeInputIndex(removeIndex);
}

void TransformGraph::clearInputs()
{
    if (source == 0)
        throw GeoUtilsError("Source node not set.");
    return source->clearInputs();
}

unsigned int TransformGraph::getNumOutputs() const
{
    if (drain == 0)
        throw GeoUtilsError("Drain node not set.");
    return drain->getNumOutputs();
}

Ionflux::GeoUtils::TransformableGroup* TransformGraph::getOutput(unsigned 
int elementIndex) const
{
    if (drain == 0)
        throw GeoUtilsError("Drain node not set.");
    return drain->getOutput(elementIndex);
}

int TransformGraph::findOutput(Ionflux::GeoUtils::TransformableGroup* 
needle, unsigned int occurence) const
{
    if (drain == 0)
        throw GeoUtilsError("Drain node not set.");
    return drain->findOutput(needle, occurence);
}

std::vector<Ionflux::GeoUtils::TransformableGroup*>& 
TransformGraph::getOutputs()
{
    if (drain == 0)
        throw GeoUtilsError("Drain node not set.");
    return drain->getOutputs();
}

void TransformGraph::addOutput(Ionflux::GeoUtils::TransformableGroup* 
addElement)
{
    if (drain == 0)
        throw GeoUtilsError("Drain node not set.");
    return drain->addOutput(addElement);
}

void TransformGraph::removeOutput(Ionflux::GeoUtils::TransformableGroup* 
removeElement)
{
    if (drain == 0)
        throw GeoUtilsError("Drain node not set.");
    return drain->removeOutput(removeElement);
}

void TransformGraph::removeOutputIndex(unsigned int removeIndex)
{
    if (drain == 0)
        throw GeoUtilsError("Drain node not set.");
    return drain->removeOutputIndex(removeIndex);
}

void TransformGraph::clearOutputs()
{
    if (drain == 0)
        throw GeoUtilsError("Drain node not set.");
    return drain->clearOutputs();
}

unsigned int TransformGraph::getNumConnections() const
{
    return connections.size();
}

Ionflux::GeoUtils::TransformNodes::Connection* 
TransformGraph::getConnection(unsigned int elementIndex) const
{
    if (elementIndex < connections.size())
		return connections[elementIndex];
	return 0;
}

int 
TransformGraph::findConnection(Ionflux::GeoUtils::TransformNodes::Connection*
needle, unsigned int occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::TransformNodes::Connection* currentConnection = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < connections.size()))
	{
		currentConnection = connections[i];
		if (currentConnection == needle)
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

std::vector<Ionflux::GeoUtils::TransformNodes::Connection*>& 
TransformGraph::getConnections()
{
    return connections;
}

void 
TransformGraph::addConnection(Ionflux::GeoUtils::TransformNodes::Connection*
addElement)
{
	addLocalRef(addElement);
	connections.push_back(addElement);
}

void 
TransformGraph::removeConnection(Ionflux::GeoUtils::TransformNodes::Connection*
removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::TransformNodes::Connection* currentConnection = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < connections.size()))
	{
		currentConnection = connections[i];
		if (currentConnection == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		connections.erase(connections.begin() + i);
		if (currentConnection != 0)
			removeLocalRef(currentConnection);
	}
}

void TransformGraph::removeConnectionIndex(unsigned int removeIndex)
{
    if (removeIndex > connections.size())
        return;
	Ionflux::GeoUtils::TransformNodes::Connection* e0 = connections[removeIndex];
    connections.erase(connections.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void TransformGraph::clearConnections()
{
    std::vector<Ionflux::GeoUtils::TransformNodes::Connection*>::iterator i;
	for (i = connections.begin(); i != connections.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	connections.clear();
}

unsigned int TransformGraph::getNumNodes() const
{
    return nodes.size();
}

Ionflux::GeoUtils::TransformNodes::TransformNode* 
TransformGraph::getNode(unsigned int elementIndex) const
{
    if (elementIndex < nodes.size())
		return nodes[elementIndex];
	return 0;
}

int 
TransformGraph::findNode(Ionflux::GeoUtils::TransformNodes::TransformNode* 
needle, unsigned int occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::TransformNodes::TransformNode* currentNode = 0;
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

std::vector<Ionflux::GeoUtils::TransformNodes::TransformNode*>& 
TransformGraph::getNodes()
{
    return nodes;
}

void 
TransformGraph::addNode(Ionflux::GeoUtils::TransformNodes::TransformNode* 
addElement)
{
	addLocalRef(addElement);
	nodes.push_back(addElement);
}

void 
TransformGraph::removeNode(Ionflux::GeoUtils::TransformNodes::TransformNode*
removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::TransformNodes::TransformNode* currentNode = 0;
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

void TransformGraph::removeNodeIndex(unsigned int removeIndex)
{
    if (removeIndex > nodes.size())
        return;
	Ionflux::GeoUtils::TransformNodes::TransformNode* e0 = nodes[removeIndex];
    nodes.erase(nodes.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void TransformGraph::clearNodes()
{
    std::vector<Ionflux::GeoUtils::TransformNodes::TransformNode*>::iterator i;
	for (i = nodes.begin(); i != nodes.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	nodes.clear();
}

void 
TransformGraph::setSource(Ionflux::GeoUtils::TransformNodes::TransformNode*
newSource)
{
	if (newSource != 0)
	{
	    // Make sure the new source node is part of the graph.
	    Ionflux::GeoUtils::TransformNodeVector::iterator i = 
	    find(nodes.begin(), nodes.end(), newSource);
	    if (i == nodes.end())
	        addNode(newSource);
	}
	source = newSource;
}

Ionflux::GeoUtils::TransformNodes::TransformNode* 
TransformGraph::getSource() const
{
    return source;
}

void 
TransformGraph::setDrain(Ionflux::GeoUtils::TransformNodes::TransformNode* 
newDrain)
{
	if (newDrain != 0)
	{
	    // Make sure the new drain node is part of the graph.
	    Ionflux::GeoUtils::TransformNodeVector::iterator i = 
	    find(nodes.begin(), nodes.end(), newDrain);
	    if (i == nodes.end())
	        addNode(newDrain);
	}
	drain = newDrain;
}

Ionflux::GeoUtils::TransformNodes::TransformNode* 
TransformGraph::getDrain() const
{
    return drain;
}

Ionflux::GeoUtils::TransformNodes::TransformGraph& 
TransformGraph::operator=(const 
Ionflux::GeoUtils::TransformNodes::TransformGraph& other)
{
    TransformNode::operator=(other);
    TransformNodeVector v0;
    source = other.source;
    drain = other.drain;
    for (TransformNodeVector::const_iterator i = other.nodes.begin(); 
        i != other.nodes.end(); i++)
    {
        addLocalRef(*i);
        v0.push_back(*i);
    }
    clearNodes();
    addNodes(v0);
    for (TransformNodeVector::const_iterator i = v0.begin(); 
        i != v0.end(); i++)
        removeLocalRef(*i);
	return *this;
}

Ionflux::GeoUtils::TransformNodes::TransformGraph* TransformGraph::copy() 
const
{
    TransformGraph* newTransformGraph = create();
    *newTransformGraph = *this;
    return newTransformGraph;
}

Ionflux::GeoUtils::TransformNodes::TransformGraph* 
TransformGraph::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<TransformGraph*>(other);
}

Ionflux::GeoUtils::TransformNodes::TransformGraph* 
TransformGraph::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    TransformGraph* newObject = new TransformGraph();
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

/** \file TransformGraph.cpp
 * \brief Transform graph implementation.
 */
