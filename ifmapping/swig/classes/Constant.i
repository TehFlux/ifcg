/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Constant.i                      Constant mapping (interface).
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
#include "ifmapping/Constant.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class ConstantClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ConstantClassInfo();
        virtual ~ConstantClassInfo();
};

class Constant
: public Ionflux::Mapping::Mapping
{
    public:
        
        Constant();
		Constant(const Ionflux::Mapping::Constant& other);
        Constant(Ionflux::Mapping::MappingValue initConstValue);
        virtual ~Constant();
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const;
        static Ionflux::Mapping::Constant* 
        create(Ionflux::Mapping::MappingValue initConstValue);
		virtual Ionflux::Mapping::Constant* copy() const;
		static Ionflux::Mapping::Constant* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Constant* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setConstValue(Ionflux::Mapping::MappingValue 
        newConstValue);
        virtual Ionflux::Mapping::MappingValue getConstValue() const;
};

}

}
