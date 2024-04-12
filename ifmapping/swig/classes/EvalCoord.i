/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * EvalCoord.i                     Evaluate coordinate point mapping 
 * (interface).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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
#include "ifmapping/EvalCoord.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class EvalCoordClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        EvalCoordClassInfo();
        virtual ~EvalCoordClassInfo();
};

class EvalCoord
: public Ionflux::Mapping::PointMapping
{
    public:
        
        EvalCoord();
		EvalCoord(const Ionflux::Mapping::EvalCoord& other);
        EvalCoord(Ionflux::Mapping::PointMapping* initFunc, 
        Ionflux::Mapping::CoordinateID initCoord = Ionflux::Mapping::C_X, 
        Ionflux::Mapping::Point initOffset = 
        Ionflux::Mapping::Point::ORIGIN, Ionflux::Mapping::Point initScale 
        = Ionflux::Mapping::Point::ONES, Ionflux::Mapping::MappingValue 
        initParamOffset = 0., Ionflux::Mapping::MappingValue initParamScale
        = 1., Ionflux::Mapping::MappingValue initPrecision = 
        Ionflux::Mapping::PointMapping::DEFAULT_PRECISION);
        virtual ~EvalCoord();
        virtual std::string getString() const;
        virtual Ionflux::Mapping::Point call(Ionflux::Mapping::MappingValue
        value);
		virtual Ionflux::Mapping::EvalCoord* copy() const;
		static Ionflux::Mapping::EvalCoord* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::Mapping::EvalCoord* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setFunc(Ionflux::Mapping::PointMapping* newFunc);
        virtual Ionflux::Mapping::PointMapping* getFunc() const;
        virtual void setCoord(Ionflux::Mapping::CoordinateID newCoord);
        virtual Ionflux::Mapping::CoordinateID getCoord() const;
        virtual void setOffset(Ionflux::Mapping::Point newOffset);
        virtual Ionflux::Mapping::Point getOffset() const;
        virtual void setScale(Ionflux::Mapping::Point newScale);
        virtual Ionflux::Mapping::Point getScale() const;
        virtual void setParamOffset(Ionflux::Mapping::MappingValue 
        newParamOffset);
        virtual Ionflux::Mapping::MappingValue getParamOffset() const;
        virtual void setParamScale(Ionflux::Mapping::MappingValue 
        newParamScale);
        virtual Ionflux::Mapping::MappingValue getParamScale() const;
        virtual void setPrecision(Ionflux::Mapping::MappingValue 
        newPrecision);
        virtual Ionflux::Mapping::MappingValue getPrecision() const;
};

}

}
