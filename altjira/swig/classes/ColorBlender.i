/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ColorBlender.i                  ColorBlender (interface).
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
#include "altjira/ColorBlender.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class ColorBlenderClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ColorBlenderClassInfo();
        virtual ~ColorBlenderClassInfo();
};

class ColorBlender
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        ColorBlender();
		ColorBlender(const Ionflux::Altjira::ColorBlender& other);
        ColorBlender(const Ionflux::Altjira::Color& initColor0, const 
        Ionflux::Altjira::Color& initColor1 = 
        Ionflux::Altjira::Color::WHITE, double initSourceOpacity = 1., 
        double initTargetOpacity = 1.);
        virtual ~ColorBlender();
        virtual void blend(Ionflux::Altjira::Color& target, const 
        Ionflux::Altjira::Color& newColor0, const Ionflux::Altjira::Color& 
        newColor1, double newSourceOpacity = 1., double newTargetOpacity = 
        1.) const;
        virtual void blend(Ionflux::Altjira::FloatColor& target, const 
        Ionflux::Altjira::FloatColor& newColor0, const 
        Ionflux::Altjira::FloatColor& newColor1, double newSourceOpacity = 
        1., double newTargetOpacity = 1.) const = 0;
        virtual void blend(Ionflux::Altjira::ByteColor& target, const 
        Ionflux::Altjira::ByteColor& newColor0, const 
        Ionflux::Altjira::ByteColor& newColor1, const 
        Ionflux::Altjira::ByteColorValue& newSourceOpacity = 255, const 
        Ionflux::Altjira::ByteColorValue& newTargetOpacity = 255) const;
        virtual void operator()(Ionflux::Altjira::Color& target, const 
        Ionflux::Altjira::Color* newColor0 = 0, const 
        Ionflux::Altjira::Color* newColor1 = 0, const double* 
        newSourceOpacity = 0, const double* newTargetOpacity = 0) const;
        virtual std::string getString() const;
        virtual void setColor0(const Ionflux::Altjira::Color& newColor0);
        virtual Ionflux::Altjira::Color getColor0() const;
        virtual void setColor1(const Ionflux::Altjira::Color& newColor1);
        virtual Ionflux::Altjira::Color getColor1() const;
        virtual void setSourceOpacity(double newSourceOpacity);
        virtual double getSourceOpacity() const;
        virtual void setTargetOpacity(double newTargetOpacity);
        virtual double getTargetOpacity() const;
};

}

}
