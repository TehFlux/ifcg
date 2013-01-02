/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Compose3.i                      Vector mapping: Compose (interface).
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
#include "geoutils/Compose3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

class Compose3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Compose3ClassInfo();
        virtual ~Compose3ClassInfo();
};

class Compose3
: public Ionflux::GeoUtils::Mapping::Vector3Mapping
{
    public:
        
        Compose3();
		Compose3(const Ionflux::GeoUtils::Mapping::Compose3& other);
        Compose3(Ionflux::Mapping::Mapping* initFuncX0, 
        Ionflux::Mapping::Mapping* initFuncX1 = 0, 
        Ionflux::Mapping::Mapping* initFuncX2 = 0);
        virtual ~Compose3();
        virtual void setFuncs(Ionflux::Mapping::Mapping* newFuncX0 = 0, 
        Ionflux::Mapping::Mapping* newFuncX1 = 0, 
        Ionflux::Mapping::Mapping* newFuncX2 = 0);
        virtual void setFuncsEqual(Ionflux::Mapping::Mapping* newFunc = 0);
        virtual Ionflux::GeoUtils::Vector3 
        call(Ionflux::Mapping::MappingValue value) const;
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::Mapping::Compose3* copy() const;
		static Ionflux::GeoUtils::Mapping::Compose3* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Mapping::Compose3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setFuncX0(Ionflux::Mapping::Mapping* newFuncX0);
        virtual Ionflux::Mapping::Mapping* getFuncX0() const;
        virtual void setFuncX1(Ionflux::Mapping::Mapping* newFuncX1);
        virtual Ionflux::Mapping::Mapping* getFuncX1() const;
        virtual void setFuncX2(Ionflux::Mapping::Mapping* newFuncX2);
        virtual Ionflux::Mapping::Mapping* getFuncX2() const;
};

}

}

}
