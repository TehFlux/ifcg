#ifndef IONFLUX_ALTJIRA_IMAGEUTILS
#define IONFLUX_ALTJIRA_IMAGEUTILS
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2009 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * imageutils.hpp                     Image utility functions (header).
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
#include "ifmapping/types.hpp"
#include "altjira/Color.hpp"

namespace Ionflux
{

namespace Altjira
{

/** A pair of colors.
 * \ingroup altjira
 */
struct ColorPair
{
    /// First color.
    Color first;
    /// Second color.
    Color second;
};

/** Initialization.
 *
 * This has to be called once before Altjira can be used to set up the 
 * implementation code.
 */
void init();

/** Create float color.
 *
 * Create a float color.
 *
 * \param c0 Color component (0).
 * \param c1 Color component (1).
 * \param c2 Color component (2).
 * \param alpha Alpha value.
 * \param space Color space.
 *
 * \return Float color.
 */
Ionflux::Altjira::FloatColor createFloatColor(
    Ionflux::Altjira::FloatColorValue c0 = 0., 
    Ionflux::Altjira::FloatColorValue c1 = 0., 
    Ionflux::Altjira::FloatColorValue c2 = 0., 
    Ionflux::Altjira::FloatColorValue alpha = 1., 
    Ionflux::Altjira::ColorSpace space = Ionflux::Altjira::Color::SPACE_HSV);

/** Create byte color.
 *
 * Create a byte color.
 *
 * \param c0 Color component (0).
 * \param c1 Color component (1).
 * \param c2 Color component (2).
 * \param alpha Alpha value.
 * \param space Color space.
 *
 * \return Byte color.
 */
Ionflux::Altjira::ByteColor createByteColor(
    Ionflux::Altjira::ByteColorValue c0 = 0., 
    Ionflux::Altjira::ByteColorValue c1 = 0., 
    Ionflux::Altjira::ByteColorValue c2 = 0., 
    Ionflux::Altjira::ByteColorValue alpha = 1., 
    Ionflux::Altjira::ColorSpace space = Ionflux::Altjira::Color::SPACE_HSV);

/** Convert byte color to float color.
 * 
 * Convert a byte color with components in the range 0...255 to a float color 
 * with components in the range 0...1.
 * 
 * \param c0 Float color.
 * \param c1 Byte color.
 */
void floatToByte(const Ionflux::Altjira::FloatColor& c0, 
    Ionflux::Altjira::ByteColor& c1);

/** Convert float color to byte color.
 * 
 * Convert a float color with components in the range 0...1 to a byte color 
 * with components in the range 0...255.
 * 
 * \param c0 Byte color.
 * \param c1 Float color.
 */
void byteToFloat(const Ionflux::Altjira::ByteColor& c0, 
    Ionflux::Altjira::FloatColor& c1);

/** Clamp color.
 * 
 * Clamp a color to a range.
 * 
 * \param c Color.
 * \param r Range.
 */
void clamp(Ionflux::Altjira::FloatColor& c, 
    const Ionflux::Mapping::Range& r = DEFAULT_CLAMP_RANGE);

/** Wrap value.
 * 
 * Wrap a color to a range.
 * 
 * \param c Color.
 * \param r Range.
 */
void wrap(Ionflux::Altjira::FloatColor& c, 
    const Ionflux::Mapping::Range& r = DEFAULT_CLAMP_RANGE);

/** Convert to HSV.
 *
 * Convert a color to the HSV color space.
 *
 * \param c Color.
 */
void toHSV(Ionflux::Altjira::FloatColor& c);

/** Convert to RGB.
 *
 * Convert a color to the RGB color space.
 *
 * \param c Color.
 */
void toRGB(Ionflux::Altjira::FloatColor& c);

/** Convert to HSL.
 *
 * Convert a color to the HSL color space.
 *
 * \param c Color.
 */
void toHSL(Ionflux::Altjira::FloatColor& c);

/** Convert to color space.
 *
 * Convert a color to the specified color space.
 *
 * \param c Color.
 * \param space Color space.
 */
void toColorSpace(Ionflux::Altjira::FloatColor& c, 
    Ionflux::Altjira::ColorSpace space);

/** Convert to HSV.
 *
 * Convert a color to the HSV color space.
 *
 * \param c Color.
 */
void toHSV(Ionflux::Altjira::ByteColor& c);

/** Convert to RGB.
 *
 * Convert a color to the RGB color space.
 *
 * \param c Color.
 */
void toRGB(Ionflux::Altjira::ByteColor& c);

/** Convert to HSL.
 *
 * Convert a color to the HSL color space.
 *
 * \param c Color.
 */
void toHSL(Ionflux::Altjira::ByteColor& c);

/** Convert to color space.
 *
 * Convert a color to the specified color space.
 *
 * \param c Color.
 * \param space Color space.
 */
void toColorSpace(Ionflux::Altjira::ByteColor& c, 
    Ionflux::Altjira::ColorSpace space);

/** Copy color.
 *
 * Copy a color.
 * 
 * \param s Source color.
 * \param t Target color.
 */
void copy(const Ionflux::Altjira::FloatColor& s, 
    Ionflux::Altjira::FloatColor& t);

/** Multiply color.
 *
 * Multiply all color components (except alpha) with the specified value.
 * 
 * \param c Color.
 * \param value Value.
 */
void multiply(Ionflux::Altjira::FloatColor& c, double value);

/** Pre-multiply alpha.
 *
 * Multiply all color components (except alpha) by the alpha component of the 
 * color.
 * 
 * \param c Color.
 * \param value Value.
 */
void preMultiply(Ionflux::Altjira::FloatColor& c);

/** Divide alpha.
 *
 * Divide all color components (except alpha) by the alpha component of the 
 * color. This can be used to undo the pre-multiply operation.
 * 
 * \param c Color.
 * \param value Value.
 */
void divideAlpha(Ionflux::Altjira::FloatColor& c);

/** Get component.
 *
 * Get the component of the color corresponding to the specified channel.
 *
 * \param c Color.
 * \param channel Channel.
 *
 * \return Color component.
 */
Ionflux::Altjira::FloatColorValue getComponent(
    Ionflux::Altjira::FloatColor& c, Ionflux::Altjira::ChannelID channel);

/** Set component.
 *
 * Set the component of the color corresponding to the specified channel.
 *
 * \param c Color.
 * \param channel Channel.
 * \param value Value.
 *
 * \return Color component.
 */
void setComponent(Ionflux::Altjira::FloatColor& c, 
    Ionflux::Altjira::ChannelID channel, 
    Ionflux::Altjira::FloatColorValue value);

/** Color to alpha.
 *
 * Replace a reference color by transparency within the source color.
 *
 * \param c Source color.
 * \param refColor Reference color.
 */
void colorToAlpha(Ionflux::Altjira::FloatColor& c, 
    const Ionflux::Altjira::FloatColor& refColor);

/** Copy color.
 *
 * Copy a color.
 * 
 * \param s Source color.
 * \param t Target color.
 */
void copy(const Ionflux::Altjira::ByteColor& s, 
    Ionflux::Altjira::ByteColor& t);

/** Multiply color.
 *
 * Multiply all color components (except alpha) with the specified value.
 * 
 * \param c Color.
 * \param value Value.
 */
void multiply(Ionflux::Altjira::ByteColor& c, double value);

/** Multiply color.
 *
 * Multiply all color components (except alpha) with the specified value.
 * 
 * \param c Color.
 * \param value Value.
 */
void multiply(Ionflux::Altjira::ByteColor& c, 
    Ionflux::Altjira::ByteColorValue value);

/** Pre-multiply alpha.
 *
 * Multiply all color components (except alpha) by the alpha component of the 
 * color.
 * 
 * \param c Color.
 * \param value Value.
 */
void preMultiply(Ionflux::Altjira::ByteColor& c);

/** Divide alpha.
 *
 * Divide all color components (except alpha) by the alpha component of the 
 * color. This can be used to undo the pre-multiply operation.
 * 
 * \param c Color.
 * \param value Value.
 */
void divideAlpha(Ionflux::Altjira::ByteColor& c);

/** Get component.
 *
 * Get the component of the color corresponding to the specified channel.
 *
 * \param c Color.
 * \param channel Channel.
 *
 * \return Color component.
 */
Ionflux::Altjira::ByteColorValue getComponent(
    Ionflux::Altjira::ByteColor& c, Ionflux::Altjira::ChannelID channel);

/** Set component.
 *
 * Set the component of the color corresponding to the specified channel.
 *
 * \param c Color.
 * \param channel Channel.
 * \param value Value.
 *
 * \return Color component.
 */
void setComponent(Ionflux::Altjira::ByteColor& c, 
    Ionflux::Altjira::ChannelID channel, 
    Ionflux::Altjira::ByteColorValue value);

/** Convert color to UInt.
 *
 * Convert a color to an unsigned integer representation. The unsigned 
 * integer contains the alpha value in the uppermost byte, followed by the 
 * red, green and blue components.
 * 
 * \param c Color.
 * \param preMultiplied Whether the resulting color should use pre-multiplied 
 * alpha.
 *
 * \return Unsigned integer representation of the color.
 */
Ionflux::ObjectBase::UInt32 toUInt(const Ionflux::Altjira::ByteColor& c, 
    bool preMultiplied = true);

/** Convert UInt to color.
 *
 * Convert an unsigned integer representation to a byte color. The unsigned 
 * integer contains the alpha value in the uppermost byte, followed by the 
 * red, green and blue components.
 * 
 * \param v Unsigned integer color value.
 * \param target Where to store the result.
 * \param preMultiplied Whether the resulting color uses pre-multiplied alpha.
 *
 * \return Unsigned integer representation of the color.
 */
void fromUInt(Ionflux::ObjectBase::UInt32 v, Ionflux::Altjira::ByteColor& c, 
    bool preMultiplied = true);

/** Get string representation.
 *
 * Get a string representation for a color space.
 * 
 * \param space Color space.
 *
 * \return String representation.
 */
std::string colorSpaceToString(const Ionflux::Altjira::ColorSpace& space);

/** Get string representation.
 *
 * Get a string representation for a color.
 * 
 * \param c Color.
 *
 * \return String representation.
 */
std::string getString(const Ionflux::Altjira::FloatColor& c);

/** Get string representation.
 *
 * Get a string representation for a color.
 * 
 * \param c Color.
 *
 * \return String representation.
 */
std::string getString(const Ionflux::Altjira::ByteColor& c);

/** Color stop.
 * \ingroup altjira
 * 
 * Contains a color and a parameter. The parameter can be used to indicate the 
 * position of the color inside a color band.
 */
struct ColorStop
{
    /// Color.
    Ionflux::Altjira::Color color;
    /// Parameter.
    double param;
};

/// Vector of color stops.
typedef std::vector<Ionflux::Altjira::ColorStop> ColorStopVector;

/// Color stop equality check.
bool operator==(const Ionflux::Altjira::ColorStop& s0, 
    const Ionflux::Altjira::ColorStop& s1);

/// Vector of colors.
typedef std::vector<Ionflux::Altjira::Color> ColorVector;

/** Create colors.
 *
 * Create colors by interpolating two source colors according to the number 
 * of steps given for each component.
 * 
 * \param target Where to store the resulting colors.
 * \param c0 First color.
 * \param c0 Second color.
 * \param stepsC0 Number of steps for component c0.
 * \param stepsC1 Number of steps for component c1.
 * \param stepsC2 Number of steps for component c2.
 * \param stepsC0 Number of steps for alpha value.
 */
void createColors(Ionflux::Altjira::ColorVector& target, 
    const Ionflux::Altjira::FloatColor& c0, 
    const Ionflux::Altjira::FloatColor& c1, 
    unsigned int stepsC0 = 2, unsigned int stepsC1 = 2, 
    unsigned int stepsC2 = 2, unsigned int stepsAlpha = 1);

/** Get color space.
 *
 * Get the color space corresponding to a channel. If the optional hint is 
 * specified, that space will be used in case the channel specification is 
 * ambiguous (such as hue and saturation, which occur in both HSV and HSL 
 * color space, or alpha, which occurs in all color spaces).
 *
 * \param channel Channel.
 * \param hint Color space hint.
 *
 * \return Color space.
 */
Ionflux::Altjira::ColorSpace getColorSpaceForChannel(
    Ionflux::Altjira::ChannelID channel, Ionflux::Altjira::ColorSpace hint = 
        Ionflux::Altjira::Color::SPACE_UNDEFINED);

}

}

/** \file imageutils.hpp
 * \brief Image utility functions (header).
 */
#endif
