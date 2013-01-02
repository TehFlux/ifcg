/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polygon3Set.i                   Polygon set (3D) (interface).
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
#include "geoutils/Polygon3Set.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Polygon3;

class Polygon3SetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Polygon3SetClassInfo();
        virtual ~Polygon3SetClassInfo();
};

class Polygon3Set
: public Ionflux::GeoUtils::TransformableObject
{
    public:
		static const Ionflux::GeoUtils::Polygon3CompareAxis COMPARE_AXIS_X;
		static const Ionflux::GeoUtils::Polygon3CompareAxis COMPARE_AXIS_Y;
		static const Ionflux::GeoUtils::Polygon3CompareAxis COMPARE_AXIS_Z;
        
        Polygon3Set();
		Polygon3Set(const Ionflux::GeoUtils::Polygon3Set& other);
        virtual ~Polygon3Set();
        virtual Ionflux::GeoUtils::Polygon3* addPolygon();
        virtual void addPolygons(const Ionflux::GeoUtils::Polygon3Vector& 
        newPolygons);
        virtual void addPolygons(const Ionflux::GeoUtils::Polygon3Set& 
        newPolygons);
        virtual std::string getString() const;
        virtual std::string getSVG(const std::string& attrs = 
        SVG_DEFAULT_POLY_STYLE, const std::string& elementIDPrefix = 
        "polygon", Ionflux::GeoUtils::AxisID axis = 
        Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::SVGShapeType 
        shapeType = Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath =
        true);
        virtual std::string getSVG(const 
        Ionflux::GeoUtils::SVGShapeStyleVector& styles, const std::string& 
        elementIDPrefix = "polygon", Ionflux::GeoUtils::AxisID axis = 
        Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::SVGShapeType 
        shapeType = Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath =
        true);
        virtual std::string getSVG(Ionflux::GeoUtils::SVGImageProperties& 
        imageProperties, const std::string& elementIDPrefix = "polygon", 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y);
        virtual void writeSVG(const std::string& fileName, const 
        std::string& attrs = SVG_DEFAULT_POLY_STYLE, const std::string& 
        elementIDPrefix = "polygon", Ionflux::GeoUtils::AxisID axis = 
        Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::SVGShapeType 
        shapeType = Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath =
        true);
        virtual void writeSVG(const std::string& fileName, const 
        Ionflux::GeoUtils::SVGShapeStyleVector& styles, const std::string& 
        elementIDPrefix = "polygon", Ionflux::GeoUtils::AxisID axis = 
        Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::SVGShapeType 
        shapeType = Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath =
        true);
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual void writeSVG(Ionflux::GeoUtils::SVGImageProperties& 
        imageProperties, const std::string& elementIDPrefix = "polygon", 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y);
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Polygon3Set& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Polygon3Set& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Polygon3Set& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Polygon3Set& normalize();
        virtual Ionflux::GeoUtils::Polygon3Set& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Polygon3Set& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Polygon3Set& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Polygon3Set& transformVI(const 
        Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4*
        image = 0);
        virtual Ionflux::GeoUtils::Polygon3Set& duplicate();
        virtual void sort(Ionflux::GeoUtils::Polygon3Compare* compFunc = 
        0);
		virtual Ionflux::GeoUtils::Polygon3Set* copy() const;
		static Ionflux::GeoUtils::Polygon3Set* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Polygon3Set* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumPolygons() const;
        virtual Ionflux::GeoUtils::Polygon3* getPolygon(unsigned int 
        elementIndex = 0) const;
		virtual int findPolygon(Ionflux::GeoUtils::Polygon3* needle, unsigned int
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Polygon3*>& getPolygons();
        virtual void addPolygon(Ionflux::GeoUtils::Polygon3* addElement);        
        virtual void removePolygon(Ionflux::GeoUtils::Polygon3* 
        removeElement);
		virtual void removePolygonIndex(unsigned int removeIndex);
		virtual void clearPolygons();
};

}

}
