#ifndef IONFLUX_ALTJIRA_NOISEMAP
#define IONFLUX_ALTJIRA_NOISEMAP
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NoiseMap.hpp                    Noise map (header).
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

#include "noise/noiseutils.h"
#include "ifmapping/types.hpp"
#include "ifmapping/constants.hpp"
#include "ifmapping/Mapping.hpp"
#include "altjira/types.hpp"
#include "altjira/constants.hpp"
#include "altjira/Image.hpp"
#include "altjira/ColorBand.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Altjira
{

namespace Noise
{

/// Class information for class NoiseMap.
class NoiseMapClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		NoiseMapClassInfo();
		/// Destructor.
		virtual ~NoiseMapClassInfo();
};

/** Noise map.
 * \ingroup altjira
 *
 * Wrapper around a noise::utils::NoiseMap that integrates the object with 
 * Altjira.
 */
class NoiseMap
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// libnoise noise map.
		noise::utils::NoiseMap* noiseMap;
		
	public:
		/// Class information instance.
		static const NoiseMapClassInfo noiseMapClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new NoiseMap object.
		 */
		NoiseMap();
		
		/** Constructor.
		 *
		 * Construct new NoiseMap object.
		 *
		 * \param other Other object.
		 */
		NoiseMap(const Ionflux::Altjira::Noise::NoiseMap& other);
		
		/** Constructor.
		 *
		 * Construct new NoiseMap object.
		 *
		 * \param initNoiseMap libnoise noise map.
		 */
		NoiseMap(noise::utils::NoiseMap* initNoiseMap);
		
		/** Destructor.
		 *
		 * Destruct NoiseMap object.
		 */
		virtual ~NoiseMap();
		
		/** Get range of values.
		 *
		 * Get the range of values in the noise map.
		 *
		 * \return Range of values.
		 */
		virtual Ionflux::Mapping::Range getRange();
		
		/** Rescale.
		 *
		 * Rescale the noise map so its values fall within the specified 
		 * range.
		 *
		 * \param range Range.
		 */
		virtual void rescale(const Ionflux::Mapping::Range& range = 
		Ionflux::Mapping::DEFAULT_CLAMP_RANGE);
		
		/** Transform.
		 *
		 * Transform the noise map using the specified input offset and scale,
		 * mapping, and output offset and scale.
		 *
		 * \param offsetIn Offset (input).
		 * \param scaleIn Scale (input).
		 * \param offsetOut Offset (output).
		 * \param scaleOut Scale (output).
		 * \param func Mapping.
		 */
		virtual void transform(double offsetIn = 0., double scaleIn = 1., double 
		offsetOut = 0., double scaleOut = 1., Ionflux::Mapping::Mapping* func = 
		0);
		
		/** Render.
		 *
		 * Render the noise map to an image using the specified color band to 
		 * map noise values to colors. If no color band is specified, a 
		 * grayscale range from black to white will be used.
		 *
		 * \param image Image.
		 * \param colors Color band.
		 */
		virtual void render(Ionflux::Altjira::Image& image, 
		Ionflux::Altjira::ColorBand* colors = 0);
		
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
		virtual Ionflux::Altjira::Noise::NoiseMap& operator=(const 
		Ionflux::Altjira::Noise::NoiseMap& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Altjira::Noise::NoiseMap* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Altjira::Noise::NoiseMap* 
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
		static Ionflux::Altjira::Noise::NoiseMap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get libnoise noise map.
		 *
		 * \return Current value of libnoise noise map.
		 */
		virtual noise::utils::NoiseMap* getNoiseMap() const;
		
		/** Set libnoise noise map.
		 *
		 * Set new value of libnoise noise map.
		 *
		 * \param newNoiseMap New value of libnoise noise map.
		 */
		virtual void setNoiseMap(noise::utils::NoiseMap* newNoiseMap);
};

}

}

}

/** \file NoiseMap.hpp
 * \brief Noise map (header).
 */
#endif
