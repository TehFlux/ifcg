/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Piece.cpp                       Piece (implementation).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFMapping - Ionflux Mapping Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFMapping - Ionflux Mapping Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "ifmapping/Piece.hpp"
#include <cmath>
#include <sstream>
#include "ifmapping/utils.hpp"
#include "ifmapping/MappingError.hpp"
#include "ifmapping/Mapping.hpp"
#include "ifmapping/Linear.hpp"
#include "ifmapping/Constant.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

PieceClassInfo::PieceClassInfo()
{
	name = "Piece";
	desc = "Piece";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

PieceClassInfo::~PieceClassInfo()
{
}

// run-time type information instance constants
const PieceClassInfo Piece::pieceClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Piece::CLASS_INFO = &Piece::pieceClassInfo;

Piece::Piece()
: mapping(0), param(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Piece::Piece(const Ionflux::Mapping::Piece& other)
: mapping(0), param(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Piece::Piece(Ionflux::Mapping::Mapping* initMapping, 
Ionflux::Mapping::MappingValue initParam)
: mapping(0), param(initParam)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setMapping(initMapping);
}

Piece::~Piece()
{
	// TODO: Nothing ATM. ;-)
}

std::string Piece::getString() const
{
	ostringstream status;
	status << getClassName() << "[";
	if (mapping != 0)
	    status << (*mapping);
	else
	    status << "<none>";
	status << ", " << param << "]";
	return status.str();
}

Ionflux::Mapping::Piece* Piece::create(Ionflux::Mapping::Mapping* 
initMapping, Ionflux::Mapping::MappingValue initParam)
{
	Piece* p0 = create();
	p0->setMapping(initMapping);
	p0->setParam(initParam);
	return p0;
}

void Piece::createPieces(const Ionflux::Mapping::PointSet& points, 
Ionflux::Mapping::PieceVector& target, const Ionflux::Mapping::Point& 
offset, const Ionflux::Mapping::Point& scale, bool addConstant)
{
	unsigned int numPoints = points.getNumPoints();
	if (numPoints < 2)
	    throw MappingError("Not enough points to create pieces " 
	        "(needs at least 2 points).");
	double tx = offset.getX();
	double ty = offset.getY();
	double sx = scale.getX();
	double sy = scale.getY();
	for (unsigned int i = 1; i < numPoints; i++)
	{
	    Point* p0 = points.getPoint(i - 1);
	    Point* p1 = points.getPoint(i);
	    Linear* m0 = Linear::create(p0->getY() * sy + ty, p1->getY() * sy + 
	ty);
	    Piece* p = Piece::create(m0, p0->getX() * sx + tx);
	    target.push_back(p);
	    if (addConstant 
	        && (i == (numPoints - 1)))
	    {
	        Constant* m1 = Constant::create(p1->getY() * sy + ty);
	        p = Piece::create(m1, p1->getX() * sx + tx);
	        target.push_back(p);
	    }
	}
}

void Piece::setMapping(Ionflux::Mapping::Mapping* newMapping)
{
	if (mapping == newMapping)
		return;
    if (newMapping != 0)
        addLocalRef(newMapping);
	if (mapping != 0)
		removeLocalRef(mapping);
	mapping = newMapping;
}

Ionflux::Mapping::Mapping* Piece::getMapping() const
{
    return mapping;
}

void Piece::setParam(Ionflux::Mapping::MappingValue newParam)
{
	param = newParam;
}

Ionflux::Mapping::MappingValue Piece::getParam() const
{
    return param;
}

Ionflux::Mapping::Piece& Piece::operator=(const Ionflux::Mapping::Piece& 
other)
{
    setMapping(other.mapping);
    param = other.param;
	return *this;
}

Ionflux::Mapping::Piece* Piece::copy() const
{
    Piece* newPiece = create();
    *newPiece = *this;
    return newPiece;
}

Ionflux::Mapping::Piece* Piece::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Piece*>(other);
}

Ionflux::Mapping::Piece* Piece::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Piece* newObject = new Piece();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Piece::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Piece.cpp
 * \brief Piece implementation.
 */
