#ifndef IONFLUX_ALTJIRA_BLENDSRCOVER
#define IONFLUX_ALTJIRA_BLENDSRCOVER
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BlendSrcOver.hpp                Color blender (SrcOver) (header).
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

#include "altjira/ColorBlender.hpp"

namespace Ionflux
{

namespace Altjira
{

/// Class information for class BlendSrcOver.
class BlendSrcOverClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		BlendSrcOverClassInfo();
		/// Destructor.
		virtual ~BlendSrcOverClassInfo();
};

/** Color blender (SrcOver).
 * \ingroup altjira
 *
 * A color blender that implements the SrcOver method. This method 
 * composites the source color over the destination color (see 
 * http://www.w3.org/TR/2004/WD-SVG12-20041027/rendering.html for details).
 */
class BlendSrcOver
: public Ionflux::Altjira::ColorBlender
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const BlendSrcOverClassInfo blendSrcOverClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new BlendSrcOver object.
		 */
		BlendSrcOver();
		
		/** Constructor.
		 *
		 * Construct new BlendSrcOver object.
		 *
		 * \param other Other object.
		 */
		BlendSrcOver(const Ionflux::Altjira::BlendSrcOver& other);
		
		/** Constructor.
		 *
		 * Construct new BlendSrcOver object.
		 *
		 * \param initColor0 Initial Color 0.
		 * \param initColor1 Initial Color 1.
		 * \param initSourceOpacity Initial source opacity.
		 * \param initTargetOpacity Initial target opacity.
		 */
		BlendSrcOver(const Ionflux::Altjira::Color& initColor0, const 
		Ionflux::Altjira::Color& initColor1 = Ionflux::Altjira::Color::WHITE, 
		double initSourceOpacity = 1., double initTargetOpacity = 1.);
		
		/** Destructor.
		 *
		 * Destruct BlendSrcOver object.
		 */
		virtual ~BlendSrcOver();
		
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
		virtual Ionflux::Altjira::BlendSrcOver& operator=(const 
		Ionflux::Altjira::BlendSrcOver& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Altjira::BlendSrcOver* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Altjira::BlendSrcOver* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
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
		static Ionflux::Altjira::BlendSrcOver* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

/** \file BlendSrcOver.hpp
 * \brief Color blender (SrcOver) (header).
 */
#endif
