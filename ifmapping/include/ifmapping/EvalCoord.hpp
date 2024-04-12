#ifndef IONFLUX_MAPPING_EVALCOORD
#define IONFLUX_MAPPING_EVALCOORD
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * EvalCoord.hpp                   Evaluate coordinate point mapping 
 * (header).
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

#include "ifmapping/types.hpp"
#include "ifmapping/constants.hpp"
#include "ifmapping/PointMapping.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class EvalCoord.
class EvalCoordClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		EvalCoordClassInfo();
		/// Destructor.
		virtual ~EvalCoordClassInfo();
};

/** Evaluate coordinate point mapping.
 * \ingroup ifmapping
 *
 * Evaluate a point mapping at a specified coordinate. This can be used to 
 * convert parametric point mappings (like \c BezierCurve or \c 
 * BezierSpline) into function mappings.
 */
class EvalCoord
: public Ionflux::Mapping::PointMapping
{
	private:
		
	protected:
		/// Mapping.
		Ionflux::Mapping::PointMapping* func;
		/// Coordinate.
		Ionflux::Mapping::CoordinateID coord;
		/// Offset.
		Ionflux::Mapping::Point offset;
		/// Scale.
		Ionflux::Mapping::Point scale;
		/// Parameter offset.
		Ionflux::Mapping::MappingValue paramOffset;
		/// Parameter scale.
		Ionflux::Mapping::MappingValue paramScale;
		/// Precision.
		Ionflux::Mapping::MappingValue precision;
		
	public:
		/// Class information instance.
		static const EvalCoordClassInfo evalCoordClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new EvalCoord object.
		 */
		EvalCoord();
		
		/** Constructor.
		 *
		 * Construct new EvalCoord object.
		 *
		 * \param other Other object.
		 */
		EvalCoord(const Ionflux::Mapping::EvalCoord& other);
		
		/** Constructor.
		 *
		 * Construct new EvalCoord object.
		 *
		 * \param initFunc Mapping.
		 * \param initCoord Coordinate.
		 * \param initOffset Offset.
		 * \param initScale Scale.
		 * \param initParamOffset Parameter offset.
		 * \param initParamScale Parameter scale.
		 * \param initPrecision Precision.
		 */
		EvalCoord(Ionflux::Mapping::PointMapping* initFunc, 
		Ionflux::Mapping::CoordinateID initCoord = Ionflux::Mapping::C_X, 
		Ionflux::Mapping::Point initOffset = Ionflux::Mapping::Point::ORIGIN, 
		Ionflux::Mapping::Point initScale = Ionflux::Mapping::Point::ONES, 
		Ionflux::Mapping::MappingValue initParamOffset = 0., 
		Ionflux::Mapping::MappingValue initParamScale = 1., 
		Ionflux::Mapping::MappingValue initPrecision = 
		Ionflux::Mapping::PointMapping::DEFAULT_PRECISION);
		
		/** Destructor.
		 *
		 * Destruct EvalCoord object.
		 */
		virtual ~EvalCoord();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Call the mapping.
		 *
		 * Calls the mapping with the specified parameter.
		 *
		 * \param value Value.
		 *
		 * \return Mapped value.
		 */
		virtual Ionflux::Mapping::Point call(Ionflux::Mapping::MappingValue 
		value);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Mapping::EvalCoord& operator=(const 
		Ionflux::Mapping::EvalCoord& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::EvalCoord* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::EvalCoord* upcast(Ionflux::ObjectBase::IFObject*
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
		static Ionflux::Mapping::EvalCoord* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get mapping.
		 *
		 * \return Current value of mapping.
		 */
		virtual Ionflux::Mapping::PointMapping* getFunc() const;
		
		/** Set mapping.
		 *
		 * Set new value of mapping.
		 *
		 * \param newFunc New value of mapping.
		 */
		virtual void setFunc(Ionflux::Mapping::PointMapping* newFunc);
		
		/** Get coordinate.
		 *
		 * \return Current value of coordinate.
		 */
		virtual Ionflux::Mapping::CoordinateID getCoord() const;
		
		/** Set coordinate.
		 *
		 * Set new value of coordinate.
		 *
		 * \param newCoord New value of coordinate.
		 */
		virtual void setCoord(Ionflux::Mapping::CoordinateID newCoord);
		
		/** Get offset.
		 *
		 * \return Current value of offset.
		 */
		virtual Ionflux::Mapping::Point getOffset() const;
		
		/** Set offset.
		 *
		 * Set new value of offset.
		 *
		 * \param newOffset New value of offset.
		 */
		virtual void setOffset(Ionflux::Mapping::Point newOffset);
		
		/** Get scale.
		 *
		 * \return Current value of scale.
		 */
		virtual Ionflux::Mapping::Point getScale() const;
		
		/** Set scale.
		 *
		 * Set new value of scale.
		 *
		 * \param newScale New value of scale.
		 */
		virtual void setScale(Ionflux::Mapping::Point newScale);
		
		/** Get parameter offset.
		 *
		 * \return Current value of parameter offset.
		 */
		virtual Ionflux::Mapping::MappingValue getParamOffset() const;
		
		/** Set parameter offset.
		 *
		 * Set new value of parameter offset.
		 *
		 * \param newParamOffset New value of parameter offset.
		 */
		virtual void setParamOffset(Ionflux::Mapping::MappingValue 
		newParamOffset);
		
		/** Get parameter scale.
		 *
		 * \return Current value of parameter scale.
		 */
		virtual Ionflux::Mapping::MappingValue getParamScale() const;
		
		/** Set parameter scale.
		 *
		 * Set new value of parameter scale.
		 *
		 * \param newParamScale New value of parameter scale.
		 */
		virtual void setParamScale(Ionflux::Mapping::MappingValue newParamScale);
		
		/** Get precision.
		 *
		 * \return Current value of precision.
		 */
		virtual Ionflux::Mapping::MappingValue getPrecision() const;
		
		/** Set precision.
		 *
		 * Set new value of precision.
		 *
		 * \param newPrecision New value of precision.
		 */
		virtual void setPrecision(Ionflux::Mapping::MappingValue newPrecision);
};

}

}

/** \file EvalCoord.hpp
 * \brief Evaluate coordinate point mapping (header).
 */
#endif
