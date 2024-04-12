#ifndef IONFLUX_GEOUTILS_UNWRAP
#define IONFLUX_GEOUTILS_UNWRAP
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Unwrap.hpp                      Transform node: Unwrap (header).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

/// Class information for class Unwrap.
class UnwrapClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		UnwrapClassInfo();
		/// Destructor.
		virtual ~UnwrapClassInfo();
};

/** Transform node: Unwrap.
 * \ingroup geoutils
 *
 * Unwrap groups which are elements of the input group by adding copies of 
 * them as output groups. Elements of the input group which are not groups 
 * are collected into a single output group.
 */
class Unwrap
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
	private:
		
	protected:
		
		/** Process inputs.
		 *
		 * Update the outputs of the node by processing the inputs. This 
		 * should be implemented by derived classes.
		 */
		virtual void process();
		
	public:
		/// Input ID: source.
		static const unsigned int INPUT_SOURCE;
		/// Output ID: first.
		static const unsigned int OUTPUT_FIRST;
		/// Class information instance.
		static const UnwrapClassInfo unwrapClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Unwrap object.
		 */
		Unwrap();
		
		/** Constructor.
		 *
		 * Construct new Unwrap object.
		 *
		 * \param other Other object.
		 */
		Unwrap(const Ionflux::GeoUtils::TransformNodes::Unwrap& other);
		
		/** Constructor.
		 *
		 * Construct new Unwrap object.
		 *
		 * \param nodeID Node ID.
		 */
		Unwrap(const Ionflux::ObjectBase::IFObjectID& nodeID);
		
		/** Destructor.
		 *
		 * Destruct Unwrap object.
		 */
		virtual ~Unwrap();
		
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
		virtual Ionflux::GeoUtils::TransformNodes::Unwrap& operator=(const 
		Ionflux::GeoUtils::TransformNodes::Unwrap& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Unwrap* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::Unwrap* 
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
		static Ionflux::GeoUtils::TransformNodes::Unwrap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
};

}

}

}

/** \file Unwrap.hpp
 * \brief Transform node: Unwrap (header).
 */
#endif
