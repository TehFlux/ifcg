#ifndef IONFLUX_GEOUTILS_SVGSHAPESTYLEMAP
#define IONFLUX_GEOUTILS_SVGSHAPESTYLEMAP
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SVGShapeStyleMap.hpp            SVG shape style map (header).
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
#include "geoutils/SVGShapeStyleSource.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class SVGShapeStyleMap.
class SVGShapeStyleMapClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		SVGShapeStyleMapClassInfo();
		/// Destructor.
		virtual ~SVGShapeStyleMapClassInfo();
};

/** SVG shape style map.
 * \ingroup geoutils
 *
 * A source for SVG shape styles that maps element IDs to shape styles 
 * using a user defined mapping.
 */
class SVGShapeStyleMap
: public Ionflux::GeoUtils::SVGShapeStyleSource
{
	private:
		
	protected:
		/// Shape style map.
		std::map<std::string, Ionflux::GeoUtils::SVGShapeStyle*> styleMap;
		
	public:
		/// Class information instance.
		static const SVGShapeStyleMapClassInfo sVGShapeStyleMapClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new SVGShapeStyleMap object.
		 */
		SVGShapeStyleMap();
		
		/** Constructor.
		 *
		 * Construct new SVGShapeStyleMap object.
		 *
		 * \param other Other object.
		 */
		SVGShapeStyleMap(const Ionflux::GeoUtils::SVGShapeStyleMap& other);
		
		/** Destructor.
		 *
		 * Destruct SVGShapeStyleMap object.
		 */
		virtual ~SVGShapeStyleMap();
		
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
		virtual Ionflux::GeoUtils::SVGShapeStyleMap& operator=(const 
		Ionflux::GeoUtils::SVGShapeStyleMap& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::SVGShapeStyleMap* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::SVGShapeStyleMap* 
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
		static Ionflux::GeoUtils::SVGShapeStyleMap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get number of styles.
		 *
		 * \return Number of styles.
		 */
		virtual unsigned int getNumStyles() const;
		
		/** Get style.
		 *
		 * Get the style with the specified key.
		 *
		 * \param elementKey Element key.
		 *
		 * \return Style with specified key.
		 */
		virtual Ionflux::GeoUtils::SVGShapeStyle* getStyle(const std::string& 
		elementKey) const;
        
		/** Get shape style map.
		 *
		 * \return shape style map.
		 */
		virtual std::map<std::string, Ionflux::GeoUtils::SVGShapeStyle*>& 
		getStyles();
		
		/** Add style.
		 *
		 * Add a style.
		 *
		 * \param elementKey Element key.
		 * \param addElement Style to be added.
		 */
		virtual void addStyle(const std::string& elementKey, 
		Ionflux::GeoUtils::SVGShapeStyle* addElement);
		
		/** Remove style.
		 *
		 * Remove the style with the specified key.
		 *
		 * \param elementKey Element key.
		 */
		virtual void removeStyle(const std::string& elementKey);
		
		/** Clear styles.
		 *
		 * Clear all styles.
		 */
		virtual void clearStyles();
};

}

}

/** \file SVGShapeStyleMap.hpp
 * \brief SVG shape style map (header).
 */
#endif
