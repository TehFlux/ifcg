#ifndef IONFLUX_GEOUTILS_CLONE
#define IONFLUX_GEOUTILS_CLONE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Clone.hpp                       Transform node: Clone (header).
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

/// Class information for class Clone.
class CloneClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		CloneClassInfo();
		/// Destructor.
		virtual ~CloneClassInfo();
};

/** Transform node: Clone.
 * \ingroup geoutils
 *
 * Create a number of duplicates of the input group, which are added as 
 * output groups.
 */
class Clone
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
	private:
		
	protected:
		/// Number of clones.
		unsigned int numClones;
		
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
		/// Default number of clones.
		static const unsigned int DEFAULT_NUM_CLONES;
		/// Class information instance.
		static const CloneClassInfo cloneClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Clone object.
		 */
		Clone();
		
		/** Constructor.
		 *
		 * Construct new Clone object.
		 *
		 * \param other Other object.
		 */
		Clone(const Ionflux::GeoUtils::TransformNodes::Clone& other);
		
		/** Constructor.
		 *
		 * Construct new Clone object.
		 *
		 * \param initNumClones Number of clones.
		 * \param nodeID Node ID.
		 */
		Clone(unsigned int initNumClones, const Ionflux::ObjectBase::IFObjectID& 
		nodeID = "");
		
		/** Destructor.
		 *
		 * Destruct Clone object.
		 */
		virtual ~Clone();
		
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
		virtual Ionflux::GeoUtils::TransformNodes::Clone& operator=(const 
		Ionflux::GeoUtils::TransformNodes::Clone& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Clone* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::Clone* 
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
		static Ionflux::GeoUtils::TransformNodes::Clone* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get number of clones.
		 *
		 * \return Current value of number of clones.
		 */
		virtual unsigned int getNumClones() const;
		
		/** Set number of clones.
		 *
		 * Set new value of number of clones.
		 *
		 * \param newNumClones New value of number of clones.
		 */
		virtual void setNumClones(unsigned int newNumClones);
};

}

}

}

/** \file Clone.hpp
 * \brief Transform node: Clone (header).
 */
#endif
