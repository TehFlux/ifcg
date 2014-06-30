#ifndef IONFLUX_GEOUTILS_ROTATE
#define IONFLUX_GEOUTILS_ROTATE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Rotate.hpp                      Transform node: Rotate (header).
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
#include "ifmapping/Mapping.hpp"
#include "geoutils/TransformNode.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

/// Class information for class Rotate.
class RotateClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		RotateClassInfo();
		/// Destructor.
		virtual ~RotateClassInfo();
};

/** Transform node: Rotate.
 * \ingroup geoutils
 *
 * Rotate elements from the input group around an axis. The rotation angle 
 * is the sum of the constant rotation angle and the rotation angles 
 * resulting from the input mappings, if specified. The index mapping maps 
 * the interval [0...1] to the interval [0...1] and controls the angle of 
 * rotation depending on the index of the input element, where the indices 
 * are mapped to the interval depending on the total number of elements. 
 * The distance mapping maps an interval of distances to the interval 
 * [0...1] and controls the angle of rotation depending on distance of the 
 * element barycenter from the coordinate origin. For both mappings, the 
 * resulting value in the range [0...1] is translated to an angle in the 
 * range specified for that mapping, where a mapping output value of 0 
 * corresponds to the lower bound of the corresponding range and a mapping 
 * output value of 1 corresponds to the upper bound of that range. The 
 * optional delta angle is multiplied by the update counter of the node and
 * added to the angle of rotation on each update. The centering method 
 * determines the center of rotation. If \c CENTER_ORIGIN is used, all 
 * elements are rotated around the origin. For \c CENTER_BARYCENTER and \c 
 * CENTER_BOUNDS, elements are rotated around individual element centers 
 * determined using the specified method.
 */
class Rotate
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
	private:
		
	protected:
		/// Axis of rotation.
		Ionflux::GeoUtils::AxisID axis;
		/// Angle.
		Ionflux::Mapping::MappingValue angle;
		/// Delta angle.
		Ionflux::Mapping::MappingValue deltaAngle;
		/// Index mapping function.
		Ionflux::Mapping::Mapping* indexFunc;
		/// Distance mapping function.
		Ionflux::Mapping::Mapping* distanceFunc;
		/// Index angle range.
		Ionflux::GeoUtils::Range indexRange;
		/// Distance angle range.
		Ionflux::GeoUtils::Range distanceRange;
		/// Centering method.
		Ionflux::GeoUtils::CenteringMethod centeringMethod;
		
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
		/// Default angle range.
		static const Ionflux::GeoUtils::Range DEFAULT_ANGLE_RANGE;
		/// Class information instance.
		static const RotateClassInfo rotateClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Rotate object.
		 */
		Rotate();
		
		/** Constructor.
		 *
		 * Construct new Rotate object.
		 *
		 * \param other Other object.
		 */
		Rotate(const Ionflux::GeoUtils::TransformNodes::Rotate& other);
		
		/** Constructor.
		 *
		 * Construct new Rotate object.
		 *
		 * \param initAxis Axis.
		 * \param initAngle Angle.
		 * \param deltaAngle Delta angle.
		 * \param initIndexFunc Index mapping function.
		 * \param initDistanceFunc Distance mapping function.
		 * \param initIndexRange Index angle range.
		 * \param initDistanceRange Distance angle range.
		 * \param initCenteringMethod Centering method.
		 * \param nodeID Node ID.
		 */
		Rotate(Ionflux::GeoUtils::AxisID initAxis, double initAngle = 0., double 
		deltaAngle = 0., Ionflux::Mapping::Mapping* initIndexFunc = 0, 
		Ionflux::Mapping::Mapping* initDistanceFunc = 0, Ionflux::GeoUtils::Range
		initIndexRange = DEFAULT_ANGLE_RANGE, Ionflux::GeoUtils::Range 
		initDistanceRange = DEFAULT_ANGLE_RANGE, 
		Ionflux::GeoUtils::CenteringMethod initCenteringMethod = CENTER_ORIGIN, 
		const Ionflux::ObjectBase::IFObjectID& nodeID = "");
		
		/** Destructor.
		 *
		 * Destruct Rotate object.
		 */
		virtual ~Rotate();
		
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
		virtual Ionflux::GeoUtils::TransformNodes::Rotate& operator=(const 
		Ionflux::GeoUtils::TransformNodes::Rotate& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Rotate* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::Rotate* 
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
		static Ionflux::GeoUtils::TransformNodes::Rotate* 
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
		
		/** Get axis of rotation.
		 *
		 * \return Current value of axis of rotation.
		 */
		virtual Ionflux::GeoUtils::AxisID getAxis() const;
		
		/** Set axis of rotation.
		 *
		 * Set new value of axis of rotation.
		 *
		 * \param newAxis New value of axis of rotation.
		 */
		virtual void setAxis(Ionflux::GeoUtils::AxisID newAxis);
		
		/** Get angle.
		 *
		 * \return Current value of angle.
		 */
		virtual Ionflux::Mapping::MappingValue getAngle() const;
		
		/** Set angle.
		 *
		 * Set new value of angle.
		 *
		 * \param newAngle New value of angle.
		 */
		virtual void setAngle(Ionflux::Mapping::MappingValue newAngle);
		
		/** Get delta angle.
		 *
		 * \return Current value of delta angle.
		 */
		virtual Ionflux::Mapping::MappingValue getDeltaAngle() const;
		
		/** Set delta angle.
		 *
		 * Set new value of delta angle.
		 *
		 * \param newDeltaAngle New value of delta angle.
		 */
		virtual void setDeltaAngle(Ionflux::Mapping::MappingValue newDeltaAngle);
		
		/** Get index mapping function.
		 *
		 * \return Current value of index mapping function.
		 */
		virtual Ionflux::Mapping::Mapping* getIndexFunc() const;
		
		/** Set index mapping function.
		 *
		 * Set new value of index mapping function.
		 *
		 * \param newIndexFunc New value of index mapping function.
		 */
		virtual void setIndexFunc(Ionflux::Mapping::Mapping* newIndexFunc);
		
		/** Get distance mapping function.
		 *
		 * \return Current value of distance mapping function.
		 */
		virtual Ionflux::Mapping::Mapping* getDistanceFunc() const;
		
		/** Set distance mapping function.
		 *
		 * Set new value of distance mapping function.
		 *
		 * \param newDistanceFunc New value of distance mapping function.
		 */
		virtual void setDistanceFunc(Ionflux::Mapping::Mapping* newDistanceFunc);
		
		/** Get index angle range.
		 *
		 * \return Current value of index angle range.
		 */
		virtual Ionflux::GeoUtils::Range getIndexRange() const;
		
		/** Set index angle range.
		 *
		 * Set new value of index angle range.
		 *
		 * \param newIndexRange New value of index angle range.
		 */
		virtual void setIndexRange(const Ionflux::GeoUtils::Range& 
		newIndexRange);
		
		/** Get distance angle range.
		 *
		 * \return Current value of distance angle range.
		 */
		virtual Ionflux::GeoUtils::Range getDistanceRange() const;
		
		/** Set distance angle range.
		 *
		 * Set new value of distance angle range.
		 *
		 * \param newDistanceRange New value of distance angle range.
		 */
		virtual void setDistanceRange(const Ionflux::GeoUtils::Range& 
		newDistanceRange);
		
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
};

}

}

}

/** \file Rotate.hpp
 * \brief Transform node: Rotate (header).
 */
#endif
