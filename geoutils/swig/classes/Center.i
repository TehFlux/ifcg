/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Center.i                        Transform node: Center (interface).
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
#include "geoutils/Center.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class CenterClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        CenterClassInfo();
        virtual ~CenterClassInfo();
};

class Center
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
        
        Center();
		Center(const Ionflux::GeoUtils::TransformNodes::Center& other);
        Center(Ionflux::GeoUtils::CenteringMethod initMethod, const 
        Ionflux::GeoUtils::Vector3& initOrigin = GeoUtils::Vector3::ZERO, 
        const Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Center();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::Center* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Center* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Center* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setOrigin(const Ionflux::GeoUtils::Vector3& 
        newOrigin);
        virtual Ionflux::GeoUtils::Vector3 getOrigin() const;
        virtual void setMethod(Ionflux::GeoUtils::CenteringMethod 
        newMethod);
        virtual Ionflux::GeoUtils::CenteringMethod getMethod() const;
};

}

}

}
