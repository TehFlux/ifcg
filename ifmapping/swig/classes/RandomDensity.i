/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * RandomDensity.i                 Random mapping (interface).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
 * 
 * IFMapping - Ionflux Mapping Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFMapping - Ionflux Mapping Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */
%{
#include "ifmapping/RandomDensity.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class RandomDensityClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        RandomDensityClassInfo();
        virtual ~RandomDensityClassInfo();
};

class RandomDensity
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        RandomDensity();
		RandomDensity(const Ionflux::Mapping::RandomDensity& other);
        RandomDensity(Ionflux::Mapping::Mapping* initFunc, 
        Ionflux::Mapping::MappingValue initMaxIters = MAX_ITERATIONS, 
        Ionflux::Mapping::MappingValue initScale = 1., 
        Ionflux::Mapping::MappingValue initOffset = 0.);
        virtual ~RandomDensity();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const;
		virtual Ionflux::Mapping::RandomDensity* copy() const;
		static Ionflux::Mapping::RandomDensity* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::RandomDensity* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setMaxIters(unsigned int newMaxIters);
        virtual unsigned int getMaxIters() const;
};

}

}
