/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NFace.cpp                       N-face (implementation).
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

#include "geoutils/NFace.hpp"
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
#include "geoutils/xmlio/NFaceXMLFactory.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

NFaceClassInfo::NFaceClassInfo()
{
	name = "NFace";
	desc = "N-face";
}

NFaceClassInfo::~NFaceClassInfo()
{
}

// public member constants
const unsigned int NFace::VERTEX_INDEX_NONE = UINT_MAX;

// run-time type information instance constants
const NFaceClassInfo NFace::nFaceClassInfo;
const Ionflux::ObjectBase::IFClassInfo* NFace::CLASS_INFO = &NFace::nFaceClassInfo;

const std::string NFace::XML_ELEMENT_NAME = "nface";

NFace::NFace()
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, Ionflux::GeoUtils::Vector3::ZERO, ""), polygon(0), vertexSource(0), faceData(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

NFace::NFace(const Ionflux::GeoUtils::NFace& other)
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, Ionflux::GeoUtils::Vector3::ZERO, ""), polygon(0), vertexSource(0), faceData(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

NFace::NFace(const Ionflux::ObjectBase::UIntVector* initVerts, 
Ionflux::GeoUtils::Vertex3Set* initVertexSource, 
Ionflux::GeoUtils::FaceData* initUV, Ionflux::GeoUtils::FaceData* 
initVertexColors)
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, 
Ionflux::GeoUtils::Vector3::ZERO, ""), polygon(0), 
vertexSource(initVertexSource), faceData(0)
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

NFace::NFace(unsigned int v0, unsigned int v1, unsigned int v2, unsigned 
int v3, Ionflux::GeoUtils::Vertex3Set* initVertexSource, 
Ionflux::GeoUtils::FaceData* initUV, Ionflux::GeoUtils::FaceData* 
initVertexColors)
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, 
Ionflux::GeoUtils::Vector3::ZERO, ""), polygon(0), 
vertexSource(initVertexSource), faceData(0)
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

NFace::~NFace()
{
	clearVertices();
	clear();
}

void NFace::recalculateBounds()
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "recalculateBounds", "Vertex source");
	TransformableObject::recalculateBounds();
	Polygon3* p0 = getPolygon();
	*boundsCache = p0->getBounds();
	bounds = *boundsCache;
}

void NFace::copyVertices()
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "copyVertices", "Vertex source");
	setVertexSource(&(vertexSource->duplicate()));
}

void NFace::update()
{
	if ((vertexSource == 0) 
	    || (vertices.size() == 0))
	    return;
	clearPolygon();
	recalculateBounds();
	updateRadiusAndCenter();
}

void NFace::clearPolygon()
{
	if (polygon != 0)
	    removeLocalRef(polygon);
	polygon = 0;
}

void NFace::clear()
{
	vertices.clear();
	setVertexSource(0);
	setFaceData(0);
	clearPolygon();
	BoxBoundsItem::clear();
	TransformableObject::clear();
}

void NFace::addVertices(unsigned int v0, unsigned int v1, unsigned int v2, 
unsigned int v3)
{
	addVertex(v0);
	if (v1 != VERTEX_INDEX_NONE)
	    addVertex(v1);
	if (v2 != VERTEX_INDEX_NONE)
	    addVertex(v2);
	if (v3 != VERTEX_INDEX_NONE)
	    addVertex(v3);
}

Ionflux::GeoUtils::VectorSet* 
NFace::addFaceData(Ionflux::GeoUtils::FaceData* newFaceData)
{
	if (faceData == 0)
	    faceData = VectorSetSet::create();
	faceData->addVectorSet(newFaceData);
	return newFaceData;
}

Ionflux::GeoUtils::VectorSet* 
NFace::addFaceData(Ionflux::GeoUtils::FaceDataTypeID dataType)
{
	FaceData* newData = FaceData::create(dataType);
	addFaceData(newData);
	return newData;
}

Ionflux::GeoUtils::VectorSet* 
NFace::addFaceData(Ionflux::GeoUtils::FaceDataTypeID dataType, 
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

Ionflux::GeoUtils::VectorSet* 
NFace::addTexCoords(Ionflux::GeoUtils::Vector* v0, 
Ionflux::GeoUtils::Vector* v1, Ionflux::GeoUtils::Vector* v2, 
Ionflux::GeoUtils::Vector* v3)
{
	// TODO: Implementation.
	return addFaceData(FaceData::TYPE_TEX_COORD, v0, v1, v2, v3);
}

Ionflux::GeoUtils::VectorSet* 
NFace::addVertexColors(Ionflux::GeoUtils::Vector* v0, 
Ionflux::GeoUtils::Vector* v1, Ionflux::GeoUtils::Vector* v2, 
Ionflux::GeoUtils::Vector* v3)
{
	// TODO: Implementation.
	return addFaceData(FaceData::TYPE_VERTEX_COLOR, v0, v1, v2, v3);
}

Ionflux::GeoUtils::VectorSet* 
NFace::addVertexNormals(Ionflux::GeoUtils::Vector* v0, 
Ionflux::GeoUtils::Vector* v1, Ionflux::GeoUtils::Vector* v2, 
Ionflux::GeoUtils::Vector* v3)
{
	// TODO: Implementation.
	return addFaceData(FaceData::TYPE_VERTEX_NORMAL, v0, v1, v2, v3);
}

void NFace::getFaceDataByType(Ionflux::GeoUtils::FaceDataTypeID dataType, 
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
NFace::getFaceDataByType0(Ionflux::GeoUtils::FaceDataTypeID dataType, 
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

void NFace::getTexCoords(Ionflux::GeoUtils::VectorSetSet& target)
{
	getFaceDataByType(FaceData::TYPE_TEX_COORD, target);
}

Ionflux::GeoUtils::FaceData* NFace::getTexCoords0(unsigned int index)
{
	// TODO: Implementation.
	return getFaceDataByType0(FaceData::TYPE_TEX_COORD, index);;
}

void NFace::getVertexColors(Ionflux::GeoUtils::VectorSetSet& target)
{
	getFaceDataByType(FaceData::TYPE_VERTEX_COLOR, target);
}

Ionflux::GeoUtils::FaceData* NFace::getVertexColors0(unsigned int index)
{
	// TODO: Implementation.
	return getFaceDataByType0(FaceData::TYPE_VERTEX_COLOR, index);;
}

void NFace::getVertexNormals(Ionflux::GeoUtils::VectorSetSet& target)
{
	getFaceDataByType(FaceData::TYPE_VERTEX_NORMAL, target);
}

Ionflux::GeoUtils::FaceData* NFace::getVertexNormals0(unsigned int index)
{
	// TODO: Implementation.
	return getFaceDataByType0(FaceData::TYPE_VERTEX_NORMAL, index);;
}

void NFace::getFaceDataByVertex(Ionflux::ObjectBase::UIntVector& 
faceVertexIndices, Ionflux::GeoUtils::VectorSetSet& target)
{
	if (faceData == 0)
	    return;
	unsigned int n0 = faceData->getNumVectorSets();
	unsigned int n2 = faceVertexIndices.size();
	if (n2 == 0)
	{
	    throw GeoUtilsError(getErrorString(
	        "Face vertex index vector is empty.", "getFaceDataByVertex"));
	}
	for (unsigned int i = 0; i < n0; i++)
	{
	    FaceData* cfd = FaceData::upcast(faceData->getVectorSet(i));
	    if (cfd != 0)
	    {
	        unsigned int n1 = cfd->getNumVectors();
	        /* <---- DEBUG ----- //
	        std::cerr << "[Face::getFaceDataByVertex] DEBUG: "
	            "number of source face data vectors = " << n1 << std::endl;
	        // ----- DEBUG ----> */
	        VectorVector v0;
	        for (unsigned int k = 0; k < n2; k++)
	        {
	            unsigned int i0 = faceVertexIndices[k];
	            if (i0 < n1)
	            {
	                Vector* cv0 = Ionflux::ObjectBase::nullPointerCheck(
	                    cfd->getVector(i0), this, "getFaceDataByVertex", 
	                        "Face data vector");
	                v0.push_back(cv0->copy());
	            } else
	            {
	                std::ostringstream status;
	                status << "Invalid face vertex index: " << i0;
	                throw GeoUtilsError(getErrorString(status.str(), 
	                    "getFaceDataByVertex"));
	            }
	        }
	        /* <---- DEBUG ----- //
	        std::cerr << "[Face::getFaceDataByVertex] DEBUG: "
	            "number of target face data vectors = " 
	            << v0.size() << std::endl;
	        // ----- DEBUG ----> */
	        FaceData* nfd = FaceData::create(v0, cfd->getDataType());
	        target.addVectorSet(nfd);
	    }
	}
}

Ionflux::GeoUtils::Polygon3* NFace::getPolygon()
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

bool NFace::checkLineInner(const Ionflux::GeoUtils::Line3& line, double t)
{
	Polygon3* p = getPolygon();
	bool result = line.intersectionInPoly(*p, t);
	return result;
}

int NFace::checkPlaneInner(const Ionflux::GeoUtils::Plane3& plane, double 
t)
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

int NFace::checkSphereInner(const Ionflux::GeoUtils::Sphere3& sphere, 
double t)
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

int NFace::checkBoxInner(const Ionflux::GeoUtils::BoxBoundsItem& other, 
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

Ionflux::GeoUtils::Vertex3* NFace::getVertexData(unsigned int index) const
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "getVertexData", "Vertex source");
	return vertexSource->getVertex(getVertex(index));;
}

bool NFace::isPlanar(double t)
{
	Polygon3* p = getPolygon();
	return p->isPlanar(t);
}

bool NFace::isEdge() const
{
	if (vertices.size() == 2)
	    return true;
	return false;
}

bool NFace::isTri() const
{
	if (vertices.size() == 3)
	    return true;
	return false;
}

bool NFace::isQuad() const
{
	if (vertices.size() == 4)
	    return true;
	return false;
}

void NFace::getEdge(Ionflux::GeoUtils::Edge& target) const
{
	if (!isEdge())
	{
	    throw GeoUtilsError(getErrorString(
	        "N-face is not an edge.", "getEdge"));
	}
	target.setV0(getVertex(0));
	target.setV1(getVertex(1));
}

Ionflux::GeoUtils::Edge NFace::getEdge0() const
{
	Edge e0;
	getEdge(e0);
	return e0;
}

void NFace::applyVertexIndexOffset(int offset)
{
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
	    unsigned int cv = vertices[i];
	    if ((offset < 0) 
	        && (static_cast<unsigned int>(-offset) > cv))
	        cv = 0;
	    else
	        cv += offset;
	    vertices[i] = cv;
	}
}

void NFace::getTris(Ionflux::GeoUtils::NFaceVector& target)
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
	        "N-face is not a quad.", "getTris"));
	}
	NFaceVector result;
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
	NFace* f0 = NFace::create(&v0, vertexSource);
	NFace* f1 = NFace::create(&v1, vertexSource);
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

void NFace::getTris(Ionflux::GeoUtils::NFaceSet& target)
{
	NFaceVector fv0;
	getTris(fv0);
	for (NFaceVector::iterator i = fv0.begin(); i!= fv0.end(); i++)
	    target.addNFace(*i);
}

Ionflux::GeoUtils::NFaceVector NFace::getTris0()
{
	NFaceVector result;
	getTris(result);
	return result;
}

void NFace::getEdges(Ionflux::GeoUtils::NFaceVector& target, bool 
copyFaceData)
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "getEdges", "Vertex source");
	unsigned int numVerts = getNumVertices();
	UIntVector vv0;
	for (unsigned int i = 0; i < numVerts; i++)
	{
	    unsigned int i1 = (i + 1) % numVerts;
	    int vi0 = getVertex(i);
	    int vi1 = getVertex(i1);
	    NFace* e0 = NFace::create();
	    e0->setVertexSource(vertexSource);
	    e0->addVertices(vi0, vi1);
	    if (copyFaceData && (faceData != 0))
	    {
	        // copy face data
	        vv0.clear();
	        Ionflux::ObjectBase::addValues(vv0, 2, i, i1);
	        VectorSetSet* fd0 = VectorSetSet::create();
	        getFaceDataByVertex(vv0, *fd0);
	        e0->setFaceData(fd0);
	    }
	    target.push_back(e0);
	}
}

void NFace::getEdges(Ionflux::GeoUtils::NFaceSet& target, bool 
copyFaceData)
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "getEdges", "Vertex source");
	NFaceVector ev0;
	getEdges(ev0, copyFaceData);
	target.addNFaces(ev0);
}

double NFace::getArea()
{
	if (isEdge())
	    return 0.;
	if (isTri())
	{
	    Vector3 v0(getVertexData(0)->getVector());
	    Vector3 v1(getVertexData(1)->getVector());
	    Vector3 v2(getVertexData(2)->getVector());
	    Vector3 e0(v1 - v0);
	    Vector3 e1(v2 - v0);
	    return 0.5 * e0.cross(e1).length();
	}
	double result = 0.;
	NFaceVector tris0;
	getTris(tris0);
	for (NFaceVector::iterator i = tris0.begin(); i != tris0.end(); i++)
	{
	    NFace* nf0 = *i;
	    result += nf0->getArea();
	    delete nf0;
	}
	return result;
}

bool NFace::operator==(const Ionflux::GeoUtils::NFace& other) const
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

bool NFace::operator!=(const Ionflux::GeoUtils::NFace& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

Ionflux::GeoUtils::Vector3 NFace::getBarycenter()
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "getBarycenter", "Vertex source");
	Polygon3* p0 = getPolygon();
	Vector3 b0 = p0->getBarycenter();
	return b0;
}

Ionflux::GeoUtils::Range3 NFace::getBounds()
{
	bounds = TransformableObject::getBounds();
	return bounds;
}

void NFace::applyTransform(bool recursive)
{
	log(IFLogMessage("Cannot apply transform to face "
	    "(should be applied to vertex source instead).", VL_WARNING, 
	    this, "applyTransform"));
	clearTransformations();
}

Ionflux::GeoUtils::NFace& NFace::scale(const Ionflux::GeoUtils::Vector3& s)
{
	TransformableObject::scale(s);
	return *this;
}

Ionflux::GeoUtils::NFace& NFace::translate(const 
Ionflux::GeoUtils::Vector3& t)
{
	TransformableObject::translate(t);
	return *this;
}

Ionflux::GeoUtils::NFace& NFace::rotate(double phi, 
Ionflux::GeoUtils::AxisID axis)
{
	TransformableObject::rotate(phi, axis);
	return *this;
}

Ionflux::GeoUtils::NFace& NFace::normalize()
{
	TransformableObject::normalize();
	return *this;
}

Ionflux::GeoUtils::NFace& NFace::center(Ionflux::GeoUtils::CenteringMethod 
method, Ionflux::GeoUtils::Vector3* origin)
{
	TransformableObject::center(method, origin);
	return *this;
}

Ionflux::GeoUtils::NFace& NFace::transform(const 
Ionflux::GeoUtils::Matrix4& matrix)
{
	log(IFLogMessage("Transforming face.", VL_WARNING, this, 
	    "transform"));
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::NFace& NFace::transform(const 
Ionflux::GeoUtils::Matrix3& matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::NFace& NFace::duplicate()
{
	// TODO: Implementation.
	return *copy();
}

std::string NFace::getValueString() const
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

unsigned int NFace::getNumVertices() const
{
    return vertices.size();
}

unsigned int NFace::getVertex(unsigned int elementIndex) const
{
    if (elementIndex < vertices.size())
		return vertices[elementIndex];
	return 0;
}

int NFace::findVertex(unsigned int needle, unsigned int occurence) const
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

std::vector<unsigned int>& NFace::getVertices()
{
    return vertices;
}

void NFace::addVertex(unsigned int addElement)
{
	vertices.push_back(addElement);
}

unsigned int NFace::addVertex()
{
	unsigned int o0 = 0;
	addVertex(o0);
	return o0;
}

void NFace::addVertices(const std::vector<unsigned int>& newVertices)
{
	for (std::vector<unsigned int>::const_iterator i = newVertices.begin(); 
	    i != newVertices.end(); i++)
	    addVertex(*i);
}

void NFace::addVertices(Ionflux::GeoUtils::NFace* newVertices)
{
	for (unsigned int i = 0; 
	    i < newVertices->getNumVertices(); i++)
	    addVertex(newVertices->getVertex(i));
}

void NFace::removeVertex(unsigned int removeElement)
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

void NFace::removeVertexIndex(unsigned int removeIndex)
{
    if (removeIndex > vertices.size())
        return;
    vertices.erase(vertices.begin() + removeIndex);
}

void NFace::clearVertices()
{
    vertices.clear();
}

void NFace::setVertexSource(Ionflux::GeoUtils::Vertex3Set* newVertexSource)
{
	vertexSource = newVertexSource;
}

Ionflux::GeoUtils::Vertex3Set* NFace::getVertexSource() const
{
    return vertexSource;
}

void NFace::setFaceData(Ionflux::GeoUtils::VectorSetSet* newFaceData)
{
	faceData = newFaceData;
}

Ionflux::GeoUtils::VectorSetSet* NFace::getFaceData() const
{
    return faceData;
}

Ionflux::GeoUtils::NFace& NFace::operator=(const Ionflux::GeoUtils::NFace& 
other)
{
    if (this == &other)
        return *this;
    TransformableObject::operator=(other);
    UIntVector v0;
    for (UIntVector::const_iterator i = other.vertices.begin(); 
        i != other.vertices.end(); i++)
        v0.push_back(*i);
    clear();
    addVertices(v0);
    setFaceData(other.faceData->copy());
    update();
	return *this;
}

Ionflux::GeoUtils::NFace* NFace::copy() const
{
    NFace* newNFace = create();
    *newNFace = *this;
    return newNFace;
}

Ionflux::GeoUtils::NFace* NFace::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<NFace*>(other);
}

Ionflux::GeoUtils::NFace* NFace::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    NFace* newObject = new NFace();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::NFace* NFace::create(const 
Ionflux::ObjectBase::UIntVector* initVerts, Ionflux::GeoUtils::Vertex3Set* 
initVertexSource, Ionflux::GeoUtils::FaceData* initUV, 
Ionflux::GeoUtils::FaceData* initVertexColors, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    NFace* newObject = new NFace(initVerts, initVertexSource, initUV, 
    initVertexColors);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::NFace* NFace::create(unsigned int v0, unsigned int v1, 
unsigned int v2, unsigned int v3, Ionflux::GeoUtils::Vertex3Set* 
initVertexSource, Ionflux::GeoUtils::FaceData* initUV, 
Ionflux::GeoUtils::FaceData* initVertexColors, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    NFace* newObject = new NFace(v0, v1, v2, v3, initVertexSource, initUV, 
    initVertexColors);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int NFace::getMemSize() const
{
    return sizeof *this;
}

std::string NFace::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string NFace::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::GeoUtils::TransformableObject::getXMLAttributeData();
	return d0.str();
}

void NFace::getXMLChildData(std::string& target, unsigned int indentLevel) 
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

void NFace::loadFromXMLFile(const std::string& fileName)
{
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, getXMLElementName());
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
NFace::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::NFaceXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::NFaceXMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 0;
        bFac = Ionflux::GeoUtils::TransformableObject::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file NFace.cpp
 * \brief N-face implementation.
 */
