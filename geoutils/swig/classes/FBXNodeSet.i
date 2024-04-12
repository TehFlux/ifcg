/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FBXNodeSet.i                    FBX node set (interface).
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
%{
#include "geoutils/FBXNodeSet.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class FBXNode;

class FBXNodeSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FBXNodeSetClassInfo();
        virtual ~FBXNodeSetClassInfo();
};

class FBXNodeSet
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        FBXNodeSet();
		FBXNodeSet(const Ionflux::GeoUtils::FBXNodeSet& other);
        FBXNodeSet(Ionflux::GeoUtils::FBXNodeVector& initNodes);
        virtual ~FBXNodeSet();
        virtual unsigned int 
        findNodesByAttributeType(Ionflux::GeoUtils::FBXNodeAttributeType t,
        Ionflux::GeoUtils::FBXNodeSet& target, bool recursive = true);
		virtual Ionflux::GeoUtils::FBXNodeSet* copy() const;
		static Ionflux::GeoUtils::FBXNodeSet* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::FBXNodeSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::FBXNodeSet* 
		create(Ionflux::GeoUtils::FBXNodeVector& initNodes, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumNodes() const;
        virtual Ionflux::GeoUtils::FBXNode* getNode(unsigned int 
        elementIndex = 0) const;
		virtual int findNode(Ionflux::GeoUtils::FBXNode* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::FBXNode*>& getNodes();
        virtual void addNode(Ionflux::GeoUtils::FBXNode* addElement);
		virtual Ionflux::GeoUtils::FBXNode* addNode();
		virtual void addNodes(std::vector<Ionflux::GeoUtils::FBXNode*>& 
		newNodes);
		virtual void addNodes(Ionflux::GeoUtils::FBXNodeSet* newNodes);        
        virtual void removeNode(Ionflux::GeoUtils::FBXNode* removeElement);
		virtual void removeNodeIndex(unsigned int removeIndex);
		virtual void clearNodes();
};

}

}
