/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SVG.i                           SVG (interface).
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
#include "geoutils/SVG.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class SVGClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SVGClassInfo();
        virtual ~SVGClassInfo();
};

class SVG
: public Ionflux::GeoUtils::TransformableObject
{
    public:
		static const Ionflux::GeoUtils::SVGType TYPE_UNDEFINED;
		static const Ionflux::GeoUtils::SVGType TYPE_FILE;
		static const Ionflux::GeoUtils::SVGType TYPE_DATA;
        
        SVG();
		SVG(const Ionflux::GeoUtils::SVG& other);
        SVG(const std::string& initSource, Ionflux::GeoUtils::SVGType 
        initType);
        virtual ~SVG();
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual Ionflux::GeoUtils::SVG& duplicate();
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::SVG* copy() const;
		static Ionflux::GeoUtils::SVG* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::SVG* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setSource(const std::string& newSource);
        virtual std::string getSource() const;
        virtual void setType(Ionflux::GeoUtils::SVGType newType);
        virtual Ionflux::GeoUtils::SVGType getType() const;
};

}

}
