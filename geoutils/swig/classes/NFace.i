/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NFace.i                         N-face (interface).
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
#include "geoutils/NFace.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VectorSetSet;
class FaceData;
class NFaceSet;

class NFaceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NFaceClassInfo();
        virtual ~NFaceClassInfo();
};

class NFace
: virtual public Ionflux::GeoUtils::BoxBoundsItem, virtual public 
Ionflux::GeoUtils::TransformableObject
{
    public:
		static const unsigned int VERTEX_INDEX_NONE;
		static const Ionflux::GeoUtils::NFaceTypeID TYPE_FACE;
		static const Ionflux::GeoUtils::NFaceTypeID TYPE_EDGE;
        
        NFace();
		NFace(const Ionflux::GeoUtils::NFace& other);
        NFace(const Ionflux::ObjectBase::UIntVector* initVerts, 
        Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
        Ionflux::GeoUtils::FaceData* initUV = 0, 
        Ionflux::GeoUtils::FaceData* initVertexColors = 0);
        NFace(unsigned int v0, unsigned int v1, unsigned int v2 = 
        Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, unsigned int v3 = 
        Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, 
        Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
        Ionflux::GeoUtils::FaceData* initUV = 0, 
        Ionflux::GeoUtils::FaceData* initVertexColors = 0);
        virtual ~NFace();
        virtual void copyVertices();
        virtual void update();
        virtual void clearPolygon();
        virtual void clear();
        virtual void addVertices(unsigned int v0, unsigned int v1 = 
        Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, unsigned int v2 = 
        Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, unsigned int v3 = 
        Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE);
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
        virtual Ionflux::GeoUtils::Polygon3* getPolygon();
        virtual bool checkLineInner(const Ionflux::GeoUtils::Line3& line, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkPlaneInner(const Ionflux::GeoUtils::Plane3& plane,
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkSphereInner(const Ionflux::GeoUtils::Sphere3& 
        sphere, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkBoxInner(const Ionflux::GeoUtils::BoxBoundsItem& 
        other, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Vertex3* getVertexData(unsigned int 
        index) const;
        virtual bool isPlanar(double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool isEdge() const;
        virtual bool isTri() const;
        virtual bool isQuad() const;
        virtual void getEdge(Ionflux::GeoUtils::Edge& target) const;
        virtual Ionflux::GeoUtils::Edge getEdge0() const;
        virtual void applyVertexIndexOffset(int offset);
        virtual void getTris(Ionflux::GeoUtils::NFaceVector& target);
        virtual void getTris(Ionflux::GeoUtils::NFaceSet& target);
        virtual Ionflux::GeoUtils::NFaceVector getTris0();
        virtual void getEdges(Ionflux::GeoUtils::NFaceVector& target, bool 
        copyFaceData = true);
        virtual void getEdges(Ionflux::GeoUtils::NFaceSet& target, bool 
        copyFaceData = true);
        virtual double getArea();
        virtual bool operator==(const Ionflux::GeoUtils::NFace& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::NFace& other) 
        const;
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual Ionflux::GeoUtils::Range3 getBounds();
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::NFace& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::NFace& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::NFace& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::NFace& normalize();
        virtual Ionflux::GeoUtils::NFace& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::NFace& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::NFace& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::NFace& duplicate();
        virtual std::string getValueString() const;
        static std::string 
        getNFaceTypeIDString(Ionflux::GeoUtils::NFaceTypeID typeID);
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::NFace* copy() const;
		static Ionflux::GeoUtils::NFace* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::NFace* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::NFace* create(const 
		Ionflux::ObjectBase::UIntVector* initVerts, 
		Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
		Ionflux::GeoUtils::FaceData* initUV = 0, Ionflux::GeoUtils::FaceData* 
		initVertexColors = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::NFace* create(unsigned int v0, unsigned int v1,
		unsigned int v2 = Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, unsigned 
		int v3 = Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, 
		Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
		Ionflux::GeoUtils::FaceData* initUV = 0, Ionflux::GeoUtils::FaceData* 
		initVertexColors = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual bool serialize(std::string& target) const;
        virtual Ionflux::ObjectBase::DataSize deserialize(const std::string& source, int offset = 0);
        virtual bool serialize(Ionflux::ObjectBase::IFIOContext& ioCtx, bool addMagicWord = true) const;
        virtual Ionflux::ObjectBase::DataSize deserialize(Ionflux::ObjectBase::IFIOContext& ioCtx, Ionflux::ObjectBase::DataSize offset = Ionflux::ObjectBase::DATA_SIZE_INVALID, bool checkMagicWord = true);
        virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllable() const;
        virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllableBase() const;        
        virtual unsigned int getNumVertices() const;
        virtual unsigned int getVertex(unsigned int elementIndex = 0) 
        const;
		virtual int findVertex(unsigned int needle, unsigned int occurence = 1) 
		const;
        virtual std::vector<unsigned int>& getVertices();
        virtual void addVertex(unsigned int addElement);
		virtual unsigned int addVertex();
		virtual void addVertices(std::vector<unsigned int>& newVertices);
		virtual void addVertices(Ionflux::GeoUtils::NFace* newVertices);        
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
