/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Line3.cpp                       Line (3D) (implementation).
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

#include "geoutils/Line3.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Matrix3.hpp"
#include "geoutils/Polygon2.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

Line3ClassInfo::Line3ClassInfo()
{
	name = "Line3";
	desc = "Line (3D)";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

Line3ClassInfo::~Line3ClassInfo()
{
}

// public member constants
const Ionflux::GeoUtils::Line3 Line3::X = Ionflux::GeoUtils::Line3(Ionflux::GeoUtils::Vector3::ZERO, 
    Ionflux::GeoUtils::Vector3::E_X);
const Ionflux::GeoUtils::Line3 Line3::Y = Ionflux::GeoUtils::Line3(Ionflux::GeoUtils::Vector3::ZERO, 
    Ionflux::GeoUtils::Vector3::E_Y);
const Ionflux::GeoUtils::Line3 Line3::Z = Ionflux::GeoUtils::Line3(Ionflux::GeoUtils::Vector3::ZERO, 
    Ionflux::GeoUtils::Vector3::E_Z);

// run-time type information instance constants
const Line3ClassInfo Line3::line3ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Line3::CLASS_INFO = &Line3::line3ClassInfo;

Line3::Line3()
: p(0., 0., 0.), u(1., 0., 0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Line3::Line3(const Ionflux::GeoUtils::Line3& other)
: p(0., 0., 0.), u(1., 0., 0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Line3::Line3(const Ionflux::GeoUtils::Vector3& initP, const 
Ionflux::GeoUtils::Vector3& initU)
: p(initP), u(initU)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Line3::~Line3()
{
	// TODO: Nothing ATM. ;-)
}

bool Line3::intersectPlane(const Ionflux::GeoUtils::Plane3& plane, 
Ionflux::GeoUtils::Vector3& result) const
{
	Vector3 r;
	try
	{
	    Matrix3 m;
	    m.setC0(plane.getU());
	    m.setC1(plane.getV());
	    m.setC2(u.flip());
	    r = m.solve((p - plane.getP()));
	} catch (GeoUtilsError& e)
	{
	    return false;
	}
	result = r[2] * u + p;
	return true;
}

bool Line3::intersectionInPoly(const Ionflux::GeoUtils::Polygon3& poly, 
double t) const
{
	if (poly.getNumVertices() < 3)
	    throw GeoUtilsError("Polygon does not have enough vertices.");
	Plane3 p0 = poly.getPlane();
	/*
	// Check for parallelity and incidence.
	Vector3 pn = p0.getNormal();
	if (eq(pn * u, 0, t))
	{
	    // Line is parallel to the plane.
	    if (eq(p.distanceToPlane(p0), 0, t))
	        // incidence
	        return true;
	    return false;
	}
	*/
	Vector3 ip;
	if (!intersectPlane(p0, ip))
	    return false;
	// Transform polygon and intersection point to tangent space.
	Matrix3 tm = p0.getTangentBase();
	Matrix3 tmInv = tm.invert();
	/* NOTE: The old Polygon3::transform() function was expected to 
	         translate the polygon vertices into the origin coordinate 
	         system. Since this has changed, we now have to translate the 
	         polygon explicitly. */
	Polygon3 tp0(poly);
	// We have at least three vertices because of the check above.
	Vector3 v0 = tp0.getVertex(0)->getVector();
	tp0.translate(v0.flip());
	tp0.transform(tmInv);
	tp0.applyTransform();
	// Check planarity.
	Polygon2 tp;
	for (unsigned int i = 0; i < tp0.getNumVertices(); i++)
	{
	    Vertex3* v = tp0.getVertex(i);
	    if (!eq(v->getZ(), 0., t))
	    {
	        ostringstream message;
	        message << "[Line3::intersectionInPoly] "
	            "Polygon is not planar (v = " 
	            + v->getString() + ").";
	        throw GeoUtilsError(message.str());
	    } else
	        tp.addVertex(new Vertex2(v->getX(), v->getY()));
	}
	for (unsigned int i = 0; i < tp0.getNumEdges(); i++)
	    tp.addEdge(new Edge(*tp0.getEdge(i)));
	Vertex3* origin = poly.getVertex(0);
	Vertex3 iv0(tmInv * (ip - origin->getVector()));
	Vertex2 iv(iv0.getX(), iv0.getY());
	return tp.checkVertex(iv, t);
}

bool Line3::operator==(const Ionflux::GeoUtils::Line3& other) const
{
	if (!((p == other.p) && (u == other.u)))
	        return false;
	return true;
}

bool Line3::operator!=(const Ionflux::GeoUtils::Line3& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

std::string Line3::getString() const
{
	ostringstream state;
	state << getClassName() << "[" << p.getString() 
	    << ", " << u.getString() << "]";
	return state.str();
}

void Line3::setP(const Ionflux::GeoUtils::Vector3& newP)
{
	p = newP;
}

Ionflux::GeoUtils::Vector3 Line3::getP() const
{
	return p;
}

void Line3::setU(const Ionflux::GeoUtils::Vector3& newU)
{
	u = newU;
}

Ionflux::GeoUtils::Vector3 Line3::getU() const
{
	return u;
}

Ionflux::GeoUtils::Line3& Line3::operator=(const Ionflux::GeoUtils::Line3& 
other)
{
setP(other.getP());
setU(other.getU());
	return *this;
}

Ionflux::GeoUtils::Line3* Line3::copy() const
{
    Line3* newLine3 = create();
    *newLine3 = *this;
    return newLine3;
}

Ionflux::GeoUtils::Line3* Line3::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Line3*>(other);
}

Ionflux::GeoUtils::Line3* Line3::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Line3* newObject = new Line3();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file Line3.cpp
 * \brief Line (3D) implementation.
 */
