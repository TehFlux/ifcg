/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Lookup.i                        Lookup mapping (interface).
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
#include "ifmapping/Lookup.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class LookupClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        LookupClassInfo();
        virtual ~LookupClassInfo();
};

class Lookup
: public Ionflux::Mapping::ChainableMapping
{
    public:
		static const unsigned int DEFAULT_NUM_ENTRIES;
		static const Ionflux::Mapping::Range CLAMP_RANGE;
        
        Lookup();
		Lookup(const Ionflux::Mapping::Lookup& other);
        Lookup(Ionflux::Mapping::Mapping* initSource, unsigned int 
        initNumEntries = DEFAULT_NUM_ENTRIES, 
        Ionflux::Mapping::MappingValue initScale = 0., 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        Lookup(const Ionflux::Mapping::MappingValueVector& initEntries, 
        unsigned int initNumEntries = 0, Ionflux::Mapping::Mapping* 
        initSource = 0, Ionflux::Mapping::MappingValue initScale = 0., 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~Lookup();
        virtual void update(unsigned int numEntries = DEFAULT_NUM_ENTRIES);
        virtual void addEntries(const Ionflux::Mapping::MappingValueVector&
        newEntries, unsigned int numEntries = 0);
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		virtual Ionflux::Mapping::Lookup* copy() const;
		static Ionflux::Mapping::Lookup* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Lookup* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;        
        virtual unsigned int getNumEntries() const;
        virtual Ionflux::Mapping::MappingValue getEntry(unsigned int 
        elementIndex = 0) const;
		virtual int findEntry(Ionflux::Mapping::MappingValue needle, unsigned int
		occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::MappingValue>& getEntries();
        virtual void addEntry(Ionflux::Mapping::MappingValue addElement);        
        virtual void removeEntry(Ionflux::Mapping::MappingValue 
        removeElement);
		virtual void removeEntryIndex(unsigned int removeIndex);
		virtual void clearEntries();
        virtual void setSource(Ionflux::Mapping::Mapping* newSource);
        virtual Ionflux::Mapping::Mapping* getSource() const;
};

}

}
