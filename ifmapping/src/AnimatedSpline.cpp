/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * AnimatedSpline.cpp              Animated Bezier spline (implementation).
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

#include "ifmapping/AnimatedSpline.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <sstream>
#include <cmath>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

AnimatedSplineClassInfo::AnimatedSplineClassInfo()
{
	name = "AnimatedSpline";
	desc = "Animated Bezier spline";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

AnimatedSplineClassInfo::~AnimatedSplineClassInfo()
{
}

// run-time type information instance constants
const AnimatedSplineClassInfo AnimatedSpline::animatedSplineClassInfo;
const Ionflux::ObjectBase::IFClassInfo* AnimatedSpline::CLASS_INFO = &AnimatedSpline::animatedSplineClassInfo;

AnimatedSpline::AnimatedSpline()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

AnimatedSpline::AnimatedSpline(const Ionflux::Mapping::AnimatedSpline& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

AnimatedSpline::~AnimatedSpline()
{
	clearKeys();
	// TODO: Nothing ATM. ;-)
}

void AnimatedSpline::getShape(Ionflux::Mapping::MappingValue t, 
Ionflux::Mapping::BezierSpline& target) const
{
	unsigned int numKeys = keys.size();
	if (numKeys == 0)
	    throw MappingError("No keys defined.");
	if (numKeys == 1)
	{
	    target = *dynamic_cast<BezierSpline*>(keys[0]);
	    return;
	}
	if (t <= keys[0]->getT())
	{
	    target = *dynamic_cast<BezierSpline*>(keys[0]);
	    return;
	}
	if (t >= keys[keys.size() - 1]->getT())
	{
	    target = *dynamic_cast<BezierSpline*>(keys[keys.size() - 1]);
	    return;
	}
	/* The parameter is somewhere in the range of the keys.
	   Find the end key. */
	unsigned int i = 0;
	BezierSplineKey* k = keys[i];
	MappingValue tk = k->getT();
	while (t > tk)
	{
	    i++;
	    /* NOTE: 'i' cannot go beyond keys.size() - 1 because of the 
	       check above. */
	    k = keys[i];
	    tk = k->getT();
	}
	if (t == tk)
	{
	    // Exact match, no need to interpolate.
	    target = *dynamic_cast<BezierSpline*>(k);
	}
	// NOTE: 'i' is larger than 0 because of the check above.
	BezierSplineKey* k0 = keys[i - 1];
	// Rescale the interpolation parameter to the interval.
	MappingValue s = (t - k0->getT()) / (k->getT() - k0->getT());
	/* <---- DEBUG ----- //
	std::ostringstream message;
	message << "t = " << t << ", s = " << s << ", k0 = " << k0->getString() 
	    << ", k = " << k->getString();
	log(IFLogMessage(message.str(), VL_DEBUG, this, "getShape"));
	// <---- DEBUG ----- */
	target = k0->interpolate(*k, s);
}

Ionflux::Mapping::BezierSpline 
AnimatedSpline::call(Ionflux::Mapping::MappingValue value) const
{
	BezierSpline target;
	getShape(value, target);
	return target;
}

std::string AnimatedSpline::getString() const
{
	ostringstream message;
	message << getClassName() << "[";
	bool e0 = true;
	for (BezierSplineKeyVector::const_iterator i = keys.begin(); 
	    i != keys.end(); i++)
	{
	    if (!e0)
	        message << ", ";
	    else
	        e0 = false;
	    message << (*i)->getString();
	}
	message << "]";
	return message.str();
}

unsigned int AnimatedSpline::getNumKeys() const
{
    return keys.size();
}

Ionflux::Mapping::BezierSplineKey* AnimatedSpline::getKey(unsigned int 
elementIndex) const
{
    if (elementIndex < keys.size())
		return keys[elementIndex];
	return 0;
}

int AnimatedSpline::findKey(Ionflux::Mapping::BezierSplineKey* needle, 
unsigned int occurence) const
{
    bool found = false;
	Ionflux::Mapping::BezierSplineKey* currentKey = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < keys.size()))
	{
		currentKey = keys[i];
		if (currentKey == needle)
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

std::vector<Ionflux::Mapping::BezierSplineKey*>& AnimatedSpline::getKeys()
{
    return keys;
}

void AnimatedSpline::addKey(Ionflux::Mapping::BezierSplineKey* addElement)
{
	addLocalRef(addElement);
	keys.push_back(addElement);
}

void AnimatedSpline::removeKey(Ionflux::Mapping::BezierSplineKey* 
removeElement)
{
    bool found = false;
	Ionflux::Mapping::BezierSplineKey* currentKey = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < keys.size()))
	{
		currentKey = keys[i];
		if (currentKey == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		keys.erase(keys.begin() + i);
		if (currentKey != 0)
			removeLocalRef(currentKey);
	}
}

void AnimatedSpline::removeKeyIndex(unsigned int removeIndex)
{
    if (removeIndex > keys.size())
        return;
	Ionflux::Mapping::BezierSplineKey* e0 = keys[removeIndex];
    keys.erase(keys.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void AnimatedSpline::clearKeys()
{
    std::vector<Ionflux::Mapping::BezierSplineKey*>::iterator i;
	for (i = keys.begin(); i != keys.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	keys.clear();
}

Ionflux::Mapping::AnimatedSpline& AnimatedSpline::operator=(const 
Ionflux::Mapping::AnimatedSpline& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Mapping::AnimatedSpline* AnimatedSpline::copy() const
{
    AnimatedSpline* newAnimatedSpline = 
        new AnimatedSpline();
    *newAnimatedSpline = *this;
    return newAnimatedSpline;
}

}

}

/** \file AnimatedSpline.cpp
 * \brief Animated Bezier spline implementation.
 */
