/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FBXNode.i                       FBX Node (interface).
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
%{
#include "geoutils/FBXNode.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Matrix4;
class Mesh;

class FBXNodeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FBXNodeClassInfo();
        virtual ~FBXNodeClassInfo();
};

class FBXNode
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_UNKNOWN;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_NULL;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_MARKER;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_SKELETON;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_MESH;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_NURBS;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_PATCH;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_CAMERA;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_CAMERASTEREO;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_CAMERASWITCHER;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_LIGHT;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_OPTICALREFERENCE;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_OPTICALMARKER;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_NURBSCURVE;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_TRIMNURBSSURFACE;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_BOUNDARY;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_NURBSSURFACE;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_SHAPE;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_LODGROUP;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_SUBDIV;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_CACHEDEFFECT;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_LINE;
        
        FBXNode();
		FBXNode(const Ionflux::GeoUtils::FBXNode& other);
        virtual ~FBXNode();
        virtual void update();
        virtual int getNumChildNodesFBX() const;
        virtual Ionflux::GeoUtils::FBXNode* getChildNodeFBX(int index) 
        const;
        virtual void addChildNodesFBX(bool recursive = false);
        virtual void listChildNodesFBX(bool recursive = false, unsigned int
        indentWidth = Ionflux::ObjectBase::DEFAULT_INDENT_WIDTH, char 
        indentChar = ' ', unsigned int depth = 0) const;
        virtual Ionflux::GeoUtils::FBXNode* findChildNodeByNameFBX(const 
        std::string& needle, bool recursive = true);
        virtual unsigned int getMesh(Ionflux::GeoUtils::Mesh& target, bool 
        recursive = false, Ionflux::GeoUtils::Matrix4* localTransform = 0, 
        bool applyNodeTransform0 = true) const;
        virtual unsigned int dumpMesh(const std::string& targetPath, bool 
        recursive = false, Ionflux::GeoUtils::Matrix4* localTransform = 0, 
        unsigned int startIndex = 0, double scale0 = 1., bool 
        applyNodeTransform0 = true) const;
        virtual unsigned int assignNodeIDs(const std::string& prefix = "", 
        unsigned int width = 8, char fillChar = '0', unsigned int offset = 
        0);
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::FBXNode* copy() const;
		static Ionflux::GeoUtils::FBXNode* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::FBXNode* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setTransformMatrix(Ionflux::GeoUtils::Matrix4* 
        newTransformMatrix);
        virtual Ionflux::GeoUtils::Matrix4* getTransformMatrix() const;        
        virtual unsigned int getNumChildNodes() const;
        virtual Ionflux::GeoUtils::FBXNode* getChildNode(unsigned int 
        elementIndex = 0) const;
		virtual int findChildNode(Ionflux::GeoUtils::FBXNode* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::FBXNode*>& getChildNodes();
        virtual void addChildNode(Ionflux::GeoUtils::FBXNode* addElement);
		virtual Ionflux::GeoUtils::FBXNode* addChildNode();
		virtual void addChildNodes(std::vector<Ionflux::GeoUtils::FBXNode*>& 
		newChildNodes);
		virtual void addChildNodes(Ionflux::GeoUtils::FBXNode* newChildNodes);        
        virtual void removeChildNode(Ionflux::GeoUtils::FBXNode* 
        removeElement);
		virtual void removeChildNodeIndex(unsigned int removeIndex);
		virtual void clearChildNodes();
        virtual void 
        setAttributeType(Ionflux::GeoUtils::FBXNodeAttributeType 
        newAttributeType);
        virtual Ionflux::GeoUtils::FBXNodeAttributeType getAttributeType() 
        const;
        virtual void setName(const std::string& newName);
        virtual std::string getName() const;
};

}

}
