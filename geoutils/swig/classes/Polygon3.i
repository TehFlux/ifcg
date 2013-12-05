/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polygon3.i                      Polygon (3D) (interface).
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
%{
#include "geoutils/Polygon3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Polygon3;

class Polygon3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Polygon3ClassInfo();
        virtual ~Polygon3ClassInfo();
};

class Polygon3
: public Ionflux::GeoUtils::TransformableObject
{
    public:
		static const Ionflux::GeoUtils::Range UV_RANGE;
        
        Polygon3();
		Polygon3(const Ionflux::GeoUtils::Polygon3& other);
        Polygon3(Ionflux::GeoUtils::Vertex3Vector* initVertices, 
        Ionflux::GeoUtils::EdgeVector* initEdges = 0);
        Polygon3(Ionflux::GeoUtils::Vertex3Set* initVertexSource, 
        Ionflux::GeoUtils::EdgeVector* initEdges = 0);
        Polygon3(const Ionflux::GeoUtils::Vertex3* v0, const 
        Ionflux::GeoUtils::Vertex3* v1, const Ionflux::GeoUtils::Vertex3* 
        v2, const Ionflux::GeoUtils::Vertex3* v3 = 0);
        virtual ~Polygon3();
        virtual void clearData();
        virtual void copyVertices();
        virtual Ionflux::GeoUtils::Edge* addEdge(int i0, int i1);
        virtual int createEdges();
        virtual Ionflux::GeoUtils::Plane3 getPlane(int v0 = 0, int v1 = 1, 
        int v2 = -1) const;
        virtual std::string getValueString() const;
        virtual std::string getSVG(const std::string& attrs = 
        SVG_DEFAULT_POLY_STYLE, const std::string& elementID = "polygon", 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y, 
        Ionflux::GeoUtils::SVGShapeType shapeType = 
        Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath = true);
        virtual std::string getSVG(const Ionflux::GeoUtils::SVGShapeStyle& 
        style, const std::string& elementID = "polygon", 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y, 
        Ionflux::GeoUtils::SVGShapeType shapeType = 
        Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath = true);
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Polygon3& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Polygon3& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Polygon3& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Polygon3& normalize();
        virtual Ionflux::GeoUtils::Polygon3& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Polygon3& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Polygon3& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Polygon3& duplicate();
        virtual bool isPlanar(double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual void getPolygon2(Ionflux::GeoUtils::Polygon2& target);
        static Ionflux::GeoUtils::Polygon3* square();
        virtual bool isTri();
        virtual bool isQuad();
        virtual void calculateUVCoefficients(const 
        Ionflux::GeoUtils::Vertex3& p, Ionflux::GeoUtils::Matrix4& target, 
        Ionflux::ObjectBase::IntVector* indices = 0, double s = 1.);
        virtual Ionflux::GeoUtils::Vector2 getUV(const 
        Ionflux::GeoUtils::Vertex3& p, Ionflux::ObjectBase::IntVector* 
        indices = 0, Ionflux::GeoUtils::QuadInterpolationTypeID 
        interpolationType = QUAD_INTERPOLATION_BILINEAR, double s = 1., 
        double t = DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Vertex3 getUVVertex(const 
        Ionflux::GeoUtils::Vector2& uv, Ionflux::ObjectBase::IntVector* 
        indices = 0, Ionflux::GeoUtils::QuadInterpolationTypeID 
        interpolationType = QUAD_INTERPOLATION_BILINEAR);
        virtual void createSpline(Ionflux::Mapping::BezierSpline& target, 
        double smoothness = 0.2);
        static Ionflux::GeoUtils::Polygon3* circle(unsigned int resolution 
        = 20);
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Polygon3* copy() const;
		static Ionflux::GeoUtils::Polygon3* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::GeoUtils::Polygon3* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		static Ionflux::GeoUtils::Polygon3* 
		create(Ionflux::GeoUtils::Vertex3Vector* initVertices, 
		Ionflux::GeoUtils::EdgeVector* initEdges = 0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Polygon3* create(Ionflux::GeoUtils::Vertex3Set*
		initVertexSource, Ionflux::GeoUtils::EdgeVector* initEdges = 0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Polygon3* create(const 
		Ionflux::GeoUtils::Vertex3* v0, const Ionflux::GeoUtils::Vertex3* v1, 
		const Ionflux::GeoUtils::Vertex3* v2, const Ionflux::GeoUtils::Vertex3* 
		v3 = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setVertexSource(Ionflux::GeoUtils::Vertex3Set* 
        newVertexSource);
        virtual Ionflux::GeoUtils::Vertex3Set* getVertexSource() const;        
        virtual unsigned int getNumVertices() const;
        virtual Ionflux::GeoUtils::Vertex3* getVertex(unsigned int 
        elementIndex = 0) const;
		virtual int findVertex(Ionflux::GeoUtils::Vertex3* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Vertex3*>& getVertices();
        virtual void addVertex(Ionflux::GeoUtils::Vertex3* addElement);
		virtual Ionflux::GeoUtils::Vertex3* addVertex();
		virtual void addVertices(std::vector<Ionflux::GeoUtils::Vertex3*>& 
		newVertices);
		virtual void addVertices(Ionflux::GeoUtils::Polygon3* newVertices);        
        virtual void removeVertex(Ionflux::GeoUtils::Vertex3* 
        removeElement);
		virtual void removeVertexIndex(unsigned int removeIndex);
		virtual void clearVertices();        
        virtual unsigned int getNumEdges() const;
        virtual Ionflux::GeoUtils::Edge* getEdge(unsigned int elementIndex 
        = 0) const;
		virtual int findEdge(Ionflux::GeoUtils::Edge* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Edge*>& getEdges();
        virtual void addEdge(Ionflux::GeoUtils::Edge* addElement);
		virtual Ionflux::GeoUtils::Edge* addEdge();
		virtual void addEdges(std::vector<Ionflux::GeoUtils::Edge*>& newEdges);
		virtual void addEdges(Ionflux::GeoUtils::Polygon3* newEdges);        
        virtual void removeEdge(Ionflux::GeoUtils::Edge* removeElement);
		virtual void removeEdgeIndex(unsigned int removeIndex);
		virtual void clearEdges();
};

}

}
