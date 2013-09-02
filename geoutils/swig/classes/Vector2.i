/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector2.i                       Vector (2 elements) (interface).
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
#include "geoutils/Vector2.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Vector2ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vector2ClassInfo();
        virtual ~Vector2ClassInfo();
};

class Vector2
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::Vector2 ZERO;
		static const Ionflux::GeoUtils::Vector2 E_X;
		static const Ionflux::GeoUtils::Vector2 E_Y;
        
        Vector2();
		Vector2(const Ionflux::GeoUtils::Vector2& other);
        Vector2(double initX0, double initX1);
        Vector2(const Ionflux::ObjectBase::DoubleVector& initElements);
        virtual ~Vector2();
        virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
        newElements);
        virtual void setElements(double newX0, double newX1);
        virtual void getElements(Ionflux::ObjectBase::DoubleVector& target)
        const;
        virtual double getElement(int index) const;
        virtual void setElement(int index, double value);
        virtual bool eq(const Ionflux::GeoUtils::Vector2& other, double t =
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Vector2 flip() const;
        virtual double norm() const;
        virtual Ionflux::GeoUtils::Vector2 normalize() const;
        virtual Ionflux::GeoUtils::Vector2 project(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual Ionflux::GeoUtils::Vector2 ortho(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual Ionflux::GeoUtils::Vector2 swap() const;
        virtual bool operator==(const Ionflux::GeoUtils::Vector2& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Vector2& other) 
        const;
        virtual Ionflux::GeoUtils::Vector2 operator+(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual Ionflux::GeoUtils::Vector2 operator-(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual double operator*(const Ionflux::GeoUtils::Vector2& other) 
        const;
        virtual Ionflux::GeoUtils::Vector2 operator*(double c) const;
        virtual Ionflux::GeoUtils::Vector2 operator/(double c) const;
        virtual std::string getValueString() const;
        static Ionflux::GeoUtils::Vector2 axis(Ionflux::GeoUtils::AxisID 
        axisID);
		virtual Ionflux::GeoUtils::Vector2* copy() const;
		static Ionflux::GeoUtils::Vector2* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Vector2* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setX0(double newX0);
        virtual double getX0() const;
        virtual void setX1(double newX1);
        virtual double getX1() const;
};

Ionflux::GeoUtils::Vector2 operator*(double c, const 
Ionflux::GeoUtils::Vector2& v);

namespace XMLUtils
{

void getVector2(const std::string& data, Ionflux::GeoUtils::Vector2& 
target);

}

}

}
