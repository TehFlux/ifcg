/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImageSource.cpp                 Image source (implementation).
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

#include "geoutils/ImageSource.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

ImageSourceClassInfo::ImageSourceClassInfo()
{
	name = "ImageSource";
	desc = "Image source";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

ImageSourceClassInfo::~ImageSourceClassInfo()
{
}

// run-time type information instance constants
const ImageSourceClassInfo ImageSource::imageSourceClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ImageSource::CLASS_INFO = &ImageSource::imageSourceClassInfo;

ImageSource::ImageSource()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ImageSource::ImageSource(const Ionflux::GeoUtils::ImageSource& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ImageSource::~ImageSource()
{
	// TODO: Nothing ATM. ;-)
}

std::string ImageSource::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

Ionflux::GeoUtils::ImageSource& ImageSource::operator=(const 
Ionflux::GeoUtils::ImageSource& other)
{
	return *this;
}

Ionflux::GeoUtils::ImageSource* 
ImageSource::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<ImageSource*>(other);
}

}

}

/** \file ImageSource.cpp
 * \brief Image source implementation.
 */
