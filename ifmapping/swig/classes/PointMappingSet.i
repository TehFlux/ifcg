/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PointMappingSet.i               PointMappingSet (interface).
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
#include "ifmapping/PointMappingSet.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class PointMapping;

class PointMappingSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PointMappingSetClassInfo();
        virtual ~PointMappingSetClassInfo();
};

class PointMappingSet
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        PointMappingSet();
		PointMappingSet(const Ionflux::Mapping::PointMappingSet& other);
        PointMappingSet(const Ionflux::Mapping::PointMappingVector& 
        initMappings);
        virtual ~PointMappingSet();
        virtual void addMappings(const 
        Ionflux::Mapping::PointMappingVector& newMappings);
        virtual std::string getString() const;
		virtual Ionflux::Mapping::PointMappingSet* copy() const;
		static Ionflux::Mapping::PointMappingSet* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::PointMappingSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;        
        virtual unsigned int getNumMappings() const;
        virtual Ionflux::Mapping::PointMapping* getMapping(unsigned int 
        elementIndex = 0) const;
		virtual int findMapping(Ionflux::Mapping::PointMapping* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::PointMapping*>& 
        getMappings();
        virtual void addMapping(Ionflux::Mapping::PointMapping* 
        addElement);        
        virtual void removeMapping(Ionflux::Mapping::PointMapping* 
        removeElement);
		virtual void removeMappingIndex(unsigned int removeIndex);
		virtual void clearMappings();
};

}

}
