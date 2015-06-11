/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ChainableNodeProcessor.cpp      Chainable node processor 
 * (implementation).
 * ========================================================================== */

#include "ifvg/ChainableNodeProcessor.hpp"
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
#include "ifvg/Node.hpp"

using namespace std;

namespace Ionflux
{

namespace VolGfx
{

ChainableNodeProcessorClassInfo::ChainableNodeProcessorClassInfo()
{
	name = "ChainableNodeProcessor";
	desc = "Chainable node processor";
	baseClassInfo.push_back(Ionflux::VolGfx::NodeProcessor::CLASS_INFO);
}

ChainableNodeProcessorClassInfo::~ChainableNodeProcessorClassInfo()
{
}

// public member constants
const Ionflux::VolGfx::NodeProcessingResultID ChainableNodeProcessor::RESULT_FINISHED = 4;

// run-time type information instance constants
const ChainableNodeProcessorClassInfo ChainableNodeProcessor::chainableNodeProcessorClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ChainableNodeProcessor::CLASS_INFO = &ChainableNodeProcessor::chainableNodeProcessorClassInfo;

ChainableNodeProcessor::ChainableNodeProcessor()
: source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ChainableNodeProcessor::ChainableNodeProcessor(const Ionflux::VolGfx::ChainableNodeProcessor& other)
: source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ChainableNodeProcessor::~ChainableNodeProcessor()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::VolGfx::NodeProcessingResultID 
ChainableNodeProcessor::process(Ionflux::VolGfx::NodeImpl* nodeImpl, void* 
userData)
{
	NodeProcessingResultID result = RESULT_UNKNOWN;
	if (source != 0)
	    result = source->process(nodeImpl, userData);
	if (!checkFlags(result, RESULT_FINISHED))
	    result = processImpl(nodeImpl, userData);
	return result;
}

Ionflux::VolGfx::NodeProcessingResultID 
ChainableNodeProcessor::process(Ionflux::VolGfx::Node* node, void* 
userData)
{
	Ionflux::ObjectBase::nullPointerCheck(node, this, 
	    "process", "Node");
	return process(node->getImpl(), userData);
}

std::string ChainableNodeProcessor::getValueString() const
{
	ostringstream status;
	status << "source: ";
	if (source != 0)
	    status << "[" << source->getValueString() << "]";
	else
	    status << "<null>";
	return status.str();
}

void ChainableNodeProcessor::setSource(Ionflux::VolGfx::NodeProcessor* 
newSource)
{
	if (source == newSource)
		return;
    if (newSource != 0)
        addLocalRef(newSource);
	if (source != 0)
		removeLocalRef(source);
	source = newSource;
}

Ionflux::VolGfx::NodeProcessor* ChainableNodeProcessor::getSource() const
{
    return source;
}

Ionflux::VolGfx::ChainableNodeProcessor& 
ChainableNodeProcessor::operator=(const 
Ionflux::VolGfx::ChainableNodeProcessor& other)
{
    if (this == &other)
        return *this;
    setSource(other.source);
	return *this;
}

Ionflux::VolGfx::ChainableNodeProcessor* ChainableNodeProcessor::copy() 
const
{
    ChainableNodeProcessor* newChainableNodeProcessor = create();
    *newChainableNodeProcessor = *this;
    return newChainableNodeProcessor;
}

Ionflux::VolGfx::ChainableNodeProcessor* 
ChainableNodeProcessor::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<ChainableNodeProcessor*>(other);
}

Ionflux::VolGfx::ChainableNodeProcessor* 
ChainableNodeProcessor::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    ChainableNodeProcessor* newObject = new ChainableNodeProcessor();
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int ChainableNodeProcessor::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file ChainableNodeProcessor.cpp
 * \brief Chainable node processor implementation.
 */
