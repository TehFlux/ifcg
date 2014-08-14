/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vertex3.i                       Vertex (3D) (interface).
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
#include "geoutils/Vertex3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Interpolator;
class Plane3;
class Vertex3;

class Vertex3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vertex3ClassInfo();
        virtual ~Vertex3ClassInfo();
};

class Vertex3
: public Ionflux::GeoUtils::TransformableObject
{
    public:
		static const Ionflux::GeoUtils::Vertex3 ORIGIN;
        
        Vertex3();
		Vertex3(const Ionflux::GeoUtils::Vertex3& other);
        Vertex3(double initX, double initY, double initZ);
        Vertex3(const Ionflux::ObjectBase::DoubleVector& initCoords);
        Vertex3(const Ionflux::GeoUtils::Vector3& initCoords);
        Vertex3(const Ionflux::GeoUtils::Vector4& initCoords);
        Vertex3(const Ionflux::Mapping::Point& initCoords);
        virtual ~Vertex3();
        virtual void setCoords(double newX, double newY, double newZ);
        virtual void setCoords(const Ionflux::ObjectBase::DoubleVector& 
        newCoords);
        virtual void setCoords(const Ionflux::GeoUtils::Vector3& 
        newCoords);
        virtual void setCoords(const Ionflux::GeoUtils::Vector4& 
        newCoords);
        virtual void getCoords(Ionflux::ObjectBase::DoubleVector& target) 
        const;
        virtual void setCoords(const Ionflux::Mapping::Point& newCoords);
        virtual void getCoords(Ionflux::GeoUtils::Vector3& target) const;
        virtual double getCoord(int index) const;
        virtual Ionflux::GeoUtils::Vector3 getVector() const;
        virtual void setCoord(int index, double value);
        virtual Ionflux::GeoUtils::Vertex3 interpolate(const 
        Ionflux::GeoUtils::Vertex3& other, double t, 
        Ionflux::GeoUtils::Interpolator* interpolator = 0) const;
        virtual double distanceToPlane(const Ionflux::GeoUtils::Plane3& 
        plane) const;
        virtual bool eq(const Ionflux::GeoUtils::Vertex3& other, double t =
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool operator==(const Ionflux::GeoUtils::Vertex3& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Vertex3& other) 
        const;
        virtual Ionflux::GeoUtils::Vertex3& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Vertex3& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Vertex3& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Vertex3& normalize();
        virtual Ionflux::GeoUtils::Vertex3& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Vertex3& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual Ionflux::GeoUtils::Range3 getBounds();
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Vertex3& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Vertex3& transformVI(const 
        Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4*
        image = 0);
        virtual Ionflux::GeoUtils::Vertex3& duplicate();
        virtual Ionflux::Mapping::Point getPoint() const;
        virtual std::string getValueString() const;
        virtual std::string getXMLData_legacy() const;
        virtual std::string getXML_legacy() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Vertex3* copy() const;
		static Ionflux::GeoUtils::Vertex3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Vertex3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Vertex3* create(double initX, double initY, 
		double initZ, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Vertex3* create(const 
		Ionflux::ObjectBase::DoubleVector& initCoords, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Vertex3* create(const 
		Ionflux::GeoUtils::Vector3& initCoords, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Vertex3* create(const 
		Ionflux::GeoUtils::Vector4& initCoords, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Vertex3* create(const Ionflux::Mapping::Point& 
		initCoords, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setX(double newX);
        virtual double getX() const;
        virtual void setY(double newY);
        virtual double getY() const;
        virtual void setZ(double newZ);
        virtual double getZ() const;
};

}

}
