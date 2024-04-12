#ifndef IONFLUX_GEOUTILS_ITERATE
#define IONFLUX_GEOUTILS_ITERATE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Iterate.hpp                     Transform node: Iterate (header).
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

/// Class information for class Iterate.
class IterateClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		IterateClassInfo();
		/// Destructor.
		virtual ~IterateClassInfo();
};

/** Transform node: Iterate.
 * \ingroup geoutils
 *
 * Query the input group a number of times and add one output group per 
 * query.
 */
class Iterate
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
	private:
		
	protected:
		/// Number of iterations.
		unsigned int numIterations;
		
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
		/// Default number of iterations.
		static const unsigned int DEFAULT_NUM_ITERATIONS;
		/// Class information instance.
		static const IterateClassInfo iterateClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Iterate object.
		 */
		Iterate();
		
		/** Constructor.
		 *
		 * Construct new Iterate object.
		 *
		 * \param other Other object.
		 */
		Iterate(const Ionflux::GeoUtils::TransformNodes::Iterate& other);
		
		/** Constructor.
		 *
		 * Construct new Iterate object.
		 *
		 * \param initNumIterations Number of iterations.
		 * \param nodeID Node ID.
		 */
		Iterate(unsigned int initNumIterations, const 
		Ionflux::ObjectBase::IFObjectID& nodeID = "");
		
		/** Destructor.
		 *
		 * Destruct Iterate object.
		 */
		virtual ~Iterate();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Update inputs.
		 *
		 * Update the inputs of the node. Each input node is updated only 
		 * once, no matter how many of its outputs are connected to this node.
		 */
		virtual void updateInputs();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Iterate& operator=(const 
		Ionflux::GeoUtils::TransformNodes::Iterate& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Iterate* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::Iterate* 
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
		static Ionflux::GeoUtils::TransformNodes::Iterate* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get number of iterations.
		 *
		 * \return Current value of number of iterations.
		 */
		virtual unsigned int getNumIterations() const;
		
		/** Set number of iterations.
		 *
		 * Set new value of number of iterations.
		 *
		 * \param newNumIterations New value of number of iterations.
		 */
		virtual void setNumIterations(unsigned int newNumIterations);
};

}

}

}

/** \file Iterate.hpp
 * \brief Transform node: Iterate (header).
 */
#endif
