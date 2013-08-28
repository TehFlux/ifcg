/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SVGShapeStyleVectorSource.i     SVG shape style vector source 
 * (interface).
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
#include "geoutils/SVGShapeStyleVectorSource.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class SVGShapeStyleVectorSourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SVGShapeStyleVectorSourceClassInfo();
        virtual ~SVGShapeStyleVectorSourceClassInfo();
};

class SVGShapeStyleVectorSource
: public Ionflux::GeoUtils::SVGShapeStyleSource
{
    public:
        
        SVGShapeStyleVectorSource();
		SVGShapeStyleVectorSource(const Ionflux::GeoUtils::SVGShapeStyleVectorSource& other);
        virtual ~SVGShapeStyleVectorSource();
        virtual Ionflux::GeoUtils::SVGShapeStyle* getStyle(const 
        std::string& elementID);
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::SVGShapeStyleVectorSource* copy() const;
		static Ionflux::GeoUtils::SVGShapeStyleVectorSource* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::SVGShapeStyleVectorSource* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setCurrentStyle(unsigned int newCurrentStyle);
        virtual unsigned int getCurrentStyle() const;        
        virtual unsigned int getNumStyles() const;
        virtual Ionflux::GeoUtils::SVGShapeStyle* getStyle(unsigned int 
        elementIndex = 0) const;
		virtual int findStyle(Ionflux::GeoUtils::SVGShapeStyle* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::SVGShapeStyle*>& 
        getStyles();
        virtual void addStyle(Ionflux::GeoUtils::SVGShapeStyle* 
        addElement);        
        virtual void removeStyle(Ionflux::GeoUtils::SVGShapeStyle* 
        removeElement);
		virtual void removeStyleIndex(unsigned int removeIndex);
		virtual void clearStyles();
};

}

}
