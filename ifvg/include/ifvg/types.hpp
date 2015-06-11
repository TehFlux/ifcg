#ifndef IONFLUX_VOLGFX_TYPES
#define IONFLUX_VOLGFX_TYPES
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * types.hpp                     Types.
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
#include <vector>
#include <string>
#include <set>
#include <map>
#include <bitset>
#include <deque>
#include "altjira/Color.hpp"
#include "geoutils/Vector3.hpp"
#include "ifobject/types.hpp"

namespace Ionflux
{

namespace VolGfx
{

class Node;

/// Location code integer.
typedef Ionflux::ObjectBase::UInt16 LocInt;

/// Child mask integer.
typedef Ionflux::ObjectBase::UInt8 ChildMaskInt;

/// Node location code.
typedef std::bitset<16> NodeLoc;

/// Child node mask.
typedef std::bitset<8> NodeChildMask;

/// Face mask integer.
typedef Ionflux::ObjectBase::UInt8 FaceMaskInt;

/// Node location code (3D).
struct NodeLoc3
{
    /// Location code (X).
    Ionflux::VolGfx::NodeLoc x;
    /// Location code (Y).
    Ionflux::VolGfx::NodeLoc y;
    /// Location code (Z).
    Ionflux::VolGfx::NodeLoc z;
};

/// Region (3D).
struct Region3
{
    /// Mininum coordinate location.
    Ionflux::VolGfx::NodeLoc3 l0;
    /// Maximum coordinate location.
    Ionflux::VolGfx::NodeLoc3 l1;
};

/// Node data type.
typedef Ionflux::ObjectBase::UInt8 NodeDataType;

/// Node data value.
typedef double NodeDataValue;

/// Node data pointer.
typedef void* NodeDataPointer;

/** Node data implementation.
 * 
 * A data record that can be attached to a voxel tree node. Functions that 
 * operate on NodeDataImpl are defined as static member functions of Node.
 */
struct NodeDataImpl
{
    /// Data type.
    Ionflux::VolGfx::NodeDataType type;
    /// Data.
    NodeDataPointer data;
};

/** Node implementation.
 * 
 * The implementation backend of a voxel tree node. Functions that 
 * operate on NodeImpl are defined as static member functions of Node.
 */
struct NodeImpl
{
    /// Reference count.
    Ionflux::ObjectBase::UInt16 refCount;
    /// Location code.
    Ionflux::VolGfx::NodeLoc3 loc;
    /// Valid mask.
    Ionflux::VolGfx::NodeChildMask valid;
    /// Leaf mask.
    Ionflux::VolGfx::NodeChildMask leaf;
    /// Parent pointer.
    Ionflux::VolGfx::NodeImpl* parent;
    /// Data pointer.
    Ionflux::VolGfx::NodeDataImpl* data;
    /// Child pointer.
    Ionflux::VolGfx::NodeImpl* child;
};

/// Vector of node implementations.
typedef std::vector<Ionflux::VolGfx::NodeImpl*> NodeImplVector;

/// Vector of node data implementations.
typedef std::vector<Ionflux::VolGfx::NodeDataImpl*> NodeDataImplVector;

/// Vector of nodes.
typedef std::vector<Ionflux::VolGfx::Node*> NodeVector;

/// Vector of node implementations.
typedef std::deque<Ionflux::VolGfx::NodeImpl*> NodeImplQueue;

/// Cylinder.
struct Cylinder
{
    /// Center point.
    Ionflux::GeoUtils::Vector3 center;
    /// Direction vector.
    Ionflux::GeoUtils::Vector3 direction;
    /// Length.
    double length;
    /// Radius.
    double radius;
};

/// Plane.
struct Plane
{
    /// Base point.
    Ionflux::GeoUtils::Vector3 p;
    /// Normal vector.
    Ionflux::GeoUtils::Vector3 normal;
};

/// Triangle.
struct Triangle
{
    /// Vertex coordinate (0).
    Ionflux::GeoUtils::Vector3 v0;
    /// Vertex coordinate (1).
    Ionflux::GeoUtils::Vector3 v1;
    /// Vertex coordinate (2).
    Ionflux::GeoUtils::Vector3 v2;
};

/// Separability ID.
typedef int SeparabilityID;

/** Node ID
 * An ID that uniquely identifies a node within an octree.
 */
struct NodeID
{
    /// Node location.
    Ionflux::VolGfx::NodeLoc3 loc;
    /// Node depth level.
    int depth;
};

/** Triangle voxelization data.
 *
 * see Huang 1998, An Accurate Method for Voxelizing Polygon Meshes
 */
struct TriangleVoxelizationData
{
    /// Voxel size.
    double voxelSize;
    /// Triangle.
    Ionflux::VolGfx::Triangle tri;
    /// Center plane.
    Ionflux::VolGfx::Plane plane;
    /// Separability.
    Ionflux::VolGfx::SeparabilityID sep;
    /// Maximum distance to voxel center (t).
    double t;
    /// Maximum distance to vertex (R_c).
    double r_c;
    /// Upper offset plane.
    Ionflux::VolGfx::Plane planeU;
    /// Lower offset plane.
    Ionflux::VolGfx::Plane planeL;
    /// Edge plane (0).
    Ionflux::VolGfx::Plane planeE0;
    /// Edge plane (1).
    Ionflux::VolGfx::Plane planeE1;
    /// Edge plane (0).
    Ionflux::VolGfx::Plane planeE2;
    /// Edge cylinder (0).
    Ionflux::VolGfx::Cylinder cylE0;
    /// Edge cylinder (1).
    Ionflux::VolGfx::Cylinder cylE1;
    /// Edge cylinder (2).
    Ionflux::VolGfx::Cylinder cylE2;
    /// Lowest containing node ID.
    Ionflux::VolGfx::NodeID node;
};

/// Voxelization target ID.
typedef int VoxelizationTargetID;

/// Node implementation hierarchy header.
struct NodeImplHierarchyHeader
{
    /// Pointer/offset map offset.
    Ionflux::ObjectBase::DataSize poMapOffset;
    /// Node implementation array stride.
    Ionflux::ObjectBase::UInt16 implArrayStride;
    /// Node implementation serialized size.
    Ionflux::ObjectBase::UInt16 implSize;
    /// Node data implementation serialized size.
    Ionflux::ObjectBase::UInt16 dataImplSize;
    /// Node data value serialized size.
    Ionflux::ObjectBase::UInt8 dataValueSize;
    /// Root node depth.
    Ionflux::ObjectBase::UInt8 rootNodeDepth;
    /// Root node pointer.
    Ionflux::ObjectBase::GenericPointer rootNodePointer;
};

/// Voxel class ID.
typedef Ionflux::ObjectBase::UInt8 VoxelClassID;

/// Node processing result ID.
typedef Ionflux::ObjectBase::UInt64 NodeProcessingResultID;

/** Node intersection.
 * 
 * A data record that stores information about a ray/node intersection.
 */
struct NodeIntersection
{
    /// Intersection.
    Ionflux::GeoUtils::AAPlanePairIntersection intersection;
    /// Node implementation.
    Ionflux::VolGfx::NodeImpl* nodeImpl;
    /// Node depth.
    int depth;
    /// Face mask for intersected faces.
    Ionflux::VolGfx::FaceMaskInt faces;
};

/// Vector of node intersections.
typedef std::vector<Ionflux::VolGfx::NodeIntersection> 
    NodeIntersectionVector;

/// Voxel class/color mapping.
struct VoxelClassColor
{
    /// Voxel class.
    Ionflux::VolGfx::VoxelClassID voxelClass;
    /// Color.
    Ionflux::Altjira::Color* color;
};

/// Vector of node intersections.
typedef std::vector<Ionflux::VolGfx::VoxelClassColor> 
    VoxelClassColorVector;

/// Color index.
typedef Ionflux::ObjectBase::Int16 ColorIndex;

/** Voxel data (inside/outside/boundary).
 * 
 * A data record that can be attached to nodes to record data for 
 * inside/outside/boundary classification.
 */
struct VoxelDataIOB
{
    /// Voxel class.
    Ionflux::VolGfx::VoxelClassID voxelClass;
    /// Number of surface intersections (direction 0).
    Ionflux::ObjectBase::UInt16 numInts0;
    /// Number of surface intersections (direction 1).
    Ionflux::ObjectBase::UInt16 numInts1;
    /// Number of votes (inside).
    Ionflux::ObjectBase::UInt16 votesInside;
    /// Number of votes (outside).
    Ionflux::ObjectBase::UInt16 votesOutside;
    /// Boundary faces.
    Ionflux::VolGfx::FaceMaskInt boundaryFaces;
    /// Wall thickness (X).
    Ionflux::ObjectBase::UInt16 wallThicknessX;
    /// Wall thickness (Y).
    Ionflux::ObjectBase::UInt16 wallThicknessY;
    /// Wall thickness (Z).
    Ionflux::ObjectBase::UInt16 wallThicknessZ;
    /// Color index.
    Ionflux::VolGfx::ColorIndex color;
};

/// Leaf status ID.
typedef Ionflux::ObjectBase::UInt8 LeafStatusID;

/// Merge policy ID.
typedef Ionflux::ObjectBase::UInt8 MergePolicyID;

/// Flags for node intersection processing.
struct NodeIntersectionProcessingFlags
{
    /// Backward iteration.
    bool directionBackward;
    /// Enable boundary classification.
    bool enableBoundaryData;
    /// Cast ray votes for interior/exterior classification.
    bool castVotes;
    /// Enable ray-stabbing pass for interior/exterior classification.
    bool enableRayStabbing;
    /// Enable wall thickness calculation.
    bool enableWallThickness;
};

}

}

/** \file types.hpp
 * \brief Types (header).
 */
#endif
