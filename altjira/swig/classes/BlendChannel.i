/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BlendChannel.i                  Color blender (Channel) (interface).
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
#include "altjira/BlendChannel.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class BlendChannelClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BlendChannelClassInfo();
        virtual ~BlendChannelClassInfo();
};

class BlendChannel
: public Ionflux::Altjira::ColorBlender
{
    public:
        
        BlendChannel();
		BlendChannel(const Ionflux::Altjira::BlendChannel& other);
        BlendChannel(const Ionflux::Altjira::Color& initColor0, const 
        Ionflux::Altjira::Color& initColor1 = 
        Ionflux::Altjira::Color::WHITE, double initSourceOpacity = 1., 
        double initTargetOpacity = 0., Ionflux::Altjira::ChannelID 
        initSrcChannel = Ionflux::Altjira::CH_VALUE, 
        Ionflux::Altjira::ChannelID initDestChannel = 
        Ionflux::Altjira::CH_VALUE, Ionflux::Altjira::ColorSpace 
        initSrcSpace = Ionflux::Altjira::Color::SPACE_UNDEFINED, 
        Ionflux::Altjira::ColorSpace initDestSpace = 
        Ionflux::Altjira::Color::SPACE_UNDEFINED, 
        Ionflux::Mapping::Mapping* initSrcFunc = 0, 
        Ionflux::Mapping::Mapping* initDestFunc = 0);
        virtual ~BlendChannel();
        virtual void blend(Ionflux::Altjira::FloatColor& target, const 
        Ionflux::Altjira::FloatColor& newColor0, const 
        Ionflux::Altjira::FloatColor& newColor1, double newSourceOpacity = 
        1., double newTargetOpacity = 0.) const;
        virtual void blend(Ionflux::Altjira::ByteColor& target, const 
        Ionflux::Altjira::ByteColor& newColor0, const 
        Ionflux::Altjira::ByteColor& newColor1, const 
        Ionflux::Altjira::ByteColorValue& newSourceOpacity = 255, const 
        Ionflux::Altjira::ByteColorValue& newTargetOpacity = 0) const;
		virtual Ionflux::Altjira::BlendChannel* copy() const;
		static Ionflux::Altjira::BlendChannel* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setSrcFunc(Ionflux::Mapping::Mapping* newSrcFunc);
        virtual Ionflux::Mapping::Mapping* getSrcFunc() const;
        virtual void setDestFunc(Ionflux::Mapping::Mapping* newDestFunc);
        virtual Ionflux::Mapping::Mapping* getDestFunc() const;
        virtual void setSrcChannel(Ionflux::Altjira::ChannelID 
        newSrcChannel);
        virtual Ionflux::Altjira::ChannelID getSrcChannel() const;
        virtual void setDestChannel(Ionflux::Altjira::ChannelID 
        newDestChannel);
        virtual Ionflux::Altjira::ChannelID getDestChannel() const;
        virtual void setSrcSpace(Ionflux::Altjira::ColorSpace newSrcSpace);
        virtual Ionflux::Altjira::ColorSpace getSrcSpace() const;
        virtual void setDestSpace(Ionflux::Altjira::ColorSpace 
        newDestSpace);
        virtual Ionflux::Altjira::ColorSpace getDestSpace() const;
};

}

}
