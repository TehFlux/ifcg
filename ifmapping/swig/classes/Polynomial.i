/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polynomial.i                    Polynomial mapping (interface).
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
#include "ifmapping/Polynomial.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class PolynomialClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PolynomialClassInfo();
        virtual ~PolynomialClassInfo();
};

class Polynomial
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        Polynomial();
		Polynomial(const Ionflux::Mapping::Polynomial& other);
        Polynomial(const Ionflux::Mapping::MappingValueVector& 
        initCoefficients, Ionflux::Mapping::MappingValue initScale = 1., 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~Polynomial();
        virtual void addCoefficients(const 
        Ionflux::Mapping::MappingValueVector& newCoefficients);
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		virtual Ionflux::Mapping::Polynomial* copy() const;
		static Ionflux::Mapping::Polynomial* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::Polynomial* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumCoefficients() const;
        virtual Ionflux::Mapping::MappingValue getCoefficient(unsigned int 
        elementIndex = 0) const;
		virtual int findCoefficient(Ionflux::Mapping::MappingValue needle, 
		unsigned int occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::MappingValue>& 
        getCoefficients();
        virtual void addCoefficient(Ionflux::Mapping::MappingValue 
        addElement);        
        virtual void removeCoefficient(Ionflux::Mapping::MappingValue 
        removeElement);
		virtual void removeCoefficientIndex(unsigned int removeIndex);
		virtual void clearCoefficients();
};

}

}
