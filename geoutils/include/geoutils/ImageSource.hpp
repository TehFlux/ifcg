#ifndef IONFLUX_GEOUTILS_IMAGESOURCE
#define IONFLUX_GEOUTILS_IMAGESOURCE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImageSource.hpp                 Image source (header).
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
#include "geoutils/Image.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class ImageSource.
class ImageSourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ImageSourceClassInfo();
		/// Destructor.
		virtual ~ImageSourceClassInfo();
};

/** Image source.
 * \ingroup geoutils
 *
 * Abstract base class for objects that provide Image objects by ID.
 */
class ImageSource
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const ImageSourceClassInfo imageSourceClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ImageSource object.
		 */
		ImageSource();
		
		/** Constructor.
		 *
		 * Construct new ImageSource object.
		 *
		 * \param other Other object.
		 */
		ImageSource(const Ionflux::GeoUtils::ImageSource& other);
		
		/** Destructor.
		 *
		 * Destruct ImageSource object.
		 */
		virtual ~ImageSource();
		
		/** Get image.
		 *
		 * Get an image by ID.
		 *
		 * \param imageID Image ID.
		 */
		virtual Ionflux::GeoUtils::Image* getImage(const 
		Ionflux::GeoUtils::ImageID& imageID) = 0;
		
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
		virtual Ionflux::GeoUtils::ImageSource& operator=(const 
		Ionflux::GeoUtils::ImageSource& other);
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::ImageSource* 
		upcast(Ionflux::ObjectBase::IFObject* other);
};

}

}

/** \file ImageSource.hpp
 * \brief Image source (header).
 */
#endif
