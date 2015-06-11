/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeFilter.cpp                  Node filter (implementation).
 * ========================================================================== */

#include "ifvg/NodeFilter.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "ifvg/utils.hpp"
#include "ifvg/IFVGError.hpp"
#include "ifvg/Context.hpp"

using namespace std;

namespace Ionflux
{

namespace VolGfx
{

NodeFilterClassInfo::NodeFilterClassInfo()
{
	name = "NodeFilter";
	desc = "Node filter";
	baseClassInfo.push_back(Ionflux::VolGfx::ChainableNodeProcessor::CLASS_INFO);
}

NodeFilterClassInfo::~NodeFilterClassInfo()
{
}

// public member constants
const Ionflux::VolGfx::NodeProcessingResultID NodeFilter::RESULT_PASS = 8;

// run-time type information instance constants
const NodeFilterClassInfo NodeFilter::nodeFilterClassInfo;
const Ionflux::ObjectBase::IFClassInfo* NodeFilter::CLASS_INFO = &NodeFilter::nodeFilterClassInfo;

NodeFilter::NodeFilter()
: context(0), minDepth(DEPTH_UNSPECIFIED), maxDepth(DEPTH_UNSPECIFIED), leafStatus(NODE_ANY), dataType(Node::DATA_TYPE_UNKNOWN), voxelClass(VOXEL_CLASS_UNDEFINED), region(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

NodeFilter::NodeFilter(const Ionflux::VolGfx::NodeFilter& other)
: context(0), minDepth(DEPTH_UNSPECIFIED), maxDepth(DEPTH_UNSPECIFIED), leafStatus(NODE_ANY), dataType(Node::DATA_TYPE_UNKNOWN), voxelClass(VOXEL_CLASS_UNDEFINED), region(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

NodeFilter::NodeFilter(Ionflux::VolGfx::Context* initContext, int 
initMinDepth, int initMaxDepth, Ionflux::VolGfx::LeafStatusID 
initLeafStatus, Ionflux::VolGfx::NodeDataType initDataType, 
Ionflux::VolGfx::VoxelClassID initVoxelClass, Ionflux::GeoUtils::Range3* 
initRegion)
: context(0), minDepth(initMinDepth), maxDepth(initMaxDepth), 
leafStatus(initLeafStatus), dataType(initDataType), 
voxelClass(initVoxelClass), region(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initContext != 0)
	    setContext(initContext);
	if (initRegion)
	    setRegion(initRegion);
}

NodeFilter::~NodeFilter()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::VolGfx::NodeProcessingResultID 
NodeFilter::processImpl(Ionflux::VolGfx::NodeImpl* nodeImpl, void* 
userData)
{
	if (filter(nodeImpl, userData))
	    return RESULT_OK | RESULT_PASS;
	return RESULT_OK | RESULT_FINISHED;
}

bool NodeFilter::filter(Ionflux::VolGfx::NodeImpl* nodeImpl, void* 
userData)
{
	Ionflux::ObjectBase::nullPointerCheck(nodeImpl, this, 
	    "filter", "Node implementation");
	if (context != 0)
	{
	    // depth check
	    if ((minDepth != DEPTH_UNSPECIFIED)
	        || (maxDepth != DEPTH_UNSPECIFIED))
	    {
	        int depth = Node::getImplDepth(nodeImpl, context);
	        if ((minDepth != DEPTH_UNSPECIFIED) 
	            && (depth < minDepth))
	                return false;
	        if ((maxDepth != DEPTH_UNSPECIFIED) 
	            && (depth > maxDepth))
	                return false;
	    }
	    if (region != 0)
	    {
	        // region check.
	        Ionflux::GeoUtils::Range3 r0;
	        Node::getImplRange(nodeImpl, context, r0);
	        if (!region->isInRange(r0.getCenter()))
	            return false;
	    }
	}
	if (dataType != Node::DATA_TYPE_UNKNOWN)
	{
	    // data type check
	    if (!Node::hasImplDataType(nodeImpl, dataType))
	        return false;
	}
	if ((leafStatus != NODE_ANY) 
	    && (leafStatus != Node::getImplLeafStatus(nodeImpl)))
	{
	    // leaf check
	    return false;
	}
	if ((voxelClass != VOXEL_CLASS_UNDEFINED) 
	    && !Node::hasImplVoxelClass(nodeImpl, voxelClass))
	    // voxel class check
	    return false;
	return true;
}

bool NodeFilter::filter(Ionflux::VolGfx::Node* node, void* userData)
{
	Ionflux::ObjectBase::nullPointerCheck(node, this, 
	    "filter", "Node");
	return filter(node->getImpl());
}

void NodeFilter::setDepthRange(int newMinDepth, int newMaxDepth)
{
	setMinDepth(newMinDepth);
	setMaxDepth(newMaxDepth);
}

std::string NodeFilter::getValueString() const
{
	ostringstream status;
	status << ChainableNodeProcessor::getValueString();
	status << "; context: ";
	if (context != 0)
	    status << "[" << context->getValueString() << "]";
	else
	    status << "<null>";
	status << ", minDepth = " << getDepthString(minDepth) 
	    << ", maxDepth = " << getDepthString(maxDepth) 
	    << ", leafStatus = " << getLeafStatusValueString(leafStatus) 
	    << ", dataType = " << Node::getDataTypeString(dataType) 
	    << ", voxelClass = " << getVoxelClassValueString(voxelClass);
	if (region != 0)
	    status << ", region = [" << region->getValueString() << "]";
	return status.str();
}

void NodeFilter::setContext(Ionflux::VolGfx::Context* newContext)
{
	context = newContext;
}

Ionflux::VolGfx::Context* NodeFilter::getContext() const
{
    return context;
}

void NodeFilter::setMinDepth(int newMinDepth)
{
	minDepth = newMinDepth;
}

int NodeFilter::getMinDepth() const
{
    return minDepth;
}

void NodeFilter::setMaxDepth(int newMaxDepth)
{
	maxDepth = newMaxDepth;
}

int NodeFilter::getMaxDepth() const
{
    return maxDepth;
}

void NodeFilter::setLeafStatus(Ionflux::VolGfx::LeafStatusID newLeafStatus)
{
	leafStatus = newLeafStatus;
}

Ionflux::VolGfx::LeafStatusID NodeFilter::getLeafStatus() const
{
    return leafStatus;
}

void NodeFilter::setDataType(Ionflux::VolGfx::NodeDataType newDataType)
{
	dataType = newDataType;
}

Ionflux::VolGfx::NodeDataType NodeFilter::getDataType() const
{
    return dataType;
}

void NodeFilter::setVoxelClass(Ionflux::VolGfx::VoxelClassID newVoxelClass)
{
	voxelClass = newVoxelClass;
}

Ionflux::VolGfx::VoxelClassID NodeFilter::getVoxelClass() const
{
    return voxelClass;
}

void NodeFilter::setRegion(Ionflux::GeoUtils::Range3* newRegion)
{
	if (region == newRegion)
		return;
    if (newRegion != 0)
        addLocalRef(newRegion);
	if (region != 0)
		removeLocalRef(region);
	region = newRegion;
}

Ionflux::GeoUtils::Range3* NodeFilter::getRegion() const
{
    return region;
}

Ionflux::VolGfx::NodeFilter& NodeFilter::operator=(const 
Ionflux::VolGfx::NodeFilter& other)
{
    if (this == &other)
        return *this;
    setContext(other.context);
    setMinDepth(other.minDepth);
    setMaxDepth(other.maxDepth);
    setLeafStatus(other.leafStatus);
    setDataType(other.dataType);
    setVoxelClass(other.voxelClass);
	return *this;
}

Ionflux::VolGfx::NodeFilter* NodeFilter::copy() const
{
    NodeFilter* newNodeFilter = create();
    *newNodeFilter = *this;
    return newNodeFilter;
}

Ionflux::VolGfx::NodeFilter* 
NodeFilter::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<NodeFilter*>(other);
}

Ionflux::VolGfx::NodeFilter* 
NodeFilter::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    NodeFilter* newObject = new NodeFilter();
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::VolGfx::NodeFilter* NodeFilter::create(Ionflux::VolGfx::Context* 
initContext, int initMinDepth, int initMaxDepth, 
Ionflux::VolGfx::LeafStatusID initLeafStatus, Ionflux::VolGfx::NodeDataType
initDataType, Ionflux::VolGfx::VoxelClassID initVoxelClass, 
Ionflux::GeoUtils::Range3* initRegion, Ionflux::ObjectBase::IFObject* 
parentObject)
{
    NodeFilter* newObject = new NodeFilter(initContext, initMinDepth, 
    initMaxDepth, initLeafStatus, initDataType, initVoxelClass, 
    initRegion);
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int NodeFilter::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file NodeFilter.cpp
 * \brief Node filter implementation.
 */
