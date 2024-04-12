/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BezierCurve.i                   Cubic Bezier curve (interface).
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
#include "ifmapping/BezierCurve.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class BezierCurveClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BezierCurveClassInfo();
        virtual ~BezierCurveClassInfo();
};

class BezierCurve
: public Ionflux::Mapping::PointMapping, public Ionflux::Mapping::PointSet
{
    public:
        
        BezierCurve();
		BezierCurve(const Ionflux::Mapping::BezierCurve& other);
        BezierCurve(const Ionflux::Mapping::Point& initP0, const 
        Ionflux::Mapping::Point& initP1, const Ionflux::Mapping::Point& 
        initP2, const Ionflux::Mapping::Point& initP3);
        BezierCurve(const Ionflux::Mapping::PointVector& initPoints);
        BezierCurve(Ionflux::Mapping::PointSet& initPoints);
        virtual ~BezierCurve();
        virtual void validate();
        virtual void setControlPoints(const Ionflux::Mapping::PointVector& 
        newPoints);
        virtual void setControlPoints(const Ionflux::Mapping::PointSet& 
        newPoints);
        virtual std::string getValueString() const;
        virtual Ionflux::Mapping::Point call(Ionflux::Mapping::MappingValue
        value);
        virtual Ionflux::Mapping::BezierCurve interpolate(const 
        Ionflux::Mapping::BezierCurve& other, 
        Ionflux::Mapping::MappingValue t = 0.5) const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::Mapping::BezierCurve* copy() const;
		static Ionflux::Mapping::BezierCurve* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::BezierCurve* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::Mapping::BezierCurve* create(const 
		Ionflux::Mapping::Point& initP0, const Ionflux::Mapping::Point& initP1, 
		const Ionflux::Mapping::Point& initP2, const Ionflux::Mapping::Point& 
		initP3, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Mapping::BezierCurve* create(const 
		Ionflux::Mapping::PointVector& initPoints, Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		static Ionflux::Mapping::BezierCurve* create(Ionflux::Mapping::PointSet& 
		initPoints, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setP0(const Ionflux::Mapping::Point& newP0);
        virtual Ionflux::Mapping::Point getP0() const;
        virtual void setP1(const Ionflux::Mapping::Point& newP1);
        virtual Ionflux::Mapping::Point getP1() const;
        virtual void setP2(const Ionflux::Mapping::Point& newP2);
        virtual Ionflux::Mapping::Point getP2() const;
        virtual void setP3(const Ionflux::Mapping::Point& newP3);
        virtual Ionflux::Mapping::Point getP3() const;
};

}

}
