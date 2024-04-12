/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Voxel.cpp                       Voxel (implementation).
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

#include "geoutils/Voxel.hpp"
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

VoxelClassInfo::VoxelClassInfo()
{
	name = "Voxel";
	desc = "Voxel";
}

VoxelClassInfo::~VoxelClassInfo()
{
}

// run-time type information instance constants
const VoxelClassInfo Voxel::voxelClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Voxel::CLASS_INFO = &Voxel::voxelClassInfo;

Voxel::Voxel()
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, Ionflux::GeoUtils::Vector3::ZERO, ""), index(Ionflux::GeoUtils::Vector3::ZERO), edgeLength(1.), offset(Ionflux::GeoUtils::Vector3::ZERO)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initBounds();
}

Voxel::Voxel(const Ionflux::GeoUtils::Voxel& other)
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, Ionflux::GeoUtils::Vector3::ZERO, ""), index(Ionflux::GeoUtils::Vector3::ZERO), edgeLength(1.), offset(Ionflux::GeoUtils::Vector3::ZERO)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Voxel::Voxel(const Ionflux::GeoUtils::Vector3& initIndex, double 
initEdgeLength, const Ionflux::GeoUtils::Vector3& initOffset)
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, 
Ionflux::GeoUtils::Vector3::ZERO, ""), index(initIndex), 
edgeLength(initEdgeLength), offset(initOffset)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initBounds();
}

Voxel::~Voxel()
{
	clear();
}

void Voxel::clear()
{
	BoxBoundsItem::clear();
	index = Ionflux::GeoUtils::Vector3::ZERO;
	edgeLength = 1.;
	offset = Ionflux::GeoUtils::Vector3::ZERO;
	initBounds();
}

void Voxel::initBounds()
{
	Vector3 stepSize(edgeLength, edgeLength, edgeLength);
	center = stepSize.multElements(index) + offset;
	rVec.setElements(0.5 * edgeLength, 0.5 * edgeLength, 0.5 * edgeLength);
	BoxBoundsItem::updateBounds();
}

std::string Voxel::getString() const
{
	ostringstream result;
	result << getClassName() << "[" << index.getString() << ", " 
	    << edgeLength << ", " << offset.getString() << "]";
	return result.str();
}

Ionflux::GeoUtils::Voxel* Voxel::create(const Ionflux::GeoUtils::Vector3& 
initIndex, double initEdgeLength, const Ionflux::GeoUtils::Vector3& 
initOffset)
{
	Voxel* v0 = new Voxel(initIndex, initEdgeLength, initOffset);
	if (v0 == 0)
	    throw GeoUtilsError("Could not allocate voxel.");
	return v0;
}

void Voxel::toVertexSet(Ionflux::GeoUtils::BoxBoundsItemSet& source, 
Ionflux::GeoUtils::Vertex3Set& target)
{
	for (BoxBoundsItemSet::iterator i = source.begin(); 
	    i != source.end(); i++)
	{
	    Voxel* v0 = Voxel::upcast(*i);
	    if (v0 != 0)
	    {
	        Vertex3* v1 = target.addVertex();
	        v1->setCoords(v0->getCenter());
	    }
	}
}

void Voxel::setIndex(const Ionflux::GeoUtils::Vector3& newIndex)
{
	index = newIndex;
}

Ionflux::GeoUtils::Vector3 Voxel::getIndex() const
{
    return index;
}

void Voxel::setEdgeLength(double newEdgeLength)
{
	edgeLength = newEdgeLength;
}

double Voxel::getEdgeLength() const
{
    return edgeLength;
}

void Voxel::setOffset(const Ionflux::GeoUtils::Vector3& newOffset)
{
	offset = newOffset;
}

Ionflux::GeoUtils::Vector3 Voxel::getOffset() const
{
    return offset;
}

Ionflux::GeoUtils::Voxel& Voxel::operator=(const Ionflux::GeoUtils::Voxel& 
other)
{
    clear();
	return *this;
}

Ionflux::GeoUtils::Voxel* Voxel::copy() const
{
    Voxel* newVoxel = create();
    *newVoxel = *this;
    return newVoxel;
}

Ionflux::GeoUtils::Voxel* Voxel::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Voxel*>(other);
}

Ionflux::GeoUtils::Voxel* Voxel::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Voxel* newObject = new Voxel();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Voxel::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Voxel.cpp
 * \brief Voxel implementation.
 */
