#ifndef IONFLUX_VOLGFX_NODEFILLPROCESSOR
#define IONFLUX_VOLGFX_NODEFILLPROCESSOR
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeFillProcessor.hpp           Node fill processor (header).
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

/// Class information for class NodeFillProcessor.
class NodeFillProcessorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		NodeFillProcessorClassInfo();
		/// Destructor.
		virtual ~NodeFillProcessorClassInfo();
};

/** Node intersection processor.
 * \ingroup ifvg
 *
 * A node processor that can be used to fill nodes, i.e. add child nodes 
 * that are not set on a node, so that the node has a full set of child 
 * nodes.
 */
class NodeFillProcessor
: public Ionflux::VolGfx::ChainableNodeProcessor
{
	private:
		
	protected:
		/// Voxel tree context.
		Ionflux::VolGfx::Context* context;
		/// Clear existing child nodes.
		bool clearExisting;
		/// Fill nodes recursively.
		bool recursive;
		/// Maximum depth.
		int maxDepth;
		
		/** Process node implementation.
		 *
		 * Process a node implementation. \c userData is expected to contain a
		 * pointer to a NodeIntersection data record for \c nodeImpl.
		 *
		 * \param nodeImpl Node implementation.
		 * \param userData User data.
		 *
		 * \return result.
		 */
		virtual Ionflux::VolGfx::NodeProcessingResultID 
		processImpl(Ionflux::VolGfx::NodeImpl* nodeImpl, void* userData = 0);
		
	public:
		/// Class information instance.
		static const NodeFillProcessorClassInfo nodeFillProcessorClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new NodeFillProcessor object.
		 */
		NodeFillProcessor();
		
		/** Constructor.
		 *
		 * Construct new NodeFillProcessor object.
		 *
		 * \param other Other object.
		 */
		NodeFillProcessor(const Ionflux::VolGfx::NodeFillProcessor& other);
		
		/** Constructor.
		 *
		 * Construct new NodeFillProcessor object.
		 *
		 * \param initContext Voxel tree context.
		 * \param initClearExisting Clear existing child nodes.
		 * \param initRecursive Fill nodes recursively.
		 * \param initMaxDepth Maximum depth.
		 */
		NodeFillProcessor(Ionflux::VolGfx::Context* initContext, bool 
		initClearExisting = false, bool initRecursive = false, int initMaxDepth =
		DEPTH_UNSPECIFIED);
		
		/** Destructor.
		 *
		 * Destruct NodeFillProcessor object.
		 */
		virtual ~NodeFillProcessor();
		
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
		virtual Ionflux::VolGfx::NodeFillProcessor& operator=(const 
		Ionflux::VolGfx::NodeFillProcessor& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::VolGfx::NodeFillProcessor* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::VolGfx::NodeFillProcessor* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
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
		static Ionflux::VolGfx::NodeFillProcessor* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new NodeFillProcessor object.
		 *
		 * \param initContext Voxel tree context.
		 * \param initClearExisting Clear existing child nodes.
		 * \param initRecursive Fill nodes recursively.
		 * \param initMaxDepth Maximum depth.
		 * \param parentObject Parent object.
		 */
		static Ionflux::VolGfx::NodeFillProcessor* 
		create(Ionflux::VolGfx::Context* initContext, bool initClearExisting = 
		false, bool initRecursive = false, int initMaxDepth = DEPTH_UNSPECIFIED, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
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
		
		/** Get clear existing child nodes.
		 *
		 * \return Current value of clear existing child nodes.
		 */
		virtual bool getClearExisting() const;
		
		/** Set clear existing child nodes.
		 *
		 * Set new value of clear existing child nodes.
		 *
		 * \param newClearExisting New value of clear existing child nodes.
		 */
		virtual void setClearExisting(bool newClearExisting);
		
		/** Get fill nodes recursively.
		 *
		 * \return Current value of fill nodes recursively.
		 */
		virtual bool getRecursive() const;
		
		/** Set fill nodes recursively.
		 *
		 * Set new value of fill nodes recursively.
		 *
		 * \param newRecursive New value of fill nodes recursively.
		 */
		virtual void setRecursive(bool newRecursive);
		
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
};

}

}

/** \file NodeFillProcessor.hpp
 * \brief Node fill processor (header).
 */
#endif
