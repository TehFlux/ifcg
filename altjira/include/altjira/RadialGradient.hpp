#ifndef IONFLUX_ALTJIRA_RADIALGRADIENT
#define IONFLUX_ALTJIRA_RADIALGRADIENT
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * RadialGradient.hpp              Radial gradient (header).
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

/// Class information for class RadialGradient.
class RadialGradientClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		RadialGradientClassInfo();
		/// Destructor.
		virtual ~RadialGradientClassInfo();
};

/** Radial gradient.
 * \ingroup geoutils
 *
 * A radial gradient pattern to be used in drawing operations.
 */
class RadialGradient
: public Ionflux::Altjira::Gradient
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const RadialGradientClassInfo radialGradientClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new RadialGradient object.
		 */
		RadialGradient();
		
		/** Constructor.
		 *
		 * Construct new RadialGradient object.
		 *
		 * \param other Other object.
		 */
		RadialGradient(const Ionflux::Altjira::RadialGradient& other);
		
		/** Constructor.
		 *
		 * Construct new RadialGradient object.
		 *
		 * \param cx0 Center of the start circle (X).
		 * \param cy0 Center of the start circle (Y).
		 * \param r0 Radius of the start circle.
		 * \param cx1 Center of the end circle (X).
		 * \param cy1 Center of the end circle (Y).
		 * \param r1 Radius of the start circle.
		 */
		RadialGradient(double cx0, double cy0, double r0, double cx1, double cy1,
		double r1);
		
		/** Destructor.
		 *
		 * Destruct RadialGradient object.
		 */
		virtual ~RadialGradient();
		
		/** Initialize radial gradient.
		 *
		 * Initialize the radial gradient with the specified parameters.
		 *
		 * \param cx0 Center of the start circle (X).
		 * \param cy0 Center of the start circle (Y).
		 * \param r0 Radius of the start circle.
		 * \param cx1 Center of the end circle (X).
		 * \param cy1 Center of the end circle (Y).
		 * \param r1 Radius of the start circle.
		 */
		virtual void init(double cx0, double cy0, double r0, double cx1, double 
		cy1, double r1);
		
		/** Create radial gradient.
		 *
		 * Create a new radial gradient with the specified parameters.
		 *
		 * \param cx0 Center of the start circle (X).
		 * \param cy0 Center of the start circle (Y).
		 * \param r0 Radius of the start circle.
		 * \param cx1 Center of the end circle (X).
		 * \param cy1 Center of the end circle (Y).
		 * \param r1 Radius of the start circle.
		 *
		 * \return Radial gradient.
		 */
		static Ionflux::Altjira::RadialGradient* create(double cx0, double cy0, 
		double r0, double cx1, double cy1, double r1);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::RadialGradient& operator=(const 
		Ionflux::Altjira::RadialGradient& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Altjira::RadialGradient* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Altjira::RadialGradient* 
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
		static Ionflux::Altjira::RadialGradient* 
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

/** \file RadialGradient.hpp
 * \brief Radial gradient (header).
 */
#endif
