/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeIOBEvalProcessor.cpp        Node inside/outside/boundary evaluation 
 * processor (implementation).
 * ========================================================================== */

#include "ifvg/NodeIOBEvalProcessor.hpp"
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

NodeIOBEvalProcessorClassInfo::NodeIOBEvalProcessorClassInfo()
{
	name = "NodeIOBEvalProcessor";
	desc = "Node inside/outside/boundary evaluation processor";
	baseClassInfo.push_back(Ionflux::VolGfx::ChainableNodeProcessor::CLASS_INFO);
}

NodeIOBEvalProcessorClassInfo::~NodeIOBEvalProcessorClassInfo()
{
}

// public member constants
const double NodeIOBEvalProcessor::DEFAULT_INSIDE_VOTE_THRESHOLD = 0.9;
const unsigned int NodeIOBEvalProcessor::DEFAULT_INSIDE_MIN_VOTES = 1;

// run-time type information instance constants
const NodeIOBEvalProcessorClassInfo NodeIOBEvalProcessor::nodeIOBEvalProcessorClassInfo;
const Ionflux::ObjectBase::IFClassInfo* NodeIOBEvalProcessor::CLASS_INFO = &NodeIOBEvalProcessor::nodeIOBEvalProcessorClassInfo;

NodeIOBEvalProcessor::NodeIOBEvalProcessor()
: context(0), insideVoteThreshold(DEFAULT_INSIDE_VOTE_THRESHOLD), insideMinVotes(DEFAULT_INSIDE_MIN_VOTES), keepExistingClassification(false), voxelClassInside(VOXEL_CLASS_INSIDE), voxelClassOutside(VOXEL_CLASS_OUTSIDE)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

NodeIOBEvalProcessor::NodeIOBEvalProcessor(const Ionflux::VolGfx::NodeIOBEvalProcessor& other)
: context(0), insideVoteThreshold(DEFAULT_INSIDE_VOTE_THRESHOLD), insideMinVotes(DEFAULT_INSIDE_MIN_VOTES), keepExistingClassification(false), voxelClassInside(VOXEL_CLASS_INSIDE), voxelClassOutside(VOXEL_CLASS_OUTSIDE)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

NodeIOBEvalProcessor::NodeIOBEvalProcessor(Ionflux::VolGfx::Context* 
initContext, double initInsideVoteThreshold, unsigned int 
initInsideMinVotes, bool initKeepExistingClassification, 
Ionflux::VolGfx::VoxelClassID initVoxelClassInside, 
Ionflux::VolGfx::VoxelClassID initVoxelClassOutside)
: context(0), insideVoteThreshold(initInsideVoteThreshold), 
insideMinVotes(initInsideMinVotes), 
keepExistingClassification(initKeepExistingClassification), 
voxelClassInside(initVoxelClassInside), 
voxelClassOutside(initVoxelClassOutside)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initContext != 0)
	    setContext(initContext);
}

NodeIOBEvalProcessor::~NodeIOBEvalProcessor()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::VolGfx::NodeProcessingResultID 
NodeIOBEvalProcessor::processImpl(Ionflux::VolGfx::NodeImpl* nodeImpl, 
void* userData)
{
	if (!Node::hasImplDataType(nodeImpl, Node::DATA_TYPE_VOXEL_IOB))
	    // Node has incompatible type.
	    return RESULT_OK;
	NodeDataImpl* dp = nodeImpl->data;
	VoxelDataIOB* d0 = Ionflux::ObjectBase::nullPointerCheck(
	    static_cast<VoxelDataIOB*>(dp->data), this, 
	    "processImpl", "Voxel inside/outside/boundary data");
	unsigned int votesTotal = d0->votesInside + d0->votesOutside;
	if (votesTotal == 0)
	{
	    // No votes at all.
	    return RESULT_OK;
	}
	// assign inside/outside classification
	double insideFrac = static_cast<double>(d0->votesInside) 
	    / votesTotal;
	VoxelClassID vc = d0->voxelClass;
	if ((d0->votesInside >= insideMinVotes) 
	    && (insideFrac >= insideVoteThreshold))
	{
	    if (!keepExistingClassification
	        || !checkVoxelClass(vc, voxelClassOutside))
	    {
	        setVoxelClass(voxelClassOutside | VOXEL_CLASS_EMPTY, 
	            d0->voxelClass, false);
	        setVoxelClass(voxelClassInside, d0->voxelClass);
	    }
	} else
	{
	    if (!keepExistingClassification
	        || !checkVoxelClass(vc, voxelClassInside))
	    {
	        setVoxelClass(voxelClassInside, d0->voxelClass, false);
	        setVoxelClass(voxelClassOutside, d0->voxelClass);
	    }
	}
	/* <---- DEBUG ----- //
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "processImpl", "Context");
	std::cerr << "[NodeIOBEvalProcessor::processImpl] DEBUG: "
	    "node: [" << Node::getImplValueString(nodeImpl, context, false) 
	    << "] -> (" << getVoxelClassValueString(d0->voxelClass) << ")" 
	    << std::endl;
	// ----- DEBUG ----> */
	return RESULT_OK;
}

std::string NodeIOBEvalProcessor::getValueString() const
{
	ostringstream status;
	status << "context: ";
	if (context == 0)
	    status << "<null>";
	else
	    status << "[" << context->getValueString() << "]";
	status << "insideVoteThreshold = " << insideVoteThreshold 
	    << ", insideMinVotes = " << insideMinVotes 
	    << ", keepExistingClassification = " 
	        << Ionflux::ObjectBase::getBooleanValueString(
	            keepExistingClassification) 
	    << ", voxelClassInside = " 
	        << getVoxelClassValueString(voxelClassInside) 
	    << ", voxelClassOutside = " 
	        << getVoxelClassValueString(voxelClassOutside);
	return status.str();
}

void NodeIOBEvalProcessor::setContext(Ionflux::VolGfx::Context* newContext)
{
	if (context == newContext)
		return;
    if (newContext != 0)
        addLocalRef(newContext);
	if (context != 0)
		removeLocalRef(context);
	context = newContext;
}

Ionflux::VolGfx::Context* NodeIOBEvalProcessor::getContext() const
{
    return context;
}

void NodeIOBEvalProcessor::setInsideVoteThreshold(double 
newInsideVoteThreshold)
{
	insideVoteThreshold = newInsideVoteThreshold;
}

double NodeIOBEvalProcessor::getInsideVoteThreshold() const
{
    return insideVoteThreshold;
}

void NodeIOBEvalProcessor::setInsideMinVotes(unsigned int 
newInsideMinVotes)
{
	insideMinVotes = newInsideMinVotes;
}

unsigned int NodeIOBEvalProcessor::getInsideMinVotes() const
{
    return insideMinVotes;
}

void NodeIOBEvalProcessor::setKeepExistingClassification(bool 
newKeepExistingClassification)
{
	keepExistingClassification = newKeepExistingClassification;
}

bool NodeIOBEvalProcessor::getKeepExistingClassification() const
{
    return keepExistingClassification;
}

void 
NodeIOBEvalProcessor::setVoxelClassInside(Ionflux::VolGfx::VoxelClassID 
newVoxelClassInside)
{
	voxelClassInside = newVoxelClassInside;
}

Ionflux::VolGfx::VoxelClassID NodeIOBEvalProcessor::getVoxelClassInside() 
const
{
    return voxelClassInside;
}

void 
NodeIOBEvalProcessor::setVoxelClassOutside(Ionflux::VolGfx::VoxelClassID 
newVoxelClassOutside)
{
	voxelClassOutside = newVoxelClassOutside;
}

Ionflux::VolGfx::VoxelClassID NodeIOBEvalProcessor::getVoxelClassOutside() 
const
{
    return voxelClassOutside;
}

Ionflux::VolGfx::NodeIOBEvalProcessor& 
NodeIOBEvalProcessor::operator=(const 
Ionflux::VolGfx::NodeIOBEvalProcessor& other)
{
    if (this == &other)
        return *this;
    setInsideVoteThreshold(other.insideVoteThreshold);
    setInsideMinVotes(other.insideMinVotes);
    setKeepExistingClassification(other.keepExistingClassification);
    setVoxelClassInside(other.voxelClassInside);
    setVoxelClassOutside(other.voxelClassOutside);
	return *this;
}

Ionflux::VolGfx::NodeIOBEvalProcessor* NodeIOBEvalProcessor::copy() const
{
    NodeIOBEvalProcessor* newNodeIOBEvalProcessor = create();
    *newNodeIOBEvalProcessor = *this;
    return newNodeIOBEvalProcessor;
}

Ionflux::VolGfx::NodeIOBEvalProcessor* 
NodeIOBEvalProcessor::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<NodeIOBEvalProcessor*>(other);
}

Ionflux::VolGfx::NodeIOBEvalProcessor* 
NodeIOBEvalProcessor::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    NodeIOBEvalProcessor* newObject = new NodeIOBEvalProcessor();
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::VolGfx::NodeIOBEvalProcessor* 
NodeIOBEvalProcessor::create(Ionflux::VolGfx::Context* initContext, double 
initInsideVoteThreshold, unsigned int initInsideMinVotes, bool 
initKeepExistingClassification, Ionflux::VolGfx::VoxelClassID 
initVoxelClassInside, Ionflux::VolGfx::VoxelClassID initVoxelClassOutside, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    NodeIOBEvalProcessor* newObject = new NodeIOBEvalProcessor(initContext,
    initInsideVoteThreshold, initInsideMinVotes, 
    initKeepExistingClassification, initVoxelClassInside, 
    initVoxelClassOutside);
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int NodeIOBEvalProcessor::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file NodeIOBEvalProcessor.cpp
 * \brief Node inside/outside/boundary evaluation processor implementation.
 */
