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
        virtual void setElement(unsigned int index, double value);
        virtual void setElement(unsigned int rowIndex, unsigned int 
        colIndex, double value);
        virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
        newElements);
        virtual void setElements(const Ionflux::GeoUtils::Vector& 
        newElements, unsigned int sourceOffset = 0, unsigned int 
        targetOffset = 0);
        virtual void setElements(const Ionflux::GeoUtils::Matrix& other, 
        unsigned int sourceRowOffset = 0, unsigned int sourceColOffset = 0,
        unsigned int targetRowOffset = 0, unsigned int targetColOffset = 
        0);
        virtual void setElements(double x0, double x1 = 0., double x2 = 0.,
        double x3 = 0., double x4 = 0., double x5 = 0., double x6 = 0., 
        double x7 = 0., double x8 = 0., double x9 = 0., double x10 = 0., 
        double x11 = 0., double x12 = 0.);
        virtual void getRow(unsigned int rowIndex, 
        Ionflux::GeoUtils::Vector& target) const;
        virtual void getCol(unsigned int colIndex, 
        Ionflux::GeoUtils::Vector& target) const;
        virtual void setRow(unsigned int rowIndex, const 
        Ionflux::GeoUtils::Vector& v, unsigned int sourceOffset = 0, 
        unsigned int targetOffset = 0);
        virtual void setCol(unsigned int colIndex, const 
        Ionflux::GeoUtils::Vector& v, unsigned int sourceOffset = 0, 
        unsigned int targetOffset = 0);
        virtual void transposeIP();
        virtual double trace() const;
        virtual void transform(const Ionflux::GeoUtils::Vector& v, 
        Ionflux::GeoUtils::Vector& target);
        virtual void multiply(const Ionflux::GeoUtils::Matrix& other, 
        Ionflux::GeoUtils::Matrix& target);
        virtual void permuteRowsIP(const Ionflux::GeoUtils::Vector& p);
        virtual void permuteColsIP(const Ionflux::GeoUtils::Vector& p);
        virtual std::string getValueString() const;
        virtual std::string getValueStringF(unsigned int fieldWidth = 5, 
        unsigned int precision = 3, const std::string& colSep = " ", const 
        std::string& rowSep = "\n", const std::string& rowPrefix = "") 
        const;
        virtual unsigned int getNumElements() const;
        virtual unsigned int getNumRows() const;
        virtual unsigned int getNumCols() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Matrix* copy() const;
		static Ionflux::GeoUtils::Matrix* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Matrix* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

}

}
