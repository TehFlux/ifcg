/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector4.i                       Vector (4 elements) (interface).
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
#include "geoutils/Vector4.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Vector4ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vector4ClassInfo();
        virtual ~Vector4ClassInfo();
};

class Vector4
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::Vector4 ZERO;
		static const Ionflux::GeoUtils::Vector4 E_X;
		static const Ionflux::GeoUtils::Vector4 E_Y;
		static const Ionflux::GeoUtils::Vector4 E_Z;
		static const Ionflux::GeoUtils::Vector4 E_W;
		static const Ionflux::GeoUtils::Vector4 H_ZERO;
		static const Ionflux::GeoUtils::Vector4 H_E_X;
		static const Ionflux::GeoUtils::Vector4 H_E_Y;
		static const Ionflux::GeoUtils::Vector4 H_E_Z;
        
        Vector4();
		Vector4(const Ionflux::GeoUtils::Vector4& other);
        Vector4(double initX0, double initX1, double initX2, double 
        initX3);
        Vector4(const Ionflux::ObjectBase::DoubleVector& initElements);
        Vector4(const Ionflux::GeoUtils::Vector2& initElements, double 
        initZ = 0., double initW = 1.);
        Vector4(const Ionflux::GeoUtils::Vector3& initElements, double 
        initW = 1.);
        virtual ~Vector4();
        virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
        newElements);
        virtual void setElements(const Ionflux::GeoUtils::Vector2& 
        newElements);
        virtual void setElements(const Ionflux::GeoUtils::Vector3& 
        newElements);
        virtual void setV2(const Ionflux::GeoUtils::Vector2& newElements, 
        double newZ = 0., double newW = 1.);
        virtual void setV3(const Ionflux::GeoUtils::Vector3& newElements, 
        double newW = 1.);
        virtual void getElements(Ionflux::ObjectBase::DoubleVector& target)
        const;
        virtual double getElement(int index) const;
        virtual void setElement(int index, double value);
        virtual bool eq(const Ionflux::GeoUtils::Vector4& other, double t =
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Vector4 flip() const;
        virtual double norm() const;
        virtual Ionflux::GeoUtils::Vector4 normalize() const;
        virtual Ionflux::GeoUtils::Vector4 project(const 
        Ionflux::GeoUtils::Vector4& other) const;
        virtual Ionflux::GeoUtils::Vector4 ortho(const 
        Ionflux::GeoUtils::Vector4& other) const;
        virtual Ionflux::GeoUtils::Vector4 permute(int px, int py, int pz, 
        int pw) const;
        virtual Ionflux::GeoUtils::Vector4 permute(const 
        Ionflux::ObjectBase::IntVector& p) const;
        virtual bool operator==(const Ionflux::GeoUtils::Vector4& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Vector4& other) 
        const;
        virtual Ionflux::GeoUtils::Vector4 operator+(const 
        Ionflux::GeoUtils::Vector4& other) const;
        virtual Ionflux::GeoUtils::Vector4 operator-(const 
        Ionflux::GeoUtils::Vector4& other) const;
        virtual double operator*(const Ionflux::GeoUtils::Vector4& other) 
        const;
        virtual Ionflux::GeoUtils::Vector4 operator*(double c) const;
        virtual Ionflux::GeoUtils::Vector4 operator/(double c) const;
        virtual Ionflux::GeoUtils::Vector2 getV2() const;
        virtual Ionflux::GeoUtils::Vector3 getV3() const;
        virtual std::string getString() const;
        static Ionflux::GeoUtils::Vector4 axis(Ionflux::GeoUtils::AxisID 
        axisID);
        static Ionflux::GeoUtils::Vector4 axisH(Ionflux::GeoUtils::AxisID 
        axisID);
		virtual Ionflux::GeoUtils::Vector4* copy() const;
        virtual void setX0(double newX0);
        virtual double getX0() const;
        virtual void setX1(double newX1);
        virtual double getX1() const;
        virtual void setX2(double newX2);
        virtual double getX2() const;
        virtual void setX3(double newX3);
        virtual double getX3() const;
};

Ionflux::GeoUtils::Vector4 operator*(double c, const 
Ionflux::GeoUtils::Vector4& v);

}

}
