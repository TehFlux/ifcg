/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NoiseMapping.i                  Noise mapping module (interface).
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
#include "ifmapping/NoiseMapping.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

namespace Noise
{

class NoiseMappingClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NoiseMappingClassInfo();
        virtual ~NoiseMappingClassInfo();
};

class NoiseMapping
: public Ionflux::ObjectBase::IFObject, public noise::module::Module
{
    public:
        
        NoiseMapping();
        NoiseMapping(Ionflux::Mapping::Mapping* initFunc, 
        Ionflux::Mapping::MappingValue initScale = 0.5, 
        Ionflux::Mapping::MappingValue initOffset = 0.5, 
        Ionflux::Mapping::MappingValue initResultScale = 2., 
        Ionflux::Mapping::MappingValue initResultOffset = -1.);
        virtual ~NoiseMapping();
        virtual int GetSourceModuleCount() const;
        virtual double GetValue(double x, double y, double z) const;
        virtual void SetSourceModule(const noise::module::Module& 
        sourceModule);
        virtual std::string getString() const;
		static Ionflux::Mapping::Noise::NoiseMapping* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::Noise::NoiseMapping* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
        virtual Ionflux::Mapping::Mapping* getFunc() const;
        virtual void setScale(Ionflux::Mapping::MappingValue newScale);
        virtual Ionflux::Mapping::MappingValue getScale() const;
        virtual void setOffset(Ionflux::Mapping::MappingValue newOffset);
        virtual Ionflux::Mapping::MappingValue getOffset() const;
        virtual void setResultScale(Ionflux::Mapping::MappingValue 
        newResultScale);
        virtual Ionflux::Mapping::MappingValue getResultScale() const;
        virtual void setResultOffset(Ionflux::Mapping::MappingValue 
        newResultOffset);
        virtual Ionflux::Mapping::MappingValue getResultOffset() const;
};

}

}

}
