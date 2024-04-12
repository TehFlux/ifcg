/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Split.i                         Axis split (interface).
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
#include "geoutils/Split.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Split;

class SplitClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SplitClassInfo();
        virtual ~SplitClassInfo();
};

class Split
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Split();
		Split(const Ionflux::GeoUtils::Split& other);
        Split(Ionflux::GeoUtils::AxisID initAxis, double initS = .5);
        virtual ~Split();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::Split* copy() const;
		static Ionflux::GeoUtils::Split* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Split* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setAxis(Ionflux::GeoUtils::AxisID newAxis);
        virtual Ionflux::GeoUtils::AxisID getAxis() const;
        virtual void setS(double newS);
        virtual double getS() const;
};

}

}
