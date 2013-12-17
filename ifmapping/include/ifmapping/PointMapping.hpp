#ifndef IONFLUX_MAPPING_POINTMAPPING
#define IONFLUX_MAPPING_POINTMAPPING
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PointMapping.hpp                Point mapping (header).
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
#include "ifmapping/constants.hpp"
#include "ifmapping/Point.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class PointMapping.
class PointMappingClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		PointMappingClassInfo();
		/// Destructor.
		virtual ~PointMappingClassInfo();
};

/** Point mapping.
 * \ingroup ifmapping
 *
 * A mapping that maps a parameter value to a point in two-dimensional 
 * space.
 */
class PointMapping
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		
	public:
		/// Default precision.
		static const Ionflux::Mapping::MappingValue DEFAULT_PRECISION;
		/// Default relative error.
		static const Ionflux::Mapping::MappingValue DEFAULT_RELATIVE_ERROR;
		/// Maximum number of iterations.
		static const unsigned int DEFAULT_MAX_NUM_ITERATIONS;
		/// Class information instance.
		static const PointMappingClassInfo pointMappingClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new PointMapping object.
		 */
		PointMapping();
		
		/** Destructor.
		 *
		 * Destruct PointMapping object.
		 */
		virtual ~PointMapping();
		
		/** Get parameter for coordinate value.
		 *
		 * Get the parameter value corresponding to the specified  coordinate 
		 * value.
		 *
		 * \param value Coordinate value.
		 * \param coord Coordinate.
		 * \param precision Precision.
		 *
		 * \return Parameter value for the specified coordinate value.
		 */
		virtual Ionflux::Mapping::MappingValue 
		getParamCoord(Ionflux::Mapping::MappingValue value, 
		Ionflux::Mapping::CoordinateID coord = Ionflux::Mapping::C_X, 
		Ionflux::Mapping::MappingValue precision = 
		Ionflux::Mapping::PointMapping::DEFAULT_PRECISION);
		
		/** Evaluate the mapping.
		 *
		 * Evaluate the mapping at the specified coordinate value.
		 *
		 * \param value Coordinate value.
		 * \param coord Coordinate.
		 * \param precision Precision.
		 *
		 * \return Mapping point for the specified coordinate value.
		 */
		virtual Ionflux::Mapping::Point evalCoord(Ionflux::Mapping::MappingValue 
		value, Ionflux::Mapping::CoordinateID coord = Ionflux::Mapping::C_X, 
		Ionflux::Mapping::MappingValue precision = 
		Ionflux::Mapping::PointMapping::DEFAULT_PRECISION);
		
		/** Get parameter for arc length.
		 *
		 * Get the parameter value corresponding to the specified arc length.
		 *
		 * \param value Arc length value.
		 * \param relativeError Relative error.
		 * \param maxNumIterations Maximum number of iterations.
		 * \param precision Precision.
		 *
		 * \return Parameter value for the specified arc length.
		 */
		virtual Ionflux::Mapping::MappingValue 
		getParamArcLength(Ionflux::Mapping::MappingValue value, 
		Ionflux::Mapping::MappingValue relativeError = 
		Ionflux::Mapping::PointMapping::DEFAULT_RELATIVE_ERROR, 
		Ionflux::Mapping::MappingValue maxNumIterations = 
		Ionflux::Mapping::PointMapping::DEFAULT_MAX_NUM_ITERATIONS, 
		Ionflux::Mapping::MappingValue precision = 
		Ionflux::Mapping::PointMapping::DEFAULT_PRECISION);
		
		/** Evaluate the mapping.
		 *
		 * Evaluate the mapping at the specified arc length.
		 *
		 * \param value Arc length value.
		 * \param relativeError Relative error.
		 * \param maxNumIterations Maximum number of iterations.
		 * \param precision Precision.
		 *
		 * \return Mapping point for the specified arc length.
		 */
		virtual Ionflux::Mapping::Point 
		evalArcLength(Ionflux::Mapping::MappingValue value, 
		Ionflux::Mapping::MappingValue relativeError = 
		Ionflux::Mapping::PointMapping::DEFAULT_RELATIVE_ERROR, 
		Ionflux::Mapping::MappingValue maxNumIterations = 
		Ionflux::Mapping::PointMapping::DEFAULT_MAX_NUM_ITERATIONS, 
		Ionflux::Mapping::MappingValue precision = 
		Ionflux::Mapping::PointMapping::DEFAULT_PRECISION);
		
		/** Evaluate the mapping.
		 *
		 * Evaluate the mapping with the specified parameter.
		 *
		 * \param value Value.
		 *
		 * \return Mapped value.
		 */
		virtual Ionflux::Mapping::Point operator()(Ionflux::Mapping::MappingValue
		value);
		
		/** Evaluate the mapping.
		 *
		 * Evaluate the mapping with the specified parameter.
		 *
		 * \param value Value.
		 */
		virtual Ionflux::Mapping::Point call(Ionflux::Mapping::MappingValue 
		value) = 0;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::PointMapping* 
		upcast(Ionflux::ObjectBase::IFObject* other);
};

}

}

/** \file PointMapping.hpp
 * \brief Point mapping (header).
 */
#endif
