#ifndef IONFLUX_GEOUTILS_WRITESVG
#define IONFLUX_GEOUTILS_WRITESVG
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * WriteSVG.hpp                    Transform node: Write SVG (header).
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

/// Class information for class WriteSVG.
class WriteSVGClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		WriteSVGClassInfo();
		/// Destructor.
		virtual ~WriteSVGClassInfo();
};

/** Transform node: Write SVG.
 * \ingroup geoutils
 *
 * Write polygons from the input groups to an SVG file. The node takes an 
 * arbitrary number of inputs and provides a flattened duplicate of the 
 * inputs as its output group.
 */
class WriteSVG
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
	private:
		
	protected:
		/// Output file name.
		std::string fileName;
		/// Shape styles.
		std::vector<Ionflux::GeoUtils::SVGShapeStyle*> styles;
		/// Element ID prefix.
		std::string elementIDPrefix;
		/// Projection axis.
		Ionflux::GeoUtils::AxisID axis;
		/// Shape type.
		Ionflux::GeoUtils::SVGShapeType shapeType;
		/// Close path.
		bool closePath;
		/// Image width.
		unsigned int width;
		/// Image height.
		unsigned int height;
		/// Origin coordinate (X).
		unsigned int originX;
		/// Origin coordinate (Y).
		unsigned int originY;
		/// SVG template.
		std::string svgTemplate;
		
		/** Process inputs.
		 *
		 * Update the outputs of the node by processing the inputs. This 
		 * should be implemented by derived classes.
		 */
		virtual void process();
		
	public:
		/// Input ID: first.
		static const unsigned int INPUT_FIRST;
		/// Output ID: composite.
		static const unsigned int OUTPUT_COMPOSITE;
		/// Class information instance.
		static const WriteSVGClassInfo writeSVGClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new WriteSVG object.
		 */
		WriteSVG();
		
		/** Constructor.
		 *
		 * Construct new WriteSVG object.
		 *
		 * \param other Other object.
		 */
		WriteSVG(const Ionflux::GeoUtils::TransformNodes::WriteSVG& other);
		
		/** Constructor.
		 *
		 * Construct new WriteSVG object.
		 *
		 * \param initFileName Output file name.
		 * \param initElementIDPrefix Element ID prefix.
		 * \param initAxis Axis.
		 * \param initShapeType Shape type.
		 * \param initClosePath Close path.
		 * \param initStyles Styles.
		 * \param initWidth Image width.
		 * \param initHeight Image height.
		 * \param initOriginX Origin coordinate (X).
		 * \param initOriginY Origin coordinate (Y).
		 * \param initSVGTemplate SVG template.
		 * \param nodeID Node ID.
		 */
		WriteSVG(const std::string& initFileName, const std::string& 
		initElementIDPrefix = "polygon", Ionflux::GeoUtils::AxisID initAxis = 
		Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::SVGShapeType initShapeType 
		= Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool initClosePath = true, const
		Ionflux::GeoUtils::SVGShapeStyleVector* initStyles = 0, unsigned int 
		initWidth = 1000, unsigned int initHeight = 1000, unsigned int 
		initOriginX = 500, unsigned int initOriginY = 500, const std::string& 
		initSVGTemplate = Ionflux::GeoUtils::SVG_TEMPLATE, const 
		Ionflux::ObjectBase::IFObjectID& nodeID = "");
		
		/** Destructor.
		 *
		 * Destruct WriteSVG object.
		 */
		virtual ~WriteSVG();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Add styles.
		 *
		 * Add styles for rendering.
		 *
		 * \param newStyles Styles.
		 */
		virtual void addStyles(const Ionflux::GeoUtils::SVGShapeStyleVector& 
		newStyles);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::WriteSVG& operator=(const 
		Ionflux::GeoUtils::TransformNodes::WriteSVG& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::WriteSVG* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::WriteSVG* 
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
		static Ionflux::GeoUtils::TransformNodes::WriteSVG* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get output file name.
		 *
		 * \return Current value of output file name.
		 */
		virtual std::string getFileName() const;
		
		/** Set output file name.
		 *
		 * Set new value of output file name.
		 *
		 * \param newFileName New value of output file name.
		 */
		virtual void setFileName(const std::string& newFileName);
		
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
        
		/** Get shape styles.
		 *
		 * \return shape styles.
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
		
		/** Get element ID prefix.
		 *
		 * \return Current value of element ID prefix.
		 */
		virtual std::string getElementIDPrefix() const;
		
		/** Set element ID prefix.
		 *
		 * Set new value of element ID prefix.
		 *
		 * \param newElementIDPrefix New value of element ID prefix.
		 */
		virtual void setElementIDPrefix(const std::string& newElementIDPrefix);
		
		/** Get projection axis.
		 *
		 * \return Current value of projection axis.
		 */
		virtual Ionflux::GeoUtils::AxisID getAxis() const;
		
		/** Set projection axis.
		 *
		 * Set new value of projection axis.
		 *
		 * \param newAxis New value of projection axis.
		 */
		virtual void setAxis(Ionflux::GeoUtils::AxisID newAxis);
		
		/** Get shape type.
		 *
		 * \return Current value of shape type.
		 */
		virtual Ionflux::GeoUtils::SVGShapeType getShapeType() const;
		
		/** Set shape type.
		 *
		 * Set new value of shape type.
		 *
		 * \param newShapeType New value of shape type.
		 */
		virtual void setShapeType(Ionflux::GeoUtils::SVGShapeType newShapeType);
		
		/** Get close path.
		 *
		 * \return Current value of close path.
		 */
		virtual bool getClosePath() const;
		
		/** Set close path.
		 *
		 * Set new value of close path.
		 *
		 * \param newClosePath New value of close path.
		 */
		virtual void setClosePath(bool newClosePath);
		
		/** Get image width.
		 *
		 * \return Current value of image width.
		 */
		virtual unsigned int getWidth() const;
		
		/** Set image width.
		 *
		 * Set new value of image width.
		 *
		 * \param newWidth New value of image width.
		 */
		virtual void setWidth(unsigned int newWidth);
		
		/** Get image height.
		 *
		 * \return Current value of image height.
		 */
		virtual unsigned int getHeight() const;
		
		/** Set image height.
		 *
		 * Set new value of image height.
		 *
		 * \param newHeight New value of image height.
		 */
		virtual void setHeight(unsigned int newHeight);
		
		/** Get origin coordinate (X).
		 *
		 * \return Current value of origin coordinate (X).
		 */
		virtual unsigned int getOriginX() const;
		
		/** Set origin coordinate (X).
		 *
		 * Set new value of origin coordinate (X).
		 *
		 * \param newOriginX New value of origin coordinate (X).
		 */
		virtual void setOriginX(unsigned int newOriginX);
		
		/** Get origin coordinate (Y).
		 *
		 * \return Current value of origin coordinate (Y).
		 */
		virtual unsigned int getOriginY() const;
		
		/** Set origin coordinate (Y).
		 *
		 * Set new value of origin coordinate (Y).
		 *
		 * \param newOriginY New value of origin coordinate (Y).
		 */
		virtual void setOriginY(unsigned int newOriginY);
		
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

}

/** \file WriteSVG.hpp
 * \brief Transform node: Write SVG (header).
 */
#endif
