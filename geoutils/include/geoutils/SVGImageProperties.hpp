#ifndef IONFLUX_GEOUTILS_SVGIMAGEPROPERTIES
#define IONFLUX_GEOUTILS_SVGIMAGEPROPERTIES
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SVGImageProperties.hpp          SVG image properties (header).
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
#include "geoutils/SVGShapeStyleSource.hpp"
#include "geoutils/ImageProperties.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class SVGImageProperties.
class SVGImagePropertiesClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		SVGImagePropertiesClassInfo();
		/// Destructor.
		virtual ~SVGImagePropertiesClassInfo();
};

/** SVG image properties.
 * \ingroup geoutils
 *
 * Properties for an SVG image.
 */
class SVGImageProperties
: public Ionflux::GeoUtils::ImageProperties
{
	private:
		
	protected:
		/// Shape style source.
		Ionflux::GeoUtils::SVGShapeStyleSource* styleSource;
		/// SVG template.
		std::string svgTemplate;
		
	public:
		/// Class information instance.
		static const SVGImagePropertiesClassInfo sVGImagePropertiesClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new SVGImageProperties object.
		 */
		SVGImageProperties();
		
		/** Constructor.
		 *
		 * Construct new SVGImageProperties object.
		 *
		 * \param other Other object.
		 */
		SVGImageProperties(const Ionflux::GeoUtils::SVGImageProperties& other);
		
		/** Constructor.
		 *
		 * Construct new SVGImageProperties object.
		 *
		 * \param initStyleSource Style source.
		 * \param initSVGTemplate SVG template.
		 */
		SVGImageProperties(Ionflux::GeoUtils::SVGShapeStyleSource* 
		initStyleSource, const std::string& initSVGTemplate = 
		Ionflux::GeoUtils::SVG_TEMPLATE);
		
		/** Destructor.
		 *
		 * Destruct SVGImageProperties object.
		 */
		virtual ~SVGImageProperties();
		
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
		virtual Ionflux::GeoUtils::SVGImageProperties& operator=(const 
		Ionflux::GeoUtils::SVGImageProperties& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::SVGImageProperties* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::SVGImageProperties* 
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
		static Ionflux::GeoUtils::SVGImageProperties* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get shape style source.
		 *
		 * \return Current value of shape style source.
		 */
		virtual Ionflux::GeoUtils::SVGShapeStyleSource* getStyleSource() const;
		
		/** Set shape style source.
		 *
		 * Set new value of shape style source.
		 *
		 * \param newStyleSource New value of shape style source.
		 */
		virtual void setStyleSource(Ionflux::GeoUtils::SVGShapeStyleSource* 
		newStyleSource);
		
		/** Get sVG template.
		 *
		 * \return Current value of sVG template.
		 */
		virtual std::string getSvgTemplate() const;
		
		/** Set sVG template.
		 *
		 * Set new value of sVG template.
		 *
		 * \param newSvgTemplate New value of sVG template.
		 */
		virtual void setSvgTemplate(const std::string& newSvgTemplate);
};

}

}

/** \file SVGImageProperties.hpp
 * \brief SVG image properties (header).
 */
#endif
