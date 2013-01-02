/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BoxBoundsItemCompareDistanceVec3.i  Box bounds item comparison function 
 * object: Distance to point (interface).
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
#include "geoutils/BoxBoundsItemCompareDistanceVec3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class BoxBoundsItemCompareDistanceVec3
: public Ionflux::GeoUtils::BoxBoundsItemCompare
{
    public:
        
        BoxBoundsItemCompareDistanceVec3();
		BoxBoundsItemCompareDistanceVec3(const Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3& other);
        BoxBoundsItemCompareDistanceVec3(const Ionflux::GeoUtils::Vector3& 
        initReference, bool initInvert = false);
        virtual ~BoxBoundsItemCompareDistanceVec3();
        virtual std::string getString() const;
        virtual bool compare(Ionflux::GeoUtils::BoxBoundsItem& b0, 
        Ionflux::GeoUtils::BoxBoundsItem& b1);
        static Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3* 
        create(const Ionflux::GeoUtils::Vector3& initReference, bool 
        initInvert = false);
		virtual Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3* copy() 
		const;
		static Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setReference(const Ionflux::GeoUtils::Vector3& 
        newReference);
        virtual Ionflux::GeoUtils::Vector3 getReference() const;
};

}

}
