/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Segment.cpp                     Segment (implementation).
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

#include "ifmapping/Segment.hpp"
#include <sstream>
#include <cmath>
#include "ifobject/objectutils.hpp"
#include "ifmapping/utils.hpp"
#include "ifmapping/MappingError.hpp"
#include "ifmapping/PointSample.hpp"
#include "ifobject/IFMMEvent.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "ifmapping/xmlutils.hpp"
#include "ifmapping/xmlio/SegmentXMLFactory.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

SegmentClassInfo::SegmentClassInfo()
{
	name = "Segment";
	desc = "Segment";
	baseClassInfo.push_back(Ionflux::Mapping::PointMapping::CLASS_INFO);
}

SegmentClassInfo::~SegmentClassInfo()
{
}

// public member constants
const Ionflux::Mapping::MappingValue Segment::DEFAULT_ERROR_THRESHOLD = 1e-4;

// run-time type information instance constants
const SegmentClassInfo Segment::segmentClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Segment::CLASS_INFO = &Segment::segmentClassInfo;

const std::string Segment::XML_ELEMENT_NAME = "ps";

Segment::Segment()
: func(0), p0(0), p1(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
    refData->mmDebug = true;
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_CREATE, this));
	// TODO: Nothing ATM. ;-)
}

Segment::Segment(const Ionflux::Mapping::Segment& other)
: func(0), p0(0), p1(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	refData->mmDebug = true;
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_CREATE, this));
	*this = other;
}

Segment::Segment(Ionflux::Mapping::PointMapping* initFunc, 
Ionflux::Mapping::MappingValue t0, Ionflux::Mapping::MappingValue t1)
: func(0), p0(0), p1(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	refData->mmDebug = true;
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_CREATE, this));
	if (initFunc != 0)
	{
	    setFunc(initFunc);
	    setP0(initFunc->getSample(t0, false));
	    setP1(initFunc->getSample(t1, false));
	}
}

Segment::Segment(Ionflux::Mapping::PointMapping* initFunc, 
Ionflux::Mapping::PointSample* initP0, Ionflux::Mapping::PointSample* 
initP1)
: func(0), p0(0), p1(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	refData->mmDebug = true;
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_CREATE, this));
	if (initFunc != 0)
	    setFunc(initFunc);
	if (initP0 != 0)
	    setP0(initP0);
	if (initP1 != 0)
	    setP1(initP1);
}

Segment::~Segment()
{
	clearSegments();
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_DELETE, this));
	// TODO: Nothing ATM. ;-)
}

Ionflux::Mapping::MappingValue Segment::getLength(bool recursive, unsigned 
int maxDepth, unsigned int depth) const
{
	Ionflux::ObjectBase::nullPointerCheck(p0, this, "getLength", 
	    "Point sample (0)");
	Ionflux::ObjectBase::nullPointerCheck(p1, this, "getLength", 
	    "Point sample (1)");
	MappingValue result = 0.;
	unsigned int numSegments0 = getNumSegments();
	if (!recursive 
	    || (numSegments0 < 2))
	{
	    Point* pp0 = p0->getCoords();
	    Point* pp1 = p1->getCoords();
	    result = pp0->distance(*pp1);
	} else
	{
	    for (unsigned int i = 0; i < numSegments0; i++)
	    {
	        Segment* s0 = getSegment(i);
	        if (s0 != 0)
	        {
	            if ((maxDepth == 0) 
	                || ((depth + 1) < maxDepth))
	            {
	                result += s0->getLength(recursive, 
	                    maxDepth, depth + 1);
	            } else
	                result += s0->getLength(false);
	        }
	    }
	}
	return result;
}

Ionflux::Mapping::MappingValue Segment::getLengthError(bool relativeError, 
unsigned int maxDepth, double t) const
{
	MappingValue l0 = getLength(false);
	if (eq(l0, 0., t))
	    throw MappingError(getErrorString(
	        "Segment has zero length.", "getLengthError"));
	if (maxDepth < 1)
	    throw MappingError(getErrorString(
	        "Maximum depth must be at least 1.", "getLengthError"));
	MappingValue l1 = getLength(true, maxDepth);
	if (eq(l0, l1, t))
	    return 0.;
	MappingValue result = 0.;
	if (relativeError)
	    result = ::fabs(l1 / l0 - 1.);
	else
	    result = ::fabs(l1 - l0);
	return result;
}

void Segment::split(unsigned int numSplits, bool recursive, bool 
relativeError, Ionflux::Mapping::MappingValue errorThreshold, unsigned int 
maxDepth, unsigned int depth, double t)
{
	if (numSplits < 2)
	{
	    std::ostringstream status;
	    status << "Number of splits must be at least two "
	        "(numSplits = " << numSplits << ").";
	    throw MappingError(getErrorString(status.str(), "split"));
	}
	if ((maxDepth != 0) 
	    && (depth >= maxDepth))
	    return;
	Ionflux::ObjectBase::nullPointerCheck(func, this, "split", 
	    "Point mapping");
	Ionflux::ObjectBase::nullPointerCheck(p0, this, "split", 
	    "Point sample (0)");
	Ionflux::ObjectBase::nullPointerCheck(p1, this, "split", 
	    "Point sample (1)");
	MappingValue t0 = p0->getParam();
	MappingValue t1 = p1->getParam();
	if (eq(t1, t0, t))
	{
	    std::ostringstream status;
	    status << "Start and end parameters are equal (t0 = " 
	        << t0 << ", t1 = " << t1 << ").";
	    throw MappingError(getErrorString(status.str(), "split"));
	}
	MappingValue dt = (t1 - t0) / numSplits;
	MappingValue l0 = p0->getArcLength();
	/* Resample the mapping at the split points and create 
	   new segments. */
	for (unsigned int i = 0; i < numSplits; i++)
	{
	    PointSample* nps0 = func->getSample(
	        static_cast<MappingValue>(i) * dt, false);
	    PointSample* nps1 = func->getSample(
	        static_cast<MappingValue>(i + 1) * dt, false);
	    Point* np0 = nps0->getCoords();
	    Point* np1 = nps1->getCoords();
	    nps0->setArcLength(l0);
	    MappingValue dl0 = np0->distance(*np1);
	    nps1->setArcLength(l0 + dl0);
	    l0 += dl0;
	    Segment* s0 = Segment::create(func, nps0, nps1);
	    addSegment(s0);
	}
	if (recursive)
	{
	    // Split segments recursively if error is above threshold.
	    MappingValue e0 = getLengthError(relativeError, 1, t);
	    if (e0 > errorThreshold)
	    {
	        for (SegmentVector::iterator i = segments.begin(); 
	            i != segments.end(); i++)
	        {
	            Segment* s0 = *i;
	            if (s0 != 0)
	            {
	                s0->split(numSplits, recursive, relativeError, 
	                    errorThreshold, maxDepth, depth + 1, t);
	            }
	        }
	    }
	}
}

Ionflux::Mapping::Segment* 
Segment::findSegment(Ionflux::Mapping::MappingValue value, 
Ionflux::Mapping::SamplingMode samplingMode, double t)
{
	unsigned int numSegments0 = getNumSegments();
	if (numSegments0 == 0)
	    return 0;
	if (ltOrEq(value, 0., t))
	    return getSegment(0);
	if (gtOrEq(value, 1., t))
	    return getSegment(numSegments0 - 1);
	Segment* result = 0;
	unsigned int k = 0;
	Segment* s0 = 0;
	bool found = false;
	// Find the relevant child segment.
	while ((k < numSegments0) 
	    && !found)
	{
	    s0 = getSegment(k);
	    if (s0 != 0)
	    {
	        PointSample* ps0 = s0->getP0();
	        PointSample* ps1 = s0->getP1();
	        MappingValue v0 = ps0->getValue(samplingMode);
	        MappingValue v1 = ps1->getValue(samplingMode);
	        if (gtOrEq(value, v0, t)
	            && ltOrEq(value, v1, t))
	            found = true;
	        else
	            k++;
	    }
	}
	if (s0 != 0)
	    result = s0;
	else
	{
	    std::ostringstream status;
	    status << "Could not find suitable non-null child "
	        "segment (value = " << value << ", samplingMode = " 
	        << getSamplingModeString(samplingMode) << " (" 
	        << samplingMode << ")).";
	    throw MappingError(getErrorString(status.str(), 
	        "findSegment"));
	}
	return result;
}

Ionflux::Mapping::PointSample* 
Segment::getSample0(Ionflux::Mapping::MappingValue value, 
Ionflux::Mapping::SamplingMode samplingMode, bool recursive, unsigned int 
maxDepth, unsigned int depth, double t)
{
	unsigned int numSegments0 = getNumSegments();
	PointSample* result = 0;
	if (recursive
	    && ((maxDepth == 0)
	        || (depth < maxDepth))
	    && (numSegments0 >= 2))
	{
	    // Sample child segments recursively.
	    Segment* s0 = findSegment(value, samplingMode, t);
	    result = s0->getSample0(value, samplingMode, recursive, 
	        maxDepth, depth + 1, t);
	    return result;
	}
	// Sample this segment.
	Ionflux::ObjectBase::nullPointerCheck(p0, this, "getSample", 
	    "Point sample (0)");
	Ionflux::ObjectBase::nullPointerCheck(p1, this, "getSample", 
	    "Point sample (1)");
	Point* pp0 = p0->getCoords();
	Point* pp1 = p1->getCoords();
	MappingValue t0 = p0->getParam();
	MappingValue t1 = p1->getParam();
	MappingValue l0 = p0->getArcLength();
	MappingValue l1 = p1->getArcLength();
	MappingValue sv0 = p0->getValue(samplingMode);
	MappingValue sv1 = p1->getValue(samplingMode);
	MappingValue it0 = (value - sv0) / (sv1 - sv0);
	Point* np0 = Point::create();
	*np0 = pp0->interpolate(*pp1, it0);
	result = PointSample::create(t0 + it0 * (t1 - t0), np0, 
	    l0 + it0 * (l1 - l0));
	return result;
}

std::string Segment::getValueString() const
{
	std::ostringstream status;
	if (p0 != 0)
	    status << "[" << p0->getValueString() << "]";
	else
	    status << "<none>";
	status << ", ";
	if (p1 != 0)
	    status << "[" << p1->getValueString() << "]";
	else
	    status << "<none>";
	status << "; [";
	bool e0 = true;
	for (SegmentVector::const_iterator i = segments.begin(); 
	    i != segments.end(); i++)
	{
	    if (!e0)
	        status << ", ";
	    else
	        e0 = false;
	    status << "[" << (*i)->getValueString() << "]";
	}
	if (segments.size() == 0)
	    status << "<none>";
	status << "]";
	return status.str();
}

Ionflux::Mapping::MappingValue 
Segment::getParamCoord(Ionflux::Mapping::MappingValue value, 
Ionflux::Mapping::CoordinateID coord, Ionflux::Mapping::MappingValue 
precision)
{
	SamplingMode m0 = SAMPLING_MODE_POINT_COORD_X;
	if (coord == C_Y)
	    m0 = SAMPLING_MODE_POINT_COORD_Y;
	else
	if (coord == C_Z)
	    m0 = SAMPLING_MODE_POINT_COORD_Z;
	PointSample* ps0 = getSample0(value, m0, true);
	addLocalRef(ps0);
	MappingValue result = ps0->getParam();
	removeLocalRef(ps0);
	return result;
}

Ionflux::Mapping::MappingValue 
Segment::getParamArcLength(Ionflux::Mapping::MappingValue value, 
Ionflux::Mapping::MappingValue relativeError, unsigned int 
maxNumIterations, Ionflux::Mapping::MappingValue precision)
{
	if (value == 0.)
	    return 0.;
	PointSample* ps0 = getSample0(value, 
	    SAMPLING_MODE_ARC_LENGTH, true);
	addLocalRef(ps0);
	MappingValue result = ps0->getArcLength();
	removeLocalRef(ps0);
	return result;
}

Ionflux::Mapping::PointSample* 
Segment::getSample(Ionflux::Mapping::MappingValue value, bool 
calculateArcLength, Ionflux::Mapping::MappingValue relativeError, unsigned 
int maxNumIterations)
{
	PointSample* result = getSample0(value, SAMPLING_MODE_PARAM, true);
	if (!calculateArcLength)
	    result->setArcLength(0);
	return result;
}

Ionflux::Mapping::Point Segment::call(Ionflux::Mapping::MappingValue value)
{
	PointSample* ps0 = getSample0(value, SAMPLING_MODE_PARAM, true);
	addLocalRef(ps0);
	Point* pps0 = ps0->getCoords();
	Point result(*pps0);
	removeLocalRef(ps0);
	return result;
}

void Segment::setFunc(Ionflux::Mapping::PointMapping* newFunc)
{
	if (func == newFunc)
		return;
    if (newFunc != 0)
        addLocalRef(newFunc);
	if (func != 0)
		removeLocalRef(func);
	func = newFunc;
}

Ionflux::Mapping::PointMapping* Segment::getFunc() const
{
    return func;
}

void Segment::setP0(Ionflux::Mapping::PointSample* newP0)
{
	if (p0 == newP0)
		return;
    if (newP0 != 0)
        addLocalRef(newP0);
	if (p0 != 0)
		removeLocalRef(p0);
	p0 = newP0;
}

Ionflux::Mapping::PointSample* Segment::getP0() const
{
    return p0;
}

void Segment::setP1(Ionflux::Mapping::PointSample* newP1)
{
	if (p1 == newP1)
		return;
    if (newP1 != 0)
        addLocalRef(newP1);
	if (p1 != 0)
		removeLocalRef(p1);
	p1 = newP1;
}

Ionflux::Mapping::PointSample* Segment::getP1() const
{
    return p1;
}

unsigned int Segment::getNumSegments() const
{
    return segments.size();
}

Ionflux::Mapping::Segment* Segment::getSegment(unsigned int elementIndex) 
const
{
    if (elementIndex < segments.size())
		return segments[elementIndex];
	return 0;
}

int Segment::findSegment(Ionflux::Mapping::Segment* needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::Mapping::Segment* currentSegment = 0;
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

std::vector<Ionflux::Mapping::Segment*>& Segment::getSegments()
{
    return segments;
}

void Segment::addSegment(Ionflux::Mapping::Segment* addElement)
{
	addLocalRef(addElement);
	segments.push_back(addElement);
}

Ionflux::Mapping::Segment* Segment::addSegment()
{
	Ionflux::Mapping::Segment* o0 = Segment::create();
	addSegment(o0);
	return o0;
}

void Segment::addSegments(const std::vector<Ionflux::Mapping::Segment*>& 
newSegments)
{
	for (std::vector<Ionflux::Mapping::Segment*>::const_iterator i = newSegments.begin(); 
	    i != newSegments.end(); i++)
	    addSegment(*i);
}

void Segment::addSegments(Ionflux::Mapping::Segment* newSegments)
{
	for (unsigned int i = 0; 
	    i < newSegments->getNumSegments(); i++)
	    addSegment(newSegments->getSegment(i));
}

void Segment::removeSegment(Ionflux::Mapping::Segment* removeElement)
{
    bool found = false;
	Ionflux::Mapping::Segment* currentSegment = 0;
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

void Segment::removeSegmentIndex(unsigned int removeIndex)
{
    if (removeIndex > segments.size())
        return;
	Ionflux::Mapping::Segment* e0 = segments[removeIndex];
    segments.erase(segments.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void Segment::clearSegments()
{
    std::vector<Ionflux::Mapping::Segment*>::iterator i;
	for (i = segments.begin(); i != segments.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	segments.clear();
}

Ionflux::Mapping::Segment& Segment::operator=(const 
Ionflux::Mapping::Segment& other)
{
    if (this == &other)
        return *this;
    if (other.p0 != 0)
        setP0(other.p0->copy());
    else
        setP0(0);
    if (other.p1 != 0)
        setP1(other.p1->copy());
    else
        setP1(0);
	return *this;
}

Ionflux::Mapping::Segment* Segment::copy() const
{
    Segment* newSegment = create();
    *newSegment = *this;
    return newSegment;
}

Ionflux::Mapping::Segment* Segment::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Segment*>(other);
}

Ionflux::Mapping::Segment* Segment::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Segment* newObject = new Segment();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Mapping::Segment* Segment::create(Ionflux::Mapping::PointMapping* 
initFunc, Ionflux::Mapping::MappingValue t0, Ionflux::Mapping::MappingValue
t1, Ionflux::ObjectBase::IFObject* parentObject)
{
    Segment* newObject = new Segment(initFunc, t0, t1);
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Mapping::Segment* Segment::create(Ionflux::Mapping::PointMapping* 
initFunc, Ionflux::Mapping::PointSample* initP0, 
Ionflux::Mapping::PointSample* initP1, Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Segment* newObject = new Segment(initFunc, initP0, initP1);
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

std::string Segment::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Segment::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::Mapping::PointMapping::getXMLAttributeData();
	return d0.str();
}

void Segment::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::Mapping::PointMapping::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	std::string iws0 = Ionflux::ObjectBase::getIndent(indentLevel);
	bool haveBCData = false;
	if (d0.str().size() > 0)
	    haveBCData = true;
	bool xcFirst = true;
    if (p0 != 0)
    {
        if (!xcFirst || haveBCData)
            d0 << "\n";
	    d0 << p0->getXML0(indentLevel, "pname=\"p0\"");
	    xcFirst = false;
    }
    if (p1 != 0)
    {
        if (!xcFirst || haveBCData)
            d0 << "\n";
	    d0 << p1->getXML0(indentLevel, "pname=\"p1\"");
	    xcFirst = false;
    }
	if (!xcFirst || haveBCData)
	    d0 << "\n";
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0(segments, "segvec", "", 
        indentLevel, "pname=\"segments\"");
    xcFirst = false;
	target = d0.str();
}

void Segment::loadFromXMLFile(const std::string& fileName)
{
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, getXMLElementName());
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
Segment::getXMLObjectFactory()
{
	static Ionflux::Mapping::XMLUtils::SegmentXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::Mapping::XMLUtils::SegmentXMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 0;
        bFac = Ionflux::Mapping::PointMapping::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file Segment.cpp
 * \brief Segment implementation.
 */
