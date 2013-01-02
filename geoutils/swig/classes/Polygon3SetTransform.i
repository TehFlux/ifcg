/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polygon3SetTransform.i          Polygon set transformation (interface).
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
#include "geoutils/Polygon3SetTransform.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Polygon3SetTransformClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Polygon3SetTransformClassInfo();
        virtual ~Polygon3SetTransformClassInfo();
};

class Polygon3SetTransform
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        Polygon3SetTransform();
		Polygon3SetTransform(const Ionflux::GeoUtils::Polygon3SetTransform& other);
        virtual ~Polygon3SetTransform();
        virtual Ionflux::GeoUtils::Polygon3Set* 
        transform(Ionflux::GeoUtils::Polygon3Set* source, 
        Ionflux::GeoUtils::Polygon3Set* target = 0, bool replace = false);
        virtual std::string getString() const;
        virtual Ionflux::GeoUtils::Polygon3Set* 
        transformAdd(Ionflux::GeoUtils::Polygon3Set* source, 
        Ionflux::GeoUtils::Polygon3Set* target) = 0;
};

}

}
