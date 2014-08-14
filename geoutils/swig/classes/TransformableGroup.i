/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TransformableGroup.i            Transformable object group (interface).
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
#include "geoutils/TransformableGroup.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class TransformableGroupClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TransformableGroupClassInfo();
        virtual ~TransformableGroupClassInfo();
};

class TransformableGroup
: public Ionflux::GeoUtils::TransformableObject
{
    public:
        
        TransformableGroup();
		TransformableGroup(const Ionflux::GeoUtils::TransformableGroup& other);
        virtual ~TransformableGroup();
        virtual void clear();
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Vector3 getBarycenter() const;
        virtual Ionflux::GeoUtils::TransformableGroup& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::TransformableGroup& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::TransformableGroup& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::TransformableGroup& normalize();
        virtual Ionflux::GeoUtils::TransformableGroup& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::TransformableGroup& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::TransformableGroup& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::TransformableGroup& transformVI(const 
        Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4*
        image = 0);
        virtual Ionflux::GeoUtils::TransformableGroup& duplicate();
        virtual Ionflux::GeoUtils::TransformableGroup& flatten();
        virtual void getLeafItems(Ionflux::GeoUtils::TransformableGroup& 
        target, unsigned int level = 0);
        virtual std::string getDebugInfo(bool expand = true, unsigned int 
        level = 0);
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::TransformableGroup* copy() const;
		static Ionflux::GeoUtils::TransformableGroup* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformableGroup* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;        
        virtual unsigned int getNumItems() const;
        virtual Ionflux::GeoUtils::TransformableObject* getItem(unsigned 
        int elementIndex = 0) const;
		virtual int findItem(Ionflux::GeoUtils::TransformableObject* needle, 
		unsigned int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::TransformableObject*>& 
        getItems();
        virtual void addItem(Ionflux::GeoUtils::TransformableObject* 
        addElement);
		virtual Ionflux::GeoUtils::TransformableObject* addItem();
		virtual void 
		addItems(std::vector<Ionflux::GeoUtils::TransformableObject*>& newItems);
		virtual void addItems(Ionflux::GeoUtils::TransformableGroup* newItems);        
        virtual void removeItem(Ionflux::GeoUtils::TransformableObject* 
        removeElement);
		virtual void removeItemIndex(unsigned int removeIndex);
		virtual void clearItems();
};

}

}
