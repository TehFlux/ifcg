/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * RootFinder.i                    Root finder (interface).
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
#include "ifmapping/RootFinder.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class RootFinderClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        RootFinderClassInfo();
        virtual ~RootFinderClassInfo();
};

class RootFinder
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        RootFinder();
		RootFinder(const Ionflux::Mapping::RootFinder& other);
        virtual ~RootFinder();
        virtual Ionflux::Mapping::MappingValue 
        compareSigns(Ionflux::Mapping::MappingValue a, 
        Ionflux::Mapping::MappingValue b) const;
        virtual void findStartIntervals(Ionflux::Mapping::RangeVector& 
        target, unsigned int samples = 101, Ionflux::Mapping::MappingValue 
        a = 0., Ionflux::Mapping::MappingValue b = 1.) const;
        virtual Ionflux::Mapping::Range findStartInterval(unsigned int 
        samples = 101, Ionflux::Mapping::MappingValue a = 0., 
        Ionflux::Mapping::MappingValue b = 1.) const;
        virtual Ionflux::Mapping::MappingValue 
        operator()(Ionflux::Mapping::MappingValue a = 0., 
        Ionflux::Mapping::MappingValue b = 0., 
        Ionflux::Mapping::MappingValue delta = 0.0001) const;
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        findRoot(Ionflux::Mapping::MappingValue a = 0., 
        Ionflux::Mapping::MappingValue b = 0., 
        Ionflux::Mapping::MappingValue delta = 0.0001) const = 0;
		static Ionflux::Mapping::RootFinder* 
		upcast(Ionflux::ObjectBase::IFObject* other);
        virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
        virtual Ionflux::Mapping::Mapping* getFunc() const;
};

}

}
