#ifndef IONFLUX_GEOUTILS_FBXNODE
#define IONFLUX_GEOUTILS_FBXNODE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FBXNode.hpp                     FBX Node (header).
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

#include "ifobject/constants.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Range3.hpp"
#include "geoutils/fbxtypes.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Matrix4;
class Mesh;
class FBXNodeSet;

namespace XMLUtils
{

class FBXNodeXMLFactory;

}

/// Class information for class FBXNode.
class FBXNodeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		FBXNodeClassInfo();
		/// Destructor.
		virtual ~FBXNodeClassInfo();
};

/** FBX Node.
 * \ingroup geoutils
 *
 * A wrapper for the FBX node.
 */
class FBXNode
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// FBX node implementation.
		FBXSDK_NAMESPACE::FbxNode* impl;
		/// Transform matrix.
		Ionflux::GeoUtils::Matrix4* transformMatrix;
		/// Child node vector.
		std::vector<Ionflux::GeoUtils::FBXNode*> childNodes;
		/// Attribute type.
		Ionflux::GeoUtils::FBXNodeAttributeType attributeType;
		/// Name.
		std::string name;
		/// Bounds.
		Ionflux::GeoUtils::Range3* bounds;
		/// Number of vertices (for mesh nodes).
		unsigned int numVerts;
		/// Number of faces (for mesh nodes).
		unsigned int numFaces;
		
	public:
		/// Node attribute type: unknown.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_UNKNOWN;
		/// Node attribute type: null.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_NULL;
		/// Node attribute type: marker.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_MARKER;
		/// Node attribute type: skeleton.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_SKELETON;
		/// Node attribute type: mesh.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_MESH;
		/// Node attribute type: nurbs.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_NURBS;
		/// Node attribute type: patch.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_PATCH;
		/// Node attribute type: camera.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_CAMERA;
		/// Node attribute type: camerastereo.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_CAMERASTEREO;
		/// Node attribute type: cameraswitcher.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_CAMERASWITCHER;
		/// Node attribute type: light.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_LIGHT;
		/// Node attribute type: opticalreference.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_OPTICALREFERENCE;
		/// Node attribute type: opticalmarker.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_OPTICALMARKER;
		/// Node attribute type: nurbscurve.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_NURBSCURVE;
		/// Node attribute type: trimnurbssurface.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_TRIMNURBSSURFACE;
		/// Node attribute type: boundary.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_BOUNDARY;
		/// Node attribute type: nurbssurface.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_NURBSSURFACE;
		/// Node attribute type: shape.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_SHAPE;
		/// Node attribute type: lodgroup.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_LODGROUP;
		/// Node attribute type: subdiv.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_SUBDIV;
		/// Node attribute type: cachedeffect.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_CACHEDEFFECT;
		/// Node attribute type: line.
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_LINE;
		/// Class information instance.
		static const FBXNodeClassInfo fBXNodeClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new FBXNode object.
		 */
		FBXNode();
		
		/** Constructor.
		 *
		 * Construct new FBXNode object.
		 *
		 * \param other Other object.
		 */
		FBXNode(const Ionflux::GeoUtils::FBXNode& other);
		
		/** Constructor.
		 *
		 * Construct new FBXNode object.
		 *
		 * \param initImpl FBX node.
		 */
		FBXNode(FBXSDK_NAMESPACE::FbxNode* initImpl);
		
		/** Destructor.
		 *
		 * Destruct FBXNode object.
		 */
		virtual ~FBXNode();
		
		/** Update.
		 *
		 * Update the state of the node from the implementation object.
		 */
		virtual void update();
		
		/** Get the number of child nodes (FBX).
		 *
		 * Get the number of child nodes from the FBX hierarchy.
		 *
		 * \return Number of child nodes.
		 */
		virtual int getNumChildNodesFBX() const;
		
		/** Get child node (FBX).
		 *
		 * Get the child node with the specified index from the FBX hierarchy.
		 * The returned node will not be referenced and must be managed by the
		 * caller.
		 *
		 * \param index child node index.
		 *
		 * \return Child node, or 0 if the child node ith the specified index 
		 * does not exist.
		 */
		virtual Ionflux::GeoUtils::FBXNode* getChildNodeFBX(int index) const;
		
		/** Add child nodes (FBX).
		 *
		 * Add the child nodes from the FBX hierarchy.
		 *
		 * \param recursive Add child nodes recursively.
		 */
		virtual void addChildNodesFBX(bool recursive = false);
		
		/** List child nodes (FBX).
		 *
		 * List the child nodes of the node from the FBX hierarchy.
		 *
		 * \param recursive List child nodes recursively.
		 * \param indentWidth Indentation width.
		 * \param indentChar Indentation character.
		 * \param depth Depth.
		 */
		virtual void listChildNodesFBX(bool recursive = false, unsigned int 
		indentWidth = Ionflux::ObjectBase::DEFAULT_INDENT_WIDTH, char indentChar 
		= ' ', unsigned int depth = 0) const;
		
		/** Find child node by name (FBX).
		 *
		 * Find a child node by name from the FBX hierarchy. The returned node
		 * will not be referenced and must be managed by the caller.
		 *
		 * \param needle name of node to be found.
		 * \param recursive look for child node recursively.
		 *
		 * \return Node with the specified name, or 0 if the node does not exist.
		 */
		virtual Ionflux::GeoUtils::FBXNode* findChildNodeByNameFBX(const 
		std::string& needle, bool recursive = true);
		
		/** Get mesh.
		 *
		 * Get the mesh attached to a node.
		 *
		 * \param target where to store the mesh data.
		 * \param recursive recursively merge meshes.
		 * \param localTransform local transformation to be applied to the mesh.
		 * \param applyNodeTransform0 apply node transformations.
		 *
		 * \return number of meshes that were merged.
		 */
		virtual unsigned int getMesh(Ionflux::GeoUtils::Mesh& target, bool 
		recursive = false, Ionflux::GeoUtils::Matrix4* localTransform = 0, bool 
		applyNodeTransform0 = true) const;
		
		/** Dump mesh.
		 *
		 * Dump mesh data from a node to a directory. Each mesh will be saved 
		 * to an individual file.
		 *
		 * \param targetPath where to store the mesh data.
		 * \param recursive recursively dump meshes.
		 * \param localTransform local transformation to be applied to the mesh.
		 * \param startIndex start index for extracted meshes.
		 * \param scale0 mesh scale factor.
		 * \param applyNodeTransform0 apply node transformations.
		 *
		 * \return number of meshes that were merged.
		 */
		virtual unsigned int dumpMesh(const std::string& targetPath, bool 
		recursive = false, Ionflux::GeoUtils::Matrix4* localTransform = 0, 
		unsigned int startIndex = 0, double scale0 = 1., bool applyNodeTransform0
		= true) const;
		
		/** Update bounds (FBX).
		 *
		 * Update the bounds of the node from the FBX hierarchy. The bounds 
		 * will be set to the bounds of the mesh for mesh nodes and to zero 
		 * for all other nodes.
		 *
		 * \param recursive recursively update bounds.
		 * \param localTransform local transformation to be applied to vertices.
		 *
		 * \return Bounds if the node is a mesh node, 0 otherwise.
		 */
		virtual Ionflux::GeoUtils::Range3* updateBoundsFBX(bool recursive = 
		false, Ionflux::GeoUtils::Matrix4* localTransform = 0);
		
		/** Update mesh data (FBX).
		 *
		 * Update the mesh data of the node from the FBX hierarchy. The mesh 
		 * data will be set only for mesh nodes.
		 *
		 * \param recursive recursively update mesh data.
		 */
		virtual void updateMeshDataFBX(bool recursive = false);
		
		/** Get node hierarchy bounds.
		 *
		 * Get the bounds of the node hierarchy starting at this node. The 
		 * target bounds will be extended if \c valid is set to \c true. 
		 * Otherwise, the bounds will be set to the first valid bounds 
		 * encountered while traversing the hierarchy and extended by any 
		 * other bounds encountered after that.
		 *
		 * \param target where to store the bounds.
		 * \param valid bounds valid flag.
		 *
		 * \return \c true if the bounds of the hierarchy are valid, \c false 
		 * otherwise.
		 */
		virtual bool getHierarchyBounds(Ionflux::GeoUtils::Range3& target, bool 
		valid = false);
		
		/** Get number of vertices of node hierarchy.
		 *
		 * Get the number of vertices of the node hierarchy starting at this 
		 * node.
		 *
		 * \return number of vertices of the node hierarchy starting at this 
		 * node.
		 */
		virtual unsigned int getHierarchyNumVerts();
		
		/** Get number of faces of node hierarchy.
		 *
		 * Get the number of faces of the node hierarchy starting at this 
		 * node.
		 *
		 * \return number of faces of the node hierarchy starting at this node.
		 */
		virtual unsigned int getHierarchyNumFaces();
		
		/** Assign node IDs.
		 *
		 * Recursively assign node IDs to the nodes contained in the hierarchy
		 * of which this node is the root. Each node is assigned an ID 
		 * consisting of the prefix and a number (starting from \c offset) 
		 * that is formatted according to the specified parameters.
		 *
		 * \param prefix ID prefix.
		 * \param width field width.
		 * \param fillChar Fill character.
		 * \param offset offset.
		 *
		 * \return new offset.
		 */
		virtual unsigned int assignNodeIDs(const std::string& prefix = "", 
		unsigned int width = 8, char fillChar = '0', unsigned int offset = 0);
		
		/** Find child node by name.
		 *
		 * Find a child node by name.
		 *
		 * \param needle name of node to be found.
		 * \param recursive look for child node recursively.
		 *
		 * \return Node with the specified name, or 0 if the node does not exist.
		 */
		virtual Ionflux::GeoUtils::FBXNode* findChildNodeByName(const 
		std::string& needle, bool recursive = true);
		
		/** Find nodes by attribute type.
		 *
		 * Find nodes by attribute type.
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
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object
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
		virtual Ionflux::GeoUtils::FBXNode& operator=(const 
		Ionflux::GeoUtils::FBXNode& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::FBXNode* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::FBXNode* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::FBXNode* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new FBXNode object.
		 *
		 * \param initImpl FBX node.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::FBXNode* create(FBXSDK_NAMESPACE::FbxNode* 
		initImpl, Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
        
		/** Get XML element name.
		 *
		 * Get the XML element name for the object.
		 *
		 * \return XML element name
		 */
		virtual std::string getXMLElementName() const;
        
		/** Get XML attribute data.
		 *
		 * Get a string containing the XML attributes of the object.
		 *
		 * \return XML attribute data
		 */
		virtual std::string getXMLAttributeData() const;
        
        /** Get XML child data.
		 *
		 * Get the XML child data for the object.
		 *
		 * \param target Where to store the XML data.
		 * \param indentLevel Indentation level.
		 */
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
        
        /** Load from XML file.
		 *
		 * Initialize the object from an XML file.
		 *
		 * \param fileName file name
		 */
		virtual void loadFromXMLFile(const std::string& FileName);
        
        /** Get XML object factory
		 *
		 * Get the XML object factory singleton for the class.
		 *
		 * \param fileName file name
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		
		/** Get fBX node implementation.
		 *
		 * \return Current value of fBX node implementation.
		 */
		virtual FBXSDK_NAMESPACE::FbxNode* getImpl() const;
		
		/** Set fBX node implementation.
		 *
		 * Set new value of fBX node implementation.
		 *
		 * \param newImpl New value of fBX node implementation.
		 */
		virtual void setImpl(FBXSDK_NAMESPACE::FbxNode* newImpl);
		
		/** Get transform matrix.
		 *
		 * \return Current value of transform matrix.
		 */
		virtual Ionflux::GeoUtils::Matrix4* getTransformMatrix() const;
		
		/** Set transform matrix.
		 *
		 * Set new value of transform matrix.
		 *
		 * \param newTransformMatrix New value of transform matrix.
		 */
		virtual void setTransformMatrix(Ionflux::GeoUtils::Matrix4* 
		newTransformMatrix);
		
		/** Get number of childNodes.
		 *
		 * \return Number of childNodes.
		 */
		virtual unsigned int getNumChildNodes() const;
		
		/** Get childNode.
		 *
		 * Get the childNode at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return ChildNode at specified index.
		 */
		virtual Ionflux::GeoUtils::FBXNode* getChildNode(unsigned int 
		elementIndex = 0) const;
		
		/** Find childNode.
		 *
		 * Find the specified occurence of a childNode.
		 *
		 * \param needle ChildNode to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the childNode, or -1 if the childNode cannot be 
		 * found.
		 */
		virtual int findChildNode(Ionflux::GeoUtils::FBXNode* needle, unsigned 
		int occurence = 1) const;
        
		/** Get child node vector.
		 *
		 * \return child node vector.
		 */
		virtual std::vector<Ionflux::GeoUtils::FBXNode*>& getChildNodes();
		
		/** Add childNode.
		 *
		 * Add a childNode.
		 *
		 * \param addElement ChildNode to be added.
		 */
		virtual void addChildNode(Ionflux::GeoUtils::FBXNode* addElement);
		
		/** Create childNode.
		 *
		 * Create a new childNode which is managed by the childNode set.
		 *
		 * \return New childNode.
		 */
		virtual Ionflux::GeoUtils::FBXNode* addChildNode();
		
		/** Add childNodes.
		 *
		 * Add childNodes from a childNode vector.
		 *
		 * \param newChildNodes childNodes.
		 */
		virtual void addChildNodes(const 
		std::vector<Ionflux::GeoUtils::FBXNode*>& newChildNodes);
		
		/** Add childNodes.
		 *
		 * Add childNodes from a childNode set.
		 *
		 * \param newChildNodes childNodes.
		 */
		virtual void addChildNodes(Ionflux::GeoUtils::FBXNode* newChildNodes);
		
		/** Remove childNode.
		 *
		 * Remove a childNode.
		 *
		 * \param removeElement ChildNode to be removed.
		 */
		virtual void removeChildNode(Ionflux::GeoUtils::FBXNode* removeElement);
		
		/** Remove childNode.
		 *
		 * Remove a childNode.
		 *
		 * \param removeIndex ChildNode to be removed.
		 */
		virtual void removeChildNodeIndex(unsigned int removeIndex);
		
		/** Clear childNodes.
		 *
		 * Clear all childNodes.
		 */
		virtual void clearChildNodes();
		
		/** Get attribute type.
		 *
		 * \return Current value of attribute type.
		 */
		virtual Ionflux::GeoUtils::FBXNodeAttributeType getAttributeType() const;
		
		/** Set attribute type.
		 *
		 * Set new value of attribute type.
		 *
		 * \param newAttributeType New value of attribute type.
		 */
		virtual void setAttributeType(Ionflux::GeoUtils::FBXNodeAttributeType 
		newAttributeType);
		
		/** Get name.
		 *
		 * \return Current value of name.
		 */
		virtual std::string getName() const;
		
		/** Set name.
		 *
		 * Set new value of name.
		 *
		 * \param newName New value of name.
		 */
		virtual void setName(const std::string& newName);
		
		/** Get bounds.
		 *
		 * \return Current value of bounds.
		 */
		virtual Ionflux::GeoUtils::Range3* getBounds() const;
		
		/** Set bounds.
		 *
		 * Set new value of bounds.
		 *
		 * \param newBounds New value of bounds.
		 */
		virtual void setBounds(Ionflux::GeoUtils::Range3* newBounds);
		
		/** Get number of vertices (for mesh nodes).
		 *
		 * \return Current value of number of vertices (for mesh nodes).
		 */
		virtual unsigned int getNumVerts() const;
		
		/** Set number of vertices (for mesh nodes).
		 *
		 * Set new value of number of vertices (for mesh nodes).
		 *
		 * \param newNumVerts New value of number of vertices (for mesh nodes).
		 */
		virtual void setNumVerts(unsigned int newNumVerts);
		
		/** Get number of faces (for mesh nodes).
		 *
		 * \return Current value of number of faces (for mesh nodes).
		 */
		virtual unsigned int getNumFaces() const;
		
		/** Set number of faces (for mesh nodes).
		 *
		 * Set new value of number of faces (for mesh nodes).
		 *
		 * \param newNumFaces New value of number of faces (for mesh nodes).
		 */
		virtual void setNumFaces(unsigned int newNumFaces);
};

}

}

/** \file FBXNode.hpp
 * \brief FBX Node (header).
 */
#endif
