/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix.i                        Matrix (interface).
 * =========================================================================
 * 
 * This file is part of Altjira - Ionflux' Image Processing Library.
 * 
 * Altjira - Ionflux' Image Processing Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * Altjira - Ionflux' Image Processing Library is distributed in the hope 
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Altjira - Ionflux' Image Processing Library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */
%{
#include "altjira/Matrix.hpp"
%}

namespace Ionflux
{

namespace Altjira
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
		Matrix(const Ionflux::Altjira::Matrix& other);
        Matrix(unsigned int initNumRows, unsigned int initNumCols = 0);
        virtual ~Matrix();
        virtual void init(unsigned int newNumRows = 0, unsigned int 
        newNumCols = 0);
        virtual void setValue(unsigned int row, unsigned int col, double 
        v);
        virtual double getValue(unsigned int row, unsigned int col) const;
        virtual double v(unsigned int row, unsigned int col) const;
        virtual void normalize();
        virtual void rescale();
        virtual void setGaussian(double stdDev = 0.);
        virtual void setInversePower(double exponent = 2., double falloff =
        0.0001);
        virtual bool operator==(const Ionflux::Altjira::Matrix& other) 
        const;
        virtual bool operator!=(const Ionflux::Altjira::Matrix& other) 
        const;
        virtual std::string getString() const;
		virtual Ionflux::Altjira::Matrix* copy() const;
		static Ionflux::Altjira::Matrix* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Altjira::Matrix* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual unsigned int getNumRows() const;
        virtual unsigned int getNumCols() const;
};

}

}
