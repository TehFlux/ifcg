/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Object3.cpp                     Object (3D) (implementation).
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

#include "geoutils/Object3.hpp"
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

Object3ClassInfo::Object3ClassInfo()
{
	name = "Object3";
	desc = "Object (3D)";
}

Object3ClassInfo::~Object3ClassInfo()
{
}

// run-time type information instance constants
const Object3ClassInfo Object3::object3ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Object3::CLASS_INFO = &Object3::object3ClassInfo;

Object3::Object3()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Object3::Object3(const Ionflux::GeoUtils::Object3& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Object3::~Object3()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::GeoUtils::Object3& Object3::scale(const 
Ionflux::GeoUtils::Vector3& s)
{
	TransformableObject::scale(s);
	return *this;
}

Ionflux::GeoUtils::Object3& Object3::translate(const 
Ionflux::GeoUtils::Vector3& t)
{
	TransformableObject::translate(t);
	return *this;
}

Ionflux::GeoUtils::Object3& Object3::rotate(double phi, 
Ionflux::GeoUtils::AxisID axis)
{
	TransformableObject::rotate(phi, axis);
	return *this;
}

Ionflux::GeoUtils::Object3& Object3::normalize()
{
	TransformableObject::normalize();
	return *this;
}

Ionflux::GeoUtils::Object3& 
Object3::center(Ionflux::GeoUtils::CenteringMethod method, 
Ionflux::GeoUtils::Vector3* origin)
{
	TransformableObject::center(method, origin);
	return *this;
}

Ionflux::GeoUtils::Object3& Object3::transform(const 
Ionflux::GeoUtils::Matrix3& matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Object3& Object3::transform(const 
Ionflux::GeoUtils::Matrix4& matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Object3& Object3::transformVI(const 
Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4* image)
{
	TransformableObject::transformVI(view, image);
	return *this;
}

Ionflux::GeoUtils::Object3& Object3::operator=(const 
Ionflux::GeoUtils::Object3& other)
{
    TransformableObject::operator=(other);
	return *this;
}

Ionflux::GeoUtils::Object3* Object3::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Object3*>(other);
}

}

}

/** \file Object3.cpp
 * \brief Object (3D) implementation.
 */
