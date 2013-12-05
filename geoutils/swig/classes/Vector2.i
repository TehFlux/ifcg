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
: public Ionflux::GeoUtils::Vector
{
    public:
		static const unsigned int NUM_ELEMENTS;
		static const Ionflux::GeoUtils::Vector2 ZERO;
		static const Ionflux::GeoUtils::Vector2 E_X;
		static const Ionflux::GeoUtils::Vector2 E_Y;
        
        Vector2();
		Vector2(const Ionflux::GeoUtils::Vector2& other);
        Vector2(double initX0, double initX1);
        Vector2(const Ionflux::ObjectBase::DoubleVector& initElements0);
        virtual ~Vector2();
        virtual void setElements(double newX0, double newX1);
        virtual Ionflux::GeoUtils::Vector2 flip() const;
        virtual Ionflux::GeoUtils::Vector2 normalize() const;
        virtual Ionflux::GeoUtils::Vector2 project(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual Ionflux::GeoUtils::Vector2 ortho(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual Ionflux::GeoUtils::Vector2 swap() const;
        virtual Ionflux::GeoUtils::Vector2 multElements(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual Ionflux::GeoUtils::Vector2 operator+(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual Ionflux::GeoUtils::Vector2 operator-(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual Ionflux::GeoUtils::Vector2 operator*(double c) const;
        virtual double operator*(const Ionflux::GeoUtils::Vector2& other) 
        const;
        virtual Ionflux::GeoUtils::Vector2 operator/(double c) const;
        virtual unsigned int getNumElements() const;
        static Ionflux::GeoUtils::Vector2 axis(Ionflux::GeoUtils::AxisID 
        axisID);
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Vector2* copy() const;
		static Ionflux::GeoUtils::Vector2* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Vector2* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Vector2* create(double initX0, double initX1, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Vector2* create(const 
		Ionflux::ObjectBase::DoubleVector& initElements0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setX0(double newX0);
        virtual double getX0() const;
        virtual void setX1(double newX1);
        virtual double getX1() const;
};

Ionflux::GeoUtils::Vector2 operator*(double c, const 
Ionflux::GeoUtils::Vector2& v);

}

}
