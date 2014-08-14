/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FaceCompare.i                   Face comparison function object 
 * (interface).
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
#include "geoutils/FaceCompare.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class FaceCompareClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FaceCompareClassInfo();
        virtual ~FaceCompareClassInfo();
};

class FaceCompare
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        FaceCompare();
		FaceCompare(const Ionflux::GeoUtils::FaceCompare& other);
        FaceCompare(bool initInvert, Ionflux::GeoUtils::FaceCompare* 
        initTarget = 0);
        virtual ~FaceCompare();
        virtual std::string getString() const;
        virtual bool operator()(Ionflux::GeoUtils::Face* f0, 
        Ionflux::GeoUtils::Face* f1);
        virtual bool compare(Ionflux::GeoUtils::Face& f0, 
        Ionflux::GeoUtils::Face& f1);
		virtual Ionflux::GeoUtils::FaceCompare* copy() const;
		static Ionflux::GeoUtils::FaceCompare* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::FaceCompare* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setInvert(bool newInvert);
        virtual bool getInvert() const;
        virtual void setTarget(Ionflux::GeoUtils::FaceCompare* newTarget);
        virtual Ionflux::GeoUtils::FaceCompare* getTarget() const;
};

}

}
