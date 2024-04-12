#ifndef IONFLUX_GEOUTILS_IMAGELOADER
#define IONFLUX_GEOUTILS_IMAGELOADER
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImageLoader.hpp                 Image loader (header).
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

#include "ifobject/IFCache.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/ImageSource.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class ImageLoader.
class ImageLoaderClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ImageLoaderClassInfo();
		/// Destructor.
		virtual ~ImageLoaderClassInfo();
};

/** Image loader.
 * \ingroup geoutils
 *
 * This class can be used to load images from the file system, cache them 
 * in memory and provide them to users using the ImageSource interface.
 */
class ImageLoader
: public Ionflux::GeoUtils::ImageSource
{
	private:
		
	protected:
		/// Image ID to file name map.
		std::map<std::string, Ionflux::GeoUtils::ImageID> idMap;
		/// File name prefix for mapped IDs.
		std::string mappedPrefix;
		/// File name prefix for unmapped IDs.
		std::string unmappedPrefix;
		/// Cache.
		Ionflux::ObjectBase::IFCache* cache;
		
		/** Get image from cache.
		 *
		 * Get an image from the cache.
		 *
		 * \param imageID Image ID.
		 *
		 * \return Image, or 0 if no image with the ID exists within the cache.
		 */
		virtual Ionflux::GeoUtils::Image* getFromCache(const 
		Ionflux::GeoUtils::ImageID& imageID);
		
		/** Get file name.
		 *
		 * Get the file name corresponding to an image ID.
		 *
		 * \param imageID Image ID.
		 *
		 * \return File name corresponsing to the specified image ID.
		 */
		virtual std::string getFileName(const Ionflux::GeoUtils::ImageID& 
		imageID);
		
		/** Load image.
		 *
		 * Load an image from the file system.
		 *
		 * \param imageID Image ID.
		 *
		 * \return Image.
		 */
		virtual Ionflux::GeoUtils::Image* loadFromFile(const 
		Ionflux::GeoUtils::ImageID& imageID);
		
	public:
		/// Class information instance.
		static const ImageLoaderClassInfo imageLoaderClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ImageLoader object.
		 */
		ImageLoader();
		
		/** Constructor.
		 *
		 * Construct new ImageLoader object.
		 *
		 * \param other Other object.
		 */
		ImageLoader(const Ionflux::GeoUtils::ImageLoader& other);
		
		/** Constructor.
		 *
		 * Construct new ImageLoader object.
		 *
		 * \param initMappedPrefix File name prefix for mapped IDs.
		 * \param initUnmappedPrefix File name prefix for unmapped IDs.
		 * \param initCache Cache.
		 */
		ImageLoader(const std::string& initMappedPrefix, const std::string& 
		initUnmappedPrefix = "", Ionflux::ObjectBase::IFCache* initCache = 0);
		
		/** Destructor.
		 *
		 * Destruct ImageLoader object.
		 */
		virtual ~ImageLoader();
		
		/** Set prefix.
		 *
		 * Set the file name prefix for both mapped and unmapped image IDs.
		 *
		 * \param prefix Prefix.
		 */
		virtual void setPrefix(const std::string& prefix);
		
		/** Add image.
		 *
		 * Add an image that has already been loaded using some other means to
		 * the loader. If \c fileName is specified, an ID mapping is added for
		 * the image. If a cache is set for the loader, the image is added to 
		 * the cache.
		 *
		 * \param imageID Image ID.
		 * \param image Image.
		 * \param fileName File name.
		 */
		virtual void addImage(const Ionflux::GeoUtils::ImageID& imageID, 
		Ionflux::GeoUtils::Image* image, const std::string& fileName = "");
		
		/** Get image.
		 *
		 * Get an image by ID.
		 *
		 * \param imageID Image ID.
		 *
		 * \return Image, or 0 if no image with the ID exists.
		 */
		virtual Ionflux::GeoUtils::Image* getImage(const 
		Ionflux::GeoUtils::ImageID& imageID);
		
		/** Initialize cache.
		 *
		 * Initialize a cache for the loader.
		 *
		 * \param maxSize Maximum cache size.
		 */
		virtual void initCache(Ionflux::ObjectBase::UInt64 maxSize = 0);
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::ImageLoader& operator=(const 
		Ionflux::GeoUtils::ImageLoader& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::ImageLoader* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::ImageLoader* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::GeoUtils::ImageLoader* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get number of imageIDs.
		 *
		 * \return Number of imageIDs.
		 */
		virtual unsigned int getNumImageIDs() const;
		
		/** Get imageID.
		 *
		 * Get the imageID with the specified key.
		 *
		 * \param elementKey Element key.
		 *
		 * \return ImageID with specified key.
		 */
		virtual Ionflux::GeoUtils::ImageID getImageID(const std::string& 
		elementKey) const;
        
		/** Get image ID to file name map.
		 *
		 * \return image ID to file name map.
		 */
		virtual std::map<std::string, Ionflux::GeoUtils::ImageID>& getImageIDs();
		
		/** Add imageID.
		 *
		 * Add a imageID.
		 *
		 * \param elementKey Element key.
		 * \param addElement ImageID to be added.
		 */
		virtual void addImageID(const std::string& elementKey, 
		Ionflux::GeoUtils::ImageID addElement);
		
		/** Remove imageID.
		 *
		 * Remove the imageID with the specified key.
		 *
		 * \param elementKey Element key.
		 */
		virtual void removeImageID(const std::string& elementKey);
		
		/** Clear imageIDs.
		 *
		 * Clear all imageIDs.
		 */
		virtual void clearImageIDs();
		
		/** Get file name prefix for mapped IDs.
		 *
		 * \return Current value of file name prefix for mapped IDs.
		 */
		virtual std::string getMappedPrefix() const;
		
		/** Set file name prefix for mapped IDs.
		 *
		 * Set new value of file name prefix for mapped IDs.
		 *
		 * \param newMappedPrefix New value of file name prefix for mapped IDs.
		 */
		virtual void setMappedPrefix(const std::string& newMappedPrefix);
		
		/** Get file name prefix for unmapped IDs.
		 *
		 * \return Current value of file name prefix for unmapped IDs.
		 */
		virtual std::string getUnmappedPrefix() const;
		
		/** Set file name prefix for unmapped IDs.
		 *
		 * Set new value of file name prefix for unmapped IDs.
		 *
		 * \param newUnmappedPrefix New value of file name prefix for unmapped 
		 * IDs.
		 */
		virtual void setUnmappedPrefix(const std::string& newUnmappedPrefix);
		
		/** Get cache.
		 *
		 * \return Current value of cache.
		 */
		virtual Ionflux::ObjectBase::IFCache* getCache() const;
		
		/** Set cache.
		 *
		 * Set new value of cache.
		 *
		 * \param newCache New value of cache.
		 */
		virtual void setCache(Ionflux::ObjectBase::IFCache* newCache);
};

}

}

/** \file ImageLoader.hpp
 * \brief Image loader (header).
 */
#endif
