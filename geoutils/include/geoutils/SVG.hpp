#ifndef IONFLUX_GEOUTILS_SVG
#define IONFLUX_GEOUTILS_SVG
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SVG.hpp                         SVG (header).
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
#include "geoutils/Range3.hpp"
#include "geoutils/Vector3.hpp"
#include "geoutils/TransformableObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class SVG.
class SVGClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		SVGClassInfo();
		/// Destructor.
		virtual ~SVGClassInfo();
};

/** Scalable Vector Graphic.
 * \ingroup geoutils
 *
 * A Scalable Vector Graphic that can be rendered using Image or transform 
 * nodes.
 */
class SVG
: public Ionflux::GeoUtils::TransformableObject
{
	private:
		
	protected:
		/// SVG data source.
		std::string source;
		/// Type of the data source.
		Ionflux::GeoUtils::SVGType type;
		
		/** Get SVG bounds.
		 *
		 * Get the bounds of the (untransformed) SVG data.
		 *
		 * \return Bounds of the SVG data.
		 */
		virtual Ionflux::GeoUtils::Range3 getSVGBounds();
		
		/** Recalculate bounds.
		 *
		 * Recalculate the bounds for the SVG object.
		 */
		virtual void recalculateBounds();
		
	public:
		/// SVG type: undefined.
		static const Ionflux::GeoUtils::SVGType TYPE_UNDEFINED;
		/// SVG type: file.
		static const Ionflux::GeoUtils::SVGType TYPE_FILE;
		/// SVG type: data.
		static const Ionflux::GeoUtils::SVGType TYPE_DATA;
		/// Class information instance.
		static const SVGClassInfo sVGClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new SVG object.
		 */
		SVG();
		
		/** Constructor.
		 *
		 * Construct new SVG object.
		 *
		 * \param other Other object.
		 */
		SVG(const Ionflux::GeoUtils::SVG& other);
		
		/** Constructor.
		 *
		 * Construct new SVG object.
		 *
		 * \param initSource Data source (file name or SVG data).
		 * \param initType Data type.
		 */
		SVG(const std::string& initSource, Ionflux::GeoUtils::SVGType initType);
		
		/** Destructor.
		 *
		 * Destruct SVG object.
		 */
		virtual ~SVG();
		
		/** Get barycenter.
		 *
		 * Get the barycenter vector for the SVG object.
		 *
		 * \return Barycenter vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getBarycenter();
		
		/** Duplicate.
		 *
		 * Create an exact duplicate of the object. The duplicate is a new 
		 * object which must be managed by the caller.
		 *
		 * \return The duplicated object.
		 */
		virtual Ionflux::GeoUtils::SVG& duplicate();
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::SVG& operator=(const Ionflux::GeoUtils::SVG& 
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::SVG* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::SVG* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		
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
		static Ionflux::GeoUtils::SVG* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get sVG data source.
		 *
		 * \return Current value of sVG data source.
		 */
		virtual std::string getSource() const;
		
		/** Set sVG data source.
		 *
		 * Set new value of sVG data source.
		 *
		 * \param newSource New value of sVG data source.
		 */
		virtual void setSource(const std::string& newSource);
		
		/** Get type of the data source.
		 *
		 * \return Current value of type of the data source.
		 */
		virtual Ionflux::GeoUtils::SVGType getType() const;
		
		/** Set type of the data source.
		 *
		 * Set new value of type of the data source.
		 *
		 * \param newType New value of type of the data source.
		 */
		virtual void setType(Ionflux::GeoUtils::SVGType newType);
};

}

}

/** \file SVG.hpp
 * \brief SVG (header).
 */
#endif
