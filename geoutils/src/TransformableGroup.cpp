/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TransformableGroup.cpp          Transformable object group 
 * (implementation).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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

#include "geoutils/TransformableGroup.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "ifobject/objectutils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Vertex3.hpp"
#include "geoutils/transformutils.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/TransformableGroupXMLFactory.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

TransformableGroupClassInfo::TransformableGroupClassInfo()
{
	name = "TransformableGroup";
	desc = "Transformable object group";
}

TransformableGroupClassInfo::~TransformableGroupClassInfo()
{
}

// run-time type information instance constants
const TransformableGroupClassInfo TransformableGroup::transformableGroupClassInfo;
const Ionflux::ObjectBase::IFClassInfo* TransformableGroup::CLASS_INFO = &TransformableGroup::transformableGroupClassInfo;

const std::string TransformableGroup::XML_ELEMENT_NAME = "transformable_group";

TransformableGroup::TransformableGroup()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

TransformableGroup::TransformableGroup(const Ionflux::GeoUtils::TransformableGroup& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

TransformableGroup::~TransformableGroup()
{
	clearItems();
	// TODO: Nothing ATM. ;-)
}

void TransformableGroup::recalculateBounds()
{
	TransformableObject::recalculateBounds();
	const TransformableGroup* g0 = this;
	TransformableGroup* g1 = 0;
	if (useTransform() || useVI())
	{
	    // Adjust for transformation.
	    g1 = copy();
	    addLocalRef(g1);
	    g1->applyTransform();
	    g0 = g1;
	}
	Ionflux::GeoUtils::TransformableObjectVector::const_iterator i;
	bool e0 = true;
	for (i = g0->items.begin(); i != g0->items.end(); i++)
	{
	    TransformableObject* to0 = 
	        Ionflux::ObjectBase::nullPointerCheck(*i, this, 
	            "recalculateBounds", "Transformable object");
	    Range3 r0(to0->getBounds());
	    if (e0)
	    {
	        boundsCache->setBounds(r0);
	        e0 = false;
	    } else
	        boundsCache->extend(r0);
	}
	if (g1 != 0)
	    removeLocalRef(g1);
}

void TransformableGroup::clear()
{
	clearItems();
	TransformableObject::clear();
}

void TransformableGroup::applyTransform(bool recursive)
{
	Ionflux::GeoUtils::applyTransform(*this, items, 
	    recursive, "Transformable object");
}

Ionflux::GeoUtils::Vector3 TransformableGroup::getBarycenter() const
{
	Vector3 vSum;
	Ionflux::GeoUtils::TransformableObjectVector::const_iterator i;
	for (i = items.begin(); i < items.end(); i++)
	    vSum = vSum + (*i)->getBarycenter();
	vSum = vSum / items.size();
	// Adjust for transformation.
	Vertex3 v0(vSum);
	if (useTransform())
	    v0.transform(*getTransformMatrix());
	if (useVI())
	    v0.transformVI(*getViewMatrix(), getImageMatrix());
	return v0.getVector();
}

Ionflux::GeoUtils::TransformableGroup& TransformableGroup::scale(const 
Ionflux::GeoUtils::Vector3& s)
{
	TransformableObject::scale(s);
	return *this;
}

Ionflux::GeoUtils::TransformableGroup& TransformableGroup::translate(const 
Ionflux::GeoUtils::Vector3& t)
{
	TransformableObject::translate(t);
	return *this;
}

Ionflux::GeoUtils::TransformableGroup& TransformableGroup::rotate(double 
phi, Ionflux::GeoUtils::AxisID axis)
{
	TransformableObject::rotate(phi, axis);
	return *this;
}

Ionflux::GeoUtils::TransformableGroup& TransformableGroup::normalize()
{
	TransformableObject::normalize();
	return *this;
}

Ionflux::GeoUtils::TransformableGroup& 
TransformableGroup::center(Ionflux::GeoUtils::CenteringMethod method, 
Ionflux::GeoUtils::Vector3* origin)
{
	TransformableObject::center(method, origin);
	return *this;
}

Ionflux::GeoUtils::TransformableGroup& TransformableGroup::transform(const 
Ionflux::GeoUtils::Matrix3& matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::TransformableGroup& TransformableGroup::transform(const 
Ionflux::GeoUtils::Matrix4& matrix)
{
	TransformableObject::transform(matrix);
	return *this;
}

Ionflux::GeoUtils::TransformableGroup& 
TransformableGroup::transformVI(const Ionflux::GeoUtils::Matrix4& view, 
const Ionflux::GeoUtils::Matrix4* image)
{
	TransformableObject::transformVI(view, image);
	return *this;
}

Ionflux::GeoUtils::TransformableGroup& TransformableGroup::duplicate()
{
	// TODO: Implementation.
	return *copy();
}

Ionflux::GeoUtils::TransformableGroup& TransformableGroup::flatten()
{
	TransformableGroup g0;
	getLeafItems(g0);
	clearItems();
	for (TransformableObjectVector::iterator i = 
	    g0.items.begin(); i != g0.items.end(); i++)
	    addItem(*i);
	return *this;
}

void 
TransformableGroup::getLeafItems(Ionflux::GeoUtils::TransformableGroup& 
target, unsigned int level)
{
	if (level == 0)
	    // If this is the top level, apply all transforms.
	    applyTransform(true);
	for (TransformableObjectVector::const_iterator i = 
	    items.begin(); i != items.end(); i++)
	{
	    TransformableGroup* g1 = upcast(*i);
	    if (g1 != 0)
	        // Add leaf items recursively.
	        g1->getLeafItems(target, level + 1);
	    else
	        target.addItem(*i);
	}
}

std::string TransformableGroup::getDebugInfo(bool expand, unsigned int 
level)
{
	std::ostringstream result;
	std::ostringstream prefix;
	for (unsigned int i = 0; i < (2 * level); i++)
	    prefix << " ";
	result << prefix.str() << getClassName() << ": bounds = " << getBounds() 
	    << ", barycenter = " << getBarycenter() << ", numItems = " 
	    << items.size()<< "\n";
	if (useTransform())
	    result << prefix.str() << "transformMatrix = [" 
	        << getTransformMatrix()->getValueString() << "]\n";
	if (useVI())
	{
	    result << prefix.str() << "viewMatrix = [" 
	        << getViewMatrix()->getValueString() << "]\n";
	    if (getImageMatrix() != 0)
	        result << prefix.str() << "imageMatrix = [" 
	            << getImageMatrix()->getValueString() << "]\n";
	}
	if (items.size() == 0)
	{
	    result << prefix.str() << "(no items)";
	    return result.str();
	}
	result << prefix.str() << "Items:\n";
	unsigned int notShown = 0;
	for (unsigned int i = 0; i < items.size(); i++)
	{
	    TransformableObject* it0 = items[i];
	    TransformableGroup* g0 = upcast(it0);
	    if (g0 != 0)
	    {
	        // Append debug info recursively.
	        if (i != 0)
	            result << prefix.str() << "\n";
	        result << g0->getDebugInfo(expand, level + 1);
	    } else
	    {
	        if (expand)
	        {
	            if (i != 0)
	                result << prefix.str() << "\n";
	            result << prefix.str() << it0->getClassName() << " (bounds = "
	
                << it0->getBounds() << ", barycenter = " 
	                << it0->getBarycenter() << ")";
	        } else
	            notShown++;
	    }
	}
	if (!expand 
	    && (notShown > 0))
	    result << prefix.str() << "  (" << notShown << " items not shown)";
	return result.str();
}

std::string TransformableGroup::getValueString() const
{
	std::ostringstream status;
	if (items.size() > 0)
	{
	    // items
	    status << "items: ";
	    bool e0 = true;
	    for (TransformableObjectVector::const_iterator i = 
	        items.begin(); i != items.end(); i++)
	    {
	        TransformableObject* to0 = *i;
	        if (!e0)
	            status << ", ";
	        else
	            e0 = false;
	        if (to0 != 0)
	            status << to0->getString();
	        else
	            status << "<null>";
	    }
	}
	// transformable object data
	std::string ts0(TransformableObject::getValueString());
	if (ts0.size() > 0)
	    status << "; " << ts0;
	return status.str();
}

unsigned int TransformableGroup::getNumItems() const
{
    return items.size();
}

Ionflux::GeoUtils::TransformableObject* 
TransformableGroup::getItem(unsigned int elementIndex) const
{
    if (elementIndex < items.size())
		return items[elementIndex];
	return 0;
}

int TransformableGroup::findItem(Ionflux::GeoUtils::TransformableObject* 
needle, unsigned int occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::TransformableObject* currentItem = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < items.size()))
	{
		currentItem = items[i];
		if (currentItem == needle)
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

std::vector<Ionflux::GeoUtils::TransformableObject*>& 
TransformableGroup::getItems()
{
    return items;
}

void TransformableGroup::addItem(Ionflux::GeoUtils::TransformableObject* 
addElement)
{
	addLocalRef(addElement);
	items.push_back(addElement);
}

Ionflux::GeoUtils::TransformableObject* TransformableGroup::addItem()
{
	Ionflux::GeoUtils::TransformableObject* o0 = TransformableObject::create();
	addItem(o0);
	return o0;
}

void TransformableGroup::addItems(const 
std::vector<Ionflux::GeoUtils::TransformableObject*>& newItems)
{
	for (std::vector<Ionflux::GeoUtils::TransformableObject*>::const_iterator i = newItems.begin(); 
	    i != newItems.end(); i++)
	    addItem(*i);
}

void TransformableGroup::addItems(Ionflux::GeoUtils::TransformableGroup* 
newItems)
{
	for (unsigned int i = 0; 
	    i < newItems->getNumItems(); i++)
	    addItem(newItems->getItem(i));
}

void TransformableGroup::removeItem(Ionflux::GeoUtils::TransformableObject*
removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::TransformableObject* currentItem = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < items.size()))
	{
		currentItem = items[i];
		if (currentItem == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		items.erase(items.begin() + i);
		if (currentItem != 0)
			removeLocalRef(currentItem);
	}
}

void TransformableGroup::removeItemIndex(unsigned int removeIndex)
{
    if (removeIndex > items.size())
        return;
	Ionflux::GeoUtils::TransformableObject* e0 = items[removeIndex];
    items.erase(items.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void TransformableGroup::clearItems()
{
    std::vector<Ionflux::GeoUtils::TransformableObject*>::iterator i;
	for (i = items.begin(); i != items.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	items.clear();
}

Ionflux::GeoUtils::TransformableGroup& TransformableGroup::operator=(const 
Ionflux::GeoUtils::TransformableGroup& other)
{
    if (this == &other)
        return *this;
    TransformableObject::operator=(other);
    TransformableObjectVector v0;
    for (TransformableObjectVector::const_iterator i = 
        other.items.begin(); i != other.items.end(); i++)
    {
        TransformableObject* ot0 = 
            Ionflux::ObjectBase::nullPointerCheck(*i, this, 
                "operator=", "Transformable object");
        v0.push_back(ot0->copy());
    }
    clearItems();
    addItems(v0);
	return *this;
}

Ionflux::GeoUtils::TransformableGroup* TransformableGroup::copy() const
{
    TransformableGroup* newTransformableGroup = create();
    *newTransformableGroup = *this;
    return newTransformableGroup;
}

Ionflux::GeoUtils::TransformableGroup* 
TransformableGroup::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<TransformableGroup*>(other);
}

Ionflux::GeoUtils::TransformableGroup* 
TransformableGroup::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    TransformableGroup* newObject = new TransformableGroup();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int TransformableGroup::getMemSize() const
{
    return sizeof *this;
}

std::string TransformableGroup::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string TransformableGroup::getXMLAttributeData() const
{
	std::ostringstream d0;
	return d0.str();
}

void TransformableGroup::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string iws0 = Ionflux::ObjectBase::getIndent(indentLevel);
	bool haveBCData = false;
	bool xcFirst = true;
	if (!xcFirst || haveBCData)
	    d0 << "\n";
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0(items, "vec", "", 
        indentLevel, "pname=\"items\"");
    xcFirst = false;
	target = d0.str();
}

void TransformableGroup::loadFromXMLFile(const std::string& fileName, const
std::string& elementName)
{
	std::string en0(elementName);
	if (en0.size() == 0)
	    en0 = getXMLElementName();
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, en0);
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
TransformableGroup::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::TransformableGroupXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::TransformableGroupXMLFactory::create();
        fac0->addRef();
    }
    return fac0;
}

}

}

/** \file TransformableGroup.cpp
 * \brief Transformable object group implementation.
 */
