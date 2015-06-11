#ifndef IONFLUX_VOLGFX_CHAINABLENODEPROCESSOR
#define IONFLUX_VOLGFX_CHAINABLENODEPROCESSOR
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ChainableNodeProcessor.hpp      Chainable node processor (header).
 * ========================================================================== */

#include "ifvg/types.hpp"
#include "ifvg/constants.hpp"
#include "ifvg/NodeProcessor.hpp"

namespace Ionflux
{

namespace VolGfx
{

class Node;

/// Class information for class ChainableNodeProcessor.
class ChainableNodeProcessorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ChainableNodeProcessorClassInfo();
		/// Destructor.
		virtual ~ChainableNodeProcessorClassInfo();
};

/** Chainable node processor.
 * \ingroup ifvg
 *
 * A chainable node processor. When a node is passed to this node 
 * processor, the processor first invokes its source node processor. If the
 * processing result of the source processor does not have the \c 
 * RESULT_FINISHED flag set, the processor then proceeds with its own node 
 * processing implementation.
 */
class ChainableNodeProcessor
: public Ionflux::VolGfx::NodeProcessor
{
	private:
		
	protected:
		/// Source node processor.
		Ionflux::VolGfx::NodeProcessor* source;
		
	public:
		/// Node processing result: finished.
		static const Ionflux::VolGfx::NodeProcessingResultID RESULT_FINISHED;
		/// Class information instance.
		static const ChainableNodeProcessorClassInfo chainableNodeProcessorClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ChainableNodeProcessor object.
		 */
		ChainableNodeProcessor();
		
		/** Constructor.
		 *
		 * Construct new ChainableNodeProcessor object.
		 *
		 * \param other Other object.
		 */
		ChainableNodeProcessor(const Ionflux::VolGfx::ChainableNodeProcessor& other);
		
		/** Destructor.
		 *
		 * Destruct ChainableNodeProcessor object.
		 */
		virtual ~ChainableNodeProcessor();
		
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
		virtual Ionflux::VolGfx::ChainableNodeProcessor& operator=(const 
		Ionflux::VolGfx::ChainableNodeProcessor& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::VolGfx::ChainableNodeProcessor* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::VolGfx::ChainableNodeProcessor* 
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
		static Ionflux::VolGfx::ChainableNodeProcessor* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get source node processor.
		 *
		 * \return Current value of source node processor.
		 */
		virtual Ionflux::VolGfx::NodeProcessor* getSource() const;
		
		/** Set source node processor.
		 *
		 * Set new value of source node processor.
		 *
		 * \param newSource New value of source node processor.
		 */
		virtual void setSource(Ionflux::VolGfx::NodeProcessor* newSource);
};

}

}

/** \file ChainableNodeProcessor.hpp
 * \brief Chainable node processor (header).
 */
#endif
