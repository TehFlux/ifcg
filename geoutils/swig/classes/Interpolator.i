/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Interpolator.i                  Interpolator (interface).
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
#include "geoutils/Interpolator.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class InterpolatorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        InterpolatorClassInfo();
        virtual ~InterpolatorClassInfo();
};

class Interpolator
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Interpolator();
		Interpolator(const Ionflux::GeoUtils::Interpolator& other);
        Interpolator(double initV0, double initV1);
        Interpolator(const Ionflux::ObjectBase::DoubleVector& initValues);
        virtual ~Interpolator();
        virtual void setValues(double newV0, double newV1);
        virtual void setValues(const Ionflux::ObjectBase::DoubleVector& 
        newValues);
        virtual void getValues(Ionflux::ObjectBase::DoubleVector& target) 
        const;
        virtual double getValue(int index) const;
        virtual Ionflux::ObjectBase::DoubleVector getVector() const;
        virtual void setValue(int index, int value);
        virtual bool operator==(const Ionflux::GeoUtils::Interpolator& 
        other) const;
        virtual bool operator!=(const Ionflux::GeoUtils::Interpolator& 
        other) const;
        virtual double interpolate(double t = 0.5) const = 0;
        virtual double operator()(double t = 0.5) const;
        virtual std::string getString() const;
        virtual void setV0(double newV0);
        virtual double getV0() const;
        virtual void setV1(double newV1);
        virtual double getV1() const;
};

}

}
