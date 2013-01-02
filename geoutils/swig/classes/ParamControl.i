/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ParamControl.i                  Parameter control (interface).
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
#include "geoutils/ParamControl.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class ParamControlClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ParamControlClassInfo();
        virtual ~ParamControlClassInfo();
};

class ParamControl
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        ParamControl();
		ParamControl(const Ionflux::GeoUtils::TransformNodes::ParamControl& other);
        ParamControl(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        initNode, Ionflux::ObjectBase::IFParamID initParamID = "", 
        Ionflux::Mapping::Mapping* initFunc = 0, unsigned int initCoord = 
        COORDINATE_NOT_SET);
        virtual ~ParamControl();
        virtual void call(Ionflux::Mapping::MappingValue value) const;
        virtual void operator()(Ionflux::Mapping::MappingValue value) 
        const;
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::ParamControl* copy() const;
		static Ionflux::GeoUtils::TransformNodes::ParamControl* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::ParamControl* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void 
        setNode(Ionflux::GeoUtils::TransformNodes::TransformNode* newNode);
        virtual Ionflux::GeoUtils::TransformNodes::TransformNode* getNode()
        const;
        virtual void setParamID(const Ionflux::ObjectBase::IFParamID& 
        newParamID);
        virtual Ionflux::ObjectBase::IFParamID getParamID() const;
        virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
        virtual Ionflux::Mapping::Mapping* getFunc() const;
        virtual void setCoord(unsigned int newCoord);
        virtual unsigned int getCoord() const;
};

}

}

}
