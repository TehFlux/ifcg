/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Wrap.i                          Transform node: Wrap (interface).
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
#include "geoutils/Wrap.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class WrapClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        WrapClassInfo();
        virtual ~WrapClassInfo();
};

class Wrap
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int INPUT_FIRST;
		static const unsigned int OUTPUT_TARGET;
        
        Wrap();
		Wrap(const Ionflux::GeoUtils::TransformNodes::Wrap& other);
        Wrap(const Ionflux::ObjectBase::IFObjectID& nodeID);
        virtual ~Wrap();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::Wrap* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Wrap* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Wrap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}
