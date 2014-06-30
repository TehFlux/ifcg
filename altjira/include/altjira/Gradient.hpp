#ifndef IONFLUX_ALTJIRA_GRADIENT
#define IONFLUX_ALTJIRA_GRADIENT
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Gradient.hpp                    Gradient (header).
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

#include "altjira/types.hpp"
#include "altjira/constants.hpp"
#include "altjira/Color.hpp"
#include "altjira/ColorBand.hpp"
#include "altjira/Pattern.hpp"

namespace Ionflux
{

namespace Altjira
{

/// Class information for class Gradient.
class GradientClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		GradientClassInfo();
		/// Destructor.
		virtual ~GradientClassInfo();
};

/** Gradient.
 * \ingroup geoutils
 *
 * A gradient pattern to be used in drawing operations.
 */
class Gradient
: public Ionflux::Altjira::Pattern
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const GradientClassInfo gradientClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Gradient object.
		 */
		Gradient();
		
		/** Constructor.
		 *
		 * Construct new Gradient object.
		 *
		 * \param other Other object.
		 */
		Gradient(const Ionflux::Altjira::Gradient& other);
		
		/** Destructor.
		 *
		 * Destruct Gradient object.
		 */
		virtual ~Gradient();
		
		/** Add color stop.
		 *
		 * Add a color stop to the gradient.
		 *
		 * \param offset Offset.
		 * \param color Color.
		 */
		virtual void addColorStop(double offset, const Ionflux::Altjira::Color& 
		color);
		
		/** Get number of color stops.
		 *
		 * Get the number of color stops in the gradient.
		 *
		 * \return Number of color stops.
		 */
		virtual unsigned int getNumColorStops() const;
		
		/** Set color stops from color band.
		 *
		 * Set color stops from a color band. If \c sampleFunc is not set, the
		 * color stops will be taken from \c colorBand as is. Otherwise, \c 
		 * colorBand will be sampled using the specified number of uniformly 
		 * spaced sampling points from the range [0..1], transformed by \c 
		 * sampleFunc.
		 *
		 * \param colorBand Color band.
		 * \param sampleFunc Sampling function.
		 * \param numSamples Number of samples.
		 */
		virtual void setFromColorBand(Ionflux::Altjira::ColorBand& colorBand, 
		Ionflux::Mapping::Mapping* sampleFunc = 0, unsigned int numSamples = 20);
		
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
		virtual Ionflux::Altjira::Gradient& operator=(const 
		Ionflux::Altjira::Gradient& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Altjira::Gradient* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Altjira::Gradient* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::Altjira::Gradient* create(Ionflux::ObjectBase::IFObject* 
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

/** \file Gradient.hpp
 * \brief Gradient (header).
 */
#endif
