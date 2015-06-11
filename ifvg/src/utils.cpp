/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utils.cpp                     Utility functions (implementation).
 * =========================================================================
 *
 * This file is part of IFVG - Ionflux' Volumetric Graphics Library.
 * 
 * IFVG - Ionflux' Volumetric Graphics Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFVG - Ionflux' Volumetric Graphics Library is distributed in the hope 
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFVG - Ionflux' Volumetric Graphics Library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */
#include <cmath>
#include <sstream>
#include "geoutils/Vector3.hpp"
#include "geoutils/VertexAttribute.hpp"
#include "ifvg/utils.hpp"
#include "ifvg/IFVGError.hpp"
#include "ifvg/Context.hpp"
#include "ifvg/Node.hpp"

namespace Ionflux
{

namespace VolGfx
{

Ionflux::VolGfx::NodeLoc3 createLoc(Ionflux::VolGfx::NodeLoc x, 
    Ionflux::VolGfx::NodeLoc y, Ionflux::VolGfx::NodeLoc z)
{
    NodeLoc3 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

Ionflux::VolGfx::Region3 createRegion(Ionflux::VolGfx::NodeLoc3 l0, 
    Ionflux::VolGfx::NodeLoc3 l1)
{
    Region3 result;
    result.l0 = l0;
    result.l1 = l1;
    return result;
}

Ionflux::VolGfx::NodeID createNodeID(int depth, 
    const Ionflux::VolGfx::NodeLoc3* loc)
{
    NodeID result;
    result.depth = depth;
    if (loc != 0)
        result.loc = *loc;
    else
        result.loc = createLoc();
    return result;
}

Ionflux::VolGfx::NodeImplHierarchyHeader createNodeImplHierarchyHeader(
    Ionflux::ObjectBase::DataSize poMapOffset, 
    Ionflux::ObjectBase::UInt16 implArrayStride, 
    Ionflux::ObjectBase::UInt16 implSize, 
    Ionflux::ObjectBase::UInt16 dataImplSize, 
    Ionflux::ObjectBase::UInt8 dataValueSize, 
    Ionflux::ObjectBase::UInt8 rootNodeDepth, 
    Ionflux::ObjectBase::GenericPointer rootNodePointer)
{
    NodeImplHierarchyHeader result;
    result.poMapOffset = poMapOffset;
    result.implArrayStride = implArrayStride;
    result.implSize = implSize;
    result.dataImplSize = dataImplSize;
    result.dataValueSize = dataValueSize;
    result.rootNodeDepth = rootNodeDepth;
    result.rootNodePointer = rootNodePointer;
    return result;
}

Ionflux::VolGfx::NodeIntersection createNodeIntersection(
    const Ionflux::GeoUtils::AAPlanePairIntersection* intersection, 
    Ionflux::VolGfx::NodeImpl* nodeImpl, int depth)
{
    NodeIntersection result;
    if (intersection != 0)
        result.intersection = *intersection;
    else
    {
        result.intersection = 
            Ionflux::GeoUtils::createAAPlanePairIntersection();
    }
    result.nodeImpl = nodeImpl;
    result.depth = depth;
    return result;
}

Ionflux::VolGfx::VoxelDataIOB createVoxelDataIOB(
    Ionflux::VolGfx::VoxelClassID voxelClass, 
    Ionflux::ObjectBase::UInt16 numInts0 , 
    Ionflux::ObjectBase::UInt16 numInts1,
    Ionflux::ObjectBase::UInt16 votesInside, 
    Ionflux::ObjectBase::UInt16 votesOutside, 
    Ionflux::VolGfx::FaceMaskInt boundaryFaces, 
    Ionflux::ObjectBase::UInt16 wallThicknessX, 
    Ionflux::ObjectBase::UInt16 wallThicknessY, 
    Ionflux::ObjectBase::UInt16 wallThicknessZ, 
    Ionflux::VolGfx::ColorIndex color)
{
    VoxelDataIOB result;
    result.voxelClass = voxelClass;
    result.numInts0 = numInts0;
    result.numInts1 = numInts1;
    result.votesInside = votesInside;
    result.votesOutside = votesOutside;
    result.boundaryFaces = boundaryFaces;
    result.wallThicknessX = wallThicknessX;
    result.wallThicknessY = wallThicknessY;
    result.wallThicknessZ = wallThicknessZ;
    result.color = color;
    return result;
}

Ionflux::VolGfx::NodeIntersectionProcessingFlags 
    createNodeIntersectionProcessingFlags(
        bool directionBackward, bool enableBoundaryData, 
        bool castVotes, bool enableRayStabbing, 
        bool enableWallThickness)
{
    NodeIntersectionProcessingFlags result;
    result.directionBackward = directionBackward;
    result.enableBoundaryData = enableBoundaryData;
    result.castVotes = castVotes;
    result.enableRayStabbing = enableRayStabbing;
    result.enableWallThickness = enableWallThickness;
    return result;
}

bool operator==(const Ionflux::VolGfx::NodeIntersection& i0, 
    const Ionflux::VolGfx::NodeIntersection& i1)
{
    if (i0.nodeImpl != i1.nodeImpl)
        return false;
    if (!(i0.intersection == i1.intersection))
        return false;
    if (i0.depth != i1.depth)
        return false;
    return true;
}

std::string getLocString(const Ionflux::VolGfx::NodeLoc& loc)
{
    std::ostringstream status;
    status << loc;
    return status.str();
}

std::string getLocString(const Ionflux::VolGfx::NodeLoc3& loc)
{
    std::ostringstream status;
    status << "(" << loc.x << ", " << loc.y << ", " << loc.z << ")";
    return status.str();
}

std::string getLocValueString(const Ionflux::VolGfx::NodeLoc& loc, 
    bool showCode, bool showIndex, 
    bool showVec, Ionflux::VolGfx::Context* context)
{
    if (context == 0)
        showVec = false;
    bool first = true;
    std::ostringstream status;
    if (showCode)
    {
        status << loc;
        first = false;
    }
    if (showIndex)
    {
        if (!first)
            status << "; ";
        status << static_cast<LocInt>(loc.to_ulong());
        first = false;
    }
    if (showVec)
    {
        double s0 = context->getMinLeafSize();
        if (!first)
            status << "; ";
        status << (s0 * loc.to_ulong());
    }
    return status.str();
}

std::string getLocValueString(const Ionflux::VolGfx::NodeLoc3& loc, 
    bool showCode, bool showIndex, 
    bool showVec, Ionflux::VolGfx::Context* context)
{
    if (context == 0)
        showVec = false;
    unsigned int numItems = 0;
    if (showCode)
        numItems++;
    if (showIndex)
        numItems++;
    if (showVec)
        numItems++;
    bool first = true;
    std::ostringstream status;
    if (showCode)
    {
        if (numItems > 1)
            status << "(";
        status << getLocValueString(loc.x, 
                true, false, false, context) 
            << ", " << getLocValueString(loc.y, 
                true, false, false, context) 
            << ", " << getLocValueString(loc.z, 
                true, false, false, context);
        if (numItems > 1)
            status << ")";
        first = false;
    }
    if (showIndex)
    {
        if (!first)
            status << "; ";
        if (numItems > 1)
            status << "(";
        status << getLocValueString(loc.x, 
                false, true, false, context) 
            << ", " << getLocValueString(loc.y, 
                false, true, false, context) 
            << ", " << getLocValueString(loc.z, 
                false, true, false, context);
        if (numItems > 1)
            status << ")";
        first = false;
    }
    if (showVec)
    {
        if (!first)
            status << "; ";
        if (numItems > 1)
            status << "(";
        status << getLocValueString(loc.x, 
                false, false, true, context) 
            << ", " << getLocValueString(loc.y, 
                false, false, true, context) 
            << ", " << getLocValueString(loc.z, 
                false, false, true, context);
        if (numItems > 1)
            status << ")";
    }
    return status.str();
}

std::string getRegionString(const Ionflux::VolGfx::Region3& region)
{
    std::ostringstream status;
    status << "[" << getLocString(region.l0) << ", " 
        << getLocString(region.l1) << "]";
    return status.str();
}

std::string getCylinderString(const Ionflux::VolGfx::Cylinder& c)
{
    std::ostringstream status;
    status << "c = (" << c.center.getValueString() << "), d = (" 
        << c.direction.getValueString() << "), l = " << c.length 
        << ", r = " << c.radius;
    return status.str();
}

std::string getPlaneString(const Ionflux::VolGfx::Plane& p)
{
    std::ostringstream status;
    status << "p = (" << p.p.getValueString() << "), n = (" 
        << p.normal.getValueString() << ")";
    return status.str();
}

std::string getTriangleString(const Ionflux::VolGfx::Triangle& tri)
{
    std::ostringstream status;
    status << "(" << tri.v0.getValueString() << ")" 
        ", (" << tri.v1.getValueString() << ")" 
        ", (" << tri.v2.getValueString() << ")";
    return status.str();
}

std::string getDepthString(int d)
{
    std::ostringstream status;
    if (d == DEPTH_UNSPECIFIED)
        status << "<unspecified>";
    else
        status << d;
    return status.str();
}

std::string getNodeIDString(const Ionflux::VolGfx::NodeID& nodeID)
{
    std::ostringstream status;
    status << getDepthString(nodeID.depth) 
        << "; " << getLocString(nodeID.loc);
    return status.str();
}

std::string getNodeIDValueString(const Ionflux::VolGfx::NodeID& nodeID, 
    bool showCode, bool showIndex, 
    bool showVec, Ionflux::VolGfx::Context* context)
{
    std::ostringstream status;
    status << getDepthString(nodeID.depth) 
        << "; [" << getLocValueString(nodeID.loc, showCode, showIndex, 
            showVec, context) << "]";
    return status.str();
}

std::string getTriangleVoxelizationDataString(
    const Ionflux::VolGfx::TriangleVoxelizationData& d)
{
    std::ostringstream status;
    status << "voxelSize = " << d.voxelSize 
        << ", tri = [" << getTriangleString(d.tri) << "]" 
        ", plane = [" << getPlaneString(d.plane) << "]" 
        ", sep = " << d.sep << ", t = " << d.t << ", r_c = " << d.r_c 
        << ", planeU = [" << getPlaneString(d.planeU) << "]" 
        ", planeL = [" << getPlaneString(d.planeL) << "]" 
        ", planeE0 = [" << getPlaneString(d.planeE0) << "]" 
        ", planeE1 = [" << getPlaneString(d.planeE1) << "]" 
        ", planeE2 = [" << getPlaneString(d.planeE2) << "]" 
        ", cylE0 = [" << getCylinderString(d.cylE0) << "]" 
        ", cylE1 = [" << getCylinderString(d.cylE1) << "]" 
        ", cylE2 = [" << getCylinderString(d.cylE2) << "]" 
        ", node = [" << getNodeIDString(d.node) << "]";
    return status.str();
}

void printTriangleVoxelizationDataDebugInfo(
    const Ionflux::VolGfx::TriangleVoxelizationData& d)
{
    std::cerr << "voxelSize = " << d.voxelSize << std::endl 
        << "tri = [" << getTriangleString(d.tri) << "]" << std::endl 
        << "plane = [" << getPlaneString(d.plane) << "]" << std::endl 
        << "sep = " << d.sep << ", t = " << d.t << ", r_c = " << d.r_c 
            << std::endl
        << "planeU = [" << getPlaneString(d.planeU) << "]" << std::endl 
        << "planeL = [" << getPlaneString(d.planeL) << "]" << std::endl 
        << "planeE0 = [" << getPlaneString(d.planeE0) << "]" << std::endl 
        << "planeE1 = [" << getPlaneString(d.planeE1) << "]" << std::endl 
        << "planeE2 = [" << getPlaneString(d.planeE2) << "]" << std::endl 
        << "cylE0 = [" << getCylinderString(d.cylE0) << "]" << std::endl 
        << "cylE1 = [" << getCylinderString(d.cylE1) << "]" << std::endl 
        << "cylE2 = [" << getCylinderString(d.cylE2) << "]" << std::endl 
        << "node = [" << getNodeIDString(d.node) << "]" << std::endl;
}

std::string getNodeImplHierarchyHeaderValueString(
    const Ionflux::VolGfx::NodeImplHierarchyHeader& h)
{
    std::ostringstream status;
    status << "poMapOffset = " << h.poMapOffset 
        << ", implArrayStride = " << h.implArrayStride
        << ", implSize = " << h.implSize
        << ", dataImplSize = " << h.dataImplSize
        << ", dataValueSize = " << h.dataValueSize
        << ", rootNodeDepth = " << h.rootNodeDepth
        << ", rootNodePointer = " << h.rootNodePointer;
    return status.str();
}

std::string getVoxelizationTargetValueString(
    Ionflux::VolGfx::VoxelizationTargetID t)
{
    if (t == VOXELIZATION_TARGET_DENSITY)
        return "density";
    if (t == VOXELIZATION_TARGET_COLOR_NORMAL)
        return "color_normal";
    return "<unknown>";
}

std::string getVoxelClassValueString(Ionflux::VolGfx::VoxelClassID t)
{
    bool first = true;
    if (t == VOXEL_CLASS_UNDEFINED)
        return "undefined";
    std::ostringstream status;
    if ((t & VOXEL_CLASS_EMPTY) != 0)
    {
        status << "empty";
        first = false;
    }
    if ((t & VOXEL_CLASS_FILLED) != 0)
    {
        if (!first)
            status << ",";
        status << "filled";
        first = false;
    }
    if ((t & VOXEL_CLASS_INSIDE) != 0)
    {
        if (!first)
            status << ",";
        status << "inside";
        first = false;
    }
    if ((t & VOXEL_CLASS_OUTSIDE) != 0)
    {
        if (!first)
            status << ",";
        status << "outside";
        first = false;
    }
    if ((t & VOXEL_CLASS_BOUNDARY) != 0)
    {
        if (!first)
            status << ",";
        status << "boundary";
        first = false;
    }
    if ((t & VOXEL_CLASS_HIT) != 0)
    {
        if (!first)
            status << ",";
        status << "hit";
        first = false;
    }
    std::string result(status.str());
    if (result.size() == 0)
        return "<unknown>";
    return result;
}

std::string getNodeIntersectionValueString(
    Ionflux::VolGfx::Context& context, 
    const Ionflux::VolGfx::NodeIntersection& i0)
{
    std::ostringstream status;
    if (i0.nodeImpl != 0)
        status << "[" << Node::getImplValueString(
            i0.nodeImpl, &context, false) << "]";
    else
        status << "<null>";
    status << "; [" 
        << Ionflux::GeoUtils::getAAPlanePairIntersectionValueString(
            i0.intersection) << "]";
    return status.str();
}

std::string getFaceMaskValueString(Ionflux::VolGfx::FaceMaskInt mask)
{
    return Ionflux::GeoUtils::getPlaneMaskValueString(
        static_cast<Ionflux::GeoUtils::PlaneMask>(mask));
}

std::string getVoxelDataIOBValueString(
    const Ionflux::VolGfx::VoxelDataIOB& data)
{
    std::ostringstream status;
    status << "voxelClass = " 
            << getVoxelClassValueString(data.voxelClass) 
        << ", numInts0 = " << data.numInts0 
        << ", numInts1 = " << data.numInts1 
        << ", votesInside = " << data.votesInside 
        << ", votesOutside = " << data.votesOutside 
        << ", boundaryFaces = " 
            << getFaceMaskValueString(data.boundaryFaces) 
        << ", wallThicknessX = " << data.wallThicknessX 
        << ", wallThicknessY = " << data.wallThicknessY 
        << ", wallThicknessZ = " << data.wallThicknessZ 
        << ", color = " << data.color;
    return status.str();
}

std::string getLeafStatusValueString(Ionflux::VolGfx::LeafStatusID s)
{
    if (s == NODE_ANY)
        return "any";
    if (s == NODE_LEAF)
        return "leaf";
    if (s == NODE_NON_LEAF)
        return "non_leaf";
    return "<unknown>";
}

std::string getMergePolicyValueString(Ionflux::VolGfx::MergePolicyID p)
{
    if (p == MERGE_POLICY_KEEP_TARGET)
        return "keep_target";
    if (p == MERGE_POLICY_TAKE_OVER_SOURCE)
        return "take_over_source";
    return "<unknown>";
}

double distanceToPlane(const Ionflux::GeoUtils::Vector3& v, 
    const Ionflux::VolGfx::Plane& p)
{
    return p.normal * (v - p.p);
}

double distanceToSphere(const Ionflux::GeoUtils::Vector3& v, 
    const Ionflux::GeoUtils::Vector3& cs, double rs)
{
    return (v - cs).length() - rs;
}

double distanceToCylinderSC(const Ionflux::GeoUtils::Vector3& v, 
    const Ionflux::VolGfx::Cylinder& c)
{
    double d0 = c.direction * (v - c.center);
    double s0 = 0.5 * c.length;
    if (::fabs(d0) <= s0)
    {
        // point lies within mantle region
        return ((v - c.center) - d0 * c.direction).norm() 
            - c.radius;
    }
    // point lies within cap region.
    if (d0 > 0.)
    {
        return distanceToSphere(v, 
            c.center + s0 * c.direction, c.radius);
    }
    return distanceToSphere(v, 
        c.center - s0 * c.direction, c.radius);
}

bool voxelizePointTest(
    const Ionflux::VolGfx::TriangleVoxelizationData& d, 
    const Ionflux::GeoUtils::Vector3& v)
{
    // check planes.
    if ((distanceToPlane(v, d.planeU) <= 0.) 
        && (distanceToPlane(v, d.planeL) <= 0.) 
        && (distanceToPlane(v, d.planeE0) <= 0.) 
        && (distanceToPlane(v, d.planeE1) <= 0.) 
        && (distanceToPlane(v, d.planeE2) <= 0.))
        return true;
    // check edge cylinders
    if (distanceToCylinderSC(v, d.cylE0) <= 0.)
        return true;
    if (distanceToCylinderSC(v, d.cylE1) <= 0.)
        return true;
    if (distanceToCylinderSC(v, d.cylE2) <= 0.)
        return true;
    return false;
}

bool voxelizePointTestDebug(
    const Ionflux::VolGfx::TriangleVoxelizationData& d, 
    const Ionflux::GeoUtils::Vector3& v)
{
    std::cerr << "[voxelizePointTestDebug] DEBUG: "
        "v = (" << v.getValueString() << "), tvd: " 
        << std::endl;
    printTriangleVoxelizationDataDebugInfo(d);
    // check planes.
    bool result = true;
    double d0 = 0.;
    d0 = distanceToPlane(v, d.planeU);
    std::cerr << "d(planeU) = " << d0 << std::endl;
    if (d0 > 0.)
        result = false;
    d0 = distanceToPlane(v, d.planeL);
    std::cerr << "d(planeL) = " << d0 << std::endl;
    if (d0 > 0.)
        result = false;
    d0 = distanceToPlane(v, d.planeE0);
    std::cerr << "d(planeE0) = " << d0 << std::endl;
    if (d0 > 0.)
        result = false;
    d0 = distanceToPlane(v, d.planeE1);
    std::cerr << "d(planeE1) = " << d0 << std::endl;
    if (d0 > 0.)
        result = false;
    d0 = distanceToPlane(v, d.planeE2);
    std::cerr << "d(planeE2) = " << d0 << std::endl;
    if (d0 > 0.)
        result = false;
    if (result)
        return true;
    // check edge cylinders
    result = true;
    d0 = distanceToCylinderSC(v, d.cylE0);
    std::cerr << "d(cylE0) = " << d0 << std::endl;
    if (d0 <= 0.)
        return true;
    d0 = distanceToCylinderSC(v, d.cylE1);
    std::cerr << "d(cylE1) = " << d0 << std::endl;
    if (d0 <= 0.)
        return true;
    d0 = distanceToCylinderSC(v, d.cylE2);
    std::cerr << "d(cylE2) = " << d0 << std::endl;
    if (d0 <= 0.)
        return true;
    return false;
}

void packVoxelClass(Ionflux::VolGfx::VoxelClassID c, 
    Ionflux::VolGfx::NodeDataPointer& target)
{
    Ionflux::ObjectBase::UInt64 v0 = 
        static_cast<Ionflux::ObjectBase::UInt64>(c);
    target = reinterpret_cast<NodeDataPointer>(v0);
}

void unpackVoxelClass(Ionflux::VolGfx::NodeDataPointer source, 
    Ionflux::VolGfx::VoxelClassID& c)
{
    Ionflux::ObjectBase::UInt64 v0 = 
        reinterpret_cast<Ionflux::ObjectBase::UInt64>(source);
    c = static_cast<VoxelClassID>(v0);
}

void setVoxelClass(Ionflux::VolGfx::VoxelClassID c, 
    Ionflux::VolGfx::VoxelClassID& target, bool enable)
{
    if (enable)
        target |= c;
    else
        target &= ~c;
}

bool checkVoxelClass(Ionflux::VolGfx::VoxelClassID source, 
    Ionflux::VolGfx::VoxelClassID mask)
{
    if ((source & mask) == 0)
        return false;
    return true;
}

bool NodeIntersectionCompare::operator()(
    const NodeIntersection& i0, const NodeIntersection& i1)
{
    return (i0.intersection.tNear < i1.intersection.tNear);
}

Ionflux::Altjira::Color* getVoxelClassColor(
    const Ionflux::VolGfx::VoxelClassColorVector& colors, 
    Ionflux::VolGfx::VoxelClassID c)
{
    unsigned int n0 = colors.size();
    unsigned int k = 0;
    Ionflux::Altjira::Color* result = 0;
    while ((k < n0) 
        && (result == 0))
    {
        VoxelClassColor vc0 = colors[k];
        if (checkVoxelClass(c, vc0.voxelClass))
            result = vc0.color;
        k++;
    }
    return result;
}

Ionflux::VolGfx::NodeLoc clampLoc(
    const Ionflux::VolGfx::NodeLoc& loc, 
    const Ionflux::VolGfx::NodeLoc& rMin, 
    const Ionflux::VolGfx::NodeLoc& rMax)
{
    if (loc.to_ulong() < rMin.to_ulong())
        return rMin;
    if (loc.to_ulong() > rMax.to_ulong())
        return rMax;
    return loc;
}

Ionflux::VolGfx::NodeLoc3 clampLoc3(
    const Ionflux::VolGfx::NodeLoc3& loc, 
    const Ionflux::VolGfx::Region3& region)
{
    NodeLoc3 result;
    result.x = clampLoc(loc.x, region.l0.x, region.l1.x);
    result.y = clampLoc(loc.y, region.l0.y, region.l1.y);
    result.z = clampLoc(loc.z, region.l0.z, region.l1.z);
    return result;
}

bool checkFaceMask(Ionflux::VolGfx::FaceMaskInt source, 
    Ionflux::VolGfx::FaceMaskInt mask)
{
    if ((source & mask) == 0)
        return false;
    return true;
}

unsigned int getNumFacesSet(Ionflux::VolGfx::FaceMaskInt mask)
{
    unsigned int result = 0;
    for (int i = 0; i < 6; i++)
    {
        if ((mask & (1 << i)) != 0)
            result++;
    }
    return result;
}

void setVertexAttributeTrianglePos(
    Ionflux::GeoUtils::VertexAttribute& target, 
    unsigned int elementIndex, const Ionflux::GeoUtils::Vector3& v0, 
    const Ionflux::GeoUtils::Vector3& v1, 
    const Ionflux::GeoUtils::Vector3& v2, bool reverse)
{
    if (!reverse)
    {
        target.setData(elementIndex, v0);
        target.setData(elementIndex + 1, v1);
        target.setData(elementIndex + 2, v2);
    } else
    {
        target.setData(elementIndex, v0);
        target.setData(elementIndex + 1, v2);
        target.setData(elementIndex + 2, v1);
    }
}

void setIOBDataWallThickness(Ionflux::VolGfx::VoxelDataIOB& data, 
    Ionflux::GeoUtils::AxisID axis, Ionflux::ObjectBase::UInt16 v)
{
    if (axis == Ionflux::GeoUtils::AXIS_X)
        data.wallThicknessX = v;
    else
    if (axis == Ionflux::GeoUtils::AXIS_Y)
        data.wallThicknessY = v;
    else
    if (axis == Ionflux::GeoUtils::AXIS_Z)
        data.wallThicknessZ = v;
}

Ionflux::ObjectBase::UInt16 getIOBDataWallThickness(
    const Ionflux::VolGfx::VoxelDataIOB& data, 
    Ionflux::GeoUtils::AxisID axis)
{
    if (axis == Ionflux::GeoUtils::AXIS_X)
        return data.wallThicknessX;
    else
    if (axis == Ionflux::GeoUtils::AXIS_Y)
        return data.wallThicknessY;
    else
    if (axis == Ionflux::GeoUtils::AXIS_Z)
        return data.wallThicknessZ;
    return 0;
}

Ionflux::ObjectBase::UInt16 getIOBDataWallThicknessMin(
    const Ionflux::VolGfx::VoxelDataIOB& data, 
    Ionflux::GeoUtils::AxisID* axis)
{
    unsigned int wtMin = 0;
    for (unsigned int i = 0; i < 3; i++)
    {
        Ionflux::ObjectBase::UInt16 wt0 = 
            getIOBDataWallThickness(data, i);
        if ((wt0 != 0) 
            && ((wt0 < wtMin) || (wtMin == 0)))
        {
            wtMin = wt0;
            if (axis != 0)
                *axis = i;
        }
    }
    return wtMin;
}

Ionflux::VolGfx::ColorIndex getColorIndex(
    Ionflux::ObjectBase::UInt16 v, 
    Ionflux::ObjectBase::UInt16 vMin, 
    Ionflux::ObjectBase::UInt16 vMax, 
    Ionflux::VolGfx::ColorIndex minColorIndex, 
    Ionflux::VolGfx::ColorIndex maxColorIndex)
{
    if ((minColorIndex == COLOR_INDEX_UNSPECIFIED) 
        || (maxColorIndex == COLOR_INDEX_UNSPECIFIED) 
        || (maxColorIndex < minColorIndex) 
        || (vMax < vMin))
        return COLOR_INDEX_UNSPECIFIED;
    if (v >= vMax)
        return maxColorIndex;
    if (v <= vMin)
        return minColorIndex;
    ColorIndex ci0 = COLOR_INDEX_UNSPECIFIED;
    ColorIndex cr0 = maxColorIndex - minColorIndex;
    Ionflux::ObjectBase::UInt16 wtr0 = vMax - vMin;
    if (wtr0 > 0)
        ci0 = (v - vMin) * cr0 / wtr0 + minColorIndex;
    else
        ci0 = cr0 / 2 + minColorIndex;
    return ci0;
}

}

}

/** \file utils.cpp
 * \brief Utility functions (implementation).
 */
