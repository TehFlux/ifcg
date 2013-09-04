/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FaceData.i                      Face data (interface).
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
#include "geoutils/FaceData.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class FaceDataClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FaceDataClassInfo();
        virtual ~FaceDataClassInfo();
};

class FaceData
: public Ionflux::GeoUtils::VectorSet
{
    public:
        
        FaceData();
		FaceData(const Ionflux::GeoUtils::FaceData& other);
        FaceData(Ionflux::GeoUtils::VectorVector& initVectors);
        virtual ~FaceData();
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::FaceData* copy() const;
		static Ionflux::GeoUtils::FaceData* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::GeoUtils::FaceData* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		static Ionflux::GeoUtils::FaceData* 
		create(Ionflux::GeoUtils::VectorVector& initVectors, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setDataType(Ionflux::GeoUtils::FaceDataTypeID 
        newDataType);
        virtual Ionflux::GeoUtils::FaceDataTypeID getDataType() const;
};

namespace XMLUtils
{

void getFaceData(const std::string& data, Ionflux::GeoUtils::FaceData& 
target);

}

}

}
