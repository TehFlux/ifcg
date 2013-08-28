/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BoxBoundsItemCompare.i          Box bounds item comparison function 
 * object (interface).
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
#include "geoutils/BoxBoundsItemCompare.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class BoxBoundsItemCompareClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BoxBoundsItemCompareClassInfo();
        virtual ~BoxBoundsItemCompareClassInfo();
};

class BoxBoundsItemCompare
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        BoxBoundsItemCompare();
		BoxBoundsItemCompare(const Ionflux::GeoUtils::BoxBoundsItemCompare& other);
        BoxBoundsItemCompare(bool initInvert, 
        Ionflux::GeoUtils::BoxBoundsItemCompare* initTarget = 0);
        virtual ~BoxBoundsItemCompare();
        virtual std::string getString() const;
        virtual bool operator()(Ionflux::GeoUtils::BoxBoundsItem* b0, 
        Ionflux::GeoUtils::BoxBoundsItem* b1);
        virtual bool compare(Ionflux::GeoUtils::BoxBoundsItem& b0, 
        Ionflux::GeoUtils::BoxBoundsItem& b1);
		virtual Ionflux::GeoUtils::BoxBoundsItemCompare* copy() const;
		static Ionflux::GeoUtils::BoxBoundsItemCompare* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::BoxBoundsItemCompare* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setInvert(bool newInvert);
        virtual bool getInvert() const;
        virtual void setTarget(Ionflux::GeoUtils::BoxBoundsItemCompare* 
        newTarget);
        virtual Ionflux::GeoUtils::BoxBoundsItemCompare* getTarget() const;
};

}

}
