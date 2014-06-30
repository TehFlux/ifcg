/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BezierSplineKey.i               Bezier spline key (interface).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFMapping - Ionflux Mapping Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFMapping - Ionflux Mapping Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */
%{
#include "ifmapping/BezierSplineKey.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class BezierSplineKeyClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BezierSplineKeyClassInfo();
        virtual ~BezierSplineKeyClassInfo();
};

class BezierSplineKey
: public Ionflux::Mapping::BezierSpline
{
    public:
        
        BezierSplineKey();
		BezierSplineKey(const Ionflux::Mapping::BezierSplineKey& other);
        BezierSplineKey(Ionflux::Mapping::MappingValue initT);
        BezierSplineKey(const Ionflux::Mapping::BezierSpline& initSpline, 
        Ionflux::Mapping::MappingValue initT);
        virtual ~BezierSplineKey();
        virtual std::string getString() const;
		virtual Ionflux::Mapping::BezierSplineKey* copy() const;
		static Ionflux::Mapping::BezierSplineKey* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::BezierSplineKey* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setT(Ionflux::Mapping::MappingValue newT);
        virtual Ionflux::Mapping::MappingValue getT() const;
};

}

}
