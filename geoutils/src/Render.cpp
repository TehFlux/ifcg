/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Render.cpp                      Transform node: Render to image 
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

#include "geoutils/Render.hpp"
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

RenderClassInfo::RenderClassInfo()
{
	name = "Render";
	desc = "Transform node: Render to image";
}

RenderClassInfo::~RenderClassInfo()
{
}

// public member constants
const unsigned int Render::INPUT_FIRST = 0;
const unsigned int Render::OUTPUT_COMPOSITE = 0;

// run-time type information instance constants
const RenderClassInfo Render::renderClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Render::CLASS_INFO = &Render::renderClassInfo;

Render::Render()
: image(0), axis(Ionflux::GeoUtils::AXIS_Z), closePath(true), originX(0), originY(0), backgroundColor(Ionflux::Altjira::Color::TRANSPARENT)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Render::Render(const Ionflux::GeoUtils::TransformNodes::Render& other)
: image(0), axis(Ionflux::GeoUtils::AXIS_Z), closePath(true), originX(0), originY(0), backgroundColor(Ionflux::Altjira::Color::TRANSPARENT)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Render::Render(Ionflux::GeoUtils::Image* initImage, 
Ionflux::GeoUtils::AxisID initAxis, bool initClosePath, const 
Ionflux::GeoUtils::SVGShapeStyleVector* initStyles, unsigned int initWidth,
unsigned int initHeight, unsigned int initOriginX, unsigned int 
initOriginY, const Ionflux::Altjira::Color& initBackgroundColor, const 
Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID), image(0), axis(initAxis), 
closePath(initClosePath), originX(initOriginX), originY(initOriginY), 
backgroundColor(initBackgroundColor)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setImage(initImage);
	if (initStyles != 0)
	    addStyles(*initStyles);
}

Render::~Render()
{
	clearStyles();
	// TODO: Nothing ATM. ;-)
}

void Render::process()
{
	clearInputGroups();
	if (image == 0)
	    throw GeoUtilsError("Image not set.");
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
	g0->flatten();
	if (backgroundColor.getAlpha() > 0.)
	    image->fill(backgroundColor);
	// Process polygons.
	Ionflux::GeoUtils::Polygon3Set ps0;
	bool ownDrawing = false;
	if (!image->drawingInProgress())
	{
	    ownDrawing = true;
	    image->begin();
	}
	for (unsigned int i = 0; i < g0->getNumItems(); i++)
	{
	    Ionflux::GeoUtils::TransformableObject* it0 = g0->getItem(i);
	    // Check for polygon.
	    Polygon3* p0 = Polygon3::upcast(it0);
	    if (p0 != 0)
	        ps0.addPolygon(p0);
	    else
	    {
	        // Check for SVG.
	        SVG* svg0 = SVG::upcast(it0);
	        if (svg0 != 0)
	            /* Render the SVG.
	               NOTE: Polygons are always rendered over SVG elements. 
	                     Find a solution that keeps the correct order. */
	            image->drawSVG(*svg0);
	    }
	}
	// Render polygons to image.
	image->drawPolygons(ps0, &styles, axis, closePath, originX, originY);
	if (ownDrawing)
	    image->finish();
	addOutput(g0);
}

std::string Render::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") 
	    << "; ";
	if (image != 0)
	    status << (*image);
	else
	    status << "<none>";
	return status.str();
}

void Render::addStyles(const Ionflux::GeoUtils::SVGShapeStyleVector& 
newStyles)
{
	for (Ionflux::GeoUtils::SVGShapeStyleVector::const_iterator i = 
	    newStyles.begin(); i != newStyles.end(); i++)
	    addStyle(*i);
}

void Render::setImage(Ionflux::GeoUtils::Image* newImage)
{
	if (image == newImage)
		return;
    if (newImage != 0)
        addLocalRef(newImage);
	if (image != 0)
		removeLocalRef(image);
	image = newImage;
}

Ionflux::GeoUtils::Image* Render::getImage() const
{
    return image;
}

unsigned int Render::getNumStyles() const
{
    return styles.size();
}

Ionflux::GeoUtils::SVGShapeStyle* Render::getStyle(unsigned int 
elementIndex) const
{
    if (elementIndex < styles.size())
		return styles[elementIndex];
	return 0;
}

int Render::findStyle(Ionflux::GeoUtils::SVGShapeStyle* needle, unsigned 
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

std::vector<Ionflux::GeoUtils::SVGShapeStyle*>& Render::getStyles()
{
    return styles;
}

void Render::addStyle(Ionflux::GeoUtils::SVGShapeStyle* addElement)
{
	styles.push_back(addElement);
}

void Render::removeStyle(Ionflux::GeoUtils::SVGShapeStyle* removeElement)
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

void Render::removeStyleIndex(unsigned int removeIndex)
{
    if (removeIndex > styles.size())
        return;
    styles.erase(styles.begin() + removeIndex);
}

void Render::clearStyles()
{
    styles.clear();
}

void Render::setAxis(Ionflux::GeoUtils::AxisID newAxis)
{
	axis = newAxis;
}

Ionflux::GeoUtils::AxisID Render::getAxis() const
{
    return axis;
}

void Render::setClosePath(bool newClosePath)
{
	closePath = newClosePath;
}

bool Render::getClosePath() const
{
    return closePath;
}

void Render::setOriginX(unsigned int newOriginX)
{
	originX = newOriginX;
}

unsigned int Render::getOriginX() const
{
    return originX;
}

void Render::setOriginY(unsigned int newOriginY)
{
	originY = newOriginY;
}

unsigned int Render::getOriginY() const
{
    return originY;
}

void Render::setBackgroundColor(const Ionflux::Altjira::Color& 
newBackgroundColor)
{
	backgroundColor = newBackgroundColor;
}

Ionflux::Altjira::Color Render::getBackgroundColor() const
{
    return backgroundColor;
}

Ionflux::GeoUtils::TransformNodes::Render& Render::operator=(const 
Ionflux::GeoUtils::TransformNodes::Render& other)
{
    TransformNode::operator=(other);
    setImage(other.image);
    styles = other.styles;
    axis = other.axis;
    closePath = other.closePath;
    originX = other.originX;
    originY = other.originY;
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Render* Render::copy() const
{
    Render* newRender = create();
    *newRender = *this;
    return newRender;
}

Ionflux::GeoUtils::TransformNodes::Render* 
Render::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Render*>(other);
}

Ionflux::GeoUtils::TransformNodes::Render* 
Render::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Render* newObject = new Render();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Render::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file Render.cpp
 * \brief Transform node: Render to image implementation.
 */
