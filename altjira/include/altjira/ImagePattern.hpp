#ifndef IONFLUX_ALTJIRA_IMAGEPATTERN
#define IONFLUX_ALTJIRA_IMAGEPATTERN
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImagePattern.hpp                Image pattern (header).
 * =========================================================================
 *
 * This file is part of Altjira - Ionflux' Image Processing Library.
 * 
 * Altjira - Ionflux' Image Processing Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * Altjira - Ionflux' Image Processing Library is distributed in the hope 
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Altjira - Ionflux' Image Processing Library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "altjira/types.hpp"
#include "altjira/constants.hpp"
#include "altjira/Pattern.hpp"

namespace Ionflux
{

namespace Altjira
{

class Image;
class ColorBlender;

/// Class information for class ImagePattern.
class ImagePatternClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ImagePatternClassInfo();
		/// Destructor.
		virtual ~ImagePatternClassInfo();
};

/** Image pattern.
 * \ingroup geoutils
 *
 * A pattern that represents an image.
 */
class ImagePattern
: public Ionflux::Altjira::Pattern
{
	private:
		
	protected:
		/// Image.
		Ionflux::Altjira::Image* image;
		/// Offset (X).
		double offsetX;
		/// Offset (Y).
		double offsetY;
		
	public:
		/// Class information instance.
		static const ImagePatternClassInfo imagePatternClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ImagePattern object.
		 */
		ImagePattern();
		
		/** Constructor.
		 *
		 * Construct new ImagePattern object.
		 *
		 * \param other Other object.
		 */
		ImagePattern(const Ionflux::Altjira::ImagePattern& other);
		
		/** Constructor.
		 *
		 * Construct new ImagePattern object.
		 *
		 * \param initImage Image.
		 * \param initOffsetX Offset (X).
		 * \param initOffsetY Offset (Y).
		 */
		ImagePattern(Ionflux::Altjira::Image* initImage, double initOffsetX = 0.,
		double initOffsetY = 0.);
		
		/** Destructor.
		 *
		 * Destruct ImagePattern object.
		 */
		virtual ~ImagePattern();
		
		/** Clear.
		 *
		 * Free resources associated with the pattern.
		 */
		virtual void clear();
		
		/** Update.
		 *
		 * Update the pattern to reflect changes to the image.
		 */
		virtual void update();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Composite image to surface.
		 *
		 * Composite the specified image onto a drawing surface using the 
		 * specified color blender. If no color blender is specified, the 
		 * default SrcOver blender will be used. This function is intended to 
		 * composite an Altjira::Image to a Cairo surface so it can be used as
		 * a pattern.
		 *
		 * \param source Source image.
		 * \param target Target surface.
		 * \param blender Color blender.
		 * \param sourceRect Source rectangle.
		 * \param offsetX Target offset for compositing (X).
		 * \param offsetY Target offset for compositing (Y).
		 */
		static void compositeToSurface(Ionflux::Altjira::Image& source, 
		cairo_surface_t* target, const Ionflux::Altjira::ColorBlender* blender = 
		0, const Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned int 
		offsetX = 0, unsigned int offsetY = 0);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::ImagePattern& operator=(const 
		Ionflux::Altjira::ImagePattern& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Altjira::ImagePattern* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Altjira::ImagePattern* 
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
		static Ionflux::Altjira::ImagePattern* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get image.
		 *
		 * \return Current value of image.
		 */
		virtual Ionflux::Altjira::Image* getImage() const;
		
		/** Set image.
		 *
		 * Set new value of image.
		 *
		 * \param newImage New value of image.
		 */
		virtual void setImage(Ionflux::Altjira::Image* newImage);
		
		/** Get offset (X).
		 *
		 * \return Current value of offset (X).
		 */
		virtual double getOffsetX() const;
		
		/** Set offset (X).
		 *
		 * Set new value of offset (X).
		 *
		 * \param newOffsetX New value of offset (X).
		 */
		virtual void setOffsetX(double newOffsetX);
		
		/** Get offset (Y).
		 *
		 * \return Current value of offset (Y).
		 */
		virtual double getOffsetY() const;
		
		/** Set offset (Y).
		 *
		 * Set new value of offset (Y).
		 *
		 * \param newOffsetY New value of offset (Y).
		 */
		virtual void setOffsetY(double newOffsetY);
};

}

}

/** \file ImagePattern.hpp
 * \brief Image pattern (header).
 */
#endif
