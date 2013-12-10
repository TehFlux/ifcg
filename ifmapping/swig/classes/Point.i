/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Point.i                         Point (interface).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFMapping - Ionflux Mapping Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFMapping - Ionflux Mapping Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */
%{
#include "ifmapping/Point.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class PointClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PointClassInfo();
        virtual ~PointClassInfo();
};

class Point
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Mapping::Point ORIGIN;
		static const Ionflux::Mapping::Point DEFAULT_STD_DEV;
		static const Ionflux::Mapping::Point ONES;
        
        Point();
		Point(const Ionflux::Mapping::Point& other);
        Point(Ionflux::Mapping::MappingValue initX, 
        Ionflux::Mapping::MappingValue initY, 
        Ionflux::Mapping::MappingValue initZ);
        Point(const Ionflux::ObjectBase::DoubleVector& initCoords);
        virtual ~Point();
        virtual void setCoords(const Ionflux::ObjectBase::DoubleVector& 
        newCoords);
        virtual void getCoords(Ionflux::ObjectBase::DoubleVector& target) 
        const;
        virtual Ionflux::Mapping::MappingValue getCoord(int index) const;
        virtual void setCoord(int index, Ionflux::Mapping::MappingValue 
        value);
        virtual Ionflux::Mapping::Point interpolate(const 
        Ionflux::Mapping::Point& other, Ionflux::Mapping::MappingValue t) 
        const;
        virtual Ionflux::Mapping::Point operator+(const 
        Ionflux::Mapping::Point& other) const;
        virtual Ionflux::Mapping::Point operator-(const 
        Ionflux::Mapping::Point& other) const;
        virtual Ionflux::Mapping::Point operator*(const 
        Ionflux::Mapping::Point& other) const;
        virtual bool operator==(const Ionflux::Mapping::Point& other) 
        const;
        virtual bool eq(const Ionflux::Mapping::Point& other, double t = 
        Ionflux::Mapping::DEFAULT_TOLERANCE) const;
        virtual bool operator!=(const Ionflux::Mapping::Point& other) 
        const;
        static Ionflux::Mapping::Point getRandom();
        static Ionflux::Mapping::Point getRandomNorm(const 
        Ionflux::Mapping::Point& mean = Ionflux::Mapping::Point::ORIGIN, 
        const Ionflux::Mapping::Point& stdDev = 
        Ionflux::Mapping::Point::DEFAULT_STD_DEV);
        virtual std::string getSVGPathData(const 
        Ionflux::Mapping::CoordinateID imagePlaneNormal = 
        Ionflux::Mapping::C_Z) const;
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::Mapping::Point* copy() const;
		static Ionflux::Mapping::Point* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Point* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::Mapping::Point* create(Ionflux::Mapping::MappingValue 
		initX, Ionflux::Mapping::MappingValue initY, 
		Ionflux::Mapping::MappingValue initZ, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::Mapping::Point* create(const 
		Ionflux::ObjectBase::DoubleVector& initCoords, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setX(Ionflux::Mapping::MappingValue newX);
        virtual Ionflux::Mapping::MappingValue getX() const;
        virtual void setY(Ionflux::Mapping::MappingValue newY);
        virtual Ionflux::Mapping::MappingValue getY() const;
        virtual void setZ(Ionflux::Mapping::MappingValue newZ);
        virtual Ionflux::Mapping::MappingValue getZ() const;
};

}

}
