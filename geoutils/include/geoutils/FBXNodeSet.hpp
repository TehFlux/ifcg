#ifndef IONFLUX_GEOUTILS_FBXNODESET
#define IONFLUX_GEOUTILS_FBXNODESET
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FBXNodeSet.hpp                  FBX node set (header).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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
#include "geoutils/fbxtypes.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class FBXNode;

/// Class information for class FBXNodeSet.
class FBXNodeSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		FBXNodeSetClassInfo();
		/// Destructor.
		virtual ~FBXNodeSetClassInfo();
};

/** FBX node set.
 * \ingroup geoutils
 *
 * A set of FBX nodes.
 */
class FBXNodeSet
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Node vector.
		std::vector<Ionflux::GeoUtils::FBXNode*> nodes;
		
	public:
		/// Class information instance.
		static const FBXNodeSetClassInfo fBXNodeSetClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new FBXNodeSet object.
		 */
		FBXNodeSet();
		
		/** Constructor.
		 *
		 * Construct new FBXNodeSet object.
		 *
		 * \param other Other object.
		 */
		FBXNodeSet(const Ionflux::GeoUtils::FBXNodeSet& other);
		
		/** Constructor.
		 *
		 * Construct new FBXNodeSet object.
		 *
		 * \param initNodes Nodes.
		 */
		FBXNodeSet(Ionflux::GeoUtils::FBXNodeVector& initNodes);
		
		/** Destructor.
		 *
		 * Destruct FBXNodeSet object.
		 */
		virtual ~FBXNodeSet();
		
		/** Find nodes by attribute type.
		 *
		 * Find nodes from the set by attribute type.
		 *
		 * \param t node attribute type.
		 * \param target where to store the nodes.
		 * \param recursive look for child nodes recursively.
		 *
		 * \return number of nodes that have been found.
		 */
		virtual unsigned int 
		findNodesByAttributeType(Ionflux::GeoUtils::FBXNodeAttributeType t, 
		Ionflux::GeoUtils::FBXNodeSet& target, bool recursive = true);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::FBXNodeSet& operator=(const 
		Ionflux::GeoUtils::FBXNodeSet& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::FBXNodeSet* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::FBXNodeSet* 
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
		static Ionflux::GeoUtils::FBXNodeSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new FBXNodeSet object.
		 *
		 * \param initNodes Nodes.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::FBXNodeSet* 
		create(Ionflux::GeoUtils::FBXNodeVector& initNodes, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
		virtual Ionflux::GeoUtils::FBXNode* getNode(unsigned int elementIndex = 
		0) const;
		
		/** Find node.
		 *
		 * Find the specified occurence of a node.
		 *
		 * \param needle Node to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the node, or -1 if the node cannot be found.
		 */
		virtual int findNode(Ionflux::GeoUtils::FBXNode* needle, unsigned int 
		occurence = 1) const;
        
		/** Get node vector.
		 *
		 * \return node vector.
		 */
		virtual std::vector<Ionflux::GeoUtils::FBXNode*>& getNodes();
		
		/** Add node.
		 *
		 * Add a node.
		 *
		 * \param addElement Node to be added.
		 */
		virtual void addNode(Ionflux::GeoUtils::FBXNode* addElement);
		
		/** Create node.
		 *
		 * Create a new node which is managed by the node set.
		 *
		 * \return New node.
		 */
		virtual Ionflux::GeoUtils::FBXNode* addNode();
		
		/** Add nodes.
		 *
		 * Add nodes from a node vector.
		 *
		 * \param newNodes nodes.
		 */
		virtual void addNodes(const std::vector<Ionflux::GeoUtils::FBXNode*>& 
		newNodes);
		
		/** Add nodes.
		 *
		 * Add nodes from a node set.
		 *
		 * \param newNodes nodes.
		 */
		virtual void addNodes(Ionflux::GeoUtils::FBXNodeSet* newNodes);
		
		/** Remove node.
		 *
		 * Remove a node.
		 *
		 * \param removeElement Node to be removed.
		 */
		virtual void removeNode(Ionflux::GeoUtils::FBXNode* removeElement);
		
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

/** \file FBXNodeSet.hpp
 * \brief FBX node set (header).
 */
#endif
