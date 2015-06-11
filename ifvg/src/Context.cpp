/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Context.cpp                     Voxel tree context (implementation).
 * ========================================================================== */

#include "ifvg/Context.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <cfloat>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/imageutils.hpp"
#include "geoutils/Vertex3.hpp"
#include "ifvg/IFVGError.hpp"
#include "ifvg/Node.hpp"
#include "ifvg/utils.hpp"

using namespace std;

namespace Ionflux
{

namespace VolGfx
{

ContextClassInfo::ContextClassInfo()
{
	name = "Context";
	desc = "Voxel tree context";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

ContextClassInfo::~ContextClassInfo()
{
}

// static protected member variables
Ionflux::GeoUtils::Vector3* Context::voxelDiag = 0;
Ionflux::GeoUtils::Vector3* Context::voxelNormal = 0;

// public member constants
const int Context::MAX_NUM_LEVELS = 16;
const int Context::DEFAULT_MAX_NUM_LEVELS = 10;
const int Context::DEFAULT_ORDER = 2;
const double Context::DEFAULT_BOX_INSET = 0.05;

// run-time type information instance constants
const ContextClassInfo Context::contextClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Context::CLASS_INFO = &Context::contextClassInfo;

Context::Context()
: depthMask(0), locMask(0), voxelSize(0), maxNumLevels(DEFAULT_MAX_NUM_LEVELS), order(DEFAULT_ORDER), tolerance(DEFAULT_TOLERANCE), validBits(0), maxNumLeafChildNodesPerNode(0), maxNumLeafChildNodesPerDimension(0), scale(1.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	update();
}

Context::Context(const Ionflux::VolGfx::Context& other)
: depthMask(0), locMask(0), voxelSize(0), maxNumLevels(DEFAULT_MAX_NUM_LEVELS), order(DEFAULT_ORDER), tolerance(DEFAULT_TOLERANCE), validBits(0), maxNumLeafChildNodesPerNode(0), maxNumLeafChildNodesPerDimension(0), scale(1.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Context::Context(int initMaxNumLevels, int initOrder, double initScale, 
double initTolerance)
: depthMask(0), locMask(0), voxelSize(0), maxNumLevels(initMaxNumLevels), 
order(initOrder), tolerance(initTolerance), maxNumLeafChildNodesPerNode(0),
maxNumLeafChildNodesPerDimension(0), scale(initScale)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	update();
}

Context::~Context()
{
	clearMasks();
	clearVoxelSize();
}

void Context::clearMasks()
{
	if (depthMask != 0)
	{
	    delete[] depthMask;
	    depthMask = 0;
	}
	if (locMask != 0)
	{
	    delete[] locMask;
	    locMask = 0;
	}
}

void Context::clearVoxelSize()
{
	if (voxelSize != 0)
	{
	    delete[] voxelSize;
	    voxelSize = 0;
	}
}

void Context::clear()
{
	maxNumLevels = DEFAULT_MAX_NUM_LEVELS;
	order = DEFAULT_ORDER;
	maxNumLeafChildNodesPerNode = 0;
	maxNumLeafChildNodesPerDimension = 0;
	clearMasks();
	clearVoxelSize();
}

void Context::update()
{
	clearMasks();
	clearVoxelSize();
	if (maxNumLevels > MAX_NUM_LEVELS)
	{
	    std::ostringstream status;
	    status << "Maximum number of levels exceeds allowed "
	        "maximum number of levels (maxNumLevels: " << maxNumLevels 
	        << ", max. allowed: " << MAX_NUM_LEVELS << ")";
	    throw IFVGError(getErrorString(status.str(), "update"));
	}
	maxNumLeafChildNodesPerNode = order * order * order;
	maxNumLeafChildNodesPerDimension = 0;
	if (maxNumLevels > 1)
	{
	    maxNumLeafChildNodesPerDimension = order;
	    for (int i = 0; i < maxNumLevels - 2; i++)
	        maxNumLeafChildNodesPerDimension *= order;
	}
	// Initialize bit masks and voxel size buffer.
	depthMask = new NodeLoc[maxNumLevels];
	if (depthMask == 0)
	{
	    throw IFVGError("Context::update"
	        "Could not allocate depth masks.");
	}
	locMask = new NodeLoc[maxNumLevels];
	if (locMask == 0)
	{
	    throw IFVGError("Context::update"
	        "Could not allocate node location masks.");
	}
	voxelSize = new double[maxNumLevels];
	if (voxelSize == 0)
	{
	    throw IFVGError("Context::update"
	        "Could not allocate voxel size buffer.");
	}
	LocInt cm = 0;
	double vs = 1.;
	for (int i = 0; i < maxNumLevels; i++)
	{
	    LocInt cb = 1 << (maxNumLevels - i - 1);
	    cm |= cb;
	    depthMask[i] = cb;
	    locMask[i] = cm;
	    voxelSize[i] = vs * scale;
	    vs /= order;
	}
	validBits = cm;
}

Ionflux::VolGfx::NodeLoc Context::createLoc(double v, bool checkBounds0)
{
	double v0 = v / scale;
	if (checkBounds0 
	    && ((v0 < 0.) || (v0 >= 1.)))
	{
	    std::ostringstream status;
	    status << "Location value out of bounds (v = " << v << ")";
	    throw IFVGError(getErrorString(status.str(), "createLoc"));
	}
	return static_cast<NodeLoc>(v * maxNumLeafChildNodesPerDimension);
}

Ionflux::VolGfx::NodeLoc3 Context::createLoc(double x, double y, double z, 
bool checkBounds0)
{
	double x0 = x / scale;
	double y0 = y / scale;
	double z0 = z / scale;
	if (checkBounds0 
	    && ((x0 < 0.) || (x0 >= 1.) 
	        || (y0 < 0.) || (y0 >= 1.)
	        || (z0 < 0.) || (z0 >= 1.)))
	{
	    std::ostringstream status;
	    status << "Location value out of bounds (x = " << x 
	        << ", y = " << y << ", z = " << z 
	        << ", scale = " << scale << ")";
	    throw IFVGError(getErrorString(status.str(), "createLoc"));
	}
	NodeLoc3 result;
	result.x = static_cast<NodeLoc>(x0 * maxNumLeafChildNodesPerDimension);
	result.y = static_cast<NodeLoc>(y0 * maxNumLeafChildNodesPerDimension);
	result.z = static_cast<NodeLoc>(z0 * maxNumLeafChildNodesPerDimension);
	return result;
}

Ionflux::VolGfx::NodeLoc3 Context::createLoc(const 
Ionflux::GeoUtils::Vector3& v, bool checkBounds0)
{
	// TODO: Implementation.
	return createLoc(v.getElement(0), v.getElement(1), v.getElement(2), 
    checkBounds0);
}

Ionflux::VolGfx::NodeLoc3 Context::createLoc(const Ionflux::Mapping::Point&
p, bool checkBounds0)
{
	// TODO: Implementation.
	return createLoc(p.getX(), p.getY(), p.getZ(), checkBounds0);
}

Ionflux::VolGfx::Region3 Context::createRegion(const 
Ionflux::GeoUtils::Range3& r)
{
	Region3 result;
	if (!checkRange(r))
	{
	    std::ostringstream status;
	    status << "Range out of bounds: [" << r.getValueString() << "]";
	    throw IFVGError(getErrorString(status.str(), "createRegion"));
	}
	result.l0 = createLoc(r.getRMin());
	result.l1 = createLoc(r.getRMax());
	return result;
}

bool Context::locEqual(const Ionflux::VolGfx::NodeLoc& loc0, const 
Ionflux::VolGfx::NodeLoc& loc1, int maxDepth)
{
	if ((maxDepth > (maxNumLevels - 1))
	    || (maxDepth < 0))
	    maxDepth = maxNumLevels - 1;
	Ionflux::ObjectBase::nullPointerCheck(locMask, this, "locEqual", 
	    "Location mask");
	NodeLoc m0 = locMask[maxDepth];
	if ((loc0 & validBits & m0) == (loc1 & validBits & m0))
	    return true;
	return false;
}

bool Context::locEqual(const Ionflux::VolGfx::NodeLoc3& loc0, const 
Ionflux::VolGfx::NodeLoc3& loc1, int maxDepth)
{
	if ((maxDepth > (maxNumLevels - 1))
	    || (maxDepth < 0))
	    maxDepth = maxNumLevels - 1;
	Ionflux::ObjectBase::nullPointerCheck(locMask, this, "locEqual", 
	    "Location mask");
	NodeLoc m0 = locMask[maxDepth];
	if (((loc0.x & validBits & m0) == (loc1.x & validBits & m0)) 
	    && ((loc0.y & validBits & m0) == (loc1.y & validBits & m0)) 
	    && ((loc0.z & validBits & m0) == (loc1.z & validBits & m0)))
	    return true;
	return false;
}

int Context::getChildOrderIndex(const Ionflux::VolGfx::NodeLoc3& loc, int 
depth) const
{
	if (order != 2)
	{
	    throw IFVGError(getErrorString("Location codes not "
	        "supported for tree order != 2.", 
	        "getChildOrderIndex"));
	}
	if (depth == 0)
	{
	    // Nodes on level 0 are never child nodes.
	    /* <---- DEBUG ----- //
	    std::cout << "[Context::getChildOrderIndex] DEBUG: "
	        << "Node on level 0 is not a child node (loc = " 
	        << getLocString(loc) << ")." << std::endl;
	    // <---- DEBUG ----- */
	    return Node::CHILD_INDEX_INVALID;
	}
	NodeLoc m0 = getDepthMask(depth);
	int n0 = maxNumLevels - depth - 1;
	/* <---- DEBUG ----- //
	std::cout << "[Context::getChildOrderIndex] DEBUG: "
	    << "loc = " << getLocString(loc) << ", depth = " 
	    << depth << "; location bits: (" 
	    << ((loc.x & m0) >> n0).to_ulong() << ", " 
	    << ((loc.y & m0) >> n0).to_ulong() << ", " 
	    << ((loc.z & m0) >> n0).to_ulong() << ")." << std::endl;
	// <---- DEBUG ----- */
	LocInt oi = (((loc.x & m0) >> n0) 
	    | (((loc.y & m0) >> n0) << 1)
	    | (((loc.z & m0) >> n0) << 2)).to_ulong();
	/* <---- DEBUG ----- //
	std::cout << "[Context::getChildOrderIndex] DEBUG: "
	    << "loc = " << getLocString(loc) << ", depth = " 
	    << depth << ", orderIndex = " << oi << "." << std::endl;
	// <---- DEBUG ----- */
	if (oi >= maxNumLeafChildNodesPerNode)
	{
	    std::ostringstream status;
	    status << "Child node index out of range: " << oi;
	    throw IFVGError(getErrorString(status.str(), 
	        "getChildOrderIndex"));
	}
	return oi;
}

int Context::getCommonAncestorLevel(const Ionflux::VolGfx::NodeLoc3& loc0, 
const Ionflux::VolGfx::NodeLoc3& loc1, int maxDepth) const
{
	if (order != 2)
	{
	    throw IFVGError(getErrorString("Location codes not "
	        "supported for tree order != 2.", 
	        "getCommonAncestorLevel"));
	}
	if ((maxDepth < 0) 
	    || (maxDepth >= maxNumLevels))
	    maxDepth = maxNumLevels - 1;
	/* <---- DEBUG ----- //
	std::cout << "[Context::getCommonAncestorLevel] DEBUG: "
	    "loc0 = " << getLocString(loc0) << ", loc1 = " 
	    << getLocString(loc1) << ", maxDepth = " << maxDepth 
	    << std::endl;
	// <---- DEBUG ----- */
	NodeLoc3 rx;
	rx.x = loc0.x ^ loc1.x;
	rx.y = loc0.y ^ loc1.y;
	rx.z = loc0.z ^ loc1.z;
	NodeLoc tl = rx.x | rx.y | rx.z;
	/* <---- DEBUG ----- //
	std::cout << "[Node::getCommonAncestorLevel] DEBUG: "
	    "rx = " << getLocString(rx) << ", tl = " << getLocString(tl) 
	    << std::endl;
	// <---- DEBUG ----- */
	int n0 = maxNumLeafChildNodesPerNode;
	int i = 0;
	bool found = false;
	while ((i < n0) 
	    && !found)
	{
	    if (tl.test(maxNumLevels - i - 1))
	        found = true;
	    i++;
	}
	int l0 = 0;
	if ((found) && (i >= 2))
	    l0 = i - 2;
	if ((maxDepth > 0) 
	    && (maxDepth < l0))
	    l0 = maxDepth;
	/* <---- DEBUG ----- //
	std::cout << "[Node::getCommonAncestorLevel] DEBUG: "
	    "target level = " << l0 << std::endl;
	// <---- DEBUG ----- */
	return l0;
}

int Context::getCommonAncestorLevel(const Ionflux::VolGfx::Region3& region,
int maxDepth) const
{
	// TODO: Implementation.
	return getCommonAncestorLevel(region.l0, region.l1, maxDepth);
}

Ionflux::VolGfx::NodeLoc Context::getDepthMask(int depth) const
{
	Ionflux::ObjectBase::nullPointerCheck(depthMask, this, "getDepthMask", 
	    "Depth mask");
	if ((depth < 0) || (depth > (maxNumLevels - 1)))
	{
	    std::ostringstream status;
	    status << "Depth out of range (maxNumLevels: " 
	        << maxNumLevels << ", depth: " << depth << ")";
	    throw IFVGError(getErrorString(status.str(), "getDepthMask"));
	}
	return depthMask[depth];
}

Ionflux::VolGfx::NodeLoc Context::getLocMask(int depth)
{
	Ionflux::ObjectBase::nullPointerCheck(depthMask, this, "getLocMask", 
	    "Location mask");
	if ((depth < 0) || (depth > (maxNumLevels - 1)))
	{
	    std::ostringstream status;
	    status << "Depth out of range (maxNumLevels: " 
	        << maxNumLevels << ", depth: " << depth << ")";
	    throw IFVGError(getErrorString(status.str(), "getLocMask"));
	}
	return locMask[depth];
}

double Context::getVoxelSize(int depth)
{
	Ionflux::ObjectBase::nullPointerCheck(voxelSize, this, "getVoxelSize", 
	    "Voxel size buffer");
	if (depth < 0)
	    depth = 0;
	if (depth >= maxNumLevels)
	{
	    double s0 = voxelSize[maxNumLevels - 1];
	    int i = maxNumLevels - 1;
	    while (i < depth)
	    {
	        s0 /= order;
	        i++;
	    }
	    return s0;
	}
	return voxelSize[depth];
}

double Context::getMinLeafSize()
{
	// TODO: Implementation.
	return getVoxelSize(maxNumLevels - 1);
}

void Context::getLocation(const Ionflux::VolGfx::NodeLoc3& loc, 
Ionflux::GeoUtils::Vector3& target)
{
	double leafSize = getMinLeafSize();
	target.setElements(leafSize * loc.x.to_ulong(), 
	    leafSize * loc.y.to_ulong(), 
	    leafSize * loc.z.to_ulong());
}

Ionflux::GeoUtils::Vector3 Context::getLocation0(const 
Ionflux::VolGfx::NodeLoc3& loc)
{
	Ionflux::GeoUtils::Vector3 l0;
	getLocation(loc, l0);
	return l0;
}

void Context::getVoxelLocation(const Ionflux::VolGfx::NodeLoc3& loc, int 
depth, Ionflux::GeoUtils::Vector3& target)
{
	double leafSize = getMinLeafSize();
	LocInt lm0 = getLocMask(depth).to_ulong();
	target.setElements(leafSize * (loc.x.to_ulong() & lm0), 
	    leafSize * (loc.y.to_ulong() & lm0), 
	    leafSize * (loc.z.to_ulong() & lm0));
}

Ionflux::GeoUtils::Vector3 Context::getVoxelLocation0(const 
Ionflux::VolGfx::NodeLoc3& loc, int depth)
{
	Ionflux::GeoUtils::Vector3 l0;
	getVoxelLocation(loc, depth, l0);
	return l0;
}

void Context::getVoxelLocation(const Ionflux::VolGfx::NodeID& node, 
Ionflux::GeoUtils::Vector3& target)
{
	getVoxelLocation(node.loc, node.depth, target);
}

void Context::getVoxelRange(const Ionflux::VolGfx::NodeLoc3& loc, int 
depth, Ionflux::GeoUtils::Range3& target)
{
	Ionflux::GeoUtils::Vector3 lv0;
	getVoxelLocation(loc, depth, lv0);
	double s0 = getVoxelSize(depth);
	target.setBounds(lv0, s0);
}

void Context::getVoxelRange(Ionflux::VolGfx::NodeID node, 
Ionflux::GeoUtils::Range3& target)
{
	getVoxelRange(node.loc, node.depth, target);
}

void Context::getVoxelRegion(const Ionflux::VolGfx::NodeLoc3& loc, int 
depth, Ionflux::VolGfx::Region3& target, bool includeMaxBoundary)
{
	if ((depth < 0) 
	    || (depth >= maxNumLevels))
	    depth = maxNumLevels - 1;
	LocInt offset0 = getDepthMask(depth).to_ulong();
	LocInt offset1 = 1;
	if (includeMaxBoundary)
	    offset1 = 0;
	target.l0 = loc;
	target.l1.x = loc.x.to_ulong() + offset0 - offset1;
	target.l1.y = loc.y.to_ulong() + offset0 - offset1;
	target.l1.z = loc.z.to_ulong() + offset0 - offset1;
}

void Context::getVoxelRegion(Ionflux::VolGfx::NodeID node, 
Ionflux::VolGfx::Region3& target, bool includeMaxBoundary)
{
	getVoxelRegion(node.loc, node.depth, target, includeMaxBoundary);
}

bool Context::checkLoc(const Ionflux::VolGfx::NodeLoc& loc, int offset)
{
	LocInt l0 = loc.to_ulong();
	LocInt maxLoc = getLocMask(maxNumLevels - 1).to_ulong();
	if (offset >= 0)
	{
	    if (l0 + offset > maxLoc)
	        return false;
	} else
	if (offset < 0)
	{
	    if (l0 < -offset)
	        return false;
	}
	return true;
}

bool Context::checkLoc(const Ionflux::GeoUtils::Vector3& v)
{
	Ionflux::GeoUtils::Range3 r0;
	NodeID nid0;
	nid0.loc = Ionflux::VolGfx::createLoc(0, 0, 0);
	nid0.depth = 0;
	getVoxelRange(nid0, r0);
	return r0.isInRange(v);
}

bool Context::checkLoc(const Ionflux::VolGfx::NodeLoc3& loc, int offsetX, 
int offsetY, int offsetZ)
{
	bool result = checkLoc(loc.x, offsetX) 
	    && checkLoc(loc.y, offsetY) 
	    && checkLoc(loc.z, offsetZ);
	// <---- DEBUG ----- //
	if (!result)
	{
	    std::cout << "[Context::checkLoc] DEBUG: "
	        "Location out of bounds (loc = " << getLocString(loc) 
	            << ", offset = (" << offsetX << ", " << offsetY 
	            << ", " << offsetZ << "))." << std::endl;
	}
	// <---- DEBUG ----- */
	return result;
}

bool Context::checkRegion(const Ionflux::VolGfx::Region3& region, int 
offsetX, int offsetY, int offsetZ)
{
	// TODO: Implementation.
	return checkLoc(region.l0, offsetX, offsetY, offsetZ) 
    && checkLoc(region.l1, offsetX, offsetY, offsetZ);
}

bool Context::checkRange(const Ionflux::GeoUtils::Range3& range, const 
Ionflux::VolGfx::NodeLoc3& loc, int depth)
{
	Ionflux::GeoUtils::Range3 r0;
	getVoxelRange(loc, depth, r0);
	Ionflux::GeoUtils::RangeCompResult result = r0.compare(range, 0.);
	if (result == Ionflux::GeoUtils::RANGE_FIRST_CONTAINS)
	    return true;
	return false;
}

bool Context::checkRange(const Ionflux::GeoUtils::Range3& range, 
Ionflux::VolGfx::NodeID node)
{
	// TODO: Implementation.
	return checkRange(range, node.loc, node.depth);
}

bool Context::checkRange(const Ionflux::GeoUtils::Range3& range)
{
	NodeLoc3 l0;
	l0.x = 0;
	l0.y = 0;
	l0.z = 0;
	return checkRange(range, l0, 0);
}

bool Context::checkDepthRange(int depth, int minDepth, int maxDepth)
{
	if (minDepth < 0)
	    minDepth = 0;
	if (depth < minDepth)
	    return false;
	int n0 = getMaxNumLevels();
	if ((maxDepth < 0) 
	    || (maxDepth >= n0))
	    maxDepth = n0 - 1;
	if (minDepth > maxDepth)
	    return false;
	if (depth > maxDepth)
	    return false;
	return true;;
}

void Context::getContainingNode(const Ionflux::GeoUtils::Range3& range, 
Ionflux::VolGfx::NodeID& target)
{
	if (!checkRange(range))
	{
	    std::ostringstream status;
	    status << "Range out of bounds: [" 
	        << range.getValueString() << "]";
	    throw IFVGError(getErrorString(status.str(), 
	        "getContainingNode"));
	}
	Region3 r0;
	r0.l0 = createLoc(range.getRMin());
	r0.l1 = createLoc(range.getRMax());
	target.loc = r0.l0;
	target.depth = getCommonAncestorLevel(r0.l0, r0.l1);
}

void Context::initTriangleVoxelizationData(const Ionflux::GeoUtils::Face& 
face, Ionflux::VolGfx::TriangleVoxelizationData& target, 
Ionflux::VolGfx::SeparabilityID sep, int depth, bool checkBounds0)
{
	if (!face.isTri())
	{
	    throw IFVGError(getErrorString("initTriangleVoxelizationData", 
	        "Face is not a triangle."));
	}
	if (depth < 0)
	    depth = maxNumLevels - 1;
	Ionflux::GeoUtils::Vertex3* v0 = 
	    Ionflux::ObjectBase::nullPointerCheck(face.getVertexData(0), 
	        this, "initTriangleVoxelizationData", "Vertex (0)");
	Ionflux::GeoUtils::Vertex3* v1 = 
	    Ionflux::ObjectBase::nullPointerCheck(face.getVertexData(1), 
	        this, "initTriangleVoxelizationData", "Vertex (1)");
	Ionflux::GeoUtils::Vertex3* v2 = 
	    Ionflux::ObjectBase::nullPointerCheck(face.getVertexData(2), 
	        this, "initTriangleVoxelizationData", "Vertex (2)");
	// triangle data
	target.tri.v0 = v0->getVector();
	target.tri.v1 = v1->getVector();
	target.tri.v2 = v2->getVector();
	Ionflux::GeoUtils::Vector3 n0 = 
	    (target.tri.v1 - target.tri.v0).cross(
	        target.tri.v2 - target.tri.v0).normalize();
	target.plane.p = target.tri.v0;
	target.plane.normal = n0;
	// separability factors
	target.sep = sep;
	double s0 = getVoxelSize(depth);
	target.voxelSize = s0;
	if (sep == SEPARABILITY_26)
	{
	    Ionflux::GeoUtils::Vector3* d0 = getMatchingVoxelDiag(n0);
	    target.t = 0.5 * s0 * SQRT_3 * n0.angleCos(*d0);
	    target.r_c = 0.5 * SQRT_3 * s0;
	} else
	if (sep == SEPARABILITY_6)
	{
	    Ionflux::GeoUtils::Vector3* n1 = getMatchingVoxelNormal(n0);
	    target.t = 0.5 * s0 * n0.angleCos(*n1);
	    target.r_c = 0.5 * s0;
	}
	// offset planes
	// upper offset plane
	target.planeU.p = target.tri.v0 + (n0 * target.t);
	target.planeU.normal = n0;
	// lower offset plane
	target.planeL.p = target.tri.v0 - (n0 * target.t);
	target.planeL.normal = n0.flip();
	// edge shapes
	// edge cylinder (0)
	target.cylE0.center = (target.tri.v1 + target.tri.v0) * 0.5;
	target.cylE0.direction = (target.tri.v1 - target.tri.v0).normalize();
	target.cylE0.length = (target.tri.v1 - target.tri.v0).length();
	target.cylE0.radius = target.r_c;
	// edge cylinder (1)
	target.cylE1.center = (target.tri.v2 + target.tri.v1) * 0.5;
	target.cylE1.direction = (target.tri.v2 - target.tri.v1).normalize();
	target.cylE1.length = (target.tri.v2 - target.tri.v1).length();
	target.cylE1.radius = target.r_c;
	// edge cylinder (2)
	target.cylE2.center = (target.tri.v0 + target.tri.v2) * 0.5;
	target.cylE2.direction = (target.tri.v0 - target.tri.v2).normalize();
	target.cylE2.length = (target.tri.v0 - target.tri.v2).length();
	target.cylE2.radius = target.r_c;
	// edge plane (0)
	target.planeE0.p = target.tri.v0;
	target.planeE0.normal = target.cylE0.direction.cross(
	    n0).normalize();
	// edge plane (1)
	target.planeE1.p = target.tri.v1;
	target.planeE1.normal = target.cylE1.direction.cross(
	    n0).normalize();
	// edge plane (2)
	target.planeE2.p = target.tri.v2;
	target.planeE2.normal = target.cylE2.direction.cross(
	    n0).normalize();
	// containing node
	Ionflux::GeoUtils::Range3 bb0;
	bb0.setBounds(target.tri.v0);
	bb0.extend(target.tri.v1);
	bb0.extend(target.tri.v2);
	bb0.extend(target.r_c);
	if (!checkRange(bb0))
	{
	    if (checkBounds0)
	    {
	        Ionflux::GeoUtils::Range3 bb1;
	        bb1.setBounds(target.tri.v0);
	        bb1.extend(target.tri.v1);
	        bb1.extend(target.tri.v2);
	        std::ostringstream status;
	        status << "Triangle voxelization not contained in voxel tree "
	            "(depth = " << depth << ", voxelSize = " 
	            << target.voxelSize << ", tri.bb = [" << bb1.getValueString() 
	            << "], tri_vox.bb = [" << bb0.getValueString() 
	            << "], tri = [" << getTriangleString(target.tri) 
	            << "], r_c = " << target.r_c << ")";
	        throw IFVGError(getErrorString(status.str(), 
	            "initTriangleVoxelizationData"));
	    } else
	    {
	        // set containing node to root
	        target.node.depth = 0;
	    }
	} else
	    getContainingNode(bb0, target.node);
}

void Context::printDebugInfo() const
{
	std::cout << "maxNumLevels = " << maxNumLevels << ", order = " 
	    << order << ", scale = " << scale << ", tolerance = " 
	    << tolerance << ", maxNumLeafChildNodesPerNode = " 
	        << maxNumLeafChildNodesPerNode 
	    << ", maxNumLeafChildNodesPerDimension = " 
	        << maxNumLeafChildNodesPerDimension << std::endl;
	std::cout << "valid bits: " << validBits << std::endl;
	std::cout << "depth masks: " << std::endl;
	if (depthMask != 0)
	{
	    for (int i = 0; i < maxNumLevels; i++)
	    {
	        std::cout << "  [" << std::setw(3) << std::setfill('0') 
	            << i << "] " << depthMask[i] << std::endl;
	    }
	} else
	{
	    std::cout << "  <null>" << std::endl;
	}
	std::cout << "location masks:" << std::endl;
	if (locMask != 0)
	{
	    for (int i = 0; i < maxNumLevels; i++)
	    {
	        std::cout << "  [" << std::setw(3) << std::setfill('0') 
	            << i << "] " << locMask[i] << std::endl;
	    }
	} else
	{
	    std::cout << "  <null>" << std::endl;
	}
}

void Context::getVoxelMesh(Ionflux::VolGfx::NodeID node, 
Ionflux::GeoUtils::Mesh& target, double boxInset, 
Ionflux::Altjira::ColorSet* colors, unsigned int colorOffset, int 
colorIndex)
{
	Ionflux::GeoUtils::Range3 r0;
	getVoxelRange(node, r0);
	if (boxInset != 0.)
	{
	    double s0 = getMinLeafSize();
	    r0.extend(-boxInset * s0 * node.depth);
	}
	Ionflux::GeoUtils::Mesh* cm0 = r0.getMesh();
	addLocalRef(cm0);
	if (colors != 0)
	{
	    unsigned int nc0 = colors->getNumColors();
	    if (nc0 > 0)
	    {
	        unsigned int d0 = static_cast<unsigned int>(node.depth);
	        unsigned int ci0 = d0 + colorOffset;
	        if (colorIndex >= 0)
	            ci0 = colorIndex;
	        Ionflux::Altjira::Color* c0 = 
	            Ionflux::ObjectBase::nullPointerCheck(
	                colors->getColor(ci0 % nc0), this, 
	                "getVoxelMesh", "Color");
	        Ionflux::GeoUtils::Vector4 cv0;
	        Ionflux::GeoUtils::colorToVec(*c0, cv0);
	        cm0->setFaceVertexColors(cv0);
	    }
	}
	target.merge(*cm0);
	removeLocalRef(cm0);
}

void Context::getVoxelVertexAttributes(Ionflux::VolGfx::NodeID node, 
Ionflux::GeoUtils::VertexAttribute* positionTarget, 
Ionflux::GeoUtils::VertexAttribute* colorTarget, 
Ionflux::GeoUtils::VertexAttribute* normalTarget, 
Ionflux::GeoUtils::NFaceTypeID nFaceType, double boxInset, 
Ionflux::Altjira::Color* color, Ionflux::GeoUtils::Vector* positionOffset, 
Ionflux::GeoUtils::Vector* positionScale, Ionflux::VolGfx::FaceMaskInt 
faces, Ionflux::VolGfx::FaceMaskInt flipNormals)
{
	if (faces == FACE_UNDEFINED)
	{
	    // Nothing to be done.
	    return;
	}
	Ionflux::GeoUtils::Range3 r0;
	getVoxelRange(node, r0);
	if (boxInset != 0.)
	{
	    double s0 = getMinLeafSize();
	    r0.extend(-boxInset * s0 * node.depth);
	}
	// box vertices
	Ionflux::GeoUtils::Vector3 v0(r0.getValue(0., 0., 0));
	Ionflux::GeoUtils::Vector3 v1(r0.getValue(1., 0., 0));
	Ionflux::GeoUtils::Vector3 v2(r0.getValue(1., 1., 0));
	Ionflux::GeoUtils::Vector3 v3(r0.getValue(0., 1., 0));
	Ionflux::GeoUtils::Vector3 v4(r0.getValue(0., 0., 1));
	Ionflux::GeoUtils::Vector3 v5(r0.getValue(1., 0., 1));
	Ionflux::GeoUtils::Vector3 v6(r0.getValue(1., 1., 1));
	Ionflux::GeoUtils::Vector3 v7(r0.getValue(0., 1., 1));
	if (positionScale != 0)
	{
	    v0.multiplyIP(*positionScale);
	    v1.multiplyIP(*positionScale);
	    v2.multiplyIP(*positionScale);
	    v3.multiplyIP(*positionScale);
	    v4.multiplyIP(*positionScale);
	    v5.multiplyIP(*positionScale);
	    v6.multiplyIP(*positionScale);
	    v7.multiplyIP(*positionScale);
	}
	if (positionOffset != 0)
	{
	    v0.addIP(*positionOffset);
	    v1.addIP(*positionOffset);
	    v2.addIP(*positionOffset);
	    v3.addIP(*positionOffset);
	    v4.addIP(*positionOffset);
	    v5.addIP(*positionOffset);
	    v6.addIP(*positionOffset);
	    v7.addIP(*positionOffset);
	}
	unsigned int numQuads = 0;
	unsigned int numVerts = 0;
	if (positionTarget != 0)
	{
	    // vertex positions
	    unsigned int ne0 = positionTarget->getNumElements();
	    if (nFaceType == Ionflux::GeoUtils::NFace::TYPE_FACE)
	    {
	        /* triangle faces
	           6 faces * 2 triangles * 3 vertices = 36 vertices */
	        numQuads = getNumFacesSet(faces);
	        if (numQuads > 0)
	        {
	            numVerts = numQuads * 2 * 3;
	            unsigned int offset0 = 0;
	            bool reverse = false;
	            positionTarget->resize(ne0 + numVerts, 3, 
	                Ionflux::GeoUtils::DATA_TYPE_FLOAT, 2.);
	            if (checkFaceMask(faces, FACE_Z0))
	            {
	                // quad (0, Z0)
	                reverse = checkFaceMask(flipNormals, FACE_Z0);
	                setVertexAttributeTrianglePos(*positionTarget, ne0, 
	                    v0, v2, v1, reverse);
	                setVertexAttributeTrianglePos(*positionTarget, ne0 + 3, 
	                    v0, v3, v2, reverse);
	                offset0 += 6;
	            }
	            if (checkFaceMask(faces, FACE_Z1))
	            {
	                // quad (1, Z1)
	                reverse = checkFaceMask(flipNormals, FACE_Z1);
	                setVertexAttributeTrianglePos(*positionTarget, 
	                    ne0 + offset0, 
	                    v4, v5, v6, reverse);
	                setVertexAttributeTrianglePos(*positionTarget, 
	                    ne0 + offset0 + 3, 
	                    v4, v6, v7, reverse);
	                offset0 += 6;
	            }
	            if (checkFaceMask(faces, FACE_Y0))
	            {
	                // quad (2, Y0)
	                reverse = checkFaceMask(flipNormals, FACE_Y0);
	                setVertexAttributeTrianglePos(*positionTarget, 
	                    ne0 + offset0, 
	                    v0, v1, v5, reverse);
	                setVertexAttributeTrianglePos(*positionTarget, 
	                    ne0 + offset0 + 3, 
	                    v0, v5, v4, reverse);
	                offset0 += 6;
	            }
	            if (checkFaceMask(faces, FACE_X1))
	            {
	                // quad (3, X1)
	                reverse = checkFaceMask(flipNormals, FACE_X1);
	                setVertexAttributeTrianglePos(*positionTarget, 
	                    ne0 + offset0, 
	                    v1, v2, v6, reverse);
	                setVertexAttributeTrianglePos(*positionTarget, 
	                    ne0 + offset0 + 3, 
	                    v1, v6, v5, reverse);
	                offset0 += 6;
	            }
	            if (checkFaceMask(faces, FACE_X0))
	            {
	                // quad (4, X0)
	                reverse = checkFaceMask(flipNormals, FACE_X0);
	                setVertexAttributeTrianglePos(*positionTarget, 
	                    ne0 + offset0, 
	                    v0, v4, v3, reverse);
	                setVertexAttributeTrianglePos(*positionTarget, 
	                    ne0 + offset0 + 3, 
	                    v3, v4, v7, reverse);
	                offset0 += 6;
	            }
	            if (checkFaceMask(faces, FACE_Y1))
	            {
	                // quad (5, Y1)
	                reverse = checkFaceMask(flipNormals, FACE_Y1);
	                setVertexAttributeTrianglePos(*positionTarget, 
	                    ne0 + offset0, 
	                    v2, v7, v6, reverse);
	                setVertexAttributeTrianglePos(*positionTarget, 
	                    ne0 + offset0 + 3, 
	                    v2, v3, v7, reverse);
	            }
	        }
	    } else
	    if (nFaceType == Ionflux::GeoUtils::NFace::TYPE_EDGE)
	    {
	        /* edges
	           12 edges * 2 vertices = 24 vertices */
	        positionTarget->resize(ne0 + 24, 3, 
	            Ionflux::GeoUtils::DATA_TYPE_FLOAT, 2.);
	        // quad (0, Z0)
	        positionTarget->setData(ne0, v0);
	        positionTarget->setData(ne0 + 1, v3);
	        positionTarget->setData(ne0 + 2, v3);
	        positionTarget->setData(ne0 + 3, v2);
	        positionTarget->setData(ne0 + 4, v2);
	        positionTarget->setData(ne0 + 5, v1);
	        positionTarget->setData(ne0 + 6, v1);
	        positionTarget->setData(ne0 + 7, v0);
	        // quad (1, Z1)
	        positionTarget->setData(ne0 + 8, v4);
	        positionTarget->setData(ne0 + 9, v5);
	        positionTarget->setData(ne0 + 10, v5);
	        positionTarget->setData(ne0 + 11, v6);
	        positionTarget->setData(ne0 + 12, v6);
	        positionTarget->setData(ne0 + 13, v7);
	        positionTarget->setData(ne0 + 14, v7);
	        positionTarget->setData(ne0 + 15, v4);
	        // Z-edges
	        positionTarget->setData(ne0 + 16, v0);
	        positionTarget->setData(ne0 + 17, v4);
	        positionTarget->setData(ne0 + 18, v1);
	        positionTarget->setData(ne0 + 19, v5);
	        positionTarget->setData(ne0 + 20, v2);
	        positionTarget->setData(ne0 + 21, v6);
	        positionTarget->setData(ne0 + 22, v3);
	        positionTarget->setData(ne0 + 23, v7);
	    }
	}
	if ((colorTarget != 0) 
	    && (color != 0))
	{
	    // vertex colors
	    Ionflux::GeoUtils::Vector4 cv0;
	    Ionflux::GeoUtils::colorToVec(*color, cv0);
	    unsigned int ne0 = colorTarget->getNumElements();
	    if (nFaceType == Ionflux::GeoUtils::NFace::TYPE_FACE)
	    {
	        /* triangle faces
	           6 faces * 2 triangles * 3 vertices = 36 vertices */
	        if (numVerts == 0)
	        {
	            throw IFVGError(getErrorString(
	                "Number of vertices is 0.", 
	                "getVoxelVertexAttributes"));
	        }
	        colorTarget->resize(ne0 + numVerts, 4, 
	            Ionflux::GeoUtils::DATA_TYPE_FLOAT, 2.);
	        for (unsigned int i = 0; i < numVerts; i++)
	            colorTarget->setData(ne0 + i, cv0);
	    } else
	    if (nFaceType == Ionflux::GeoUtils::NFace::TYPE_EDGE)
	    {
	        /* edges
	           12 edges * 2 vertices = 24 vertices */
	        colorTarget->resize(ne0 + 24, 4, 
	            Ionflux::GeoUtils::DATA_TYPE_FLOAT, 2.);
	        for (unsigned int i = 0; i < 24; i++)
	            colorTarget->setData(ne0 + i, cv0);
	    }
	}
	if (normalTarget != 0)
	{
	    // vertex normals
	    unsigned int ne0 = normalTarget->getNumElements();
	    if (nFaceType == Ionflux::GeoUtils::NFace::TYPE_FACE)
	    {
	        /* triangle faces
	           6 faces * 2 triangles * 3 vertices = 36 vertices */
	        unsigned int offset0 = 0;
	        if (numVerts == 0)
	        {
	            throw IFVGError(getErrorString(
	                "Number of vertices is 0.", 
	                "getVoxelVertexAttributes"));
	        }
	        normalTarget->resize(ne0 + numVerts, 3, 
	            Ionflux::GeoUtils::DATA_TYPE_FLOAT, 2.);
	        Ionflux::GeoUtils::Vector3 cn0;
	        if (checkFaceMask(faces, FACE_Z0))
	        {
	            // quad (0, Z0)
	            if (!checkFaceMask(flipNormals, FACE_Z0))
	                cn0 = Ionflux::GeoUtils::Vector3::E_Z.flip();
	            else
	                cn0 = Ionflux::GeoUtils::Vector3::E_Z;
	            for (unsigned int i = 0; i < 6; i++)
	                normalTarget->setData(ne0 + i, cn0);
	            offset0 += 6;
	        }
	        if (checkFaceMask(faces, FACE_Z1))
	        {
	            // quad (1, Z1)
	            if (!checkFaceMask(flipNormals, FACE_Z1))
	                cn0 = Ionflux::GeoUtils::Vector3::E_Z;
	            else
	                cn0 = Ionflux::GeoUtils::Vector3::E_Z.flip();
	            for (unsigned int i = 0; i < 6; i++)
	                normalTarget->setData(ne0 + offset0 + i, cn0);
	            offset0 += 6;
	        }
	        if (checkFaceMask(faces, FACE_Y0))
	        {
	            // quad (2, Y0)
	            if (!checkFaceMask(flipNormals, FACE_Y0))
	                cn0 = Ionflux::GeoUtils::Vector3::E_Y.flip();
	            else
	                cn0 = Ionflux::GeoUtils::Vector3::E_Y;
	            for (unsigned int i = 0; i < 6; i++)
	                normalTarget->setData(ne0 + offset0 + i, cn0);
	            offset0 += 6;
	        }
	        if (checkFaceMask(faces, FACE_X1))
	        {
	            // quad (3, X1)
	            if (!checkFaceMask(flipNormals, FACE_X1))
	                cn0 = Ionflux::GeoUtils::Vector3::E_X;
	            else
	                cn0 = Ionflux::GeoUtils::Vector3::E_X.flip();
	            for (unsigned int i = 0; i < 6; i++)
	                normalTarget->setData(ne0 + offset0 + i, cn0);
	            offset0 += 6;
	        }
	        if (checkFaceMask(faces, FACE_X0))
	        {
	            // quad (4, X0)
	            if (!checkFaceMask(flipNormals, FACE_X0))
	                cn0 = Ionflux::GeoUtils::Vector3::E_X.flip();
	            else
	                cn0 = Ionflux::GeoUtils::Vector3::E_X;
	            for (unsigned int i = 0; i < 6; i++)
	                normalTarget->setData(ne0 + offset0 + i, cn0);
	            offset0 += 6;
	        }
	        if (checkFaceMask(faces, FACE_Y1))
	        {
	            // quad (5, Y1)
	            if (!checkFaceMask(flipNormals, FACE_Y1))
	                cn0 = Ionflux::GeoUtils::Vector3::E_Y;
	            else
	                cn0 = Ionflux::GeoUtils::Vector3::E_Y.flip();
	            for (unsigned int i = 0; i < 6; i++)
	                normalTarget->setData(ne0 + offset0 + i, cn0);
	        }
	    } else
	    if (nFaceType == Ionflux::GeoUtils::NFace::TYPE_EDGE)
	    {
	        /* edges
	           12 edges * 2 vertices = 24 vertices */
	        normalTarget->resize(ne0 + 24, 3, 
	            Ionflux::GeoUtils::DATA_TYPE_FLOAT, 2.);
	        // quad (0)
	        for (unsigned int i = 0; i < 8; i++)
	            normalTarget->setData(ne0 + i, 
	                Ionflux::GeoUtils::Vector3::E_Z.flip());
	        // quad (1)
	        for (unsigned int i = 0; i < 8; i++)
	            normalTarget->setData(ne0 + 8 + i, 
	                Ionflux::GeoUtils::Vector3::E_Z);
	        // Z-edges
	        for (unsigned int i = 0; i < 4; i++)
	            normalTarget->setData(ne0 + 16 + i, 
	                Ionflux::GeoUtils::Vector3::E_Y.flip());
	        for (unsigned int i = 0; i < 4; i++)
	            normalTarget->setData(ne0 + 20 + i, 
	                Ionflux::GeoUtils::Vector3::E_Y);
	    }
	}
}

bool Context::getIntersectionLoc(Ionflux::GeoUtils::Line3& line, const 
Ionflux::GeoUtils::AAPlanePairIntersection& interData, 
Ionflux::VolGfx::Region3& target, bool checkBounds0)
{
	if (!interData.valid)
	    return false;
	target.l0 = createLoc(line.eval(interData.tNear), checkBounds0);
	target.l1 = createLoc(line.eval(interData.tFar), checkBounds0);
	return true;
}

bool Context::getIntersectionLoc(const Ionflux::VolGfx::NodeID& node, 
Ionflux::GeoUtils::Line3& line, const 
Ionflux::GeoUtils::AAPlanePairIntersection& interData, 
Ionflux::VolGfx::Region3& target, bool clampToNodeRegion, bool 
includeMaxBoundary)
{
	if (!interData.valid)
	    return false;
	Region3 t0, r0;
	getIntersectionLoc(line, interData, t0, false);
	if (!clampToNodeRegion)
	    return true;
	getVoxelRegion(node, r0, includeMaxBoundary);
	target.l0 = clampLoc3(t0.l0, r0);
	target.l1 = clampLoc3(t0.l1, r0);
	return true;
}

std::string Context::getValueString() const
{
	std::ostringstream status;
	status << "maxNumLevels = " << maxNumLevels << ", order = " 
	    << order << ", scale = " << scale << ", tolerance = " 
	    << tolerance << ", maxNumLeafChildNodesPerNode = " 
	    << maxNumLeafChildNodesPerNode 
	    << ", maxNumLeafChildNodesPerDimension = " 
	        << maxNumLeafChildNodesPerDimension;
	return status.str();
}

Ionflux::GeoUtils::Vector3* Context::getVoxelDiag(int index)
{
	if (voxelDiag == 0)
	{
	    // initialize static voxel diagonal vectors
	    voxelDiag = new Ionflux::GeoUtils::Vector3[8];
	    Ionflux::ObjectBase::nullPointerCheck(voxelDiag, 
	        "Context::getVoxelDiag", "Voxel diagonal vector array");
	    for (int i = 0; i < 2; i++)
	    {
	        for (int j = 0; j < 2; j++)
	        {
	            for (int k = 0; k < 2; k++)
	            {
	                voxelDiag[4 * i + 2 * j + k].setElements(
	                    (-1 + 2 * k) * SQRT_3_INV, 
	                    (-1 + 2 * j) * SQRT_3_INV, 
	                    (-1 + 2 * i) * SQRT_3_INV);
	            }
	        }
	    }
	}
	Ionflux::ObjectBase::rangeCheck(index, 0, 7, 
	    "Context::getVoxelDiag", "Index");
	return &(voxelDiag[index]);;
}

Ionflux::GeoUtils::Vector3* Context::getVoxelDiag(int x, int y, int z)
{
	// TODO: Implementation.
	return getVoxelDiag(4 * z + 2 * y + x);;
}

void Context::cleanupVoxelDiag()
{
	if (voxelDiag != 0)
	    delete[] voxelDiag;
	voxelDiag = 0;
}

Ionflux::GeoUtils::Vector3* Context::getMatchingVoxelDiag(const 
Ionflux::GeoUtils::Vector3& v)
{
	Ionflux::GeoUtils::Vector3 s0;
	v.getElementSigns(s0);
	Ionflux::GeoUtils::Vector3 c0((s0 
	    + Ionflux::GeoUtils::Vector3::E_SUM) / 2.);
	return getVoxelDiag(c0[0], c0[1], c0[2]);
}

Ionflux::GeoUtils::Vector3* Context::getVoxelNormal(int index)
{
	if (voxelNormal == 0)
	{
	    // initialize static voxel face normal vectors
	    voxelNormal = new Ionflux::GeoUtils::Vector3[6];
	    Ionflux::ObjectBase::nullPointerCheck(voxelNormal, 
	        "Context::getVoxelDiag", "Voxel face normal vector array");
	    for (int i = 0; i < 3; i++)
	    {
	        voxelNormal[2 * i].setElement(i, -1.);
	        voxelNormal[2 * i + 1].setElement(i, 1.);
	    }
	}
	Ionflux::ObjectBase::rangeCheck(index, 0, 5, 
	    "Context::getVoxelNormal", "Index");
	return &(voxelNormal[index]);;
}

Ionflux::GeoUtils::Vector3* Context::getMatchingVoxelNormal(const 
Ionflux::GeoUtils::Vector3& v)
{
	Ionflux::GeoUtils::Vector3* result = 0;
	double bc0 = 0.;
	for (int i = 0; i < 6; i++)
	{
	    Ionflux::GeoUtils::Vector3* n0 = getVoxelNormal(i);
	    double cc0 = v.angleCos(*n0);
	    if ((cc0 > 0.) 
	        && (cc0 > bc0))
	    {
	        bc0 = cc0;
	        result = n0;
	    }
	}
	return result;
}

void Context::cleanupVoxelNormal()
{
	if (voxelNormal != 0)
	    delete[] voxelNormal;
	voxelNormal = 0;
}

void Context::cleanup()
{
	cleanupVoxelDiag();
	cleanupVoxelNormal();
}

void Context::setMaxNumLevels(int newMaxNumLevels)
{
	maxNumLevels = newMaxNumLevels;
}

int Context::getMaxNumLevels() const
{
    return maxNumLevels;
}

void Context::setOrder(int newOrder)
{
	order = newOrder;
}

int Context::getOrder() const
{
    return order;
}

void Context::setTolerance(double newTolerance)
{
	tolerance = newTolerance;
}

double Context::getTolerance() const
{
    return tolerance;
}

void Context::setValidBits(const Ionflux::VolGfx::NodeLoc& newValidBits)
{
	validBits = newValidBits;
}

Ionflux::VolGfx::NodeLoc Context::getValidBits() const
{
    return validBits;
}

void Context::setMaxNumLeafChildNodesPerNode(int 
newMaxNumLeafChildNodesPerNode)
{
	maxNumLeafChildNodesPerNode = newMaxNumLeafChildNodesPerNode;
}

int Context::getMaxNumLeafChildNodesPerNode() const
{
    return maxNumLeafChildNodesPerNode;
}

void Context::setMaxNumLeafChildNodesPerDimension(int 
newMaxNumLeafChildNodesPerDimension)
{
	maxNumLeafChildNodesPerDimension = newMaxNumLeafChildNodesPerDimension;
}

int Context::getMaxNumLeafChildNodesPerDimension() const
{
    return maxNumLeafChildNodesPerDimension;
}

void Context::setScale(double newScale)
{
	scale = newScale;
}

double Context::getScale() const
{
    return scale;
}

Ionflux::VolGfx::Context& Context::operator=(const 
Ionflux::VolGfx::Context& other)
{
    if (this == &other)
        return *this;
    setMaxNumLevels(other.maxNumLevels);
    setOrder(other.order);
    setTolerance(other.tolerance);
    update();
	return *this;
}

Ionflux::VolGfx::Context* Context::copy() const
{
    Context* newContext = create();
    *newContext = *this;
    return newContext;
}

Ionflux::VolGfx::Context* Context::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Context*>(other);
}

Ionflux::VolGfx::Context* Context::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Context* newObject = new Context();
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::VolGfx::Context* Context::create(int initMaxNumLevels, int 
initOrder, double initScale, double initTolerance, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Context* newObject = new Context(initMaxNumLevels, initOrder, 
    initScale, initTolerance);
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Context::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Context.cpp
 * \brief Voxel tree context implementation.
 */
