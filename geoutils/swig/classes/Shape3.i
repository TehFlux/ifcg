/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Shape3.i                        Shape (3D) (interface).
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
#include "geoutils/Shape3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Shape3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Shape3ClassInfo();
        virtual ~Shape3ClassInfo();
};

class Shape3
: virtual public Ionflux::GeoUtils::TransformableObject
{
    public:
        
        Shape3();
		Shape3(const Ionflux::GeoUtils::Shape3& other);
        virtual ~Shape3();
        virtual Ionflux::GeoUtils::Shape3& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Shape3& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Shape3& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Shape3& normalize();
        virtual Ionflux::GeoUtils::Shape3& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Shape3& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Shape3& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Shape3& transformVI(const 
        Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4*
        image = 0);
        virtual bool checkVertex(const Ionflux::GeoUtils::Vertex3& v, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual Ionflux::GeoUtils::Shape3& duplicate();
		virtual Ionflux::GeoUtils::Shape3* copy() const;
		static Ionflux::GeoUtils::Shape3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Shape3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

}

}
