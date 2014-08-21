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
#include "geoutils/fbxtypes.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Matrix4;
class Mesh;

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
		
		/** Get the node attribute type.
		 *
		 * Get the node attribute type.
		 *
		 * \return String representation.
		 */
		virtual Ionflux::GeoUtils::FBXNodeAttributeType getAttributeType() const;
		
		/** Get the node name.
		 *
		 * Get the node name.
		 *
		 * \return Name.
		 */
		virtual std::string getName() const;
		
		/** Get the number of child nodes.
		 *
		 * Get the number of child nodes.
		 *
		 * \return Number of child nodes.
		 */
		virtual int getNumChildNodes() const;
		
		/** Get child node.
		 *
		 * Get the child node with the specified index. The returned node will
		 * not be referenced and must be managed by the caller.
		 *
		 * \param index child node index.
		 *
		 * \return Child node, or 0 if the child node ith the specified index 
		 * does not exist.
		 */
		virtual Ionflux::GeoUtils::FBXNode* getChildNode(int index) const;
		
		/** List child nodes.
		 *
		 * List the child nodes of the node
		 *
		 * \param recursive List child nodes recursively.
		 * \param indentWidth Indentation width.
		 * \param indentChar Indentation character.
		 * \param depth Depth.
		 */
		virtual void listChildNodes(bool recursive = false, unsigned int 
		indentWidth = Ionflux::ObjectBase::DEFAULT_INDENT_WIDTH, char indentChar 
		= ' ', unsigned int depth = 0) const;
		
		/** Find child node by name.
		 *
		 * Find a child node by name. The returned node will not be referenced
		 * and must be managed by the caller.
		 *
		 * \param needle name of node to be found.
		 * \param recursive look for child node.
		 *
		 * \return Node with the specified name, or 0 if the node does not exist.
		 */
		virtual Ionflux::GeoUtils::FBXNode* findChildNodeByName(const 
		std::string& needle, bool recursive = true);
		
		/** Get mesh.
		 *
		 * Get the mesh attached to a node.
		 *
		 * \param target where to store the mesh data.
		 * \param recursive recursively merge meshes.
		 * \param localTransform local transformation to be applied to the mesh.
		 *
		 * \return number of meshes that were merged.
		 */
		virtual unsigned int getMesh(Ionflux::GeoUtils::Mesh& target, bool 
		recursive = false, Ionflux::GeoUtils::Matrix4* localTransform = 0) const;
		
		/** Dump mesh.
		 *
		 * Dump mesh data from a node to a directory. Each mesh will be saved 
		 * to an individual file.
		 *
		 * \param targetPath where to store the mesh data.
		 * \param recursive recursively dump meshes.
		 * \param localTransform local transformation to be applied to the mesh.
		 *
		 * \return number of meshes that were merged.
		 */
		virtual unsigned int dumpMesh(const std::string& targetPath, bool 
		recursive = false, Ionflux::GeoUtils::Matrix4* localTransform = 0) const;
		
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
};

}

}

/** \file FBXNode.hpp
 * \brief FBX Node (header).
 */
#endif
