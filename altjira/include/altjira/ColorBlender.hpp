#ifndef IONFLUX_ALTJIRA_COLORBLENDER
#define IONFLUX_ALTJIRA_COLORBLENDER
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ColorBlender.hpp                ColorBlender (header).
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

#include "altjira/Color.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Altjira
{

/// Class information for class ColorBlender.
class ColorBlenderClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ColorBlenderClassInfo();
		/// Destructor.
		virtual ~ColorBlenderClassInfo();
};

/** Color blender.
 * \ingroup altjira
 *
 * An object that can be used to blend two colors. This is used as an 
 * abstract base class for color blenders that use a specific blending 
 * method. Colors and source and target opacity are taken from the internal
 * state of the blender if they are not specified on the invocation of the 
 * blender.
 */
class ColorBlender
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Color 0.
		Ionflux::Altjira::Color color0;
		/// Color 1.
		Ionflux::Altjira::Color color1;
		/// Source opacity.
		double sourceOpacity;
		/// Target opacity.
		double targetOpacity;
		
	public:
		/// Class information instance.
		static const ColorBlenderClassInfo colorBlenderClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ColorBlender object.
		 */
		ColorBlender();
		
		/** Constructor.
		 *
		 * Construct new ColorBlender object.
		 *
		 * \param other Other object.
		 */
		ColorBlender(const Ionflux::Altjira::ColorBlender& other);
		
		/** Constructor.
		 *
		 * Construct new ColorBlender object.
		 *
		 * \param initColor0 Initial Color 0.
		 * \param initColor1 Initial Color 1.
		 * \param initSourceOpacity Initial source opacity.
		 * \param initTargetOpacity Initial target opacity.
		 */
		ColorBlender(const Ionflux::Altjira::Color& initColor0, const 
		Ionflux::Altjira::Color& initColor1 = Ionflux::Altjira::Color::WHITE, 
		double initSourceOpacity = 1., double initTargetOpacity = 1.);
		
		/** Destructor.
		 *
		 * Destruct ColorBlender object.
		 */
		virtual ~ColorBlender();
		
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
		virtual void blend(Ionflux::Altjira::Color& target, const 
		Ionflux::Altjira::Color& newColor0, const Ionflux::Altjira::Color& 
		newColor1, double newSourceOpacity = 1., double newTargetOpacity = 1.) 
		const;
		
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
		double newTargetOpacity = 1.) const = 0;
		
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
		
		/** Blend colors.
		 *
		 * Blend the colors.
		 *
		 * \param target Target color.
		 * \param newColor0 Color 0.
		 * \param newColor1 Color 1.
		 * \param newSourceOpacity Source opacity.
		 * \param newTargetOpacity Target opacity.
		 *
		 * \return Blended color.
		 */
		virtual void operator()(Ionflux::Altjira::Color& target, const 
		Ionflux::Altjira::Color* newColor0 = 0, const Ionflux::Altjira::Color* 
		newColor1 = 0, const double* newSourceOpacity = 0, const double* 
		newTargetOpacity = 0) const;
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::ColorBlender& operator=(const 
		Ionflux::Altjira::ColorBlender& other);
		
		/** Get color 0.
		 *
		 * \return Current value of color 0.
		 */
		virtual Ionflux::Altjira::Color getColor0() const;
		
		/** Set color 0.
		 *
		 * Set new value of color 0.
		 *
		 * \param newColor0 New value of color 0.
		 */
		virtual void setColor0(const Ionflux::Altjira::Color& newColor0);
		
		/** Get color 1.
		 *
		 * \return Current value of color 1.
		 */
		virtual Ionflux::Altjira::Color getColor1() const;
		
		/** Set color 1.
		 *
		 * Set new value of color 1.
		 *
		 * \param newColor1 New value of color 1.
		 */
		virtual void setColor1(const Ionflux::Altjira::Color& newColor1);
		
		/** Get source opacity.
		 *
		 * \return Current value of source opacity.
		 */
		virtual double getSourceOpacity() const;
		
		/** Set source opacity.
		 *
		 * Set new value of source opacity.
		 *
		 * \param newSourceOpacity New value of source opacity.
		 */
		virtual void setSourceOpacity(double newSourceOpacity);
		
		/** Get target opacity.
		 *
		 * \return Current value of target opacity.
		 */
		virtual double getTargetOpacity() const;
		
		/** Set target opacity.
		 *
		 * Set new value of target opacity.
		 *
		 * \param newTargetOpacity New value of target opacity.
		 */
		virtual void setTargetOpacity(double newTargetOpacity);
};

}

}

/** \file ColorBlender.hpp
 * \brief ColorBlender (header).
 */
#endif
