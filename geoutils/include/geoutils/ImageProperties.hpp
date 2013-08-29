#ifndef IONFLUX_GEOUTILS_IMAGEPROPERTIES
#define IONFLUX_GEOUTILS_IMAGEPROPERTIES
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImageProperties.hpp             Image properties (header).
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

#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Vector2.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class ImageProperties.
class ImagePropertiesClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ImagePropertiesClassInfo();
		/// Destructor.
		virtual ~ImagePropertiesClassInfo();
};

/** Image properties.
 * \ingroup geoutils
 *
 * Properties for an image.
 */
class ImageProperties
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// File name.
		std::string fileName;
		/// Width.
		unsigned int width;
		/// Height.
		unsigned int height;
		/// Origin.
		Ionflux::GeoUtils::Vector2 origin;
		
	public:
		/// Default width.
		static const unsigned int DEFAULT_WIDTH;
		/// Default height.
		static const unsigned int DEFAULT_HEIGHT;
		/// Default origin.
		static const Ionflux::GeoUtils::Vector2 DEFAULT_ORIGIN;
		/// Class information instance.
		static const ImagePropertiesClassInfo imagePropertiesClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ImageProperties object.
		 */
		ImageProperties();
		
		/** Constructor.
		 *
		 * Construct new ImageProperties object.
		 *
		 * \param other Other object.
		 */
		ImageProperties(const Ionflux::GeoUtils::ImageProperties& other);
		
		/** Destructor.
		 *
		 * Destruct ImageProperties object.
		 */
		virtual ~ImageProperties();
		
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
		virtual Ionflux::GeoUtils::ImageProperties& operator=(const 
		Ionflux::GeoUtils::ImageProperties& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::ImageProperties* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::ImageProperties* 
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
		static Ionflux::GeoUtils::ImageProperties* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get file name.
		 *
		 * \return Current value of file name.
		 */
		virtual std::string getFileName() const;
		
		/** Set file name.
		 *
		 * Set new value of file name.
		 *
		 * \param newFileName New value of file name.
		 */
		virtual void setFileName(const std::string& newFileName);
		
		/** Get width.
		 *
		 * \return Current value of width.
		 */
		virtual unsigned int getWidth() const;
		
		/** Set width.
		 *
		 * Set new value of width.
		 *
		 * \param newWidth New value of width.
		 */
		virtual void setWidth(unsigned int newWidth);
		
		/** Get height.
		 *
		 * \return Current value of height.
		 */
		virtual unsigned int getHeight() const;
		
		/** Set height.
		 *
		 * Set new value of height.
		 *
		 * \param newHeight New value of height.
		 */
		virtual void setHeight(unsigned int newHeight);
		
		/** Get origin.
		 *
		 * \return Current value of origin.
		 */
		virtual Ionflux::GeoUtils::Vector2 getOrigin() const;
		
		/** Set origin.
		 *
		 * Set new value of origin.
		 *
		 * \param newOrigin New value of origin.
		 */
		virtual void setOrigin(const Ionflux::GeoUtils::Vector2& newOrigin);
};

}

}

/** \file ImageProperties.hpp
 * \brief Image properties (header).
 */
#endif
