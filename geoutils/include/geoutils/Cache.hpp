#ifndef IONFLUX_GEOUTILS_CACHE
#define IONFLUX_GEOUTILS_CACHE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Cache.hpp                       Transform node: Cache (header).
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

/// Class information for class Cache.
class CacheClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		CacheClassInfo();
		/// Destructor.
		virtual ~CacheClassInfo();
};

/** Transform node: Cache.
 * \ingroup geoutils
 *
 * Provides a copy of the input group as its output group until the 
 * inputCache is cleared by an explicit call (cleanup() does not clean the 
 * input cache for a Cache node).
 */
class Cache
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
		/// Output ID: target.
		static const unsigned int OUTPUT_TARGET;
		/// Class information instance.
		static const CacheClassInfo cacheClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Cache object.
		 */
		Cache();
		
		/** Constructor.
		 *
		 * Construct new Cache object.
		 *
		 * \param other Other object.
		 */
		Cache(const Ionflux::GeoUtils::TransformNodes::Cache& other);
		
		/** Constructor.
		 *
		 * Construct new Cache object.
		 *
		 * \param nodeID Node ID.
		 */
		Cache(const Ionflux::ObjectBase::IFObjectID& nodeID);
		
		/** Destructor.
		 *
		 * Destruct Cache object.
		 */
		virtual ~Cache();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Clean up.
		 *
		 * Clean up resources created by the node during an update operation.
		 */
		virtual void cleanup();
		
		/** Update.
		 *
		 * Update the outputs of the node. This updates all inputs and checks 
		 * the loop counter to make sure the maximum number of loop iterations
		 * is not exceeded. It clears the output groups and calls process() to
		 * do the actual processing of the inputs. Note that a transform node 
		 * does not have outputs unless update() has been called and finished 
		 * processing at least once. Outputs are considered a cache rather 
		 * than state of the object (they are also not copied when using an 
		 * assignment or copy constructor). See the spec for details.
		 */
		virtual void update();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Cache& operator=(const 
		Ionflux::GeoUtils::TransformNodes::Cache& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Cache* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::Cache* 
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
		static Ionflux::GeoUtils::TransformNodes::Cache* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}

/** \file Cache.hpp
 * \brief Transform node: Cache (header).
 */
#endif
