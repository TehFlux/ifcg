#ifndef IONFLUX_VOLGFX_NODESET
#define IONFLUX_VOLGFX_NODESET
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeSet.hpp                     Node set (header).
 * ========================================================================== */

#include "ifvg/types.hpp"
#include "ifvg/constants.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace VolGfx
{

class Node;

/// Class information for class NodeSet.
class NodeSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		NodeSetClassInfo();
		/// Destructor.
		virtual ~NodeSetClassInfo();
};

/** Node set.
 * \ingroup ifvg
 *
 * A set of nodes.
 */
class NodeSet
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Vector of nodes.
		std::vector<Ionflux::VolGfx::Node*> nodes;
		
	public:
		/// Class information instance.
		static const NodeSetClassInfo nodeSetClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new NodeSet object.
		 */
		NodeSet();
		
		/** Constructor.
		 *
		 * Construct new NodeSet object.
		 *
		 * \param other Other object.
		 */
		NodeSet(const Ionflux::VolGfx::NodeSet& other);
		
		/** Destructor.
		 *
		 * Destruct NodeSet object.
		 */
		virtual ~NodeSet();
		
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
		virtual Ionflux::VolGfx::NodeSet& operator=(const 
		Ionflux::VolGfx::NodeSet& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::VolGfx::NodeSet* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::VolGfx::NodeSet* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::VolGfx::NodeSet* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
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
		virtual Ionflux::VolGfx::Node* getNode(unsigned int elementIndex = 0) 
		const;
		
		/** Find node.
		 *
		 * Find the specified occurence of a node.
		 *
		 * \param needle Node to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the node, or -1 if the node cannot be found.
		 */
		virtual int findNode(Ionflux::VolGfx::Node* needle, unsigned int 
		occurence = 1) const;
        
		/** Get vector of nodes.
		 *
		 * \return vector of nodes.
		 */
		virtual std::vector<Ionflux::VolGfx::Node*>& getNodes();
		
		/** Add node.
		 *
		 * Add a node.
		 *
		 * \param addElement Node to be added.
		 */
		virtual void addNode(Ionflux::VolGfx::Node* addElement);
		
		/** Create node.
		 *
		 * Create a new node which is managed by the node set.
		 *
		 * \return New node.
		 */
		virtual Ionflux::VolGfx::Node* addNode();
		
		/** Add nodes.
		 *
		 * Add nodes from a node vector.
		 *
		 * \param newNodes nodes.
		 */
		virtual void addNodes(const std::vector<Ionflux::VolGfx::Node*>& 
		newNodes);
		
		/** Add nodes.
		 *
		 * Add nodes from a node set.
		 *
		 * \param newNodes nodes.
		 */
		virtual void addNodes(Ionflux::VolGfx::NodeSet* newNodes);
		
		/** Remove node.
		 *
		 * Remove a node.
		 *
		 * \param removeElement Node to be removed.
		 */
		virtual void removeNode(Ionflux::VolGfx::Node* removeElement);
		
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
};

}

}

/** \file NodeSet.hpp
 * \brief Node set (header).
 */
#endif
