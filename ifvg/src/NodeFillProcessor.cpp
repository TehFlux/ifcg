/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeFillProcessor.cpp           Node fill processor (implementation).
 * ========================================================================== */

#include "ifvg/NodeFillProcessor.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "altjira/Color.hpp"
#include "geoutils/Vector3.hpp"
#include "ifvg/utils.hpp"
#include "ifvg/IFVGError.hpp"
#include "ifvg/Context.hpp"

using namespace std;

namespace Ionflux
{

namespace VolGfx
{

NodeFillProcessorClassInfo::NodeFillProcessorClassInfo()
{
	name = "NodeFillProcessor";
	desc = "Node fill processor";
	baseClassInfo.push_back(Ionflux::VolGfx::ChainableNodeProcessor::CLASS_INFO);
}

NodeFillProcessorClassInfo::~NodeFillProcessorClassInfo()
{
}

// run-time type information instance constants
const NodeFillProcessorClassInfo NodeFillProcessor::nodeFillProcessorClassInfo;
const Ionflux::ObjectBase::IFClassInfo* NodeFillProcessor::CLASS_INFO = &NodeFillProcessor::nodeFillProcessorClassInfo;

NodeFillProcessor::NodeFillProcessor()
: context(0), clearExisting(false), recursive(false), maxDepth(DEPTH_UNSPECIFIED)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

NodeFillProcessor::NodeFillProcessor(const Ionflux::VolGfx::NodeFillProcessor& other)
: context(0), clearExisting(false), recursive(false), maxDepth(DEPTH_UNSPECIFIED)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

NodeFillProcessor::NodeFillProcessor(Ionflux::VolGfx::Context* initContext,
bool initClearExisting, bool initRecursive, int initMaxDepth)
: context(0), clearExisting(initClearExisting), recursive(initRecursive), 
maxDepth(initMaxDepth)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initContext != 0)
	    setContext(initContext);
}

NodeFillProcessor::~NodeFillProcessor()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::VolGfx::NodeProcessingResultID 
NodeFillProcessor::processImpl(Ionflux::VolGfx::NodeImpl* nodeImpl, void* 
userData)
{
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "processImpl", "Context");
	/* <---- DEBUG ----- //
	int depth = Node::getImplDepth(nodeImpl, context);
	if (depth == 2)
	{
	    std::cerr << "[NodeFillProcessor::processImpl] DEBUG: " 
	        "processing node: [" 
	        << Node::getImplValueString(nodeImpl, context, false) << "]" 
	        << std::endl;
	}
	// ----- DEBUG ----> */
	Node::fillImpl(nodeImpl, context, clearExisting, recursive, maxDepth);
	/* <---- DEBUG ----- //
	if (depth == 2)
	{
	    std::cerr << "[NodeFillProcessor::processImpl] DEBUG: " 
	        "after processing: [" 
	        << Node::getImplValueString(nodeImpl, context, false) << "]" 
	        << std::endl;
	}
	// ----- DEBUG ----> */
	return RESULT_OK;
}

std::string NodeFillProcessor::getValueString() const
{
	ostringstream status;
	status << "context: ";
	if (context == 0)
	    status << "<null>";
	else
	    status << "[" << context->getValueString() << "]";
	status << "; clearExisting = " << clearExisting 
	    << ", recursive = " << recursive
	    << ", maxDepth = " << getDepthString(maxDepth);
	return status.str();
}

void NodeFillProcessor::setContext(Ionflux::VolGfx::Context* newContext)
{
	if (context == newContext)
		return;
    if (newContext != 0)
        addLocalRef(newContext);
	if (context != 0)
		removeLocalRef(context);
	context = newContext;
}

Ionflux::VolGfx::Context* NodeFillProcessor::getContext() const
{
    return context;
}

void NodeFillProcessor::setClearExisting(bool newClearExisting)
{
	clearExisting = newClearExisting;
}

bool NodeFillProcessor::getClearExisting() const
{
    return clearExisting;
}

void NodeFillProcessor::setRecursive(bool newRecursive)
{
	recursive = newRecursive;
}

bool NodeFillProcessor::getRecursive() const
{
    return recursive;
}

void NodeFillProcessor::setMaxDepth(int newMaxDepth)
{
	maxDepth = newMaxDepth;
}

int NodeFillProcessor::getMaxDepth() const
{
    return maxDepth;
}

Ionflux::VolGfx::NodeFillProcessor& NodeFillProcessor::operator=(const 
Ionflux::VolGfx::NodeFillProcessor& other)
{
    if (this == &other)
        return *this;
    setContext(other.context);
    setClearExisting(other.clearExisting);
    setRecursive(other.recursive);
    setMaxDepth(other.maxDepth);
	return *this;
}

Ionflux::VolGfx::NodeFillProcessor* NodeFillProcessor::copy() const
{
    NodeFillProcessor* newNodeFillProcessor = create();
    *newNodeFillProcessor = *this;
    return newNodeFillProcessor;
}

Ionflux::VolGfx::NodeFillProcessor* 
NodeFillProcessor::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<NodeFillProcessor*>(other);
}

Ionflux::VolGfx::NodeFillProcessor* 
NodeFillProcessor::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    NodeFillProcessor* newObject = new NodeFillProcessor();
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::VolGfx::NodeFillProcessor* 
NodeFillProcessor::create(Ionflux::VolGfx::Context* initContext, bool 
initClearExisting, bool initRecursive, int initMaxDepth, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    NodeFillProcessor* newObject = new NodeFillProcessor(initContext, 
    initClearExisting, initRecursive, initMaxDepth);
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int NodeFillProcessor::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file NodeFillProcessor.cpp
 * \brief Node fill processor implementation.
 */
