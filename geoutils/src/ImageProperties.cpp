/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImageProperties.cpp             Image properties (implementation).
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

#include "geoutils/ImageProperties.hpp"
#include <sys/time.h>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

ImagePropertiesClassInfo::ImagePropertiesClassInfo()
{
	name = "ImageProperties";
	desc = "Image properties";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

ImagePropertiesClassInfo::~ImagePropertiesClassInfo()
{
}

// public member constants
const unsigned int ImageProperties::DEFAULT_WIDTH = 1000;
const unsigned int ImageProperties::DEFAULT_HEIGHT = 1000;
const Ionflux::GeoUtils::Vector2 ImageProperties::DEFAULT_ORIGIN = Ionflux::GeoUtils::Vector2(500, 500);

// run-time type information instance constants
const ImagePropertiesClassInfo ImageProperties::imagePropertiesClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ImageProperties::CLASS_INFO = &ImageProperties::imagePropertiesClassInfo;

ImageProperties::ImageProperties()
: fileName("unnamed_image"), width(Ionflux::GeoUtils::ImageProperties::DEFAULT_WIDTH), height(Ionflux::GeoUtils::ImageProperties::DEFAULT_HEIGHT), origin(Ionflux::GeoUtils::ImageProperties::DEFAULT_ORIGIN)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ImageProperties::ImageProperties(const Ionflux::GeoUtils::ImageProperties& other)
: fileName("unnamed_image"), width(Ionflux::GeoUtils::ImageProperties::DEFAULT_WIDTH), height(Ionflux::GeoUtils::ImageProperties::DEFAULT_HEIGHT), origin(Ionflux::GeoUtils::ImageProperties::DEFAULT_ORIGIN)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ImageProperties::~ImageProperties()
{
	// TODO: Nothing ATM. ;-)
}

std::string ImageProperties::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << width 
	    << height << ", " << origin << "]";
	return status.str();
}

void ImageProperties::setFileName(const std::string& newFileName)
{
	fileName = newFileName;
}

std::string ImageProperties::getFileName() const
{
	return fileName;
}

void ImageProperties::setWidth(unsigned int newWidth)
{
	width = newWidth;
}

unsigned int ImageProperties::getWidth() const
{
	return width;
}

void ImageProperties::setHeight(unsigned int newHeight)
{
	height = newHeight;
}

unsigned int ImageProperties::getHeight() const
{
	return height;
}

void ImageProperties::setOrigin(const Ionflux::GeoUtils::Vector2& 
newOrigin)
{
	origin = newOrigin;
}

Ionflux::GeoUtils::Vector2 ImageProperties::getOrigin() const
{
	return origin;
}

Ionflux::GeoUtils::ImageProperties& ImageProperties::operator=(const 
Ionflux::GeoUtils::ImageProperties& other)
{
    height = other.height;
    width = other.width;
    origin = other.origin;
	return *this;
}

Ionflux::GeoUtils::ImageProperties* ImageProperties::copy() const
{
    ImageProperties* newImageProperties = create();
    *newImageProperties = *this;
    return newImageProperties;
}

Ionflux::GeoUtils::ImageProperties* 
ImageProperties::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<ImageProperties*>(other);
}

Ionflux::GeoUtils::ImageProperties* 
ImageProperties::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    ImageProperties* newObject = new ImageProperties();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file ImageProperties.cpp
 * \brief Image properties implementation.
 */
