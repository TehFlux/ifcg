/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Normalize.i                     Transform node: Normalize (interface).
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
#include "geoutils/Normalize.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class NormalizeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NormalizeClassInfo();
        virtual ~NormalizeClassInfo();
};

class Normalize
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
        
        Normalize();
		Normalize(const Ionflux::GeoUtils::TransformNodes::Normalize& other);
        Normalize(const Ionflux::ObjectBase::IFObjectID& nodeID);
        virtual ~Normalize();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::Normalize* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Normalize* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Normalize* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}
