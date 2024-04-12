/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Range3.i                        Range of values (3D) (interface).
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
#include "geoutils/Range3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Line3;
class Vertex3Set;
class Mesh;

class Range3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Range3ClassInfo();
        virtual ~Range3ClassInfo();
};

class Range3
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Range3();
		Range3(const Ionflux::GeoUtils::Range3& other);
        Range3(const Ionflux::GeoUtils::Vector3& initCenter, const 
        Ionflux::GeoUtils::Vector3* initRadius = 0);
        Range3(const Ionflux::GeoUtils::Range& initX, const 
        Ionflux::GeoUtils::Range& initY, const Ionflux::GeoUtils::Range& 
        initZ);
        Range3(const Ionflux::GeoUtils::Vector2& rx, const 
        Ionflux::GeoUtils::Vector2& ry, const Ionflux::GeoUtils::Vector2& 
        rz);
        Range3(double xMin, double xMax, double yMin, double yMax, double 
        zMin, double zMax);
        Range3(const Ionflux::GeoUtils::Vector3& initMin, double 
        edgeLength);
        virtual ~Range3();
        virtual void extend(const Ionflux::GeoUtils::Range3& other);
        virtual void extend(const Ionflux::GeoUtils::Vector3& v);
        virtual void extend(double rd);
        virtual Ionflux::GeoUtils::Vector3 getCenter() const;
        virtual Ionflux::GeoUtils::Vector3 getRadius() const;
        virtual Ionflux::GeoUtils::Vector3 getExtent() const;
        virtual double getExtent(Ionflux::GeoUtils::AxisID axis) const;
        virtual Ionflux::GeoUtils::Vector3 getValue(double v0, double v1, 
        double v2) const;
        virtual Ionflux::GeoUtils::Vector3 getValue(const 
        Ionflux::GeoUtils::Vector3 v) const;
        virtual Ionflux::GeoUtils::Vector3 getRMin() const;
        virtual Ionflux::GeoUtils::Vector3 getRMax() const;
        virtual Ionflux::GeoUtils::Vector3 clamp(const 
        Ionflux::GeoUtils::Vector3 v) const;
        virtual Ionflux::GeoUtils::Vector3 getClampedValue(const 
        Ionflux::GeoUtils::Vector3 v) const;
        virtual Ionflux::GeoUtils::Range 
        getAxisRange(Ionflux::GeoUtils::AxisID axis) const;
        virtual void setBounds(const Ionflux::GeoUtils::Vector3& v);
        virtual void setBounds(const Ionflux::GeoUtils::Range3& other);
        virtual void setBounds(const Ionflux::GeoUtils::Vector3& v, const 
        Ionflux::GeoUtils::Vector3* r);
        virtual void setBounds(const Ionflux::GeoUtils::Vector3& v, double 
        edgeLength);
        virtual Ionflux::GeoUtils::RangeCompResult3 compare3(const 
        Ionflux::GeoUtils::Range3& other, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual Ionflux::GeoUtils::RangeCompResult compare(const 
        Ionflux::GeoUtils::Range3& other, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual bool isInRange(const Ionflux::GeoUtils::Vector3& v, double 
        t = Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual bool intersect(const Ionflux::GeoUtils::Line3& line, 
        Ionflux::GeoUtils::AxisID axis, 
        Ionflux::GeoUtils::AAPlanePairIntersection& result, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual bool intersect(const Ionflux::GeoUtils::Line3& line, 
        Ionflux::GeoUtils::AAPlanePairIntersection& result, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual Ionflux::GeoUtils::AxisTriple getAxisOrder() const;
        virtual Ionflux::GeoUtils::Mesh* getMesh() const;
        virtual bool operator==(const Ionflux::GeoUtils::Range3& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Range3& other) 
        const;
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Range3* copy() const;
		static Ionflux::GeoUtils::Range3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Range3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Range3* create(const 
		Ionflux::GeoUtils::Vector3& initCenter, const Ionflux::GeoUtils::Vector3*
		initRadius = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Range3* create(const Ionflux::GeoUtils::Range& 
		initX, const Ionflux::GeoUtils::Range& initY, const 
		Ionflux::GeoUtils::Range& initZ, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Range3* create(const 
		Ionflux::GeoUtils::Vector2& rx, const Ionflux::GeoUtils::Vector2& ry, 
		const Ionflux::GeoUtils::Vector2& rz, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Range3* create(double xMin, double xMax, double
		yMin, double yMax, double zMin, double zMax, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Range3* create(const 
		Ionflux::GeoUtils::Vector3& initMin, double edgeLength, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setX(const Ionflux::GeoUtils::Range& newX);
        virtual Ionflux::GeoUtils::Range getX() const;
        virtual void setY(const Ionflux::GeoUtils::Range& newY);
        virtual Ionflux::GeoUtils::Range getY() const;
        virtual void setZ(const Ionflux::GeoUtils::Range& newZ);
        virtual Ionflux::GeoUtils::Range getZ() const;
};

}

}
