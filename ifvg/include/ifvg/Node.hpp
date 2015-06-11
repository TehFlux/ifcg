#ifndef IONFLUX_VOLGFX_NODE
#define IONFLUX_VOLGFX_NODE
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Node.hpp                        Voxel tree node (header).
 * ========================================================================== */

#include "ifobject/types.hpp"
#include "ifobject/constants.hpp"
#include "altjira/Color.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/Vector3.hpp"
#include "geoutils/Range3.hpp"
#include "geoutils/Line3.hpp"
#include "geoutils/Mesh.hpp"
#include "geoutils/NFace.hpp"
#include "ifvg/types.hpp"
#include "ifvg/constants.hpp"
#include "ifvg/Context.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace VolGfx
{

class NodeSet;
class IOContext;
class NodeProcessor;
class NodeFilter;
class NodeIntersectionProcessor;

/// Class information for class Node.
class NodeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		NodeClassInfo();
		/// Destructor.
		virtual ~NodeClassInfo();
};

/** Voxel tree node.
 * \ingroup ifvg
 *
 * A data node in a voxel tree. The data node is a wrapper around a 
 * NodeImpl object, which, together with the static 'Impl' member functions
 * of Node, provides the low-level implementation of the node hierarchy. 
 * Node is intended as a convenient interface for operations on the root 
 * node of a voxel tree hierarchy. In this function, it provides automatic 
 * memory management for the voxel tree. However, it is usually best to use
 * the NodeImpl object and the static 'Impl' functions directly when 
 * implementing low-level operations for voxel tree nodes.
 * 
 * Node should always be constructed with a Context, which provides 
 * meta-information needed for the voxel tree operations.
 */
class Node
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Node implementation.
		Ionflux::VolGfx::NodeImpl* impl;
		/// Voxel tree context.
		Ionflux::VolGfx::Context* context;
		
	public:
		/// Node data type: unknown.
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_UNKNOWN;
		/// Node data type: null.
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_NULL;
		/// Node data type: density.
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_DENSITY;
		/// Node data type: color (RGBA).
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_COLOR_RGBA;
		/// Node data type: distance field (8 elements).
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_DISTANCE_8;
		/// Node data type: color/normal.
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_COLOR_NORMAL;
		/// Node data type: face vector.
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_FACE_VEC;
		/// Node data type: voxel class.
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_VOXEL_CLASS;
		/// Node data type: voxel inside/outside/boundary.
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_VOXEL_IOB;
		/// Node data type: any (not null).
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_ANY_NOT_NULL;
		/// Child index: invalid.
		static const int CHILD_INDEX_INVALID;
		/// Magic syllable: header (HE).
		static const Ionflux::ObjectBase::MagicSyllable MAGIC_SYLLABLE_HEADER;
		/// Magic syllable: root (NR).
		static const Ionflux::ObjectBase::MagicSyllable MAGIC_SYLLABLE_ROOT;
		/// Magic syllable: node (NO).
		static const Ionflux::ObjectBase::MagicSyllable MAGIC_SYLLABLE_NODE;
		/// Magic syllable: offset map (OM).
		static const Ionflux::ObjectBase::MagicSyllable MAGIC_SYLLABLE_OFFSET_MAP;
		/// Magic syllable: node data (ND).
		static const Ionflux::ObjectBase::MagicSyllable MAGIC_SYLLABLE_DATA;
		/// Default ray plane offset.
		static const double DEFAULT_RAY_PLANE_OFFSET;
		/// Class information instance.
		static const NodeClassInfo nodeClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Node object.
		 */
		Node();
		
		/** Constructor.
		 *
		 * Construct new Node object.
		 *
		 * \param other Other object.
		 */
		Node(const Ionflux::VolGfx::Node& other);
		
		/** Constructor.
		 *
		 * Construct new Node object.
		 *
		 * \param initContext Voxel tree context.
		 * \param initImpl Node implementation.
		 */
		Node(Ionflux::VolGfx::Context* initContext, Ionflux::VolGfx::NodeImpl* 
		initImpl = 0);
		
		/** Destructor.
		 *
		 * Destruct Node object.
		 */
		virtual ~Node();
		
		/** Clear node.
		 *
		 * Clear all data in the node.
		 */
		virtual void clear() const;
		
		/** Get parent node.
		 *
		 * Get the parent node. The caller is responsible for managing the 
		 * returned object.
		 *
		 * \return Parent node, or 0 if the parent node does not exist.
		 */
		virtual Ionflux::VolGfx::Node* getParent() const;
		
		/** Set child nodes.
		 *
		 * Set the child nodes of this node. \c newNodes is expected to be a 
		 * vector containing a number of nodes equal or greater than the the 
		 * maximum number of child nodes per node, ordered by ascending local 
		 * X, Y, Z coordinate. Invalid nodes are identified by a zero entry 
		 * within the vector.
		 *
		 * \param newNodes Vector of nodes.
		 */
		virtual void setChildNodes(const Ionflux::VolGfx::NodeVector& newNodes) 
		const;
		
		/** Merge child nodes.
		 *
		 * Merge the nodes from the vector with the current child nodes of 
		 * this node. \c newNodes is expected to be a vector containing a 
		 * number of node implementations equal or greater than the maximum 
		 * number of child nodes per node, ordered by ascending local X, Y, Z 
		 * coordinate. Nodes that should not be changed are identified by a 
		 * zero entry within the vector. A new node implementation will be 
		 * created for each entry in \c newNodes. This node implementation 
		 * takes over all data and child nodes from the entry in \c newNodes.
		 *
		 * \param newNodes Vector of node implementations.
		 * \param fill0 Create a full set of child nodes if one is missing.
		 */
		virtual void mergeChildNodes(const Ionflux::VolGfx::NodeImplVector& 
		newNodes, bool fill0 = false) const;
		
		/** Merge child nodes.
		 *
		 * Merge the nodes from the vector with the current child nodes of 
		 * this node. \c newNodes is expected to be a vector containing a 
		 * number of node implementations equal or greater than the maximum 
		 * number of child nodes per node, ordered by ascending local X, Y, Z 
		 * coordinate. Nodes that should not be changed are identified by a 
		 * zero entry within the vector. A new node implementation will be 
		 * created for each entry in \c newNodes. This node implementation 
		 * takes over all data and child nodes from the entry in \c newNodes.
		 *
		 * \param newNodes Vector of nodes.
		 * \param fill0 Create a full set of child nodes if one is missing.
		 */
		virtual void mergeChildNodes(const Ionflux::VolGfx::NodeVector& newNodes,
		bool fill0 = false) const;
		
		/** Set child node.
		 *
		 * Set the child node for the child node with the specified order 
		 * index.
		 *
		 * \param newNode Child node.
		 * \param orderIndex Order index.
		 */
		virtual void setChildNodeByOrderIndex(Ionflux::VolGfx::Node* newNode, int
		orderIndex) const;
		
		/** Clear child nodes.
		 *
		 * Clear the child nodes indicated by a bit set in the location mask.
		 *
		 * \param clearNodes Mask indicating nodes to be cleared.
		 */
		virtual void clearChildNodes(const Ionflux::VolGfx::NodeChildMask& 
		clearNodes) const;
		
		/** Prune empty child nodes.
		 *
		 * Clear the child nodes which are leaf nodes but do not contain any 
		 * data.
		 *
		 * \param recursive recursively prune nodes.
		 *
		 * \return number of nodes that were pruned.
		 */
		virtual unsigned int pruneEmpty(bool recursive = false) const;
		
		/** Clear data.
		 *
		 * Clear data of this node.
		 */
		virtual void clearData() const;
		
		/** Clear child nodes.
		 *
		 * Clear child nodes of this node. If this node is leaf node, this 
		 * function will not do anything.
		 */
		virtual void clearChildNodes() const;
		
		/** Set data.
		 *
		 * Set the data of this node. The node implementation will take 
		 * ownership of the data.
		 *
		 * \param newData Node data.
		 */
		virtual void setData(Ionflux::VolGfx::NodeDataImpl* newData) const;
		
		/** Set data.
		 *
		 * Set the data of this node to a new data instance of the specified 
		 * type. If the node is not a leaf, any child nodes will be deleted. 
		 * If the optional \c newData is specified, elements from this vector 
		 * will be used to initialize the data record according to the data 
		 * type.
		 *
		 * \param newType Node data type.
		 * \param newData Node data vector.
		 */
		virtual void setData(Ionflux::VolGfx::NodeDataType newType, const 
		Ionflux::ObjectBase::DoubleVector* newData = 0) const;
		
		/** Clear leaf data.
		 *
		 * Clear the leaf data of this node. If this node is not a leaf node, 
		 * this function will not do anything.
		 */
		virtual void clearLeafData() const;
		
		/** Get number of child nodes.
		 *
		 * Get the number of valid child nodes of this node.
		 *
		 * \return Number of child nodes.
		 */
		virtual int getNumChildNodes() const;
		
		/** Fill node.
		 *
		 * Fill the node. This creates new child nodes so that all children of
		 * this node are valid. If \c clearExisting is set to \c true, any 
		 * existing data is cleared. If \c recursive is set to \c true, child 
		 * nodes are filled recursively. If \c maxDepth is greater than zero, 
		 * child nodes will be filled up to and including the maximum depth 
		 * specified.
		 *
		 * \param clearExisting Clear existing data.
		 * \param recursive Fill nodes recursively.
		 * \param maxDepth Maximum depth.
		 *
		 * \return Number of new nodes that have been created.
		 */
		virtual int fill(bool clearExisting = false, bool recursive = false, int 
		maxDepth = 0) const;
		
		/** Get valid child index.
		 *
		 * Get the index of the specified child node among the valid child 
		 * nodes.
		 *
		 * \param n Node.
		 *
		 * \return Index of the specified child node among the valid child nodes,
		 * or CHILD_INDEX_INVALID if the node is not a child of this node.
		 */
		virtual int getChildValidIndex(Ionflux::VolGfx::Node* n) const;
		
		/** Get valid child index.
		 *
		 * Get the index of the specified child node implementation among the 
		 * valid child node implementations.
		 *
		 * \param otherImpl Node implementation.
		 *
		 * \return Index of the specified child node among the valid child nodes,
		 * or CHILD_INDEX_INVALID if the node is not a child of this node.
		 */
		virtual int getChildValidIndex(Ionflux::VolGfx::NodeImpl* otherImpl) 
		const;
		
		/** Get valid child index.
		 *
		 * Get the index of the child node with the specified order index 
		 * among the valid child nodes.
		 *
		 * \param orderIndex Order index.
		 *
		 * \return Index of the specified child node among the valid child nodes,
		 * or CHILD_INDEX_INVALID if the node is not a child of this node.
		 */
		virtual int getChildValidIndex(int orderIndex) const;
		
		/** Get child order index.
		 *
		 * Get the index of the child node with the specified valid index 
		 * among all child nodes (including invalid nodes). This can be used 
		 * to calculate the coordinates of a child node or to test the mask 
		 * bits.
		 *
		 * \param index Index.
		 *
		 * \return \c true if the child with the specified index is a leaf node, 
		 * \c false otherwise.
		 */
		virtual int getChildOrderIndex(int index) const;
		
		/** Get child location code.
		 *
		 * Get the location code of the child node with the specified order 
		 * index. This will also report the correct location code for child 
		 * nodes that currently do not exist. If The depth of a child node 
		 * would be above the maximum depth for the tree, an exception will be
		 * raised.
		 *
		 * \param orderIndex Order index.
		 *
		 * \return Location code for the child node with the specified order 
		 * index.
		 */
		virtual Ionflux::VolGfx::NodeLoc3 getChildLoc(int orderIndex) const;
		
		/** Leaf check.
		 *
		 * Check whether the child node with the specified valid index is a 
		 * leaf node.
		 *
		 * \param orderIndex Order index.
		 *
		 * \return \c true if the child with the specified index is a leaf node, 
		 * \c false otherwise.
		 */
		virtual bool isLeafOrderChild(int orderIndex) const;
		
		/** Leaf check.
		 *
		 * Check whether the child node with the specified valid index is a 
		 * leaf node.
		 *
		 * \param index Index.
		 *
		 * \return \c true if the child with the specified index is a leaf node, 
		 * \c false otherwise.
		 */
		virtual bool isLeafValidChild(int index) const;
		
		/** Leaf check.
		 *
		 * Check whether this node is a leaf node.
		 *
		 * \return \c true if this node is a leaf node, \c false otherwise..
		 */
		virtual bool isLeaf() const;
		
		/** Get leaf status.
		 *
		 * Get leaf status.
		 *
		 * \return leaf status of the node implementation.
		 */
		virtual Ionflux::VolGfx::LeafStatusID getLeafStatus();
		
		/** Update node state.
		 *
		 * Update the node state according to changes in the child nodes.
		 */
		virtual void update();
		
		/** Node data type voxel class information check.
		 *
		 * Check whether the node has a data type that has voxel class 
		 * information attached.
		 *
		 * \return \c true if the node has a data type that has voxel class 
		 * information attached, \c false otherwise.
		 */
		virtual bool hasVoxelClassInfo();
		
		/** Get node voxel class.
		 *
		 * Get the voxel class of the node.
		 *
		 * \return Voxel class, or VOXEL_CLASS_UNDEFINED if the node does not 
		 * have voxel class data attached.
		 */
		virtual Ionflux::VolGfx::VoxelClassID getVoxelClass();
		
		/** Node voxel class check.
		 *
		 * Check if the node voxel class matches the specified mask.
		 *
		 * \param mask Voxel class mask.
		 *
		 * \return \c true if the node voxel class matches the specified mask, \c
		 * false otherwise.
		 */
		virtual bool hasVoxelClass(Ionflux::VolGfx::VoxelClassID mask);
		
		/** Set node implementation voxel class.
		 *
		 * Set the voxel class mask for the node implementation. If \c enable 
		 * is set to \c false, the specified voxel class mask will be unset 
		 * instead of set. If the node implementation does not have any data 
		 * of a compatible type attached and \c createDataType is 0, this 
		 * function does nothing. Otherwise, if there is no data attached to 
		 * the node, a new record of type \c createDataType will be created.
		 *
		 * \param mask Voxel class mask.
		 * \param enable enable flag.
		 * \param createDataType data type for new records.
		 *
		 * \return new voxel class of the node implementation.
		 */
		virtual Ionflux::VolGfx::VoxelClassID 
		setVoxelClass(Ionflux::VolGfx::VoxelClassID mask, bool enable = true, 
		Ionflux::VolGfx::NodeDataType createDataType = DATA_TYPE_UNKNOWN);
		
		/** Set node implementation voxel class.
		 *
		 * Set the voxel class mask for node implementations within the 
		 * hierarchy that pass the specified filter. If \c enable is set to \c
		 * false, the specified voxel class mask will be unset instead of set.
		 * If one of the node implementations does not have any data of a 
		 * compatible type attached and \c createDataType is 0, it will be 
		 * left unchanged by this function. Otherwise, if there is no data 
		 * attached to the node, a new record of type \c createDataType will 
		 * be created.
		 *
		 * \param mask Voxel class mask.
		 * \param enable enable flag.
		 * \param filter node filter.
		 * \param recursive process nodes recursively.
		 * \param createDataType data type for new records.
		 *
		 * \return number of nodes on which the voxel class was set.
		 */
		virtual unsigned int setVoxelClass0(Ionflux::VolGfx::VoxelClassID mask, 
		bool enable = true, Ionflux::VolGfx::NodeFilter* filter = 0, bool 
		recursive = true, Ionflux::VolGfx::NodeDataType createDataType = 
		DATA_TYPE_UNKNOWN);
		
		/** Node data type color index check.
		 *
		 * Check whether the node has a data type that has a color index 
		 * attached.
		 *
		 * \return \c true if the node has a data type that has a color index 
		 * attached, \c false otherwise.
		 */
		virtual bool hasColorIndex();
		
		/** Get node color index.
		 *
		 * Get the color index of the node.
		 *
		 * \return Color index, or COLOR_INDEX_UNSPECIFIED if the node does not 
		 * have a color index attached.
		 */
		virtual Ionflux::VolGfx::ColorIndex getColorIndex();
		
		/** Set node implementation color index.
		 *
		 * Set the color index for the node implementation. If the node 
		 * implementation does not have any data of a compatible type attached
		 * and \c createDataType is 0, this function does nothing. Otherwise, 
		 * if there is no data attached to the node, a new record of type \c 
		 * createDataType will be created.
		 *
		 * \param color Color index.
		 * \param createDataType data type for new records.
		 *
		 * \return new color index of the node implementation.
		 */
		virtual Ionflux::VolGfx::ColorIndex 
		setColorIndex(Ionflux::VolGfx::ColorIndex color, 
		Ionflux::VolGfx::NodeDataType createDataType = DATA_TYPE_UNKNOWN);
		
		/** Set node implementation color index.
		 *
		 * Set the color index for node implementations within the hierarchy 
		 * that pass the specified filter. If one of the node implementations 
		 * does not have any data of a compatible type attached and \c 
		 * createDataType is 0, it will be left unchanged by this function. 
		 * Otherwise, if there is no data attached to the node, a new record 
		 * of type \c createDataType will be created.
		 *
		 * \param color Color index.
		 * \param filter node filter.
		 * \param recursive process nodes recursively.
		 * \param createDataType data type for new records.
		 *
		 * \return number of nodes on which the color index was set.
		 */
		virtual unsigned int setColorIndex0(Ionflux::VolGfx::ColorIndex color, 
		Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = true, 
		Ionflux::VolGfx::NodeDataType createDataType = DATA_TYPE_UNKNOWN);
		
		/** Get child node by order index.
		 *
		 * Get the child node with the specified order index. The caller is 
		 * responsible for managing the returned object.
		 *
		 * \param orderIndex Order index.
		 * \param autoCreate Create child nodes automatically if they do not 
		 * exist.
		 *
		 * \return Child node with the specified order index, or 0 if the child 
		 * node does not exist.
		 */
		virtual Ionflux::VolGfx::Node* getChildByOrderIndex(int orderIndex, bool 
		autoCreate = false) const;
		
		/** Get child by order index.
		 *
		 * Get the child node with the specified valid index. The caller is 
		 * responsible for managing the returned object.
		 *
		 * \param index Valid index.
		 *
		 * \return Child node with the specified order index, or 0 if the child 
		 * node does not exist.
		 */
		virtual Ionflux::VolGfx::Node* getChildByValidIndex(int index) const;
		
		/** Locate child node.
		 *
		 * Locate the child node that contains the specified location index. 
		 * If \c maxDepth not negative, the search for the node stops at the 
		 * specified maximum depth. The caller is responsible for managing the
		 * returned object.
		 *
		 * \param loc Node data.
		 * \param maxDepth Maximum depth.
		 *
		 * \return Leaf node containing the specified location, or 0 if no 
		 * suitable node was found.
		 */
		virtual Ionflux::VolGfx::Node* locateChild(const 
		Ionflux::VolGfx::NodeLoc3& loc, int maxDepth = DEPTH_UNSPECIFIED);
		
		/** Locate child node.
		 *
		 * Locate the child node that contains the specified point. If \c 
		 * maxDepth is greater than zero, the search for the node stops at the
		 * specified maximum depth. The caller is responsible for managing the
		 * returned object.
		 *
		 * \param p Point.
		 * \param maxDepth Maximum depth.
		 *
		 * \return Leaf node containing the specified location, or 0 if no 
		 * suitable node was found.
		 */
		virtual Ionflux::VolGfx::Node* locateChild(const 
		Ionflux::GeoUtils::Vector3& p, int maxDepth = DEPTH_UNSPECIFIED);
		
		/** Locate region.
		 *
		 * Locate the node that contains the specified region. If \c maxDepth 
		 * is not negative, the search for the node stops at the specified 
		 * maximum depth. The caller is responsible for managing the returned 
		 * object.
		 *
		 * \param region Region.
		 * \param maxDepth Maximum depth.
		 *
		 * \return Node containing the specified region, or 0 if no suitable node
		 * was found.
		 */
		virtual Ionflux::VolGfx::Node* locateRegion(const 
		Ionflux::VolGfx::Region3& region, int maxDepth = DEPTH_UNSPECIFIED);
		
		/** Locate region.
		 *
		 * Locate the node that contains the specified region. If \c maxDepth 
		 * is not negative, the search for the node stops at the specified 
		 * maximum depth. The caller is responsible for managing the returned 
		 * object.
		 *
		 * \param range Range.
		 * \param maxDepth Maximum depth.
		 *
		 * \return Node containing the specified region, or 0 if no suitable node
		 * was found.
		 */
		virtual Ionflux::VolGfx::Node* locateRegion(const 
		Ionflux::GeoUtils::Range3& range, int maxDepth = DEPTH_UNSPECIFIED);
		
		/** Locate node.
		 *
		 * Locate the node that contains the specified location index. If \c 
		 * maxDepth is not negative, the search for the node stops at the 
		 * specified maximum depth. This function will search the ancestors of
		 * the current node implementation upwards if the specified location 
		 * is not contained in this node. The caller is responsible for 
		 * managing the returned object.
		 *
		 * \param loc Location.
		 * \param maxDepth Maximum depth.
		 *
		 * \return Node containing the specified location, or 0 if no suitable 
		 * node was found.
		 */
		virtual Ionflux::VolGfx::Node* locateNode(const 
		Ionflux::VolGfx::NodeLoc3& loc, int maxDepth = DEPTH_UNSPECIFIED);
		
		/** Get depth.
		 *
		 * Get the depth of the node.
		 *
		 * \return Node depth.
		 */
		virtual int getDepth() const;
		
		/** Get maximum depth.
		 *
		 * Get the maximum depth of the node hierarchy.
		 *
		 * \return Maximum node depth of the hierarchy.
		 */
		virtual int getMaxDepth() const;
		
		/** Insert child node.
		 *
		 * Insert a child node at the specified depth that contains the 
		 * specified location index. If \c depth is negative, a leaf node at 
		 * the maximum depth will be inserted. If a node with the specified 
		 * location code already exists at the specified depth, that node will
		 * be returned. The caller is responsible for managing the returned 
		 * object.
		 *
		 * \param loc Node data.
		 * \param depth Depth at which to create the node.
		 * \param fill0 Create a full set of child nodes if one is missing.
		 * \param fillTargetDepth0 Create a full set of child nodes at the target
		 * depth level if one is missing.
		 *
		 * \return Node at the specified location and depth, or 0 if the location
		 * is outside the bounds of this node.
		 */
		virtual Ionflux::VolGfx::Node* insertChild(const 
		Ionflux::VolGfx::NodeLoc3& loc, int depth = DEPTH_UNSPECIFIED, bool fill0
		= false, bool fillTargetDepth0 = false);
		
		/** Insert child node.
		 *
		 * Insert a child node at the specified depth that contains the 
		 * specified point. If \c depth is negative, a leaf node at the 
		 * maximum depth will be inserted. If a node with the specified 
		 * location code already exists at the specified depth, that node will
		 * be returned. The caller is responsible for managing the returned 
		 * object.
		 *
		 * \param p Point.
		 * \param depth Depth at which to create the node.
		 * \param fill0 Create a full set of child nodes if one is missing.
		 *
		 * \return Node at the specified location and depth, or 0 if the location
		 * is outside the bounds of this node.
		 */
		virtual Ionflux::VolGfx::Node* insertChild(const 
		Ionflux::GeoUtils::Vector3& p, int depth = DEPTH_UNSPECIFIED, bool fill0 
		= false);
		
		/** Insert child node.
		 *
		 * Insert a child node identified by the specified node ID. If \c 
		 * depth is not greater than zero, a leaf node at the maximum depth 
		 * will be inserted. If a node with the specified location code 
		 * already exists at the specified depth, that node will be returned. 
		 * The caller is responsible for managing the returned object.
		 *
		 * \param nodeID Node ID.
		 * \param fill0 Create a full set of child nodes if one is missing.
		 *
		 * \return Node at the specified location and depth, or 0 if the location
		 * is outside the bounds of this node.
		 */
		virtual Ionflux::VolGfx::Node* insertChild(const Ionflux::VolGfx::NodeID&
		nodeID, bool fill0 = false);
		
		/** Get voxel size.
		 *
		 * Get the voxel size for the node.
		 *
		 * \return Location vector.
		 */
		virtual double getVoxelSize();
		
		/** Get voxel size.
		 *
		 * Get the voxel size for the node in location code units.
		 *
		 * \return Location vector.
		 */
		virtual double getVoxelSizeLoc();
		
		/** Get location.
		 *
		 * Get the location vector for the corner of the node with the lowest 
		 * coordinates on each of the axes.
		 *
		 * \return Location vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getLocation() const;
		
		/** Get neighbor location code.
		 *
		 * Get the location code of the smallest size neighbor node with the 
		 * specified offset, where the offset is one of {-1, 0, 1} If the 
		 * neighbor node location is within the bounds of the tree, the 
		 * location code is stored in \c target. If no neighbor exists within 
		 * the bounds of the tree, the function returns \c false and the 
		 * contents of \c target is undefined.
		 *
		 * \param offsetX Offset (x).
		 * \param offsetY Offset (y).
		 * \param offsetZ Offset (z).
		 * \param target Where to store the neighbor location.
		 *
		 * \return \c true if the neighbor node exists, \c false otherwise.
		 */
		virtual bool getNeighborLoc(int offsetX, int offsetY, int offsetZ, 
		Ionflux::VolGfx::NodeLoc3& target);
		
		/** Get range.
		 *
		 * Get the range of values contained in the node.
		 *
		 * \param target Where to store the range data.
		 */
		virtual void getRange(Ionflux::GeoUtils::Range3& target) const;
		
		/** Get line intersection location.
		 *
		 * Get the intersection location codes for the specified intersection 
		 * data. If there is a valid intersection, the intersection location 
		 * codes will be stored in \c target. Otherwise, \c target will be 
		 * undefined and the function returns \c false.
		 *
		 * \param line Line.
		 * \param interData Intersection data.
		 * \param target Where to store the intersection location codes.
		 *
		 * \return \c true if the intersection data is valid, \c false otherwise.
		 */
		virtual bool getIntersectionLoc(Ionflux::GeoUtils::Line3& line, const 
		Ionflux::GeoUtils::AAPlanePairIntersection& interData, 
		Ionflux::VolGfx::Region3& target) const;
		
		/** Find nodes.
		 *
		 * Find nodes by depth range. All nodes that are within the specified 
		 * depth range and meet the additional requirements will be added to 
		 * the \c target set. If \c target is 0, nodes will be counted but not
		 * added to the target set.
		 *
		 * \param target Where to store the nodes.
		 * \param filter node filter.
		 * \param recursive find nodes recursively.
		 *
		 * \return number of node implementations found.
		 */
		virtual unsigned int find(Ionflux::VolGfx::NodeSet* target, 
		Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = true);
		
		/** Process nodes.
		 *
		 * Process nodes that pass the specified filter using the specified 
		 * node processors. The \c preProcessor is invoked before the 
		 * recursion. The \c postProcessor is invoked after the recursion. 
		 * Recursive traversal stops when the \c preProcessor returns 
		 * ChainableNodeProcessor::RESULT_FINISHED, or when the maximum depth 
		 * as set on the \c filter is reached.
		 *
		 * \param preProcessor node processor (pre).
		 * \param filter node filter.
		 * \param postProcessor node processor (post).
		 * \param recursive find nodes recursively.
		 *
		 * \return number of node implementations processed.
		 */
		virtual unsigned int process(Ionflux::VolGfx::NodeProcessor* 
		preProcessor, Ionflux::VolGfx::NodeFilter* filter = 0, 
		Ionflux::VolGfx::NodeProcessor* postProcessor = 0, bool recursive = 
		true);
		
		/** Get color.
		 *
		 * Get a color for the node. If the optional \c colors color set is 
		 * specified, the color for the node is selected from the color set 
		 * according to the depth level of the node and the specified color 
		 * offset. If \c colorIndex is not negative, the specified color index
		 * will be used for selecting a color from the color set. If the 
		 * optional \c voxelClassColors is specified and the node has a voxel 
		 * class attached to its data, the color for the node is selected 
		 * according to the first entry in the vector that matches one of the 
		 * voxel classes of the node. The \c colorIndex takes precedence over 
		 * all other color specifications, followed by the voxel class color, 
		 * the leaf color index and finally the depth based color.
		 *
		 * \param colors color set.
		 * \param colorIndexOffset color index offset.
		 * \param colorIndexRange color index range.
		 * \param colorIndex color index.
		 * \param leafColorIndex leaf color index.
		 * \param voxelClassColors voxel class colors.
		 *
		 * \return color, or 0 if no color is specified for the node.
		 */
		virtual Ionflux::Altjira::Color* getColor(Ionflux::Altjira::ColorSet* 
		colors = 0, unsigned int colorIndexOffset = 0, unsigned int 
		colorIndexRange = 0, int colorIndex = COLOR_INDEX_UNSPECIFIED, int 
		leafColorIndex = COLOR_INDEX_UNSPECIFIED, 
		Ionflux::VolGfx::VoxelClassColorVector* voxelClassColors = 0);
		
		/** Get mesh.
		 *
		 * Get a mesh for the node. One box is generated for each node. If the
		 * optional \c colors color set is specified, the vertex colors for 
		 * each box are selected from the color set according to the depth 
		 * level of the node. Boxes will be inset by the amount specified in 
		 * \c boxInset, scaled by the size of the octree. The mesh for the 
		 * node will be merged into the \c target mesh.
		 *
		 * \param target where to store the mesh.
		 * \param boxInset box inset per depth level.
		 * \param colors vertex colors.
		 * \param colorOffset color index offset.
		 * \param colorIndexOffset color index offset.
		 * \param colorIndexRange color index range.
		 * \param leafColorIndex leaf color index.
		 * \param filter node filter.
		 * \param recursive recursively create meshes.
		 */
		virtual void getMesh(Ionflux::GeoUtils::Mesh& target, double boxInset = 
		Ionflux::VolGfx::Context::DEFAULT_BOX_INSET, Ionflux::Altjira::ColorSet* 
		colors = 0, unsigned int colorOffset = 0, unsigned int colorIndexOffset =
		0, unsigned int colorIndexRange = 0, int leafColorIndex = 
		COLOR_INDEX_UNSPECIFIED, Ionflux::VolGfx::NodeFilter* filter = 0, bool 
		recursive = false);
		
		/** Get vertex attributes.
		 *
		 * Get vertex attributes for the node. Boxes will be inset by the 
		 * amount specified in \c boxInset, scaled by the leaf voxel size. If 
		 * the optional \c colors color set is specified, the vertex colors 
		 * for the box are selected from the color set according to the depth 
		 * level of the node and the specified color offset. If \c colorIndex 
		 * is not negative, the specified color index will be used for 
		 * selecting a color from the color set. If the optional \c 
		 * voxelClassColors is specified, the colors for nodes that have a 
		 * voxel class set is selected according to the first entry in the 
		 * vector that matches one of the voxel classes of the node. Data will
		 * be appended to a specified vertex attributes for each target vertex
		 * attribute that is not null. If the optional \c positionOffset or \c
		 * positionScale are specified, vertex positions will be scaled or 
		 * translated by these vectors.
		 *
		 * \param positionTarget target for position data.
		 * \param colorTarget target for color data.
		 * \param normalTarget target for normal data.
		 * \param nFaceType Mesh N-face type.
		 * \param boxInset box inset per depth level.
		 * \param colors vertex colors.
		 * \param colorIndexOffset color index offset.
		 * \param colorIndexRange color index range.
		 * \param colorIndex color index.
		 * \param leafColorIndex leaf color index.
		 * \param voxelClassColors voxel class colors.
		 * \param positionOffset position offset.
		 * \param positionScale position scale.
		 * \param filter node filter.
		 * \param recursive recursively get vertex attributes.
		 * \param boundaryFacesOnly show only boundary faces.
		 */
		virtual void getVertexAttributes(Ionflux::GeoUtils::VertexAttribute* 
		positionTarget = 0, Ionflux::GeoUtils::VertexAttribute* colorTarget = 0, 
		Ionflux::GeoUtils::VertexAttribute* normalTarget = 0, 
		Ionflux::GeoUtils::NFaceTypeID nFaceType = 
		Ionflux::GeoUtils::NFace::TYPE_FACE, double boxInset = 
		Ionflux::VolGfx::Context::DEFAULT_BOX_INSET, Ionflux::Altjira::ColorSet* 
		colors = 0, unsigned int colorIndexOffset = 0, unsigned int 
		colorIndexRange = 0, int colorIndex = COLOR_INDEX_UNSPECIFIED, int 
		leafColorIndex = COLOR_INDEX_UNSPECIFIED, 
		Ionflux::VolGfx::VoxelClassColorVector* voxelClassColors = 0, 
		Ionflux::GeoUtils::Vector* positionOffset = 0, Ionflux::GeoUtils::Vector*
		positionScale = 0, Ionflux::VolGfx::NodeFilter* filter = 0, bool 
		recursive = false, bool boundaryFacesOnly = false);
		
		/** Get number of faces.
		 *
		 * Get the number of faces for the node. This is the total number of 
		 * faces attached to the node or, if \c recursive is set to \c true, 
		 * the hierarchy of nodes starting at this node.
		 *
		 * \param recursive count faces recursively.
		 *
		 * \return Number of faces.
		 */
		virtual unsigned int getNumFaces(bool recursive = false);
		
		/** Insert face for voxelization.
		 *
		 * Insert a face into the node hierarchy for voxelization. The face 
		 * will be attached to the deepest node that completely contains its 
		 * voxelization.
		 *
		 * \param face face.
		 * \param sep separability.
		 * \param fill0 Create a full set of child nodes if one is missing.
		 *
		 * \return \c true if the face was inserted into the node hierarchy, \c 
		 * false if the node hierarchy does not contain the face voxelization.
		 */
		virtual bool voxelizeInsertFace(Ionflux::GeoUtils::Face* face, 
		Ionflux::VolGfx::SeparabilityID sep, bool fill0 = false);
		
		/** Insert faces for voxelization.
		 *
		 * Insert faces from the mesh into the node hierarchy for 
		 * voxelization. Each face will be attached to the deepest node that 
		 * completely contains its voxelization.
		 *
		 * \param mesh mesh.
		 * \param sep separability.
		 * \param fill0 Create a full set of child nodes if one is missing.
		 *
		 * \return number of faces that were inserted into the node hierarchy.
		 */
		virtual unsigned int voxelizeInsertFaces(const Ionflux::GeoUtils::Mesh& 
		mesh, Ionflux::VolGfx::SeparabilityID sep, bool fill0 = false);
		
		/** Voxelize faces.
		 *
		 * Voxelize faces that are attached to the node hierarchy. The 
		 * voxelization data will replace any data currently attached to the 
		 * nodes (including face data). Data will be generated according to 
		 * the \c target parameter, at the depth level specified via the \c 
		 * targetDepth parameter. If \c targetDepth is negative, the target 
		 * depth is set to the maximum depth. Faces passed in via the optional
		 * \c faces parameter will be appended to the face list for the node.
		 *
		 * \param processor node processor.
		 * \param targetDepth target depth.
		 * \param sep separability.
		 * \param fillTargetDepth Create a full set of child nodes at the target 
		 * depth if one is missing.
		 * \param pruneEmpty0 Prune empty child nodes after voxelization.
		 * \param faces0 additional faces.
		 *
		 * \return number of voxels that were set.
		 */
		virtual unsigned int voxelizeFaces(Ionflux::VolGfx::NodeProcessor* 
		processor, int targetDepth, Ionflux::VolGfx::SeparabilityID sep, bool 
		fillTargetDepth = false, bool pruneEmpty0 = false, 
		Ionflux::GeoUtils::FaceVector* faces0 = 0);
		
		/** Get allocated size.
		 *
		 * Get the allocated size in memory for this node, including the size 
		 * of the allocated data.
		 *
		 * \param recursive recursively calculate allocated size.
		 *
		 * \return allocated size of the node implementation.
		 */
		virtual unsigned int getMemSize(bool recursive = false);
		
		/** Get allocated size for data.
		 *
		 * Get the allocated size in memory for the data of this node.
		 *
		 * \return allocated size of the node data.
		 */
		virtual unsigned int getDataMemSize();
		
		/** Serialize node hierarchy.
		 *
		 * Serialize the node hierarchy of which this node is the root node.
		 *
		 * \param target where to store the serialized data.
		 */
		virtual void serializeHierarchy(std::ostream& target);
		
		/** Serialize node hierarchy.
		 *
		 * Serialize the node hierarchy of which this node is the root node.
		 *
		 * \param ioContext I/O context.
		 */
		virtual void serializeHierarchy(Ionflux::VolGfx::IOContext& ioContext);
		
		/** Deserialize node.
		 *
		 * Deserialize a node from the specified offset.
		 *
		 * \param ioContext I/O context.
		 * \param offset deserialization offset.
		 * \param magicSyllable magic syllable to be used to indicate the node 
		 * type.
		 * \param deserializeData deserialize node data.
		 * \param zeroChildPointer zero the child pointer.
		 * \param zeroParentPointer zero the parent pointer.
		 */
		virtual void deserialize(Ionflux::VolGfx::IOContext& ioContext, 
		Ionflux::ObjectBase::DataSize offset = 
		Ionflux::ObjectBase::DATA_SIZE_INVALID, 
		Ionflux::ObjectBase::MagicSyllable magicSyllable = MAGIC_SYLLABLE_NODE, 
		bool deserializeData = true, bool zeroChildPointer = true, bool 
		zeroParentPointer = true);
		
		/** Deserialize node hierarchy.
		 *
		 * Deserialize a node hierarchy from the specified source. This node 
		 * will become the root of the hierarchy. If \c targetNode is 
		 * specified, the node ID of the root node of the deserialized 
		 * hierarchy will be stored in \c targetNode.
		 *
		 * \param source data source.
		 * \param header where to store the node implementation hierarchy header.
		 * \param targetNode where to store the node ID.
		 * \param poMap where to store the pointer/offset map (serialized).
		 * \param poMapCurrent where to store the pointer/offset map (current).
		 * \param deserializeData deserialize node data.
		 * \param maxDepth maximum depth for deserializing child nodes.
		 */
		virtual void deserializeHierarchy(std::istream& source, 
		Ionflux::VolGfx::NodeImplHierarchyHeader* header = 0, 
		Ionflux::VolGfx::NodeID* targetNode = 0, 
		Ionflux::ObjectBase::PointerOffsetMap* poMap = 0, 
		Ionflux::ObjectBase::PointerOffsetMap* poMapCurrent = 0, bool 
		deserializeData = true, int maxDepth = DEPTH_UNSPECIFIED);
		
		/** Deserialize node hierarchy.
		 *
		 * Deserialize a node hierarchy from the specified source. This node 
		 * will become the root of the hierarchy. If \c targetNode is 
		 * specified, the node ID of the root node of the deserialized 
		 * hierarchy will be stored in \c targetNode.
		 *
		 * \param ioContext I/O context.
		 * \param deserializeData deserialize node data.
		 * \param maxDepth maximum depth for deserializing child nodes.
		 */
		virtual void deserializeHierarchy(Ionflux::VolGfx::IOContext& ioContext, 
		bool deserializeData = true, int maxDepth = DEPTH_UNSPECIFIED);
		
		/** Intersect ray.
		 *
		 * Find intersections between the node and the specified ray.
		 *
		 * \param ray ray.
		 * \param target where to store the node intersection data.
		 * \param t tolerance.
		 *
		 * \return \c true if the intersection is valid, \c false otherwise.
		 */
		virtual bool intersectRay(const Ionflux::GeoUtils::Line3& ray, 
		Ionflux::VolGfx::NodeIntersection& target, double t = DEFAULT_TOLERANCE);
		
		/** Intersect ray.
		 *
		 * Find intersections between the node and the specified ray. Node 
		 * intersections are passed to the specified intersection processor in
		 * order of occurence along the ray. Ray traversal stops when the 
		 * processor returns ChainableNodeProcessor::RESULT_FINISHED. If \c 
		 * filter is specified, only intersections for nodes that pass the 
		 * filter will be processed. However, if \c recursive is \c true, 
		 * child nodes of nodes that do not pass the filter may still be 
		 * processed.
		 *
		 * \param ray ray.
		 * \param processor node intersection processor.
		 * \param filter node filter.
		 * \param recursive intersect nodes recursively.
		 * \param t tolerance.
		 * \param pcIntersection precomputed node intersection.
		 * \param fill0 create a full set of child nodes for nodes that intersect
		 * the ray.
		 * \param pruneEmpty0 prune empty child nodes after processing an 
		 * intersection.
		 *
		 * \return number of nodes that have intersections.
		 */
		virtual unsigned int intersectRay(const Ionflux::GeoUtils::Line3& ray, 
		Ionflux::VolGfx::NodeIntersectionProcessor* processor = 0, 
		Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = true, double t 
		= DEFAULT_TOLERANCE, Ionflux::VolGfx::NodeIntersection* pcIntersection = 
		0, bool fill0 = false, bool pruneEmpty0 = false);
		
		/** Cast ray grid.
		 *
		 * Cast a number of rays arranged in a grid defined by the specified 
		 * parameters. Rays are arranged in a two-dimensional grid, where each
		 * ray is offset from the next along each coordinate by the ray origin
		 * step specified for that coordinate. The grid has a number of rays 
		 * in each coordinate according to the specified number of rays.
		 *
		 * \param rayOrigin ray origin.
		 * \param rayDirection ray direction.
		 * \param originStepX ray origin step (X).
		 * \param originStepY ray origin step (Y).
		 * \param numRaysX number of rays in X direction.
		 * \param numRaysY number of rays in Y direction.
		 * \param processor node intersection processor.
		 * \param filter node filter.
		 * \param recursive intersect nodes recursively.
		 * \param t tolerance.
		 * \param fill0 create a full set of child nodes for nodes that intersect
		 * a ray.
		 * \param pruneEmpty0 prune empty child nodes after processing an 
		 * intersection.
		 *
		 * \return number of nodes that have intersections.
		 */
		virtual unsigned int castRayGrid(const Ionflux::GeoUtils::Vector3& 
		rayOrigin, const Ionflux::GeoUtils::Vector3& rayDirection, const 
		Ionflux::GeoUtils::Vector3& originStepX, const 
		Ionflux::GeoUtils::Vector3& originStepY, unsigned int numRaysX, unsigned 
		int numRaysY, Ionflux::VolGfx::NodeIntersectionProcessor* processor = 0, 
		Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = true, double t 
		= DEFAULT_TOLERANCE, bool fill0 = false, bool pruneEmpty0 = false);
		
		/** Cast ray grid.
		 *
		 * Cast a number of rays arranged in a grid defined by the specified 
		 * parameters. Rays are arranged in a regular grid in such a way that 
		 * nodes on the specified target depth level are covered by one ray 
		 * each that passes through the center of each node at that depth 
		 * level. Rays in the grid are cast along the specified axis, and they
		 * are offset from the node by the specified \c planeOffset, given as 
		 * a fraction of the node size at the target level.
		 *
		 * \param axis axis to be used as the direction vector.
		 * \param targetDepth target depth level.
		 * \param planeOffset ray plane offset.
		 * \param processor node intersection processor.
		 * \param filter node filter.
		 * \param recursive intersect nodes recursively.
		 * \param t tolerance.
		 * \param fill0 create a full set of child nodes for nodes that intersect
		 * a ray.
		 * \param pruneEmpty0 prune empty child nodes after processing an 
		 * intersection.
		 *
		 * \return number of nodes that have intersections.
		 */
		virtual unsigned int castRayGrid(const Ionflux::GeoUtils::AxisID& axis, 
		int targetDepth = DEPTH_UNSPECIFIED, double planeOffset = 
		DEFAULT_RAY_PLANE_OFFSET, Ionflux::VolGfx::NodeIntersectionProcessor* 
		processor = 0, Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = 
		true, double t = DEFAULT_TOLERANCE, bool fill0 = false, bool pruneEmpty0 
		= false);
		
		/** Merge node hierarchies.
		 *
		 * Merge two node hierarchies. The merging operation will be applied 
		 * to a source and a target node if they pass their respective filters
		 * (if set). A valid source child node will be taken over by the 
		 * target node if either the corresponding target child note is not 
		 * set or the child merge policy is \c MERGE_POLICY_TAKE_OVER_SOURCE 
		 * and the source child node passes the source merge filter (if set). 
		 * A valid source data entry will be taken over by the target node if 
		 * either there is no data record attached to the target node or the 
		 * data merge policy is \c MERGE_POLICY_TAKE_OVER_SOURCE and the 
		 * source child node passes the source merge filter (if set). If \c 
		 * recursive is set to true, child nodes will be merged recursively if
		 * both the target and its corresponding source child node are set and
		 * the child node merge policy is either not \c 
		 * MERGE_POLICY_TAKE_OVER_SOURCE, or the source child node did not 
		 * pass the filter.
		 *
		 * \param source Source node.
		 * \param childPolicy Policy for merging child nodes.
		 * \param dataPolicy Policy for merging data.
		 * \param sourceFilter source node filter.
		 * \param targetFilter target node filter.
		 * \param sourceMergeFilter source node merge filter.
		 * \param recursive merge nodes recursively.
		 * \param fill0 Create a full set of child nodes on the target node if 
		 * one is missing.
		 *
		 * \return number of nodes that have been merged.
		 */
		virtual unsigned int merge(Ionflux::VolGfx::Node& source, 
		Ionflux::VolGfx::MergePolicyID childPolicy = MERGE_POLICY_KEEP_TARGET, 
		Ionflux::VolGfx::MergePolicyID dataPolicy = MERGE_POLICY_KEEP_TARGET, 
		Ionflux::VolGfx::NodeFilter* sourceFilter = 0, 
		Ionflux::VolGfx::NodeFilter* targetFilter = 0, 
		Ionflux::VolGfx::NodeFilter* sourceMergeFilter = 0, bool recursive = 
		true, bool fill0 = false);
		
		/** Print debug information.
		 *
		 * Print debug information.
		 *
		 * \param recursive List child nodes recursively.
		 * \param indentWidth Indentation width.
		 * \param indentChar Indentation character.
		 * \param depth Depth.
		 *
		 * \return String representation.
		 */
		virtual void printDebugInfo(bool recursive = false, unsigned int 
		indentWidth = Ionflux::ObjectBase::DEFAULT_INDENT_WIDTH, char indentChar 
		= ' ', unsigned int depth = 0) const;
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Get node data type string.
		 *
		 * Get a string representation for a node data type.
		 *
		 * \param t Node data type.
		 *
		 * \return Node data type string.
		 */
		static std::string getDataTypeString(Ionflux::VolGfx::NodeDataType t);
		
		/** Get number of elements for data type.
		 *
		 * Get the number of elements for array data types.
		 *
		 * \param t Node data type.
		 *
		 * \return number of elements for the data type, or DATA_SIZE_INVALID if 
		 * the data type is not an array type.
		 */
		static Ionflux::ObjectBase::DataSize 
		getDataTypeNumElements(Ionflux::VolGfx::NodeDataType t);
		
		/** Get node data value string.
		 *
		 * Get a string representation for a node data value.
		 *
		 * \param data Node data implementation.
		 *
		 * \return Node data type string.
		 */
		static std::string getDataValueString(Ionflux::VolGfx::NodeDataImpl* 
		data);
		
		/** Create node implementation.
		 *
		 * Create a new node implementation. The caller is responsible for 
		 * managing the node implementation.
		 *
		 * \return New node implementation.
		 */
		static Ionflux::VolGfx::NodeImpl* createImpl();
		
		/** Copy node implementation.
		 *
		 * Create a new node implementation that is a copy of the specified 
		 * node implementation. If \c takeover is set to \c true, the target 
		 * node implementation will take over the child nodes and data from 
		 * the source node implementation. In this case, the entries in the 
		 * source node related to the child nodes and data are cleared. 
		 * Otherwise, the child node and data entries will not be copied to 
		 * the target node implementation.
		 *
		 * \param source Source node implementation.
		 * \param target Target node implementation.
		 * \param takeover Take over the data of the source node.
		 */
		static void copyImpl(Ionflux::VolGfx::NodeImpl& source, 
		Ionflux::VolGfx::NodeImpl& target, bool takeover = false);
		
		/** Reference node implementation.
		 *
		 * Reference a node implementation.
		 *
		 * \param otherImpl Node implementation.
		 *
		 * \return New reference count of the node implementation.
		 */
		static Ionflux::ObjectBase::UInt16 refImpl(Ionflux::VolGfx::NodeImpl* 
		otherImpl);
		
		/** Clear node data implementation.
		 *
		 * Clear the data of the specified node data implementation.
		 *
		 * \param dataImpl Node data implementation.
		 */
		static void clearDataImpl(Ionflux::VolGfx::NodeDataImpl* dataImpl);
		
		/** Clear node implementation.
		 *
		 * Clear the child nodes and data of the specified node 
		 * implementation. This assumes that there are no references held on 
		 * any nodes that are part of the hierarchy starting from \c 
		 * otherImpl. If this is not the case, an exception will be thrown.
		 *
		 * \param otherImpl Node implementation.
		 * \param recursive Recursively clear data.
		 * \param clearData Clear data.
		 * \param clearChildNodes Clear child nodes.
		 */
		static void clearImpl(Ionflux::VolGfx::NodeImpl* otherImpl, bool 
		recursive = true, bool clearData = true, bool clearChildNodes = true);
		
		/** Unreference node implementation.
		 *
		 * Unreference a node implementation.
		 *
		 * \param otherImpl Node implementation.
		 *
		 * \return New reference count of the node implementation.
		 */
		static Ionflux::ObjectBase::UInt16 unrefImpl(Ionflux::VolGfx::NodeImpl* 
		otherImpl);
		
		/** Wrap node implementation.
		 *
		 * Wrap a node implementation in a new node object. If the node 
		 * implementation is 0, no node object will be created. The caller is 
		 * responsible for managing the returned object.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 *
		 * \return New node object, or 0 if the node implementation is 0.
		 */
		static Ionflux::VolGfx::Node* wrapImpl(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::VolGfx::Context* context);
		
		/** Set node implementation parent node.
		 *
		 * Set the parent node for all child nodes of the node implementation.
		 *
		 * \param otherImpl Node implementation.
		 */
		static void setImplParent(Ionflux::VolGfx::NodeImpl* otherImpl);
		
		/** Update node implementation state.
		 *
		 * Update the node implementation state according to changes in the 
		 * child nodes.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 */
		static void updateImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context);
		
		/** Create node data implementation.
		 *
		 * Create a new node data implementation. The caller is responsible 
		 * for managing the node implementation.
		 *
		 * \param t Node data type.
		 * \param newData Node data vector.
		 *
		 * \return New node data implementation.
		 */
		static Ionflux::VolGfx::NodeDataImpl* 
		createDataImpl(Ionflux::VolGfx::NodeDataType t, const 
		Ionflux::ObjectBase::DoubleVector* newData = 0);
		
		/** Get node data implementation allocated size.
		 *
		 * Get the allocated size in memory for a node data implementation, 
		 * including the size of the allocated data.
		 *
		 * \param dataImpl Node data implementation.
		 *
		 * \return allocated size of the node data.
		 */
		static unsigned int getDataImplMemSize(Ionflux::VolGfx::NodeDataImpl* 
		dataImpl);
		
		/** Set node data (color/normal).
		 *
		 * Set the color/normal data for the specified node data 
		 * implementation to the specified values.
		 *
		 * \param dataImpl Node data implementation.
		 * \param color color.
		 * \param normal normal vector.
		 */
		static void setDataImplColorNormal(Ionflux::VolGfx::NodeDataImpl* 
		dataImpl, const Ionflux::Altjira::Color& color, const 
		Ionflux::GeoUtils::Vector3& normal);
		
		/** Get node implementation data type.
		 *
		 * Get the data type of the node implementation data.
		 *
		 * \param otherImpl Node implementation.
		 *
		 * \return Node data type, or DATA_TYPE_NULL if the node does not have 
		 * any data.
		 */
		static Ionflux::VolGfx::NodeDataType 
		getImplDataType(Ionflux::VolGfx::NodeImpl* otherImpl);
		
		/** Check node implementation data type.
		 *
		 * Check if the node implementation has a data record of the specified
		 * type.
		 *
		 * \param otherImpl Node implementation.
		 * \param dataType data type.
		 *
		 * \return \c true if the node implementation has a data record of the 
		 * specified type, \c false otherwise.
		 */
		static bool hasImplDataType(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::NodeDataType dataType);
		
		/** Get node implementation data. This ensures that the data that is returned exists and has the specified type. If the node data has a different type, it will be cleared and a new data record of the specified type will be created and attached to the node implementation..
		 *
		 * \param otherImpl Node implementation.
		 * \param dataType data type.
		 *
		 * \return Node data implementation of specified type.
		 */
		static Ionflux::VolGfx::NodeDataImpl* 
		getImplData(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::NodeDataType dataType);
		
		/** Node data type voxel class information check.
		 *
		 * Check whether the specified node data type has voxel class 
		 * information attached.
		 *
		 * \param dataType Node data type.
		 *
		 * \return \c true if the specified node data type has voxel class 
		 * information attached, \c false otherwise.
		 */
		static bool dataTypeHasVoxelClassInfo(Ionflux::VolGfx::NodeDataType 
		dataType);
		
		/** Node data type voxel class information check.
		 *
		 * Check whether the specified node implementation has a data type 
		 * that has voxel class information attached.
		 *
		 * \param otherImpl Node implementation.
		 *
		 * \return \c true if the specified node implementation has a data type 
		 * that has voxel class information attached, \c false otherwise.
		 */
		static bool hasImplVoxelClassInfo(Ionflux::VolGfx::NodeImpl* otherImpl);
		
		/** Get node implementation voxel class.
		 *
		 * Get the voxel class of the node implementation.
		 *
		 * \param otherImpl Node implementation.
		 *
		 * \return Voxel class, or VOXEL_CLASS_UNDEFINED if the node does not 
		 * have voxel class data attached.
		 */
		static Ionflux::VolGfx::VoxelClassID 
		getImplVoxelClass(Ionflux::VolGfx::NodeImpl* otherImpl);
		
		/** Node implementation voxel class check.
		 *
		 * Check if the node implementation voxel class matches the specified 
		 * mask.
		 *
		 * \param otherImpl Node implementation.
		 * \param mask Voxel class mask.
		 *
		 * \return \c true if the node implementation voxel class matches the 
		 * specified mask, \c false otherwise.
		 */
		static bool hasImplVoxelClass(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::VoxelClassID mask);
		
		/** Set node implementation voxel class.
		 *
		 * Set the voxel class mask for the node implementation. If \c enable 
		 * is set to \c false, the specified voxel class mask will be unset 
		 * instead of set. If the node implementation does not have any data 
		 * of a compatible type attached and \c createDataType is 0, this 
		 * function does nothing. Otherwise, if there is no data attached to 
		 * the node, a new record of type \c createDataType will be created.
		 *
		 * \param otherImpl Node implementation.
		 * \param mask Voxel class mask.
		 * \param enable enable flag.
		 * \param createDataType data type for new records.
		 *
		 * \return new voxel class of the node implementation.
		 */
		static Ionflux::VolGfx::VoxelClassID 
		setImplVoxelClass(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::VoxelClassID mask, bool enable = true, 
		Ionflux::VolGfx::NodeDataType createDataType = DATA_TYPE_UNKNOWN);
		
		/** Set node implementation voxel class.
		 *
		 * Set the voxel class mask for node implementations within the 
		 * hierarchy that pass the specified filter. If \c enable is set to \c
		 * false, the specified voxel class mask will be unset instead of set.
		 * If one of the node implementations does not have any data of a 
		 * compatible type attached and \c createDataType is 0, it will be 
		 * left unchanged by this function. Otherwise, if there is no data 
		 * attached to the node, a new record of type \c createDataType will 
		 * be created.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param mask Voxel class mask.
		 * \param enable enable flag.
		 * \param filter node filter.
		 * \param recursive process nodes recursively.
		 * \param createDataType data type for new records.
		 *
		 * \return number of nodes on which the voxel class was set.
		 */
		static unsigned int setImplVoxelClass(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::VolGfx::Context* context, 
		Ionflux::VolGfx::VoxelClassID mask, bool enable = true, 
		Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = true, 
		Ionflux::VolGfx::NodeDataType createDataType = DATA_TYPE_UNKNOWN);
		
		/** Node data type color index check.
		 *
		 * Check whether the specified node data type has a color index 
		 * attached.
		 *
		 * \param dataType Node data type.
		 *
		 * \return \c true if the specified node data type has voxel class 
		 * information attached, \c false otherwise.
		 */
		static bool dataTypeHasColorIndex(Ionflux::VolGfx::NodeDataType 
		dataType);
		
		/** Node data type color index check.
		 *
		 * Check whether the specified node implementation has a data type 
		 * that has a color index attached.
		 *
		 * \param otherImpl Node implementation.
		 *
		 * \return \c true if the specified node implementation has a data type 
		 * that has a color index attached, \c false otherwise.
		 */
		static bool hasImplColorIndex(Ionflux::VolGfx::NodeImpl* otherImpl);
		
		/** Get node implementation color index.
		 *
		 * Get the color index of the node implementation.
		 *
		 * \param otherImpl Node implementation.
		 *
		 * \return Color index, or COLOR_INDEX_UNSPECIFIED if the node does not 
		 * have color index data attached.
		 */
		static Ionflux::VolGfx::ColorIndex 
		getImplColorIndex(Ionflux::VolGfx::NodeImpl* otherImpl);
		
		/** Set node implementation color index.
		 *
		 * Set the color index for the node implementation. If the node 
		 * implementation does not have any data of a compatible type attached
		 * and \c createDataType is 0, this function does nothing. Otherwise, 
		 * if there is no data attached to the node, a new record of type \c 
		 * createDataType will be created.
		 *
		 * \param otherImpl Node implementation.
		 * \param color Color index.
		 * \param createDataType data type for new records.
		 *
		 * \return new color of the node implementation.
		 */
		static Ionflux::VolGfx::ColorIndex 
		setImplColorIndex(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::ColorIndex color, Ionflux::VolGfx::NodeDataType 
		createDataType = DATA_TYPE_UNKNOWN);
		
		/** Set node implementation color index.
		 *
		 * Set the color index for node implementations within the hierarchy 
		 * that pass the specified filter. If one of the node implementations 
		 * does not have any data of a compatible type attached and \c 
		 * createDataType is 0, it will be left unchanged by this function. 
		 * Otherwise, if there is no data attached to the node, a new record 
		 * of type \c createDataType will be created.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param color Color index.
		 * \param filter node filter.
		 * \param recursive process nodes recursively.
		 * \param createDataType data type for new records.
		 *
		 * \return number of nodes on which the color index was set.
		 */
		static unsigned int setImplColorIndex(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::VolGfx::Context* context, Ionflux::VolGfx::ColorIndex
		color, Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = true, 
		Ionflux::VolGfx::NodeDataType createDataType = DATA_TYPE_UNKNOWN);
		
		/** Get node implementation boundary faces.
		 *
		 * Get the boundary faces of the node implementation.
		 *
		 * \param otherImpl Node implementation.
		 *
		 * \return boundary face mask, or DACE_UNDEFINED if the node does not 
		 * have boundary face data attached.
		 */
		static Ionflux::VolGfx::FaceMaskInt 
		getImplBoundaryFaces(Ionflux::VolGfx::NodeImpl* otherImpl);
		
		/** Get parent node implementation.
		 *
		 * Get the parent node implementation. The caller is responsible for 
		 * managing the returned object.
		 *
		 * \param otherImpl Node implementation.
		 *
		 * \return Parent node implementation, or 0 if the parent node does not 
		 * exist.
		 */
		static Ionflux::VolGfx::NodeImpl* 
		getImplParent(Ionflux::VolGfx::NodeImpl* otherImpl);
		
		/** Leaf check.
		 *
		 * Check whether the node implementation is a leaf node.
		 *
		 * \param otherImpl Node implementation.
		 *
		 * \return \c true if the node implementation is a leaf node, \c false 
		 * otherwise.
		 */
		static bool isImplLeaf(Ionflux::VolGfx::NodeImpl* otherImpl);
		
		/** Get leaf status.
		 *
		 * Get leaf status.
		 *
		 * \param otherImpl Node implementation.
		 *
		 * \return leaf status of the node implementation.
		 */
		static Ionflux::VolGfx::LeafStatusID 
		getImplLeafStatus(Ionflux::VolGfx::NodeImpl* otherImpl);
		
		/** Leaf check.
		 *
		 * Check whether the child node with the specified valid index is a 
		 * leaf node.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param orderIndex Order index.
		 *
		 * \return \c true if the child with the specified index is a leaf node, 
		 * \c false otherwise.
		 */
		static bool isImplLeafOrderChild(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, int orderIndex);
		
		/** Leaf check.
		 *
		 * Check whether the child node with the specified valid index is a 
		 * leaf node.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param index Index.
		 *
		 * \return \c true if the child with the specified index is a leaf node, 
		 * \c false otherwise.
		 */
		static bool isImplLeafValidChild(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, int index);
		
		/** Get depth.
		 *
		 * Get the depth of the node.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 *
		 * \return Node depth.
		 */
		static int getImplDepth(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context);
		
		/** Get maximum depth.
		 *
		 * Get the maximum depth of the node hierarchy.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 *
		 * \return Maximum node implementation depth of the hierarchy.
		 */
		static int getImplMaxDepth(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context);
		
		/** Get node ID.
		 *
		 * Get the ID of the node.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 *
		 * \return Node ID.
		 */
		static Ionflux::VolGfx::NodeID getImplNodeID(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::VolGfx::Context* context);
		
		/** Get valid child index.
		 *
		 * Get the index of the specified child node implementation among the 
		 * valid child node implementations.
		 *
		 * \param otherImpl Node implementation.
		 * \param childImpl Child node implementation.
		 *
		 * \return Index of the specified child node among the valid child nodes,
		 * or CHILD_INDEX_INVALID if the node is not a child of this node.
		 */
		static int getImplChildValidIndex(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::NodeImpl* childImpl);
		
		/** Get valid child index.
		 *
		 * Get the index of the child node with the specified order index 
		 * among the valid child nodes.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param orderIndex Order index.
		 *
		 * \return Index of the specified child node among the valid child nodes,
		 * or CHILD_INDEX_INVALID if the node is not a child of this node.
		 */
		static int getImplChildValidIndex(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, int orderIndex);
		
		/** Get child order index.
		 *
		 * Get the index of the child node with the specified valid index 
		 * among all child nodes (including invalid nodes). This can be used 
		 * to calculate the coordinates of a child node or to test the mask 
		 * bits.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param index Index.
		 *
		 * \return \c true if the child with the specified index is a leaf node, 
		 * \c false otherwise.
		 */
		static int getImplChildOrderIndex(Ionflux::VolGfx::NodeImpl* otherImpl, 
		const Ionflux::VolGfx::Context* context, int index);
		
		/** Get child order index.
		 *
		 * Get the order index of the specified child node implementation.
		 *
		 * \param otherImpl Node implementation.
		 * \param childImpl Child node implementation.
		 *
		 * \return \c true if the child with the specified index is a leaf node, 
		 * \c false otherwise.
		 */
		static int getImplChildOrderIndex(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::NodeImpl* childImpl);
		
		/** Get child node implementation by order index.
		 *
		 * Get the child node implementation with the specified order index. 
		 * The caller is responsible for managing the returned object.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param orderIndex Order index.
		 * \param autoCreate Create child nodes automatically if they do not 
		 * exist.
		 * \param fill0 Create a full set of child nodes if one is missing.
		 *
		 * \return Child node with the specified order index, or 0 if the child 
		 * node does not exist.
		 */
		static Ionflux::VolGfx::NodeImpl* 
		getImplChildByOrderIndex(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, int orderIndex, bool autoCreate = 
		false, bool fill0 = false);
		
		/** Get number of child nodes.
		 *
		 * Get the number of valid child nodes of this node.
		 *
		 * \param otherImpl Node implementation.
		 *
		 * \return String representation.
		 */
		static int getImplNumChildNodes(Ionflux::VolGfx::NodeImpl* otherImpl);
		
		/** Get child implementation by valid index.
		 *
		 * Get the child node implementation with the specified valid index. 
		 * If the child node with the specified index does not exist, an 
		 * exception will be raised.
		 *
		 * \param otherImpl Node implementation.
		 * \param index Valid index.
		 *
		 * \return Child node with the specified valid index.
		 */
		static Ionflux::VolGfx::NodeImpl* 
		getImplChildByValidIndex(Ionflux::VolGfx::NodeImpl* otherImpl, int 
		index);
		
		/** Locate child node implementation.
		 *
		 * Locate the child node that contains the specified location index. 
		 * If \c maxDepth is greater than zero, the search for the node stops 
		 * at the specified maximum depth.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param loc Node data.
		 * \param maxDepth Maximum depth.
		 *
		 * \return Node containing the specified location, or 0 if no suitable 
		 * node was found.
		 */
		static Ionflux::VolGfx::NodeImpl* 
		locateImplChild(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, const Ionflux::VolGfx::NodeLoc3& loc, 
		int maxDepth = DEPTH_UNSPECIFIED);
		
		/** Locate child node.
		 *
		 * Locate the child node that contains the specified point. If \c 
		 * maxDepth is greater than zero, the search for the node stops at the
		 * specified maximum depth. The caller is responsible for managing the
		 * returned object.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param p Point.
		 * \param maxDepth Maximum depth.
		 *
		 * \return Leaf node containing the specified location, or 0 if no 
		 * suitable node was found.
		 */
		static Ionflux::VolGfx::NodeImpl* 
		locateImplChild(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, const Ionflux::GeoUtils::Vector3& p, 
		int maxDepth = DEPTH_UNSPECIFIED);
		
		/** Insert child node implementation.
		 *
		 * Insert a child node at the specified depth that contains the 
		 * specified location index. If \c depth is negative, a leaf node at 
		 * the maximum depth will be inserted. If a node with the specified 
		 * location code already exists at the specified depth, that node will
		 * be returned.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param loc Node data.
		 * \param depth Depth at which to create the node.
		 * \param fill0 Create a full set of child nodes if one is missing.
		 * \param fillTargetDepth0 Create a full set of child nodes at the target
		 * depth level if one is missing.
		 *
		 * \return Node at the specified location and depth, or 0 if the location
		 * is outside the bounds of this node.
		 */
		static Ionflux::VolGfx::NodeImpl* 
		insertImplChild(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, const Ionflux::VolGfx::NodeLoc3& loc, 
		int depth = DEPTH_UNSPECIFIED, bool fill0 = false, bool fillTargetDepth0 
		= false);
		
		/** Insert child node implementation.
		 *
		 * Insert a child node at the specified depth that contains the 
		 * specified location index. If \c depth is negative, a leaf node at 
		 * the maximum depth will be inserted. If a node with the specified 
		 * location code already exists at the specified depth, that node will
		 * be returned.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param p Point.
		 * \param depth Depth at which to create the node.
		 * \param fill0 Create a full set of child nodes if one is missing.
		 * \param fillTargetDepth0 Create a full set of child nodes at the target
		 * depth level if one is missing.
		 *
		 * \return Node at the specified location and depth, or 0 if the location
		 * is outside the bounds of this node.
		 */
		static Ionflux::VolGfx::NodeImpl* 
		insertImplChild(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, const Ionflux::GeoUtils::Vector3& p, 
		int depth = DEPTH_UNSPECIFIED, bool fill0 = false, bool fillTargetDepth0 
		= false);
		
		/** Insert child node implementation.
		 *
		 * Insert a child node identified by the specified node ID. If \c 
		 * depth is not greater than zero, a leaf node at the maximum depth 
		 * will be inserted. If a node with the specified location code 
		 * already exists at the specified depth, that node will be returned.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param nodeID Node ID.
		 * \param fill0 Create a full set of child nodes if one is missing.
		 * \param fillTargetDepth0 Create a full set of child nodes at the target
		 * depth level if one is missing.
		 *
		 * \return Node at the specified location and depth, or 0 if the location
		 * is outside the bounds of this node.
		 */
		static Ionflux::VolGfx::NodeImpl* 
		insertImplChild(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, const Ionflux::VolGfx::NodeID& nodeID,
		bool fill0 = false, bool fillTargetDepth0 = false);
		
		/** Merge child nodes.
		 *
		 * Merge the nodes from the vector with the current child nodes of the
		 * node implementation. \c newNodes is expected to be a vector 
		 * containing a number of node implementations equal or greater than 
		 * the maximum number of child nodes per node, ordered by ascending 
		 * local X, Y, Z coordinate. Nodes that should not be changed are 
		 * identified by a zero entry within the vector. A new node 
		 * implementation will be created for each entry in \c newNodes. This 
		 * node implementation takes over all data and child nodes from the 
		 * entry in \c newNodes.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param newNodes Vector of node implementations.
		 * \param fill0 Create a full set of child nodes if one is missing.
		 */
		static void mergeImplChildNodes(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, const Ionflux::VolGfx::NodeImplVector&
		newNodes, bool fill0 = false);
		
		/** Set child node.
		 *
		 * Set the child node implementation for the child node with the 
		 * specified order index.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param newNode Child node implementation.
		 * \param orderIndex Order index.
		 */
		static void setImplChildByOrderIndex(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::VolGfx::Context* context, Ionflux::VolGfx::NodeImpl* 
		newNode, int orderIndex);
		
		/** Set child node.
		 *
		 * Set the child node implementation for the child node with the 
		 * specified valid index. Any existing child data for that index will 
		 * be cleared.
		 *
		 * \param otherImpl Node implementation.
		 * \param newImpl Child node implementation.
		 * \param index Valid index.
		 */
		static void setImplChildByValidIndex(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::VolGfx::NodeImpl* newImpl, int index);
		
		/** Set child nodes.
		 *
		 * Set the child nodes of the node. \c newNodes is expected to be a 
		 * vector containing a number of node implementations equal or greater
		 * than the maximum number of child nodes per node, ordered by 
		 * ascending local X, Y, Z coordinate. Invalid nodes are identified by
		 * a zero entry within the vector. Existing child nodes will be 
		 * cleared.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param newNodes Vector of node implementations.
		 */
		static void setImplChildNodes(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, const Ionflux::VolGfx::NodeImplVector&
		newNodes);
		
		/** Clear child nodes.
		 *
		 * Clear the child nodes indicated by a bit set in the child node 
		 * mask.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param clearNodes Mask indicating nodes to be cleared.
		 */
		static void clearImplChildNodes(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, const Ionflux::VolGfx::NodeChildMask& 
		clearNodes);
		
		/** Prune empty child nodes.
		 *
		 * Clear the child nodes which are leaf nodes but do not contain any 
		 * data.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param recursive recursively prune nodes.
		 *
		 * \return number of nodes that were pruned.
		 */
		static unsigned int pruneEmptyImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, bool recursive = false);
		
		/** Fill node.
		 *
		 * Fill the node. This creates new child nodes so that all children of
		 * this node are valid. If \c clearExisting is set to \c true, any 
		 * existing child nodes are cleared. If \c recursive is set to \c 
		 * true, child nodes are filled recursively. If \c maxDepth is not 
		 * negative, child nodes will be filled up to and including the 
		 * maximum depth specified.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param clearExisting Clear existing child nodes.
		 * \param recursive Fill nodes recursively.
		 * \param maxDepth Maximum depth.
		 *
		 * \return Number of new nodes that have been created.
		 */
		static int fillImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, bool clearExisting = false, bool 
		recursive = false, int maxDepth = DEPTH_UNSPECIFIED);
		
		/** Locate region.
		 *
		 * Locate the node that contains the specified region. If \c maxDepth 
		 * is greater than zero, the search for the node stops at the 
		 * specified maximum depth.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param region Region.
		 * \param maxDepth Maximum depth.
		 *
		 * \return Node containing the specified region, or 0 if no suitable node
		 * was found.
		 */
		static Ionflux::VolGfx::NodeImpl* 
		locateImplRegion(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, const Ionflux::VolGfx::Region3& 
		region, int maxDepth = DEPTH_UNSPECIFIED);
		
		/** Locate node implementation.
		 *
		 * Locate the node that contains the specified location index. If \c 
		 * maxDepth is not negative, the search for the node stops at the 
		 * specified maximum depth. This function will search the ancestors of
		 * the current node implementation upwards if the specified location 
		 * is not contained in this node.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param loc Location.
		 * \param maxDepth Maximum depth.
		 *
		 * \return Node containing the specified location, or 0 if no suitable 
		 * node was found.
		 */
		static Ionflux::VolGfx::NodeImpl* 
		locateImplNode(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, const Ionflux::VolGfx::NodeLoc3& loc, 
		int maxDepth = DEPTH_UNSPECIFIED);
		
		/** Get child location code.
		 *
		 * Get the location code of the child node with the specified order 
		 * index. This will also report the correct location code for child 
		 * nodes that currently do not exist. If The depth of a child node 
		 * would be above the maximum depth for the tree, an exception will be
		 * raised.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param orderIndex Order index.
		 *
		 * \return Location code for the child node with the specified order 
		 * index.
		 */
		static Ionflux::VolGfx::NodeLoc3 
		getImplChildLoc(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, int orderIndex);
		
		/** Get voxel size.
		 *
		 * Get the voxel size for the node.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 *
		 * \return Location vector.
		 */
		static double getImplVoxelSize(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context);
		
		/** Get voxel size.
		 *
		 * Get the voxel size for the node in location code units.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 *
		 * \return Location vector.
		 */
		static Ionflux::VolGfx::LocInt 
		getImplVoxelSizeLoc(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context);
		
		/** Get neighbor location code.
		 *
		 * Get the location code of the smallest size neighbor node with the 
		 * specified offset, where the offset is one of {-1, 0, 1} If the 
		 * neighbor node location is within the bounds of the tree, the 
		 * location code is stored in \c target. If no neighbor exists within 
		 * the bounds of the tree, the function returns \c false and the 
		 * contents of \c target is undefined.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param offsetX Offset (x).
		 * \param offsetY Offset (y).
		 * \param offsetZ Offset (z).
		 * \param target Where to store the neighbor location.
		 *
		 * \return \c true if the neighbor node exists, \c false otherwise.
		 */
		static bool getImplNeighborLoc(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, int offsetX, int offsetY, int offsetZ,
		Ionflux::VolGfx::NodeLoc3& target);
		
		/** Get location.
		 *
		 * Get the location vector for the corner of the node with the lowest 
		 * coordinates on each of the axes.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 *
		 * \return Location vector.
		 */
		static Ionflux::GeoUtils::Vector3 
		getImplLocation(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context);
		
		/** Get range.
		 *
		 * Get the range of values contained in the node implementation.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param target Where to store the range data.
		 */
		static void getImplRange(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, Ionflux::GeoUtils::Range3& target);
		
		/** Find node implementations.
		 *
		 * Find node implementations that pass the specified filter. If \c 
		 * target is 0, nodes will be counted but not added to the target set.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param target Where to store the node implementations.
		 * \param filter node filter.
		 * \param recursive find nodes recursively.
		 *
		 * \return number of node implementations found.
		 */
		static unsigned int findImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, Ionflux::VolGfx::NodeImplVector* 
		target, Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = true);
		
		/** Process node implementations.
		 *
		 * Process node implementations that pass the specified filter using 
		 * the specified node processors. The \c preProcessor is invoked 
		 * before the recursion. The \c postProcessor is invoked after the 
		 * recursion. Recursive traversal stops when the \c preProcessor 
		 * returns ChainableNodeProcessor::RESULT_FINISHED, or when the 
		 * maximum depth as set on the \c filter is reached.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param preProcessor node processor (pre).
		 * \param filter node filter.
		 * \param postProcessor node processor (post).
		 * \param recursive find nodes recursively.
		 *
		 * \return number of node implementations processed.
		 */
		static unsigned int processImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, Ionflux::VolGfx::NodeProcessor* 
		preProcessor, Ionflux::VolGfx::NodeFilter* filter = 0, 
		Ionflux::VolGfx::NodeProcessor* postProcessor = 0, bool recursive = 
		true);
		
		/** Get color.
		 *
		 * Get a color for the node implementation. If the optional \c colors 
		 * color set is specified, the color for the node is selected from the
		 * color set according to the depth level of the node and the 
		 * specified color offset. If \c colorIndex is not negative, the 
		 * specified color index will be used for selecting a color from the 
		 * color set. If the optional \c voxelClassColors is specified and the
		 * node has a voxel class attached to its data, the color for the node
		 * is selected according to the first entry in the vector that matches
		 * one of the voxel classes of the node. The \c colorIndex takes 
		 * precedence over all other color specifications, followed by the 
		 * node color index, the voxel class color, the leaf color index and 
		 * finally the depth based color.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param colors color set.
		 * \param colorIndexOffset color index offset.
		 * \param colorIndexRange color index range.
		 * \param colorIndex color index.
		 * \param leafColorIndex leaf color index.
		 * \param voxelClassColors voxel class colors.
		 *
		 * \return color, or 0 if no color is specified for the node.
		 */
		static Ionflux::Altjira::Color* getImplColor(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::VolGfx::Context* context, Ionflux::Altjira::ColorSet*
		colors = 0, unsigned int colorIndexOffset = 0, unsigned int 
		colorIndexRange = 0, int colorIndex = COLOR_INDEX_UNSPECIFIED, int 
		leafColorIndex = COLOR_INDEX_UNSPECIFIED, 
		Ionflux::VolGfx::VoxelClassColorVector* voxelClassColors = 0);
		
		/** Get mesh.
		 *
		 * Get a mesh for the node implementation. One box is generated for 
		 * each node. If the optional \c colors color set is specified, the 
		 * vertex colors for each box are selected from the color set 
		 * according to the depth level of the node. Node colors are selected 
		 * according to getImplColor(). Boxes will be inset by the amount 
		 * specified in \c boxInset, scaled by the size of the octree. The 
		 * mesh for the node will be merged into the \c target mesh.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param target where to store the mesh.
		 * \param boxInset box inset per depth level.
		 * \param colors vertex colors.
		 * \param colorIndexOffset color index offset.
		 * \param colorIndexRange color index range.
		 * \param colorIndex color index.
		 * \param leafColorIndex leaf color index.
		 * \param filter node filter.
		 * \param recursive recursively create meshes.
		 */
		static void getImplMesh(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, Ionflux::GeoUtils::Mesh& target, 
		double boxInset = Ionflux::VolGfx::Context::DEFAULT_BOX_INSET, 
		Ionflux::Altjira::ColorSet* colors = 0, unsigned int colorIndexOffset = 
		0, unsigned int colorIndexRange = 0, int colorIndex = 
		COLOR_INDEX_UNSPECIFIED, int leafColorIndex = COLOR_INDEX_UNSPECIFIED, 
		Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = false);
		
		/** Get vertex attributes.
		 *
		 * Get vertex attributes for the node implementation. If the optional 
		 * \c colors color set is specified, the vertex colors for the box are
		 * selected from the color set according to the depth level of the 
		 * node and the specified color offset. Boxes will be inset by the 
		 * amount specified in \c boxInset, scaled by the leaf voxel size. 
		 * Data will be appended to a specified vertex attributes for each 
		 * target vertex attribute that is not null. Node colors are selected 
		 * according to getImplColor(). If the optional \c positionOffset or 
		 * \c positionScale are specified, vertex positions will be scaled or 
		 * translated by these vectors.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param positionTarget target for position data.
		 * \param colorTarget target for color data.
		 * \param normalTarget target for normal data.
		 * \param nFaceType Mesh N-face type.
		 * \param boxInset box inset per depth level.
		 * \param colors vertex colors.
		 * \param colorIndexOffset color index offset.
		 * \param colorIndexRange color index range.
		 * \param colorIndex color index.
		 * \param leafColorIndex leaf color index.
		 * \param voxelClassColors voxel class colors.
		 * \param positionOffset position offset.
		 * \param positionScale position scale.
		 * \param filter node filter.
		 * \param recursive recursively get vertex attributes.
		 * \param boundaryFacesOnly show only boundary faces.
		 */
		static void getImplVertexAttributes(Ionflux::VolGfx::NodeImpl* otherImpl,
		Ionflux::VolGfx::Context* context, Ionflux::GeoUtils::VertexAttribute* 
		positionTarget = 0, Ionflux::GeoUtils::VertexAttribute* colorTarget = 0, 
		Ionflux::GeoUtils::VertexAttribute* normalTarget = 0, 
		Ionflux::GeoUtils::NFaceTypeID nFaceType = 
		Ionflux::GeoUtils::NFace::TYPE_FACE, double boxInset = 
		Ionflux::VolGfx::Context::DEFAULT_BOX_INSET, Ionflux::Altjira::ColorSet* 
		colors = 0, unsigned int colorIndexOffset = 0, unsigned int 
		colorIndexRange = 0, int colorIndex = COLOR_INDEX_UNSPECIFIED, int 
		leafColorIndex = COLOR_INDEX_UNSPECIFIED, 
		Ionflux::VolGfx::VoxelClassColorVector* voxelClassColors = 0, 
		Ionflux::GeoUtils::Vector* positionOffset = 0, Ionflux::GeoUtils::Vector*
		positionScale = 0, Ionflux::VolGfx::NodeFilter* filter = 0, bool 
		recursive = false, bool boundaryFacesOnly = false);
		
		/** Get number of faces.
		 *
		 * Get the number of faces for the node implementation. This is the 
		 * total number of faces attached to the node or, if \c recursive is 
		 * set to \c true, the hierarchy of nodes starting at this node.
		 *
		 * \param otherImpl Node implementation.
		 * \param recursive count faces recursively.
		 *
		 * \return Number of faces.
		 */
		static unsigned int getImplNumFaces(Ionflux::VolGfx::NodeImpl* otherImpl,
		bool recursive = false);
		
		/** Get face color/normal.
		 *
		 * Get the area-weighted average face color and normal for the node 
		 * implementation. If \c recursive is set to \c true, the face 
		 * color/normals are calculated for the hierarchy of nodes starting at
		 * this node. Colors and normals are assumed to be uniform across each
		 * face. Only the first entry in each face data set will be used.
		 *
		 * \param otherImpl Node implementation.
		 * \param targetColor target color.
		 * \param targetNormal target color.
		 * \param recursive count faces recursively.
		 *
		 * \return total area of faces.
		 */
		static double getImplFaceColorNormal(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::Altjira::Color& targetColor, 
		Ionflux::GeoUtils::Vector3& targetNormal, bool recursive = false);
		
		/** Insert face for voxelization.
		 *
		 * Insert a face into the node hierarchy for voxelization. The face 
		 * will be attached to the deepest node that completely contains its 
		 * voxelization.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param face face.
		 * \param sep separability.
		 * \param fill0 Create a full set of child nodes if one is missing.
		 *
		 * \return \c true if the face was inserted into the node hierarchy, \c 
		 * false if the node hierarchy does not contain the face voxelization.
		 */
		static bool voxelizeImplInsertFace(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, Ionflux::GeoUtils::Face* face, 
		Ionflux::VolGfx::SeparabilityID sep, bool fill0 = false);
		
		/** Insert faces for voxelization.
		 *
		 * Insert faces from the mesh into the node hierarchy for 
		 * voxelization. Each face will be attached to the deepest node that 
		 * completely contains its voxelization.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param mesh mesh.
		 * \param sep separability.
		 * \param fill0 Create a full set of child nodes if one is missing.
		 *
		 * \return number of faces that were inserted into the node hierarchy.
		 */
		static unsigned int voxelizeImplInsertFaces(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::VolGfx::Context* context, const 
		Ionflux::GeoUtils::Mesh& mesh, Ionflux::VolGfx::SeparabilityID sep, bool 
		fill0 = false);
		
		/** Voxelize faces.
		 *
		 * Voxelize faces that are attached to the node hierarchy. The 
		 * voxelization data will replace any data currently attached to the 
		 * nodes (including face data). Data will be generated according to 
		 * the \c target parameter, at the depth level specified via the \c 
		 * targetDepth parameter. If \c targetDepth is negative, the target 
		 * depth is set to the maximum depth. Faces passed in via the optional
		 * \c faces parameter will be appended to the face list for the node.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param processor node processor.
		 * \param targetDepth target depth.
		 * \param sep separability.
		 * \param fillTargetDepth Create a full set of child nodes at the target 
		 * depth if one is missing.
		 * \param pruneEmpty0 Prune empty child nodes after voxelization.
		 * \param faces0 additional faces.
		 *
		 * \return number of voxels that were set.
		 */
		static unsigned int voxelizeImplFaces(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::VolGfx::Context* context, 
		Ionflux::VolGfx::NodeProcessor* processor, int targetDepth, 
		Ionflux::VolGfx::SeparabilityID sep, bool fillTargetDepth = false, bool 
		pruneEmpty0 = false, Ionflux::GeoUtils::FaceVector* faces0 = 0);
		
		/** Get node implementation allocated size.
		 *
		 * Get the allocated size in memory for a node implementation, 
		 * including the size of the allocated data.
		 *
		 * \param otherImpl Node implementation.
		 * \param recursive recursively calculate allocated size.
		 *
		 * \return allocated size of the node implementation.
		 */
		static unsigned int getImplMemSize(Ionflux::VolGfx::NodeImpl* otherImpl, 
		bool recursive = false);
		
		/** Serialize data implementation.
		 *
		 * Serialize data implementation.
		 *
		 * \param dataImpl Node data implementation.
		 * \param target where to store the serialized data.
		 */
		static void serializeDataImpl(Ionflux::VolGfx::NodeDataImpl* dataImpl, 
		std::string& target);
		
		/** Get serialized size of data value.
		 *
		 * Get the serialized size of a single data value.
		 *
		 * \return serialized size of data value.
		 */
		static Ionflux::ObjectBase::DataSize getDataValueSerializedSize();
		
		/** Get serialized size of data implementation.
		 *
		 * Get the serialized size of a data implementation of the specified 
		 * type.
		 *
		 * \param t Node data type.
		 *
		 * \return serialized size of node data implementation.
		 */
		static Ionflux::ObjectBase::DataSize 
		getDataImplSerializedSize(Ionflux::VolGfx::NodeDataType t = 
		DATA_TYPE_NULL);
		
		/** Deserialize data implementation.
		 *
		 * Deserialize data implementation.
		 *
		 * \param dataImpl Node data implementation.
		 * \param source serialized data.
		 * \param offset deserialization offset.
		 *
		 * \return offset of remaining data.
		 */
		static Ionflux::ObjectBase::DataSize 
		deserializeDataImpl(Ionflux::VolGfx::NodeDataImpl* dataImpl, const 
		std::string& source, Ionflux::ObjectBase::DataSize offset = 0);
		
		/** Deserialize node data implementation.
		 *
		 * Deserialize a node data implementation from the specified stream.
		 *
		 * \param dataImpl Node data implementation.
		 * \param source data source.
		 * \param offset offset.
		 * \param poMapCurrent pointer/offset map (current).
		 */
		static void deserializeDataImpl(Ionflux::VolGfx::NodeDataImpl* dataImpl, 
		std::istream& source, Ionflux::ObjectBase::DataSize offset = 
		Ionflux::ObjectBase::DATA_SIZE_INVALID, 
		Ionflux::ObjectBase::PointerOffsetMap* poMapCurrent = 0);
		
		/** Deserialize node data implementation.
		 *
		 * Deserialize a node data implementation from the specified stream.
		 *
		 * \param dataImpl Node data implementation.
		 * \param ioContext I/O context.
		 * \param offset offset.
		 */
		static void deserializeDataImpl(Ionflux::VolGfx::NodeDataImpl* dataImpl, 
		Ionflux::VolGfx::IOContext& ioContext, Ionflux::ObjectBase::DataSize 
		offset = Ionflux::ObjectBase::DATA_SIZE_INVALID);
		
		/** Serialize node implementation.
		 *
		 * Serialize node implementation.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param target where to store the serialized data.
		 * \param magicSyllable magic syllable to be used to indicate the node 
		 * type.
		 */
		static void serializeImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, std::string& target, 
		Ionflux::ObjectBase::MagicSyllable magicSyllable = MAGIC_SYLLABLE_NODE);
		
		/** Serialize child node implementations.
		 *
		 * Serialize child node implementations of the specified node 
		 * implementation. Child node implementations will be serialized in 
		 * order of increasing depth, between the minimum and maximum depth 
		 * specified. If \c recursive is set to \c true, child node 
		 * implementations will be serialized recursively. Offsets for the 
		 * child node implementations will be stored in the pointer/offset 
		 * map.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param target where to store the serialized data.
		 * \param poMap pointer/offset map.
		 * \param minDepth minimum depth.
		 * \param maxDepth maximum depth.
		 * \param recursive recursively serialize child node implementations.
		 * \param serializeData serialize child node data.
		 */
		static void serializeImplChildNodes(Ionflux::VolGfx::NodeImpl* otherImpl,
		Ionflux::VolGfx::Context* context, std::ostream& target, 
		Ionflux::ObjectBase::PointerOffsetMap& poMap, int minDepth = 1, int 
		maxDepth = DEPTH_UNSPECIFIED, bool recursive = true, bool serializeData =
		true);
		
		/** Serialize child node implementations.
		 *
		 * Serialize child node implementations of the specified node 
		 * implementation. Child node implementations will be serialized in 
		 * order of increasing depth, between the minimum and maximum depth 
		 * specified. If \c recursive is set to \c true, child node 
		 * implementations will be serialized recursively. Offsets for the 
		 * child node implementations will be stored in the pointer/offset 
		 * map.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param ioContext I/O context.
		 * \param minDepth minimum depth.
		 * \param maxDepth maximum depth.
		 * \param recursive recursively serialize child node implementations.
		 * \param serializeData serialize child node data.
		 */
		static void serializeImplChildNodes(Ionflux::VolGfx::NodeImpl* otherImpl,
		Ionflux::VolGfx::Context* context, Ionflux::VolGfx::IOContext& ioContext,
		int minDepth = 1, int maxDepth = DEPTH_UNSPECIFIED, bool recursive = 
		true, bool serializeData = true);
		
		/** Get serialized size of node implementation.
		 *
		 * Get the serialized size of a node implementation.
		 *
		 * \param t Node data type.
		 *
		 * \return serialized size of node implementation.
		 */
		static Ionflux::ObjectBase::DataSize 
		getImplSerializedSize(Ionflux::VolGfx::NodeDataType t = DATA_TYPE_NULL);
		
		/** Serialize node implementation hierarchy.
		 *
		 * Serialize the node implementation hierarchy of which the specified 
		 * node is the root node.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param target where to store the serialized data.
		 * \param header where to store the header.
		 * \param poMap where to store the pointer/offset map.
		 */
		static void serializeImplHierarchy(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, std::ostream& target, 
		Ionflux::VolGfx::NodeImplHierarchyHeader* header = 0, 
		Ionflux::ObjectBase::PointerOffsetMap* poMap = 0);
		
		/** Serialize node implementation hierarchy.
		 *
		 * Serialize the node implementation hierarchy of which the specified 
		 * node is the root node.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param ioContext I/O context.
		 */
		static void serializeImplHierarchy(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, Ionflux::VolGfx::IOContext& 
		ioContext);
		
		/** Get serialized size of node implementation hierarchy header.
		 *
		 * Get the serialized size of a node implementation hierarchy header.
		 *
		 * \return serialized size of node implementation.
		 */
		static Ionflux::ObjectBase::DataSize 
		getImplHierarchyHeaderSerializedSize();
		
		/** Deserialize node implementation.
		 *
		 * Deserialize node implementation.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param source serialized data.
		 * \param offset deserialization offset.
		 * \param magicSyllable magic syllable to be used to indicate the node 
		 * type.
		 *
		 * \return offset of remaining data.
		 */
		static Ionflux::ObjectBase::DataSize 
		deserializeImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, const std::string& source, 
		Ionflux::ObjectBase::DataSize offset = 0, 
		Ionflux::ObjectBase::MagicSyllable magicSyllable = MAGIC_SYLLABLE_NODE);
		
		/** Deserialize node implementation.
		 *
		 * Deserialize node implementation.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param source source stream.
		 * \param header node implementation hierarchy header.
		 * \param poMap pointer/offset map.
		 * \param offset deserialization offset.
		 * \param magicSyllable magic syllable to be used to indicate the node 
		 * type.
		 * \param poMapCurrent pointer/offset map (current).
		 * \param deserializeData deserialize node data.
		 * \param zeroChildPointer zero the child pointer.
		 * \param zeroParentPointer zero the parent pointer.
		 */
		static void deserializeImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, std::istream& source, const 
		Ionflux::VolGfx::NodeImplHierarchyHeader& header, const 
		Ionflux::ObjectBase::PointerOffsetMap& poMap, 
		Ionflux::ObjectBase::DataSize offset = 
		Ionflux::ObjectBase::DATA_SIZE_INVALID, 
		Ionflux::ObjectBase::MagicSyllable magicSyllable = MAGIC_SYLLABLE_NODE, 
		Ionflux::ObjectBase::PointerOffsetMap* poMapCurrent = 0, bool 
		deserializeData = true, bool zeroChildPointer = true, bool 
		zeroParentPointer = true);
		
		/** Deserialize node implementation.
		 *
		 * Deserialize node implementation.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param ioContext I/O context.
		 * \param offset deserialization offset.
		 * \param magicSyllable magic syllable to be used to indicate the node 
		 * type.
		 * \param deserializeData deserialize node data.
		 * \param zeroChildPointer zero the child pointer.
		 * \param zeroParentPointer zero the parent pointer.
		 */
		static void deserializeImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, Ionflux::VolGfx::IOContext& ioContext,
		Ionflux::ObjectBase::DataSize offset = 
		Ionflux::ObjectBase::DATA_SIZE_INVALID, 
		Ionflux::ObjectBase::MagicSyllable magicSyllable = MAGIC_SYLLABLE_NODE, 
		bool deserializeData = true, bool zeroChildPointer = true, bool 
		zeroParentPointer = true);
		
		/** Deserialize child node implementations.
		 *
		 * Deserialize child node implementations of the node implementation 
		 * with the specified serialized child pointer from the source stream.
		 * Deserialized child node implementations will be added as 
		 * descendants of the specified node implementation. Child node 
		 * implementations will be deserialized up to the maximum depth 
		 * specified. If \c recursive is set to \c true, child node 
		 * implementations will be serialized recursively. Offsets for the 
		 * child node implementations will be obtained from the pointer/offset
		 * map. \c magicSyllable will be used for extracting the node 
		 * implementation at the specified stream offset. For all other node 
		 * implementations, MAGIC_SYLLABLE_NODE will be used.
		 * 
		 * \note This function requires \c otherImpl to be the deserialized 
		 * node implementation data, with a zero child pointer, corresponding 
		 * to \c childPointer. The original node data for this node will not 
		 * be read from the stream. To use any existing node as the target 
		 * node implementation, use the version of deserializeImplChildNodes()
		 * that takes a stream offset as a parameter.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param source source stream.
		 * \param childPointer serialized child pointer.
		 * \param header node implementation hierarchy header.
		 * \param poMap pointer/offset map.
		 * \param poMapCurrent pointer/offset map (current).
		 * \param maxDepth maximum depth.
		 * \param recursive recursively deserialize child node implementations.
		 * \param deserializeData deserialize child node data.
		 */
		static void deserializeImplChildNodes(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::VolGfx::Context* context, std::istream& source, 
		Ionflux::ObjectBase::GenericPointer childPointer, const 
		Ionflux::VolGfx::NodeImplHierarchyHeader& header, 
		Ionflux::ObjectBase::PointerOffsetMap& poMap, 
		Ionflux::ObjectBase::PointerOffsetMap* poMapCurrent = 0, int maxDepth = 
		DEPTH_UNSPECIFIED, bool recursive = true, bool deserializeData = true);
		
		/** Deserialize child node implementations.
		 *
		 * Deserialize child node implementations of the node implementation 
		 * with the specified serialized child pointer from the source stream.
		 * Deserialized child node implementations will be added as 
		 * descendants of the specified node implementation. Child node 
		 * implementations will be deserialized up to the maximum depth 
		 * specified. If \c recursive is set to \c true, child node 
		 * implementations will be serialized recursively. Offsets for the 
		 * child node implementations will be obtained from the pointer/offset
		 * map. \c magicSyllable will be used for extracting the node 
		 * implementation at the specified stream offset. For all other node 
		 * implementations, MAGIC_SYLLABLE_NODE will be used.
		 * 
		 * \note This function requires \c otherImpl to be the deserialized 
		 * node implementation data, with a zero child pointer, corresponding 
		 * to \c childPointer. The original node data for this node will not 
		 * be read from the stream. To use any existing node as the target 
		 * node implementation, use the version of deserializeImplChildNodes()
		 * that takes a stream offset as a parameter.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param ioContext I/O context.
		 * \param childPointer serialized child pointer.
		 * \param maxDepth maximum depth.
		 * \param recursive recursively deserialize child node implementations.
		 * \param deserializeData deserialize child node data.
		 */
		static void deserializeImplChildNodes(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::VolGfx::Context* context, Ionflux::VolGfx::IOContext&
		ioContext, Ionflux::ObjectBase::GenericPointer childPointer, int maxDepth
		= DEPTH_UNSPECIFIED, bool recursive = true, bool deserializeData = true);
		
		/** Deserialize child node implementations.
		 *
		 * Deserialize child node implementations of the node implementation 
		 * with the specified stream offset from the source stream. 
		 * Deserialized child node implementations will be added as 
		 * descendants of the specified node implementation. Child node 
		 * implementations will be deserialized up to the maximum depth 
		 * specified. If \c recursive is set to \c true, child node 
		 * implementations will be serialized recursively. Offsets for the 
		 * child node implementations will be obtained from the pointer/offset
		 * map. \c magicSyllable will be used for extracting the node 
		 * implementation at the specified stream offset. For all other node 
		 * implementations, MAGIC_SYLLABLE_NODE will be used.
		 * 
		 * \note This function will read the original node implementation data
		 * from the stream and initialize \c otherImpl accordingly.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param source source stream.
		 * \param offset stream offset of the node implementation.
		 * \param header node implementation hierarchy header.
		 * \param poMap pointer/offset map.
		 * \param poMapCurrent pointer/offset map (current).
		 * \param magicSyllable magic syllable to be used to indicate the node 
		 * type.
		 * \param maxDepth maximum depth.
		 * \param recursive recursively deserialize child node implementations.
		 * \param deserializeData deserialize child node data.
		 */
		static void deserializeImplChildNodes(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::VolGfx::Context* context, std::istream& source, 
		Ionflux::ObjectBase::DataSize offset, const 
		Ionflux::VolGfx::NodeImplHierarchyHeader& header, 
		Ionflux::ObjectBase::PointerOffsetMap& poMap, 
		Ionflux::ObjectBase::PointerOffsetMap* poMapCurrent = 0, 
		Ionflux::ObjectBase::MagicSyllable magicSyllable = MAGIC_SYLLABLE_NODE, 
		int maxDepth = DEPTH_UNSPECIFIED, bool recursive = true, bool 
		deserializeData = true);
		
		/** Deserialize child node implementations.
		 *
		 * Deserialize child node implementations of the node implementation 
		 * with the specified stream offset from the source stream. 
		 * Deserialized child node implementations will be added as 
		 * descendants of the specified node implementation. Child node 
		 * implementations will be deserialized up to the maximum depth 
		 * specified. If \c recursive is set to \c true, child node 
		 * implementations will be serialized recursively. Offsets for the 
		 * child node implementations will be obtained from the pointer/offset
		 * map. \c magicSyllable will be used for extracting the node 
		 * implementation at the specified stream offset. For all other node 
		 * implementations, MAGIC_SYLLABLE_NODE will be used.
		 * 
		 * \note This function will read the original node implementation data
		 * from the stream and initialize \c otherImpl accordingly.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param ioContext I/O context.
		 * \param offset stream offset of the node implementation.
		 * \param magicSyllable magic syllable to be used to indicate the node 
		 * type.
		 * \param maxDepth maximum depth.
		 * \param recursive recursively deserialize child node implementations.
		 * \param deserializeData deserialize child node data.
		 */
		static void deserializeImplChildNodes(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::VolGfx::Context* context, Ionflux::VolGfx::IOContext&
		ioContext, Ionflux::ObjectBase::DataSize offset, 
		Ionflux::ObjectBase::MagicSyllable magicSyllable = MAGIC_SYLLABLE_NODE, 
		int maxDepth = DEPTH_UNSPECIFIED, bool recursive = true, bool 
		deserializeData = true);
		
		/** Deserialize node implementation hierarchy.
		 *
		 * Deserialize a node implementation hierarchy from the specified 
		 * source. The specified node implementation will become the root of 
		 * the hierarchy. If \c targetNode is specified, the node ID of the 
		 * root node of the deserialized hierarchy will be stored in \c 
		 * targetNode.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param source data source.
		 * \param header where to store the node implementation hierarchy header.
		 * \param targetNode where to store the node ID.
		 * \param poMap where to store the pointer/offset map (serialized).
		 * \param poMapCurrent where to store the pointer/offset map (current).
		 * \param deserializeData deserialize node data.
		 * \param maxDepth maximum depth for deserializing child nodes.
		 */
		static void deserializeImplHierarchy(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::VolGfx::Context* context, std::istream& source, 
		Ionflux::VolGfx::NodeImplHierarchyHeader* header = 0, 
		Ionflux::VolGfx::NodeID* targetNode = 0, 
		Ionflux::ObjectBase::PointerOffsetMap* poMap = 0, 
		Ionflux::ObjectBase::PointerOffsetMap* poMapCurrent = 0, bool 
		deserializeData = true, int maxDepth = DEPTH_UNSPECIFIED);
		
		/** Deserialize node implementation hierarchy.
		 *
		 * Deserialize a node implementation hierarchy from the specified 
		 * source. The specified node implementation will become the root of 
		 * the hierarchy. If \c targetNode is specified, the node ID of the 
		 * root node of the deserialized hierarchy will be stored in \c 
		 * targetNode.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param ioContext I/O context.
		 * \param deserializeData deserialize node data.
		 * \param maxDepth maximum depth for deserializing child nodes.
		 */
		static void deserializeImplHierarchy(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::VolGfx::Context* context, Ionflux::VolGfx::IOContext&
		ioContext, bool deserializeData = true, int maxDepth = 
		DEPTH_UNSPECIFIED);
		
		/** Get node implementation array stride.
		 *
		 * Get the node implementation array stride.
		 *
		 * \return node implementation array stride.
		 */
		static Ionflux::ObjectBase::DataSize getImplArrayStride();
		
		/** Intersect ray.
		 *
		 * Find intersections between the node implementation and the 
		 * specified ray.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param ray ray.
		 * \param target where to store the node intersection data.
		 * \param t tolerance.
		 *
		 * \return \c true if the intersection is valid, \c false otherwise.
		 */
		static bool intersectRayImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, const Ionflux::GeoUtils::Line3& ray, 
		Ionflux::VolGfx::NodeIntersection& target, double t = DEFAULT_TOLERANCE);
		
		/** Intersect ray.
		 *
		 * Find intersections between the node and the specified ray. Node 
		 * intersections are passed to the specified intersection processor in
		 * order of occurence along the ray. Ray traversal stops when the 
		 * processor returns ChainableNodeProcessor::RESULT_FINISHED. If \c 
		 * filter is specified, only intersections for nodes that pass the 
		 * filter will be processed. However, if \c recursive is \c true, 
		 * child nodes of nodes that intersect the ray but do not pass the 
		 * filter are still be processed, up to the maximum depth specified on
		 * the filter.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param ray ray.
		 * \param processor node intersection processor.
		 * \param filter node filter.
		 * \param recursive intersect nodes recursively.
		 * \param t tolerance.
		 * \param pcIntersection precomputed node intersection.
		 * \param fill0 create a full set of child nodes for nodes that intersect
		 * the ray.
		 * \param pruneEmpty0 prune empty child nodes after processing an 
		 * intersection.
		 *
		 * \return number of nodes that have intersections.
		 */
		static unsigned int intersectRayImpl(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::VolGfx::Context* context, const 
		Ionflux::GeoUtils::Line3& ray, 
		Ionflux::VolGfx::NodeIntersectionProcessor* processor = 0, 
		Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = true, double t 
		= DEFAULT_TOLERANCE, const Ionflux::VolGfx::NodeIntersection* 
		pcIntersection = 0, bool fill0 = false, bool pruneEmpty0 = false);
		
		/** Cast ray grid.
		 *
		 * Cast a number of rays arranged in a grid defined by the specified 
		 * parameters. Rays are arranged in a two-dimensional grid, where each
		 * ray is offset from the next along each coordinate by the ray origin
		 * step specified for that coordinate. The grid has a number of rays 
		 * in each coordinate according to the specified number of rays.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param rayOrigin ray origin.
		 * \param rayDirection ray direction.
		 * \param originStepX ray origin step (X).
		 * \param originStepY ray origin step (Y).
		 * \param numRaysX number of rays in X direction.
		 * \param numRaysY number of rays in Y direction.
		 * \param processor node intersection processor.
		 * \param filter node filter.
		 * \param recursive intersect nodes recursively.
		 * \param t tolerance.
		 * \param fill0 create a full set of child nodes for nodes that intersect
		 * a ray.
		 * \param pruneEmpty0 prune empty child nodes after processing an 
		 * intersection.
		 *
		 * \return number of nodes that have intersections.
		 */
		static unsigned int castRayGridImpl(Ionflux::VolGfx::NodeImpl* otherImpl,
		Ionflux::VolGfx::Context* context, const Ionflux::GeoUtils::Vector3& 
		rayOrigin, const Ionflux::GeoUtils::Vector3& rayDirection, const 
		Ionflux::GeoUtils::Vector3& originStepX, const 
		Ionflux::GeoUtils::Vector3& originStepY, unsigned int numRaysX, unsigned 
		int numRaysY, Ionflux::VolGfx::NodeIntersectionProcessor* processor = 0, 
		Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = true, double t 
		= DEFAULT_TOLERANCE, bool fill0 = false, bool pruneEmpty0 = false);
		
		/** Cast ray grid.
		 *
		 * Cast a number of rays arranged in a grid defined by the specified 
		 * parameters. Rays are arranged in a regular grid in such a way that 
		 * nodes on the specified target depth level are covered by one ray 
		 * each that passes through the center of each node at that depth 
		 * level. Rays in the grid are cast along the specified axis, and they
		 * are offset from the node by the specified \c planeOffset, given as 
		 * a fraction of the node size at the target level.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param axis axis to be used as the direction vector.
		 * \param targetDepth target depth level.
		 * \param planeOffset ray plane offset.
		 * \param processor node intersection processor.
		 * \param filter node filter.
		 * \param recursive intersect nodes recursively.
		 * \param t tolerance.
		 * \param fill0 create a full set of child nodes for nodes that intersect
		 * a ray.
		 * \param pruneEmpty0 prune empty child nodes after processing an 
		 * intersection.
		 *
		 * \return number of nodes that have intersections.
		 */
		static unsigned int castRayGridImpl(Ionflux::VolGfx::NodeImpl* otherImpl,
		Ionflux::VolGfx::Context* context, const Ionflux::GeoUtils::AxisID& axis,
		int targetDepth = DEPTH_UNSPECIFIED, double planeOffset = 
		DEFAULT_RAY_PLANE_OFFSET, Ionflux::VolGfx::NodeIntersectionProcessor* 
		processor = 0, Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = 
		true, double t = DEFAULT_TOLERANCE, bool fill0 = false, bool pruneEmpty0 
		= false);
		
		/** Merge node hierarchies.
		 *
		 * Merge two node implementation hierarchies. The merging operation 
		 * will be applied to a source and a target node if they pass their 
		 * respective filters (if set). A valid source child node will be 
		 * taken over by the target node if either the corresponding target 
		 * child note is not set or the child merge policy is \c 
		 * MERGE_POLICY_TAKE_OVER_SOURCE and the source child node passes the 
		 * source merge filter (if set). A valid source data entry will be 
		 * taken over by the target node if either there is no data record 
		 * attached to the target node or the data merge policy is \c 
		 * MERGE_POLICY_TAKE_OVER_SOURCE and the source child node passes the 
		 * source merge filter (if set). If \c recursive is set to true, child
		 * nodes will be merged recursively if both the target and its 
		 * corresponding source child node are set and the child node merge 
		 * policy is either not \c MERGE_POLICY_TAKE_OVER_SOURCE, or the 
		 * source child node did not pass the filter.
		 *
		 * \param sourceImpl Source node implementation.
		 * \param targetImpl Target node implementation.
		 * \param context Voxel tree context.
		 * \param childPolicy Policy for merging child nodes.
		 * \param dataPolicy Policy for merging data.
		 * \param sourceFilter source node filter.
		 * \param targetFilter target node filter.
		 * \param sourceMergeFilter source node merge filter.
		 * \param recursive merge nodes recursively.
		 * \param fill0 Create a full set of child nodes on the target node if 
		 * one is missing.
		 *
		 * \return number of nodes that have been merged.
		 */
		static unsigned int mergeImpl(Ionflux::VolGfx::NodeImpl* sourceImpl, 
		Ionflux::VolGfx::NodeImpl* targetImpl, Ionflux::VolGfx::Context* context,
		Ionflux::VolGfx::MergePolicyID childPolicy = MERGE_POLICY_KEEP_TARGET, 
		Ionflux::VolGfx::MergePolicyID dataPolicy = MERGE_POLICY_KEEP_TARGET, 
		Ionflux::VolGfx::NodeFilter* sourceFilter = 0, 
		Ionflux::VolGfx::NodeFilter* targetFilter = 0, 
		Ionflux::VolGfx::NodeFilter* sourceMergeFilter = 0, bool recursive = 
		true, bool fill0 = false);
		
		/** Get string representation of node implementation.
		 *
		 * Get a string representation of the value of the node 
		 * implementation.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param showData show data.
		 *
		 * \return String representation.
		 */
		static std::string getImplValueString(Ionflux::VolGfx::NodeImpl* 
		otherImpl, Ionflux::VolGfx::Context* context, bool showData = true);
		
		/** Print debug information.
		 *
		 * Print debug information.
		 *
		 * \param otherImpl Node implementation.
		 * \param context Voxel tree context.
		 * \param recursive List child nodes recursively.
		 * \param indentWidth Indentation width.
		 * \param indentChar Indentation character.
		 * \param depth Depth.
		 */
		static void printImplDebugInfo(Ionflux::VolGfx::NodeImpl* otherImpl, 
		Ionflux::VolGfx::Context* context, bool recursive = false, unsigned int 
		indentWidth = Ionflux::ObjectBase::DEFAULT_INDENT_WIDTH, char indentChar 
		= ' ', unsigned int depth = 0);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::VolGfx::Node& operator=(const Ionflux::VolGfx::Node& 
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::VolGfx::Node* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::VolGfx::Node* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::VolGfx::Node* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Node object.
		 *
		 * \param initContext Voxel tree context.
		 * \param initImpl Node implementation.
		 * \param parentObject Parent object.
		 */
		static Ionflux::VolGfx::Node* create(Ionflux::VolGfx::Context* 
		initContext, Ionflux::VolGfx::NodeImpl* initImpl = 0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get node implementation.
		 *
		 * \return Current value of node implementation.
		 */
		virtual Ionflux::VolGfx::NodeImpl* getImpl() const;
		
		/** Set node implementation.
		 *
		 * Set new value of node implementation.
		 *
		 * \param newImpl New value of node implementation.
		 */
		virtual void setImpl(Ionflux::VolGfx::NodeImpl* newImpl);
		
		/** Get voxel tree context.
		 *
		 * \return Current value of voxel tree context.
		 */
		virtual Ionflux::VolGfx::Context* getContext() const;
		
		/** Set voxel tree context.
		 *
		 * Set new value of voxel tree context.
		 *
		 * \param newContext New value of voxel tree context.
		 */
		virtual void setContext(Ionflux::VolGfx::Context* newContext);
};

}

}

/** \file Node.hpp
 * \brief Voxel tree node (header).
 */
#endif
