#ifndef IONFLUX_GEOUTILS_SCATTER
#define IONFLUX_GEOUTILS_SCATTER
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Scatter.hpp                     Transform node: Scatter (header).
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

#include "ifmapping/types.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Range.hpp"
#include "geoutils/Vector3.hpp"
#include "geoutils/Vector3Mapping.hpp"
#include "geoutils/Shape3.hpp"
#include "geoutils/TransformNode.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

/// Class information for class Scatter.
class ScatterClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ScatterClassInfo();
		/// Destructor.
		virtual ~ScatterClassInfo();
};

/** Transform node: Scatter.
 * \ingroup geoutils
 *
 * Scatter elements from the input group. The offset vectors for scattering
 * are taken from the specified mapping and scaled with the specified scale
 * vector, scale factor and delta scale factor. A constant offset can be 
 * specified that is added to all element offsets. A mapping can be 
 * specified to control the order in which offset vectors are read from the
 * offset mapping. The scatter node also supports optional mappings for 
 * scaling individual elements of the input group according to their index 
 * or distance from the coordinate system center after scattering.
 */
class Scatter
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
	private:
		
	protected:
		/// Constant offset.
		Ionflux::GeoUtils::Vector3 offset;
		/// Offset mapping.
		Ionflux::GeoUtils::Mapping::Vector3Mapping* offsetFunc;
		/// Offset index mapping.
		Ionflux::Mapping::Mapping* offsetIndexFunc;
		/// Offset scale vector.
		Ionflux::GeoUtils::Vector3 offsetScale;
		/// Offset scale factor (all axes).
		Ionflux::Mapping::MappingValue offsetScaleFactor;
		/// Offset delta scale factor (all axes).
		Ionflux::Mapping::MappingValue offsetDeltaScaleFactor;
		/// Offset for the offset index.
		Ionflux::Mapping::MappingValue offsetIndexOffset;
		/// Scale factor for the offset index.
		Ionflux::Mapping::MappingValue offsetIndexScale;
		/// Element scale vector.
		Ionflux::GeoUtils::Vector3 elementScale;
		/// Element scale factor (all axes).
		Ionflux::Mapping::MappingValue elementScaleFactor;
		/// Element delta scale factor (all axes).
		Ionflux::Mapping::MappingValue elementDeltaScaleFactor;
		/// Element scale index mapping.
		Ionflux::GeoUtils::Mapping::Vector3Mapping* elementScaleIndexFunc;
		/// Element scale distance mapping function.
		Ionflux::GeoUtils::Mapping::Vector3Mapping* elementScaleDistanceFunc;
		/// Centering method for element scaling.
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
		/// Default number of lookup table entries.
		static const unsigned int DEFAULT_NUM_LUT_ENTRIES;
		/// Offset index range.
		static const Ionflux::Mapping::Range OFFSET_INDEX_RANGE;
		/// Class information instance.
		static const ScatterClassInfo scatterClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Scatter object.
		 */
		Scatter();
		
		/** Constructor.
		 *
		 * Construct new Scatter object.
		 *
		 * \param other Other object.
		 */
		Scatter(const Ionflux::GeoUtils::TransformNodes::Scatter& other);
		
		/** Constructor.
		 *
		 * Construct new Scatter object.
		 *
		 * \param initOffset Offset.
		 * \param initOffsetFunc Offset mapping.
		 * \param initOffsetIndexFunc Offset index mapping.
		 * \param initOffsetScale Offset scale vector.
		 * \param initOffsetScaleFactor Offset scale factor (all axes).
		 * \param initOffsetDeltaScaleFactor Offset delta scale factor (all 
		 * axes).
		 * \param initOffsetIndexOffset Offset index offset.
		 * \param initOffsetIndexScale Offset index scale.
		 * \param initElementScale Element scale vector.
		 * \param initElementScaleFactor Element scale factor (all axes).
		 * \param initElementDeltaScaleFactor Element delta scale factor (all 
		 * axes).
		 * \param initElementScaleIndexFunc Scale index mapping function.
		 * \param initElementScaleDistanceFunc Scale distance mapping function.
		 * \param initCenteringMethod Centering method.
		 * \param nodeID Node ID.
		 */
		Scatter(const Ionflux::GeoUtils::Vector3& initOffset, 
		Ionflux::GeoUtils::Mapping::Vector3Mapping* initOffsetFunc = 0, 
		Ionflux::Mapping::Mapping* initOffsetIndexFunc = 0, const 
		Ionflux::GeoUtils::Vector3& initOffsetScale = GeoUtils::Vector3::E_SUM, 
		Ionflux::Mapping::MappingValue initOffsetScaleFactor = 1., 
		Ionflux::Mapping::MappingValue initOffsetDeltaScaleFactor = 0., 
		Ionflux::Mapping::MappingValue initOffsetIndexOffset = 0., 
		Ionflux::Mapping::MappingValue initOffsetIndexScale = 1., const 
		Ionflux::GeoUtils::Vector3& initElementScale = GeoUtils::Vector3::E_SUM, 
		Ionflux::Mapping::MappingValue initElementScaleFactor = 1., 
		Ionflux::Mapping::MappingValue initElementDeltaScaleFactor = 0., 
		Ionflux::GeoUtils::Mapping::Vector3Mapping* initElementScaleIndexFunc = 
		0, Ionflux::GeoUtils::Mapping::Vector3Mapping* 
		initElementScaleDistanceFunc = 0, Ionflux::GeoUtils::CenteringMethod 
		initCenteringMethod = CENTER_BARYCENTER, const 
		Ionflux::ObjectBase::IFObjectID& nodeID = "");
		
		/** Destructor.
		 *
		 * Destruct Scatter object.
		 */
		virtual ~Scatter();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Create offset lookup table.
		 *
		 * Create an offset lookup table suitable for use with the scatter 
		 * node. If the optional source functions are specified, those 
		 * functions will be used as the source for generating coordinate 
		 * values for the lookup table. A random normal generator with the 
		 * sppecified parameters will be used in place of any coordinate 
		 * functions that are not specified. If an optional reference object 
		 * is specified, all generated offsets will be contained within the 
		 * reference object. The mapping that is returned will not be 
		 * referenced and must be managed by the caller.
		 *
		 * \param numEntries Number of entries in the table.
		 * \param stdDev Standard deviation for normal distribution.
		 * \param mean Mean value for normal distribution.
		 * \param refObject Reference object.
		 * \param sourceFuncX Source function (X).
		 * \param sourceFuncY Source function (Y).
		 * \param sourceFuncZ Source function (Z).
		 *
		 * \return Offset lookup table.
		 */
		static Ionflux::GeoUtils::Mapping::Vector3Mapping* createLUT(unsigned int
		numEntries = DEFAULT_NUM_LUT_ENTRIES, const Ionflux::GeoUtils::Vector3& 
		stdDev = Ionflux::GeoUtils::Vector3::E_SUM, const 
		Ionflux::GeoUtils::Vector3& mean = Ionflux::GeoUtils::Vector3::ZERO, 
		Ionflux::GeoUtils::Shape3* refObject = 0, Ionflux::Mapping::Mapping* 
		sourceFuncX = 0, Ionflux::Mapping::Mapping* sourceFuncY = 0, 
		Ionflux::Mapping::Mapping* sourceFuncZ = 0);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Scatter& operator=(const 
		Ionflux::GeoUtils::TransformNodes::Scatter& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Scatter* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::Scatter* 
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
		static Ionflux::GeoUtils::TransformNodes::Scatter* 
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
		
		/** Get constant offset.
		 *
		 * \return Current value of constant offset.
		 */
		virtual Ionflux::GeoUtils::Vector3 getOffset() const;
		
		/** Set constant offset.
		 *
		 * Set new value of constant offset.
		 *
		 * \param newOffset New value of constant offset.
		 */
		virtual void setOffset(const Ionflux::GeoUtils::Vector3& newOffset);
		
		/** Get offset mapping.
		 *
		 * \return Current value of offset mapping.
		 */
		virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* getOffsetFunc() 
		const;
		
		/** Set offset mapping.
		 *
		 * Set new value of offset mapping.
		 *
		 * \param newOffsetFunc New value of offset mapping.
		 */
		virtual void setOffsetFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
		newOffsetFunc);
		
		/** Get offset index mapping.
		 *
		 * \return Current value of offset index mapping.
		 */
		virtual Ionflux::Mapping::Mapping* getOffsetIndexFunc() const;
		
		/** Set offset index mapping.
		 *
		 * Set new value of offset index mapping.
		 *
		 * \param newOffsetIndexFunc New value of offset index mapping.
		 */
		virtual void setOffsetIndexFunc(Ionflux::Mapping::Mapping* 
		newOffsetIndexFunc);
		
		/** Get offset scale vector.
		 *
		 * \return Current value of offset scale vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getOffsetScale() const;
		
		/** Set offset scale vector.
		 *
		 * Set new value of offset scale vector.
		 *
		 * \param newOffsetScale New value of offset scale vector.
		 */
		virtual void setOffsetScale(const Ionflux::GeoUtils::Vector3& 
		newOffsetScale);
		
		/** Get offset scale factor (all axes).
		 *
		 * \return Current value of offset scale factor (all axes).
		 */
		virtual Ionflux::Mapping::MappingValue getOffsetScaleFactor() const;
		
		/** Set offset scale factor (all axes).
		 *
		 * Set new value of offset scale factor (all axes).
		 *
		 * \param newOffsetScaleFactor New value of offset scale factor (all 
		 * axes).
		 */
		virtual void setOffsetScaleFactor(Ionflux::Mapping::MappingValue 
		newOffsetScaleFactor);
		
		/** Get offset delta scale factor (all axes).
		 *
		 * \return Current value of offset delta scale factor (all axes).
		 */
		virtual Ionflux::Mapping::MappingValue getOffsetDeltaScaleFactor() const;
		
		/** Set offset delta scale factor (all axes).
		 *
		 * Set new value of offset delta scale factor (all axes).
		 *
		 * \param newOffsetDeltaScaleFactor New value of offset delta scale 
		 * factor (all axes).
		 */
		virtual void setOffsetDeltaScaleFactor(Ionflux::Mapping::MappingValue 
		newOffsetDeltaScaleFactor);
		
		/** Get offset for the offset index.
		 *
		 * \return Current value of offset for the offset index.
		 */
		virtual Ionflux::Mapping::MappingValue getOffsetIndexOffset() const;
		
		/** Set offset for the offset index.
		 *
		 * Set new value of offset for the offset index.
		 *
		 * \param newOffsetIndexOffset New value of offset for the offset index.
		 */
		virtual void setOffsetIndexOffset(Ionflux::Mapping::MappingValue 
		newOffsetIndexOffset);
		
		/** Get scale factor for the offset index.
		 *
		 * \return Current value of scale factor for the offset index.
		 */
		virtual Ionflux::Mapping::MappingValue getOffsetIndexScale() const;
		
		/** Set scale factor for the offset index.
		 *
		 * Set new value of scale factor for the offset index.
		 *
		 * \param newOffsetIndexScale New value of scale factor for the offset 
		 * index.
		 */
		virtual void setOffsetIndexScale(Ionflux::Mapping::MappingValue 
		newOffsetIndexScale);
		
		/** Get element scale vector.
		 *
		 * \return Current value of element scale vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getElementScale() const;
		
		/** Set element scale vector.
		 *
		 * Set new value of element scale vector.
		 *
		 * \param newElementScale New value of element scale vector.
		 */
		virtual void setElementScale(const Ionflux::GeoUtils::Vector3& 
		newElementScale);
		
		/** Get element scale factor (all axes).
		 *
		 * \return Current value of element scale factor (all axes).
		 */
		virtual Ionflux::Mapping::MappingValue getElementScaleFactor() const;
		
		/** Set element scale factor (all axes).
		 *
		 * Set new value of element scale factor (all axes).
		 *
		 * \param newElementScaleFactor New value of element scale factor (all 
		 * axes).
		 */
		virtual void setElementScaleFactor(Ionflux::Mapping::MappingValue 
		newElementScaleFactor);
		
		/** Get element delta scale factor (all axes).
		 *
		 * \return Current value of element delta scale factor (all axes).
		 */
		virtual Ionflux::Mapping::MappingValue getElementDeltaScaleFactor() 
		const;
		
		/** Set element delta scale factor (all axes).
		 *
		 * Set new value of element delta scale factor (all axes).
		 *
		 * \param newElementDeltaScaleFactor New value of element delta scale 
		 * factor (all axes).
		 */
		virtual void setElementDeltaScaleFactor(Ionflux::Mapping::MappingValue 
		newElementDeltaScaleFactor);
		
		/** Get element scale index mapping.
		 *
		 * \return Current value of element scale index mapping.
		 */
		virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* 
		getElementScaleIndexFunc() const;
		
		/** Set element scale index mapping.
		 *
		 * Set new value of element scale index mapping.
		 *
		 * \param newElementScaleIndexFunc New value of element scale index 
		 * mapping.
		 */
		virtual void 
		setElementScaleIndexFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
		newElementScaleIndexFunc);
		
		/** Get element scale distance mapping function.
		 *
		 * \return Current value of element scale distance mapping function.
		 */
		virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* 
		getElementScaleDistanceFunc() const;
		
		/** Set element scale distance mapping function.
		 *
		 * Set new value of element scale distance mapping function.
		 *
		 * \param newElementScaleDistanceFunc New value of element scale distance
		 * mapping function.
		 */
		virtual void 
		setElementScaleDistanceFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
		newElementScaleDistanceFunc);
		
		/** Get centering method for element scaling.
		 *
		 * \return Current value of centering method for element scaling.
		 */
		virtual Ionflux::GeoUtils::CenteringMethod getCenteringMethod() const;
		
		/** Set centering method for element scaling.
		 *
		 * Set new value of centering method for element scaling.
		 *
		 * \param newCenteringMethod New value of centering method for element 
		 * scaling.
		 */
		virtual void setCenteringMethod(Ionflux::GeoUtils::CenteringMethod 
		newCenteringMethod);
};

}

}

}

/** \file Scatter.hpp
 * \brief Transform node: Scatter (header).
 */
#endif
