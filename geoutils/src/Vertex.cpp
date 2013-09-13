/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vertex.cpp                      Mesh vertex (implementation).
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

#include "geoutils/Vertex.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/LinearInterpolator.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

VertexClassInfo::VertexClassInfo()
{
	name = "Vertex";
	desc = "Mesh vertex";
}

VertexClassInfo::~VertexClassInfo()
{
}

// run-time type information instance constants
const VertexClassInfo Vertex::vertexClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Vertex::CLASS_INFO = &Vertex::vertexClassInfo;

Vertex::Vertex()
: Vertex3(0., 0., 0.), normal(Ionflux::GeoUtils::Vector3::E_X)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Vertex::Vertex(const Ionflux::GeoUtils::Vertex& other)
: Vertex3(0., 0., 0.), normal(Ionflux::GeoUtils::Vector3::E_X)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Vertex::Vertex(double initX, double initY, double initZ, const 
Ionflux::GeoUtils::Vector3& initNormal)
: Vertex3(initX, initY, initZ), normal(initNormal)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Vertex::Vertex(const Ionflux::ObjectBase::DoubleVector& initCoords, const 
Ionflux::GeoUtils::Vector3& initNormal)
: Vertex3(0., 0., 0.), normal(initNormal)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setCoords(initCoords);
}

Vertex::Vertex(const Ionflux::GeoUtils::Vector3& initCoords, const 
Ionflux::GeoUtils::Vector3& initNormal)
: Vertex3(0., 0., 0.), normal(initNormal)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setCoords(initCoords);
}

Vertex::~Vertex()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::GeoUtils::Vertex Vertex::interpolate(const 
Ionflux::GeoUtils::Vertex& other, double t, 
Ionflux::GeoUtils::Interpolator* interpolator) const
{
	Vertex result;
	Interpolator* i0 = 0;
	if (interpolator == 0)
	{
	    i0 = new LinearInterpolator();
	    if (i0 == 0)
	        throw GeoUtilsError("Could not allocate object.");
	    interpolator = i0;
	}
	interpolator->setValues(x, other.x);
	result.setX((*interpolator)(t));
	interpolator->setValues(y, other.y);
	result.setY((*interpolator)(t));
	interpolator->setValues(z, other.z);
	result.setZ((*interpolator)(t));
	Vector3 n0 = other.getNormal();
	Vector3 n1;
	interpolator->setValues(normal.getX0(), n0.getX0());
	n1.setX0((*interpolator)(t));
	interpolator->setValues(normal.getX1(), n0.getX1());
	n1.setX1((*interpolator)(t));
	interpolator->setValues(normal.getX2(), n0.getX2());
	n1.setX2((*interpolator)(t));
	result.setNormal(n1);
	if (i0 != 0)
	    delete i0;
	return result;
}

Ionflux::GeoUtils::Vertex& Vertex::scale(const Ionflux::GeoUtils::Vector3& 
s)
{
	Vertex3::scale(s);
	return *this;
}

Ionflux::GeoUtils::Vertex& Vertex::translate(const 
Ionflux::GeoUtils::Vector3& t)
{
	Vertex3::translate(t);
	return *this;
}

Ionflux::GeoUtils::Vertex& Vertex::rotate(double phi, 
Ionflux::GeoUtils::AxisID axis)
{
	Vertex3::rotate(phi, axis);
	return *this;
}

Ionflux::GeoUtils::Vertex& Vertex::normalize()
{
	Vertex3::normalize();
	return *this;
}

Ionflux::GeoUtils::Vertex& 
Vertex::center(Ionflux::GeoUtils::CenteringMethod method, 
Ionflux::GeoUtils::Vector3* origin)
{
	Vertex3::center(method, origin);
	return *this;
}

Ionflux::GeoUtils::Vertex& Vertex::transform(const 
Ionflux::GeoUtils::Matrix4& matrix)
{
	Vertex3::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Vertex& Vertex::transform(const 
Ionflux::GeoUtils::Matrix3& matrix)
{
	Vertex3::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Vertex& Vertex::duplicate()
{
	Vertex* result = new Vertex(*this);
	if (result == 0)
	    throw GeoUtilsError("Could not allocate object.");
	return *result;
}

std::string Vertex::getString() const
{
	ostringstream state;
	state << getClassName() << "[" << x << ", " << y << ", " << z << ", " 
	    << normal.getString() << "]";
	return state.str();
}

Ionflux::GeoUtils::Vertex* Vertex::create(double newX, double newY, double 
newZ)
{
	Vertex* v0 = create();
	v0->setCoords(newX, newY, newZ);
	return v0;
}

void Vertex::setNormal(const Ionflux::GeoUtils::Vector3& newNormal)
{
	normal = newNormal;
}

Ionflux::GeoUtils::Vector3 Vertex::getNormal() const
{
    return normal;
}

Ionflux::GeoUtils::Vertex& Vertex::operator=(const 
Ionflux::GeoUtils::Vertex& other)
{
    Vertex3::operator=(other);
    normal = other.normal;
	return *this;
}

Ionflux::GeoUtils::Vertex* Vertex::copy() const
{
    Vertex* newVertex = create();
    *newVertex = *this;
    return newVertex;
}

Ionflux::GeoUtils::Vertex* Vertex::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Vertex*>(other);
}

Ionflux::GeoUtils::Vertex* Vertex::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Vertex* newObject = new Vertex();
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

/** \file Vertex.cpp
 * \brief Mesh vertex implementation.
 */
