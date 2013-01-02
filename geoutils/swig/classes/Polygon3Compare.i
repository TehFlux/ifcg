/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polygon3Compare.i               Polygon comparison function object 
 * (interface).
 * =========================================================================

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
#include "geoutils/Polygon3Compare.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Polygon3CompareClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Polygon3CompareClassInfo();
        virtual ~Polygon3CompareClassInfo();
};

class Polygon3Compare
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        Polygon3Compare();
		Polygon3Compare(const Ionflux::GeoUtils::Polygon3Compare& other);
        Polygon3Compare(bool initInvert, 
        Ionflux::GeoUtils::Polygon3Compare* initTarget = 0);
        virtual ~Polygon3Compare();
        virtual std::string getString() const;
        virtual bool operator()(Ionflux::GeoUtils::Polygon3* p0, 
        Ionflux::GeoUtils::Polygon3* p1);
        virtual bool compare(Ionflux::GeoUtils::Polygon3& p0, 
        Ionflux::GeoUtils::Polygon3& p1);
		virtual Ionflux::GeoUtils::Polygon3Compare* copy() const;
		static Ionflux::GeoUtils::Polygon3Compare* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Polygon3Compare* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setInvert(bool newInvert);
        virtual bool getInvert() const;
        virtual void setTarget(Ionflux::GeoUtils::Polygon3Compare* 
        newTarget);
        virtual Ionflux::GeoUtils::Polygon3Compare* getTarget() const;
};

}

}
