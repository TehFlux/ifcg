#ifndef IONFLUX_GEOUTILS_XMLUTILS_PRIVATE
#define IONFLUX_GEOUTILS_XMLUTILS_PRIVATE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * xmlutils_private.hpp                  XML utility functions (header).
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



namespace Ionflux
{

namespace GeoUtils
{

class Vector;

namespace XMLUtils
{

/// Initialize Vector from TiXmlElement.
void getVector(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector& target, const std::string& elementName = 
Ionflux::GeoUtils::Vector::XML_ELEMENT_NAME);

/// Create new Vector from TiXmlElement.
Ionflux::GeoUtils::Vector* createVector(TiXmlElement* e0, const 
std::string& elementName = Ionflux::GeoUtils::Vector::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Vector from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Vector>(TiXmlElement* e0, 
Ionflux::GeoUtils::Vector& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Vector2;

namespace XMLUtils
{

/// Initialize Vector2 from TiXmlElement.
void getVector2(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector2& target, const std::string& elementName = 
Ionflux::GeoUtils::Vector2::XML_ELEMENT_NAME);

/// Create new Vector2 from TiXmlElement.
Ionflux::GeoUtils::Vector2* createVector2(TiXmlElement* e0, const 
std::string& elementName = Ionflux::GeoUtils::Vector2::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Vector2 from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Vector2>(TiXmlElement* e0, 
Ionflux::GeoUtils::Vector2& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Vector3;

namespace XMLUtils
{

/// Initialize Vector3 from TiXmlElement.
void getVector3(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector3& target, const std::string& elementName = 
Ionflux::GeoUtils::Vector3::XML_ELEMENT_NAME);

/// Create new Vector3 from TiXmlElement.
Ionflux::GeoUtils::Vector3* createVector3(TiXmlElement* e0, const 
std::string& elementName = Ionflux::GeoUtils::Vector3::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Vector3 from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Vector3>(TiXmlElement* e0, 
Ionflux::GeoUtils::Vector3& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Vector4;

namespace XMLUtils
{

/// Initialize Vector4 from TiXmlElement.
void getVector4(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector4& target, const std::string& elementName = 
Ionflux::GeoUtils::Vector4::XML_ELEMENT_NAME);

/// Create new Vector4 from TiXmlElement.
Ionflux::GeoUtils::Vector4* createVector4(TiXmlElement* e0, const 
std::string& elementName = Ionflux::GeoUtils::Vector4::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Vector4 from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Vector4>(TiXmlElement* e0, 
Ionflux::GeoUtils::Vector4& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class VectorSet;

namespace XMLUtils
{

/// Initialize VectorSet from TiXmlElement.
void getVectorSet(TiXmlElement* e0, 
    Ionflux::GeoUtils::VectorSet& target, const std::string& elementName = 
Ionflux::GeoUtils::VectorSet::XML_ELEMENT_NAME);

/// Create new VectorSet from TiXmlElement.
Ionflux::GeoUtils::VectorSet* createVectorSet(TiXmlElement* e0, const 
std::string& elementName = Ionflux::GeoUtils::VectorSet::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize VectorSet from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::VectorSet>(TiXmlElement* e0, 
Ionflux::GeoUtils::VectorSet& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class FaceData;

namespace XMLUtils
{

/// Initialize FaceData from TiXmlElement.
void getFaceData(TiXmlElement* e0, 
    Ionflux::GeoUtils::FaceData& target, const std::string& elementName = 
Ionflux::GeoUtils::FaceData::XML_ELEMENT_NAME);

/// Create new FaceData from TiXmlElement.
Ionflux::GeoUtils::FaceData* createFaceData(TiXmlElement* e0, const 
std::string& elementName = Ionflux::GeoUtils::FaceData::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize FaceData from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::FaceData>(TiXmlElement* e0, 
Ionflux::GeoUtils::FaceData& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Matrix;

namespace XMLUtils
{

/// Initialize Matrix from TiXmlElement.
void getMatrix(TiXmlElement* e0, 
    Ionflux::GeoUtils::Matrix& target, const std::string& elementName = 
Ionflux::GeoUtils::Matrix::XML_ELEMENT_NAME);

/// Create new Matrix from TiXmlElement.
Ionflux::GeoUtils::Matrix* createMatrix(TiXmlElement* e0, const 
std::string& elementName = Ionflux::GeoUtils::Matrix::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Matrix from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Matrix>(TiXmlElement* e0, 
Ionflux::GeoUtils::Matrix& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Matrix2;

namespace XMLUtils
{

/// Initialize Matrix2 from TiXmlElement.
void getMatrix2(TiXmlElement* e0, 
    Ionflux::GeoUtils::Matrix2& target, const std::string& elementName = 
Ionflux::GeoUtils::Matrix2::XML_ELEMENT_NAME);

/// Create new Matrix2 from TiXmlElement.
Ionflux::GeoUtils::Matrix2* createMatrix2(TiXmlElement* e0, const 
std::string& elementName = Ionflux::GeoUtils::Matrix2::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Matrix2 from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Matrix2>(TiXmlElement* e0, 
Ionflux::GeoUtils::Matrix2& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Matrix3;

namespace XMLUtils
{

/// Initialize Matrix3 from TiXmlElement.
void getMatrix3(TiXmlElement* e0, 
    Ionflux::GeoUtils::Matrix3& target, const std::string& elementName = 
Ionflux::GeoUtils::Matrix3::XML_ELEMENT_NAME);

/// Create new Matrix3 from TiXmlElement.
Ionflux::GeoUtils::Matrix3* createMatrix3(TiXmlElement* e0, const 
std::string& elementName = Ionflux::GeoUtils::Matrix3::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Matrix3 from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Matrix3>(TiXmlElement* e0, 
Ionflux::GeoUtils::Matrix3& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Matrix4;

namespace XMLUtils
{

/// Initialize Matrix4 from TiXmlElement.
void getMatrix4(TiXmlElement* e0, 
    Ionflux::GeoUtils::Matrix4& target, const std::string& elementName = 
Ionflux::GeoUtils::Matrix4::XML_ELEMENT_NAME);

/// Create new Matrix4 from TiXmlElement.
Ionflux::GeoUtils::Matrix4* createMatrix4(TiXmlElement* e0, const 
std::string& elementName = Ionflux::GeoUtils::Matrix4::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Matrix4 from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Matrix4>(TiXmlElement* e0, 
Ionflux::GeoUtils::Matrix4& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class VectorSetSet;

namespace XMLUtils
{

/// Initialize VectorSetSet from TiXmlElement.
void getVectorSetSet(TiXmlElement* e0, 
    Ionflux::GeoUtils::VectorSetSet& target, const std::string& elementName
= Ionflux::GeoUtils::VectorSetSet::XML_ELEMENT_NAME);

/// Create new VectorSetSet from TiXmlElement.
Ionflux::GeoUtils::VectorSetSet* createVectorSetSet(TiXmlElement* e0, const
std::string& elementName = 
Ionflux::GeoUtils::VectorSetSet::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize VectorSetSet from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::VectorSetSet>(TiXmlElement* e0, 
Ionflux::GeoUtils::VectorSetSet& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class DeferredTransform;

namespace XMLUtils
{

/// Initialize DeferredTransform from TiXmlElement.
void getDeferredTransform(TiXmlElement* e0, 
    Ionflux::GeoUtils::DeferredTransform& target, const std::string& 
elementName = Ionflux::GeoUtils::DeferredTransform::XML_ELEMENT_NAME);

/// Create new DeferredTransform from TiXmlElement.
Ionflux::GeoUtils::DeferredTransform* createDeferredTransform(TiXmlElement*
e0, const std::string& elementName = 
Ionflux::GeoUtils::DeferredTransform::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize DeferredTransform from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::DeferredTransform>(TiXmlElement* e0, 
Ionflux::GeoUtils::DeferredTransform& target, const std::string& 
elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class TransformableObject;

namespace XMLUtils
{

/// Initialize TransformableObject from TiXmlElement.
void getTransformableObject(TiXmlElement* e0, 
    Ionflux::GeoUtils::TransformableObject& target, const std::string& 
elementName = Ionflux::GeoUtils::TransformableObject::XML_ELEMENT_NAME);

/// Create new TransformableObject from TiXmlElement.
Ionflux::GeoUtils::TransformableObject* 
createTransformableObject(TiXmlElement* e0, const std::string& elementName 
= Ionflux::GeoUtils::TransformableObject::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize TransformableObject from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::TransformableObject>(TiXmlElement* e0, 
Ionflux::GeoUtils::TransformableObject& target, const std::string& 
elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Vertex2;

namespace XMLUtils
{

/// Initialize Vertex2 from TiXmlElement.
void getVertex2(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vertex2& target, const std::string& elementName = 
Ionflux::GeoUtils::Vertex2::XML_ELEMENT_NAME);

/// Create new Vertex2 from TiXmlElement.
Ionflux::GeoUtils::Vertex2* createVertex2(TiXmlElement* e0, const 
std::string& elementName = Ionflux::GeoUtils::Vertex2::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Vertex2 from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Vertex2>(TiXmlElement* e0, 
Ionflux::GeoUtils::Vertex2& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Vertex3;

namespace XMLUtils
{

/// Initialize Vertex3 from TiXmlElement.
void getVertex3(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vertex3& target, const std::string& elementName = 
Ionflux::GeoUtils::Vertex3::XML_ELEMENT_NAME);

/// Create new Vertex3 from TiXmlElement.
Ionflux::GeoUtils::Vertex3* createVertex3(TiXmlElement* e0, const 
std::string& elementName = Ionflux::GeoUtils::Vertex3::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Vertex3 from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Vertex3>(TiXmlElement* e0, 
Ionflux::GeoUtils::Vertex3& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Vertex3Set;

namespace XMLUtils
{

/// Initialize Vertex3Set from TiXmlElement.
void getVertex3Set(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vertex3Set& target, const std::string& elementName =
Ionflux::GeoUtils::Vertex3Set::XML_ELEMENT_NAME);

/// Create new Vertex3Set from TiXmlElement.
Ionflux::GeoUtils::Vertex3Set* createVertex3Set(TiXmlElement* e0, const 
std::string& elementName = 
Ionflux::GeoUtils::Vertex3Set::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Vertex3Set from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Vertex3Set>(TiXmlElement* e0, 
Ionflux::GeoUtils::Vertex3Set& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Face;

namespace XMLUtils
{

/// Initialize Face from TiXmlElement.
void getFace(TiXmlElement* e0, 
    Ionflux::GeoUtils::Face& target, const std::string& elementName = 
Ionflux::GeoUtils::Face::XML_ELEMENT_NAME);

/// Create new Face from TiXmlElement.
Ionflux::GeoUtils::Face* createFace(TiXmlElement* e0, const std::string& 
elementName = Ionflux::GeoUtils::Face::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Face from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Face>(TiXmlElement* e0, 
Ionflux::GeoUtils::Face& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Edge;

namespace XMLUtils
{

/// Initialize Edge from TiXmlElement.
void getEdge(TiXmlElement* e0, 
    Ionflux::GeoUtils::Edge& target, const std::string& elementName = 
Ionflux::GeoUtils::Edge::XML_ELEMENT_NAME);

/// Create new Edge from TiXmlElement.
Ionflux::GeoUtils::Edge* createEdge(TiXmlElement* e0, const std::string& 
elementName = Ionflux::GeoUtils::Edge::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Edge from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Edge>(TiXmlElement* e0, 
Ionflux::GeoUtils::Edge& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Mesh;

namespace XMLUtils
{

/// Initialize Mesh from TiXmlElement.
void getMesh(TiXmlElement* e0, 
    Ionflux::GeoUtils::Mesh& target, const std::string& elementName = 
Ionflux::GeoUtils::Mesh::XML_ELEMENT_NAME);

/// Create new Mesh from TiXmlElement.
Ionflux::GeoUtils::Mesh* createMesh(TiXmlElement* e0, const std::string& 
elementName = Ionflux::GeoUtils::Mesh::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Mesh from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Mesh>(TiXmlElement* e0, 
Ionflux::GeoUtils::Mesh& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Object3;

namespace XMLUtils
{

/// Initialize Object3 from TiXmlElement.
void getObject3(TiXmlElement* e0, 
    Ionflux::GeoUtils::Object3& target, const std::string& elementName = 
Ionflux::GeoUtils::Object3::XML_ELEMENT_NAME);

/// Create new Object3 from TiXmlElement.
Ionflux::GeoUtils::Object3* createObject3(TiXmlElement* e0, const 
std::string& elementName = Ionflux::GeoUtils::Object3::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Object3 from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Object3>(TiXmlElement* e0, 
Ionflux::GeoUtils::Object3& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class TransformableGroup;

namespace XMLUtils
{

/// Initialize TransformableGroup from TiXmlElement.
void getTransformableGroup(TiXmlElement* e0, 
    Ionflux::GeoUtils::TransformableGroup& target, const std::string& 
elementName = Ionflux::GeoUtils::TransformableGroup::XML_ELEMENT_NAME);

/// Create new TransformableGroup from TiXmlElement.
Ionflux::GeoUtils::TransformableGroup* 
createTransformableGroup(TiXmlElement* e0, const std::string& elementName =
Ionflux::GeoUtils::TransformableGroup::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize TransformableGroup from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::TransformableGroup>(TiXmlElement* e0, 
Ionflux::GeoUtils::TransformableGroup& target, const std::string& 
elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Polygon3;

namespace XMLUtils
{

/// Initialize Polygon3 from TiXmlElement.
void getPolygon3(TiXmlElement* e0, 
    Ionflux::GeoUtils::Polygon3& target, const std::string& elementName = 
Ionflux::GeoUtils::Polygon3::XML_ELEMENT_NAME);

/// Create new Polygon3 from TiXmlElement.
Ionflux::GeoUtils::Polygon3* createPolygon3(TiXmlElement* e0, const 
std::string& elementName = Ionflux::GeoUtils::Polygon3::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Polygon3 from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Polygon3>(TiXmlElement* e0, 
Ionflux::GeoUtils::Polygon3& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Polygon3Set;

namespace XMLUtils
{

/// Initialize Polygon3Set from TiXmlElement.
void getPolygon3Set(TiXmlElement* e0, 
    Ionflux::GeoUtils::Polygon3Set& target, const std::string& elementName 
= Ionflux::GeoUtils::Polygon3Set::XML_ELEMENT_NAME);

/// Create new Polygon3Set from TiXmlElement.
Ionflux::GeoUtils::Polygon3Set* createPolygon3Set(TiXmlElement* e0, const 
std::string& elementName = 
Ionflux::GeoUtils::Polygon3Set::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Polygon3Set from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Polygon3Set>(TiXmlElement* e0, 
Ionflux::GeoUtils::Polygon3Set& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Shape3;

namespace XMLUtils
{

/// Initialize Shape3 from TiXmlElement.
void getShape3(TiXmlElement* e0, 
    Ionflux::GeoUtils::Shape3& target, const std::string& elementName = 
Ionflux::GeoUtils::Shape3::XML_ELEMENT_NAME);

/// Create new Shape3 from TiXmlElement.
Ionflux::GeoUtils::Shape3* createShape3(TiXmlElement* e0, const 
std::string& elementName = Ionflux::GeoUtils::Shape3::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Shape3 from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Shape3>(TiXmlElement* e0, 
Ionflux::GeoUtils::Shape3& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Camera;

namespace XMLUtils
{

/// Initialize Camera from TiXmlElement.
void getCamera(TiXmlElement* e0, 
    Ionflux::GeoUtils::Camera& target, const std::string& elementName = 
Ionflux::GeoUtils::Camera::XML_ELEMENT_NAME);

/// Create new Camera from TiXmlElement.
Ionflux::GeoUtils::Camera* createCamera(TiXmlElement* e0, const 
std::string& elementName = Ionflux::GeoUtils::Camera::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Initialize Camera from TiXmlElement.
template<>
void getObject0<Ionflux::GeoUtils::Camera>(TiXmlElement* e0, 
Ionflux::GeoUtils::Camera& target, const std::string& elementName);

}

}

}


/** \file xmlutils_private.hpp
 * \brief XML utility functions (header).
 */
#endif
