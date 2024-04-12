/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ArcLength.i                     Arc length mapping (interface).
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
#include "ifmapping/ArcLength.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class ArcLengthClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ArcLengthClassInfo();
        virtual ~ArcLengthClassInfo();
};

class ArcLength
: public Ionflux::Mapping::Mapping
{
    public:
		static const Ionflux::Mapping::MappingValue DEFAULT_RELATIVE_ERROR;
		static const unsigned int DEFAULT_MAX_NUM_ITERATIONS;
        
        ArcLength();
		ArcLength(const Ionflux::Mapping::ArcLength& other);
        ArcLength(Ionflux::Mapping::PointMapping* initFunc, 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::MappingValue initScale = 1., 
        Ionflux::Mapping::MappingValue initRefParam = 0., 
        Ionflux::Mapping::MappingValue initRelativeError = 
        DEFAULT_RELATIVE_ERROR, Ionflux::Mapping::MappingValue 
        initMaxNumIterations = DEFAULT_MAX_NUM_ITERATIONS);
        virtual ~ArcLength();
        virtual std::string getValueString() const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const;
		virtual Ionflux::Mapping::ArcLength* copy() const;
		static Ionflux::Mapping::ArcLength* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::Mapping::ArcLength* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::Mapping::ArcLength* 
		create(Ionflux::Mapping::PointMapping* initFunc, 
		Ionflux::Mapping::MappingValue initOffset = 0., 
		Ionflux::Mapping::MappingValue initScale = 1., 
		Ionflux::Mapping::MappingValue initRefParam = 0., 
		Ionflux::Mapping::MappingValue initRelativeError = 
		DEFAULT_RELATIVE_ERROR, Ionflux::Mapping::MappingValue 
		initMaxNumIterations = DEFAULT_MAX_NUM_ITERATIONS, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setFunc(Ionflux::Mapping::PointMapping* newFunc);
        virtual Ionflux::Mapping::PointMapping* getFunc() const;
        virtual void setOffset(Ionflux::Mapping::MappingValue newOffset);
        virtual Ionflux::Mapping::MappingValue getOffset() const;
        virtual void setScale(Ionflux::Mapping::MappingValue newScale);
        virtual Ionflux::Mapping::MappingValue getScale() const;
        virtual void setRefParam(Ionflux::Mapping::MappingValue 
        newRefParam);
        virtual Ionflux::Mapping::MappingValue getRefParam() const;
        virtual void setRelativeError(Ionflux::Mapping::MappingValue 
        newRelativeError);
        virtual Ionflux::Mapping::MappingValue getRelativeError() const;
        virtual void setMaxNumIterations(unsigned int newMaxNumIterations);
        virtual unsigned int getMaxNumIterations() const;
};

}

}
