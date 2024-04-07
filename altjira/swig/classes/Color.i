/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Color.i                         Color (interface).
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
%{
#include "altjira/Color.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

struct ColorPair;

class ColorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ColorClassInfo();
        virtual ~ColorClassInfo();
};

class Color
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Altjira::Color TRANSPARENT;
		static const Ionflux::Altjira::Color BLACK;
		static const Ionflux::Altjira::Color WHITE;
		static const Ionflux::Altjira::Color GRAY_10;
		static const Ionflux::Altjira::Color GRAY_20;
		static const Ionflux::Altjira::Color GRAY_30;
		static const Ionflux::Altjira::Color GRAY_40;
		static const Ionflux::Altjira::Color GRAY_50;
		static const Ionflux::Altjira::Color GRAY_60;
		static const Ionflux::Altjira::Color GRAY_70;
		static const Ionflux::Altjira::Color GRAY_80;
		static const Ionflux::Altjira::Color GRAY_90;
		static const Ionflux::Altjira::Color RED;
		static const Ionflux::Altjira::Color GREEN;
		static const Ionflux::Altjira::Color BLUE;
		static const Ionflux::Altjira::Color CYAN;
		static const Ionflux::Altjira::Color MAGENTA;
		static const Ionflux::Altjira::Color YELLOW;
		static const Ionflux::Altjira::Color VIOLET;
		static const Ionflux::Altjira::Color ORANGE;
		static const Ionflux::Altjira::ColorSpace SPACE_UNDEFINED;
		static const Ionflux::Altjira::ColorSpace SPACE_RGB;
		static const Ionflux::Altjira::ColorSpace SPACE_HSV;
		static const Ionflux::Altjira::ColorSpace SPACE_HSL;
        
        Color();
		Color(const Ionflux::Altjira::Color& other);
        Color(const ByteColor& initColor);
        Color(const FloatColor& initColor);
        Color(FloatColorValue initRed, FloatColorValue initGreen, 
        FloatColorValue initBlue, FloatColorValue initAlpha);
        Color(ByteColorValue initRed, ByteColorValue initGreen, 
        ByteColorValue initBlue, ByteColorValue initAlpha);
        Color(const std::string& hexColor);
        virtual ~Color();
        virtual Ionflux::Altjira::Color& setFromHex(const std::string& 
        hexColor);
        virtual std::string getHex() const;
        virtual Ionflux::Altjira::Color& clampRed(const 
        Ionflux::Mapping::Range& range = DEFAULT_CLAMP_RANGE);
        virtual Ionflux::Altjira::Color& clampGreen(const 
        Ionflux::Mapping::Range& range = DEFAULT_CLAMP_RANGE);
        virtual Ionflux::Altjira::Color& clampBlue(const 
        Ionflux::Mapping::Range& range = DEFAULT_CLAMP_RANGE);
        virtual Ionflux::Altjira::Color& clampAlpha(const 
        Ionflux::Mapping::Range& range = DEFAULT_CLAMP_RANGE);
        virtual Ionflux::Altjira::Color& clamp(const 
        Ionflux::Mapping::Range& range = DEFAULT_CLAMP_RANGE);
        static Ionflux::Altjira::Color interpolate(const 
        Ionflux::Altjira::Color& first, const Ionflux::Altjira::Color& 
        second, double factor);
        virtual Ionflux::Altjira::Color& setFromFloatColor(const 
        Ionflux::Altjira::FloatColor& other);
        virtual Ionflux::Altjira::Color& 
        setComponents(Ionflux::Altjira::FloatColorValue newRed, 
        Ionflux::Altjira::FloatColorValue newGreen, 
        Ionflux::Altjira::FloatColorValue newBlue, 
        Ionflux::Altjira::FloatColorValue newAlpha);
        virtual Ionflux::Altjira::Color& 
        setComponents(Ionflux::Altjira::ByteColorValue newRed, 
        Ionflux::Altjira::ByteColorValue newGreen, 
        Ionflux::Altjira::ByteColorValue newBlue, 
        Ionflux::Altjira::ByteColorValue newAlpha);
        virtual void getFloatColor(Ionflux::Altjira::FloatColor& color) 
        const;
        virtual void getByteColor(Ionflux::Altjira::ByteColor& color) 
        const;
        virtual Ionflux::Altjira::Color& setFromByteColor(const 
        Ionflux::Altjira::ByteColor& other);
        virtual void multiply(Ionflux::Altjira::Color& target, double 
        value);
        virtual double getMeanSquaredError(const Ionflux::Altjira::Color& 
        refColor);
        virtual void preMultiply(Ionflux::Altjira::Color& target);
        virtual void divideAlpha(Ionflux::Altjira::Color& target);
        virtual bool operator==(const Ionflux::Altjira::Color& other) 
        const;
        virtual bool operator!=(const Ionflux::Altjira::Color& other) 
        const;
        virtual std::string getValueString() const;
        static Ionflux::Altjira::Color interpolate(const 
        Ionflux::Altjira::ColorPair& colors, double factor = 0.5);
		virtual Ionflux::Altjira::Color* copy() const;
		static Ionflux::Altjira::Color* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Altjira::Color* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::Altjira::Color* create(const ByteColor& initColor, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Altjira::Color* create(const FloatColor& initColor, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Altjira::Color* create(FloatColorValue initRed, 
		FloatColorValue initGreen, FloatColorValue initBlue, FloatColorValue 
		initAlpha, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Altjira::Color* create(ByteColorValue initRed, 
		ByteColorValue initGreen, ByteColorValue initBlue, ByteColorValue 
		initAlpha, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Altjira::Color* create(const std::string& hexColor, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setRed(double newRed);
        virtual double getRed() const;
        virtual void setGreen(double newGreen);
        virtual double getGreen() const;
        virtual void setBlue(double newBlue);
        virtual double getBlue() const;
        virtual void setAlpha(double newAlpha);
        virtual double getAlpha() const;
        virtual void setHue(double newHue);
        virtual double getHue() const;
        virtual void setSaturation(double newSaturation);
        virtual double getSaturation() const;
        virtual void setLuminance(double newLuminance);
        virtual double getLuminance() const;
};

}

}
