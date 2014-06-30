#ifndef IONFLUX_ALTJIRA_LINEARGRADIENT
#define IONFLUX_ALTJIRA_LINEARGRADIENT
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * LinearGradient.hpp              Linear gradient (header).
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

#include "altjira/Gradient.hpp"

namespace Ionflux
{

namespace Altjira
{

/// Class information for class LinearGradient.
class LinearGradientClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		LinearGradientClassInfo();
		/// Destructor.
		virtual ~LinearGradientClassInfo();
};

/** Linear gradient.
 * \ingroup geoutils
 *
 * A linear gradient pattern to be used in drawing operations.
 */
class LinearGradient
: public Ionflux::Altjira::Gradient
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const LinearGradientClassInfo linearGradientClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new LinearGradient object.
		 */
		LinearGradient();
		
		/** Constructor.
		 *
		 * Construct new LinearGradient object.
		 *
		 * \param other Other object.
		 */
		LinearGradient(const Ionflux::Altjira::LinearGradient& other);
		
		/** Constructor.
		 *
		 * Construct new LinearGradient object.
		 *
		 * \param x0 Start point (X).
		 * \param y0 Start point (Y).
		 * \param x1 End point (X).
		 * \param y1 End point (Y).
		 */
		LinearGradient(double x0, double y0, double x1, double y1);
		
		/** Destructor.
		 *
		 * Destruct LinearGradient object.
		 */
		virtual ~LinearGradient();
		
		/** Initialize radial gradient.
		 *
		 * Initialize the radial gradient with the specified parameters.
		 *
		 * \param x0 Start point (X).
		 * \param y0 Start point (Y).
		 * \param x1 End point (X).
		 * \param y1 End point (Y).
		 */
		virtual void init(double x0, double y0, double x1, double y1);
		
		/** Create linear gradient.
		 *
		 * Create a new linear gradient with the specified parameters.
		 *
		 * \param x0 Start point (X).
		 * \param y0 Start point (Y).
		 * \param x1 End point (X).
		 * \param y1 End point (Y).
		 *
		 * \return Linear gradient.
		 */
		static Ionflux::Altjira::LinearGradient* create(double x0, double y0, 
		double x1, double y1);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::LinearGradient& operator=(const 
		Ionflux::Altjira::LinearGradient& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Altjira::LinearGradient* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Altjira::LinearGradient* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::Altjira::LinearGradient* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
};

}

}

/** \file LinearGradient.hpp
 * \brief Linear gradient (header).
 */
#endif
