#ifndef IONFLUX_ALTJIRA_COLORBAND
#define IONFLUX_ALTJIRA_COLORBAND
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ColorBand.hpp                   Color band (header).
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

#include "altjira/utils.hpp"
#include "altjira/imageutils.hpp"
#include "ifmapping/Piecewise.hpp"
#include "ifmapping/Constant.hpp"
#include "ifmapping/Linear.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Altjira
{

class ColorSet;

/// Class information for class ColorBand.
class ColorBandClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ColorBandClassInfo();
		/// Destructor.
		virtual ~ColorBandClassInfo();
};

/** Color band.
 * \ingroup altjira
 *
 * A collection of colors and positions which can be used to interpolate 
 * between any number of colors over the range 0...1. At this time,  only 
 * linear interpolation is supported.
 */
class ColorBand
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Mapping for the red component.
		Ionflux::Mapping::Piecewise* red;
		/// Mapping for the green component.
		Ionflux::Mapping::Piecewise* green;
		/// Mapping for the blue component.
		Ionflux::Mapping::Piecewise* blue;
		/// Mapping for the alpha component.
		Ionflux::Mapping::Piecewise* alpha;
		/// Color stops..
		std::vector<Ionflux::Altjira::ColorStop> colorStops;
		
		/** Initialize mappings.
		 *
		 * Initialize the mappings for the color band.
		 */
		virtual void initMappings();
		
	public:
		/// Class information instance.
		static const ColorBandClassInfo colorBandClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ColorBand object.
		 */
		ColorBand();
		
		/** Constructor.
		 *
		 * Construct new ColorBand object.
		 *
		 * \param other Other object.
		 */
		ColorBand(const Ionflux::Altjira::ColorBand& other);
		
		/** Constructor.
		 *
		 * Construct new ColorBand object.
		 *
		 * \param initColorStops Color stops.
		 */
		ColorBand(Ionflux::Altjira::ColorStopVector initColorStops);
		
		/** Destructor.
		 *
		 * Destruct ColorBand object.
		 */
		virtual ~ColorBand();
		
		/** Clear the color band.
		 *
		 * Clears all data in the color band.
		 */
		virtual void clear();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Update the color band.
		 *
		 * Updates the color band according to the currently set color stops.
		 */
		virtual void update();
		
		/** Evaluate the color band..
		 *
		 * Evaluate the color band at the specified value and store the result
		 * in the target color.
		 *
		 * \param value Value.
		 * \param target Target color.
		 */
		virtual void eval(double value, Ionflux::Altjira::FloatColor& target);
		
		/** Evaluate the color band..
		 *
		 * Evaluate the color band at the specified value and store the result
		 * in the target color.
		 *
		 * \param value Value.
		 * \param target Target color.
		 */
		virtual void eval(double value, Ionflux::Altjira::ByteColor& target);
		
		/** Evaluate the color band..
		 *
		 * Evaluate the color band at the specified value and store the result
		 * in the target color.
		 *
		 * \param value Value.
		 * \param target Target color.
		 */
		virtual void eval(double value, Ionflux::Altjira::Color& target);
		
		/** Evaluate the color band.
		 *
		 * Evaluate the color band at the specified value.
		 *
		 * \param value Value.
		 *
		 * \return Resulting color.
		 */
		virtual Ionflux::Altjira::Color operator()(double value);
		
		/** Sample colors.
		 *
		 * Sample colors from the color band at regular intervals and store 
		 * them in a color set.
		 *
		 * \param numSamples number of samples.
		 * \param target Where to store the colors.
		 */
		virtual void sample(unsigned int numSamples, Ionflux::Altjira::ColorSet& 
		target);
		
		/** Create color band: Rainbow.
		 *
		 * Create a color band using evenly spaced rainbow colors. The caller 
		 * is responsible for managing the new color band.
		 *
		 * \return New color band.
		 */
		static Ionflux::Altjira::ColorBand* rainbow();
		
		/** Create color band: Flame.
		 *
		 * Create a color band using evenly spaced flame colors. The caller is
		 * responsible for managing the new color band.
		 *
		 * \return New color band.
		 */
		static Ionflux::Altjira::ColorBand* flame();
		
		/** Create color band: Ice.
		 *
		 * Create a color band using evenly spaced ice colors. The caller is 
		 * responsible for managing the new color band.
		 *
		 * \return New color band.
		 */
		static Ionflux::Altjira::ColorBand* ice();
		
		/** Create color band: Terrain.
		 *
		 * Create a color band using terrain colors. The caller is responsible
		 * for managing the new color band.
		 *
		 * \return New color band.
		 */
		static Ionflux::Altjira::ColorBand* terrain();
		
		/** Create color band: Heat.
		 *
		 * Create a color band using heat colors. The caller is responsible 
		 * for managing the new color band.
		 *
		 * \return New color band.
		 */
		static Ionflux::Altjira::ColorBand* heat();
		
		/** Create color band: Glow.
		 *
		 * Create a color band that suggests a 'glowing' base color with a 
		 * luminance transition from dark to light.
		 *
		 * \param color Base color.
		 * \param maxL Maximum luminance.
		 *
		 * \return New color band.
		 */
		static Ionflux::Altjira::ColorBand* glow(const Ionflux::Altjira::Color& 
		color, double maxL = 1.);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::ColorBand& operator=(const 
		Ionflux::Altjira::ColorBand& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Altjira::ColorBand* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Altjira::ColorBand* upcast(Ionflux::ObjectBase::IFObject*
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
		static Ionflux::Altjira::ColorBand* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new ColorBand object.
		 *
		 * \param initColorStops Color stops.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Altjira::ColorBand* 
		create(Ionflux::Altjira::ColorStopVector initColorStops, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get number of colorStops.
		 *
		 * \return Number of colorStops.
		 */
		virtual unsigned int getNumColorStops() const;
		
		/** Get colorStop.
		 *
		 * Get the colorStop at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return ColorStop at specified index.
		 */
		virtual Ionflux::Altjira::ColorStop getColorStop(unsigned int 
		elementIndex = 0) const;
		
		/** Find colorStop.
		 *
		 * Find the specified occurence of a colorStop.
		 *
		 * \param needle ColorStop to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the colorStop, or -1 if the colorStop cannot be 
		 * found.
		 */
		virtual int findColorStop(Ionflux::Altjira::ColorStop needle, unsigned 
		int occurence = 1) const;
        
		/** Get color stops..
		 *
		 * \return color stops..
		 */
		virtual std::vector<Ionflux::Altjira::ColorStop>& getColorStops();
		
		/** Add colorStop.
		 *
		 * Add a colorStop.
		 *
		 * \param addElement ColorStop to be added.
		 */
		virtual void addColorStop(Ionflux::Altjira::ColorStop addElement);
		
		/** Remove colorStop.
		 *
		 * Remove a colorStop.
		 *
		 * \param removeElement ColorStop to be removed.
		 */
		virtual void removeColorStop(Ionflux::Altjira::ColorStop removeElement);
		
		/** Remove colorStop.
		 *
		 * Remove a colorStop.
		 *
		 * \param removeIndex ColorStop to be removed.
		 */
		virtual void removeColorStopIndex(unsigned int removeIndex);
		
		/** Clear colorStops.
		 *
		 * Clear all colorStops.
		 */
		virtual void clearColorStops();
};

}

}

/** \file ColorBand.hpp
 * \brief Color band (header).
 */
#endif
