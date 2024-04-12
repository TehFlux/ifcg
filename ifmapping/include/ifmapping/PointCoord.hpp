#ifndef IONFLUX_MAPPING_POINTCOORD
#define IONFLUX_MAPPING_POINTCOORD
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PointCoord.hpp                  Point coordinate mapping (header).
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
#include "ifmapping/Mapping.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class PointCoord.
class PointCoordClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		PointCoordClassInfo();
		/// Destructor.
		virtual ~PointCoordClassInfo();
};

/** Point coordinate mapping.
 * \ingroup ifmapping
 *
 * Extracts one coordinate from the result of a point mapping and adds an 
 * optional offset.
 */
class PointCoord
: public Ionflux::Mapping::Mapping
{
	private:
		
	protected:
		/// Mapping.
		Ionflux::Mapping::PointMapping* func;
		/// Coordinate.
		Ionflux::Mapping::CoordinateID coord;
		/// Offset.
		Ionflux::Mapping::MappingValue offset;
		/// Scale.
		Ionflux::Mapping::MappingValue scale;
		
	public:
		/// Class information instance.
		static const PointCoordClassInfo pointCoordClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new PointCoord object.
		 */
		PointCoord();
		
		/** Constructor.
		 *
		 * Construct new PointCoord object.
		 *
		 * \param other Other object.
		 */
		PointCoord(const Ionflux::Mapping::PointCoord& other);
		
		/** Constructor.
		 *
		 * Construct new PointCoord object.
		 *
		 * \param initFunc Mapping.
		 * \param initCoord Coordinate.
		 * \param initOffset Offset.
		 * \param initScale Scale.
		 */
		PointCoord(Ionflux::Mapping::PointMapping* initFunc, 
		Ionflux::Mapping::CoordinateID initCoord = Ionflux::Mapping::C_X, 
		Ionflux::Mapping::MappingValue initOffset = 0., 
		Ionflux::Mapping::MappingValue initScale = 1.);
		
		/** Destructor.
		 *
		 * Destruct PointCoord object.
		 */
		virtual ~PointCoord();
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Call the mapping.
		 *
		 * Calls the mapping with the specified parameter.
		 *
		 * \param value Value.
		 *
		 * \return Mapped value.
		 */
		virtual Ionflux::Mapping::MappingValue 
		call(Ionflux::Mapping::MappingValue value) const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Mapping::PointCoord& operator=(const 
		Ionflux::Mapping::PointCoord& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::PointCoord* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::PointCoord* 
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
		static Ionflux::Mapping::PointCoord* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new PointCoord object.
		 *
		 * \param initFunc Mapping.
		 * \param initCoord Coordinate.
		 * \param initOffset Offset.
		 * \param initScale Scale.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Mapping::PointCoord* 
		create(Ionflux::Mapping::PointMapping* initFunc, 
		Ionflux::Mapping::CoordinateID initCoord = Ionflux::Mapping::C_X, 
		Ionflux::Mapping::MappingValue initOffset = 0., 
		Ionflux::Mapping::MappingValue initScale = 1., 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
		virtual Ionflux::Mapping::MappingValue getOffset() const;
		
		/** Set offset.
		 *
		 * Set new value of offset.
		 *
		 * \param newOffset New value of offset.
		 */
		virtual void setOffset(Ionflux::Mapping::MappingValue newOffset);
		
		/** Get scale.
		 *
		 * \return Current value of scale.
		 */
		virtual Ionflux::Mapping::MappingValue getScale() const;
		
		/** Set scale.
		 *
		 * Set new value of scale.
		 *
		 * \param newScale New value of scale.
		 */
		virtual void setScale(Ionflux::Mapping::MappingValue newScale);
};

}

}

/** \file PointCoord.hpp
 * \brief Point coordinate mapping (header).
 */
#endif
