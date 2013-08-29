/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Mesh.cpp                        Mesh (implementation).
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

#include "geoutils/Mesh.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "ifmapping/utils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Vertex.hpp"
#include "geoutils/FaceCompareAxis.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

MeshClassInfo::MeshClassInfo()
{
	name = "Mesh";
	desc = "Mesh";
}

MeshClassInfo::~MeshClassInfo()
{
}

// public member constants
const std::string Mesh::DEFAULT_ID = "mesh01";

// run-time type information instance constants
const MeshClassInfo Mesh::meshClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Mesh::CLASS_INFO = &Mesh::meshClassInfo;

const std::string Mesh::XML_ELEMENT_NAME = "mesh";

Mesh::Mesh()
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, Ionflux::GeoUtils::Vector3::ZERO, ""), vertexSource(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setVertexSource(Vertex3Set::create());
}

Mesh::Mesh(const Ionflux::GeoUtils::Mesh& other)
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, Ionflux::GeoUtils::Vector3::ZERO, ""), vertexSource(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Mesh::Mesh(Ionflux::GeoUtils::Vertex3Vector* initVerts, const 
Ionflux::GeoUtils::FaceVector* initFaces)
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, 
Ionflux::GeoUtils::Vector3::ZERO, ""), vertexSource(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setVertexSource(Vertex3Set::create());
	if (initVerts != 0)
	    addVertices(*initVerts);
	if (initFaces != 0)
	    addFaces(*initFaces);
	update();
}

Mesh::Mesh(Ionflux::GeoUtils::Vertex3Set* initVertexSource, const 
Ionflux::GeoUtils::FaceVector* initFaces)
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, 
Ionflux::GeoUtils::Vector3::ZERO, ""), vertexSource(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initVertexSource)
	    setVertexSource(initVertexSource);
	else
	    setVertexSource(Vertex3Set::create());
	if (initFaces != 0)
	    addFaces(*initFaces);
	update();
}

Mesh::~Mesh()
{
	clearFaces();
	// TODO: Nothing ATM. ;-)
}

void Mesh::recalculateBounds()
{
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source not set.");
	TransformableObject::recalculateBounds();
	if (!useTransform && !useVI)
	{
	    *boundsCache = vertexSource->getBounds();
	    bounds = *boundsCache;
	    return;
	}
	// Adjust for transformation.
	Mesh* m0 = copy();
	m0->applyTransform();
	if (m0->useTransform)
	    throw GeoUtilsError("Transform matrix still in use after "
	        "applying transformations.");
	*boundsCache = m0->getBounds();
	bounds = *boundsCache;
	delete m0;
}

Ionflux::GeoUtils::Range3 Mesh::getBounds()
{
	bounds = TransformableObject::getBounds();
	return bounds;
}

void Mesh::copyVertices()
{
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source not set.");
	setVertexSource(&(vertexSource->duplicate()));
}

Ionflux::GeoUtils::Vertex3* Mesh::addVertex()
{
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source not set.");
	return vertexSource->addVertex();
}

void Mesh::addVertices(Ionflux::GeoUtils::Vertex3Vector& newVerts)
{
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source not set.");
	for (Vertex3Vector::iterator i = newVerts.begin(); 
	    i != newVerts.end(); i++)
	    vertexSource->addVertex(*i);
}

void Mesh::addVertices(Ionflux::GeoUtils::Vertex3Set& newVerts)
{
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source not set.");
	for (unsigned int i = 0; i < newVerts.getNumVertices(); i++)
	    vertexSource->addVertex(newVerts.getVertex(i));
}

void Mesh::update()
{
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source not set.");
	// Determine the bounds.
	recalculateBounds();
	// Update the faces.
	for (FaceVector::iterator i = faces.begin(); 
	    i != faces.end(); i++)
	{
	    Face* f = *i;
	    if (f->getVertexSource() == 0)
	    {
	        /* If the vertex source is not defined for the face, set it 
	           to the vertex source of this mesh. */
	        f->setVertexSource(vertexSource);
	    }
	    f->update();
	}
	updateRadiusAndCenter();
}

void Mesh::clear()
{
	setVertexSource(0);
	clearFaces();
	BoxBoundsItem::clear();
}

void Mesh::addFaces(const Ionflux::GeoUtils::FaceVector& newFaces)
{
	for (FaceVector::const_iterator i = newFaces.begin(); 
	    i != newFaces.end(); i++)
	    addFace(*i);
}

void Mesh::setFaceIDs()
{
	ostringstream fid;
	unsigned int k = 0;
	for (FaceVector::const_iterator i = faces.begin(); 
	    i != faces.end(); i++)
	{
	    fid.str("");
	    fid << "face" << right << setfill('0') << setw(8) << k;
	    (*i)->setItemID(fid.str());
	    k++;
	}
}

Ionflux::GeoUtils::BoxBoundsItem* Mesh::getItem(const std::string& itemID)
{
	ostringstream message;
	if ((itemID.size() < 12) 
	    || (itemID.substr(0, 4) != "face"))
	{
	    message << "Bad item ID for mesh: '" << itemID << "'";
	    throw GeoUtilsError(message.str());
	}
	size_t i0 = itemID.find_first_not_of("0", 4);
	unsigned int fi = 0;
	if (i0 != string::npos)
	    fi = strtol(itemID.substr(i0).c_str(), 0, 10);
	if (fi >= faces.size())
	{
	    message << "Invalid face index: '" << itemID << "'";
	    throw GeoUtilsError(message.str());
	}
	return faces[fi];
}

int Mesh::checkPlaneInner(const Ionflux::GeoUtils::Plane3& plane, double t)
{
	bool e0 = true;
	int c0 = 0;
	int c1 = 1;
	for (FaceVector::const_iterator i = faces.begin(); 
	    i != faces.end(); i++)
	{
	    c1 = (*i)->checkPlaneInner(plane, t);
	    if (e0)
	    {
	        // Initialize comparison value on first iteration.
	        c0 = c1;
	        e0 = false;
	    }
	    else 
	    {
	        /* If there are two faces on opposite sides of the plane, 
	           there is some intersection for this mesh. */
	        if (c0 != c1)
	            return 0;
	    }
	}
	return c0;
}

int Mesh::checkSphereInner(const Ionflux::GeoUtils::Sphere3& sphere, double
t)
{
	bool e0 = true;
	int c0 = 0;
	int c1 = 1;
	for (FaceVector::const_iterator i = faces.begin(); 
	    i != faces.end(); i++)
	{
	    c1 = (*i)->checkSphereInner(sphere, t);
	    if (e0)
	    {
	        // Initialize comparison value on first iteration.
	        c0 = c1;
	        e0 = false;
	    }
	    else 
	    {
	        /* If there are two faces on opposite sides of the sphere, 
	           there is some intersection for this mesh. */
	        if (c0 != c1)
	            return 0;
	    }
	}
	return c0;
}

bool Mesh::checkLineInner(const Ionflux::GeoUtils::Line3& line, double t)
{
	for (FaceVector::const_iterator i = faces.begin(); 
	    i != faces.end(); i++)
	{
	    if((*i)->checkLineInner(line, t))
	        return true;
	}
	return false;
}

int Mesh::checkBoxInner(const Ionflux::GeoUtils::BoxBoundsItem& other, 
double t)
{
	bool e0 = true;
	int c0 = 0;
	int c1 = 1;
	for (FaceVector::const_iterator i = faces.begin(); 
	    i != faces.end(); i++)
	{
	    c1 = (*i)->checkBoxInner(other, t);
	    if (e0)
	    {
	        // Initialize comparison value on first iteration.
	        c0 = c1;
	        e0 = false;
	    }
	    else 
	    {
	        /* If there are two faces on opposite sides of the box, 
	           there is some intersection for this mesh. */
	        if (c0 != c1)
	            return 0;
	    }
	}
	return checkBox(other, t);
}

bool Mesh::operator==(const Ionflux::GeoUtils::Mesh& other) const
{
	if (faces.size() != other.faces.size())
	    return false;
	bool result = true;
	unsigned int i = 0;
	while (result 
	    && (i < faces.size()))
	{
	    if (faces[i] != other.faces[i])
	        result = false;
	    i++;
	}
	if ((vertexSource == 0) && (other.vertexSource == 0))
	    return true;
	if ((vertexSource == 0) || (other.vertexSource == 0))
	    return false;
	unsigned int numVerts = getNumVertices();
	if (numVerts != other.getNumVertices())
	    return false;
	i = 0;
	while (result 
	    && (i < numVerts))
	{
	    if ((*getVertex(i)) != (*other.getVertex(i)))
	        result = false;
	    i++;
	}
	if (!result)
	    return false;
	return true;
}

bool Mesh::operator!=(const Ionflux::GeoUtils::Mesh& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

std::string Mesh::getString() const
{
	ostringstream result;
	result << getClassName();
	if (itemID.size() > 0)
	    result << "[" << itemID << "]";
	return result.str();
}

Ionflux::GeoUtils::Vector3 Mesh::getBarycenter()
{
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source not set.");
	if (!useTransform)
	    return vertexSource->getBarycenter();
	// Adjust for transformation.
	Vertex3 v0(vertexSource->getBarycenter());
	if (useTransform)
	    v0.transform(transformMatrix);
	if (useVI)
	    v0.transformVI(viewMatrix, &imageMatrix);
	return v0.getVector();
}

void Mesh::applyTransform(bool recursive)
{
	if (!useTransform && !useVI)
	{
	    if (recursive)
	        vertexSource->applyTransform(recursive);
	    return;
	}
	Vertex3Set* vs0 = vertexSource;
	addLocalRef(vs0);
	copyVertices();
	if (useTransform)
	{
	    vertexSource->transform(transformMatrix);
	    vertexSource->applyTransform();
	    transformMatrix = Matrix4::UNIT;
	    useTransform = false;
	}
	if (useVI)
	{
	    vertexSource->transformVI(viewMatrix, &imageMatrix);
	    vertexSource->applyTransform();
	    viewMatrix = Matrix4::UNIT;
	    imageMatrix = Matrix4::UNIT;
	    useVI = false;
	}
	// Update faces.
	for (FaceVector::iterator i = faces.begin(); i != faces.end(); i++)
	{
	    // Update vertex source used by the faces.
	    Face* f0 = *i;
	    if (f0->getVertexSource() == vs0)
	        f0->setVertexSource(vertexSource);
	    // Clear face data dependent on transformation.
	    f0->clearTangentSpace();
	    f0->clearPolygon();
	}
	removeLocalRef(vs0);
}

Ionflux::GeoUtils::Mesh& Mesh::scale(const Ionflux::GeoUtils::Vector3& s)
{
	TransformableObject::scale(s);
	return *this;
}

Ionflux::GeoUtils::Mesh& Mesh::translate(const Ionflux::GeoUtils::Vector3& 
t)
{
	TransformableObject::translate(t);
	return *this;
}

Ionflux::GeoUtils::Mesh& Mesh::rotate(double phi, Ionflux::GeoUtils::AxisID
axis)
{
	TransformableObject::rotate(phi, axis);
	return *this;
}

Ionflux::GeoUtils::Mesh& Mesh::normalize()
{
	TransformableObject::normalize();
	return *this;
}

Ionflux::GeoUtils::Mesh& Mesh::center(Ionflux::GeoUtils::CenteringMethod 
method, Ionflux::GeoUtils::Vector3* origin)
{
	TransformableObject::center(method, origin);
	return *this;
}

Ionflux::GeoUtils::Mesh& Mesh::transform(const Ionflux::GeoUtils::Matrix4& 
matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Mesh& Mesh::transform(const Ionflux::GeoUtils::Matrix3& 
matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Mesh& Mesh::duplicate()
{
	// TODO: Implementation.
	return *copy();
}

void Mesh::getPolygons(Ionflux::GeoUtils::Polygon3Set& target)
{
	Polygon3Set* ps0;
	bool t0 = false;
	if (useTransform || useVI)
	{
	    /* Use a temporary polygon set to transform the polygons 
	       according to the mesh transformations. */
	    ps0 = Polygon3Set::create();
	    ps0->copyTransform(*this);
	    t0 = true;
	} else
	    ps0 = &target;
	for (FaceVector::iterator i = faces.begin(); 
	    i != faces.end(); i++)
	{
	    // Add face polygons to the target or temporary set.
	    Face* f0 = *i;
	    ps0->addPolygon(f0->getPolygon());
	}
	if (t0)
	{
	    /* Transform polygons in the temporary set, then add them to 
	       the target set. */
	    ps0->applyTransform();
	    target.addPolygons(*ps0);
	    delete ps0;
	}
}

std::string Mesh::getXML_legacy() const
{
	ostringstream d0;
	std::string mID = getID();
	if (mID.size() == 0)
	    mID = DEFAULT_ID;
	d0 << "<mesh id=\"" << mID << "\"><vertices>";
	// Vertices.
	d0 << vertexSource->getXML_legacy();
	// Faces.
	d0 << "</vertices><faces>";
	for (FaceVector::const_iterator i = faces.begin(); 
	    i != faces.end(); i++)
	    d0 << (*i)->getXML_legacy();
	d0 << "</faces></mesh>";
	return d0.str();
}

void Mesh::writeToFile(const std::string& fileName) const
{
	ofstream f0;
	f0.open(fileName.c_str(), ios_base::out);
	f0 << XML_HEADER << getXML_legacy();
}

void Mesh::removeBackfaces(const Ionflux::GeoUtils::Vector3& front)
{
	FaceVector keepFaces;
	for (FaceVector::iterator i = faces.begin(); i != faces.end(); i++)
	{
	    Face* f0 = *i;
	    if (!f0->isBackface(front))
	    {
	        keepFaces.push_back(f0);
	        addLocalRef(f0);
	    }
	}
	clearFaces();
	addFaces(keepFaces);
	for (FaceVector::iterator i = keepFaces.begin(); 
	    i != keepFaces.end(); i++)
	    removeLocalRef(*i);
}

void Mesh::sortFaces(Ionflux::GeoUtils::FaceCompare* compFunc)
{
	FaceCompare wrap0;
	if (compFunc == 0)
	    wrap0.setTarget(FaceCompareAxis::create(AXIS_Z));
	else
	    wrap0.setTarget(compFunc);
	::sort(faces.begin(), faces.end(), wrap0);
}

unsigned int Mesh::makePlanar(const Ionflux::ObjectBase::UIntVector& 
indices, unsigned int maxIterations, double p, double t)
{
	unsigned int numFaces = faces.size();
	unsigned int numIndices = indices.size();
	if (numIndices > numFaces)
	    throw GeoUtilsError("[Mesh::makePlanar] "
	        "Too many face indices specified.");
	unsigned int nonPlanar = numIndices;
	unsigned int i = 0;
	while ((i < maxIterations) && (nonPlanar > 0))
	{
	    unsigned int k = indices[
	        Ionflux::Mapping::getRandomInt() % numIndices];
	    Face* f0 = getFace(k);
	    if (f0 == 0)
	    {
	        std::ostringstream status;
	        status << "[Mesh::makePlanar] "
	            "Face index out of range: " << k;
	        throw GeoUtilsError(status.str());
	    }
	    f0->makePlanar(p, t);
	    nonPlanar = 0;
	    for(unsigned int j = 0; j < numIndices; j++)
	    {
	        f0 = getFace(indices[j]);
	        f0->update();
	        if (!f0->isPlanar(t))
	            nonPlanar++;
	    }
	    i++;
	}
	/* <---- DEBUG ----- //
	std::cerr << "[Mesh::makePlanar] DEBUG: "
	    "Non-planar faces after " << i << " iterations: " << nonPlanar 
	    << std::endl;
	// <---- DEBUG ----- */
	update();
	return nonPlanar;
}

Ionflux::GeoUtils::Mesh* Mesh::plane()
{
	Mesh* m0 = create();
	double s = 0.5;
	// Vertices.
	Vertex3Vector verts0;
	verts0.push_back(Vertex::create(-s, -s, 0));
	verts0.push_back(Vertex::create(-s, s, 0));
	verts0.push_back(Vertex::create(s, s, 0));
	verts0.push_back(Vertex::create(s, -s, 0));
	m0->addVertices(verts0);
	// Faces.
	FaceVector faces0;
	faces0.push_back(Face::create(0, 1, 2, 3, m0->getVertexSource()));
	m0->addFaces(faces0);
	m0->update();
	return m0;
}

Ionflux::GeoUtils::Mesh* Mesh::cube()
{
	Mesh* m0 = create();
	double s = 0.5;
	// Vertices.
	Vertex3Vector verts0;
	verts0.push_back(Vertex::create(-s, -s, -s));
	verts0.push_back(Vertex::create(-s, s, -s));
	verts0.push_back(Vertex::create(s, s, -s));
	verts0.push_back(Vertex::create(s, -s, -s));
	verts0.push_back(Vertex::create(s, -s, s));
	verts0.push_back(Vertex::create(s, s, s));
	verts0.push_back(Vertex::create(-s, s, s));
	verts0.push_back(Vertex::create(-s, -s, s));
	m0->addVertices(verts0);
	// Faces.
	FaceVector faces0;
	faces0.push_back(Face::create(0, 3, 4, 7, m0->getVertexSource()));
	faces0.push_back(Face::create(3, 2, 5, 4, m0->getVertexSource()));
	faces0.push_back(Face::create(1, 6, 5, 2, m0->getVertexSource()));
	faces0.push_back(Face::create(0, 7, 6, 1, m0->getVertexSource()));
	faces0.push_back(Face::create(4, 5, 6, 7, m0->getVertexSource()));
	faces0.push_back(Face::create(0, 1, 2, 3, m0->getVertexSource()));
	m0->addFaces(faces0);
	m0->update();
	return m0;
}

Ionflux::GeoUtils::Mesh* Mesh::cylinder(unsigned int subDivs, double 
length, double radius)
{
	Mesh* m0 = create();
	double s = 0.5 * length;
	// Vertices.
	Vertex3Vector verts0;
	double dPhi = 2. * M_PI / subDivs;
	// Hull vertices.
	for (unsigned int i = 0; i < subDivs; i++)
	{
	    double x = radius * ::sin(i * dPhi);
	    double y = radius * ::cos(i * dPhi);
	    verts0.push_back(Vertex::create(x, y, s));
	    verts0.push_back(Vertex::create(x, y, -s));
	}
	// Center vertices.
	verts0.push_back(Vertex::create(0., 0., s));
	verts0.push_back(Vertex::create(0., 0., -s));
	m0->addVertices(verts0);
	// Faces.
	FaceVector faces0;
	// Hull faces.
	for (unsigned int i = 0; i < subDivs; i++)
	{
	    if (i < (subDivs - 1))
	        faces0.push_back(Face::create(
	            2 * i, 2 * i + 2, 2 * i + 3, 2 * i + 1, 
	            m0->getVertexSource()));
	    else
	        faces0.push_back(Face::create(
	            2 * i, 0, 1, 2 * i + 1, 
	            m0->getVertexSource()));
	}
	// Top faces.
	unsigned int i0 = verts0.size() - 2;
	for (unsigned int i = 0; i < subDivs; i++)
	{
	    if (i < (subDivs - 1))
	        faces0.push_back(Face::create(
	            i0, 2 * i + 2, 2 * i, Face::VERTEX_INDEX_NONE, 
	            m0->getVertexSource()));
	    else
	        faces0.push_back(Face::create(
	            i0, 0, 2 * i, Face::VERTEX_INDEX_NONE, 
	            m0->getVertexSource()));
	}
	// Bottom faces.
	i0 = verts0.size() - 1;
	for (unsigned int i = 0; i < subDivs; i++)
	{
	    if (i < (subDivs - 1))
	        faces0.push_back(Face::create(
	            i0, 2 * i + 1, 2 * i + 3, Face::VERTEX_INDEX_NONE, 
	            m0->getVertexSource()));
	    else
	        faces0.push_back(Face::create(
	            i0, 2 * i + 1, 1, Face::VERTEX_INDEX_NONE, 
	            m0->getVertexSource()));
	}
	m0->addFaces(faces0);
	m0->update();
	return m0;
}

Ionflux::GeoUtils::Mesh* Mesh::arrow(unsigned int subDivs, double length, 
double radius, double headLength, double headRadius)
{
	Mesh* m0 = create();
	// Vertices.
	Vertex3Vector verts0;
	double dPhi = 2. * M_PI / subDivs;
	// Hull vertices.
	for (unsigned int i = 0; i < subDivs; i++)
	{
	    double x = radius * ::sin(i * dPhi);
	    double y = radius * ::cos(i * dPhi);
	    verts0.push_back(Vertex::create(x * headRadius, y * headRadius, 
	        (0.5 - headLength) * length));
	    verts0.push_back(Vertex::create(x, y, 
	        (0.5 - headLength) * length));
	    verts0.push_back(Vertex::create(x, y, -0.5 * length));
	}
	// Center vertices.
	verts0.push_back(Vertex::create(0., 0., 0.5 * length));
	verts0.push_back(Vertex::create(0., 0., -0.5 * length));
	m0->addVertices(verts0);
	// Faces.
	FaceVector faces0;
	// Hull faces.
	for (unsigned int i = 0; i < subDivs; i++)
	{
	    if (i < (subDivs - 1))
	    {
	        faces0.push_back(Face::create(
	            3 * i, 3 * i + 3, 3 * i + 4, 3 * i + 1, 
	            m0->getVertexSource()));
	        faces0.push_back(Face::create(
	            3 * i + 1, 3 * i + 4, 3 * i + 5, 3 * i + 2, 
	            m0->getVertexSource()));
	    } else
	    {
	        faces0.push_back(Face::create(
	            3 * i, 0, 1, 3 * i + 1, 
	            m0->getVertexSource()));
	        faces0.push_back(Face::create(
	            3 * i + 1, 1, 2, 3 * i + 2, 
	            m0->getVertexSource()));
	    }
	}
	// Top faces.
	unsigned int i0 = verts0.size() - 2;
	for (unsigned int i = 0; i < subDivs; i++)
	{
	    if (i < (subDivs - 1))
	        faces0.push_back(Face::create(
	            i0, 3 * i + 3, 3 * i, Face::VERTEX_INDEX_NONE, 
	            m0->getVertexSource()));
	    else
	        faces0.push_back(Face::create(
	            i0, 0, 3 * i, Face::VERTEX_INDEX_NONE, 
	            m0->getVertexSource()));
	}
	// Bottom faces.
	i0 = verts0.size() - 1;
	for (unsigned int i = 0; i < subDivs; i++)
	{
	    if (i < (subDivs - 1))
	        faces0.push_back(Face::create(
	            i0, 3 * i + 2, 3 * i + 5, Face::VERTEX_INDEX_NONE, 
	            m0->getVertexSource()));
	    else
	        faces0.push_back(Face::create(
	            i0, 3 * i + 2, 2, Face::VERTEX_INDEX_NONE, 
	            m0->getVertexSource()));
	}
	m0->addFaces(faces0);
	m0->update();
	return m0;
}

void Mesh::setVertexSource(Ionflux::GeoUtils::Vertex3Set* newVertexSource)
{
	if (vertexSource == newVertexSource)
		return;
    if (newVertexSource != 0)
        addLocalRef(newVertexSource);
	if (vertexSource != 0)
		removeLocalRef(vertexSource);
	vertexSource = newVertexSource;
}

Ionflux::GeoUtils::Vertex3Set* Mesh::getVertexSource() const
{
	return vertexSource;
}

unsigned int Mesh::getNumVertices() const
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->getNumVertices();
}

Ionflux::GeoUtils::Vertex3* Mesh::getVertex(unsigned int elementIndex) 
const
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->getVertex(elementIndex);
}

int Mesh::findVertex(Ionflux::GeoUtils::Vertex3* needle, unsigned int 
occurence) const
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->findVertex(needle, occurence);
}

std::vector<Ionflux::GeoUtils::Vertex3*>& Mesh::getVertices()
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->getVertices();
}

void Mesh::addVertex(Ionflux::GeoUtils::Vertex3* addElement)
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->addVertex(addElement);
}

void Mesh::removeVertex(Ionflux::GeoUtils::Vertex3* removeElement)
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->removeVertex(removeElement);
}

void Mesh::removeVertexIndex(unsigned int removeIndex)
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->removeVertexIndex(removeIndex);
}

void Mesh::clearVertices()
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->clearVertices();
}

unsigned int Mesh::getNumFaces() const
{
    return faces.size();
}

Ionflux::GeoUtils::Face* Mesh::getFace(unsigned int elementIndex) const
{
    if (elementIndex < faces.size())
		return faces[elementIndex];
	return 0;
}

int Mesh::findFace(Ionflux::GeoUtils::Face* needle, unsigned int occurence)
const
{
    bool found = false;
	Ionflux::GeoUtils::Face* currentFace = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < faces.size()))
	{
		currentFace = faces[i];
		if (currentFace == needle)
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

std::vector<Ionflux::GeoUtils::Face*>& Mesh::getFaces()
{
    return faces;
}

void Mesh::addFace(Ionflux::GeoUtils::Face* addElement)
{
	addLocalRef(addElement);
	faces.push_back(addElement);
}

void Mesh::removeFace(Ionflux::GeoUtils::Face* removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::Face* currentFace = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < faces.size()))
	{
		currentFace = faces[i];
		if (currentFace == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		faces.erase(faces.begin() + i);
		if (currentFace != 0)
			removeLocalRef(currentFace);
	}
}

void Mesh::removeFaceIndex(unsigned int removeIndex)
{
    if (removeIndex > faces.size())
        return;
	Ionflux::GeoUtils::Face* e0 = faces[removeIndex];
    faces.erase(faces.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void Mesh::clearFaces()
{
    std::vector<Ionflux::GeoUtils::Face*>::iterator i;
	for (i = faces.begin(); i != faces.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	faces.clear();
}

Ionflux::GeoUtils::Mesh& Mesh::operator=(const Ionflux::GeoUtils::Mesh& 
other)
{
    TransformableObject::operator=(other);
    setVertexSource(other.vertexSource);
    FaceVector f0;
    for (FaceVector::const_iterator i = other.faces.begin(); 
        i != other.faces.end(); i++)
    {
        Face* ft0 = Face::create();
        *ft0 = *(*i);
        f0.push_back(ft0);
    }
    clearFaces();
    addFaces(f0);
    BoxBoundsItem::clear();
    update();
	return *this;
}

Ionflux::GeoUtils::Mesh* Mesh::copy() const
{
    Mesh* newMesh = create();
    *newMesh = *this;
    return newMesh;
}

Ionflux::GeoUtils::Mesh* Mesh::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Mesh*>(other);
}

Ionflux::GeoUtils::Mesh* Mesh::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Mesh* newObject = new Mesh();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

std::string Mesh::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Mesh::getXMLAttributeData() const
{
	std::string a0(Ionflux::GeoUtils::TransformableObject::getXMLAttributeData());
	std::ostringstream d0;
	if (a0.size() > 0)
	    d0 << a0;
	return d0.str();
}

void Mesh::getXMLChildData(std::string& target, unsigned int indentLevel) 
const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::GeoUtils::TransformableObject::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	std::string iws0 = Ionflux::ObjectBase::getIndent(indentLevel);
	if (d0.str().size() > 0)
	    d0 << "\n";
	d0 << vertexSource->getXML0(indentLevel, "pname=\"vertex_source\"");
	target = d0.str();
}

}

}

/** \file Mesh.cpp
 * \brief Mesh implementation.
 */
