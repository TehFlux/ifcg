/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Face.cpp                        Mesh face (implementation).
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

#include "geoutils/Face.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "ifobject/objectutils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Vertex3Set.hpp"
#include "geoutils/VectorSetSet.hpp"
#include "geoutils/FaceData.hpp"
#include "geoutils/NFaceSet.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/FaceXMLFactory.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

FaceClassInfo::FaceClassInfo()
{
	name = "Face";
	desc = "Mesh face";
}

FaceClassInfo::~FaceClassInfo()
{
}

// run-time type information instance constants
const FaceClassInfo Face::faceClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Face::CLASS_INFO = &Face::faceClassInfo;

const std::string Face::XML_ELEMENT_NAME = "face";

Face::Face()
: tangent(0), normal(0), binormal(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Face::Face(const Ionflux::GeoUtils::Face& other)
: tangent(0), normal(0), binormal(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Face::Face(const Ionflux::ObjectBase::UIntVector* initVerts, 
Ionflux::GeoUtils::Vertex3Set* initVertexSource, 
Ionflux::GeoUtils::FaceData* initUV, Ionflux::GeoUtils::FaceData* 
initVertexColors)
: tangent(0), normal(0), binormal(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initVerts != 0)
	    addVertices(*initVerts);
	if (initVertexSource != 0)
	    setVertexSource(initVertexSource);
	if (initUV != 0)
	    addFaceData(initUV);
	if (initVertexColors != 0)
	    addFaceData(initVertexColors);
	update();
}

Face::Face(unsigned int v0, unsigned int v1, unsigned int v2, unsigned int 
v3, Ionflux::GeoUtils::Vertex3Set* initVertexSource, 
Ionflux::GeoUtils::FaceData* initUV, Ionflux::GeoUtils::FaceData* 
initVertexColors)
: tangent(0), normal(0), binormal(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addVertices(v0, v1, v2, v3);
	if (initVertexSource != 0)
	    setVertexSource(initVertexSource);
	if (initUV != 0)
	    addFaceData(initUV);
	if (initVertexColors != 0)
	    addFaceData(initVertexColors);
	update();
}

Face::~Face()
{
	clear();
}

void Face::update()
{
	NFace::update();
	clearTangentSpace();
}

void Face::clearTangentSpace()
{
	if (tangent != 0)
	    removeLocalRef(tangent);
	tangent = 0;
	if (normal != 0)
	    removeLocalRef(normal);
	normal = 0;
	if (binormal != 0)
	    removeLocalRef(binormal);
	binormal = 0;
}

void Face::clear()
{
	NFace::clear();
	clearTangentSpace();
}

void Face::setFaceVertexNormals()
{
	Vector3 n0 = getNormal();
	FaceData* vn0 = getVertexNormals0();
	if (vn0 == 0)
	{
	    vn0 = FaceData::upcast(
	        addFaceData(FaceData::TYPE_VERTEX_NORMAL));
	}
	vn0->clearVectors();
	unsigned int numVerts = getNumVertices();
	for (unsigned int i = 0; i < numVerts; i++)
	    vn0->addVector(n0.copy());
}

void Face::setVertexColors(const Ionflux::GeoUtils::Vector4& color)
{
	FaceData* vc0 = getVertexColors0();
	if (vc0 == 0)
	{
	    vc0 = FaceData::upcast(
	        addFaceData(FaceData::TYPE_VERTEX_COLOR));
	}
	vc0->clearVectors();
	unsigned int numVerts = getNumVertices();
	for (unsigned int i = 0; i < numVerts; i++)
	{
	    vc0->addVector(color.copy());
	}
}

Ionflux::GeoUtils::Vector3 Face::getTangent()
{
	if (tangent != 0)
	    return *tangent;
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "getTangent", "Vertex source");
	if (vertices.size() < 3)
	    throw GeoUtilsError(getErrorString(
	        "Face does not have enough vertices.", "getTangent"));
	Vertex3* pv0 = vertexSource->getVertex(vertices[0]);
	Vector3 p0 = pv0->getVector();
	Vertex3* pv1 = vertexSource->getVertex(vertices[1]);
	Vector3 p1 = pv1->getVector();
	tangent = Vector3::create();
	addLocalRef(tangent);
	Vector3 b = getBinormal();
	FaceData* uv = getTexCoords0();
	if ((uv == 0) 
	    || (uv->getNumVectors() < 3))
	{
	    *tangent = b.ortho(p1 - p0).normalize();
	    return *tangent;
	}
	// Calculate tangent vector according to texture coordinates.
	Vector* uv0 = Ionflux::ObjectBase::nullPointerCheck(
	    uv->getVector(0), this, "getTangent", "Texture coordinate vector");
	Vector* uv1 = Ionflux::ObjectBase::nullPointerCheck(
	    uv->getVector(1), this, "getTangent", "Texture coordinate vector");
	double u0 = uv0->getElement(0);
	double v0 = uv0->getElement(1);
	double u1 = uv1->getElement(0);
	double v1 = uv1->getElement(1);
	*tangent = 1. / (u1 - u0) * ((p1 - p0) - (v1 - v0) * b);
	return *tangent;
}

Ionflux::GeoUtils::Vector3 Face::getBinormal()
{
	if (binormal != 0)
	    return *binormal;
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "getBinormal", "Vertex source");
	if (vertices.size() < 3)
	    throw GeoUtilsError("Face does not have enough vertices.");
	binormal = Vector3::create();
	addLocalRef(binormal);
	Vertex3* pv0 = vertexSource->getVertex(vertices[0]);
	Vector3 p0 = pv0->getVector();
	Vertex3* pv1 = vertexSource->getVertex(vertices[1]);
	Vector3 p1 = pv1->getVector();
	Vertex3* pv2 = vertexSource->getVertex(vertices[2]);
	Vector3 p2 = pv2->getVector();
	FaceData* uv = getTexCoords0();
	if ((uv == 0) 
	    || (uv->getNumVectors() < 3))
	{
	    *binormal = (p2 - p0).normalize();
	    return *binormal;
	}
	// Calculate binormal vector according to texture coordinates.
	Vector* uv0 = Ionflux::ObjectBase::nullPointerCheck(
	    uv->getVector(0), this, "getBinormal", "Texture coordinate vector");
	Vector* uv1 = Ionflux::ObjectBase::nullPointerCheck(
	    uv->getVector(1), this, "getBinormal", "Texture coordinate vector");
	Vector* uv2 = Ionflux::ObjectBase::nullPointerCheck(
	    uv->getVector(2), this, "getBinormal", "Texture coordinate vector");
	double u0 = uv0->getElement(0);
	double v0 = uv0->getElement(1);
	double u1 = uv1->getElement(0);
	double v1 = uv1->getElement(1);
	double u2 = uv2->getElement(0);
	double v2 = uv2->getElement(1);
	*binormal = 1. / ((v2 - v0) * (u1 - u0) 
	    - (v1 - v0) * (u2 - u0)) 
	    * ((u1 - u0) * (p2 - p0) - (u2 - u0) * (p1 - p0));
	return *binormal;
}

Ionflux::GeoUtils::Vector3 Face::getNormal()
{
	if (normal != 0)
	    return *normal;
	Vector3 t = getTangent();
	Vector3 b = getBinormal();
	normal = Vector3::create();
	addLocalRef(normal);
	*normal = t.cross(b).normalize();
	return *normal;
}

Ionflux::GeoUtils::Matrix3 Face::getTangentBase()
{
	Matrix3 m;
	m.setC0(getTangent());
	m.setC1(getBinormal());
	m.setC2(getNormal());
	return m;
}

void Face::makePlanar(double p, double t)
{
	if (isPlanar(t))
	    return;
	if (vertexSource == 0)
	    throw GeoUtilsError(getErrorString("Vertex source is not set.", 
	        "makePlanar"));
	if (vertices.size() < 3)
	    throw GeoUtilsError(getErrorString(
	        "Face does not have enough vertices.", "makePlanar"));
	Vertex3Set vs;
	for (UIntVector::iterator i = vertices.begin(); i != vertices.end(); i++)
	    vs.addVertex(vertexSource->getVertex(*i)->copy());
	Plane3 pl = vs.getPlaneFit();
	Vector3 n0 = pl.getNormal();
	for (UIntVector::iterator i = vertices.begin(); i != vertices.end(); i++)
	{
	    Vertex3* v0 = vertexSource->getVertex(*i);
	    double d0 = v0->distanceToPlane(pl);
	    Vector3 offset = n0 * (-d0 * p);
	    v0->translate(offset);
	    v0->applyTransform();
	}
	update();
}

bool Face::isBackface(const Ionflux::GeoUtils::Vector3& front)
{
	if (normal == 0)
	    getNormal();
	if (normal->angle(front) > (0.5 * M_PI))
	    return true;
	return false;
}

void Face::getTris(Ionflux::GeoUtils::FaceVector& target)
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "getTris", "Vertex source");
	if (isTri())
	{
	    target.push_back(copy());
	    return;
	}
	if (!isQuad())
	{
	    throw GeoUtilsError(getErrorString(
	        "Face is not a quad.", "getTris"));
	}
	FaceVector result;
	UIntVector v0;
	v0.push_back(vertices[0]);
	v0.push_back(vertices[1]);
	v0.push_back(vertices[2]);
	UIntVector v1;
	v1.push_back(vertices[0]);
	v1.push_back(vertices[2]);
	v1.push_back(vertices[3]);
	UIntVector iv0;
	iv0.push_back(0);
	iv0.push_back(1);
	iv0.push_back(2);
	UIntVector iv1;
	iv1.push_back(0);
	iv1.push_back(2);
	iv1.push_back(3);
	Face* f0 = Face::create(&v0, vertexSource);
	Face* f1 = Face::create(&v1, vertexSource);
	if (faceData != 0)
	{
	    // copy face data
	    VectorSetSet* nfd0 = VectorSetSet::create();
	    VectorSetSet* nfd1 = VectorSetSet::create();
	    getFaceDataByVertex(iv0, *nfd0);
	    getFaceDataByVertex(iv1, *nfd1);
	    f0->setFaceData(nfd0);
	    f1->setFaceData(nfd1);
	}
	target.push_back(f0);
	target.push_back(f1);
}

Ionflux::GeoUtils::Face& Face::scale(const Ionflux::GeoUtils::Vector3& s)
{
	TransformableObject::scale(s);
	return *this;
}

Ionflux::GeoUtils::Face& Face::translate(const Ionflux::GeoUtils::Vector3& 
t)
{
	TransformableObject::translate(t);
	return *this;
}

Ionflux::GeoUtils::Face& Face::rotate(double phi, Ionflux::GeoUtils::AxisID
axis)
{
	TransformableObject::rotate(phi, axis);
	return *this;
}

Ionflux::GeoUtils::Face& Face::normalize()
{
	TransformableObject::normalize();
	return *this;
}

Ionflux::GeoUtils::Face& Face::center(Ionflux::GeoUtils::CenteringMethod 
method, Ionflux::GeoUtils::Vector3* origin)
{
	TransformableObject::center(method, origin);
	return *this;
}

Ionflux::GeoUtils::Face& Face::transform(const Ionflux::GeoUtils::Matrix4& 
matrix)
{
	log(IFLogMessage("Transforming face.", VL_WARNING, this, 
	    "transform"));
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Face& Face::transform(const Ionflux::GeoUtils::Matrix3& 
matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Face& Face::duplicate()
{
	// TODO: Implementation.
	return *copy();
}

Ionflux::GeoUtils::Face& Face::operator=(const Ionflux::GeoUtils::Face& 
other)
{
    clear();
    for (UIntVector::const_iterator i = other.vertices.begin(); 
        i != other.vertices.end(); i++)
        vertices.push_back(*i);
    NFace::operator=(other);
    update();
	return *this;
}

Ionflux::GeoUtils::Face* Face::copy() const
{
    Face* newFace = create();
    *newFace = *this;
    return newFace;
}

Ionflux::GeoUtils::Face* Face::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Face*>(other);
}

Ionflux::GeoUtils::Face* Face::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Face* newObject = new Face();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Face* Face::create(const 
Ionflux::ObjectBase::UIntVector* initVerts, Ionflux::GeoUtils::Vertex3Set* 
initVertexSource, Ionflux::GeoUtils::FaceData* initUV, 
Ionflux::GeoUtils::FaceData* initVertexColors, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Face* newObject = new Face(initVerts, initVertexSource, initUV, 
    initVertexColors);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Face* Face::create(unsigned int v0, unsigned int v1, 
unsigned int v2, unsigned int v3, Ionflux::GeoUtils::Vertex3Set* 
initVertexSource, Ionflux::GeoUtils::FaceData* initUV, 
Ionflux::GeoUtils::FaceData* initVertexColors, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Face* newObject = new Face(v0, v1, v2, v3, initVertexSource, initUV, 
    initVertexColors);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Face::getMemSize() const
{
    return sizeof *this;
}

std::string Face::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Face::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::GeoUtils::NFace::getXMLAttributeData();
	return d0.str();
}

void Face::getXMLChildData(std::string& target, unsigned int indentLevel) 
const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::GeoUtils::NFace::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void Face::loadFromXMLFile(const std::string& fileName)
{
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, getXMLElementName());
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
Face::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::FaceXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::FaceXMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 0;
        bFac = Ionflux::GeoUtils::NFace::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file Face.cpp
 * \brief Mesh face implementation.
 */
