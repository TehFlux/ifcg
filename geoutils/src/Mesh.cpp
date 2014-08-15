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
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Vertex.hpp"
#include "geoutils/Edge.hpp"
#include "geoutils/NFaceSet.hpp"
#include "geoutils/VectorSetSet.hpp"
#include "geoutils/FaceCompareAxis.hpp"
#include "geoutils/xmlutils.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/MeshXMLFactory.hpp"

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
	baseClassInfo.push_back(Ionflux::GeoUtils::BoxBoundsItem::CLASS_INFO);
	baseClassInfo.push_back(Ionflux::GeoUtils::ItemSource::CLASS_INFO);
	baseClassInfo.push_back(Ionflux::GeoUtils::TransformableObject::CLASS_INFO);
}

MeshClassInfo::~MeshClassInfo()
{
}

// public member constants
const std::string Mesh::DEFAULT_ID = "mesh01";
const Ionflux::GeoUtils::MeshNFaceTypeID Mesh::NFACE_TYPE_FACE = 0;
const Ionflux::GeoUtils::MeshNFaceTypeID Mesh::NFACE_TYPE_EDGE = 1;

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
	clearEdges();
	// TODO: Nothing ATM. ;-)
}

void Mesh::recalculateBounds()
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "recalculateBounds", "Vertex source");
	TransformableObject::recalculateBounds();
	if (!useTransform() && !useVI())
	{
	    *boundsCache = vertexSource->getBounds();
	    bounds = *boundsCache;
	    return;
	}
	// Adjust for transformation.
	Mesh* m0 = copy();
	addLocalRef(m0);
	m0->applyTransform();
	if (m0->useTransform())
	    throw GeoUtilsError(getErrorString(
	        "Transform matrix still in use after "
	        "applying transformations.", "recalculateBounds"));
	*boundsCache = m0->getBounds();
	bounds = *boundsCache;
	removeLocalRef(m0);
}

Ionflux::GeoUtils::Range3 Mesh::getBounds()
{
	bounds = TransformableObject::getBounds();
	return bounds;
}

void Mesh::copyVertices()
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "copyVertices", "Vertex source");
	setVertexSource(vertexSource->copy());
}

void Mesh::update()
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "update", "Vertex source");
	// Determine the bounds.
	recalculateBounds();
	// update faces.
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
	// update edges.
	for (NFaceVector::iterator i = edges.begin(); 
	    i != edges.end(); i++)
	{
	    NFace* e = *i;
	    if (e->getVertexSource() == 0)
	    {
	        /* If the vertex source is not defined for the edge, set it 
	           to the vertex source of this mesh. */
	        e->setVertexSource(vertexSource);
	    }
	    e->update();
	}
	updateRadiusAndCenter();
}

void Mesh::clear()
{
	setVertexSource(0);
	clearFaces();
	clearEdges();
	BoxBoundsItem::clear();
	TransformableObject::clear();
}

void Mesh::clearData()
{
	if (vertexSource != 0)
	    vertexSource->clearVertices();
	clearFaces();
	clearEdges();
	BoxBoundsItem::clear();
	TransformableObject::clear();
}

void Mesh::setFaceIDs()
{
	std::ostringstream fid;
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

void Mesh::setEdgeIDs()
{
	std::ostringstream eid;
	unsigned int k = 0;
	for (NFaceVector::const_iterator i = edges.begin(); 
	    i != edges.end(); i++)
	{
	    eid.str("");
	    eid << "edge" << right << setfill('0') << setw(8) << k;
	    (*i)->setItemID(eid.str());
	    k++;
	}
}

Ionflux::GeoUtils::BoxBoundsItem* Mesh::getItem(const std::string& itemID)
{
	if (itemID.size() < 4)
	{
	    std::ostringstream status;
	    status << "Bad item ID for mesh: '" << itemID << "'";
	    throw GeoUtilsError(getErrorString(status.str(), "getItem"));
	}
	std::string itemType = itemID.substr(0, 4);
	if (itemType == "face")
	{
	    // face
	    if (itemID.size() < 12)
	    {
	        std::ostringstream status;
	        status << "Bad item ID for mesh: '" << itemID 
	            << "' (itemType = " << itemType << ")";
	        throw GeoUtilsError(getErrorString(status.str(), "getItem"));
	    }
	    size_t i0 = itemID.find_first_not_of("0", 4);
	    unsigned int fi = 0;
	    if (i0 != string::npos)
	        fi = strtol(itemID.substr(i0).c_str(), 0, 10);
	    if (fi >= faces.size())
	    {
	        std::ostringstream status;
	        status << "Invalid face index: '" << itemID << "'";
	        throw GeoUtilsError(getErrorString(status.str(), "getItem"));
	    }
	    return faces[fi];
	} else
	if (itemType == "edge")
	{
	    // edge
	    if (itemID.size() < 12)
	    {
	        std::ostringstream status;
	        status << "Bad item ID for mesh: '" << itemID 
	            << "' (itemType = " << itemType << ")";
	        throw GeoUtilsError(getErrorString(status.str(), "getItem"));
	    }
	    size_t i0 = itemID.find_first_not_of("0", 4);
	    unsigned int ei = 0;
	    if (i0 != string::npos)
	        ei = strtol(itemID.substr(i0).c_str(), 0, 10);
	    if (ei >= edges.size())
	    {
	        std::ostringstream status;
	        status << "Invalid edge index: '" << itemID << "'";
	        throw GeoUtilsError(getErrorString(status.str(), "getItem"));
	    }
	    return edges[ei];
	} else
	{
	    std::ostringstream status;
	    status << "Bad item type for mesh: '" << itemType << "'";
	    throw GeoUtilsError(getErrorString(status.str(), "getItem"));
	}
	return 0;
}

Ionflux::GeoUtils::NFace* Mesh::getNFace(Ionflux::GeoUtils::MeshNFaceTypeID
typeID, unsigned int index) const
{
	if (typeID == NFACE_TYPE_FACE)
	    return getFace(index);
	if (typeID == NFACE_TYPE_EDGE)
	    return getEdge(index);
	return 0;
}

unsigned int Mesh::getNumNFaces(Ionflux::GeoUtils::MeshNFaceTypeID typeID) 
const
{
	if (typeID == NFACE_TYPE_FACE)
	    return getNumFaces();
	if (typeID == NFACE_TYPE_EDGE)
	    return getNumEdges();
	return 0;
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
	// faces
	unsigned int i = 0;
	while (result 
	    && (i < faces.size()))
	{
	    if (faces[i] != other.faces[i])
	        result = false;
	    i++;
	}
	if (!result)
	    return false;
	// edges
	i = 0;
	while (result 
	    && (i < edges.size()))
	{
	    if (edges[i] != other.edges[i])
	        result = false;
	    i++;
	}
	if (!result)
	    return false;
	// vertices
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

Ionflux::GeoUtils::Vector3 Mesh::getBarycenter()
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "getBarycenter", "Vertex source");
	if (!useTransform())
	    return vertexSource->getBarycenter();
	// Adjust for transformation.
	Vertex3 v0(vertexSource->getBarycenter());
	if (useTransform())
	    v0.transform(*getTransformMatrix());
	if (useVI())
	    v0.transformVI(*getViewMatrix(), getImageMatrix());
	return v0.getVector();
}

void Mesh::applyTransform(bool recursive)
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "applyTransform", "Vertex source");
	if (!useTransform() && !useVI())
	{
	    if (recursive)
	        vertexSource->applyTransform(recursive);
	    clearTransformations();
	    return;
	}
	Vertex3Set* vs0 = vertexSource;
	addLocalRef(vs0);
	copyVertices();
	if (useTransform())
	    vertexSource->transform(*getTransformMatrix());
	if (useVI())
	    vertexSource->transformVI(*getViewMatrix(), getImageMatrix());
	if (useTransform() || useVI())
	    vertexSource->applyTransform(recursive);
	// update faces.
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
	// update edges
	for (NFaceVector::iterator i = edges.begin(); i != edges.end(); i++)
	{
	    // Update vertex source used by the edges.
	    NFace* e0 = *i;
	    if (e0->getVertexSource() == vs0)
	        e0->setVertexSource(vertexSource);
	    // Clear edge data dependent on transformation.
	    e0->clearPolygon();
	}
	removeLocalRef(vs0);
	clearTransformations();
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

Ionflux::GeoUtils::Mesh& Mesh::swapAxes(Ionflux::GeoUtils::AxisID x, 
Ionflux::GeoUtils::AxisID y, Ionflux::GeoUtils::AxisID z, 
Ionflux::GeoUtils::AxisID w)
{
	TransformableObject::swapAxes(x, y, z, w);
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

void Mesh::getFacePolygons(Ionflux::GeoUtils::Polygon3Set& target)
{
	Polygon3Set* ps0 = 0;
	bool t0 = false;
	if (useTransform() || useVI())
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
	    target.addPolygons(ps0);
	    delete ps0;
	}
}

void Mesh::getEdgePolygons(Ionflux::GeoUtils::Polygon3Set& target)
{
	Polygon3Set* ps0 = 0;
	bool t0 = false;
	if (useTransform() || useVI())
	{
	    /* Use a temporary polygon set to transform the polygons 
	       according to the mesh transformations. */
	    ps0 = Polygon3Set::create();
	    ps0->copyTransform(*this);
	    t0 = true;
	} else
	    ps0 = &target;
	for (NFaceVector::iterator i = edges.begin(); 
	    i != edges.end(); i++)
	{
	    // Add edge polygons to the target or temporary set.
	    NFace* e0 = *i;
	    ps0->addPolygon(e0->getPolygon());
	}
	if (t0)
	{
	    /* Transform polygons in the temporary set, then add them to 
	       the target set. */
	    ps0->applyTransform();
	    target.addPolygons(ps0);
	    delete ps0;
	}
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

unsigned int Mesh::makeTris()
{
	unsigned int numFaces = getNumFaces();
	unsigned int ntCount = 0;
	Mesh m0;
	FaceVector nfv;
	for (unsigned int i = 0; i < numFaces; i++)
	{
	    Face* cf = getFace(i);
	    if (cf != 0)
	    {
	        if (cf->isTri())
	        {
	            // keep existing tri face
	            m0.addFace(cf);
	        } else
	        {
	            // not a tri face
	            nfv.clear();
	            cf->getTris(nfv);
	            m0.addFaces(nfv);
	            ntCount++;
	        }
	    }
	}
	if (ntCount > 0)
	{
	    clearFaces();
	    addFaces(m0.getFaces());
	}
	return ntCount;
}

void Mesh::setFaceVertexNormals(bool flip0)
{
	unsigned int numFaces = getNumFaces();
	for (unsigned int i = 0; i < numFaces; i++)
	{
	    Face* cf = getFace(i);
	    if (cf != 0)
	        cf->setFaceVertexNormals(flip0);
	}
}

void Mesh::setFaceVertexColors(const Ionflux::GeoUtils::Vector4& color)
{
	unsigned int numFaces = getNumFaces();
	for (unsigned int i = 0; i < numFaces; i++)
	{
	    Face* cf = getFace(i);
	    if (cf != 0)
	        cf->setVertexColors(color);
	}
}

bool Mesh::isTriMesh() const
{
	unsigned int numFaces = getNumFaces();
	unsigned int i = 0;
	while (i < numFaces)
	{
	    Face* cf = getFace(i);
	    if (cf != 0)
	    {
	        if (!cf->isTri())
	            return false;
	    }
	    i++;
	}
	return true;
}

unsigned int Mesh::createEdges()
{
	unsigned int numFaces = getNumFaces();
	unsigned int neCount = 0;
	NFaceSet nes;
	NFaceSet ces;
	EdgeObjSet es0;
	for (unsigned int i = 0; i < numFaces; i++)
	{
	    Face* cf = getFace(i);
	    if (cf != 0)
	    {
	        ces.clearNFaces();
	        cf->getEdges(ces, true);
	        for (unsigned int k = 0; k < ces.getNumNFaces(); k++)
	        {
	            NFace* ce0 = Ionflux::ObjectBase::nullPointerCheck(
	                ces.getNFace(k), this, "createEdges", "Edge");
	            Edge ce1;
	            ce0->getEdge(ce1);
	            ce1.sort();
	            /* <---- DEBUG ----- //
	            std::cerr << "[Mesh::createEdges] DEBUG: "
	                "N-face: [" << ce0->getValueString() 
	                << "], edge: [" << ce1.getValueString() << "]" 
	                << std::endl;
	            // ----- DEBUG ----> */
	            if (es0.count(ce1) == 0)
	            {
	                /* <---- DEBUG ----- //
	                std::cerr << "[Mesh::createEdges] DEBUG: "
	                    "adding edge: [" << ce0->getValueString() 
	                    << "]" << std::endl;
	                // ----- DEBUG ----> */
	                // new edge
	                es0.insert(ce1);
	                nes.addNFace(ce0);
	                neCount++;
	            } else 
	            {
	                /* <---- DEBUG ----- //
	                std::cerr << "[Mesh::createEdges] DEBUG: "
	                    "not adding edge to new edge set" 
	                    << std::endl;
	                // ----- DEBUG ----> */
	            }
	        }
	    }
	}
	if (neCount > 0)
	{
	    clearEdges();
	    addEdges(nes.getNFaces());
	}
	return neCount;
}

void Mesh::merge(const Ionflux::GeoUtils::Mesh& other)
{
	unsigned int numVerts0 = getNumVertices();
	unsigned int numVerts1 = other.getNumVertices();
	// vertices
	for (unsigned int i = 0; i < numVerts1; i++)
	{
	    Vertex3* cv0 = Ionflux::ObjectBase::nullPointerCheck(
	        other.getVertex(i), this, "merge", "Source mesh vertex");
	    addVertex(cv0->copy());
	}
	// faces
	unsigned int numFaces1 = other.getNumFaces();
	for (unsigned int i = 0; i < numFaces1; i++)
	{
	    Face* cf0 = Ionflux::ObjectBase::nullPointerCheck(
	        other.getFace(i), this, "merge", "Source mesh face");
	    Face* nf0 = cf0->copy();
	    nf0->applyVertexIndexOffset(numVerts0);
	    addFace(nf0);
	}
	// edges
	unsigned int numEdges1 = other.getNumEdges();
	for (unsigned int i = 0; i < numEdges1; i++)
	{
	    NFace* ce0 = Ionflux::ObjectBase::nullPointerCheck(
	        other.getEdge(i), this, "merge", "Source mesh edge");
	    NFace* ne0 = ce0->copy();
	    ne0->applyVertexIndexOffset(numVerts0);
	    addEdge(ne0);
	}
}

std::string Mesh::getValueString() const
{
	std::ostringstream status;
	// vertices
	status << "verts: ";
	if (vertexSource != 0)
	{
	    unsigned int numVerts = vertexSource->getNumVertices();
	    if (numVerts > 0)
	    {
	        status << "[";
	        bool e0 = true;
	        for (unsigned int i = 0; i < numVerts; i++)
	        {
	            Vertex3* v0 = vertexSource->getVertex(i);
	            if (!e0)
	                status << ", ";
	            else
	                e0 = false;
	            status << "(" << v0->getValueString() << ")";
	        }
	        status << "]";
	    } else
	        status << "<none>";
	} else
	    status << "<none>";
	// faces
	status << "; faces: ";
	unsigned int numFaces = faces.size();
	if (numFaces > 0)
	{
	    status << "[";
	    bool e0 = true;
	    for (FaceVector::const_iterator i = faces.begin(); 
	        i != faces.end(); i++)
	    {
	        Face* f0 = *i;
	        if (!e0)
	            status << ", ";
	        else
	            e0 = false;
	        status << "[" << f0->getValueString() << "]";
	    }
	    status << "]";
	} else
	    status << "<none>";
	// edges
	status << "; edges: ";
	unsigned int numEdges = edges.size();
	if (numEdges > 0)
	{
	    status << "[";
	    bool ef0 = true;
	    for (NFaceVector::const_iterator i = edges.begin(); 
	        i != edges.end(); i++)
	    {
	        NFace* e0 = *i;
	        if (!ef0)
	            status << ", ";
	        else
	            ef0 = false;
	        status << "[" << e0->getValueString() << "]";
	    }
	    status << "]";
	} else
	    status << "<none>";
	// transformable object data
	std::string ts0(TransformableObject::getValueString());
	if (ts0.size() > 0)
	    status << "; " << ts0;
	return status.str();
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
	/* <---- DEBUG ----- //
	std::cerr << "[Mesh::cube] DEBUG: "
	    << "Adding faces..." << std::endl;
	// <---- DEBUG ----- */
	FaceVector faces0;
	faces0.push_back(Face::create(0, 3, 4, 7, m0->getVertexSource()));
	faces0.push_back(Face::create(3, 2, 5, 4, m0->getVertexSource()));
	faces0.push_back(Face::create(1, 6, 5, 2, m0->getVertexSource()));
	faces0.push_back(Face::create(0, 7, 6, 1, m0->getVertexSource()));
	faces0.push_back(Face::create(4, 5, 6, 7, m0->getVertexSource()));
	faces0.push_back(Face::create(0, 1, 2, 3, m0->getVertexSource()));
	m0->addFaces(faces0);
	/* <---- DEBUG ----- //
	std::cerr << "[Mesh::cube] DEBUG: "
	    << "Updating mesh..." << std::endl;
	// <---- DEBUG ----- */
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

Ionflux::GeoUtils::Mesh* Mesh::grid(unsigned int subDivsX, unsigned int 
subDivsY)
{
	if (subDivsX < 1)
	{
	    std::ostringstream status;
	    status << "[Mesh::grid] "
	        "Subdivisions (X) must be at least 1.";
	    throw GeoUtilsError(status.str());
	}
	if (subDivsY < 1)
	{
	    std::ostringstream status;
	    status << "[Mesh::grid] "
	        "Subdivisions (Y) must be at least 1.";
	    throw GeoUtilsError(status.str());
	}
	Mesh* m0 = create();
	double s = 0.5;
	// Vertices.
	Vertex3Vector verts0;
	double dx = 2. * s / subDivsX;
	double dy = 2. * s / subDivsY;
	for (unsigned int i = 0; i <= subDivsY; i++)
	{
	    for (unsigned int j = 0; j <= subDivsX; j++)
	    {
	        verts0.push_back(Vertex::create(-s + j * dx, 
	            -s + i * dy, 0));
	    }
	}
	m0->addVertices(verts0);
	// Faces.
	FaceVector faces0;
	for (unsigned int i = 0; i < subDivsY; i++)
	{
	    for (unsigned int j = 0; j < subDivsX; j++)
	    {
	        faces0.push_back(Face::create(
	            (j + 1) + i * (subDivsX + 1), 
	            (j + 1) + (i + 1) * (subDivsX + 1), 
	            j + (i + 1) * (subDivsX + 1), 
	            j + i * (subDivsX + 1), 
	            /*
	            j + i * (subDivsX + 1), 
	            j + (i + 1) * (subDivsX + 1), 
	            (j + 1) + (i + 1) * (subDivsX + 1), 
	            (j + 1) + i * (subDivsX + 1), 
	            */
	            m0->getVertexSource()));
	    }
	}
	m0->addFaces(faces0);
	m0->update();
	return m0;
}

Ionflux::GeoUtils::Mesh* Mesh::fiber(unsigned int aSubDivs, unsigned int 
lSubDivs, double length, double radius)
{
	Mesh* m0 = create();
	double s = 0.5 * length;
	// Vertices.
	Vertex3Vector verts0;
	double dPhi = 2. * M_PI / aSubDivs;
	double ds = length / lSubDivs;
	// Bottom center vertex.
	verts0.push_back(Vertex::create(0., 0., -s));
	// Hull vertices.
	for (unsigned int i = 0; i <= lSubDivs; i++)
	{
	    double z = -s + i * ds;
	    for (unsigned int j = 0; j < aSubDivs; j++)
	    {
	        double x = radius * ::sin(j * dPhi);
	        double y = radius * ::cos(j * dPhi);
	        verts0.push_back(Vertex::create(x, y, z));
	    }
	}
	// Top center vertex.
	verts0.push_back(Vertex::create(0., 0., s));
	m0->addVertices(verts0);
	// Faces.
	FaceVector faces0;
	// Hull faces.
	for (unsigned int i = 0; i < lSubDivs; i++)
	{
	    for (unsigned int j = 0; j < aSubDivs; j++)
	    {
	        if (j < (aSubDivs - 1))
	            faces0.push_back(Face::create(
	                1 + i * aSubDivs + j, 
	                1 + (i + 1) * aSubDivs + j, 
	                1 + (i + 1) * aSubDivs + j + 1, 
	                1 + i * aSubDivs + j + 1, 
	                m0->getVertexSource()));
	        else
	            faces0.push_back(Face::create(
	                1 + i * aSubDivs + j, 
	                1 + (i + 1) * aSubDivs + j, 
	                1 + (i + 1) * aSubDivs, 
	                1 + i * aSubDivs, 
	                m0->getVertexSource()));
	    }
	}
	// Bottom faces.
	unsigned int i0 = 0;
	for (unsigned int i = 0; i < aSubDivs; i++)
	{
	    if (i < (aSubDivs - 1))
	        faces0.push_back(Face::create(
	            i0, i + 1, i + 2, Face::VERTEX_INDEX_NONE, 
	            m0->getVertexSource()));
	    else
	        faces0.push_back(Face::create(
	            i0, i + 1, 1, Face::VERTEX_INDEX_NONE, 
	            m0->getVertexSource()));
	}
	// Top faces.
	i0 = verts0.size() - 1;
	unsigned int k0 = aSubDivs * lSubDivs;
	for (unsigned int i = 0; i < aSubDivs; i++)
	{
	    if (i < (aSubDivs - 1))
	        faces0.push_back(Face::create(
	            i0, k0 + i + 2, k0 + i + 1, Face::VERTEX_INDEX_NONE, 
	            m0->getVertexSource()));
	    else
	        faces0.push_back(Face::create(
	            i0, k0 + 1, k0 + i + 1, Face::VERTEX_INDEX_NONE, 
	            m0->getVertexSource()));
	}
	m0->addFaces(faces0);
	m0->update();
	return m0;
}

std::string Mesh::getNFaceTypeIDString(Ionflux::GeoUtils::MeshNFaceTypeID 
typeID)
{
	if (typeID == NFACE_TYPE_FACE)
	    return "face";
	if (typeID == NFACE_TYPE_EDGE)
	    return "edge";
	return "<unknown>";
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

Ionflux::GeoUtils::Vertex3* Mesh::addVertex()
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->addVertex();
}

void Mesh::addVertices(const std::vector<Ionflux::GeoUtils::Vertex3*>& 
newVertices)
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->addVertices(newVertices);
}

void Mesh::addVertices(Ionflux::GeoUtils::Mesh* newVertices)
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->addVertices(newVertices->vertexSource);
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

Ionflux::GeoUtils::Face* Mesh::addFace()
{
	Ionflux::GeoUtils::Face* o0 = Face::create();
	addFace(o0);
	return o0;
}

void Mesh::addFaces(const std::vector<Ionflux::GeoUtils::Face*>& newFaces)
{
	for (std::vector<Ionflux::GeoUtils::Face*>::const_iterator i = newFaces.begin(); 
	    i != newFaces.end(); i++)
	    addFace(*i);
}

void Mesh::addFaces(Ionflux::GeoUtils::Mesh* newFaces)
{
	for (unsigned int i = 0; 
	    i < newFaces->getNumFaces(); i++)
	    addFace(newFaces->getFace(i));
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

unsigned int Mesh::getNumEdges() const
{
    return edges.size();
}

Ionflux::GeoUtils::NFace* Mesh::getEdge(unsigned int elementIndex) const
{
    if (elementIndex < edges.size())
		return edges[elementIndex];
	return 0;
}

int Mesh::findEdge(Ionflux::GeoUtils::NFace* needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::NFace* currentEdge = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < edges.size()))
	{
		currentEdge = edges[i];
		if (currentEdge == needle)
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

std::vector<Ionflux::GeoUtils::NFace*>& Mesh::getEdges()
{
    return edges;
}

void Mesh::addEdge(Ionflux::GeoUtils::NFace* addElement)
{
	addLocalRef(addElement);
	edges.push_back(addElement);
}

Ionflux::GeoUtils::NFace* Mesh::addEdge()
{
	Ionflux::GeoUtils::NFace* o0 = NFace::create();
	addEdge(o0);
	return o0;
}

void Mesh::addEdges(const std::vector<Ionflux::GeoUtils::NFace*>& newEdges)
{
	for (std::vector<Ionflux::GeoUtils::NFace*>::const_iterator i = newEdges.begin(); 
	    i != newEdges.end(); i++)
	    addEdge(*i);
}

void Mesh::addEdges(Ionflux::GeoUtils::Mesh* newEdges)
{
	for (unsigned int i = 0; 
	    i < newEdges->getNumEdges(); i++)
	    addEdge(newEdges->getEdge(i));
}

void Mesh::removeEdge(Ionflux::GeoUtils::NFace* removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::NFace* currentEdge = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < edges.size()))
	{
		currentEdge = edges[i];
		if (currentEdge == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		edges.erase(edges.begin() + i);
		if (currentEdge != 0)
			removeLocalRef(currentEdge);
	}
}

void Mesh::removeEdgeIndex(unsigned int removeIndex)
{
    if (removeIndex > edges.size())
        return;
	Ionflux::GeoUtils::NFace* e0 = edges[removeIndex];
    edges.erase(edges.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void Mesh::clearEdges()
{
    std::vector<Ionflux::GeoUtils::NFace*>::iterator i;
	for (i = edges.begin(); i != edges.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	edges.clear();
}

Ionflux::GeoUtils::Mesh& Mesh::operator=(const Ionflux::GeoUtils::Mesh& 
other)
{
    if (this == &other)
        return *this;
    TransformableObject::operator=(other);
    setVertexSource(other.vertexSource);
    // faces
    FaceVector f0;
    for (FaceVector::const_iterator i = other.faces.begin(); 
        i != other.faces.end(); i++)
    {
        Face* ft0 = Ionflux::ObjectBase::nullPointerCheck(*i, this, 
            "operator=", "Face");
        f0.push_back(ft0->copy());
    }
    clearFaces();
    addFaces(f0);
    // edges
    NFaceVector ev0;
    for (NFaceVector::const_iterator i = other.edges.begin(); 
        i != other.edges.end(); i++)
    {
        NFace* e0 = Ionflux::ObjectBase::nullPointerCheck(*i, this, 
            "operator=", "Edge");
        ev0.push_back(e0->copy());
    }
    clearEdges();
    addEdges(ev0);
    BoxBoundsItem::clear();
    TransformableObject::clear();
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

Ionflux::GeoUtils::Mesh* Mesh::create(Ionflux::GeoUtils::Vertex3Vector* 
initVerts, const Ionflux::GeoUtils::FaceVector* initFaces, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Mesh* newObject = new Mesh(initVerts, initFaces);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Mesh* Mesh::create(Ionflux::GeoUtils::Vertex3Set* 
initVertexSource, const Ionflux::GeoUtils::FaceVector* initFaces, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Mesh* newObject = new Mesh(initVertexSource, initFaces);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Mesh::getMemSize() const
{
    return sizeof *this;
}

std::string Mesh::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Mesh::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::GeoUtils::TransformableObject::getXMLAttributeData();
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
	bool haveBCData = false;
	if (d0.str().size() > 0)
	    haveBCData = true;
	bool xcFirst = true;
    if (vertexSource != 0)
    {
        if (!xcFirst || haveBCData)
            d0 << "\n";
	    d0 << vertexSource->getXML0(indentLevel, "pname=\"vertex_source\"");
	    xcFirst = false;
    }
	if (!xcFirst || haveBCData)
	    d0 << "\n";
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0(faces, "vec", "", 
        indentLevel, "pname=\"faces\"");
    xcFirst = false;
	if (!xcFirst || haveBCData)
	    d0 << "\n";
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0(edges, "vec", "", 
        indentLevel, "pname=\"edges\"");
    xcFirst = false;
	target = d0.str();
}

void Mesh::loadFromXMLFile(const std::string& fileName)
{
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, getXMLElementName());
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
Mesh::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::MeshXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::MeshXMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 0;
        bFac = Ionflux::GeoUtils::TransformableObject::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file Mesh.cpp
 * \brief Mesh implementation.
 */
