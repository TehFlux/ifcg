/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * DekkerRootFinder.i              Dekker root finder (interface).
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
#include "ifmapping/DekkerRootFinder.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class DekkerRootFinderClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        DekkerRootFinderClassInfo();
        virtual ~DekkerRootFinderClassInfo();
};

class DekkerRootFinder
: public Ionflux::Mapping::RootFinder
{
    public:
        
        DekkerRootFinder();
		DekkerRootFinder(const Ionflux::Mapping::DekkerRootFinder& other);
        virtual ~DekkerRootFinder();
        virtual Ionflux::Mapping::MappingValue 
        findRoot(Ionflux::Mapping::MappingValue a = 0., 
        Ionflux::Mapping::MappingValue b = 0., 
        Ionflux::Mapping::MappingValue delta = 0.0001) const;
        virtual Ionflux::Mapping::MappingValue 
        findRoot(Ionflux::Mapping::MappingValue a, 
        Ionflux::Mapping::MappingValue b, Ionflux::Mapping::MappingValue 
        delta, unsigned int samples, unsigned int maxIters = 50, unsigned 
        int i = 0) const;
        virtual std::string getString() const;
		virtual Ionflux::Mapping::DekkerRootFinder* copy() const;
		static Ionflux::Mapping::DekkerRootFinder* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::DekkerRootFinder* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}
