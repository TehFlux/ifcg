/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImageItem.i                     Image item (interface).
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
#include "geoutils/ImageItem.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class ImageItemClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ImageItemClassInfo();
        virtual ~ImageItemClassInfo();
};

class ImageItem
: public Ionflux::GeoUtils::BoxBoundsItem
{
    public:
		static const Ionflux::GeoUtils::SVGType SOURCE_TYPE_UNDEFINED;
		static const Ionflux::GeoUtils::SVGType SOURCE_TYPE_FILE;
		static const Ionflux::GeoUtils::SVGType SOURCE_TYPE_SOURCE;
        
        ImageItem();
		ImageItem(const Ionflux::GeoUtils::ImageItem& other);
        ImageItem(const std::string& initImageID, 
        Ionflux::GeoUtils::ImageSourceType initSourceType, const 
        Ionflux::GeoUtils::Vector3& initOffset = 
        Ionflux::GeoUtils::Vector3::ZERO, Ionflux::Altjira::ColorBlender* 
        initBlender = 0, Ionflux::GeoUtils::Image* initImage = 0, 
        Ionflux::GeoUtils::ImageSource* initSource = 0);
        virtual ~ImageItem();
        virtual void clear();
        virtual void update();
        virtual void acquire();
        virtual void release();
        virtual void load();
        virtual void clearData();
        virtual std::string getString() const;
        static std::string 
        getSourceTypeString(Ionflux::GeoUtils::ImageSourceType sourceType);
		virtual Ionflux::GeoUtils::ImageItem* copy() const;
		static Ionflux::GeoUtils::ImageItem* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::ImageItem* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setImage(Ionflux::GeoUtils::Image* newImage);
        virtual Ionflux::GeoUtils::Image* getImage() const;
        virtual void setImageID(const std::string& newImageID);
        virtual std::string getImageID() const;
        virtual void setSourceType(Ionflux::GeoUtils::ImageSourceType 
        newSourceType);
        virtual Ionflux::GeoUtils::ImageSourceType getSourceType() const;
        virtual void setBlender(Ionflux::Altjira::ColorBlender* 
        newBlender);
        virtual Ionflux::Altjira::ColorBlender* getBlender() const;
        virtual void setNumUsers(unsigned int newNumUsers);
        virtual unsigned int getNumUsers() const;
        virtual void setSource(Ionflux::GeoUtils::ImageSource* newSource);
        virtual Ionflux::GeoUtils::ImageSource* getSource() const;
        virtual void setOffset(Ionflux::GeoUtils::Vector3 newOffset);
        virtual Ionflux::GeoUtils::Vector3 getOffset() const;
};

}

}
