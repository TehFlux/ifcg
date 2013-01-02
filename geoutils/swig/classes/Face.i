/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Face.i                          Mesh face (interface).
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
#include "geoutils/Face.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class FaceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FaceClassInfo();
        virtual ~FaceClassInfo();
};

class Face
: public Ionflux::GeoUtils::BoxBoundsItem, public 
Ionflux::GeoUtils::TransformableObject
{
    public:
		static const unsigned int VERTEX_INDEX_NONE;
        
        Face();
		Face(const Ionflux::GeoUtils::Face& other);
        Face(const Ionflux::ObjectBase::UIntVector* initVerts, 
        Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, const 
        Ionflux::GeoUtils::TexCoordsVector* initUV = 0);
        Face(unsigned int v0, unsigned int v1, unsigned int v2, unsigned 
        int v3 = Ionflux::GeoUtils::Face::VERTEX_INDEX_NONE, 
        Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, const 
        Ionflux::GeoUtils::TexCoordsVector* initUV = 0);
        virtual ~Face();
        virtual void copyVertices();
        virtual void update();
        virtual void clearTangentSpace();
        virtual void clearPolygon();
        virtual void clear();
        virtual void addVertices(unsigned int v0, unsigned int v1, unsigned
        int v2, unsigned int v3 = 
        Ionflux::GeoUtils::Face::VERTEX_INDEX_NONE);
        virtual void addVertices(const Ionflux::ObjectBase::UIntVector& 
        newVerts);
        virtual void addTexCoords(const Ionflux::GeoUtils::TexCoordsVector&
        newTexCoords);
        virtual Ionflux::GeoUtils::Vector3 getTangent();
        virtual Ionflux::GeoUtils::Vector3 getBinormal();
        virtual Ionflux::GeoUtils::Vector3 getNormal();
        virtual Ionflux::GeoUtils::Matrix3 getTangentBase();
        virtual Ionflux::GeoUtils::Polygon3* getPolygon();
        virtual bool checkLineInner(const Ionflux::GeoUtils::Line3& line, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkPlaneInner(const Ionflux::GeoUtils::Plane3& plane,
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkSphereInner(const Ionflux::GeoUtils::Sphere3& 
        sphere, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkBoxInner(const Ionflux::GeoUtils::BoxBoundsItem& 
        other, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::FaceVector getTris();
        virtual bool isPlanar(double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual void makePlanar(double p = 1., double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool operator==(const Ionflux::GeoUtils::Face& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Face& other) 
        const;
        virtual std::string getString() const;
        virtual bool isBackface(const Ionflux::GeoUtils::Vector3& front);
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual Ionflux::GeoUtils::Range3 getBounds();
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Face& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Face& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Face& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Face& normalize();
        virtual Ionflux::GeoUtils::Face& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Face& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Face& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Face& duplicate();
        static Ionflux::GeoUtils::Face* create(unsigned int v0, unsigned 
        int v1, unsigned int v2, unsigned int v3 = 
        Ionflux::GeoUtils::Face::VERTEX_INDEX_NONE, 
        Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, const 
        Ionflux::GeoUtils::TexCoordsVector* initUV = 0);
        virtual std::string getXMLDataVertices() const;
        virtual std::string getXMLDataTexCoords() const;
        virtual std::string getXML() const;
        virtual void setFromXMLData(const std::string& vertexData, const 
        std::string& texCoordData);
		virtual Ionflux::GeoUtils::Face* copy() const;
		static Ionflux::GeoUtils::Face* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Face* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);        
        virtual unsigned int getNumVertices() const;
        virtual unsigned int getVertex(unsigned int elementIndex = 0) 
        const;
		virtual int findVertex(unsigned int needle, unsigned int occurence = 1) 
		const;
        virtual std::vector<unsigned int>& getVertices();
        virtual void addVertex(unsigned int addElement);        
        virtual void removeVertex(unsigned int removeElement);
		virtual void removeVertexIndex(unsigned int removeIndex);
		virtual void clearVertices();        
        virtual unsigned int getNumTexCoords() const;
        virtual Ionflux::GeoUtils::TexCoords getTexCoord(unsigned int 
        elementIndex = 0) const;
		virtual int findTexCoord(Ionflux::GeoUtils::TexCoords needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::TexCoords>& getTexCoords();
        virtual void addTexCoord(Ionflux::GeoUtils::TexCoords addElement);        
        virtual void removeTexCoord(Ionflux::GeoUtils::TexCoords 
        removeElement);
		virtual void removeTexCoordIndex(unsigned int removeIndex);
		virtual void clearTexCoords();
        virtual void setVertexSource(Ionflux::GeoUtils::Vertex3Set* 
        newVertexSource);
        virtual Ionflux::GeoUtils::Vertex3Set* getVertexSource() const;
};

}

}
