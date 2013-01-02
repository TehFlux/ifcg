/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SplitSet.i                      Axis split set (interface).
 * =========================================================================

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
#include "geoutils/SplitSet.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class SplitSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SplitSetClassInfo();
        virtual ~SplitSetClassInfo();
};

class SplitSet
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        SplitSet();
		SplitSet(const Ionflux::GeoUtils::SplitSet& other);
        virtual ~SplitSet();
        virtual Ionflux::GeoUtils::SplitVector 
        addSplits(Ionflux::GeoUtils::AxisID axis, unsigned int num = 1);
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::SplitSet* copy() const;
		static Ionflux::GeoUtils::SplitSet* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::GeoUtils::SplitSet* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);        
        virtual unsigned int getNumSplits() const;
        virtual Ionflux::GeoUtils::Split* getSplit(unsigned int 
        elementIndex = 0) const;
		virtual int findSplit(Ionflux::GeoUtils::Split* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Split*>& getSplits();
        virtual void addSplit(Ionflux::GeoUtils::Split* addElement);        
        virtual void removeSplit(Ionflux::GeoUtils::Split* removeElement);
		virtual void removeSplitIndex(unsigned int removeIndex);
		virtual void clearSplits();
};

}

}
