#ifndef IONFLUX_ALTJIRA_DRAWABLE
#define IONFLUX_ALTJIRA_DRAWABLE
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Drawable.hpp                    Drawable (header).
 * =========================================================================
 * 
 * This file is part of Altjira - Ionflux' Image Processing Library.
 * 
 * Altjira - Ionflux' Image Processing Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * Altjira - Ionflux' Image Processing Library is distributed in the hope 
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Altjira - Ionflux' Image Processing Library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include <cairo.h>
#include <cmath>
#include "altjira/ColorBlender.hpp"
#include "altjira/Image.hpp"

namespace Ionflux
{

namespace Altjira
{

class Pattern;

/// Class information for class Drawable.
class DrawableClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		DrawableClassInfo();
		/// Destructor.
		virtual ~DrawableClassInfo();
};

/** Drawable.
 * \ingroup geoutils
 *
 * An image with support for drawing operations.
 */
class Drawable
: public Ionflux::Altjira::Image
{
	private:
		
	protected:
		/// Cairo context.
		cairo_t* context;
		/// Cairo surface.
		cairo_surface_t* surface;
		/// Drawing in progress flag.
		bool inProgress;
		
		/** Transform pattern.
		 *
		 * Transform the pattern coordinate system using the specified matrix.
		 * 
		 * \note This is an ugly hack to make pattern transformations 
		 * available to classes derived from drawable. This should be solved 
		 * instead by adding a public transform function to Pattern.
		 *
		 * \param pattern Pattern.
		 * \param m Matrix.
		 */
		virtual void transformPattern(Ionflux::Altjira::Pattern& pattern, 
		cairo_matrix_t& m);
		
	public:
		/// Class information instance.
		static const DrawableClassInfo drawableClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Drawable object.
		 */
		Drawable();
		
		/** Constructor.
		 *
		 * Construct new Drawable object.
		 *
		 * \param other Other object.
		 */
		Drawable(const Ionflux::Altjira::Drawable& other);
		
		/** Constructor.
		 *
		 * Construct new Drawable object.
		 *
		 * \param fileName File name of an image to be loaded.
		 */
		Drawable(const std::string& fileName);
		
		/** Constructor.
		 *
		 * Construct new Drawable object.
		 *
		 * \param initImage Image.
		 */
		Drawable(const Ionflux::Altjira::Image& initImage);
		
		/** Constructor.
		 *
		 * Construct new Drawable object.
		 *
		 * \param initWidth Width.
		 * \param initHeight Height.
		 * \param initAlpha Create alpha channel.
		 * \param initBitsPerSample Bits pers sample.
		 * \param initColorSpace Color space.
		 */
		Drawable(unsigned int initWidth, unsigned int initHeight, bool initAlpha 
		= true, unsigned int initBitsPerSample = 8, Ionflux::Altjira::ColorSpace 
		initColorSpace = Ionflux::Altjira::Color::SPACE_RGB);
		
		/** Destructor.
		 *
		 * Destruct Drawable object.
		 */
		virtual ~Drawable();
		
		/** Begin drawing.
		 *
		 * Begin a sequence of drawing options.
		 *
		 * \param originX Coordinate origin (X).
		 * \param originY Coordinate origin (Y).
		 */
		virtual void begin(double originX = 0., double originY = 0.);
		
		/** Discard drawing.
		 *
		 * Discard the current drawing without compositing it onto the image.
		 */
		virtual void discard();
		
		/** Finish drawing.
		 *
		 * Finish a sequence of drawing options. The drawing will be 
		 * composited onto the image using the specified color blender. If no 
		 * color blender is specified, the default SrcOver blender will be 
		 * used.
		 *
		 * \param blender Color blender.
		 */
		virtual void finish(const Ionflux::Altjira::ColorBlender* blender = 0);
		
		/** Save drawing state.
		 *
		 * Save the drawing state.
		 */
		virtual void save();
		
		/** Restore drawing state.
		 *
		 * Restore the drawing state that was previously saved using a save() 
		 * operation.
		 */
		virtual void restore();
		
		/** Translate.
		 *
		 * Translate the coordinate origin.
		 *
		 * \param tx Translation (X).
		 * \param ty Translation (Y).
		 */
		virtual void translate(double tx, double ty);
		
		/** Scale.
		 *
		 * Scale the coordinate system.
		 *
		 * \param sx Scale factor (X).
		 * \param sy Scale factor (Y).
		 */
		virtual void scale(double sx, double sy);
		
		/** Rotate.
		 *
		 * Rotate the coordinate system.
		 *
		 * \param phi Rotation angle.
		 */
		virtual void rotate(double phi);
		
		/** Start new path.
		 *
		 * Start a new path.
		 */
		virtual void newPath();
		
		/** Start new sub-path.
		 *
		 * Start a new sub-path.
		 */
		virtual void newSubPath();
		
		/** Close path.
		 *
		 * Close the current path.
		 */
		virtual void closePath();
		
		/** Move to.
		 *
		 * Change the current drawing position.
		 *
		 * \param x X coordinate.
		 * \param y Y coordinate.
		 */
		virtual void moveTo(double x, double y);
		
		/** Line to.
		 *
		 * Draw a line segment.
		 *
		 * \param x X coordinate.
		 * \param y Y coordinate.
		 */
		virtual void lineTo(double x, double y);
		
		/** Curve to.
		 *
		 * Draw a cubic Bézier spline segment.
		 *
		 * \param x0 X coordinate (first control point).
		 * \param y0 Y coordinate (first control point).
		 * \param x1 X coordinate (second control point).
		 * \param y1 Y coordinate (second control point).
		 * \param x2 X coordinate (third control point).
		 * \param y2 Y coordinate (third control point).
		 */
		virtual void curveTo(double x0, double y0, double x1, double y1, double 
		x2, double y2);
		
		/** Rectangle.
		 *
		 * Add a rectangle to the current path.
		 *
		 * \param x X coordinate of upper left corner.
		 * \param y Y coordinate of upper left corner.
		 * \param width Width.
		 * \param height height.
		 */
		virtual void rectangle(double x, double y, double width, double height);
		
		/** Arc.
		 *
		 * Add an arc to the current path.
		 *
		 * \param x X coordinate of center.
		 * \param y Y coordinate of center.
		 * \param radius Radius.
		 * \param phi0 From angle.
		 * \param phi1 To angle.
		 */
		virtual void arc(double x, double y, double radius, double phi0 = 0., 
		double phi1 = 2. * M_PI);
		
		/** Set source color.
		 *
		 * Set a source color for drawing.
		 *
		 * \param color Color.
		 */
		virtual void setSourceColor(const Ionflux::Altjira::Color& color);
		
		/** Set source pattern.
		 *
		 * Set a source pattern for drawing.
		 *
		 * \param pattern Pattern.
		 */
		virtual void setSource(Ionflux::Altjira::Pattern& pattern);
		
		/** Set source image.
		 *
		 * Set a source image for drawing. The image will be placed at the 
		 * position specified by the offset parameters. The source image will 
		 * be referenced.
		 *
		 * \param image Image.
		 * \param x Offset (X).
		 * \param y Offset (Y).
		 */
		virtual void setSourceImage(Ionflux::Altjira::Image* image, double x = 
		0., double y = 0.);
		
		/** Set fill rule.
		 *
		 * Set the fill rule for drawing.
		 *
		 * \param fillRule Fill rule.
		 */
		virtual void setFillRule(Ionflux::Altjira::FillRule fillRule);
		
		/** Stroke path.
		 *
		 * Stroke the current path.
		 *
		 * \param lineWidth Line width.
		 * \param preserve Preserve path.
		 */
		virtual void stroke(double lineWidth = 1., bool preserve = false);
		
		/** Fill path.
		 *
		 * Fill the current path.
		 *
		 * \param preserve Preserve path.
		 */
		virtual void fillPath(bool preserve = false);
		
		/** Paint.
		 *
		 * Paint the current path.
		 */
		virtual void paint();
		
		/** Get text size.
		 *
		 * Get the size of the specified text as it would be rendered to the 
		 * Drawable.
		 *
		 * \param text Text.
		 * \param fontDesc Font description.
		 * \param fontSize Font size.
		 *
		 * \return A rectangle corresponding to the size of the text.
		 */
		virtual Ionflux::Altjira::ImageRect getTextSize(const std::string& text, 
		const std::string& fontDesc = DEFAULT_FONT_DESCRIPTION, double fontSize =
		DEFAULT_FONT_SIZE) const;
		
		/** Draw text.
		 *
		 * Draw text on the drawable.
		 *
		 * \param x X coordinate.
		 * \param y Y coordinate.
		 * \param text Text.
		 * \param fontDesc Font description.
		 * \param fontSize Font size.
		 * \param color Text color.
		 */
		virtual void drawText(double x, double y, const std::string& text, const 
		std::string& fontDesc = DEFAULT_FONT_DESCRIPTION, double fontSize = 
		DEFAULT_FONT_SIZE, const Ionflux::Altjira::Color& color = 
		Ionflux::Altjira::Color::BLACK);
		
		/** Draw SVG data.
		 *
		 * Draw SVG data to the image. The origin is by default translated to 
		 * the center of the image.
		 *
		 * \param svgData SVG data.
		 * \param originX Coordinate origin (X).
		 * \param originY Coordinate origin (Y).
		 */
		virtual void drawSVG(const std::string& svgData, int originX = 0, int 
		originY = 0);
		
		/** Draw SVG file.
		 *
		 * Draw an SVG file to the image. The origin is by default translated 
		 * to the center of the image.
		 *
		 * \param svgFileName SVG file name.
		 * \param originX Coordinate origin (X).
		 * \param originY Coordinate origin (Y).
		 */
		virtual void drawSVGFile(const std::string& svgFileName, int originX = 0,
		int originY = 0);
		
		/** Drawing in progress check.
		 *
		 * Check whether a drawing operation is in progress.
		 *
		 * \return \c true if a drawing operation is in progress, \c false 
		 * otherwise.
		 */
		virtual bool drawingInProgress() const;
		
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
		virtual Ionflux::Altjira::Drawable& operator=(const 
		Ionflux::Altjira::Drawable& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Altjira::Drawable* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Altjira::Drawable* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::Altjira::Drawable* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

}

}

/** \file Drawable.hpp
 * \brief Drawable (header).
 */
#endif
