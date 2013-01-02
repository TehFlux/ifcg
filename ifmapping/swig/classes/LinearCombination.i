/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * LinearCombination.i             Linear combination mapping (interface).
 * =========================================================================

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
%{
#include "ifmapping/LinearCombination.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class Piece;

class LinearCombinationClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        LinearCombinationClassInfo();
        virtual ~LinearCombinationClassInfo();
};

class LinearCombination
: public Ionflux::Mapping::Mapping
{
    public:
        
        LinearCombination();
		LinearCombination(const Ionflux::Mapping::LinearCombination& other);
        LinearCombination(const Ionflux::Mapping::PieceVector& initPieces);
        virtual ~LinearCombination();
        virtual void addPieces(const Ionflux::Mapping::PieceVector& 
        newPieces);
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const;
		virtual Ionflux::Mapping::LinearCombination* copy() const;
		static Ionflux::Mapping::LinearCombination* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::LinearCombination* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumPieces() const;
        virtual Ionflux::Mapping::Piece* getPiece(unsigned int elementIndex
        = 0) const;
		virtual int findPiece(Ionflux::Mapping::Piece* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::Piece*>& getPieces();
        virtual void addPiece(Ionflux::Mapping::Piece* addElement);        
        virtual void removePiece(Ionflux::Mapping::Piece* removeElement);
		virtual void removePieceIndex(unsigned int removeIndex);
		virtual void clearPieces();
};

}

}
