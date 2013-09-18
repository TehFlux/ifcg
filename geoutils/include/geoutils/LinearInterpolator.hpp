#ifndef IONFLUX_GEOUTILS_LINEARINTERPOLATOR
#define IONFLUX_GEOUTILS_LINEARINTERPOLATOR
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * LinearInterpolator.hpp          Linear interpolator (header).
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

#include "ifobject/types.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Interpolator.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class LinearInterpolator.
class LinearInterpolatorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		LinearInterpolatorClassInfo();
		/// Destructor.
		virtual ~LinearInterpolatorClassInfo();
};

/** Linear interpolator.
 * \ingroup geoutils
 *
 * An object that does linear interpolation between two scalar values.
 */
class LinearInterpolator
: public Ionflux::GeoUtils::Interpolator
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const LinearInterpolatorClassInfo linearInterpolatorClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new LinearInterpolator object.
		 */
		LinearInterpolator();
		
		/** Constructor.
		 *
		 * Construct new LinearInterpolator object.
		 *
		 * \param other Other object.
		 */
		LinearInterpolator(const Ionflux::GeoUtils::LinearInterpolator& other);
		
		/** Constructor.
		 *
		 * Construct new LinearInterpolator object.
		 *
		 * \param initV0 First value.
		 * \param initV1 Second value.
		 */
		LinearInterpolator(double initV0, double initV1);
		
		/** Constructor.
		 *
		 * Construct new LinearInterpolator object.
		 *
		 * \param initValues Value vector.
		 */
		LinearInterpolator(const Ionflux::ObjectBase::DoubleVector& initValues);
		
		/** Destructor.
		 *
		 * Destruct LinearInterpolator object.
		 */
		virtual ~LinearInterpolator();
		
		/** Interpolate.
		 *
		 * Interpolate the current values using the specified parameter.
		 *
		 * \param t Interpolation parameter.
		 *
		 * \return Interpolated value.
		 */
		virtual double interpolate(double t = 0.5) const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::LinearInterpolator& operator=(const 
		Ionflux::GeoUtils::LinearInterpolator& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::LinearInterpolator* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::LinearInterpolator* 
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
		static Ionflux::GeoUtils::LinearInterpolator* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new LinearInterpolator object.
		 *
		 * \param initV0 First value.
		 * \param initV1 Second value.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::LinearInterpolator* create(double initV0, 
		double initV1, Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new LinearInterpolator object.
		 *
		 * \param initValues Value vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::LinearInterpolator* create(const 
		Ionflux::ObjectBase::DoubleVector& initValues, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

/** \file LinearInterpolator.hpp
 * \brief Linear interpolator (header).
 */
#endif
