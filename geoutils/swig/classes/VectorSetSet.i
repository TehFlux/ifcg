/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * VectorSetSet.i                  Set of vector sets (interface).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
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
#include "geoutils/VectorSetSet.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VectorSet;

class VectorSetSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VectorSetSetClassInfo();
        virtual ~VectorSetSetClassInfo();
};

class VectorSetSet
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        VectorSetSet();
		VectorSetSet(const Ionflux::GeoUtils::VectorSetSet& other);
        VectorSetSet(Ionflux::GeoUtils::VectorSetVector& initVectorSets);
        virtual ~VectorSetSet();
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::VectorSetSet* copy() const;
		static Ionflux::GeoUtils::VectorSetSet* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::VectorSetSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::VectorSetSet* 
		create(Ionflux::GeoUtils::VectorSetVector& initVectorSets, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumVectorSets() const;
        virtual Ionflux::GeoUtils::VectorSet* getVectorSet(unsigned int 
        elementIndex = 0) const;
		virtual int findVectorSet(Ionflux::GeoUtils::VectorSet* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::VectorSet*>& 
        getVectorSets();
        virtual void addVectorSet(Ionflux::GeoUtils::VectorSet* 
        addElement);
		virtual Ionflux::GeoUtils::VectorSet* addVectorSet();
		virtual void addVectorSets(std::vector<Ionflux::GeoUtils::VectorSet*>& 
		newVectorSets);
		virtual void addVectorSets(Ionflux::GeoUtils::VectorSetSet* 
		newVectorSets);        
        virtual void removeVectorSet(Ionflux::GeoUtils::VectorSet* 
        removeElement);
		virtual void removeVectorSetIndex(unsigned int removeIndex);
		virtual void clearVectorSets();
};

namespace XMLUtils
{

void getVectorSetSet(const std::string& data, 
Ionflux::GeoUtils::VectorSetSet& target);

}

}

}
