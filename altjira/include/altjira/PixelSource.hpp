#ifndef IONFLUX_ALTJIRA_PIXELSOURCE
#define IONFLUX_ALTJIRA_PIXELSOURCE
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PixelSource.hpp                 Pixel source (header).
 * =========================================================================
 * 
 * This file is part of Altjira - Ionflux' Image Processing Library.
 * 
 * Altjira - Ionflux' Image Processing Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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

#include "altjira/constants.hpp"
#include "altjira/Color.hpp"
#include <limits>
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Altjira
{

/// Class information for class PixelSource.
class PixelSourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		PixelSourceClassInfo();
		/// Destructor.
		virtual ~PixelSourceClassInfo();
};

/** Pixel source.
 * \ingroup altjira
 *
 * A source for pixels. Pixels are indexed by two-dimensional coordinates 
 * (x, y). A pixel source has a width and a height, either of which can be 
 * infinite.
 */
class PixelSource
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const PixelSourceClassInfo pixelSourceClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new PixelSource object.
		 */
		PixelSource();
		
		/** Constructor.
		 *
		 * Construct new PixelSource object.
		 *
		 * \param other Other object.
		 */
		PixelSource(const Ionflux::Altjira::PixelSource& other);
		
		/** Destructor.
		 *
		 * Destruct PixelSource object.
		 */
		virtual ~PixelSource();
		
		/** Get width.
		 *
		 * Get width.
		 */
		virtual unsigned int getWidth() const = 0;
		
		/** Get height.
		 *
		 * Get height.
		 */
		virtual unsigned int getHeight() const = 0;
		
		/** Get pixel color.
		 *
		 * Get pixel color.
		 *
		 * \param x Pixel coordinate (X).
		 * \param y Pixel coordinate (Y).
		 * \param color Color.
		 */
		virtual bool getPixel(unsigned int x, unsigned int y, 
		Ionflux::Altjira::ByteColor& color) const = 0;
		
		/** Get pixel color.
		 *
		 * Get pixel color.
		 *
		 * \param x Pixel coordinate (X).
		 * \param y Pixel coordinate (Y).
		 * \param color Color.
		 */
		virtual bool getPixel(unsigned int x, unsigned int y, 
		Ionflux::Altjira::FloatColor& color) const = 0;
		
		/** Get pixel color.
		 *
		 * Get pixel color.
		 *
		 * \param x Pixel coordinate (X).
		 * \param y Pixel coordinate (Y).
		 * \param color Color.
		 */
		virtual bool getPixel(unsigned int x, unsigned int y, 
		Ionflux::Altjira::Color& color) const = 0;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::PixelSource& operator=(const 
		Ionflux::Altjira::PixelSource& other);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
};

}

}

/** \file PixelSource.hpp
 * \brief Pixel source (header).
 */
#endif
