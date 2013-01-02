/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Pattern.cpp                     Pattern (implementation).
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

#include "altjira/Pattern.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "altjira/AltjiraError.hpp"
#include "altjira/utils.hpp"
#include "altjira/imageutils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;
using namespace Ionflux::Altjira;

namespace Ionflux
{

namespace Altjira
{

PatternClassInfo::PatternClassInfo()
{
	name = "Pattern";
	desc = "Pattern";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

PatternClassInfo::~PatternClassInfo()
{
}

// run-time type information instance constants
const PatternClassInfo Pattern::patternClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Pattern::CLASS_INFO = &Pattern::patternClassInfo;

Pattern::Pattern()
: pattern(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Pattern::Pattern(const Ionflux::Altjira::Pattern& other)
: pattern(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Pattern::~Pattern()
{
	clear();
}

void Pattern::transform(cairo_matrix_t& m)
{
	if (pattern == 0)
	    throw AltjiraError("[Pattern::transform] "
	        "Pattern not set!");
	cairo_matrix_t m0;
	cairo_pattern_get_matrix(pattern, &m0);
	cairo_matrix_multiply(&m0, &m0, &m);
	cairo_pattern_set_matrix(pattern, &m0);
}

void Pattern::clear()
{
	if (pattern != 0)
	    cairo_pattern_destroy(pattern);
	pattern = 0;
}

void Pattern::translate(double tx, double ty)
{
	cairo_matrix_t m1;
	cairo_matrix_init_translate(&m1, tx, ty);
	transform(m1);
}

void Pattern::scale(double sx, double sy)
{
	cairo_matrix_t m1;
	cairo_matrix_init_scale(&m1, sx, sy);
	transform(m1);
}

void Pattern::rotate(double phi)
{
	cairo_matrix_t m1;
	cairo_matrix_init_rotate(&m1, phi);
	transform(m1);
}

std::string Pattern::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

Ionflux::Altjira::Pattern& Pattern::operator=(const 
Ionflux::Altjira::Pattern& other)
{
    if (pattern != other.pattern)
    {
        cairo_pattern_reference(other.pattern);
        clear();
        pattern = other.pattern;
    }
	return *this;
}

Ionflux::Altjira::Pattern* Pattern::copy() const
{
    Pattern* newPattern = create();
    *newPattern = *this;
    return newPattern;
}

Ionflux::Altjira::Pattern* Pattern::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Pattern*>(other);
}

Ionflux::Altjira::Pattern* Pattern::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Pattern* newObject = new Pattern();
    if (newObject == 0)
    {
        throw AltjiraError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file Pattern.cpp
 * \brief Pattern implementation.
 */
