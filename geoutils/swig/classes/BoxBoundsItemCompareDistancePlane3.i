/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BoxBoundsItemCompareDistancePlane3.i  Box bounds item comparison 
 * function object: Distance to plane (interface).
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
#include "geoutils/BoxBoundsItemCompareDistancePlane3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class BoxBoundsItemCompareDistancePlane3
: public Ionflux::GeoUtils::BoxBoundsItemCompare
{
    public:
        
        BoxBoundsItemCompareDistancePlane3();
		BoxBoundsItemCompareDistancePlane3(const Ionflux::GeoUtils::BoxBoundsItemCompareDistancePlane3& other);
        BoxBoundsItemCompareDistancePlane3(const Ionflux::GeoUtils::Plane3&
        initReference, bool initInvert = false);
        virtual ~BoxBoundsItemCompareDistancePlane3();
        virtual std::string getString() const;
        virtual bool compare(Ionflux::GeoUtils::BoxBoundsItem& b0, 
        Ionflux::GeoUtils::BoxBoundsItem& b1);
        static Ionflux::GeoUtils::BoxBoundsItemCompareDistancePlane3* 
        create(const Ionflux::GeoUtils::Plane3& initReference, bool 
        initInvert = false);
		virtual Ionflux::GeoUtils::BoxBoundsItemCompareDistancePlane3* copy() 
		const;
		static Ionflux::GeoUtils::BoxBoundsItemCompareDistancePlane3* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::BoxBoundsItemCompareDistancePlane3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setReference(const Ionflux::GeoUtils::Plane3& 
        newReference);
        virtual Ionflux::GeoUtils::Plane3 getReference() const;
};

}

}
