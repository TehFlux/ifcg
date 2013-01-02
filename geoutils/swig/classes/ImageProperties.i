/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImageProperties.i               Image properties (interface).
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
#include "geoutils/ImageProperties.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class ImagePropertiesClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ImagePropertiesClassInfo();
        virtual ~ImagePropertiesClassInfo();
};

class ImageProperties
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
		static const unsigned int DEFAULT_WIDTH;
		static const unsigned int DEFAULT_HEIGHT;
		static const Ionflux::GeoUtils::Vector2 DEFAULT_ORIGIN;
        
        ImageProperties();
		ImageProperties(const Ionflux::GeoUtils::ImageProperties& other);
        virtual ~ImageProperties();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::ImageProperties* copy() const;
		static Ionflux::GeoUtils::ImageProperties* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::ImageProperties* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setFileName(const std::string& newFileName);
        virtual std::string getFileName() const;
        virtual void setWidth(unsigned int newWidth);
        virtual unsigned int getWidth() const;
        virtual void setHeight(unsigned int newHeight);
        virtual unsigned int getHeight() const;
        virtual void setOrigin(const Ionflux::GeoUtils::Vector2& 
        newOrigin);
        virtual Ionflux::GeoUtils::Vector2 getOrigin() const;
};

}

}
