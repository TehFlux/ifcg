/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Accept3.i                       Vector mapping: Accept (interface).
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
#include "geoutils/Accept3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

class Accept3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Accept3ClassInfo();
        virtual ~Accept3ClassInfo();
};

class Accept3
: public Ionflux::GeoUtils::Mapping::Vector3Mapping
{
    public:
        
        Accept3();
		Accept3(const Ionflux::GeoUtils::Mapping::Accept3& other);
        Accept3(Ionflux::GeoUtils::Mapping::Vector3Mapping* initSource, 
        Ionflux::Mapping::MappingValue initMaxIters = 
        Ionflux::Mapping::MAX_ITERATIONS);
        virtual ~Accept3();
        virtual Ionflux::GeoUtils::Vector3 
        call(Ionflux::Mapping::MappingValue value) const;
        virtual std::string getString() const;
        virtual bool checkCondition(const Ionflux::GeoUtils::Vector3& v) 
        const = 0;
		static Ionflux::GeoUtils::Mapping::Accept3* 
		upcast(Ionflux::ObjectBase::IFObject* other);
        virtual void setMaxIters(unsigned int newMaxIters);
        virtual unsigned int getMaxIters() const;
        virtual void setSource(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        newSource);
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* getSource() 
        const;
};

}

}

}
