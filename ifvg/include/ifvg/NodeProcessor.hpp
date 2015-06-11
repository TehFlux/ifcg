#ifndef IONFLUX_VOLGFX_NODEPROCESSOR
#define IONFLUX_VOLGFX_NODEPROCESSOR
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeProcessor.hpp               Node processor (header).
 * ========================================================================== */

#include "ifvg/types.hpp"
#include "ifvg/constants.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace VolGfx
{

class Node;

/// Class information for class NodeProcessor.
class NodeProcessorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		NodeProcessorClassInfo();
		/// Destructor.
		virtual ~NodeProcessorClassInfo();
};

/** Node processor.
 * \ingroup ifvg
 *
 * A base class for objects that process nodes or node implementations. Any
 * node processor can be used with Node::process() or Node::processImpl().
 */
class NodeProcessor
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		
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
		/// Node processing result: unknown.
		static const Ionflux::VolGfx::NodeProcessingResultID RESULT_UNKNOWN;
		/// Node processing result: ok.
		static const Ionflux::VolGfx::NodeProcessingResultID RESULT_OK;
		/// Node processing result: failed.
		static const Ionflux::VolGfx::NodeProcessingResultID RESULT_FAILED;
		/// Class information instance.
		static const NodeProcessorClassInfo nodeProcessorClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new NodeProcessor object.
		 */
		NodeProcessor();
		
		/** Constructor.
		 *
		 * Construct new NodeProcessor object.
		 *
		 * \param other Other object.
		 */
		NodeProcessor(const Ionflux::VolGfx::NodeProcessor& other);
		
		/** Destructor.
		 *
		 * Destruct NodeProcessor object.
		 */
		virtual ~NodeProcessor();
		
		/** Process node implementation.
		 *
		 * Process a node implementation.
		 *
		 * \param nodeImpl Node implementation.
		 * \param userData User data.
		 *
		 * \return result.
		 */
		virtual Ionflux::VolGfx::NodeProcessingResultID 
		process(Ionflux::VolGfx::NodeImpl* nodeImpl, void* userData = 0);
		
		/** Process node.
		 *
		 * Process a node.
		 *
		 * \param node Node.
		 * \param userData User data.
		 *
		 * \return result.
		 */
		virtual Ionflux::VolGfx::NodeProcessingResultID 
		process(Ionflux::VolGfx::Node* node, void* userData = 0);
		
		/** Process node implementation.
		 *
		 * Process a node implementation.
		 *
		 * \param nodeImpl Node implementation.
		 * \param userData User data.
		 *
		 * \return result.
		 */
		virtual Ionflux::VolGfx::NodeProcessingResultID 
		operator()(Ionflux::VolGfx::NodeImpl* nodeImpl, void* userData = 0);
		
		/** Process node.
		 *
		 * Process a node.
		 *
		 * \param node Node.
		 * \param userData User data.
		 *
		 * \return result.
		 */
		virtual Ionflux::VolGfx::NodeProcessingResultID 
		operator()(Ionflux::VolGfx::Node* node, void* userData = 0);
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Check processing result flags.
		 *
		 * Check if the specified processing result flags are set within the 
		 * specified node processing result.
		 *
		 * \param result node processing result.
		 * \param flags node processing result flags.
		 *
		 * \return \c true if the specified node processing result flags are set 
		 * within the node processing result.
		 */
		static bool checkFlags(Ionflux::VolGfx::NodeProcessingResultID result, 
		Ionflux::VolGfx::NodeProcessingResultID flags);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::VolGfx::NodeProcessor& operator=(const 
		Ionflux::VolGfx::NodeProcessor& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::VolGfx::NodeProcessor* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::VolGfx::NodeProcessor* 
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
		static Ionflux::VolGfx::NodeProcessor* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
};

}

}

/** \file NodeProcessor.hpp
 * \brief Node processor (header).
 */
#endif
