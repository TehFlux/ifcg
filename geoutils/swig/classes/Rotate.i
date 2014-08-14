/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Rotate.i                        Transform node: Rotate (interface).
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
#include "geoutils/Rotate.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class RotateClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        RotateClassInfo();
        virtual ~RotateClassInfo();
};

class Rotate
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
		static const Ionflux::GeoUtils::Range DEFAULT_ANGLE_RANGE;
        
        Rotate();
		Rotate(const Ionflux::GeoUtils::TransformNodes::Rotate& other);
        Rotate(Ionflux::GeoUtils::AxisID initAxis, double initAngle = 0., 
        double deltaAngle = 0., Ionflux::Mapping::Mapping* initIndexFunc = 
        0, Ionflux::Mapping::Mapping* initDistanceFunc = 0, 
        Ionflux::GeoUtils::Range initIndexRange = DEFAULT_ANGLE_RANGE, 
        Ionflux::GeoUtils::Range initDistanceRange = DEFAULT_ANGLE_RANGE, 
        Ionflux::GeoUtils::CenteringMethod initCenteringMethod = 
        CENTER_ORIGIN, const Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Rotate();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::Rotate* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Rotate* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Rotate* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		virtual void setParam(Ionflux::ObjectBase::IFParamID paramID, 
		Ionflux::Mapping::MappingValue paramValue);
		virtual Ionflux::Mapping::MappingValue 
		getParam(Ionflux::ObjectBase::IFParamID paramID);
        virtual void setAxis(Ionflux::GeoUtils::AxisID newAxis);
        virtual Ionflux::GeoUtils::AxisID getAxis() const;
        virtual void setAngle(Ionflux::Mapping::MappingValue newAngle);
        virtual Ionflux::Mapping::MappingValue getAngle() const;
        virtual void setDeltaAngle(Ionflux::Mapping::MappingValue 
        newDeltaAngle);
        virtual Ionflux::Mapping::MappingValue getDeltaAngle() const;
        virtual void setIndexFunc(Ionflux::Mapping::Mapping* newIndexFunc);
        virtual Ionflux::Mapping::Mapping* getIndexFunc() const;
        virtual void setDistanceFunc(Ionflux::Mapping::Mapping* 
        newDistanceFunc);
        virtual Ionflux::Mapping::Mapping* getDistanceFunc() const;
        virtual void setIndexRange(const Ionflux::GeoUtils::Range& 
        newIndexRange);
        virtual Ionflux::GeoUtils::Range getIndexRange() const;
        virtual void setDistanceRange(const Ionflux::GeoUtils::Range& 
        newDistanceRange);
        virtual Ionflux::GeoUtils::Range getDistanceRange() const;
        virtual void setCenteringMethod(Ionflux::GeoUtils::CenteringMethod 
        newCenteringMethod);
        virtual Ionflux::GeoUtils::CenteringMethod getCenteringMethod() 
        const;
};

}

}

}
