#ifndef IONFLUX_VOLGFX_NODEFILTER
#define IONFLUX_VOLGFX_NODEFILTER
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeFilter.hpp                  Node filter (header).
 * ========================================================================== */

#include "ifvg/types.hpp"
#include "ifvg/constants.hpp"
#include "ifvg/Node.hpp"
#include "ifvg/ChainableNodeProcessor.hpp"

namespace Ionflux
{

namespace VolGfx
{

class Context;

/// Class information for class NodeFilter.
class NodeFilterClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		NodeFilterClassInfo();
		/// Destructor.
		virtual ~NodeFilterClassInfo();
};

/** Node filter.
 * \ingroup ifvg
 *
 * A node processor that can be used to filter nodes based on various 
 * criteria, such as depth range, data type, voxel class and leaf flag. 
 * Node filters can be used with functions such as Node::process(), 
 * Node::find(), Node::getMesh(), Node::getVertexAttributes() and 
 * Node::intersectRay() to restrict the operation to a certain subset of 
 * nodes. The filter will return \c RESULT_OK | \c RESULT_PASS if the node 
 * passes the filter and \c RESULT_OK if the node does not pass the filter.
 * Also, the filter() member function can be used to obtain a boolean 
 * result of applying the filter to a node.
 */
class NodeFilter
: public Ionflux::VolGfx::ChainableNodeProcessor
{
	private:
		
	protected:
		/// context.
		Ionflux::VolGfx::Context* context;
		/// minimum depth.
		int minDepth;
		/// maximum depth.
		int maxDepth;
		/// leaf status.
		Ionflux::VolGfx::LeafStatusID leafStatus;
		/// node data type.
		Ionflux::VolGfx::NodeDataType dataType;
		/// voxel class mask.
		Ionflux::VolGfx::VoxelClassID voxelClass;
		/// region.
		Ionflux::GeoUtils::Range3* region;
		
		/** Process node implementation.
		 *
		 * Process a node implementation. This function should be implemented 
		 * by derived classes.
		 *
		 * \param nodeImpl Node implementation.
		 * \param userData User data.
		 *
		 * \return result.
		 */
		virtual Ionflux::VolGfx::NodeProcessingResultID 
		processImpl(Ionflux::VolGfx::NodeImpl* nodeImpl, void* userData = 0);
		
	public:
		/// Node processing result: pass.
		static const Ionflux::VolGfx::NodeProcessingResultID RESULT_PASS;
		/// Class information instance.
		static const NodeFilterClassInfo nodeFilterClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new NodeFilter object.
		 */
		NodeFilter();
		
		/** Constructor.
		 *
		 * Construct new NodeFilter object.
		 *
		 * \param other Other object.
		 */
		NodeFilter(const Ionflux::VolGfx::NodeFilter& other);
		
		/** Constructor.
		 *
		 * Construct new NodeFilter object.
		 *
		 * \param initContext context.
		 * \param initMinDepth minimum depth.
		 * \param initMaxDepth maximum depth.
		 * \param initLeafStatus leaf status.
		 * \param initDataType node data type.
		 * \param initVoxelClass voxel class.
		 * \param initRegion region.
		 */
		NodeFilter(Ionflux::VolGfx::Context* initContext, int initMinDepth = 
		DEPTH_UNSPECIFIED, int initMaxDepth = DEPTH_UNSPECIFIED, 
		Ionflux::VolGfx::LeafStatusID initLeafStatus = NODE_ANY, 
		Ionflux::VolGfx::NodeDataType initDataType = Node::DATA_TYPE_UNKNOWN, 
		Ionflux::VolGfx::VoxelClassID initVoxelClass = VOXEL_CLASS_UNDEFINED, 
		Ionflux::GeoUtils::Range3* initRegion = 0);
		
		/** Destructor.
		 *
		 * Destruct NodeFilter object.
		 */
		virtual ~NodeFilter();
		
		/** Filter node.
		 *
		 * Apply the filter to a node implementation. This should be 
		 * overridden by derived classes.
		 *
		 * \param nodeImpl Node implementation.
		 * \param userData User data.
		 *
		 * \return result.
		 */
		virtual bool filter(Ionflux::VolGfx::NodeImpl* nodeImpl, void* userData =
		0);
		
		/** Filter node.
		 *
		 * Apply the filter to a node.
		 *
		 * \param node Node.
		 * \param userData User data.
		 *
		 * \return result.
		 */
		virtual bool filter(Ionflux::VolGfx::Node* node, void* userData = 0);
		
		/** Set depth range.
		 *
		 * Set the allowable depth range for the filter.
		 *
		 * \param newMinDepth minimum depth.
		 * \param newMaxDepth maximum depth.
		 */
		virtual void setDepthRange(int newMinDepth = DEPTH_UNSPECIFIED, int 
		newMaxDepth = DEPTH_UNSPECIFIED);
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::VolGfx::NodeFilter& operator=(const 
		Ionflux::VolGfx::NodeFilter& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::VolGfx::NodeFilter* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::VolGfx::NodeFilter* upcast(Ionflux::ObjectBase::IFObject*
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
		static Ionflux::VolGfx::NodeFilter* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new NodeFilter object.
		 *
		 * \param initContext context.
		 * \param initMinDepth minimum depth.
		 * \param initMaxDepth maximum depth.
		 * \param initLeafStatus leaf status.
		 * \param initDataType node data type.
		 * \param initVoxelClass voxel class.
		 * \param initRegion region.
		 * \param parentObject Parent object.
		 */
		static Ionflux::VolGfx::NodeFilter* create(Ionflux::VolGfx::Context* 
		initContext, int initMinDepth = DEPTH_UNSPECIFIED, int initMaxDepth = 
		DEPTH_UNSPECIFIED, Ionflux::VolGfx::LeafStatusID initLeafStatus = 
		NODE_ANY, Ionflux::VolGfx::NodeDataType initDataType = 
		Node::DATA_TYPE_UNKNOWN, Ionflux::VolGfx::VoxelClassID initVoxelClass = 
		VOXEL_CLASS_UNDEFINED, Ionflux::GeoUtils::Range3* initRegion = 0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get context.
		 *
		 * \return Current value of context.
		 */
		virtual Ionflux::VolGfx::Context* getContext() const;
		
		/** Set context.
		 *
		 * Set new value of context.
		 *
		 * \param newContext New value of context.
		 */
		virtual void setContext(Ionflux::VolGfx::Context* newContext);
		
		/** Get minimum depth.
		 *
		 * \return Current value of minimum depth.
		 */
		virtual int getMinDepth() const;
		
		/** Set minimum depth.
		 *
		 * Set new value of minimum depth.
		 *
		 * \param newMinDepth New value of minimum depth.
		 */
		virtual void setMinDepth(int newMinDepth);
		
		/** Get maximum depth.
		 *
		 * \return Current value of maximum depth.
		 */
		virtual int getMaxDepth() const;
		
		/** Set maximum depth.
		 *
		 * Set new value of maximum depth.
		 *
		 * \param newMaxDepth New value of maximum depth.
		 */
		virtual void setMaxDepth(int newMaxDepth);
		
		/** Get leaf status.
		 *
		 * \return Current value of leaf status.
		 */
		virtual Ionflux::VolGfx::LeafStatusID getLeafStatus() const;
		
		/** Set leaf status.
		 *
		 * Set new value of leaf status.
		 *
		 * \param newLeafStatus New value of leaf status.
		 */
		virtual void setLeafStatus(Ionflux::VolGfx::LeafStatusID newLeafStatus);
		
		/** Get node data type.
		 *
		 * \return Current value of node data type.
		 */
		virtual Ionflux::VolGfx::NodeDataType getDataType() const;
		
		/** Set node data type.
		 *
		 * Set new value of node data type.
		 *
		 * \param newDataType New value of node data type.
		 */
		virtual void setDataType(Ionflux::VolGfx::NodeDataType newDataType);
		
		/** Get voxel class mask.
		 *
		 * \return Current value of voxel class mask.
		 */
		virtual Ionflux::VolGfx::VoxelClassID getVoxelClass() const;
		
		/** Set voxel class mask.
		 *
		 * Set new value of voxel class mask.
		 *
		 * \param newVoxelClass New value of voxel class mask.
		 */
		virtual void setVoxelClass(Ionflux::VolGfx::VoxelClassID newVoxelClass);
		
		/** Get region.
		 *
		 * \return Current value of region.
		 */
		virtual Ionflux::GeoUtils::Range3* getRegion() const;
		
		/** Set region.
		 *
		 * Set new value of region.
		 *
		 * \param newRegion New value of region.
		 */
		virtual void setRegion(Ionflux::GeoUtils::Range3* newRegion);
};

}

}

/** \file NodeFilter.hpp
 * \brief Node filter (header).
 */
#endif
