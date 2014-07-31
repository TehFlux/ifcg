/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Mesh.i                          Mesh (interface).
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
#include "geoutils/Mesh.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class MeshClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MeshClassInfo();
        virtual ~MeshClassInfo();
};

class Mesh
: virtual public Ionflux::GeoUtils::BoxBoundsItem, virtual public 
Ionflux::GeoUtils::ItemSource, virtual public 
Ionflux::GeoUtils::TransformableObject
{
    public:
		static const std::string DEFAULT_ID;
        
        Mesh();
		Mesh(const Ionflux::GeoUtils::Mesh& other);
        Mesh(Ionflux::GeoUtils::Vertex3Vector* initVerts, const 
        Ionflux::GeoUtils::FaceVector* initFaces);
        Mesh(Ionflux::GeoUtils::Vertex3Set* initVertexSource, const 
        Ionflux::GeoUtils::FaceVector* initFaces);
        virtual ~Mesh();
        virtual Ionflux::GeoUtils::Range3 getBounds();
        virtual void copyVertices();
        virtual void update();
        virtual void clear();
        virtual void clearData();
        virtual void setFaceIDs();
        virtual Ionflux::GeoUtils::BoxBoundsItem* getItem(const 
        std::string& itemID);
        virtual int checkPlaneInner(const Ionflux::GeoUtils::Plane3& plane,
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkSphereInner(const Ionflux::GeoUtils::Sphere3& 
        sphere, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool checkLineInner(const Ionflux::GeoUtils::Line3& line, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkBoxInner(const Ionflux::GeoUtils::BoxBoundsItem& 
        other, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool operator==(const Ionflux::GeoUtils::Mesh& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Mesh& other) 
        const;
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Mesh& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Mesh& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Mesh& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Mesh& swapAxes(Ionflux::GeoUtils::AxisID
        x = Ionflux::GeoUtils::AXIS_X, Ionflux::GeoUtils::AxisID y = 
        Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID z = 
        Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID w = 
        Ionflux::GeoUtils::AXIS_W);
        virtual Ionflux::GeoUtils::Mesh& normalize();
        virtual Ionflux::GeoUtils::Mesh& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Mesh& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Mesh& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Mesh& duplicate();
        virtual void getPolygons(Ionflux::GeoUtils::Polygon3Set& target);
        virtual void removeBackfaces(const Ionflux::GeoUtils::Vector3& 
        front);
        virtual void sortFaces(Ionflux::GeoUtils::FaceCompare* compFunc = 
        0);
        virtual unsigned int makePlanar(const 
        Ionflux::ObjectBase::UIntVector& indices, unsigned int 
        maxIterations = 10000, double p = 1., double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual unsigned int makeTris();
        virtual std::string getValueString() const;
        static Ionflux::GeoUtils::Mesh* plane();
        static Ionflux::GeoUtils::Mesh* cube();
        static Ionflux::GeoUtils::Mesh* cylinder(unsigned int subDivs = 10,
        double length = 1., double radius = 0.5);
        static Ionflux::GeoUtils::Mesh* arrow(unsigned int subDivs = 10, 
        double length = 1., double radius = 0.005, double headLength = 0.1,
        double headRadius = 4.);
        static Ionflux::GeoUtils::Mesh* grid(unsigned int subDivsX = 10, 
        unsigned int subDivsY = 10);
        static Ionflux::GeoUtils::Mesh* fiber(unsigned int aSubDivs = 10, 
        unsigned int lSubDivs = 10, double length = 1., double radius = 
        0.05);
        virtual std::string getXML_legacy() const;
        virtual void writeToFile_legacy(const std::string& fileName) const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Mesh* copy() const;
		static Ionflux::GeoUtils::Mesh* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Mesh* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Mesh* create(Ionflux::GeoUtils::Vertex3Vector* 
		initVerts, const Ionflux::GeoUtils::FaceVector* initFaces, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Mesh* create(Ionflux::GeoUtils::Vertex3Set* 
		initVertexSource, const Ionflux::GeoUtils::FaceVector* initFaces, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
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
		virtual void addVertices(Ionflux::GeoUtils::Mesh* newVertices);        
        virtual void removeVertex(Ionflux::GeoUtils::Vertex3* 
        removeElement);
		virtual void removeVertexIndex(unsigned int removeIndex);
		virtual void clearVertices();        
        virtual unsigned int getNumFaces() const;
        virtual Ionflux::GeoUtils::Face* getFace(unsigned int elementIndex 
        = 0) const;
		virtual int findFace(Ionflux::GeoUtils::Face* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Face*>& getFaces();
        virtual void addFace(Ionflux::GeoUtils::Face* addElement);
		virtual Ionflux::GeoUtils::Face* addFace();
		virtual void addFaces(std::vector<Ionflux::GeoUtils::Face*>& newFaces);
		virtual void addFaces(Ionflux::GeoUtils::Mesh* newFaces);        
        virtual void removeFace(Ionflux::GeoUtils::Face* removeElement);
		virtual void removeFaceIndex(unsigned int removeIndex);
		virtual void clearFaces();
};

}

}
