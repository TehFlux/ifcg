#ifndef IONFLUX_GEOUTILS_WRAP
#define IONFLUX_GEOUTILS_WRAP
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Wrap.hpp                        Transform node: Wrap (header).
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

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

/// Class information for class Wrap.
class WrapClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		WrapClassInfo();
		/// Destructor.
		virtual ~WrapClassInfo();
};

/** Transform node: Wrap.
 * \ingroup geoutils
 *
 * Wrap a copy of each of the input groups into the output group.
 */
class Wrap
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
		/// Input ID: first.
		static const unsigned int INPUT_FIRST;
		/// Output ID: target.
		static const unsigned int OUTPUT_TARGET;
		/// Class information instance.
		static const WrapClassInfo wrapClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Wrap object.
		 */
		Wrap();
		
		/** Constructor.
		 *
		 * Construct new Wrap object.
		 *
		 * \param other Other object.
		 */
		Wrap(const Ionflux::GeoUtils::TransformNodes::Wrap& other);
		
		/** Constructor.
		 *
		 * Construct new Wrap object.
		 *
		 * \param nodeID Node ID.
		 */
		Wrap(const Ionflux::ObjectBase::IFObjectID& nodeID);
		
		/** Destructor.
		 *
		 * Destruct Wrap object.
		 */
		virtual ~Wrap();
		
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
		virtual Ionflux::GeoUtils::TransformNodes::Wrap& operator=(const 
		Ionflux::GeoUtils::TransformNodes::Wrap& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Wrap* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::Wrap* 
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
		static Ionflux::GeoUtils::TransformNodes::Wrap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}

/** \file Wrap.hpp
 * \brief Transform node: Wrap (header).
 */
#endif
