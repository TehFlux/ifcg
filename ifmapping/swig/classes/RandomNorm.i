/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * RandomNorm.i                    Random mapping (interface).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
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
#include "ifmapping/RandomNorm.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class RandomNormClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        RandomNormClassInfo();
        virtual ~RandomNormClassInfo();
};

class RandomNorm
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        RandomNorm();
		RandomNorm(const Ionflux::Mapping::RandomNorm& other);
        RandomNorm(Ionflux::Mapping::MappingValue initMean, 
        Ionflux::Mapping::MappingValue initStdDev = 1., 
        Ionflux::Mapping::MappingValue initScale = 1., 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~RandomNorm();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		virtual Ionflux::Mapping::RandomNorm* copy() const;
		static Ionflux::Mapping::RandomNorm* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::RandomNorm* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setMean(Ionflux::Mapping::MappingValue newMean);
        virtual Ionflux::Mapping::MappingValue getMean() const;
        virtual void setStdDev(Ionflux::Mapping::MappingValue newStdDev);
        virtual Ionflux::Mapping::MappingValue getStdDev() const;
};

}

}
