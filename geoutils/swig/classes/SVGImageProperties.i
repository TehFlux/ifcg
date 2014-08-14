/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SVGImageProperties.i            SVG image properties (interface).
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
#include "geoutils/SVGImageProperties.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class SVGImagePropertiesClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SVGImagePropertiesClassInfo();
        virtual ~SVGImagePropertiesClassInfo();
};

class SVGImageProperties
: public Ionflux::GeoUtils::ImageProperties
{
    public:
        
        SVGImageProperties();
		SVGImageProperties(const Ionflux::GeoUtils::SVGImageProperties& other);
        SVGImageProperties(Ionflux::GeoUtils::SVGShapeStyleSource* 
        initStyleSource, const std::string& initSVGTemplate = 
        Ionflux::GeoUtils::SVG_TEMPLATE);
        virtual ~SVGImageProperties();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::SVGImageProperties* copy() const;
		static Ionflux::GeoUtils::SVGImageProperties* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::SVGImageProperties* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setStyleSource(Ionflux::GeoUtils::SVGShapeStyleSource*
        newStyleSource);
        virtual Ionflux::GeoUtils::SVGShapeStyleSource* getStyleSource() 
        const;
        virtual void setSvgTemplate(const std::string& newSvgTemplate);
        virtual std::string getSvgTemplate() const;
};

}

}
