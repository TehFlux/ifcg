/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Chain.i                         Chain mapping (interface).
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
#include "ifmapping/Chain.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class ChainClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ChainClassInfo();
        virtual ~ChainClassInfo();
};

class Chain
: public Ionflux::Mapping::Mapping
{
    public:
        
        Chain();
		Chain(const Ionflux::Mapping::Chain& other);
        Chain(const Ionflux::Mapping::MappingVector& initFuncs);
        virtual ~Chain();
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const;
		virtual Ionflux::Mapping::Chain* copy() const;
		static Ionflux::Mapping::Chain* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Chain* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);        
        virtual unsigned int getNumFuncs() const;
        virtual Ionflux::Mapping::Mapping* getFunc(unsigned int 
        elementIndex = 0) const;
		virtual int findFunc(Ionflux::Mapping::Mapping* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::Mapping*>& getFuncs();
        virtual void addFunc(Ionflux::Mapping::Mapping* addElement);        
        virtual void removeFunc(Ionflux::Mapping::Mapping* removeElement);
		virtual void removeFuncIndex(unsigned int removeIndex);
		virtual void clearFuncs();
};

}

}
