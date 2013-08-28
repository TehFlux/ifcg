/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BoxBoundsItemCompareAxis.i      Box bounds item comparison function 
 * object: Axis coordinate (interface).
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
#include "geoutils/BoxBoundsItemCompareAxis.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class BoxBoundsItemCompareAxis
: public Ionflux::GeoUtils::BoxBoundsItemCompare
{
    public:
        
        BoxBoundsItemCompareAxis();
		BoxBoundsItemCompareAxis(const Ionflux::GeoUtils::BoxBoundsItemCompareAxis& other);
        BoxBoundsItemCompareAxis(Ionflux::GeoUtils::AxisID initAxis, bool 
        initInvert = true);
        virtual ~BoxBoundsItemCompareAxis();
        virtual std::string getString() const;
        virtual bool compare(Ionflux::GeoUtils::BoxBoundsItem& b0, 
        Ionflux::GeoUtils::BoxBoundsItem& b1);
        static Ionflux::GeoUtils::BoxBoundsItemCompareAxis* 
        create(Ionflux::GeoUtils::AxisID initAxis, bool initInvert = true);
		virtual Ionflux::GeoUtils::BoxBoundsItemCompareAxis* copy() const;
		static Ionflux::GeoUtils::BoxBoundsItemCompareAxis* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::BoxBoundsItemCompareAxis* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setAxis(Ionflux::GeoUtils::AxisID newAxis);
        virtual Ionflux::GeoUtils::AxisID getAxis() const;
};

}

}
