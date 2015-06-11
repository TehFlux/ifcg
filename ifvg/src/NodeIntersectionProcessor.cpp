/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeIntersectionProcessor.cpp   Node intersection processor 
 * (implementation).
 * ========================================================================== */

#include "ifvg/NodeIntersectionProcessor.hpp"
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
#include "ifvg/NodeFilter.hpp"

using namespace std;

namespace Ionflux
{

namespace VolGfx
{

NodeIntersectionProcessorClassInfo::NodeIntersectionProcessorClassInfo()
{
	name = "NodeIntersectionProcessor";
	desc = "Node intersection processor";
	baseClassInfo.push_back(Ionflux::VolGfx::ChainableNodeProcessor::CLASS_INFO);
}

NodeIntersectionProcessorClassInfo::~NodeIntersectionProcessorClassInfo()
{
}

// run-time type information instance constants
const NodeIntersectionProcessorClassInfo NodeIntersectionProcessor::nodeIntersectionProcessorClassInfo;
const Ionflux::ObjectBase::IFClassInfo* NodeIntersectionProcessor::CLASS_INFO = &NodeIntersectionProcessor::nodeIntersectionProcessorClassInfo;

NodeIntersectionProcessor::NodeIntersectionProcessor()
: context(0), hitDataType(Node::DATA_TYPE_UNKNOWN), voxelClassHit(VOXEL_CLASS_UNDEFINED), leafStatus(NODE_LEAF), ray(0), enableBoundaryData(false), targetDepth(DEPTH_UNSPECIFIED), fillNewIntersections(true), pruneEmptyNewIntersections(false), enableIOB(true), enableRayStabbing(false), enableWallThickness(false), voxelClassFilled(VOXEL_CLASS_FILLED), voxelClassInside(VOXEL_CLASS_INSIDE), voxelClassOutside(VOXEL_CLASS_OUTSIDE), voxelClassBoundary(VOXEL_CLASS_BOUNDARY), tolerance(DEFAULT_TOLERANCE), rayAxis(Ionflux::GeoUtils::AXIS_UNDEFINED), minWallThickness(0), fillInsideOnly(true), maxNumWallThicknessPasses(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

NodeIntersectionProcessor::NodeIntersectionProcessor(const Ionflux::VolGfx::NodeIntersectionProcessor& other)
: context(0), hitDataType(Node::DATA_TYPE_UNKNOWN), voxelClassHit(VOXEL_CLASS_UNDEFINED), leafStatus(NODE_LEAF), ray(0), enableBoundaryData(false), targetDepth(DEPTH_UNSPECIFIED), fillNewIntersections(true), pruneEmptyNewIntersections(false), enableIOB(true), enableRayStabbing(false), enableWallThickness(false), voxelClassFilled(VOXEL_CLASS_FILLED), voxelClassInside(VOXEL_CLASS_INSIDE), voxelClassOutside(VOXEL_CLASS_OUTSIDE), voxelClassBoundary(VOXEL_CLASS_BOUNDARY), tolerance(DEFAULT_TOLERANCE), rayAxis(Ionflux::GeoUtils::AXIS_UNDEFINED), minWallThickness(0), fillInsideOnly(true), maxNumWallThicknessPasses(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

NodeIntersectionProcessor::NodeIntersectionProcessor(Ionflux::VolGfx::Context*
initContext, Ionflux::VolGfx::NodeDataType initHitDataType, 
Ionflux::VolGfx::VoxelClassID initVoxelClassHit, 
Ionflux::VolGfx::LeafStatusID initLeafStatus, Ionflux::GeoUtils::Line3* 
initRay, bool initEnableBoundaryData, int initTargetDepth, bool 
initFillNewIntersections, bool initPruneEmptyNewIntersections, bool 
initEnableIOB, bool initEnableRayStabbing, bool initEnableWallThickness, 
Ionflux::VolGfx::VoxelClassID initVoxelClassFilled, 
Ionflux::VolGfx::VoxelClassID initVoxelClassInside, 
Ionflux::VolGfx::VoxelClassID initVoxelClassOutside, 
Ionflux::VolGfx::VoxelClassID initVoxelClassBoundary, double initTolerance,
unsigned int initMinWallThickness, bool initFillInsideOnly, unsigned int 
initMaxNumWallThicknessPasses)
: context(0), hitDataType(initHitDataType), 
voxelClassHit(initVoxelClassHit), leafStatus(initLeafStatus), ray(0), 
enableBoundaryData(initEnableBoundaryData), targetDepth(initTargetDepth), 
fillNewIntersections(initFillNewIntersections), 
pruneEmptyNewIntersections(initPruneEmptyNewIntersections), 
enableIOB(initEnableIOB), enableRayStabbing(initEnableRayStabbing), 
enableWallThickness(initEnableWallThickness), 
voxelClassFilled(initVoxelClassFilled), 
voxelClassInside(initVoxelClassInside), 
voxelClassOutside(initVoxelClassOutside), 
voxelClassBoundary(initVoxelClassBoundary), tolerance(initTolerance), 
rayAxis(Ionflux::GeoUtils::AXIS_UNDEFINED), 
minWallThickness(initMinWallThickness), fillInsideOnly(initFillInsideOnly),
maxNumWallThicknessPasses(initMaxNumWallThicknessPasses)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initContext != 0)
	    setContext(initContext);
	if (initRay != 0)
	    setRay(initRay);
}

NodeIntersectionProcessor::~NodeIntersectionProcessor()
{
	clearIntersections();
	// TODO: Nothing ATM. ;-)
}

void NodeIntersectionProcessor::updateIntersections(bool reverse)
{
	// <---- DEBUG ----- //
	for (unsigned int i = 0; i < updatedIntersections.size(); i++)
	{
	    NodeIntersection ci0 = updatedIntersections[i];
	    NodeImpl* ni0 = ci0.nodeImpl;
	    LeafStatusID ls0 = Node::getImplLeafStatus(ni0);
	    NodeID nid0 = Node::getImplNodeID(ni0, context);
	    if ((leafStatus != NODE_ANY) 
	        && (ls0 != leafStatus))
	    {
	        std::ostringstream status;
	        status << "Leaf status flag mismatch for updated node #" << i 
	            << " " << ni0 << " [" << getNodeIDValueString(nid0, 
	                false, true, true, context) << "]" 
	            << " (current: " << getLeafStatusValueString(ls0) 
	            << ", expected: " << getLeafStatusValueString(leafStatus) 
	            << ").";
	        throw IFVGError(getErrorString(status.str(), 
	            "updateIntersections"));
	    }
	}
	// ----- DEBUG ----> */
	if (updatedIntersections.size() > intersections.size())
	{
	    if (!reverse)
	        intersections = updatedIntersections;
	    else
	    {
	        clearIntersections();
	        unsigned int n0 = updatedIntersections.size();
	        for (unsigned int i = 0; i < n0; i++)
	        {
	            NodeIntersection ci0 = updatedIntersections[n0 - i - 1];
	            intersections.push_back(ci0);
	        }
	    }
	}
	updatedIntersections.clear();
}

Ionflux::VolGfx::NodeProcessingResultID 
NodeIntersectionProcessor::processImpl(Ionflux::VolGfx::NodeImpl* nodeImpl,
void* userData)
{
	if (userData == 0)
	    return RESULT_OK;
	const NodeIntersection* ni = 
	    reinterpret_cast<const NodeIntersection*>(userData);
	processIntersection(*ni, userData);
	return RESULT_OK;
}

void NodeIntersectionProcessor::processIntersectionsIOB(const 
Ionflux::VolGfx::NodeIntersectionVector& intersections0, 
Ionflux::VolGfx::VoxelClassID& state, unsigned int& numIntersections0, 
Ionflux::VolGfx::NodeIntersectionProcessingFlags processingFlags, unsigned 
int* wallThickness, unsigned int* maxWallThickness)
{
	unsigned int n0 = intersections0.size();
	if (n0 == 0)
	    return;
	if (processingFlags.enableWallThickness)
	{
	    Ionflux::ObjectBase::nullPointerCheck(wallThickness, this,  
	        "processIntersectionsWallThickness", "Wall thickness counter");
	    Ionflux::ObjectBase::nullPointerCheck(maxWallThickness, this,  
	        "processIntersectionsWallThickness", 
	        "Maximum wall thickness counter");
	}
	if (!processingFlags.directionBackward)
	{
	    for (unsigned int i = 0; i < n0; i++)
	    {
	        NodeIntersection ci0 = intersections0[i];
	        processIOBStep(ci0, state, numIntersections0, processingFlags, 
	            wallThickness, maxWallThickness);
	    }
	} else
	{
	    for (unsigned int i = n0; i > 0; i--)
	    {
	        NodeIntersection ci0 = intersections0[i - 1];
	        processIOBStep(ci0, state, numIntersections0, processingFlags, 
	            wallThickness, maxWallThickness);
	    }
	}
}

void NodeIntersectionProcessor::createAndProcessIntersectionsIOB(const 
Ionflux::VolGfx::NodeIntersection& intersection0, bool createNear, bool 
createFar, Ionflux::VolGfx::VoxelClassID& state, unsigned int& 
numIntersections0, Ionflux::VolGfx::NodeIntersectionProcessingFlags 
processingFlags, unsigned int* wallThickness, unsigned int* 
maxWallThickness)
{
	NodeIntersectionVector niv0;
	unsigned int n0 = createIntersections(intersection0, 
	    niv0, createNear, createFar);
	if (n0 == 0)
	{
	    throw IFVGError(getErrorString(
	        "Could not create new node intersections.", 
	        "createAndProcessIntersectionsIOB"));
	}
	// process new intersections recursively
	processIntersectionsIOB(niv0, state, numIntersections0, 
	    processingFlags, wallThickness, maxWallThickness);
}

void NodeIntersectionProcessor::processIOBStep(const 
Ionflux::VolGfx::NodeIntersection& intersection0, 
Ionflux::VolGfx::VoxelClassID& state, unsigned int& numIntersections0, 
Ionflux::VolGfx::NodeIntersectionProcessingFlags processingFlags, unsigned 
int* wallThickness, unsigned int* maxWallThickness)
{
	if (processingFlags.enableBoundaryData 
	    || processingFlags.enableWallThickness)
	{
	    Ionflux::ObjectBase::nullPointerCheck(
	        context, this, "processIOBStep", "Context");
	}
	NodeImpl* ni = Ionflux::ObjectBase::nullPointerCheck(
	    intersection0.nodeImpl, this, "processIOBStep", 
	    "Node implementation");
	int maxNumLevels = DEPTH_UNSPECIFIED;
	bool createNear = false;
	bool createFar = false;
	if (processingFlags.enableBoundaryData)
	{
	    // parameters required for boundary voxel classification
	    maxNumLevels = context->getMaxNumLevels();
	    if ((targetDepth < 0) 
	        || (targetDepth >= maxNumLevels))
	        targetDepth = maxNumLevels - 1;
	    if (!processingFlags.directionBackward)
	    {
	        // ray enters boundary voxel at near intersection point
	        createNear = true;
	        createFar = false;
	    } else
	    {
	        // ray leaves boundary voxel at far intersection point
	        createNear = false;
	        createFar = true;
	    }
	}
	LeafStatusID ls0 = Node::getImplLeafStatus(ni);
	if ((leafStatus != NODE_ANY) 
	    && (ls0 != leafStatus))
	{
	    std::ostringstream status;
	    status << "Leaf status flag mismatch (current: " 
	        << getLeafStatusValueString(ls0) << ", expected: " 
	        << getLeafStatusValueString(leafStatus) << ").";
	    throw IFVGError(getErrorString(status.str(), "processIOBStep"));
	}
	unsigned int wtStep = 0;
	if (processingFlags.enableWallThickness)
	{
	    if (rayAxis == Ionflux::GeoUtils::AXIS_UNDEFINED)
	    {
	        processingFlags.enableWallThickness = false;
	    } else 
	    {
	        // parameters required for wall thickness calculation
	        wtStep = context->getDepthMask(intersection0.depth).to_ulong();
	    }
	}
	VoxelClassID vc = Node::getImplVoxelClass(ni);
	/* <---- DEBUG ----- //
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "processIOBStep", "Context");
	NodeID nid0 = Node::getImplNodeID(ni, context);
	std::cerr << "[NodeIntersectionProcessor::processIOBStep] DEBUG: ";
	if (directionBackward)
	    std::cerr << "(backward) ";
	std::cerr << "node: [" << getNodeIDValueString(nid0, 
	    true, true, true, context) 
	    << "] voxelClass = " << getVoxelClassValueString(vc) 
	    << ", state = " << getVoxelClassValueString(state) 
	    << ", numIntersections = " << numIntersections0;
	if (enableWallThickness0)
	{
	    std::cerr << ", rayAxis = " 
	        << Ionflux::GeoUtils::axisToString(rayAxis)
	        << ", wallThickness = " << *wallThickness 
	        << ", maxWallThickness = " << *maxWallThickness 
	        << ", wtStep = " << wtStep;
	}
	std::cerr << std::endl;
	// ----- DEBUG ----> */
	/* set current state according to previous state and current 
	   voxel class */
	VoxelClassID ps = state;
	bool split0 = false;
	bool boundary = false;
	VoxelDataIOB* d0 = 0;
	if (ps == VOXEL_CLASS_UNDEFINED)
	{
	    if (checkVoxelClass(vc, voxelClassFilled))
	    {
	        state = VOXEL_CLASS_INSIDE;
	        if (processingFlags.enableWallThickness)
	        {
	            // initialize wall thickness data for inside voxel
	            *wallThickness = wtStep;
	            d0 = getIOBData(intersection0);
	            *maxWallThickness = getIOBDataWallThickness(*d0, rayAxis);
	            /* <---- DEBUG ----- //
	            std::cerr << "[NodeIntersectionProcessor::"
	                "processIOBStep] DEBUG: "
	                << "(undefined -> inside) "
	                    "initializing wall thickness data (" 
	                << "wallThickness = " << *wallThickness 
	                << ", maxWallThickness = " << *maxWallThickness << ")" 
	                << std::endl;
	            // ----- DEBUG ----> */
	        }
	    } else
	        state = VOXEL_CLASS_OUTSIDE;
	} else
	if (ps == VOXEL_CLASS_INSIDE)
	{
	    if (!checkVoxelClass(vc, voxelClassFilled))
	    {
	        // inside -> outside
	        if (processingFlags.enableWallThickness)
	        {
	            // reset wall thickness data
	            *wallThickness = 0;
	            *maxWallThickness = 0;
	            /* <---- DEBUG ----- //
	            std::cerr << "[NodeIntersectionProcessor::"
	                "processIOBStep] DEBUG: "
	                << "(inside -> outside) resetting wall thickness data (" 
	                << "wallThickness = " << *wallThickness 
	                << ", maxWallThickness = " << *maxWallThickness << ")" 
	                << std::endl;
	            // ----- DEBUG ----> */
	        }
	        if (processingFlags.enableBoundaryData)
	        {
	            if (intersection0.depth == targetDepth)
	            {
	                // boundary voxel at target depth
	                boundary = true;
	            } else
	            {
	                // insert boundary voxel at target depth
	                createAndProcessIntersectionsIOB(intersection0, 
	                    createNear, createFar, state, numIntersections0, 
	                    processingFlags, wallThickness, maxWallThickness);
	                split0 = true;
	            }
	        }
	        if (!split0)
	        {
	            state = VOXEL_CLASS_OUTSIDE;
	            numIntersections0++;
	        }
	    } else
	    {
	        // inside -> inside
	        if (processingFlags.enableWallThickness)
	        {
	            *wallThickness += wtStep;
	            /* <---- DEBUG ----- //
	            std::cerr << "[NodeIntersectionProcessor::"
	                "processIOBStep] DEBUG: "
	                << "(inside -> inside) " 
	                << "wallThickness = " << *wallThickness 
	                << ", maxWallThickness = " << *maxWallThickness 
	                << std::endl;
	            // ----- DEBUG ----> */
	        }
	    }
	} else
	if (ps == VOXEL_CLASS_OUTSIDE)
	{
	    if (checkVoxelClass(vc, voxelClassFilled))
	    {
	        // outside -> inside
	        state = VOXEL_CLASS_INSIDE;
	        if (processingFlags.enableWallThickness)
	        {
	            // initialize wall thickness data for inside voxel
	            *wallThickness = wtStep;
	            d0 = getIOBData(intersection0);
	            *maxWallThickness = getIOBDataWallThickness(*d0, rayAxis);
	            /* <---- DEBUG ----- //
	            std::cerr << "[NodeIntersectionProcessor::"
	                "processIOBStep] DEBUG: "
	                << "(outside -> inside) initializing wall thickness "
	                    "for inside voxel (" 
	                << "wallThickness = " << *wallThickness 
	                << ", maxWallThickness = " << *maxWallThickness << ")"
	                << std::endl;
	            // ----- DEBUG ----> */
	        }
	    }
	}
	if (split0)
	{
	    // node intersection has been split and processed recursively
	    return;
	}
	// update the node data
	if (d0 == 0)
	    d0 = getIOBData(intersection0);
	if (!processingFlags.directionBackward)
	{
	    // foward iteration
	    d0->numInts0 = numIntersections0;
	    if (boundary)
	    {
	        // set boundary faces
	        d0->boundaryFaces |= intersection0.intersection.nearPlane;
	    }
	} else
	{
	    // backward iteration
	    d0->numInts1 = numIntersections0;
	    if (processingFlags.enableRayStabbing 
	        && ((d0->numInts0 == 0)
	            || (d0->numInts1 == 0)))
	    {
	        // set node with zero intersections to outside (ray-stabbing)
	        vc |= voxelClassOutside;
	    }
	    if (processingFlags.castVotes)
	    {
	        // set ray votes
	        if ((d0->numInts0 % 2) == 0)
	            d0->votesOutside++;
	        else
	            d0->votesInside++;
	        if ((d0->numInts1 % 2) == 0)
	            d0->votesOutside++;
	        else
	            d0->votesInside++;
	    }
	    if (boundary)
	    {
	        // set boundary faces
	        d0->boundaryFaces |= intersection0.intersection.farPlane;
	    }
	}
	if (boundary)
	    setVoxelClass(voxelClassBoundary, vc);
	setVoxelClass(vc, d0->voxelClass);
	if (processingFlags.enableWallThickness)
	{
	    unsigned int wt0 = *wallThickness;
	    if (*maxWallThickness > wt0)
	        wt0 = *maxWallThickness;
	    /* <---- DEBUG ----- //
	    std::cerr << "[NodeIntersectionProcessor::"
	        "processIOBStep] DEBUG: setting wall thickness = " 
	        << wt0 << std::endl;
	    // ----- DEBUG ----> */
	    setIOBDataWallThickness(*d0, rayAxis, wt0);
	}
	/* <---- DEBUG ----- //
	NodeID nid0 = Node::getImplNodeID(ni, context);
	std::cerr << "[NodeIntersectionProcessor::"
	    "processIOBStep] DEBUG: ";
	if (processingFlags.directionBackward)
	    std::cerr << "(backward) ";
	std::cerr << "finished node: " << ni 
	    << " [" << getNodeIDValueString(nid0, 
	        false, true, true, context) 
	    << "] voxelClass = " << getVoxelClassValueString(vc) 
	    << ", state = " << getVoxelClassValueString(state);
	std::cerr << std::endl;
	// ----- DEBUG ----> */
	updatedIntersections.push_back(intersection0);
}

void NodeIntersectionProcessor::processIntersectionsWallThickness(const 
Ionflux::VolGfx::NodeIntersectionVector& intersections0, 
Ionflux::VolGfx::VoxelClassID& state, 
Ionflux::VolGfx::NodeIntersectionProcessingFlags processingFlags, unsigned 
int& wallThickness, unsigned int& maxWallThickness, unsigned int 
minWallThickness0, unsigned int maxNumFillNodes, bool insideOnly, unsigned 
int* numThinComponents, unsigned int* numNodesFilled)
{
	unsigned int n0 = intersections0.size();
	if (n0 == 0)
	    return;
	if (minWallThickness > 0)
	{
	    Ionflux::ObjectBase::nullPointerCheck(numThinComponents, this,  
	        "processIntersectionsWallThickness", "Thin component counter");
	    Ionflux::ObjectBase::nullPointerCheck(numNodesFilled, this,  
	        "processIntersectionsWallThickness", "Filled nodes counter");
	}
	if (!processingFlags.directionBackward)
	{
	    for (unsigned int i = 0; i < n0; i++)
	    {
	        NodeIntersection ci0 = intersections0[i];
	        processWallThicknessStep(ci0, state, processingFlags, 
	            wallThickness, maxWallThickness, minWallThickness0, 
	            maxNumFillNodes, insideOnly, numThinComponents, 
	            numNodesFilled);
	    }
	} else
	{
	    for (unsigned int i = n0; i > 0; i--)
	    {
	        NodeIntersection ci0 = intersections0[i - 1];
	        processWallThicknessStep(ci0, state, processingFlags, 
	            wallThickness, maxWallThickness, minWallThickness0, 
	            maxNumFillNodes, insideOnly, numThinComponents, 
	            numNodesFilled);
	    }
	}
}

void 
NodeIntersectionProcessor::createAndProcessIntersectionsWallThickness(const
Ionflux::VolGfx::NodeIntersection& intersection0, bool createNear, bool 
createFar, Ionflux::VolGfx::VoxelClassID& state, 
Ionflux::VolGfx::NodeIntersectionProcessingFlags processingFlags, unsigned 
int& wallThickness, unsigned int& maxWallThickness, unsigned int 
minWallThickness0, unsigned int maxNumFillNodes, bool insideOnly, unsigned 
int* numThinComponents, unsigned int* numNodesFilled)
{
	NodeIntersectionVector niv0;
	unsigned int n0 = createIntersections(intersection0, 
	    niv0, createNear, createFar);
	if (n0 == 0)
	{
	    throw IFVGError(getErrorString(
	        "Could not create new node intersections.", 
	        "createAndProcessIntersectionsWallThickness"));
	}
	// process new intersections recursively
	processIntersectionsWallThickness(niv0, state, processingFlags, 
	    wallThickness, maxWallThickness, minWallThickness0, maxNumFillNodes, 
	    insideOnly, numThinComponents, numNodesFilled);
}

void NodeIntersectionProcessor::processWallThicknessStep(const 
Ionflux::VolGfx::NodeIntersection& intersection0, 
Ionflux::VolGfx::VoxelClassID& state, 
Ionflux::VolGfx::NodeIntersectionProcessingFlags processingFlags, unsigned 
int& wallThickness, unsigned int& maxWallThickness, unsigned int 
minWallThickness0, unsigned int maxNumFillNodes, bool insideOnly, unsigned 
int* numThinComponents, unsigned int* numNodesFilled)
{
	Ionflux::ObjectBase::nullPointerCheck(
	    context, this, "processWallThicknessStep", "Context");
	NodeImpl* ni = Ionflux::ObjectBase::nullPointerCheck(
	    intersection0.nodeImpl, this, "processWallThicknessStep", 
	    "Node implementation");
	int maxNumLevels = context->getMaxNumLevels();
	bool createNear = false;
	bool createFar = false;
	if ((targetDepth < 0) 
	    || (targetDepth >= maxNumLevels))
	    targetDepth = maxNumLevels - 1;
	if (!processingFlags.directionBackward)
	{
	    // ray enters boundary voxel at near intersection point
	    createNear = true;
	    createFar = false;
	} else
	{
	    // ray leaves boundary voxel at far intersection point
	    createNear = false;
	    createFar = true;
	}
	LeafStatusID ls0 = Node::getImplLeafStatus(ni);
	if ((leafStatus != NODE_ANY) 
	    && (ls0 != leafStatus))
	{
	    std::ostringstream status;
	    status << "Leaf status flag mismatch (current: " 
	        << getLeafStatusValueString(ls0) << ", expected: " 
	        << getLeafStatusValueString(leafStatus) << ").";
	    throw IFVGError(getErrorString(status.str(), 
	        "processWallThicknessStep"));
	}
	if (rayAxis == Ionflux::GeoUtils::AXIS_UNDEFINED)
	{
	    throw IFVGError(getErrorString("Ray axis is undefined", 
	        "processWallThicknessStep"));
	}
	unsigned int wtStep = context->getDepthMask(
	    intersection0.depth).to_ulong();
	bool fillNodes = false;
	if (minWallThickness0 > 0)
	    fillNodes = true;
	VoxelClassID vc = Node::getImplVoxelClass(ni);
	/* <---- DEBUG ----- //
	NodeID nid0 = Node::getImplNodeID(ni, context);
	// ----- DEBUG ----> */
	/* <---- DEBUG ----- //
	std::cerr << "[NodeIntersectionProcessor::"
	    "processWallThicknessStep] DEBUG: ";
	if (processingFlags.directionBackward)
	    std::cerr << "(backward) ";
	std::cerr << "begin node: [" << getNodeIDValueString(nid0, 
	    false, true, true, context) 
	    << "] voxelClass = " << getVoxelClassValueString(vc) 
	    << ", state = " << getVoxelClassValueString(state) 
	    << ", wallThickness = " << wallThickness 
	    << ", minWallThickness = " << minWallThickness
	    << ", maxWallThickness = " << maxWallThickness
	    << ", numNodesFilled = " << *numNodesFilled
	    << ", numThinComponents = " << *numThinComponents
	    << ", fillNodes = " 
	        << Ionflux::ObjectBase::getBooleanValueString(fillNodes);
	std::cerr << std::endl;
	// ----- DEBUG ----> */
	/* set current state according to previous state and current 
	   voxel class */
	VoxelClassID ps = state;
	bool split0 = false;
	bool filled = false;
	bool boundary = false;
	VoxelDataIOB* d0 = 0;
	if (ps == VOXEL_CLASS_UNDEFINED)
	{
	    if (checkVoxelClass(vc, voxelClassFilled))
	    {
	        state = VOXEL_CLASS_INSIDE;
	        // initialize wall thickness data for inside voxel
	        wallThickness = wtStep;
	        d0 = getIOBData(intersection0);
	        maxWallThickness = getIOBDataWallThickness(*d0, rayAxis);
	        if (fillNodes)
	            *numNodesFilled = 0;
	        /* <---- DEBUG ----- //
	        std::cerr << "[NodeIntersectionProcessor::"
	            "processWallThicknessStep] DEBUG: "
	            << "(undefined -> inside) "
	                "initializing wall thickness data (" 
	            << "wallThickness = " << wallThickness 
	            << ", maxWallThickness = " << maxWallThickness 
	            << ", numNodesFilled = " << *numNodesFilled << ")" 
	            << std::endl;
	        // ----- DEBUG ----> */
	    } else
	        state = VOXEL_CLASS_OUTSIDE;
	} else
	if (ps == VOXEL_CLASS_INSIDE)
	{
	    if (!checkVoxelClass(vc, voxelClassFilled))
	    {
	        // inside -> outside
	        unsigned int wt0 = wallThickness;
	        if (maxWallThickness > wt0)
	            wt0 = maxWallThickness;
	        if (fillNodes 
	            && (wt0 < minWallThickness0))
	        {
	            // thin component
	            if ((!insideOnly 
	                    || checkVoxelClass(vc, voxelClassInside)) 
	                && ((maxNumFillNodes == 0) 
	                    || (*numNodesFilled < maxNumFillNodes)))
	            {
	                // current node can be filled
	                if (intersection0.depth == targetDepth)
	                {
	                    // voxel at target depth
	                    /* <---- DEBUG ----- //
	                    std::cerr << "[NodeIntersectionProcessor::"
	                        "processWallThicknessStep] DEBUG: "
	                        << "(inside -> outside) "
	                            "filling node at target depth (" 
	                        << "wallThickness = " << wallThickness 
	                        << ", wt0 = " << wt0 
	                        << ", minWallThickness = " << minWallThickness 
	                        << ", maxWallThickness = " << maxWallThickness 
	                        << ", numNodesFilled = " << *numNodesFilled 
	                        << ", maxNumFillNodes = " << maxNumFillNodes
	                        << ")" << std::endl;
	                    // ----- DEBUG ----> */
	                    filled = true;
	                } else
	                {
	                    // insert voxel at target depth
	                    /* <---- DEBUG ----- //
	                    std::cerr << "[NodeIntersectionProcessor::"
	                        "processWallThicknessStep] DEBUG: "
	                        << "(inside -> outside) "
	                            "inserting node at target depth (" 
	                        << "wallThickness = " << wallThickness 
	                        << ", wt0 = " << wt0 
	                        << ", minWallThickness = " << minWallThickness 
	                        << ", maxWallThickness = " << maxWallThickness 
	                        << ", numNodesFilled = " << *numNodesFilled 
	                        << ", maxNumFillNodes = " << maxNumFillNodes
	                        << ")" << std::endl;
	                    // ----- DEBUG ----> */
	                    createAndProcessIntersectionsWallThickness(
	                        intersection0, createNear, createFar, state, 
	                        processingFlags, wallThickness, maxWallThickness, 
	                        minWallThickness0, maxNumFillNodes, insideOnly, 
	                        numThinComponents, numNodesFilled);
	                    split0 = true;
	                }
	            }
	        }
	        if (!split0)
	        {
	            if (!filled)
	            {
	                if (processingFlags.enableBoundaryData)
	                {
	                    if (intersection0.depth == targetDepth)
	                    {
	                        // boundary voxel at target depth
	                        /* <---- DEBUG ----- //
	                        std::cerr << "[NodeIntersectionProcessor::"
	                            "processWallThicknessStep] DEBUG: "
	                            << "(inside -> outside) "
	                                "boundary node at target depth" 
	                            << std::endl;
	                        // ----- DEBUG ----> */
	                        boundary = true;
	                    } else
	                    {
	                        // insert boundary voxel at target depth
	                        /* <---- DEBUG ----- //
	                        std::cerr << "[NodeIntersectionProcessor::"
	                            "processWallThicknessStep] DEBUG: "
	                            << "(inside -> outside) "
	                                "inserting boundary node at target depth" 
	                            << std::endl;
	                        // ----- DEBUG ----> */
	                        createAndProcessIntersectionsWallThickness(
	                            intersection0, createNear, createFar, state, 
	                            processingFlags, wallThickness, 
	maxWallThickness, 
	                            minWallThickness0, maxNumFillNodes, 
	insideOnly, 
	                            numThinComponents, numNodesFilled);
	                        split0 = true;
	                    }
	                }
	                if (!split0)
	                {
	                    // reset wall thickness data
	                    wallThickness = 0;
	                    maxWallThickness = 0;
	                    if (wt0 < minWallThickness0)
	                        (*numThinComponents)++;
	                    /* <---- DEBUG ----- //
	                    std::cerr << "[NodeIntersectionProcessor::"
	                        "processWallThicknessStep] DEBUG: "
	                        << "(inside -> outside) resetting wall thickness "
	                            "data (" 
	                        << "wallThickness = " << wallThickness 
	                        << ", maxWallThickness = " << maxWallThickness 
	                        << ", numThinComponents = " << *numThinComponents 
	                        << ")" << std::endl;
	                    // ----- DEBUG ----> */
	                    state = VOXEL_CLASS_OUTSIDE;
	                }
	            } else
	            {
	                // still inside because the current node has been filled
	                wallThickness += wtStep;
	                /* <---- DEBUG ----- //
	                std::cerr << "[NodeIntersectionProcessor::"
	                    "processWallThicknessStep] DEBUG: "
	                    << "(inside -> inside) node filled (" 
	                    << "wallThickness = " << wallThickness 
	                    << ", maxWallThickness = " << maxWallThickness 
	                    << ", numNodesFilled = " << *numNodesFilled 
	                    << ", maxNumFillNodes = " << maxNumFillNodes
	                    << ")" << std::endl;
	                // ----- DEBUG ----> */
	            }
	        }
	    } else
	    {
	        // inside -> inside
	        wallThickness += wtStep;
	        /* <---- DEBUG ----- //
	        std::cerr << "[NodeIntersectionProcessor::"
	            "processWallThicknessStep] DEBUG: "
	            << "(inside -> inside) " 
	            << "wallThickness = " << wallThickness 
	            << ", maxWallThickness = " << maxWallThickness 
	            << std::endl;
	        // ----- DEBUG ----> */
	    }
	} else
	if (ps == VOXEL_CLASS_OUTSIDE)
	{
	    if (checkVoxelClass(vc, voxelClassFilled))
	    {
	        // outside -> inside
	        state = VOXEL_CLASS_INSIDE;
	        // initialize wall thickness data for inside voxel
	        wallThickness = wtStep;
	        d0 = getIOBData(intersection0);
	        maxWallThickness = getIOBDataWallThickness(*d0, rayAxis);
	        if (fillNodes)
	            *numNodesFilled = 0;
	        /* <---- DEBUG ----- //
	        std::cerr << "[NodeIntersectionProcessor::"
	            "processWallThicknessStep] DEBUG: "
	            << "(outside -> inside) initializing wall thickness "
	                "for inside voxel (" 
	            << "wallThickness = " << wallThickness 
	            << ", maxWallThickness = " << maxWallThickness << ")" 
	            << std::endl;
	        // ----- DEBUG ----> */
	    }
	}
	if (split0)
	{
	    // node intersection has been split and processed recursively
	    return;
	}
	// update wall thickness for the node
	if (d0 == 0)
	    d0 = getIOBData(intersection0);
	if (filled)
	{
	    setVoxelClass(voxelClassInside | voxelClassOutside 
	        | voxelClassBoundary | VOXEL_CLASS_EMPTY, vc, false);
	    setVoxelClass(voxelClassFilled, vc);
	    d0->boundaryFaces = FACE_UNDEFINED;
	    (*numNodesFilled)++;
	} else
	if (boundary)
	{
	    setVoxelClass(voxelClassBoundary, vc);
	    if (!processingFlags.directionBackward)
	        d0->boundaryFaces |= intersection0.intersection.nearPlane;
	    else
	        d0->boundaryFaces |= intersection0.intersection.farPlane;
	}
	d0->voxelClass = vc;
	unsigned int wt0 = wallThickness;
	if (maxWallThickness > wt0)
	    wt0 = maxWallThickness;
	setIOBDataWallThickness(*d0, rayAxis, wt0);
	/* <---- DEBUG ----- //
	std::cerr << "[NodeIntersectionProcessor::"
	    "processWallThicknessStep] DEBUG: ";
	if (processingFlags.directionBackward)
	    std::cerr << "(backward) ";
	std::cerr << "finished node: [" << getNodeIDValueString(nid0, 
	    false, true, true, context) 
	    << "] voxelClass = " << getVoxelClassValueString(vc) 
	    << ", state = " << getVoxelClassValueString(state) 
	    << ", wallThickness = " << wallThickness 
	    << ", maxWallThickness = " << maxWallThickness
	    << ", numNodesFilled = " << *numNodesFilled
	    << ", numThinComponents = " << *numThinComponents
	    << ", wt0 = " << wt0;
	std::cerr << std::endl;
	// ----- DEBUG ----> */
	updatedIntersections.push_back(intersection0);
}

void NodeIntersectionProcessor::processIntersectionsBoundary(const 
Ionflux::VolGfx::NodeIntersectionVector& intersections0, 
Ionflux::VolGfx::VoxelClassID& state, 
Ionflux::VolGfx::NodeIntersectionProcessingFlags processingFlags, 
Ionflux::VolGfx::ColorIndex* colorIndex)
{
	unsigned int n0 = intersections0.size();
	if (n0 == 0)
	    return;
	if (!processingFlags.directionBackward)
	{
	    for (unsigned int i = 0; i < n0; i++)
	    {
	        NodeIntersection ci0 = intersections0[i];
	        processBoundaryStep(ci0, state, processingFlags, colorIndex);
	    }
	} else
	{
	    for (unsigned int i = n0; i > 0; i--)
	    {
	        NodeIntersection ci0 = intersections0[i - 1];
	        processBoundaryStep(ci0, state, processingFlags, colorIndex);
	    }
	}
}

void NodeIntersectionProcessor::createAndProcessIntersectionsBoundary(const
Ionflux::VolGfx::NodeIntersection& intersection0, bool createNear, bool 
createFar, Ionflux::VolGfx::VoxelClassID& state, 
Ionflux::VolGfx::NodeIntersectionProcessingFlags processingFlags, 
Ionflux::VolGfx::ColorIndex* colorIndex)
{
	NodeIntersectionVector niv0;
	unsigned int n0 = createIntersections(intersection0, 
	    niv0, createNear, createFar);
	if (n0 == 0)
	{
	    throw IFVGError(getErrorString(
	        "Could not create new node intersections.", 
	        "createAndProcessIntersectionsBoundary"));
	}
	// process new intersections recursively
	processIntersectionsBoundary(niv0, state, processingFlags, colorIndex);
}

void NodeIntersectionProcessor::processBoundaryStep(const 
Ionflux::VolGfx::NodeIntersection& intersection0, 
Ionflux::VolGfx::VoxelClassID& state, 
Ionflux::VolGfx::NodeIntersectionProcessingFlags processingFlags, 
Ionflux::VolGfx::ColorIndex* colorIndex)
{
	Ionflux::ObjectBase::nullPointerCheck(
	    context, this, "processBoundaryStep", "Context");
	NodeImpl* ni = Ionflux::ObjectBase::nullPointerCheck(
	    intersection0.nodeImpl, this, "processBoundaryStep", 
	    "Node implementation");
	int maxNumLevels = context->getMaxNumLevels();
	bool createNear = false;
	bool createFar = false;
	if ((targetDepth < 0) 
	    || (targetDepth >= maxNumLevels))
	    targetDepth = maxNumLevels - 1;
	if (!processingFlags.directionBackward)
	{
	    // ray enters boundary voxel at near intersection point
	    createNear = true;
	    createFar = false;
	} else
	{
	    // ray leaves boundary voxel at far intersection point
	    createNear = false;
	    createFar = true;
	}
	LeafStatusID ls0 = Node::getImplLeafStatus(ni);
	if ((leafStatus != NODE_ANY) 
	    && (ls0 != leafStatus))
	{
	    std::ostringstream status;
	    status << "Leaf status flag mismatch (current: " 
	        << getLeafStatusValueString(ls0) << ", expected: " 
	        << getLeafStatusValueString(leafStatus) << ").";
	    throw IFVGError(getErrorString(status.str(), 
	        "processBoundaryStep"));
	}
	if (rayAxis == Ionflux::GeoUtils::AXIS_UNDEFINED)
	{
	    throw IFVGError(getErrorString("Ray axis is undefined", 
	        "processBoundaryStep"));
	}
	VoxelClassID vc = Node::getImplVoxelClass(ni);
	/* <---- DEBUG ----- //
	NodeID nid0 = Node::getImplNodeID(ni, context);
	// ----- DEBUG ----> */
	/* <---- DEBUG ----- //
	std::cerr << "[NodeIntersectionProcessor::"
	    "processBoundaryStep] DEBUG: ";
	if (processingFlags.directionBackward)
	    std::cerr << "(backward) ";
	std::cerr << "begin node: [" << getNodeIDValueString(nid0, 
	    false, true, true, context) 
	    << "] voxelClass = " << getVoxelClassValueString(vc) 
	    << ", state = " << getVoxelClassValueString(state) 
	    << ", wallThickness = " << wallThickness 
	    << ", minWallThickness = " << minWallThickness
	    << ", maxWallThickness = " << maxWallThickness
	    << ", numNodesFilled = " << *numNodesFilled
	    << ", numThinComponents = " << *numThinComponents
	    << ", fillNodes = " 
	        << Ionflux::ObjectBase::getBooleanValueString(fillNodes);
	std::cerr << std::endl;
	// ----- DEBUG ----> */
	/* set current state according to previous state and current 
	   voxel class */
	VoxelClassID ps = state;
	bool split0 = false;
	bool boundary = false;
	VoxelDataIOB* d0 = 0;
	if (ps == VOXEL_CLASS_UNDEFINED)
	{
	    // initialize voxel class and color index
	    if (checkVoxelClass(vc, voxelClassFilled))
	    {
	        state = VOXEL_CLASS_INSIDE;
	        if (colorIndex != 0)
	            *colorIndex = COLOR_INDEX_UNSPECIFIED;
	    } else
	    {
	        state = VOXEL_CLASS_OUTSIDE;
	        if (colorIndex != 0)
	            *colorIndex = COLOR_INDEX_UNSPECIFIED;
	    }
	} else
	if (ps == VOXEL_CLASS_INSIDE)
	{
	    if (!checkVoxelClass(vc, voxelClassFilled))
	    {
	        // inside -> outside
	        if (intersection0.depth == targetDepth)
	        {
	            // boundary voxel at target depth
	            /* <---- DEBUG ----- //
	            std::cerr << "[NodeIntersectionProcessor::"
	                "processBoundaryStep] DEBUG: "
	                << "(inside -> outside) "
	                    "boundary node at target depth" 
	                << std::endl;
	            // ----- DEBUG ----> */
	            boundary = true;
	        } else
	        {
	            // insert boundary voxel at target depth
	            /* <---- DEBUG ----- //
	            std::cerr << "[NodeIntersectionProcessor::"
	                "processBoundaryStep] DEBUG: "
	                << "(inside -> outside) "
	                    "inserting boundary node at target depth" 
	                << std::endl;
	            // ----- DEBUG ----> */
	            createAndProcessIntersectionsBoundary(
	                intersection0, createNear, createFar, state, 
	                processingFlags, colorIndex);
	            split0 = true;
	        }
	        if (!split0)
	            state = VOXEL_CLASS_OUTSIDE;
	    } else
	    {
	        // inside -> inside
	        if (colorIndex != 0)
	        {
	            // update color index
	            d0 = getIOBData(intersection0);
	            *colorIndex = d0->color;
	        }
	    }
	} else
	if (ps == VOXEL_CLASS_OUTSIDE)
	{
	    if (checkVoxelClass(vc, voxelClassFilled))
	    {
	        // outside -> inside
	        state = VOXEL_CLASS_INSIDE;
	        if (colorIndex != 0)
	        {
	            // initialize color index
	            d0 = getIOBData(intersection0);
	            *colorIndex = d0->color;
	        }
	    }
	}
	if (split0)
	{
	    // node intersection has been split and processed recursively
	    return;
	}
	// update wall thickness for the node
	if (d0 == 0)
	    d0 = getIOBData(intersection0);
	if (boundary)
	{
	    setVoxelClass(voxelClassBoundary, vc);
	    if (!processingFlags.directionBackward)
	        d0->boundaryFaces |= intersection0.intersection.nearPlane;
	    else
	        d0->boundaryFaces |= intersection0.intersection.farPlane;
	    if ((colorIndex != 0) 
	        && (*colorIndex != COLOR_INDEX_UNSPECIFIED))
	    {
	        // assign color index
	        d0->color = *colorIndex;
	        *colorIndex = COLOR_INDEX_UNSPECIFIED;
	    }
	}
	d0->voxelClass = vc;
	/* <---- DEBUG ----- //
	std::cerr << "[NodeIntersectionProcessor::"
	    "processBoundaryStep] DEBUG: ";
	if (processingFlags.directionBackward)
	    std::cerr << "(backward) ";
	std::cerr << "finished node: [" << getNodeIDValueString(nid0, 
	    false, true, true, context) 
	    << "] voxelClass = " << getVoxelClassValueString(vc) 
	    << ", state = " << getVoxelClassValueString(state) 
	    << ", wallThickness = " << wallThickness 
	    << ", maxWallThickness = " << maxWallThickness
	    << ", numNodesFilled = " << *numNodesFilled
	    << ", numThinComponents = " << *numThinComponents
	    << ", wt0 = " << wt0;
	std::cerr << std::endl;
	// ----- DEBUG ----> */
	updatedIntersections.push_back(intersection0);
}

void NodeIntersectionProcessor::clear()
{
	clearIntersections();
}

void NodeIntersectionProcessor::begin()
{
	clear();
}

void NodeIntersectionProcessor::finish()
{
	bool fillNodes = false;
	if (enableWallThickness 
	    && (minWallThickness > 0))
	    fillNodes = true;
	if (enableIOB)
	{
	    NodeIntersectionProcessingFlags pf0 = 
	        createNodeIntersectionProcessingFlags(false, 
	            false, false, enableRayStabbing, 
	            enableWallThickness && !fillNodes);
	    setIOBData(&pf0);
	}
	if (fillNodes 
	    || (!enableIOB && enableWallThickness))
	{
	    NodeIntersectionProcessingFlags pf0 = 
	        createNodeIntersectionProcessingFlags(false, 
	            false, false, enableRayStabbing, true);
	    processWallThickness(&pf0);
	}
	if (enableBoundaryData)
	    processBoundary();
}

Ionflux::VolGfx::NodeProcessingResultID 
NodeIntersectionProcessor::processIntersection(const 
Ionflux::VolGfx::NodeIntersection& newIntersection, void* userData)
{
	NodeImpl* ni = Ionflux::ObjectBase::nullPointerCheck(
	    newIntersection.nodeImpl, this, "processIntersection", 
	    "Node implementation");
	/* <---- DEBUG ----- //
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "processIntersection", "Context");
	std::cerr << "[NodeIntersectionProcessor::processIntersection] DEBUG: " 
	    "processing intersection: " << ni << " [" 
	    << getNodeIntersectionValueString(*context, newIntersection) 
	    << "]" << std::endl;
	// ----- DEBUG ----> */
	if (hitDataType != Node::DATA_TYPE_UNKNOWN)
	{
	    if (Node::hasImplDataType(ni, Node::DATA_TYPE_NULL))
	        Node::getImplData(ni, hitDataType);
	}
	if ((voxelClassHit != VOXEL_CLASS_UNDEFINED) 
	    && Node::hasImplVoxelClassInfo(ni))
	{
	    Node::setImplVoxelClass(ni, voxelClassHit);
	}
	addIntersection(newIntersection);
	return RESULT_OK;
}

void 
NodeIntersectionProcessor::setIOBData(Ionflux::VolGfx::NodeIntersectionProcessingFlags*
processingFlags)
{
	updatedIntersections.clear();
	// forward pass
	VoxelClassID cs = VOXEL_CLASS_UNDEFINED;
	unsigned int numInts0 = 0;
	unsigned int wallThickness0 = 0;
	unsigned int maxWallThickness0 = 0;
	NodeIntersectionProcessingFlags pf0;
	if (processingFlags == 0)
	{
	    pf0 = createNodeIntersectionProcessingFlags(false, 
	        enableBoundaryData, false, enableRayStabbing, 
	        enableWallThickness);
	} else
	    pf0 = *processingFlags;
	processIntersectionsIOB(intersections, cs, numInts0, pf0, 
	    &wallThickness0, &maxWallThickness0);
	pf0.castVotes = true;
	if ((numInts0 % 2) != 0)
	{
	    // Invalid ray does not vote.
	    pf0.castVotes = false;
	    if (!enableBoundaryData && !enableRayStabbing 
	        && !enableWallThickness)
	        return;
	}
	// use updated intersections for backward pass
	updateIntersections();
	// backward pass
	cs = VOXEL_CLASS_UNDEFINED;
	numInts0 = 0;
	pf0.directionBackward = true;
	processIntersectionsIOB(intersections, cs, numInts0, pf0, 
	    &wallThickness0, &maxWallThickness0);
	// update intersections from backward pass
	updateIntersections(true);
}

void 
NodeIntersectionProcessor::processWallThickness(Ionflux::VolGfx::NodeIntersectionProcessingFlags*
processingFlags)
{
	updatedIntersections.clear();
	VoxelClassID cs = VOXEL_CLASS_UNDEFINED;
	unsigned int wallThickness0 = 0;
	unsigned int maxWallThickness0 = 0;
	unsigned int numThinComponents0 = 0;
	unsigned int numNodesFilled0 = 0;
	NodeIntersectionProcessingFlags pf0;
	if (processingFlags == 0)
	{
	    pf0 = createNodeIntersectionProcessingFlags(false, 
	        enableBoundaryData, false, enableRayStabbing, 
	        enableWallThickness);
	} else
	    pf0 = *processingFlags;
	// forward pass (fill inside only)
	processIntersectionsWallThickness(intersections, cs, pf0, 
	    wallThickness0, maxWallThickness0, minWallThickness, 0, true, 
	    &numThinComponents0, &numNodesFilled0);
	// use updated intersections for backward pass
	updateIntersections();
	// backward pass (fill inside only)
	cs = VOXEL_CLASS_UNDEFINED;
	pf0.directionBackward = true;
	numThinComponents0 = 0;
	numNodesFilled0 = 0;
	processIntersectionsWallThickness(intersections, cs, pf0, 
	    wallThickness0, maxWallThickness0, minWallThickness, 0, true, 
	    &numThinComponents0, &numNodesFilled0);
	// update intersections from backward pass
	updateIntersections(true);
	if (minWallThickness > 0)
	{
	    /* in case some nodes were filled in the backward pass, we need an 
	       additional forward pass to propagate the wall thickness */
	    cs = VOXEL_CLASS_UNDEFINED;
	    pf0.directionBackward = false;
	    numThinComponents0 = 0;
	    numNodesFilled0 = 0;
	    processIntersectionsWallThickness(intersections, cs, pf0, 
	        wallThickness0, maxWallThickness0, minWallThickness, 0, true, 
	        &numThinComponents0, &numNodesFilled0);
	    updateIntersections();
	    if (!fillInsideOnly) 
	    {
	        unsigned int numPasses = 0;
	        while ((numThinComponents0 > 0) 
	            && ((maxNumWallThicknessPasses == 0) 
	                || (numPasses < maxNumWallThicknessPasses)))
	        {
	            // forward pass (1)
	            cs = VOXEL_CLASS_UNDEFINED;
	            pf0.directionBackward = false;
	            numThinComponents0 = 0;
	            numNodesFilled0 = 0;
	            processIntersectionsWallThickness(intersections, cs, pf0, 
	                wallThickness0, maxWallThickness0, minWallThickness, 1, 
	                false, &numThinComponents0, &numNodesFilled0);
	            updateIntersections();
	            // backward pass
	            cs = VOXEL_CLASS_UNDEFINED;
	            pf0.directionBackward = true;
	            numThinComponents0 = 0;
	            numNodesFilled0 = 0;
	            processIntersectionsWallThickness(intersections, cs, pf0, 
	                wallThickness0, maxWallThickness0, minWallThickness, 1, 
	                false, &numThinComponents0, &numNodesFilled0);
	            updateIntersections(true);
	            // forward pass (2)
	            cs = VOXEL_CLASS_UNDEFINED;
	            pf0.directionBackward = false;
	            numThinComponents0 = 0;
	            numNodesFilled0 = 0;
	            processIntersectionsWallThickness(intersections, cs, pf0, 
	                wallThickness0, maxWallThickness0, minWallThickness, 1, 
	                false, &numThinComponents0, &numNodesFilled0);
	            updateIntersections();
	            numPasses++;
	        }
	    }
	}
}

void 
NodeIntersectionProcessor::processBoundary(Ionflux::VolGfx::NodeIntersectionProcessingFlags*
processingFlags)
{
	updatedIntersections.clear();
	VoxelClassID cs = VOXEL_CLASS_UNDEFINED;
	ColorIndex colorIndex0 = COLOR_INDEX_UNSPECIFIED;
	NodeIntersectionProcessingFlags pf0;
	if (processingFlags == 0)
	{
	    pf0 = createNodeIntersectionProcessingFlags(false, 
	        enableBoundaryData, false, enableRayStabbing, 
	        enableWallThickness);
	} else
	    pf0 = *processingFlags;
	// forward pass
	processIntersectionsBoundary(intersections, cs, pf0, &colorIndex0);
	// use updated intersections for backward pass
	updateIntersections();
	// backward pass
	cs = VOXEL_CLASS_UNDEFINED;
	pf0.directionBackward = true;
	colorIndex0 = COLOR_INDEX_UNSPECIFIED;
	processIntersectionsBoundary(intersections, cs, pf0, &colorIndex0);
	// update intersections from backward pass
	updateIntersections(true);
}

unsigned int NodeIntersectionProcessor::createIntersections(const 
Ionflux::VolGfx::NodeIntersection& intersection0, 
Ionflux::VolGfx::NodeIntersectionVector& newIntersections, bool createNear,
bool createFar)
{
	Ionflux::ObjectBase::nullPointerCheck(
	    context, this, "createIntersections", "Context");
	Ionflux::ObjectBase::nullPointerCheck(
	    ray, this, "createIntersections", "Ray");
	NodeImpl* ci = Ionflux::ObjectBase::nullPointerCheck(
	    intersection0.nodeImpl, this, "createIntersections", 
	    "Node implementation");
	VoxelClassID vc = Node::getImplVoxelClass(ci);
	int maxNumLevels = context->getMaxNumLevels();
	if ((targetDepth < 0) 
	    || (targetDepth >= maxNumLevels))
	    targetDepth = maxNumLevels - 1;
	int depth = Node::getImplDepth(ci, context);
	if (depth >= targetDepth)
	{
	    // Nothing to be done for this node.
	    return 0;
	}
	VoxelDataIOB* d0 = 0;
	if (Node::hasImplDataType(ci, Node::DATA_TYPE_VOXEL_IOB))
	    d0 = getIOBData(intersection0);
	NodeID nid0;
	nid0.loc = ci->loc;
	nid0.depth = depth;
	Region3 r0;
	if (!context->getIntersectionLoc(nid0, *ray, 
	    intersection0.intersection, r0))
	{
	    std::ostringstream status;
	    status << "Invalid node intersection: [" 
	        << getNodeIntersectionValueString(*context, intersection0) 
	        << "].";
	    throw IFVGError(getErrorString(status.str(), 
	        "createIntersections"));
	}
	unsigned int n0 = 0;
	if (createNear)
	{
	    // insert node at near intersection point
	    /* <---- DEBUG ----- //
	    Ionflux::GeoUtils::Vector3 tl0;
	    context->getLocation(r0.l0, tl0);
	    Ionflux::GeoUtils::Range3 tr0;
	    context->getVoxelRange(r0.l0, targetDepth, tr0);
	    Ionflux::GeoUtils::Vector3 trMin = tr0.getRMin();
	    Ionflux::GeoUtils::Vector3 trMax = tr0.getRMax();
	    std::cerr << "[NodeIntersectionProcessor::createIntersections] "
	        "DEBUG: inserting node at near intersection point " 
	        << " (loc = [" << getLocString(r0.l0) << ", (" 
	        << tl0.getValueString() <<")], range = [(" 
	        << trMin.getValueString() << "), (" << trMax.getValueString() 
	        << ")], targetDepth = " << targetDepth << ", voxelSize = "
	        << context->getVoxelSize(targetDepth) << ")." << std::endl;
	    // ----- DEBUG ----> */
	    Ionflux::ObjectBase::nullPointerCheck(
	        Node::insertImplChild(ci, context, r0.l0, 
	        targetDepth, true), this, 
	        "createIntersections", 
	        "Node implementation (near intersection point)");
	    n0++;
	}
	if (createFar)
	{
	    // insert node at far intersection point
	    /* <---- DEBUG ----- //
	    Ionflux::GeoUtils::Vector3 tl0;
	    context->getLocation(r0.l0, tl0);
	    Ionflux::GeoUtils::Range3 tr0;
	    context->getVoxelRange(r0.l0, targetDepth, tr0);
	    Ionflux::GeoUtils::Vector3 trMin = tr0.getRMin();
	    Ionflux::GeoUtils::Vector3 trMax = tr0.getRMax();
	    std::cerr << "[NodeIntersectionProcessor::createIntersections] "
	        "DEBUG: inserting node at far intersection point " 
	        << " (loc = [" << getLocString(r0.l0) << ", (" 
	        << tl0.getValueString() <<")], range = [(" 
	        << trMin.getValueString() << "), (" << trMax.getValueString() 
	        << ")], targetDepth = " << targetDepth << ", voxelSize = "
	        << context->getVoxelSize(targetDepth) << ")." << std::endl;
	    // ----- DEBUG ----> */
	    Ionflux::ObjectBase::nullPointerCheck(
	        Node::insertImplChild(ci, context, r0.l1, 
	        targetDepth, true), this, 
	        "createIntersections", 
	        "Node implementation (far intersection point)");
	    n0++;
	}
	// calculate new node intersections
	NodeIntersectionProcessor proc0(context, hitDataType, 
	    voxelClassHit, NODE_LEAF, ray);
	NodeFilter nf0(context, DEPTH_UNSPECIFIED, 
	    targetDepth, NODE_LEAF);
	/* <---- DEBUG ----- //
	std::cerr << "[NodeIntersectionProcessor::createIntersections] "
	    "DEBUG: filter: [" << nf0.getValueString() << "]" 
	    << std::endl;
	// ----- DEBUG ----> */
	unsigned int n1 = Node::intersectRayImpl(ci, context, *ray, 
	    &proc0, &nf0, true, tolerance, &intersection0, 
	    fillNewIntersections, pruneEmptyNewIntersections);
	if (n1 < n0)
	{
	    std::ostringstream status;
	    status << "Unexpected number of child node intersections "
	        "(expected: " << n0 << ", current: " << n1 << ").";
	    throw IFVGError(getErrorString(status.str(), 
	        "createIntersections"));
	}
	newIntersections = proc0.getIntersections();
	// propagate parent voxel class to leaf child nodes
	setVoxelClass(voxelClassHit, vc, false);
	Node::setImplVoxelClass(ci, context, vc, true, &nf0, true, 
	    Node::DATA_TYPE_VOXEL_IOB);
	if (d0 != 0)
	{
	    // propagate number of intersections to intersected nodes
	    for (unsigned int i = 0; i < newIntersections.size(); i++)
	    {
	        NodeIntersection ci0 = newIntersections[i];
	        VoxelClassID vc0 = Node::getImplVoxelClass(ci0.nodeImpl);
	        VoxelDataIOB* cd0 = getIOBData(ci0);
	        cd0->voxelClass = vc0;
	        cd0->numInts0 = d0->numInts0;
	        cd0->numInts1 = d0->numInts1;
	    }
	}
	/* <---- DEBUG ----- //
	std::cerr << "[NodeIntersectionProcessor::createIntersections] "
	    "DEBUG: new intersections (node: " << ci << " [" 
	        << getNodeIDValueString(nid0, false, true, true, context) 
	            << "]):" << std::endl;
	for (unsigned int i = 0; i < newIntersections.size(); i++)
	{
	    NodeIntersection ci0 = newIntersections[i];
	    NodeImpl* ni0 = ci0.nodeImpl;
	    LeafStatusID ls0 = Node::getImplLeafStatus(ni0);
	    nid0 = Node::getImplNodeID(ni0, context);
	    std::cerr << "  [" << std::setw(3) << std::setfill('0') 
	        << i << "] " << getNodeIntersectionValueString(*context, ci0) 
	        << " [" << getNodeIDValueString(nid0, 
	            false, true, true, context) << "]" 
	        << " (" << getLeafStatusValueString(ls0) << ")" 
	        << std::endl;
	}
	// ----- DEBUG ----> */
	return newIntersections.size();
}

std::string NodeIntersectionProcessor::getValueString() const
{
	ostringstream status;
	status << "context: ";
	if (context == 0)
	    status << "<null>";
	else
	    status << "[" << context->getValueString() << "]";
	status << "; hitDataType = " << Node::getDataTypeString(hitDataType) 
	    << ", voxelClassHit = " << getVoxelClassValueString(voxelClassHit) 
	    << ", leafStatus = " << getLeafStatusValueString(leafStatus) 
	    << ", enableBoundaryData = " 
	        << Ionflux::ObjectBase::getBooleanValueString(
	            enableBoundaryData) 
	    << ", targetDepth = " << getDepthString(leafStatus) 
	    << ", fillNewIntersections = " 
	        << Ionflux::ObjectBase::getBooleanValueString(
	            fillNewIntersections) 
	    << ", pruneEmptyNewIntersections = " 
	        << Ionflux::ObjectBase::getBooleanValueString(
	            pruneEmptyNewIntersections) 
	    << ", enableIOB = " 
	        << Ionflux::ObjectBase::getBooleanValueString(enableIOB) 
	    << ", enableRayStabbing = " 
	        << Ionflux::ObjectBase::getBooleanValueString(
	            enableRayStabbing) 
	    << ", enableWallThickness = " 
	        << Ionflux::ObjectBase::getBooleanValueString(
	            enableWallThickness) 
	    << ", voxelClassFilled = " 
	        << getVoxelClassValueString(voxelClassFilled) 
	    << ", voxelClassInside = " 
	        << getVoxelClassValueString(voxelClassInside) 
	    << ", voxelClassOutside = " 
	        << getVoxelClassValueString(voxelClassOutside) 
	    << ", voxelClassBoundary = " 
	        << getVoxelClassValueString(voxelClassBoundary) 
	    << ", minWallThickness = " << minWallThickness 
	    << ", fillInsideOnly = " 
	        << Ionflux::ObjectBase::getBooleanValueString(
	            fillInsideOnly) 
	    << ", maxNumWallThicknessPasses = " << maxNumWallThicknessPasses 
	    << ", tolerance = " << tolerance 
	    << ", numIntersections = " << intersections.size();
	status << "; ray: ";
	if (ray == 0)
	    status << "<null>";
	else
	{
	    status << "[" << ray->getValueString() << "]";
	    if (rayAxis != Ionflux::GeoUtils::AXIS_UNDEFINED)
	    {
	        status << " (" << Ionflux::GeoUtils::axisToString(rayAxis) 
	            << ")";
	    }
	}
	return status.str();
}

Ionflux::VolGfx::VoxelDataIOB* NodeIntersectionProcessor::getIOBData(const 
Ionflux::VolGfx::NodeIntersection& intersection0)
{
	NodeImpl* cn0 = Ionflux::ObjectBase::nullPointerCheck(
	    intersection0.nodeImpl, "NodeIntersectionProcessor::getImplIOBData", 
	    "Node implementation");
	NodeDataImpl* dp = Ionflux::ObjectBase::nullPointerCheck(
	    Node::getImplData(cn0, Node::DATA_TYPE_VOXEL_IOB), 
	    "NodeIntersectionProcessor::getImplIOBData", "Node data");
	VoxelDataIOB* d0 = Ionflux::ObjectBase::nullPointerCheck(
	    static_cast<VoxelDataIOB*>(dp->data), 
	    "NodeIntersectionProcessor::getImplIOBData", 
	    "Voxel inside/outside/boundary data");
	return d0;
}

unsigned int NodeIntersectionProcessor::getNumIntersections() const
{
    return intersections.size();
}

Ionflux::VolGfx::NodeIntersection 
NodeIntersectionProcessor::getIntersection(unsigned int elementIndex) const
{
    if (elementIndex < intersections.size())
		return intersections[elementIndex];
	return createNodeIntersection();
}

int NodeIntersectionProcessor::findIntersection(const 
Ionflux::VolGfx::NodeIntersection& needle, unsigned int occurence) const
{
    bool found = false;
	Ionflux::VolGfx::NodeIntersection currentIntersection = createNodeIntersection();
	unsigned int i = 0;
	while (!found 
		&& (i < intersections.size()))
	{
		currentIntersection = intersections[i];
		if (currentIntersection == needle)
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

std::vector<Ionflux::VolGfx::NodeIntersection>& 
NodeIntersectionProcessor::getIntersections()
{
    return intersections;
}

void NodeIntersectionProcessor::addIntersection(const 
Ionflux::VolGfx::NodeIntersection& addElement)
{
	intersections.push_back(addElement);
}

const Ionflux::VolGfx::NodeIntersection& 
NodeIntersectionProcessor::addIntersection()
{
	const Ionflux::VolGfx::NodeIntersection& o0 = createNodeIntersection();
	addIntersection(o0);
	return o0;
}

void NodeIntersectionProcessor::addIntersections(const 
std::vector<Ionflux::VolGfx::NodeIntersection>& newIntersections)
{
	for (std::vector<Ionflux::VolGfx::NodeIntersection>::const_iterator i = newIntersections.begin(); 
	    i != newIntersections.end(); i++)
	    addIntersection(*i);
}

void 
NodeIntersectionProcessor::addIntersections(Ionflux::VolGfx::NodeIntersectionProcessor*
newIntersections)
{
	for (unsigned int i = 0; 
	    i < newIntersections->getNumIntersections(); i++)
	    addIntersection(newIntersections->getIntersection(i));
}

void NodeIntersectionProcessor::removeIntersection(const 
Ionflux::VolGfx::NodeIntersection& removeElement)
{
    bool found = false;
	Ionflux::VolGfx::NodeIntersection currentIntersection = createNodeIntersection();
	unsigned int i = 0;
	while (!found 
		&& (i < intersections.size()))
	{
		currentIntersection = intersections[i];
		if (currentIntersection == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		intersections.erase(intersections.begin() + i);
	}
}

void NodeIntersectionProcessor::removeIntersectionIndex(unsigned int 
removeIndex)
{
    if (removeIndex > intersections.size())
        return;
    intersections.erase(intersections.begin() + removeIndex);
}

void NodeIntersectionProcessor::clearIntersections()
{
    intersections.clear();
}

void NodeIntersectionProcessor::setContext(Ionflux::VolGfx::Context* 
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

Ionflux::VolGfx::Context* NodeIntersectionProcessor::getContext() const
{
    return context;
}

void 
NodeIntersectionProcessor::setHitDataType(Ionflux::VolGfx::NodeDataType 
newHitDataType)
{
	hitDataType = newHitDataType;
}

Ionflux::VolGfx::NodeDataType NodeIntersectionProcessor::getHitDataType() 
const
{
    return hitDataType;
}

void 
NodeIntersectionProcessor::setVoxelClassHit(Ionflux::VolGfx::VoxelClassID 
newVoxelClassHit)
{
	voxelClassHit = newVoxelClassHit;
}

Ionflux::VolGfx::VoxelClassID NodeIntersectionProcessor::getVoxelClassHit()
const
{
    return voxelClassHit;
}

void NodeIntersectionProcessor::setLeafStatus(Ionflux::VolGfx::LeafStatusID
newLeafStatus)
{
	leafStatus = newLeafStatus;
}

Ionflux::VolGfx::LeafStatusID NodeIntersectionProcessor::getLeafStatus() 
const
{
    return leafStatus;
}

void NodeIntersectionProcessor::setRay(Ionflux::GeoUtils::Line3* newRay)
{
	if (ray == newRay)
	    return;
	if (newRay != 0)
	{
	    addLocalRef(newRay);
	    rayAxis = newRay->getAxis();
	}
	if (ray != 0)
	    removeLocalRef(ray);
	ray = newRay;
}

Ionflux::GeoUtils::Line3* NodeIntersectionProcessor::getRay() const
{
    return ray;
}

void NodeIntersectionProcessor::setEnableBoundaryData(bool 
newEnableBoundaryData)
{
	enableBoundaryData = newEnableBoundaryData;
}

bool NodeIntersectionProcessor::getEnableBoundaryData() const
{
    return enableBoundaryData;
}

void NodeIntersectionProcessor::setTargetDepth(int newTargetDepth)
{
	targetDepth = newTargetDepth;
}

int NodeIntersectionProcessor::getTargetDepth() const
{
    return targetDepth;
}

void NodeIntersectionProcessor::setFillNewIntersections(bool 
newFillNewIntersections)
{
	fillNewIntersections = newFillNewIntersections;
}

bool NodeIntersectionProcessor::getFillNewIntersections() const
{
    return fillNewIntersections;
}

void NodeIntersectionProcessor::setPruneEmptyNewIntersections(bool 
newPruneEmptyNewIntersections)
{
	pruneEmptyNewIntersections = newPruneEmptyNewIntersections;
}

bool NodeIntersectionProcessor::getPruneEmptyNewIntersections() const
{
    return pruneEmptyNewIntersections;
}

void NodeIntersectionProcessor::setEnableIOB(bool newEnableIOB)
{
	enableIOB = newEnableIOB;
}

bool NodeIntersectionProcessor::getEnableIOB() const
{
    return enableIOB;
}

void NodeIntersectionProcessor::setEnableRayStabbing(bool 
newEnableRayStabbing)
{
	enableRayStabbing = newEnableRayStabbing;
}

bool NodeIntersectionProcessor::getEnableRayStabbing() const
{
    return enableRayStabbing;
}

void NodeIntersectionProcessor::setEnableWallThickness(bool 
newEnableWallThickness)
{
	enableWallThickness = newEnableWallThickness;
}

bool NodeIntersectionProcessor::getEnableWallThickness() const
{
    return enableWallThickness;
}

void 
NodeIntersectionProcessor::setVoxelClassFilled(Ionflux::VolGfx::VoxelClassID
newVoxelClassFilled)
{
	voxelClassFilled = newVoxelClassFilled;
}

Ionflux::VolGfx::VoxelClassID 
NodeIntersectionProcessor::getVoxelClassFilled() const
{
    return voxelClassFilled;
}

void 
NodeIntersectionProcessor::setVoxelClassInside(Ionflux::VolGfx::VoxelClassID
newVoxelClassInside)
{
	voxelClassInside = newVoxelClassInside;
}

Ionflux::VolGfx::VoxelClassID 
NodeIntersectionProcessor::getVoxelClassInside() const
{
    return voxelClassInside;
}

void 
NodeIntersectionProcessor::setVoxelClassOutside(Ionflux::VolGfx::VoxelClassID
newVoxelClassOutside)
{
	voxelClassOutside = newVoxelClassOutside;
}

Ionflux::VolGfx::VoxelClassID 
NodeIntersectionProcessor::getVoxelClassOutside() const
{
    return voxelClassOutside;
}

void 
NodeIntersectionProcessor::setVoxelClassBoundary(Ionflux::VolGfx::VoxelClassID
newVoxelClassBoundary)
{
	voxelClassBoundary = newVoxelClassBoundary;
}

Ionflux::VolGfx::VoxelClassID 
NodeIntersectionProcessor::getVoxelClassBoundary() const
{
    return voxelClassBoundary;
}

void NodeIntersectionProcessor::setTolerance(double newTolerance)
{
	tolerance = newTolerance;
}

double NodeIntersectionProcessor::getTolerance() const
{
    return tolerance;
}

void NodeIntersectionProcessor::setRayAxis(Ionflux::GeoUtils::AxisID 
newRayAxis)
{
	rayAxis = newRayAxis;
}

Ionflux::GeoUtils::AxisID NodeIntersectionProcessor::getRayAxis() const
{
    return rayAxis;
}

void NodeIntersectionProcessor::setMinWallThickness(unsigned int 
newMinWallThickness)
{
	minWallThickness = newMinWallThickness;
}

unsigned int NodeIntersectionProcessor::getMinWallThickness() const
{
    return minWallThickness;
}

void NodeIntersectionProcessor::setFillInsideOnly(bool newFillInsideOnly)
{
	fillInsideOnly = newFillInsideOnly;
}

bool NodeIntersectionProcessor::getFillInsideOnly() const
{
    return fillInsideOnly;
}

void NodeIntersectionProcessor::setMaxNumWallThicknessPasses(unsigned int 
newMaxNumWallThicknessPasses)
{
	maxNumWallThicknessPasses = newMaxNumWallThicknessPasses;
}

unsigned int NodeIntersectionProcessor::getMaxNumWallThicknessPasses() 
const
{
    return maxNumWallThicknessPasses;
}

Ionflux::VolGfx::NodeIntersectionProcessor& 
NodeIntersectionProcessor::operator=(const 
Ionflux::VolGfx::NodeIntersectionProcessor& other)
{
    if (this == &other)
        return *this;
    clearIntersections();
    for (NodeIntersectionVector::const_iterator i = 
        other.intersections.begin(); i != other.intersections.end(); i++)
        intersections.push_back(*i);
    setContext(other.context);
    setHitDataType(other.hitDataType);
    setVoxelClassHit(other.voxelClassHit);
    setLeafStatus(other.leafStatus);
    setLeafStatus(other.leafStatus);
    setRay(other.ray);
    setEnableBoundaryData(other.enableBoundaryData);
    setPruneEmptyNewIntersections(other.targetDepth);
    setEnableIOB(other.enableIOB);
    setEnableRayStabbing(other.enableRayStabbing);
    setVoxelClassFilled(other.voxelClassFilled);
    setVoxelClassInside(other.voxelClassInside);
    setVoxelClassOutside(other.voxelClassOutside);
    setVoxelClassBoundary(other.voxelClassBoundary);
    setTolerance(other.tolerance);
    setMinWallThickness(other.minWallThickness);
    setFillInsideOnly(other.fillInsideOnly);
    setMaxNumWallThicknessPasses(other.maxNumWallThicknessPasses);
	return *this;
}

Ionflux::VolGfx::NodeIntersectionProcessor* 
NodeIntersectionProcessor::copy() const
{
    NodeIntersectionProcessor* newNodeIntersectionProcessor = create();
    *newNodeIntersectionProcessor = *this;
    return newNodeIntersectionProcessor;
}

Ionflux::VolGfx::NodeIntersectionProcessor* 
NodeIntersectionProcessor::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<NodeIntersectionProcessor*>(other);
}

Ionflux::VolGfx::NodeIntersectionProcessor* 
NodeIntersectionProcessor::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    NodeIntersectionProcessor* newObject = new NodeIntersectionProcessor();
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::VolGfx::NodeIntersectionProcessor* 
NodeIntersectionProcessor::create(Ionflux::VolGfx::Context* initContext, 
Ionflux::VolGfx::NodeDataType initHitDataType, 
Ionflux::VolGfx::VoxelClassID initVoxelClassHit, 
Ionflux::VolGfx::LeafStatusID initLeafStatus, Ionflux::GeoUtils::Line3* 
initRay, bool initEnableBoundaryData, int initTargetDepth, bool 
initFillNewIntersections, bool initPruneEmptyNewIntersections, bool 
initEnableIOB, bool initEnableRayStabbing, bool initEnableWallThickness, 
Ionflux::VolGfx::VoxelClassID initVoxelClassFilled, 
Ionflux::VolGfx::VoxelClassID initVoxelClassInside, 
Ionflux::VolGfx::VoxelClassID initVoxelClassOutside, 
Ionflux::VolGfx::VoxelClassID initVoxelClassBoundary, double initTolerance,
unsigned int initMinWallThickness, bool initFillInsideOnly, unsigned int 
initMaxNumWallThicknessPasses, Ionflux::ObjectBase::IFObject* parentObject)
{
    NodeIntersectionProcessor* newObject = new 
    NodeIntersectionProcessor(initContext, initHitDataType, 
    initVoxelClassHit, initLeafStatus, initRay, initEnableBoundaryData, 
    initTargetDepth, initFillNewIntersections, 
    initPruneEmptyNewIntersections, initEnableIOB, initEnableRayStabbing, 
    initEnableWallThickness, initVoxelClassFilled, initVoxelClassInside, 
    initVoxelClassOutside, initVoxelClassBoundary, initTolerance, 
    initMinWallThickness, initFillInsideOnly, 
    initMaxNumWallThicknessPasses);
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int NodeIntersectionProcessor::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file NodeIntersectionProcessor.cpp
 * \brief Node intersection processor implementation.
 */
