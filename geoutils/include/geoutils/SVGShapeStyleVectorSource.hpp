#ifndef IONFLUX_GEOUTILS_SVGSHAPESTYLEVECTORSOURCE
#define IONFLUX_GEOUTILS_SVGSHAPESTYLEVECTORSOURCE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SVGShapeStyleVectorSource.hpp   SVG shape style vector source (header).
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

/// Class information for class SVGShapeStyleVectorSource.
class SVGShapeStyleVectorSourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		SVGShapeStyleVectorSourceClassInfo();
		/// Destructor.
		virtual ~SVGShapeStyleVectorSourceClassInfo();
};

/** SVG shape style vector source.
 * \ingroup geoutils
 *
 * A source for SVG shape styles that provides shape styles from a vector.
 */
class SVGShapeStyleVectorSource
: public Ionflux::GeoUtils::SVGShapeStyleSource
{
	private:
		
	protected:
		/// Current style index.
		unsigned int currentStyle;
		/// Shape style vector.
		std::vector<Ionflux::GeoUtils::SVGShapeStyle*> styles;
		
	public:
		/// Class information instance.
		static const SVGShapeStyleVectorSourceClassInfo sVGShapeStyleVectorSourceClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new SVGShapeStyleVectorSource object.
		 */
		SVGShapeStyleVectorSource();
		
		/** Constructor.
		 *
		 * Construct new SVGShapeStyleVectorSource object.
		 *
		 * \param other Other object.
		 */
		SVGShapeStyleVectorSource(const Ionflux::GeoUtils::SVGShapeStyleVectorSource& other);
		
		/** Destructor.
		 *
		 * Destruct SVGShapeStyleVectorSource object.
		 */
		virtual ~SVGShapeStyleVectorSource();
		
		/** Get style.
		 *
		 * Get a shape style for the SVG element identified by the specified 
		 * ID. This returns the current style as indicated by the current 
		 * style index and then increments the current style index. Style 
		 * selection restarts at the beginning if there are not enough styles 
		 * in the vector.
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
		virtual Ionflux::GeoUtils::SVGShapeStyleVectorSource& operator=(const 
		Ionflux::GeoUtils::SVGShapeStyleVectorSource& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::SVGShapeStyleVectorSource* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::SVGShapeStyleVectorSource* 
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
		static Ionflux::GeoUtils::SVGShapeStyleVectorSource* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get current style index.
		 *
		 * \return Current value of current style index.
		 */
		virtual unsigned int getCurrentStyle() const;
		
		/** Set current style index.
		 *
		 * Set new value of current style index.
		 *
		 * \param newCurrentStyle New value of current style index.
		 */
		virtual void setCurrentStyle(unsigned int newCurrentStyle);
		
		/** Get number of styles.
		 *
		 * \return Number of styles.
		 */
		virtual unsigned int getNumStyles() const;
		
		/** Get style.
		 *
		 * Get the style at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Style at specified index.
		 */
		virtual Ionflux::GeoUtils::SVGShapeStyle* getStyle(unsigned int 
		elementIndex = 0) const;
		
		/** Find style.
		 *
		 * Find the specified occurence of a style.
		 *
		 * \param needle Style to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the style, or -1 if the style cannot be found.
		 */
		virtual int findStyle(Ionflux::GeoUtils::SVGShapeStyle* needle, unsigned 
		int occurence = 1) const;
        
		/** Get shape style vector.
		 *
		 * \return shape style vector.
		 */
		virtual std::vector<Ionflux::GeoUtils::SVGShapeStyle*>& getStyles();
		
		/** Add style.
		 *
		 * Add a style.
		 *
		 * \param addElement Style to be added.
		 */
		virtual void addStyle(Ionflux::GeoUtils::SVGShapeStyle* addElement);
		
		/** Remove style.
		 *
		 * Remove a style.
		 *
		 * \param removeElement Style to be removed.
		 */
		virtual void removeStyle(Ionflux::GeoUtils::SVGShapeStyle* 
		removeElement);
		
		/** Remove style.
		 *
		 * Remove a style.
		 *
		 * \param removeIndex Style to be removed.
		 */
		virtual void removeStyleIndex(unsigned int removeIndex);
		
		/** Clear styles.
		 *
		 * Clear all styles.
		 */
		virtual void clearStyles();
};

}

}

/** \file SVGShapeStyleVectorSource.hpp
 * \brief SVG shape style vector source (header).
 */
#endif
