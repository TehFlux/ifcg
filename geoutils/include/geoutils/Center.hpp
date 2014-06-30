#ifndef IONFLUX_GEOUTILS_CENTER
#define IONFLUX_GEOUTILS_CENTER
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Center.hpp                      Transform node: Center (header).
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

/// Class information for class Center.
class CenterClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		CenterClassInfo();
		/// Destructor.
		virtual ~CenterClassInfo();
};

/** Transform node: Center.
 * \ingroup geoutils
 *
 * Center elements from the input group using the specified centering 
 * method and origin vector.
 */
class Center
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
	private:
		
	protected:
		/// Origin vector.
		Ionflux::GeoUtils::Vector3 origin;
		/// Centering method.
		Ionflux::GeoUtils::CenteringMethod method;
		
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
		static const CenterClassInfo centerClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Center object.
		 */
		Center();
		
		/** Constructor.
		 *
		 * Construct new Center object.
		 *
		 * \param other Other object.
		 */
		Center(const Ionflux::GeoUtils::TransformNodes::Center& other);
		
		/** Constructor.
		 *
		 * Construct new Center object.
		 *
		 * \param initMethod Centering method.
		 * \param initOrigin Origin vector.
		 * \param nodeID Node ID.
		 */
		Center(Ionflux::GeoUtils::CenteringMethod initMethod, const 
		Ionflux::GeoUtils::Vector3& initOrigin = GeoUtils::Vector3::ZERO, const 
		Ionflux::ObjectBase::IFObjectID& nodeID = "");
		
		/** Destructor.
		 *
		 * Destruct Center object.
		 */
		virtual ~Center();
		
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
		virtual Ionflux::GeoUtils::TransformNodes::Center& operator=(const 
		Ionflux::GeoUtils::TransformNodes::Center& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Center* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::Center* 
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
		static Ionflux::GeoUtils::TransformNodes::Center* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get origin vector.
		 *
		 * \return Current value of origin vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getOrigin() const;
		
		/** Set origin vector.
		 *
		 * Set new value of origin vector.
		 *
		 * \param newOrigin New value of origin vector.
		 */
		virtual void setOrigin(const Ionflux::GeoUtils::Vector3& newOrigin);
		
		/** Get centering method.
		 *
		 * \return Current value of centering method.
		 */
		virtual Ionflux::GeoUtils::CenteringMethod getMethod() const;
		
		/** Set centering method.
		 *
		 * Set new value of centering method.
		 *
		 * \param newMethod New value of centering method.
		 */
		virtual void setMethod(Ionflux::GeoUtils::CenteringMethod newMethod);
};

}

}

}

/** \file Center.hpp
 * \brief Transform node: Center (header).
 */
#endif
