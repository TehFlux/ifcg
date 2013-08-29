/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Piece.i                         Piece (interface).
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
#include "ifmapping/Piece.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class Mapping;

class PieceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PieceClassInfo();
        virtual ~PieceClassInfo();
};

class Piece
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Piece();
		Piece(const Ionflux::Mapping::Piece& other);
        Piece(Ionflux::Mapping::Mapping* initMapping, 
        Ionflux::Mapping::MappingValue initParam = 0.);
        virtual ~Piece();
        virtual std::string getString() const;
        static Ionflux::Mapping::Piece* create(Ionflux::Mapping::Mapping* 
        initMapping, Ionflux::Mapping::MappingValue initParam);
        static void createPieces(const Ionflux::Mapping::PointSet& points, 
        Ionflux::Mapping::PieceVector& target, const 
        Ionflux::Mapping::Point& offset = Ionflux::Mapping::Point::ORIGIN, 
        const Ionflux::Mapping::Point& scale = 
        Ionflux::Mapping::Point::ONES, bool addConstant = true);
		virtual Ionflux::Mapping::Piece* copy() const;
		static Ionflux::Mapping::Piece* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Piece* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setMapping(Ionflux::Mapping::Mapping* newMapping);
        virtual Ionflux::Mapping::Mapping* getMapping() const;
        virtual void setParam(Ionflux::Mapping::MappingValue newParam);
        virtual Ionflux::Mapping::MappingValue getParam() const;
};

}

}
