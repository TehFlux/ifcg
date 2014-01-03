/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Segment.i                       Segment (interface).
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
#include "ifmapping/Segment.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class PointSample;

class SegmentClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SegmentClassInfo();
        virtual ~SegmentClassInfo();
};

class Segment
: public Ionflux::Mapping::PointMapping
{
    public:
		static const Ionflux::Mapping::MappingValue DEFAULT_ERROR_THRESHOLD;
        
        Segment();
		Segment(const Ionflux::Mapping::Segment& other);
        Segment(Ionflux::Mapping::PointMapping* initFunc, 
        Ionflux::Mapping::MappingValue t0 = 0., 
        Ionflux::Mapping::MappingValue t1 = 1.);
        Segment(Ionflux::Mapping::PointMapping* initFunc, 
        Ionflux::Mapping::PointSample* initP0, 
        Ionflux::Mapping::PointSample* initP1 = 0);
        virtual ~Segment();
        virtual Ionflux::Mapping::MappingValue getLength(bool recursive = 
        false, unsigned int maxDepth = 0, unsigned int depth = 0) const;
        virtual Ionflux::Mapping::MappingValue getLengthError(bool 
        relativeError = true, unsigned int maxDepth = 1, double t = 
        Ionflux::Mapping::DEFAULT_TOLERANCE) const;
        virtual void split(unsigned int numSplits = 2, bool recursive = 
        false, bool relativeError = true, Ionflux::Mapping::MappingValue 
        errorThreshold = 
        Ionflux::Mapping::Segment::DEFAULT_ERROR_THRESHOLD, unsigned int 
        maxDepth = 0, unsigned int depth = 0, double t = 
        Ionflux::Mapping::DEFAULT_TOLERANCE);
        virtual Ionflux::Mapping::Segment* 
        findSegment(Ionflux::Mapping::MappingValue value, 
        Ionflux::Mapping::SamplingMode samplingMode = 
        Ionflux::Mapping::SAMPLING_MODE_PARAM, double t = 
        Ionflux::Mapping::DEFAULT_TOLERANCE);
        virtual Ionflux::Mapping::PointSample* 
        getSample0(Ionflux::Mapping::MappingValue value, 
        Ionflux::Mapping::SamplingMode samplingMode = 
        Ionflux::Mapping::SAMPLING_MODE_PARAM, bool recursive = false, 
        unsigned int maxDepth = 0, unsigned int depth = 0, double t = 
        Ionflux::Mapping::DEFAULT_TOLERANCE);
        virtual std::string getValueString() const;
        virtual Ionflux::Mapping::MappingValue 
        getParamCoord(Ionflux::Mapping::MappingValue value, 
        Ionflux::Mapping::CoordinateID coord = Ionflux::Mapping::C_X, 
        Ionflux::Mapping::MappingValue precision = 
        Ionflux::Mapping::PointMapping::DEFAULT_PRECISION);
        virtual Ionflux::Mapping::MappingValue 
        getParamArcLength(Ionflux::Mapping::MappingValue value, 
        Ionflux::Mapping::MappingValue relativeError = 
        Ionflux::Mapping::PointMapping::DEFAULT_RELATIVE_ERROR, unsigned 
        int maxNumIterations = 
        Ionflux::Mapping::PointMapping::DEFAULT_MAX_NUM_ITERATIONS, 
        Ionflux::Mapping::MappingValue precision = 
        Ionflux::Mapping::PointMapping::DEFAULT_PRECISION);
        virtual Ionflux::Mapping::PointSample* 
        getSample(Ionflux::Mapping::MappingValue value, bool 
        calculateArcLength = false, Ionflux::Mapping::MappingValue 
        relativeError = 
        Ionflux::Mapping::PointMapping::DEFAULT_RELATIVE_ERROR, unsigned 
        int maxNumIterations = 
        Ionflux::Mapping::PointMapping::DEFAULT_MAX_NUM_ITERATIONS);
        virtual Ionflux::Mapping::Point call(Ionflux::Mapping::MappingValue
        value);
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::Mapping::Segment* copy() const;
		static Ionflux::Mapping::Segment* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Segment* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::Mapping::Segment* create(Ionflux::Mapping::PointMapping* 
		initFunc, Ionflux::Mapping::MappingValue t0 = 0., 
		Ionflux::Mapping::MappingValue t1 = 1., Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::Mapping::Segment* create(Ionflux::Mapping::PointMapping* 
		initFunc, Ionflux::Mapping::PointSample* initP0, 
		Ionflux::Mapping::PointSample* initP1 = 0, Ionflux::ObjectBase::IFObject*
		parentObject = 0);
        virtual void setFunc(Ionflux::Mapping::PointMapping* newFunc);
        virtual Ionflux::Mapping::PointMapping* getFunc() const;
        virtual void setP0(Ionflux::Mapping::PointSample* newP0);
        virtual Ionflux::Mapping::PointSample* getP0() const;
        virtual void setP1(Ionflux::Mapping::PointSample* newP1);
        virtual Ionflux::Mapping::PointSample* getP1() const;        
        virtual unsigned int getNumSegments() const;
        virtual Ionflux::Mapping::Segment* getSegment(unsigned int 
        elementIndex = 0) const;
		virtual int findSegment(Ionflux::Mapping::Segment* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::Segment*>& getSegments();
        virtual void addSegment(Ionflux::Mapping::Segment* addElement);
		virtual Ionflux::Mapping::Segment* addSegment();
		virtual void addSegments(std::vector<Ionflux::Mapping::Segment*>& 
		newSegments);
		virtual void addSegments(Ionflux::Mapping::Segment* newSegments);        
        virtual void removeSegment(Ionflux::Mapping::Segment* 
        removeElement);
		virtual void removeSegmentIndex(unsigned int removeIndex);
		virtual void clearSegments();
};

}

}
