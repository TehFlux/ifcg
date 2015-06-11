#ifndef IONFLUX_VOLGFX_UTILS
#define IONFLUX_VOLGFX_UTILS
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utils.hpp                     Utility functions (header).
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
#include <string>
#include "ifobject/types.hpp"
#include "ifvg/types.hpp"
#include "ifvg/constants.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Vector3;
class VertexAttribute;

}

namespace VolGfx
{

class Context;

/// Create node location code (3D).
Ionflux::VolGfx::NodeLoc3 createLoc(Ionflux::VolGfx::NodeLoc x = 0, 
    Ionflux::VolGfx::NodeLoc y = 0, Ionflux::VolGfx::NodeLoc z = 0);

/// Create region (3D).
Ionflux::VolGfx::Region3 createRegion(Ionflux::VolGfx::NodeLoc3 l0, 
    Ionflux::VolGfx::NodeLoc3 l1);

/// Create node ID.
Ionflux::VolGfx::NodeID createNodeID(int depth = DEPTH_UNSPECIFIED, 
    const Ionflux::VolGfx::NodeLoc3* loc = 0);

/// Create node ID.
Ionflux::VolGfx::NodeImplHierarchyHeader createNodeImplHierarchyHeader(
    Ionflux::ObjectBase::DataSize poMapOffset = 
        Ionflux::ObjectBase::DATA_SIZE_INVALID, 
    Ionflux::ObjectBase::UInt16 implArrayStride = 0, 
    Ionflux::ObjectBase::UInt16 implSize = 0, 
    Ionflux::ObjectBase::UInt16 dataImplSize = 0, 
    Ionflux::ObjectBase::UInt8 dataValueSize = 0, 
    Ionflux::ObjectBase::UInt8 rootNodeDepth = 0, 
    Ionflux::ObjectBase::GenericPointer rootNodePointer = 0);

/// Create node intersection.
Ionflux::VolGfx::NodeIntersection createNodeIntersection(
    const Ionflux::GeoUtils::AAPlanePairIntersection* intersection = 0, 
    Ionflux::VolGfx::NodeImpl* nodeImpl = 0, 
    int depth = DEPTH_UNSPECIFIED);

/// Create voxel data (inside/outside/boundary).
Ionflux::VolGfx::VoxelDataIOB createVoxelDataIOB(
    Ionflux::VolGfx::VoxelClassID voxelClass = VOXEL_CLASS_UNDEFINED, 
    Ionflux::ObjectBase::UInt16 numInts0 = 0, 
    Ionflux::ObjectBase::UInt16 numInts1 = 0,
    Ionflux::ObjectBase::UInt16 votesInside = 0, 
    Ionflux::ObjectBase::UInt16 votesOutside = 0, 
    Ionflux::VolGfx::FaceMaskInt boundaryFaces = FACE_UNDEFINED, 
    Ionflux::ObjectBase::UInt16 wallThicknessX = 0, 
    Ionflux::ObjectBase::UInt16 wallThicknessY = 0, 
    Ionflux::ObjectBase::UInt16 wallThicknessZ = 0, 
    Ionflux::VolGfx::ColorIndex color = COLOR_INDEX_UNSPECIFIED);

/// Create flags for node intersection processing.
Ionflux::VolGfx::NodeIntersectionProcessingFlags 
    createNodeIntersectionProcessingFlags(
        bool directionBackward = false, bool enableBoundaryData = false, 
        bool castVotes = true, bool enableRayStabbing = false, 
        bool enableWallThickness = false);

/// Comparison operator.
bool operator==(const Ionflux::VolGfx::NodeIntersection& i0, 
    const Ionflux::VolGfx::NodeIntersection& i1);

/// Get node location string.
std::string getLocString(const Ionflux::VolGfx::NodeLoc& loc);

/// Get node location string (3D).
std::string getLocString(const Ionflux::VolGfx::NodeLoc3& loc);

/** Get node location value string.
 * 
 * Get a string representation for a node location code. The string 
 * representation can include the binary location code, the integer location 
 * index and the location vector for the node location, depending on which 
 * of the \c showMask, \c showIndex, \c showVec flags are set. Note that the 
 * location vector can be shown only if \c context is not null.
 * 
 * \param loc node location
 * \param showCode show the node location code
 * \param showIndex show the node index
 * \param showVec show the node location vector
 * \param context voxel tree context
 * 
 * \return string representation
 */
std::string getLocValueString(const Ionflux::VolGfx::NodeLoc& loc, 
    bool showCode = true, bool showIndex = false, 
    bool showVec = false, Ionflux::VolGfx::Context* context = 0);

/** Get node location value string (3D).
 * 
 * Get a string representation for a node location code (3D). The string 
 * representation can include the binary location code, the integer location 
 * index and the location vector for the node location, depending on which 
 * of the \c showMask, \c showIndex, \c showVec flags are set. Note that the 
 * location vector can be shown only if \c context is not null.
 * 
 * \param loc node location (3D)
 * \param showCode show the node location code
 * \param showIndex show the node index
 * \param showVec show the node location vector
 * \param context voxel tree context
 * 
 * \return string representation
 */
std::string getLocValueString(const Ionflux::VolGfx::NodeLoc3& loc, 
    bool showCode = true, bool showIndex = false, 
    bool showVec = false, Ionflux::VolGfx::Context* context = 0);

/// Get region string (3D).
std::string getRegionString(const Ionflux::VolGfx::Region3& region);

/// Get cylinder string.
std::string getCylinderString(const Ionflux::VolGfx::Cylinder& c);

/// Get plane string.
std::string getPlaneString(const Ionflux::VolGfx::Plane& p);

/// Get triangle string.
std::string getTriangleString(const Ionflux::VolGfx::Triangle& tri);

/// Get depth string.
std::string getDepthString(int d);

/// Get node ID string.
std::string getNodeIDString(const Ionflux::VolGfx::NodeID& nodeID);

/** Get node ID value string.
 * 
 * Get a string representation for a node ID.
 * 
 * \param nodeID node ID
 * \param showCode show the node location code
 * \param showIndex show the node index
 * \param showVec show the node location vector
 * \param context voxel tree context
 * 
 * \return string representation
 * 
 * \sa getLocValueString()
 */
std::string getNodeIDValueString(const Ionflux::VolGfx::NodeID& nodeID, 
    bool showCode = true, bool showIndex = false, 
    bool showVec = false, Ionflux::VolGfx::Context* context = 0);

/// Get triangle voxelization data string.
std::string getTriangleVoxelizationDataString(
    const Ionflux::VolGfx::TriangleVoxelizationData& d);

/// Print triangle voxelization data debug info.
void printTriangleVoxelizationDataDebugInfo(
    const Ionflux::VolGfx::TriangleVoxelizationData& d);

/// Get node implementation hierarchy string.
std::string getNodeImplHierarchyHeaderValueString(
    const Ionflux::VolGfx::NodeImplHierarchyHeader& h);

/// Get voxelization target string.
std::string getVoxelizationTargetValueString(
    Ionflux::VolGfx::VoxelizationTargetID t);

/// Get voxel class string.
std::string getVoxelClassValueString(Ionflux::VolGfx::VoxelClassID t);

/// Get string representation for node intersection.
std::string getNodeIntersectionValueString(
    Ionflux::VolGfx::Context& context, 
    const Ionflux::VolGfx::NodeIntersection& i0);

/// Get string representation for face mask.
std::string getFaceMaskValueString(Ionflux::VolGfx::FaceMaskInt mask);

/// Get string representation for voxel data (inside/outside/boundary).
std::string getVoxelDataIOBValueString(
    const Ionflux::VolGfx::VoxelDataIOB& data);

/// Get string representation for leaf status.
std::string getLeafStatusValueString(Ionflux::VolGfx::LeafStatusID s);

/// Get string representation for merge policy.
std::string getMergePolicyValueString(Ionflux::VolGfx::MergePolicyID p);

/** Calculate point to plane distance.
 *
 * Calculate the signed distance between a point and a plane.
 *
 * \param v point coordinate vector
 * \param p plane
 *
 * \return signed distance value
 */
double distanceToPlane(const Ionflux::GeoUtils::Vector3& v, 
    const Ionflux::VolGfx::Plane& p);

/** Calculate point to sphere distance.
 *
 * Calculate the signed distance between a point and a sphere surface.
 *
 * \param v point coordinate vector
 * \param cs sphere center
 * \param rs sphere radius
 *
 * \return signed distance value
 */
double distanceToSphere(const Ionflux::GeoUtils::Vector3& v, 
    const Ionflux::GeoUtils::Vector3& cs, double rs);

/** Calculate point to spherically capped cylinder distance.
 *
 * Calculate the signed distance between a point and a spherically capped 
 * cylinder. The cylinder is assumed to be capped with half-spheres of the 
 * same radius as the cylinder at its end surfaces.
 *
 * \param v point coordinate vector
 * \param c sphere capped cylinder
 *
 * \return signed distance value
 */
double distanceToCylinderSC(const Ionflux::GeoUtils::Vector3& v, 
    const Ionflux::VolGfx::Cylinder& c);

/** Voxelize point test.
 *
 * Test if a voxel with the specified center point coordinates should be 
 * included in the voxelization, using the specified triangle voxelization 
 * data.
 *
 * \param d triangle voxelization data
 * \param v point coordinate vector
 */
bool voxelizePointTest(
    const Ionflux::VolGfx::TriangleVoxelizationData& d, 
    const Ionflux::GeoUtils::Vector3& v);

/** Voxelize point test (debug).
 *
 * Test if a voxel with the specified center point coordinates should be 
 * included in the voxelization, using the specified triangle voxelization 
 * data.
 *
 * \param d triangle voxelization data
 * \param v point coordinate vector
 */
bool voxelizePointTestDebug(
    const Ionflux::VolGfx::TriangleVoxelizationData& d, 
    const Ionflux::GeoUtils::Vector3& v);

/** Pack voxel class ID into node data pointer.
 * 
 * Pack a voxel class ID into a node data pointer for compact storage.
 * 
 * \param c voxel class ID
 * \param target target pointer
 */
void packVoxelClass(Ionflux::VolGfx::VoxelClassID c, 
    Ionflux::VolGfx::NodeDataPointer& target);

/** Pack voxel class ID into node data pointer.
 * 
 * Pack a voxel class ID into a node data pointer for compact storage.
 * 
 * \param c voxel class ID
 * \param target target pointer
 */
void packVoxelClass(Ionflux::VolGfx::VoxelClassID c, 
    Ionflux::VolGfx::NodeDataPointer& target);

/** Unpack voxel class ID from node data pointer.
 * 
 * Unpack a voxel class ID from a node data pointer.
 * 
 * \param source source pointer
 * \param c voxel class ID
 */
void unpackVoxelClass(Ionflux::VolGfx::NodeDataPointer source, 
    Ionflux::VolGfx::VoxelClassID& c);

/** Set voxel class ID.
 * 
 * Set the specified voxel class ID mask on the target voxel class ID. If 
 * \c enable is \c false, the specified voxel class ID mask will be unset.
 * 
 * \param c voxel class ID mask
 * \param target target voxel class ID
 * \param enable enable flag
 */
void setVoxelClass(Ionflux::VolGfx::VoxelClassID c, 
    Ionflux::VolGfx::VoxelClassID& target, bool enable = true);

/** Check voxel class IDs.
 * 
 * Check if the specified voxel class ID mask is set on the source voxel 
 * class ID.
 * 
 * \param source voxel class ID
 * \param mask voxel class ID mask
 *
 * \return \c true if the source voxel class matches the specified mask, 
 * \c false otherwise.
 */
bool checkVoxelClass(Ionflux::VolGfx::VoxelClassID source, 
    Ionflux::VolGfx::VoxelClassID mask);

/// Comparison object for node intersection.
struct NodeIntersectionCompare
{
    /// Comparison operator.
    bool operator()(const NodeIntersection& i0, 
        const NodeIntersection& i1);
};

/** Get color for voxel class.
 * 
 * Get a color for the specified voxel class from the specified voxel 
 * class color vector. This function returns the color of the first entry in 
 * \c colors that matches one of the voxel classes set in \c c.
 *
 * \param colors voxel class color vector
 * \param c voxel class
 *
 * \return color, or 0 if no matching color mapping exists for the voxel 
 * class.
 */
Ionflux::Altjira::Color* getVoxelClassColor(
    const Ionflux::VolGfx::VoxelClassColorVector& colors, 
    Ionflux::VolGfx::VoxelClassID c);

/** Clamp node location code.
 * 
 * Clamp a node location code to the specified range.
 * 
 * \param loc node location
 * \param rMin range minimum value
 * \param rMax range maximum value
 * 
 * \return clamped node location code
 */
Ionflux::VolGfx::NodeLoc clampLoc(
    const Ionflux::VolGfx::NodeLoc& loc, 
    const Ionflux::VolGfx::NodeLoc& rMin, 
    const Ionflux::VolGfx::NodeLoc& rMax);

/** Clamp node location code (3D).
 * 
 * Clamp a node location code to the specified region.
 * 
 * \param loc node location
 * \param region region
 * 
 * \return clamped node location code
 */
Ionflux::VolGfx::NodeLoc3 clampLoc3(
    const Ionflux::VolGfx::NodeLoc3& loc, 
    const Ionflux::VolGfx::Region3& region);

/** Check face mask.
 * 
 * Check if the specified face mask is set on the source face mask.
 * 
 * \param source face mask
 * \param mask face mask to be checked
 *
 * \return \c true if the source face mask matches the specified mask, 
 * \c false otherwise.
 */
bool checkFaceMask(Ionflux::VolGfx::FaceMaskInt source, 
    Ionflux::VolGfx::FaceMaskInt mask);

/** Get number of faces set.
 * 
 * Get the number of faces set in the face mask.
 * 
 * \param mask face mask
 * 
 * \return number of faces set in the face mask.
 */
unsigned int getNumFacesSet(Ionflux::VolGfx::FaceMaskInt mask);

/** Set vertex attribute data (triangle position).
 * 
 * Set the vertex attribute data for a triangle position on the specified 
 * target vertex attribute.
 *
 * \param target vertex attribute
 * \param elementIndex element index of the first vertex
 * \param v0 vertex position (0)
 * \param v1 vertex position (1)
 * \param v2 vertex position (2)
 * \param reverse reverse winding order of the triangle
 */
void setVertexAttributeTrianglePos(
    Ionflux::GeoUtils::VertexAttribute& target, 
    unsigned int elementIndex, const Ionflux::GeoUtils::Vector3& v0, 
    const Ionflux::GeoUtils::Vector3& v1, 
    const Ionflux::GeoUtils::Vector3& v2, bool reverse = false);

/** Set voxel inside/outside/boundary data wall thickness.
 * 
 * Set the wall thickness value for the specified axis on the specified 
 * voxel inside/outside/boundary data record.
 * 
 * \param data voxel IOB data
 * \param axis axis
 * \param v wall thickness
 */
void setIOBDataWallThickness(Ionflux::VolGfx::VoxelDataIOB& data, 
    Ionflux::GeoUtils::AxisID axis, Ionflux::ObjectBase::UInt16 v);

/// Get voxel inside/outside/boundary data wall thickness.
Ionflux::ObjectBase::UInt16 getIOBDataWallThickness(
    const Ionflux::VolGfx::VoxelDataIOB& data, 
    Ionflux::GeoUtils::AxisID axis);

/** Get voxel inside/outside/boundary data minimum wall thickness.
 * 
 * Get the minimum (non-zero) value for wall thickness for the specified 
 * inside/outside/boundary data record. If \c axis is specified, the axis 
 * on which the minimum value occurs is stored at the specified location.
 * 
 * \param data voxel IOB data
 * \param axis where to store the minimum value axis
 * 
 * \return minimum wall thickness
 */
Ionflux::ObjectBase::UInt16 getIOBDataWallThicknessMin(
    const Ionflux::VolGfx::VoxelDataIOB& data, 
    Ionflux::GeoUtils::AxisID* axis = 0);

/** Get color index.
 * 
 * Get a color index by mapping the specified value range onto the 
 * specified color index range. COLOR_INDEX_UNSPECIFIED will be returned if 
 * either one of the ranges is not valid.
 * 
 * \param v value
 * \param vMin value range minimum
 * \param vMax value range maximum
 * \param minColorIndex color index minimum
 * \param maxColorIndex color index maximum
 * 
 * \return color index
 */
Ionflux::VolGfx::ColorIndex getColorIndex(
    Ionflux::ObjectBase::UInt16 v, 
    Ionflux::ObjectBase::UInt16 vMin, 
    Ionflux::ObjectBase::UInt16 vMax, 
    Ionflux::VolGfx::ColorIndex minColorIndex, 
    Ionflux::VolGfx::ColorIndex maxColorIndex);

}

}

/** \file utils.hpp
 * \brief Utility functions (header).
 */
#endif
