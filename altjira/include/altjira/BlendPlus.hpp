#ifndef IONFLUX_ALTJIRA_BLENDPLUS
#define IONFLUX_ALTJIRA_BLENDPLUS
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BlendPlus.hpp                   Color blender (Plus) (header).
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

#include "altjira/ColorBlender.hpp"

namespace Ionflux
{

namespace Altjira
{

/// Class information for class BlendPlus.
class BlendPlusClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		BlendPlusClassInfo();
		/// Destructor.
		virtual ~BlendPlusClassInfo();
};

/** Color blender (Plus).
 * \ingroup altjira
 *
 * A color blender that implements the Plus method. This method adds the 
 * source color to the destination color (see 
 * http://www.w3.org/TR/2004/WD-SVG12-20041027/rendering.html for details).
 */
class BlendPlus
: public Ionflux::Altjira::ColorBlender
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const BlendPlusClassInfo blendPlusClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new BlendPlus object.
		 */
		BlendPlus();
		
		/** Constructor.
		 *
		 * Construct new BlendPlus object.
		 *
		 * \param other Other object.
		 */
		BlendPlus(const Ionflux::Altjira::BlendPlus& other);
		
		/** Constructor.
		 *
		 * Construct new BlendPlus object.
		 *
		 * \param initColor0 Initial Color 0.
		 * \param initColor1 Initial Color 1.
		 * \param initSourceOpacity Initial source opacity.
		 * \param initTargetOpacity Initial target opacity.
		 */
		BlendPlus(const Ionflux::Altjira::Color& initColor0, const 
		Ionflux::Altjira::Color& initColor1 = Ionflux::Altjira::Color::WHITE, 
		double initSourceOpacity = 1., double initTargetOpacity = 1.);
		
		/** Destructor.
		 *
		 * Destruct BlendPlus object.
		 */
		virtual ~BlendPlus();
		
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
		double newTargetOpacity = 1.) const;
		
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
		Ionflux::Altjira::ByteColorValue& newTargetOpacity = 255) const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::BlendPlus& operator=(const 
		Ionflux::Altjira::BlendPlus& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Altjira::BlendPlus* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Altjira::BlendPlus* upcast(Ionflux::ObjectBase::IFObject*
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
		static Ionflux::Altjira::BlendPlus* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
};

}

}

/** \file BlendPlus.hpp
 * \brief Color blender (Plus) (header).
 */
#endif
