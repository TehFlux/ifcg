/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImageLoader.cpp                 Image loader (implementation).
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

#include "geoutils/ImageLoader.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

ImageLoaderClassInfo::ImageLoaderClassInfo()
{
	name = "ImageLoader";
	desc = "Image loader";
	baseClassInfo.push_back(Ionflux::GeoUtils::ImageSource::CLASS_INFO);
}

ImageLoaderClassInfo::~ImageLoaderClassInfo()
{
}

// run-time type information instance constants
const ImageLoaderClassInfo ImageLoader::imageLoaderClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ImageLoader::CLASS_INFO = &ImageLoader::imageLoaderClassInfo;

ImageLoader::ImageLoader()
: cache(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ImageLoader::ImageLoader(const Ionflux::GeoUtils::ImageLoader& other)
: cache(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ImageLoader::ImageLoader(const std::string& initMappedPrefix, const 
std::string& initUnmappedPrefix, Ionflux::ObjectBase::IFCache* initCache)
: mappedPrefix(initMappedPrefix), unmappedPrefix(initUnmappedPrefix), 
cache(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setCache(initCache);
}

ImageLoader::~ImageLoader()
{
	clearImageIDs();
	// TODO: Nothing ATM. ;-)
}

Ionflux::GeoUtils::Image* ImageLoader::getFromCache(const 
Ionflux::GeoUtils::ImageID& imageID)
{
	if (cache == 0)
	    return 0;
	std::ostringstream status;
	IFObject* it0 = cache->getItem(imageID);
	if (it0 == 0)
	{
	    // <---- DEBUG ----- //
	    status << "Cache miss (id = '" << imageID << "')";
	    log(IFLogMessage(status.str(), VL_DEBUG, this, "getFromCache"));
	    // ----- DEBUG ----> */
	    return 0;
	}
	// <---- DEBUG ----- //
	status << "Cache hit (id = '" << imageID << "')";
	log(IFLogMessage(status.str(), VL_DEBUG, this, "getFromCache"));
	// ----- DEBUG ----> */
	Image* img0 = Image::upcast(it0);
	if (img0 == 0)
	{
	    status.str("");
	    status << "[ImageLoader::getFromCache] "
	        "Cached item is not an image (id = '" << imageID << "')!";
	    throw GeoUtilsError(status.str());
	}
	return img0;
}

std::string ImageLoader::getFileName(const Ionflux::GeoUtils::ImageID& 
imageID)
{
	std::ostringstream result;
	std::map<std::string, Ionflux::GeoUtils::ImageID>::const_iterator i = 
	idMap.find(imageID);
	if (i != idMap.end())
	    // Mapped ID.
	    result << mappedPrefix << (*i).second;
	else
	    // Unmapped ID.
	    result << unmappedPrefix << imageID;
	return result.str();
}

Ionflux::GeoUtils::Image* ImageLoader::loadFromFile(const 
Ionflux::GeoUtils::ImageID& imageID)
{
	std::ostringstream status;
	std::string fileName = getFileName(imageID);
	if (fileName.size() == 0)
	{
	    status << "[ImageLoader::loadFromFile] "
	        "Could not determine file name for image (id = '" 
	        << imageID << "')!";
	    throw GeoUtilsError(status.str());
	}
	// <---- DEBUG ----- //
	status.str("");
	status << "Loading image (id = '" << imageID << "', fileName = '" 
	    << fileName << "')";
	log(IFLogMessage(status.str(), VL_DEBUG, this, "loadFromFile"));
	// ----- DEBUG ----> */
	Image* img0 = Image::create();
	img0->loadFromFile(fileName);
	return img0;
}

void ImageLoader::setPrefix(const std::string& prefix)
{
	mappedPrefix = prefix;
	unmappedPrefix = prefix;
}

void ImageLoader::addImage(const Ionflux::GeoUtils::ImageID& imageID, 
Ionflux::GeoUtils::Image* image, const std::string& fileName)
{
	if (fileName.size() > 0)
	    addImageID(imageID, fileName);
	if (cache != 0)
	    cache->addItem(imageID, image);
}

Ionflux::GeoUtils::Image* ImageLoader::getImage(const 
Ionflux::GeoUtils::ImageID& imageID)
{
	Image* img0 = getFromCache(imageID);
	if (img0 != 0)
	    // Image is in the cache.
	    return img0;
	img0 = loadFromFile(imageID);
	if ((img0 != 0) 
	    && (cache != 0))
	    // Add image to cache.
	    cache->addItem(imageID, img0);
	return img0;
}

void ImageLoader::initCache(Ionflux::ObjectBase::UInt64 maxSize)
{
	IFCache* c0 = IFCache::create();
	c0->setMaxSize(maxSize);
	setCache(c0);
}

std::string ImageLoader::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

unsigned int ImageLoader::getNumImageIDs() const
{
	return idMap.size();
}

Ionflux::GeoUtils::ImageID ImageLoader::getImageID(const std::string& 
elementKey) const
{
	std::map<std::string, Ionflux::GeoUtils::ImageID>::const_iterator i = idMap.find(elementKey);
	if (i != idMap.end())
		return (*i).second;
	return "";
}

std::map<std::string, Ionflux::GeoUtils::ImageID>& 
ImageLoader::getImageIDs()
{
	return idMap;
}

void ImageLoader::addImageID(const std::string& elementKey, 
Ionflux::GeoUtils::ImageID addElement)
{
	Ionflux::GeoUtils::ImageID theImageID = getImageID(elementKey);
	if (theImageID != "")
		return;
	idMap[elementKey] = addElement;
}

void ImageLoader::removeImageID(const std::string& elementKey)
{
	std::map<std::string, Ionflux::GeoUtils::ImageID>::iterator i = idMap.find(elementKey);
	if (i != idMap.end())
	{
		idMap.erase(i);
	}
}

void ImageLoader::clearImageIDs()
{
	idMap.clear();
}

void ImageLoader::setMappedPrefix(const std::string& newMappedPrefix)
{
	mappedPrefix = newMappedPrefix;
}

std::string ImageLoader::getMappedPrefix() const
{
    return mappedPrefix;
}

void ImageLoader::setUnmappedPrefix(const std::string& newUnmappedPrefix)
{
	unmappedPrefix = newUnmappedPrefix;
}

std::string ImageLoader::getUnmappedPrefix() const
{
    return unmappedPrefix;
}

void ImageLoader::setCache(Ionflux::ObjectBase::IFCache* newCache)
{
	if (cache == newCache)
		return;
    if (newCache != 0)
        addLocalRef(newCache);
	if (cache != 0)
		removeLocalRef(cache);
	cache = newCache;
}

Ionflux::ObjectBase::IFCache* ImageLoader::getCache() const
{
    return cache;
}

Ionflux::GeoUtils::ImageLoader& ImageLoader::operator=(const 
Ionflux::GeoUtils::ImageLoader& other)
{
    if (this == &other)
        return *this;
    ImageSource::operator=(other);
    mappedPrefix = other.mappedPrefix;
    unmappedPrefix = other.unmappedPrefix;
    idMap = other.idMap;
    setCache(other.cache);
	return *this;
}

Ionflux::GeoUtils::ImageLoader* ImageLoader::copy() const
{
    ImageLoader* newImageLoader = create();
    *newImageLoader = *this;
    return newImageLoader;
}

Ionflux::GeoUtils::ImageLoader* 
ImageLoader::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<ImageLoader*>(other);
}

Ionflux::GeoUtils::ImageLoader* 
ImageLoader::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    ImageLoader* newObject = new ImageLoader();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int ImageLoader::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file ImageLoader.cpp
 * \brief Image loader implementation.
 */
