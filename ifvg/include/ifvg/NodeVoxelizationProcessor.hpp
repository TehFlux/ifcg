#ifndef IONFLUX_VOLGFX_NODEVOXELIZATIONPROCESSOR
#define IONFLUX_VOLGFX_NODEVOXELIZATIONPROCESSOR
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeVoxelizationProcessor.hpp   Node voxelization processor (header).
 * ========================================================================== */

#include "ifvg/types.hpp"
#include "ifvg/constants.hpp"
#include "ifvg/ChainableNodeProcessor.hpp"

namespace Ionflux
{

namespace VolGfx
{

class Node;

/// Class information for class NodeVoxelizationProcessor.
class NodeVoxelizationProcessorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		NodeVoxelizationProcessorClassInfo();
		/// Destructor.
		virtual ~NodeVoxelizationProcessorClassInfo();
};

/** Node voxelization processor.
 * \ingroup ifvg
 *
 * A node processor for voxelization. When used with Node::voxelizeFaces(),
 * this processor attaches a data record to the target node according to 
 * the voxelization target that is set on the processor.
 */
class NodeVoxelizationProcessor
: public Ionflux::VolGfx::ChainableNodeProcessor
{
	private:
		
	protected:
		/// Voxelization target.
		Ionflux::VolGfx::VoxelizationTargetID target;
		
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
		/// Class information instance.
		static const NodeVoxelizationProcessorClassInfo nodeVoxelizationProcessorClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new NodeVoxelizationProcessor object.
		 */
		NodeVoxelizationProcessor();
		
		/** Constructor.
		 *
		 * Construct new NodeVoxelizationProcessor object.
		 *
		 * \param other Other object.
		 */
		NodeVoxelizationProcessor(const Ionflux::VolGfx::NodeVoxelizationProcessor& other);
		
		/** Destructor.
		 *
		 * Destruct NodeVoxelizationProcessor object.
		 */
		virtual ~NodeVoxelizationProcessor();
		
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
		virtual Ionflux::VolGfx::NodeVoxelizationProcessor& operator=(const 
		Ionflux::VolGfx::NodeVoxelizationProcessor& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::VolGfx::NodeVoxelizationProcessor* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::VolGfx::NodeVoxelizationProcessor* 
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
		static Ionflux::VolGfx::NodeVoxelizationProcessor* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get voxelization target.
		 *
		 * \return Current value of voxelization target.
		 */
		virtual Ionflux::VolGfx::VoxelizationTargetID getTarget() const;
		
		/** Set voxelization target.
		 *
		 * Set new value of voxelization target.
		 *
		 * \param newTarget New value of voxelization target.
		 */
		virtual void setTarget(Ionflux::VolGfx::VoxelizationTargetID newTarget);
};

}

}

/** \file NodeVoxelizationProcessor.hpp
 * \brief Node voxelization processor (header).
 */
#endif
