/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polygon3.cpp                    Polygon (3D) (implementation).
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

#include "geoutils/Polygon3.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

Polygon3ClassInfo::Polygon3ClassInfo()
{
	name = "Polygon3";
	desc = "Polygon (3D)";
}

Polygon3ClassInfo::~Polygon3ClassInfo()
{
}

// run-time type information instance constants
const Polygon3ClassInfo Polygon3::polygon3ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Polygon3::CLASS_INFO = &Polygon3::polygon3ClassInfo;

Polygon3::Polygon3()
: vertexSource(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setVertexSource(Vertex3Set::create());
}

Polygon3::Polygon3(const Ionflux::GeoUtils::Polygon3& other)
: vertexSource(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Polygon3::Polygon3(Ionflux::GeoUtils::Vertex3Vector* initVertices, 
Ionflux::GeoUtils::EdgeVector* initEdges)
: vertexSource(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setVertexSource(Vertex3Set::create());
	if (initVertices != 0)
	    addVertices(*initVertices);
	if (initEdges != 0)
	    addEdges(*initEdges);
}

Polygon3::Polygon3(Ionflux::GeoUtils::Vertex3Set* initVertexSource, 
Ionflux::GeoUtils::EdgeVector* initEdges)
: vertexSource(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initVertexSource)
	    setVertexSource(initVertexSource);
	else
	    setVertexSource(Vertex3Set::create());
	if (initEdges != 0)
	    addEdges(*initEdges);
}

Polygon3::Polygon3(const Ionflux::GeoUtils::Vertex3* v0, const 
Ionflux::GeoUtils::Vertex3* v1, const Ionflux::GeoUtils::Vertex3* v2, const
Ionflux::GeoUtils::Vertex3* v3)
: vertexSource(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setVertexSource(Vertex3Set::create());
	Vertex3* vt0 = 0;
	if (v0 != 0)
	{
	    vt0 = Vertex3::create();
	    *vt0 = *v0;
	    addVertex(vt0);
	}
	if (v1 != 0)
	{
	    vt0 = Vertex3::create();
	    *vt0 = *v1;
	    addVertex(vt0);
	}
	if (v2 != 0)
	{
	    vt0 = Vertex3::create();
	    *vt0 = *v2;
	    addVertex(vt0);
	}
	if (v3 != 0)
	{
	    vt0 = Vertex3::create();
	    *vt0 = *v3;
	    addVertex(vt0);
	}
	createEdges();
}

Polygon3::~Polygon3()
{
	clearEdges();
	// TODO: Nothing ATM. ;-)
}

void Polygon3::recalculateBounds()
{
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source not set.");
	TransformableObject::recalculateBounds();
	if (!useTransform && !useVI)
	{
	    *boundsCache = vertexSource->getBounds();
	    return;
	}
	// Adjust for transformation.
	Polygon3* p0 = copy();
	p0->applyTransform();
	if (p0->useTransform)
	    throw GeoUtilsError("Transform matrix still in use after "
	        "applying transformations.");
	*boundsCache = p0->getBounds();
	delete p0;
}

void Polygon3::copyVertices()
{
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source not set.");
	setVertexSource(&(vertexSource->duplicate()));
}

Ionflux::GeoUtils::Vertex3* Polygon3::addVertex()
{
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source not set.");
	return vertexSource->addVertex();
}

void Polygon3::addVertices(Ionflux::GeoUtils::Vertex3Vector& newVerts)
{
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source not set.");
	for (Vertex3Vector::iterator i = newVerts.begin(); 
	    i != newVerts.end(); i++)
	    vertexSource->addVertex(*i);
}

void Polygon3::addVertices(Ionflux::GeoUtils::Vertex3Set& newVerts)
{
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source not set.");
	for (unsigned int i = 0; i < newVerts.getNumVertices(); i++)
	    vertexSource->addVertex(newVerts.getVertex(i));
}

Ionflux::GeoUtils::Edge* Polygon3::addEdge()
{
	Edge* e0 = new Edge();
	if (e0 == 0)
	    throw GeoUtilsError("Could not allocate object.");
	addEdge(e0);
	return e0;
}

void Polygon3::addEdges(Ionflux::GeoUtils::EdgeVector& newEdges)
{
	if (newEdges.size() == 0)
	    return;
	for (Ionflux::GeoUtils::EdgeVector::iterator i = newEdges.begin(); 
	    i != newEdges.end(); i++)
	    addEdge(*i);
}

int Polygon3::createEdges()
{
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source not set.");
	clearEdges();
	unsigned int numVerts = getNumVertices();
	if (numVerts < 2)
	    return 0;
	Edge* e0 = 0;
	for (unsigned int i = 1; i < numVerts; i++)
	{
	    e0 = Edge::create();
	    e0->setV0(i - 1);
	    e0->setV1(i);
	    addEdge(e0);
	}
	if (numVerts >= 3)
	{
	    e0 = Edge::create();
	    e0->setV0(numVerts - 1);
	    e0->setV1(0);
	    addEdge(e0);
	}
	return edges.size();
}

Ionflux::GeoUtils::Plane3 Polygon3::getPlane(int v0, int v1, int v2) const
{
	unsigned int numVerts = getNumVertices();
	if (v0 < 0)
	    v0 = numVerts + v0;
	if (v1 < 0)
	    v1 = numVerts + v1;
	if (v2 < 0)
	    v2 = numVerts + v2;
	if ((v0 < 0) || (static_cast<unsigned int>(v0) >= numVerts))
	{
	    std::ostringstream status;
	    status << "[Polygon3::getPlane] "
	        "Vertex index v0 out of range (numVerts = " << numVerts 
	        << ", v0 = " << v0 << ").";
	    throw GeoUtilsError(status.str());
	}
	if ((v1 < 0) || (static_cast<unsigned int>(v1) >= numVerts))
	{
	    std::ostringstream status;
	    status << "[Polygon3::getPlane] "
	        "Vertex index v1 out of range (numVerts = " << numVerts 
	        << ", v1 = " << v1 << ").";
	    throw GeoUtilsError(status.str());
	}
	if ((v2 < 0) || (static_cast<unsigned int>(v2) >= numVerts))
	{
	    std::ostringstream status;
	    status << "[Polygon3::getPlane] "
	        "Vertex index v2 out of range (numVerts = " << numVerts 
	        << ", v2 = " << v2 << ").";
	    throw GeoUtilsError(status.str());
	}
	Vector3 a = getVertex(v0)->getVector();
	Vector3 b = getVertex(v1)->getVector();
	Vector3 c = getVertex(v2)->getVector();
	return Plane3(a, b - a, c - a);;
}

std::string Polygon3::getValueString() const
{
	ostringstream status;
	status << "verts: [";
	bool e0 = true;
	for (unsigned int i = 0; i < getNumVertices(); i++)
	{
	    Vertex3* v0 = getVertex(i);
	    if (!e0)
	        status << ", ";
	    else
	        e0 = false;
	    status << "(" << v0->getValueString() << ")";
	}
	status << "]";
	if (edges.size() > 0)
	{
	    status << " edges: [";
	    e0 = true;
	    for (EdgeVector::const_iterator j = edges.begin(); 
	        j != edges.end(); j++)
	    {
	        if (!e0)
	            status << ", ";
	        else
	            e0 = false;
	        status << "(" << (*j)->getValueString() << ")";
	    }
	    status << "]";
	}
	if (!useTransform && !useVI)
	    return status.str();
	status << "; " << TransformableObject::getValueString();
	return status.str();
}

std::string Polygon3::getSVG(const std::string& attrs, const std::string& 
elementID, Ionflux::GeoUtils::AxisID axis, Ionflux::GeoUtils::SVGShapeType 
shapeType, bool closePath)
{
	ostringstream svg;
	AxisID oa[2];
	if (axis == AXIS_Y)
	{
	    oa[0] = AXIS_X;
	    oa[1] = AXIS_Z;
	} else
	if (axis == AXIS_X)
	{
	    oa[0] = AXIS_Y;
	    oa[1] = AXIS_Z;
	} else
	if (axis == AXIS_Z)
	{
	    oa[0] = AXIS_X;
	    oa[1] = AXIS_Y;
	} else
	{
	    svg << "Invalid axis: " << axis;
	    throw GeoUtilsError(svg.str());
	}
	if (shapeType == SHAPE_TYPE_POLYGON)
	    svg << "<polygon";
	else
	if (shapeType == SHAPE_TYPE_PATH)
	    svg << "<path";
	else
	{
	    std::ostringstream message;
	    message << "Unknown shape type: " << shapeType;
	    throw GeoUtilsError(message.str());
	}
	if (elementID.size() > 0)
	    svg << " id=\"" << elementID << "\"";
	if (attrs.size() > 0)
	    svg << " " << attrs;
	if (shapeType == SHAPE_TYPE_POLYGON)
	    svg << " points=\"";
	else
	    svg << " d=\"";
	bool s0 = true;
	/* <---- DEBUG ----- //
	ostringstream message;
	message << "Before applyTransform(): numVertices = " << getNumVertices();
	log(IFLogMessage(message.str(), VL_DEBUG, this, "getSVG"));
	// <---- DEBUG ----- */
	applyTransform();
	/* <---- DEBUG ----- //
	message.str("");
	message << "After applyTransform(): numVertices = " << getNumVertices();
	log(IFLogMessage(message.str(), VL_DEBUG, this, "getSVG"));
	// <---- DEBUG ----- */
	for (unsigned int i = 0; i < getNumVertices(); i++)
	{
	    Vertex3* v0 = getVertex(i);
	    if (!s0)
	    {
	        svg << " ";
	        if (shapeType == SHAPE_TYPE_PATH)
	            svg << "L ";
	    } else
	    {
	        if (shapeType == SHAPE_TYPE_PATH)
	            svg << "M ";
	        s0 = false;
	    }
	    svg << (*v0)[oa[0]] << "," << (*v0)[oa[1]];
	}
	if (closePath 
	    && (shapeType == SHAPE_TYPE_PATH))
	    svg << " z";
	svg << "\" />";
	return svg.str();
}

std::string Polygon3::getSVG(const Ionflux::GeoUtils::SVGShapeStyle& style,
const std::string& elementID, Ionflux::GeoUtils::AxisID axis, 
Ionflux::GeoUtils::SVGShapeType shapeType, bool closePath)
{
	std::string a0 = getSVGPolygonStyle(style);
	return getSVG(a0, elementID, axis, shapeType, closePath);
}

Ionflux::GeoUtils::Vector3 Polygon3::getBarycenter()
{
	if (vertexSource == 0)
	    throw GeoUtilsError("Vertex source not set.");
	if (!useTransform && !useVI)
	    return vertexSource->getBarycenter();
	// Adjust for transformation.
	Vertex3 v0(vertexSource->getBarycenter());
	if (useTransform)
	    v0.transform(transformMatrix);
	if (useVI)
	    v0.transformVI(viewMatrix, &imageMatrix);
	return v0.getVector();
}

void Polygon3::applyTransform(bool recursive)
{
	if (!useTransform && !useVI)
	{
	    if (recursive)
	        vertexSource->applyTransform(recursive);
	    return;
	}
	copyVertices();
	if (useTransform)
	{
	    vertexSource->transform(transformMatrix);
	    vertexSource->applyTransform(recursive);
	    transformMatrix = Matrix4::UNIT;
	    useTransform = false;
	}
	if (useVI)
	{
	    vertexSource->transformVI(viewMatrix, &imageMatrix);
	    vertexSource->applyTransform(recursive);
	    viewMatrix = Matrix4::UNIT;
	    imageMatrix = Matrix4::UNIT;
	    useVI = false;
	}
}

Ionflux::GeoUtils::Polygon3& Polygon3::scale(const 
Ionflux::GeoUtils::Vector3& s)
{
	TransformableObject::scale(s);
	return *this;
}

Ionflux::GeoUtils::Polygon3& Polygon3::translate(const 
Ionflux::GeoUtils::Vector3& t)
{
	TransformableObject::translate(t);
	return *this;
}

Ionflux::GeoUtils::Polygon3& Polygon3::rotate(double phi, 
Ionflux::GeoUtils::AxisID axis)
{
	TransformableObject::rotate(phi, axis);
	return *this;
}

Ionflux::GeoUtils::Polygon3& Polygon3::normalize()
{
	TransformableObject::normalize();
	return *this;
}

Ionflux::GeoUtils::Polygon3& 
Polygon3::center(Ionflux::GeoUtils::CenteringMethod method, 
Ionflux::GeoUtils::Vector3* origin)
{
	TransformableObject::center(method, origin);
	return *this;
}

Ionflux::GeoUtils::Polygon3& Polygon3::transform(const 
Ionflux::GeoUtils::Matrix4& matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Polygon3& Polygon3::transform(const 
Ionflux::GeoUtils::Matrix3& matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Polygon3& Polygon3::duplicate()
{
	// TODO: Implementation.
	return *copy();
}

bool Polygon3::isPlanar(double t)
{
	Plane3 pl0 = getPlane();
	for (unsigned int i = 0; i < getNumVertices(); i++)
	{
	    double d0 = getVertex(i)->distanceToPlane(pl0);
	    if (!eq(d0, 0., t))
	        return false;
	}
	return true;
}

void Polygon3::getPolygon2(Ionflux::GeoUtils::Polygon2& target)
{
	for (unsigned int i = 0; i < getNumVertices(); i++)
	{
	    Vertex3* v0 = getVertex(i);
	    target.addVertex(new Vertex2(v0->getX(), v0->getY()));
	}
	for (unsigned int i = 0; i < getNumEdges(); i++)
	    target.addEdge(new Edge(*getEdge(i)));\
}

Ionflux::GeoUtils::Polygon3* Polygon3::square()
{
	Polygon3* p0 = Polygon3::create();
	double s = 0.5;
	Vertex3Vector verts0;
	verts0.push_back(Vertex3::create(-s, 0., -s));
	verts0.push_back(Vertex3::create(s, 0., -s));
	verts0.push_back(Vertex3::create(s, 0., s));
	verts0.push_back(Vertex3::create(-s, 0., s));
	p0->addVertices(verts0);
	p0->createEdges();
	return p0;
}

Ionflux::GeoUtils::Polygon3* Polygon3::circle(unsigned int resolution)
{
	Polygon3* p0 = Polygon3::create();
	double s = 0.5;
	Vertex3Vector verts0;
	for (unsigned int i = 0; i <= resolution; i++)
	{
	    Vertex3* v0 = Vertex3::create(s, 0., 0.);
	    v0->rotate(2. * M_PI / resolution * i, AXIS_Y);
	    verts0.push_back(v0);
	}
	p0->addVertices(verts0);
	p0->createEdges();
	return p0;
}

void Polygon3::setVertexSource(Ionflux::GeoUtils::Vertex3Set* 
newVertexSource)
{
	if (vertexSource == newVertexSource)
		return;
    if (newVertexSource != 0)
        addLocalRef(newVertexSource);
	if (vertexSource != 0)
		removeLocalRef(vertexSource);
	vertexSource = newVertexSource;
}

Ionflux::GeoUtils::Vertex3Set* Polygon3::getVertexSource() const
{
	return vertexSource;
}

unsigned int Polygon3::getNumVertices() const
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->getNumVertices();
}

Ionflux::GeoUtils::Vertex3* Polygon3::getVertex(unsigned int elementIndex) 
const
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->getVertex(elementIndex);
}

int Polygon3::findVertex(Ionflux::GeoUtils::Vertex3* needle, unsigned int 
occurence) const
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->findVertex(needle, occurence);
}

std::vector<Ionflux::GeoUtils::Vertex3*>& Polygon3::getVertices()
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->getVertices();
}

void Polygon3::addVertex(Ionflux::GeoUtils::Vertex3* addElement)
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->addVertex(addElement);
}

void Polygon3::removeVertex(Ionflux::GeoUtils::Vertex3* removeElement)
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->removeVertex(removeElement);
}

void Polygon3::removeVertexIndex(unsigned int removeIndex)
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->removeVertexIndex(removeIndex);
}

void Polygon3::clearVertices()
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->clearVertices();
}

unsigned int Polygon3::getNumEdges() const
{
    return edges.size();
}

Ionflux::GeoUtils::Edge* Polygon3::getEdge(unsigned int elementIndex) const
{
    if (elementIndex < edges.size())
		return edges[elementIndex];
	return 0;
}

int Polygon3::findEdge(Ionflux::GeoUtils::Edge* needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::Edge* currentEdge = 0;
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

std::vector<Ionflux::GeoUtils::Edge*>& Polygon3::getEdges()
{
    return edges;
}

void Polygon3::addEdge(Ionflux::GeoUtils::Edge* addElement)
{
	addLocalRef(addElement);
	edges.push_back(addElement);
}

void Polygon3::removeEdge(Ionflux::GeoUtils::Edge* removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::Edge* currentEdge = 0;
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

void Polygon3::removeEdgeIndex(unsigned int removeIndex)
{
    if (removeIndex > edges.size())
        return;
	Ionflux::GeoUtils::Edge* e0 = edges[removeIndex];
    edges.erase(edges.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void Polygon3::clearEdges()
{
    std::vector<Ionflux::GeoUtils::Edge*>::iterator i;
	for (i = edges.begin(); i != edges.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	edges.clear();
}

Ionflux::GeoUtils::Polygon3& Polygon3::operator=(const 
Ionflux::GeoUtils::Polygon3& other)
{
    TransformableObject::operator=(other);
    setVertexSource(other.vertexSource);
    EdgeVector e0;
    for (EdgeVector::const_iterator i = other.edges.begin(); 
        i != other.edges.end(); i++)
    {
        Edge* et0 = Edge::create();
        *et0 = *(*i);
        e0.push_back(et0);
    }
    clearEdges();
    addEdges(e0);
	return *this;
}

Ionflux::GeoUtils::Polygon3* Polygon3::copy() const
{
    Polygon3* newPolygon3 = create();
    *newPolygon3 = *this;
    return newPolygon3;
}

Ionflux::GeoUtils::Polygon3* 
Polygon3::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Polygon3*>(other);
}

Ionflux::GeoUtils::Polygon3* 
Polygon3::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Polygon3* newObject = new Polygon3();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file Polygon3.cpp
 * \brief Polygon (3D) implementation.
 */
