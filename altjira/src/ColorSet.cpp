/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ColorSet.cpp                    Color set (implementation).
 * =========================================================================
 * 
 * This file is part of Altjira - Ionflux' Image Processing Library.
 * 
 * Altjira - Ionflux' Image Processing Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
 * 
 * Altjira - Ionflux' Image Processing Library is distributed in the hope 
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Altjira - Ionflux' Image Processing Library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "altjira/ColorSet.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "altjira/AltjiraError.hpp"
#include "altjira/Color.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Altjira
{

ColorSetClassInfo::ColorSetClassInfo()
{
	name = "ColorSet";
	desc = "Color set";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

ColorSetClassInfo::~ColorSetClassInfo()
{
}

// run-time type information instance constants
const ColorSetClassInfo ColorSet::colorSetClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ColorSet::CLASS_INFO = &ColorSet::colorSetClassInfo;

ColorSet::ColorSet()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ColorSet::ColorSet(const Ionflux::Altjira::ColorSet& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ColorSet::ColorSet(Ionflux::Altjira::ColorVector& initColors)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addColors(initColors);
}

ColorSet::~ColorSet()
{
	clearColors();
	// TODO: Nothing ATM. ;-)
}

bool ColorSet::operator==(const Ionflux::Altjira::ColorSet& other) const
{
	if (colors.size() != other.colors.size())
	    return false;
	for (unsigned int i = 0; i < colors.size(); i++)
	{
	    Color* v0 = colors[i];
	    Color* v1 = other.colors[i];
	    if ((v0 != 0) && (v1 != 0))
	    {
	        if (*v0 != *v1)
	            return false;
	    } else
	        return false;
	}
	return true;
}

bool ColorSet::operator!=(const Ionflux::Altjira::ColorSet& other) const
{
	// TODO: Implementation.
	return !(*this == other);;
}

std::string ColorSet::getValueString() const
{
	ostringstream status;
	bool e0 = true;
	for (ColorVector::const_iterator i = colors.begin(); 
	    i != colors.end(); i++)
	{
	    if (!e0)
	        status << ", ";
	    else
	        e0 = false;
	    status << "(" << (*i)->getValueString() << ")";
	}
	if (colors.size() == 0)
	    status << "<none>";
	return status.str();
}

unsigned int ColorSet::getNumColors() const
{
    return colors.size();
}

Ionflux::Altjira::Color* ColorSet::getColor(unsigned int elementIndex) 
const
{
    if (elementIndex < colors.size())
		return colors[elementIndex];
	return 0;
}

int ColorSet::findColor(Ionflux::Altjira::Color* needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::Altjira::Color* currentColor = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < colors.size()))
	{
		currentColor = colors[i];
		if (currentColor == needle)
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

std::vector<Ionflux::Altjira::Color*>& ColorSet::getColors()
{
    return colors;
}

void ColorSet::addColor(Ionflux::Altjira::Color* addElement)
{
	addLocalRef(addElement);
	colors.push_back(addElement);
}

Ionflux::Altjira::Color* ColorSet::addColor()
{
	Ionflux::Altjira::Color* o0 = Color::create();
	addColor(o0);
	return o0;
}

void ColorSet::addColors(const std::vector<Ionflux::Altjira::Color*>& 
newColors)
{
	for (std::vector<Ionflux::Altjira::Color*>::const_iterator i = newColors.begin(); 
	    i != newColors.end(); i++)
	    addColor(*i);
}

void ColorSet::addColors(Ionflux::Altjira::ColorSet* newColors)
{
	for (unsigned int i = 0; 
	    i < newColors->getNumColors(); i++)
	    addColor(newColors->getColor(i));
}

void ColorSet::removeColor(Ionflux::Altjira::Color* removeElement)
{
    bool found = false;
	Ionflux::Altjira::Color* currentColor = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < colors.size()))
	{
		currentColor = colors[i];
		if (currentColor == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		colors.erase(colors.begin() + i);
		if (currentColor != 0)
			removeLocalRef(currentColor);
	}
}

void ColorSet::removeColorIndex(unsigned int removeIndex)
{
    if (removeIndex > colors.size())
        return;
	Ionflux::Altjira::Color* e0 = colors[removeIndex];
    colors.erase(colors.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void ColorSet::clearColors()
{
    std::vector<Ionflux::Altjira::Color*>::iterator i;
	for (i = colors.begin(); i != colors.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	colors.clear();
}

Ionflux::Altjira::ColorSet& ColorSet::operator=(const 
Ionflux::Altjira::ColorSet& other)
{
    if (this == &other)
        return *this;
    ColorVector v0;
    for (ColorVector::const_iterator i = other.colors.begin(); 
        i != other.colors.end(); i++)
        v0.push_back((*i)->copy());
    clearColors();
    addColors(v0);
	return *this;
}

Ionflux::Altjira::ColorSet* ColorSet::copy() const
{
    ColorSet* newColorSet = create();
    *newColorSet = *this;
    return newColorSet;
}

Ionflux::Altjira::ColorSet* ColorSet::upcast(Ionflux::ObjectBase::IFObject*
other)
{
    return dynamic_cast<ColorSet*>(other);
}

Ionflux::Altjira::ColorSet* ColorSet::create(Ionflux::ObjectBase::IFObject*
parentObject)
{
    ColorSet* newObject = new ColorSet();
    if (newObject == 0)
    {
        throw AltjiraError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Altjira::ColorSet* ColorSet::create(Ionflux::Altjira::ColorVector&
initColors, Ionflux::ObjectBase::IFObject* parentObject)
{
    ColorSet* newObject = new ColorSet(initColors);
    if (newObject == 0)
    {
        throw AltjiraError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int ColorSet::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file ColorSet.cpp
 * \brief Color set implementation.
 */
