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
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "geoutils/xmlutils.hpp"

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

// public member constants
const unsigned int Face::VERTEX_INDEX_NONE = UINT_MAX;

// run-time type information instance constants
const FaceClassInfo Face::faceClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Face::CLASS_INFO = &Face::faceClassInfo;

const std::string Face::XML_ELEMENT_NAME = "face";

Face::Face()
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, Ionflux::GeoUtils::Vector3::ZERO, ""), tangent(0), normal(0), binormal(0), polygon(0), vertexSource(0), faceData(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Face::Face(const Ionflux::GeoUtils::Face& other)
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, Ionflux::GeoUtils::Vector3::ZERO, ""), tangent(0), normal(0), binormal(0), polygon(0), vertexSource(0), faceData(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Face::Face(const Ionflux::ObjectBase::UIntVector* initVerts, 
Ionflux::GeoUtils::Vertex3Set* initVertexSource, 
Ionflux::GeoUtils::FaceData* initUV, Ionflux::GeoUtils::FaceData* 
initVertexColors)
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, 
Ionflux::GeoUtils::Vector3::ZERO, ""), tangent(0), normal(0), binormal(0), 
polygon(0), vertexSource(initVertexSource), faceData(0)
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
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, 
Ionflux::GeoUtils::Vector3::ZERO, ""), tangent(0), normal(0), binormal(0), 
polygon(0), vertexSource(initVertexSource), faceData(0)
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
	clearVertices();
	clear();
}

void Face::recalculateBounds()
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "recalculateBounds", "Vertex source");
	TransformableObject::recalculateBounds();
	Polygon3* p0 = getPolygon();
	*boundsCache = p0->getBounds();
	bounds = *boundsCache;
}

void Face::copyVertices()
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "copyVertices", "Vertex source");
	setVertexSource(&(vertexSource->duplicate()));
}

void Face::update()
{
	if ((vertexSource == 0) 
	    || (vertices.size() == 0))
	    return;
	clearTangentSpace();
	clearPolygon();
	recalculateBounds();
	updateRadiusAndCenter();
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

void Face::clearPolygon()
{
	if (polygon != 0)
	    removeLocalRef(polygon);
	polygon = 0;
}

void Face::clear()
{
	vertices.clear();
	setVertexSource(0);
	setFaceData(0);
	clearTangentSpace();
	clearPolygon();
	BoxBoundsItem::clear();
	TransformableObject::clear();
}

void Face::addVertices(unsigned int v0, unsigned int v1, unsigned int v2, 
unsigned int v3)
{
	addVertex(v0);
	addVertex(v1);
	addVertex(v2);
	if (v3 != VERTEX_INDEX_NONE)
	    addVertex(v3);
}

Ionflux::GeoUtils::VectorSet* 
Face::addFaceData(Ionflux::GeoUtils::FaceData* newFaceData)
{
	if (faceData == 0)
	    faceData = VectorSetSet::create();
	faceData->addVectorSet(newFaceData);
	return newFaceData;
}

Ionflux::GeoUtils::VectorSet* 
Face::addFaceData(Ionflux::GeoUtils::FaceDataTypeID dataType)
{
	FaceData* newData = FaceData::create(dataType);
	addFaceData(newData);
	return newData;
}

Ionflux::GeoUtils::VectorSet* 
Face::addFaceData(Ionflux::GeoUtils::FaceDataTypeID dataType, 
Ionflux::GeoUtils::Vector* v0, Ionflux::GeoUtils::Vector* v1, 
Ionflux::GeoUtils::Vector* v2, Ionflux::GeoUtils::Vector* v3)
{
	FaceData* newData = FaceData::create(dataType);
	unsigned int numNonNull = 0;
	if (v0 != 0)
	{
	    newData->addVector(v0);
	    numNonNull++;
	}
	if (v1 != 0)
	{
	    newData->addVector(v1);
	    numNonNull++;
	}
	if (v2 != 0)
	{
	    newData->addVector(v2);
	    numNonNull++;
	}
	if (v3 != 0)
	{
	    newData->addVector(v3);
	    numNonNull++;
	}
	unsigned int expected = getNumVertices();
	if (numNonNull < expected)
	{
	    std::ostringstream status;
	    status << "Not enough input vectors for face data (" 
	        << FaceData::getTypeIDString(dataType) << ", expected " 
	        << expected << ", have " << numNonNull << ")";
	    throw GeoUtilsError(getErrorString(status.str(), "addFaceData"));
	}
	addFaceData(newData);
	return newData;
}

Ionflux::GeoUtils::VectorSet* Face::addTexCoords(Ionflux::GeoUtils::Vector*
v0, Ionflux::GeoUtils::Vector* v1, Ionflux::GeoUtils::Vector* v2, 
Ionflux::GeoUtils::Vector* v3)
{
	// TODO: Implementation.
	return addFaceData(FaceData::TYPE_TEX_COORD, v0, v1, v2, v3);
}

Ionflux::GeoUtils::VectorSet* 
Face::addVertexColors(Ionflux::GeoUtils::Vector* v0, 
Ionflux::GeoUtils::Vector* v1, Ionflux::GeoUtils::Vector* v2, 
Ionflux::GeoUtils::Vector* v3)
{
	// TODO: Implementation.
	return addFaceData(FaceData::TYPE_VERTEX_COLOR, v0, v1, v2, v3);
}

Ionflux::GeoUtils::VectorSet* 
Face::addVertexNormals(Ionflux::GeoUtils::Vector* v0, 
Ionflux::GeoUtils::Vector* v1, Ionflux::GeoUtils::Vector* v2, 
Ionflux::GeoUtils::Vector* v3)
{
	// TODO: Implementation.
	return addFaceData(FaceData::TYPE_VERTEX_NORMAL, v0, v1, v2, v3);
}

void Face::getFaceDataByType(Ionflux::GeoUtils::FaceDataTypeID dataType, 
Ionflux::GeoUtils::VectorSetSet& target)
{
	if (faceData == 0)
	    return;
	for (unsigned int i = 0; i < faceData->getNumVectorSets(); i++)
	{
	    FaceData* cfd = FaceData::upcast(faceData->getVectorSet(i));
	    if ((cfd != 0) 
	        && cfd->hasType(dataType))
	        target.addVectorSet(cfd);
	}
}

Ionflux::GeoUtils::FaceData* 
Face::getFaceDataByType0(Ionflux::GeoUtils::FaceDataTypeID dataType, 
unsigned int index)
{
	if (faceData == 0)
	    return 0;
	FaceData* result = 0;
	unsigned int i = 0;
	unsigned int k = 0;
	while ((i < faceData->getNumVectorSets()) 
	    && (result == 0))
	{
	    FaceData* cfd = FaceData::upcast(faceData->getVectorSet(i));
	    if ((cfd != 0) 
	        && cfd->hasType(dataType))
	    {
	        if (k == index)
	            result = cfd;
	        else
	            k++;
	    }
	    i++;
	}
	return result;
}

void Face::getTexCoords(Ionflux::GeoUtils::VectorSetSet& target)
{
	getFaceDataByType(FaceData::TYPE_TEX_COORD, target);
}

Ionflux::GeoUtils::FaceData* Face::getTexCoords0(unsigned int index)
{
	// TODO: Implementation.
	return getFaceDataByType0(FaceData::TYPE_TEX_COORD, index);;
}

void Face::getVertexColors(Ionflux::GeoUtils::VectorSetSet& target)
{
	getFaceDataByType(FaceData::TYPE_VERTEX_COLOR, target);
}

Ionflux::GeoUtils::FaceData* Face::getVertexColors0(unsigned int index)
{
	// TODO: Implementation.
	return getFaceDataByType0(FaceData::TYPE_VERTEX_COLOR, index);;
}

void Face::getVertexNormals(Ionflux::GeoUtils::VectorSetSet& target)
{
	getFaceDataByType(FaceData::TYPE_VERTEX_NORMAL, target);
}

Ionflux::GeoUtils::FaceData* Face::getVertexNormals0(unsigned int index)
{
	// TODO: Implementation.
	return getFaceDataByType0(FaceData::TYPE_VERTEX_NORMAL, index);;
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

Ionflux::GeoUtils::Polygon3* Face::getPolygon()
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "getPolygon", "Vertex source");
	if (polygon != 0)
	    return polygon;
	polygon = Polygon3::create();
	addLocalRef(polygon);
	polygon->copyTransform(*vertexSource);
	for (UIntVector::iterator i = vertices.begin(); i != vertices.end(); i++)
	    polygon->addVertex(vertexSource->getVertex(*i)->copy());
	polygon->createEdges();
	if (useTransform())
	    polygon->transform(*getTransformMatrix());
	if (useVI())
	    polygon->transformVI(*getViewMatrix(), getImageMatrix());
	return polygon;
}

bool Face::checkLineInner(const Ionflux::GeoUtils::Line3& line, double t)
{
	Polygon3* p = getPolygon();
	bool result = line.intersectionInPoly(*p, t);
	return result;
}

int Face::checkPlaneInner(const Ionflux::GeoUtils::Plane3& plane, double t)
{
	Polygon3* p = getPolygon();
	bool e0 = true;
	int c0 = 0;
	int c1 = 1;
	for (unsigned int i = 0; i < p->getNumVertices(); i++)
	{
	    double d = p->getVertex(i)->distanceToPlane(plane);
	    if (lt(d, 0., t))
	        c1 = -1;
	    else
	    if (gt(d, 0., t))
	        c1 = 1;
	    else
	        c1 = 0;
	    if (e0)
	    {
	        // Initialize comparison value on first iteration.
	        c0 = c1;
	        e0 = false;
	    }
	    else 
	    {
	        /* If there are two vertices on opposite sides of the plane, 
	           there is some intersection for this face. */
	        if (c0 != c1)
	            return 0;
	    }
	}
	return c0;
}

int Face::checkSphereInner(const Ionflux::GeoUtils::Sphere3& sphere, double
t)
{
	Polygon3* p = getPolygon();
	Plane3 pl0 = p->getPlane();
	// Check planarity of the face.
	double d0 = 0.;
	for (unsigned int i = 0; i < p->getNumVertices(); i++)
	{
	    double d0 = p->getVertex(i)->distanceToPlane(pl0);
	    if (!eq(d0, 0., t))
	    {
	        // Face is not planar, we have to stick with the bounding box.
	        return checkSphere(sphere, t);
	    }
	}
	// Polygon is planar.
	Vertex3 sp = Vertex3(sphere.getP());
	d0 = sp.distanceToPlane(pl0);
	double sr = sphere.getR();
	if (gt(d0, sr, t))
	{
	    /* Face is outside the sphere, since the minimum distance 
	       between the face and the sphere center is greater than the 
	       sphere radius. */
	    return 1;
	}
	// There may be some intersection, check all vertices.
	int c0 = 0;
	int c1 = 0;
	bool e0 = true;
	for (unsigned int i = 0; i < p->getNumVertices(); i++)
	{
	    double d = (p->getVertex(i)->getVector() - sphere.getP()).norm();
	    if (lt(d, sr, t))
	        c1 = -1;
	    else
	    if (gt(d, sr, t))
	        c1 = 1;
	    else
	        c1 = 0;
	    if (e0)
	    {
	        // Initialize comparison value on first iteration.
	        c0 = c1;
	        e0 = false;
	    }
	    else 
	    {
	        /* If there are two vertices on opposite sides of the sphere, 
	           there is some intersection for this face. */
	        if (c0 != c1)
	            return 0;
	    }
	}
	return c0;
}

int Face::checkBoxInner(const Ionflux::GeoUtils::BoxBoundsItem& other, 
double t)
{
	Polygon3* p = getPolygon();
	if (!p->isPlanar())
	    // Face is not planar, we have to stick with the bounding box.
	    return checkBox(other, t);
	// Polygon is planar.
	Plane3 pl0 = p->getPlane();
	Vertex3 bc = Vertex3(other.getCenter());
	double d0 = bc.distanceToPlane(pl0);
	double br = other.getRadius();
	if (gt(d0, br, t))
	{
	    /* Face is outside the box, since the minimum distance 
	       between the face and the box center is greater than the 
	       radius of the bounding sphere of the box. */
	    return 1;
	}
	// There may be some intersection, check all vertices.
	int c0 = 0;
	int c1 = 0;
	bool e0 = true;
	Range3 r0 = other.getBounds();
	for (unsigned int i = 0; i < p->getNumVertices(); i++)
	{
	    Range3 r1(p->getVertex(i)->getVector());
	    RangeCompResult rcs0 = r0.compare(r1, t);
	    if (rcs0 == RANGE_FIRST_CONTAINS)
	        c1 = -1;
	    else
	    if (rcs0 == RANGE_DISJOINT)
	        c1 = 1;
	    else
	        c1 = 0;
	    if (e0)
	    {
	        // Initialize comparison value on first iteration.
	        c0 = c1;
	        e0 = false;
	    }
	    else 
	    {
	        /* If there are two vertices on opposite sides of the box, 
	           there is some intersection for this face. */
	        if (c0 != c1)
	            return 0;
	    }
	}
	return c0;
}

Ionflux::GeoUtils::FaceVector Face::getTris()
{
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source is not set.");
	if (vertices.size() != 4)
	    throw GeoUtilsError("Face is not a quad.");
	FaceVector result;
	UIntVector v0;
	v0.push_back(vertices[0]);
	v0.push_back(vertices[1]);
	v0.push_back(vertices[2]);
	UIntVector v1;
	v1.push_back(vertices[0]);
	v1.push_back(vertices[2]);
	v1.push_back(vertices[3]);
	FaceData* uv0 = 0;
	FaceData* uv1 = 0;
	FaceData* uv = getTexCoords0();
	if ((uv != 0) 
	    && (uv->getNumVectors() == vertices.size()))
	{
	    uv0 = FaceData::create();
	    uv0->addVector(Ionflux::ObjectBase::nullPointerCheck(
	        uv->getVector(0), this, "Texture coordinate vector")->copy());
	    uv0->addVector(Ionflux::ObjectBase::nullPointerCheck(
	        uv->getVector(1), this, "Texture coordinate vector")->copy());
	    uv0->addVector(Ionflux::ObjectBase::nullPointerCheck(
	        uv->getVector(2), this, "Texture coordinate vector")->copy());
	    uv1 = FaceData::create();
	    uv1->addVector(Ionflux::ObjectBase::nullPointerCheck(
	        uv->getVector(0), this, "Texture coordinate vector")->copy());
	    uv1->addVector(Ionflux::ObjectBase::nullPointerCheck(
	        uv->getVector(2), this, "Texture coordinate vector")->copy());
	    uv1->addVector(Ionflux::ObjectBase::nullPointerCheck(
	        uv->getVector(3), this, "Texture coordinate vector")->copy());
	}
	Face* f0 = Face::create(&v0, vertexSource, uv0);
	result.push_back(f0);
	Face* f1 = Face::create(&v1, vertexSource, uv1);
	result.push_back(f1);
	return result;
}

bool Face::isPlanar(double t)
{
	Polygon3* p = getPolygon();
	return p->isPlanar(t);
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

bool Face::operator==(const Ionflux::GeoUtils::Face& other) const
{
	if (vertices.size() != other.vertices.size()) 
	    return false;
	if (vertexSource != other.vertexSource)
	    return false;
	bool result = true;
	unsigned int i = 0;
	while (result 
	    && (i < vertices.size()))
	{
	    if (vertices[i] != other.vertices[i])
	        result = false;
	    i++;
	}
	if ((faceData == 0) 
	    && (other.faceData == 0))
	    return result;
	if ((faceData == 0) 
	    && (other.faceData != 0))
	    return false;
	if ((faceData != 0) 
	    && (other.faceData == 0))
	    return false;
	if (*faceData != *other.faceData)
	    return false;
	return result;
}

bool Face::operator!=(const Ionflux::GeoUtils::Face& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

bool Face::isBackface(const Ionflux::GeoUtils::Vector3& front)
{
	if (normal == 0)
	    getNormal();
	if (normal->angle(front) > (0.5 * M_PI))
	    return true;
	return false;
}

Ionflux::GeoUtils::Vector3 Face::getBarycenter()
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "getBarycenter", "Vertex source");
	Polygon3* p0 = getPolygon();
	Vector3 b0 = p0->getBarycenter();
	return b0;
}

Ionflux::GeoUtils::Range3 Face::getBounds()
{
	bounds = TransformableObject::getBounds();
	return bounds;
}

void Face::applyTransform(bool recursive)
{
	log(IFLogMessage("Cannot apply transform to face "
	    "(should be applied to vertex source instead).", VL_WARNING, 
	    this, "applyTransform"));
	clearTransformations();
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

std::string Face::getValueString() const
{
	std::ostringstream status;
	bool e0 = true;
	// vertices
	status << "verts: ";
	unsigned int numVerts = vertices.size();
	if (numVerts > 0)
	{
	    status << "(";
	    for (UIntVector::const_iterator i = vertices.begin(); 
	        i != vertices.end(); i++)
	    {
	        if (!e0)
	            status << ", ";
	        else
	            e0 = false;
	        status << *i;
	    }
	    status << ")";
	} else
	    status << "<none>";
	// face data
	if (faceData != 0)
	{
	    status << "; faceData: [" 
	        << faceData->getValueString() << "]";
	}
	// transformable object data
	std::string ts0(TransformableObject::getValueString());
	if (ts0.size() > 0)
	    status << "; " << ts0;
	return status.str();
}

std::string Face::getXMLDataVertices_legacy() const
{
	ostringstream d0;
	bool first = true;
	for (UIntVector::const_iterator i = vertices.begin(); 
	    i != vertices.end(); i++)
	{
	    if (!first)
	        d0 << " ";
	    else
	        first = false;
	    d0 << (*i);
	}
	return d0.str();
}

std::string Face::getXMLDataTexCoords_legacy() const
{
	// NOTE: Not implemented, use the new XML I/O API instead.
	return "";
}

std::string Face::getXML_legacy() const
{
	ostringstream d0;
	d0 << "<f d=\"" << getXMLDataVertices_legacy() << "\" uv=\"" 
	    << getXMLDataTexCoords_legacy() << "\" />";
	return d0.str();
}

void Face::setFromXMLData_legacy(const std::string& vertexData, const 
std::string& texCoordData)
{
	Ionflux::ObjectBase::StringVector parts0;
	explode(vertexData, " ", parts0);
	for (Ionflux::ObjectBase::StringVector::const_iterator i = 
	    parts0.begin(); i != parts0.end(); i++)
	    addVertex(strtol((*i).c_str(), 0, 10));
}

unsigned int Face::getNumVertices() const
{
    return vertices.size();
}

unsigned int Face::getVertex(unsigned int elementIndex) const
{
    if (elementIndex < vertices.size())
		return vertices[elementIndex];
	return 0;
}

int Face::findVertex(unsigned int needle, unsigned int occurence) const
{
    bool found = false;
	unsigned int currentVertex = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < vertices.size()))
	{
		currentVertex = vertices[i];
		if (currentVertex == needle)
        {
            if (occurence == 1)
			    found = true;
            else
                occurence--;
		} else
			i++;
	}
	if (found)
        return i;
	return -1;
}

std::vector<unsigned int>& Face::getVertices()
{
    return vertices;
}

void Face::addVertex(unsigned int addElement)
{
	vertices.push_back(addElement);
}

unsigned int Face::addVertex()
{
	unsigned int o0 = 0;
	addVertex(o0);
	return o0;
}

void Face::addVertices(const std::vector<unsigned int>& newVertices)
{
	for (std::vector<unsigned int>::const_iterator i = newVertices.begin(); 
	    i != newVertices.end(); i++)
	    addVertex(*i);
}

void Face::addVertices(Ionflux::GeoUtils::Face* newVertices)
{
	for (unsigned int i = 0; 
	    i < newVertices->getNumVertices(); i++)
	    addVertex(newVertices->getVertex(i));
}

void Face::removeVertex(unsigned int removeElement)
{
    bool found = false;
	unsigned int currentVertex = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < vertices.size()))
	{
		currentVertex = vertices[i];
		if (currentVertex == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		vertices.erase(vertices.begin() + i);
	}
}

void Face::removeVertexIndex(unsigned int removeIndex)
{
    if (removeIndex > vertices.size())
        return;
    vertices.erase(vertices.begin() + removeIndex);
}

void Face::clearVertices()
{
    vertices.clear();
}

void Face::setVertexSource(Ionflux::GeoUtils::Vertex3Set* newVertexSource)
{
	vertexSource = newVertexSource;
}

Ionflux::GeoUtils::Vertex3Set* Face::getVertexSource() const
{
    return vertexSource;
}

void Face::setFaceData(Ionflux::GeoUtils::VectorSetSet* newFaceData)
{
	faceData = newFaceData;
}

Ionflux::GeoUtils::VectorSetSet* Face::getFaceData() const
{
    return faceData;
}

Ionflux::GeoUtils::Face& Face::operator=(const Ionflux::GeoUtils::Face& 
other)
{
    clear();
    for (UIntVector::const_iterator i = other.vertices.begin(); 
        i != other.vertices.end(); i++)
        vertices.push_back(*i);
    setFaceData(other.faceData->copy());
    TransformableObject::operator=(other);
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

std::string Face::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Face::getXMLAttributeData() const
{
	std::string a0(Ionflux::GeoUtils::TransformableObject::getXMLAttributeData());
	std::ostringstream d0;
	if (a0.size() > 0)
	    d0 << a0;
	return d0.str();
}

void Face::getXMLChildData(std::string& target, unsigned int indentLevel) 
const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::GeoUtils::TransformableObject::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	std::string iws0 = Ionflux::ObjectBase::getIndent(indentLevel);
	bool haveBCData = false;
	if (d0.str().size() > 0)
	    haveBCData = true;
	bool xcFirst = true;
	if (!xcFirst || haveBCData)
	    d0 << "\n";
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0(vertices, "", 
        indentLevel, "pname=\"vertices\"");
    xcFirst = false;
    if (faceData != 0)
    {
        if (!xcFirst || haveBCData)
            d0 << "\n";
	    d0 << faceData->getXML0(indentLevel, "pname=\"fds\"");
	    xcFirst = false;
    }
	target = d0.str();
}

void Face::loadFromXMLFile(std::string& fileName)
{
	std::string data;
	Ionflux::ObjectBase::readFile(fileName, data);
	Ionflux::GeoUtils::XMLUtils::getFace(data, *this);
}

}

}

/** \file Face.cpp
 * \brief Mesh face implementation.
 */
