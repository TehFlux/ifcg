/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BezierSpline.i                  Cubic Bezier spline (interface).
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
#include "ifmapping/BezierSpline.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class BezierSplineClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BezierSplineClassInfo();
        virtual ~BezierSplineClassInfo();
};

class BezierSpline
: public Ionflux::Mapping::PointMapping
{
    public:
        
        BezierSpline();
		BezierSpline(const Ionflux::Mapping::BezierSpline& other);
        virtual ~BezierSpline();
        virtual unsigned int getSegmentIndex(Ionflux::Mapping::MappingValue
        t) const;
        virtual void getPoints(Ionflux::Mapping::PointSet& target, 
        Ionflux::Mapping::MappingValue x0 = 0., 
        Ionflux::Mapping::MappingValue x1 = 1., unsigned int numPoints = 
        10, Ionflux::Mapping::CoordinateID coord = Ionflux::Mapping::C_X, 
        Ionflux::Mapping::MappingValue precision = 
        Ionflux::Mapping::PointMapping::DEFAULT_PRECISION);
        virtual void initFromSVG(const std::string& rawData);
        virtual Ionflux::Mapping::Point call(Ionflux::Mapping::MappingValue
        value);
        virtual Ionflux::Mapping::BezierSpline interpolate(const 
        Ionflux::Mapping::BezierSpline& other, 
        Ionflux::Mapping::MappingValue t = 0.5) const;
        virtual Ionflux::Mapping::Mapping* 
        createFunc(Ionflux::Mapping::MappingValue paramScale = 1., 
        Ionflux::Mapping::MappingValue paramOffset = 0., const 
        Ionflux::Mapping::Point& outputScale = 
        Ionflux::Mapping::Point::ONES, const Ionflux::Mapping::Point& 
        outputOffset = Ionflux::Mapping::Point::ORIGIN, 
        Ionflux::Mapping::CoordinateID inCoord = Ionflux::Mapping::C_X, 
        Ionflux::Mapping::CoordinateID outCoord = Ionflux::Mapping::C_Y);
        virtual std::string getSVGPathData(const 
        Ionflux::Mapping::CoordinateID imagePlaneNormal = 
        Ionflux::Mapping::C_Z) const;
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::Mapping::BezierSpline* copy() const;
		static Ionflux::Mapping::BezierSpline* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::BezierSpline* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;        
        virtual unsigned int getNumSegments() const;
        virtual Ionflux::Mapping::BezierCurve* getSegment(unsigned int 
        elementIndex = 0) const;
		virtual int findSegment(Ionflux::Mapping::BezierCurve* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::BezierCurve*>& getSegments();
        virtual void addSegment(Ionflux::Mapping::BezierCurve* addElement);
		virtual Ionflux::Mapping::BezierCurve* addSegment();
		virtual void addSegments(std::vector<Ionflux::Mapping::BezierCurve*>& 
		newSegments);
		virtual void addSegments(Ionflux::Mapping::BezierSpline* newSegments);        
        virtual void removeSegment(Ionflux::Mapping::BezierCurve* 
        removeElement);
		virtual void removeSegmentIndex(unsigned int removeIndex);
		virtual void clearSegments();
};

}

}
