#ifndef IONFLUX_GEOUTILS_EXPLODE
#define IONFLUX_GEOUTILS_EXPLODE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Explode.hpp                     Transform node: Explode (header).
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

/// Class information for class Explode.
class ExplodeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ExplodeClassInfo();
		/// Destructor.
		virtual ~ExplodeClassInfo();
};

/** Transform node: Explode.
 * \ingroup geoutils
 *
 * Explode the contents of the input group into several output groups.
 */
class Explode
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
	private:
		
	protected:
		/// Number of elements per group.
		unsigned int elementsPerGroup;
		
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
		/// Default number of elements per group.
		static const unsigned int DEFAULT_ELEMENTS_PER_GROUP;
		/// Class information instance.
		static const ExplodeClassInfo explodeClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Explode object.
		 */
		Explode();
		
		/** Constructor.
		 *
		 * Construct new Explode object.
		 *
		 * \param other Other object.
		 */
		Explode(const Ionflux::GeoUtils::TransformNodes::Explode& other);
		
		/** Constructor.
		 *
		 * Construct new Explode object.
		 *
		 * \param initElementsPerGroup Number of elements per group.
		 * \param nodeID Node ID.
		 */
		Explode(unsigned int initElementsPerGroup, const 
		Ionflux::ObjectBase::IFObjectID& nodeID = "");
		
		/** Destructor.
		 *
		 * Destruct Explode object.
		 */
		virtual ~Explode();
		
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
		virtual Ionflux::GeoUtils::TransformNodes::Explode& operator=(const 
		Ionflux::GeoUtils::TransformNodes::Explode& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Explode* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::Explode* 
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
		static Ionflux::GeoUtils::TransformNodes::Explode* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get number of elements per group.
		 *
		 * \return Current value of number of elements per group.
		 */
		virtual unsigned int getElementsPerGroup() const;
		
		/** Set number of elements per group.
		 *
		 * Set new value of number of elements per group.
		 *
		 * \param newElementsPerGroup New value of number of elements per group.
		 */
		virtual void setElementsPerGroup(unsigned int newElementsPerGroup);
};

}

}

}

/** \file Explode.hpp
 * \brief Transform node: Explode (header).
 */
#endif
