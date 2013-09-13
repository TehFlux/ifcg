/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix4.i                       Matrix (4x4) (interface).
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
#include "geoutils/Matrix4.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Matrix4ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Matrix4ClassInfo();
        virtual ~Matrix4ClassInfo();
};

class Matrix4
: public Ionflux::GeoUtils::Matrix
{
    public:
		static const unsigned int NUM_ELEMENTS;
		static const unsigned int NUM_ROWS;
		static const unsigned int NUM_COLS;
		static const Ionflux::GeoUtils::Matrix4 ZERO;
		static const Ionflux::GeoUtils::Matrix4 UNIT;
        
        Matrix4();
		Matrix4(const Ionflux::GeoUtils::Matrix4& other);
        Matrix4(double initX00, double initX01, double initX02, double 
        initX03, double initX10, double initX11, double initX12, double 
        initX13, double initX20, double initX21, double initX22, double 
        initX23, double initX30, double initX31, double initX32, double 
        initX33);
        Matrix4(const Ionflux::ObjectBase::DoubleVector& initElements0);
        Matrix4(const Ionflux::GeoUtils::Matrix3& initElements0);
        virtual ~Matrix4();
        virtual void setElements(const Ionflux::GeoUtils::Matrix3& 
        newElements);
        virtual void setM3x3(const Ionflux::GeoUtils::Matrix3& newElements,
        double newX33 = 1., double newX03 = 0., double newX13 = 0., double 
        newX23 = 0., double newX30 = 0., double newX31 = 0., double newX32 
        = 0.);
        virtual Ionflux::GeoUtils::Matrix4 transpose() const;
        virtual Ionflux::GeoUtils::Matrix4 permuteColumns(int px, int py, 
        int pz, int pw) const;
        virtual Ionflux::GeoUtils::Matrix4 permuteColumns(const 
        Ionflux::ObjectBase::IntVector& p) const;
        virtual Ionflux::GeoUtils::Matrix4 permuteRows(int px, int py, int 
        pz, int pw) const;
        virtual Ionflux::GeoUtils::Matrix4 permuteRows(const 
        Ionflux::ObjectBase::IntVector& p) const;
        virtual Ionflux::GeoUtils::Vector4 solve(const 
        Ionflux::GeoUtils::Vector4& v) const;
        virtual Ionflux::GeoUtils::Matrix4 invert() const;
        virtual Ionflux::GeoUtils::Matrix4& multiplyLeft(const 
        Ionflux::GeoUtils::Matrix4& other);
        virtual Ionflux::GeoUtils::Matrix4& multiplyRight(const 
        Ionflux::GeoUtils::Matrix4& other);
        virtual Ionflux::GeoUtils::Matrix4 operator*(const 
        Ionflux::GeoUtils::Matrix4& other) const;
        virtual Ionflux::GeoUtils::Vector4 operator*(const 
        Ionflux::GeoUtils::Vector4& v) const;
        virtual Ionflux::GeoUtils::Matrix4 operator*(double c) const;
        virtual Ionflux::GeoUtils::Matrix4 operator/(double c) const;
        virtual Ionflux::GeoUtils::Matrix3 getM3x3() const;
        virtual unsigned int getNumElements() const;
        virtual unsigned int getNumRows() const;
        virtual unsigned int getNumCols() const;
        static Ionflux::GeoUtils::Matrix4 scale(double sx = 1., double sy =
        1., double sz = 1., double sw = 1.);
        static Ionflux::GeoUtils::Matrix4 scale(const 
        Ionflux::GeoUtils::Vector3& s, double sw = 1.);
        static Ionflux::GeoUtils::Matrix4 scale(const 
        Ionflux::GeoUtils::Vector4& s);
        static Ionflux::GeoUtils::Matrix4 translate(double tx = 0., double 
        ty = 0., double tz = 0.);
        static Ionflux::GeoUtils::Matrix4 translate(const 
        Ionflux::GeoUtils::Vector3& t);
        static Ionflux::GeoUtils::Matrix4 rotate(double phi = 0., 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        static Ionflux::GeoUtils::Matrix4 
        swapAxes(Ionflux::GeoUtils::AxisID x = Ionflux::GeoUtils::AXIS_X, 
        Ionflux::GeoUtils::AxisID y = Ionflux::GeoUtils::AXIS_Y, 
        Ionflux::GeoUtils::AxisID z = Ionflux::GeoUtils::AXIS_Z, 
        Ionflux::GeoUtils::AxisID w = Ionflux::GeoUtils::AXIS_W);
        static Ionflux::GeoUtils::Matrix4 perspective(double d = 1., 
        Ionflux::GeoUtils::AxisID depthAxis = Ionflux::GeoUtils::AXIS_Y);
        static Ionflux::GeoUtils::Matrix4 imageTransform(double screenWidth
        = 1.33, double screenHeight = 1., double imageWidth = 800., double 
        imageHeight = 600., Ionflux::GeoUtils::AxisID upAxis = 
        Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID depthAxis = 
        Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID horizonAxis = 
        Ionflux::GeoUtils::AXIS_X);
		virtual Ionflux::GeoUtils::Matrix4* copy() const;
		static Ionflux::GeoUtils::Matrix4* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Matrix4* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Matrix4* create(double initX00, double initX01,
		double initX02, double initX03, double initX10, double initX11, double 
		initX12, double initX13, double initX20, double initX21, double initX22, 
		double initX23, double initX30, double initX31, double initX32, double 
		initX33, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Matrix4* create(const 
		Ionflux::ObjectBase::DoubleVector& initElements0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Matrix4* create(const 
		Ionflux::GeoUtils::Matrix3& initElements0, Ionflux::ObjectBase::IFObject*
		parentObject = 0);
        virtual void setR0(const Ionflux::GeoUtils::Vector4& newR0);
        virtual Ionflux::GeoUtils::Vector4 getR0() const;
        virtual void setR1(const Ionflux::GeoUtils::Vector4& newR1);
        virtual Ionflux::GeoUtils::Vector4 getR1() const;
        virtual void setR2(const Ionflux::GeoUtils::Vector4& newR2);
        virtual Ionflux::GeoUtils::Vector4 getR2() const;
        virtual void setR3(const Ionflux::GeoUtils::Vector4& newR3);
        virtual Ionflux::GeoUtils::Vector4 getR3() const;
        virtual void setC0(const Ionflux::GeoUtils::Vector4& newC0);
        virtual Ionflux::GeoUtils::Vector4 getC0() const;
        virtual void setC1(const Ionflux::GeoUtils::Vector4& newC1);
        virtual Ionflux::GeoUtils::Vector4 getC1() const;
        virtual void setC2(const Ionflux::GeoUtils::Vector4& newC2);
        virtual Ionflux::GeoUtils::Vector4 getC2() const;
        virtual void setC3(const Ionflux::GeoUtils::Vector4& newC3);
        virtual Ionflux::GeoUtils::Vector4 getC3() const;
};

Ionflux::GeoUtils::Matrix4 operator*(double c, const 
Ionflux::GeoUtils::Matrix4& m);

namespace XMLUtils
{

void getMatrix4(const std::string& data, Ionflux::GeoUtils::Matrix4& 
target);

}

}

}
