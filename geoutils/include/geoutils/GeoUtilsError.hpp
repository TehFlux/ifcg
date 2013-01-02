#ifndef IONFLUX_GEOUTILS_GEOUTILSERROR
#define IONFLUX_GEOUTILS_GEOUTILSERROR
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * GeoUtilsError.hpp               GeoUtils error (header).
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

#include <string>
#include <exception>

namespace Ionflux
{

namespace GeoUtils
{

/** GeoUtils error.
 * \ingroup geoutils
 *
 * Exception to be used for errors if no more specific exception class 
 * exists.
 */
class GeoUtilsError
: public std::exception
{
	private:
		
	protected:
		/// Reason.
		std::string reason;
		
	public:
		
		/** Constructor.
		 *
		 * Construct new GeoUtilsError object.
		 */
		GeoUtilsError();
		
		/** Constructor.
		 *
		 * Construct new GeoUtilsError object.
		 *
		 * \param other Other object.
		 */
		GeoUtilsError(const Ionflux::GeoUtils::GeoUtilsError& other);
		
		/** Constructor.
		 *
		 * Construct new GeoUtilsError object.
		 *
		 * \param initReason Initial reason.
		 */
		GeoUtilsError(const std::string& initReason);
		
		/** Destructor.
		 *
		 * Destruct GeoUtilsError object.
		 */
		virtual ~GeoUtilsError() throw();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Get exception information.
		 *
		 * Get information on what happened.
		 *
		 * \return Exception information.
		 */
		virtual const char* what() const throw();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::GeoUtilsError& operator=(const 
		Ionflux::GeoUtils::GeoUtilsError& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::GeoUtilsError* copy() const;
		
		/** Get reason.
		 *
		 * \return Current value of reason.
		 */
		virtual std::string getReason() const;
		
		/** Set reason.
		 *
		 * Set new value of reason.
		 *
		 * \param newReason New value of reason.
		 */
		virtual void setReason(const std::string& newReason);
};

}

}

/** \file GeoUtilsError.hpp
 * \brief GeoUtils error (header).
 */
#endif
