#ifndef IONFLUX_ALTJIRA_COLOR
#define IONFLUX_ALTJIRA_COLOR
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Color.hpp                       Color (header).
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

#include "ifmapping/types.hpp"
#include "altjira/types.hpp"
#include "altjira/constants.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Altjira
{

struct ColorPair;

/// Class information for class Color.
class ColorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ColorClassInfo();
		/// Destructor.
		virtual ~ColorClassInfo();
};

/** Color.
 * \ingroup altjira
 *
 * An RGBA color. This color has the following components: red, green, 
 * blue, alpha.
 */
class Color
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Red component.
		double red;
		/// Green component.
		double green;
		/// Blue component.
		double blue;
		/// Alpha component.
		double alpha;
		
	public:
		/// Color: transparent.
		static const Ionflux::Altjira::Color TRANSPARENT;
		/// Color: black.
		static const Ionflux::Altjira::Color BLACK;
		/// Color: white.
		static const Ionflux::Altjira::Color WHITE;
		/// Color: gray (10%).
		static const Ionflux::Altjira::Color GRAY_10;
		/// Color: gray (20%).
		static const Ionflux::Altjira::Color GRAY_20;
		/// Color: gray (30%).
		static const Ionflux::Altjira::Color GRAY_30;
		/// Color: gray (40%).
		static const Ionflux::Altjira::Color GRAY_40;
		/// Color: gray (50%).
		static const Ionflux::Altjira::Color GRAY_50;
		/// Color: gray (60%).
		static const Ionflux::Altjira::Color GRAY_60;
		/// Color: gray (70%).
		static const Ionflux::Altjira::Color GRAY_70;
		/// Color: gray (80%).
		static const Ionflux::Altjira::Color GRAY_80;
		/// Color: gray (90%).
		static const Ionflux::Altjira::Color GRAY_90;
		/// Color: red.
		static const Ionflux::Altjira::Color RED;
		/// Color: green.
		static const Ionflux::Altjira::Color GREEN;
		/// Color: blue.
		static const Ionflux::Altjira::Color BLUE;
		/// Color: cyan.
		static const Ionflux::Altjira::Color CYAN;
		/// Color: magenta.
		static const Ionflux::Altjira::Color MAGENTA;
		/// Color: yellow.
		static const Ionflux::Altjira::Color YELLOW;
		/// Color: violet.
		static const Ionflux::Altjira::Color VIOLET;
		/// Color: orange.
		static const Ionflux::Altjira::Color ORANGE;
		/// Color space: undefined.
		static const Ionflux::Altjira::ColorSpace SPACE_UNDEFINED;
		/// Color space: RGB.
		static const Ionflux::Altjira::ColorSpace SPACE_RGB;
		/// Color space: HSV.
		static const Ionflux::Altjira::ColorSpace SPACE_HSV;
		/// Color space: HSL.
		static const Ionflux::Altjira::ColorSpace SPACE_HSL;
		/// Class information instance.
		static const ColorClassInfo colorClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Color object.
		 */
		Color();
		
		/** Constructor.
		 *
		 * Construct new Color object.
		 *
		 * \param other Other object.
		 */
		Color(const Ionflux::Altjira::Color& other);
		
		/** Constructor.
		 *
		 * Construct new Color object.
		 *
		 * \param initColor Initial color.
		 */
		Color(const ByteColor& initColor);
		
		/** Constructor.
		 *
		 * Construct new Color object.
		 *
		 * \param initColor Initial color.
		 */
		Color(const FloatColor& initColor);
		
		/** Constructor.
		 *
		 * Construct new Color object.
		 *
		 * \param initRed Initial red component.
		 * \param initGreen Initial green component.
		 * \param initBlue Initial blue component.
		 * \param initAlpha Initial alpha component.
		 */
		Color(FloatColorValue initRed, FloatColorValue initGreen, FloatColorValue
		initBlue, FloatColorValue initAlpha);
		
		/** Constructor.
		 *
		 * Construct new Color object.
		 *
		 * \param initRed Initial red component.
		 * \param initGreen Initial green component.
		 * \param initBlue Initial blue component.
		 * \param initAlpha Initial alpha component.
		 */
		Color(ByteColorValue initRed, ByteColorValue initGreen, ByteColorValue 
		initBlue, ByteColorValue initAlpha);
		
		/** Constructor.
		 *
		 * Construct new Color object.
		 *
		 * \param hexColor Hex color.
		 */
		Color(const std::string& hexColor);
		
		/** Destructor.
		 *
		 * Destruct Color object.
		 */
		virtual ~Color();
		
		/** Set from hexadecimal representation.
		 *
		 * Set the color from a hexadecimal representation starting with a 
		 * hash. The representation uses one byte (two hexadecimal digits) per
		 * component, in the order RGBA.
		 *
		 * \param hexColor Hexadecimal color.
		 *
		 * \return The color itself.
		 */
		virtual Ionflux::Altjira::Color& setFromHex(const std::string& hexColor);
		
		/** Get hexadecimal representation.
		 *
		 * Get a hexadecimal representation of the color.
		 *
		 * \return Hexadecimal representation.
		 */
		virtual std::string getHex() const;
		
		/** Clamp red component.
		 *
		 * Clamp the red component to the specified range of values.
		 *
		 * \param range Range.
		 *
		 * \return The color itself.
		 */
		virtual Ionflux::Altjira::Color& clampRed(const Ionflux::Mapping::Range& 
		range = DEFAULT_CLAMP_RANGE);
		
		/** Clamp green component.
		 *
		 * Clamp the green component to the specified range of values.
		 *
		 * \param range Range.
		 *
		 * \return The color itself.
		 */
		virtual Ionflux::Altjira::Color& clampGreen(const 
		Ionflux::Mapping::Range& range = DEFAULT_CLAMP_RANGE);
		
		/** Clamp blue component.
		 *
		 * Clamp the blue component to the specified range of values.
		 *
		 * \param range Range.
		 *
		 * \return The color itself.
		 */
		virtual Ionflux::Altjira::Color& clampBlue(const Ionflux::Mapping::Range&
		range = DEFAULT_CLAMP_RANGE);
		
		/** Clamp alpha component.
		 *
		 * Clamp the alpha component to the specified range of values.
		 *
		 * \param range Range.
		 *
		 * \return The color itself.
		 */
		virtual Ionflux::Altjira::Color& clampAlpha(const 
		Ionflux::Mapping::Range& range = DEFAULT_CLAMP_RANGE);
		
		/** Clamp components.
		 *
		 * Clamp the components to the specified range of values.
		 *
		 * \param range Range.
		 *
		 * \return The color itself.
		 */
		virtual Ionflux::Altjira::Color& clamp(const Ionflux::Mapping::Range& 
		range = DEFAULT_CLAMP_RANGE);
		
		/** Interpolate colors.
		 *
		 * Interpolate between two colors. The interpolation used is linear 
		 * and component-wise.
		 *
		 * \param first First color.
		 * \param second Second color.
		 * \param factor Interpolation factor.
		 *
		 * \return Interpolated color.
		 */
		static Ionflux::Altjira::Color interpolate(const Ionflux::Altjira::Color&
		first, const Ionflux::Altjira::Color& second, double factor);
		
		/** Set color components from float color.
		 *
		 * Set the color component values from a float color.
		 *
		 * \param other Color.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::Color& setFromFloatColor(const 
		Ionflux::Altjira::FloatColor& other);
		
		/** Set color components.
		 *
		 * Set the color component values.
		 *
		 * \param newRed Color component (red).
		 * \param newGreen Color component (green).
		 * \param newBlue Color component (blue).
		 * \param newAlpha Color component (alpha).
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::Color& 
		setComponents(Ionflux::Altjira::FloatColorValue newRed, 
		Ionflux::Altjira::FloatColorValue newGreen, 
		Ionflux::Altjira::FloatColorValue newBlue, 
		Ionflux::Altjira::FloatColorValue newAlpha);
		
		/** Set color components.
		 *
		 * Set the color component values.
		 *
		 * \param newRed Color component (red).
		 * \param newGreen Color component (green).
		 * \param newBlue Color component (blue).
		 * \param newAlpha Color component (alpha).
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::Color& 
		setComponents(Ionflux::Altjira::ByteColorValue newRed, 
		Ionflux::Altjira::ByteColorValue newGreen, 
		Ionflux::Altjira::ByteColorValue newBlue, 
		Ionflux::Altjira::ByteColorValue newAlpha);
		
		/** Get float color.
		 *
		 * Get color components in a float color structure.
		 *
		 * \param color Color.
		 */
		virtual void getFloatColor(Ionflux::Altjira::FloatColor& color) const;
		
		/** Get byte color.
		 *
		 * Get color components in a byte color structure.
		 *
		 * \param color Color.
		 */
		virtual void getByteColor(Ionflux::Altjira::ByteColor& color) const;
		
		/** Set color components from byte color.
		 *
		 * Set the color component values from a byte color.
		 *
		 * \param other Color.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::Color& setFromByteColor(const 
		Ionflux::Altjira::ByteColor& other);
		
		/** Multiply color components.
		 *
		 * Multiply the color components (except alpha) by a scalar value.
		 *
		 * \param target Target color.
		 * \param value Value.
		 */
		virtual void multiply(Ionflux::Altjira::Color& target, double value);
		
		/** Get mean squared error.
		 *
		 * Get the mean squared error between the color and the reference 
		 * color. The alpha value is ignored.
		 *
		 * \param refColor Reference color.
		 *
		 * \return Result of the calculation.
		 */
		virtual double getMeanSquaredError(const Ionflux::Altjira::Color& 
		refColor);
		
		/** Pre-multiply alpha.
		 *
		 * Pre-multiply alpha value.
		 *
		 * \param target Target color.
		 */
		virtual void preMultiply(Ionflux::Altjira::Color& target);
		
		/** Divide by alpha.
		 *
		 * Divide color components by alpha value. This can be used to undo a 
		 * premultiply operation.
		 *
		 * \param target Target color.
		 */
		virtual void divideAlpha(Ionflux::Altjira::Color& target);
		
		/** Assignment operator.
		 *
		 * Assign a color.
		 *
		 * \param other Color.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::Color& operator=(const 
		Ionflux::Altjira::FloatColor& other);
		
		/** Assignment operator.
		 *
		 * Assign a color.
		 *
		 * \param other Color.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::Color& operator=(const 
		Ionflux::Altjira::ByteColor& other);
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Color.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::Altjira::Color& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Color.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::Altjira::Color& other) const;
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Interpolate colors.
		 *
		 * Interpolate between two colors. The interpolation used is linear 
		 * and component-wise.
		 *
		 * \param colors Colors.
		 * \param factor Interpolation factor.
		 *
		 * \return Interpolated color.
		 */
		static Ionflux::Altjira::Color interpolate(const 
		Ionflux::Altjira::ColorPair& colors, double factor = 0.5);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::Color& operator=(const Ionflux::Altjira::Color&
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Altjira::Color* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Altjira::Color* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		
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
		static Ionflux::Altjira::Color* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Color object.
		 *
		 * \param initColor Initial color.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Altjira::Color* create(const ByteColor& initColor, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Color object.
		 *
		 * \param initColor Initial color.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Altjira::Color* create(const FloatColor& initColor, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Color object.
		 *
		 * \param initRed Initial red component.
		 * \param initGreen Initial green component.
		 * \param initBlue Initial blue component.
		 * \param initAlpha Initial alpha component.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Altjira::Color* create(FloatColorValue initRed, 
		FloatColorValue initGreen, FloatColorValue initBlue, FloatColorValue 
		initAlpha, Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Color object.
		 *
		 * \param initRed Initial red component.
		 * \param initGreen Initial green component.
		 * \param initBlue Initial blue component.
		 * \param initAlpha Initial alpha component.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Altjira::Color* create(ByteColorValue initRed, 
		ByteColorValue initGreen, ByteColorValue initBlue, ByteColorValue 
		initAlpha, Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Color object.
		 *
		 * \param hexColor Hex color.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Altjira::Color* create(const std::string& hexColor, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get red component.
		 *
		 * \return Current value of red component.
		 */
		virtual double getRed() const;
		
		/** Set red component.
		 *
		 * Set new value of red component.
		 *
		 * \param newRed New value of red component.
		 */
		virtual void setRed(double newRed);
		
		/** Get green component.
		 *
		 * \return Current value of green component.
		 */
		virtual double getGreen() const;
		
		/** Set green component.
		 *
		 * Set new value of green component.
		 *
		 * \param newGreen New value of green component.
		 */
		virtual void setGreen(double newGreen);
		
		/** Get blue component.
		 *
		 * \return Current value of blue component.
		 */
		virtual double getBlue() const;
		
		/** Set blue component.
		 *
		 * Set new value of blue component.
		 *
		 * \param newBlue New value of blue component.
		 */
		virtual void setBlue(double newBlue);
		
		/** Get alpha component.
		 *
		 * \return Current value of alpha component.
		 */
		virtual double getAlpha() const;
		
		/** Set alpha component.
		 *
		 * Set new value of alpha component.
		 *
		 * \param newAlpha New value of alpha component.
		 */
		virtual void setAlpha(double newAlpha);
		
		/** Get hue component.
		 *
		 * \return Current value of hue component.
		 */
		virtual double getHue() const;
		
		/** Set hue component.
		 *
		 * Set new value of hue component.
		 *
		 * \param newHue New value of hue component.
		 */
		virtual void setHue(double newHue);
		
		/** Get saturation component.
		 *
		 * \return Current value of saturation component.
		 */
		virtual double getSaturation() const;
		
		/** Set saturation component.
		 *
		 * Set new value of saturation component.
		 *
		 * \param newSaturation New value of saturation component.
		 */
		virtual void setSaturation(double newSaturation);
		
		/** Get luminance component.
		 *
		 * \return Current value of luminance component.
		 */
		virtual double getLuminance() const;
		
		/** Set luminance component.
		 *
		 * Set new value of luminance component.
		 *
		 * \param newLuminance New value of luminance component.
		 */
		virtual void setLuminance(double newLuminance);
};

}

}

/** \file Color.hpp
 * \brief Color (header).
 */
#endif
