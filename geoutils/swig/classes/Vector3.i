/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector3.i                       Vector (3 elements) (interface).
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
#include "geoutils/Vector3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Plane3;
class Range;

class Vector3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vector3ClassInfo();
        virtual ~Vector3ClassInfo();
};

class Vector3
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::Vector3 ZERO;
		static const Ionflux::GeoUtils::Vector3 E_X;
		static const Ionflux::GeoUtils::Vector3 E_Y;
		static const Ionflux::GeoUtils::Vector3 E_Z;
		static const Ionflux::GeoUtils::Vector3 E_SUM;
        
        Vector3();
		Vector3(const Ionflux::GeoUtils::Vector3& other);
        Vector3(double initX0, double initX1, double initX2);
        Vector3(const Ionflux::ObjectBase::DoubleVector& initElements);
        Vector3(const Ionflux::GeoUtils::Vector2& initElements, double 
        initZ = 1.);
        virtual ~Vector3();
        virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
        newElements);
        virtual void setElements(double newX0, double newX1, double newX2);
        virtual void setElements(const Ionflux::GeoUtils::Vector2& 
        newElements);
        virtual void setV2(const Ionflux::GeoUtils::Vector2& newElements, 
        double newZ = 1.);
        virtual void getElements(Ionflux::ObjectBase::DoubleVector& target)
        const;
        virtual double getElement(int index) const;
        virtual void setElement(int index, double value);
        virtual bool eq(const Ionflux::GeoUtils::Vector3& other, double t =
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Vector3 flip() const;
        virtual double norm() const;
        virtual Ionflux::GeoUtils::Vector3 normalize() const;
        virtual Ionflux::GeoUtils::Vector3 cross(const 
        Ionflux::GeoUtils::Vector3& other) const;
        virtual Ionflux::GeoUtils::Vector3 project(const 
        Ionflux::GeoUtils::Vector3& other) const;
        virtual Ionflux::GeoUtils::Vector3 ortho(const 
        Ionflux::GeoUtils::Vector3& other) const;
        virtual Ionflux::GeoUtils::Vector3 ortho() const;
        virtual double angle(const Ionflux::GeoUtils::Vector3& other) 
        const;
        virtual Ionflux::GeoUtils::Vector3 permute(int px, int py, int pz) 
        const;
        virtual Ionflux::GeoUtils::Vector3 permute(const 
        Ionflux::ObjectBase::IntVector& p) const;
        virtual Ionflux::GeoUtils::Vector3 multElements(const 
        Ionflux::GeoUtils::Vector3& other) const;
        virtual Ionflux::GeoUtils::Vector3 interpolate(const 
        Ionflux::GeoUtils::Vector3& other, double t) const;
        virtual Ionflux::GeoUtils::AxisTriple getAxisOrder() const;
        virtual bool operator==(const Ionflux::GeoUtils::Vector3& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Vector3& other) 
        const;
        virtual Ionflux::GeoUtils::Vector3 operator+(const 
        Ionflux::GeoUtils::Vector3& other) const;
        virtual Ionflux::GeoUtils::Vector3 operator-(const 
        Ionflux::GeoUtils::Vector3& other) const;
        virtual double operator*(const Ionflux::GeoUtils::Vector3& other) 
        const;
        virtual Ionflux::GeoUtils::Vector3 operator*(double c) const;
        virtual Ionflux::GeoUtils::Vector3 operator/(double c) const;
        virtual Ionflux::GeoUtils::Vector3& operator+=(const 
        Ionflux::GeoUtils::Vector3& other);
        virtual Ionflux::GeoUtils::Vector3& operator-=(const 
        Ionflux::GeoUtils::Vector3& other);
        virtual int findElement(double v, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual int findMatchingElements(const Ionflux::GeoUtils::Vector3& 
        other, Ionflux::ObjectBase::DoubleVector& target, const 
        Ionflux::GeoUtils::Range* range = 0, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Vector2 getV2() const;
        virtual double distanceToPlane(const Ionflux::GeoUtils::Plane3& 
        plane) const;
        virtual std::string getValueString() const;
        static Ionflux::GeoUtils::Vector3 axis(Ionflux::GeoUtils::AxisID 
        axisID);
		virtual Ionflux::GeoUtils::Vector3* copy() const;
		static Ionflux::GeoUtils::Vector3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Vector3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setX0(double newX0);
        virtual double getX0() const;
        virtual void setX1(double newX1);
        virtual double getX1() const;
        virtual void setX2(double newX2);
        virtual double getX2() const;
};

Ionflux::GeoUtils::Vector3 operator*(double c, const 
Ionflux::GeoUtils::Vector3& v);

namespace XMLUtils
{

void getVector3(const std::string& data, Ionflux::GeoUtils::Vector3& 
target);

}

}

}
