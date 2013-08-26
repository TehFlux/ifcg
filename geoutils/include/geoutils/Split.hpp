#ifndef IONFLUX_GEOUTILS_SPLIT
#define IONFLUX_GEOUTILS_SPLIT
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Split.hpp                       Axis split (header).
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

#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Split;

/// Class information for class Split.
class SplitClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		SplitClassInfo();
		/// Destructor.
		virtual ~SplitClassInfo();
};

/** Axis split.
 * \ingroup geoutils
 *
 * A split object specifies an axis and a parameter for determining a 
 * position on the axis where a split occurs.
 */
class Split
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Split axis.
		Ionflux::GeoUtils::AxisID axis;
		/// Split parameter.
		double s;
		
	public:
		/// Class information instance.
		static const SplitClassInfo splitClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Split object.
		 */
		Split();
		
		/** Constructor.
		 *
		 * Construct new Split object.
		 *
		 * \param other Other object.
		 */
		Split(const Ionflux::GeoUtils::Split& other);
		
		/** Constructor.
		 *
		 * Construct new Split object.
		 *
		 * \param initAxis Axis.
		 * \param initS Parameter.
		 */
		Split(Ionflux::GeoUtils::AxisID initAxis, double initS = .5);
		
		/** Destructor.
		 *
		 * Destruct Split object.
		 */
		virtual ~Split();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Split& operator=(const 
		Ionflux::GeoUtils::Split& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Split* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Split* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		
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
		static Ionflux::GeoUtils::Split* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get split axis.
		 *
		 * \return Current value of split axis.
		 */
		virtual Ionflux::GeoUtils::AxisID getAxis() const;
		
		/** Set split axis.
		 *
		 * Set new value of split axis.
		 *
		 * \param newAxis New value of split axis.
		 */
		virtual void setAxis(Ionflux::GeoUtils::AxisID newAxis);
		
		/** Get split parameter.
		 *
		 * \return Current value of split parameter.
		 */
		virtual double getS() const;
		
		/** Set split parameter.
		 *
		 * Set new value of split parameter.
		 *
		 * \param newS New value of split parameter.
		 */
		virtual void setS(double newS);
};

}

}

/** \file Split.hpp
 * \brief Axis split (header).
 */
#endif
