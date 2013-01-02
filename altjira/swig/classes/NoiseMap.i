/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NoiseMap.i                      Noise map (interface).
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
#include "altjira/NoiseMap.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

namespace Noise
{

class NoiseMapClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NoiseMapClassInfo();
        virtual ~NoiseMapClassInfo();
};

class NoiseMap
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        NoiseMap();
		NoiseMap(const Ionflux::Altjira::Noise::NoiseMap& other);
        NoiseMap(noise::utils::NoiseMap* initNoiseMap);
        virtual ~NoiseMap();
        virtual Ionflux::Mapping::Range getRange();
        virtual void rescale(const Ionflux::Mapping::Range& range = 
        Ionflux::Mapping::DEFAULT_CLAMP_RANGE);
        virtual void transform(double offsetIn = 0., double scaleIn = 1., 
        double offsetOut = 0., double scaleOut = 1., 
        Ionflux::Mapping::Mapping* func = 0);
        virtual void render(Ionflux::Altjira::Image& image, 
        Ionflux::Altjira::ColorBand* colors = 0);
        virtual std::string getString() const;
		virtual Ionflux::Altjira::Noise::NoiseMap* copy() const;
		static Ionflux::Altjira::Noise::NoiseMap* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Altjira::Noise::NoiseMap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setNoiseMap(noise::utils::NoiseMap* newNoiseMap);
        virtual noise::utils::NoiseMap* getNoiseMap() const;
};

}

}

}
