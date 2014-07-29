/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * VertexArrayObject.cpp           Vertex array object (OpenGL) 
 * (implementation).
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

#include "geoutils/VertexArrayObject.hpp"
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/glutils.hpp"
#include "geoutils/VertexAttribute.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

VertexArrayObjectClassInfo::VertexArrayObjectClassInfo()
{
	name = "VertexArrayObject";
	desc = "Vertex array object (OpenGL)";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

VertexArrayObjectClassInfo::~VertexArrayObjectClassInfo()
{
}

// run-time type information instance constants
const VertexArrayObjectClassInfo VertexArrayObject::vertexArrayObjectClassInfo;
const Ionflux::ObjectBase::IFClassInfo* VertexArrayObject::CLASS_INFO = &VertexArrayObject::vertexArrayObjectClassInfo;

VertexArrayObject::VertexArrayObject()
: vaoImpl(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

VertexArrayObject::VertexArrayObject(const Ionflux::GeoUtils::VertexArrayObject& other)
: vaoImpl(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

VertexArrayObject::~VertexArrayObject()
{
	clearAttributes();
	cleanup();
}

void VertexArrayObject::cleanup()
{
	if (vaoImpl != 0)
	{
	    glDeleteVertexArrays(1, &vaoImpl);
	    vaoImpl = 0;
	}
}

void VertexArrayObject::init()
{
	if (vaoImpl != 0)
	    glDeleteVertexArrays(1, &vaoImpl);
	glGenVertexArrays(1, &vaoImpl);
	if (vaoImpl == 0)
	{
	    throw GeoUtilsError(getErrorString(
	        "Could not allocate OpenGL vertex array object.", "init"));
	}
}

void VertexArrayObject::bind()
{
	if (vaoImpl == 0)
	{
	    throw GeoUtilsError(getErrorString(
	        "OpenGL vertex array object not initialized.", "bind"));
	}
	glBindVertexArray(vaoImpl);
}

void VertexArrayObject::update()
{
	if (vaoImpl == 0)
	{
	    throw GeoUtilsError(getErrorString(
	        "OpenGL vertex array object not initialized.", "update"));
	}
	bind();
	int k = 0;
	for (VertexAttributeVector::iterator i = attributes.begin(); 
	    i != attributes.end(); i++)
	{
	    VertexAttribute* va = *i;
	    if (va != 0)
	    {
	        // <---- DEBUG ----- //
	        std::cerr << "[VertexArrayObject::update] "
	            "Enabling vertex attribute: index = " << k << ", [" 
	            << va->getValueString() << "]" << std::endl;
	        // ----- DEBUG ----> //
	        va->enable(k);
	        k++;
	    }
	}
}

std::string VertexArrayObject::getValueString() const
{
	ostringstream status;
	bool e0 = true;
	for (VertexAttributeVector::const_iterator i = attributes.begin(); 
	    i != attributes.end(); i++)
	{
	    if (!e0)
	        status << ", ";
	    else
	        e0 = false;
	    status << "(" << (*i)->getValueString() << ")";
	}
	if (attributes.size() == 0)
	    status << "<none>";
	return status.str();
}

void VertexArrayObject::setVaoImpl(GLuint newVaoImpl)
{
	vaoImpl = newVaoImpl;
}

GLuint VertexArrayObject::getVaoImpl() const
{
    return vaoImpl;
}

unsigned int VertexArrayObject::getNumAttributes() const
{
    return attributes.size();
}

Ionflux::GeoUtils::VertexAttribute* 
VertexArrayObject::getAttribute(unsigned int elementIndex) const
{
    if (elementIndex < attributes.size())
		return attributes[elementIndex];
	return 0;
}

int VertexArrayObject::findAttribute(Ionflux::GeoUtils::VertexAttribute* 
needle, unsigned int occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::VertexAttribute* currentAttribute = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < attributes.size()))
	{
		currentAttribute = attributes[i];
		if (currentAttribute == needle)
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

std::vector<Ionflux::GeoUtils::VertexAttribute*>& 
VertexArrayObject::getAttributes()
{
    return attributes;
}

void VertexArrayObject::addAttribute(Ionflux::GeoUtils::VertexAttribute* 
addElement)
{
	addLocalRef(addElement);
	attributes.push_back(addElement);
}

Ionflux::GeoUtils::VertexAttribute* VertexArrayObject::addAttribute()
{
	Ionflux::GeoUtils::VertexAttribute* o0 = VertexAttribute::create();
	addAttribute(o0);
	return o0;
}

void VertexArrayObject::addAttributes(const 
std::vector<Ionflux::GeoUtils::VertexAttribute*>& newAttributes)
{
	for (std::vector<Ionflux::GeoUtils::VertexAttribute*>::const_iterator i = newAttributes.begin(); 
	    i != newAttributes.end(); i++)
	    addAttribute(*i);
}

void VertexArrayObject::addAttributes(Ionflux::GeoUtils::VertexArrayObject*
newAttributes)
{
	for (unsigned int i = 0; 
	    i < newAttributes->getNumAttributes(); i++)
	    addAttribute(newAttributes->getAttribute(i));
}

void VertexArrayObject::removeAttribute(Ionflux::GeoUtils::VertexAttribute*
removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::VertexAttribute* currentAttribute = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < attributes.size()))
	{
		currentAttribute = attributes[i];
		if (currentAttribute == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		attributes.erase(attributes.begin() + i);
		if (currentAttribute != 0)
			removeLocalRef(currentAttribute);
	}
}

void VertexArrayObject::removeAttributeIndex(unsigned int removeIndex)
{
    if (removeIndex > attributes.size())
        return;
	Ionflux::GeoUtils::VertexAttribute* e0 = attributes[removeIndex];
    attributes.erase(attributes.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void VertexArrayObject::clearAttributes()
{
    std::vector<Ionflux::GeoUtils::VertexAttribute*>::iterator i;
	for (i = attributes.begin(); i != attributes.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	attributes.clear();
}

Ionflux::GeoUtils::VertexArrayObject& VertexArrayObject::operator=(const 
Ionflux::GeoUtils::VertexArrayObject& other)
{
    if (this == &other)
        return *this;
	return *this;
}

Ionflux::GeoUtils::VertexArrayObject* VertexArrayObject::copy() const
{
    VertexArrayObject* newVertexArrayObject = create();
    *newVertexArrayObject = *this;
    return newVertexArrayObject;
}

Ionflux::GeoUtils::VertexArrayObject* 
VertexArrayObject::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<VertexArrayObject*>(other);
}

Ionflux::GeoUtils::VertexArrayObject* 
VertexArrayObject::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    VertexArrayObject* newObject = new VertexArrayObject();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int VertexArrayObject::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file VertexArrayObject.cpp
 * \brief Vertex array object (OpenGL) implementation.
 */
