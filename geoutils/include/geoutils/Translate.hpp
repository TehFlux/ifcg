#ifndef IONFLUX_GEOUTILS_TRANSLATE
#define IONFLUX_GEOUTILS_TRANSLATE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Translate.hpp                   Transform node: Translate (header).
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
#include "geoutils/Range.hpp"
#include "geoutils/Vector3.hpp"
#include "geoutils/Vector3Mapping.hpp"
#include "geoutils/TransformNode.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

/// Class information for class Translate.
class TranslateClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		TranslateClassInfo();
		/// Destructor.
		virtual ~TranslateClassInfo();
};

/** Transform node: Translate.
 * \ingroup geoutils
 *
 * Translate elements from the input group. The translation vector is the 
 * sum of the constant translation vector and the vectors resulting from 
 * the input mappings, if specified. The index mapping maps the interval 
 * [0...1] to the interval [0...1]^3 and controls the translation depending
 * on the index of the input element, where the indices are mapped to the 
 * interval depending on the total number of elements. The distance mapping
 * maps an interval of distances to the interval [0...1]^3 and controls the
 * translation depending on the distance of the element barycenter from the
 * coordinate origin. For both mappings, the resulting value in the range 
 * [0...1]^3 is translated to an offset vector in the range specified for 
 * that mapping, where a mapping output value of 0 corresponds to the lower
 * bound of the corresponding range and a mapping output value of 1 
 * corresponds to the upper bound of that range.
 */
class Translate
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
	private:
		
	protected:
		/// Offset.
		Ionflux::GeoUtils::Vector3 offset;
		/// Index mapping function.
		Ionflux::GeoUtils::Mapping::Vector3Mapping* indexFunc;
		/// Distance mapping function.
		Ionflux::GeoUtils::Mapping::Vector3Mapping* distanceFunc;
		
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
		/// Class information instance.
		static const TranslateClassInfo translateClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Translate object.
		 */
		Translate();
		
		/** Constructor.
		 *
		 * Construct new Translate object.
		 *
		 * \param other Other object.
		 */
		Translate(const Ionflux::GeoUtils::TransformNodes::Translate& other);
		
		/** Constructor.
		 *
		 * Construct new Translate object.
		 *
		 * \param initOffset Offset.
		 * \param initIndexFunc Index mapping function.
		 * \param initDistanceFunc Distance mapping function.
		 * \param nodeID Node ID.
		 */
		Translate(const Ionflux::GeoUtils::Vector3& initOffset, 
		Ionflux::GeoUtils::Mapping::Vector3Mapping* initIndexFunc = 0, 
		Ionflux::GeoUtils::Mapping::Vector3Mapping* initDistanceFunc = 0, const 
		Ionflux::ObjectBase::IFObjectID& nodeID = "");
		
		/** Destructor.
		 *
		 * Destruct Translate object.
		 */
		virtual ~Translate();
		
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
		virtual Ionflux::GeoUtils::TransformNodes::Translate& operator=(const 
		Ionflux::GeoUtils::TransformNodes::Translate& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Translate* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::Translate* 
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
		static Ionflux::GeoUtils::TransformNodes::Translate* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get offset.
		 *
		 * \return Current value of offset.
		 */
		virtual Ionflux::GeoUtils::Vector3 getOffset() const;
		
		/** Set offset.
		 *
		 * Set new value of offset.
		 *
		 * \param newOffset New value of offset.
		 */
		virtual void setOffset(const Ionflux::GeoUtils::Vector3& newOffset);
		
		/** Get index mapping function.
		 *
		 * \return Current value of index mapping function.
		 */
		virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* getIndexFunc() const;
		
		/** Set index mapping function.
		 *
		 * Set new value of index mapping function.
		 *
		 * \param newIndexFunc New value of index mapping function.
		 */
		virtual void setIndexFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
		newIndexFunc);
		
		/** Get distance mapping function.
		 *
		 * \return Current value of distance mapping function.
		 */
		virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* getDistanceFunc() 
		const;
		
		/** Set distance mapping function.
		 *
		 * Set new value of distance mapping function.
		 *
		 * \param newDistanceFunc New value of distance mapping function.
		 */
		virtual void setDistanceFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
		newDistanceFunc);
};

}

}

}

/** \file Translate.hpp
 * \brief Transform node: Translate (header).
 */
#endif
