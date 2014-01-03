/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BezierCurve.cpp                 Cubic Bezier curve (implementation).
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

#include "ifmapping/BezierCurve.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <sstream>
#include "ifmapping/utils.hpp"
#include "ifmapping/MappingError.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "ifmapping/xmlutils.hpp"
#include "ifmapping/xmlio/BezierCurveXMLFactory.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

BezierCurveClassInfo::BezierCurveClassInfo()
{
	name = "BezierCurve";
	desc = "Cubic Bezier curve";
	baseClassInfo.push_back(Ionflux::Mapping::PointMapping::CLASS_INFO);
	baseClassInfo.push_back(Ionflux::Mapping::PointSet::CLASS_INFO);
}

BezierCurveClassInfo::~BezierCurveClassInfo()
{
}

// run-time type information instance constants
const BezierCurveClassInfo BezierCurve::bezierCurveClassInfo;
const Ionflux::ObjectBase::IFClassInfo* BezierCurve::CLASS_INFO = &BezierCurve::bezierCurveClassInfo;

const std::string BezierCurve::XML_ELEMENT_NAME = "bezcurve";

BezierCurve::BezierCurve()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

BezierCurve::BezierCurve(const Ionflux::Mapping::BezierCurve& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

BezierCurve::BezierCurve(const Ionflux::Mapping::Point& initP0, const 
Ionflux::Mapping::Point& initP1, const Ionflux::Mapping::Point& initP2, 
const Ionflux::Mapping::Point& initP3)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addPoint(initP0.copy());
	addPoint(initP1.copy());
	addPoint(initP2.copy());
	addPoint(initP3.copy());
}

BezierCurve::BezierCurve(const Ionflux::Mapping::PointVector& initPoints)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addPoints(initPoints);
	validate();
}

BezierCurve::BezierCurve(Ionflux::Mapping::PointSet& initPoints)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addPoints(&initPoints);
	validate();
}

BezierCurve::~BezierCurve()
{
	// TODO: Nothing ATM. ;-)
}

void BezierCurve::validate()
{
	unsigned int numPoints = getNumPoints();
	unsigned int k = 0;
	while (k < 4)
	{
	    if (k < numPoints)
	    {
	        if (points[k] == 0)
	        {
	            Point* p0 = Point::create();
	            addLocalRef(p0);
	            points[k] = p0;
	        }
	    } else
	        addPoint();
	    k++;
	}
}

void BezierCurve::setControlPoints(const Ionflux::Mapping::PointVector& 
newPoints)
{
	unsigned int numPoints = getNumPoints();
	for (unsigned int i = 0; i < newPoints.size(); i++)
	{
	    Point* p0 = newPoints[i];
	    if ((i < numPoints) 
	        && (p0 != 0))
	        *(points[i]) = *p0;
	    else
	    {
	        if (p0 != 0)
	            addPoint(p0->copy());
	        else
	            addPoint(0);
	    }
	}
}

void BezierCurve::setControlPoints(const Ionflux::Mapping::PointSet& 
newPoints)
{
	unsigned int numPoints = getNumPoints();
	for (unsigned int i = 0; i < newPoints.getNumPoints(); i++)
	{
	    Point* p0 = newPoints.getPoint(i);
	    if ((i < numPoints) 
	        && (p0 != 0))
	        *(points[i]) = *p0;
	    else
	    {
	        if (p0 != 0)
	            addPoint(p0->copy());
	        else
	            addPoint(0);
	    }
	}
}

std::string BezierCurve::getValueString() const
{
	std::ostringstream status;
	for (unsigned int i = 0; i < 4; i++)
	{
	    if (i > 0)
	        status << ", ";
	    Point* p0 = points[i];
	    if (p0 != 0)
	        status << "(" << p0->getValueString() << ")";
	    else
	        status << "<null>";
	}
	return status.str();
}

Ionflux::Mapping::Point BezierCurve::call(Ionflux::Mapping::MappingValue 
value)
{
	// TODO: Implementation.
	return bezier(value, points);
}

Ionflux::Mapping::BezierCurve BezierCurve::interpolate(const 
Ionflux::Mapping::BezierCurve& other, Ionflux::Mapping::MappingValue t) 
const
{
	/* <---- DEBUG ----- //
	std::ostringstream message;
	// <---- DEBUG ----- */
	BezierCurve result;
	for (unsigned int i = 0; i < points.size(); i++)
	{
	    Point* p0 = points[i];
	    if (p0 == 0)
	        throw MappingError(getErrorString("Point (0) is null.", 
	            "interpolate"));
	    Point* p1 = other.points[i];
	    if (p1 == 0)
	        throw MappingError(getErrorString("Point (1) is null.", 
	            "interpolate"));
	    Point p2 = p0->interpolate(*p1, t);
	    /* <---- DEBUG ----- //
	    message.str("");
	    message << "(" << p0.x << ", " << p0.y << ")";
	    log(IFLogMessage(message.str(), VL_DEBUG, this, "interpolate"));
	    // <---- DEBUG ----- */
	    *(result.points[i]) = p2;
	}
	return result;
}

void BezierCurve::setP0(const Ionflux::Mapping::Point& newP0)
{
	*(points[0]) = newP0;
}

Ionflux::Mapping::Point BezierCurve::getP0() const
{
	return *(points[0]);
}

void BezierCurve::setP1(const Ionflux::Mapping::Point& newP1)
{
	*(points[1]) = newP1;
}

Ionflux::Mapping::Point BezierCurve::getP1() const
{
	return *(points[1]);
}

void BezierCurve::setP2(const Ionflux::Mapping::Point& newP2)
{
	*(points[2]) = newP2;
}

Ionflux::Mapping::Point BezierCurve::getP2() const
{
	return *(points[2]);
}

void BezierCurve::setP3(const Ionflux::Mapping::Point& newP3)
{
	*(points[3]) = newP3;
}

Ionflux::Mapping::Point BezierCurve::getP3() const
{
	return *(points[3]);
}

Ionflux::Mapping::BezierCurve& BezierCurve::operator=(const 
Ionflux::Mapping::BezierCurve& other)
{
    PointSet::operator=(other);
    validate();
	return *this;
}

Ionflux::Mapping::BezierCurve* BezierCurve::copy() const
{
    BezierCurve* newBezierCurve = create();
    *newBezierCurve = *this;
    return newBezierCurve;
}

Ionflux::Mapping::BezierCurve* 
BezierCurve::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<BezierCurve*>(other);
}

Ionflux::Mapping::BezierCurve* 
BezierCurve::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    BezierCurve* newObject = new BezierCurve();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Mapping::BezierCurve* BezierCurve::create(const 
Ionflux::Mapping::Point& initP0, const Ionflux::Mapping::Point& initP1, 
const Ionflux::Mapping::Point& initP2, const Ionflux::Mapping::Point& 
initP3, Ionflux::ObjectBase::IFObject* parentObject)
{
    BezierCurve* newObject = new BezierCurve(initP0, initP1, initP2, 
    initP3);
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Mapping::BezierCurve* BezierCurve::create(const 
Ionflux::Mapping::PointVector& initPoints, Ionflux::ObjectBase::IFObject* 
parentObject)
{
    BezierCurve* newObject = new BezierCurve(initPoints);
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Mapping::BezierCurve* 
BezierCurve::create(Ionflux::Mapping::PointSet& initPoints, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    BezierCurve* newObject = new BezierCurve(initPoints);
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

std::string BezierCurve::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string BezierCurve::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::Mapping::PointMapping::getXMLAttributeData();
	d0 << " " << Ionflux::Mapping::PointSet::getXMLAttributeData();
	return d0.str();
}

void BezierCurve::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::Mapping::PointMapping::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	Ionflux::Mapping::PointSet::getXMLChildData(bc0, indentLevel);
	d0 << "\n" << bc0;
	target = d0.str();
}

void BezierCurve::loadFromXMLFile(const std::string& fileName)
{
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, getXMLElementName());
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
BezierCurve::getXMLObjectFactory()
{
	static Ionflux::Mapping::XMLUtils::BezierCurveXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::Mapping::XMLUtils::BezierCurveXMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 0;
        bFac = Ionflux::Mapping::PointMapping::getXMLObjectFactory();
        bFac->addFactory(fac0);
        bFac = Ionflux::Mapping::PointSet::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file BezierCurve.cpp
 * \brief Cubic Bezier curve implementation.
 */
