/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Scatter.i                       Transform node: Scatter (interface).
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
#include "geoutils/Scatter.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class ScatterClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ScatterClassInfo();
        virtual ~ScatterClassInfo();
};

class Scatter
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
		static const unsigned int DEFAULT_NUM_LUT_ENTRIES;
		static const Ionflux::Mapping::Range OFFSET_INDEX_RANGE;
        
        Scatter();
		Scatter(const Ionflux::GeoUtils::TransformNodes::Scatter& other);
        Scatter(const Ionflux::GeoUtils::Vector3& initOffset, 
        Ionflux::GeoUtils::Mapping::Vector3Mapping* initOffsetFunc = 0, 
        Ionflux::Mapping::Mapping* initOffsetIndexFunc = 0, const 
        Ionflux::GeoUtils::Vector3& initOffsetScale = 
        GeoUtils::Vector3::E_SUM, Ionflux::Mapping::MappingValue 
        initOffsetScaleFactor = 1., Ionflux::Mapping::MappingValue 
        initOffsetDeltaScaleFactor = 0., Ionflux::Mapping::MappingValue 
        initOffsetIndexOffset = 0., Ionflux::Mapping::MappingValue 
        initOffsetIndexScale = 1., const Ionflux::GeoUtils::Vector3& 
        initElementScale = GeoUtils::Vector3::E_SUM, 
        Ionflux::Mapping::MappingValue initElementScaleFactor = 1., 
        Ionflux::Mapping::MappingValue initElementDeltaScaleFactor = 0., 
        Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        initElementScaleIndexFunc = 0, 
        Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        initElementScaleDistanceFunc = 0, 
        Ionflux::GeoUtils::CenteringMethod initCenteringMethod = 
        CENTER_BARYCENTER, const Ionflux::ObjectBase::IFObjectID& nodeID = 
        "");
        virtual ~Scatter();
        virtual std::string getString() const;
        static Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        createLUT(unsigned int numEntries = DEFAULT_NUM_LUT_ENTRIES, const 
        Ionflux::GeoUtils::Vector3& stdDev = 
        Ionflux::GeoUtils::Vector3::E_SUM, const 
        Ionflux::GeoUtils::Vector3& mean = 
        Ionflux::GeoUtils::Vector3::ZERO, Ionflux::GeoUtils::Shape3* 
        refObject = 0, Ionflux::Mapping::Mapping* sourceFuncX = 0, 
        Ionflux::Mapping::Mapping* sourceFuncY = 0, 
        Ionflux::Mapping::Mapping* sourceFuncZ = 0);
		virtual Ionflux::GeoUtils::TransformNodes::Scatter* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Scatter* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Scatter* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		virtual void setParam(Ionflux::ObjectBase::IFParamID paramID, 
		Ionflux::Mapping::MappingValue paramValue);
		virtual Ionflux::Mapping::MappingValue 
		getParam(Ionflux::ObjectBase::IFParamID paramID);
        virtual void setOffset(const Ionflux::GeoUtils::Vector3& 
        newOffset);
        virtual Ionflux::GeoUtils::Vector3 getOffset() const;
        virtual void 
        setOffsetFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        newOffsetFunc);
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* getOffsetFunc()
        const;
        virtual void setOffsetIndexFunc(Ionflux::Mapping::Mapping* 
        newOffsetIndexFunc);
        virtual Ionflux::Mapping::Mapping* getOffsetIndexFunc() const;
        virtual void setOffsetScale(const Ionflux::GeoUtils::Vector3& 
        newOffsetScale);
        virtual Ionflux::GeoUtils::Vector3 getOffsetScale() const;
        virtual void setOffsetScaleFactor(Ionflux::Mapping::MappingValue 
        newOffsetScaleFactor);
        virtual Ionflux::Mapping::MappingValue getOffsetScaleFactor() 
        const;
        virtual void 
        setOffsetDeltaScaleFactor(Ionflux::Mapping::MappingValue 
        newOffsetDeltaScaleFactor);
        virtual Ionflux::Mapping::MappingValue getOffsetDeltaScaleFactor() 
        const;
        virtual void setOffsetIndexOffset(Ionflux::Mapping::MappingValue 
        newOffsetIndexOffset);
        virtual Ionflux::Mapping::MappingValue getOffsetIndexOffset() 
        const;
        virtual void setOffsetIndexScale(Ionflux::Mapping::MappingValue 
        newOffsetIndexScale);
        virtual Ionflux::Mapping::MappingValue getOffsetIndexScale() const;
        virtual void setElementScale(const Ionflux::GeoUtils::Vector3& 
        newElementScale);
        virtual Ionflux::GeoUtils::Vector3 getElementScale() const;
        virtual void setElementScaleFactor(Ionflux::Mapping::MappingValue 
        newElementScaleFactor);
        virtual Ionflux::Mapping::MappingValue getElementScaleFactor() 
        const;
        virtual void 
        setElementDeltaScaleFactor(Ionflux::Mapping::MappingValue 
        newElementDeltaScaleFactor);
        virtual Ionflux::Mapping::MappingValue getElementDeltaScaleFactor()
        const;
        virtual void 
        setElementScaleIndexFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping*
        newElementScaleIndexFunc);
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        getElementScaleIndexFunc() const;
        virtual void 
        setElementScaleDistanceFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping*
        newElementScaleDistanceFunc);
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        getElementScaleDistanceFunc() const;
        virtual void setCenteringMethod(Ionflux::GeoUtils::CenteringMethod 
        newCenteringMethod);
        virtual Ionflux::GeoUtils::CenteringMethod getCenteringMethod() 
        const;
};

}

}

}
