/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * GeoUtilsError.i                 GeoUtils error (interface).
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
#include "geoutils/GeoUtilsError.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class GeoUtilsError
: public std::exception
{
    public:
        
        GeoUtilsError();
		GeoUtilsError(const Ionflux::GeoUtils::GeoUtilsError& other);
        GeoUtilsError(const std::string& initReason);
        virtual ~GeoUtilsError() throw();
        virtual std::string getString() const;
        virtual const char* what() const throw();
		virtual Ionflux::GeoUtils::GeoUtilsError* copy() const;
        virtual void setReason(const std::string& newReason);
        virtual std::string getReason() const;
};

}

}
