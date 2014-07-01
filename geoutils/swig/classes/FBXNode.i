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
        virtual Ionflux::GeoUtils::FBXNodeAttributeType getAttributeType() 
        const;
        virtual std::string getName() const;
        virtual int getNumChildNodes() const;
        virtual Ionflux::GeoUtils::FBXNode* getChildNode(int index) const;
        virtual void listChildNodes(bool recursive = false, unsigned int 
        indentWidth = Ionflux::ObjectBase::DEFAULT_INDENT_WIDTH, char 
        indentChar = ' ', unsigned int depth = 0) const;
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::FBXNode* copy() const;
		static Ionflux::GeoUtils::FBXNode* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::FBXNode* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setTransformMatrix(Ionflux::GeoUtils::Matrix4* 
        newTransformMatrix);
        virtual Ionflux::GeoUtils::Matrix4* getTransformMatrix() const;
};

}

}
