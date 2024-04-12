/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Lookup3.i                       Vector mapping: Lookup (interface).
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
#include "geoutils/Lookup3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

class Lookup3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Lookup3ClassInfo();
        virtual ~Lookup3ClassInfo();
};

class Lookup3
: public Ionflux::GeoUtils::Mapping::Vector3Mapping
{
    public:
		static const unsigned int DEFAULT_NUM_ENTRIES;
		static const Ionflux::Mapping::Range CLAMP_RANGE;
        
        Lookup3();
		Lookup3(const Ionflux::GeoUtils::Mapping::Lookup3& other);
        Lookup3(Ionflux::GeoUtils::Mapping::Vector3Mapping* initSource, 
        unsigned int initNumEntries = DEFAULT_NUM_ENTRIES);
        virtual ~Lookup3();
        virtual void update(unsigned int numEntries = DEFAULT_NUM_ENTRIES);
        virtual void addEntries(const Ionflux::GeoUtils::Vector3Vector& 
        newEntries, unsigned int numEntries = 0);
        virtual Ionflux::GeoUtils::Vector3 
        call(Ionflux::Mapping::MappingValue value) const;
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::Mapping::Lookup3* copy() const;
		static Ionflux::GeoUtils::Mapping::Lookup3* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Mapping::Lookup3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;        
        virtual unsigned int getNumEntries() const;
        virtual Ionflux::GeoUtils::Vector3* getEntry(unsigned int 
        elementIndex = 0) const;
		virtual int findEntry(Ionflux::GeoUtils::Vector3* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Vector3*>& getEntries();
        virtual void addEntry(Ionflux::GeoUtils::Vector3* addElement);        
        virtual void removeEntry(Ionflux::GeoUtils::Vector3* 
        removeElement);
		virtual void removeEntryIndex(unsigned int removeIndex);
		virtual void clearEntries();
        virtual void setSource(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        newSource);
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* getSource() 
        const;
};

}

}

}
