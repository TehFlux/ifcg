/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Duplicate.i                     Transform node: Duplicate (interface).
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
#include "geoutils/Duplicate.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class DuplicateClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        DuplicateClassInfo();
        virtual ~DuplicateClassInfo();
};

class Duplicate
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
		static const unsigned int DEFAULT_NUM_DUPLICATES;
		static const Ionflux::Mapping::Range CLAMP_RANGE;
        
        Duplicate();
		Duplicate(const Ionflux::GeoUtils::TransformNodes::Duplicate& other);
        Duplicate(unsigned int initNumDuplicates, 
        Ionflux::Mapping::Mapping* initFunc = 0, const 
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Duplicate();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::Duplicate* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Duplicate* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Duplicate* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual void setParam(Ionflux::ObjectBase::IFParamID paramID, 
		Ionflux::Mapping::MappingValue paramValue);
		virtual Ionflux::Mapping::MappingValue 
		getParam(Ionflux::ObjectBase::IFParamID paramID);
        virtual void setNumDuplicates(unsigned int newNumDuplicates);
        virtual unsigned int getNumDuplicates() const;
        virtual void setNumDuplicatesParam(Ionflux::Mapping::MappingValue 
        newNumDuplicatesParam);
        virtual Ionflux::Mapping::MappingValue getNumDuplicatesParam() 
        const;
        virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
        virtual Ionflux::Mapping::Mapping* getFunc() const;
};

}

}

}
