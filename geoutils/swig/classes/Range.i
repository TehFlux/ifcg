/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Range.i                         Range of values (interface).
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
#include "geoutils/Range.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class RangeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        RangeClassInfo();
        virtual ~RangeClassInfo();
};

class Range
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Range();
		Range(const Ionflux::GeoUtils::Range& other);
        Range(double initRMin, double initRMax);
        virtual ~Range();
        virtual void extend(double value);
        virtual double getCenter() const;
        virtual double getRadius() const;
        virtual double getExtent() const;
        virtual double getValue(double s) const;
        virtual double getParam(double v) const;
        virtual double clamp(double value) const;
        virtual double getClampedValue(double s) const;
        virtual Ionflux::GeoUtils::RangeCompResult compare(const 
        Ionflux::GeoUtils::Range& other, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual bool isInRange(double v, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual void setBounds(double rMinNew, double rMaxNew);
        virtual bool operator==(const Ionflux::GeoUtils::Range& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Range& other) 
        const;
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::Range* copy() const;
		static Ionflux::GeoUtils::Range* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Range* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setRMin(double newRMin);
        virtual double getRMin() const;
        virtual void setRMax(double newRMax);
        virtual double getRMax() const;
        virtual void setBounds(const Ionflux::ObjectBase::DoubleVector& 
        newBounds);
        virtual Ionflux::ObjectBase::DoubleVector getBounds() const;
};

}

}
