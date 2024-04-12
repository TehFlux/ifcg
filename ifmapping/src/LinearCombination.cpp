/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * LinearCombination.cpp           Linear combination mapping 
 * (implementation).
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

#include "ifmapping/LinearCombination.hpp"
#include <sstream>
#include "ifmapping/utils.hpp"
#include "ifmapping/MappingError.hpp"
#include "ifmapping/Piece.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

LinearCombinationClassInfo::LinearCombinationClassInfo()
{
	name = "LinearCombination";
	desc = "Linear combination mapping";
}

LinearCombinationClassInfo::~LinearCombinationClassInfo()
{
}

// run-time type information instance constants
const LinearCombinationClassInfo LinearCombination::linearCombinationClassInfo;
const Ionflux::ObjectBase::IFClassInfo* LinearCombination::CLASS_INFO = &LinearCombination::linearCombinationClassInfo;

LinearCombination::LinearCombination()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

LinearCombination::LinearCombination(const Ionflux::Mapping::LinearCombination& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

LinearCombination::LinearCombination(const Ionflux::Mapping::PieceVector& 
initPieces)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	pieces = initPieces;
}

LinearCombination::~LinearCombination()
{
	clearPieces();
	// TODO: Nothing ATM. ;-)
}

void LinearCombination::addPieces(const Ionflux::Mapping::PieceVector& 
newPieces)
{
	for (PieceVector::const_iterator i = newPieces.begin(); 
	    i != newPieces.end(); i++)
	    addPiece(*i);
}

std::string LinearCombination::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

Ionflux::Mapping::MappingValue 
LinearCombination::call(Ionflux::Mapping::MappingValue value) const
{
	Ionflux::Mapping::MappingValue result = 0.;
	for (PieceVector::const_iterator i = pieces.begin(); 
	    i != pieces.end(); i++)
	{
	    Piece* p0 = *i;
	    if (p0 == 0)
	        throw MappingError("Piece is null.");
	    result += (p0->getParam() * (*(p0->getMapping()))(value));
	}
	return result;
}

unsigned int LinearCombination::getNumPieces() const
{
    return pieces.size();
}

Ionflux::Mapping::Piece* LinearCombination::getPiece(unsigned int 
elementIndex) const
{
    if (elementIndex < pieces.size())
		return pieces[elementIndex];
	return 0;
}

int LinearCombination::findPiece(Ionflux::Mapping::Piece* needle, unsigned 
int occurence) const
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

std::vector<Ionflux::Mapping::Piece*>& LinearCombination::getPieces()
{
    return pieces;
}

void LinearCombination::addPiece(Ionflux::Mapping::Piece* addElement)
{
	addLocalRef(addElement);
	pieces.push_back(addElement);
}

void LinearCombination::removePiece(Ionflux::Mapping::Piece* removeElement)
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

void LinearCombination::removePieceIndex(unsigned int removeIndex)
{
    if (removeIndex > pieces.size())
        return;
	Ionflux::Mapping::Piece* e0 = pieces[removeIndex];
    pieces.erase(pieces.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void LinearCombination::clearPieces()
{
    std::vector<Ionflux::Mapping::Piece*>::iterator i;
	for (i = pieces.begin(); i != pieces.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	pieces.clear();
}

Ionflux::Mapping::LinearCombination& LinearCombination::operator=(const 
Ionflux::Mapping::LinearCombination& other)
{
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

Ionflux::Mapping::LinearCombination* LinearCombination::copy() const
{
    LinearCombination* newLinearCombination = create();
    *newLinearCombination = *this;
    return newLinearCombination;
}

Ionflux::Mapping::LinearCombination* 
LinearCombination::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<LinearCombination*>(other);
}

Ionflux::Mapping::LinearCombination* 
LinearCombination::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    LinearCombination* newObject = new LinearCombination();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int LinearCombination::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file LinearCombination.cpp
 * \brief Linear combination mapping implementation.
 */
