#ifndef IONFLUX_ALTJIRA_BLENDCHANNEL
#define IONFLUX_ALTJIRA_BLENDCHANNEL
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BlendChannel.hpp                Color blender (Channel) (header).
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

#include "ifmapping/Mapping.hpp"
#include "altjira/ColorBlender.hpp"

namespace Ionflux
{

namespace Altjira
{

/// Class information for class BlendChannel.
class BlendChannelClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		BlendChannelClassInfo();
		/// Destructor.
		virtual ~BlendChannelClassInfo();
};

/** Color blender (Channel).
 * \ingroup altjira
 *
 * A color blender that replaces a single channel of the destination color 
 * with a combination of the channel itself and a single channel of the 
 * source color. Source and target opacities can be used to determine how 
 * much the destination channel is affected by either channel. It is 
 * possible to specify mappings that are applied to the source and 
 * destination channels before the operation takes place.
 */
class BlendChannel
: public Ionflux::Altjira::ColorBlender
{
	private:
		
	protected:
		/// Source mapping.
		Ionflux::Mapping::Mapping* srcFunc;
		/// Destination mapping.
		Ionflux::Mapping::Mapping* destFunc;
		/// Source Channel.
		Ionflux::Altjira::ChannelID srcChannel;
		/// Destinantion Channel.
		Ionflux::Altjira::ChannelID destChannel;
		/// Source color space.
		Ionflux::Altjira::ColorSpace srcSpace;
		/// Destination color space.
		Ionflux::Altjira::ColorSpace destSpace;
		
	public:
		/// Class information instance.
		static const BlendChannelClassInfo blendChannelClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new BlendChannel object.
		 */
		BlendChannel();
		
		/** Constructor.
		 *
		 * Construct new BlendChannel object.
		 *
		 * \param other Other object.
		 */
		BlendChannel(const Ionflux::Altjira::BlendChannel& other);
		
		/** Constructor.
		 *
		 * Construct new BlendChannel object.
		 *
		 * \param initColor0 Initial Color 0.
		 * \param initColor1 Initial Color 1.
		 * \param initSourceOpacity Initial source opacity.
		 * \param initTargetOpacity Initial target opacity.
		 * \param initSrcChannel Initial source channel.
		 * \param initDestChannel Initial destination channel.
		 * \param initSrcSpace Initial source color space.
		 * \param initDestSpace Initial destination color space.
		 * \param initSrcFunc Initial source mapping.
		 * \param initDestFunc Initial destination mapping.
		 */
		BlendChannel(const Ionflux::Altjira::Color& initColor0, const 
		Ionflux::Altjira::Color& initColor1 = Ionflux::Altjira::Color::WHITE, 
		double initSourceOpacity = 1., double initTargetOpacity = 0., 
		Ionflux::Altjira::ChannelID initSrcChannel = Ionflux::Altjira::CH_VALUE, 
		Ionflux::Altjira::ChannelID initDestChannel = Ionflux::Altjira::CH_VALUE,
		Ionflux::Altjira::ColorSpace initSrcSpace = 
		Ionflux::Altjira::Color::SPACE_UNDEFINED, Ionflux::Altjira::ColorSpace 
		initDestSpace = Ionflux::Altjira::Color::SPACE_UNDEFINED, 
		Ionflux::Mapping::Mapping* initSrcFunc = 0, Ionflux::Mapping::Mapping* 
		initDestFunc = 0);
		
		/** Destructor.
		 *
		 * Destruct BlendChannel object.
		 */
		virtual ~BlendChannel();
		
		/** Blend colors.
		 *
		 * Blend the colors.
		 *
		 * \param target Target color.
		 * \param newColor0 Color 0.
		 * \param newColor1 Color 1.
		 * \param newSourceOpacity Source opacity.
		 * \param newTargetOpacity Target opacity.
		 */
		virtual void blend(Ionflux::Altjira::FloatColor& target, const 
		Ionflux::Altjira::FloatColor& newColor0, const 
		Ionflux::Altjira::FloatColor& newColor1, double newSourceOpacity = 1., 
		double newTargetOpacity = 0.) const;
		
		/** Blend colors.
		 *
		 * Blend the colors.
		 *
		 * \param target Target color.
		 * \param newColor0 Color 0.
		 * \param newColor1 Color 1.
		 * \param newSourceOpacity Source opacity.
		 * \param newTargetOpacity Target opacity.
		 */
		virtual void blend(Ionflux::Altjira::ByteColor& target, const 
		Ionflux::Altjira::ByteColor& newColor0, const 
		Ionflux::Altjira::ByteColor& newColor1, const 
		Ionflux::Altjira::ByteColorValue& newSourceOpacity = 255, const 
		Ionflux::Altjira::ByteColorValue& newTargetOpacity = 0) const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::BlendChannel& operator=(const 
		Ionflux::Altjira::BlendChannel& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Altjira::BlendChannel* copy() const;
		
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
		static Ionflux::Altjira::BlendChannel* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get source mapping.
		 *
		 * \return Current value of source mapping.
		 */
		virtual Ionflux::Mapping::Mapping* getSrcFunc() const;
		
		/** Set source mapping.
		 *
		 * Set new value of source mapping.
		 *
		 * \param newSrcFunc New value of source mapping.
		 */
		virtual void setSrcFunc(Ionflux::Mapping::Mapping* newSrcFunc);
		
		/** Get destination mapping.
		 *
		 * \return Current value of destination mapping.
		 */
		virtual Ionflux::Mapping::Mapping* getDestFunc() const;
		
		/** Set destination mapping.
		 *
		 * Set new value of destination mapping.
		 *
		 * \param newDestFunc New value of destination mapping.
		 */
		virtual void setDestFunc(Ionflux::Mapping::Mapping* newDestFunc);
		
		/** Get source Channel.
		 *
		 * \return Current value of source Channel.
		 */
		virtual Ionflux::Altjira::ChannelID getSrcChannel() const;
		
		/** Set source Channel.
		 *
		 * Set new value of source Channel.
		 *
		 * \param newSrcChannel New value of source Channel.
		 */
		virtual void setSrcChannel(Ionflux::Altjira::ChannelID newSrcChannel);
		
		/** Get destinantion Channel.
		 *
		 * \return Current value of destinantion Channel.
		 */
		virtual Ionflux::Altjira::ChannelID getDestChannel() const;
		
		/** Set destinantion Channel.
		 *
		 * Set new value of destinantion Channel.
		 *
		 * \param newDestChannel New value of destinantion Channel.
		 */
		virtual void setDestChannel(Ionflux::Altjira::ChannelID newDestChannel);
		
		/** Get source color space.
		 *
		 * \return Current value of source color space.
		 */
		virtual Ionflux::Altjira::ColorSpace getSrcSpace() const;
		
		/** Set source color space.
		 *
		 * Set new value of source color space.
		 *
		 * \param newSrcSpace New value of source color space.
		 */
		virtual void setSrcSpace(Ionflux::Altjira::ColorSpace newSrcSpace);
		
		/** Get destination color space.
		 *
		 * \return Current value of destination color space.
		 */
		virtual Ionflux::Altjira::ColorSpace getDestSpace() const;
		
		/** Set destination color space.
		 *
		 * Set new value of destination color space.
		 *
		 * \param newDestSpace New value of destination color space.
		 */
		virtual void setDestSpace(Ionflux::Altjira::ColorSpace newDestSpace);
};

}

}

/** \file BlendChannel.hpp
 * \brief Color blender (Channel) (header).
 */
#endif
