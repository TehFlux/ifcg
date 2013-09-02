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
        virtual void zero();
        virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
        newElements);
        virtual void getElements(Ionflux::ObjectBase::DoubleVector& target)
        const;
        virtual double getElement(unsigned int index) const;
        virtual void setElement(unsigned int index, double value);
        virtual bool eq(const Ionflux::GeoUtils::Vector& other, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual double dot(const Ionflux::GeoUtils::Vector& other) const;
        virtual double norm() const;
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
        virtual bool operator==(const Ionflux::GeoUtils::Vector& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Vector& other) 
        const;
        virtual double operator*(const Ionflux::GeoUtils::Vector& other) 
        const;
        virtual std::string getValueString() const;
        virtual unsigned int getNumElements() const;
		virtual Ionflux::GeoUtils::Vector* copy() const;
		static Ionflux::GeoUtils::Vector* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Vector* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

namespace XMLUtils
{

void getVector(const std::string& data, Ionflux::GeoUtils::Vector& target);

}

}

}
