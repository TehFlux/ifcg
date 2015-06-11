#ifndef IONFLUX_VOLGFX_CONTEXT
#define IONFLUX_VOLGFX_CONTEXT
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Context.hpp                     Voxel tree context (header).
 * ========================================================================== */

#include "ifobject/types.hpp"
#include "ifmapping/Point.hpp"
#include "altjira/ColorSet.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/Vector3.hpp"
#include "geoutils/Range3.hpp"
#include "geoutils/Face.hpp"
#include "geoutils/Mesh.hpp"
#include "geoutils/NFace.hpp"
#include "geoutils/VertexAttribute.hpp"
#include "ifvg/types.hpp"
#include "ifvg/constants.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace VolGfx
{

/// Class information for class Context.
class ContextClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ContextClassInfo();
		/// Destructor.
		virtual ~ContextClassInfo();
};

/** Voxel tree context.
 * \ingroup ifvg
 *
 * A context that contains all relevent metadata for a voxel tree. The 
 * context is shared by all Nodes of a tree and is used to obtain global 
 * information about the structure of the tree, such as the maximum depth 
 * of the tree and the scale of the root node.
 */
class Context
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Masks for single location code bit at each depth.
		Ionflux::VolGfx::NodeLoc* depthMask;
		/// Masks for all location code bits up to and including each depth.
		Ionflux::VolGfx::NodeLoc* locMask;
		/// Voxel size for each depth.
		double* voxelSize;
		/// Voxel diagonal vectors.
		static Ionflux::GeoUtils::Vector3* voxelDiag;
		/// Voxel face normals.
		static Ionflux::GeoUtils::Vector3* voxelNormal;
		/// Maximum number of levels.
		int maxNumLevels;
		/// Order (number of children per non-leaf node and dimension).
		int order;
		/// Tolerance for comparisons.
		double tolerance;
		/// Mask for valid bits from a location code.
		Ionflux::VolGfx::NodeLoc validBits;
		/// Maximum number of leaf child nodes per node.
		int maxNumLeafChildNodesPerNode;
		/// Maximum number of leaf child nodes per dimension.
		int maxNumLeafChildNodesPerDimension;
		/// Length scale factor.
		double scale;
		
		/** Clear masks.
		 *
		 * Clear bit masks.
		 */
		virtual void clearMasks();
		
		/** Clear voxel size buffer.
		 *
		 * Clear voxel size buffer.
		 */
		virtual void clearVoxelSize();
		
		/** Set maximum number of leaf child nodes per node.
		 *
		 * Set new value of maximum number of leaf child nodes per node.
		 *
		 * \param newMaxNumLeafChildNodesPerNode New value of maximum number of 
		 * leaf child nodes per node.
		 */
		virtual void setMaxNumLeafChildNodesPerNode(int 
		newMaxNumLeafChildNodesPerNode);
		
		/** Set maximum number of leaf child nodes per dimension.
		 *
		 * Set new value of maximum number of leaf child nodes per dimension.
		 *
		 * \param newMaxNumLeafChildNodesPerDimension New value of maximum number
		 * of leaf child nodes per dimension.
		 */
		virtual void setMaxNumLeafChildNodesPerDimension(int 
		newMaxNumLeafChildNodesPerDimension);
		
	public:
		/// Maximum number of tree levels.
		static const int MAX_NUM_LEVELS;
		/// Default maximum number of tree levels.
		static const int DEFAULT_MAX_NUM_LEVELS;
		/// Default order.
		static const int DEFAULT_ORDER;
		/// Default box inset.
		static const double DEFAULT_BOX_INSET;
		/// Class information instance.
		static const ContextClassInfo contextClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Context object.
		 */
		Context();
		
		/** Constructor.
		 *
		 * Construct new Context object.
		 *
		 * \param other Other object.
		 */
		Context(const Ionflux::VolGfx::Context& other);
		
		/** Constructor.
		 *
		 * Construct new Context object.
		 *
		 * \param initMaxNumLevels Maximum number of levels.
		 * \param initOrder Order.
		 * \param initScale Length scale factor.
		 * \param initTolerance Tolerance for comparisons.
		 */
		Context(int initMaxNumLevels, int initOrder = DEFAULT_ORDER, double 
		initScale = 1., double initTolerance = DEFAULT_TOLERANCE);
		
		/** Destructor.
		 *
		 * Destruct Context object.
		 */
		virtual ~Context();
		
		/** Clear.
		 *
		 * Clear all data in the context.
		 */
		virtual void clear();
		
		/** Update.
		 *
		 * Update the context metadata.
		 */
		virtual void update();
		
		/** Create node location code.
		 *
		 * Create a node location code for the specified value.
		 *
		 * \param v value.
		 * \param checkBounds0 check bounds.
		 *
		 * \return Node location code.
		 */
		virtual Ionflux::VolGfx::NodeLoc createLoc(double v, bool checkBounds0 = 
		true);
		
		/** Create node location code (3D).
		 *
		 * Create a node location code for the specified coordinate values.
		 *
		 * \param x X coordinate.
		 * \param y Y coordinate.
		 * \param z Z coordinate.
		 * \param checkBounds0 check bounds.
		 *
		 * \return Node location code.
		 */
		virtual Ionflux::VolGfx::NodeLoc3 createLoc(double x, double y, double z,
		bool checkBounds0 = true);
		
		/** Create node location code (3D).
		 *
		 * Create a node location code for the specified coordinate vector.
		 *
		 * \param v Vector.
		 * \param checkBounds0 check bounds.
		 *
		 * \return Node location code.
		 */
		virtual Ionflux::VolGfx::NodeLoc3 createLoc(const 
		Ionflux::GeoUtils::Vector3& v, bool checkBounds0 = true);
		
		/** Create node location code (3D).
		 *
		 * Create a node location code for the specified coordinate vector.
		 *
		 * \param p Point.
		 * \param checkBounds0 check bounds.
		 *
		 * \return Node location code.
		 */
		virtual Ionflux::VolGfx::NodeLoc3 createLoc(const 
		Ionflux::Mapping::Point& p, bool checkBounds0 = true);
		
		/** Create region (3D).
		 *
		 * Create a region for the specified range.
		 *
		 * \param r Range.
		 *
		 * \return Node location code.
		 */
		virtual Ionflux::VolGfx::Region3 createRegion(const 
		Ionflux::GeoUtils::Range3& r);
		
		/** Location equality check.
		 *
		 * Check whether two node location codes are equal. If \c maxDepth is 
		 * larger than -1, the location codes will be compared only up to and 
		 * including this depth.
		 *
		 * \param loc0 Node location code (0).
		 * \param loc1 Node location code (1).
		 * \param maxDepth Maximum depth.
		 *
		 * \return \c true if the location codes are equal, \c false otherwise.
		 */
		virtual bool locEqual(const Ionflux::VolGfx::NodeLoc& loc0, const 
		Ionflux::VolGfx::NodeLoc& loc1, int maxDepth = DEPTH_UNSPECIFIED);
		
		/** Location equality check (3D).
		 *
		 * Check whether two node location codes are equal. If \c maxDepth is 
		 * larger than -1, the location codes will be compared only up to and 
		 * including this depth.
		 *
		 * \param loc0 Node location code (0).
		 * \param loc1 Node location code (1).
		 * \param maxDepth Maximum depth.
		 *
		 * \return \c true if the location codes are equal, \c false otherwise.
		 */
		virtual bool locEqual(const Ionflux::VolGfx::NodeLoc3& loc0, const 
		Ionflux::VolGfx::NodeLoc3& loc1, int maxDepth = DEPTH_UNSPECIFIED);
		
		/** Get child order index.
		 *
		 * Get the index of the child node with the specified location code on
		 * the specified depth level.
		 *
		 * \param loc Location code.
		 * \param depth Depth level.
		 *
		 * \return \c true if the child with the specified index is a leaf node, 
		 * \c false otherwise.
		 */
		virtual int getChildOrderIndex(const Ionflux::VolGfx::NodeLoc3& loc, int 
		depth) const;
		
		/** Get common ancestor level.
		 *
		 * Get the level of the deepest common ancestor of the two location 
		 * codes. If \c maxDepth not negative, this level will be returned 
		 * instead, if the actual level of the deepest common ancestor node is
		 * below that level.
		 *
		 * \param loc0 Location code (0).
		 * \param loc1 Location code (1).
		 * \param maxDepth Maximum depth.
		 *
		 * \return Level of the deepest common ancestor node of the specified 
		 * locations.
		 */
		virtual int getCommonAncestorLevel(const Ionflux::VolGfx::NodeLoc3& loc0,
		const Ionflux::VolGfx::NodeLoc3& loc1, int maxDepth = DEPTH_UNSPECIFIED) 
		const;
		
		/** Get common ancestor level.
		 *
		 * Get the level of the deepest common ancestor of the two location 
		 * codes. If \c maxDepth is not negative, this level will be returned 
		 * instead, if the actual level of the deepest common ancestor node is
		 * below that level.
		 *
		 * \param region Region.
		 * \param maxDepth Maximum depth.
		 *
		 * \return Level of the deepest common ancestor node of the specified 
		 * locations.
		 */
		virtual int getCommonAncestorLevel(const Ionflux::VolGfx::Region3& 
		region, int maxDepth = DEPTH_UNSPECIFIED) const;
		
		/** Get depth mask.
		 *
		 * Get the depth mask for the specified depth.
		 *
		 * \param depth Depth.
		 *
		 * \return Depth mask.
		 */
		virtual Ionflux::VolGfx::NodeLoc getDepthMask(int depth) const;
		
		/** Get location mask.
		 *
		 * Get the location mask for the specified depth.
		 *
		 * \param depth Depth.
		 *
		 * \return Location mask.
		 */
		virtual Ionflux::VolGfx::NodeLoc getLocMask(int depth);
		
		/** Get voxel size.
		 *
		 * Get the size (edge length) of a voxel at the specified depth.
		 *
		 * \param depth Depth.
		 *
		 * \return Voxel size.
		 */
		virtual double getVoxelSize(int depth = 0);
		
		/** Get minimum leaf voxel size.
		 *
		 * Get the size (edge length) of a leaf voxel at the maximum depth 
		 * level of the octree.
		 *
		 * \return Leaf voxel size.
		 */
		virtual double getMinLeafSize();
		
		/** Get location.
		 *
		 * Get the location vector for the specified location code.
		 *
		 * \param loc Location code.
		 * \param target Where to store the location data.
		 */
		virtual void getLocation(const Ionflux::VolGfx::NodeLoc3& loc, 
		Ionflux::GeoUtils::Vector3& target);
		
		/** Get location.
		 *
		 * Get the location vector for the specified location code.
		 *
		 * \param loc Voxel location code.
		 *
		 * \return Location vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getLocation0(const 
		Ionflux::VolGfx::NodeLoc3& loc);
		
		/** Get voxel location.
		 *
		 * Get the location vector for the voxel with the specified 
		 * coordinates at the specified level.
		 *
		 * \param loc Voxel location code.
		 * \param depth Voxel depth.
		 * \param target Where to store the location data.
		 */
		virtual void getVoxelLocation(const Ionflux::VolGfx::NodeLoc3& loc, int 
		depth, Ionflux::GeoUtils::Vector3& target);
		
		/** Get voxel location.
		 *
		 * Get the location vector for the voxel with the specified 
		 * coordinates at the specified level. This is the location of the 
		 * lower left front corner of the voxel.
		 *
		 * \param loc Voxel location code.
		 * \param depth Voxel depth.
		 *
		 * \return Voxel location vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getVoxelLocation0(const 
		Ionflux::VolGfx::NodeLoc3& loc, int depth);
		
		/** Get voxel location.
		 *
		 * Get the location vector for the voxel with the specified 
		 * coordinates at the specified level. This is the location of the 
		 * lower left front corner of the voxel.
		 *
		 * \param node Node ID.
		 * \param target Where to store the location data.
		 */
		virtual void getVoxelLocation(const Ionflux::VolGfx::NodeID& node, 
		Ionflux::GeoUtils::Vector3& target);
		
		/** Get voxel range.
		 *
		 * Get the range of values contained by the voxel with the specified 
		 * coordinates at the specified level.
		 *
		 * \param loc Voxel location code.
		 * \param depth Voxel depth.
		 * \param target Where to store the range data.
		 */
		virtual void getVoxelRange(const Ionflux::VolGfx::NodeLoc3& loc, int 
		depth, Ionflux::GeoUtils::Range3& target);
		
		/** Get voxel range.
		 *
		 * Get the range of values contained by the voxel with the specified 
		 * coordinates at the specified level.
		 *
		 * \param node Node ID.
		 * \param target Where to store the range data.
		 */
		virtual void getVoxelRange(Ionflux::VolGfx::NodeID node, 
		Ionflux::GeoUtils::Range3& target);
		
		/** Get voxel region.
		 *
		 * Get the region contained by the voxel with the specified location 
		 * code at the specified level. If \c includeMaxBoundary is \c false, 
		 * the region is defined in such a way that each location code within 
		 * this region is a valid location code of a child voxel of the 
		 * specified voxel. Otherwise, the boundary of maximum extent will be 
		 * included in the region. (Note that location codes for the maximum 
		 * boundary are located within neighboring voxels.)
		 *
		 * \param loc Voxel location code.
		 * \param depth Voxel depth.
		 * \param target Where to store the region data.
		 * \param includeMaxBoundary Include the node maximum boundary in the 
		 * region.
		 */
		virtual void getVoxelRegion(const Ionflux::VolGfx::NodeLoc3& loc, int 
		depth, Ionflux::VolGfx::Region3& target, bool includeMaxBoundary = 
		false);
		
		/** Get voxel region.
		 *
		 * Get the region contained by the voxel with the specified node ID. 
		 * If \c includeMaxBoundary is \c false, the region is defined in such
		 * a way that each location code within this region is a valid 
		 * location code of a child voxel of the specified voxel. Otherwise, 
		 * the boundary of maximum extent will be included in the region. 
		 * (Note that location codes for the maximum boundary are located 
		 * within neighboring voxels.)
		 *
		 * \param node Node ID.
		 * \param target Where to store the region data.
		 * \param includeMaxBoundary Include the node maximum boundary in the 
		 * region.
		 */
		virtual void getVoxelRegion(Ionflux::VolGfx::NodeID node, 
		Ionflux::VolGfx::Region3& target, bool includeMaxBoundary = false);
		
		/** Check location.
		 *
		 * Check whether the specified location code is within the range of 
		 * the tree when adding the specified offset.
		 *
		 * \param loc Location code.
		 * \param offset Offset.
		 *
		 * \return \c true if the location is within range when adding the 
		 * specified offset, \c false otherwise.
		 */
		virtual bool checkLoc(const Ionflux::VolGfx::NodeLoc& loc, int offset = 
		0);
		
		/** Check location.
		 *
		 * Check whether the specified location vector is within the range of 
		 * the tree.
		 *
		 * \param v Location vector.
		 *
		 * \return \c true if the location is within range when adding the 
		 * specified offset, \c false otherwise.
		 */
		virtual bool checkLoc(const Ionflux::GeoUtils::Vector3& v);
		
		/** Check location.
		 *
		 * Check whether the specified location code is within the range of 
		 * the tree when adding the specified offsets.
		 *
		 * \param loc Location code.
		 * \param offsetX Offset (x).
		 * \param offsetY Offset (y).
		 * \param offsetZ Offset (z).
		 *
		 * \return \c true if the location is within range when adding the 
		 * specified offsets, \c false otherwise.
		 */
		virtual bool checkLoc(const Ionflux::VolGfx::NodeLoc3& loc, int offsetX =
		0, int offsetY = 0, int offsetZ = 0);
		
		/** Check region.
		 *
		 * Check whether the specified region is within the range of the tree 
		 * when adding the specified offsets.
		 *
		 * \param region Region.
		 * \param offsetX Offset (x).
		 * \param offsetY Offset (y).
		 * \param offsetZ Offset (z).
		 *
		 * \return \c true if the location is within range when adding the 
		 * specified offsets, \c false otherwise.
		 */
		virtual bool checkRegion(const Ionflux::VolGfx::Region3& region, int 
		offsetX = 0, int offsetY = 0, int offsetZ = 0);
		
		/** Check range.
		 *
		 * Check whether the specified range is within the range of the 
		 * specified node.
		 *
		 * \param range Range.
		 * \param loc Voxel location code.
		 * \param depth Voxel depth.
		 *
		 * \return \c true if the location is within range when adding the 
		 * specified offsets, \c false otherwise.
		 */
		virtual bool checkRange(const Ionflux::GeoUtils::Range3& range, const 
		Ionflux::VolGfx::NodeLoc3& loc, int depth);
		
		/** Check range.
		 *
		 * Check whether the specified range is within the range of the 
		 * specified node.
		 *
		 * \param range Range.
		 * \param node Node ID.
		 *
		 * \return \c true if the location is within range when adding the 
		 * specified offsets, \c false otherwise.
		 */
		virtual bool checkRange(const Ionflux::GeoUtils::Range3& range, 
		Ionflux::VolGfx::NodeID node);
		
		/** Check range.
		 *
		 * Check whether the specified range is within the range of the voxel 
		 * tree.
		 *
		 * \param range Range.
		 *
		 * \return \c true if the location is within range when adding the 
		 * specified offsets, \c false otherwise.
		 */
		virtual bool checkRange(const Ionflux::GeoUtils::Range3& range);
		
		/** Check depth.
		 *
		 * Check whether the specified depth is within the specified range.
		 *
		 * \param depth depth.
		 * \param minDepth minimum depth.
		 * \param maxDepth maximum depth.
		 *
		 * \return \c true if the location is within range when adding the 
		 * specified offsets, \c false otherwise.
		 */
		virtual bool checkDepthRange(int depth, int minDepth = DEPTH_UNSPECIFIED,
		int maxDepth = DEPTH_UNSPECIFIED);
		
		/** Get containing node.
		 *
		 * Get the ID for the deepest node that contains the specified range 
		 * of values.
		 *
		 * \param range range.
		 * \param target where to store the node ID.
		 */
		virtual void getContainingNode(const Ionflux::GeoUtils::Range3& range, 
		Ionflux::VolGfx::NodeID& target);
		
		/** Initialize triangle voxelization data.
		 *
		 * Initialize triangle voxelization data from a GeoUtils::Face, using 
		 * the specified separability and depth level. If \c depth is 
		 * negative, the maximum depth will be used.
		 * 
		 * See Huang 1998, "An Accurate Method for Voxelizing Polygon Meshes" 
		 * for details.
		 *
		 * \param face Face.
		 * \param target triangle voxelization data.
		 * \param sep separability.
		 * \param depth depth.
		 * \param checkBounds0 check bounds.
		 */
		virtual void initTriangleVoxelizationData(const Ionflux::GeoUtils::Face& 
		face, Ionflux::VolGfx::TriangleVoxelizationData& target, 
		Ionflux::VolGfx::SeparabilityID sep = SEPARABILITY_26, int depth = 
		DEPTH_UNSPECIFIED, bool checkBounds0 = true);
		
		/** Print debug information.
		 *
		 * Print debug information.
		 */
		virtual void printDebugInfo() const;
		
		/** Get voxel mesh.
		 *
		 * Get a box mesh for the node with the specified ID. If the optional 
		 * \c colors color set is specified, the vertex colors for the box are
		 * selected from the color set according to the depth level of the 
		 * node and the specified color offset. If \c colorIndex is not 
		 * negative, the specified color index will be used for selecting a 
		 * color from the color set. Boxes will be inset by the amount 
		 * specified in \c boxInset, scaled by the leaf voxel size.
		 *
		 * \param node Node ID.
		 * \param target where to store the mesh.
		 * \param boxInset box inset per depth level.
		 * \param colors vertex colors.
		 * \param colorOffset color index offset.
		 * \param colorIndex color index.
		 */
		virtual void getVoxelMesh(Ionflux::VolGfx::NodeID node, 
		Ionflux::GeoUtils::Mesh& target, double boxInset = DEFAULT_BOX_INSET, 
		Ionflux::Altjira::ColorSet* colors = 0, unsigned int colorOffset = 0, int
		colorIndex = COLOR_INDEX_UNSPECIFIED);
		
		/** Get voxel vertex attributes.
		 *
		 * Get vertex attributes for a box mesh for the node with the 
		 * specified ID. Boxes will be inset by the amount specified in \c 
		 * boxInset, scaled by the leaf voxel size. Data will be appended to a
		 * specified vertex attributes for each target vertex attribute that 
		 * is not null. If the optional \c color is specified, this color is 
		 * used for the vertex colors of the box. If the optional \c 
		 * positionOffset or \c positionScale are specified, vertex positions 
		 * will be scaled or translated by these vectors.
		 *
		 * \param node Node ID.
		 * \param positionTarget target for position data.
		 * \param colorTarget target for color data.
		 * \param normalTarget target for normal data.
		 * \param nFaceType N-face type.
		 * \param boxInset box inset per depth level.
		 * \param color vertex color.
		 * \param positionOffset position offset.
		 * \param positionScale position scale.
		 * \param faces faces to be rendered.
		 * \param flipNormals faces for which the normals should be flipped.
		 */
		virtual void getVoxelVertexAttributes(Ionflux::VolGfx::NodeID node, 
		Ionflux::GeoUtils::VertexAttribute* positionTarget = 0, 
		Ionflux::GeoUtils::VertexAttribute* colorTarget = 0, 
		Ionflux::GeoUtils::VertexAttribute* normalTarget = 0, 
		Ionflux::GeoUtils::NFaceTypeID nFaceType = 
		Ionflux::GeoUtils::NFace::TYPE_FACE, double boxInset = DEFAULT_BOX_INSET,
		Ionflux::Altjira::Color* color = 0, Ionflux::GeoUtils::Vector* 
		positionOffset = 0, Ionflux::GeoUtils::Vector* positionScale = 0, 
		Ionflux::VolGfx::FaceMaskInt faces = FACE_ALL, 
		Ionflux::VolGfx::FaceMaskInt flipNormals = FACE_UNDEFINED);
		
		/** Get line intersection.
		 *
		 * Get the intersection location codes for the specified intersection 
		 * data. If there is a valid intersection, the intersection location 
		 * codes will be stored in \c target. Otherwise, \c target will be 
		 * undefined and the function returns \c false.
		 *
		 * \param line Line.
		 * \param interData Intersection data.
		 * \param target Where to store the intersection location codes.
		 * \param checkBounds0 check bounds.
		 *
		 * \return \c true if the intersection data is valid, \c false otherwise.
		 */
		virtual bool getIntersectionLoc(Ionflux::GeoUtils::Line3& line, const 
		Ionflux::GeoUtils::AAPlanePairIntersection& interData, 
		Ionflux::VolGfx::Region3& target, bool checkBounds0 = true);
		
		/** Get line intersection.
		 *
		 * Get the intersection location codes for the specified intersection 
		 * data and node ID. If there is a valid intersection, the 
		 * intersection location codes will be stored in \c target. Otherwise,
		 * \c target will be undefined and the function returns \c false. If 
		 * \c clampToNodeRegion is true, this function ensures that the 
		 * intersection locations will be located within the region as 
		 * returned by getVoxelRegion().
		 *
		 * \param node Node.
		 * \param line Line.
		 * \param interData Intersection data.
		 * \param target Where to store the intersection location codes.
		 * \param clampToNodeRegion Clamp values to node region.
		 * \param includeMaxBoundary Include the node maximum boundary in the 
		 * region.
		 *
		 * \return \c true if the intersection data is valid, \c false otherwise.
		 */
		virtual bool getIntersectionLoc(const Ionflux::VolGfx::NodeID& node, 
		Ionflux::GeoUtils::Line3& line, const 
		Ionflux::GeoUtils::AAPlanePairIntersection& interData, 
		Ionflux::VolGfx::Region3& target, bool clampToNodeRegion = true, bool 
		includeMaxBoundary = false);
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Get voxel diagonal vector.
		 *
		 * Get the voxel diagonal unit vector with the specified index.
		 *
		 * \param index index.
		 *
		 * \return Voxel diagonal unit vector.
		 */
		static Ionflux::GeoUtils::Vector3* getVoxelDiag(int index);
		
		/** Get voxel diagonal vector.
		 *
		 * Get the voxel diagonal unit vector with the specified indices.
		 *
		 * \param x index (x).
		 * \param y index (y).
		 * \param z index (z).
		 *
		 * \return Voxel diagonal unit vector.
		 */
		static Ionflux::GeoUtils::Vector3* getVoxelDiag(int x, int y, int z);
		
		/** Clean up voxel diagonal vectors.
		 *
		 * Clean up the global voxel diagonal vectors.
		 */
		static void cleanupVoxelDiag();
		
		/** Get matching voxel diagonal vector.
		 *
		 * Get the voxel diagonal unit vector that best matches the specified 
		 * vector.
		 *
		 * \param v vector.
		 *
		 * \return Matching voxel diagonal vector.
		 */
		static Ionflux::GeoUtils::Vector3* getMatchingVoxelDiag(const 
		Ionflux::GeoUtils::Vector3& v);
		
		/** Get voxel face normal vector.
		 *
		 * Get the voxel face normal vector with the specified index.
		 *
		 * \param index index.
		 *
		 * \return Voxel face normal vector.
		 */
		static Ionflux::GeoUtils::Vector3* getVoxelNormal(int index);
		
		/** Get matching voxel face normal vector.
		 *
		 * Get the voxel face normal vector that best matches the specified 
		 * vector.
		 *
		 * \param v vector.
		 *
		 * \return Matching voxel face normal vector.
		 */
		static Ionflux::GeoUtils::Vector3* getMatchingVoxelNormal(const 
		Ionflux::GeoUtils::Vector3& v);
		
		/** Clean up voxel normal vectors.
		 *
		 * Clean up the global voxel normal vectors.
		 */
		static void cleanupVoxelNormal();
		
		/** Clean up global data.
		 *
		 * Clean up any global data that has been allocated by one of the 
		 * static context functions.
		 */
		static void cleanup();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::VolGfx::Context& operator=(const 
		Ionflux::VolGfx::Context& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::VolGfx::Context* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::VolGfx::Context* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::VolGfx::Context* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Context object.
		 *
		 * \param initMaxNumLevels Maximum number of levels.
		 * \param initOrder Order.
		 * \param initScale Length scale factor.
		 * \param initTolerance Tolerance for comparisons.
		 * \param parentObject Parent object.
		 */
		static Ionflux::VolGfx::Context* create(int initMaxNumLevels, int 
		initOrder = DEFAULT_ORDER, double initScale = 1., double initTolerance = 
		DEFAULT_TOLERANCE, Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get maximum number of levels.
		 *
		 * \return Current value of maximum number of levels.
		 */
		virtual int getMaxNumLevels() const;
		
		/** Set maximum number of levels.
		 *
		 * Set new value of maximum number of levels.
		 *
		 * \param newMaxNumLevels New value of maximum number of levels.
		 */
		virtual void setMaxNumLevels(int newMaxNumLevels);
		
		/** Get order (number of children per non-leaf node and dimension).
		 *
		 * \return Current value of order (number of children per non-leaf node 
		 * and dimension).
		 */
		virtual int getOrder() const;
		
		/** Set order (number of children per non-leaf node and dimension).
		 *
		 * Set new value of order (number of children per non-leaf node and dimension).
		 *
		 * \param newOrder New value of order (number of children per non-leaf 
		 * node and dimension).
		 */
		virtual void setOrder(int newOrder);
		
		/** Get tolerance for comparisons.
		 *
		 * \return Current value of tolerance for comparisons.
		 */
		virtual double getTolerance() const;
		
		/** Set tolerance for comparisons.
		 *
		 * Set new value of tolerance for comparisons.
		 *
		 * \param newTolerance New value of tolerance for comparisons.
		 */
		virtual void setTolerance(double newTolerance);
		
		/** Get mask for valid bits from a location code.
		 *
		 * \return Current value of mask for valid bits from a location code.
		 */
		virtual Ionflux::VolGfx::NodeLoc getValidBits() const;
		
		/** Set mask for valid bits from a location code.
		 *
		 * Set new value of mask for valid bits from a location code.
		 *
		 * \param newValidBits New value of mask for valid bits from a location 
		 * code.
		 */
		virtual void setValidBits(const Ionflux::VolGfx::NodeLoc& newValidBits);
		
		/** Get maximum number of leaf child nodes per node.
		 *
		 * \return Current value of maximum number of leaf child nodes per node.
		 */
		virtual int getMaxNumLeafChildNodesPerNode() const;
		
		/** Get maximum number of leaf child nodes per dimension.
		 *
		 * \return Current value of maximum number of leaf child nodes per 
		 * dimension.
		 */
		virtual int getMaxNumLeafChildNodesPerDimension() const;
		
		/** Get length scale factor.
		 *
		 * \return Current value of length scale factor.
		 */
		virtual double getScale() const;
		
		/** Set length scale factor.
		 *
		 * Set new value of length scale factor.
		 *
		 * \param newScale New value of length scale factor.
		 */
		virtual void setScale(double newScale);
};

}

}

/** \file Context.hpp
 * \brief Voxel tree context (header).
 */
#endif
