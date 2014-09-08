/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector.i                        Vector (interface).
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
#include "geoutils/Vector.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VectorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VectorClassInfo();
        virtual ~VectorClassInfo();
};

class Vector
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const unsigned int NUM_ELEMENTS;
        
        Vector();
		Vector(const Ionflux::GeoUtils::Vector& other);
        virtual ~Vector();
        virtual void cleanup();
        virtual void zero();
        virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
        newElements);
        virtual void setElements(const Ionflux::GeoUtils::Vector& other, 
        unsigned int sourceOffset = 0, unsigned int targetOffset = 0);
        virtual void setElements(double x0, double x1 = 0., double x2 = 0.,
        double x3 = 0., double x4 = 0., double x5 = 0., double x6 = 0., 
        double x7 = 0., double x8 = 0., double x9 = 0., double x10 = 0., 
        double x11 = 0., double x12 = 0.);
        virtual void getElements(Ionflux::ObjectBase::DoubleVector& target)
        const;
        virtual double getElement(unsigned int index) const;
        virtual void setElement(unsigned int index, double value);
        virtual bool eq(const Ionflux::GeoUtils::Vector& other, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual double dot(const Ionflux::GeoUtils::Vector& other) const;
        virtual double norm() const;
        virtual double length() const;
        virtual Ionflux::GeoUtils::Vector& normalizeIP();
        virtual Ionflux::GeoUtils::Vector& multiplyIP(double c);
        virtual Ionflux::GeoUtils::Vector& divideIP(double c);
        virtual Ionflux::GeoUtils::Vector& flipIP();
        virtual Ionflux::GeoUtils::Vector& multiplyIP(const 
        Ionflux::GeoUtils::Vector& other);
        virtual Ionflux::GeoUtils::Vector& subtractIP(const 
        Ionflux::GeoUtils::Vector& other);
        virtual Ionflux::GeoUtils::Vector& addIP(const 
        Ionflux::GeoUtils::Vector& other);
        virtual Ionflux::GeoUtils::Vector& roundIP(unsigned int numDecimals
        = 0);
        virtual bool operator==(const Ionflux::GeoUtils::Vector& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Vector& other) 
        const;
        virtual double operator*(const Ionflux::GeoUtils::Vector& other) 
        const;
        virtual unsigned int getNumElements() const;
        virtual void getElementSigns(Ionflux::ObjectBase::IntVector& 
        target) const;
        virtual void getElementSigns(Ionflux::GeoUtils::Vector& target) 
        const;
        virtual std::string getValueStringF(unsigned int fieldWidth = 5, 
        unsigned int precision = 3, const std::string& colSep = " ") const;
        virtual std::string getXMLAttributeDataValueString() const;
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Vector* copy() const;
		static Ionflux::GeoUtils::Vector* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Vector* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}
