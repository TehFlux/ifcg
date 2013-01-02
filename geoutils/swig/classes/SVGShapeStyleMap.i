/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SVGShapeStyleMap.i              SVG shape style map (interface).
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
#include "geoutils/SVGShapeStyleMap.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class SVGShapeStyleMapClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SVGShapeStyleMapClassInfo();
        virtual ~SVGShapeStyleMapClassInfo();
};

class SVGShapeStyleMap
: public Ionflux::GeoUtils::SVGShapeStyleSource
{
    public:
        
        SVGShapeStyleMap();
		SVGShapeStyleMap(const Ionflux::GeoUtils::SVGShapeStyleMap& other);
        virtual ~SVGShapeStyleMap();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::SVGShapeStyleMap* copy() const;
		static Ionflux::GeoUtils::SVGShapeStyleMap* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::SVGShapeStyleMap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual unsigned int getNumStyles() const;
        virtual Ionflux::GeoUtils::SVGShapeStyle* getStyle(const 
        std::string& elementKey) const;

        virtual std::map<std::string, Ionflux::GeoUtils::SVGShapeStyle*>& 
        getStyles();
        virtual void addStyle(const std::string& elementKey, 
        Ionflux::GeoUtils::SVGShapeStyle* addElement);        
        virtual void removeStyle(const std::string& elementKey);
		virtual void clearStyles();
};

}

}
