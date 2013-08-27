/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vertex3Set.cpp                  Vertex set (3D) (implementation).
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

#include "geoutils/Vertex3Set.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Vertex3.hpp"
#include "geoutils/gslutils.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

Vertex3SetClassInfo::Vertex3SetClassInfo()
{
	name = "Vertex3Set";
	desc = "Vertex set (3D)";
}

Vertex3SetClassInfo::~Vertex3SetClassInfo()
{
}

// run-time type information instance constants
const Vertex3SetClassInfo Vertex3Set::vertex3SetClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Vertex3Set::CLASS_INFO = &Vertex3Set::vertex3SetClassInfo;

const std::string Vertex3Set::XML_ELEMENT_NAME = "vertex3set";

Vertex3Set::Vertex3Set()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Vertex3Set::Vertex3Set(const Ionflux::GeoUtils::Vertex3Set& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Vertex3Set::Vertex3Set(Ionflux::GeoUtils::Vertex3Vector& initVertices)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addVertices(initVertices);
}

Vertex3Set::~Vertex3Set()
{
	clearVertices();
	// TODO: Nothing ATM. ;-)
}

void Vertex3Set::recalculateBounds()
{
	TransformableObject::recalculateBounds();
	Ionflux::GeoUtils::Vertex3Vector::const_iterator i;
	bool e0 = true;
	for (i = vertices.begin(); i < vertices.end(); i++)
	{
	    Vertex3 v0(*(*i));
	    if (useTransform)
	        // Adjust for transformation.
	        v0.transform(transformMatrix);
	    if (useVI)
	        // Adjust for view/image matrix.
	        v0.transformVI(viewMatrix, &imageMatrix);
	    if (e0)
	    {
	        boundsCache->setBounds(v0.getVector());
	        e0 = false;
	    } else
	        boundsCache->extend(v0.getVector());
	}
}

Ionflux::GeoUtils::Vertex3* Vertex3Set::addVertex()
{
	Vertex3* v0 = new Vertex3();
	if (v0 == 0)
	    throw GeoUtilsError("Could not allocate object.");
	addVertex(v0);
	return v0;
}

void Vertex3Set::addVertices(Ionflux::GeoUtils::Vertex3Vector& newVerts)
{
	for (Vertex3Vector::iterator i = newVerts.begin(); 
	    i != newVerts.end(); i++)
	    addVertex(*i);
}

void Vertex3Set::addVertices(Ionflux::GeoUtils::Vertex3Set& newVerts)
{
	for (unsigned int i = 0; i < newVerts.getNumVertices(); i++)
	    addVertex(newVerts.getVertex(i));
}

std::string Vertex3Set::getValueString() const
{
	ostringstream status;
	bool e0 = true;
	for (Vertex3Vector::const_iterator i = vertices.begin(); 
	    i != vertices.end(); i++)
	{
	    if (!e0)
	        status << ", ";
	    else
	        e0 = false;
	    status << "(" << (*i)->getValueString() << ")";
	}
	if (!useTransform && !useVI)
	    return status.str();
	if (!useTransform && !useVI)
	    return status.str();
	status << "; " << TransformableObject::getValueString();
	return status.str();
}

Ionflux::GeoUtils::Vector3 Vertex3Set::getBarycenter()
{
	Vector3 vSum;
	Ionflux::GeoUtils::Vertex3Vector::const_iterator i;
	for (i = vertices.begin(); i < vertices.end(); i++)
	    vSum = vSum + (*i)->getVector();
	vSum = vSum / vertices.size();
	// Adjust for transformation.
	Vertex3 v0(vSum);
	if (useTransform)
	    v0.transform(transformMatrix);
	if (useVI)
	    v0.transformVI(viewMatrix, &imageMatrix);
	/* <---- DEBUG ----- //
	std::ostringstream message;
	message << "barycenter = " << v0;
	log(IFLogMessage(message.str(), VL_DEBUG, this, "getBarycenter"));
	// <---- DEBUG ----- */
	return v0.getVector();
}

void Vertex3Set::applyTransform(bool recursive)
{
	if (!useTransform 
	    && !useVI)
	    // Nothing to be done.
	    return;
	for (Vertex3Vector::iterator i = vertices.begin(); 
	    i != vertices.end(); i++)
	{
	    if (useTransform)
	        (*i)->transform(transformMatrix);
	    if (useVI)
	        (*i)->transformVI(viewMatrix, &imageMatrix);
	    if (recursive)
	        (*i)->applyTransform(recursive);
	}
	if (useTransform)
	{
	    transformMatrix = Matrix4::UNIT;
	    useTransform = false;
	}
	if (useVI)
	{
	    viewMatrix = Matrix4::UNIT;
	    imageMatrix = Matrix4::UNIT;
	    useVI = false;
	}
}

Ionflux::GeoUtils::Vertex3Set& Vertex3Set::scale(const 
Ionflux::GeoUtils::Vector3& s)
{
	TransformableObject::scale(s);
	return *this;
}

Ionflux::GeoUtils::Vertex3Set& Vertex3Set::translate(const 
Ionflux::GeoUtils::Vector3& t)
{
	TransformableObject::translate(t);
	return *this;
}

Ionflux::GeoUtils::Vertex3Set& Vertex3Set::rotate(double phi, 
Ionflux::GeoUtils::AxisID axis)
{
	TransformableObject::rotate(phi, axis);
	return *this;
}

Ionflux::GeoUtils::Vertex3Set& Vertex3Set::normalize()
{
	TransformableObject::normalize();
	return *this;
}

Ionflux::GeoUtils::Vertex3Set& 
Vertex3Set::center(Ionflux::GeoUtils::CenteringMethod method, 
Ionflux::GeoUtils::Vector3* origin)
{
	TransformableObject::center(method, origin);
	return *this;
}

Ionflux::GeoUtils::Vertex3Set& Vertex3Set::transform(const 
Ionflux::GeoUtils::Matrix3& matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Vertex3Set& Vertex3Set::transform(const 
Ionflux::GeoUtils::Matrix4& matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::Vertex3Set& Vertex3Set::transformVI(const 
Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4* image)
{
	TransformableObject::transformVI(view, image);
	return *this;
}

Ionflux::GeoUtils::Vertex3Set& Vertex3Set::duplicate()
{
	// TODO: Implementation.
	return *copy();
}

Ionflux::GeoUtils::Matrix3 Vertex3Set::getCovariance()
{
	Matrix3 result;
	Ionflux::GeoUtils::covariance(*this, result);
	return result;
}

Ionflux::GeoUtils::Matrix3 Vertex3Set::getPCABase()
{
	Vertex3Set* vs = copy();
	vs->center(CENTER_BARYCENTER);
	vs->applyTransform();
	Matrix3 cov = vs->getCovariance();
	Matrix3 u;
	Vector3 s;
	Matrix3 v;
	cov.svd(u, s, v);
	delete vs;
	return v;
}

Ionflux::GeoUtils::Plane3 Vertex3Set::getPlaneFit()
{
	Vector3 bc = getBarycenter();
	Matrix3 pcaBase = getPCABase();
	return Plane3::createFromNormal(pcaBase.getC2(), pcaBase.getC1(), bc);
}

std::string Vertex3Set::getXMLData_legacy() const
{
	ostringstream d0;
	bool first = true;
	for (Vertex3Vector::const_iterator i = vertices.begin(); 
	    i != vertices.end(); i++)
	{
	    if (!first)
	        d0 << " ";
	    else
	        first = false;
	    d0 << (*i)->getXMLData_legacy();
	}
	return d0.str();
}

std::string Vertex3Set::getXML_legacy() const
{
	ostringstream d0;
	d0 << "<vertex3set d=\"" << getXMLData_legacy() << "\" />";
	return d0.str();
}

unsigned int Vertex3Set::getNumVertices() const
{
    return vertices.size();
}

Ionflux::GeoUtils::Vertex3* Vertex3Set::getVertex(unsigned int 
elementIndex) const
{
    if (elementIndex < vertices.size())
		return vertices[elementIndex];
	return 0;
}

int Vertex3Set::findVertex(Ionflux::GeoUtils::Vertex3* needle, unsigned int
occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::Vertex3* currentVertex = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < vertices.size()))
	{
		currentVertex = vertices[i];
		if (currentVertex == needle)
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

std::vector<Ionflux::GeoUtils::Vertex3*>& Vertex3Set::getVertices()
{
    return vertices;
}

void Vertex3Set::addVertex(Ionflux::GeoUtils::Vertex3* addElement)
{
	addLocalRef(addElement);
	vertices.push_back(addElement);
}

void Vertex3Set::removeVertex(Ionflux::GeoUtils::Vertex3* removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::Vertex3* currentVertex = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < vertices.size()))
	{
		currentVertex = vertices[i];
		if (currentVertex == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		vertices.erase(vertices.begin() + i);
		if (currentVertex != 0)
			removeLocalRef(currentVertex);
	}
}

void Vertex3Set::removeVertexIndex(unsigned int removeIndex)
{
    if (removeIndex > vertices.size())
        return;
	Ionflux::GeoUtils::Vertex3* e0 = vertices[removeIndex];
    vertices.erase(vertices.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void Vertex3Set::clearVertices()
{
    std::vector<Ionflux::GeoUtils::Vertex3*>::iterator i;
	for (i = vertices.begin(); i != vertices.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	vertices.clear();
}

Ionflux::GeoUtils::Vertex3Set& Vertex3Set::operator=(const 
Ionflux::GeoUtils::Vertex3Set& other)
{
    TransformableObject::operator=(other);
    Vertex3Vector v0;
    for (Vertex3Vector::const_iterator i = other.vertices.begin(); 
        i != other.vertices.end(); i++)
        v0.push_back(&((*i)->duplicate()));
    clearVertices();
    addVertices(v0);
	return *this;
}

Ionflux::GeoUtils::Vertex3Set* Vertex3Set::copy() const
{
    Vertex3Set* newVertex3Set = create();
    *newVertex3Set = *this;
    return newVertex3Set;
}

Ionflux::GeoUtils::Vertex3Set* 
Vertex3Set::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Vertex3Set*>(other);
}

Ionflux::GeoUtils::Vertex3Set* 
Vertex3Set::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Vertex3Set* newObject = new Vertex3Set();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

std::string Vertex3Set::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Vertex3Set::getXMLAttributeData() const
{
	std::string a0(Ionflux::ObjectBase::IFObject::getXMLAttributeData());
	std::ostringstream d0;
	if ((d0.str().size() > 0) && (a0.size() > 0))
	    d0 << " ";
    d0 << a0;
	return d0.str();
}

void Vertex3Set::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::string iws0 = Ionflux::ObjectBase::getIndent(indentLevel);
	std::ostringstream d0;
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0(vertices, "vert3vec", "", 
        indentLevel, "pname=\"vertices\"");
	target = d0.str();
}

}

}

/** \file Vertex3Set.cpp
 * \brief Vertex set (3D) implementation.
 */
