/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Array.i                         Transform node: Array (interface).
 * =========================================================================

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
%{
#include "geoutils/Array.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class ArrayClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ArrayClassInfo();
        virtual ~ArrayClassInfo();
};

class Array
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
		static const unsigned int DEFAULT_NUM_ROWS;
		static const unsigned int DEFAULT_NUM_COLUMNS;
		static const double DEFAULT_CELL_WIDTH;
		static const double DEFAULT_CELL_HEIGHT;
        
        Array();
		Array(const Ionflux::GeoUtils::TransformNodes::Array& other);
        Array(unsigned int initNumRows, unsigned int initNumColumns = 
        DEFAULT_NUM_COLUMNS, double initCellWidth = DEFAULT_CELL_WIDTH, 
        double initCellHeight = DEFAULT_CELL_HEIGHT, const 
        Ionflux::GeoUtils::Vector3& initOffset = GeoUtils::Vector3::ZERO, 
        const Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Array();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::Array* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Array* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Array* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setOffset(const Ionflux::GeoUtils::Vector3& 
        newOffset);
        virtual Ionflux::GeoUtils::Vector3 getOffset() const;
        virtual void setNumRows(unsigned int newNumRows);
        virtual unsigned int getNumRows() const;
        virtual void setNumColumns(unsigned int newNumColumns);
        virtual unsigned int getNumColumns() const;
        virtual void setCellWidth(double newCellWidth);
        virtual double getCellWidth() const;
        virtual void setCellHeight(double newCellHeight);
        virtual double getCellHeight() const;
};

}

}

}
