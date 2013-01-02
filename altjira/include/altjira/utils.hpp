#ifndef IONFLUX_ALTJIRA_UTILS
#define IONFLUX_ALTJIRA_UTILS
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2009 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utils.hpp                     Utility functions (header).
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
#include "ifobject/types.hpp"
#include "altjira/types.hpp"
#include "altjira/constants.hpp"

namespace Ionflux
{

namespace Altjira
{

/** Convert float value to byte.
 * 
 * Convert a float value in the range 0...1 to a byte value in the range 
 * 0...255.
 * 
 * \param v Value.
 * 
 * \return Byte value.
 */
unsigned char floatToByte(double v);

/** Convert byte value to float.
 * 
 * Convert a byte value in the range 0...255 to a float value in the range 
 * 0...1.
 * 
 * \param v Value.
 * 
 * \return Float value.
 */
double byteToFloat(unsigned char v);

/** Add.
 *
 * Add bytes (representing the range [0...1]) using lookup tables.
 *
 * \param x First operand.
 * \param y Second operand.
 *
 * \return Result of the calculation.
 */
unsigned char lutAdd(unsigned char x, unsigned char y);

/** Multiply.
 *
 * Multiply bytes (representing the range [0...1]) using lookup tables.
 *
 * \param x First operand.
 * \param y Second operand.
 *
 * \return Result of the calculation.
 */
unsigned char lutMult(unsigned char x, unsigned char y);

/** Subtract.
 *
 * Subtract bytes (representing the range [0...1]) using lookup tables.
 *
 * \param x First operand.
 * \param y Second operand.
 *
 * \return Result of the calculation.
 */
unsigned char lutSub(unsigned char x, unsigned char y);

/** Divide.
 *
 * Divide bytes (representing the range [0...1]) using lookup tables.
 *
 * \param x First operand.
 * \param y Second operand.
 *
 * \return Result of the calculation.
 */
unsigned char lutDiv(unsigned char x, unsigned char y);

/** Create GIMP GIH rank specification.
 *
 * Create a GIMP brush pipe (GIH) rank specification. This is required for 
 * creating GIMP brushes with the Image class.
 *
 * \param selection Selection mode.
 * \param size Rank size.
 *
 * \return GIH rank specification.
 */
Ionflux::Altjira::GIHRankSpec createGIHRankSpec(std::string selection, 
    unsigned int size);

/** Initialize rectangle.
 *
 * Initialize a rectangle with the specified values.
 *
 * \param r Rectangle.
 * \param x X coordinate.
 * \param x Y coordinate.
 * \param width Width.
 * \param height Height.
 */
void initRectangle(Ionflux::Altjira::ImageRect& r, double x, double y, 
    double width, double height);

/** Intersect rectangles.
 *
 * Intersect two rectangles and return the resulting rectangle.
 *
 * \param r0 First rectangle.
 * \param r1 Second rectangle.
 */
Ionflux::Altjira::ImageRect intersect(const Ionflux::Altjira::ImageRect& r0, 
    const Ionflux::Altjira::ImageRect& r1);

}

}

/** \file utils.hpp
 * \brief Utility functions (header).
 */
#endif
