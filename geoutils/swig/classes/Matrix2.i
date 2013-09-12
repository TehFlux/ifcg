/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix2.i                       Matrix (2x2) (interface).
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
#include "geoutils/Matrix2.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Matrix2ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Matrix2ClassInfo();
        virtual ~Matrix2ClassInfo();
};

class Matrix2
: public Ionflux::GeoUtils::Matrix
{
    public:
		static const unsigned int NUM_ELEMENTS;
		static const unsigned int NUM_ROWS;
		static const unsigned int NUM_COLS;
		static const Ionflux::GeoUtils::Matrix2 ZERO;
		static const Ionflux::GeoUtils::Matrix2 UNIT;
        
        Matrix2();
		Matrix2(const Ionflux::GeoUtils::Matrix2& other);
        Matrix2(double initX00, double initX01, double initX10, double 
        initX11);
        Matrix2(const Ionflux::ObjectBase::DoubleVector& initElements0);
        virtual ~Matrix2();
        virtual Ionflux::GeoUtils::Matrix2 transpose() const;
        virtual Ionflux::GeoUtils::Matrix2 swapColumns() const;
        virtual Ionflux::GeoUtils::Vector2 solve(const 
        Ionflux::GeoUtils::Vector2& v) const;
        virtual Ionflux::GeoUtils::Matrix2 invert() const;
        virtual Ionflux::GeoUtils::Matrix2 operator*(const 
        Ionflux::GeoUtils::Matrix2& other) const;
        virtual Ionflux::GeoUtils::Vector2 operator*(const 
        Ionflux::GeoUtils::Vector2& v) const;
        virtual Ionflux::GeoUtils::Matrix2 operator*(double c) const;
        virtual Ionflux::GeoUtils::Matrix2 operator/(double c) const;
        virtual unsigned int getNumElements() const;
        virtual unsigned int getNumRows() const;
        virtual unsigned int getNumCols() const;
        static Ionflux::GeoUtils::Matrix2 scale(double sx = 1., double sy =
        1.);
        static Ionflux::GeoUtils::Matrix2 rotate(double phi = 0.);
		virtual Ionflux::GeoUtils::Matrix2* copy() const;
		static Ionflux::GeoUtils::Matrix2* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Matrix2* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Matrix2* create(double initX00, double initX01,
		double initX10, double initX11, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Matrix2* create(const 
		Ionflux::ObjectBase::DoubleVector& initElements0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setR0(const Ionflux::GeoUtils::Vector2& newR0);
        virtual Ionflux::GeoUtils::Vector2 getR0() const;
        virtual void setR1(const Ionflux::GeoUtils::Vector2& newR1);
        virtual Ionflux::GeoUtils::Vector2 getR1() const;
        virtual void setC0(const Ionflux::GeoUtils::Vector2& newC0);
        virtual Ionflux::GeoUtils::Vector2 getC0() const;
        virtual void setC1(const Ionflux::GeoUtils::Vector2& newC1);
        virtual Ionflux::GeoUtils::Vector2 getC1() const;
};

Ionflux::GeoUtils::Matrix2 operator*(double c, const 
Ionflux::GeoUtils::Matrix2& m);

namespace XMLUtils
{

void getMatrix2(const std::string& data, Ionflux::GeoUtils::Matrix2& 
target);

}

}

}
