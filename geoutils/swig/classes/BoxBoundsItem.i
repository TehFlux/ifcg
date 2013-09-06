/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BoxBoundsItem.i                 Item with box bounds (interface).
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
#include "geoutils/BoxBoundsItem.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class BoxBoundsItem;

class BoxBoundsItemClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BoxBoundsItemClassInfo();
        virtual ~BoxBoundsItemClassInfo();
};

class BoxBoundsItem
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        BoxBoundsItem();
		BoxBoundsItem(const Ionflux::GeoUtils::BoxBoundsItem& other);
        BoxBoundsItem(const Ionflux::GeoUtils::Vector3& initCenter, const 
        Ionflux::GeoUtils::Vector3& initRVec = 
        Ionflux::GeoUtils::Vector3::ZERO, const std::string& initItemID = 
        "");
        virtual ~BoxBoundsItem();
        virtual void updateBounds();
        virtual void updateRadiusAndCenter();
        virtual void clear();
        virtual Ionflux::GeoUtils::Vertex3Vector getBoxVertices();
        virtual Ionflux::GeoUtils::Polygon3Vector getBoxFaces();
        virtual int checkPlane(const Ionflux::GeoUtils::Plane3& plane, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkPlaneInner(const Ionflux::GeoUtils::Plane3& plane,
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkSphere(const Ionflux::GeoUtils::Sphere3& sphere, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkSphereInner(const Ionflux::GeoUtils::Sphere3& 
        sphere, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool checkLine(const Ionflux::GeoUtils::Line3& line, double
        t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool checkLineInner(const Ionflux::GeoUtils::Line3& line, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::RangeCompResult3 compare3(const 
        Ionflux::GeoUtils::BoxBoundsItem& other, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual Ionflux::GeoUtils::RangeCompResult compare(const 
        Ionflux::GeoUtils::BoxBoundsItem& other, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual int checkBox(const Ionflux::GeoUtils::BoxBoundsItem& other,
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkBoxInner(const Ionflux::GeoUtils::BoxBoundsItem& 
        other, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool checkRay(const Ionflux::GeoUtils::Line3& ray, double t
        = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool checkRayInner(const Ionflux::GeoUtils::Line3& ray, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool operator==(const Ionflux::GeoUtils::BoxBoundsItem& 
        other) const;
        virtual bool operator!=(const Ionflux::GeoUtils::BoxBoundsItem& 
        other) const;
        virtual std::string getXML_legacy() const;
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::BoxBoundsItem* copy() const;
		static Ionflux::GeoUtils::BoxBoundsItem* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::BoxBoundsItem* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setCenter(const Ionflux::GeoUtils::Vector3& 
        newCenter);
        virtual Ionflux::GeoUtils::Vector3 getCenter() const;
        virtual void setRVec(const Ionflux::GeoUtils::Vector3& newRVec);
        virtual Ionflux::GeoUtils::Vector3 getRVec() const;
        virtual void setItemID(const std::string& newItemID);
        virtual std::string getItemID() const;
        virtual void setBounds(const Ionflux::GeoUtils::Range3& newBounds);
        virtual Ionflux::GeoUtils::Range3 getBounds() const;
        virtual void setRadius(double newRadius);
        virtual double getRadius() const;        
        virtual unsigned int getNumBoxVertices() const;
        virtual Ionflux::GeoUtils::Vertex3* getBoxVertex(unsigned int 
        elementIndex = 0) const;
		virtual int findBoxVertex(Ionflux::GeoUtils::Vertex3* needle, unsigned 
		int occurence = 1) const;
        virtual void addBoxVertex(Ionflux::GeoUtils::Vertex3* addElement);        
        virtual void removeBoxVertex(Ionflux::GeoUtils::Vertex3* 
        removeElement);
		virtual void removeBoxVertexIndex(unsigned int removeIndex);
		virtual void clearBoxVertices();        
        virtual unsigned int getNumBoxFaces() const;
        virtual Ionflux::GeoUtils::Polygon3* getBoxFace(unsigned int 
        elementIndex = 0) const;
		virtual int findBoxFace(Ionflux::GeoUtils::Polygon3* needle, unsigned int
		occurence = 1) const;
        virtual void addBoxFace(Ionflux::GeoUtils::Polygon3* addElement);        
        virtual void removeBoxFace(Ionflux::GeoUtils::Polygon3* 
        removeElement);
		virtual void removeBoxFaceIndex(unsigned int removeIndex);
		virtual void clearBoxFaces();
};

}

}
