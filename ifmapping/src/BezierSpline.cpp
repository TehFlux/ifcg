/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BezierSpline.cpp                Cubic Bezier spline (implementation).
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

#include "ifmapping/BezierSpline.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <sstream>
#include <cmath>
#include "ifobject/objectutils.hpp"
#include "ifmapping/utils.hpp"
#include "ifmapping/MappingError.hpp"
#include "ifmapping/EvalCoord.hpp"
#include "ifmapping/PointCoord.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "ifmapping/xmlutils.hpp"
#include "ifmapping/xmlio/BezierSplineXMLFactory.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

BezierSplineClassInfo::BezierSplineClassInfo()
{
	name = "BezierSpline";
	desc = "Cubic Bezier spline";
	baseClassInfo.push_back(Ionflux::Mapping::PointMapping::CLASS_INFO);
}

BezierSplineClassInfo::~BezierSplineClassInfo()
{
}

// run-time type information instance constants
const BezierSplineClassInfo BezierSpline::bezierSplineClassInfo;
const Ionflux::ObjectBase::IFClassInfo* BezierSpline::CLASS_INFO = &BezierSpline::bezierSplineClassInfo;

const std::string BezierSpline::XML_ELEMENT_NAME = "bezspline";

BezierSpline::BezierSpline()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

BezierSpline::BezierSpline(const Ionflux::Mapping::BezierSpline& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

BezierSpline::~BezierSpline()
{
	clearSegments();
	// TODO: Nothing ATM. ;-)
}

unsigned int BezierSpline::getSegmentIndex(Ionflux::Mapping::MappingValue 
t) const
{
	unsigned int numSegments0 = getNumSegments();
	if (numSegments0 == 0)
	    throw MappingError(getErrorString(
	        "Spline does not have any segments.", 
	        "getSegmentIndex"));
	int si = static_cast<int>(floor(t * numSegments0));
	if (si < 0)
	    si = 0;
	else
	if (static_cast<unsigned int>(si) >= numSegments0)
	    si = numSegments0 - 1;
	return static_cast<unsigned int>(si);
}

void BezierSpline::getPoints(Ionflux::Mapping::PointSet& target, 
Ionflux::Mapping::MappingValue x0, Ionflux::Mapping::MappingValue x1, 
unsigned int numPoints, Ionflux::Mapping::CoordinateID coord, 
Ionflux::Mapping::MappingValue precision)
{
	Ionflux::Mapping::MappingValue dx = (x1 - x0) / (numPoints - 1);
	for (unsigned int i = 0; i < numPoints; i++)
	{
	    Ionflux::Mapping::MappingValue xc = x0 + i * dx;
	    Ionflux::Mapping::Point* p0 = 
	        evalCoord(xc, coord, precision).copy();
	    target.addPoint(p0);
	}
}

void BezierSpline::initFromSVG(const std::string& rawData)
{
	clearSegments();
	PointSet points;
	extractSVGControlPoints(rawData, points);
	unsigned int numPoints = points.getNumPoints();
	if (numPoints % 4 != 0)
	{
	    std::ostringstream message;
	    message << "Invalid number of points (" << numPoints << ").";
	    throw MappingError(getErrorString(message.str(), "initFromSVG"));
	}
	unsigned int numSegments = numPoints / 4;
	for (unsigned int i = 0; i < numSegments; i++)
	{
	    Point* p0 = points.getPoint(4 * i);
	    Point* p1 = points.getPoint(4 * i + 1);
	    Point* p2 = points.getPoint(4 * i + 2);
	    Point* p3 = points.getPoint(4 * i + 3);
	    BezierCurve* c0 = BezierCurve::create(*p0, *p1, *p2, *p3);
	    addSegment(c0);
	}
}

Ionflux::Mapping::Point BezierSpline::call(Ionflux::Mapping::MappingValue 
value)
{
	unsigned int numSegments0 = getNumSegments();
	unsigned int si = getSegmentIndex(value);
	Ionflux::Mapping::BezierCurve* s = getSegment(si);
	double d = 1. / numSegments0;
	return (*s)((value - d * si) / d);
}

Ionflux::Mapping::BezierSpline BezierSpline::interpolate(const 
Ionflux::Mapping::BezierSpline& other, Ionflux::Mapping::MappingValue t) 
const
{
	BezierSpline result;
	if (segments.size() != other.segments.size())
	    throw MappingError(getErrorString(
	        "Cannot interpolate splines with "
	        "different number of segments.", "interpolate"));
	/* <---- DEBUG ----- //
	std::ostringstream message;
	// <---- DEBUG ----- */
	for (unsigned int i = 0; i < segments.size(); i++)
	{
	    BezierCurve* c0 = 
	        segments[i]->interpolate(*(other.segments[i]), t).copy();
	    /* <---- DEBUG ----- //
	    message.str("");
	    message << c0->getString();
	    log(IFLogMessage(message.str(), VL_DEBUG, this, "interpolate"));
	    // <---- DEBUG ----- */
	    result.addSegment(c0);
	}
	return result;
}

Ionflux::Mapping::Mapping* 
BezierSpline::createFunc(Ionflux::Mapping::MappingValue paramScale, 
Ionflux::Mapping::MappingValue paramOffset, const Ionflux::Mapping::Point& 
outputScale, const Ionflux::Mapping::Point& outputOffset, 
Ionflux::Mapping::CoordinateID inCoord, Ionflux::Mapping::CoordinateID 
outCoord)
{
	EvalCoord* ec = EvalCoord::create();
	ec->setFunc(this);
	ec->setCoord(inCoord);
	ec->setParamScale(paramScale);
	ec->setParamOffset(paramOffset);
	ec->setScale(outputScale);
	ec->setOffset(outputOffset);
	PointCoord* pc = PointCoord::create();
	pc->setFunc(ec);
	pc->setCoord(outCoord);
	return pc;
}

std::string BezierSpline::getSVGPathData(const 
Ionflux::Mapping::CoordinateID imagePlaneNormal) const
{
	std::ostringstream result;
	unsigned int numSegments = getNumSegments();
	Point* pPrev = 0;
	for (unsigned int k = 0; k < numSegments; k++)
	{
	    BezierCurve* c0 = getSegment(k);
	    if (c0 != 0)
	    {
	        Point* p0 = Ionflux::ObjectBase::nullPointerCheck(
	            c0->getPoint(0), this, "getSVGPathData", "Point (0)");
	        if (k == 0)
	        {
	            // first segment
	            result << "M ";
	            result << p0->getSVGPathData(imagePlaneNormal) << " C";
	        } else
	        {
	            /* Check whether the last point of the previous segment 
	               is equal to the first point of this segment. */
	            if (!p0->eq(*pPrev))
	            {
	                std::ostringstream status;
	                status << "Spline is not continuous (p0 = (" 
	                    << p0->getValueString()<< "), pPrev = (" 
	                    << pPrev->getValueString() << "))";
	                throw MappingError(getErrorString(status.str(), 
	                    "getSVGPathData"));
	            }
	        }
	        result << " " << c0->getSVGPathData(imagePlaneNormal, 1);
	        pPrev = Ionflux::ObjectBase::nullPointerCheck(
	            c0->getPoint(3), this, "getSVGPathData", "Point (3)");
	    }
	}
	return result.str();
}

std::string BezierSpline::getValueString() const
{
	std::ostringstream status;
	bool e0 = true;
	for (BezierCurveVector::const_iterator i = segments.begin(); 
	    i != segments.end(); i++)
	{
	    if (!e0)
	        status << ", ";
	    else
	        e0 = false;
	    status << "[" << (*i)->getValueString() << "]";
	}
	return status.str();
}

unsigned int BezierSpline::getNumSegments() const
{
    return segments.size();
}

Ionflux::Mapping::BezierCurve* BezierSpline::getSegment(unsigned int 
elementIndex) const
{
    if (elementIndex < segments.size())
		return segments[elementIndex];
	return 0;
}

int BezierSpline::findSegment(Ionflux::Mapping::BezierCurve* needle, 
unsigned int occurence) const
{
    bool found = false;
	Ionflux::Mapping::BezierCurve* currentSegment = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < segments.size()))
	{
		currentSegment = segments[i];
		if (currentSegment == needle)
        {
            if (occurence == 1)
			    found = true;
            else
                occurence--;
		} else
			i++;
	}
	if (found)
        return i;
	return -1;
}

std::vector<Ionflux::Mapping::BezierCurve*>& BezierSpline::getSegments()
{
    return segments;
}

void BezierSpline::addSegment(Ionflux::Mapping::BezierCurve* addElement)
{
	addLocalRef(addElement);
	segments.push_back(addElement);
}

Ionflux::Mapping::BezierCurve* BezierSpline::addSegment()
{
	Ionflux::Mapping::BezierCurve* o0 = BezierCurve::create();
	addSegment(o0);
	return o0;
}

void BezierSpline::addSegments(const 
std::vector<Ionflux::Mapping::BezierCurve*>& newSegments)
{
	for (std::vector<Ionflux::Mapping::BezierCurve*>::const_iterator i = newSegments.begin(); 
	    i != newSegments.end(); i++)
	    addSegment(*i);
}

void BezierSpline::addSegments(Ionflux::Mapping::BezierSpline* newSegments)
{
	for (unsigned int i = 0; 
	    i < newSegments->getNumSegments(); i++)
	    addSegment(newSegments->getSegment(i));
}

void BezierSpline::removeSegment(Ionflux::Mapping::BezierCurve* 
removeElement)
{
    bool found = false;
	Ionflux::Mapping::BezierCurve* currentSegment = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < segments.size()))
	{
		currentSegment = segments[i];
		if (currentSegment == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		segments.erase(segments.begin() + i);
		if (currentSegment != 0)
			removeLocalRef(currentSegment);
	}
}

void BezierSpline::removeSegmentIndex(unsigned int removeIndex)
{
    if (removeIndex > segments.size())
        return;
	Ionflux::Mapping::BezierCurve* e0 = segments[removeIndex];
    segments.erase(segments.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void BezierSpline::clearSegments()
{
    std::vector<Ionflux::Mapping::BezierCurve*>::iterator i;
	for (i = segments.begin(); i != segments.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	segments.clear();
}

Ionflux::Mapping::BezierSpline& BezierSpline::operator=(const 
Ionflux::Mapping::BezierSpline& other)
{
    BezierCurveVector v0;
    for (BezierCurveVector::const_iterator i = other.segments.begin(); 
        i != other.segments.end(); i++)
    {
        BezierCurve* c0 = *i;
        if (c0 != 0)
            v0.push_back(c0->copy());
        else
            v0.push_back(0);
    }
    /* <---- DEBUG ----- //
    std::ostringstream message;
    message << "Segments: " << other.getNumSegments();
    log(IFLogMessage(message.str(), VL_DEBUG, this, "operator="));
    // <---- DEBUG ----- */
    clearSegments();
    addSegments(v0);
	return *this;
}

Ionflux::Mapping::BezierSpline* BezierSpline::copy() const
{
    BezierSpline* newBezierSpline = create();
    *newBezierSpline = *this;
    return newBezierSpline;
}

Ionflux::Mapping::BezierSpline* 
BezierSpline::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<BezierSpline*>(other);
}

Ionflux::Mapping::BezierSpline* 
BezierSpline::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    BezierSpline* newObject = new BezierSpline();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int BezierSpline::getMemSize() const
{
    return sizeof *this;
}

std::string BezierSpline::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string BezierSpline::getXMLAttributeData() const
{
	std::ostringstream d0;
	return d0.str();
}

void BezierSpline::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string iws0 = Ionflux::ObjectBase::getIndent(indentLevel);
	bool haveBCData = false;
	bool xcFirst = true;
	if (!xcFirst || haveBCData)
	    d0 << "\n";
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0(segments, "bezcurvevec", "", 
        indentLevel, "pname=\"segments\"");
    xcFirst = false;
	target = d0.str();
}

void BezierSpline::loadFromXMLFile(const std::string& fileName)
{
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, getXMLElementName());
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
BezierSpline::getXMLObjectFactory()
{
	static Ionflux::Mapping::XMLUtils::BezierSplineXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::Mapping::XMLUtils::BezierSplineXMLFactory::create();
        fac0->addRef();
    }
    return fac0;
}

}

}

/** \file BezierSpline.cpp
 * \brief Cubic Bezier spline implementation.
 */
