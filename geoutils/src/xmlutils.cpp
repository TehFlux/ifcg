/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * xmlutils.cpp                   XML utility functions (implementation).
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
#include <sstream>
#include "geoutils/geoutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils_private.hpp"
#include "geoutils/xmlio/MeshXMLFactory.hpp"

using namespace Ionflux::GeoUtils;
using namespace Ionflux::GeoUtils::XMLUtils;

namespace Ionflux
{

namespace GeoUtils
{

void getSVGPolygons(const std::string& fileName, 
    const Ionflux::ObjectBase::StringVector& elementIDs, 
    Ionflux::GeoUtils::Polygon3Set& target)
{
    Ionflux::ObjectBase::StringVector attrs;
    Ionflux::ObjectBase::XMLUtils::getAttrValues(
        fileName, "path", "d", elementIDs, attrs);
    for (Ionflux::ObjectBase::StringVector::const_iterator i = 
        attrs.begin(); i != attrs.end(); i++)
    {
        Polygon3* p0 = target.addPolygon();
        extractSVGVertices(*i, *p0->getVertexSource());
    }
}

// Initialize box bounds item from an XML element.
void getBoxBoundsItem(TiXmlElement* e0, 
    Ionflux::GeoUtils::BoxBoundsItem& target)
{
    const char* a1 = e0->Attribute("id");
    if (a1 == 0)
        throw GeoUtilsError("Box bounds item element does not have "
            "attribute 'id'.");
    target.setItemID(a1);
    a1 = e0->Attribute("center");
    if (a1 == 0)
        throw GeoUtilsError("Box bounds item element does not have "
            "attribute 'center'.");
    Vertex3 v0;
    extractXMLVertex(a1, v0);
    target.setCenter(v0.getVector());
    a1 = e0->Attribute("rvec");
    if (a1 == 0)
        throw GeoUtilsError("Box bounds item element does not have "
            "attribute 'rvec'.");
    extractXMLVertex(a1, v0);
    target.setRVec(v0.getVector());
    target.updateBounds();
}

// Initialize bounding box from an XML element.
void getBoundingBox(TiXmlElement* e0, Ionflux::GeoUtils::BoundingBox& target)
{
    const char* a0 = e0->Value();
    if (std::string(a0) != "bbox")
        throw GeoUtilsError("XML element is not a bounding box.");
    // Initialize bounding box.
    getBoxBoundsItem(e0, target);
    TiXmlElement* items0 = 
        Ionflux::ObjectBase::XMLUtils::findElementByName(
            e0, "items");
    if (items0 == 0)
        throw GeoUtilsError("Element 'items' not found.");
    // Iterate child elements.
    TiXmlElement* c0 = items0->FirstChildElement();
    while (c0 != 0)
    {
        const char* b0 = c0->Value();
        if (std::string(b0) == "bbox")
        {
            // Bounding box.
            BoundingBox* bb0 = BoundingBox::create();
            getBoundingBox(c0, *bb0);
            target.addItem(bb0);
        } else
        if (std::string(b0) == "bbitem")
        {
            // Box bounds item.
            BoxBoundsItem* bi0 = BoxBoundsItem::create();
            getBoxBoundsItem(c0, *bi0);
            target.addItem(bi0);
        } else
        if (std::string(b0) == "mesh")
        {
            // Mesh.
            Mesh* m0 = Mesh::create();
            MeshXMLFactory* xf = MeshXMLFactory::upcast(
                m0->getXMLObjectFactory());
            xf->initObject(c0, *m0, b0);
            target.addItem(m0);
        }
        c0 = c0->NextSiblingElement();
    }
}

void getBoundingBox(const std::string& fileName, const std::string& elementID, 
    Ionflux::GeoUtils::BoundingBox& target)
{
    std::ostringstream message;
    TiXmlDocument d0(fileName.c_str());
    if (!d0.LoadFile(TIXML_ENCODING_UTF8))
    {
        message << "Unable to read from file '" << fileName << "'.";
        throw GeoUtilsError(message.str());
    }
    TiXmlElement* b0 = 
        Ionflux::ObjectBase::XMLUtils::findElementByID(
            d0.RootElement(), "bbox", elementID);
    if (b0 == 0)
    {
        message << "Element 'bbox' with ID '" << elementID << "' not found.";
        throw GeoUtilsError(message.str());
    }
    getBoundingBox(b0, target);
}

}

}

/** \file xmlutils.cpp
 * \brief XML utility functions (implementation).
 */
