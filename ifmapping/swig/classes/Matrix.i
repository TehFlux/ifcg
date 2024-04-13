/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix.i                        Matrix (interface).
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
%{
#include "ifmapping/Matrix.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class MatrixClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MatrixClassInfo();
        virtual ~MatrixClassInfo();
};

class Matrix
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Matrix();
		Matrix(const Ionflux::Mapping::Matrix& other);
        Matrix(unsigned int initNumRows, unsigned int initNumCols, const 
        Ionflux::ObjectBase::DoubleVector* const initValues = nullptr);
        Matrix(unsigned int initNumRows, unsigned int initNumCols, double 
        initV00, double initV01 = 0., double initV02 = 0., double initV03 =
        0., double initV04 = 0., double initV05 = 0., double initV06 = 0., 
        double initV07 = 0., double initV08 = 0., double initV09 = 0., 
        double initV10 = 0., double initV11 = 0.);
        virtual ~Matrix();
        virtual void init(unsigned int newNumRows = 0, unsigned int 
        newNumCols = 0);
        virtual bool isWithinBounds(unsigned int row, unsigned int col) 
        const;
        virtual void setValue(unsigned int row, unsigned int col, double 
        v);
        virtual void setValues(const Ionflux::ObjectBase::DoubleVector 
        newValues);
        virtual void getValues(Ionflux::ObjectBase::DoubleVector& target);
        virtual double getValue(unsigned int row, unsigned int col) const;
        virtual void getRow(unsigned int row, 
        Ionflux::ObjectBase::DoubleVector& target) const;
        virtual void getCol(unsigned int col, 
        Ionflux::ObjectBase::DoubleVector& target) const;
        virtual double v(unsigned int row, unsigned int col) const;
        virtual void normalize();
        virtual void rescale();
        virtual void setGaussian(double stdDev = 0.);
        virtual void setInversePower(double exponent = 2., double falloff =
        0.0001);
        virtual void sampleColumns(unsigned int numSamples, 
        Ionflux::Mapping::Matrix& target, double sampleOffset = 0.5);
        virtual bool operator==(const Ionflux::Mapping::Matrix& other) 
        const;
        virtual bool operator!=(const Ionflux::Mapping::Matrix& other) 
        const;
        virtual std::string getString() const;
        virtual std::string getValueStringFormatted(unsigned int precision 
        = 3, unsigned int fieldWidth = 8, unsigned int offsetCols = 0, 
        unsigned int offsetRows = 0, unsigned int maxNumCols = 20, unsigned
        int maxNumRows = 20) const;
		virtual Ionflux::Mapping::Matrix* copy() const;
		static Ionflux::Mapping::Matrix* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Matrix* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::Mapping::Matrix* create(unsigned int initNumRows, 
		unsigned int initNumCols, const Ionflux::ObjectBase::DoubleVector* const 
		initValues = nullptr, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Mapping::Matrix* create(unsigned int initNumRows, 
		unsigned int initNumCols, double initV00, double initV01 = 0., double 
		initV02 = 0., double initV03 = 0., double initV04 = 0., double initV05 = 
		0., double initV06 = 0., double initV07 = 0., double initV08 = 0., double
		initV09 = 0., double initV10 = 0., double initV11 = 0., 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual unsigned int getNumRows() const;
        virtual unsigned int getNumCols() const;
};

}

}
