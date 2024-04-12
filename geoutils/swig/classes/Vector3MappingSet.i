/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector3MappingSet.i             Vector3MappingSet (interface).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
 * 
 * GeoUtils - Ionflux' Geometry Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with GeoUtils - Ionflux' Geometry Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */
%{
#include "geoutils/Vector3MappingSet.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Vector3MappingSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vector3MappingSetClassInfo();
        virtual ~Vector3MappingSetClassInfo();
};

class Vector3MappingSet
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Vector3MappingSet();
		Vector3MappingSet(const Ionflux::GeoUtils::Vector3MappingSet& other);
        Vector3MappingSet(const Ionflux::GeoUtils::Vector3MappingVector& 
        initMappings);
        virtual ~Vector3MappingSet();
        virtual void addMappings(const 
        Ionflux::GeoUtils::Vector3MappingVector& newMappings);
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::Vector3MappingSet* copy() const;
		static Ionflux::GeoUtils::Vector3MappingSet* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Vector3MappingSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;        
        virtual unsigned int getNumMappings() const;
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        getMapping(unsigned int elementIndex = 0) const;
		virtual int findMapping(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
		needle, unsigned int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Mapping::Vector3Mapping*>& 
        getMappings();
        virtual void addMapping(Ionflux::GeoUtils::Mapping::Vector3Mapping*
        addElement);        
        virtual void 
        removeMapping(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        removeElement);
		virtual void removeMappingIndex(unsigned int removeIndex);
		virtual void clearMappings();
};

}

}
