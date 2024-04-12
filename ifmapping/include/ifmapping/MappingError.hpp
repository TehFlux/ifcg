#ifndef IONFLUX_MAPPING_MAPPINGERROR
#define IONFLUX_MAPPING_MAPPINGERROR
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * MappingError.hpp                Mapping error (header).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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

#include <string>
#include <exception>

namespace Ionflux
{

namespace Mapping
{

/** Mapping error.
 * \ingroup ifmapping
 *
 * Exception to be used for errors if no more specific exception class 
 * exists.
 */
class MappingError
: public std::exception
{
	private:
		
	protected:
		/// Reason.
		std::string reason;
		
	public:
		
		/** Constructor.
		 *
		 * Construct new MappingError object.
		 */
		MappingError();
		
		/** Constructor.
		 *
		 * Construct new MappingError object.
		 *
		 * \param other Other object.
		 */
		MappingError(const Ionflux::Mapping::MappingError& other);
		
		/** Constructor.
		 *
		 * Construct new MappingError object.
		 *
		 * \param initReason Initial reason.
		 */
		MappingError(const std::string& initReason);
		
		/** Destructor.
		 *
		 * Destruct MappingError object.
		 */
		virtual ~MappingError() throw();
		
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
		virtual Ionflux::Mapping::MappingError& operator=(const 
		Ionflux::Mapping::MappingError& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::MappingError* copy() const;
		
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

/** \file MappingError.hpp
 * \brief Mapping error (header).
 */
#endif
