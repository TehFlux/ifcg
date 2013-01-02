/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Accept.i                        Accept method mapping (interface).
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
#include "ifmapping/Accept.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class AcceptClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        AcceptClassInfo();
        virtual ~AcceptClassInfo();
};

class Accept
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        Accept();
		Accept(const Ionflux::Mapping::Accept& other);
        Accept(Ionflux::Mapping::Mapping* initFunc, unsigned int 
        initMaxIters = MAX_ITERATIONS, Ionflux::Mapping::MappingValue 
        initScale = 1., Ionflux::Mapping::MappingValue initOffset = 0.);
        virtual ~Accept();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const;
		virtual Ionflux::Mapping::Accept* copy() const;
		static Ionflux::Mapping::Accept* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Accept* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setMaxIters(unsigned int newMaxIters);
        virtual unsigned int getMaxIters() const;
        virtual void setAcceptRange(const Ionflux::Mapping::Range& 
        newAcceptRange);
        virtual Ionflux::Mapping::Range getAcceptRange() const;
};

}

}
