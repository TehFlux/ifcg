#ifndef IONFLUX_MAPPING_BEZIERSPLINEKEY
#define IONFLUX_MAPPING_BEZIERSPLINEKEY
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BezierSplineKey.hpp             Bezier spline key (header).
 * =========================================================================
 *
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
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

#include "ifmapping/types.hpp"
#include "ifmapping/BezierSpline.hpp"
#include "ifmapping/BezierSpline.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class BezierSplineKey.
class BezierSplineKeyClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		BezierSplineKeyClassInfo();
		/// Destructor.
		virtual ~BezierSplineKeyClassInfo();
};

/** Bezier spline key.
 * \ingroup altjira
 *
 * A cubic bezier spline that can be used as a key in an animated spline. 
 * The key consists of a spline and a parameter value for the key frame.
 */
class BezierSplineKey
: public Ionflux::Mapping::BezierSpline
{
	private:
		
	protected:
		/// Parameter.
		Ionflux::Mapping::MappingValue t;
		
	public:
		/// Class information instance.
		static const BezierSplineKeyClassInfo bezierSplineKeyClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new BezierSplineKey object.
		 */
		BezierSplineKey();
		
		/** Constructor.
		 *
		 * Construct new BezierSplineKey object.
		 *
		 * \param other Other object.
		 */
		BezierSplineKey(const Ionflux::Mapping::BezierSplineKey& other);
		
		/** Constructor.
		 *
		 * Construct new BezierSplineKey object.
		 *
		 * \param initT Parameter.
		 */
		BezierSplineKey(Ionflux::Mapping::MappingValue initT);
		
		/** Constructor.
		 *
		 * Construct new BezierSplineKey object.
		 *
		 * \param initSpline Bezier spline.
		 * \param initT Parameter.
		 */
		BezierSplineKey(const Ionflux::Mapping::BezierSpline& initSpline, 
		Ionflux::Mapping::MappingValue initT);
		
		/** Destructor.
		 *
		 * Destruct BezierSplineKey object.
		 */
		virtual ~BezierSplineKey();
		
		/** Assignment operator.
		 *
		 * Assign a Bezier spline.
		 *
		 * \param other Bezier spline.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Mapping::BezierSplineKey& operator=(const 
		Ionflux::Mapping::BezierSpline& other);
		
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
		virtual Ionflux::Mapping::BezierSplineKey& operator=(const 
		Ionflux::Mapping::BezierSplineKey& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::BezierSplineKey* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::BezierSplineKey* 
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
		static Ionflux::Mapping::BezierSplineKey* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get parameter.
		 *
		 * \return Current value of parameter.
		 */
		virtual Ionflux::Mapping::MappingValue getT() const;
		
		/** Set parameter.
		 *
		 * Set new value of parameter.
		 *
		 * \param newT New value of parameter.
		 */
		virtual void setT(Ionflux::Mapping::MappingValue newT);
};

}

}

/** \file BezierSplineKey.hpp
 * \brief Bezier spline key (header).
 */
#endif
