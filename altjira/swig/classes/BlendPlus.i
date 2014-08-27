/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BlendPlus.i                     Color blender (Plus) (interface).
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
%{
#include "altjira/BlendPlus.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class BlendPlusClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BlendPlusClassInfo();
        virtual ~BlendPlusClassInfo();
};

class BlendPlus
: public Ionflux::Altjira::ColorBlender
{
    public:
        
        BlendPlus();
		BlendPlus(const Ionflux::Altjira::BlendPlus& other);
        BlendPlus(const Ionflux::Altjira::Color& initColor0, const 
        Ionflux::Altjira::Color& initColor1 = 
        Ionflux::Altjira::Color::WHITE, double initSourceOpacity = 1., 
        double initTargetOpacity = 1.);
        virtual ~BlendPlus();
        virtual void blend(Ionflux::Altjira::FloatColor& target, const 
        Ionflux::Altjira::FloatColor& newColor0, const 
        Ionflux::Altjira::FloatColor& newColor1, double newSourceOpacity = 
        1., double newTargetOpacity = 1.) const;
        virtual void blend(Ionflux::Altjira::ByteColor& target, const 
        Ionflux::Altjira::ByteColor& newColor0, const 
        Ionflux::Altjira::ByteColor& newColor1, const 
        Ionflux::Altjira::ByteColorValue& newSourceOpacity = 255, const 
        Ionflux::Altjira::ByteColorValue& newTargetOpacity = 255) const;
		virtual Ionflux::Altjira::BlendPlus* copy() const;
		static Ionflux::Altjira::BlendPlus* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::Altjira::BlendPlus* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}
