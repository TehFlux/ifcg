/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vertex2.i                       Vertex (2D) (interface).
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
#include "geoutils/Vertex2.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Interpolator;
class Vertex2;

class Vertex2ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vertex2ClassInfo();
        virtual ~Vertex2ClassInfo();
};

class Vertex2
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::Vertex2 ORIGIN;
        
        Vertex2();
		Vertex2(const Ionflux::GeoUtils::Vertex2& other);
        Vertex2(double initX, double initY);
        Vertex2(const Ionflux::ObjectBase::DoubleVector& initCoords);
        Vertex2(const Ionflux::GeoUtils::Vector2& initCoords);
        virtual ~Vertex2();
        virtual void setCoords(const Ionflux::ObjectBase::DoubleVector& 
        newCoords);
        virtual void setCoords(const Ionflux::GeoUtils::Vector2& 
        newCoords);
        virtual void getCoords(Ionflux::ObjectBase::DoubleVector& target) 
        const;
        virtual void getCoords(Ionflux::GeoUtils::Vector2& target) const;
        virtual double getCoord(int index) const;
        virtual Ionflux::GeoUtils::Vector2 getVector() const;
        virtual void setCoord(int index, double value);
        virtual Ionflux::GeoUtils::Vertex2 interpolate(const 
        Ionflux::GeoUtils::Vertex2& other, double t, 
        Ionflux::GeoUtils::Interpolator* interpolator = 0) const;
        virtual bool eq(const Ionflux::GeoUtils::Vertex2& other, double t =
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool operator==(const Ionflux::GeoUtils::Vertex2& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Vertex2& other) 
        const;
        virtual std::string getString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Vertex2* copy() const;
		static Ionflux::GeoUtils::Vertex2* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Vertex2* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Vertex2* create(double initX, double initY, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Vertex2* create(const 
		Ionflux::ObjectBase::DoubleVector& initCoords, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Vertex2* create(const 
		Ionflux::GeoUtils::Vector2& initCoords, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setX(double newX);
        virtual double getX() const;
        virtual void setY(double newY);
        virtual double getY() const;
};

}

}
