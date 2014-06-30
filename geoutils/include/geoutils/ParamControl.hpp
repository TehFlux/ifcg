#ifndef IONFLUX_GEOUTILS_PARAMCONTROL
#define IONFLUX_GEOUTILS_PARAMCONTROL
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ParamControl.hpp                Parameter control (header).
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
#include "geoutils/TransformNode.hpp"
#include "ifmapping/Mapping.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

/// Class information for class ParamControl.
class ParamControlClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ParamControlClassInfo();
		/// Destructor.
		virtual ~ParamControlClassInfo();
};

/** Parameter control.
 * \ingroup geoutils
 *
 * A parameter control is used to control a parameter on a transform node. 
 * Each time the parameter control is invoked with a value, it calls its 
 * associated mapping with that value and then sets the parameter it 
 * controls on the transform node to the mapped value. A coordinate index 
 * can be set on a parameter control. If this is done, the parameter 
 * control will be passed a (normalized) coordinate value instead of the 
 * regular value by callers that support this feature (such as the Batch 
 * node).
 */
class ParamControl
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Transform node.
		Ionflux::GeoUtils::TransformNodes::TransformNode* node;
		/// Parameter ID.
		Ionflux::ObjectBase::IFParamID paramID;
		/// Mapping.
		Ionflux::Mapping::Mapping* func;
		/// Coordinate index.
		unsigned int coord;
		
	public:
		/// Class information instance.
		static const ParamControlClassInfo paramControlClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ParamControl object.
		 */
		ParamControl();
		
		/** Constructor.
		 *
		 * Construct new ParamControl object.
		 *
		 * \param other Other object.
		 */
		ParamControl(const Ionflux::GeoUtils::TransformNodes::ParamControl& other);
		
		/** Constructor.
		 *
		 * Construct new ParamControl object.
		 *
		 * \param initNode Transform node.
		 * \param initParamID Parameter ID.
		 * \param initFunc Mapping.
		 * \param initCoord Coordinate index.
		 */
		ParamControl(Ionflux::GeoUtils::TransformNodes::TransformNode* initNode, 
		Ionflux::ObjectBase::IFParamID initParamID = "", 
		Ionflux::Mapping::Mapping* initFunc = 0, unsigned int initCoord = 
		COORDINATE_NOT_SET);
		
		/** Destructor.
		 *
		 * Destruct ParamControl object.
		 */
		virtual ~ParamControl();
		
		/** Call.
		 *
		 * Update the parameter controlled by the object using the specified 
		 * value as the input to the mapping.
		 *
		 * \param value Value.
		 */
		virtual void call(Ionflux::Mapping::MappingValue value) const;
		
		/** Call.
		 *
		 * Update the parameter controlled by the object using the specified 
		 * value as the input to the mapping.
		 *
		 * \param value Value.
		 */
		virtual void operator()(Ionflux::Mapping::MappingValue value) const;
		
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
		virtual Ionflux::GeoUtils::TransformNodes::ParamControl& operator=(const 
		Ionflux::GeoUtils::TransformNodes::ParamControl& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::ParamControl* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::ParamControl* 
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
		static Ionflux::GeoUtils::TransformNodes::ParamControl* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get transform node.
		 *
		 * \return Current value of transform node.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::TransformNode* getNode() 
		const;
		
		/** Set transform node.
		 *
		 * Set new value of transform node.
		 *
		 * \param newNode New value of transform node.
		 */
		virtual void setNode(Ionflux::GeoUtils::TransformNodes::TransformNode* 
		newNode);
		
		/** Get parameter ID.
		 *
		 * \return Current value of parameter ID.
		 */
		virtual Ionflux::ObjectBase::IFParamID getParamID() const;
		
		/** Set parameter ID.
		 *
		 * Set new value of parameter ID.
		 *
		 * \param newParamID New value of parameter ID.
		 */
		virtual void setParamID(const Ionflux::ObjectBase::IFParamID& 
		newParamID);
		
		/** Get mapping.
		 *
		 * \return Current value of mapping.
		 */
		virtual Ionflux::Mapping::Mapping* getFunc() const;
		
		/** Set mapping.
		 *
		 * Set new value of mapping.
		 *
		 * \param newFunc New value of mapping.
		 */
		virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
		
		/** Get coordinate index.
		 *
		 * \return Current value of coordinate index.
		 */
		virtual unsigned int getCoord() const;
		
		/** Set coordinate index.
		 *
		 * Set new value of coordinate index.
		 *
		 * \param newCoord New value of coordinate index.
		 */
		virtual void setCoord(unsigned int newCoord);
};

}

}

}

/** \file ParamControl.hpp
 * \brief Parameter control (header).
 */
#endif
