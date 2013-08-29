/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Cubic.i                         Cubic mapping (interface).
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
#include "ifmapping/Cubic.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class CubicClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        CubicClassInfo();
        virtual ~CubicClassInfo();
};

class Cubic
: public Ionflux::Mapping::Linear
{
    public:
        
        Cubic();
		Cubic(const Ionflux::Mapping::Cubic& other);
        Cubic(Ionflux::Mapping::MappingValue initLower, 
        Ionflux::Mapping::MappingValue initUpper);
        virtual ~Cubic();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		virtual Ionflux::Mapping::Cubic* copy() const;
		static Ionflux::Mapping::Cubic* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Cubic* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

}

}
