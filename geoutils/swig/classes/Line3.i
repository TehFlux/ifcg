/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Line3.i                         Line (3D) (interface).
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
#include "geoutils/Line3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Line3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Line3ClassInfo();
        virtual ~Line3ClassInfo();
};

class Line3
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::Line3 X;
		static const Ionflux::GeoUtils::Line3 Y;
		static const Ionflux::GeoUtils::Line3 Z;
        
        Line3();
		Line3(const Ionflux::GeoUtils::Line3& other);
        Line3(const Ionflux::GeoUtils::Vector3& initP, const 
        Ionflux::GeoUtils::Vector3& initU);
        virtual ~Line3();
        virtual bool intersect(const Ionflux::GeoUtils::Line3& other, 
        Ionflux::GeoUtils::Vector3& result) const;
        virtual bool intersect(const Ionflux::GeoUtils::Plane3& plane, 
        Ionflux::GeoUtils::Vector3& result) const;
        virtual bool intersectionInPoly(const Ionflux::GeoUtils::Polygon3& 
        poly, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual bool operator==(const Ionflux::GeoUtils::Line3& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Line3& other) 
        const;
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::Line3* copy() const;
		static Ionflux::GeoUtils::Line3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Line3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setP(const Ionflux::GeoUtils::Vector3& newP);
        virtual Ionflux::GeoUtils::Vector3 getP() const;
        virtual void setU(const Ionflux::GeoUtils::Vector3& newU);
        virtual Ionflux::GeoUtils::Vector3 getU() const;
};

}

}
