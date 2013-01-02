/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Rescale.cpp                     Rescale mapping (implementation).
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

#include "ifmapping/Rescale.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <sstream>
#include "ifmapping/MappingError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

RescaleClassInfo::RescaleClassInfo()
{
	name = "Rescale";
	desc = "Rescale mapping";
}

RescaleClassInfo::~RescaleClassInfo()
{
}

// run-time type information instance constants
const RescaleClassInfo Rescale::rescaleClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Rescale::CLASS_INFO = &Rescale::rescaleClassInfo;

Rescale::Rescale()
: func(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	args.push_back(0.);
	args.push_back(1.);
}

Rescale::Rescale(const Ionflux::Mapping::Rescale& other)
: func(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Rescale::Rescale(Ionflux::Mapping::Mapping* initFunc, const 
Ionflux::Mapping::MappingValueVector* initArgs)
: func(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initArgs != 0)
	    args = *initArgs;
	else
	{
	    args.push_back(0.);
	    args.push_back(1.);
	}
	setFunc(initFunc);
}

Rescale::~Rescale()
{
	clearArgs();
	// TODO: Nothing ATM. ;-)
}

void Rescale::addArgs(const Ionflux::Mapping::MappingValueVector& newArgs)
{
	for (MappingValueVector::const_iterator i = newArgs.begin(); 
	    i != newArgs.end(); i++)
	    addArg(*i);
}

void Rescale::findExtremePoints()
{
	if (func == 0)
	{
	    vMin = 0.;
	    vMax = 1.;
	    return;
	}
	bool vMinDefined = false;
	bool vMaxDefined = false;
	Ionflux::Mapping::MappingValue nvMin = 0.;
	Ionflux::Mapping::MappingValue nvMax = 0.;
	for (unsigned int i = 0; i < args.size(); i++)
	{
	    Ionflux::Mapping::MappingValue v = (*func)(args[i]);
	    if (!vMinDefined 
	        || (v < nvMin))
	    {
	        nvMin = v;
	        vMinDefined = true;
	    }
	    if (!vMaxDefined 
	        || (v > nvMax))
	    {
	        nvMax = v;
	        vMaxDefined = true;
	    }
	}
	vMin = nvMin;
	vMax = nvMax;
	/* <---- DEBUG ----- //
	std::ostringstream message;
	message << "args.size = " << args.size() << ", vMin = " << vMin 
	    << ", vMax = " << vMax;
	log(IFLogMessage(message.str(), VL_DEBUG, this, "findExtremePoints"));
	// <---- DEBUG ----- */
}

std::string Rescale::getString() const
{
	ostringstream status;
	status << getClassName() << "[";
	if (func != 0)
	    status << (*func);
	else
	    status << "<none>";
	status << "]";
	return status.str();
}

Ionflux::Mapping::MappingValue Rescale::call(Ionflux::Mapping::MappingValue
value) const
{
	// TODO: Implementation.
	return ((*func)(value) - vMin) / (vMax - vMin);
}

void Rescale::setFunc(Ionflux::Mapping::Mapping* newFunc)
{
	if (func == newFunc)
	    return;
	if (newFunc != 0)
	    addLocalRef(newFunc);
	if (func != 0)
	    removeLocalRef(func);
	func = newFunc;
	if (func != 0)
	    findExtremePoints();
}

Ionflux::Mapping::Mapping* Rescale::getFunc() const
{
	return func;
}

unsigned int Rescale::getNumArgs() const
{
    return args.size();
}

Ionflux::Mapping::MappingValue Rescale::getArg(unsigned int elementIndex) 
const
{
    if (elementIndex < args.size())
		return args[elementIndex];
	return 0;
}

int Rescale::findArg(Ionflux::Mapping::MappingValue needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::Mapping::MappingValue currentArg = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < args.size()))
	{
		currentArg = args[i];
		if (currentArg == needle)
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

std::vector<Ionflux::Mapping::MappingValue>& Rescale::getArgs()
{
    return args;
}

void Rescale::addArg(Ionflux::Mapping::MappingValue addElement)
{
	args.push_back(addElement);
}

void Rescale::removeArg(Ionflux::Mapping::MappingValue removeElement)
{
    bool found = false;
	Ionflux::Mapping::MappingValue currentArg = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < args.size()))
	{
		currentArg = args[i];
		if (currentArg == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		args.erase(args.begin() + i);
	}
}

void Rescale::removeArgIndex(unsigned int removeIndex)
{
    if (removeIndex > args.size())
        return;
    args.erase(args.begin() + removeIndex);
}

void Rescale::clearArgs()
{
    args.clear();
}

Ionflux::Mapping::Rescale& Rescale::operator=(const 
Ionflux::Mapping::Rescale& other)
{
    args = other.args;
    setFunc(other.func);
	return *this;
}

Ionflux::Mapping::Rescale* Rescale::copy() const
{
    Rescale* newRescale = create();
    *newRescale = *this;
    return newRescale;
}

Ionflux::Mapping::Rescale* Rescale::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Rescale* newObject = new Rescale();
    if (newObject == 0)
    {
        throw MappingError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file Rescale.cpp
 * \brief Rescale mapping implementation.
 */
