/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Mapping.i                       Mapping (interface).
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
#include "ifmapping/Mapping.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class MappingClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MappingClassInfo();
        virtual ~MappingClassInfo();
};

class Mapping
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Mapping();
        virtual ~Mapping();
        virtual Ionflux::Mapping::MappingValue 
        operator()(Ionflux::Mapping::MappingValue value) const;
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const = 0;
        virtual Ionflux::Mapping::Sample 
        sample(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::Mapping* upcast(Ionflux::ObjectBase::IFObject* 
		other);
};

}

}
