/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * LoadSVG.cpp                     Transform node: Load SVG 
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

#include "geoutils/LoadSVG.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "ifmapping/utils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/Polygon3Set.hpp"
#include "geoutils/Polygon3.hpp"
#include "geoutils/SVG.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;
using Ionflux::Mapping::defaultStr;

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

LoadSVGClassInfo::LoadSVGClassInfo()
{
	name = "LoadSVG";
	desc = "Transform node: Load SVG";
}

LoadSVGClassInfo::~LoadSVGClassInfo()
{
}

// run-time type information instance constants
const LoadSVGClassInfo LoadSVG::loadSVGClassInfo;
const Ionflux::ObjectBase::IFClassInfo* LoadSVG::CLASS_INFO = &LoadSVG::loadSVGClassInfo;

LoadSVG::LoadSVG()
: fileName("")
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

LoadSVG::LoadSVG(const Ionflux::GeoUtils::TransformNodes::LoadSVG& other)
: fileName("")
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

LoadSVG::LoadSVG(const std::string& initFileName, const 
Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID), fileName(initFileName)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

LoadSVG::~LoadSVG()
{
	clearElementIDs();
	// TODO: Nothing ATM. ;-)
}

void LoadSVG::process()
{
	if (fileName.size() == 0)
	    throw GeoUtilsError("Input file name not specified.");
	TransformableGroup* g0 = new TransformableGroup();
	if (g0 == 0)
	throw GeoUtilsError("[LoadSVG::process] "
	    "Could not allocate transformable group!");
	if (elementIDs.size() > 0)
	{
	    // Create polygons.
	    Polygon3Set ps0;
	    Ionflux::GeoUtils::getSVGPolygons(fileName, elementIDs, ps0);
	    for (unsigned int i = 0; i < ps0.getNumPolygons(); i++)
	    {
	        Polygon3* p0 = ps0.getPolygon(i);
	        g0->addItem(p0);
	    }
	} else
	{
	    // Create SVG object.
	    SVG* svg0 = SVG::create();
	    svg0->setSource(fileName);
	    svg0->setType(SVG::TYPE_FILE);
	    g0->addItem(svg0);
	}
	addOutput(g0);
}

std::string LoadSVG::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") 
	    << "; " << defaultStr(fileName, "<none>") << "]";
	return status.str();
}

void LoadSVG::setFileName(const std::string& newFileName)
{
	fileName = newFileName;
}

std::string LoadSVG::getFileName() const
{
	return fileName;
}

unsigned int LoadSVG::getNumElementIDs() const
{
    return elementIDs.size();
}

std::string LoadSVG::getElementID(unsigned int elementIndex) const
{
    if (elementIndex < elementIDs.size())
		return elementIDs[elementIndex];
	return "";
}

int LoadSVG::findElementID(std::string needle, unsigned int occurence) 
const
{
    bool found = false;
	std::string currentElementID = "";
	unsigned int i = 0;
	while (!found 
		&& (i < elementIDs.size()))
	{
		currentElementID = elementIDs[i];
		if (currentElementID == needle)
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

std::vector<std::string>& LoadSVG::getElementIDs()
{
    return elementIDs;
}

void LoadSVG::addElementID(std::string addElement)
{
	elementIDs.push_back(addElement);
}

void LoadSVG::removeElementID(std::string removeElement)
{
    bool found = false;
	std::string currentElementID = "";
	unsigned int i = 0;
	while (!found 
		&& (i < elementIDs.size()))
	{
		currentElementID = elementIDs[i];
		if (currentElementID == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		elementIDs.erase(elementIDs.begin() + i);
	}
}

void LoadSVG::removeElementIDIndex(unsigned int removeIndex)
{
    if (removeIndex > elementIDs.size())
        return;
    elementIDs.erase(elementIDs.begin() + removeIndex);
}

void LoadSVG::clearElementIDs()
{
    elementIDs.clear();
}

Ionflux::GeoUtils::TransformNodes::LoadSVG& LoadSVG::operator=(const 
Ionflux::GeoUtils::TransformNodes::LoadSVG& other)
{
    TransformNode::operator=(other);
    fileName = other.fileName;
	return *this;
}

Ionflux::GeoUtils::TransformNodes::LoadSVG* LoadSVG::copy() const
{
    LoadSVG* newLoadSVG = create();
    *newLoadSVG = *this;
    return newLoadSVG;
}

Ionflux::GeoUtils::TransformNodes::LoadSVG* 
LoadSVG::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<LoadSVG*>(other);
}

Ionflux::GeoUtils::TransformNodes::LoadSVG* 
LoadSVG::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    LoadSVG* newObject = new LoadSVG();
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

}

/** \file LoadSVG.cpp
 * \brief Transform node: Load SVG implementation.
 */
