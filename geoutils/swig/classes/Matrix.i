/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix.i                        Matrix (interface).
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
%{
#include "geoutils/Matrix.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class MatrixClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MatrixClassInfo();
        virtual ~MatrixClassInfo();
};

class Matrix
: public Ionflux::GeoUtils::Vector
{
    public:
		static const unsigned int NUM_ROWS;
		static const unsigned int NUM_COLS;
        
        Matrix();
		Matrix(const Ionflux::GeoUtils::Matrix& other);
        virtual ~Matrix();
        virtual double getElement(unsigned int rowIndex, unsigned int 
        colIndex) const;
        virtual void setElement(unsigned int rowIndex, unsigned int 
        colIndex, double value);
        virtual void getRow(unsigned int rowIndex, 
        Ionflux::GeoUtils::Vector& target) const;
        virtual void getCol(unsigned int colIndex, 
        Ionflux::GeoUtils::Vector& target) const;
        virtual void transposeIP();
        virtual double trace() const;
        virtual void transform(const Ionflux::GeoUtils::Vector& v, 
        Ionflux::GeoUtils::Vector& target);
        virtual void multiply(const Ionflux::GeoUtils::Matrix& other, 
        Ionflux::GeoUtils::Matrix& target);
        virtual void permuteRowsIP(const Ionflux::GeoUtils::Vector& p);
        virtual void permuteColsIP(const Ionflux::GeoUtils::Vector& p);
        virtual std::string getValueString() const;
        virtual unsigned int getNumElements() const;
        virtual unsigned int getNumRows() const;
        virtual unsigned int getNumCols() const;
		virtual Ionflux::GeoUtils::Matrix* copy() const;
		static Ionflux::GeoUtils::Matrix* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Matrix* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

namespace XMLUtils
{

void getMatrix(const std::string& data, Ionflux::GeoUtils::Matrix& target);

}

}

}
