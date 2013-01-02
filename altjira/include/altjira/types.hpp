#ifndef IONFLUX_ALTJIRA_TYPES
#define IONFLUX_ALTJIRA_TYPES
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2009 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * types.hpp                       Types (header).
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

#include <vector>
#include <string>
#include <gdk-pixbuf/gdk-pixbuf.h>

namespace Ionflux
{

namespace Altjira
{

/// Image type.
typedef unsigned int ImageType;
/// Color space.
typedef unsigned int ColorSpace;
/// Pixel data.
typedef guchar* PixelData;
/// Float color value.
typedef double FloatColorValue;
/// Byte color value.
typedef unsigned char ByteColorValue;
/// Desaturation method.
typedef unsigned int DesaturationMethod;
/// Channel ID.
typedef unsigned int ChannelID;
/// Fill rule.
typedef int FillRule;

/** Byte color.
 * \ingroup altjira
 */
struct ByteColor
{
    /// Component value (0).
    ByteColorValue c0;
    /// Component value (1).
    ByteColorValue c1;
    /// Component value (2).
    ByteColorValue c2;
    /// Component value (alpha).
    ByteColorValue alpha;
    /// Color space.
    ColorSpace space;
};

/** Float color.
 * \ingroup altjira
 */
struct FloatColor
{
    /// Component value (0).
    FloatColorValue c0;
    /// Component value (1).
    FloatColorValue c1;
    /// Component value (2).
    FloatColorValue c2;
    /// Component value (alpha).
    FloatColorValue alpha;
    /// Color space.
    ColorSpace space;
};

/** A rectangle.
 * \ingroup altjira
 */
template<class T>
struct Rectangle
{
	/// X coordinate of upper left corner.
	T x;
	/// Y coordinate of upper left corner..
	T y;
    /// Width.
    T width;
    /// Height.
    T height;
};

/// Image rectangle.
typedef Rectangle<unsigned int> ImageRect;

class Image;

// Vector of images.
typedef std::vector<Ionflux::Altjira::Image*> ImageVector;

/** GIMP GIH brush rank specification.
 * \ingroup altjira
 */
struct GIHRankSpec
{
    /// Selection mode.
    std::string selection;
    /// Rank size.
    unsigned int size;
};

// Vector of GIMP GIH rank specifications.
typedef std::vector<Ionflux::Altjira::GIHRankSpec> GIHRankSpecVector;

}

}

/** \file types.hpp
 * \brief Types (header).
 */
#endif
