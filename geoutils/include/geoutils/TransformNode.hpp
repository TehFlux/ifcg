#ifndef IONFLUX_GEOUTILS_TRANSFORMNODE
#define IONFLUX_GEOUTILS_TRANSFORMNODE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TransformNode.hpp               Transform node (header).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * GeoUtils - Ionflux' Geometry Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with GeoUtils - Ionflux' Geometry Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "ifobject/types.hpp"
#include "ifmapping/types.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/TransformableGroup.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

/// Class information for class TransformNode.
class TransformNodeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		TransformNodeClassInfo();
		/// Destructor.
		virtual ~TransformNodeClassInfo();
};

/** Transform node.
 * \ingroup geoutils
 *
 * Abstract base class for a node that applies some transformation to a set
 * of input transformable groups and provides a set of output transformable
 * groups. The transformation is initiated by calling the update() method 
 * (or the call operator) on the node. The node then queries all of its 
 * inputs for data and updates the outputs. The outputs can then be queried
 * using the getOutput() method.
 */
class TransformNode
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Loop counter.
		unsigned int loopCounter;
		/// Visited flag.
		bool visited;
		/// Debug mode flag.
		bool debugMode;
		/// Debug expand flag.
		bool debugExpand;
		/// Input group cache.
		Ionflux::GeoUtils::TransformableGroupVector inputCache;
		/// Vector of input node specifications.
		std::vector<Ionflux::GeoUtils::TransformNodes::InputNodeSpec> inputs;
		/// Vector of output groups.
		std::vector<Ionflux::GeoUtils::TransformableGroup*> outputs;
		/// Maximum loop count.
		unsigned int loopMax;
		/// Maximum number of inputs.
		unsigned int maxNumInputs;
		/// Update counter.
		unsigned int updateCounter;
		
		/** Process inputs.
		 *
		 * Update the outputs of the node by processing the inputs. This 
		 * should be implemented by derived classes.
		 */
		virtual void process();
		
	public:
		/// Default maximum loop count.
		static const unsigned int DEFAULT_LOOP_MAX;
		/// Class information instance.
		static const TransformNodeClassInfo transformNodeClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new TransformNode object.
		 */
		TransformNode();
		
		/** Constructor.
		 *
		 * Construct new TransformNode object.
		 *
		 * \param other Other object.
		 */
		TransformNode(const Ionflux::GeoUtils::TransformNodes::TransformNode& other);
		
		/** Constructor.
		 *
		 * Construct new TransformNode object.
		 *
		 * \param nodeID Node ID.
		 */
		TransformNode(const Ionflux::ObjectBase::IFObjectID& nodeID);
		
		/** Destructor.
		 *
		 * Destruct TransformNode object.
		 */
		virtual ~TransformNode();
		
		/** Add inputs.
		 *
		 * Add input nodes.
		 *
		 * \param newInputs Input node specifications.
		 */
		virtual void addInputs(const Ionflux::GeoUtils::InputNodeSpecVector& 
		newInputs);
		
		/** Get linked inputs.
		 *
		 * Get all input nodes that, via some path starting from this node, 
		 * are linked to the inputs of this node.
		 *
		 * \param target Target vector.
		 */
		virtual void getLinkedInputs(Ionflux::GeoUtils::TransformNodeVector& 
		target);
		
		/** Set input.
		 *
		 * Set the input with the specified ID.
		 *
		 * \param newInput Input node specification.
		 * \param inputID Input ID.
		 */
		virtual void setInput(const 
		Ionflux::GeoUtils::TransformNodes::InputNodeSpec& newInput, unsigned int 
		inputID = INPUT_NEXT_FREE);
		
		/** Clear input group cache.
		 *
		 * Clear the input group cache.
		 */
		virtual void clearInputCache();
		
		/** Update inputs.
		 *
		 * Update the inputs of the node. Each input node is updated only 
		 * once, no matter how many of its outputs are connected to this node.
		 */
		virtual void updateInputs();
		
		/** Clear input Groups.
		 *
		 * Clear the input groups, that is the output groups of the input 
		 * nodes.
		 */
		virtual void clearInputGroups();
		
		/** Clean up.
		 *
		 * Clean up resources created by the node during an update operation.
		 */
		virtual void cleanup();
		
		/** Update.
		 *
		 * Update the outputs of the node. This updates all inputs and checks 
		 * the loop counter to make sure the maximum number of loop iterations
		 * is not exceeded. It clears the output groups and calls process() to
		 * do the actual processing of the inputs. Note that a transform node 
		 * does not have outputs unless update() has been called and finished 
		 * processing at least once. Outputs are considered a cache rather 
		 * than state of the object (they are also not copied when using an 
		 * assignment or copy constructor). See the spec for details.
		 */
		virtual void update();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Get debugging information.
		 *
		 * Get a representation of the node and its contents that is usable 
		 * for debugging.
		 *
		 * \param expand Display information about non-group items.
		 *
		 * \return Debugging information.
		 */
		virtual std::string getDebugInfo(bool expand = true);
		
		/** Enable debug mode.
		 *
		 * Enable (or disable) the debug mode, which provides useful 
		 * information for debugging on an update() call.
		 *
		 * \param newDebugMode Debug mode flag.
		 * \param expand Show information about non-group items..
		 */
		virtual void enableDebugMode(bool newDebugMode = true, bool expand = 
		false);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::TransformNode& operator=(const
		Ionflux::GeoUtils::TransformNodes::TransformNode& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::TransformNode* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::TransformNode* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Set parameter.
		 *
		 * Set the parameter with the specified ID.
		 *
		 * \param paramID Parameter ID.
		 * \param paramValue Parameter value.
		 */
		virtual void setParam(Ionflux::ObjectBase::IFParamID paramID, 
		Ionflux::Mapping::MappingValue paramValue);
		
		/** Get parameter.
		 *
		 * Get the parameter with the specified ID.
		 *
		 * \param paramID Parameter ID.
		 */
		virtual Ionflux::Mapping::MappingValue 
		getParam(Ionflux::ObjectBase::IFParamID paramID);
		
		/** Get number of inputs.
		 *
		 * \return Number of inputs.
		 */
		virtual unsigned int getNumInputs() const;
		
		/** Get input.
		 *
		 * Get the input at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Input at specified index.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::InputNodeSpec 
		getInput(unsigned int elementIndex = 0) const;
		
		/** Find input.
		 *
		 * Find the specified occurence of a input.
		 *
		 * \param needle Input to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the input, or -1 if the input cannot be found.
		 */
		virtual int findInput(Ionflux::GeoUtils::TransformNodes::InputNodeSpec 
		needle, unsigned int occurence = 1) const;
        
		/** Get vector of input node specifications.
		 *
		 * \return vector of input node specifications.
		 */
		virtual std::vector<Ionflux::GeoUtils::TransformNodes::InputNodeSpec>& 
		getInputs();
		
		/** Add input.
		 *
		 * Add a input.
		 *
		 * \param addElement Input to be added.
		 */
		virtual void addInput(const 
		Ionflux::GeoUtils::TransformNodes::InputNodeSpec& addElement);
		
		/** Remove input.
		 *
		 * Remove a input.
		 *
		 * \param removeElement Input to be removed.
		 */
		virtual void removeInput(const 
		Ionflux::GeoUtils::TransformNodes::InputNodeSpec& removeElement);
		
		/** Remove input.
		 *
		 * Remove a input.
		 *
		 * \param removeIndex Input to be removed.
		 */
		virtual void removeInputIndex(unsigned int removeIndex);
		
		/** Clear inputs.
		 *
		 * Clear all inputs.
		 */
		virtual void clearInputs();
		
		/** Get number of outputs.
		 *
		 * \return Number of outputs.
		 */
		virtual unsigned int getNumOutputs() const;
		
		/** Get output.
		 *
		 * Get the output at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Output at specified index.
		 */
		virtual Ionflux::GeoUtils::TransformableGroup* getOutput(unsigned int 
		elementIndex = 0) const;
		
		/** Find output.
		 *
		 * Find the specified occurence of a output.
		 *
		 * \param needle Output to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the output, or -1 if the output cannot be found.
		 */
		virtual int findOutput(Ionflux::GeoUtils::TransformableGroup* needle, 
		unsigned int occurence = 1) const;
        
		/** Get vector of output groups.
		 *
		 * \return vector of output groups.
		 */
		virtual std::vector<Ionflux::GeoUtils::TransformableGroup*>& 
		getOutputs();
		
		/** Add output.
		 *
		 * Add a output.
		 *
		 * \param addElement Output to be added.
		 */
		virtual void addOutput(Ionflux::GeoUtils::TransformableGroup* 
		addElement);
		
		/** Remove output.
		 *
		 * Remove a output.
		 *
		 * \param removeElement Output to be removed.
		 */
		virtual void removeOutput(Ionflux::GeoUtils::TransformableGroup* 
		removeElement);
		
		/** Remove output.
		 *
		 * Remove a output.
		 *
		 * \param removeIndex Output to be removed.
		 */
		virtual void removeOutputIndex(unsigned int removeIndex);
		
		/** Clear outputs.
		 *
		 * Clear all outputs.
		 */
		virtual void clearOutputs();
		
		/** Get maximum loop count.
		 *
		 * \return Current value of maximum loop count.
		 */
		virtual unsigned int getLoopMax() const;
		
		/** Set maximum loop count.
		 *
		 * Set new value of maximum loop count.
		 *
		 * \param newLoopMax New value of maximum loop count.
		 */
		virtual void setLoopMax(unsigned int newLoopMax);
		
		/** Get maximum number of inputs.
		 *
		 * \return Current value of maximum number of inputs.
		 */
		virtual unsigned int getMaxNumInputs() const;
		
		/** Set maximum number of inputs.
		 *
		 * Set new value of maximum number of inputs.
		 *
		 * \param newMaxNumInputs New value of maximum number of inputs.
		 */
		virtual void setMaxNumInputs(unsigned int newMaxNumInputs);
		
		/** Get update counter.
		 *
		 * \return Current value of update counter.
		 */
		virtual unsigned int getUpdateCounter() const;
		
		/** Set update counter.
		 *
		 * Set new value of update counter.
		 *
		 * \param newUpdateCounter New value of update counter.
		 */
		virtual void setUpdateCounter(unsigned int newUpdateCounter);
};

}

}

}

/** \file TransformNode.hpp
 * \brief Transform node (header).
 */
#endif
