/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeIOBWallThicknessProcessor.cpp  Node inside/outside/boundary wall 
 * thickness processor (implementation).
 * ========================================================================== */

#include "ifvg/NodeIOBWallThicknessProcessor.hpp"
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

NodeIOBWallThicknessProcessorClassInfo::NodeIOBWallThicknessProcessorClassInfo()
{
	name = "NodeIOBWallThicknessProcessor";
	desc = "Node inside/outside/boundary wall thickness processor";
	baseClassInfo.push_back(Ionflux::VolGfx::ChainableNodeProcessor::CLASS_INFO);
}

NodeIOBWallThicknessProcessorClassInfo::~NodeIOBWallThicknessProcessorClassInfo()
{
}

// run-time type information instance constants
const NodeIOBWallThicknessProcessorClassInfo NodeIOBWallThicknessProcessor::nodeIOBWallThicknessProcessorClassInfo;
const Ionflux::ObjectBase::IFClassInfo* NodeIOBWallThicknessProcessor::CLASS_INFO = &NodeIOBWallThicknessProcessor::nodeIOBWallThicknessProcessorClassInfo;

NodeIOBWallThicknessProcessor::NodeIOBWallThicknessProcessor()
: context(0), minColorIndex(COLOR_INDEX_UNSPECIFIED), maxColorIndex(COLOR_INDEX_UNSPECIFIED), enableScanWallThickness(true), minWallThickness(0), maxWallThickness(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

NodeIOBWallThicknessProcessor::NodeIOBWallThicknessProcessor(const Ionflux::VolGfx::NodeIOBWallThicknessProcessor& other)
: context(0), minColorIndex(COLOR_INDEX_UNSPECIFIED), maxColorIndex(COLOR_INDEX_UNSPECIFIED), enableScanWallThickness(true), minWallThickness(0), maxWallThickness(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

NodeIOBWallThicknessProcessor::NodeIOBWallThicknessProcessor(Ionflux::VolGfx::Context*
initContext, Ionflux::VolGfx::ColorIndex initMinColorIndex, 
Ionflux::VolGfx::ColorIndex initMaxColorIndex, bool 
initEnableScanWallThickness, Ionflux::ObjectBase::UInt16 
initMinWallThickness, Ionflux::ObjectBase::UInt16 initMaxWallThickness)
: context(0), minColorIndex(initMinColorIndex), 
maxColorIndex(initMaxColorIndex), 
enableScanWallThickness(initEnableScanWallThickness), 
minWallThickness(initMinWallThickness), 
maxWallThickness(initMaxWallThickness)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initContext != 0)
	    setContext(initContext);
}

NodeIOBWallThicknessProcessor::~NodeIOBWallThicknessProcessor()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::VolGfx::NodeProcessingResultID 
NodeIOBWallThicknessProcessor::processImpl(Ionflux::VolGfx::NodeImpl* 
nodeImpl, void* userData)
{
	if (!Node::hasImplDataType(nodeImpl, Node::DATA_TYPE_VOXEL_IOB))
	    // Node has incompatible type.
	    return RESULT_OK;
	NodeDataImpl* dp = nodeImpl->data;
	VoxelDataIOB* d0 = Ionflux::ObjectBase::nullPointerCheck(
	    static_cast<VoxelDataIOB*>(dp->data), this, 
	    "processImpl", "Voxel inside/outside/boundary data");
	Ionflux::ObjectBase::UInt16 cwt0 = getIOBDataWallThicknessMin(*d0);
	/* <---- DEBUG ----- //
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "processImpl", "Context");
	NodeID nid0 = Node::getImplNodeID(nodeImpl, context);
	// ----- DEBUG ----> */
	/* <---- DEBUG ----- //
	std::cerr << "[NodeIOBWallThicknessProcessor::processImpl] DEBUG: "
	    "node: [" << getNodeIDValueString(nid0, false, true, true, context) 
	    << "] cwt0 = " << cwt0 << std::endl;
	// ----- DEBUG ----> */
	if (enableScanWallThickness)
	{
	    // determine minimum wall thickness range
	    if ((minWallThickness == 0) 
	        || ((cwt0 > 0) 
	            && (cwt0 < minWallThickness)))
	    {
	        minWallThickness = cwt0;
	    }
	    if ((maxWallThickness == 0) 
	        || ((cwt0 > 0) 
	            && (cwt0 > maxWallThickness)))
	    {
	        maxWallThickness = cwt0;
	    }
	} else
	{
	    // assign color index
	    ColorIndex ci = getColorIndex(cwt0, minWallThickness, 
	        maxWallThickness, minColorIndex, maxColorIndex);
	    /* <---- DEBUG ----- //
	    std::cerr << "[NodeIOBWallThicknessProcessor::processImpl] DEBUG: "
	        "node: [" << getNodeIDValueString(nid0, true, true, true, context)
	
        << "] colorIndex = " << ci << std::endl;
	    // ----- DEBUG ----> */
	    d0->color = ci;
	}
	return RESULT_OK;
}

std::string NodeIOBWallThicknessProcessor::getValueString() const
{
	ostringstream status;
	status << "context: ";
	if (context == 0)
	    status << "<null>";
	else
	    status << "[" << context->getValueString() << "]";
	status << "minColorIndex = " << minColorIndex 
	    << ", maxColorIndex = " << maxColorIndex 
	    << ", enableScanWallThickness = " 
	        << Ionflux::ObjectBase::getBooleanValueString(
	            enableScanWallThickness) 
	    << ", minWallThickness = " << minWallThickness 
	    << ", maxWallThickness = " << maxWallThickness;
	return status.str();
}

void NodeIOBWallThicknessProcessor::setContext(Ionflux::VolGfx::Context* 
newContext)
{
	if (context == newContext)
		return;
    if (newContext != 0)
        addLocalRef(newContext);
	if (context != 0)
		removeLocalRef(context);
	context = newContext;
}

Ionflux::VolGfx::Context* NodeIOBWallThicknessProcessor::getContext() const
{
    return context;
}

void 
NodeIOBWallThicknessProcessor::setMinColorIndex(Ionflux::VolGfx::ColorIndex
newMinColorIndex)
{
	minColorIndex = newMinColorIndex;
}

Ionflux::VolGfx::ColorIndex 
NodeIOBWallThicknessProcessor::getMinColorIndex() const
{
    return minColorIndex;
}

void 
NodeIOBWallThicknessProcessor::setMaxColorIndex(Ionflux::VolGfx::ColorIndex
newMaxColorIndex)
{
	maxColorIndex = newMaxColorIndex;
}

Ionflux::VolGfx::ColorIndex 
NodeIOBWallThicknessProcessor::getMaxColorIndex() const
{
    return maxColorIndex;
}

void NodeIOBWallThicknessProcessor::setEnableScanWallThickness(bool 
newEnableScanWallThickness)
{
	enableScanWallThickness = newEnableScanWallThickness;
}

bool NodeIOBWallThicknessProcessor::getEnableScanWallThickness() const
{
    return enableScanWallThickness;
}

void 
NodeIOBWallThicknessProcessor::setMinWallThickness(Ionflux::ObjectBase::UInt16
newMinWallThickness)
{
	minWallThickness = newMinWallThickness;
}

Ionflux::ObjectBase::UInt16 
NodeIOBWallThicknessProcessor::getMinWallThickness() const
{
    return minWallThickness;
}

void 
NodeIOBWallThicknessProcessor::setMaxWallThickness(Ionflux::ObjectBase::UInt16
newMaxWallThickness)
{
	maxWallThickness = newMaxWallThickness;
}

Ionflux::ObjectBase::UInt16 
NodeIOBWallThicknessProcessor::getMaxWallThickness() const
{
    return maxWallThickness;
}

Ionflux::VolGfx::NodeIOBWallThicknessProcessor& 
NodeIOBWallThicknessProcessor::operator=(const 
Ionflux::VolGfx::NodeIOBWallThicknessProcessor& other)
{
    if (this == &other)
        return *this;
    setMinColorIndex(other.minColorIndex);
    setMaxColorIndex(other.maxColorIndex);
    setEnableScanWallThickness(other.enableScanWallThickness);
    setMinWallThickness(other.minWallThickness);
    setMaxWallThickness(other.maxWallThickness);
	return *this;
}

Ionflux::VolGfx::NodeIOBWallThicknessProcessor* 
NodeIOBWallThicknessProcessor::copy() const
{
    NodeIOBWallThicknessProcessor* newNodeIOBWallThicknessProcessor = create();
    *newNodeIOBWallThicknessProcessor = *this;
    return newNodeIOBWallThicknessProcessor;
}

Ionflux::VolGfx::NodeIOBWallThicknessProcessor* 
NodeIOBWallThicknessProcessor::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<NodeIOBWallThicknessProcessor*>(other);
}

Ionflux::VolGfx::NodeIOBWallThicknessProcessor* 
NodeIOBWallThicknessProcessor::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    NodeIOBWallThicknessProcessor* newObject = new NodeIOBWallThicknessProcessor();
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::VolGfx::NodeIOBWallThicknessProcessor* 
NodeIOBWallThicknessProcessor::create(Ionflux::VolGfx::Context* 
initContext, Ionflux::VolGfx::ColorIndex initMinColorIndex, 
Ionflux::VolGfx::ColorIndex initMaxColorIndex, bool 
initEnableScanWallThickness, Ionflux::ObjectBase::UInt16 
initMinWallThickness, Ionflux::ObjectBase::UInt16 initMaxWallThickness, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    NodeIOBWallThicknessProcessor* newObject = new 
    NodeIOBWallThicknessProcessor(initContext, initMinColorIndex, 
    initMaxColorIndex, initEnableScanWallThickness, initMinWallThickness, 
    initMaxWallThickness);
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int NodeIOBWallThicknessProcessor::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file NodeIOBWallThicknessProcessor.cpp
 * \brief Node inside/outside/boundary wall thickness processor implementation.
 */
