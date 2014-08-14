/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImageLoader.i                   Image loader (interface).
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
#include "geoutils/ImageLoader.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class ImageLoaderClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ImageLoaderClassInfo();
        virtual ~ImageLoaderClassInfo();
};

class ImageLoader
: public Ionflux::GeoUtils::ImageSource
{
    public:
        
        ImageLoader();
		ImageLoader(const Ionflux::GeoUtils::ImageLoader& other);
        ImageLoader(const std::string& initMappedPrefix, const std::string&
        initUnmappedPrefix = "", Ionflux::ObjectBase::IFCache* initCache = 
        0);
        virtual ~ImageLoader();
        virtual void setPrefix(const std::string& prefix);
        virtual void addImage(const Ionflux::GeoUtils::ImageID& imageID, 
        Ionflux::GeoUtils::Image* image, const std::string& fileName = "");
        virtual Ionflux::GeoUtils::Image* getImage(const 
        Ionflux::GeoUtils::ImageID& imageID);
        virtual void initCache(Ionflux::ObjectBase::UInt64 maxSize = 0);
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::ImageLoader* copy() const;
		static Ionflux::GeoUtils::ImageLoader* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::ImageLoader* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual unsigned int getNumImageIDs() const;
        virtual Ionflux::GeoUtils::ImageID getImageID(const std::string& 
        elementKey) const;

        virtual std::map<std::string, Ionflux::GeoUtils::ImageID>& 
        getImageIDs();
        virtual void addImageID(const std::string& elementKey, 
        Ionflux::GeoUtils::ImageID addElement);        
        virtual void removeImageID(const std::string& elementKey);
		virtual void clearImageIDs();
        virtual void setMappedPrefix(const std::string& newMappedPrefix);
        virtual std::string getMappedPrefix() const;
        virtual void setUnmappedPrefix(const std::string& 
        newUnmappedPrefix);
        virtual std::string getUnmappedPrefix() const;
        virtual void setCache(Ionflux::ObjectBase::IFCache* newCache);
        virtual Ionflux::ObjectBase::IFCache* getCache() const;
};

}

}
