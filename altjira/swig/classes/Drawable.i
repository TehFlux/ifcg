/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Drawable.i                      Drawable (interface).
 * =========================================================================

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
%{
#include "altjira/Drawable.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class Pattern;

class DrawableClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        DrawableClassInfo();
        virtual ~DrawableClassInfo();
};

class Drawable
: public Ionflux::Altjira::Image
{
    public:
        
        Drawable();
		Drawable(const Ionflux::Altjira::Drawable& other);
        Drawable(const std::string& fileName);
        Drawable(const Ionflux::Altjira::Image& initImage);
        Drawable(unsigned int initWidth, unsigned int initHeight, bool 
        initAlpha = true, unsigned int initBitsPerSample = 8, 
        Ionflux::Altjira::ColorSpace initColorSpace = 
        Ionflux::Altjira::Color::SPACE_RGB);
        virtual ~Drawable();
        virtual void begin(double originX = 0., double originY = 0.);
        virtual void discard();
        virtual void finish(const Ionflux::Altjira::ColorBlender* blender =
        0);
        virtual void save();
        virtual void restore();
        virtual void translate(double tx, double ty);
        virtual void scale(double sx, double sy);
        virtual void rotate(double phi);
        virtual void newPath();
        virtual void newSubPath();
        virtual void closePath();
        virtual void moveTo(double x, double y);
        virtual void lineTo(double x, double y);
        virtual void curveTo(double x0, double y0, double x1, double y1, 
        double x2, double y2);
        virtual void rectangle(double x, double y, double width, double 
        height);
        virtual void arc(double x, double y, double radius, double phi0 = 
        0., double phi1 = 2. * M_PI);
        virtual void setSourceColor(const Ionflux::Altjira::Color& color);
        virtual void setSource(Ionflux::Altjira::Pattern& pattern);
        virtual void setSourceImage(Ionflux::Altjira::Image* image, double 
        x = 0., double y = 0.);
        virtual void setFillRule(Ionflux::Altjira::FillRule fillRule);
        virtual void stroke(double lineWidth = 1., bool preserve = false);
        virtual void fillPath(bool preserve = false);
        virtual void paint();
        virtual Ionflux::Altjira::ImageRect getTextSize(const std::string& 
        text, const std::string& fontDesc = DEFAULT_FONT_DESCRIPTION, 
        double fontSize = DEFAULT_FONT_SIZE) const;
        virtual void drawText(double x, double y, const std::string& text, 
        const std::string& fontDesc = DEFAULT_FONT_DESCRIPTION, double 
        fontSize = DEFAULT_FONT_SIZE, const Ionflux::Altjira::Color& color 
        = Ionflux::Altjira::Color::BLACK);
        virtual void drawSVG(const std::string& svgData, int originX = 0, 
        int originY = 0);
        virtual void drawSVGFile(const std::string& svgFileName, int 
        originX = 0, int originY = 0);
        virtual bool drawingInProgress() const;
        virtual std::string getString() const;
		virtual Ionflux::Altjira::Drawable* copy() const;
		static Ionflux::Altjira::Drawable* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Altjira::Drawable* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

}

}
