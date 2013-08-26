#ifndef IONFLUX_GEOUTILS_IMAGE
#define IONFLUX_GEOUTILS_IMAGE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Image.hpp                       Image (header).
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

#include "altjira/Matrix.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Range3.hpp"
#include "geoutils/Vector3.hpp"
#include "geoutils/Polygon3Set.hpp"
#include "geoutils/SVG.hpp"
#include "altjira/Drawable.hpp"
#include "geoutils/TransformableObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Image.
class ImageClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ImageClassInfo();
		/// Destructor.
		virtual ~ImageClassInfo();
};

/** Image.
 * \ingroup geoutils
 *
 * A bitmap image with support for GeoUtils features.
 */
class Image
: public Ionflux::Altjira::Drawable, public 
Ionflux::GeoUtils::TransformableObject
{
	private:
		
	protected:
		
		/** Get image bounds.
		 *
		 * Get the bounds of the (untransformed) image.
		 *
		 * \return Bounds of the image.
		 */
		virtual Ionflux::GeoUtils::Range3 getImageBounds();
		
		/** Recalculate bounds.
		 *
		 * Recalculate the bounds for the image.
		 */
		virtual void recalculateBounds();
		
	public:
		/// tangent vectors for the 9 neighbouring pixel directions.
		static const Ionflux::GeoUtils::Vector3 TANGENT_VECTORS[3][3];
		/// Class information instance.
		static const ImageClassInfo imageClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Image object.
		 */
		Image();
		
		/** Constructor.
		 *
		 * Construct new Image object.
		 *
		 * \param other Other object.
		 */
		Image(const Ionflux::GeoUtils::Image& other);
		
		/** Constructor.
		 *
		 * Construct new Image object.
		 *
		 * \param fileName File name of an image to be loaded.
		 */
		Image(const std::string& fileName);
		
		/** Constructor.
		 *
		 * Construct new Image object.
		 *
		 * \param initImage Image.
		 */
		Image(const Ionflux::Altjira::Image& initImage);
		
		/** Constructor.
		 *
		 * Construct new Image object.
		 *
		 * \param initDrawable Drawable.
		 */
		Image(const Ionflux::Altjira::Drawable& initDrawable);
		
		/** Constructor.
		 *
		 * Construct new Image object.
		 *
		 * \param initWidth Width.
		 * \param initHeight Height.
		 * \param initAlpha Create alpha channel.
		 * \param initBitsPerSample Bits pers sample.
		 * \param initColorSpace Color space.
		 */
		Image(unsigned int initWidth, unsigned int initHeight, bool initAlpha = 
		true, unsigned int initBitsPerSample = 8, Ionflux::Altjira::ColorSpace 
		initColorSpace = Ionflux::Altjira::Color::SPACE_RGB);
		
		/** Destructor.
		 *
		 * Destruct Image object.
		 */
		virtual ~Image();
		
		/** Draw polygons.
		 *
		 * Draw polygons to the image. The origin is by default translated to 
		 * the center of the image.
		 *
		 * \param polygons Polygons.
		 * \param styles Element styles.
		 * \param axis Projection axis.
		 * \param closePath Close path.
		 * \param originX Coordinate origin (X).
		 * \param originY Coordinate origin (Y).
		 */
		virtual void drawPolygons(Ionflux::GeoUtils::Polygon3Set& polygons, const
		Ionflux::GeoUtils::SVGShapeStyleVector* styles = 0, 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y, bool 
		closePath = true, int originX = 0, int originY = 0);
		
		/** Draw SVG object.
		 *
		 * Draw an SVG object to the image. The origin is by default 
		 * translated to the center of the image.
		 *
		 * \param svg SVG object.
		 * \param originX Coordinate origin (X).
		 * \param originY Coordinate origin (Y).
		 */
		virtual void drawSVG(Ionflux::GeoUtils::SVG& svg, int originX = 0, int 
		originY = 0);
		
		/** Draw image.
		 *
		 * Draw a source image to the image. The origin is by default 
		 * translated to the center of the image. The source image will be 
		 * referenced.
		 *
		 * \param image Source image.
		 * \param originX Coordinate origin (X).
		 * \param originY Coordinate origin (Y).
		 */
		virtual void drawImage(Ionflux::GeoUtils::Image* image, int originX = 0, 
		int originY = 0);
		
		/** Create normal map from heightmap.
		 *
		 * Create a normal map from a heightmap (encoded by value).
		 *
		 * \param target target image.
		 * \param maxHeight maximum height.
		 */
		virtual void valueToNormal(Ionflux::Altjira::Image& target, double 
		maxHeight) const;
		
		/** Scale.
		 *
		 * Scale the object by the specified scale factors.
		 *
		 * \param s Vector of scale factors.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::TransformableObject& scale(const 
		Ionflux::GeoUtils::Vector3& s);
		
		/** Translate.
		 *
		 * Translate the object by the specified vector.
		 *
		 * \param t Translation vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::TransformableObject& translate(const 
		Ionflux::GeoUtils::Vector3& t);
		
		/** Rotate.
		 *
		 * Rotate the object by the specified angle around the specified axis.
		 *
		 * \param phi Angle.
		 * \param axis Axis.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::TransformableObject& rotate(double phi, 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
		
		/** Translate (drawing operation).
		 *
		 * Translate the coordinate origin.
		 *
		 * \param tx Translation (X).
		 * \param ty Translation (Y).
		 */
		virtual void drawTranslate(double tx, double ty);
		
		/** Scale (drawing operation).
		 *
		 * Scale the coordinate system.
		 *
		 * \param sx Scale factor (X).
		 * \param sy Scale factor (Y).
		 */
		virtual void drawScale(double sx, double sy);
		
		/** Rotate (drawing operation).
		 *
		 * Rotate the coordinate system.
		 *
		 * \param phi Rotation angle.
		 */
		virtual void drawRotate(double phi);
		
		/** Set drawing matrix.
		 *
		 * Set the transform matrix to be used for drawing.
		 *
		 * \param m Matrix.
		 */
		virtual void setDrawingMatrix(const Ionflux::GeoUtils::Matrix4& m);
		
		/** Get barycenter.
		 *
		 * Get the barycenter vector for the image.
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
		virtual Ionflux::GeoUtils::Image& duplicate();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Get value matrix.
		 *
		 * Get a matrix of pixel values.
		 *
		 * \param target target matrix.
		 */
		virtual void getValueMatrix(Ionflux::Altjira::Matrix& target);
		
		/** Set value matrix.
		 *
		 * Set pixel values according to values from the specified matrix.
		 *
		 * \param m matrix.
		 */
		virtual void setValueMatrix(const Ionflux::Altjira::Matrix& m);
		
		/** Get pixel AABB tree.
		 *
		 * Get an AABB tree containing references to the image pixels. The 
		 * pixel items will be stored as voxels of size 1 in in the target 
		 * bounding box.
		 *
		 * \param target target bounding box.
		 */
		virtual void getPixelTree(Ionflux::GeoUtils::BoundingBox* target);
		
		/** Mark pixels.
		 *
		 * Mark pixels that are in the specified box bounds item set (as 
		 * voxels).
		 *
		 * \param markPixels pixels to be marked.
		 * \param color Color.
		 * \param blender Color blender.
		 */
		virtual void markPixels(Ionflux::GeoUtils::BoxBoundsItemSet& markPixels, 
		const Ionflux::Altjira::Color& color = Ionflux::Altjira::Color::BLUE, 
		const Ionflux::Altjira::ColorBlender* blender = 0);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Image& operator=(const 
		Ionflux::GeoUtils::Image& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Image* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Image* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Image* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

}

}

/** \file Image.hpp
 * \brief Image (header).
 */
#endif
