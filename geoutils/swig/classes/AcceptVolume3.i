/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * AcceptVolume3.i                 Vector mapping: Accept volume 
 * (interface).
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
#include "geoutils/AcceptVolume3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

class AcceptVolume3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        AcceptVolume3ClassInfo();
        virtual ~AcceptVolume3ClassInfo();
};

class AcceptVolume3
: public Ionflux::GeoUtils::Mapping::Accept3
{
    public:
        
        AcceptVolume3();
		AcceptVolume3(const Ionflux::GeoUtils::Mapping::AcceptVolume3& other);
        AcceptVolume3(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        initSource, Ionflux::GeoUtils::Object3* initRefObject, 
        Ionflux::Mapping::MappingValue initMaxIters = 
        Ionflux::Mapping::MAX_ITERATIONS);
        virtual ~AcceptVolume3();
        virtual std::string getString() const;
        virtual bool checkCondition(const Ionflux::GeoUtils::Vector3& v) 
        const;
		virtual Ionflux::GeoUtils::Mapping::AcceptVolume3* copy() const;
		static Ionflux::GeoUtils::Mapping::AcceptVolume3* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Mapping::AcceptVolume3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setRefObject(Ionflux::GeoUtils::Object3* 
        newRefObject);
        virtual Ionflux::GeoUtils::Object3* getRefObject() const;
};

}

}

}
