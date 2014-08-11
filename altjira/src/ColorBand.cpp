/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ColorBand.cpp                   Color band (implementation).
 * =========================================================================
 * 
 * This file is part of Altjira - Ionflux' Image Processing Library.
 * 
 * Altjira - Ionflux' Image Processing Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
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

#include "altjira/ColorBand.hpp"
#include <sstream>
#include "ifmapping/utils.hpp"
#include "ifmapping/Piece.hpp"
#include "altjira/AltjiraError.hpp"
#include "altjira/ColorSet.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Altjira
{

ColorBandClassInfo::ColorBandClassInfo()
{
	name = "ColorBand";
	desc = "Color band";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

ColorBandClassInfo::~ColorBandClassInfo()
{
}

// run-time type information instance constants
const ColorBandClassInfo ColorBand::colorBandClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ColorBand::CLASS_INFO = &ColorBand::colorBandClassInfo;

ColorBand::ColorBand()
: red(0), green(0), blue(0), alpha(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ColorBand::ColorBand(const Ionflux::Altjira::ColorBand& other)
: red(0), green(0), blue(0), alpha(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ColorBand::ColorBand(Ionflux::Altjira::ColorStopVector initColorStops)
: red(0), green(0), blue(0), alpha(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	colorStops = initColorStops;
}

ColorBand::~ColorBand()
{
	clearColorStops();
	clearColorStops();
	if (red != 0)
	    removeLocalRef(red);
	red = 0;
	if (green != 0)
	    removeLocalRef(green);
	green = 0;
	if (blue != 0)
	    removeLocalRef(blue);
	blue = 0;
	if (alpha != 0)
	    removeLocalRef(alpha);
	alpha = 0;
}

void ColorBand::initMappings()
{
	if (red == 0)
	{
	    red = new Ionflux::Mapping::Piecewise();
	    addLocalRef(red);
	} else
	    red->clearPieces();
	if (green == 0)
	{
	    green = new Ionflux::Mapping::Piecewise();
	    addLocalRef(green);
	} else
	    green->clearPieces();
	if (blue == 0)
	{
	    blue = new Ionflux::Mapping::Piecewise();
	    addLocalRef(blue);
	} else
	    blue->clearPieces();
	if (alpha == 0)
	{
	    alpha = new Ionflux::Mapping::Piecewise();
	    addLocalRef(alpha);
	} else
	    alpha->clearPieces();
}

void ColorBand::clear()
{
	colorStops.clear();
	initMappings();
}

std::string ColorBand::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

void ColorBand::update()
{
	initMappings();
	if (colorStops.size() < 2)
	    return;
	for (unsigned int i = 0; i < (colorStops.size() - 1); i++)
	{
	    ColorStop c0 = colorStops[i];
	    ColorStop c1 = colorStops[i + 1];
	    double t = c0.param;
	    Ionflux::Mapping::Linear* ipr = 
	        new Ionflux::Mapping::Linear(
	            c0.color.getRed(), c1.color.getRed());
	    Ionflux::Mapping::Linear* ipg = 
	        new Ionflux::Mapping::Linear(
	            c0.color.getGreen(), c1.color.getGreen());
	    Ionflux::Mapping::Linear* ipb = 
	        new Ionflux::Mapping::Linear(
	            c0.color.getBlue(), c1.color.getBlue());
	    Ionflux::Mapping::Linear* ipa = 
	        new Ionflux::Mapping::Linear(
	            c0.color.getAlpha(), c1.color.getAlpha());
	    red->addPiece(new Ionflux::Mapping::Piece(ipr, t));
	    green->addPiece(new Ionflux::Mapping::Piece(ipg, t));
	    blue->addPiece(new Ionflux::Mapping::Piece(ipb, t));
	    alpha->addPiece(new Ionflux::Mapping::Piece(ipa, t));
	}
	ColorStop c = colorStops[colorStops.size() - 1];
	Ionflux::Mapping::Constant* cpr = 
	    new Ionflux::Mapping::Constant(c.color.getRed());
	Ionflux::Mapping::Constant* cpg = 
	    new Ionflux::Mapping::Constant(c.color.getGreen());
	Ionflux::Mapping::Constant* cpb = 
	    new Ionflux::Mapping::Constant(c.color.getBlue());
	Ionflux::Mapping::Constant* cpa = 
	    new Ionflux::Mapping::Constant(c.color.getAlpha());
	red->addPiece(new Ionflux::Mapping::Piece(cpr, 1.));
	green->addPiece(new Ionflux::Mapping::Piece(cpg, 1.));
	blue->addPiece(new Ionflux::Mapping::Piece(cpb, 1.));
	alpha->addPiece(new Ionflux::Mapping::Piece(cpa, 1.));
}

void ColorBand::eval(double value, Ionflux::Altjira::FloatColor& target)
{
	if (target.space != Ionflux::Altjira::Color::SPACE_RGB)
	{
	    FloatColor fc = createFloatColor(
	        (*red)(value), (*green)(value), (*blue)(value), 
	        (*alpha)(value), Ionflux::Altjira::Color::SPACE_RGB);
	    toColorSpace(fc, target.space);
	    target = fc;
	} else
	{
	    target.c0 = (*red)(value);
	    target.c1 = (*green)(value);
	    target.c2 = (*blue)(value);
	    target.alpha = (*alpha)(value);
	}
}

void ColorBand::eval(double value, Ionflux::Altjira::ByteColor& target)
{
	FloatColor fc;
	fc.space = target.space;
	eval(value, fc);
	floatToByte(fc, target);
}

void ColorBand::eval(double value, Ionflux::Altjira::Color& target)
{
	target.setRed((*red)(value));
	target.setGreen((*green)(value));
	target.setBlue((*blue)(value));
	target.setAlpha((*alpha)(value));
}

Ionflux::Altjira::Color ColorBand::operator()(double value)
{
	Ionflux::Altjira::Color result;
	eval(value, result);
	return result;
}

void ColorBand::sample(unsigned int numSamples, Ionflux::Altjira::ColorSet&
target)
{
	if (numSamples == 0)
	    return;
	double step = 1. / (numSamples - 1.);
	double v = 0.;
	for (unsigned int i = 0; i < numSamples; i++)
	{
	    Color* c0 = target.addColor();
	    eval(v, *c0);
	    v += step;
	}
}

Ionflux::Altjira::ColorBand* ColorBand::rainbow()
{
	ColorBand* result = create();
	ColorStop cs;
	cs.color = Ionflux::Altjira::Color::VIOLET;
	cs.param = 0.;
	result->addColorStop(cs);
	cs.color = Ionflux::Altjira::Color::BLUE;
	cs.param = 1. / 6.;
	result->addColorStop(cs);
	cs.color = Ionflux::Altjira::Color::CYAN;
	cs.param = 2. / 6.;
	result->addColorStop(cs);
	cs.color = Ionflux::Altjira::Color::GREEN;
	cs.param = 3. / 6.;
	result->addColorStop(cs);
	cs.color = Ionflux::Altjira::Color::YELLOW;
	cs.param = 4. / 6.;
	result->addColorStop(cs);
	cs.color = Ionflux::Altjira::Color::ORANGE;
	cs.param = 5. / 6.;
	result->addColorStop(cs);
	cs.color = Ionflux::Altjira::Color::RED;
	cs.param = 1.;
	result->addColorStop(cs);
	result->update();
	return result;
}

Ionflux::Altjira::ColorBand* ColorBand::flame()
{
	ColorBand* result = create();
	ColorStop cs;
	cs.color = Ionflux::Altjira::Color::BLACK;
	cs.param = 0.;
	result->addColorStop(cs);
	cs.color = Ionflux::Altjira::Color::RED;
	cs.param = 1. / 4.;
	result->addColorStop(cs);
	cs.color = Ionflux::Altjira::Color::ORANGE;
	cs.param = 1. / 2.;
	result->addColorStop(cs);
	cs.color = Ionflux::Altjira::Color::YELLOW;
	cs.param = 3. / 4.;
	result->addColorStop(cs);
	cs.color = Ionflux::Altjira::Color::WHITE;
	cs.param = 1.;
	result->addColorStop(cs);
	result->update();
	return result;
}

Ionflux::Altjira::ColorBand* ColorBand::ice()
{
	ColorBand* result = create();
	ColorStop cs;
	cs.color = Ionflux::Altjira::Color::BLUE;
	cs.param = 0.;
	result->addColorStop(cs);
	cs.color = Ionflux::Altjira::Color::CYAN;
	cs.param = 1. / 2.;
	result->addColorStop(cs);
	cs.color = Ionflux::Altjira::Color::WHITE;
	cs.param = 1.;
	result->addColorStop(cs);
	result->update();
	return result;
}

Ionflux::Altjira::ColorBand* ColorBand::terrain()
{
	ColorBand* result = create();
	ColorStop cs;
	// Dark blue (deep water).
	cs.color.setFromHex("#00048dff");
	cs.param = 0.;
	result->addColorStop(cs);
	// Light blue (water).
	cs.color.setFromHex("#015afbff");
	cs.param = 0.30;
	result->addColorStop(cs);
	// Cyan (coastal water).
	cs.color.setFromHex("#23c2fcff");
	cs.param = 0.34;
	result->addColorStop(cs);
	// Light green (shore).
	cs.color.setFromHex("#bae086ff");
	cs.param = 0.35;
	result->addColorStop(cs);
	// Grass green (coastal land).
	cs.color.setFromHex("#299e3bff");
	cs.param = 0.39;
	result->addColorStop(cs);
	// Forest green (inner land).
	cs.color.setFromHex("#0d751fff");
	cs.param = 0.56;
	result->addColorStop(cs);
	// Dark green (inner land, high).
	cs.color.setFromHex("#024500ff");
	cs.param = 0.70;
	result->addColorStop(cs);
	// Grey brown (hills).
	cs.color.setFromHex("#585144ff");
	cs.param = 0.87;
	result->addColorStop(cs);
	// Dark grey (mountains).
	cs.color.setFromHex("#544f46ff");
	cs.param = 0.95;
	result->addColorStop(cs);
	// Middle grey (high mountains).
	cs.color.setFromHex("#827f78ff");
	cs.param = 0.98;
	result->addColorStop(cs);
	// White (Snow).
	cs.color.setFromHex("#ffffffff");
	cs.param = 1.;
	result->addColorStop(cs);
	result->update();
	return result;
}

Ionflux::Altjira::ColorBand* ColorBand::heat()
{
	ColorBand* result = create();
	ColorStop cs;
	// Blue.
	cs.color.setFromHex("#0000ffff");
	cs.param = 0.;
	result->addColorStop(cs);
	// Cyan.
	cs.color.setFromHex("#0cb6ffff");
	cs.param = 0.2;
	result->addColorStop(cs);
	// Violet.
	cs.color.setFromHex("#8f68ffff");
	cs.param = 0.4;
	result->addColorStop(cs);
	// Red.
	cs.color.setFromHex("#ff0000ff");
	cs.param = 0.6;
	result->addColorStop(cs);
	// Yellow.
	cs.color.setFromHex("#ffec00ff");
	cs.param = 0.8;
	result->addColorStop(cs);
	// White.
	cs.color.setFromHex("#ffffffff");
	cs.param = 1.;
	result->addColorStop(cs);
	result->update();
	return result;
}

Ionflux::Altjira::ColorBand* ColorBand::glow(const Ionflux::Altjira::Color&
color, double maxL)
{
	ColorBand* result = create();
	FloatColor c0;
	c0.space = Color::SPACE_HSL;
	color.getFloatColor(c0);
	FloatColor c1 = c0;
	c1.alpha = 0.;
	FloatColor c2 = c0;
	c2.c2 = maxL;
	c2.alpha = color.getAlpha();
	ColorStop cs;
	cs.color = c1;
	cs.param = 0.;
	result->addColorStop(cs);
	cs.color = c2;
	cs.param = 1.;
	result->addColorStop(cs);
	/* <---- DEBUG ----- //
	std::cout << "[ColorBand::glow] DEBUG: c0 = " 
	    << Ionflux::Altjira::getString(c0) 
	    << ", c1 = " << Ionflux::Altjira::getString(c1) 
	    << ", c2 = " << Ionflux::Altjira::getString(c2) << std::endl;
	// ----- DEBUG ----> */
	result->update();
	return result;
}

unsigned int ColorBand::getNumColorStops() const
{
    return colorStops.size();
}

Ionflux::Altjira::ColorStop ColorBand::getColorStop(unsigned int 
elementIndex) const
{
    if (elementIndex < colorStops.size())
		return colorStops[elementIndex];
	return ColorStop();
}

int ColorBand::findColorStop(Ionflux::Altjira::ColorStop needle, unsigned 
int occurence) const
{
    bool found = false;
	Ionflux::Altjira::ColorStop currentColorStop = ColorStop();
	unsigned int i = 0;
	while (!found 
		&& (i < colorStops.size()))
	{
		currentColorStop = colorStops[i];
		if (currentColorStop == needle)
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

std::vector<Ionflux::Altjira::ColorStop>& ColorBand::getColorStops()
{
    return colorStops;
}

void ColorBand::addColorStop(Ionflux::Altjira::ColorStop addElement)
{
	colorStops.push_back(addElement);
}

void ColorBand::removeColorStop(Ionflux::Altjira::ColorStop removeElement)
{
    bool found = false;
	Ionflux::Altjira::ColorStop currentColorStop = ColorStop();
	unsigned int i = 0;
	while (!found 
		&& (i < colorStops.size()))
	{
		currentColorStop = colorStops[i];
		if (currentColorStop == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		colorStops.erase(colorStops.begin() + i);
	}
}

void ColorBand::removeColorStopIndex(unsigned int removeIndex)
{
    if (removeIndex > colorStops.size())
        return;
    colorStops.erase(colorStops.begin() + removeIndex);
}

void ColorBand::clearColorStops()
{
    colorStops.clear();
}

Ionflux::Altjira::ColorBand& ColorBand::operator=(const 
Ionflux::Altjira::ColorBand& other)
{
    ColorStopVector v0 = other.colorStops;
    for (ColorStopVector::const_iterator i = other.colorStops.begin(); 
        i != other.colorStops.end(); i++)
        v0.push_back(*i);
    clearColorStops();
    colorStops = v0;
	return *this;
}

Ionflux::Altjira::ColorBand* ColorBand::copy() const
{
    ColorBand* newColorBand = create();
    *newColorBand = *this;
    return newColorBand;
}

Ionflux::Altjira::ColorBand* 
ColorBand::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<ColorBand*>(other);
}

Ionflux::Altjira::ColorBand* 
ColorBand::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    ColorBand* newObject = new ColorBand();
    if (newObject == 0)
    {
        throw AltjiraError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Altjira::ColorBand* 
ColorBand::create(Ionflux::Altjira::ColorStopVector initColorStops, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    ColorBand* newObject = new ColorBand(initColorStops);
    if (newObject == 0)
    {
        throw AltjiraError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int ColorBand::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file ColorBand.cpp
 * \brief Color band implementation.
 */
