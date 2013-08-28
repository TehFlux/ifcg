/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * LinearInterpolator.i            Linear interpolator (interface).
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
#include "geoutils/LinearInterpolator.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class LinearInterpolatorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        LinearInterpolatorClassInfo();
        virtual ~LinearInterpolatorClassInfo();
};

class LinearInterpolator
: public Ionflux::GeoUtils::Interpolator
{
    public:
        
        LinearInterpolator();
		LinearInterpolator(const Ionflux::GeoUtils::LinearInterpolator& other);
        LinearInterpolator(double initV0, double initV1);
        LinearInterpolator(const Ionflux::ObjectBase::DoubleVector& 
        initValues);
        virtual ~LinearInterpolator();
        virtual double interpolate(double t = 0.5) const;
		virtual Ionflux::GeoUtils::LinearInterpolator* copy() const;
};

}

}
