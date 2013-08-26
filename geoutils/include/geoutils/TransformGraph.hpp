#ifndef IONFLUX_GEOUTILS_TRANSFORMGRAPH
#define IONFLUX_GEOUTILS_TRANSFORMGRAPH
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TransformGraph.hpp              Transform graph (header).
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

#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/TransformableGroup.hpp"
#include "geoutils/TransformNode.hpp"
#include "geoutils/Connection.hpp"
#include "geoutils/TransformNode.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

/// Class information for class TransformGraph.
class TransformGraphClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		TransformGraphClassInfo();
		/// Destructor.
		virtual ~TransformGraphClassInfo();
};

/** Transform graph.
 * \ingroup geoutils
 *
 * A transform graph is a network of transform nodes that is itself a 
 * transform node. The graph identifies a source node to which inputs can 
 * be added and a drain node which can be queried for output groups. The 
 * graph also provides a simple interface to manage connections between 
 * nodes that are part of the graph.
 */
class TransformGraph
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
	private:
		
	protected:
		/// Vector of input node specifications.
		std::vector<Ionflux::GeoUtils::TransformNodes::InputNodeSpec> inputs;
		/// Vector of output groups.
		std::vector<Ionflux::GeoUtils::TransformableGroup*> outputs;
		/// Vector of connections.
		std::vector<Ionflux::GeoUtils::TransformNodes::Connection*> connections;
		/// Vector of nodes.
		std::vector<Ionflux::GeoUtils::TransformNodes::TransformNode*> nodes;
		/// Source node.
		Ionflux::GeoUtils::TransformNodes::TransformNode* source;
		/// Drain node.
		Ionflux::GeoUtils::TransformNodes::TransformNode* drain;
		
		/** Process inputs.
		 *
		 * Update the outputs of the node by processing the inputs.
		 */
		virtual void process();
		
	public:
		/// Index of the last node.
		static const unsigned int NODE_INDEX_LAST;
		/// Class information instance.
		static const TransformGraphClassInfo transformGraphClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new TransformGraph object.
		 */
		TransformGraph();
		
		/** Constructor.
		 *
		 * Construct new TransformGraph object.
		 *
		 * \param other Other object.
		 */
		TransformGraph(const Ionflux::GeoUtils::TransformNodes::TransformGraph& other);
		
		/** Destructor.
		 *
		 * Destruct TransformGraph object.
		 */
		virtual ~TransformGraph();
		
		/** Add linked nodes.
		 *
		 * Add the specified node and all nodes that are linked, via some path
		 * starting at the node, to its inputs. Nodes will not be added if 
		 * they already exist within the graph.
		 *
		 * \param newNode Node.
		 */
		virtual void addLinked(Ionflux::GeoUtils::TransformNodes::TransformNode* 
		newNode);
		
		/** Clear graph.
		 *
		 * Clear the transform graph. This removes all nodes and connections.
		 */
		virtual void clear();
		
		/** Add nodes.
		 *
		 * Add nodes.
		 *
		 * \param newNodes Nodes.
		 */
		virtual void addNodes(Ionflux::GeoUtils::TransformNodeVector& newNodes);
		
		/** Find connection.
		 *
		 * Find a connection within the graph.
		 *
		 * \param source Source node.
		 * \param target Target node.
		 * \param outputID Output ID.
		 * \param inputID Input ID.
		 * \param connectLater Connect later.
		 *
		 * \return Connection, or \c 0 if the connection does not exist.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Connection* 
		findConnection(Ionflux::GeoUtils::TransformNodes::TransformNode* source =
		0, Ionflux::GeoUtils::TransformNodes::TransformNode* target = 0, unsigned
		int outputID = 0, unsigned int inputID = 0, bool connectLater = false);
		
		/** Connect.
		 *
		 * Establish a connection from the specified output slot of the source
		 * node to the specified input slot of the target node. If \c 
		 * connectLater is \c true, the internal state will be set up but the 
		 * connection will not be established immediately.
		 *
		 * \param source Source node.
		 * \param target Target node.
		 * \param outputID Output ID.
		 * \param inputID Input ID.
		 * \param connectLater Connect later.
		 *
		 * \return \c true if a connection has been established, \c false 
		 * otherwise.
		 */
		virtual bool connect(Ionflux::GeoUtils::TransformNodes::TransformNode* 
		source = 0, Ionflux::GeoUtils::TransformNodes::TransformNode* target = 0,
		unsigned int outputID = 0, unsigned int inputID = INPUT_NEXT_FREE, bool 
		connectLater = false);
		
		/** Disconnect.
		 *
		 * Disconnect a connection between nodes.
		 *
		 * \param source Source node.
		 * \param target Target node.
		 * \param outputID Output ID.
		 * \param inputID Input ID.
		 *
		 * \return \c true if the connection has been discarded, \c false 
		 * otherwise.
		 */
		virtual bool disconnect(Ionflux::GeoUtils::TransformNodes::TransformNode*
		source, Ionflux::GeoUtils::TransformNodes::TransformNode* target, 
		unsigned int outputID = 0, unsigned int inputID = 0);
		
		/** Chain nodes.
		 *
		 * Establish connections between the specified nodes using default 
		 * parameters. This can be used to conveniently establish a chain of 
		 * nodes within the graph. If the index of the last node is \c 
		 * NODE_INDEX_LAST, the maximum possible index will be used as the 
		 * index of the last node.
		 *
		 * \param first Index of first node.
		 * \param last Index of last node.
		 */
		virtual void chain(unsigned int first = 0, unsigned int last = 
		NODE_INDEX_LAST);
		
		/** Connect a range of outputs.
		 *
		 * Connect the specified number of output slots of the source node 
		 * starting from the specified first output slot to the range of input
		 * slots of the target node starting at the specified first input 
		 * slot.
		 *
		 * \param source Source node.
		 * \param target Target node.
		 * \param numOutputSlots Number of output slots to connect.
		 * \param firstOutputID ID of first output to connect.
		 * \param firstInputID ID of first input to connect.
		 */
		virtual void 
		connectRange(Ionflux::GeoUtils::TransformNodes::TransformNode* source, 
		Ionflux::GeoUtils::TransformNodes::TransformNode* target, unsigned int 
		numOutputSlots, unsigned int firstOutputID = 0, unsigned int firstInputID
		= INPUT_NEXT_FREE);
		
		/** Connect one output to a range of inputs.
		 *
		 * Connect the specified output slot of the source node to the range 
		 * of input slots of the target node starting at the specified first 
		 * input slot.
		 *
		 * \param source Source node.
		 * \param target Target node.
		 * \param numInputSlots Number of input slots to connect.
		 * \param outputID ID of output to connect.
		 * \param firstInputID ID of first input to connect.
		 */
		virtual void connectFan(Ionflux::GeoUtils::TransformNodes::TransformNode*
		source, Ionflux::GeoUtils::TransformNodes::TransformNode* target, 
		unsigned int numInputSlots, unsigned int outputID = 0, unsigned int 
		firstInputID = INPUT_NEXT_FREE);
		
		/** Set input/output nodes.
		 *
		 * Set the source and drain nodes to the nodes with the specified 
		 * indices.
		 *
		 * \param sourceIndex Index of source node.
		 * \param drainIndex Index of drain node.
		 */
		virtual void setIO(unsigned int sourceIndex = 0, unsigned int drainIndex 
		= NODE_INDEX_LAST);
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
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
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::TransformGraph& 
		operator=(const Ionflux::GeoUtils::TransformNodes::TransformGraph& 
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::TransformGraph* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::TransformGraph* 
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
		static Ionflux::GeoUtils::TransformNodes::TransformGraph* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
		
		/** Get number of connections.
		 *
		 * \return Number of connections.
		 */
		virtual unsigned int getNumConnections() const;
		
		/** Get connection.
		 *
		 * Get the connection at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Connection at specified index.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Connection* 
		getConnection(unsigned int elementIndex = 0) const;
		
		/** Find connection.
		 *
		 * Find the specified occurence of a connection.
		 *
		 * \param needle Connection to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the connection, or -1 if the connection cannot be 
		 * found.
		 */
		virtual int findConnection(Ionflux::GeoUtils::TransformNodes::Connection*
		needle, unsigned int occurence = 1) const;
        
		/** Get vector of connections.
		 *
		 * \return vector of connections.
		 */
		virtual std::vector<Ionflux::GeoUtils::TransformNodes::Connection*>& 
		getConnections();
		
		/** Add connection.
		 *
		 * Add a connection.
		 *
		 * \param addElement Connection to be added.
		 */
		virtual void addConnection(Ionflux::GeoUtils::TransformNodes::Connection*
		addElement);
		
		/** Remove connection.
		 *
		 * Remove a connection.
		 *
		 * \param removeElement Connection to be removed.
		 */
		virtual void 
		removeConnection(Ionflux::GeoUtils::TransformNodes::Connection* 
		removeElement);
		
		/** Remove connection.
		 *
		 * Remove a connection.
		 *
		 * \param removeIndex Connection to be removed.
		 */
		virtual void removeConnectionIndex(unsigned int removeIndex);
		
		/** Clear connections.
		 *
		 * Clear all connections.
		 */
		virtual void clearConnections();
		
		/** Get number of nodes.
		 *
		 * \return Number of nodes.
		 */
		virtual unsigned int getNumNodes() const;
		
		/** Get node.
		 *
		 * Get the node at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Node at specified index.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::TransformNode* 
		getNode(unsigned int elementIndex = 0) const;
		
		/** Find node.
		 *
		 * Find the specified occurence of a node.
		 *
		 * \param needle Node to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the node, or -1 if the node cannot be found.
		 */
		virtual int findNode(Ionflux::GeoUtils::TransformNodes::TransformNode* 
		needle, unsigned int occurence = 1) const;
        
		/** Get vector of nodes.
		 *
		 * \return vector of nodes.
		 */
		virtual std::vector<Ionflux::GeoUtils::TransformNodes::TransformNode*>& 
		getNodes();
		
		/** Add node.
		 *
		 * Add a node.
		 *
		 * \param addElement Node to be added.
		 */
		virtual void addNode(Ionflux::GeoUtils::TransformNodes::TransformNode* 
		addElement);
		
		/** Remove node.
		 *
		 * Remove a node.
		 *
		 * \param removeElement Node to be removed.
		 */
		virtual void removeNode(Ionflux::GeoUtils::TransformNodes::TransformNode*
		removeElement);
		
		/** Remove node.
		 *
		 * Remove a node.
		 *
		 * \param removeIndex Node to be removed.
		 */
		virtual void removeNodeIndex(unsigned int removeIndex);
		
		/** Clear nodes.
		 *
		 * Clear all nodes.
		 */
		virtual void clearNodes();
		
		/** Get source node.
		 *
		 * \return Current value of source node.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::TransformNode* getSource() 
		const;
		
		/** Set source node.
		 *
		 * Set new value of source node.
		 *
		 * \param newSource New value of source node.
		 */
		virtual void setSource(Ionflux::GeoUtils::TransformNodes::TransformNode* 
		newSource);
		
		/** Get drain node.
		 *
		 * \return Current value of drain node.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::TransformNode* getDrain() 
		const;
		
		/** Set drain node.
		 *
		 * Set new value of drain node.
		 *
		 * \param newDrain New value of drain node.
		 */
		virtual void setDrain(Ionflux::GeoUtils::TransformNodes::TransformNode* 
		newDrain);
};

}

}

}

/** \file TransformGraph.hpp
 * \brief Transform graph (header).
 */
#endif
