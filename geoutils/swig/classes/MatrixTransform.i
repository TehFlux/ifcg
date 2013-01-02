/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * MatrixTransform.i               Transform node: Matrix transform 
 * (interface).
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
#include "geoutils/MatrixTransform.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class MatrixTransformClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MatrixTransformClassInfo();
        virtual ~MatrixTransformClassInfo();
};

class MatrixTransform
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
        
        MatrixTransform();
		MatrixTransform(const Ionflux::GeoUtils::TransformNodes::MatrixTransform& other);
        MatrixTransform(const Ionflux::GeoUtils::Matrix4& initMatrix, const
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~MatrixTransform();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::MatrixTransform* copy() const;
		static Ionflux::GeoUtils::TransformNodes::MatrixTransform* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::MatrixTransform* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setMatrix(const Ionflux::GeoUtils::Matrix4& 
        newMatrix);
        virtual Ionflux::GeoUtils::Matrix4 getMatrix() const;
};

}

}

}
