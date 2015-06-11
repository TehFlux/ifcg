/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Node.cpp                        Voxel tree node (implementation).
 * ========================================================================== */

#include "ifvg/Node.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/imageutils.hpp"
#include "geoutils/FaceData.hpp"
#include "ifvg/utils.hpp"
#include "ifvg/serialize.hpp"
#include "ifvg/IFVGError.hpp"
#include "ifvg/NodeSet.hpp"
#include "ifvg/IOContext.hpp"
#include "ifvg/NodeProcessor.hpp"
#include "ifvg/NodeFilter.hpp"
#include "ifvg/NodeIntersectionProcessor.hpp"

using namespace std;

namespace Ionflux
{

namespace VolGfx
{

NodeClassInfo::NodeClassInfo()
{
	name = "Node";
	desc = "Voxel tree node";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

NodeClassInfo::~NodeClassInfo()
{
}

// public member constants
const Ionflux::VolGfx::NodeDataType Node::DATA_TYPE_UNKNOWN = 0;
const Ionflux::VolGfx::NodeDataType Node::DATA_TYPE_NULL = 1;
const Ionflux::VolGfx::NodeDataType Node::DATA_TYPE_DENSITY = 2;
const Ionflux::VolGfx::NodeDataType Node::DATA_TYPE_COLOR_RGBA = 3;
const Ionflux::VolGfx::NodeDataType Node::DATA_TYPE_DISTANCE_8 = 4;
const Ionflux::VolGfx::NodeDataType Node::DATA_TYPE_COLOR_NORMAL = 5;
const Ionflux::VolGfx::NodeDataType Node::DATA_TYPE_FACE_VEC = 6;
const Ionflux::VolGfx::NodeDataType Node::DATA_TYPE_VOXEL_CLASS = 7;
const Ionflux::VolGfx::NodeDataType Node::DATA_TYPE_VOXEL_IOB = 8;
const Ionflux::VolGfx::NodeDataType Node::DATA_TYPE_ANY_NOT_NULL = 100;
const int Node::CHILD_INDEX_INVALID = -1;
const Ionflux::ObjectBase::MagicSyllable Node::MAGIC_SYLLABLE_HEADER = 0x4845;
const Ionflux::ObjectBase::MagicSyllable Node::MAGIC_SYLLABLE_ROOT = 0x4e52;
const Ionflux::ObjectBase::MagicSyllable Node::MAGIC_SYLLABLE_NODE = 0x4e4f;
const Ionflux::ObjectBase::MagicSyllable Node::MAGIC_SYLLABLE_OFFSET_MAP = 0x4f4d;
const Ionflux::ObjectBase::MagicSyllable Node::MAGIC_SYLLABLE_DATA = 0x4e44;
const double Node::DEFAULT_RAY_PLANE_OFFSET = 0.5;

// run-time type information instance constants
const NodeClassInfo Node::nodeClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Node::CLASS_INFO = &Node::nodeClassInfo;

Node::Node()
: impl(0), context(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setImpl(createImpl());
}

Node::Node(const Ionflux::VolGfx::Node& other)
: impl(0), context(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Node::Node(Ionflux::VolGfx::Context* initContext, 
Ionflux::VolGfx::NodeImpl* initImpl)
: impl(0), context(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initContext != 0)
	    setContext(initContext);
	if (initImpl != 0)
	    setImpl(initImpl);
	else
	    setImpl(createImpl());
}

Node::~Node()
{
	if (impl != 0)
	    setImpl(0);
}

void Node::clear() const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "clear", "Node implementation");
	clearImpl(impl, true, true, true);
}

Ionflux::VolGfx::Node* Node::getParent() const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getParent", "Node implementation");
	return wrapImpl(impl->parent, context);
}

void Node::setChildNodes(const Ionflux::VolGfx::NodeVector& newNodes) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "setChildNodes", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "setChildNodes", "Context");
	int n0 = context->getMaxNumLeafChildNodesPerNode();
	if (newNodes.size() < static_cast<unsigned int>(n0))
	{
	    std::ostringstream status;
	    status << "Unexpected number of nodes in vector (expected: " 
	        << n0 << ", got: " << newNodes.size() << ")";
	    throw IFVGError(getErrorString(status.str(), "setChildNodes"));
	}
	NodeImplVector niv;
	for (int i = 0; i < n0; i++)
	{
	    Node* cn = newNodes[i];
	    if (cn != 0)
	    {
	        NodeImpl* ci = cn->getImpl();
	        Ionflux::ObjectBase::nullPointerCheck(ci, this, 
	            "setChildNodes", "Child node implementation");
	        niv.push_back(ci);
	    } else
	        niv.push_back(0);
	}
	setImplChildNodes(impl, context, niv);
}

void Node::mergeChildNodes(const Ionflux::VolGfx::NodeImplVector& newNodes,
bool fill0) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "mergeChildNodes", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "mergeChildNodes", "Context");
	mergeImplChildNodes(impl, context, newNodes, fill0);
}

void Node::mergeChildNodes(const Ionflux::VolGfx::NodeVector& newNodes, 
bool fill0) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "mergeChildNodes", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "mergeChildNodes", "Context");
	int n0 = context->getMaxNumLeafChildNodesPerNode();
	if (newNodes.size() < static_cast<unsigned int>(n0))
	{
	    std::ostringstream status;
	    status << "Unexpected number of nodes in vector (expected: " 
	        << n0 << ", got: " << newNodes.size() << ")";
	    throw IFVGError(getErrorString(status.str(), "mergeChildNodes"));
	}
	NodeImplVector niv;
	for (int i = 0; i < n0; i++)
	{
	    Node* cn = newNodes[i];
	    if (cn != 0)
	    {
	        NodeImpl* ci = cn->getImpl();
	        Ionflux::ObjectBase::nullPointerCheck(ci, this, 
	            "mergeChildNodes", "Child node implementation");
	        niv.push_back(ci);
	    } else
	        niv.push_back(0);
	}
	mergeImplChildNodes(impl, context, niv, fill0);
}

void Node::setChildNodeByOrderIndex(Ionflux::VolGfx::Node* newNode, int 
orderIndex) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "setChildNodeByOrderIndex", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "setChildNodeByOrderIndex", "Context");
	Ionflux::ObjectBase::nullPointerCheck(newNode, this, 
	    "setChildNodeByOrderIndex", "Node");
	NodeImpl* nImpl = newNode->getImpl();
	Ionflux::ObjectBase::nullPointerCheck(nImpl, this, 
	    "setChildNodeByOrderIndex", "Node implementation (new)");
	setImplChildByOrderIndex(impl, context, nImpl, orderIndex);
}

void Node::clearChildNodes(const Ionflux::VolGfx::NodeChildMask& 
clearNodes) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "clearChildNodes", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "clearChildNodes", "Context");
	clearImplChildNodes(impl, context, clearNodes);
}

unsigned int Node::pruneEmpty(bool recursive) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "pruneEmpty", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "pruneEmpty", "Context");
	return pruneEmptyImpl(impl, context, recursive);;
}

void Node::clearData() const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "clearData", "Node implementation");
	clearImpl(impl, true, true, false);
}

void Node::clearChildNodes() const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "clearChildNodes", "Node implementation");
	if (isImplLeaf(impl))
	    return;
	clearImpl(impl, true, false, true);
	NodeImpl* pi = impl->parent;
	if (pi != 0)
	    updateImpl(pi, context);
}

void Node::setData(Ionflux::VolGfx::NodeDataImpl* newData) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "setData", "Node implementation");
	clearImpl(impl, false, true, false);
	impl->data = newData;
}

void Node::setData(Ionflux::VolGfx::NodeDataType newType, const 
Ionflux::ObjectBase::DoubleVector* newData) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "setData", "Node implementation");
	NodeDataImpl* d0 = createDataImpl(newType, newData);
	clearImpl(impl, false, true, false);
	impl->data = d0;
}

void Node::clearLeafData() const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "clearLeafData", "Node implementation");
	if (!isLeaf())
	    return;
	clearImpl(impl, false, true, false);
}

int Node::getNumChildNodes() const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getNumChildNodes", "Node implementation");
	return getImplNumChildNodes(impl);
}

int Node::fill(bool clearExisting, bool recursive, int maxDepth) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "fill", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "fill", "Context");
	return fillImpl(impl, context, clearExisting, recursive, maxDepth);;
}

int Node::getChildValidIndex(Ionflux::VolGfx::Node* n) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getValidChildIndex", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(n, this, 
	    "getValidChildIndex", "Node");
	NodeImpl* oi = n->getImpl();
	Ionflux::ObjectBase::nullPointerCheck(oi, this, 
	    "getValidChildIndex", "Node implementation (other)");
	return getImplChildValidIndex(impl, oi);
}

int Node::getChildValidIndex(Ionflux::VolGfx::NodeImpl* otherImpl) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getValidChildIndex", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, this, 
	    "getValidChildIndex", "Node implementation (other)");
	return getImplChildValidIndex(impl, otherImpl);
}

int Node::getChildValidIndex(int orderIndex) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getChildValidIndex", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "setChildNodes", "Context");
	return getImplChildValidIndex(impl, context, orderIndex);
}

int Node::getChildOrderIndex(int index) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getChildOrderIndex", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "getChildOrderIndex", "Context");
	return getImplChildOrderIndex(impl, context, index);
}

Ionflux::VolGfx::NodeLoc3 Node::getChildLoc(int orderIndex) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getChildLoc", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "getChildLoc", "Context");
	return getImplChildLoc(impl, context, orderIndex);
}

bool Node::isLeafOrderChild(int orderIndex) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "isLeafOrderChild", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "isLeafOrderChild", "Context");
	return isImplLeafOrderChild(impl, context, orderIndex);;
}

bool Node::isLeafValidChild(int index) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "isLeafValidChild", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "isLeafOrderChild", "Context");
	return isImplLeafValidChild(impl, context, index);;
}

bool Node::isLeaf() const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "isLeaf", "Node implementation");
	return !impl->valid.any();
}

Ionflux::VolGfx::LeafStatusID Node::getLeafStatus()
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getLeafStatus", "Node implementation");
	return getImplLeafStatus(impl);
}

void Node::update()
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "update", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "update", "Context");
	updateImpl(impl, context);
}

bool Node::hasVoxelClassInfo()
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "hasVoxelClassInfo", "Node implementation");
	return hasImplVoxelClassInfo(impl);;
}

Ionflux::VolGfx::VoxelClassID Node::getVoxelClass()
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getVoxelClass", "Node implementation");
	return getImplVoxelClass(impl);
}

bool Node::hasVoxelClass(Ionflux::VolGfx::VoxelClassID mask)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "hasVoxelClass", "Node implementation");
	return hasImplVoxelClass(impl, mask);
}

Ionflux::VolGfx::VoxelClassID 
Node::setVoxelClass(Ionflux::VolGfx::VoxelClassID mask, bool enable, 
Ionflux::VolGfx::NodeDataType createDataType)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "setVoxelClass", "Node implementation");
	return setImplVoxelClass(impl, mask, enable, createDataType);
}

unsigned int Node::setVoxelClass0(Ionflux::VolGfx::VoxelClassID mask, bool 
enable, Ionflux::VolGfx::NodeFilter* filter, bool recursive, 
Ionflux::VolGfx::NodeDataType createDataType)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "setVoxelClass", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "setVoxelClass", "Context");
	return setImplVoxelClass(impl, context, mask, enable, filter, 
    recursive, createDataType);
}

bool Node::hasColorIndex()
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "hasColorIndex", "Node implementation");
	return hasImplColorIndex(impl);;
}

Ionflux::VolGfx::ColorIndex Node::getColorIndex()
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getColorIndex", "Node implementation");
	return getImplColorIndex(impl);
}

Ionflux::VolGfx::ColorIndex Node::setColorIndex(Ionflux::VolGfx::ColorIndex
color, Ionflux::VolGfx::NodeDataType createDataType)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "setColorIndex", "Node implementation");
	return setImplColorIndex(impl, color, createDataType);
}

unsigned int Node::setColorIndex0(Ionflux::VolGfx::ColorIndex color, 
Ionflux::VolGfx::NodeFilter* filter, bool recursive, 
Ionflux::VolGfx::NodeDataType createDataType)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "setColorIndex", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "setColorIndex", "Context");
	return setImplColorIndex(impl, context, color, filter, recursive, 
    createDataType);
}

Ionflux::VolGfx::Node* Node::getChildByOrderIndex(int orderIndex, bool 
autoCreate) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getChildByOrderIndex", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "getChildByOrderIndex", "Context");
	NodeImpl* ni = getImplChildByOrderIndex(impl, context, orderIndex, 
	    autoCreate);
	return wrapImpl(ni, context);
}

Ionflux::VolGfx::Node* Node::getChildByValidIndex(int index) const
{
	NodeImpl* ni = getImplChildByValidIndex(impl, index);
	return wrapImpl(ni, context);
}

Ionflux::VolGfx::Node* Node::locateChild(const Ionflux::VolGfx::NodeLoc3& 
loc, int maxDepth)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "locateChild", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "locateChild", "Context");
	NodeImpl* ni = locateImplChild(impl, context, loc, maxDepth);
	return wrapImpl(ni, context);
}

Ionflux::VolGfx::Node* Node::locateChild(const Ionflux::GeoUtils::Vector3& 
p, int maxDepth)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "locateChild", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "locateChild", "Context");
	NodeImpl* ni = locateImplChild(impl, context, p, maxDepth);
	return wrapImpl(ni, context);
}

Ionflux::VolGfx::Node* Node::locateRegion(const Ionflux::VolGfx::Region3& 
region, int maxDepth)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "locateRegion", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "locateRegion", "Context");
	NodeImpl* ni = locateImplRegion(impl, context, region, maxDepth);
	return wrapImpl(ni, context);
}

Ionflux::VolGfx::Node* Node::locateRegion(const Ionflux::GeoUtils::Range3& 
range, int maxDepth)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "locateRegion", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "locateRegion", "Context");
	Region3 r0 = context->createRegion(range);
	NodeImpl* ni = locateImplRegion(impl, context, r0, maxDepth);
	return wrapImpl(ni, context);
}

Ionflux::VolGfx::Node* Node::locateNode(const Ionflux::VolGfx::NodeLoc3& 
loc, int maxDepth)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "locateNode", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "locateNode", "Context");
	NodeImpl* ni = locateImplNode(impl, context, loc, maxDepth);
	return wrapImpl(ni, context);
}

int Node::getDepth() const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getDepth", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "getDepth", "Context");
	return getImplDepth(impl, context);;
}

int Node::getMaxDepth() const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getMaxDepth", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "getMaxDepth", "Context");
	return getImplMaxDepth(impl, context);;
}

Ionflux::VolGfx::Node* Node::insertChild(const Ionflux::VolGfx::NodeLoc3& 
loc, int depth, bool fill0, bool fillTargetDepth0)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "insertChild", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "insertChild", "Context");
	NodeImpl* ni = insertImplChild(impl, context, loc, depth, fill0, 
	    fillTargetDepth0);
	return wrapImpl(ni, context);
}

Ionflux::VolGfx::Node* Node::insertChild(const Ionflux::GeoUtils::Vector3& 
p, int depth, bool fill0)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "insertChild", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "insertChild", "Context");
	NodeImpl* ni = insertImplChild(impl, context, p, depth, fill0);
	return wrapImpl(ni, context);
}

Ionflux::VolGfx::Node* Node::insertChild(const Ionflux::VolGfx::NodeID& 
nodeID, bool fill0)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "insertChild", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "insertChild", "Context");
	NodeImpl* ni = insertImplChild(impl, context, nodeID, fill0);
	return wrapImpl(ni, context);
}

double Node::getVoxelSize()
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getVoxelSize", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "getVoxelSize", "Context");
	return getImplVoxelSize(impl, context);
}

double Node::getVoxelSizeLoc()
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getVoxelSizeLoc", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "getVoxelSizeLoc", "Context");
	return getImplVoxelSizeLoc(impl, context);
}

Ionflux::GeoUtils::Vector3 Node::getLocation() const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getLocation", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "getLocation", "Context");
	return getImplLocation(impl, context);
}

bool Node::getNeighborLoc(int offsetX, int offsetY, int offsetZ, 
Ionflux::VolGfx::NodeLoc3& target)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getNeighborLoc", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "getNeighborLoc", "Context");
	return getImplNeighborLoc(impl, context, offsetX, offsetY, offsetZ, target);
}

void Node::getRange(Ionflux::GeoUtils::Range3& target) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getRange", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "getRange", "Context");
	getImplRange(impl, context, target);
}

bool Node::getIntersectionLoc(Ionflux::GeoUtils::Line3& line, const 
Ionflux::GeoUtils::AAPlanePairIntersection& interData, 
Ionflux::VolGfx::Region3& target) const
{
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "getIntersection", "Context");
	return context->getIntersectionLoc(line, interData, target);
}

unsigned int Node::find(Ionflux::VolGfx::NodeSet* target, 
Ionflux::VolGfx::NodeFilter* filter, bool recursive)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "find", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "find", "Context");
	unsigned int numNodes = 0;
	if (target != 0)
	{
	    NodeImplVector v0;
	    numNodes = findImpl(impl, context, &v0, filter, recursive);
	    for (NodeImplVector::iterator i = v0.begin(); i != v0.end(); i++)
	    {
	        NodeImpl* ci = *i;
	        if (ci != 0)
	            target->addNode(wrapImpl(ci, context));
	    }
	} else
	    numNodes = findImpl(impl, context, 0, filter, recursive);
	return numNodes;
}

unsigned int Node::process(Ionflux::VolGfx::NodeProcessor* preProcessor, 
Ionflux::VolGfx::NodeFilter* filter, Ionflux::VolGfx::NodeProcessor* 
postProcessor, bool recursive)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "process", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "process", "Context");
	return processImpl(impl, context, preProcessor, filter, 
    postProcessor, recursive);
}

Ionflux::Altjira::Color* Node::getColor(Ionflux::Altjira::ColorSet* colors,
unsigned int colorIndexOffset, unsigned int colorIndexRange, int 
colorIndex, int leafColorIndex, Ionflux::VolGfx::VoxelClassColorVector* 
voxelClassColors)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getColor", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "getColor", "Context");
	return getImplColor(impl, context, colors, colorIndexOffset, 
    colorIndexRange, colorIndex, leafColorIndex, voxelClassColors);
}

void Node::getMesh(Ionflux::GeoUtils::Mesh& target, double boxInset, 
Ionflux::Altjira::ColorSet* colors, unsigned int colorOffset, unsigned int 
colorIndexOffset, unsigned int colorIndexRange, int leafColorIndex, 
Ionflux::VolGfx::NodeFilter* filter, bool recursive)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getMesh", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "getMesh", "Context");
	getImplMesh(impl, context, target, boxInset, colors, 
	    colorOffset, colorIndexOffset, colorIndexRange, leafColorIndex, 
	    filter, recursive);
}

void Node::getVertexAttributes(Ionflux::GeoUtils::VertexAttribute* 
positionTarget, Ionflux::GeoUtils::VertexAttribute* colorTarget, 
Ionflux::GeoUtils::VertexAttribute* normalTarget, 
Ionflux::GeoUtils::NFaceTypeID nFaceType, double boxInset, 
Ionflux::Altjira::ColorSet* colors, unsigned int colorIndexOffset, unsigned
int colorIndexRange, int colorIndex, int leafColorIndex, 
Ionflux::VolGfx::VoxelClassColorVector* voxelClassColors, 
Ionflux::GeoUtils::Vector* positionOffset, Ionflux::GeoUtils::Vector* 
positionScale, Ionflux::VolGfx::NodeFilter* filter, bool recursive, bool 
boundaryFacesOnly)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getMesh", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "getMesh", "Context");
	getImplVertexAttributes(impl, context, positionTarget, 
	    colorTarget, normalTarget, nFaceType, boxInset, colors, 
	    colorIndexOffset, colorIndexRange, colorIndex, leafColorIndex, 
	    voxelClassColors, positionOffset, positionScale, filter, 
	    recursive, boundaryFacesOnly);
}

unsigned int Node::getNumFaces(bool recursive)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "getNumFaces", "Node implementation");
	return getImplNumFaces(impl);
}

bool Node::voxelizeInsertFace(Ionflux::GeoUtils::Face* face, 
Ionflux::VolGfx::SeparabilityID sep, bool fill0)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "voxelizeInsertFace", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "voxelizeInsertFace", "Context");
	return voxelizeImplInsertFace(impl, context, face, sep, fill0);
}

unsigned int Node::voxelizeInsertFaces(const Ionflux::GeoUtils::Mesh& mesh,
Ionflux::VolGfx::SeparabilityID sep, bool fill0)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "Node::voxelizeInsertImplFaces", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "Node::voxelizeInsertImplFaces", "Context");
	return voxelizeImplInsertFaces(impl, context, mesh, sep, fill0);
}

unsigned int Node::voxelizeFaces(Ionflux::VolGfx::NodeProcessor* processor,
int targetDepth, Ionflux::VolGfx::SeparabilityID sep, bool fillTargetDepth,
bool pruneEmpty0, Ionflux::GeoUtils::FaceVector* faces0)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "voxelizeFaces", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "voxelizeFaces", "Context");
	return voxelizeImplFaces(impl, context, processor, targetDepth, sep, 
    fillTargetDepth, pruneEmpty0, faces0);;
}

unsigned int Node::getMemSize(bool recursive)
{
	unsigned int s0 = sizeof(Node);
	if (impl != 0)
	    s0 += getImplMemSize(impl, recursive);
	return s0;
}

unsigned int Node::getDataMemSize()
{
	if (impl == 0)
	    return 0;
	return getDataImplMemSize(impl->data);
}

void Node::serializeHierarchy(std::ostream& target)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "serializeHierarchy", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "serializeHierarchy", "Context");
	serializeImplHierarchy(impl, context, target);
}

void Node::serializeHierarchy(Ionflux::VolGfx::IOContext& ioContext)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "serializeHierarchy", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "serializeHierarchy", "Context");
	serializeImplHierarchy(impl, context, ioContext);
}

void Node::deserialize(Ionflux::VolGfx::IOContext& ioContext, 
Ionflux::ObjectBase::DataSize offset, Ionflux::ObjectBase::MagicSyllable 
magicSyllable, bool deserializeData, bool zeroChildPointer, bool 
zeroParentPointer)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "deserialize", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "deserialize", "Context");
	deserializeImpl(impl, context, ioContext, offset, magicSyllable, 
	    deserializeData, zeroChildPointer, zeroParentPointer);
}

void Node::deserializeHierarchy(std::istream& source, 
Ionflux::VolGfx::NodeImplHierarchyHeader* header, Ionflux::VolGfx::NodeID* 
targetNode, Ionflux::ObjectBase::PointerOffsetMap* poMap, 
Ionflux::ObjectBase::PointerOffsetMap* poMapCurrent, bool deserializeData, 
int maxDepth)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "deserializeImplHierarchy", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "deserializeImplHierarchy", "Context");
	deserializeImplHierarchy(impl, context, source, header, targetNode, 
	    poMap, poMapCurrent, deserializeData, maxDepth);
}

void Node::deserializeHierarchy(Ionflux::VolGfx::IOContext& ioContext, bool
deserializeData, int maxDepth)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "deserializeImplHierarchy", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "deserializeImplHierarchy", "Context");
	deserializeImplHierarchy(impl, context, ioContext, deserializeData, 
	    maxDepth);
}

bool Node::intersectRay(const Ionflux::GeoUtils::Line3& ray, 
Ionflux::VolGfx::NodeIntersection& target, double t)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "intersectRay", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "intersectRay", "Context");
	return intersectRayImpl(impl, context, ray, target, t);
}

unsigned int Node::intersectRay(const Ionflux::GeoUtils::Line3& ray, 
Ionflux::VolGfx::NodeIntersectionProcessor* processor, 
Ionflux::VolGfx::NodeFilter* filter, bool recursive, double t, 
Ionflux::VolGfx::NodeIntersection* pcIntersection, bool fill0, bool 
pruneEmpty0)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "intersectRay", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "intersectRay", "Context");
	return intersectRayImpl(impl, context, ray, processor, filter, 
    recursive, t, pcIntersection, fill0, pruneEmpty0);
}

unsigned int Node::castRayGrid(const Ionflux::GeoUtils::Vector3& rayOrigin,
const Ionflux::GeoUtils::Vector3& rayDirection, const 
Ionflux::GeoUtils::Vector3& originStepX, const Ionflux::GeoUtils::Vector3& 
originStepY, unsigned int numRaysX, unsigned int numRaysY, 
Ionflux::VolGfx::NodeIntersectionProcessor* processor, 
Ionflux::VolGfx::NodeFilter* filter, bool recursive, double t, bool fill0, 
bool pruneEmpty0)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "castRayGrid", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "castRayGrid", "Context");
	return castRayGridImpl(impl, context, rayOrigin, rayDirection, originStepX, 
    originStepY, numRaysX, numRaysY, processor, filter, recursive, t, 
    fill0, pruneEmpty0);
}

unsigned int Node::castRayGrid(const Ionflux::GeoUtils::AxisID& axis, int 
targetDepth, double planeOffset, 
Ionflux::VolGfx::NodeIntersectionProcessor* processor, 
Ionflux::VolGfx::NodeFilter* filter, bool recursive, double t, bool fill0, 
bool pruneEmpty0)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "castRayGrid", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, this, 
	    "castRayGrid", "Context");
	return castRayGridImpl(impl, context, axis, targetDepth, planeOffset, 
    processor, filter, recursive, t, fill0, pruneEmpty0);
}

unsigned int Node::merge(Ionflux::VolGfx::Node& source, 
Ionflux::VolGfx::MergePolicyID childPolicy, Ionflux::VolGfx::MergePolicyID 
dataPolicy, Ionflux::VolGfx::NodeFilter* sourceFilter, 
Ionflux::VolGfx::NodeFilter* targetFilter, Ionflux::VolGfx::NodeFilter* 
sourceMergeFilter, bool recursive, bool fill0)
{
	NodeImpl* sourceImpl = source.getImpl();
	Ionflux::ObjectBase::nullPointerCheck(sourceImpl, 
	    "merge", "Node implementation (source)");
	Ionflux::ObjectBase::nullPointerCheck(impl, 
	    "merge", "Node implementation (target)");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "merge", "Context");
	return mergeImpl(sourceImpl, impl, context, childPolicy, dataPolicy, 
    sourceFilter, targetFilter, sourceMergeFilter, recursive, fill0);
}

void Node::printDebugInfo(bool recursive, unsigned int indentWidth, char 
indentChar, unsigned int depth) const
{
	// TODO: Implementation.
	return printImplDebugInfo(impl, context, recursive, indentWidth, indentChar, depth);
}

std::string Node::getValueString() const
{
	std::ostringstream status;
	status << getImplValueString(impl, context);
	return status.str();
}

std::string Node::getDataTypeString(Ionflux::VolGfx::NodeDataType t)
{
	if (t == DATA_TYPE_UNKNOWN)
	    return "<unknown>";
	else
	if (t == DATA_TYPE_NULL)
	    return "<null>";
	else
	if (t == DATA_TYPE_DENSITY)
	    return "density";
	else
	if (t == DATA_TYPE_COLOR_RGBA)
	    return "color_rgba";
	else
	if (t == DATA_TYPE_DISTANCE_8)
	    return "distance_8";
	else
	if (t == DATA_TYPE_COLOR_NORMAL)
	    return "color_normal";
	else
	if (t == DATA_TYPE_FACE_VEC)
	    return "face_vec";
	else
	if (t == DATA_TYPE_VOXEL_CLASS)
	    return "voxel_class";
	else
	if (t == DATA_TYPE_VOXEL_IOB)
	    return "voxel_iob";
	return "<unknown>";
}

Ionflux::ObjectBase::DataSize 
Node::getDataTypeNumElements(Ionflux::VolGfx::NodeDataType t)
{
	if (t == DATA_TYPE_DENSITY)
	    return 1;
	else
	if (t == DATA_TYPE_COLOR_RGBA)
	    return 4;
	else
	if (t == DATA_TYPE_DISTANCE_8)
	    return 8;
	else
	if (t == DATA_TYPE_COLOR_NORMAL)
	    return 7;
	return Ionflux::ObjectBase::DATA_SIZE_INVALID;
}

std::string Node::getDataValueString(Ionflux::VolGfx::NodeDataImpl* data)
{
	Ionflux::ObjectBase::nullPointerCheck(data, 
	    "Node::getDataValueString", "Node data implementation");
	NodeDataType t = data->type;
	if (t == DATA_TYPE_UNKNOWN)
	    return "";
	else
	if (t == DATA_TYPE_NULL)
	    return "";
	else
	if (t == DATA_TYPE_DENSITY)
	{
	    // density value
	    NodeDataValue* d0 = static_cast<NodeDataValue*>(data->data);
	    Ionflux::ObjectBase::nullPointerCheck(d0, 
	        "Node::getDataValueString", "Node data value");
	    std::ostringstream status;
	    status << *d0;
	    return status.str();
	} else
	if (t == DATA_TYPE_FACE_VEC)
	{
	    // face vector
	    Ionflux::GeoUtils::FaceVector* dp1 = 
	        static_cast<Ionflux::GeoUtils::FaceVector*>(data->data);
	    std::ostringstream status;
	    for (unsigned int i = 0; i < dp1->size(); i++)
	    {
	        Ionflux::GeoUtils::Face* cf = (*dp1)[i];
	        if (cf != 0)
	        {
	            if (i > 0)
	                status << ", ";
	            status << "[" << cf->getValueString() << "]";
	        }
	    }
	    return status.str();
	} else
	if (t == DATA_TYPE_VOXEL_CLASS)
	{
	    // voxel class
	    VoxelClassID c0;
	    unpackVoxelClass(data->data, c0);
	    return getVoxelClassValueString(c0);
	} else
	if (t == DATA_TYPE_VOXEL_IOB)
	{
	    // voxel inside/outside/boundary
	    VoxelDataIOB* dp1 = static_cast<VoxelDataIOB*>(data->data);
	    return getVoxelDataIOBValueString(*dp1);
	} else
	if ((t == DATA_TYPE_COLOR_RGBA) 
	    || (t == DATA_TYPE_DISTANCE_8) 
	    || (t == DATA_TYPE_COLOR_NORMAL))
	{
	    // array data types
	    Ionflux::ObjectBase::DataSize n0 = getDataTypeNumElements(t);
	    if (n0 != Ionflux::ObjectBase::DATA_SIZE_INVALID)
	    {
	        NodeDataValue* d0 = static_cast<NodeDataValue*>(data->data);
	        Ionflux::ObjectBase::nullPointerCheck(d0, 
	            "Node::getDataValueString", "Node data value");
	        std::ostringstream status;
	        for (Ionflux::ObjectBase::DataSize i = 0; i < n0; i++)
	        {
	            if (i > 0)
	                status << ", ";
	            status << d0[i];
	        }
	        return status.str();
	    }
	}
	return "<unknown>";
}

Ionflux::VolGfx::NodeImpl* Node::createImpl()
{
	NodeImpl* newImpl = Ionflux::ObjectBase::create<NodeImpl>(
	    "Node::createImpl", "node implementation");
	newImpl->refCount = 0;
	newImpl->loc.x = 0;
	newImpl->loc.y = 0;
	newImpl->loc.z = 0;
	newImpl->valid = 0;
	newImpl->leaf = 0;
	newImpl->parent = 0;
	newImpl->data = 0;
	newImpl->child = 0;
	return newImpl;
}

void Node::copyImpl(Ionflux::VolGfx::NodeImpl& source, 
Ionflux::VolGfx::NodeImpl& target, bool takeover)
{
	target.loc.x = source.loc.x;
	target.loc.y = source.loc.y;
	target.loc.z = source.loc.z;
	if (!takeover)
	{
	    target.valid = 0;
	    target.leaf = 0;
	    target.data = 0;
	    target.child = 0;
	} else
	{
	    target.valid = source.valid;
	    target.leaf = source.leaf;
	    target.data = source.data;
	    target.child = source.child;
	    source.valid = 0;
	    source.leaf = 0;
	    source.data = 0;
	    source.child = 0;
	}
}

Ionflux::ObjectBase::UInt16 Node::refImpl(Ionflux::VolGfx::NodeImpl* 
otherImpl)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::refImpl", "Node implementation");
	if (otherImpl->refCount < MAX_REF_COUNT)
	    otherImpl->refCount++;
	else
	    throw IFVGError("[Node::refImpl] Reference count overflow.");
	return otherImpl->refCount;
}

void Node::clearDataImpl(Ionflux::VolGfx::NodeDataImpl* dataImpl)
{
	Ionflux::ObjectBase::nullPointerCheck(dataImpl, 
	    "Node::clearDataImpl", "Node data implementation");
	NodeDataImpl* dp = dataImpl;
	if (dp->type == DATA_TYPE_DENSITY)
	{
	    // density value
	    NodeDataValue* dp1 = 
	        static_cast<NodeDataValue*>(dp->data);
	    delete dp1;
	} else 
	if (dp->type == DATA_TYPE_FACE_VEC)
	{
	    // face vector
	    Ionflux::GeoUtils::FaceVector* dp1 = 
	        static_cast<Ionflux::GeoUtils::FaceVector*>(dp->data);
	    delete dp1;
	} else 
	if (dp->type == DATA_TYPE_VOXEL_CLASS)
	{
	    // voxel class
	    // Nothing to be done.
	} else 
	if (dp->type == DATA_TYPE_VOXEL_IOB)
	{
	    // voxel inside/outside/boundary
	    VoxelDataIOB* dp1 = static_cast<VoxelDataIOB*>(dp->data);
	    delete dp1;
	} else 
	if ((dp->type == DATA_TYPE_COLOR_RGBA) 
	    || (dp->type == DATA_TYPE_DISTANCE_8) 
	    || (dp->type == DATA_TYPE_COLOR_NORMAL))
	{
	    // array types
	    NodeDataValue* dp1 = 
	        static_cast<NodeDataValue*>(dp->data);
	    delete[] dp1;
	} else 
	if (dp->type != DATA_TYPE_NULL)
	{
	    throw IFVGError("[Node::clearDataImpl] "
	        "Cannot delete data of unknown type");
	}
	dp->data = 0;
	dp->type = DATA_TYPE_NULL;
}

void Node::clearImpl(Ionflux::VolGfx::NodeImpl* otherImpl, bool recursive, 
bool clearData, bool clearChildNodes)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::clearImpl", "Node implementation");
	if (clearChildNodes && otherImpl->valid.any())
	{
	    NodeImpl* cp = otherImpl->child;
	    if (cp != 0)
	    {
	        // Delete child nodes.
	        int numChildNodes = otherImpl->valid.count();
	        for (int i = 0; i < numChildNodes; i++)
	        {
	            NodeImpl& cn = cp[i];
	            if (cn.refCount > 1)
	            {
	                std::ostringstream status;
	                status << "[Node::unrefImpl] Cannot delete "
	                    "child node because it is still referenced "
	                    "(i = " << i << ").";
	                throw IFVGError(status.str());
	            } else
	            if (cn.refCount == 0)
	            {
	                throw IFVGError("[Node::clearImpl] Attempt to remove "
	                    "reference from node implementation with zero "
	                    "references.");
	            }
	            cn.refCount = 0;
	            cn.parent = 0;
	            if (recursive)
	            {
	                /* NOTE: Data has to be cleared as well when recursively 
	                         deleting nodes. */
	                clearImpl(&cn, true, true, clearChildNodes);
	            }
	        }
	        delete[] cp;
	        otherImpl->child = 0;
	    }
	    otherImpl->valid = 0;
	    otherImpl->leaf = 0;
	}
	if (clearData && (otherImpl->data != 0))
	{
	    // Delete data node.
	    NodeDataImpl* dp = otherImpl->data;
	    clearDataImpl(dp);
	    delete dp;
	    otherImpl->data = 0;
	}
}

Ionflux::ObjectBase::UInt16 Node::unrefImpl(Ionflux::VolGfx::NodeImpl* 
otherImpl)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::refImpl", "Node implementation");
	if (otherImpl->refCount > 0)
	{
	    otherImpl->refCount--;
	    if (otherImpl->refCount == 0)
	    {
	        clearImpl(otherImpl, true, true, true);
	        delete otherImpl;
	    }
	    return 0;
	} else
	{
	    throw IFVGError("[Node::unrefImpl] Attempt to remove "
	        "reference from node implementation with zero "
	        "references.");
	}
	return otherImpl->refCount;
}

Ionflux::VolGfx::Node* Node::wrapImpl(Ionflux::VolGfx::NodeImpl* otherImpl,
Ionflux::VolGfx::Context* context)
{
	Node* result = 0;
	if (otherImpl != 0)
	    result = Node::create(context, otherImpl);
	return result;
}

void Node::setImplParent(Ionflux::VolGfx::NodeImpl* otherImpl)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::setImplParent", "Node implementation");
	if (otherImpl->valid.any())
	{
	    NodeImpl* cp = otherImpl->child;
	    if (cp != 0)
	    {
	        // Set parent for child nodes.
	        int numChildNodes = otherImpl->valid.count();
	        for (int i = 0; i < numChildNodes; i++)
	        {
	            NodeImpl& cn = cp[i];
	            cn.parent = otherImpl;
	        }
	    }
	}
}

void Node::updateImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::updateImpl", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::updateImpl", "Context");
	// Update leaf node flags.
	otherImpl->leaf = 0;
	NodeImpl* cp = otherImpl->child;
	if (cp != 0)
	{
	    if (otherImpl->valid.any())
	    {
	        int n0 = context->getMaxNumLeafChildNodesPerNode();
	        int k = 0;
	        for (int i = 0; i < n0; i++)
	        {
	            if (otherImpl->valid.test(i))
	            {
	                NodeImpl& cn = cp[k];
	                if (!cn.valid.any())
	                    otherImpl->leaf.set(i, true);
	                k++;
	            }
	        }
	    }
	} else
	    otherImpl->valid = 0;
}

Ionflux::VolGfx::NodeDataImpl* 
Node::createDataImpl(Ionflux::VolGfx::NodeDataType t, const 
Ionflux::ObjectBase::DoubleVector* newData)
{
	Ionflux::VolGfx::NodeDataImpl* newImpl = 
	    Ionflux::ObjectBase::create<NodeDataImpl>("Node::createDataImpl", 
	        "node data implementation");
	newImpl->type = t;
	if (t == DATA_TYPE_NULL)
	    newImpl->data = 0;
	else
	if (t == DATA_TYPE_DENSITY)
	{
	    // density value
	    NodeDataValue* dp = Ionflux::ObjectBase::create<NodeDataValue>(
	        "Node::createDataImpl", "Node density data");
	    if ((newData != 0) 
	        && (newData->size() > 0))
	    {
	        *dp = (*newData)[0];
	    } else
	        *dp = DENSITY_EMPTY;
	    newImpl->data = dp;
	} else
	if (t == DATA_TYPE_FACE_VEC)
	{
	    // face vector
	    Ionflux::GeoUtils::FaceVector* dp = 
	        new Ionflux::GeoUtils::FaceVector;
	    if (dp == 0)
	    {
	        throw IFVGError("[Node::createDataImpl] "
	            "Could not allocate data.");
	    }
	    newImpl->data = dp;
	} else
	if (t == DATA_TYPE_VOXEL_CLASS)
	{
	    // voxel class
	    packVoxelClass(VOXEL_CLASS_UNDEFINED, newImpl->data);
	} else
	if (t == DATA_TYPE_VOXEL_IOB)
	{
	    // voxel inside/outside/boundary
	    VoxelDataIOB* dp = Ionflux::ObjectBase::create<VoxelDataIOB>(
	        "Node::createDataImpl", "Voxel data");
	    *dp = createVoxelDataIOB();
	    newImpl->data = dp;
	} else
	if ((t == DATA_TYPE_COLOR_RGBA) 
	    || (t == DATA_TYPE_DISTANCE_8) 
	    || (t == DATA_TYPE_COLOR_NORMAL))
	{
	    // array types
	    Ionflux::ObjectBase::DataSize n0 = getDataTypeNumElements(t);
	    if (n0 != Ionflux::ObjectBase::DATA_SIZE_INVALID)
	    {
	        // allocate data array
	        NodeDataValue* dp = new NodeDataValue[n0];
	        if (dp == 0)
	        {
	            throw IFVGError("[Node::createDataImpl] "
	                "Could not allocate data.");
	        }
	        for (Ionflux::ObjectBase::DataSize i = 0; i < n0; i++)
	        {
	            NodeDataValue& v0 = dp[i];
	            if ((newData != 0) 
	                && (newData->size() > i))
	            {
	                v0 = (*newData)[i];
	            } else
	                v0 = 0.;
	        }
	        newImpl->data = dp;
	    } else
	    {
	        std::ostringstream status;
	        status << "[Node::createDataImpl] Invalid node data type: " << t;
	        throw IFVGError(status.str());
	    }
	}
	return newImpl;
}

unsigned int Node::getDataImplMemSize(Ionflux::VolGfx::NodeDataImpl* 
dataImpl)
{
	if (dataImpl == 0)
	    return 0;
	unsigned int s0 = sizeof(NodeDataImpl);
	NodeDataType t0 = dataImpl->type;
	if (t0 == DATA_TYPE_DENSITY)
	{
	    // density value
	    s0 += 1;
	} else
	if (t0 == DATA_TYPE_FACE_VEC)
	{
	    // face vector
	    Ionflux::GeoUtils::FaceVector* dp = 
	        static_cast<Ionflux::GeoUtils::FaceVector*>(dataImpl->data);
	    if (dp != 0)
	    {
	        s0 += sizeof(Ionflux::GeoUtils::FaceVector);
	        s0 += (dp->size() * sizeof(Ionflux::GeoUtils::Face*));
	    }
	} else
	if (t0 == DATA_TYPE_VOXEL_IOB)
	{
	    // voxel inside/outside/boundary
	    VoxelDataIOB* dp = static_cast<VoxelDataIOB*>(dataImpl->data);
	    if (dp != 0)
	        s0 += sizeof(VoxelDataIOB);
	} else
	if (t0 == DATA_TYPE_VOXEL_CLASS)
	{
	    // voxel class
	    // Nothing to be done.
	} else
	if ((t0 == DATA_TYPE_COLOR_RGBA) 
	    || (t0 == DATA_TYPE_DISTANCE_8) 
	    || (t0 == DATA_TYPE_COLOR_NORMAL))
	{
	    // array types
	    unsigned int n0 = getDataTypeNumElements(t0);
	    s0 += (n0 * sizeof(NodeDataValue));
	}
	return s0;
}

void Node::setDataImplColorNormal(Ionflux::VolGfx::NodeDataImpl* dataImpl, 
const Ionflux::Altjira::Color& color, const Ionflux::GeoUtils::Vector3& 
normal)
{
	Ionflux::ObjectBase::nullPointerCheck(dataImpl, 
	    "Node::setDataImplColorNormal", "Node data implementation");
	if (dataImpl->type != DATA_TYPE_COLOR_NORMAL)
	{
	    std::ostringstream status;
	    status << "[Node::setDataImplColorNormal] "
	        "Node data implementation has incorrect type (type = '" 
	        << getDataTypeString(dataImpl->type) << "').";
	    throw IFVGError(status.str());
	}
	NodeDataValue* dp = Ionflux::ObjectBase::nullPointerCheck(
	    static_cast<NodeDataValue*>(dataImpl->data), 
	    "Node::setDataImplColorNormal", "Data pointer");
	for (unsigned int i = 0; i < 7; i++)
	{
	    if (i == 0)
	        dp[i] = color.getRed();
	    else 
	    if (i == 1)
	        dp[i] = color.getGreen();
	    else 
	    if (i == 2)
	        dp[i] = color.getBlue();
	    else 
	    if (i == 3)
	        dp[i] = color.getAlpha();
	    else 
	    if (i > 3)
	        dp[i] = normal[i - 3];
	}
}

Ionflux::VolGfx::NodeDataType 
Node::getImplDataType(Ionflux::VolGfx::NodeImpl* otherImpl)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplDataType", "Node data implementation");
	NodeDataImpl* d0 = otherImpl->data;
	if (d0 != 0)
	    return d0->type;
	return DATA_TYPE_NULL;
}

bool Node::hasImplDataType(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::NodeDataType dataType)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::hasImplDataType", "Node data implementation");
	NodeDataType t0 = getImplDataType(otherImpl);
	if (((dataType == DATA_TYPE_ANY_NOT_NULL) 
	        && (t0 != DATA_TYPE_NULL))
	    || (t0 == dataType))
	    return true;
	return false;
}

Ionflux::VolGfx::NodeDataImpl* Node::getImplData(Ionflux::VolGfx::NodeImpl*
otherImpl, Ionflux::VolGfx::NodeDataType dataType)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplData", "Node data implementation");
	NodeDataImpl* d0 = otherImpl->data;
	if ((d0 != 0)
	    && (d0->type != dataType))
	{
	    // clear existing data of wrong type
	    clearImpl(otherImpl, false, true, false);
	    d0 = otherImpl->data;
	}
	if (d0 == 0)
	{
	    // create new data of specified type
	    d0 = createDataImpl(dataType);
	    otherImpl->data = d0;
	}
	return otherImpl->data;
}

bool Node::dataTypeHasVoxelClassInfo(Ionflux::VolGfx::NodeDataType 
dataType)
{
	if ((dataType == DATA_TYPE_VOXEL_CLASS) 
	    || (dataType == DATA_TYPE_VOXEL_IOB))
	    return true;
	return false;
}

bool Node::hasImplVoxelClassInfo(Ionflux::VolGfx::NodeImpl* otherImpl)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::hasImplVoxelClassInfo", "Node implementation");
	NodeDataType t0 = getImplDataType(otherImpl);
	return dataTypeHasVoxelClassInfo(t0);;
}

Ionflux::VolGfx::VoxelClassID 
Node::getImplVoxelClass(Ionflux::VolGfx::NodeImpl* otherImpl)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplVoxelClass", "Node implementation");
	VoxelClassID c0 = VOXEL_CLASS_UNDEFINED;
	NodeDataType t0 = getImplDataType(otherImpl);
	if (t0 == DATA_TYPE_NULL)
	    return c0;
	NodeDataImpl* dp = Ionflux::ObjectBase::nullPointerCheck(
	    otherImpl->data, "Node::getImplVoxelClass", "Node data");
	if (t0 == DATA_TYPE_VOXEL_CLASS)
	{
	    // voxel class
	    unpackVoxelClass(dp->data, c0);
	} else
	if (t0 == DATA_TYPE_VOXEL_IOB)
	{
	    // voxel inside/outside/boundary
	    VoxelDataIOB* d0 = static_cast<VoxelDataIOB*>(dp->data);
	    if (d0 != 0)
	        c0 = d0->voxelClass;
	}
	return c0;
}

bool Node::hasImplVoxelClass(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::VoxelClassID mask)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::hasImplVoxelClass", "Node implementation");
	VoxelClassID c0 = getImplVoxelClass(otherImpl);
	if (Ionflux::VolGfx::checkVoxelClass(c0, mask))
	    return true;
	return false;
}

Ionflux::VolGfx::VoxelClassID 
Node::setImplVoxelClass(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::VoxelClassID mask, bool enable, 
Ionflux::VolGfx::NodeDataType createDataType)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::setImplVoxelClass", "Node implementation");
	VoxelClassID c0 = VOXEL_CLASS_UNDEFINED;
	NodeDataType t0 = getImplDataType(otherImpl);
	NodeDataImpl* dp = 0;
	if (t0 == DATA_TYPE_NULL)
	{
	    // no data attached
	    if (createDataType == DATA_TYPE_UNKNOWN)
	        return c0;
	    if (!dataTypeHasVoxelClassInfo(createDataType))
	    {
	        std::ostringstream status;
	        status << "Data type to be created does not support "
	            "voxel class info (" 
	            << getDataTypeString(createDataType) << " (" 
	            << static_cast<int>(createDataType) << ")).";
	        throw IFVGError(Ionflux::ObjectBase::getErrorString(
	            status.str(), "Node::setImplVoxelClass"));
	    }
	    dp = getImplData(otherImpl, createDataType);
	    t0 = createDataType;
	} else
	{
	    dp = Ionflux::ObjectBase::nullPointerCheck(
	        otherImpl->data, "Node::getImplVoxelClass", "Node data");
	}
	if (t0 == DATA_TYPE_VOXEL_CLASS)
	{
	    // voxel class
	    unpackVoxelClass(dp->data, c0);
	    Ionflux::VolGfx::setVoxelClass(mask, c0, enable);
	    packVoxelClass(c0, dp->data);
	} else
	if (t0 == DATA_TYPE_VOXEL_IOB)
	{
	    // voxel inside/outside/boundary
	    VoxelDataIOB* d0 = static_cast<VoxelDataIOB*>(dp->data);
	    if (d0 != 0)
	    {
	        Ionflux::VolGfx::setVoxelClass(mask, d0->voxelClass, enable);
	        c0 = d0->voxelClass;
	    }
	}
	return c0;
}

unsigned int Node::setImplVoxelClass(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, Ionflux::VolGfx::VoxelClassID mask, bool
enable, Ionflux::VolGfx::NodeFilter* filter, bool recursive, 
Ionflux::VolGfx::NodeDataType createDataType)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::setImplVoxelClass", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::setImplVoxelClass", "Context");
	if (filter != 0)
	{
	    int maxDepth = filter->getMaxDepth();
	    int depth = getImplDepth(otherImpl, context);
	    if (!context->checkDepthRange(depth, 0, maxDepth))
	        return 0;
	}
	unsigned int numNodes = 0;
	if ((filter == 0) 
	    || NodeProcessor::checkFlags(
	        filter->process(otherImpl), NodeFilter::RESULT_PASS))
	{
	    // set voxel class on this node implementation
	    setImplVoxelClass(otherImpl, mask, enable, createDataType);
	    numNodes++;
	}
	if (!recursive)
	    return numNodes;
	// set voxel class recursively
	int n0 = getImplNumChildNodes(otherImpl);
	for (int i = 0; i < n0; i++)
	{
	    NodeImpl* cn0 = Ionflux::ObjectBase::nullPointerCheck(
	        getImplChildByValidIndex(otherImpl, i), 
	        "Node::setImplVoxelClass", "Child node implementation");
	    numNodes += setImplVoxelClass(cn0, context, mask, enable, 
	        filter, true, createDataType);
	}
	return numNodes;
}

bool Node::dataTypeHasColorIndex(Ionflux::VolGfx::NodeDataType dataType)
{
	if (dataType == DATA_TYPE_VOXEL_IOB)
	    return true;
	return false;
}

bool Node::hasImplColorIndex(Ionflux::VolGfx::NodeImpl* otherImpl)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::hasImplColorIndex", "Node implementation");
	NodeDataType t0 = getImplDataType(otherImpl);
	return dataTypeHasColorIndex(t0);;
}

Ionflux::VolGfx::ColorIndex 
Node::getImplColorIndex(Ionflux::VolGfx::NodeImpl* otherImpl)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplColorIndex", "Node implementation");
	ColorIndex c0 = COLOR_INDEX_UNSPECIFIED;
	NodeDataType t0 = getImplDataType(otherImpl);
	if (t0 == DATA_TYPE_NULL)
	    return c0;
	NodeDataImpl* dp = Ionflux::ObjectBase::nullPointerCheck(
	    otherImpl->data, "Node::getImplColorIndex", "Node data");
	if (t0 == DATA_TYPE_VOXEL_IOB)
	{
	    // voxel inside/outside/boundary
	    VoxelDataIOB* d0 = static_cast<VoxelDataIOB*>(dp->data);
	    if (d0 != 0)
	        c0 = d0->color;
	}
	return c0;
}

Ionflux::VolGfx::ColorIndex 
Node::setImplColorIndex(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::ColorIndex color, Ionflux::VolGfx::NodeDataType 
createDataType)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::setImplColorIndex", "Node implementation");
	ColorIndex c0 = COLOR_INDEX_UNSPECIFIED;
	NodeDataType t0 = getImplDataType(otherImpl);
	NodeDataImpl* dp = 0;
	if (t0 == DATA_TYPE_NULL)
	{
	    // no data attached
	    if (createDataType == DATA_TYPE_UNKNOWN)
	        return c0;
	    if (!dataTypeHasColorIndex(createDataType))
	    {
	        std::ostringstream status;
	        status << "Data type to be created does not support "
	            "color index (" 
	            << getDataTypeString(createDataType) << " (" 
	            << static_cast<int>(createDataType) << ")).";
	        throw IFVGError(Ionflux::ObjectBase::getErrorString(
	            status.str(), "Node::setImplColorIndex"));
	    }
	    dp = getImplData(otherImpl, createDataType);
	    t0 = createDataType;
	} else
	{
	    dp = Ionflux::ObjectBase::nullPointerCheck(
	        otherImpl->data, "Node::setImplColorIndex", "Node data");
	}
	if (t0 == DATA_TYPE_VOXEL_IOB)
	{
	    // voxel inside/outside/boundary
	    VoxelDataIOB* d0 = static_cast<VoxelDataIOB*>(dp->data);
	    if (d0 != 0)
	    {
	        d0->color = color;
	        c0 = d0->color;
	    }
	}
	return c0;
}

unsigned int Node::setImplColorIndex(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, Ionflux::VolGfx::ColorIndex color, 
Ionflux::VolGfx::NodeFilter* filter, bool recursive, 
Ionflux::VolGfx::NodeDataType createDataType)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::setImplColorIndex", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::setImplColorIndex", "Context");
	if (filter != 0)
	{
	    int maxDepth = filter->getMaxDepth();
	    int depth = getImplDepth(otherImpl, context);
	    if (!context->checkDepthRange(depth, 0, maxDepth))
	        return 0;
	}
	unsigned int numNodes = 0;
	if ((filter == 0) 
	    || NodeProcessor::checkFlags(
	        filter->process(otherImpl), NodeFilter::RESULT_PASS))
	{
	    // set color index on this node implementation
	    setImplColorIndex(otherImpl, color, createDataType);
	    numNodes++;
	}
	if (!recursive)
	    return numNodes;
	// set color index recursively
	int n0 = getImplNumChildNodes(otherImpl);
	for (int i = 0; i < n0; i++)
	{
	    NodeImpl* cn0 = Ionflux::ObjectBase::nullPointerCheck(
	        getImplChildByValidIndex(otherImpl, i), 
	        "Node::setImplColorIndex", "Child node implementation");
	    numNodes += setImplColorIndex(cn0, context, color, filter, 
	        true, createDataType);
	}
	return numNodes;
}

Ionflux::VolGfx::FaceMaskInt 
Node::getImplBoundaryFaces(Ionflux::VolGfx::NodeImpl* otherImpl)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplBoundaryFaces", "Node implementation");
	NodeDataType t0 = getImplDataType(otherImpl);
	if (t0 == DATA_TYPE_NULL)
	    return FACE_UNDEFINED;
	NodeDataImpl* dp = Ionflux::ObjectBase::nullPointerCheck(
	    otherImpl->data, "Node::getImplBoundaryFaces", "Node data");
	FaceMaskInt fm0 = FACE_UNDEFINED;
	if (t0 == DATA_TYPE_VOXEL_IOB)
	{
	    // voxel inside/outside/boundary
	    VoxelDataIOB* d0 = static_cast<VoxelDataIOB*>(dp->data);
	    if (d0 != 0)
	        fm0 = d0->boundaryFaces;
	}
	return fm0;
}

Ionflux::VolGfx::NodeImpl* Node::getImplParent(Ionflux::VolGfx::NodeImpl* 
otherImpl)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::isImplParent", "Node implementation");
	return otherImpl->parent;
}

bool Node::isImplLeaf(Ionflux::VolGfx::NodeImpl* otherImpl)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::isImplLeaf", "Node implementation");
	return !otherImpl->valid.any();
}

Ionflux::VolGfx::LeafStatusID 
Node::getImplLeafStatus(Ionflux::VolGfx::NodeImpl* otherImpl)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplLeafStatus", "Node implementation");
	if (isImplLeaf(otherImpl))
	    return NODE_LEAF;
	return NODE_NON_LEAF;
}

bool Node::isImplLeafOrderChild(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, int orderIndex)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::isImplLeafOrderChild", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::isImplLeafOrderChild", "Context");
	if (orderIndex < 0)
	{
	    std::ostringstream status;
	    status << "[Node::isImplLeafOrderChild] "
	        "Invalid child order index (" << orderIndex << ").";
	    throw IFVGError(status.str());
	}
	int n0 = context->getMaxNumLeafChildNodesPerNode();
	if (orderIndex >= n0)
	{
	    std::ostringstream status;
	    status << "[Node::isImplLeafOrderChild] "
	        "Child node index out of range: " << orderIndex;
	    throw IFVGError(status.str());
	}
	return otherImpl->leaf.test(orderIndex);
}

bool Node::isImplLeafValidChild(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, int index)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::isImplLeafValidChild", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::isImplLeafValidChild", "Context");
	int numChildNodes = getImplNumChildNodes(otherImpl);
	if (index > numChildNodes)
	{
	    std::ostringstream status;
	    status << "[Node::isImplLeafValidChild] "
	        "Child node index out of range: " << index;
	    throw IFVGError(status.str());
	}
	int oi = getImplChildOrderIndex(otherImpl, context, index);
	return isImplLeafOrderChild(otherImpl, context, oi);;
}

int Node::getImplDepth(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplDepth", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::getImplDepth", "Context");
	LocInt maxNumLevels = context->getMaxNumLevels();
	if (otherImpl->parent == 0)
	    return 0;
	int depth = 0;
	NodeImpl* ci = otherImpl;
	while ((ci->parent != 0) 
	    && (depth < (maxNumLevels - 1)))
	{
	    depth++;
	    ci = ci->parent;
	}
	if (depth >= maxNumLevels)
	{
	    std::ostringstream status;
	    status << "[Node::getImplDepth] Depth above maximum "
	        "(maxNumLevels = " << maxNumLevels << ", depth = " 
	        << depth << ")";
	    throw IFVGError(status.str());
	}
	return depth;
}

int Node::getImplMaxDepth(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplMaxDepth", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::getImplMaxDepth", "Context");
	int maxDepth = getImplDepth(otherImpl, context);
	int n0 = getImplNumChildNodes(otherImpl);
	for (int i = 0; i < n0; i++)
	{
	    NodeImpl* cn0 = Ionflux::ObjectBase::nullPointerCheck(
	        getImplChildByValidIndex(otherImpl, i), 
	        "Node::getImplMaxDepth", "Child node implementation");
	    int d0 = getImplMaxDepth(cn0, context);
	    if (d0 > maxDepth)
	        maxDepth = d0;
	}
	return maxDepth;
}

Ionflux::VolGfx::NodeID Node::getImplNodeID(Ionflux::VolGfx::NodeImpl* 
otherImpl, Ionflux::VolGfx::Context* context)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplNodeID", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::getImplNodeID", "Context");
	NodeID nid0;
	nid0.loc = otherImpl->loc;
	nid0.depth = getImplDepth(otherImpl, context);
	return nid0;
}

int Node::getImplChildValidIndex(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::NodeImpl* childImpl)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplChildValidIndex", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(childImpl, 
	    "Node::getImplChildValidIndex", "Node implementation");
	int numChildNodes = getImplNumChildNodes(otherImpl);
	NodeImpl* cp = otherImpl->child;
	Ionflux::ObjectBase::nullPointerCheck(cp, 
	    "Node::getImplChildValidIndex", "Child node pointer");
	int result = CHILD_INDEX_INVALID;
	int i = 0;
	while ((i < numChildNodes) 
	    && (result == CHILD_INDEX_INVALID))
	{
	    NodeImpl& cn = cp[i];
	    if (&cn == otherImpl)
	        result = i;
	    i++;
	}
	return result;
}

int Node::getImplChildValidIndex(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, int orderIndex)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplChildValidIndex", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::getImplChildValidIndex", "Context");
	int n0 = context->getMaxNumLeafChildNodesPerNode();
	int numChildNodes = getImplNumChildNodes(otherImpl);
	if (orderIndex >= n0)
	{
	    std::ostringstream status;
	    status << "[Node::getImplChildValidIndex] "
	        "Child node index out of range: " << orderIndex;
	    throw IFVGError(status.str());
	}
	if (!otherImpl->valid.test(orderIndex))
	{
	    /* <---- DEBUG ----- //
	    std::cout << "[Node::getImplChildValidIndex] DEBUG: ["
	        << getImplValueString(otherImpl, context) << "] "
	        "Child node invalid for order index (" 
	        << orderIndex << ")." << std::endl;
	    // <---- DEBUG ----- */
	    return CHILD_INDEX_INVALID;
	}
	int i = 0;
	int k = 0;
	while ((i <= orderIndex) 
	    && (k < numChildNodes))
	{
	    if (otherImpl->valid.test(i))
	        k++;
	    i++;
	}
	if (i == orderIndex + 1)
	    return k - 1;
	/* <---- DEBUG ----- //
	std::cout << "[Node::getImplChildValidIndex] DEBUG: ["
	    << getImplValueString(otherImpl, context) << "] "
	    "Child node invalid for order index (orderIndex = " 
	    << orderIndex << ", i = " << i << ", k = " << k << ")." 
	    << std::endl;
	// <---- DEBUG ----- */
	return CHILD_INDEX_INVALID;
}

int Node::getImplChildOrderIndex(Ionflux::VolGfx::NodeImpl* otherImpl, 
const Ionflux::VolGfx::Context* context, int index)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplChildOrderIndex", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::getImplChildOrderIndex", "Context");
	int numChildNodes = getImplNumChildNodes(otherImpl);
	if (index >= numChildNodes)
	{
	    std::ostringstream status;
	    status << "[Node::getImplChildOrderIndex] "
	        "Child node index out of range: " << index;
	    throw IFVGError(status.str());
	}
	// Find the bit index of the child with the specified index.
	int i = 0;
	int n0 = context->getMaxNumLeafChildNodesPerNode();
	int validCount = 0;
	while ((validCount < index) 
	    && (i < n0))
	{
	    if (otherImpl->valid.test(i))
	        validCount++;
	    i++;
	}
	if ((validCount - 1) == index)
	    return i - 1;
	return CHILD_INDEX_INVALID;
}

int Node::getImplChildOrderIndex(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::NodeImpl* childImpl)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplChildOrderIndex", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(childImpl, 
	    "Node::getImplChildOrderIndex", "Child node implementation");
	if (isImplLeaf(otherImpl))
	    return CHILD_INDEX_INVALID;
	int numChildNodes = getImplNumChildNodes(otherImpl);
	// Find the bit index of the matching child node implementation.
	int i = 0;
	int validCount = 0;
	NodeImpl* cp = otherImpl->child;
	bool found = false;
	while ((validCount < numChildNodes) 
	    && !found)
	{
	    if (otherImpl->valid.test(i))
	    {
	        NodeImpl* ci = &(cp[validCount]);
	        if (ci == childImpl)
	            found = true;
	        validCount++;
	    }
	    i++;
	}
	if (found)
	    return i - 1;
	return CHILD_INDEX_INVALID;
}

Ionflux::VolGfx::NodeImpl* 
Node::getImplChildByOrderIndex(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, int orderIndex, bool autoCreate, bool 
fill0)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplChildByOrderIndex", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::getImplChildByOrderIndex", "Context");
	int n0 = context->getMaxNumLeafChildNodesPerNode();
	if (orderIndex >= n0)
	{
	    std::ostringstream status;
	    status << "[Node::getImplChildByOrderIndex] "
	        "Child node index out of range: " << orderIndex;
	    throw IFVGError(status.str());
	}
	int vi = getImplChildValidIndex(otherImpl, context, orderIndex);
	if (vi == CHILD_INDEX_INVALID)
	{
	    if (autoCreate)
	    {
	        // Create a new child node.
	        /* <---- DEBUG ----- //
	        std::cout << "[Node::getImplChildByOrderIndex] DEBUG: ["
	            << getImplValueString(otherImpl, context) << "] "
	            "Child node does not exist for order index (" 
	            << orderIndex << "), creating new node." << std::endl;
	        // <---- DEBUG ----- */
	        NodeImplVector newImpl;
	        NodeImpl* createdImpl = 0;
	        for (int i = 0; i < n0; i++)
	        {
	            if (i == orderIndex)
	            {
	                /* Create a new node implementation for this 
	                   order index. */
	                createdImpl = createImpl();
	                refImpl(createdImpl);
	                createdImpl->parent = otherImpl;
	                newImpl.push_back(createdImpl);
	            } else
	            {
	                // Add invalid node.
	                newImpl.push_back(0);
	            }
	        }
	        mergeImplChildNodes(otherImpl, context, newImpl, fill0);
	        if (createdImpl != 0)
	            unrefImpl(createdImpl);
	        vi = getImplChildValidIndex(otherImpl, context, orderIndex);
	    } else
	    {
	        // Node is invalid and should not be created.
	        /* <---- DEBUG ----- //
	        unsigned int d0 = getImplDepth(otherImpl, context);
	        Ionflux::GeoUtils::Vector3 lv0;
	        context->getVoxelLocation(otherImpl->loc, d0, lv0);
	        std::cout << "[Node::getImplChildByOrderIndex] DEBUG: "
	            "node: [" << d0 << ", (" << lv0.getValueString() << ")] "
	            "Child node does not exist for order index " 
	            << orderIndex << ")." << std::endl;
	        // <---- DEBUG ----- */
	        return 0;
	    }
	}
	NodeImpl* cn = getImplChildByValidIndex(otherImpl, vi);
	if (cn == 0)
	{
	    std::ostringstream status;
	    unsigned int d0 = getImplDepth(otherImpl, context);
	    Ionflux::GeoUtils::Vector3 lv0;
	    context->getVoxelLocation(otherImpl->loc, d0, lv0);
	    status << "[Node::getImplChildByOrderIndex] "
	        << "Child with valid index #" << vi 
	        << " is null [this.loc = (" 
	        << lv0.getValueString() << "), this.depth = " 
	        << d0 << "].";
	    throw IFVGError(status.str());
	}
	return cn;
}

int Node::getImplNumChildNodes(Ionflux::VolGfx::NodeImpl* otherImpl)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplNumChildNodes", "Node implementation");
	return otherImpl->valid.count();
}

Ionflux::VolGfx::NodeImpl* 
Node::getImplChildByValidIndex(Ionflux::VolGfx::NodeImpl* otherImpl, int 
index)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "getImplChildByValidIndex", "Node implementation");
	NodeImpl* cp = otherImpl->child;
	Ionflux::ObjectBase::nullPointerCheck(cp, 
	    "getImplChildByValidIndex", "Node child pointer");
	int numChildNodes = getImplNumChildNodes(otherImpl);
	if ((index < 0) || (index > numChildNodes))
	{
	    std::ostringstream status;
	    status << "[Node::getImplChildByValidIndex] "
	        "Child node index out of range: " << index;
	    throw IFVGError(status.str());
	}
	return &(cp[index]);
}

Ionflux::VolGfx::NodeImpl* Node::locateImplChild(Ionflux::VolGfx::NodeImpl*
otherImpl, Ionflux::VolGfx::Context* context, const 
Ionflux::VolGfx::NodeLoc3& loc, int maxDepth)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::locateImplChild", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::locateImplChild", "Context");
	LocInt maxNumLevels = context->getMaxNumLevels();
	LocInt depth = getImplDepth(otherImpl, context);
	if ((maxDepth < 0) 
	    || (maxDepth >= maxNumLevels))
	    maxDepth = maxNumLevels - 1;
	/* <---- DEBUG ----- //
	std::cout << "[Node::locateImplChild] DEBUG: ["
	    << getImplValueString(otherImpl, context) << "] loc = " 
	    << getLocString(loc) << ", maxDepth = " << maxDepth 
	    << std::endl;
	// <---- DEBUG ----- */
	if (depth > maxDepth)
	{
	    // Current node is below the maximum depth.
	    /* <---- DEBUG ----- //
	    std::cout << "[Node::locateImplChild] DEBUG: "
	        << "Current node is below maximum depth." << std::endl;
	    // <---- DEBUG ----- */
	    return 0;
	}
	// Check location code of the current node.
	if (!context->locEqual(loc, otherImpl->loc, depth))
	{
	    // Location is outside the bounds of this node.
	    /* <---- DEBUG ----- //
	    std::cout << "[Node::locateImplChild] DEBUG: "
	        << "Location is outside the bounds of this node (loc = " 
	        << getLocString(loc) << ")." << std::endl;
	    // <---- DEBUG ----- */
	    return 0;
	}
	if (isImplLeaf(otherImpl) || (depth == maxDepth))
	{
	    /* The current node is the closest leaf node to the 
	       specified location. */
	    /* <---- DEBUG ----- //
	    std::cout << "[Node::locateImplChild] DEBUG: "
	        << "Current node is the closest leaf node to loc = " 
	        << getLocString(loc) << "." << std::endl;
	    // <---- DEBUG ----- */
	    return otherImpl;
	}
	NodeImpl* ci0 = otherImpl;
	NodeImpl* ci1 = 0;
	bool found = false;
	while (!found)
	{
	    if (depth >= (maxNumLevels - 1))
	    {
	        // This node should be a leaf node.
	        std::ostringstream status;
	        status << "[Node::locateImplChild] "
	            "Depth above maximum (maxNumLevels = " << maxNumLevels 
	            << ", depth = " << (depth + 1) << ").";
	        throw IFVGError(status.str());
	    }
	    int oi = context->getChildOrderIndex(loc, depth + 1);
	    if (oi < 0)
	    {
	        std::ostringstream status;
	        status << "[Node::locateImplChild] "
	            "Invalid child order index (maxNumLevels = " 
	            << maxNumLevels << ", depth = " << (depth + 1) 
	            << ", loc = " << getLocString(loc) << ").";
	        throw IFVGError(status.str());
	    }
	    if (ci0->valid.test(oi))
	    {
	        ci1 = ci0;
	        ci0 = getImplChildByOrderIndex(ci0, context, oi);
	        if (ci0 == 0)
	        {
	            std::ostringstream status;
	            unsigned int d0 = getImplDepth(ci1, context);
	            Ionflux::GeoUtils::Vector3 lv0;
	            context->getVoxelLocation(ci1->loc, d0, lv0);
	            Ionflux::GeoUtils::Vector3 lv1;
	            context->getLocation(loc, lv1);
	            status << "[Node::locateImplChild] "
	                << "Child with valid order index #" << oi 
	                << " does not exist [this.loc = (" 
	                << lv0.getValueString() << "), this.depth = " << d0 
	                << ", target.loc = (" << lv1.getValueString() 
	                << "), target.depth = " << maxDepth << "].";
	            throw IFVGError(status.str());
	        }
	        if (otherImpl->leaf.test(oi))
	        {
	            // Child node is a leaf node.
	            /* <---- DEBUG ----- //
	            std::cout << "[Node::locateImplChild] DEBUG: "
	                << "Matching leaf child node with order index: " 
	                << oi << "." << std::endl;
	            // <---- DEBUG ----- */
	            found = true;
	        } else
	        {
	            // Continue with child node.
	            depth++;
	            if (depth == maxDepth)
	            {
	                // Child note is at the specified depth.
	                /* <---- DEBUG ----- //
	                std::cout << "[Node::locateImplChild] DEBUG: "
	                    << "Matching child node with order index (" 
	                    << oi << ") at target depth (" << maxDepth 
	                    << ")." << std::endl;
	                // <---- DEBUG ----- */
	                found = true;
	            }
	        }
	    } else
	    {
	        /* If the child specified by the location code is not valid, 
	           the current node is the closest node to the specified 
	           location. */
	        /* <---- DEBUG ----- //
	        std::cout << "[Node::locateImplChild] DEBUG: "
	            << "Matching child node does not exist (orderIndex = " 
	            << oi << ")." << std::endl;
	        // <---- DEBUG ----- */
	        found = true;
	    }
	}
	return ci0;
}

Ionflux::VolGfx::NodeImpl* Node::locateImplChild(Ionflux::VolGfx::NodeImpl*
otherImpl, Ionflux::VolGfx::Context* context, const 
Ionflux::GeoUtils::Vector3& p, int maxDepth)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::locateImplChild", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::locateImplChild", "Context");
	// <---- DEBUG ----- //
	if (!context->checkLoc(p))
	{
	    std::ostringstream status;
	    status << "Location out of bounds (v = (" << p.getValueString() 
	        << "))";
	    throw IFVGError(Ionflux::ObjectBase::getErrorString(
	        status.str(), "Node::locateImplChild"));
	}
	// <---- DEBUG ----- */
	NodeLoc3 loc = context->createLoc(p);
	return locateImplChild(otherImpl, context, loc, maxDepth);
}

Ionflux::VolGfx::NodeImpl* Node::insertImplChild(Ionflux::VolGfx::NodeImpl*
otherImpl, Ionflux::VolGfx::Context* context, const 
Ionflux::VolGfx::NodeLoc3& loc, int depth, bool fill0, bool 
fillTargetDepth0)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::insertImplChild", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::insertImplChild", "Context");
	LocInt maxNumLevels = context->getMaxNumLevels();
	if (depth < 0)
	    depth = maxNumLevels - 1;
	/* <---- DEBUG ----- //
	std::cout << "[Node::insertImplChild] DEBUG: ["
	    << getImplValueString(otherImpl, context) << "] loc = " 
	    << getLocString(loc) << ", depth = " << depth 
	    << std::endl;
	// <---- DEBUG ----- */
	if (depth > (maxNumLevels - 1))
	{
	    std::ostringstream status;
	    status << "[Node::insertImplChild] "
	        "Depth above maximum (maxNumLevels = " << maxNumLevels 
	        << ", depth = " << depth << ")";
	    throw IFVGError(status.str());
	}
	// Locate the node that is closest to the specified location.
	NodeImpl* ci = locateImplChild(otherImpl, context, loc, depth);
	if (ci == 0)
	{
	    // Location is outside the bounds of this node.
	    // <---- DEBUG ----- //
	    unsigned int d0 = getImplDepth(otherImpl, context);
	    Ionflux::GeoUtils::Vector3 lv0;
	    context->getVoxelLocation(otherImpl->loc, d0, lv0);
	    Ionflux::GeoUtils::Vector3 lv1;
	    context->getLocation(loc, lv1);
	    std::cout << "[Node::insertImplChild] DEBUG: "
	        << "Location is outside the bounds of this node "
	        "[this.loc = (" << lv0.getValueString() << "), this.depth = " 
	        << d0 << ", target.loc = (" << lv1.getValueString() 
	        << "), target.depth = " << depth << "]." << std::endl;
	    // <---- DEBUG ----- */
	    return 0;
	}
	int cd = getImplDepth(ci, context);
	if (cd == depth)
	{
	    // Node has the specified depth.
	    /* <---- DEBUG ----- //
	    std::cout << "[Node::insertImplChild] DEBUG: "
	        << "Returning existing node (depth = " << depth 
	        << ", loc = " << getLocString(loc) << ")." 
	        << std::endl;
	    // <---- DEBUG ----- */
	    return ci;
	}
	/* <---- DEBUG ----- //
	std::cout << "[Node::insertImplChild] DEBUG: "
	    << "Closest leaf node [" 
	    << getImplValueString(otherImpl, context) << "] loc = " 
	    << getLocString(loc) << ", depth = " << depth 
	    << std::endl;
	// <---- DEBUG ----- */
	// Add nodes until specified depth is reached.
	while (cd < depth)
	{
	    if (cd > (maxNumLevels - 1))
	    {
	        std::ostringstream status;
	        status << "[Node::insertImplChild] "
	            "Depth above maximum (maxNumLevels = " 
	            << maxNumLevels << ", depth = " << (cd + 1) 
	            << ").";
	        throw IFVGError(status.str());
	    }
	    int oi = context->getChildOrderIndex(loc, cd + 1);
	    bool fill1 = fill0;
	    if (!fill0 && (cd == (depth - 1)))
	        fill1 = fillTargetDepth0;
	    /* <---- DEBUG ----- //
	    std::cout << "[Node::insertImplChild] DEBUG: "
	        << "Inserting node (depth = " << (cd + 1) 
	        << ", loc = " << getLocString(loc) << ", orderIndex = " 
	        << oi << ")." << std::endl;
	    // <---- DEBUG ----- */
	    ci = getImplChildByOrderIndex(ci, context, oi, true, fill1);
	    if (ci == 0)
	    {
	        Ionflux::GeoUtils::Vector3 lv0;
	        context->getLocation(loc, lv0);
	        std::ostringstream status;
	        status << "[Node::insertImplChild] "
	            "Could not create child node [loc = (" 
	            << lv0.getValueString() << "), depth = " << depth 
	            << ", orderIndex = " << oi << "].";
	        throw IFVGError(status.str());
	    }
	    cd++;
	}
	return ci;
}

Ionflux::VolGfx::NodeImpl* Node::insertImplChild(Ionflux::VolGfx::NodeImpl*
otherImpl, Ionflux::VolGfx::Context* context, const 
Ionflux::GeoUtils::Vector3& p, int depth, bool fill0, bool 
fillTargetDepth0)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::insertImplChild", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::insertImplChild", "Context");
	// <---- DEBUG ----- //
	if (!context->checkLoc(p))
	{
	    std::ostringstream status;
	    status << "Location out of bounds (v = (" << p.getValueString() 
	        << "))";
	    throw IFVGError(Ionflux::ObjectBase::getErrorString(
	        status.str(), "Node::insertImplChild"));
	}
	// <---- DEBUG ----- */
	NodeLoc3 loc = context->createLoc(p);
	return insertImplChild(otherImpl, context, loc, depth, fill0, 
    fillTargetDepth0);
}

Ionflux::VolGfx::NodeImpl* Node::insertImplChild(Ionflux::VolGfx::NodeImpl*
otherImpl, Ionflux::VolGfx::Context* context, const 
Ionflux::VolGfx::NodeID& nodeID, bool fill0, bool fillTargetDepth0)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::insertImplChild", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::insertImplChild", "Context");
	return insertImplChild(otherImpl, context, nodeID.loc, nodeID.depth, fill0, 
    fillTargetDepth0);;
}

void Node::mergeImplChildNodes(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, const Ionflux::VolGfx::NodeImplVector& 
newNodes, bool fill0)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::mergeImplChildNodes", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::mergeImplChildNodes", "Context");
	int n0 = context->getMaxNumLeafChildNodesPerNode();
	if (newNodes.size() < static_cast<unsigned int>(n0))
	{
	    std::ostringstream status;
	    status << "[Node::mergeImplChildNodes] "
	        "Unexpected number of nodes in vector (expected: " 
	        << n0 << ", got: " << newNodes.size() << ")";
	    throw IFVGError(status.str());
	}
	NodeImplVector newNodes0 = newNodes;
	int numValid = 0;
	NodeImpl* cp0 = 0;
	if (!isImplLeaf(otherImpl))
	{
	    cp0 = Ionflux::ObjectBase::nullPointerCheck(
	        otherImpl->child, "Node::mergeImplChildNodes", 
	            "Child node pointer");
	}
	// Scan for valid nodes.
	NodeChildMask newLeaf = otherImpl->leaf;
	NodeChildMask newValid = otherImpl->valid;
	NodeImplVector createdImpl;
	for (int i = 0; i < n0; i++)
	{
	    NodeImpl* ci = newNodes0[i];
	    if (ci != 0)
	    {
	        // Use the new node implementation.
	        newValid.set(i, true);
	        if (!ci->valid.any())
	            newLeaf.set(i, true);
	        else
	            newLeaf.set(i, false);
	        numValid++;
	    } else 
	    if (otherImpl->valid.test(i))
	    {
	        // Use existing node implementation.
	        numValid++;
	    } else
	    if (fill0)
	    {
	        // Create missing nodes.
	        newValid.set(i, true);
	        newLeaf.set(i, true);
	        ci = createImpl();
	        refImpl(ci);
	        ci->parent = otherImpl;
	        createdImpl.push_back(ci);
	        newNodes0[i] = ci;
	        numValid++;
	    }
	}
	// Copy node implementations.
	NodeImpl* cp1 = new NodeImpl[numValid];
	if (cp1 == 0)
	{
	    throw IFVGError("Node::mergeImplChildNodes"
	        "Could not allocate child node implementations.");
	}
	int k = 0;
	int l = 0;
	for (int i = 0; i < n0; i++)
	{
	    NodeImpl* ci = newNodes0[i];
	    if (ci != 0)
	    {
	        // Create new child node implementation.
	        copyImpl(*ci, cp1[k], true);
	        cp1[k].refCount = 0;
	        cp1[k].parent = otherImpl;
	        cp1[k].loc = getImplChildLoc(otherImpl, context, i);
	        setImplParent(&(cp1[k]));
	        // This reference will be cleared by clearImpl().
	        refImpl(&(cp1[k]));
	        k++;
	    } else
	    if (otherImpl->valid.test(i))
	    {
	        // Copy existing child node implementation.
	        copyImpl(cp0[l], cp1[k], true);
	        cp1[k].refCount = 0;
	        cp1[k].parent = otherImpl;
	        cp1[k].loc = getImplChildLoc(otherImpl, context, i);
	        setImplParent(&(cp1[k]));
	        // This reference will be cleared by clearImpl().
	        refImpl(&(cp1[k]));
	        l++;
	        k++;
	    }
	}
	/* NOTE: Data for any nodes that should be kept has already been taken 
	         over, so clearing all old child nodes here should be safe. */
	clearImpl(otherImpl, true, false, true);
	otherImpl->child = cp1;
	otherImpl->valid = newValid;
	otherImpl->leaf = newLeaf;
	NodeImpl* pi = otherImpl->parent;
	if (pi != 0)
	    updateImpl(pi, context);
	// clean up references to temporary nodes
	for (NodeImplVector::iterator i = createdImpl.begin(); 
	    i != createdImpl.end(); i++)
	    unrefImpl(*i);
}

void Node::setImplChildByOrderIndex(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, Ionflux::VolGfx::NodeImpl* newNode, int 
orderIndex)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::setImplChildByOrderIndex", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::setImplChildByOrderIndex", "Context");
	int n0 = context->getMaxNumLeafChildNodesPerNode();
	if (orderIndex >= n0)
	{
	    std::ostringstream status;
	    status << "[Node::setImplChildNodeByOrderIndex] "
	        "Child node index out of range: " << orderIndex;
	    throw IFVGError(status.str());
	}
	NodeImplVector niv;
	for (int i = 0; i < n0; i++)
	{
	    if (i == orderIndex)
	    {
	        refImpl(newNode);
	        niv.push_back(newNode);
	    } else
	        niv.push_back(0);
	}
	mergeImplChildNodes(otherImpl, context, niv);
	// Unreference temporary nodes.
	for (int i = 0; i < n0; i++)
	{
	    NodeImpl* ci = niv[i];
	    if (ci != 0)
	        unrefImpl(ci);
	}
}

void Node::setImplChildByValidIndex(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::NodeImpl* newImpl, int index)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::setImplChildByValidIndex", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(newImpl, 
	    "Node::setImplChildByValidIndex", "Node implementation (child)");
	int numChildNodes = getImplNumChildNodes(otherImpl);
	if (index >= numChildNodes)
	{
	    std::ostringstream status;
	    status << "[Node::setImplChildByValidIndex]" 
	        "Child node index out of range: " << index;
	    throw IFVGError(status.str());
	}
	NodeImpl* cp = otherImpl->child;
	Ionflux::ObjectBase::nullPointerCheck(cp, 
	    "Node::setImplChildByValidIndex", "Child node pointer");
	NodeImpl& ci = cp[index];
	Ionflux::ObjectBase::UInt16 rc0 = ci.refCount;
	NodeLoc3 loc0 = ci.loc;
	if (rc0 != 0)
	{
	    std::ostringstream status;
	    status << "[Node::setImplChildByValidIndex] "
	        "Child node has zero references (index = " << index 
	        << ").";
	    throw IFVGError(status.str());
	}
	if (rc0 > 1)
	{
	    std::ostringstream status;
	    status << "[Node::setImplChildByValidIndex] "
	        "Cannot replace child node with external references "
	        "(index = " << index << ", refCount = " << rc0 << ").";
	    throw IFVGError(status.str());
	}
	clearImpl(&ci, true, true, true);
	copyImpl(*newImpl, ci, true);
	/* Since the pointer to the child that is being replaced stays the 
	   same, the reference count can also be taken over. */
	ci.refCount = rc0;
	ci.parent = otherImpl;
	ci.loc = loc0;
	setImplParent(&ci);
}

void Node::setImplChildNodes(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, const Ionflux::VolGfx::NodeImplVector& 
newNodes)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::setImplChildNodes", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::setImplChildNodes", "Context");
	int n0 = context->getMaxNumLeafChildNodesPerNode();
	if (newNodes.size() < static_cast<unsigned int>(n0))
	{
	    std::ostringstream status;
	    status << "[Node::setImplChildNodes] "
	        "Unexpected number of nodes in vector (expected: " 
	        << n0 << ", got: " << newNodes.size() << ")";
	    throw IFVGError(status.str());
	}
	int numValid = 0;
	otherImpl->valid = 0;
	otherImpl->leaf = 0;
	// Scan for valid nodes.
	for (int i = 0; i < n0; i++)
	{
	    NodeImpl* ci = newNodes[i];
	    if (ci != 0)
	    {
	        otherImpl->valid.set(i, true);
	        if (!ci->valid.any())
	            otherImpl->leaf.set(i, true);
	        numValid++;
	    }
	}
	// Copy node implementations.
	NodeImpl* cp = new NodeImpl[numValid];
	if (cp == 0)
	{
	    throw IFVGError("Node::setImplChildNodes"
	        "Could not allocate child node implementations.");
	}
	int k = 0;
	for (int i = 0; i < n0; i++)
	{
	    NodeImpl* ci = newNodes[i];
	    if (ci != 0)
	    {
	        copyImpl(*ci, cp[k], true);
	        cp[k].refCount = 0;
	        cp[k].parent = otherImpl;
	        cp[k].loc = getImplChildLoc(otherImpl, context, i);
	        setImplParent(&(cp[k]));
	        // This reference will be cleared by clearImpl().
	        refImpl(&(cp[k]));
	        k++;
	    }
	}
	clearImpl(otherImpl, true, false, true);
	otherImpl->child = cp;
	NodeImpl* pi = otherImpl->parent;
	if (pi != 0)
	    updateImpl(pi, context);
}

void Node::clearImplChildNodes(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, const Ionflux::VolGfx::NodeChildMask& 
clearNodes)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::clearImplChildNodes", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::clearImplChildNodes", "Context");
	int n0 = context->getMaxNumLeafChildNodesPerNode();
	int numValid = 0;
	if (isImplLeaf(otherImpl))
	{
	    // This is a leaf node, nothing to be done.
	    return;
	}
	NodeImpl* cp0 = Ionflux::ObjectBase::nullPointerCheck(
	    otherImpl->child, "Node::clearImplChildNodes", 
	    "Child node pointer");
	// Scan for valid nodes.
	NodeChildMask newLeaf = otherImpl->leaf;
	NodeChildMask newValid = otherImpl->valid;
	for (int i = 0; i < n0; i++)
	{
	    if (otherImpl->valid.test(i))
	    {
	        if (!clearNodes.test(i)) 
	        {
	            // keep this node.
	            numValid++;
	        } else
	        {
	            // node will be cleared
	            newValid.set(i, false);
	            newLeaf.set(i, false);
	        }
	    }
	}
	// Copy node implementations.
	NodeImpl* cp1 = new NodeImpl[numValid];
	if (cp1 == 0)
	{
	    throw IFVGError("Node::clearImplChildNodes"
	        "Could not allocate child node implementations.");
	}
	int k = 0;
	int l = 0;
	for (int i = 0; i < n0; i++)
	{
	    if (otherImpl->valid.test(i))
	    {
	        if (!clearNodes.test(i))
	        {
	            // Copy existing child node implementation.
	            copyImpl(cp0[l], cp1[k], true);
	            cp1[k].refCount = 0;
	            cp1[k].parent = otherImpl;
	            cp1[k].loc = getImplChildLoc(otherImpl, context, i);
	            setImplParent(&(cp1[k]));
	            // This reference will be cleared by clearImpl().
	            refImpl(&(cp1[k]));
	            k++;
	        }
	        l++;
	    }
	}
	/* NOTE: Data for any nodes that should be kept has already been taken 
	         over, so clearing all old child nodes here should be safe. */
	clearImpl(otherImpl, true, false, true);
	otherImpl->child = cp1;
	otherImpl->valid = newValid;
	otherImpl->leaf = newLeaf;
	NodeImpl* pi = otherImpl->parent;
	if (pi != 0)
	    updateImpl(pi, context);
}

unsigned int Node::pruneEmptyImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, bool recursive)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::pruneEmptyImpl", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::pruneEmptyImpl", "Context");
	int n0 = context->getMaxNumLeafChildNodesPerNode();
	NodeChildMask cm0 = 0;
	unsigned int numPruned = 0;
	for (int i = 0; i < n0; i++)
	{
	    if (otherImpl->valid.test(i))
	    {
	        NodeImpl* cn = Ionflux::ObjectBase::nullPointerCheck(
	            getImplChildByOrderIndex(otherImpl, context, i, false), 
	                "Node::pruneEmptyImpl", "Child node implementation");
	        if (recursive)
	            numPruned += pruneEmptyImpl(cn, context, true);
	        if (otherImpl->leaf.test(i))
	        {
	            if ((cn->data == 0) 
	                || (cn->data->type == DATA_TYPE_NULL))
	            {
	                cm0.set(i, true);
	                numPruned++;
	            }
	        }
	    }
	}
	if (cm0.any())
	    clearImplChildNodes(otherImpl, context, cm0);
	return numPruned;
}

int Node::fillImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, bool clearExisting, bool recursive, int 
maxDepth)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::fillImpl", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::fillImpl", "Context");
	LocInt maxNumLevels = context->getMaxNumLevels();
	int n0 = context->getMaxNumLeafChildNodesPerNode();
	LocInt depth = getImplDepth(otherImpl, context);
	if ((maxDepth < 0) 
	    || (maxDepth >= maxNumLevels))
	    maxDepth = maxNumLevels - 1;
	/* <---- DEBUG ----- //
	if (depth == 2)
	{
	    std::cout << "[Node::fillImpl] DEBUG: ["
	        << getImplValueString(otherImpl, context) << "] depth = " 
	        << depth << ", maxDepth = " << maxDepth << std::endl;
	}
	// <---- DEBUG ----- */
	if (depth >= maxDepth)
	{
	    // Current node is at the maximum depth.
	    /* <---- DEBUG ----- //
	    std::cout << "[Node::fillImpl] DEBUG: "
	        << "Current node is at maximum depth." << std::endl;
	    // <---- DEBUG ----- */
	    return 0;
	}
	if (clearExisting)
	{
	    /* <---- DEBUG ----- //
	    std::cout << "[Node::fillImpl] DEBUG: "
	        << "Clearing data." << std::endl;
	    // <---- DEBUG ----- */
	    clearImpl(otherImpl, true, false, true);
	}
	// Add new child nodes.
	int nodesCreated = 0;
	NodeImplVector niv;
	for (int i = 0; i < n0; i++)
	{
	    if (!otherImpl->valid.test(i))
	    {
	        /* <---- DEBUG ----- //
	        if (depth == 2)
	        {
	            std::cout << "[Node::fillImpl] DEBUG: "
	                << "Creating node #" << std::setw(3) 
	                << std::setfill('0') << i << "." << std::endl;
	        }
	        // <---- DEBUG ----- */
	        NodeImpl* ci = createImpl();
	        refImpl(ci);
	        niv.push_back(ci);
	        nodesCreated++;
	    } else
	        niv.push_back(0);
	}
	mergeImplChildNodes(otherImpl, context, niv);
	// Unreference temporary nodes.
	for (int i = 0; i < n0; i++)
	{
	    NodeImpl* ci = niv[i];
	    if (ci != 0)
	        unrefImpl(ci);
	}
	if ((recursive)
	    && (depth < maxDepth))
	{
	    // Recursively fill nodes.
	    /* <---- DEBUG ----- //
	    std::cout << "[Node::fillImpl] DEBUG: "
	        << "Recursively filling nodes." << std::endl;
	    // <---- DEBUG ----- */
	    for (int i = 0; i < n0; i++)
	    {
	        if (otherImpl->valid.test(i))
	        {
	            /* <---- DEBUG ----- //
	            std::cout << "[Node::fillImpl] DEBUG: "
	                << "Filling child node #" << std::setw(3) 
	                << std::setfill('0') << i << "." << std::endl;
	            // <---- DEBUG ----- */
	            NodeImpl* ci = getImplChildByOrderIndex(otherImpl, 
	                context, i, false);
	            Ionflux::ObjectBase::nullPointerCheck(ci, 
	                "Node::fillImpl", "Child node implementation");
	            int nc0 = fillImpl(ci, context, clearExisting, 
	                recursive, maxDepth);
	            nodesCreated += nc0;
	        }
	    }
	}
	return nodesCreated;
}

Ionflux::VolGfx::NodeImpl* 
Node::locateImplRegion(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, const Ionflux::VolGfx::Region3& region, 
int maxDepth)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::locateImplRegion", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::locateImplRegion", "Context");
	// <---- DEBUG ----- //
	std::cout << "[Node::locateImplRegion] DEBUG: ["
	    << getImplValueString(otherImpl, context) << "] region = " 
	    << getRegionString(region) << ", maxDepth = " << maxDepth 
	    << std::endl;
	// <---- DEBUG ----- */
	int l0 = context->getCommonAncestorLevel(region, maxDepth);
	// <---- DEBUG ----- //
	std::cout << "[Node::locateImplRegion] DEBUG: "
	    "target level = " << l0 << std::endl;
	// <---- DEBUG ----- */
	NodeImpl* ni = locateImplChild(otherImpl, context, region.l0, l0);
	// <---- DEBUG ----- //
	if (ni != 0)
	{
	    std::cout << "[Node::locateImplRegion] DEBUG: result node: ["
	        << getImplValueString(ni, context) << "]." << std::endl;
	} else
	{
	    std::cout << "[Node::locateImplRegion] DEBUG: "
	        "No suitable node was found." << std::endl;
	}
	// <---- DEBUG ----- */
	return ni;
}

Ionflux::VolGfx::NodeImpl* Node::locateImplNode(Ionflux::VolGfx::NodeImpl* 
otherImpl, Ionflux::VolGfx::Context* context, const 
Ionflux::VolGfx::NodeLoc3& loc, int maxDepth)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::locateImplNode", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::locateImplNode", "Context");
	LocInt maxNumLevels = context->getMaxNumLevels();
	LocInt depth = getImplDepth(otherImpl, context);
	if ((maxDepth < 0) 
	    || (maxDepth >= maxNumLevels))
	    maxDepth = maxNumLevels - 1;
	// <---- DEBUG ----- //
	std::cout << "[Node::locateImplNode] DEBUG: ["
	    << getImplValueString(otherImpl, context) << "] loc = " 
	    << getLocString(loc) << ", maxDepth = " << maxDepth 
	    << std::endl;
	// <---- DEBUG ----- */
	NodeImpl* ci = otherImpl;
	int d0 = context->getCommonAncestorLevel(ci->loc, loc, maxDepth);
	// <---- DEBUG ----- //
	std::cout << "[Node::locateImplNode] DEBUG: "
	    << "depth of common ancestor = " << d0 << std::endl;
	// <---- DEBUG ----- */
	while ((d0 < depth) 
	    && (ci->parent != 0))
	{
	    ci = ci->parent;
	    depth--;
	}
	return locateImplChild(ci, context, loc, maxDepth);;
}

Ionflux::VolGfx::NodeLoc3 Node::getImplChildLoc(Ionflux::VolGfx::NodeImpl* 
otherImpl, Ionflux::VolGfx::Context* context, int orderIndex)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplChildLoc", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::getImplChildLoc", "Context");
	if (context->getOrder() != 2)
	{
	    throw IFVGError("[Node::getImplChildLoc] "
	        "Location codes not supported for tree order != 2.");
	}
	int n0 = context->getMaxNumLeafChildNodesPerNode();
	if (orderIndex >= n0)
	{
	    std::ostringstream status;
	    status << "[Node::getImplChildLoc] "
	        "Child node index out of range: " << orderIndex;
	    throw IFVGError(status.str());
	}
	LocInt maxNumLevels = context->getMaxNumLevels();
	LocInt depth = getImplDepth(otherImpl, context);
	if (depth >= (maxNumLevels - 1))
	{
	    // This node should be a leaf node.
	    std::ostringstream status;
	    status << "[Node::getImplChildLoc] "
	        "Depth above maximum (maxNumLevels = " << maxNumLevels 
	        << ", depth = " << (depth + 1) << ").";
	    throw IFVGError(status.str());
	}
	NodeLoc m0 = context->getLocMask(depth);
	NodeLoc3 loc = otherImpl->loc;
	int n1 = maxNumLevels - depth - 2;
	loc.x = (loc.x & m0) | NodeLoc((orderIndex & 1) << n1);
	loc.y = (loc.y & m0) | NodeLoc(((orderIndex & 2) >> 1) << n1);
	loc.z = (loc.z & m0) | NodeLoc(((orderIndex & 4) >> 2) << n1);
	return loc;
}

double Node::getImplVoxelSize(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplVoxelSize", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::getImplVoxelSize", "Context");
	int depth = getImplDepth(otherImpl, context);
	return context->getVoxelSize(depth);
}

Ionflux::VolGfx::LocInt 
Node::getImplVoxelSizeLoc(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplVoxelSizeLoc", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::getImplVoxelSizeLoc", "Context");
	int depth = getImplDepth(otherImpl, context);
	return context->getDepthMask(depth).to_ulong();
}

bool Node::getImplNeighborLoc(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, int offsetX, int offsetY, int offsetZ, 
Ionflux::VolGfx::NodeLoc3& target)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplNeighborLoc", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::getImplNeighborLoc", "Context");
	if (context->getOrder() != 2)
	{
	    throw IFVGError("[Node::getImplNeighborLoc] "
	        "Location codes not supported for tree order != 2.");
	}
	// <---- DEBUG ----- //
	std::cout << "[Node::getImplNeighborLoc] DEBUG: ["
	    << getImplValueString(otherImpl, context) << "] offset = (" 
	    << offsetX << ", " << offsetY << ", " << offsetZ << ")" 
	    << std::endl;
	// <---- DEBUG ----- */
	LocInt vs = getImplVoxelSizeLoc(otherImpl, context);
	// X
	int ox = offsetX;
	if (offsetX > 0)
	    ox = offsetX * vs;
	else
	if (offsetX < 0)
	    ox = -(offsetX + 1) * vs - 1;
	// Y
	int oy = offsetY;
	if (offsetY > 0)
	    oy = offsetY * vs;
	else
	if (offsetY < 0)
	    oy = -(offsetY + 1) * vs - 1;
	// Z
	int oz = offsetZ;
	if (offsetZ > 0)
	    oz = offsetZ * vs;
	else
	if (offsetZ < 0)
	    oz = -(offsetZ + 1) * vs - 1;
	if (!context->checkLoc(otherImpl->loc, ox, oy, oz))
	    return false;
	target.x = otherImpl->loc.x.to_ulong() + ox;
	target.y = otherImpl->loc.y.to_ulong() + oy;
	target.z = otherImpl->loc.z.to_ulong() + oz;
	return true;
}

Ionflux::GeoUtils::Vector3 Node::getImplLocation(Ionflux::VolGfx::NodeImpl*
otherImpl, Ionflux::VolGfx::Context* context)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplLocation", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::getImplLocation", "Context");
	int depth = getImplDepth(otherImpl, context);
	return context->getVoxelLocation0(otherImpl->loc, depth);;
}

void Node::getImplRange(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, Ionflux::GeoUtils::Range3& target)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplRange", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::getImplRange", "Context");
	int depth = getImplDepth(otherImpl, context);
	context->getVoxelRange(otherImpl->loc, depth, target);
}

unsigned int Node::findImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, Ionflux::VolGfx::NodeImplVector* target,
Ionflux::VolGfx::NodeFilter* filter, bool recursive)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::findImpl", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::findImpl", "Context");
	if (filter != 0)
	{
	    int maxDepth = filter->getMaxDepth();
	    int depth = getImplDepth(otherImpl, context);
	    if (!context->checkDepthRange(depth, 0, maxDepth))
	        return 0;
	}
	unsigned int numNodes = 0;
	if ((filter == 0) 
	    || NodeProcessor::checkFlags(
	        filter->process(otherImpl), NodeFilter::RESULT_PASS))
	{
	    // add this node implementation
	    if (target != 0)
	        target->push_back(otherImpl);
	    numNodes++;
	}
	if (!recursive)
	    return numNodes;
	// find nodes recursively
	int n0 = getImplNumChildNodes(otherImpl);
	for (int i = 0; i < n0; i++)
	{
	    NodeImpl* cn0 = Ionflux::ObjectBase::nullPointerCheck(
	        getImplChildByValidIndex(otherImpl, i), 
	        "Node::findImplByDepthRange", "Child node implementation");
	    numNodes += findImpl(cn0, context, target, filter, true);
	}
	return numNodes;
}

unsigned int Node::processImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, Ionflux::VolGfx::NodeProcessor* 
preProcessor, Ionflux::VolGfx::NodeFilter* filter, 
Ionflux::VolGfx::NodeProcessor* postProcessor, bool recursive)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::processImpl", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::processImpl", "Context");
	if (filter != 0)
	{
	    int maxDepth = filter->getMaxDepth();
	    int depth = getImplDepth(otherImpl, context);
	    if (!context->checkDepthRange(depth, 0, maxDepth))
	        return 0;
	}
	unsigned int numNodes = 0;
	NodeProcessingResultID result = NodeProcessor::RESULT_OK;
	bool process0 = false;
	if ((filter == 0) 
	    || NodeProcessor::checkFlags(
	        filter->process(otherImpl), NodeFilter::RESULT_PASS))
	{
	    // process this node (pre)
	    if (preProcessor != 0)
	        result = preProcessor->process(otherImpl);
	    numNodes++;
	    process0 = true;
	}
	if (!recursive 
	    || NodeProcessor::checkFlags(result, 
	        ChainableNodeProcessor::RESULT_FINISHED))
	    return numNodes;
	// process nodes recursively
	int n0 = getImplNumChildNodes(otherImpl);
	for (int i = 0; i < n0; i++)
	{
	    NodeImpl* cn0 = Ionflux::ObjectBase::nullPointerCheck(
	        getImplChildByValidIndex(otherImpl, i), 
	        "Node::processImpl", "Child node implementation");
	    numNodes += processImpl(cn0, context, preProcessor, filter, 
	        postProcessor, true);
	}
	if (process0)
	{
	    // process this node (post)
	    if (postProcessor != 0)
	        result = postProcessor->process(otherImpl);
	}
	return numNodes;
}

Ionflux::Altjira::Color* Node::getImplColor(Ionflux::VolGfx::NodeImpl* 
otherImpl, Ionflux::VolGfx::Context* context, Ionflux::Altjira::ColorSet* 
colors, unsigned int colorIndexOffset, unsigned int colorIndexRange, int 
colorIndex, int leafColorIndex, Ionflux::VolGfx::VoxelClassColorVector* 
voxelClassColors)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplColor", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::getImplColor", "Context");
	int ci0 = colorIndex;
	Ionflux::Altjira::Color* c0 = 0;
	if (ci0 < 0)
	{
	    // use node color index
	    ci0 = getImplColorIndex(otherImpl);
	    /* <---- DEBUG ----- //
	    if (ci0 >= 0)
	    {
	        NodeID nid0 = Node::getImplNodeID(otherImpl, context);
	        std::cerr << "[Node::getImplColor] DEBUG: "
	            "node: [" << getNodeIDValueString(nid0, false, true, true, 
	context) 
	            << "] colorIndex = " << ci0 << std::endl;
	    }
	    // ----- DEBUG ----> */
	}
	if (ci0 < 0)
	{
	    if ((voxelClassColors != 0) 
	        && (hasImplVoxelClassInfo(otherImpl)))
	    {
	        // use voxel class color
	        VoxelClassID vc = getImplVoxelClass(otherImpl);
	        c0 = getVoxelClassColor(*voxelClassColors, vc);
	    }
	}
	if ((c0 == 0) 
	    && (colors != 0))
	{
	    // select a color from the color set
	    unsigned int nc0 = colors->getNumColors();
	    if (colorIndexRange == 0)
	        colorIndexRange = nc0;
	    if (ci0 < 0)
	    {
	        bool leafFlag = isImplLeaf(otherImpl);
	        if (leafFlag 
	            && (leafColorIndex >= 0))
	        {
	            // use leaf color index
	            ci0 = leafColorIndex;
	        } else
	        {
	            // use color index based on depth
	            int d0 = getImplDepth(otherImpl, context);
	            unsigned int cMax = colorIndexOffset + colorIndexRange;
	            if (cMax > nc0)
	                colorIndexRange = nc0 - colorIndexOffset;
	            ci0 = (d0 % colorIndexRange) + colorIndexOffset;
	        }
	    }
	    if (nc0 > 0)
	    {
	        c0 = Ionflux::ObjectBase::nullPointerCheck(
	            colors->getColor(ci0 % nc0), 
	            "Node::getImplVertexAttributes", "Color");
	    }
	}
	return c0;
}

void Node::getImplMesh(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, Ionflux::GeoUtils::Mesh& target, double 
boxInset, Ionflux::Altjira::ColorSet* colors, unsigned int 
colorIndexOffset, unsigned int colorIndexRange, int colorIndex, int 
leafColorIndex, Ionflux::VolGfx::NodeFilter* filter, bool recursive)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplMesh", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::getImplMesh", "Context");
	NodeID nid0 = getImplNodeID(otherImpl, context);
	int ci0 = colorIndex;
	bool leafFlag = isImplLeaf(otherImpl);
	if ((leafColorIndex >= 0) && leafFlag)
	    ci0 = leafColorIndex;
	if (filter != 0)
	{
	    int maxDepth = filter->getMaxDepth();
	    int depth = getImplDepth(otherImpl, context);
	    if (!context->checkDepthRange(depth, 0, maxDepth))
	        return;
	}
	if ((filter == 0) 
	    || NodeProcessor::checkFlags(
	        filter->process(otherImpl), NodeFilter::RESULT_PASS))
	{
	    context->getVoxelMesh(nid0, target, boxInset, colors, 
	        colorIndexOffset, ci0);
	}
	if (!recursive)
	    return;
	int n0 = getImplNumChildNodes(otherImpl);
	for (int i = 0; i < n0; i++)
	{
	    NodeImpl* cn0 = Ionflux::ObjectBase::nullPointerCheck(
	        getImplChildByValidIndex(otherImpl, i), 
	        "Node::getImplMesh", "Child node implementation");
	    getImplMesh(cn0, context, target, boxInset, colors, 
	        colorIndexOffset, colorIndexRange, colorIndex, leafColorIndex, 
	        filter, true);
	}
}

void Node::getImplVertexAttributes(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, Ionflux::GeoUtils::VertexAttribute* 
positionTarget, Ionflux::GeoUtils::VertexAttribute* colorTarget, 
Ionflux::GeoUtils::VertexAttribute* normalTarget, 
Ionflux::GeoUtils::NFaceTypeID nFaceType, double boxInset, 
Ionflux::Altjira::ColorSet* colors, unsigned int colorIndexOffset, unsigned
int colorIndexRange, int colorIndex, int leafColorIndex, 
Ionflux::VolGfx::VoxelClassColorVector* voxelClassColors, 
Ionflux::GeoUtils::Vector* positionOffset, Ionflux::GeoUtils::Vector* 
positionScale, Ionflux::VolGfx::NodeFilter* filter, bool recursive, bool 
boundaryFacesOnly)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplVertexAttributes", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::getImplVertexAttributes", "Context");
	NodeID nid0 = getImplNodeID(otherImpl, context);
	if ((filter == 0) 
	    || NodeProcessor::checkFlags(
	        filter->process(otherImpl), NodeFilter::RESULT_PASS))
	{
	    // get vertex attributes for this node
	    Ionflux::Altjira::Color* c0 = getImplColor(otherImpl, context, 
	        colors, colorIndexOffset, colorIndexRange, colorIndex, 
	        leafColorIndex, voxelClassColors);
	    FaceMaskInt fm0 = FACE_ALL;
	    FaceMaskInt flipFM = FACE_UNDEFINED;
	    if (boundaryFacesOnly)
	    {
	        fm0 = getImplBoundaryFaces(otherImpl);
	        flipFM = fm0;
	    }
	    context->getVoxelVertexAttributes(nid0, positionTarget, 
	        colorTarget, normalTarget, nFaceType, boxInset, c0, 
	        positionOffset, positionScale, fm0, flipFM);
	}
	if (filter != 0)
	{
	    int maxDepth = filter->getMaxDepth();
	    if (!context->checkDepthRange(nid0.depth, 0, maxDepth))
	        return;
	}
	if (!recursive)
	    return;
	// process child nodes recursively
	int n0 = getImplNumChildNodes(otherImpl);
	for (int i = 0; i < n0; i++)
	{
	    NodeImpl* cn0 = Ionflux::ObjectBase::nullPointerCheck(
	        getImplChildByValidIndex(otherImpl, i), 
	        "Node::getImplVertexAttributes", 
	        "Child node implementation");
	    getImplVertexAttributes(cn0, context, positionTarget, 
	        colorTarget, normalTarget, nFaceType, boxInset, colors, 
	        colorIndexOffset, colorIndexRange, colorIndex, leafColorIndex, 
	        voxelClassColors, positionOffset, positionScale, filter, true, 
	        boundaryFacesOnly);
	}
}

unsigned int Node::getImplNumFaces(Ionflux::VolGfx::NodeImpl* otherImpl, 
bool recursive)
{
	unsigned int result = 0;
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplNumFaces", "Node implementation");
	NodeDataImpl* d0 = otherImpl->data;
	if ((d0 != 0) 
	    && (d0->type == DATA_TYPE_FACE_VEC))
	{
	    Ionflux::GeoUtils::FaceVector* fv0 = 
	        Ionflux::ObjectBase::nullPointerCheck(
	            static_cast<Ionflux::GeoUtils::FaceVector*>(d0->data));
	    result += fv0->size();
	}
	if (recursive)
	{
	    int n0 = getImplNumChildNodes(otherImpl);
	    for (int i = 0; i < n0; i++)
	    {
	        NodeImpl* cn0 = Ionflux::ObjectBase::nullPointerCheck(
	            getImplChildByValidIndex(otherImpl, i), 
	            "Node::getImplNumFaces", "Child node implementation");
	        result += getImplNumFaces(cn0, true);
	    }
	}
	return result;
}

double Node::getImplFaceColorNormal(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::Altjira::Color& targetColor, Ionflux::GeoUtils::Vector3& 
targetNormal, bool recursive)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::getImplFaceColorNormal", "Node implementation");
	NodeDataImpl* d0 = otherImpl->data;
	double at0 = 0.;
	double at1 = 0.;
	Ionflux::GeoUtils::Vector4 c0;
	Ionflux::GeoUtils::Vector3 n0;
	Ionflux::GeoUtils::Vector4 c1;
	Ionflux::GeoUtils::Vector3 n1;
	if ((d0 != 0) 
	    && (d0->type == DATA_TYPE_FACE_VEC))
	{
	    // process attached faces
	    Ionflux::GeoUtils::FaceVector* fv0 = 
	        Ionflux::ObjectBase::nullPointerCheck(
	            static_cast<Ionflux::GeoUtils::FaceVector*>(d0->data), 
	                "Node::getImplFaceColorNormal", "Face vector");
	    for (Ionflux::GeoUtils::FaceVector::iterator i = fv0->begin(); 
	        i != fv0->end(); i++)
	    {
	        Ionflux::GeoUtils::Face* cf0 = 
	            Ionflux::ObjectBase::nullPointerCheck(*i, 
	                "Node::getImplFaceColorNormal", "Face");
	        double a0 = cf0->getArea();
	        at0 += a0;
	        // vertex colors
	        Ionflux::GeoUtils::FaceData* vc0 = cf0->getVertexColors0();
	        if (vc0 != 0)
	        {
	            Ionflux::GeoUtils::Vector4* cc0 = 
	                Ionflux::GeoUtils::Vector4::upcast(vc0->getVector(0));
	            if (cc0 != 0)
	                c0.addIP((*cc0) * a0);
	        }
	        c0.multiplyIP(1. / at0);
	        // vertex normals
	        Ionflux::GeoUtils::FaceData* vn0 = cf0->getVertexNormals0();
	        if (vn0 != 0)
	        {
	            Ionflux::GeoUtils::Vector3* cn0 = 
	                Ionflux::GeoUtils::Vector3::upcast(vc0->getVector(0));
	            if (cn0 != 0)
	                n0.addIP((*cn0) * a0);
	        }
	        n0.multiplyIP(1. / at0);
	    }
	}
	if (recursive)
	{
	    // process child nodes
	    int n0 = getImplNumChildNodes(otherImpl);
	    for (int i = 0; i < n0; i++)
	    {
	        NodeImpl* cn0 = Ionflux::ObjectBase::nullPointerCheck(
	            getImplChildByValidIndex(otherImpl, i), 
	            "Node::getImplNumFaces", "Child node implementation");
	        Ionflux::Altjira::Color cc1;
	        Ionflux::GeoUtils::Vector3 cn1;
	        double ca0 = getImplFaceColorNormal(cn0, cc1, cn1);
	        at1 += ca0;
	        Ionflux::GeoUtils::Vector4 cc2;
	        Ionflux::GeoUtils::colorToVec(cc1, cc2);
	        c1.addIP(ca0 * cc2);
	        n1.addIP(ca0 * cn1);
	    }
	    c1.multiplyIP(1. / at1);
	    n1.multiplyIP(1. / at1);
	}
	// calculate total area-weighted color and normal
	double area0 = at0 + at1;
	Ionflux::GeoUtils::Vector4 c2;
	c2.addIP(at0 * c0 + at1 * c1);
	c2.multiplyIP(1. / area0);
	Ionflux::GeoUtils::vecToColor(c2, targetColor);
	targetNormal = (at0 * n0 + at1 * n1) / area0;
	return area0;
}

bool Node::voxelizeImplInsertFace(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, Ionflux::GeoUtils::Face* face, 
Ionflux::VolGfx::SeparabilityID sep, bool fill0)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::voxelizeInsertImplFace", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::voxelizeInsertImplFace", "Context");
	Ionflux::ObjectBase::nullPointerCheck(face, 
	    "Node::voxelizeInsertImplFace", "Face");
	int depth = getImplDepth(otherImpl, context);
	TriangleVoxelizationData tvd0;
	// NOTE: We need the triangle voxelization data for the leaf nodes here.
	context->initTriangleVoxelizationData(*face, tvd0, sep);
	/* <---- DEBUG ----- //
	std::cerr << "[Node::voxelizeInsertImplFace] DEBUG: "
	    "node: [" << getImplValueString(otherImpl, context) << "]; "
	    "face: [" << face->getValueString() << "], tvd: [" 
	    << getTriangleVoxelizationDataString(tvd0) << "]" 
	    << std::endl;
	// ----- DEBUG ----> */
	if ((tvd0.node.depth < depth) 
	    || (!context->locEqual(tvd0.node.loc, otherImpl->loc, depth)))
	{
	    // Node does not contain the voxelization.
	    return false;
	}
	NodeImpl* cn0 = 0;
	if (tvd0.node.depth > depth)
	{
	    // insert child node at target location and depth
	    cn0 = insertImplChild(otherImpl, context, tvd0.node, fill0);
	    if (cn0 == 0)
	    {
	        Ionflux::GeoUtils::Vector3 lv0;
	        context->getVoxelLocation(tvd0.node, lv0);
	        std::ostringstream status;
	        status << "[Node::voxelizeInsertImplFace] "
	            "Containing node implementation is null (node: [" 
	                << getImplValueString(otherImpl, context) << "]; "
	            << "target node: [" << tvd0.node.depth << ", (" 
	            << lv0.getValueString() << ")]; "
	            << "face: [" << face->getValueString() << "], tvd: [" 
	            << getTriangleVoxelizationDataString(tvd0) << "]";
	        throw IFVGError(status.str());
	    }
	} else
	{
	    // attach face to this node
	    /* <---- DEBUG ----- //
	    if (depth == 0)
	    {
	        std::cerr << "[Node::voxelizeInsertImplFace] DEBUG: "
	            "tvd = [" << getTriangleVoxelizationDataString(tvd0) << "]" 
	            << std::endl;
	    }
	    // ----- DEBUG ----> */
	    cn0 = otherImpl;
	}
	NodeDataImpl* d0 = cn0->data;
	if (d0 != 0)
	{
	    if (d0->type != DATA_TYPE_FACE_VEC)
	    {
	        std::ostringstream status;
	        status << "[Node::voxelizeInsertImplFace] " 
	            "Unexpected node data type: " 
	            << getDataTypeString(d0->type) << "(" << d0->type 
	            << ")";
	        throw IFVGError(status.str());
	    }
	} else
	{
	    d0 = createDataImpl(DATA_TYPE_FACE_VEC);
	    cn0->data = d0;
	}
	Ionflux::GeoUtils::FaceVector* fv0 = 
	    Ionflux::ObjectBase::nullPointerCheck(
	        static_cast<Ionflux::GeoUtils::FaceVector*>(d0->data), 
	        "Node::voxelizeInsertImplFace", "Face vector");
	fv0->push_back(face);
	/* <---- DEBUG ----- //
	std::cerr << "[Node::voxelizeInsertImplFace] DEBUG: "
	    "appending face to node: [" << getImplValueString(cn0, context) 
	    << "] (numFaces = " << fv0->size() << ")" << std::endl;
	// ----- DEBUG ----> */
	return true;
}

unsigned int Node::voxelizeImplInsertFaces(Ionflux::VolGfx::NodeImpl* 
otherImpl, Ionflux::VolGfx::Context* context, const 
Ionflux::GeoUtils::Mesh& mesh, Ionflux::VolGfx::SeparabilityID sep, bool 
fill0)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::voxelizeInsertImplFaces", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::voxelizeInsertImplFaces", "Context");
	unsigned int numFaces = mesh.getNumFaces();
	unsigned int nf0 = 0;
	for (unsigned int i = 0; i < numFaces; i++)
	{
	    Ionflux::GeoUtils::Face* f0 = mesh.getFace(i);
	    if (f0 != 0)
	    {
	        if (voxelizeImplInsertFace(otherImpl, context, f0, sep, fill0))
	            nf0++;
	    }
	}
	return nf0;
}

unsigned int Node::voxelizeImplFaces(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, Ionflux::VolGfx::NodeProcessor* 
processor, int targetDepth, Ionflux::VolGfx::SeparabilityID sep, bool 
fillTargetDepth, bool pruneEmpty0, Ionflux::GeoUtils::FaceVector* faces0)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::voxelizeImplFaces", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::voxelizeImplFaces", "Context");
	int maxNumLevels = context->getMaxNumLevels();
	if ((targetDepth < 0) 
	    || (targetDepth >= maxNumLevels))
	    targetDepth = maxNumLevels - 1;
	int depth = getImplDepth(otherImpl, context);
	// obtain set of faces for this node
	/* <---- DEBUG ----- //
	std::cerr << "[Node::voxelizeImplFaces] DEBUG: "
	    "node [" << getImplValueString(otherImpl, context, false) << "]: "
	    "Initializing faces..." << std::endl;
	// ----- DEBUG ----> */
	NodeDataImpl* d0 = otherImpl->data;
	Ionflux::GeoUtils::FaceVector fv0;
	if (faces0 != 0)
	{
	    // add faces passed in to the function
	    fv0.insert(fv0.end(), faces0->begin(), faces0->end());
	}
	if ((d0 != 0) 
	    && (d0->type == DATA_TYPE_FACE_VEC))
	{
	    // add faces attached to this node
	    Ionflux::GeoUtils::FaceVector* fv1 = 
	        Ionflux::ObjectBase::nullPointerCheck(
	            static_cast<Ionflux::GeoUtils::FaceVector*>(d0->data));
	    fv0.insert(fv0.end(), fv1->begin(), fv1->end());
	}
	// voxelize faces
	unsigned int numFaces = fv0.size();
	unsigned int numVoxels = 0;
	/* <---- DEBUG ----- //
	std::cerr << "[Node::voxelizeImplFaces] DEBUG: "
	    "node: [" << getImplValueString(otherImpl, context, false) << "], "
	    "numFaces = " << numFaces << std::endl;
	// ----- DEBUG ----> */
	if (depth == targetDepth)
	{
	    /* voxelize on this level.
	       If there is at least one face in the herarchy starting at this 
	       node or passed down to this node, we can set the voxelization 
	       data for this node, since all faces that were passed down have 
	       already been checked by the parent node and faces contained in 
	       child nodes are also contained in this node. */
	    unsigned int fc0 = getImplNumFaces(otherImpl, true);
	    unsigned int fc1 = numFaces + fc0;
	    if (fc1 > 0)
	    {
	        if (processor != 0)
	            processor->process(otherImpl);
	        numVoxels++;
	    }
	} else
	{
	    // process child nodes
	    /* <---- DEBUG ----- //
	    std::cerr << "[Node::voxelizeImplFaces] DEBUG: "
	        "processing child nodes (child node depth = " << (depth + 1) 
	        << ")" << std::endl;
	    // ----- DEBUG ----> */
	    bool fill0 = false;
	    bool checkBounds0 = false;
	    if ((depth + 1) == targetDepth)
	    {
	        fill0 = fillTargetDepth;
	        checkBounds0 = true;
	    }
	    // create triangle voxelization data
	    TriangleVoxelizationData* tvd0 = 
	        new TriangleVoxelizationData[numFaces];
	    if (tvd0 == 0)
	    {
	        throw IFVGError("[Node::voxelizeImplFaces] "
	            "Could not allocate triangle voxelization data.");
	    }
	    for (unsigned int k = 0; k < numFaces; k++)
	    {
	        Ionflux::GeoUtils::Face* cf = 
	            Ionflux::ObjectBase::nullPointerCheck(fv0[k], 
	                "Node::voxelizeImplFaces", "Face");
	        TriangleVoxelizationData& ctv = tvd0[k];
	        context->initTriangleVoxelizationData(*cf, ctv, sep, 
	            depth + 1, checkBounds0);
	        /* <---- DEBUG ----- //
	        std::cerr << "[Node::voxelizeImplFaces] DEBUG: "
	            "created triangle voxelization data:" << std::endl;
	        printTriangleVoxelizationDataDebugInfo(ctv);
	        // ----- DEBUG ----> */
	    }
	    // iterate over all child nodes by order index
	    unsigned int n0 = context->getMaxNumLeafChildNodesPerNode();
	    Ionflux::GeoUtils::Range3 r0;
	    for (unsigned int i = 0; i < n0; i++)
	    {
	        NodeLoc3 cl0 = getImplChildLoc(otherImpl, context, i);
	        context->getVoxelRange(cl0, depth + 1, r0);
	        Ionflux::GeoUtils::Vector3 c0 = r0.getCenter();
	        /* <---- DEBUG ----- //
	        std::cerr << "[Node::voxelizeImplFaces] DEBUG: "
	            "processing child node #" << std::setw(3) 
	            << std::setfill('0') << i << " [depth = " 
	            << (depth + 1) << ", loc = [" << getLocString(cl0) 
	            << "; (" << r0.getRMin().getValueString() 
	            << ")], size = " << (2. * r0.getRadius().getX0()) 
	            << ", center = (" << c0.getValueString() << ")]" 
	            << std::endl;
	        // ----- DEBUG ----> */
	        // create list of faces for child node
	        Ionflux::GeoUtils::FaceVector fv2;
	        bool createCN = false;
	        for (unsigned int k = 0; k < numFaces; k++)
	        {
	            Ionflux::GeoUtils::Face* cf = fv0[k];
	            TriangleVoxelizationData& ctv = tvd0[k];
	            /* <---- DEBUG ----- //
	            std::cerr << "[Node::voxelizeImplFaces] DEBUG: "
	                "testing face: (" << cf->getValueString() << "), tvd: " 
	                << std::endl;
	            //printTriangleVoxelizationDataDebugInfo(ctv);
	            // ----- DEBUG ----> */
	            if (voxelizePointTest(ctv, c0))
	            {
	                /* <---- DEBUG ----- //
	                std::cerr << "[Node::voxelizeImplFaces] DEBUG: "
	                    "voxelize point test: true" << std::endl;
	                // ----- DEBUG ----> */
	                fv2.push_back(cf);
	                /* create child node if it does not exist if there is 
	                   at least one potential face intersection */
	                createCN = true;
	            } else
	            {
	                /* <---- DEBUG ----- //
	                std::cerr << "[Node::voxelizeImplFaces] DEBUG: "
	                    "voxelize point test: false" << std::endl;
	                // ----- DEBUG ----> */
	            }
	        }
	        NodeImpl* cn0 = getImplChildByOrderIndex(otherImpl, context, 
	            i, createCN, fill0);
	        if (cn0 != 0)
	        {
	            // voxelize recursively
	            /* <---- DEBUG ----- //
	            std::cerr << "[Node::voxelizeImplFaces] DEBUG: "
	                "voxelizing child node #" << std::setw(3) 
	                << std::setfill('0') << i << " [depth = " 
	                << (depth + 1) << ", loc = [" << getLocString(cl0) 
	                << "; (" << r0.getRMin().getValueString() 
	                << ")], size = " << (2. * r0.getRadius().getX0()) 
	                << ", center = (" << c0.getValueString() 
	                << ")], numFaces = " << fv2.size() << std::endl;
	            // ----- DEBUG ----> */
	            numVoxels += voxelizeImplFaces(cn0, context, processor, 
	                targetDepth, sep, fill0, pruneEmpty0, &fv2);
	        }
	    }
	    // clean up
	    delete[] tvd0;
	    clearImpl(otherImpl, false, true, false);
	    if (pruneEmpty0)
	        pruneEmptyImpl(otherImpl, context);
	}
	return numVoxels;
}

unsigned int Node::getImplMemSize(Ionflux::VolGfx::NodeImpl* otherImpl, 
bool recursive)
{
	if (otherImpl == 0)
	    return 0;
	unsigned int s0 = sizeof(NodeImpl) 
	    + getDataImplMemSize(otherImpl->data);
	int n0 = otherImpl->valid.count();
	if (n0 > 0)
	{
	    NodeImpl* cp = otherImpl->child;
	    if (cp != 0)
	    {
	        s0 += (n0 * sizeof(NodeImpl*));
	        if (recursive)
	        {
	            for (int i = 0; i < n0; i++)
	            {
	                NodeImpl& cn = cp[i];
	                s0 += getImplMemSize(&cn, true);
	            }
	        }
	    }
	}
	return s0;
}

void Node::serializeDataImpl(Ionflux::VolGfx::NodeDataImpl* dataImpl, 
std::string& target)
{
	Ionflux::ObjectBase::nullPointerCheck(dataImpl, 
	    "Node::serializeDataImpl", "Node data implementation");
	Ionflux::ObjectBase::pack(MAGIC_SYLLABLE_BASE, MAGIC_SYLLABLE_DATA, 
	    target, true);
	pack(*dataImpl, target, true);
}

Ionflux::ObjectBase::DataSize Node::getDataValueSerializedSize()
{
	std::string t0;
	NodeDataValue v0 = 0.;
	Ionflux::ObjectBase::pack(v0, t0);
	return t0.size();
}

Ionflux::ObjectBase::DataSize 
Node::getDataImplSerializedSize(Ionflux::VolGfx::NodeDataType t)
{
	if (t == DATA_TYPE_UNKNOWN)
	{
	    throw IFVGError(Ionflux::ObjectBase::getErrorString(
	        "Data type 'unknown' does not have a serialized size.", 
	        "Node::getDataImplSerializedSize"));
	}
	std::string t0;
	Ionflux::ObjectBase::pack(MAGIC_SYLLABLE_BASE, MAGIC_SYLLABLE_DATA, 
	    t0, true);
	NodeDataImpl* d0 = createDataImpl(DATA_TYPE_NULL);
	pack(*d0, t0, true);
	delete d0;
	Ionflux::ObjectBase::DataSize n0 = t0.size();
	if ((t == DATA_TYPE_DENSITY) 
	    || (t == DATA_TYPE_COLOR_RGBA) 
	    || (t == DATA_TYPE_DISTANCE_8) 
	    || (t == DATA_TYPE_COLOR_NORMAL))
	{
	    // array types
	    Ionflux::ObjectBase::DataSize n1 = getDataTypeNumElements(t);
	    Ionflux::ObjectBase::DataSize n2 = 0;
	    if (n1 != Ionflux::ObjectBase::DATA_SIZE_INVALID)
	        n2 = getDataValueSerializedSize();
	    return n0 + n1 * n2;
	} else
	if (t == DATA_TYPE_VOXEL_CLASS)
	{
	    // voxel class
	    return n0 + sizeof(VoxelClassID);
	} else
	if (t == DATA_TYPE_VOXEL_IOB)
	{
	    // voxel inside/outside/boundary
	    VoxelDataIOB d0 = createVoxelDataIOB();
	    pack(d0, t0, false);
	    return n0 + t0.size();
	}
	return 0;
}

Ionflux::ObjectBase::DataSize 
Node::deserializeDataImpl(Ionflux::VolGfx::NodeDataImpl* dataImpl, const 
std::string& source, Ionflux::ObjectBase::DataSize offset)
{
	Ionflux::ObjectBase::nullPointerCheck(dataImpl, 
	    "Node::deserializeDataImpl", "Node data implementation");
	// Magic word check
	Ionflux::ObjectBase::DataSize o0 = 
	    Ionflux::ObjectBase::unpackAndCheckMagicWord(source, 
	        MAGIC_SYLLABLE_BASE, MAGIC_SYLLABLE_DATA, offset, 0, 
	        "Node::deserializeDataImpl");
	// unpack the data
	o0 = unpack(source, *dataImpl, o0);
	if (o0 == Ionflux::ObjectBase::DATA_SIZE_INVALID)
	{
	    std::ostringstream status;
	    status << "Could not deserialize node data implementation (" 
	        "offset = " << offset << ", source.size = " << source.size() 
	        << ").";
	    throw IFVGError(Ionflux::ObjectBase::getErrorString(
	        status.str(), "Node::deserializeDataImpl"));
	}
	return o0;
}

void Node::deserializeDataImpl(Ionflux::VolGfx::NodeDataImpl* dataImpl, 
std::istream& source, Ionflux::ObjectBase::DataSize offset, 
Ionflux::ObjectBase::PointerOffsetMap* poMapCurrent)
{
	Ionflux::ObjectBase::nullPointerCheck(dataImpl, 
	    "Node::deserializeDataImpl", "Node data implementation");
	if (offset != Ionflux::ObjectBase::DATA_SIZE_INVALID)
	{
	    source.seekg(offset);
	    if (!source.good())
	    {
	        std::ostringstream status;
	        status << "Invalid stream offset: " << offset;
	        throw IFVGError(Ionflux::ObjectBase::getErrorString(
	            status.str(), "Node::deserializeDataImpl"));
	    }
	} else
	    offset = source.tellg();
	std::streampos p0 = source.tellg();
	// Magic word check
	std::string t0;
	Ionflux::ObjectBase::readFromStream(source, t0, 
	    sizeof(Ionflux::ObjectBase::MagicWord));
	Ionflux::ObjectBase::unpackAndCheckMagicWord(t0, 
	    MAGIC_SYLLABLE_BASE, MAGIC_SYLLABLE_DATA, 0, 0, 
	    "Node::deserializeDataImpl");
	// unpack data type
	NodeDataType dt0 = Node::DATA_TYPE_UNKNOWN;
	Ionflux::ObjectBase::readFromStream(source, t0, sizeof(NodeDataType));
	Ionflux::ObjectBase::unpack(t0, dt0, 0);
	Ionflux::ObjectBase::DataSize s0 = getDataImplSerializedSize(dt0);
	// deserialize data
	source.seekg(p0);
	Ionflux::ObjectBase::readFromStream(source, t0, s0);
	deserializeDataImpl(dataImpl, t0, 0);
	if (poMapCurrent != 0)
	{
	    // update the current pointer/offset map
	    Ionflux::ObjectBase::GenericPointer dp0 = 
	        static_cast<Ionflux::ObjectBase::GenericPointer>(dataImpl);
	    (*poMapCurrent)[dp0] = offset;
	}
}

void Node::deserializeDataImpl(Ionflux::VolGfx::NodeDataImpl* dataImpl, 
Ionflux::VolGfx::IOContext& ioContext, Ionflux::ObjectBase::DataSize 
offset)
{
	std::istream* source = Ionflux::ObjectBase::nullPointerCheck(
	    ioContext.getInputStream(), "Node::deserializeDataImpl", 
	    "Input stream");
	deserializeDataImpl(dataImpl, *source, offset, 
	    ioContext.getPoMapCurrent());
}

void Node::serializeImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, std::string& target, 
Ionflux::ObjectBase::MagicSyllable magicSyllable)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::serializeImpl", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::serializeImpl", "Context");
	Ionflux::ObjectBase::pack(MAGIC_SYLLABLE_BASE, magicSyllable, 
	    target, true);
	pack(*otherImpl, target, true);
}

void Node::serializeImplChildNodes(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, std::ostream& target, 
Ionflux::ObjectBase::PointerOffsetMap& poMap, int minDepth, int maxDepth, 
bool recursive, bool serializeData)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::serializeImplChildNodes", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::serializeImplChildNodes", "Context");
	int depth = getImplDepth(otherImpl, context);
	int maxNumLevels = context->getMaxNumLevels();
	if (minDepth < 1)
	{
	    // There are no child nodes on level 0.
	    minDepth = 1;
	}
	if ((maxDepth == DEPTH_UNSPECIFIED) 
	    || (maxDepth >= maxNumLevels))
	    maxDepth = maxNumLevels - 1;
	if (minDepth > maxDepth)
	    return;
	if (depth > maxDepth)
	    return;
	if ((depth < minDepth)
	    && (!recursive))
	    return;
	NodeImplQueue q0;
	q0.push_back(otherImpl);
	std::string t0;
	Ionflux::ObjectBase::DataSize offset = target.tellp();
	while (!q0.empty())
	{
	    NodeImpl* ci = q0.front();
	    q0.pop_front();
	    int d0 = getImplDepth(ci, context);
	    if ((d0 >= minDepth) 
	        && (d0 <= maxDepth))
	    {
	        /* <---- DEBUG ----- //
	        std::cout << "[Node::serializeImplHierarchy] DEBUG: "
	            "serializing node implementation: " << ci << " (depth = " 
	            << d0 << ", offset = " << offset << ")." << std::endl;
	        // ----- DEBUG ----> */
	        // serialize node implementation
	        poMap[ci] = offset;
	        serializeImpl(ci, context, t0, MAGIC_SYLLABLE_NODE);
	        target.write(t0.c_str(), t0.size());
	        offset += t0.size();
	        t0.assign("");
	        // serialize node data
	        if ((ci->data != 0) 
	            && serializeData)
	        {
	            /* <---- DEBUG ----- //
	            std::cout << "[Node::serializeImplHierarchy] DEBUG: "
	                "serializing node data: " << ci->data 
	                << ", offset = " << offset << ")." << std::endl;
	            // ----- DEBUG ----> */
	            poMap[ci->data] = offset;
	            serializeDataImpl(ci->data, t0);
	            target.write(t0.c_str(), t0.size());
	            offset += t0.size();
	            t0.assign("");
	        }
	    }
	    if ((d0 < maxDepth) 
	        && recursive)
	    {
	        // enqueue child nodes
	        int n0 = getImplNumChildNodes(ci);
	        for (int i = 0; i < n0; i++)
	        {
	            NodeImpl* cn0 = Ionflux::ObjectBase::nullPointerCheck(
	                getImplChildByValidIndex(ci, i), 
	                "Node::serializeImplChildNodes", 
	                "Child node implementation");
	            /* <---- DEBUG ----- //
	            std::cout << "[Node::serializeImplHierarchy] DEBUG: "
	                "enqueuing child node: " << cn0 << " (depth = " 
	                << (d0 + 1) << ")" << std::endl;
	            // ----- DEBUG ----> */
	            q0.push_back(cn0);
	        }
	    }
	}
}

void Node::serializeImplChildNodes(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, Ionflux::VolGfx::IOContext& ioContext, 
int minDepth, int maxDepth, bool recursive, bool serializeData)
{
	std::ostream* target = Ionflux::ObjectBase::nullPointerCheck(
	    ioContext.getOutputStream(), "Node::serializeImplChildNodes", 
	    "Output stream");
	Ionflux::ObjectBase::PointerOffsetMap* poMap = 
	    Ionflux::ObjectBase::nullPointerCheck(
	        ioContext.getPoMapSerialized(), 
	    "Node::serializeImplChildNodes", 
	    "Pointer/offset map (serialized)");
	serializeImplChildNodes(otherImpl, context, *target, *poMap, minDepth, 
	    maxDepth, recursive, serializeData);
}

Ionflux::ObjectBase::DataSize 
Node::getImplSerializedSize(Ionflux::VolGfx::NodeDataType t)
{
	std::string t0;
	Ionflux::ObjectBase::pack(MAGIC_SYLLABLE_BASE, MAGIC_SYLLABLE_NODE, 
	    t0, true);
	NodeImpl* n0 = createImpl();
	pack(*n0, t0, true);
	delete n0;
	return t0.size();
}

void Node::serializeImplHierarchy(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, std::ostream& target, 
Ionflux::VolGfx::NodeImplHierarchyHeader* header, 
Ionflux::ObjectBase::PointerOffsetMap* poMap)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::serializeImplHierarchy", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::serializeImplHierarchy", "Context");
	Ionflux::ObjectBase::DataSize offset = 0;
	// header
	std::string t0;
	Ionflux::ObjectBase::pack(MAGIC_SYLLABLE_BASE, MAGIC_SYLLABLE_HEADER, 
	    t0, true);
	// pointer/offset map offset to be set later
	Ionflux::ObjectBase::DataSize poMapOffsetPos = t0.size();
	NodeImplHierarchyHeader* header0 = 0;
	if (header == 0)
	{
	    header0 = Ionflux::ObjectBase::create<NodeImplHierarchyHeader>(
	        "Node::serializeImplHierarchy", "header");
	    header = header0;
	}
	header->poMapOffset = 0;
	header->implArrayStride = 
	    static_cast<Ionflux::ObjectBase::UInt16>(
	        getImplArrayStride());
	header->implSize = 
	    static_cast<Ionflux::ObjectBase::UInt16>(
	        getImplSerializedSize());
	header->dataImplSize = 
	    static_cast<Ionflux::ObjectBase::UInt16>(
	        getDataImplSerializedSize());
	header->dataValueSize = 
	    static_cast<Ionflux::ObjectBase::UInt8>(
	        getDataValueSerializedSize());
	header->rootNodeDepth = 
	    static_cast<Ionflux::ObjectBase::UInt8>(
	        getImplDepth(otherImpl, context));
	header->rootNodePointer = 
	    static_cast<Ionflux::ObjectBase::GenericPointer>(otherImpl);
	pack(*header, t0, true);
	target.write(t0.c_str(), t0.size());
	offset += t0.size();
	t0.assign("");
	// root node
	/* <---- DEBUG ----- //
	std::cout << "[Node::serializeImplHierarchy] DEBUG: "
	    "root node: " << otherImpl << std::endl;
	// ----- DEBUG ----> */
	Ionflux::ObjectBase::PointerOffsetMap* poMap0 = 0;
	if (poMap == 0)
	{
	    poMap0 = Ionflux::ObjectBase::create<
	        Ionflux::ObjectBase::PointerOffsetMap>(
	            "Node::serializeImplHierarchy", 
	            "pointer/offset map (serialized)");
	    poMap = poMap0;
	}
	(*poMap)[otherImpl] = offset;
	serializeImpl(otherImpl, context, t0, MAGIC_SYLLABLE_ROOT);
	target.write(t0.c_str(), t0.size());
	offset += t0.size();
	t0.assign("");
	// root node data
	if (otherImpl->data != 0)
	{
	    /* <---- DEBUG ----- //
	    std::cout << "[Node::serializeImplHierarchy] DEBUG: "
	        "root node data: " << otherImpl->data << std::endl;
	    // ----- DEBUG ----> */
	    (*poMap)[otherImpl->data] = offset;
	    serializeDataImpl(otherImpl->data, t0);
	    target.write(t0.c_str(), t0.size());
	    offset += t0.size();
	    t0.assign("");
	}
	// serialize child nodes.
	serializeImplChildNodes(otherImpl, context, target, *poMap);
	offset = target.tellp();
	// pointer/offset map
	header->poMapOffset = offset;
	Ionflux::ObjectBase::pack(MAGIC_SYLLABLE_BASE, 
	    MAGIC_SYLLABLE_OFFSET_MAP, t0, false);
	Ionflux::ObjectBase::pack(*poMap, t0, true);
	target.write(t0.c_str(), t0.size());
	std::streampos p0 = target.tellp();
	Ionflux::ObjectBase::pack(header->poMapOffset, t0, false);
	Ionflux::ObjectBase::writeToStream(target, t0, poMapOffsetPos);
	target.seekp(p0);
	// clean up
	if (header0 != 0)
	    delete header0;
	header0 = 0;
	if (poMap0 != 0)
	    delete poMap0;
	poMap0 = 0;
}

void Node::serializeImplHierarchy(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, Ionflux::VolGfx::IOContext& ioContext)
{
	std::ostream* target = Ionflux::ObjectBase::nullPointerCheck(
	    ioContext.getOutputStream(), "Node::serializeImplHierarchy", 
	    "Output stream");
	Ionflux::ObjectBase::PointerOffsetMap* poMap = 
	    Ionflux::ObjectBase::nullPointerCheck(
	        ioContext.getPoMapSerialized(), 
	    "Node::serializeImplHierarchy", 
	    "Pointer/offset map (serialized)");
	NodeImplHierarchyHeader header;
	serializeImplHierarchy(otherImpl, context, *target, &header, poMap);
	ioContext.setHeader(header);
}

Ionflux::ObjectBase::DataSize Node::getImplHierarchyHeaderSerializedSize()
{
	std::string t0;
	NodeImplHierarchyHeader h0;
	pack(h0, t0, true);
	return t0.size() + sizeof(Ionflux::ObjectBase::MagicWord);
}

Ionflux::ObjectBase::DataSize 
Node::deserializeImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, const std::string& source, 
Ionflux::ObjectBase::DataSize offset, Ionflux::ObjectBase::MagicSyllable 
magicSyllable)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::deserializeImpl", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::deserializeImpl", "Context");
	// Magic word check
	Ionflux::ObjectBase::DataSize o0 = 
	    Ionflux::ObjectBase::unpackAndCheckMagicWord(source, 
	        MAGIC_SYLLABLE_BASE, magicSyllable, offset, 0, 
	        "Node::deserializeImpl");
	// unpack the node
	clearImpl(otherImpl, true, true, true);
	o0 = unpack(source, *otherImpl, o0);
	if (o0 == Ionflux::ObjectBase::DATA_SIZE_INVALID)
	{
	    std::ostringstream status;
	    status << "Could not deserialize node implementation (" 
	        "offset = " << offset << ", source.size = " << source.size() 
	        << ").";
	    throw IFVGError(Ionflux::ObjectBase::getErrorString(
	        status.str(), "Node::deserializeImpl"));
	}
	return o0;
}

void Node::deserializeImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, std::istream& source, const 
Ionflux::VolGfx::NodeImplHierarchyHeader& header, const 
Ionflux::ObjectBase::PointerOffsetMap& poMap, Ionflux::ObjectBase::DataSize
offset, Ionflux::ObjectBase::MagicSyllable magicSyllable, 
Ionflux::ObjectBase::PointerOffsetMap* poMapCurrent, bool deserializeData, 
bool zeroChildPointer, bool zeroParentPointer)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::deserializeImpl", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::deserializeImpl", "Context");
	if (offset != Ionflux::ObjectBase::DATA_SIZE_INVALID)
	{
	    source.seekg(offset);
	    if (!source.good())
	    {
	        std::ostringstream status;
	        status << "Invalid stream offset: " << offset;
	        throw IFVGError(Ionflux::ObjectBase::getErrorString(
	            status.str(), "Node::deserializeImpl"));
	    }
	} else
	    offset = source.tellg();
	// Magic word check
	std::string t0;
	Ionflux::ObjectBase::readFromStream(source, t0, 
	    sizeof(Ionflux::ObjectBase::MagicWord) + header.implSize);
	Ionflux::ObjectBase::DataSize o0 = 
	    Ionflux::ObjectBase::unpackAndCheckMagicWord(t0, 
	        MAGIC_SYLLABLE_BASE, magicSyllable, 0, 0, 
	        "Node::deserializeImpl");
	// unpack node implementation
	unpack(t0, *otherImpl, o0);
	/* NOTE: Set parent/child node pointers to null to prevent accesses 
	         into unallocated memory. */
	if (zeroChildPointer)
	    otherImpl->child = 0;
	if (zeroParentPointer)
	    otherImpl->parent = 0;
	if (poMapCurrent != 0)
	{
	    // update the current pointer/offset map
	    Ionflux::ObjectBase::GenericPointer np0 = 
	        static_cast<Ionflux::ObjectBase::GenericPointer>(otherImpl);
	    (*poMapCurrent)[np0] = offset;
	}
	NodeDataImpl* dp0 = otherImpl->data;
	otherImpl->data = 0;
	if ((dp0 != 0) 
	    && (deserializeData))
	{
	    // unpack node data
	    Ionflux::ObjectBase::DataSize do0 = 
	        Ionflux::ObjectBase::checkedLookup(poMap, 
	            static_cast<Ionflux::ObjectBase::GenericPointer>(dp0), 
	            "Node::deserializeImpl", "Node data offset");
	    dp0 = createDataImpl(DATA_TYPE_NULL);
	    deserializeDataImpl(dp0, source, do0, poMapCurrent);
	    otherImpl->data = dp0;
	}
}

void Node::deserializeImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, Ionflux::VolGfx::IOContext& ioContext, 
Ionflux::ObjectBase::DataSize offset, Ionflux::ObjectBase::MagicSyllable 
magicSyllable, bool deserializeData, bool zeroChildPointer, bool 
zeroParentPointer)
{
	std::istream* source = Ionflux::ObjectBase::nullPointerCheck(
	    ioContext.getInputStream(), "Node::deserializeImpl", 
	    "Input stream");
	Ionflux::ObjectBase::PointerOffsetMap* poMap = 
	    Ionflux::ObjectBase::nullPointerCheck(
	        ioContext.getPoMapSerialized(), 
	    "Node::deserializeImpl", 
	    "Pointer/offset map (serialized)");
	Ionflux::ObjectBase::PointerOffsetMap* poMapCurrent = 
	    Ionflux::ObjectBase::nullPointerCheck(
	        ioContext.getPoMapCurrent(), 
	    "Node::deserializeImpl", 
	    "Pointer/offset map (current)");
	NodeImplHierarchyHeader header = ioContext.getHeader();
	deserializeImpl(otherImpl, context, *source, header, *poMap, offset, 
	    magicSyllable, poMapCurrent, deserializeData, zeroChildPointer, 
	    zeroParentPointer);
}

void Node::deserializeImplChildNodes(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, std::istream& source, 
Ionflux::ObjectBase::GenericPointer childPointer, const 
Ionflux::VolGfx::NodeImplHierarchyHeader& header, 
Ionflux::ObjectBase::PointerOffsetMap& poMap, 
Ionflux::ObjectBase::PointerOffsetMap* poMapCurrent, int maxDepth, bool 
recursive, bool deserializeData)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::deserializeImplChildNodes", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::deserializeImplChildNodes", "Context");
	int depth = getImplDepth(otherImpl, context);
	int maxNumLevels = context->getMaxNumLevels();
	if ((maxDepth == DEPTH_UNSPECIFIED) 
	    || (maxDepth >= maxNumLevels))
	    maxDepth = maxNumLevels - 1;
	if (depth >= maxDepth)
	    return;
	/* <---- DEBUG ----- //
	std::cout << "[Node::deserializeImplChildNodes] DEBUG: "
	    "node: " << getImplValueString(otherImpl, context, false) 
	    << std::endl;
	// ----- DEBUG ----> */
	NodeImpl* cp0 = static_cast<NodeImpl*>(childPointer);
	if (otherImpl->child != 0)
	{
	    throw IFVGError("[Node::deserializeImplChildNodes] "
	        "Node implementation has non-zero child node pointer.");
	}
	int n0 = getImplNumChildNodes(otherImpl);
	// allocate new child node array
	NodeImpl* cp1 = new NodeImpl[n0];
	if (cp1 == 0)
	{
	    throw IFVGError("Node::deserializeImplChildNodes"
	        "Could not allocate child node implementations.");
	}
	Ionflux::ObjectBase::UInt64 cpi0 = 
	    reinterpret_cast<Ionflux::ObjectBase::UInt64>(cp0);
	for (int i = 0; i < n0; i++)
	{
	    Ionflux::ObjectBase::GenericPointer cpc0 = 
	        reinterpret_cast<Ionflux::ObjectBase::GenericPointer>(cpi0);
	    Ionflux::ObjectBase::PointerOffsetMap::const_iterator poi0 = 
	        poMap.find(cpc0);
	    if (poi0 == poMap.end())
	    {
	        std::ostringstream status;
	        status << "Offset not found for child node implementation "
	            "(child pointer = " << cp0 << ", child node = " 
	            << cpc0 << ", implArrayStride = " << header.implArrayStride 
	            << ").";
	        throw IFVGError(Ionflux::ObjectBase::getErrorString(
	            status.str(), "Node::deserializeImplChildNodes"));
	    }
	    Ionflux::ObjectBase::DataSize co0 = (*poi0).second;
	    NodeImpl* cc0 = &(cp1[i]);
	    // refCount not set by deserializeImpl()
	    cc0->refCount = 0;
	    // This reference will be cleared by clearImpl().
	    refImpl(cc0);
	    deserializeImpl(cc0, context, source, header, poMap, co0, 
	        MAGIC_SYLLABLE_NODE, poMapCurrent, deserializeData, false, 
	        true);
	    cp0 = cc0->child;
	    cc0->child = 0;
	    if (recursive)
	    {
	        // deserialize child nodes recursively
	        deserializeImplChildNodes(cc0, context, source, 
	            static_cast<Ionflux::ObjectBase::GenericPointer>(cp0), 
	            header, poMap, poMapCurrent, maxDepth, true, 
	            deserializeData);
	    }
	    cpi0 += header.implArrayStride;
	}
	otherImpl->child = cp1;
	setImplParent(otherImpl);
}

void Node::deserializeImplChildNodes(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, Ionflux::VolGfx::IOContext& ioContext, 
Ionflux::ObjectBase::GenericPointer childPointer, int maxDepth, bool 
recursive, bool deserializeData)
{
	std::istream* source = Ionflux::ObjectBase::nullPointerCheck(
	    ioContext.getInputStream(), "Node::deserializeImplChildNodes", 
	    "Input stream");
	Ionflux::ObjectBase::PointerOffsetMap* poMap = 
	    Ionflux::ObjectBase::nullPointerCheck(
	        ioContext.getPoMapSerialized(), 
	    "Node::deserializeImplChildNodes", 
	    "Pointer/offset map (serialized)");
	Ionflux::ObjectBase::PointerOffsetMap* poMapCurrent = 
	    Ionflux::ObjectBase::nullPointerCheck(
	        ioContext.getPoMapCurrent(), 
	    "Node::deserializeImplChildNodes", 
	    "Pointer/offset map (current)");
	NodeImplHierarchyHeader header = ioContext.getHeader();
	deserializeImplChildNodes(otherImpl, context, *source, childPointer, 
	    header, *poMap, poMapCurrent, maxDepth, recursive, deserializeData);
}

void Node::deserializeImplChildNodes(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, std::istream& source, 
Ionflux::ObjectBase::DataSize offset, const 
Ionflux::VolGfx::NodeImplHierarchyHeader& header, 
Ionflux::ObjectBase::PointerOffsetMap& poMap, 
Ionflux::ObjectBase::PointerOffsetMap* poMapCurrent, 
Ionflux::ObjectBase::MagicSyllable magicSyllable, int maxDepth, bool 
recursive, bool deserializeData)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::deserializeImplChildNodes", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::deserializeImplChildNodes", "Context");
	int depth = getImplDepth(otherImpl, context);
	int maxNumLevels = context->getMaxNumLevels();
	if ((maxDepth == DEPTH_UNSPECIFIED) 
	    || (maxDepth >= maxNumLevels))
	    maxDepth = maxNumLevels - 1;
	if (depth >= maxDepth)
	    return;
	// get the child node pointer from the stream
	NodeImpl* cn0 = createImpl();
	refImpl(cn0);
	deserializeImpl(cn0, context, source, header, poMap, offset, 
	    magicSyllable, poMapCurrent, true, false, true);
	// <---- DEBUG ----- //
	std::cout << "[Node::deserializeImplChildNodes] DEBUG: "
	    "node: " << getImplValueString(cn0, context, false) 
	    << std::endl;
	// ----- DEBUG ----> */
	NodeImpl* cp0 = cn0->child;
	cn0->child = 0;
	int n0 = getImplNumChildNodes(cn0);
	if (n0 == 0)
	{
	    // node has no child nodes.
	    return;
	}
	deserializeImplChildNodes(cn0, context, source, 
	    static_cast<Ionflux::ObjectBase::GenericPointer>(cp0), header, 
	    poMap, poMapCurrent, maxDepth, recursive, deserializeData);
	clearImpl(otherImpl, true, true, true);
	copyImpl(*cn0, *otherImpl, true);
	setImplParent(otherImpl);
	unrefImpl(cn0);
}

void Node::deserializeImplChildNodes(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, Ionflux::VolGfx::IOContext& ioContext, 
Ionflux::ObjectBase::DataSize offset, Ionflux::ObjectBase::MagicSyllable 
magicSyllable, int maxDepth, bool recursive, bool deserializeData)
{
	std::istream* source = Ionflux::ObjectBase::nullPointerCheck(
	    ioContext.getInputStream(), "Node::deserializeImplChildNodes", 
	    "Input stream");
	Ionflux::ObjectBase::PointerOffsetMap* poMap = 
	    Ionflux::ObjectBase::nullPointerCheck(
	        ioContext.getPoMapSerialized(), 
	    "Node::deserializeImplChildNodes", 
	    "Pointer/offset map (serialized)");
	Ionflux::ObjectBase::PointerOffsetMap* poMapCurrent = 
	    Ionflux::ObjectBase::nullPointerCheck(
	        ioContext.getPoMapCurrent(), 
	    "Node::deserializeImplChildNodes", 
	    "Pointer/offset map (current)");
	NodeImplHierarchyHeader header = ioContext.getHeader();
	deserializeImplChildNodes(otherImpl, context, *source, offset, 
	    header, *poMap, poMapCurrent, magicSyllable, maxDepth, recursive, 
	    deserializeData);
}

void Node::deserializeImplHierarchy(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, std::istream& source, 
Ionflux::VolGfx::NodeImplHierarchyHeader* header, Ionflux::VolGfx::NodeID* 
targetNode, Ionflux::ObjectBase::PointerOffsetMap* poMap, 
Ionflux::ObjectBase::PointerOffsetMap* poMapCurrent, bool deserializeData, 
int maxDepth)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::deserializeImplHierarchy", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::deserializeImplHierarchy", "Context");
	// Magic word check
	std::string t0;
	Ionflux::ObjectBase::DataSize s0 = 
	    getImplHierarchyHeaderSerializedSize();
	Ionflux::ObjectBase::readFromStream(source, t0, s0);
	Ionflux::ObjectBase::DataSize o0 = 
	    Ionflux::ObjectBase::unpackAndCheckMagicWord(t0, 
	        MAGIC_SYLLABLE_BASE, MAGIC_SYLLABLE_HEADER, 0, 0, 
	        "Node::deserializeImplHierarchy");
	// header
	NodeImplHierarchyHeader* header0 = 0;
	if (header == 0)
	{
	    header0 = Ionflux::ObjectBase::create<NodeImplHierarchyHeader>(
	        "Node::deserializeImplHierarchy", "header");
	    header = header0;
	}
	unpack(t0, *header, o0);
	/* <---- DEBUG ----- //
	std::cout << "[Node::deserializeImplHierarchy] DEBUG: "
	    "unpacked header: [" << getNodeImplHierarchyHeaderValueString(*header)
	
    << std::endl;
	// ----- DEBUG ----> */
	// pointer/offset map
	source.seekg(header->poMapOffset);
	if (!source.good())
	{
	    std::ostringstream status;
	    status << "Invalid stream offset for pointer/offset map (offset = " 
	        << header->poMapOffset << ").";
	    throw IFVGError(Ionflux::ObjectBase::getErrorString(
	        status.str(), "Node::deserializeImplHierarchy"));
	}
	Ionflux::ObjectBase::readFromStream(source, t0, 
	    sizeof(Ionflux::ObjectBase::MagicWord));
	Ionflux::ObjectBase::unpackAndCheckMagicWord(t0, 
	    MAGIC_SYLLABLE_BASE, MAGIC_SYLLABLE_OFFSET_MAP, 0, 0, 
	    "Node::deserializeImplHierarchy");
	Ionflux::ObjectBase::PointerOffsetMap* poMap0 = 0;
	if (poMap == 0)
	{
	    poMap0 = Ionflux::ObjectBase::create<
	        Ionflux::ObjectBase::PointerOffsetMap>(
	            "Node::deserializeImplHierarchy", 
	            "pointer/offset map (serialized)");
	    poMap = poMap0;
	}
	Ionflux::ObjectBase::readFromStream(source, t0);
	Ionflux::ObjectBase::unpack(t0, *poMap);
	/* <---- DEBUG ----- //
	std::cout << "[Node::deserializeImplHierarchy] DEBUG: "
	    "pointer/offset map: " << std::endl;
	Ionflux::ObjectBase::DataSize k = 0;
	for (Ionflux::ObjectBase::PointerOffsetMap::const_iterator i = 
	    poMap->begin(); i != poMap->end(); i++)
	{
	    std::cout << "  [" << std::setw(3) << std::setfill('0') 
	        << std::right << k << "] " << (*i).first << " -> " 
	        << (*i).second << std::endl;
	    k++;
	}
	// ----- DEBUG ----> */
	// root node
	Ionflux::ObjectBase::DataSize ro0 = 
	    Ionflux::ObjectBase::checkedLookup(*poMap, header->rootNodePointer, 
	        "Node::deserializeImplHierarchy", "Root node offset");
	/* <---- DEBUG ----- //
	std::cout << "[Node::deserializeImplHierarchy] DEBUG: "
	    "root node offset = " << ro0 << std::endl;
	// ----- DEBUG ----> */
	NodeImpl* root0 = createImpl();
	refImpl(root0);
	deserializeImpl(root0, context, source, *header, *poMap, ro0, 
	    MAGIC_SYLLABLE_ROOT, poMapCurrent, true, false, true);
	Ionflux::ObjectBase::GenericPointer cp0 = 
	    static_cast<Ionflux::ObjectBase::GenericPointer>(root0->child);
	root0->child = 0;
	if (targetNode != 0)
	{
	    targetNode->depth = header->rootNodeDepth;
	    targetNode->loc = root0->loc;
	}
	if ((maxDepth == DEPTH_UNSPECIFIED) 
	    || (maxDepth > header->rootNodeDepth))
	{
	    // deserialize child nodes
	    deserializeImplChildNodes(root0, context, source, cp0, *header, 
	*poMap, 
	        poMapCurrent, maxDepth, true, deserializeData);
	}
	/* <---- DEBUG ----- //
	std::cout << "[Node::deserializeImplHierarchy] DEBUG: "
	    "root node: " << getImplValueString(root0, context) 
	    << std::endl;
	// ----- DEBUG ----> */
	clearImpl(otherImpl, true, true, true);
	copyImpl(*root0, *otherImpl, true);
	setImplParent(otherImpl);
	unrefImpl(root0);
	// clean up
	if (header0 != 0)
	    delete header0;
	header0 = 0;
	if (poMap0 != 0)
	    delete poMap0;
	poMap0 = 0;
}

void Node::deserializeImplHierarchy(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, Ionflux::VolGfx::IOContext& ioContext, 
bool deserializeData, int maxDepth)
{
	std::istream* source = Ionflux::ObjectBase::nullPointerCheck(
	    ioContext.getInputStream(), "Node::deserializeImplHierarchy", 
	    "Input stream");
	Ionflux::ObjectBase::PointerOffsetMap* poMap = 
	    Ionflux::ObjectBase::nullPointerCheck(
	        ioContext.getPoMapSerialized(), 
	    "Node::deserializeImplHierarchy", 
	    "Pointer/offset map (serialized)");
	Ionflux::ObjectBase::PointerOffsetMap* poMapCurrent = 
	    Ionflux::ObjectBase::nullPointerCheck(
	        ioContext.getPoMapCurrent(), 
	    "Node::deserializeImplHierarchy", 
	    "Pointer/offset map (current)");
	NodeImplHierarchyHeader header;
	NodeID rootNodeID;
	deserializeImplHierarchy(otherImpl, context, *source, &header, 
	    &rootNodeID, poMap, poMapCurrent, deserializeData, maxDepth);
	ioContext.setHeader(header);
	ioContext.setRootNodeID(rootNodeID);
}

Ionflux::ObjectBase::DataSize Node::getImplArrayStride()
{
	NodeImpl* p0 = 0;
	return reinterpret_cast<Ionflux::ObjectBase::DataSize>(p0 + 1) 
    - reinterpret_cast<Ionflux::ObjectBase::DataSize>(p0);
}

bool Node::intersectRayImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, const Ionflux::GeoUtils::Line3& ray, 
Ionflux::VolGfx::NodeIntersection& target, double t)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::intersectRayImpl", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::intersectRayImpl", "Context");
	Ionflux::GeoUtils::Range3 r0;
	getImplRange(otherImpl, context, r0);
	target.nodeImpl = otherImpl;
	target.depth = getImplDepth(otherImpl, context);
	r0.intersect(ray, target.intersection);
	target.faces = (target.intersection.nearPlane 
	    | target.intersection.farPlane);
	return target.intersection.valid;
}

unsigned int Node::intersectRayImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, const Ionflux::GeoUtils::Line3& ray, 
Ionflux::VolGfx::NodeIntersectionProcessor* processor, 
Ionflux::VolGfx::NodeFilter* filter, bool recursive, double t, const 
Ionflux::VolGfx::NodeIntersection* pcIntersection, bool fill0, bool 
pruneEmpty0)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::intersectRayImpl", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::intersectRayImpl", "Context");
	int depth = getImplDepth(otherImpl, context);
	int maxDepth = DEPTH_UNSPECIFIED;
	bool atMaxDepth = false;
	if (filter != 0)
	{
	    maxDepth = filter->getMaxDepth();
	    if (!context->checkDepthRange(depth, 0, maxDepth))
	        return 0;
	    if ((maxDepth != DEPTH_UNSPECIFIED) 
	        && (depth == maxDepth))
	        atMaxDepth = true;
	}
	// get intersections for this node
	NodeIntersection ni0;
	if (pcIntersection != 0)
	{
	    ni0 = *pcIntersection;
	} else
	    intersectRayImpl(otherImpl, context, ray, ni0, t);
	if (!ni0.intersection.valid)
	    return 0;
	if (fill0 && !atMaxDepth)
	    fillImpl(otherImpl, context);
	unsigned int numNodes = 0;
	NodeProcessingResultID result = NodeProcessor::RESULT_OK;
	if ((filter == 0) 
	    || NodeProcessor::checkFlags(
	        filter->process(otherImpl), NodeFilter::RESULT_PASS))
	{
	    // process this node intersection
	    if (processor != 0)
	        result = processor->processIntersection(ni0);
	    numNodes++;
	}
	if (!recursive 
	    || atMaxDepth 
	    || NodeProcessor::checkFlags(result, 
	        ChainableNodeProcessor::RESULT_FINISHED))
	    return numNodes;
	// get intersection order for child nodes
	/* <---- DEBUG ----- //
	int n1 = getImplNumChildNodes(otherImpl);
	unsigned int cni1 = 0;
	for (int i = 0; i < n1; i++)
	{
	    NodeImpl& cn = otherImpl->child[i];
	    if (hasImplVoxelClass(&cn, VOXEL_CLASS_FILLED))
	        cni1++;
	}
	if (cni1 != 0)
	{
	    std::cerr << "[Node::intersectRayImpl] DEBUG: " 
	        "Node before filling:" << std::endl;
	    printImplDebugInfo(otherImpl, context, true);
	}
	// ----- DEBUG ----> */
	/* <---- DEBUG ----- //
	if (cni1 != 0)
	{
	    std::cerr << "[Node::intersectRayImpl] DEBUG: " 
	        "Node after filling:" << std::endl;
	    printImplDebugInfo(otherImpl, context, true);
	}
	// ----- DEBUG ----> */
	NodeIntersectionVector niv0;
	int n0 = getImplNumChildNodes(otherImpl);
	for (int i = 0; i < n0; i++)
	{
	    NodeImpl* cn0 = Ionflux::ObjectBase::nullPointerCheck(
	        getImplChildByValidIndex(otherImpl, i), 
	        "Node::intersectRayImpl", "Child node implementation");
	    if (intersectRayImpl(cn0, context, ray, ni0, t))
	    {
	        /* <---- DEBUG ----- //
	        if (cni1 != 0)
	        {
	            std::cerr << "[Node::intersectRayImpl] DEBUG: " 
	                "child node intersection: " << ni0.nodeImpl << " [" 
	                << getNodeIntersectionValueString(*context, ni0) << "]"
	                << std::endl;
	        }
	        // ----- DEBUG ----> */
	        niv0.push_back(ni0);
	    }
	}
	NodeIntersectionCompare cmp0;
	std::sort(niv0.begin(), niv0.end(), cmp0);
	// intersect nodes recursively
	/* <---- DEBUG ----- //
	if (cni1 != 0)
	{
	    std::cerr << "[Node::intersectRayImpl] DEBUG: " 
	        "Node before child intersections:" << std::endl;
	    printImplDebugInfo(otherImpl, context, true);
	}
	// ----- DEBUG ----> */
	
	for (NodeIntersectionVector::iterator i = niv0.begin(); 
	    i != niv0.end(); i++)
	{
	    NodeIntersection& ci = *i;
	    numNodes += intersectRayImpl(ci.nodeImpl, context, ray, 
	        processor, filter, true, t, &ci, fill0, pruneEmpty0);
	}
	/* <---- DEBUG ----- //
	if (cni1 != 0)
	{
	    std::cerr << "[Node::intersectRayImpl] DEBUG: " 
	        "Node before pruning:" << std::endl;
	    printImplDebugInfo(otherImpl, context, true);
	}
	// ----- DEBUG ----> */
	if (pruneEmpty0)
	    pruneEmptyImpl(otherImpl, context);
	/* <---- DEBUG ----- //
	if (cni1 != 0)
	{
	    std::cerr << "[Node::intersectRayImpl] DEBUG: " 
	        "Node after pruning:" << std::endl;
	    printImplDebugInfo(otherImpl, context, true);
	}
	// ----- DEBUG ----> */
	return numNodes;
}

unsigned int Node::castRayGridImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, const Ionflux::GeoUtils::Vector3& 
rayOrigin, const Ionflux::GeoUtils::Vector3& rayDirection, const 
Ionflux::GeoUtils::Vector3& originStepX, const Ionflux::GeoUtils::Vector3& 
originStepY, unsigned int numRaysX, unsigned int numRaysY, 
Ionflux::VolGfx::NodeIntersectionProcessor* processor, 
Ionflux::VolGfx::NodeFilter* filter, bool recursive, double t, bool fill0, 
bool pruneEmpty0)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::castRayGridImpl", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::castRayGridImpl", "Context");
	unsigned int numNodes = 0;
	Ionflux::ObjectBase::IFObject mm;
	Ionflux::GeoUtils::Line3* ray0 = 
	    Ionflux::GeoUtils::Line3::create(rayOrigin, rayDirection);
	mm.addLocalRef(ray0);
	if (processor != 0)
	    processor->setRay(ray0);
	Ionflux::GeoUtils::Vector3 ox;
	// <---- DEBUG ----- //
	std::cerr << "[Node::castRayGridImpl] DEBUG: "
	    "ray = [" << ray0->getValueString() << "], numRays = (" 
	    << numRaysX << ", " << numRaysY << "), originStep = [(" 
	    << originStepX.getValueString() << "), (" 
	    << originStepY.getValueString() << ")]" << std::endl;
	// ----- DEBUG ----> */
	for (unsigned int i = 0; i < numRaysX; i++)
	{
	    Ionflux::GeoUtils::Vector3 oy;
	    for (unsigned int j = 0; j < numRaysY; j++)
	    {
	        ray0->setP(rayOrigin + ox + oy);
	        if (processor != 0)
	            processor->begin();
	        numNodes += intersectRayImpl(otherImpl, context, *ray0, 
	            processor, filter, recursive, t, 0, fill0, pruneEmpty0);
	        if (processor != 0)
	            processor->finish();
	        oy.addIP(originStepY);
	    }
	    ox.addIP(originStepX);
	}
	mm.removeLocalRef(ray0);
	return numNodes;
}

unsigned int Node::castRayGridImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, const Ionflux::GeoUtils::AxisID& axis, 
int targetDepth, double planeOffset, 
Ionflux::VolGfx::NodeIntersectionProcessor* processor, 
Ionflux::VolGfx::NodeFilter* filter, bool recursive, double t, bool fill0, 
bool pruneEmpty0)
{
	Ionflux::ObjectBase::nullPointerCheck(otherImpl, 
	    "Node::castRayGridImpl", "Node implementation");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::castRayGridImpl", "Context");
	int maxNumLevels = context->getMaxNumLevels();
	if ((targetDepth < 0) 
	    || (targetDepth >= maxNumLevels))
	    targetDepth = maxNumLevels - 1;
	// calculate number of rays
	int depth = getImplDepth(otherImpl, context);
	LocInt dm0 = context->getDepthMask(depth).to_ulong();
	LocInt dm1 = context->getDepthMask(targetDepth).to_ulong();
	unsigned int numRaysXY = dm0 / dm1;
	// calculate ray origin, direction, and step
	double ts0 = context->getVoxelSize(targetDepth);
	double po0 = -planeOffset * ts0;
	Ionflux::GeoUtils::Vector3 rayDir(
	    Ionflux::GeoUtils::Vector3::axis(axis));
	Ionflux::GeoUtils::Vector3 originStepX;
	Ionflux::GeoUtils::Vector3 originStepY;
	Ionflux::GeoUtils::Vector3::getOtherAxes(axis, 
	    originStepX, originStepY);
	originStepX.multiplyIP(ts0);
	originStepY.multiplyIP(ts0);
	Ionflux::GeoUtils::Vector3 rayOrigin(
	    getImplLocation(otherImpl, context));
	rayOrigin.addIP(po0 * rayDir + 0.5 * originStepX + 0.5 * originStepY);
	// <---- DEBUG ----- //
	std::cerr << "[Node::castRayGridImpl] DEBUG: "
	    "depth = " << depth << ", targetDepth = " << targetDepth 
	    << ", depthMask0 = " << dm0 << ", depthMask1 = " << dm1 
	    << ", numRaysXY = " << numRaysXY << ", targetVoxelSize = " << ts0 
	    << ", planeOffset = " << po0 << ", rayDirection = (" 
	    << rayDir.getValueString() << "), rayOrigin = (" 
	    << rayOrigin.getValueString() << "), originStepX = (" 
	    << originStepX.getValueString() << "), originStepY = (" 
	    << originStepY.getValueString() << ")" << std::endl;
	// ----- DEBUG ----> */
	return castRayGridImpl(otherImpl, context, rayOrigin, rayDir, 
    originStepX, originStepY, numRaysXY, numRaysXY, 
    processor, filter, recursive, t, fill0, pruneEmpty0);
}

unsigned int Node::mergeImpl(Ionflux::VolGfx::NodeImpl* sourceImpl, 
Ionflux::VolGfx::NodeImpl* targetImpl, Ionflux::VolGfx::Context* context, 
Ionflux::VolGfx::MergePolicyID childPolicy, Ionflux::VolGfx::MergePolicyID 
dataPolicy, Ionflux::VolGfx::NodeFilter* sourceFilter, 
Ionflux::VolGfx::NodeFilter* targetFilter, Ionflux::VolGfx::NodeFilter* 
sourceMergeFilter, bool recursive, bool fill0)
{
	Ionflux::ObjectBase::nullPointerCheck(sourceImpl, 
	    "Node::mergeImpl", "Node implementation (source)");
	Ionflux::ObjectBase::nullPointerCheck(targetImpl, 
	    "Node::mergeImpl", "Node implementation (target)");
	Ionflux::ObjectBase::nullPointerCheck(context, 
	    "Node::mergeImpl", "Context");
	// check filters
	if ((sourceFilter != 0) 
	    && !NodeProcessor::checkFlags(sourceFilter->process(sourceImpl), 
	        NodeFilter::RESULT_PASS))
	{
	    return 0;
	}
	if ((targetFilter != 0) 
	    && !NodeProcessor::checkFlags(targetFilter->process(targetImpl), 
	        NodeFilter::RESULT_PASS))
	{
	    return 0;
	}
	unsigned int numNodes = 1;
	// merge child nodes
	int n0 = context->getMaxNumLeafChildNodesPerNode();
	NodeImplVector niv;
	NodeChildMask takeOver = 0;
	for (int i = 0; i < n0; i++)
	{
	    bool cs0 = sourceImpl->valid.test(i);
	    bool ct0 = targetImpl->valid.test(i);
	    NodeImpl* cnm = 0;
	    bool toCN = false;
	    if (cs0)
	    {
	        if ((!ct0) 
	            || (childPolicy == MERGE_POLICY_TAKE_OVER_SOURCE))
	        {
	            cnm = Ionflux::ObjectBase::nullPointerCheck(
	                getImplChildByOrderIndex(sourceImpl, context, i), 
	                "Node::mergeImpl", "Child node (source)");
	            if ((sourceMergeFilter == 0) 
	                || NodeProcessor::checkFlags(
	                    sourceMergeFilter->process(cnm), 
	                    NodeFilter::RESULT_PASS))
	            {
	                // take over source child node
	                niv.push_back(cnm);
	                takeOver.set(i, true);
	                toCN = true;
	                numNodes++;
	            }
	        }
	        if (!toCN && cs0 && ct0 && recursive)
	        {
	            // merge child nodes recursively
	            NodeImpl* cns = Ionflux::ObjectBase::nullPointerCheck(
	                getImplChildByOrderIndex(sourceImpl, context, i), 
	                "Node::mergeImpl", "Child node (source)");
	            NodeImpl* cnt = Ionflux::ObjectBase::nullPointerCheck(
	                getImplChildByOrderIndex(targetImpl, context, i), 
	                "Node::mergeImpl", "Child node (target)");
	            numNodes += mergeImpl(cns, cnt, context, childPolicy, 
	                dataPolicy, sourceFilter, targetFilter, 
	                sourceMergeFilter, true, fill0);
	        }
	    }
	    if (!toCN)
	    {
	        // keep target child node
	        niv.push_back(0);
	    }
	}
	if (takeOver.any())
	    mergeImplChildNodes(targetImpl, context, niv, fill0);
	// merge data
	NodeDataImpl* ds0 = sourceImpl->data;
	NodeDataImpl* dt0 = targetImpl->data;
	if (ds0 != 0)
	{
	    if ((dt0 == 0) 
	        || (dataPolicy == MERGE_POLICY_TAKE_OVER_SOURCE))
	    {
	        if ((sourceMergeFilter == 0) 
	            || NodeProcessor::checkFlags(
	                sourceMergeFilter->process(sourceImpl), 
	                NodeFilter::RESULT_PASS))
	        {
	            // take over source data
	            if (dt0 != 0)
	                clearImpl(targetImpl, false, true, false);
	            targetImpl->data = ds0;
	            sourceImpl->data = 0;
	        }
	    }
	}
	return numNodes;
}

std::string Node::getImplValueString(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, bool showData)
{
	std::ostringstream status;
	if (otherImpl == 0)
	    status << "<null>";
	else
	{
	    int depth = -1;
	    if (context != 0)
	    {
	        //status << "ctx = [" << context->getValueString() << "]; ";
	        depth = getImplDepth(otherImpl, context);
	    }
	    status << "refCount = " << otherImpl->refCount 
	        << "; loc.x = " << otherImpl->loc.x 
	        << ", loc.y = " << otherImpl->loc.y 
	        << ", loc.z = " << otherImpl->loc.z 
	        << ", valid = " << otherImpl->valid 
	        << ", leaf = " << otherImpl->leaf 
	        << ", parent = " << otherImpl->parent 
	        << ", child = " << otherImpl->child;
	    if (depth != -1)
	        status << ", depth = " << depth;
	    if (isImplLeaf(otherImpl))
	    {
	        status << "; (leaf)";
	    }
	    if (otherImpl->data != 0)
	    {
	        status << "; ";
	        if (showData)
	        {
	            NodeDataImpl* dp = otherImpl->data;
	            status << getDataTypeString(dp->type);
	            if ((dp->type != DATA_TYPE_NULL) 
	                && (dp->type != DATA_TYPE_UNKNOWN))
	            {
	                status << " (" << getDataValueString(dp) << ")";
	            }
	        } else
	            status << otherImpl->data;
	    } else
	        status << "; <null>";
	}
	return status.str();
}

void Node::printImplDebugInfo(Ionflux::VolGfx::NodeImpl* otherImpl, 
Ionflux::VolGfx::Context* context, bool recursive, unsigned int 
indentWidth, char indentChar, unsigned int depth)
{
	std::string indent0 = Ionflux::ObjectBase::getIndent(depth, 
	    indentWidth, indentChar);
	std::string indent1 = Ionflux::ObjectBase::getIndent(depth + 1, 
	    indentWidth, indentChar);
	std::cout << indent0 << "[";
	NodeImpl* p0 = otherImpl->parent;
	if (p0 != 0)
	{
	    int orderIndex = getImplChildOrderIndex(p0, otherImpl);
	    std::cout << "#" << std::setw(3) << std::setfill('0') 
	        << orderIndex << " ";
	}
	std::cout << "Node: ";
	if (otherImpl == 0)
	{
	    std::cout << "<null>]" << std::endl;
	    return;
	}
	std::cout << "impl = " << otherImpl;
	if (p0 != 0)
	    std::cout << ", parent = " << p0;
	std::cout << ", refCount = " << otherImpl->refCount;
	if (context != 0)
	{
	    Ionflux::GeoUtils::Vector3 loc = 
	        getImplLocation(otherImpl, context);
	    double size = getImplVoxelSize(otherImpl, context);
	    int d0 = getImplDepth(otherImpl, context);
	    std::cout << std::endl << indent1 << "depth = " << d0 
	        << ", loc = (" << loc.getValueString() << "), size = " 
	        << size;
	    Region3 r0;
	    NodeID nid0;
	    nid0.loc = otherImpl->loc;
	    nid0.depth = d0;
	    context->getVoxelRegion(nid0, r0);
	    std::cout << std::endl << indent1 << "region = " 
	        << getRegionString(r0);
	}
	std::cout << std::endl;
	std::cout << indent1 << "loc.x  = " << otherImpl->loc.x << std::endl;
	std::cout << indent1 << "loc.y  = " << otherImpl->loc.y << std::endl;
	std::cout << indent1 << "loc.z  = " << otherImpl->loc.z << std::endl;
	if (otherImpl->valid.any())
	    std::cout << indent1 << "valid  = " << otherImpl->valid << std::endl;
	if (otherImpl->leaf.any())
	    std::cout << indent1 << "leaf   = " << otherImpl->leaf << std::endl;
	if (otherImpl->data != 0)
	{
	    // Node data
	    std::cout << indent1 << "data: ";
	    NodeDataImpl* dp = static_cast<NodeDataImpl*>(
	        otherImpl->data);
	    std::cout << getDataTypeString(dp->type) << " (" 
	        << otherImpl->data;
	    if ((dp->type != DATA_TYPE_NULL) 
	        && (dp->type != DATA_TYPE_UNKNOWN))
	    {
	        std::cout << ", " << getDataValueString(dp);
	    }
	    std::cout << ")";
	    if (isImplLeaf(otherImpl))
	        std::cout << "]" << std::endl;
	    else
	        std::cout << std::endl;
	}
	if (!isImplLeaf(otherImpl))
	{
	    // Child nodes.
	    int n0 = getImplNumChildNodes(otherImpl);
	    NodeImpl* cp = otherImpl->child;
	    std::cout << indent1 << "child nodes (" << n0 
	        << ", cp = " << cp << ")";
	    if (recursive 
	        && (cp != 0))
	    {
	        std::cout << ":" << std::endl;
	        for (int i = 0; i < n0; i++)
	        {
	            NodeImpl* ci = &(cp[i]);
	            if (ci != 0)
	            {
	                printImplDebugInfo(ci, context, recursive, 
	                    indentWidth, indentChar, depth + 2);
	            }
	        }
	        std::cout << indent0 << "]" << std::endl;
	    } else
	        std::cout << "]" << std::endl;
	}
}

void Node::setImpl(Ionflux::VolGfx::NodeImpl* newImpl)
{
	if (impl == newImpl)
	    return;
	if (newImpl != 0)
	{
	    if ((newImpl->parent != 0) 
	        && (newImpl->refCount < 1))
	    {
	        /* Node implementation must have a reference from its 
	           parent. */
	        throw IFVGError(getErrorString("Attempt to reference "
	            "node implementation that has a parent and no "
	            "reference.", "setImpl"));
	    }
	    refImpl(newImpl);
	}
	if (impl != 0)
	{
	    if ((impl->parent != 0) 
	        && (impl->refCount < 2))
	    {
	        /* Node implementation must have a reference from its 
	           parent and this node. */
	        throw IFVGError(getErrorString("Attempt to unreference "
	            "node implementation that has a parent and less than "
	            "two references.", "setImpl"));
	    }
	    unrefImpl(impl);
	}
	impl = newImpl;
}

Ionflux::VolGfx::NodeImpl* Node::getImpl() const
{
    return impl;
}

void Node::setContext(Ionflux::VolGfx::Context* newContext)
{
	if (context == newContext)
		return;
    if (newContext != 0)
        addLocalRef(newContext);
	if (context != 0)
		removeLocalRef(context);
	context = newContext;
}

Ionflux::VolGfx::Context* Node::getContext() const
{
    return context;
}

Ionflux::VolGfx::Node& Node::operator=(const Ionflux::VolGfx::Node& other)
{
    if (this == &other)
        return *this;
    setContext(other.context);
    setImpl(other.impl);
	return *this;
}

Ionflux::VolGfx::Node* Node::copy() const
{
    Node* newNode = create();
    *newNode = *this;
    return newNode;
}

Ionflux::VolGfx::Node* Node::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Node*>(other);
}

Ionflux::VolGfx::Node* Node::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Node* newObject = new Node();
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::VolGfx::Node* Node::create(Ionflux::VolGfx::Context* initContext, 
Ionflux::VolGfx::NodeImpl* initImpl, Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Node* newObject = new Node(initContext, initImpl);
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Node::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Node.cpp
 * \brief Voxel tree node implementation.
 */
