/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vertex.i                        Mesh vertex (interface).
 * =========================================================================

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
#include "geoutils/Vertex.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VertexClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VertexClassInfo();
        virtual ~VertexClassInfo();
};

class Vertex
: public Ionflux::GeoUtils::Vertex3
{
    public:
        
        Vertex();
		Vertex(const Ionflux::GeoUtils::Vertex& other);
        Vertex(double initX, double initY, double initZ, const 
        Ionflux::GeoUtils::Vector3& initNormal = 
        Ionflux::GeoUtils::Vector3::E_X);
        Vertex(const Ionflux::ObjectBase::DoubleVector& initCoords, const 
        Ionflux::GeoUtils::Vector3& initNormal = 
        Ionflux::GeoUtils::Vector3::E_X);
        Vertex(const Ionflux::GeoUtils::Vector3& initCoords, const 
        Ionflux::GeoUtils::Vector3& initNormal = 
        Ionflux::GeoUtils::Vector3::E_X);
        virtual ~Vertex();
        virtual Ionflux::GeoUtils::Vertex interpolate(const 
        Ionflux::GeoUtils::Vertex& other, double t, 
        Ionflux::GeoUtils::Interpolator* interpolator = 0) const;
        virtual Ionflux::GeoUtils::Vertex& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Vertex& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Vertex& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Vertex& normalize();
        virtual Ionflux::GeoUtils::Vertex& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Vertex& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Vertex& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Vertex& duplicate();
        virtual std::string getString() const;
        static Ionflux::GeoUtils::Vertex* create(double newX, double newY, 
        double newZ);
		virtual Ionflux::GeoUtils::Vertex* copy() const;
		static Ionflux::GeoUtils::Vertex* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Vertex* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setNormal(const Ionflux::GeoUtils::Vector3& 
        newNormal);
        virtual Ionflux::GeoUtils::Vector3 getNormal() const;
};

}

}
