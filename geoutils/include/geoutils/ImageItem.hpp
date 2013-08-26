#ifndef IONFLUX_GEOUTILS_IMAGEITEM
#define IONFLUX_GEOUTILS_IMAGEITEM
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImageItem.hpp                   Image item (header).
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

#include "altjira/ColorBlender.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Vector3.hpp"
#include "geoutils/Image.hpp"
#include "geoutils/ImageSource.hpp"
#include "geoutils/BoxBoundsItem.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class ImageItem.
class ImageItemClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ImageItemClassInfo();
		/// Destructor.
		virtual ~ImageItemClassInfo();
};

/** Image item.
 * \ingroup geoutils
 *
 * A box bounds item that represents an image.
 */
class ImageItem
: public Ionflux::GeoUtils::BoxBoundsItem
{
	private:
		
	protected:
		/// Image.
		Ionflux::GeoUtils::Image* image;
		/// Image ID.
		std::string imageID;
		/// Image source type.
		Ionflux::GeoUtils::ImageSourceType sourceType;
		/// Color blender.
		Ionflux::Altjira::ColorBlender* blender;
		/// Number of users of the image.
		unsigned int numUsers;
		/// Image source.
		Ionflux::GeoUtils::ImageSource* source;
		/// Offset vector.
		Ionflux::GeoUtils::Vector3 offset;
		
	public:
		/// Image source type: undefined.
		static const Ionflux::GeoUtils::SVGType SOURCE_TYPE_UNDEFINED;
		/// Image source type: file.
		static const Ionflux::GeoUtils::SVGType SOURCE_TYPE_FILE;
		/// Image source type: source.
		static const Ionflux::GeoUtils::SVGType SOURCE_TYPE_SOURCE;
		/// Class information instance.
		static const ImageItemClassInfo imageItemClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ImageItem object.
		 */
		ImageItem();
		
		/** Constructor.
		 *
		 * Construct new ImageItem object.
		 *
		 * \param other Other object.
		 */
		ImageItem(const Ionflux::GeoUtils::ImageItem& other);
		
		/** Constructor.
		 *
		 * Construct new ImageItem object.
		 *
		 * \param initImageID Image ID.
		 * \param initSourceType Image source type.
		 * \param initOffset Offset vector.
		 * \param initBlender Color blender.
		 * \param initImage Image.
		 * \param initSource Image source.
		 */
		ImageItem(const std::string& initImageID, 
		Ionflux::GeoUtils::ImageSourceType initSourceType, const 
		Ionflux::GeoUtils::Vector3& initOffset = 
		Ionflux::GeoUtils::Vector3::ZERO, Ionflux::Altjira::ColorBlender* 
		initBlender = 0, Ionflux::GeoUtils::Image* initImage = 0, 
		Ionflux::GeoUtils::ImageSource* initSource = 0);
		
		/** Destructor.
		 *
		 * Destruct ImageItem object.
		 */
		virtual ~ImageItem();
		
		/** Clear item.
		 *
		 * Clears the bounds data of the item.
		 */
		virtual void clear();
		
		/** Update.
		 *
		 * Update all state according to the image source.
		 */
		virtual void update();
		
		/** Acquire image data.
		 *
		 * Increment the user count for the image data. Loads the image data 
		 * from the source if it is not currently loaded.
		 */
		virtual void acquire();
		
		/** Release image data.
		 *
		 * Decrement the user count for the image data. Unloads the image data
		 * if there are no more users.
		 */
		virtual void release();
		
		/** Load image data.
		 *
		 * Load the image data from the source.
		 */
		virtual void load();
		
		/** Clear data.
		 *
		 * Clear the image data.
		 */
		virtual void clearData();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Get string representation for source type.
		 *
		 * Get a string representation for a source type.
		 *
		 * \param sourceType Image source type.
		 *
		 * \return String representation.
		 */
		static std::string getSourceTypeString(Ionflux::GeoUtils::ImageSourceType
		sourceType);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::ImageItem& operator=(const 
		Ionflux::GeoUtils::ImageItem& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::ImageItem* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::ImageItem* 
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
		static Ionflux::GeoUtils::ImageItem* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get image.
		 *
		 * \return Current value of image.
		 */
		virtual Ionflux::GeoUtils::Image* getImage() const;
		
		/** Set image.
		 *
		 * Set new value of image.
		 *
		 * \param newImage New value of image.
		 */
		virtual void setImage(Ionflux::GeoUtils::Image* newImage);
		
		/** Get image ID.
		 *
		 * \return Current value of image ID.
		 */
		virtual std::string getImageID() const;
		
		/** Set image ID.
		 *
		 * Set new value of image ID.
		 *
		 * \param newImageID New value of image ID.
		 */
		virtual void setImageID(const std::string& newImageID);
		
		/** Get image source type.
		 *
		 * \return Current value of image source type.
		 */
		virtual Ionflux::GeoUtils::ImageSourceType getSourceType() const;
		
		/** Set image source type.
		 *
		 * Set new value of image source type.
		 *
		 * \param newSourceType New value of image source type.
		 */
		virtual void setSourceType(Ionflux::GeoUtils::ImageSourceType 
		newSourceType);
		
		/** Get color blender.
		 *
		 * \return Current value of color blender.
		 */
		virtual Ionflux::Altjira::ColorBlender* getBlender() const;
		
		/** Set color blender.
		 *
		 * Set new value of color blender.
		 *
		 * \param newBlender New value of color blender.
		 */
		virtual void setBlender(Ionflux::Altjira::ColorBlender* newBlender);
		
		/** Get number of users of the image.
		 *
		 * \return Current value of number of users of the image.
		 */
		virtual unsigned int getNumUsers() const;
		
		/** Set number of users of the image.
		 *
		 * Set new value of number of users of the image.
		 *
		 * \param newNumUsers New value of number of users of the image.
		 */
		virtual void setNumUsers(unsigned int newNumUsers);
		
		/** Get image source.
		 *
		 * \return Current value of image source.
		 */
		virtual Ionflux::GeoUtils::ImageSource* getSource() const;
		
		/** Set image source.
		 *
		 * Set new value of image source.
		 *
		 * \param newSource New value of image source.
		 */
		virtual void setSource(Ionflux::GeoUtils::ImageSource* newSource);
		
		/** Get offset vector.
		 *
		 * \return Current value of offset vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getOffset() const;
		
		/** Set offset vector.
		 *
		 * Set new value of offset vector.
		 *
		 * \param newOffset New value of offset vector.
		 */
		virtual void setOffset(Ionflux::GeoUtils::Vector3 newOffset);
};

}

}

/** \file ImageItem.hpp
 * \brief Image item (header).
 */
#endif
