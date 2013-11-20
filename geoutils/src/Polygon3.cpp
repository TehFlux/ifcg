/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
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
#include "ifobject/objectutils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Line3.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "geoutils/xmlutils.hpp"

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

// public member constants
const Ionflux::GeoUtils::Range Polygon3::UV_RANGE = Ionflux::GeoUtils::Range(0., 1.);

// run-time type information instance constants
const Polygon3ClassInfo Polygon3::polygon3ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Polygon3::CLASS_INFO = &Polygon3::polygon3ClassInfo;

const std::string Polygon3::XML_ELEMENT_NAME = "polygon3";

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
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "recalculateBounds", "Vertex source");
	TransformableObject::recalculateBounds();
	if (!useTransform() && !useVI())
	{
	    *boundsCache = vertexSource->getBounds();
	    return;
	}
	// Adjust for transformation.
	Polygon3* p0 = copy();
	addLocalRef(p0);
	p0->applyTransform();
	if (p0->useTransform())
	    throw GeoUtilsError(getErrorString(
	        "Transform matrix still in use after "
	        "applying transformations.", "recalculateBounds"));
	*boundsCache = p0->getBounds();
	removeLocalRef(p0);
}

void Polygon3::clearData()
{
	if (vertexSource != 0)
	    vertexSource->clearVertices();
	clearEdges();
	TransformableObject::clear();
}

void Polygon3::copyVertices()
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "copyVertices", "Vertex source");
	setVertexSource(vertexSource->copy());
}

int Polygon3::createEdges()
{
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "createEdges", "Vertex source");
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
	    status << "Vertex index v0 out of range (numVerts = " 
	        << numVerts << ", v0 = " << v0 << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "getPlane"));
	}
	if ((v1 < 0) || (static_cast<unsigned int>(v1) >= numVerts))
	{
	    std::ostringstream status;
	    status << "Vertex index v1 out of range (numVerts = " 
	        << numVerts << ", v1 = " << v1 << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "getPlane"));
	}
	if ((v2 < 0) || (static_cast<unsigned int>(v2) >= numVerts))
	{
	    std::ostringstream status;
	    status << "Vertex index v2 out of range (numVerts = " 
	        << numVerts << ", v2 = " << v2 << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "getPlane"));
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
	// transformable object data
	std::string ts0(TransformableObject::getValueString());
	if (ts0.size() > 0)
	    status << "; " << ts0;
	return status.str();
}

std::string Polygon3::getSVG(const std::string& attrs, const std::string& 
elementID, Ionflux::GeoUtils::AxisID axis, Ionflux::GeoUtils::SVGShapeType 
shapeType, bool closePath)
{
	std::ostringstream svg;
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
	Ionflux::ObjectBase::nullPointerCheck(vertexSource, this, 
	    "getBarycenter", "Vertex source");
	if (!useTransform() && !useVI())
	    return vertexSource->getBarycenter();
	// Adjust for transformation.
	Vertex3 v0(vertexSource->getBarycenter());
	if (useTransform())
	    v0.transform(*getTransformMatrix());
	if (useVI())
	    v0.transformVI(*getViewMatrix(), getImageMatrix());
	return v0.getVector();
}

void Polygon3::applyTransform(bool recursive)
{
	if (vertexSource == 0)
	{
	    clearTransformations();
	    return;
	}
	if (!useTransform() && !useVI())
	{
	    if (recursive)
	        vertexSource->applyTransform(recursive);
	    clearTransformations();
	    return;
	}
	copyVertices();
	if (useTransform())
	    vertexSource->transform(*getTransformMatrix());
	if (useVI())
	    vertexSource->transformVI(*getViewMatrix(), getImageMatrix());
	if (useTransform() || useVI())
	    vertexSource->applyTransform(recursive);
	clearTransformations();
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
	    Vertex3* vt0 = Ionflux::ObjectBase::nullPointerCheck(
	        getVertex(i), this, "getPolygon2", "Vertex");
	    target.addVertex(Vertex2::create(vt0->getX(), vt0->getY()));
	}
	for (unsigned int i = 0; i < getNumEdges(); i++)
	{
	    Edge* et0 = Ionflux::ObjectBase::nullPointerCheck(
	        getEdge(i), this, "getPolygon2", "Edge");
	    target.addEdge(et0->copy());
	}
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

bool Polygon3::isTri()
{
	// TODO: Implementation.
	return (getNumVertices() == 3);
}

bool Polygon3::isQuad()
{
	// TODO: Implementation.
	return (getNumVertices() == 4);
}

void Polygon3::calculateUVCoefficients(const Ionflux::GeoUtils::Vertex3& p,
Ionflux::GeoUtils::Matrix4& target, Ionflux::ObjectBase::IntVector* 
indices, double s)
{
	if (!isQuad())
	    throw GeoUtilsError(getErrorString(
	        "Polygon is not a quadrilateral", "calculateUVCoefficients"));
	Vertex3Vector vs;
	if (indices != 0)
	{
	    if (indices->size() < 4)
	        throw GeoUtilsError(getErrorString(
	            "Not enough elements in index vector.", 
	                "calculateUVCoefficients"));
	    for (unsigned int i = 0; i < 4; i++)
	    {
	        Vertex3* v0 = Ionflux::ObjectBase::nullPointerCheck(
	            getVertex((*indices)[i]), this, "calculateUVCoefficients", 
	                "Vertex");
	        vs.push_back(v0);
	    }
	} else 
	{
	    for (unsigned int i = 0; i < 4; i++)
	    {
	        Vertex3* v0 = Ionflux::ObjectBase::nullPointerCheck(
	            getVertex(i), this, "calculateUVCoefficients", 
	                "Vertex");
	        vs.push_back(v0);
	    }
	}
	Vector3 v1(vs[0]->getVector());
	Vector3 v2(vs[3]->getVector());
	Vector3 v3(vs[2]->getVector());
	Vector3 v4(vs[1]->getVector());
	/* Here the magic happens.
	   (These equations come from parameterizing the lines through the 
	   points on two opposite sides of the quadrilateral with u (or v, 
	   respectively) and solving for the distance vector of p to that 
	   line.)
	 */
	Vector3 a(v2 - v1);
	Vector3 b(v3 - v2 - v4 + v1);
	Vector3 d(v1 - v4);
	Vector3 e(p.getVector() - v1);
	Vector4 eta1((b * b) * d - (b * d) * b, 0.);
	Vector4 eta2(2. * (a * b) * d + (b * b) * e - (b * d) * a 
	    - (a * d) * b - (b * e) * b, 0.);
	Vector4 eta3(2. * (a * b) * e + (a * a) * d - (a * d) * a 
	    - (b * e) * a - (a * e) * b, 0.);
	Vector4 eta4((a * a) * e - (a * e) * a, 0.);
	target.setC0(eta1 * s);
	target.setC1(eta2 * s);
	target.setC2(eta3 * s);
	target.setC3(eta4 * s);
}

Ionflux::GeoUtils::Vector2 Polygon3::getUV(const 
Ionflux::GeoUtils::Vertex3& p, Ionflux::ObjectBase::IntVector* indices, 
Ionflux::GeoUtils::QuadInterpolationTypeID interpolationType, double s, 
double t)
{
	if (!isQuad())
	    throw GeoUtilsError(getErrorString(
	        "Polygon is not a quadrilateral", "getUV"));
	Ionflux::ObjectBase::IntVector i0;
	if (indices == 0)
	{
	    for (unsigned int i = 0; i < 4; i++)
	        i0.push_back(i);
	} else
	    i0 = *indices;
	if (i0.size() < 4)
	    throw GeoUtilsError(getErrorString(
	        "Not enough elements in index vector.", "getUV"));
	// Calculate UV coefficients.
	Matrix4 m0;
	calculateUVCoefficients(p, m0, &i0, s);
	// Solve equation systems.
	double u = 0.;
	double v = 0.;
	Vector3 s11;
	solveCubicEquation(m0.getElement(0, 0), m0.getElement(0, 1), 
	    m0.getElement(0, 2), m0.getElement(0, 3), s11);
	Vector3 s12;
	solveCubicEquation(m0.getElement(1, 0), m0.getElement(1, 1), 
	    m0.getElement(1, 2), m0.getElement(1, 3), s12);
	Ionflux::ObjectBase::DoubleVector r0;
	s11.findMatchingElements(s12, r0, &UV_RANGE, t);
	if (r0.size() == 0)
	{
	    std::ostringstream status;
	    status << "No solution found for U coordinates (p = (" 
	        << p.getValueString() << "), quad = " << getValueString() 
	        << ", s11 = (" << s11.getValueString() 
	        << "), s12 = (" << s12.getValueString()
	        << ")).";
	    throw GeoUtilsError(getErrorString(status.str(), "getUV"));
	}
	u = r0[0];
	if (interpolationType == QUAD_INTERPOLATION_SYMMETRIC)
	{
	    shift(i0, -1);
	    Matrix4 m1;
	    calculateUVCoefficients(p, m1, &i0, s);
	    Vector3 s21;
	    solveCubicEquation(m1.getElement(0, 0), m1.getElement(0, 1), 
	        m1.getElement(0, 2), m1.getElement(0, 3), s21);
	    Vector3 s22;
	    solveCubicEquation(m1.getElement(1, 0), m1.getElement(1, 1), 
	        m1.getElement(1, 2), m1.getElement(1, 3), s22);
	    Ionflux::ObjectBase::DoubleVector r1;
	    s21.findMatchingElements(s22, r1, &UV_RANGE, t);
	    if (r0.size() == 0)
	    {
	        std::ostringstream status;
	        status << "No solution found for V coordinates (p = (" 
	            << p.getValueString() << "), quad = " << getValueString() 
	            << "), s21 = (" << s21.getValueString() 
	            << "), s22 = (" << s22.getValueString()
	            << ")).";
	        throw GeoUtilsError(getErrorString(status.str(), "getUV"));
	    }
	    v = r1[0];
	} else
	if (interpolationType == QUAD_INTERPOLATION_BILINEAR)
	{
	    Vertex3Vector vs;
	    for (unsigned int i = 0; i < 4; i++)
	    {
	        Vertex3* v0 = Ionflux::ObjectBase::nullPointerCheck(
	            getVertex(i0[i]), this, "getUV", "Vertex");
	        vs.push_back(v0);
	    }
	    Vector3 v1(vs[0]->getVector());
	    Vector3 v2(vs[1]->getVector());
	    Vector3 v3(vs[2]->getVector());
	    Vector3 v4(vs[3]->getVector());
	    Vector3 w1(v1 + u * (v2 - v1));
	    Vector3 w2(v4 + u * (v3 - v4));
	    /* <---- DEBUG ----- //
	    std::cerr << "[Polygon3::getUV] DEBUG: "
	        "w1 = (" << w1.getValueString() << "), w2 = (" 
	        << w2.getValueString() << ")" << std::endl;
	    // ----- DEBUG ----> */
	    Vector3 vp(p.getVector());
	    v = (vp - w1).norm() / (w2 - w1).norm();
	} else
	{
	    std::ostringstream status;
	    status << "Unknown interpolation type: " << interpolationType;
	    throw GeoUtilsError(getErrorString(status.str(), "getUV"));
	}
	return Vector2(u, v);
}

Ionflux::GeoUtils::Vertex3 Polygon3::getUVVertex(const 
Ionflux::GeoUtils::Vector2& uv, Ionflux::ObjectBase::IntVector* indices, 
Ionflux::GeoUtils::QuadInterpolationTypeID interpolationType)
{
	if (!isQuad())
	    throw GeoUtilsError(getErrorString(
	        "Polygon is not a quadrilateral", "getUVVertex"));
	Ionflux::ObjectBase::IntVector i0;
	if (indices == 0)
	{
	    for (unsigned int i = 0; i < 4; i++)
	        i0.push_back(i);
	} else
	    i0 = *indices;
	if (i0.size() < 4)
	    throw GeoUtilsError(getErrorString(
	        "Not enough elements in index vector.", "getUVVertex"));
	Vertex3Vector vs;
	for (unsigned int i = 0; i < 4; i++)
	{
	    Vertex3* v0 = Ionflux::ObjectBase::nullPointerCheck(
	        getVertex(i0[i]), this, "getUVVertex", "Vertex");
	    vs.push_back(v0);
	}
	double u = uv[0];
	double v = uv[1];
	Vector3 p;
	Vector3 v1(vs[0]->getVector());
	Vector3 v2(vs[1]->getVector());
	Vector3 v3(vs[2]->getVector());
	Vector3 v4(vs[3]->getVector());
	Vector3 w1(v1 + u * (v2 - v1));
	Vector3 w2(v4 + u * (v3 - v4));
	if (interpolationType == QUAD_INTERPOLATION_BILINEAR)
	{
	    p = w1 + v * (w2 - w1);
	} else
	if (interpolationType == QUAD_INTERPOLATION_SYMMETRIC)
	{
	    Vector3 w3(v1 + v * (v4 - v1));
	    Vector3 w4(v2 + v * (v3 - v2));
	    Line3 l0(w1, (w2 - w1).normalize());
	    Line3 l1(w3, (w4 - w3).normalize());
	    if (!l0.intersect(l1, p))
	    {
	        std::ostringstream status;
	        status << "Interpolation lines do not intersect (uv = (" 
	            << uv.getValueString() << "), quad = " << getValueString() 
	            << ").";
	        throw GeoUtilsError(getErrorString(status.str(), "getUVVertex"));
	    }
	} else
	{
	    std::ostringstream status;
	    status << "Unknown interpolation type: " << interpolationType;
	    throw GeoUtilsError(getErrorString(status.str(), "getUVVertex"));
	}
	return Vertex3(p);
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

Ionflux::GeoUtils::Vertex3* Polygon3::addVertex()
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->addVertex();
}

void Polygon3::addVertices(const std::vector<Ionflux::GeoUtils::Vertex3*>& 
newVertices)
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->addVertices(newVertices);
}

void Polygon3::addVertices(Ionflux::GeoUtils::Polygon3* newVertices)
{
    if (vertexSource == 0)
        throw GeoUtilsError("Vertex source not set.");
    return vertexSource->addVertices(newVertices->vertexSource);
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

Ionflux::GeoUtils::Edge* Polygon3::addEdge()
{
	Ionflux::GeoUtils::Edge* o0 = Edge::create();
	addEdge(o0);
	return o0;
}

void Polygon3::addEdges(const std::vector<Ionflux::GeoUtils::Edge*>& 
newEdges)
{
	for (std::vector<Ionflux::GeoUtils::Edge*>::const_iterator i = newEdges.begin(); 
	    i != newEdges.end(); i++)
	    addEdge(*i);
}

void Polygon3::addEdges(Ionflux::GeoUtils::Polygon3* newEdges)
{
	for (unsigned int i = 0; 
	    i < newEdges->getNumEdges(); i++)
	    addEdge(newEdges->getEdge(i));
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
    if (this == &other)
        return *this;
    TransformableObject::operator=(other);
    setVertexSource(other.vertexSource);
    EdgeVector e0;
    for (EdgeVector::const_iterator i = other.edges.begin(); 
        i != other.edges.end(); i++)
    {
        Edge* et0 = Ionflux::ObjectBase::nullPointerCheck(*i, this, 
            "operator=", "Edge");
        e0.push_back(et0->copy());
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

Ionflux::GeoUtils::Polygon3* 
Polygon3::create(Ionflux::GeoUtils::Vertex3Vector* initVertices, 
Ionflux::GeoUtils::EdgeVector* initEdges, Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Polygon3* newObject = new Polygon3(initVertices, initEdges);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Polygon3* 
Polygon3::create(Ionflux::GeoUtils::Vertex3Set* initVertexSource, 
Ionflux::GeoUtils::EdgeVector* initEdges, Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Polygon3* newObject = new Polygon3(initVertexSource, initEdges);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Polygon3* Polygon3::create(const 
Ionflux::GeoUtils::Vertex3* v0, const Ionflux::GeoUtils::Vertex3* v1, const
Ionflux::GeoUtils::Vertex3* v2, const Ionflux::GeoUtils::Vertex3* v3, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Polygon3* newObject = new Polygon3(v0, v1, v2, v3);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

std::string Polygon3::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Polygon3::getXMLAttributeData() const
{
	std::ostringstream d0;
	return d0.str();
}

void Polygon3::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string iws0 = Ionflux::ObjectBase::getIndent(indentLevel);
	bool haveBCData = false;
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
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0(edges, "vec", "", 
        indentLevel, "pname=\"edges\"");
    xcFirst = false;
	target = d0.str();
}

void Polygon3::loadFromXMLFile(const std::string& fileName)
{
	std::string data;
	Ionflux::ObjectBase::readFile(fileName, data);
	/* <---- DEBUG ----- //
	std::cerr << "[Polygon3::loadFromXMLFile] data = " << data 
	    << std::endl;
	// <---- DEBUG ----- */
	Ionflux::GeoUtils::XMLUtils::getPolygon3(data, *this);
}

}

}

/** \file Polygon3.cpp
 * \brief Polygon (3D) implementation.
 */
