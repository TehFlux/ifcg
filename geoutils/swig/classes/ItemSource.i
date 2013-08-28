/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ItemSource.i                    Source for items (interface).
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
#include "geoutils/ItemSource.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class BoxBoundsItem;

class ItemSourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ItemSourceClassInfo();
        virtual ~ItemSourceClassInfo();
};

class ItemSource
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        ItemSource();
		ItemSource(const Ionflux::GeoUtils::ItemSource& other);
        virtual ~ItemSource();
        virtual Ionflux::GeoUtils::BoxBoundsItem* getItem(const 
        std::string& itemID) = 0;
        virtual std::string getString() const;
};

}

}
