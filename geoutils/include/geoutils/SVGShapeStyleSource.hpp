#ifndef IONFLUX_GEOUTILS_SVGSHAPESTYLESOURCE
#define IONFLUX_GEOUTILS_SVGSHAPESTYLESOURCE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SVGShapeStyleSource.hpp         SVG shape style source (header).
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
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class SVGShapeStyleSource.
class SVGShapeStyleSourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		SVGShapeStyleSourceClassInfo();
		/// Destructor.
		virtual ~SVGShapeStyleSourceClassInfo();
};

/** SVG shape style source.
 * \ingroup geoutils
 *
 * A source for SVG shape styles.
 */
class SVGShapeStyleSource
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Default style.
		Ionflux::GeoUtils::SVGShapeStyle defaultStyle;
		
	public:
		/// Class information instance.
		static const SVGShapeStyleSourceClassInfo sVGShapeStyleSourceClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new SVGShapeStyleSource object.
		 */
		SVGShapeStyleSource();
		
		/** Constructor.
		 *
		 * Construct new SVGShapeStyleSource object.
		 *
		 * \param other Other object.
		 */
		SVGShapeStyleSource(const Ionflux::GeoUtils::SVGShapeStyleSource& other);
		
		/** Destructor.
		 *
		 * Destruct SVGShapeStyleSource object.
		 */
		virtual ~SVGShapeStyleSource();
		
		/** Get style.
		 *
		 * Get a shape style for the SVG element identified by the specified 
		 * ID. This implementation returns the current default style for any 
		 * element ID.
		 *
		 * \param elementID Element ID.
		 *
		 * \return Shape style.
		 */
		virtual Ionflux::GeoUtils::SVGShapeStyle* getStyle(const std::string& 
		elementID);
		
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
		virtual Ionflux::GeoUtils::SVGShapeStyleSource& operator=(const 
		Ionflux::GeoUtils::SVGShapeStyleSource& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::SVGShapeStyleSource* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::SVGShapeStyleSource* 
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
		static Ionflux::GeoUtils::SVGShapeStyleSource* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get default style.
		 *
		 * \return Current value of default style.
		 */
		virtual Ionflux::GeoUtils::SVGShapeStyle getDefaultStyle() const;
		
		/** Set default style.
		 *
		 * Set new value of default style.
		 *
		 * \param newDefaultStyle New value of default style.
		 */
		virtual void setDefaultStyle(const Ionflux::GeoUtils::SVGShapeStyle& 
		newDefaultStyle);
};

}

}

/** \file SVGShapeStyleSource.hpp
 * \brief SVG shape style source (header).
 */
#endif
