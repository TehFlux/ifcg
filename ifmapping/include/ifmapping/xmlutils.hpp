#ifndef IONFLUX_MAPPING_XMLUTILS
#define IONFLUX_MAPPING_XMLUTILS
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * xmlutils.hpp                     XML utility functions (header).
 * =========================================================================
 *
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFMapping - Ionflux Mapping Library is distributed in the hope 
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFMapping - Ionflux Mapping Library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */
#include <string>
#include "ifobject/types.hpp"

namespace Ionflux
{

namespace Mapping
{

class BezierSpline;
class AnimatedSpline;

/**
 * Get attribute value.
 *
 * Get the value of an attribute from an element, identified by an element 
 * ID, within a certain XML file.
 *
 * \param fileName File name.
 * \param elementName Element name.
 * \param elementID Element ID.
 * \param attrName Attribute name.
 *
 * \return Attribute value, or an empty string if the attribute is not found.
 */
std::string getAttrValue(const std::string& fileName, 
    const std::string& elementName, const std::string& elementID, 
    const std::string& attrName);

/**
 * Get attribute values.
 *
 * Get the values of a specified attribute from multiple elements, 
 * identified by a vector of element IDs, within a certain XML file.
 *
 * \param fileName File name.
 * \param elementName Element name.
 * \param attrName Attribute name.
 * \param elementIDs Element IDs.
 * \param target Where to store the extracted attributes.
 */
void getAttrValues(const std::string& fileName, 
    const std::string& elementName, const std::string& attrName, 
    const Ionflux::ObjectBase::StringVector& elementIDs, 
    Ionflux::ObjectBase::StringVector& target);

/**
 * Get Bezier spline frames from SVG file.
 *
 * Extract multiple bezier splines from an SVG path in the specified file. 
 * The splines are identified by element IDs from the specified vector. They 
 * are added as key splines to the specified animated bezier spline.
 *
 * \param fileName File name.
 * \param elementIDs Element IDs.
 * \param target Where to store the Bezier key spline data.
 */
void getSVGBezierSplineFrames(const std::string& fileName, 
    const Ionflux::ObjectBase::StringVector& elementIDs, 
    Ionflux::Mapping::AnimatedSpline& target);

}

}

/** \file xmlutils.hpp
 * \brief XML utility functions (header).
 */
#endif
