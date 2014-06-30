/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Rescale.i                       Rescale mapping (interface).
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
#include "ifmapping/Rescale.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class RescaleClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        RescaleClassInfo();
        virtual ~RescaleClassInfo();
};

class Rescale
: public Ionflux::Mapping::Mapping
{
    public:
        
        Rescale();
		Rescale(const Ionflux::Mapping::Rescale& other);
        Rescale(Ionflux::Mapping::Mapping* initFunc, const 
        Ionflux::Mapping::MappingValueVector* initArgs = 0);
        virtual ~Rescale();
        virtual void addArgs(const Ionflux::Mapping::MappingValueVector& 
        newArgs);
        virtual void findExtremePoints();
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const;
		virtual Ionflux::Mapping::Rescale* copy() const;
		static Ionflux::Mapping::Rescale* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
        virtual Ionflux::Mapping::Mapping* getFunc() const;        
        virtual unsigned int getNumArgs() const;
        virtual Ionflux::Mapping::MappingValue getArg(unsigned int 
        elementIndex = 0) const;
		virtual int findArg(Ionflux::Mapping::MappingValue needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::MappingValue>& getArgs();
        virtual void addArg(Ionflux::Mapping::MappingValue addElement);        
        virtual void removeArg(Ionflux::Mapping::MappingValue 
        removeElement);
		virtual void removeArgIndex(unsigned int removeIndex);
		virtual void clearArgs();
};

}

}
