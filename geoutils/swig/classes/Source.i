/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Source.i                        Transform node: Source (interface).
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
#include "geoutils/Source.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class SourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SourceClassInfo();
        virtual ~SourceClassInfo();
};

class Source
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int OUTPUT_TARGET;
        
        Source();
		Source(const Ionflux::GeoUtils::TransformNodes::Source& other);
        Source(Ionflux::GeoUtils::TransformableGroup* initSource, const 
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Source();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::Source* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Source* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Source* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setSource(Ionflux::GeoUtils::TransformableGroup* 
        newSource);
        virtual Ionflux::GeoUtils::TransformableGroup* getSource() const;
};

}

}

}
