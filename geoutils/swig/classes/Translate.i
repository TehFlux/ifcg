/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Translate.i                     Transform node: Translate (interface).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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
#include "geoutils/Translate.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class TranslateClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TranslateClassInfo();
        virtual ~TranslateClassInfo();
};

class Translate
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
        
        Translate();
		Translate(const Ionflux::GeoUtils::TransformNodes::Translate& other);
        Translate(const Ionflux::GeoUtils::Vector3& initOffset, 
        Ionflux::GeoUtils::Mapping::Vector3Mapping* initIndexFunc = 0, 
        Ionflux::GeoUtils::Mapping::Vector3Mapping* initDistanceFunc = 0, 
        const Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Translate();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::Translate* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Translate* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Translate* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setOffset(const Ionflux::GeoUtils::Vector3& 
        newOffset);
        virtual Ionflux::GeoUtils::Vector3 getOffset() const;
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
};

}

}

}
