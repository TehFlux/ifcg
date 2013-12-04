/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TransformNode.cpp               Transform node (implementation).
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

#include "geoutils/TransformNode.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;
using Ionflux::GeoUtils::TransformableGroupVector;

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

TransformNodeClassInfo::TransformNodeClassInfo()
{
	name = "TransformNode";
	desc = "Transform node";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

TransformNodeClassInfo::~TransformNodeClassInfo()
{
}

// public member constants
const unsigned int TransformNode::DEFAULT_LOOP_MAX = 10;

// run-time type information instance constants
const TransformNodeClassInfo TransformNode::transformNodeClassInfo;
const Ionflux::ObjectBase::IFClassInfo* TransformNode::CLASS_INFO = &TransformNode::transformNodeClassInfo;

TransformNode::TransformNode()
: loopCounter(0), visited(false), debugMode(false), debugExpand(false), loopMax(DEFAULT_LOOP_MAX), maxNumInputs(DEFAULT_MAX_NUM_INPUTS), updateCounter(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

TransformNode::TransformNode(const Ionflux::GeoUtils::TransformNodes::TransformNode& other)
: loopCounter(0), visited(false), debugMode(false), debugExpand(false), loopMax(DEFAULT_LOOP_MAX), maxNumInputs(DEFAULT_MAX_NUM_INPUTS), updateCounter(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

TransformNode::TransformNode(const Ionflux::ObjectBase::IFObjectID& nodeID)
: loopCounter(0), visited(false), debugMode(false), debugExpand(false), 
loopMax(DEFAULT_LOOP_MAX), maxNumInputs(DEFAULT_MAX_NUM_INPUTS), 
updateCounter(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setID(nodeID);
}

TransformNode::~TransformNode()
{
	clearInputs();
	clearOutputs();
	// TODO: Nothing ATM. ;-)
}

void TransformNode::process()
{
	// TODO: Implementation.
}

void TransformNode::addInputs(const Ionflux::GeoUtils::InputNodeSpecVector&
newInputs)
{
	for (InputNodeSpecVector::const_iterator i = newInputs.begin(); 
	    i != newInputs.end(); i++)
	    addInput(*i);
}

void TransformNode::getLinkedInputs(Ionflux::GeoUtils::TransformNodeVector&
target)
{
	if (visited)
	    // There is some loop, return immediately.
	    return;
	visited = true;
	for (InputNodeSpecVector::const_iterator i = inputs.begin(); 
	    i != inputs.end(); i++)
	{
	    TransformNode* n0 = (*i).node;
	    if (n0 != 0)
	    {
	        target.push_back(n0);
	        n0->getLinkedInputs(target);
	    }
	}
	visited = false;
}

void TransformNode::setInput(const 
Ionflux::GeoUtils::TransformNodes::InputNodeSpec& newInput, unsigned int 
inputID)
{
	if (inputID == INPUT_NEXT_FREE)
	    inputID = inputs.size();
	if (inputID > maxNumInputs)
	    throw GeoUtilsError("Maximum number of inputs exceeded.");
	unsigned int numInputs = inputs.size();
	for (unsigned int i = numInputs; i <= inputID; i++)
	    inputs.push_back(DEFAULT_INPUT_NODE_SPEC);
	inputs[inputID] = newInput;
}

void TransformNode::clearInputCache()
{
	for (TransformableGroupVector::iterator i = 
	    inputCache.begin(); i != inputCache.end(); i++)
	{
	    TransformableGroup* g0 = *i;
	    if (g0 != 0)
	        removeLocalRef(g0);
	}
	inputCache.clear();
}

void TransformNode::updateInputs()
{
	// Determine the set of unique input nodes.
	std::set<TransformNode*> is0;
	for (InputNodeSpecVector::iterator i = inputs.begin(); 
	    i != inputs.end(); i++)
	{
	    TransformNode* n0 = (*i).node;
	    if (n0 != 0)
	        is0.insert(n0);
	    else
	        throw GeoUtilsError("Input node is null.");
	}
	// Update the nodes.
	for (std::set<TransformNode*>::iterator j = is0.begin(); 
	    j != is0.end(); j++)
	{
	    /* <---- DEBUG ----- //
	    ostringstream message;
	    message << "updating node: " << (*(*j));
	    log(IFLogMessage(message.str(), VL_DEBUG, this, "updateInputs"));
	    // ----- DEBUG ----> */
	    (*j)->update();
	}
	// Populate the input cache.
	clearInputCache();
	for (InputNodeSpecVector::iterator k = inputs.begin(); 
	    k != inputs.end(); k++)
	{
	    TransformNode* n0 = (*k).node;
	    if (n0 == 0)
	        throw GeoUtilsError("Input node not set.");
	    TransformableGroup* g0 = n0->getOutput((*k).outputID);
	    /* <---- DEBUG ----- //
	    ostringstream message;
	    message << "node: " << (*n0) << ", group #" << (*k).outputID 
	        << ": ";
	    if (g0 != 0)
	        message << (*g0);
	    else
	        message << "<missing>";
	    log(IFLogMessage(message.str(), VL_DEBUG, this, "updateInputs"));
	    // ----- DEBUG ----> */
	    if (g0 == 0)
	    {
	        std::ostringstream message;
	        message << "[Input node does not supply the specified "
	            "output (node = " << (*n0) << ", outputID = " 
	            << (*k).outputID << ", numOutputs = " 
	            << n0->getNumOutputs() << ").";
	        throw GeoUtilsError(message.str());
	    }
	    addLocalRef(g0);
	    inputCache.push_back(g0);
	}
}

void TransformNode::clearInputGroups()
{
	std::set<TransformNode*> is0;
	for (InputNodeSpecVector::iterator i = inputs.begin(); 
	    i != inputs.end(); i++)
	{
	    TransformNode* n0 = (*i).node;
	    if (n0 != 0)
	        is0.insert(n0);
	}
	for (std::set<TransformNode*>::iterator j = is0.begin(); 
	    j != is0.end(); j++)
	    (*j)->clearOutputs();
}

void TransformNode::cleanup()
{
	clearInputCache();
}

void TransformNode::update()
{
	if (loopCounter >= loopMax)
	    throw GeoUtilsError("Maximum number of loop iterations exceeded.");
	loopCounter++;
	/* <---- DEBUG ----- //
	Ionflux::GeoUtils::Clock c0;
	double inputUpdateTime = 0.;
	double outputClearTime = 0.;
	double processingTime = 0.;
	c0.start();
	// ----- DEBUG ----> */
	updateInputs();
	// NOTE: This can be enabled when all nodes use the input cache.
	//clearInputGroups();
	/* <---- DEBUG ----- //
	c0.stop();
	inputUpdateTime = c0.getElapsedTime();
	c0.start();
	// ----- DEBUG ----> */
	clearOutputs();
	/* <---- DEBUG ----- //
	c0.stop();
	outputClearTime = c0.getElapsedTime();
	c0.start();
	// ----- DEBUG ----> */
	/* <---- DEBUG ----- //
	log(IFLogMessage("Processing...", VL_DEBUG, this, "update"));
	// ----- DEBUG ----> */
	process();
	/* <---- DEBUG ----- //
	log(IFLogMessage("Finished.", VL_DEBUG, this, "update"));
	// ----- DEBUG ----> */
	/* <---- DEBUG ----- //
	c0.stop();
	processingTime = c0.getElapsedTime();
	std::ostringstream message;
	message << "inputUpdateTime = " << inputUpdateTime 
	    << ", outputClearTime = " << outputClearTime 
	    << ", processingTime = " << processingTime << " secs";
	log(IFLogMessage(message.str(), VL_DEBUG, this, "update"));
	// ----- DEBUG ----> */
	updateCounter++;
	loopCounter = 0;
	if (debugMode)
	    log(IFLogMessage(getDebugInfo(debugExpand), VL_DEBUG, 
	        this, "update"));
	cleanup();
}

std::string TransformNode::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << id << "]";
	return status.str();
}

std::string TransformNode::getDebugInfo(bool expand)
{
	ostringstream result;
	result << getString() << ": numInputs = " << inputs.size() 
	    << ", numOutputs = " << outputs.size() << ", loopCounter = " 
	    << loopCounter << ", updateCounter = " << updateCounter << "\n";
	result << "Inputs:";
	for (Ionflux::GeoUtils::InputNodeSpecVector::iterator i = 
	    inputs.begin(); i != inputs.end(); i++)
	{
	    result << "\n";
	    TransformNode* n0 = (*i).node;
	    if (n0 != 0)
	    {
	        result << "  " << (*n0) << "\n";
	        TransformableGroup* o0 = n0->getOutput((*i).outputID);
	        if (o0 != 0)
	            result << o0->getDebugInfo(expand, 2);
	        else
	            result << "<not available>";
	    }
	}
	result << "\nInputs (cached):";
	for (Ionflux::GeoUtils::TransformableGroupVector::iterator k = 
	    inputCache.begin(); k != inputCache.end(); k++)
	{
	    result << "\n";
	    TransformableGroup* o0 = *k;
	    if (o0 == 0)
	    {
	        std::ostringstream message;
	        message << "Input group missing.";
	        throw GeoUtilsError(message.str());
	    }
	    result << o0->getDebugInfo(expand, 2);
	}
	result << "\nOutputs:";
	for (unsigned int j = 0; j < outputs.size(); j++)
	{
	    result << "\n";
	    TransformableGroup* g0 = outputs[j];
	    if (g0 != 0)
	        result << g0->getDebugInfo(expand, 2);
	    else
	        result << "  <null>";
	}
	return result.str();
}

void TransformNode::enableDebugMode(bool newDebugMode, bool expand)
{
	debugMode = newDebugMode;
	debugExpand = expand;
}

unsigned int TransformNode::getNumInputs() const
{
    return inputs.size();
}

Ionflux::GeoUtils::TransformNodes::InputNodeSpec 
TransformNode::getInput(unsigned int elementIndex) const
{
    if (elementIndex < inputs.size())
		return inputs[elementIndex];
	return DEFAULT_INPUT_NODE_SPEC;
}

int 
TransformNode::findInput(Ionflux::GeoUtils::TransformNodes::InputNodeSpec 
needle, unsigned int occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::TransformNodes::InputNodeSpec currentInput = DEFAULT_INPUT_NODE_SPEC;
	unsigned int i = 0;
	while (!found 
		&& (i < inputs.size()))
	{
		currentInput = inputs[i];
		if (currentInput == needle)
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

std::vector<Ionflux::GeoUtils::TransformNodes::InputNodeSpec>& 
TransformNode::getInputs()
{
    return inputs;
}

void TransformNode::addInput(const 
Ionflux::GeoUtils::TransformNodes::InputNodeSpec& addElement)
{
	if (inputs.size() >= maxNumInputs)
	    throw GeoUtilsError("Maximum number of inputs exceeded.");
	inputs.push_back(addElement);
}

void TransformNode::removeInput(const 
Ionflux::GeoUtils::TransformNodes::InputNodeSpec& removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::TransformNodes::InputNodeSpec currentInput = DEFAULT_INPUT_NODE_SPEC;
	unsigned int i = 0;
	while (!found 
		&& (i < inputs.size()))
	{
		currentInput = inputs[i];
		if (currentInput == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		inputs.erase(inputs.begin() + i);
	}
}

void TransformNode::removeInputIndex(unsigned int removeIndex)
{
    if (removeIndex > inputs.size())
        return;
    inputs.erase(inputs.begin() + removeIndex);
}

void TransformNode::clearInputs()
{
    inputs.clear();
}

unsigned int TransformNode::getNumOutputs() const
{
    return outputs.size();
}

Ionflux::GeoUtils::TransformableGroup* TransformNode::getOutput(unsigned 
int elementIndex) const
{
    if (elementIndex < outputs.size())
		return outputs[elementIndex];
	return 0;
}

int TransformNode::findOutput(Ionflux::GeoUtils::TransformableGroup* 
needle, unsigned int occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::TransformableGroup* currentOutput = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < outputs.size()))
	{
		currentOutput = outputs[i];
		if (currentOutput == needle)
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

std::vector<Ionflux::GeoUtils::TransformableGroup*>& 
TransformNode::getOutputs()
{
    return outputs;
}

void TransformNode::addOutput(Ionflux::GeoUtils::TransformableGroup* 
addElement)
{
	addLocalRef(addElement);
	outputs.push_back(addElement);
}

void TransformNode::removeOutput(Ionflux::GeoUtils::TransformableGroup* 
removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::TransformableGroup* currentOutput = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < outputs.size()))
	{
		currentOutput = outputs[i];
		if (currentOutput == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		outputs.erase(outputs.begin() + i);
		if (currentOutput != 0)
			removeLocalRef(currentOutput);
	}
}

void TransformNode::removeOutputIndex(unsigned int removeIndex)
{
    if (removeIndex > outputs.size())
        return;
	Ionflux::GeoUtils::TransformableGroup* e0 = outputs[removeIndex];
    outputs.erase(outputs.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void TransformNode::clearOutputs()
{
    std::vector<Ionflux::GeoUtils::TransformableGroup*>::iterator i;
	for (i = outputs.begin(); i != outputs.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	outputs.clear();
}

void TransformNode::setLoopMax(unsigned int newLoopMax)
{
	loopMax = newLoopMax;
}

unsigned int TransformNode::getLoopMax() const
{
    return loopMax;
}

void TransformNode::setMaxNumInputs(unsigned int newMaxNumInputs)
{
	maxNumInputs = newMaxNumInputs;
}

unsigned int TransformNode::getMaxNumInputs() const
{
    return maxNumInputs;
}

void TransformNode::setUpdateCounter(unsigned int newUpdateCounter)
{
	updateCounter = newUpdateCounter;
}

unsigned int TransformNode::getUpdateCounter() const
{
    return updateCounter;
}

Ionflux::GeoUtils::TransformNodes::TransformNode& 
TransformNode::operator=(const 
Ionflux::GeoUtils::TransformNodes::TransformNode& other)
{
    InputNodeSpecVector v0;
    loopMax = other.loopMax;
    /* No local references are needed since we do not manage the 
       inputs anyway. */
    for (InputNodeSpecVector::const_iterator i = other.inputs.begin(); 
        i != other.inputs.end(); i++)
        v0.push_back(*i);
    clearInputs();
    clearOutputs();
    addInputs(v0);
	return *this;
}

Ionflux::GeoUtils::TransformNodes::TransformNode* TransformNode::copy() 
const
{
    TransformNode* newTransformNode = 
        new TransformNode();
    *newTransformNode = *this;
    return newTransformNode;
}

Ionflux::GeoUtils::TransformNodes::TransformNode* 
TransformNode::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<TransformNode*>(other);
}

void TransformNode::setParam(Ionflux::ObjectBase::IFParamID paramID, 
Ionflux::Mapping::MappingValue paramValue)
{
    throw GeoUtilsError("Parameter does not exist.");
}

Ionflux::Mapping::MappingValue 
TransformNode::getParam(Ionflux::ObjectBase::IFParamID paramID)
{
    throw GeoUtilsError("Parameter does not exist.");
}

}

}

}

/** \file TransformNode.cpp
 * \brief Transform node implementation.
 */
