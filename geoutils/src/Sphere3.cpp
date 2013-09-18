/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Sphere3.cpp                     Sphere (3D) (implementation).
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

#include "geoutils/Sphere3.hpp"
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

Sphere3ClassInfo::Sphere3ClassInfo()
{
	name = "Sphere3";
	desc = "Sphere (3D)";
}

Sphere3ClassInfo::~Sphere3ClassInfo()
{
}

// run-time type information instance constants
const Sphere3ClassInfo Sphere3::sphere3ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Sphere3::CLASS_INFO = &Sphere3::sphere3ClassInfo;

Sphere3::Sphere3()
: p(Ionflux::GeoUtils::Vector3::ZERO), r(1.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Sphere3::Sphere3(const Ionflux::GeoUtils::Sphere3& other)
: p(Ionflux::GeoUtils::Vector3::ZERO), r(1.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Sphere3::Sphere3(const Ionflux::GeoUtils::Vector3& initP, double initR)
: p(initP), r(initR)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Sphere3::~Sphere3()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::GeoUtils::Vector3 Sphere3::getBarycenter() const
{
	// TODO: Implementation.
	return p;
}

Ionflux::GeoUtils::Range3 Sphere3::getBounds() const
{
	Vector3 r0(r, r, r);
	Range3 result(p, &r0);
	return result;
}

bool Sphere3::checkVertex(const Ionflux::GeoUtils::Vertex3& v, double t) 
const
{
	double d0 = 0.;
	if (!useTransform())
	{
	    Vector3 v0(v.getVector());
	    d0 = (v0 - p).norm();
	} else
	{
	    /* Transform the vertex into the transformed sphere coordinate 
	       system. */
	    Vertex3 v1(v);
	    v1.transform(getTransformMatrix()->invert());
	    d0 = (v1.getVector() - p).norm();
	}
	return ltOrEq(d0, r, t);
}

bool Sphere3::operator==(const Ionflux::GeoUtils::Sphere3& other) const
{
	if (!((p == other.p) && (r == other.r)))
	        return false;
	return true;
}

bool Sphere3::operator!=(const Ionflux::GeoUtils::Sphere3& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

Ionflux::GeoUtils::Sphere3& Sphere3::scale(const 
Ionflux::GeoUtils::Vector3& s)
{
	Shape3::scale(s);
	return *this;
}

Ionflux::GeoUtils::Sphere3& Sphere3::translate(const 
Ionflux::GeoUtils::Vector3& t)
{
	Shape3::translate(t);
	return *this;
}

Ionflux::GeoUtils::Sphere3& Sphere3::rotate(double phi, 
Ionflux::GeoUtils::AxisID axis)
{
	Shape3::rotate(phi, axis);
	return *this;
}

Ionflux::GeoUtils::Sphere3& Sphere3::normalize()
{
	Shape3::normalize();
	return *this;
}

Ionflux::GeoUtils::Sphere3& 
Sphere3::center(Ionflux::GeoUtils::CenteringMethod method, 
Ionflux::GeoUtils::Vector3* origin)
{
	Shape3::center(method, origin);
	return *this;
}

Ionflux::GeoUtils::Sphere3& Sphere3::transform(const 
Ionflux::GeoUtils::Matrix3& matrix)
{
	Shape3::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Sphere3& Sphere3::transform(const 
Ionflux::GeoUtils::Matrix4& matrix)
{
	Shape3::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Sphere3& Sphere3::transformVI(const 
Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4* image)
{
	Shape3::transformVI(view, image);
	return *this;
}

std::string Sphere3::getValueString() const
{
	ostringstream status;
	status << "p = (" << p.getValueString() << "), " << r;
	// transformable object data
	std::string ts0(TransformableObject::getValueString());
	if (ts0.size() > 0)
	    status << "; " << ts0;
	return status.str();
}

Ionflux::GeoUtils::Sphere3& Sphere3::duplicate()
{
	// TODO: Implementation.
	return *copy();
}

const Ionflux::GeoUtils::Sphere3& Sphere3::unit()
{
	static const Sphere3 s0(Ionflux::GeoUtils::Vector3::ZERO, 1.);
	return s0;
}

void Sphere3::setP(const Ionflux::GeoUtils::Vector3& newP)
{
	p = newP;
}

Ionflux::GeoUtils::Vector3 Sphere3::getP() const
{
    return p;
}

void Sphere3::setR(double newR)
{
	r = newR;
}

double Sphere3::getR() const
{
    return r;
}

Ionflux::GeoUtils::Sphere3& Sphere3::operator=(const 
Ionflux::GeoUtils::Sphere3& other)
{
    Shape3::operator=(other);
    p = other.p;
    r = other.r;
	return *this;
}

Ionflux::GeoUtils::Sphere3* Sphere3::copy() const
{
    Sphere3* newSphere3 = create();
    *newSphere3 = *this;
    return newSphere3;
}

Ionflux::GeoUtils::Sphere3* Sphere3::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Sphere3*>(other);
}

Ionflux::GeoUtils::Sphere3* Sphere3::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Sphere3* newObject = new Sphere3();
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

/** \file Sphere3.cpp
 * \brief Sphere (3D) implementation.
 */
