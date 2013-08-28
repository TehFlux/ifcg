/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix3.i                       Matrix (3x3) (interface).
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
#include "geoutils/Matrix3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Matrix3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Matrix3ClassInfo();
        virtual ~Matrix3ClassInfo();
};

class Matrix3
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::Matrix3 ZERO;
		static const Ionflux::GeoUtils::Matrix3 UNIT;
        
        Matrix3();
		Matrix3(const Ionflux::GeoUtils::Matrix3& other);
        Matrix3(double initX00, double initX01, double initX02, double 
        initX10, double initX11, double initX12, double initX20, double 
        initX21, double initX22);
        Matrix3(const Ionflux::ObjectBase::DoubleVector& initElements);
        virtual ~Matrix3();
        virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
        newElements);
        virtual void getElements(Ionflux::ObjectBase::DoubleVector& target)
        const;
        virtual double getElement(int row, int column) const;
        virtual void setElement(int row, int column, double value);
        virtual bool eq(const Ionflux::GeoUtils::Matrix3& other, double t =
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Matrix3 transpose() const;
        virtual Ionflux::GeoUtils::Matrix3 permuteColumns(int px, int py, 
        int pz) const;
        virtual Ionflux::GeoUtils::Matrix3 permuteColumns(const 
        Ionflux::ObjectBase::IntVector& p) const;
        virtual Ionflux::GeoUtils::Vector3 solve(const 
        Ionflux::GeoUtils::Vector3& v) const;
        virtual Ionflux::GeoUtils::Matrix3 invert() const;
        virtual bool operator==(const Ionflux::GeoUtils::Matrix3& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Matrix3& other) 
        const;
        virtual Ionflux::GeoUtils::Matrix3 operator*(const 
        Ionflux::GeoUtils::Matrix3& other) const;
        virtual Ionflux::GeoUtils::Vector3 operator*(const 
        Ionflux::GeoUtils::Vector3& v) const;
        virtual Ionflux::GeoUtils::Matrix3 operator*(double c) const;
        virtual Ionflux::GeoUtils::Matrix3 operator/(double c) const;
        virtual void svd(Ionflux::GeoUtils::Matrix3& u, 
        Ionflux::GeoUtils::Vector3& s, Ionflux::GeoUtils::Matrix3& v) 
        const;
        virtual std::string getString() const;
        static Ionflux::GeoUtils::Matrix3 scale(double sx = 1., double sy =
        1., double sz = 1.);
        static Ionflux::GeoUtils::Matrix3 translate(double tx = 0., double 
        ty = 0.);
        static Ionflux::GeoUtils::Matrix3 rotate(double phi = 0., 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
		virtual Ionflux::GeoUtils::Matrix3* copy() const;
        virtual void setR0(const Ionflux::GeoUtils::Vector3& newR0);
        virtual Ionflux::GeoUtils::Vector3 getR0() const;
        virtual void setR1(const Ionflux::GeoUtils::Vector3& newR1);
        virtual Ionflux::GeoUtils::Vector3 getR1() const;
        virtual void setR2(const Ionflux::GeoUtils::Vector3& newR2);
        virtual Ionflux::GeoUtils::Vector3 getR2() const;
        virtual void setC0(const Ionflux::GeoUtils::Vector3& newC0);
        virtual Ionflux::GeoUtils::Vector3 getC0() const;
        virtual void setC1(const Ionflux::GeoUtils::Vector3& newC1);
        virtual Ionflux::GeoUtils::Vector3 getC1() const;
        virtual void setC2(const Ionflux::GeoUtils::Vector3& newC2);
        virtual Ionflux::GeoUtils::Vector3 getC2() const;
};

Ionflux::GeoUtils::Matrix3 operator*(double c, const 
Ionflux::GeoUtils::Matrix3& m);

}

}
