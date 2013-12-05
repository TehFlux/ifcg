/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Object3.i                       Object (3D) (interface).
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
#include "geoutils/Object3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Mesh;

class Object3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Object3ClassInfo();
        virtual ~Object3ClassInfo();
};

class Object3
: public Ionflux::GeoUtils::TransformableObject
{
    public:
        
        Object3();
		Object3(const Ionflux::GeoUtils::Object3& other);
        Object3(Ionflux::GeoUtils::Mesh* initMesh);
        virtual ~Object3();
        virtual void update();
        virtual void clear();
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Object3& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Object3& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Object3& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Object3& normalize();
        virtual Ionflux::GeoUtils::Object3& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Object3& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Object3& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Object3& transformVI(const 
        Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4*
        image = 0);
        virtual std::string getValueString() const;
        virtual Ionflux::GeoUtils::Object3& duplicate();
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Object3* copy() const;
		static Ionflux::GeoUtils::Object3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Object3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Object3* create(Ionflux::GeoUtils::Mesh* 
		initMesh, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setMesh(Ionflux::GeoUtils::Mesh* newMesh);
        virtual Ionflux::GeoUtils::Mesh* getMesh() const;
};

}

}
