/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Face.i                          Mesh face (interface).
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
#include "geoutils/Face.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VectorSetSet;
class FaceData;

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
        Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
        Ionflux::GeoUtils::FaceData* initUV = 0, 
        Ionflux::GeoUtils::FaceData* initVertexColors = 0);
        Face(unsigned int v0, unsigned int v1, unsigned int v2, unsigned 
        int v3 = Ionflux::GeoUtils::Face::VERTEX_INDEX_NONE, 
        Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
        Ionflux::GeoUtils::FaceData* initUV = 0, 
        Ionflux::GeoUtils::FaceData* initVertexColors = 0);
        virtual ~Face();
        virtual void copyVertices();
        virtual void update();
        virtual void clearTangentSpace();
        virtual void clearPolygon();
        virtual void clear();
        virtual void addVertices(unsigned int v0, unsigned int v1, unsigned
        int v2, unsigned int v3 = 
        Ionflux::GeoUtils::Face::VERTEX_INDEX_NONE);
        virtual Ionflux::GeoUtils::VectorSet* 
        addFaceData(Ionflux::GeoUtils::FaceData* newFaceData);
        virtual Ionflux::GeoUtils::VectorSet* 
        addFaceData(Ionflux::GeoUtils::FaceDataTypeID dataType);
        virtual Ionflux::GeoUtils::VectorSet* 
        addFaceData(Ionflux::GeoUtils::FaceDataTypeID dataType, 
        Ionflux::GeoUtils::Vector* v0, Ionflux::GeoUtils::Vector* v1 = 0, 
        Ionflux::GeoUtils::Vector* v2 = 0, Ionflux::GeoUtils::Vector* v3 = 
        0);
        virtual Ionflux::GeoUtils::VectorSet* 
        addTexCoords(Ionflux::GeoUtils::Vector* v0, 
        Ionflux::GeoUtils::Vector* v1 = 0, Ionflux::GeoUtils::Vector* v2 = 
        0, Ionflux::GeoUtils::Vector* v3 = 0);
        virtual Ionflux::GeoUtils::VectorSet* 
        addVertexColors(Ionflux::GeoUtils::Vector* v0, 
        Ionflux::GeoUtils::Vector* v1 = 0, Ionflux::GeoUtils::Vector* v2 = 
        0, Ionflux::GeoUtils::Vector* v3 = 0);
        virtual Ionflux::GeoUtils::VectorSet* 
        addVertexNormals(Ionflux::GeoUtils::Vector* v0, 
        Ionflux::GeoUtils::Vector* v1 = 0, Ionflux::GeoUtils::Vector* v2 = 
        0, Ionflux::GeoUtils::Vector* v3 = 0);
        virtual void getFaceDataByType(Ionflux::GeoUtils::FaceDataTypeID 
        dataType, Ionflux::GeoUtils::VectorSetSet& target);
        virtual Ionflux::GeoUtils::FaceData* 
        getFaceDataByType0(Ionflux::GeoUtils::FaceDataTypeID dataType, 
        unsigned int index = 0);
        virtual void getTexCoords(Ionflux::GeoUtils::VectorSetSet& target);
        virtual Ionflux::GeoUtils::FaceData* getTexCoords0(unsigned int 
        index = 0);
        virtual void getVertexColors(Ionflux::GeoUtils::VectorSetSet& 
        target);
        virtual Ionflux::GeoUtils::FaceData* getVertexColors0(unsigned int 
        index = 0);
        virtual void getVertexNormals(Ionflux::GeoUtils::VectorSetSet& 
        target);
        virtual Ionflux::GeoUtils::FaceData* getVertexNormals0(unsigned int
        index = 0);
        virtual void getFaceDataByVertex(Ionflux::ObjectBase::UIntVector& 
        faceVertexIndices, Ionflux::GeoUtils::VectorSetSet& target);
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
        virtual void getTris(Ionflux::GeoUtils::FaceVector& target);
        virtual Ionflux::GeoUtils::FaceVector getTris0();
        virtual bool isTri();
        virtual bool isQuad();
        virtual bool isPlanar(double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual void makePlanar(double p = 1., double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool operator==(const Ionflux::GeoUtils::Face& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Face& other) 
        const;
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
        virtual std::string getValueString() const;
        virtual std::string getXMLDataVertices_legacy() const;
        virtual std::string getXMLDataTexCoords_legacy() const;
        virtual std::string getXML_legacy() const;
        virtual void setFromXMLData_legacy(const std::string& vertexData, 
        const std::string& texCoordData);
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Face* copy() const;
		static Ionflux::GeoUtils::Face* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Face* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Face* create(const 
		Ionflux::ObjectBase::UIntVector* initVerts, 
		Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
		Ionflux::GeoUtils::FaceData* initUV = 0, Ionflux::GeoUtils::FaceData* 
		initVertexColors = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Face* create(unsigned int v0, unsigned int v1, 
		unsigned int v2, unsigned int v3 = 
		Ionflux::GeoUtils::Face::VERTEX_INDEX_NONE, 
		Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
		Ionflux::GeoUtils::FaceData* initUV = 0, Ionflux::GeoUtils::FaceData* 
		initVertexColors = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumVertices() const;
        virtual unsigned int getVertex(unsigned int elementIndex = 0) 
        const;
		virtual int findVertex(unsigned int needle, unsigned int occurence = 1) 
		const;
        virtual std::vector<unsigned int>& getVertices();
        virtual void addVertex(unsigned int addElement);
		virtual unsigned int addVertex();
		virtual void addVertices(std::vector<unsigned int>& newVertices);
		virtual void addVertices(Ionflux::GeoUtils::Face* newVertices);        
        virtual void removeVertex(unsigned int removeElement);
		virtual void removeVertexIndex(unsigned int removeIndex);
		virtual void clearVertices();
        virtual void setVertexSource(Ionflux::GeoUtils::Vertex3Set* 
        newVertexSource);
        virtual Ionflux::GeoUtils::Vertex3Set* getVertexSource() const;
        virtual void setFaceData(Ionflux::GeoUtils::VectorSetSet* 
        newFaceData);
        virtual Ionflux::GeoUtils::VectorSetSet* getFaceData() const;
};

}

}
