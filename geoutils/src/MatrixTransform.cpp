/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * MatrixTransform.cpp             Transform node: Matrix transform 
 * (implementation).
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

#include "geoutils/MatrixTransform.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "geoutils/GeoUtilsError.hpp"
#include "ifmapping/utils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;
using Ionflux::Mapping::defaultStr;

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

MatrixTransformClassInfo::MatrixTransformClassInfo()
{
	name = "MatrixTransform";
	desc = "Transform node: Matrix transform";
}

MatrixTransformClassInfo::~MatrixTransformClassInfo()
{
}

// public member constants
const unsigned int MatrixTransform::INPUT_SOURCE = 0;
const unsigned int MatrixTransform::OUTPUT_TARGET = 0;

// run-time type information instance constants
const MatrixTransformClassInfo MatrixTransform::matrixTransformClassInfo;
const Ionflux::ObjectBase::IFClassInfo* MatrixTransform::CLASS_INFO = &MatrixTransform::matrixTransformClassInfo;

MatrixTransform::MatrixTransform()
: matrix(Ionflux::GeoUtils::Matrix4::UNIT)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

MatrixTransform::MatrixTransform(const Ionflux::GeoUtils::TransformNodes::MatrixTransform& other)
: matrix(Ionflux::GeoUtils::Matrix4::UNIT)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

MatrixTransform::MatrixTransform(const Ionflux::GeoUtils::Matrix4& 
initMatrix, const Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID), matrix(initMatrix)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

MatrixTransform::~MatrixTransform()
{
	// TODO: Nothing ATM. ;-)
}

void MatrixTransform::process()
{
	if (inputCache.size() < 1)
	    throw GeoUtilsError("Input cache is empty.");
	clearInputGroups();
	TransformableGroup* g0 = inputCache[0];
	g0->transform(matrix);
	addOutput(g0);
}

std::string MatrixTransform::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") << "; " 
	    << matrix.getString() << "]";
	return status.str();
}

void MatrixTransform::setMatrix(const Ionflux::GeoUtils::Matrix4& 
newMatrix)
{
	matrix = newMatrix;
}

Ionflux::GeoUtils::Matrix4 MatrixTransform::getMatrix() const
{
    return matrix;
}

Ionflux::GeoUtils::TransformNodes::MatrixTransform& 
MatrixTransform::operator=(const 
Ionflux::GeoUtils::TransformNodes::MatrixTransform& other)
{
    TransformNode::operator=(other);
    matrix = other.matrix;
	return *this;
}

Ionflux::GeoUtils::TransformNodes::MatrixTransform* MatrixTransform::copy()
const
{
    MatrixTransform* newMatrixTransform = create();
    *newMatrixTransform = *this;
    return newMatrixTransform;
}

Ionflux::GeoUtils::TransformNodes::MatrixTransform* 
MatrixTransform::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<MatrixTransform*>(other);
}

Ionflux::GeoUtils::TransformNodes::MatrixTransform* 
MatrixTransform::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    MatrixTransform* newObject = new MatrixTransform();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int MatrixTransform::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file MatrixTransform.cpp
 * \brief Transform node: Matrix transform implementation.
 */
