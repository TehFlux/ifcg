#ifndef IONFLUX_VOLGFX_IFVGERROR
#define IONFLUX_VOLGFX_IFVGERROR
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFVGError.hpp                   IFVG error (header).
 * ========================================================================== */

#include <string>
#include <exception>

namespace Ionflux
{

namespace VolGfx
{

/** IFVG error.
 * \ingroup IFVG
 *
 * Exception to be used for errors if no more specific exception class 
 * exists.
 */
class IFVGError
: public std::exception
{
	private:
		
	protected:
		/// Reason.
		std::string reason;
		
	public:
		
		/** Constructor.
		 *
		 * Construct new IFVGError object.
		 */
		IFVGError();
		
		/** Constructor.
		 *
		 * Construct new IFVGError object.
		 *
		 * \param other Other object.
		 */
		IFVGError(const Ionflux::VolGfx::IFVGError& other);
		
		/** Constructor.
		 *
		 * Construct new IFVGError object.
		 *
		 * \param initReason Initial reason.
		 */
		IFVGError(const std::string& initReason);
		
		/** Destructor.
		 *
		 * Destruct IFVGError object.
		 */
		virtual ~IFVGError() throw();
		
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
		virtual Ionflux::VolGfx::IFVGError& operator=(const 
		Ionflux::VolGfx::IFVGError& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::VolGfx::IFVGError* copy() const;
		
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

/** \file IFVGError.hpp
 * \brief IFVG error (header).
 */
#endif
