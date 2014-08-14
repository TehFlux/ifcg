/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Scale.i                         Transform node: Scale (interface).
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
#include "geoutils/Scale.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class ScaleClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ScaleClassInfo();
        virtual ~ScaleClassInfo();
};

class Scale
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
        
        Scale();
		Scale(const Ionflux::GeoUtils::TransformNodes::Scale& other);
        Scale(const Ionflux::GeoUtils::Vector3& initScale, 
        Ionflux::GeoUtils::Mapping::Vector3Mapping* initIndexFunc = 0, 
        Ionflux::GeoUtils::Mapping::Vector3Mapping* initDistanceFunc = 0, 
        Ionflux::GeoUtils::CenteringMethod initCenteringMethod = 
        CENTER_ORIGIN, Ionflux::Mapping::MappingValue initScaleFactor = 1.,
        Ionflux::Mapping::MappingValue initDeltaScaleFactor = 0., const 
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Scale();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::Scale* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Scale* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Scale* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		virtual void setParam(Ionflux::ObjectBase::IFParamID paramID, 
		Ionflux::Mapping::MappingValue paramValue);
		virtual Ionflux::Mapping::MappingValue 
		getParam(Ionflux::ObjectBase::IFParamID paramID);
        virtual void setScale(const Ionflux::GeoUtils::Vector3& newScale);
        virtual Ionflux::GeoUtils::Vector3 getScale() const;
        virtual void 
        setIndexFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        newIndexFunc);
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* getIndexFunc() 
        const;
        virtual void 
        setDistanceFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        newDistanceFunc);
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        getDistanceFunc() const;
        virtual void setCenteringMethod(Ionflux::GeoUtils::CenteringMethod 
        newCenteringMethod);
        virtual Ionflux::GeoUtils::CenteringMethod getCenteringMethod() 
        const;
        virtual void setScaleFactor(Ionflux::Mapping::MappingValue 
        newScaleFactor);
        virtual Ionflux::Mapping::MappingValue getScaleFactor() const;
        virtual void setDeltaScaleFactor(Ionflux::Mapping::MappingValue 
        newDeltaScaleFactor);
        virtual Ionflux::Mapping::MappingValue getDeltaScaleFactor() const;
};

}

}

}
