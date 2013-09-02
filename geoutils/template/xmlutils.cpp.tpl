/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009 Jörn P. Meier
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
#include "geoutils/utils.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Polygon3Set.hpp"
#include "geoutils/Polygon3.hpp"
#include "geoutils/Mesh.hpp"
#include "geoutils/BoundingBox.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils_private.hpp"

namespace Ionflux
{

namespace GeoUtils
{

TiXmlElement* findElementByID(TiXmlElement* start, 
    const std::string& elementName, const std::string& elementID)
{
    if (start == 0)
        return 0;
    const char* a0 = start->Attribute("id");
    if (a0 != 0)
    {
        const char* b0 = start->Value();
        if ((std::string(a0) == elementID) 
            && (std::string(b0) == elementName))
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

TiXmlElement* findElementByName(TiXmlElement* start, 
    const std::string& elementName)
{
    if (start == 0)
        return 0;
    const char* a0 = start->Value();
    if (std::string(a0) == elementName)
        return start;
    TiXmlElement* e0 = start->FirstChildElement();
    if (e0 != 0)
        a0 = e0->Value();
    while ((e0 != 0) 
        && (std::string(a0) != elementName))
    {
        e0 = e0->NextSiblingElement();
        if (e0 != 0)
            a0 = e0->Value();
    }
    return e0;
}

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

// Initialize mesh from an XML element.
void getMesh_legacy(TiXmlElement* e0, Ionflux::GeoUtils::Mesh& target)
{
    std::ostringstream message;
    const char* a0 = e0->Value();
    if (std::string(a0) != "mesh")
        throw GeoUtilsError("XML element is not a mesh.");
    TiXmlElement* v0 = findElementByName(e0, "vertices");
    if (v0 == 0)
    {
        message << "Element 'vertices' not found.";
        throw GeoUtilsError(message.str());
    }
    TiXmlElement* f0 = findElementByName(e0, "faces");
    if (f0 == 0)
    {
        message << "Element 'faces' not found.";
        throw GeoUtilsError(message.str());
    }
    TiXmlElement* vs0e = findElementByName(v0, "vertex3set");
    if (vs0e == 0)
    {
        message << "Element 'vertex3set' not found.";
        throw GeoUtilsError(message.str());
    }
    const char* d1 = vs0e->Attribute("d");
    if (d1 == 0)
    {
        message << "Element 'vertex3set' does not have attribute 'd'.";
        throw GeoUtilsError(message.str());
    }
    Vertex3Set* vs0 = Vertex3Set::create();
    extractXMLVertices(d1, *vs0);
    TiXmlElement* f1 = f0->FirstChildElement();
    FaceVector fv0;
    while (f1 != 0)
    {
        const char* a0 = f1->Value();
        if (std::string(a0) == "f")
        {
            a0 = f1->Attribute("d");
            if (a0 == 0)
            {
                message << "Element 'f' does not have attribute 'd'.";
                throw GeoUtilsError(message.str());
            }
            std::string vertexData(a0);
            a0 = f1->Attribute("uv");
            if (a0 == 0)
            {
                message << "Element 'f' does not have attribute 'uv'.";
                throw GeoUtilsError(message.str());
            }
            std::string texCoordData(a0);
            Face* f2 = Face::create();
            f2->setFromXMLData(vertexData, texCoordData);
            fv0.push_back(f2);
        }
        f1 = f1->NextSiblingElement();
    }
    target.setVertexSource(vs0);
    target.addFaces(fv0);
    target.update();
}

void getMesh_legacy(const std::string& fileName, const std::string& elementID, 
    Ionflux::GeoUtils::Mesh& target)
{
    std::ostringstream message;
    TiXmlDocument d0(fileName.c_str());
    if (!d0.LoadFile(TIXML_ENCODING_UTF8))
    {
        message << "Unable to read from file '" << fileName << "'.";
        throw GeoUtilsError(message.str());
    }
    TiXmlElement* m0 = findElementByID(d0.RootElement(), "mesh", elementID);
    if (m0 == 0)
    {
        message << "Element 'mesh' with ID '" << elementID << "' not found.";
        throw GeoUtilsError(message.str());
    }
    getMesh_legacy(m0, target);
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
    TiXmlElement* items0 = findElementByName(e0, "items");
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
            getMesh_legacy(c0, *m0);
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
    TiXmlElement* b0 = findElementByID(d0.RootElement(), "bbox", elementID);
    if (b0 == 0)
    {
        message << "Element 'bbox' with ID '" << elementID << "' not found.";
        throw GeoUtilsError(message.str());
    }
    getBoundingBox(b0, target);
}

// Initialize vertex set from an XML element.
void getVertex3Set_legacy(TiXmlElement* e0, Ionflux::GeoUtils::Vertex3Set& target)
{
    std::ostringstream message;
    const char* a0 = e0->Value();
    if (std::string(a0) != "vertex3set")
        throw GeoUtilsError("[getVertex3Set] "
            "XML element is not a vertex set.");
    const char* d0 = e0->Attribute("d");
    if (d0 == 0)
    {
        message << "[getVertex3Set] "
            "Element 'vertex3set' does not have attribute 'd'.";
        throw GeoUtilsError(message.str());
    }
    extractXMLVertices(d0, target);
}

void getVertex3Set_legacy(const std::string& fileName, const std::string& elementID, 
    Ionflux::GeoUtils::Vertex3Set& target)
{
    std::ostringstream message;
    TiXmlDocument d0(fileName.c_str());
    if (!d0.LoadFile(TIXML_ENCODING_UTF8))
    {
        message << "[getVertex3Set] "
            "Unable to read from file '" << fileName << "'.";
        throw GeoUtilsError(message.str());
    }
    TiXmlElement* m0 = findElementByID(d0.RootElement(), "vertex3set", 
        elementID);
    if (m0 == 0)
    {
        message << "[getVertex3Set] "
            "Element 'vertex3set' with ID '" << elementID << "' not found.";
        throw GeoUtilsError(message.str());
    }
    getVertex3Set_legacy(m0, target);
}

}

}

$Vector
$Vector2
$Vector3
$Vector4
$TransformableObject
$Vertex3
$Vertex3Set
$Face
$Mesh

/** \file xmlutils.cpp
 * \brief XML utility functions (implementation).
 */
