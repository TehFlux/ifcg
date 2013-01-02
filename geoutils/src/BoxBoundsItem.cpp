/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BoxBoundsItem.cpp               Item with box bounds (implementation).
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

#include "geoutils/BoxBoundsItem.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

BoxBoundsItemClassInfo::BoxBoundsItemClassInfo()
{
	name = "BoxBoundsItem";
	desc = "Item with box bounds";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

BoxBoundsItemClassInfo::~BoxBoundsItemClassInfo()
{
}

// run-time type information instance constants
const BoxBoundsItemClassInfo BoxBoundsItem::boxBoundsItemClassInfo;
const Ionflux::ObjectBase::IFClassInfo* BoxBoundsItem::CLASS_INFO = &BoxBoundsItem::boxBoundsItemClassInfo;

BoxBoundsItem::BoxBoundsItem()
: center(Ionflux::GeoUtils::Vector3::ZERO), rVec(Ionflux::GeoUtils::Vector3::ZERO), itemID(""), radius(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

BoxBoundsItem::BoxBoundsItem(const Ionflux::GeoUtils::BoxBoundsItem& other)
: center(Ionflux::GeoUtils::Vector3::ZERO), rVec(Ionflux::GeoUtils::Vector3::ZERO), itemID(""), radius(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

BoxBoundsItem::BoxBoundsItem(const Ionflux::GeoUtils::Vector3& initCenter, 
const Ionflux::GeoUtils::Vector3& initRVec, const std::string& initItemID)
: center(initCenter), rVec(initRVec), itemID(initItemID)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	updateBounds();
}

BoxBoundsItem::~BoxBoundsItem()
{
	clearBoxVertices();
	clearBoxFaces();
	// TODO: Nothing ATM. ;-)
}

void BoxBoundsItem::updateBounds()
{
	bounds = Range3(center);
	bounds.extend(center + rVec);
	bounds.extend(center - rVec);
	radius = rVec.norm();
	clearBoxVertices();
	clearBoxFaces();
}

void BoxBoundsItem::updateRadiusAndCenter()
{
	center = bounds.getCenter();
	rVec = bounds.getRadius();
	radius = rVec.norm();
	clearBoxVertices();
	clearBoxFaces();
}

void BoxBoundsItem::clear()
{
	center = Vector3::ZERO;
	rVec = Vector3::ZERO;
	clearBoxVertices();
	clearBoxFaces();
	updateBounds();
}

Ionflux::GeoUtils::Vertex3Vector BoxBoundsItem::getBoxVertices()
{
	if (bVerts.size() > 0)
	    return bVerts;
	Vertex3Vector tVerts;
	// Top vertices.
	tVerts.push_back(new Vertex3(rVec[0], rVec[1], rVec[2]));
	tVerts.push_back(new Vertex3(-rVec[0], rVec[1], rVec[2]));
	tVerts.push_back(new Vertex3(-rVec[0], -rVec[1], rVec[2]));
	tVerts.push_back(new Vertex3(rVec[0], -rVec[1], rVec[2]));
	// Bottom vertices.
	tVerts.push_back(new Vertex3(rVec[0], rVec[1], -rVec[2]));
	tVerts.push_back(new Vertex3(-rVec[0], rVec[1], -rVec[2]));
	tVerts.push_back(new Vertex3(-rVec[0], -rVec[1], -rVec[2]));
	tVerts.push_back(new Vertex3(rVec[0], -rVec[1], -rVec[2]));
	clearBoxVertices();
	for (Vertex3Vector::iterator i = tVerts.begin(); i < tVerts.end(); i++)
	{
	    addBoxVertex(new Vertex3(center + (*i)->getVector()));
	    delete *i;
	}
	return bVerts;
}

Ionflux::GeoUtils::Polygon3Vector BoxBoundsItem::getBoxFaces()
{
	if (bFaces.size() > 0)
	    return bFaces;
	if (bVerts.size() < 8)
	    getBoxVertices();
	Polygon3Vector tFaces;
	tFaces.push_back(new Polygon3(bVerts[0], bVerts[1], bVerts[2], 
	bVerts[3]));
	tFaces.push_back(new Polygon3(bVerts[4], bVerts[7], bVerts[6], 
	bVerts[5]));
	tFaces.push_back(new Polygon3(bVerts[0], bVerts[3], bVerts[7], 
	bVerts[4]));
	tFaces.push_back(new Polygon3(bVerts[1], bVerts[5], bVerts[6], 
	bVerts[2]));
	tFaces.push_back(new Polygon3(bVerts[2], bVerts[6], bVerts[7], 
	bVerts[3]));
	tFaces.push_back(new Polygon3(bVerts[0], bVerts[4], bVerts[5], 
	bVerts[1]));
	clearBoxFaces();
	for (Polygon3Vector::iterator i = tFaces.begin(); i < tFaces.end(); i++)
	    addBoxFace(*i);
	return bFaces;
}

int BoxBoundsItem::checkPlane(const Ionflux::GeoUtils::Plane3& plane, 
double t)
{
	double d = plane.getNormal() * (center - plane.getP());
	if (gt(d, radius, t))
	    return 1;
	if (lt(d, -radius, t))
	    return -1;
	/* The bounding box may intersect the plane, we have to check 
	   individual vertices. If all of them are above or below the plane, 
	   so is the bounding box. Otherwise, there is an intersection. */
	// Reference value.
	int c = 0;
	// Current vertex result.
	int s = 0;
	getBoxVertices();
	for (Vertex3Vector::const_iterator i = bVerts.begin(); 
	    i != bVerts.end(); i++) 
	{
	    d = plane.getNormal() * ((*i)->getVector() - plane.getP());
	    if (eq(d, 0., t))
	        // Vertex lies on plane.
	        return 0;
	    else 
	    if (gt(d, 0., t))
	        // Vertex is above the plane.
	        s = 1;
	    else 
	    if (lt(d, 0., t))
	        // Vertex is below the plane.
	        s = -1;
	    if (c == 0)
	        // First vertex initializes the reference.
	        c = s;
	    else 
	    if (c != s)
	        // Some are above, some below.
	        return 0;
	}
	return c;
}

int BoxBoundsItem::checkPlaneInner(const Ionflux::GeoUtils::Plane3& plane, 
double t)
{
	// TODO: Implementation.
	return checkPlane(plane, t);
}

int BoxBoundsItem::checkSphere(const Ionflux::GeoUtils::Sphere3& sphere, 
double t)
{
	double d = (center - sphere.getP()).norm();
	if (gt(d, radius + sphere.getR(), t))
	    return -1;
	if (lt(d + radius, sphere.getR(), t))
	    return 1;
	return 0;
}

int BoxBoundsItem::checkSphereInner(const Ionflux::GeoUtils::Sphere3& 
sphere, double t)
{
	// TODO: Implementation.
	return checkSphere(sphere, t);
}

bool BoxBoundsItem::checkLine(const Ionflux::GeoUtils::Line3& line, double 
t)
{
	Polygon3Vector faces = getBoxFaces();
	for (Polygon3Vector::iterator i = faces.begin(); i != faces.end(); i++)
	{
	    Polygon3* p0 = *i;
	    if (line.intersectionInPoly(*p0, t))
	    {
	        /* <---- DEBUG ----- //
	        std::cerr << "[BoxBoundsItem::checkLine] "
	        << "intersection: " << p0->getString() << std::endl;
	        // ----- DEBUG ----> */
	        return true;
	    }
	}
	clearBoxVertices();
	clearBoxFaces();
	return false;
}

bool BoxBoundsItem::checkLineInner(const Ionflux::GeoUtils::Line3& line, 
double t)
{
	// TODO: Implementation.
	return checkLine(line, t);
}

Ionflux::GeoUtils::RangeCompResult3 BoxBoundsItem::compare3(const 
Ionflux::GeoUtils::BoxBoundsItem& other, double t) const
{
	// TODO: Implementation.
	return bounds.compare3(other.bounds, t);
}

Ionflux::GeoUtils::RangeCompResult BoxBoundsItem::compare(const 
Ionflux::GeoUtils::BoxBoundsItem& other, double t) const
{
	// TODO: Implementation.
	return bounds.compare(other.getBounds(), t);
}

int BoxBoundsItem::checkBox(const Ionflux::GeoUtils::BoxBoundsItem& other, 
double t)
{
	RangeCompResult r = compare(other, t);
	if (r == RANGE_DISJOINT)
	    return -1;
	if (r == RANGE_OTHER_CONTAINS)
	    return 1;
	return 0;
}

int BoxBoundsItem::checkBoxInner(const Ionflux::GeoUtils::BoxBoundsItem& 
other, double t)
{
	// TODO: Implementation.
	return checkBox(other, t);
}

bool BoxBoundsItem::checkRay(const Ionflux::GeoUtils::Line3& ray, double t)
{
	/* Do a plane check first to see if the item is in the 
	   same half space as the ray. */
	// TODO: Use a ray class to avoid creating a new plane for each check.
	Plane3 p = Plane3::createFromNormal(ray.getU(), Vector3::E_X, 
	    ray.getP());
	if (checkPlane(p, t) == -1)
	    return false;
	return checkLine(ray, t);
}

bool BoxBoundsItem::checkRayInner(const Ionflux::GeoUtils::Line3& ray, 
double t)
{
	// TODO: Implementation.
	return checkRay(ray, t);
}

bool BoxBoundsItem::operator==(const Ionflux::GeoUtils::BoxBoundsItem& 
other) const
{
	if (!((center == other.center) && (rVec == other.rVec)))
	        return false;
	return true;
}

bool BoxBoundsItem::operator!=(const Ionflux::GeoUtils::BoxBoundsItem& 
other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

std::string BoxBoundsItem::getXML() const
{
	ostringstream d0;
	if (itemID.size() == 0)
	    throw GeoUtilsError("Item ID not set.");
	d0 << "<bbitem id=\"" << itemID << "\" center=\"" << center[0] << "," 
	    << center[1] << "," << center[2] << "\" rvec=\"" << rVec[0] << "," 
	    << rVec[1] << "," << rVec[2] << "\" />";
	return d0.str();
}

std::string BoxBoundsItem::getString() const
{
	ostringstream state;
	state << getClassName() << "[" << center.getString() 
	    << ", " << rVec.getString() << ", '" << itemID << "']";
	return state.str();
}

void BoxBoundsItem::setCenter(const Ionflux::GeoUtils::Vector3& newCenter)
{
	center = newCenter;
}

Ionflux::GeoUtils::Vector3 BoxBoundsItem::getCenter() const
{
	return center;
}

void BoxBoundsItem::setRVec(const Ionflux::GeoUtils::Vector3& newRVec)
{
	rVec = newRVec;
}

Ionflux::GeoUtils::Vector3 BoxBoundsItem::getRVec() const
{
	return rVec;
}

void BoxBoundsItem::setItemID(const std::string& newItemID)
{
	itemID = newItemID;
}

std::string BoxBoundsItem::getItemID() const
{
	return itemID;
}

void BoxBoundsItem::setBounds(const Ionflux::GeoUtils::Range3& newBounds)
{
	bounds = newBounds;
}

Ionflux::GeoUtils::Range3 BoxBoundsItem::getBounds() const
{
	return bounds;
}

void BoxBoundsItem::setRadius(double newRadius)
{
	radius = newRadius;
}

double BoxBoundsItem::getRadius() const
{
	return radius;
}

unsigned int BoxBoundsItem::getNumBoxVertices() const
{
    return bVerts.size();
}

Ionflux::GeoUtils::Vertex3* BoxBoundsItem::getBoxVertex(unsigned int 
elementIndex) const
{
    if (elementIndex < bVerts.size())
		return bVerts[elementIndex];
	return 0;
}

int BoxBoundsItem::findBoxVertex(Ionflux::GeoUtils::Vertex3* needle, 
unsigned int occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::Vertex3* currentBoxVertex = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < bVerts.size()))
	{
		currentBoxVertex = bVerts[i];
		if (currentBoxVertex == needle)
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

void BoxBoundsItem::addBoxVertex(Ionflux::GeoUtils::Vertex3* addElement)
{
	addLocalRef(addElement);
	bVerts.push_back(addElement);
}

void BoxBoundsItem::removeBoxVertex(Ionflux::GeoUtils::Vertex3* 
removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::Vertex3* currentBoxVertex = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < bVerts.size()))
	{
		currentBoxVertex = bVerts[i];
		if (currentBoxVertex == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		bVerts.erase(bVerts.begin() + i);
		if (currentBoxVertex != 0)
			removeLocalRef(currentBoxVertex);
	}
}

void BoxBoundsItem::removeBoxVertexIndex(unsigned int removeIndex)
{
    if (removeIndex > bVerts.size())
        return;
	Ionflux::GeoUtils::Vertex3* e0 = bVerts[removeIndex];
    bVerts.erase(bVerts.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void BoxBoundsItem::clearBoxVertices()
{
    std::vector<Ionflux::GeoUtils::Vertex3*>::iterator i;
	for (i = bVerts.begin(); i != bVerts.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	bVerts.clear();
}

unsigned int BoxBoundsItem::getNumBoxFaces() const
{
    return bFaces.size();
}

Ionflux::GeoUtils::Polygon3* BoxBoundsItem::getBoxFace(unsigned int 
elementIndex) const
{
    if (elementIndex < bFaces.size())
		return bFaces[elementIndex];
	return 0;
}

int BoxBoundsItem::findBoxFace(Ionflux::GeoUtils::Polygon3* needle, 
unsigned int occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::Polygon3* currentBoxFace = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < bFaces.size()))
	{
		currentBoxFace = bFaces[i];
		if (currentBoxFace == needle)
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

void BoxBoundsItem::addBoxFace(Ionflux::GeoUtils::Polygon3* addElement)
{
	addLocalRef(addElement);
	bFaces.push_back(addElement);
}

void BoxBoundsItem::removeBoxFace(Ionflux::GeoUtils::Polygon3* 
removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::Polygon3* currentBoxFace = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < bFaces.size()))
	{
		currentBoxFace = bFaces[i];
		if (currentBoxFace == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		bFaces.erase(bFaces.begin() + i);
		if (currentBoxFace != 0)
			removeLocalRef(currentBoxFace);
	}
}

void BoxBoundsItem::removeBoxFaceIndex(unsigned int removeIndex)
{
    if (removeIndex > bFaces.size())
        return;
	Ionflux::GeoUtils::Polygon3* e0 = bFaces[removeIndex];
    bFaces.erase(bFaces.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void BoxBoundsItem::clearBoxFaces()
{
    std::vector<Ionflux::GeoUtils::Polygon3*>::iterator i;
	for (i = bFaces.begin(); i != bFaces.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	bFaces.clear();
}

Ionflux::GeoUtils::BoxBoundsItem& BoxBoundsItem::operator=(const 
Ionflux::GeoUtils::BoxBoundsItem& other)
{
    clear();
    center = other.center;
    rVec = other.rVec;
	return *this;
}

Ionflux::GeoUtils::BoxBoundsItem* BoxBoundsItem::copy() const
{
    BoxBoundsItem* newBoxBoundsItem = create();
    *newBoxBoundsItem = *this;
    return newBoxBoundsItem;
}

Ionflux::GeoUtils::BoxBoundsItem* 
BoxBoundsItem::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<BoxBoundsItem*>(other);
}

Ionflux::GeoUtils::BoxBoundsItem* 
BoxBoundsItem::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    BoxBoundsItem* newObject = new BoxBoundsItem();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file BoxBoundsItem.cpp
 * \brief Item with box bounds implementation.
 */
