/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Hexagon2.i                      Hexagon (2D) (interface).
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
#include "geoutils/Hexagon2.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Hexagon2ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Hexagon2ClassInfo();
        virtual ~Hexagon2ClassInfo();
};

class Hexagon2
: public Ionflux::GeoUtils::Polygon2
{
    public:
        
        Hexagon2();
		Hexagon2(const Ionflux::GeoUtils::Hexagon2& other);
        Hexagon2(double initBaseLength);
        virtual ~Hexagon2();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::Hexagon2* copy() const;
        virtual void setBaseLength(double newBaseLength);
        virtual double getBaseLength() const;
};

}

}
