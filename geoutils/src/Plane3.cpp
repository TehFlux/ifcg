/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Plane3.cpp                      Plane (3D) (implementation).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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

#include "geoutils/Plane3.hpp"
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

Plane3ClassInfo::Plane3ClassInfo()
{
	name = "Plane3";
	desc = "Plane (3D)";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

Plane3ClassInfo::~Plane3ClassInfo()
{
}

// run-time type information instance constants
const Plane3ClassInfo Plane3::plane3ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Plane3::CLASS_INFO = &Plane3::plane3ClassInfo;

Plane3::Plane3()
: p(0., 0., 0.), u(1., 0., 0.), v(0., 1., 0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Plane3::Plane3(const Ionflux::GeoUtils::Plane3& other)
: p(0., 0., 0.), u(1., 0., 0.), v(0., 1., 0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Plane3::Plane3(const Ionflux::GeoUtils::Vector3& initP, const 
Ionflux::GeoUtils::Vector3& initU, const Ionflux::GeoUtils::Vector3& initV)
: p(initP), u(initU), v(initV)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Plane3::~Plane3()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::GeoUtils::Vector3 Plane3::getTangent() const
{
	// TODO: Implementation.
	return u.normalize();
}

Ionflux::GeoUtils::Vector3 Plane3::getBinormal() const
{
	// TODO: Implementation.
	return v.normalize();
}

Ionflux::GeoUtils::Vector3 Plane3::getNormal() const
{
	// TODO: Implementation.
	return u.cross(v).normalize();
}

Ionflux::GeoUtils::Matrix3 Plane3::getTangentBase() const
{
	Matrix3 result;
	Vector3 u0 = getTangent();
	Vector3 v0 = u0.ortho(getBinormal());
	result.setC0(u0);
	result.setC1(v0);
	result.setC2(getNormal());
	return result;
}

bool Plane3::operator==(const Ionflux::GeoUtils::Plane3& other) const
{
	if (!((p == other.p) && (u == other.u) && (v == other.v)))
	        return false;
	return true;
}

bool Plane3::operator!=(const Ionflux::GeoUtils::Plane3& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

std::string Plane3::getValueString() const
{
	std::ostringstream status;
	status << "p = (" << p.getValueString() 
	    << "), u = (" << u.getValueString() << ", v = (" 
	    << v.getValueString() << ")";
	return status.str();
}

const Ionflux::GeoUtils::Plane3& Plane3::planeXY()
{
	static const Plane3 p0(Vector3::ZERO, Vector3::E_X, Vector3::E_Y);
	return p0;
}

const Ionflux::GeoUtils::Plane3& Plane3::planeYZ()
{
	static const Plane3 p0(Vector3::ZERO, Vector3::E_Y, Vector3::E_Z);
	return p0;
}

const Ionflux::GeoUtils::Plane3& Plane3::planeZX()
{
	static const Plane3 p0(Vector3::ZERO, Vector3::E_Z, Vector3::E_X);
	return p0;
}

Ionflux::GeoUtils::Plane3 Plane3::createFromNormal(const 
Ionflux::GeoUtils::Vector3& n, const Ionflux::GeoUtils::Vector3& t, const 
Ionflux::GeoUtils::Vector3& p)
{
	Vector3 u(t);
	// If n and t are not linearly independent, modify t.
	int i = 0;
	while (eq(n.cross(u).norm(), 0.) 
	    && (i < 2))
	{
	    if (i == 0)
	        u = Vector3::E_Y;
	    else
	    if (i == 1)
	        u = Vector3::E_Z;
	    i++;
	}
	u = n.ortho(u).normalize();
	Vector3 v = n.cross(u).normalize();
	return Plane3(p, u, v);;
}

void Plane3::setP(const Ionflux::GeoUtils::Vector3& newP)
{
	p = newP;
}

Ionflux::GeoUtils::Vector3 Plane3::getP() const
{
    return p;
}

void Plane3::setU(const Ionflux::GeoUtils::Vector3& newU)
{
	u = newU;
}

Ionflux::GeoUtils::Vector3 Plane3::getU() const
{
    return u;
}

void Plane3::setV(const Ionflux::GeoUtils::Vector3& newV)
{
	v = newV;
}

Ionflux::GeoUtils::Vector3 Plane3::getV() const
{
    return v;
}

Ionflux::GeoUtils::Plane3& Plane3::operator=(const 
Ionflux::GeoUtils::Plane3& other)
{
if (this == &other)
    return *this;
setP(other.getP());
setU(other.getU());
setV(other.getV());
	return *this;
}

Ionflux::GeoUtils::Plane3* Plane3::copy() const
{
    Plane3* newPlane3 = create();
    *newPlane3 = *this;
    return newPlane3;
}

Ionflux::GeoUtils::Plane3* Plane3::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Plane3*>(other);
}

Ionflux::GeoUtils::Plane3* Plane3::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Plane3* newObject = new Plane3();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Plane3::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Plane3.cpp
 * \brief Plane (3D) implementation.
 */
