/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PointSample.i                   Point sample (interface).
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
#include "ifmapping/PointSample.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class PointSampleClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PointSampleClassInfo();
        virtual ~PointSampleClassInfo();
};

class PointSample
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        PointSample();
		PointSample(const Ionflux::Mapping::PointSample& other);
        PointSample(Ionflux::Mapping::MappingValue initParam, 
        Ionflux::Mapping::Point* initCoords = 0, 
        Ionflux::Mapping::MappingValue initArcLength = 0.);
        virtual ~PointSample();
        virtual Ionflux::Mapping::MappingValue 
        getValue(Ionflux::Mapping::SamplingMode samplingMode = 
        Ionflux::Mapping::SAMPLING_MODE_PARAM);
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::Mapping::PointSample* copy() const;
		static Ionflux::Mapping::PointSample* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::PointSample* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::Mapping::PointSample* 
		create(Ionflux::Mapping::MappingValue initParam, Ionflux::Mapping::Point*
		initCoords = 0, Ionflux::Mapping::MappingValue initArcLength = 0., 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setParam(Ionflux::Mapping::MappingValue newParam);
        virtual Ionflux::Mapping::MappingValue getParam() const;
        virtual void setCoords(Ionflux::Mapping::Point* newCoords);
        virtual Ionflux::Mapping::Point* getCoords() const;
        virtual void setArcLength(Ionflux::Mapping::MappingValue 
        newArcLength);
        virtual Ionflux::Mapping::MappingValue getArcLength() const;
};

}

}
