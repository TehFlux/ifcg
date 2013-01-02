/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * WritePNG.cpp                    Transform node: Write PNG 
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

#include "geoutils/WritePNG.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "ifmapping/utils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/Polygon3Set.hpp"
#include "geoutils/Polygon3.hpp"
#include "geoutils/Image.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;
using Ionflux::Mapping::defaultStr;

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

WritePNGClassInfo::WritePNGClassInfo()
{
	name = "WritePNG";
	desc = "Transform node: Write PNG";
}

WritePNGClassInfo::~WritePNGClassInfo()
{
}

// public member constants
const unsigned int WritePNG::INPUT_FIRST = 0;
const unsigned int WritePNG::OUTPUT_COMPOSITE = 0;

// run-time type information instance constants
const WritePNGClassInfo WritePNG::writePNGClassInfo;
const Ionflux::ObjectBase::IFClassInfo* WritePNG::CLASS_INFO = &WritePNG::writePNGClassInfo;

WritePNG::WritePNG()
: fileName(""), axis(Ionflux::GeoUtils::AXIS_Z), closePath(true), width(1000), height(1000), originX(0), originY(0), backgroundColor(Ionflux::Altjira::Color::TRANSPARENT)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

WritePNG::WritePNG(const Ionflux::GeoUtils::TransformNodes::WritePNG& other)
: fileName(""), axis(Ionflux::GeoUtils::AXIS_Z), closePath(true), width(1000), height(1000), originX(0), originY(0), backgroundColor(Ionflux::Altjira::Color::TRANSPARENT)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

WritePNG::WritePNG(const std::string& initFileName, 
Ionflux::GeoUtils::AxisID initAxis, bool initClosePath, const 
Ionflux::GeoUtils::SVGShapeStyleVector* initStyles, unsigned int initWidth,
unsigned int initHeight, unsigned int initOriginX, unsigned int 
initOriginY, const Ionflux::Altjira::Color& initBackgroundColor, const 
Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID), fileName(initFileName), axis(initAxis), 
closePath(initClosePath), width(initWidth), height(initHeight), 
originX(initOriginX), originY(initOriginY), 
backgroundColor(initBackgroundColor)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initStyles != 0)
	    addStyles(*initStyles);
}

WritePNG::~WritePNG()
{
	clearStyles();
	// TODO: Nothing ATM. ;-)
}

void WritePNG::process()
{
	clearInputGroups();
	if (fileName.size() == 0)
	    throw GeoUtilsError("Output file name not specified.");
	TransformableGroup* g0 = new TransformableGroup();
	if (g0 == 0)
	    throw GeoUtilsError("Could not allocate object.");
	// Add all input groups.
	for (Ionflux::GeoUtils::TransformableGroupVector::iterator i = 
	    inputCache.begin(); i != inputCache.end(); i++)
	{
	    TransformableGroup* o0 = *i;
	    g0->addItem(o0);
	}
	// Get polygons.
	g0->flatten();
	Ionflux::GeoUtils::Polygon3Set ps0;
	for (unsigned int i = 0; i < g0->getNumItems(); i++)
	{
	    Ionflux::GeoUtils::TransformableObject* it0 = g0->getItem(i);
	    Polygon3* p0 = Polygon3::upcast(it0);
	    if (p0 != 0)
	        ps0.addPolygon(p0);
	}
	// Render polygons to image.
	Ionflux::GeoUtils::Image i0(width, height);
	i0.begin();
	if (backgroundColor.getAlpha() > 0.)
	    i0.fill(backgroundColor);
	i0.drawPolygons(ps0, &styles, axis, closePath, originX, originY);
	i0.finish();
	// Write it to file.
	i0.writeToFile(fileName);
	addOutput(g0);
}

std::string WritePNG::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") 
	    << "; " << defaultStr(fileName, "<none>") << "]";
	return status.str();
}

void WritePNG::addStyles(const Ionflux::GeoUtils::SVGShapeStyleVector& 
newStyles)
{
	for (Ionflux::GeoUtils::SVGShapeStyleVector::const_iterator i = 
	    newStyles.begin(); i != newStyles.end(); i++)
	    addStyle(*i);
}

void WritePNG::setFileName(const std::string& newFileName)
{
	fileName = newFileName;
}

std::string WritePNG::getFileName() const
{
	return fileName;
}

unsigned int WritePNG::getNumStyles() const
{
    return styles.size();
}

Ionflux::GeoUtils::SVGShapeStyle* WritePNG::getStyle(unsigned int 
elementIndex) const
{
    if (elementIndex < styles.size())
		return styles[elementIndex];
	return 0;
}

int WritePNG::findStyle(Ionflux::GeoUtils::SVGShapeStyle* needle, unsigned 
int occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::SVGShapeStyle* currentStyle = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < styles.size()))
	{
		currentStyle = styles[i];
		if (currentStyle == needle)
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

std::vector<Ionflux::GeoUtils::SVGShapeStyle*>& WritePNG::getStyles()
{
    return styles;
}

void WritePNG::addStyle(Ionflux::GeoUtils::SVGShapeStyle* addElement)
{
	styles.push_back(addElement);
}

void WritePNG::removeStyle(Ionflux::GeoUtils::SVGShapeStyle* removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::SVGShapeStyle* currentStyle = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < styles.size()))
	{
		currentStyle = styles[i];
		if (currentStyle == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		styles.erase(styles.begin() + i);
	}
}

void WritePNG::removeStyleIndex(unsigned int removeIndex)
{
    if (removeIndex > styles.size())
        return;
    styles.erase(styles.begin() + removeIndex);
}

void WritePNG::clearStyles()
{
    styles.clear();
}

void WritePNG::setAxis(Ionflux::GeoUtils::AxisID newAxis)
{
	axis = newAxis;
}

Ionflux::GeoUtils::AxisID WritePNG::getAxis() const
{
	return axis;
}

void WritePNG::setClosePath(bool newClosePath)
{
	closePath = newClosePath;
}

bool WritePNG::getClosePath() const
{
	return closePath;
}

void WritePNG::setWidth(unsigned int newWidth)
{
	width = newWidth;
}

unsigned int WritePNG::getWidth() const
{
	return width;
}

void WritePNG::setHeight(unsigned int newHeight)
{
	height = newHeight;
}

unsigned int WritePNG::getHeight() const
{
	return height;
}

void WritePNG::setOriginX(unsigned int newOriginX)
{
	originX = newOriginX;
}

unsigned int WritePNG::getOriginX() const
{
	return originX;
}

void WritePNG::setOriginY(unsigned int newOriginY)
{
	originY = newOriginY;
}

unsigned int WritePNG::getOriginY() const
{
	return originY;
}

void WritePNG::setBackgroundColor(const Ionflux::Altjira::Color& 
newBackgroundColor)
{
	backgroundColor = newBackgroundColor;
}

Ionflux::Altjira::Color WritePNG::getBackgroundColor() const
{
	return backgroundColor;
}

Ionflux::GeoUtils::TransformNodes::WritePNG& WritePNG::operator=(const 
Ionflux::GeoUtils::TransformNodes::WritePNG& other)
{
    TransformNode::operator=(other);
    fileName = other.fileName;
    styles = other.styles;
    axis = other.axis;
    closePath = other.closePath;
    width = other.width;
    height = other.height;
    originX = other.originX;
    originY = other.originY;
	return *this;
}

Ionflux::GeoUtils::TransformNodes::WritePNG* WritePNG::copy() const
{
    WritePNG* newWritePNG = create();
    *newWritePNG = *this;
    return newWritePNG;
}

Ionflux::GeoUtils::TransformNodes::WritePNG* 
WritePNG::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<WritePNG*>(other);
}

Ionflux::GeoUtils::TransformNodes::WritePNG* 
WritePNG::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    WritePNG* newObject = new WritePNG();
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

/** \file WritePNG.cpp
 * \brief Transform node: Write PNG implementation.
 */
