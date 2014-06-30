#ifndef IONFLUX_GEOUTILS_DUPLICATE
#define IONFLUX_GEOUTILS_DUPLICATE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Duplicate.hpp                   Transform node: Duplicate (header).
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
#include "ifmapping/Mapping.hpp"
#include "geoutils/TransformNode.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

/// Class information for class Duplicate.
class DuplicateClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		DuplicateClassInfo();
		/// Destructor.
		virtual ~DuplicateClassInfo();
};

/** Transform node: Duplicate.
 * \ingroup geoutils
 *
 * Duplicate elements from the input group. The element that is duplicated 
 * is selected in each step using the specified mapping function. The 
 * mapping function is expected to map the interval [0...1] to the interval
 * [0...1], where the input and output element indices are mapped to those 
 * intervals according to how many elements exist for input and output. If 
 * no mapping function is specified, source elements are selected in order.
 */
class Duplicate
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
	private:
		
	protected:
		/// Number of duplicates.
		unsigned int numDuplicates;
		/// Mapping function.
		Ionflux::Mapping::Mapping* func;
		
		/** Process inputs.
		 *
		 * Update the outputs of the node by processing the inputs. This 
		 * should be implemented by derived classes.
		 */
		virtual void process();
		
	public:
		/// Input ID: source.
		static const unsigned int INPUT_SOURCE;
		/// Output ID: target.
		static const unsigned int OUTPUT_TARGET;
		/// .
		static const unsigned int DEFAULT_NUM_DUPLICATES;
		/// .
		static const Ionflux::Mapping::Range CLAMP_RANGE;
		/// Class information instance.
		static const DuplicateClassInfo duplicateClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Duplicate object.
		 */
		Duplicate();
		
		/** Constructor.
		 *
		 * Construct new Duplicate object.
		 *
		 * \param other Other object.
		 */
		Duplicate(const Ionflux::GeoUtils::TransformNodes::Duplicate& other);
		
		/** Constructor.
		 *
		 * Construct new Duplicate object.
		 *
		 * \param initNumDuplicates Number of duplicates.
		 * \param initFunc Mapping function.
		 * \param nodeID Node ID.
		 */
		Duplicate(unsigned int initNumDuplicates, Ionflux::Mapping::Mapping* 
		initFunc = 0, const Ionflux::ObjectBase::IFObjectID& nodeID = "");
		
		/** Destructor.
		 *
		 * Destruct Duplicate object.
		 */
		virtual ~Duplicate();
		
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
		virtual Ionflux::GeoUtils::TransformNodes::Duplicate& operator=(const 
		Ionflux::GeoUtils::TransformNodes::Duplicate& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Duplicate* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::Duplicate* 
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
		static Ionflux::GeoUtils::TransformNodes::Duplicate* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Set parameter.
		 *
		 * Set the parameter with the specified ID.
		 *
		 * \param paramID Parameter ID.
		 * \param paramValue Parameter value.
		 */
		virtual void setParam(Ionflux::ObjectBase::IFParamID paramID, 
		Ionflux::Mapping::MappingValue paramValue);
		
		/** Get parameter.
		 *
		 * Get the parameter with the specified ID.
		 *
		 * \param paramID Parameter ID.
		 */
		virtual Ionflux::Mapping::MappingValue 
		getParam(Ionflux::ObjectBase::IFParamID paramID);
		
		/** Get number of duplicates.
		 *
		 * \return Current value of number of duplicates.
		 */
		virtual unsigned int getNumDuplicates() const;
		
		/** Set number of duplicates.
		 *
		 * Set new value of number of duplicates.
		 *
		 * \param newNumDuplicates New value of number of duplicates.
		 */
		virtual void setNumDuplicates(unsigned int newNumDuplicates);
		
		/** Get number of duplicates (parameter).
		 *
		 * \return Current value of number of duplicates (parameter).
		 */
		virtual Ionflux::Mapping::MappingValue getNumDuplicatesParam() const;
		
		/** Set number of duplicates (parameter).
		 *
		 * Set new value of number of duplicates (parameter).
		 *
		 * \param newNumDuplicatesParam New value of number of duplicates 
		 * (parameter).
		 */
		virtual void setNumDuplicatesParam(Ionflux::Mapping::MappingValue 
		newNumDuplicatesParam);
		
		/** Get mapping function.
		 *
		 * \return Current value of mapping function.
		 */
		virtual Ionflux::Mapping::Mapping* getFunc() const;
		
		/** Set mapping function.
		 *
		 * Set new value of mapping function.
		 *
		 * \param newFunc New value of mapping function.
		 */
		virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
};

}

}

}

/** \file Duplicate.hpp
 * \brief Transform node: Duplicate (header).
 */
#endif
