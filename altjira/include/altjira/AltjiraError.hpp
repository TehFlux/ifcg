#ifndef IONFLUX_ALTJIRA_ALTJIRAERROR
#define IONFLUX_ALTJIRA_ALTJIRAERROR
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * AltjiraError.hpp                Altjira error (header).
 * =========================================================================
 *
 * This file is part of Altjira - Ionflux' Image Processing Library.
 * 
 * Altjira - Ionflux' Image Processing Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * Altjira - Ionflux' Image Processing Library is distributed in the hope 
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Altjira - Ionflux' Image Processing Library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include <string>
#include <exception>

namespace Ionflux
{

namespace Altjira
{

/** Altjira error.
 * \ingroup altjira
 *
 * Exception to be used for errors if no more specific exception class 
 * exists.
 */
class AltjiraError
: public std::exception
{
	private:
		
	protected:
		/// Reason.
		std::string reason;
		
	public:
		
		/** Constructor.
		 *
		 * Construct new AltjiraError object.
		 */
		AltjiraError();
		
		/** Constructor.
		 *
		 * Construct new AltjiraError object.
		 *
		 * \param other Other object.
		 */
		AltjiraError(const Ionflux::Altjira::AltjiraError& other);
		
		/** Constructor.
		 *
		 * Construct new AltjiraError object.
		 *
		 * \param initReason Initial reason.
		 */
		AltjiraError(const std::string& initReason);
		
		/** Destructor.
		 *
		 * Destruct AltjiraError object.
		 */
		virtual ~AltjiraError() throw();
		
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
		virtual Ionflux::Altjira::AltjiraError& operator=(const 
		Ionflux::Altjira::AltjiraError& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Altjira::AltjiraError* copy() const;
		
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

/** \file AltjiraError.hpp
 * \brief Altjira error (header).
 */
#endif
