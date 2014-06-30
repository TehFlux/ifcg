/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Cos.i                           Cosine mapping (interface).
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
#include "ifmapping/Cos.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class CosClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        CosClassInfo();
        virtual ~CosClassInfo();
};

class Cos
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        Cos();
		Cos(const Ionflux::Mapping::Cos& other);
        Cos(Ionflux::Mapping::MappingValue initScale, 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~Cos();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		virtual Ionflux::Mapping::Cos* copy() const;
		static Ionflux::Mapping::Cos* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Cos* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}
