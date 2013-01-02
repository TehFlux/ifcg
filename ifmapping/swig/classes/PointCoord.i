/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PointCoord.i                    Point coordinate mapping (interface).
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
#include "ifmapping/PointCoord.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class PointCoordClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PointCoordClassInfo();
        virtual ~PointCoordClassInfo();
};

class PointCoord
: public Ionflux::Mapping::Mapping
{
    public:
        
        PointCoord();
		PointCoord(const Ionflux::Mapping::PointCoord& other);
        PointCoord(Ionflux::Mapping::PointMapping* initFunc, 
        Ionflux::Mapping::CoordinateID initCoord = Ionflux::Mapping::C_X, 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::MappingValue initScale = 1.);
        virtual ~PointCoord();
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const;
		virtual Ionflux::Mapping::PointCoord* copy() const;
		static Ionflux::Mapping::PointCoord* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::PointCoord* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setFunc(Ionflux::Mapping::PointMapping* newFunc);
        virtual Ionflux::Mapping::PointMapping* getFunc() const;
        virtual void setCoord(Ionflux::Mapping::CoordinateID newCoord);
        virtual Ionflux::Mapping::CoordinateID getCoord() const;
        virtual void setOffset(Ionflux::Mapping::MappingValue newOffset);
        virtual Ionflux::Mapping::MappingValue getOffset() const;
        virtual void setScale(Ionflux::Mapping::MappingValue newScale);
        virtual Ionflux::Mapping::MappingValue getScale() const;
};

}

}
