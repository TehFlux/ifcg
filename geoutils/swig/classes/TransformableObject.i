/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TransformableObject.i           Transformable object (interface).
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
#include "geoutils/TransformableObject.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class TransformableObjectClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TransformableObjectClassInfo();
        virtual ~TransformableObjectClassInfo();
};

class TransformableObject
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        TransformableObject();
		TransformableObject(const Ionflux::GeoUtils::TransformableObject& other);
        virtual ~TransformableObject();
        virtual std::string getValueString() const;
        virtual void copyTransform(const 
        Ionflux::GeoUtils::TransformableObject& other);
        virtual void onTransformChanged();
        virtual void onVIChanged();
        virtual bool checkTransform(double t = 
        Ionflux::GeoUtils::DeferredTransform::COMPARE_TOLERANCE);
        virtual bool checkVI(double t = 
        Ionflux::GeoUtils::DeferredTransform::COMPARE_TOLERANCE);
        virtual Ionflux::GeoUtils::TransformableObject& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::TransformableObject& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::TransformableObject& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::TransformableObject& normalize();
        virtual Ionflux::GeoUtils::TransformableObject& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::TransformableObject& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::TransformableObject& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::TransformableObject& transformVI(const 
        Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4*
        image = 0);
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual Ionflux::GeoUtils::Range3 getBounds();
        virtual Ionflux::GeoUtils::TransformableObject& duplicate() = 0;
		static Ionflux::GeoUtils::TransformableObject* 
		upcast(Ionflux::ObjectBase::IFObject* other);
        virtual void setTransformMatrix(const Ionflux::GeoUtils::Matrix4& 
        newTransformMatrix);
        virtual Ionflux::GeoUtils::Matrix4 getTransformMatrix() const;
        virtual void setViewMatrix(const Ionflux::GeoUtils::Matrix4& 
        newViewMatrix);
        virtual Ionflux::GeoUtils::Matrix4 getViewMatrix() const;
        virtual void setImageMatrix(const Ionflux::GeoUtils::Matrix4& 
        newImageMatrix);
        virtual Ionflux::GeoUtils::Matrix4 getImageMatrix() const;
        virtual void setLastTransformMatrix(const 
        Ionflux::GeoUtils::Matrix4& newLastTransformMatrix);
        virtual Ionflux::GeoUtils::Matrix4 getLastTransformMatrix() const;
        virtual void setLastViewMatrix(const Ionflux::GeoUtils::Matrix4& 
        newLastViewMatrix);
        virtual Ionflux::GeoUtils::Matrix4 getLastViewMatrix() const;
        virtual void setLastImageMatrix(const Ionflux::GeoUtils::Matrix4& 
        newLastImageMatrix);
        virtual Ionflux::GeoUtils::Matrix4 getLastImageMatrix() const;
};

namespace XMLUtils
{

void getTransformableObject(const std::string& data, 
Ionflux::GeoUtils::TransformableObject& target);

}

}

}
