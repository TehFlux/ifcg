/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polygon2.cpp                    Polygon (2D) (implementation).
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

#include "geoutils/Polygon2.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Matrix2.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

Polygon2ClassInfo::Polygon2ClassInfo()
{
	name = "Polygon2";
	desc = "Polygon (2D)";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

Polygon2ClassInfo::~Polygon2ClassInfo()
{
}

// run-time type information instance constants
const Polygon2ClassInfo Polygon2::polygon2ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Polygon2::CLASS_INFO = &Polygon2::polygon2ClassInfo;

Polygon2::Polygon2()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Polygon2::Polygon2(const Ionflux::GeoUtils::Polygon2& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Polygon2::Polygon2(Ionflux::GeoUtils::Vertex2Vector* initVertices, 
Ionflux::GeoUtils::EdgeVector* initEdges)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initVertices != 0)
	    addVertices(*initVertices);
	if (initEdges != 0)
	    addEdges(*initEdges);
}

Polygon2::~Polygon2()
{
	clearVertices();
	clearEdges();
	// TODO: Nothing ATM. ;-)
}

void Polygon2::addVertices(Ionflux::GeoUtils::Vertex2Vector& newVertices)
{
	if (newVertices.size() == 0)
	    return;
	Ionflux::GeoUtils::Vertex2Vector::iterator i;
	for (i = newVertices.begin(); i < newVertices.end(); i++)
	    addVertex(*i);
}

void Polygon2::addEdges(Ionflux::GeoUtils::EdgeVector& newEdges)
{
	if (newEdges.size() == 0)
	    return;
	Ionflux::GeoUtils::EdgeVector::iterator i;
	for (i = newEdges.begin(); i < newEdges.end(); i++)
	    addEdge(*i);
}

int Polygon2::createEdges()
{
	clearEdges();
	if (vertices.size() < 2)
	    return 0;
	for (unsigned int i = 1; i < vertices.size(); i++)
	    addEdge(new Edge(i - 1, 1));
	if (vertices.size() >= 3)
	    addEdge(new Edge(vertices.size() - 1, 0));
	return edges.size();
}

bool Polygon2::checkVertex(const Ionflux::GeoUtils::Vertex2& v, double t)
{
	ostringstream status;
	int intersections = 0;
	for (unsigned int i = 0; i < edges.size(); i++)
	{
	    Edge& e = *edges[i];
	    Vertex2& a = *vertices[e[0]];
	    Vertex2& b = *vertices[e[1]];
	    Vertex2 vt(v.getX(), v.getY());
	    /* <---- DEBUG ----- //
	    status.str("");
	    status << "v = " << v << ", a = " << a << ", b = " << b;
	    log(IFLogMessage(status.str(), VL_DEBUG, this, "checkVertex"));
	    // ----- DEBUG ----> */
	    if (vt.eq(a, t) || vt.eq(b, t))
	    {
	        /* <---- DEBUG ----- //
	        log(IFLogMessage("Test vertex incident to poly vertex.", 
	            VL_DEBUG, this, "checkVertex"));
	        // ----- DEBUG ----> */
	        return true;
	    }
	    if (eq(vt.getY(), a.getY(), t) && eq(vt.getY(), b.getY(), t))
	    {
	        // Horizontal edge.
	        /* <---- DEBUG ----- //
	        log(IFLogMessage("Horizontal edge.", 
	            VL_DEBUG, this, "checkVertex"));
	        // ----- DEBUG ----> */
	        if (gtOrEq(vt.getX(), min(a.getX(), b.getX()), t) 
	            && ltOrEq(vt.getX(), max(a.getX(), b.getX()), t))
	        {
	            // Vertex lies on horizontal edge.
	            /* <---- DEBUG ----- //
	            log(IFLogMessage("Vertex lies on horizontal edge.", 
	                VL_DEBUG, this, "checkVertex"));
	            // ----- DEBUG ----> */
	            return true;
	        } else
	        {
	            /* <---- DEBUG ----- //
	            log(IFLogMessage("Vertex does not lie on horizontal edge.", 
	                VL_DEBUG, this, "checkVertex"));
	            // ----- DEBUG ----> */
	        }
	    } else
	    {
	        /* Rather ugly: Offset the point so it will not have the same 
	           coordinate as any polygon vertex as this situation makes 
	           correct intersection counts difficult. */
	        if (eq(vt.getY(), a.getY(), t))
	            vt.setY(vt.getY() - 1.1 * t);
	        if (eq(vt.getY(), b.getY(), t))
	            vt.setY(vt.getY() - 1.1 * t);
	        if (!((gt(vt.getX(), a.getX(), t) 
	                && gt(vt.getX(), b.getX(), t))
	            || (lt(vt.getY(), a.getY(), t) 
	                && lt(vt.getY(), b.getY(), t))
	            || (gt(vt.getY(), a.getY(), t) 
	                && gt(vt.getY(), b.getY(), t))))
	        {
	            // Find intersection in vertex space.
	            Vector2 r = Matrix2(b.getX() - a.getX(), -1., 
	                b.getY() - a.getY(), 0.).solve(
	                    Vector2(vt.getX() - a.getX(), vt.getY() - a.getY()));
	            Vertex2 iv(r[1], 0.);
	            /* <---- DEBUG ----- //
	            status.str("");
	            status << "intersection: iv = " << iv;
	            log(IFLogMessage("Vertex does not lie on horizontal edge.", 
	                VL_DEBUG, this, "checkVertex"));
	            // ----- DEBUG ----> */
	            if (eq(iv.getX(), 0., t) && eq(iv.getY(), 0., t))
	            {
	                // Vertex lies on an edge of the poly.
	                return true;
	            } else
	            if (gt(iv.getX(), 0., t))
	                intersections += 1;
	        }
	    }
	}
	/* <---- DEBUG ----- //
	status.str("");
	status << "intersections = " + intersections;
	log(IFLogMessage("Vertex does not lie on horizontal edge.", 
	    VL_DEBUG, this, "checkVertex"));
	// ----- DEBUG ----> */
	if (intersections % 2 == 0)
	    return false;
	return true;
}

unsigned int Polygon2::getNumVertices() const
{
    return vertices.size();
}

Ionflux::GeoUtils::Vertex2* Polygon2::getVertex(unsigned int elementIndex) 
const
{
    if (elementIndex < vertices.size())
		return vertices[elementIndex];
	return 0;
}

int Polygon2::findVertex(Ionflux::GeoUtils::Vertex2* needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::Vertex2* currentVertex = 0;
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

std::vector<Ionflux::GeoUtils::Vertex2*>& Polygon2::getVertices()
{
    return vertices;
}

void Polygon2::addVertex(Ionflux::GeoUtils::Vertex2* addElement)
{
	addLocalRef(addElement);
	vertices.push_back(addElement);
}

void Polygon2::removeVertex(Ionflux::GeoUtils::Vertex2* removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::Vertex2* currentVertex = 0;
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
		if (currentVertex != 0)
			removeLocalRef(currentVertex);
	}
}

void Polygon2::removeVertexIndex(unsigned int removeIndex)
{
    if (removeIndex > vertices.size())
        return;
	Ionflux::GeoUtils::Vertex2* e0 = vertices[removeIndex];
    vertices.erase(vertices.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void Polygon2::clearVertices()
{
    std::vector<Ionflux::GeoUtils::Vertex2*>::iterator i;
	for (i = vertices.begin(); i != vertices.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	vertices.clear();
}

unsigned int Polygon2::getNumEdges() const
{
    return edges.size();
}

Ionflux::GeoUtils::Edge* Polygon2::getEdge(unsigned int elementIndex) const
{
    if (elementIndex < edges.size())
		return edges[elementIndex];
	return 0;
}

int Polygon2::findEdge(Ionflux::GeoUtils::Edge* needle, unsigned int 
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

std::vector<Ionflux::GeoUtils::Edge*>& Polygon2::getEdges()
{
    return edges;
}

void Polygon2::addEdge(Ionflux::GeoUtils::Edge* addElement)
{
	addLocalRef(addElement);
	edges.push_back(addElement);
}

void Polygon2::removeEdge(Ionflux::GeoUtils::Edge* removeElement)
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

void Polygon2::removeEdgeIndex(unsigned int removeIndex)
{
    if (removeIndex > edges.size())
        return;
	Ionflux::GeoUtils::Edge* e0 = edges[removeIndex];
    edges.erase(edges.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void Polygon2::clearEdges()
{
    std::vector<Ionflux::GeoUtils::Edge*>::iterator i;
	for (i = edges.begin(); i != edges.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	edges.clear();
}

Ionflux::GeoUtils::Polygon2& Polygon2::operator=(const 
Ionflux::GeoUtils::Polygon2& other)
{
    Vertex2Vector v0;
    for (Vertex2Vector::const_iterator i = other.vertices.begin(); 
        i != other.vertices.end(); i++)
        v0.push_back(new Vertex2(*(*i)));
    clearVertices();
    addVertices(v0);
	return *this;
}

Ionflux::GeoUtils::Polygon2* Polygon2::copy() const
{
    Polygon2* newPolygon2 = 
        new Polygon2();
    *newPolygon2 = *this;
    return newPolygon2;
}

}

}

/** \file Polygon2.cpp
 * \brief Polygon (2D) implementation.
 */
