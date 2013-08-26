#ifndef IONFLUX_GEOUTILS_SCALE
#define IONFLUX_GEOUTILS_SCALE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Scale.hpp                       Transform node: Scale (header).
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

/// Class information for class Scale.
class ScaleClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ScaleClassInfo();
		/// Destructor.
		virtual ~ScaleClassInfo();
};

/** Transform node: Scale.
 * \ingroup geoutils
 *
 * Scale elements from the input group. The scale vector is the sum of the 
 * constant scale vector and the vectors resulting from the input mappings,
 * if specified. The index mapping maps the interval [0...1] to the 
 * interval [0...1]^3 and controls the scale factor depending on the index 
 * of the input element, where the indices are mapped to the interval 
 * depending on the total number of elements. The distance mapping maps an 
 * interval of distances to the interval [0...1]^3 and controls the scale 
 * factor depending on the distance of the element barycenter from the 
 * coordinate origin. For both mappings, the resulting value in the range 
 * [0...1]^3 is translated to an offset vector in the range specified for 
 * that mapping, where a mapping output value of 0 corresponds to the lower
 * bound of the corresponding range and a mapping output value of 1 
 * corresponds to the upper bound of that range. The centering method 
 * determines the center of scaling. If \c CENTER_ORIGIN is used, all 
 * elements are scaled around the origin. For \c CENTER_BARYCENTER and \c 
 * CENTER_BOUNDS, elements are scaled around individual element centers 
 * determined using the specified method.
 */
class Scale
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
	private:
		
	protected:
		/// Scale vector.
		Ionflux::GeoUtils::Vector3 scale;
		/// Index mapping function.
		Ionflux::GeoUtils::Mapping::Vector3Mapping* indexFunc;
		/// Distance mapping function.
		Ionflux::GeoUtils::Mapping::Vector3Mapping* distanceFunc;
		/// Centering method.
		Ionflux::GeoUtils::CenteringMethod centeringMethod;
		/// Scale factor (all axes).
		Ionflux::Mapping::MappingValue scaleFactor;
		/// Delta scale factor (all axes).
		Ionflux::Mapping::MappingValue deltaScaleFactor;
		
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
		static const ScaleClassInfo scaleClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Scale object.
		 */
		Scale();
		
		/** Constructor.
		 *
		 * Construct new Scale object.
		 *
		 * \param other Other object.
		 */
		Scale(const Ionflux::GeoUtils::TransformNodes::Scale& other);
		
		/** Constructor.
		 *
		 * Construct new Scale object.
		 *
		 * \param initScale Scale vector.
		 * \param initIndexFunc Index mapping function.
		 * \param initDistanceFunc Distance mapping function.
		 * \param initCenteringMethod Centering method.
		 * \param initScaleFactor Scale factor (all axes).
		 * \param initDeltaScaleFactor Delta scale factor (all axes).
		 * \param nodeID Node ID.
		 */
		Scale(const Ionflux::GeoUtils::Vector3& initScale, 
		Ionflux::GeoUtils::Mapping::Vector3Mapping* initIndexFunc = 0, 
		Ionflux::GeoUtils::Mapping::Vector3Mapping* initDistanceFunc = 0, 
		Ionflux::GeoUtils::CenteringMethod initCenteringMethod = CENTER_ORIGIN, 
		Ionflux::Mapping::MappingValue initScaleFactor = 1., 
		Ionflux::Mapping::MappingValue initDeltaScaleFactor = 0., const 
		Ionflux::ObjectBase::IFObjectID& nodeID = "");
		
		/** Destructor.
		 *
		 * Destruct Scale object.
		 */
		virtual ~Scale();
		
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
		virtual Ionflux::GeoUtils::TransformNodes::Scale& operator=(const 
		Ionflux::GeoUtils::TransformNodes::Scale& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Scale* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::Scale* 
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
		static Ionflux::GeoUtils::TransformNodes::Scale* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
		
		/** Get scale vector.
		 *
		 * \return Current value of scale vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getScale() const;
		
		/** Set scale vector.
		 *
		 * Set new value of scale vector.
		 *
		 * \param newScale New value of scale vector.
		 */
		virtual void setScale(const Ionflux::GeoUtils::Vector3& newScale);
		
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
		
		/** Get centering method.
		 *
		 * \return Current value of centering method.
		 */
		virtual Ionflux::GeoUtils::CenteringMethod getCenteringMethod() const;
		
		/** Set centering method.
		 *
		 * Set new value of centering method.
		 *
		 * \param newCenteringMethod New value of centering method.
		 */
		virtual void setCenteringMethod(Ionflux::GeoUtils::CenteringMethod 
		newCenteringMethod);
		
		/** Get scale factor (all axes).
		 *
		 * \return Current value of scale factor (all axes).
		 */
		virtual Ionflux::Mapping::MappingValue getScaleFactor() const;
		
		/** Set scale factor (all axes).
		 *
		 * Set new value of scale factor (all axes).
		 *
		 * \param newScaleFactor New value of scale factor (all axes).
		 */
		virtual void setScaleFactor(Ionflux::Mapping::MappingValue 
		newScaleFactor);
		
		/** Get delta scale factor (all axes).
		 *
		 * \return Current value of delta scale factor (all axes).
		 */
		virtual Ionflux::Mapping::MappingValue getDeltaScaleFactor() const;
		
		/** Set delta scale factor (all axes).
		 *
		 * Set new value of delta scale factor (all axes).
		 *
		 * \param newDeltaScaleFactor New value of delta scale factor (all axes).
		 */
		virtual void setDeltaScaleFactor(Ionflux::Mapping::MappingValue 
		newDeltaScaleFactor);
};

}

}

}

/** \file Scale.hpp
 * \brief Transform node: Scale (header).
 */
#endif
