/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
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
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Vertex3Set.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"

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
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, Ionflux::GeoUtils::Vector3::ZERO, ""), tangent(0), normal(0), binormal(0), polygon(0), vertexSource(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Face::Face(const Ionflux::GeoUtils::Face& other)
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, Ionflux::GeoUtils::Vector3::ZERO, ""), tangent(0), normal(0), binormal(0), polygon(0), vertexSource(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Face::Face(const Ionflux::ObjectBase::UIntVector* initVerts, 
Ionflux::GeoUtils::Vertex3Set* initVertexSource, const 
Ionflux::GeoUtils::TexCoordsVector* initUV, const 
Ionflux::GeoUtils::ColorVector* initVertexColors)
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, 
Ionflux::GeoUtils::Vector3::ZERO, ""), tangent(0), normal(0), binormal(0), 
polygon(0), vertexSource(initVertexSource)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initVerts != 0)
	    addVertices(*initVerts);
	if (initVertexSource != 0)
	    setVertexSource(initVertexSource);
	if (initUV != 0)
	    addTexCoords(*initUV);
	if (initVertexColors != 0)
	    addVertexColors(*initVertexColors);
	update();
}

Face::Face(unsigned int v0, unsigned int v1, unsigned int v2, unsigned int 
v3, Ionflux::GeoUtils::Vertex3Set* initVertexSource, const 
Ionflux::GeoUtils::TexCoordsVector* initUV, const 
Ionflux::GeoUtils::ColorVector* initVertexColors)
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, 
Ionflux::GeoUtils::Vector3::ZERO, ""), tangent(0), normal(0), binormal(0), 
polygon(0), vertexSource(initVertexSource)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addVertices(v0, v1, v2, v3);
	if (initVertexSource != 0)
	    setVertexSource(initVertexSource);
	if (initUV != 0)
	    addTexCoords(*initUV);
	if (initVertexColors != 0)
	    addVertexColors(*initVertexColors);
	update();
}

Face::~Face()
{
	clearVertices();
	clearTexCoords();
	clearVertexColors();
	clear();
}

void Face::recalculateBounds()
{
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source not set.");
	TransformableObject::recalculateBounds();
	Polygon3* p0 = getPolygon();
	*boundsCache = p0->getBounds();
	bounds = *boundsCache;
}

void Face::copyVertices()
{
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source not set.");
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
	uv.clear();
	clearTangentSpace();
	clearPolygon();
	BoxBoundsItem::clear();
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

void Face::addVertices(const Ionflux::ObjectBase::UIntVector& newVerts)
{
	for (UIntVector::const_iterator i = newVerts.begin(); 
	    i != newVerts.end(); i++)
	    addVertex(*i);
}

void Face::addTexCoords(const Ionflux::GeoUtils::TexCoordsVector& 
newTexCoords)
{
	for (TexCoordsVector::const_iterator i = newTexCoords.begin(); 
	    i != newTexCoords.end(); i++)
	    addTexCoord(*i);
}

void Face::addVertexColors(const Ionflux::GeoUtils::ColorVector& 
newVertexColors)
{
	for (ColorVector::const_iterator i = newVertexColors.begin(); 
	    i != newVertexColors.end(); i++)
	    addVertexColor(*i);
}

Ionflux::GeoUtils::Vector3 Face::getTangent()
{
	if (tangent != 0)
	    return *tangent;
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source is not set.");
	if (vertices.size() < 3)
	    throw GeoUtilsError("Face does not have enough vertices.");
	Vertex3* pv0 = vertexSource->getVertex(vertices[0]);
	Vector3 p0 = pv0->getVector();
	Vertex3* pv1 = vertexSource->getVertex(vertices[1]);
	Vector3 p1 = pv1->getVector();
	tangent = Vector3::create();
	addLocalRef(tangent);
	Vector3 b = getBinormal();
	if (uv.size() < 3)
	{
	    *tangent = b.ortho(p1 - p0).normalize();
	    return *tangent;
	}
	TexCoords uv0 = uv[0];
	TexCoords uv1 = uv[1];
	*tangent = 1. / (uv1.u - uv0.u) * ((p1 - p0) - (uv1.v - uv0.v) * b);
	return *tangent;
}

Ionflux::GeoUtils::Vector3 Face::getBinormal()
{
	if (binormal != 0)
	    return *binormal;
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source is not set.");
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
	if (uv.size() < 3)
	{
	    *binormal = (p2 - p0).normalize();
	    return *binormal;
	}
	TexCoords uv0 = uv[0];
	TexCoords uv1 = uv[1];
	TexCoords uv2 = uv[2];
	*binormal = 1. / ((uv2.v - uv0.v) * (uv1.u - uv0.u) 
	    - (uv1.v - uv0.v) * (uv2.u - uv0.u)) 
	    * ((uv1.u - uv0.u) * (p2 - p0) - (uv2.u - uv0.u) * (p1 - p0));
	return *binormal;
}

Ionflux::GeoUtils::Vector3 Face::getNormal()
{
	if (normal != 0)
	    return *normal;
	Vector3 t = getTangent();
	Vector3 b = getBinormal();
	normal = new Vector3();
	if (normal == 0)
	    throw GeoUtilsError("Could not allocate object.");
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
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source is not set.");
	if (polygon != 0)
	    return polygon;
	polygon = Polygon3::create();
	addLocalRef(polygon);
	polygon->copyTransform(*vertexSource);
	for (UIntVector::iterator i = vertices.begin(); i != vertices.end(); i++)
	    polygon->addVertex(vertexSource->getVertex(*i)->copy());
	polygon->createEdges();
	if (useTransform);
	    polygon->transform(transformMatrix);
	if (useVI);
	    polygon->transformVI(viewMatrix, &imageMatrix);
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
	TexCoordsVector uv0;
	TexCoordsVector uv1;
	if (uv.size() == vertices.size())
	{
	    uv0.push_back(uv[0]);
	    uv0.push_back(uv[1]);
	    uv0.push_back(uv[2]);
	    uv1.push_back(uv[0]);
	    uv1.push_back(uv[2]);
	    uv1.push_back(uv[3]);
	}
	Face* f0 = new Face(&v0, vertexSource, &uv0);
	if (f0 == 0)
	    throw GeoUtilsError("Could not allocate object");
	result.push_back(f0);
	Face* f1 = new Face(&v1, vertexSource, &uv1);
	if (f1 == 0)
	    throw GeoUtilsError("Could not allocate object");
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
	    throw GeoUtilsError("[Face::makePlanar] "
	        "Vertex source is not set.");
	if (vertices.size() < 3)
	    throw GeoUtilsError("[Face::makePlanar] "
	        "Face does not have enough vertices.");
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
	if ((vertices.size() != other.vertices.size()) 
	    || (uv.size() != other.uv.size()))
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
	i = 0;
	while (result 
	    && (i < uv.size()))
	{
	    if (uv[i] != other.uv[i])
	        result = false;
	    i++;
	}
	if (!result 
	    || (vertexSource != other.vertexSource))
	    return false;
	return true;
}

bool Face::operator!=(const Ionflux::GeoUtils::Face& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

std::string Face::getString() const
{
	ostringstream result;
	result << getClassName() << "[verts: [";
	bool e0 = true;
	for (UIntVector::const_iterator i = vertices.begin(); 
	    i != vertices.end(); i++)
	{
	    if (!e0)
	        result << ", ";
	    else
	        e0 = false;
	    result << *i;
	}
	result << "]; uv: [";
	e0 = true;
	for (TexCoordsVector::const_iterator j = uv.begin(); 
	    j != uv.end(); j++)
	{
	    if (!e0)
	        result << ", ";
	    else
	        e0 = false;
	    result << "(" << (*j).u << ", " << (*j).v << ")";
	}
	result << "]]";
	return result.str();
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
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source not set.");
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
	log(IFLogMessage("Cannot apply transform to face. "
	    "(Should be applied to vertex source instead.)", VL_WARNING, this, 
	    "applyTransform"));
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

Ionflux::GeoUtils::Face* Face::create(unsigned int v0, unsigned int v1, 
unsigned int v2, unsigned int v3, Ionflux::GeoUtils::Vertex3Set* 
initVertexSource, const Ionflux::GeoUtils::TexCoordsVector* initUV)
{
	Face* f0 = create();
	f0->addVertices(v0, v1, v2, v3);
	if (initVertexSource != 0)
	    f0->setVertexSource(initVertexSource);
	if (initUV != 0)
	    f0->addTexCoords(*initUV);
	f0->update();
	return f0;
}

std::string Face::getXMLDataVertices() const
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

std::string Face::getXMLDataTexCoords() const
{
	ostringstream d0;
	bool first = true;
	for (TexCoordsVector::const_iterator i = uv.begin(); 
	    i != uv.end(); i++)
	{
	    if (!first)
	        d0 << " ";
	    else
	        first = false;
	    d0 << (*i).u << "," << (*i).v;
	}
	return d0.str();
}

std::string Face::getXML_legacy() const
{
	ostringstream d0;
	d0 << "<f d=\"" << getXMLDataVertices() << "\" uv=\"" 
	    << getXMLDataTexCoords() << "\" />";
	return d0.str();
}

void Face::setFromXMLData(const std::string& vertexData, const std::string&
texCoordData)
{
	Ionflux::ObjectBase::StringVector parts0;
	explode(vertexData, " ", parts0);
	for (Ionflux::ObjectBase::StringVector::const_iterator i = 
	    parts0.begin(); i != parts0.end(); i++)
	    addVertex(strtol((*i).c_str(), 0, 10));
	Vertex3Set vs0;
	extractSVGVertices(texCoordData, vs0);
	for (unsigned int k = 0; k < vs0.getNumVertices(); k++)
	{
	    Vertex3* v0 = vs0.getVertex(k);
	    TexCoords uv0;
	    uv0.u = v0->getX();
	    uv0.v = v0->getY();
	    addTexCoord(uv0);
	}
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

unsigned int Face::getNumTexCoords() const
{
    return uv.size();
}

Ionflux::GeoUtils::TexCoords Face::getTexCoord(unsigned int elementIndex) 
const
{
    if (elementIndex < uv.size())
		return uv[elementIndex];
	return Ionflux::GeoUtils::DEFAULT_TEX_COORDS;
}

int Face::findTexCoord(Ionflux::GeoUtils::TexCoords needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::TexCoords currentTexCoord = Ionflux::GeoUtils::DEFAULT_TEX_COORDS;
	unsigned int i = 0;
	while (!found 
		&& (i < uv.size()))
	{
		currentTexCoord = uv[i];
		if (currentTexCoord == needle)
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

std::vector<Ionflux::GeoUtils::TexCoords>& Face::getTexCoords()
{
    return uv;
}

void Face::addTexCoord(Ionflux::GeoUtils::TexCoords addElement)
{
	uv.push_back(addElement);
}

void Face::removeTexCoord(Ionflux::GeoUtils::TexCoords removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::TexCoords currentTexCoord = Ionflux::GeoUtils::DEFAULT_TEX_COORDS;
	unsigned int i = 0;
	while (!found 
		&& (i < uv.size()))
	{
		currentTexCoord = uv[i];
		if (currentTexCoord == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		uv.erase(uv.begin() + i);
	}
}

void Face::removeTexCoordIndex(unsigned int removeIndex)
{
    if (removeIndex > uv.size())
        return;
    uv.erase(uv.begin() + removeIndex);
}

void Face::clearTexCoords()
{
    uv.clear();
}

unsigned int Face::getNumVertexColors() const
{
    return vertexColors.size();
}

Ionflux::GeoUtils::Color Face::getVertexColor(unsigned int elementIndex) 
const
{
    if (elementIndex < vertexColors.size())
		return vertexColors[elementIndex];
	return Ionflux::GeoUtils::DEFAULT_VERTEX_COLOR;
}

int Face::findVertexColor(Ionflux::GeoUtils::Color needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::Color currentVertexColor = Ionflux::GeoUtils::DEFAULT_VERTEX_COLOR;
	unsigned int i = 0;
	while (!found 
		&& (i < vertexColors.size()))
	{
		currentVertexColor = vertexColors[i];
		if (currentVertexColor == needle)
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

std::vector<Ionflux::GeoUtils::Color>& Face::getVertexColors()
{
    return vertexColors;
}

void Face::addVertexColor(Ionflux::GeoUtils::Color addElement)
{
	vertexColors.push_back(addElement);
}

void Face::removeVertexColor(Ionflux::GeoUtils::Color removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::Color currentVertexColor = Ionflux::GeoUtils::DEFAULT_VERTEX_COLOR;
	unsigned int i = 0;
	while (!found 
		&& (i < vertexColors.size()))
	{
		currentVertexColor = vertexColors[i];
		if (currentVertexColor == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		vertexColors.erase(vertexColors.begin() + i);
	}
}

void Face::removeVertexColorIndex(unsigned int removeIndex)
{
    if (removeIndex > vertexColors.size())
        return;
    vertexColors.erase(vertexColors.begin() + removeIndex);
}

void Face::clearVertexColors()
{
    vertexColors.clear();
}

void Face::setVertexSource(Ionflux::GeoUtils::Vertex3Set* newVertexSource)
{
	vertexSource = newVertexSource;
}

Ionflux::GeoUtils::Vertex3Set* Face::getVertexSource() const
{
	return vertexSource;
}

Ionflux::GeoUtils::Face& Face::operator=(const Ionflux::GeoUtils::Face& 
other)
{
    clear();
    for (UIntVector::const_iterator i = other.vertices.begin(); 
        i != other.vertices.end(); i++)
        vertices.push_back(*i);
    uv = other.uv;
    vertexColors = other.vertexColors;
    setVertexSource(other.vertexSource);
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

std::string Face::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Face::getXMLAttributeData() const
{
	std::string a0(Ionflux::ObjectBase::IFObject::getXMLAttributeData());
	std::ostringstream d0;
	if ((d0.str().size() > 0) && (a0.size() > 0))
	    d0 << " ";
    d0 << a0;
	return d0.str();
}

void Face::getXMLChildData(std::string& target, unsigned int indentLevel) 
const
{
	std::string iws0 = Ionflux::ObjectBase::getIndent(indentLevel);
	std::ostringstream d0;
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0(vertices, "", 
        indentLevel, "pname=\"vertices\"");
	target = d0.str();
}

}

}

/** \file Face.cpp
 * \brief Mesh face implementation.
 */
