/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImageSource.i                   Image source (interface).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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
#include "geoutils/ImageSource.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class ImageSourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ImageSourceClassInfo();
        virtual ~ImageSourceClassInfo();
};

class ImageSource
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        ImageSource();
		ImageSource(const Ionflux::GeoUtils::ImageSource& other);
        virtual ~ImageSource();
        virtual Ionflux::GeoUtils::Image* getImage(const 
        Ionflux::GeoUtils::ImageID& imageID) = 0;
        virtual std::string getString() const;
		static Ionflux::GeoUtils::ImageSource* 
		upcast(Ionflux::ObjectBase::IFObject* other);
};

}

}
