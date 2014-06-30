/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polygon3Set.cpp                 Polygon set (3D) (implementation).
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

#include "geoutils/Polygon3Set.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "ifobject/objectutils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Polygon3.hpp"
#include "geoutils/transformutils.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/Polygon3SetXMLFactory.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

Polygon3SetClassInfo::Polygon3SetClassInfo()
{
	name = "Polygon3Set";
	desc = "Polygon set (3D)";
}

Polygon3SetClassInfo::~Polygon3SetClassInfo()
{
}

// public member constants
const Ionflux::GeoUtils::Polygon3CompareAxis Polygon3Set::COMPARE_AXIS_X = Ionflux::GeoUtils::Polygon3CompareAxis(Ionflux::GeoUtils::AXIS_X);
const Ionflux::GeoUtils::Polygon3CompareAxis Polygon3Set::COMPARE_AXIS_Y = Ionflux::GeoUtils::Polygon3CompareAxis(Ionflux::GeoUtils::AXIS_Y);
const Ionflux::GeoUtils::Polygon3CompareAxis Polygon3Set::COMPARE_AXIS_Z = Ionflux::GeoUtils::Polygon3CompareAxis(Ionflux::GeoUtils::AXIS_Z);

// run-time type information instance constants
const Polygon3SetClassInfo Polygon3Set::polygon3SetClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Polygon3Set::CLASS_INFO = &Polygon3Set::polygon3SetClassInfo;

const std::string Polygon3Set::XML_ELEMENT_NAME = "poly3set";

Polygon3Set::Polygon3Set()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Polygon3Set::Polygon3Set(const Ionflux::GeoUtils::Polygon3Set& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Polygon3Set::Polygon3Set(Ionflux::GeoUtils::Polygon3Vector& initPolygons)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addPolygons(initPolygons);
}

Polygon3Set::~Polygon3Set()
{
	clearPolygons();
	// TODO: Nothing ATM. ;-)
}

void Polygon3Set::recalculateBounds()
{
	TransformableObject::recalculateBounds();
	const Polygon3Set* ps0 = this;
	Polygon3Set* ps1 = 0;
	if (useTransform() || useVI())
	{
	    // Adjust for transformation.
	    Polygon3Set* ps1 = copy();
	    addLocalRef(ps1);
	    ps1->applyTransform();
	    ps0 = ps1;
	}
	Ionflux::GeoUtils::Polygon3Vector::const_iterator i;
	bool e0 = true;
	for (i = ps0->polys.begin(); i < ps0->polys.end(); i++)
	{
	    Range3 r0((*i)->getBounds());
	    if (e0)
	    {
	        boundsCache->setBounds(r0);
	        e0 = false;
	    } else
	        boundsCache->extend(r0);
	}
	if (ps1 != 0)
	    removeLocalRef(ps1);
}

Ionflux::GeoUtils::Vector3 Polygon3Set::getBarycenter()
{
	Vector3 vSum;
	Ionflux::GeoUtils::Polygon3Vector::const_iterator i;
	for (i = polys.begin(); i < polys.end(); i++)
	    vSum = vSum + (*i)->getBarycenter();
	vSum = vSum / polys.size();
	// Adjust for transformation.
	Vertex3 v0(vSum);
	if (useTransform())
	    v0.transform(*getTransformMatrix());
	if (useVI())
	    v0.transformVI(*getViewMatrix(), getImageMatrix());
	return v0.getVector();
}

void Polygon3Set::applyTransform(bool recursive)
{
	Ionflux::GeoUtils::applyTransform(*this, polys, 
	    recursive, "Polygon");
}

std::string Polygon3Set::getSVG(const std::string& attrs, const 
std::string& elementIDPrefix, Ionflux::GeoUtils::AxisID axis, 
Ionflux::GeoUtils::SVGShapeType shapeType, bool closePath)
{
	ostringstream svg;
	ostringstream eid;
	unsigned int k = 0;
	applyTransform();
	for (Polygon3Vector::const_iterator i = polys.begin(); 
	    i != polys.end(); i++)
	{
	    Polygon3* p0 = *i;
	    eid.str("");
	    eid << elementIDPrefix << right << setfill('0') << setw(8) << k;
	    if (k > 0)
	        svg << "\n";
	    svg << p0->getSVG(attrs, eid.str(), axis, shapeType, closePath);
	    k++;
	}
	return svg.str();
}

std::string Polygon3Set::getSVG(const 
Ionflux::GeoUtils::SVGShapeStyleVector& styles, const std::string& 
elementIDPrefix, Ionflux::GeoUtils::AxisID axis, 
Ionflux::GeoUtils::SVGShapeType shapeType, bool closePath)
{
	Ionflux::ObjectBase::StringVector attrs;
	    for (SVGShapeStyleVector::const_iterator j = styles.begin(); 
	        j != styles.end(); j++)
	    attrs.push_back(getSVGPolygonStyle(*(*j)));
	if (attrs.size() == 0)
	    attrs.push_back(SVG_DEFAULT_POLY_STYLE);
	ostringstream svg;
	ostringstream eid;
	unsigned int k = 0;
	unsigned int numAttrs = attrs.size();
	applyTransform();
	for (Polygon3Vector::const_iterator i = polys.begin(); 
	    i != polys.end(); i++)
	{
	    Polygon3* p0 = *i;
	    eid.str("");
	    eid << elementIDPrefix << right << setfill('0') << setw(8) << k;
	    if (k > 0)
	        svg << "\n";
	    std::string a0 = attrs[k % numAttrs];
	    svg << p0->getSVG(a0, eid.str(), axis, shapeType, closePath);
	    k++;
	}
	return svg.str();
}

std::string Polygon3Set::getSVG(Ionflux::GeoUtils::SVGImageProperties& 
imageProperties, const std::string& elementIDPrefix, 
Ionflux::GeoUtils::AxisID axis)
{
	ostringstream svg;
	ostringstream eid;
	unsigned int k = 0;
	applyTransform();
	SVGShapeStyleSource* src0 = imageProperties.getStyleSource();
	for (Polygon3Vector::const_iterator i = polys.begin(); 
	    i != polys.end(); i++)
	{
	    Polygon3* p0 = *i;
	    eid.str("");
	    eid << elementIDPrefix << right << setfill('0') << setw(8) << k;
	    SVGShapeStyle* s0 = src0->getStyle(eid.str());
	    if (k > 0)
	        svg << "\n";
	    svg << p0->getSVG(*s0, eid.str(), axis, s0->shapeType, s0->closePath);
	    k++;
	}
	return svg.str();
}

void Polygon3Set::writeSVG(const std::string& fileName, const std::string& 
attrs, const std::string& elementIDPrefix, Ionflux::GeoUtils::AxisID axis, 
Ionflux::GeoUtils::SVGShapeType shapeType, bool closePath)
{
	ofstream f0;
	f0.open(fileName.c_str(), ios_base::out);
	f0 << SVG_DEFAULT_HEADER << getSVG(attrs, elementIDPrefix, 
	    axis, shapeType, closePath) << SVG_DEFAULT_FOOTER;
}

void Polygon3Set::writeSVG(const std::string& fileName, const 
Ionflux::GeoUtils::SVGShapeStyleVector& styles, const std::string& 
elementIDPrefix, Ionflux::GeoUtils::AxisID axis, 
Ionflux::GeoUtils::SVGShapeType shapeType, bool closePath)
{
	std::ofstream f0;
	f0.open(fileName.c_str(), ios_base::out);
	f0 << SVG_DEFAULT_HEADER << getSVG(styles, elementIDPrefix, axis, 
	    shapeType, closePath) << SVG_DEFAULT_FOOTER;
}

void Polygon3Set::writeSVG(Ionflux::GeoUtils::SVGImageProperties& 
imageProperties, const std::string& elementIDPrefix, 
Ionflux::GeoUtils::AxisID axis)
{
	std::ofstream f0;
	f0.open(imageProperties.getFileName().c_str(), ios_base::out);
	Vector2 o0 = imageProperties.getOrigin();
	std::string d0 = getSVG(imageProperties, elementIDPrefix, axis);
	f0 << getSVGImage(d0, imageProperties.getWidth(), 
	    imageProperties.getHeight(), static_cast<int>(o0.getX0()), 
	    static_cast<int>(o0.getX1()));
}

Ionflux::GeoUtils::Polygon3Set& Polygon3Set::scale(const 
Ionflux::GeoUtils::Vector3& s)
{
	TransformableObject::scale(s);
	return *this;
}

Ionflux::GeoUtils::Polygon3Set& Polygon3Set::translate(const 
Ionflux::GeoUtils::Vector3& t)
{
	TransformableObject::translate(t);
	return *this;
}

Ionflux::GeoUtils::Polygon3Set& Polygon3Set::rotate(double phi, 
Ionflux::GeoUtils::AxisID axis)
{
	TransformableObject::rotate(phi, axis);
	return *this;
}

Ionflux::GeoUtils::Polygon3Set& Polygon3Set::normalize()
{
	TransformableObject::normalize();
	return *this;
}

Ionflux::GeoUtils::Polygon3Set& 
Polygon3Set::center(Ionflux::GeoUtils::CenteringMethod method, 
Ionflux::GeoUtils::Vector3* origin)
{
	TransformableObject::center(method, origin);
	return *this;
}

Ionflux::GeoUtils::Polygon3Set& Polygon3Set::transform(const 
Ionflux::GeoUtils::Matrix3& matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Polygon3Set& Polygon3Set::transform(const 
Ionflux::GeoUtils::Matrix4& matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Polygon3Set& Polygon3Set::transformVI(const 
Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4* image)
{
	TransformableObject::transformVI(view, image);
	return *this;
}

Ionflux::GeoUtils::Polygon3Set& Polygon3Set::duplicate()
{
	// TODO: Implementation.
	return *copy();
}

void Polygon3Set::sort(Ionflux::GeoUtils::Polygon3Compare* compFunc)
{
	Polygon3Compare wrap0;
	if (compFunc == 0)
	    wrap0.setTarget(Polygon3CompareAxis::create(AXIS_Z));
	else
	    wrap0.setTarget(compFunc);
	::sort(polys.begin(), polys.end(), wrap0);
}

std::string Polygon3Set::getValueString() const
{
	std::ostringstream status;
	bool e0 = true;
	for (Polygon3Vector::const_iterator i = polys.begin(); 
	    i != polys.end(); i++)
	{
	    if (!e0)
	        status << ", ";
	    else
	        e0 = false;
	    status << "[" << (*i)->getValueString() << "]";
	}
	// transformable object data
	std::string ts0(TransformableObject::getValueString());
	if (ts0.size() > 0)
	    status << "; " << ts0;
	return status.str();
}

unsigned int Polygon3Set::getNumPolygons() const
{
    return polys.size();
}

Ionflux::GeoUtils::Polygon3* Polygon3Set::getPolygon(unsigned int 
elementIndex) const
{
    if (elementIndex < polys.size())
		return polys[elementIndex];
	return 0;
}

int Polygon3Set::findPolygon(Ionflux::GeoUtils::Polygon3* needle, unsigned 
int occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::Polygon3* currentPolygon = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < polys.size()))
	{
		currentPolygon = polys[i];
		if (currentPolygon == needle)
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

std::vector<Ionflux::GeoUtils::Polygon3*>& Polygon3Set::getPolygons()
{
    return polys;
}

void Polygon3Set::addPolygon(Ionflux::GeoUtils::Polygon3* addElement)
{
	addLocalRef(addElement);
	polys.push_back(addElement);
}

Ionflux::GeoUtils::Polygon3* Polygon3Set::addPolygon()
{
	Ionflux::GeoUtils::Polygon3* o0 = Polygon3::create();
	addPolygon(o0);
	return o0;
}

void Polygon3Set::addPolygons(const 
std::vector<Ionflux::GeoUtils::Polygon3*>& newPolygons)
{
	for (std::vector<Ionflux::GeoUtils::Polygon3*>::const_iterator i = newPolygons.begin(); 
	    i != newPolygons.end(); i++)
	    addPolygon(*i);
}

void Polygon3Set::addPolygons(Ionflux::GeoUtils::Polygon3Set* newPolygons)
{
	for (unsigned int i = 0; 
	    i < newPolygons->getNumPolygons(); i++)
	    addPolygon(newPolygons->getPolygon(i));
}

void Polygon3Set::removePolygon(Ionflux::GeoUtils::Polygon3* removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::Polygon3* currentPolygon = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < polys.size()))
	{
		currentPolygon = polys[i];
		if (currentPolygon == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		polys.erase(polys.begin() + i);
		if (currentPolygon != 0)
			removeLocalRef(currentPolygon);
	}
}

void Polygon3Set::removePolygonIndex(unsigned int removeIndex)
{
    if (removeIndex > polys.size())
        return;
	Ionflux::GeoUtils::Polygon3* e0 = polys[removeIndex];
    polys.erase(polys.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void Polygon3Set::clearPolygons()
{
    std::vector<Ionflux::GeoUtils::Polygon3*>::iterator i;
	for (i = polys.begin(); i != polys.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	polys.clear();
}

Ionflux::GeoUtils::Polygon3Set& Polygon3Set::operator=(const 
Ionflux::GeoUtils::Polygon3Set& other)
{
    if (this == &other)
        return *this;
    TransformableObject::operator=(other);
    Polygon3Vector pv0;
    for (Polygon3Vector::const_iterator i = other.polys.begin(); 
        i != other.polys.end(); i++)
    {
        Polygon3* pt0 = Ionflux::ObjectBase::nullPointerCheck(*i, this, 
            "operator=", "Polygon");
        pv0.push_back(pt0->copy());
    }
    clearPolygons();
    addPolygons(pv0);
	return *this;
}

Ionflux::GeoUtils::Polygon3Set* Polygon3Set::copy() const
{
    Polygon3Set* newPolygon3Set = create();
    *newPolygon3Set = *this;
    return newPolygon3Set;
}

Ionflux::GeoUtils::Polygon3Set* 
Polygon3Set::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Polygon3Set*>(other);
}

Ionflux::GeoUtils::Polygon3Set* 
Polygon3Set::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Polygon3Set* newObject = new Polygon3Set();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Polygon3Set* 
Polygon3Set::create(Ionflux::GeoUtils::Polygon3Vector& initPolygons, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Polygon3Set* newObject = new Polygon3Set(initPolygons);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Polygon3Set::getMemSize() const
{
    return sizeof *this;
}

std::string Polygon3Set::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Polygon3Set::getXMLAttributeData() const
{
	std::ostringstream d0;
	return d0.str();
}

void Polygon3Set::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string iws0 = Ionflux::ObjectBase::getIndent(indentLevel);
	bool haveBCData = false;
	bool xcFirst = true;
	if (!xcFirst || haveBCData)
	    d0 << "\n";
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0(polys, "poly3vec", "", 
        indentLevel, "pname=\"polygons\"");
    xcFirst = false;
	target = d0.str();
}

void Polygon3Set::loadFromXMLFile(const std::string& fileName)
{
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, getXMLElementName());
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
Polygon3Set::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::Polygon3SetXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::Polygon3SetXMLFactory::create();
        fac0->addRef();
    }
    return fac0;
}

}

}

/** \file Polygon3Set.cpp
 * \brief Polygon set (3D) implementation.
 */
