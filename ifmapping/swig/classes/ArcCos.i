/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ArcCos.i                        Arc cosine mapping (interface).
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
#include "ifmapping/ArcCos.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class ArcCosClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ArcCosClassInfo();
        virtual ~ArcCosClassInfo();
};

class ArcCos
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        ArcCos();
		ArcCos(const Ionflux::Mapping::ArcCos& other);
        ArcCos(Ionflux::Mapping::MappingValue initScale, 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~ArcCos();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		virtual Ionflux::Mapping::ArcCos* copy() const;
		static Ionflux::Mapping::ArcCos* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::ArcCos* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

}

}
