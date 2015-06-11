/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeProcessor.cpp               Node processor (implementation).
 * ========================================================================== */

#include "ifvg/NodeProcessor.hpp"
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

NodeProcessorClassInfo::NodeProcessorClassInfo()
{
	name = "NodeProcessor";
	desc = "Node processor";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

NodeProcessorClassInfo::~NodeProcessorClassInfo()
{
}

// public member constants
const Ionflux::VolGfx::NodeProcessingResultID NodeProcessor::RESULT_UNKNOWN = 0;
const Ionflux::VolGfx::NodeProcessingResultID NodeProcessor::RESULT_OK = 1;
const Ionflux::VolGfx::NodeProcessingResultID NodeProcessor::RESULT_FAILED = 2;

// run-time type information instance constants
const NodeProcessorClassInfo NodeProcessor::nodeProcessorClassInfo;
const Ionflux::ObjectBase::IFClassInfo* NodeProcessor::CLASS_INFO = &NodeProcessor::nodeProcessorClassInfo;

NodeProcessor::NodeProcessor()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

NodeProcessor::NodeProcessor(const Ionflux::VolGfx::NodeProcessor& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

NodeProcessor::~NodeProcessor()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::VolGfx::NodeProcessingResultID 
NodeProcessor::processImpl(Ionflux::VolGfx::NodeImpl* nodeImpl, void* 
userData)
{
	// TODO: Implementation.
	return RESULT_UNKNOWN;
}

Ionflux::VolGfx::NodeProcessingResultID 
NodeProcessor::process(Ionflux::VolGfx::NodeImpl* nodeImpl, void* userData)
{
	Ionflux::ObjectBase::nullPointerCheck(nodeImpl, this, 
	    "process", "Node implementation");
	processImpl(nodeImpl, userData);
	return RESULT_UNKNOWN;
}

Ionflux::VolGfx::NodeProcessingResultID 
NodeProcessor::process(Ionflux::VolGfx::Node* node, void* userData)
{
	Ionflux::ObjectBase::nullPointerCheck(node, this, 
	    "process", "Node");
	return process(node->getImpl(), userData);
}

Ionflux::VolGfx::NodeProcessingResultID 
NodeProcessor::operator()(Ionflux::VolGfx::NodeImpl* nodeImpl, void* 
userData)
{
	// TODO: Implementation.
	return process(nodeImpl, userData);
}

Ionflux::VolGfx::NodeProcessingResultID 
NodeProcessor::operator()(Ionflux::VolGfx::Node* node, void* userData)
{
	// TODO: Implementation.
	return process(node, userData);
}

std::string NodeProcessor::getValueString() const
{
	ostringstream status;
	// TODO: Implementation.
	return status.str();
}

bool NodeProcessor::checkFlags(Ionflux::VolGfx::NodeProcessingResultID 
result, Ionflux::VolGfx::NodeProcessingResultID flags)
{
	if ((result & flags) == 0)
	    return false;
	return true;
}

Ionflux::VolGfx::NodeProcessor& NodeProcessor::operator=(const 
Ionflux::VolGfx::NodeProcessor& other)
{
    if (this == &other)
        return *this;
	return *this;
}

Ionflux::VolGfx::NodeProcessor* NodeProcessor::copy() const
{
    NodeProcessor* newNodeProcessor = create();
    *newNodeProcessor = *this;
    return newNodeProcessor;
}

Ionflux::VolGfx::NodeProcessor* 
NodeProcessor::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<NodeProcessor*>(other);
}

Ionflux::VolGfx::NodeProcessor* 
NodeProcessor::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    NodeProcessor* newObject = new NodeProcessor();
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int NodeProcessor::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file NodeProcessor.cpp
 * \brief Node processor implementation.
 */
