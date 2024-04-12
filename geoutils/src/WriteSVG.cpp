/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * WriteSVG.cpp                    Transform node: Write SVG 
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

#include "geoutils/WriteSVG.hpp"
#include "ifobject/IFLogMessage.hpp"
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

using namespace std;
using namespace Ionflux::ObjectBase;
using Ionflux::Mapping::defaultStr;

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

WriteSVGClassInfo::WriteSVGClassInfo()
{
	name = "WriteSVG";
	desc = "Transform node: Write SVG";
}

WriteSVGClassInfo::~WriteSVGClassInfo()
{
}

// public member constants
const unsigned int WriteSVG::INPUT_FIRST = 0;
const unsigned int WriteSVG::OUTPUT_COMPOSITE = 0;

// run-time type information instance constants
const WriteSVGClassInfo WriteSVG::writeSVGClassInfo;
const Ionflux::ObjectBase::IFClassInfo* WriteSVG::CLASS_INFO = &WriteSVG::writeSVGClassInfo;

WriteSVG::WriteSVG()
: fileName(""), elementIDPrefix("polygon"), axis(Ionflux::GeoUtils::AXIS_Z), shapeType(Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE), closePath(true), width(1000), height(1000), originX(500), originY(500), svgTemplate(Ionflux::GeoUtils::SVG_TEMPLATE)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

WriteSVG::WriteSVG(const Ionflux::GeoUtils::TransformNodes::WriteSVG& other)
: fileName(""), elementIDPrefix("polygon"), axis(Ionflux::GeoUtils::AXIS_Z), shapeType(Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE), closePath(true), width(1000), height(1000), originX(500), originY(500), svgTemplate(Ionflux::GeoUtils::SVG_TEMPLATE)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

WriteSVG::WriteSVG(const std::string& initFileName, const std::string& 
initElementIDPrefix, Ionflux::GeoUtils::AxisID initAxis, 
Ionflux::GeoUtils::SVGShapeType initShapeType, bool initClosePath, const 
Ionflux::GeoUtils::SVGShapeStyleVector* initStyles, unsigned int initWidth,
unsigned int initHeight, unsigned int initOriginX, unsigned int 
initOriginY, const std::string& initSVGTemplate, const 
Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID), fileName(initFileName), 
elementIDPrefix(initElementIDPrefix), axis(initAxis), 
shapeType(initShapeType), closePath(initClosePath), width(initWidth), 
height(initHeight), originX(initOriginX), originY(initOriginY), 
svgTemplate(initSVGTemplate)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initStyles != 0)
	    addStyles(*initStyles);
}

WriteSVG::~WriteSVG()
{
	clearStyles();
	// TODO: Nothing ATM. ;-)
}

void WriteSVG::process()
{
	clearInputGroups();
	if (fileName.size() == 0)
	    throw GeoUtilsError("Output file name not specified.");
	if (elementIDPrefix.size() == 0)
	    throw GeoUtilsError("No element ID prefix specified.");
	TransformableGroup* g0 = new TransformableGroup();
	if (g0 == 0)
	    throw GeoUtilsError("Could not allocate object.");
	// Add all input groups.
	/* <---- DEBUG ----- //
	log(IFLogMessage("Merging input groups...", VL_DEBUG, this, "process"));
	// ----- DEBUG ----> */
	for (Ionflux::GeoUtils::TransformableGroupVector::iterator i = 
	    inputCache.begin(); i != inputCache.end(); i++)
	{
	    TransformableGroup* o0 = *i;
	    g0->addItem(o0);
	}
	// Get polygons.
	/* <---- DEBUG ----- //
	log(IFLogMessage("Flattening groups...", VL_DEBUG, this, "process"));
	// ----- DEBUG ----> */
	g0->flatten();
	Ionflux::GeoUtils::Polygon3Set ps0;
	for (unsigned int i = 0; i < g0->getNumItems(); i++)
	{
	    Ionflux::GeoUtils::TransformableObject* it0 = g0->getItem(i);
	    Polygon3* p0 = Polygon3::upcast(it0);
	    if (p0 != 0)
	        ps0.addPolygon(p0);
	}
	// Create SVG code.
	/* <---- DEBUG ----- //
	log(IFLogMessage("Creating SVG...", VL_DEBUG, this, "process"));
	// ----- DEBUG ----> */
	std::string svg0 = ps0.getSVG(styles, elementIDPrefix, axis, 
	    shapeType, closePath);
	std::string svg1 = Ionflux::GeoUtils::getSVGImage(svg0, 
	    width, height, originX, originY, svgTemplate);
	// Write it to the file.
	ofstream f0;
	f0.open(fileName.c_str(), ios_base::out);
	f0 << svg1;
	addOutput(g0);
}

std::string WriteSVG::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") 
	    << "; " << defaultStr(fileName, "<none>") << "]";
	return status.str();
}

void WriteSVG::addStyles(const Ionflux::GeoUtils::SVGShapeStyleVector& 
newStyles)
{
	for (Ionflux::GeoUtils::SVGShapeStyleVector::const_iterator i = 
	    newStyles.begin(); i != newStyles.end(); i++)
	    addStyle(*i);
}

void WriteSVG::setFileName(const std::string& newFileName)
{
	fileName = newFileName;
}

std::string WriteSVG::getFileName() const
{
    return fileName;
}

unsigned int WriteSVG::getNumStyles() const
{
    return styles.size();
}

Ionflux::GeoUtils::SVGShapeStyle* WriteSVG::getStyle(unsigned int 
elementIndex) const
{
    if (elementIndex < styles.size())
		return styles[elementIndex];
	return 0;
}

int WriteSVG::findStyle(Ionflux::GeoUtils::SVGShapeStyle* needle, unsigned 
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

std::vector<Ionflux::GeoUtils::SVGShapeStyle*>& WriteSVG::getStyles()
{
    return styles;
}

void WriteSVG::addStyle(Ionflux::GeoUtils::SVGShapeStyle* addElement)
{
	styles.push_back(addElement);
}

void WriteSVG::removeStyle(Ionflux::GeoUtils::SVGShapeStyle* removeElement)
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

void WriteSVG::removeStyleIndex(unsigned int removeIndex)
{
    if (removeIndex > styles.size())
        return;
    styles.erase(styles.begin() + removeIndex);
}

void WriteSVG::clearStyles()
{
    styles.clear();
}

void WriteSVG::setElementIDPrefix(const std::string& newElementIDPrefix)
{
	elementIDPrefix = newElementIDPrefix;
}

std::string WriteSVG::getElementIDPrefix() const
{
    return elementIDPrefix;
}

void WriteSVG::setAxis(Ionflux::GeoUtils::AxisID newAxis)
{
	axis = newAxis;
}

Ionflux::GeoUtils::AxisID WriteSVG::getAxis() const
{
    return axis;
}

void WriteSVG::setShapeType(Ionflux::GeoUtils::SVGShapeType newShapeType)
{
	shapeType = newShapeType;
}

Ionflux::GeoUtils::SVGShapeType WriteSVG::getShapeType() const
{
    return shapeType;
}

void WriteSVG::setClosePath(bool newClosePath)
{
	closePath = newClosePath;
}

bool WriteSVG::getClosePath() const
{
    return closePath;
}

void WriteSVG::setWidth(unsigned int newWidth)
{
	width = newWidth;
}

unsigned int WriteSVG::getWidth() const
{
    return width;
}

void WriteSVG::setHeight(unsigned int newHeight)
{
	height = newHeight;
}

unsigned int WriteSVG::getHeight() const
{
    return height;
}

void WriteSVG::setOriginX(unsigned int newOriginX)
{
	originX = newOriginX;
}

unsigned int WriteSVG::getOriginX() const
{
    return originX;
}

void WriteSVG::setOriginY(unsigned int newOriginY)
{
	originY = newOriginY;
}

unsigned int WriteSVG::getOriginY() const
{
    return originY;
}

void WriteSVG::setSvgTemplate(const std::string& newSvgTemplate)
{
	svgTemplate = newSvgTemplate;
}

std::string WriteSVG::getSvgTemplate() const
{
    return svgTemplate;
}

Ionflux::GeoUtils::TransformNodes::WriteSVG& WriteSVG::operator=(const 
Ionflux::GeoUtils::TransformNodes::WriteSVG& other)
{
    TransformNode::operator=(other);
    fileName = other.fileName;
    styles = other.styles;
    elementIDPrefix = other.elementIDPrefix;
    axis = other.axis;
    shapeType = other.shapeType;
    closePath = other.closePath;
	return *this;
}

Ionflux::GeoUtils::TransformNodes::WriteSVG* WriteSVG::copy() const
{
    WriteSVG* newWriteSVG = create();
    *newWriteSVG = *this;
    return newWriteSVG;
}

Ionflux::GeoUtils::TransformNodes::WriteSVG* 
WriteSVG::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<WriteSVG*>(other);
}

Ionflux::GeoUtils::TransformNodes::WriteSVG* 
WriteSVG::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    WriteSVG* newObject = new WriteSVG();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int WriteSVG::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file WriteSVG.cpp
 * \brief Transform node: Write SVG implementation.
 */
