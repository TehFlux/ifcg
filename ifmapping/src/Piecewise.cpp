/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Piecewise.cpp                   Piecewise mapping (implementation).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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

#include "ifmapping/Piecewise.hpp"
#include <sstream>
#include "ifmapping/utils.hpp"
#include "ifmapping/MappingError.hpp"
#include "ifmapping/Piece.hpp"
#include "ifmapping/Constant.hpp"
#include "ifmapping/Linear.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

PiecewiseClassInfo::PiecewiseClassInfo()
{
	name = "Piecewise";
	desc = "Piecewise mapping";
	baseClassInfo.push_back(Ionflux::Mapping::ChainableMapping::CLASS_INFO);
}

PiecewiseClassInfo::~PiecewiseClassInfo()
{
}

// run-time type information instance constants
const PiecewiseClassInfo Piecewise::piecewiseClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Piecewise::CLASS_INFO = &Piecewise::piecewiseClassInfo;

Piecewise::Piecewise()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Piecewise::Piecewise(const Ionflux::Mapping::Piecewise& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Piecewise::Piecewise(const Ionflux::Mapping::PieceVector& initPieces, 
Ionflux::Mapping::Mapping* initFunc, Ionflux::Mapping::MappingValue 
initScale, Ionflux::Mapping::MappingValue initOffset)
: ChainableMapping(initFunc, initScale, initOffset)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addPieces(initPieces);
}

Piecewise::Piecewise(const Ionflux::Mapping::PointSet& points, 
Ionflux::Mapping::Mapping* initFunc, Ionflux::Mapping::MappingValue 
initScale, Ionflux::Mapping::MappingValue initOffset)
: ChainableMapping(initFunc, initScale, initOffset)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	PieceVector target;
	Piece::createPieces(points, target);
	addPieces(target);
}

Piecewise::~Piecewise()
{
	clearPieces();
	// TODO: Nothing ATM. ;-)
}

void Piecewise::addPieces(const Ionflux::Mapping::PieceVector& newPieces)
{
	for (PieceVector::const_iterator i = newPieces.begin(); 
	    i != newPieces.end(); i++)
	    addPiece(*i);
}

Ionflux::Mapping::Piece 
Piecewise::getPieceForT(Ionflux::Mapping::MappingValue t, 
Ionflux::Mapping::MappingValue tolerance) const
{
	Piece* p0 = 0;
	if (pieces.size() == 0)
	    return Piece();
	p0 = pieces[0];
	if (p0 == 0)
	    throw MappingError("Piece is null.");
	Ionflux::Mapping::MappingValue t0 = p0->getParam();
	if ((pieces.size() == 1)
	    || ltOrEq(t, t0, tolerance))
	    /* Use the first (or only) piece with the unmodified 
	       parameter. */
	    return Piece(p0->getMapping(), t);
	p0 = pieces[pieces.size() - 1];
	if (p0 == 0)
	    throw MappingError("Piece is null.");
	if (gtOrEq(t, p0->getParam(), tolerance))
	    // Use the last piece with a truncated parameter.
	    return Piece(p0->getMapping(), t - p0->getParam());
	/* Find the first piece that has a parameter greater than the 
	   current parameter. */
	unsigned int i = 0;
	p0 = pieces[1];
	if (p0 == 0)
	    throw MappingError("Piece is null.");
	Ionflux::Mapping::MappingValue t1 = p0->getParam();
	while (gtOrEq(t, t1, tolerance))
	{
	    i++;
	    /* The (i+1)-th piece exists because there has to be a piece 
	       (with parameter ti) for which t < ti. */
	    p0 = pieces[i + 1];
	    if (p0 == 0)
	        throw MappingError("Piece is null.");
	    t0 = t1;
	    t1 = p0->getParam();
	    if (t1 <= t0)
	    {
	        std::ostringstream message;
	        message << "Piece out of sequence: " << (*p0);
	        throw MappingError(message.str());
	    }
	}
	Piece* p1 = pieces[i];
	// Rescale the parameter.
	Ionflux::Mapping::MappingValue s = (t - p1->getParam()) 
	    / (p0->getParam() - p1->getParam());
	return Piece(p1->getMapping(), s);
}

Ionflux::Mapping::MappingValue 
Piecewise::callWithParam(Ionflux::Mapping::MappingValue value) const
{
	Piece p = getPieceForT(value);
	if (p.getMapping() == 0)
	    return 0.;
	return (*p.getMapping())(p.getParam());
}

Ionflux::Mapping::Piecewise* 
Piecewise::sawtooth(Ionflux::Mapping::MappingValue freq, 
Ionflux::Mapping::MappingValue ampMin, Ionflux::Mapping::MappingValue 
ampMax)
{
	if (freq <= 0.)
	    throw MappingError("Frequency must be positive.");
	Linear* l0 = Linear::create();
	Piecewise* result = Piecewise::create();
	l0->setLower(ampMin);
	l0->setUpper(ampMax);
	MappingValue d = 1. / freq;
	MappingValue t = 0.;
	Piece* p0 = 0;
	while (t < 1.)
	{
	    p0 = Piece::create();
	    p0->setMapping(l0);
	    p0->setParam(t);
	    result->addPiece(p0);
	    t += d;
	}
	Constant* c0 = Constant::create();
	c0->setConstValue(ampMax);
	p0 = Piece::create();
	p0->setMapping(c0);
	p0->setParam(1.);
	result->addPiece(p0);
	return result;
}

Ionflux::Mapping::Piecewise* Piecewise::step(Ionflux::Mapping::MappingValue
numSteps, Ionflux::Mapping::MappingValue minValue, 
Ionflux::Mapping::MappingValue maxValue)
{
	if (numSteps <= 0.)
	    throw MappingError("Number of steps must be positive.");
	Piecewise* result = Piecewise::create();
	MappingValue dt = 1. / numSteps;
	MappingValue dv = (maxValue - minValue) / numSteps;
	MappingValue t = 0.;
	MappingValue v = minValue;
	Piece* p0 = 0;
	while (t <= 1.)
	{
	    p0 = Piece::create();
	    Constant* l0 = Constant::create();
	    l0->setConstValue(v);
	    p0->setMapping(l0);
	    p0->setParam(t);
	    result->addPiece(p0);
	    t += dt;
	    v += dv;
	}
	return result;
}

unsigned int Piecewise::getNumPieces() const
{
	return pieces.size();
}

Ionflux::Mapping::Piece* Piecewise::getPiece(unsigned int elementIndex) 
const
{
	if (elementIndex < pieces.size())
		return pieces[elementIndex];
	return 0;
}

int Piecewise::findPiece(Ionflux::Mapping::Piece* needle, unsigned int 
occurence) const
{
	bool found = false;
	Ionflux::Mapping::Piece* currentPiece = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < pieces.size()))
	{
		currentPiece = pieces[i];
		if (currentPiece == needle)
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

std::vector<Ionflux::Mapping::Piece*>& Piecewise::getPieces()
{
	return pieces;
}

void Piecewise::addPiece(Ionflux::Mapping::Piece* addElement)
{
	addLocalRef(addElement);
	pieces.push_back(addElement);
}

void Piecewise::removePiece(Ionflux::Mapping::Piece* removeElement)
{
	bool found = false;
	Ionflux::Mapping::Piece* currentPiece = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < pieces.size()))
	{
		currentPiece = pieces[i];
		if (currentPiece == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		pieces.erase(pieces.begin() + i);
		if (currentPiece != 0)
			removeLocalRef(currentPiece);
	}
}

void Piecewise::removePieceIndex(unsigned int removeIndex)
{
	if (removeIndex > pieces.size())
		return;
	Ionflux::Mapping::Piece* e0 = pieces[removeIndex];
	pieces.erase(pieces.begin() + removeIndex);
	if (e0 != 0)
		removeLocalRef(e0);
}

void Piecewise::clearPieces()
{
	std::vector<Ionflux::Mapping::Piece*>::iterator i;
	for (i = pieces.begin(); i != pieces.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	pieces.clear();
}

Ionflux::Mapping::Piecewise& Piecewise::operator=(const 
Ionflux::Mapping::Piecewise& other)
{
	ChainableMapping::operator=(other);
	PieceVector v0;
	for (PieceVector::const_iterator i = other.pieces.begin(); 
	    i != other.pieces.end(); i++)
	{
	    Piece* p0 = *i;
	    if (p0 != 0)
	        v0.push_back(new Piece(*p0));
	    else
	        v0.push_back(0);
	}
	clearPieces();
	addPieces(v0);
	return *this;
}

Ionflux::Mapping::Piecewise* Piecewise::copy() const
{
	Piecewise* newPiecewise = create();
	*newPiecewise = *this;
	return newPiecewise;
}

Ionflux::Mapping::Piecewise* 
Piecewise::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Piecewise*>(other);
}

Ionflux::Mapping::Piecewise* 
Piecewise::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Piecewise* newObject = new Piecewise();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Piecewise::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Piecewise.cpp
 * \brief Piecewise mapping implementation.
 */
