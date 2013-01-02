/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2009 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * imageutility.cpp               Image utility functions (implementation).
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

#include <cmath>
#include <sstream>
#include "ifmapping/utils.hpp"
#include "altjira/utils.hpp"
#include "altjira/imageutils.hpp"
#include "altjira/AltjiraError.hpp"
#include "altjira/lut_mult.hpp"
#include "altjira/lut_div.hpp"

namespace Ionflux
{

namespace Altjira
{

void init()
{
    static bool initialized = false;
    if (!initialized)
    {
        // Initialize the GObject system.
        g_type_init();
        initialized = true;
    }
}

Ionflux::Altjira::FloatColor createFloatColor(
    Ionflux::Altjira::FloatColorValue c0, 
    Ionflux::Altjira::FloatColorValue c1, 
    Ionflux::Altjira::FloatColorValue c2, 
    Ionflux::Altjira::FloatColorValue alpha, 
    Ionflux::Altjira::ColorSpace space)
{
    FloatColor cr0;
    cr0.c0 = c0;
    cr0.c1 = c1;
    cr0.c2 = c2;
    cr0.alpha = alpha;
    cr0.space = space;
    return cr0;
}

Ionflux::Altjira::ByteColor createByteColor(
    Ionflux::Altjira::ByteColorValue c0, 
    Ionflux::Altjira::ByteColorValue c1, 
    Ionflux::Altjira::ByteColorValue c2, 
    Ionflux::Altjira::ByteColorValue alpha, 
    Ionflux::Altjira::ColorSpace space)
{
    ByteColor cr0;
    cr0.c0 = c0;
    cr0.c1 = c1;
    cr0.c2 = c2;
    cr0.alpha = alpha;
    cr0.space = space;
    return cr0;
}

void floatToByte(const Ionflux::Altjira::FloatColor& c0, 
    Ionflux::Altjira::ByteColor& c1)
{
    c1.c0 = floatToByte(c0.c0);
    c1.c1 = floatToByte(c0.c1);
    c1.c2 = floatToByte(c0.c2);
    c1.alpha = floatToByte(c0.alpha);
    c1.space = c0.space;
}

void byteToFloat(const Ionflux::Altjira::ByteColor& c0, 
    Ionflux::Altjira::FloatColor& c1)
{
    c1.c0 = byteToFloat(c0.c0);
    c1.c1 = byteToFloat(c0.c1);
    c1.c2 = byteToFloat(c0.c2);
    c1.alpha = byteToFloat(c0.alpha);
    c1.space = c0.space;
}

void clamp(Ionflux::Altjira::FloatColor& c, 
    const Ionflux::Mapping::Range& r)
{
    c.c0 = Ionflux::Mapping::clamp(c.c0, r);
    c.c1 = Ionflux::Mapping::clamp(c.c1, r);
    c.c2 = Ionflux::Mapping::clamp(c.c2, r);
    c.alpha = Ionflux::Mapping::clamp(c.alpha, r);
}

void wrap(Ionflux::Altjira::FloatColor& c, 
    const Ionflux::Mapping::Range& r)
{
    c.c0 = Ionflux::Mapping::wrap(c.c0, r);
    c.c1 = Ionflux::Mapping::wrap(c.c1, r);
    c.c2 = Ionflux::Mapping::wrap(c.c2, r);
    c.alpha = Ionflux::Mapping::wrap(c.alpha, r);
}

void toHSV(Ionflux::Altjira::FloatColor& c)
{
    if (c.space == Color::SPACE_HSV)
        return;
    if (c.space != Color::SPACE_RGB)
        toRGB(c);
    double cMax = fmax(c.c0, fmax(c.c1, c.c2));
    double cMin = fmin(c.c0, fmin(c.c1, c.c2));
    double h = 0.;
    double s = 0.;
    // value
    double v = cMax;
    // hue
    if (cMax != cMin)
    {
        if (cMax == c.c0)
        {
            if (c.c1 >= c.c2)
                h = (c.c1 - c.c2) / (6. * (cMax - cMin));
            else
                h = (c.c1 - c.c2) / (6. * (cMax - cMin)) + 1.;
        } else
        if (cMax == c.c1)
            h = (c.c2 - c.c0) / (6. * (cMax - cMin)) + 1. / 3.;
        else
            h = (c.c0 - c.c1) / (6. * (cMax - cMin)) + 2. / 3.;
    }
    // saturation
    if (cMax == 0.)
        s = 0.;
    else
        s = (cMax - cMin) / cMax;
    c.c0 = h;
    c.c1 = s;
    c.c2 = v;
    /* <---- DEBUG ----- //
    std::cerr << "[toHSV] DEBUG: h = " << h << ", s = " << s << ", v = " 
        << v << std::endl;
    // ----- DEBUG ----> */
    c.space = Color::SPACE_HSV;
}

void toRGB(Ionflux::Altjira::FloatColor& c)
{
    if (c.space == Color::SPACE_RGB)
        return;
    if (c.space == Color::SPACE_HSV)
    {
        // HSV to RGB.
        if (c.c1 == 0.)
        {
            // zero saturation
            c.c0 = c.c2;
            c.c1 = c.c2;
            c.space = Color::SPACE_RGB;
            return;
        }
        if (c.c0 == 1.)
            c.c0 = 0.;
        int hi = static_cast<int>(floor(6. * c.c0)) % 6;
        double f = 6. * c.c0 - floor(6. * c.c0);
        double p = c.c2 * (1. - c.c1);
        double q = c.c2 * (1. - f * c.c1);
        double t = c.c2 * (1. - c.c1 * (1. - f));
        if (hi == 0)
        {
            c.c0 = c.c2;
            c.c1 = t;
            c.c2 = p;
        } else
        if (hi == 1)
        {
            c.c0 = q;
            c.c1 = c.c2;
            c.c2 = p;
        } else
        if (hi == 2)
        {
            c.c0 = p;
            c.c1 = c.c2;
            c.c2 = t;
        } else
        if (hi == 3)
        {
            c.c0 = p;
            c.c1 = q;
        } else
        if (hi == 4)
        {
            c.c0 = t;
            c.c1 = p;
        } else
        if (hi == 5)
        {
            c.c0 = c.c2;
            c.c1 = p;
            c.c2 = q;
        }
        c.space = Color::SPACE_RGB;
    } else
    if (c.space == Color::SPACE_HSL)
    {
        // HSL to RGB.
        if (c.c1 == 0.)
        {
            // zero saturation
            c.c0 = c.c2;
            c.c1 = c.c2;
            c.space = Color::SPACE_RGB;
            return;
        }
        double q = 0.;
        if (c.c2 < 0.5)
            q = c.c2  * (1. + c.c1);
        else
            q = c.c2 + c.c1 - c.c2 * c.c1;
        double p = 2. * c.c2 - q;
        double t[] = { c.c0 + 1. / 3., c.c0, c.c0 - 1. / 3. };
        double cx[] = { 0., 0., 0. };
        for (unsigned int i = 0; i < 3; i++)
        {
            if (t[i] < 0.)
                t[i] += 1.;
            else
            if (t[i] > 1.)
                t[i] -= 1.;
            if (t[i] < (1. / 6.))
                cx[i] = p + ((q - p) * 6. * t[i]);
            else
            if ((t[i] >= (1. / 6.)) && (t[i] < 0.5))
                cx[i] = q;
            else
            if ((t[i] >= 0.5) && (t[i] < (2. / 3.)))
                cx[i] = p + ((q - p) * ((2. / 3.) - t[i]) * 6.);
            else
                cx[i] = p;
        }
        c.c0 = cx[0];
        c.c1 = cx[1];
        c.c2 = cx[2];
        c.space = Color::SPACE_RGB;
    }
}

void toHSL(Ionflux::Altjira::FloatColor& c)
{
    if (c.space == Color::SPACE_HSL)
        return;
    if (c.space != Color::SPACE_RGB)
        toRGB(c);
    double cMax = fmax(c.c0, fmax(c.c1, c.c2));
    double cMin = fmin(c.c0, fmin(c.c1, c.c2));
    double h = 0.;
    double s = 0.;
    // value
    double l = 0.5 * (cMax + cMin);
    // hue
    if (cMax != cMin)
    {
        if (cMax == c.c0)
        {
            if (c.c1 >= c.c2)
                h = (c.c1 - c.c2) / (6. * (cMax - cMin));
            else
                h = (c.c1 - c.c2) / (6. * (cMax - cMin)) + 1.;
        } else
        if (cMax == c.c1)
            h = (c.c2 - c.c0) / (6. * (cMax - cMin)) + 1. / 3.;
        else
            h = (c.c0 - c.c1) / (6. * (cMax - cMin)) + 2. / 3.;
    }
    // saturation
    if ((l == 0.) || (cMax == cMin))
        s = 0.;
    else
    if ((l > 0.) && (l <= 0.5))
        s = (cMax - cMin) / (2. * l);
    else
        s = (cMax - cMin) / (2. * (1. - l));
    c.c0 = h;
    c.c1 = s;
    c.c2 = l;
    c.space = Color::SPACE_HSL;
}

void toColorSpace(Ionflux::Altjira::FloatColor& c, 
    Ionflux::Altjira::ColorSpace space)
{
    if ((c.space == space)
        || (space == Color::SPACE_UNDEFINED))
        return;
    if (space == Color::SPACE_RGB)
        toRGB(c);
    else
    if (space == Color::SPACE_HSV)
        toHSV(c);
    else
    if (space == Color::SPACE_HSL)
        toHSL(c);
}

void toHSV(Ionflux::Altjira::ByteColor& c)
{
    FloatColor c0;
    byteToFloat(c, c0);
    toHSV(c0);
    floatToByte(c0, c);
}

void toRGB(Ionflux::Altjira::ByteColor& c)
{
    FloatColor c0;
    byteToFloat(c, c0);
    toRGB(c0);
    floatToByte(c0, c);
}

void toHSL(Ionflux::Altjira::ByteColor& c)
{
    FloatColor c0;
    byteToFloat(c, c0);
    toHSL(c0);
    floatToByte(c0, c);
}

void toColorSpace(Ionflux::Altjira::ByteColor& c, 
    Ionflux::Altjira::ColorSpace space)
{
    if ((c.space == space)
        || (space == Color::SPACE_UNDEFINED))
        return;
    FloatColor c0;
    byteToFloat(c, c0);
    toColorSpace(c0, space);
    floatToByte(c0, c);
}

void copy(const Ionflux::Altjira::FloatColor& s, 
    Ionflux::Altjira::FloatColor& t)
{
    t.c0 = s.c0;
    t.c1 = s.c1;
    t.c2 = s.c2;
    t.alpha = s.alpha;
    t.space = s.space;
}

void multiply(Ionflux::Altjira::FloatColor& c, double value)
{
    c.c0 *= value;
    c.c1 *= value;
    c.c2 *= value;
}

void preMultiply(Ionflux::Altjira::FloatColor& c)
{
    multiply(c, c.alpha);
}

void divideAlpha(Ionflux::Altjira::FloatColor& c)
{
    multiply(c, 1. / c.alpha);
}

Ionflux::Altjira::FloatColorValue getComponent(
    Ionflux::Altjira::FloatColor& c, Ionflux::Altjira::ChannelID channel)
{
    if ((channel == CH_RED) 
        || (channel == CH_HUE))
        return c.c0;
    else
    if ((channel == CH_GREEN) 
        || (channel == CH_SATURATION))
        return c.c1;
    else
    if ((channel == CH_BLUE) 
        || (channel == CH_VALUE) 
        || (channel == CH_LUMINANCE))
        return c.c2;
    return c.alpha;
}

void setComponent(Ionflux::Altjira::FloatColor& c, 
    Ionflux::Altjira::ChannelID channel, 
    Ionflux::Altjira::FloatColorValue value)
{
    if ((channel == CH_RED) 
        || (channel == CH_HUE))
        c.c0 = value;
    else
    if ((channel == CH_GREEN) 
        || (channel == CH_SATURATION))
        c.c1 = value;
    else
    if ((channel == CH_BLUE) 
        || (channel == CH_VALUE) 
        || (channel == CH_LUMINANCE))
        c.c2 = value;
    else
        c.alpha = value;
}

void colorToAlpha(Ionflux::Altjira::FloatColor& c, 
    const Ionflux::Altjira::FloatColor& refColor)
{
    // Inspired by GIMP color-to-alpha.c.
    ColorSpace cs0 = c.space;
    toRGB(c);
    FloatColor ref0;
    copy(refColor, ref0);
    toRGB(ref0);
    
    FloatColor alpha;
    alpha.alpha = c.alpha;
    
    if (refColor.c0 < 0.0001)
        alpha.c0 = c.c0;
    else 
    if (c.c0 > refColor.c0)
        alpha.c0 = (c.c0 - refColor.c0) / (1.0 - refColor.c0);
    else 
    if (c.c0 < refColor.c0)
        alpha.c0 = (refColor.c0 - c.c0) / refColor.c0;
    else 
        alpha.c0 = 0.0;
    
    if (refColor.c1 < 0.0001)
        alpha.c1 = c.c1;
    else 
    if (c.c1 > refColor.c1)
        alpha.c1 = (c.c1 - refColor.c1) / (1.0 - refColor.c1);
    else 
    if (c.c1 < refColor.c1)
        alpha.c1 = (refColor.c1 - c.c1) / (refColor.c1);
    else 
        alpha.c1 = 0.0;
    
    if (refColor.c2 < 0.0001)
        alpha.c2 = c.c2;
    else 
    if (c.c2 > refColor.c2)
        alpha.c2 = (c.c2 - refColor.c2) / (1.0 - refColor.c2);
    else 
    if (c.c2 < refColor.c2)
        alpha.c2 = (refColor.c2 - c.c2) / (refColor.c2);
    else alpha.c2 = 0.0;
    
    if (alpha.c0 > alpha.c1)
    {
        if (alpha.c0 > alpha.c2)
            c.alpha = alpha.c0;
        else
            c.alpha = alpha.c2;
    } else
    if (alpha.c1 > alpha.c2)
        c.alpha = alpha.c1;
    else
        c.alpha = alpha.c2;
    
    if (c.alpha < 0.0001)
        return;
    
    c.c0 = (c.c0 - refColor.c0) / c.alpha + refColor.c0;
    c.c1 = (c.c1 - refColor.c1) / c.alpha + refColor.c1;
    c.c2 = (c.c2 - refColor.c2) / c.alpha + refColor.c2;
    
    c.alpha *= alpha.alpha;
    
    toColorSpace(c, cs0);
}

void copy(const Ionflux::Altjira::ByteColor& s, 
    Ionflux::Altjira::ByteColor& t)
{
    t.c0 = s.c0;
    t.c1 = s.c1;
    t.c2 = s.c2;
    t.alpha = s.alpha;
    t.space = s.space;
}

void multiply(Ionflux::Altjira::ByteColor& c, double value)
{
    c.c0 = floatToByte(byteToFloat(c.c0) * value);
    c.c1 = floatToByte(byteToFloat(c.c1) * value);
    c.c2 = floatToByte(byteToFloat(c.c2) * value);
}

void multiply(Ionflux::Altjira::ByteColor& c, 
    Ionflux::Altjira::ByteColorValue value)
{
    c.c0 = LUT_MULT[256 * value + c.c0];
    c.c1 = LUT_MULT[256 * value + c.c1];
    c.c2 = LUT_MULT[256 * value + c.c2];
}

void preMultiply(Ionflux::Altjira::ByteColor& c)
{
    multiply(c, c.alpha);
}

void divideAlpha(Ionflux::Altjira::ByteColor& c)
{
    c.c0 = LUT_DIV[256 * c.c0 + c.alpha];
    c.c1 = LUT_DIV[256 * c.c1 + c.alpha];
    c.c2 = LUT_DIV[256 * c.c2 + c.alpha];
}

Ionflux::Altjira::ByteColorValue getComponent(
    Ionflux::Altjira::ByteColor& c, Ionflux::Altjira::ChannelID channel)
{
    if ((channel == CH_RED) 
        || (channel == CH_HUE))
        return c.c0;
    else
    if ((channel == CH_GREEN) 
        || (channel == CH_SATURATION))
        return c.c1;
    else
    if ((channel == CH_BLUE) 
        || (channel == CH_VALUE) 
        || (channel == CH_LUMINANCE))
        return c.c2;
    return c.alpha;
}

void setComponent(Ionflux::Altjira::ByteColor& c, 
    Ionflux::Altjira::ChannelID channel, 
    Ionflux::Altjira::ByteColorValue value)
{
    if ((channel == CH_RED) 
        || (channel == CH_HUE))
        c.c0 = value;
    else
    if ((channel == CH_GREEN) 
        || (channel == CH_SATURATION))
        c.c1 = value;
    else
    if ((channel == CH_BLUE) 
        || (channel == CH_VALUE) 
        || (channel == CH_LUMINANCE))
        c.c2 = value;
    else
        c.alpha = value;
}

Ionflux::ObjectBase::UInt32 toUInt(const Ionflux::Altjira::ByteColor& c, 
    bool preMultiplied)
{
    ByteColor c0;
    copy(c, c0);
    if (preMultiplied)
        preMultiply(c0);
    Ionflux::ObjectBase::UInt32 result = 0;
    result |= (static_cast<Ionflux::ObjectBase::UInt32>(c0.alpha) << 24);
    result |= (static_cast<Ionflux::ObjectBase::UInt32>(c0.c0) << 16);
    result |= (static_cast<Ionflux::ObjectBase::UInt32>(c0.c1) << 8);
    result |= static_cast<Ionflux::ObjectBase::UInt32>(c0.c2);
    return result;
}

void fromUInt(Ionflux::ObjectBase::UInt32 v, Ionflux::Altjira::ByteColor& c, 
    bool preMultiplied)
{
    ColorSpace s = c.space;
    c.space = Color::SPACE_RGB;
    c.alpha = (v >> 24) & 0xff;
    c.c0 = (v >> 16) & 0xff;
    c.c1 = (v >> 8) & 0xff;
    c.c2 = v & 0xff;
    if (preMultiplied)
        divideAlpha(c);
    if (s != c.space)
        toColorSpace(c, s);
}

std::string colorSpaceToString(const Ionflux::Altjira::ColorSpace& space)
{
    if (space == Color::SPACE_RGB)
        return "RGB";
    if (space == Color::SPACE_HSV)
        return "HSV";
    if (space == Color::SPACE_HSL)
        return "HSL";
    return "<unknown>";
}

std::string getString(const Ionflux::Altjira::FloatColor& c)
{
    std::ostringstream result;
    result << "FloatColor[" << c.c0 << ", " << c.c1 << ", " << c.c2 
        << ", " << c.alpha << "; " << colorSpaceToString(c.space) << "]";
    return result.str();
}

std::string getString(const Ionflux::Altjira::ByteColor& c)
{
    std::ostringstream result;
    result << "ByteColor[" << static_cast<int>(c.c0) << ", " 
        << static_cast<int>(c.c1) << ", " << static_cast<int>(c.c2) 
        << ", " << static_cast<int>(c.alpha) << "; " 
        << colorSpaceToString(c.space) << "]";
    return result.str();
}

bool operator==(const Ionflux::Altjira::ColorStop& s0, 
    const Ionflux::Altjira::ColorStop& s1)
{
    return (s0.color == s1.color) && (s0.param == s1.param);
}

void createColors(Ionflux::Altjira::ColorVector& target, 
    const Ionflux::Altjira::FloatColor& c0, 
    const Ionflux::Altjira::FloatColor& c1, 
    unsigned int stepsC0, unsigned int stepsC1, unsigned int stepsC2, 
    unsigned int stepsAlpha)
{
    FloatColor c2;
    copy(c1, c2);
    if (c2.space != c0.space)
        toColorSpace(c2, c0.space);
    double dc0 = 0.;
    double dc1 = 0.;
    double dc2 = 0.;
    double dAlpha = 0.;
    if (stepsC0 > 1)
        dc0 = (c2.c0 - c0.c0) / (stepsC0 - 1);
    if (stepsC1 > 1)
        dc1 = (c2.c1 - c0.c1) / (stepsC1 - 1);
    if (stepsC2 > 1)
        dc2 = (c2.c2 - c0.c2) / (stepsC2 - 1);
    if (stepsAlpha > 1)
        dAlpha = (c2.alpha - c0.alpha) / (stepsAlpha - 1);
    FloatColor cr;
    cr.space = c0.space;
    for (unsigned int i = 0; i < stepsC0; i++)
    {
        if (stepsC0 == 1)
            cr.c0 = 0.5 * (c2.c0 + c0.c0);
        else
            cr.c0 = c0.c0 + i * dc0;
        for (unsigned int j = 0; j < stepsC1; j++)
        {
            if (stepsC1 == 1)
                cr.c1 = 0.5 * (c2.c1 + c0.c1);
            else
                cr.c1 = c0.c1 + j * dc1;
            for (unsigned int k = 0; k < stepsC2; k++)
            {
                if (stepsC2 == 1)
                    cr.c2 = 0.5 * (c2.c2 + c0.c2);
                else
                    cr.c2 = c0.c2 + k * dc2;
                for (unsigned int l = 0; l < stepsAlpha; l++)
                {
                    if (stepsAlpha == 1)
                        cr.alpha = 0.5 * (c2.alpha + c0.alpha);
                    else
                        cr.alpha = c0.alpha + l * dAlpha;
                    target.push_back(Color(cr));
                }
            }
        }
    }
}

Ionflux::Altjira::ColorSpace  getColorSpaceForChannel(
    Ionflux::Altjira::ChannelID channel, Ionflux::Altjira::ColorSpace hint)
{
    // Unambiguous channels.
    if ((channel == CH_RED) 
        || (channel == CH_GREEN) 
        || (channel == CH_BLUE))
        return Ionflux::Altjira::Color::SPACE_RGB;
    else
    if (channel == CH_VALUE)
        return Ionflux::Altjira::Color::SPACE_HSV;
    else
    if (channel == CH_LUMINANCE)
        return Ionflux::Altjira::Color::SPACE_HSL;
    // Ambiguous channels.
    if ((channel == CH_HUE) 
        || (channel == CH_SATURATION))
    {
        // HSV or HSL.
        if (hint == Ionflux::Altjira::Color::SPACE_HSL)
            return hint;
        else
            return Ionflux::Altjira::Color::SPACE_HSV;
    }
    if (hint == Ionflux::Altjira::Color::SPACE_UNDEFINED)
        return Ionflux::Altjira::Color::SPACE_RGB;
    return hint;
}

}

}

/** \file imageutility.cpp
 * \brief Image utility functions (implementation).
 */
