/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PointMapping.i                  Point mapping (interface).
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
#include "ifmapping/PointMapping.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class PointMappingClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PointMappingClassInfo();
        virtual ~PointMappingClassInfo();
};

class PointMapping
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Mapping::MappingValue DEFAULT_PRECISION;
        
        PointMapping();
        virtual ~PointMapping();
        virtual Ionflux::Mapping::Point 
        evalCoord(Ionflux::Mapping::MappingValue value, 
        Ionflux::Mapping::CoordinateID coord = Ionflux::Mapping::C_X, 
        Ionflux::Mapping::MappingValue precision = 
        Ionflux::Mapping::PointMapping::DEFAULT_PRECISION);
        virtual Ionflux::Mapping::Point 
        operator()(Ionflux::Mapping::MappingValue value);
        virtual std::string getString() const;
        virtual Ionflux::Mapping::Point call(Ionflux::Mapping::MappingValue
        value) = 0;
		static Ionflux::Mapping::PointMapping* 
		upcast(Ionflux::ObjectBase::IFObject* other);
};

}

}
