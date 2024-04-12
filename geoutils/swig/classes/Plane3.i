/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Plane3.i                        Plane (3D) (interface).
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
#include "geoutils/Plane3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Plane3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Plane3ClassInfo();
        virtual ~Plane3ClassInfo();
};

class Plane3
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Plane3();
		Plane3(const Ionflux::GeoUtils::Plane3& other);
        Plane3(const Ionflux::GeoUtils::Vector3& initP, const 
        Ionflux::GeoUtils::Vector3& initU, const 
        Ionflux::GeoUtils::Vector3& initV);
        virtual ~Plane3();
        virtual Ionflux::GeoUtils::Vector3 getTangent() const;
        virtual Ionflux::GeoUtils::Vector3 getBinormal() const;
        virtual Ionflux::GeoUtils::Vector3 getNormal() const;
        virtual Ionflux::GeoUtils::Matrix3 getTangentBase() const;
        virtual bool operator==(const Ionflux::GeoUtils::Plane3& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Plane3& other) 
        const;
        virtual std::string getValueString() const;
        static const Ionflux::GeoUtils::Plane3& planeXY();
        static const Ionflux::GeoUtils::Plane3& planeYZ();
        static const Ionflux::GeoUtils::Plane3& planeZX();
        static Ionflux::GeoUtils::Plane3 createFromNormal(const 
        Ionflux::GeoUtils::Vector3& n, const Ionflux::GeoUtils::Vector3& t 
        = Ionflux::GeoUtils::Vector3::E_X, const 
        Ionflux::GeoUtils::Vector3& p = Ionflux::GeoUtils::Vector3::ZERO);
		virtual Ionflux::GeoUtils::Plane3* copy() const;
		static Ionflux::GeoUtils::Plane3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Plane3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setP(const Ionflux::GeoUtils::Vector3& newP);
        virtual Ionflux::GeoUtils::Vector3 getP() const;
        virtual void setU(const Ionflux::GeoUtils::Vector3& newU);
        virtual Ionflux::GeoUtils::Vector3 getU() const;
        virtual void setV(const Ionflux::GeoUtils::Vector3& newV);
        virtual Ionflux::GeoUtils::Vector3 getV() const;
};

}

}
