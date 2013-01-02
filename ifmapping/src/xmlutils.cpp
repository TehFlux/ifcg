/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * xmlutils.cpp                   XML utility functions (implementation).
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
#include <sstream>
#include "ifmapping/utils.hpp"
#include "ifmapping/xmlutils.hpp"
#include "ifmapping/MappingError.hpp"
#include "ifmapping/BezierSpline.hpp"
#include "ifmapping/AnimatedSpline.hpp"
#define TIXML_USE_STL
#include "tinyxml/tinyxml.h"
#undef TIXML_USE_STL

using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

TiXmlElement* findElementByID(TiXmlElement* start, 
    const std::string& elementName, const std::string& elementID)
{
    if (start == 0)
        return 0;
    const char* a0 = start->Attribute("id");
    if (a0 != 0)
    {
        if (std::string(a0) == elementID)
            return start;
    }
    TiXmlElement* e1 = start->FirstChildElement();
    TiXmlElement* e0 = findElementByID(e1, elementName, elementID);
    while ((e0 == 0) 
        && (e1 != 0))
    {
        e1 = e1->NextSiblingElement();
        if (e1 != 0)
            e0 = findElementByID(e1, elementName, elementID);
    }
    return e0;
}

std::string getAttrValue(const std::string& fileName, 
    const std::string& elementName, const std::string& elementID, 
    const std::string& attrName)
{
    std::ostringstream message;
    TiXmlDocument d0(fileName.c_str());
    if (!d0.LoadFile(TIXML_ENCODING_UTF8))
    {
        message << "Unable to read from file '" << fileName << "'.";
        throw MappingError(message.str());
    }
    TiXmlElement* result = findElementByID(d0.RootElement(), 
        elementName, elementID);
    if (result != 0)
    {
        const char* a0 = result->Attribute(attrName.c_str());
        if (a0 != 0)
            return std::string(a0);
    }
    return "";
}

void getAttrValues(const std::string& fileName, 
    const std::string& elementName, const std::string& attrName, 
    const Ionflux::ObjectBase::StringVector& elementIDs, 
    Ionflux::ObjectBase::StringVector& target)
{
    TiXmlDocument d0(fileName.c_str());
    if (!d0.LoadFile(TIXML_ENCODING_UTF8))
    {
        std::ostringstream message;
        message << "Unable to read from file '" << fileName << "'.";
        throw MappingError(message.str());
    }
    for (StringVector::const_iterator i = elementIDs.begin(); 
        i != elementIDs.end(); i++)
    {
        std::string elementID = *i;
        TiXmlElement* result = findElementByID(d0.RootElement(), 
            elementName, elementID);
        if (result != 0)
        {
            const char* a0 = result->Attribute(attrName.c_str());
            if (a0 != 0)
                target.push_back(std::string(a0));
            else
            {
                std::ostringstream message;
                message << "Attribute '" << attrName 
                    << "' not found on element ID '" << elementID << "'.";
                throw MappingError(message.str());
            }
        }
    }
}

void getSVGBezierSplineFrames(const std::string& fileName, 
    const Ionflux::ObjectBase::StringVector& elementIDs, 
    Ionflux::Mapping::AnimatedSpline& target)
{
    if (elementIDs.size() == 0)
        return;
    StringVector attrs;
    getAttrValues(fileName, "path", "d", elementIDs, attrs);
    unsigned int numKeys = attrs.size();
    /* <---- DEBUG ----- //
    std::cerr << "[getSVGBezierSplineFrames] DEBUG: " 
    << "numKeys = " << numKeys << std::endl;
    // <---- DEBUG ----- */
    MappingValue dt = 1.;
    if (numKeys >= 2)
        dt = 1. / (numKeys - 1);
    MappingValue t = 0;
    for (StringVector::const_iterator i = attrs.begin(); 
        i != attrs.end(); i++)
    {
        BezierSplineKey* s0 = new Ionflux::Mapping::BezierSplineKey();
        s0->initFromSVG(*i);
        s0->setT(t);
        target.addKey(s0);
        t += dt;
    }
}

}

}

/** \file xmlutils.cpp
 * \brief XML utility functions (implementation).
 */
