/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * VectorN.i                       Vector (N-D) (interface).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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
#include "geoutils/VectorN.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VectorNClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VectorNClassInfo();
        virtual ~VectorNClassInfo();
};

class VectorN
: public Ionflux::GeoUtils::Vector
{
    public:
        
        VectorN();
		VectorN(const Ionflux::GeoUtils::VectorN& other);
        VectorN(unsigned int initNumElements);
        VectorN(unsigned int initNumElements, double x0, double x1 = 0., 
        double x2 = 0., double x3 = 0., double x4 = 0., double x5 = 0., 
        double x6 = 0., double x7 = 0., double x8 = 0., double x9 = 0., 
        double x10 = 0., double x11 = 0., double x12 = 0.);
        virtual ~VectorN();
        virtual Ionflux::GeoUtils::VectorN interpolate(const 
        Ionflux::GeoUtils::VectorN& other, double t = 0.5, 
        Ionflux::GeoUtils::Interpolator* interp = 0);
        virtual Ionflux::GeoUtils::VectorN operator+(const 
        Ionflux::GeoUtils::VectorN& other) const;
        virtual Ionflux::GeoUtils::VectorN operator-(const 
        Ionflux::GeoUtils::VectorN& other) const;
        virtual Ionflux::GeoUtils::VectorN operator*(double c) const;
        virtual double operator*(const Ionflux::GeoUtils::VectorN& other) 
        const;
        virtual Ionflux::GeoUtils::VectorN operator/(double c) const;
        static Ionflux::GeoUtils::VectorN* sample(const 
        Ionflux::Mapping::Mapping& mapping, unsigned int numPoints, double 
        t0 = 0., double t1 = 1.);
        static Ionflux::GeoUtils::VectorN* linear(unsigned int numPoints, 
        double t0 = 0., double t1 = 1., Ionflux::Mapping::MappingValue 
        lower = 0., Ionflux::Mapping::MappingValue upper = 1., 
        Ionflux::Mapping::MappingValue scale = 1., 
        Ionflux::Mapping::MappingValue offset = 0.);
        static Ionflux::GeoUtils::VectorN* cubic(unsigned int numPoints, 
        double t0 = 0., double t1 = 1., Ionflux::Mapping::MappingValue 
        lower = 0., Ionflux::Mapping::MappingValue upper = 1.);
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::VectorN* copy() const;
		static Ionflux::GeoUtils::VectorN* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::VectorN* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::VectorN* create(unsigned int initNumElements, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::VectorN* create(unsigned int initNumElements, 
		double x0, double x1 = 0., double x2 = 0., double x3 = 0., double x4 = 
		0., double x5 = 0., double x6 = 0., double x7 = 0., double x8 = 0., 
		double x9 = 0., double x10 = 0., double x11 = 0., double x12 = 0., 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setNumElements(unsigned int newNumElements);
        virtual unsigned int getNumElements() const;
};

Ionflux::GeoUtils::VectorN operator*(double c, const 
Ionflux::GeoUtils::VectorN& v);

}

}
