/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Piecewise.i                     Piecewise mapping (interface).
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
%{
#include "ifmapping/Piecewise.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class Piece;

class PiecewiseClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PiecewiseClassInfo();
        virtual ~PiecewiseClassInfo();
};

class Piecewise
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        Piecewise();
		Piecewise(const Ionflux::Mapping::Piecewise& other);
        Piecewise(const Ionflux::Mapping::PieceVector& initPieces, 
        Ionflux::Mapping::Mapping* initFunc = 0, 
        Ionflux::Mapping::MappingValue initScale = 1., 
        Ionflux::Mapping::MappingValue initOffset = 0.);
        Piecewise(const Ionflux::Mapping::PointSet& points, 
        Ionflux::Mapping::Mapping* initFunc = 0, 
        Ionflux::Mapping::MappingValue initScale = 1., 
        Ionflux::Mapping::MappingValue initOffset = 0.);
        virtual ~Piecewise();
        virtual void addPieces(const Ionflux::Mapping::PieceVector& 
        newPieces);
        virtual Ionflux::Mapping::Piece 
        getPieceForT(Ionflux::Mapping::MappingValue t, 
        Ionflux::Mapping::MappingValue tolerance = 
        Ionflux::Mapping::DEFAULT_TOLERANCE) const;
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
        static Ionflux::Mapping::Piecewise* 
        sawtooth(Ionflux::Mapping::MappingValue freq = 1., 
        Ionflux::Mapping::MappingValue ampMin = 0., 
        Ionflux::Mapping::MappingValue ampMax = 1.);
        static Ionflux::Mapping::Piecewise* 
        step(Ionflux::Mapping::MappingValue numSteps = 1., 
        Ionflux::Mapping::MappingValue minValue = 0., 
        Ionflux::Mapping::MappingValue maxValue = 1.);
		virtual Ionflux::Mapping::Piecewise* copy() const;
		static Ionflux::Mapping::Piecewise* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::Mapping::Piecewise* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);        
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
