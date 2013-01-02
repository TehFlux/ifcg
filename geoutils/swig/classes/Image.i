/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Image.i                         Image (interface).
 * =========================================================================

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
%{
#include "geoutils/Image.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class ImageClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ImageClassInfo();
        virtual ~ImageClassInfo();
};

class Image
: public Ionflux::Altjira::Drawable, public 
Ionflux::GeoUtils::TransformableObject
{
    public:
		static const Ionflux::GeoUtils::Vector3 TANGENT_VECTORS[3][3];
        
        Image();
		Image(const Ionflux::GeoUtils::Image& other);
        Image(const std::string& fileName);
        Image(const Ionflux::Altjira::Image& initImage);
        Image(const Ionflux::Altjira::Drawable& initDrawable);
        Image(unsigned int initWidth, unsigned int initHeight, bool 
        initAlpha = true, unsigned int initBitsPerSample = 8, 
        Ionflux::Altjira::ColorSpace initColorSpace = 
        Ionflux::Altjira::Color::SPACE_RGB);
        virtual ~Image();
        virtual void drawPolygons(Ionflux::GeoUtils::Polygon3Set& polygons,
        const Ionflux::GeoUtils::SVGShapeStyleVector* styles = 0, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y, bool 
        closePath = true, int originX = 0, int originY = 0);
        virtual void drawSVG(Ionflux::GeoUtils::SVG& svg, int originX = 0, 
        int originY = 0);
        virtual void drawImage(Ionflux::GeoUtils::Image* image, int originX
        = 0, int originY = 0);
        virtual void valueToNormal(Ionflux::Altjira::Image& target, double 
        maxHeight) const;
        virtual Ionflux::GeoUtils::TransformableObject& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::TransformableObject& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::TransformableObject& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual void drawTranslate(double tx, double ty);
        virtual void drawScale(double sx, double sy);
        virtual void drawRotate(double phi);
        virtual void setDrawingMatrix(const Ionflux::GeoUtils::Matrix4& m);
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual Ionflux::GeoUtils::Image& duplicate();
        virtual std::string getString() const;
        virtual void getValueMatrix(Ionflux::Altjira::Matrix& target);
        virtual void setValueMatrix(const Ionflux::Altjira::Matrix& m);
        virtual void getPixelTree(Ionflux::GeoUtils::BoundingBox* target);
        virtual void markPixels(Ionflux::GeoUtils::BoxBoundsItemSet& 
        markPixels, const Ionflux::Altjira::Color& color = 
        Ionflux::Altjira::Color::BLUE, const 
        Ionflux::Altjira::ColorBlender* blender = 0);
		virtual Ionflux::GeoUtils::Image* copy() const;
		static Ionflux::GeoUtils::Image* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Image* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

}

}
