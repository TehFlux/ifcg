/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SVGShapeStyleSource.i           SVG shape style source (interface).
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
#include "geoutils/SVGShapeStyleSource.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class SVGShapeStyleSourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SVGShapeStyleSourceClassInfo();
        virtual ~SVGShapeStyleSourceClassInfo();
};

class SVGShapeStyleSource
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        SVGShapeStyleSource();
		SVGShapeStyleSource(const Ionflux::GeoUtils::SVGShapeStyleSource& other);
        virtual ~SVGShapeStyleSource();
        virtual Ionflux::GeoUtils::SVGShapeStyle* getStyle(const 
        std::string& elementID);
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::SVGShapeStyleSource* copy() const;
		static Ionflux::GeoUtils::SVGShapeStyleSource* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::SVGShapeStyleSource* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setDefaultStyle(const 
        Ionflux::GeoUtils::SVGShapeStyle& newDefaultStyle);
        virtual Ionflux::GeoUtils::SVGShapeStyle getDefaultStyle() const;
};

}

}
