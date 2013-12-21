/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * MatrixMN.i                      Matrix (NxM) (interface).
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
#include "geoutils/MatrixMN.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VectorN;

class MatrixMNClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MatrixMNClassInfo();
        virtual ~MatrixMNClassInfo();
};

class MatrixMN
: public Ionflux::GeoUtils::Matrix
{
    public:
        
        MatrixMN();
		MatrixMN(const Ionflux::GeoUtils::MatrixMN& other);
        MatrixMN(unsigned int initNumCols, unsigned int initNumRows);
        MatrixMN(unsigned int initNumCols, unsigned int initNumRows, double
        x0, double x1 = 0., double x2 = 0., double x3 = 0., double x4 = 0.,
        double x5 = 0., double x6 = 0., double x7 = 0., double x8 = 0., 
        double x9 = 0., double x10 = 0., double x11 = 0., double x12 = 0.);
        virtual ~MatrixMN();
        virtual Ionflux::GeoUtils::MatrixMN transpose() const;
        virtual void qrDecomp(Ionflux::GeoUtils::MatrixMN& q, 
        Ionflux::GeoUtils::MatrixMN& r) const;
        virtual Ionflux::GeoUtils::VectorN solve(const 
        Ionflux::GeoUtils::VectorN& b) const;
        virtual Ionflux::GeoUtils::MatrixMN invert() const;
        static void qrSolve(const Ionflux::GeoUtils::MatrixMN& q, const 
        Ionflux::GeoUtils::MatrixMN& r, const Ionflux::GeoUtils::VectorN& 
        b, Ionflux::GeoUtils::VectorN& x);
        virtual unsigned int getNumElements() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::MatrixMN* copy() const;
		static Ionflux::GeoUtils::MatrixMN* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::GeoUtils::MatrixMN* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		static Ionflux::GeoUtils::MatrixMN* create(unsigned int initNumCols, 
		unsigned int initNumRows, Ionflux::ObjectBase::IFObject* parentObject = 
		0);
		static Ionflux::GeoUtils::MatrixMN* create(unsigned int initNumCols, 
		unsigned int initNumRows, double x0, double x1 = 0., double x2 = 0., 
		double x3 = 0., double x4 = 0., double x5 = 0., double x6 = 0., double x7
		= 0., double x8 = 0., double x9 = 0., double x10 = 0., double x11 = 0., 
		double x12 = 0., Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setNumRows(unsigned int newNumRows);
        virtual unsigned int getNumRows() const;
        virtual void setNumCols(unsigned int newNumCols);
        virtual unsigned int getNumCols() const;
};

}

}
