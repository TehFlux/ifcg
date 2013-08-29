/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Hexagon2.cpp                    Hexagon (2D) (implementation).
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

#include "geoutils/Hexagon2.hpp"
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

Hexagon2ClassInfo::Hexagon2ClassInfo()
{
	name = "Hexagon2";
	desc = "Hexagon (2D)";
}

Hexagon2ClassInfo::~Hexagon2ClassInfo()
{
}

// run-time type information instance constants
const Hexagon2ClassInfo Hexagon2::hexagon2ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Hexagon2::CLASS_INFO = &Hexagon2::hexagon2ClassInfo;

Hexagon2::Hexagon2()
: baseLength(1.0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	createVertices();
	createEdges();
}

Hexagon2::Hexagon2(const Ionflux::GeoUtils::Hexagon2& other)
: baseLength(1.0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Hexagon2::Hexagon2(double initBaseLength)
: baseLength(initBaseLength)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	createVertices();
	createEdges();
}

Hexagon2::~Hexagon2()
{
	// TODO: Nothing ATM. ;-)
}

void Hexagon2::createVertices()
{
	double c = baseLength / 4.;
	double b = c * ::tan(M_PI / 3.);
	addVertex(new Vertex2(-baseLength / 4., -b));
	addVertex(new Vertex2(baseLength / 4., -b));
	addVertex(new Vertex2(baseLength / 2., 0.));
	addVertex(new Vertex2(baseLength / 4., b));
	addVertex(new Vertex2(-baseLength / 4., b));
	addVertex(new Vertex2(-baseLength / 2., 0.));
}

std::string Hexagon2::getString() const
{
	ostringstream state;
	state << getClassName() << "[" << baseLength << "]";
	return state.str();
}

void Hexagon2::setBaseLength(double newBaseLength)
{
	baseLength = newBaseLength;
}

double Hexagon2::getBaseLength() const
{
	return baseLength;
}

Ionflux::GeoUtils::Hexagon2& Hexagon2::operator=(const 
Ionflux::GeoUtils::Hexagon2& other)
{
    clearVertices();
    clearEdges();
    baseLength = other.baseLength;
    createVertices();
    createEdges();
	return *this;
}

Ionflux::GeoUtils::Hexagon2* Hexagon2::copy() const
{
    Hexagon2* newHexagon2 = 
        new Hexagon2();
    *newHexagon2 = *this;
    return newHexagon2;
}

}

}

/** \file Hexagon2.cpp
 * \brief Hexagon (2D) implementation.
 */
