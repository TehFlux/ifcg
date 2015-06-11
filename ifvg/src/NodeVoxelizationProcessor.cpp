/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeVoxelizationProcessor.cpp   Node voxelization processor 
 * (implementation).
 * ========================================================================== */

#include "ifvg/NodeVoxelizationProcessor.hpp"
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

NodeVoxelizationProcessorClassInfo::NodeVoxelizationProcessorClassInfo()
{
	name = "NodeVoxelizationProcessor";
	desc = "Node voxelization processor";
	baseClassInfo.push_back(Ionflux::VolGfx::ChainableNodeProcessor::CLASS_INFO);
}

NodeVoxelizationProcessorClassInfo::~NodeVoxelizationProcessorClassInfo()
{
}

// run-time type information instance constants
const NodeVoxelizationProcessorClassInfo NodeVoxelizationProcessor::nodeVoxelizationProcessorClassInfo;
const Ionflux::ObjectBase::IFClassInfo* NodeVoxelizationProcessor::CLASS_INFO = &NodeVoxelizationProcessor::nodeVoxelizationProcessorClassInfo;

NodeVoxelizationProcessor::NodeVoxelizationProcessor()
: target(VOXELIZATION_TARGET_DENSITY)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

NodeVoxelizationProcessor::NodeVoxelizationProcessor(const Ionflux::VolGfx::NodeVoxelizationProcessor& other)
: target(VOXELIZATION_TARGET_DENSITY)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

NodeVoxelizationProcessor::~NodeVoxelizationProcessor()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::VolGfx::NodeProcessingResultID 
NodeVoxelizationProcessor::processImpl(Ionflux::VolGfx::NodeImpl* nodeImpl,
void* userData)
{
	NodeDataImpl* d0 = 0;
	if (target == VOXELIZATION_TARGET_CLASS)
	{
	    // attach voxel class data
	    d0 = Node::getImplData(nodeImpl, Node::DATA_TYPE_VOXEL_CLASS);
	    VoxelClassID c0;
	    unpackVoxelClass(d0->data, c0);
	    setVoxelClass(VOXEL_CLASS_EMPTY, c0, false);
	    setVoxelClass(VOXEL_CLASS_FILLED, c0);
	    packVoxelClass(c0, d0->data);
	} else
	if (target == VOXELIZATION_TARGET_DENSITY)
	{
	    // attach density data
	    d0 = Node::getImplData(nodeImpl, Node::DATA_TYPE_DENSITY);
	    NodeDataValue* dv = 
	        Ionflux::ObjectBase::nullPointerCheck(
	            static_cast<NodeDataValue*>(d0->data), this, 
	                "processImpl", "Data pointer");
	    *dv = DENSITY_FILLED;
	} else
	if (target == VOXELIZATION_TARGET_COLOR_NORMAL)
	{
	    // attach color/normal data
	    d0 = Node::getImplData(nodeImpl, Node::DATA_TYPE_COLOR_NORMAL);
	    Ionflux::Altjira::Color ac0;
	    Ionflux::GeoUtils::Vector3 an0;
	    Node::getImplFaceColorNormal(nodeImpl, ac0, an0, true);
	    Node::setDataImplColorNormal(d0, ac0, an0);
	}
	return RESULT_OK;
}

std::string NodeVoxelizationProcessor::getValueString() const
{
	ostringstream status;
	status << getVoxelizationTargetValueString(target);
	return status.str();
}

void 
NodeVoxelizationProcessor::setTarget(Ionflux::VolGfx::VoxelizationTargetID 
newTarget)
{
	target = newTarget;
}

Ionflux::VolGfx::VoxelizationTargetID 
NodeVoxelizationProcessor::getTarget() const
{
    return target;
}

Ionflux::VolGfx::NodeVoxelizationProcessor& 
NodeVoxelizationProcessor::operator=(const 
Ionflux::VolGfx::NodeVoxelizationProcessor& other)
{
    if (this == &other)
        return *this;
    setTarget(other.target);
	return *this;
}

Ionflux::VolGfx::NodeVoxelizationProcessor* 
NodeVoxelizationProcessor::copy() const
{
    NodeVoxelizationProcessor* newNodeVoxelizationProcessor = create();
    *newNodeVoxelizationProcessor = *this;
    return newNodeVoxelizationProcessor;
}

Ionflux::VolGfx::NodeVoxelizationProcessor* 
NodeVoxelizationProcessor::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<NodeVoxelizationProcessor*>(other);
}

Ionflux::VolGfx::NodeVoxelizationProcessor* 
NodeVoxelizationProcessor::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    NodeVoxelizationProcessor* newObject = new NodeVoxelizationProcessor();
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int NodeVoxelizationProcessor::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file NodeVoxelizationProcessor.cpp
 * \brief Node voxelization processor implementation.
 */
