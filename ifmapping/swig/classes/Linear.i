/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Linear.i                        Linear mapping (interface).
 * =========================================================================

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
#include "ifmapping/Linear.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class LinearClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        LinearClassInfo();
        virtual ~LinearClassInfo();
};

class Linear
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        Linear();
		Linear(const Ionflux::Mapping::Linear& other);
        Linear(Ionflux::Mapping::MappingValue initLower, 
        Ionflux::Mapping::MappingValue initUpper, 
        Ionflux::Mapping::MappingValue initScale = 1., 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~Linear();
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
        static Ionflux::Mapping::Linear* 
        create(Ionflux::Mapping::MappingValue initLower, 
        Ionflux::Mapping::MappingValue initUpper);
		virtual Ionflux::Mapping::Linear* copy() const;
		static Ionflux::Mapping::Linear* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Linear* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setLower(Ionflux::Mapping::MappingValue newLower);
        virtual Ionflux::Mapping::MappingValue getLower() const;
        virtual void setUpper(Ionflux::Mapping::MappingValue newUpper);
        virtual Ionflux::Mapping::MappingValue getUpper() const;
};

}

}
