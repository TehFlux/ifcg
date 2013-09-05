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

using namespace Ionflux::GeoUtils;
using namespace Ionflux::GeoUtils::XMLUtils;

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
            f2->setFromXMLData_legacy(vertexData, texCoordData);
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

#include "geoutils/Vector.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Vector* createVector(TiXmlElement* e0, const 
std::string& elementName)
{
    std::string en0(e0->Value());
    Vector* o0 = 0;
    if (en0 == elementName)
    {
        // default (Vector)
        o0 = Vector::create();
        getVector(e0, *o0, en0);
    } else
    if (en0 == Vector2::XML_ELEMENT_NAME)
    {
        // Vector2
        Vector2* o1 = Vector2::create();
        getVector2(e0, *o1, en0);
        o0 = o1;
    } else
    if (en0 == Vector3::XML_ELEMENT_NAME)
    {
        // Vector3
        Vector3* o1 = Vector3::create();
        getVector3(e0, *o1, en0);
        o0 = o1;
    } else
    if (en0 == Vector4::XML_ELEMENT_NAME)
    {
        // Vector4
        Vector4* o1 = Vector4::create();
        getVector4(e0, *o1, en0);
        o0 = o1;
    } else
    {
        std::ostringstream status;
        status << "[createVector] "
            << "Unexpected child element name: '" << en0 << "'";
        throw Ionflux::ObjectBase::IFError(status.str());
    }
    return o0;
}

void getVector(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector& target, const std::string& elementName)
{
    Ionflux::ObjectBase::XMLUtils::checkElementNameOrError(e0, 
        elementName, "getVector");
    Ionflux::ObjectBase::XMLUtils::getObject(e0, target);
    // Get element attribute data.
    std::string a0;
    a0 = Ionflux::ObjectBase::XMLUtils::getAttributeValue(
        e0, "d", true);
    Ionflux::ObjectBase::DoubleVector dv0;
    Ionflux::ObjectBase::vectorFromList(a0, dv0);
    target.setElements(dv0);
}

void getVector(const std::string& data, Ionflux::GeoUtils::Vector& target)
{
    TiXmlDocument d0;
    
    std::string d1(data);
    d1.append(1, ' ');
    if (!d0.Parse(d1.c_str(), 0, TIXML_ENCODING_UTF8))
        throw ("[getVector] "
            "Unable to parse XML data.");
    TiXmlElement* m0 = 
        Ionflux::ObjectBase::XMLUtils::findElementByNameOrError(
            d0.RootElement(), 
            Ionflux::GeoUtils::Vector::XML_ELEMENT_NAME);
    getVector(m0, target);
}

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

template<>
void getObject0<Ionflux::GeoUtils::Vector>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector& target, const std::string& elementName)
{
    
    if (elementName.size() == 0)
        Ionflux::GeoUtils::XMLUtils::getVector(e0, target);
    else
        Ionflux::GeoUtils::XMLUtils::getVector(e0, target, elementName);
}

template<>
void getObjVector<Ionflux::GeoUtils::Vector,
    Ionflux::GeoUtils::Vector*>(TiXmlElement* e0, 
    std::vector<Ionflux::GeoUtils::Vector*>& target, 
    const std::string& elementName, 
    const std::string& childElementName)
{
    checkElementNameOrError(e0, elementName, 
        "getObjVector<Vector>");
    TiXmlElement* ce0 = e0->FirstChildElement();
    while (ce0 != 0)
    {
        // Iterate over vector entries.
        std::string en0(ce0->Value());
        if (en0 == childElementName)
        {
            // default (Vector)
            Ionflux::GeoUtils::Vector* co0 = 
                Ionflux::GeoUtils::Vector::create();
            getObject0(ce0, *co0, childElementName);
            target.push_back(co0);
        } else
        if (en0 == 
            Vector2::XML_ELEMENT_NAME)
        {
            // Vector2
            Vector2* co0 = 
                Vector2::create();
            getObject0(ce0, *co0, childElementName);
            target.push_back(co0);
        } else
        if (en0 == 
            Vector3::XML_ELEMENT_NAME)
        {
            // Vector3
            Vector3* co0 = 
                Vector3::create();
            getObject0(ce0, *co0, childElementName);
            target.push_back(co0);
        } else
        if (en0 == 
            Vector4::XML_ELEMENT_NAME)
        {
            // Vector4
            Vector4* co0 = 
                Vector4::create();
            getObject0(ce0, *co0, childElementName);
            target.push_back(co0);
        } else
        {
            std::ostringstream status;
            status << "[getObjVector<Vector>] "
                << "Unexpected child element name: '" << en0 << "'";
            throw Ionflux::ObjectBase::IFError(status.str());
        }
        ce0 = ce0->NextSiblingElement();
    }
}

template<>
void getObjMap<Ionflux::GeoUtils::Vector,
    Ionflux::GeoUtils::Vector*>(TiXmlElement* e0, 
    std::map<std::string, Ionflux::GeoUtils::Vector*>& target, 
    const std::string& elementName, 
    const std::string& childElementName)
{
    checkElementNameOrError(e0, elementName, "getObjMap<Vector>");
    TiXmlElement* ee0 = e0->FirstChildElement();
    while (ee0 != 0)
    {
        // Iterate over map entries.
        std::string en0(ee0->Value());
        if (en0 == "entry")
        {
            std::string k = getAttributeValue(ee0, "key", false);
            TiXmlElement* ce0 = ee0->FirstChildElement();
            if (ce0 == 0)
            {
                std::ostringstream status;
                status << "[getObjMap<Vector>] "
                    << "Missing value for key: '" << k << "'";
                throw Ionflux::ObjectBase::IFError(status.str());
            }
            std::string en1(ce0->Value());
            Ionflux::GeoUtils::Vector* co0 = 0;
            // Add an object of the appropriate class. 
            if (en1 == childElementName)
            {
                // default (Vector)
                co0 = Ionflux::GeoUtils::Vector::create();
                getObject0(ce0, *co0, childElementName);
            } else
            if (en1 == 
                Vector2::XML_ELEMENT_NAME)
            {
                // Vector2
                Vector2* co1 = 
                    Vector2::create();
                getObject0(ce0, *co0, childElementName);
                co0 = co1;
            } else
            if (en1 == 
                Vector3::XML_ELEMENT_NAME)
            {
                // Vector3
                Vector3* co1 = 
                    Vector3::create();
                getObject0(ce0, *co0, childElementName);
                co0 = co1;
            } else
            if (en1 == 
                Vector4::XML_ELEMENT_NAME)
            {
                // Vector4
                Vector4* co1 = 
                    Vector4::create();
                getObject0(ce0, *co0, childElementName);
                co0 = co1;
            } else
            {
                std::ostringstream status;
                status << "[getObjMap<Vector>] "
                    << "Unexpected child element name: '" << en1 << "'";
                throw Ionflux::ObjectBase::IFError(status.str());
            }
            typename std::map<std::string, 
                Ionflux::GeoUtils::Vector*>::iterator j = target.find(k);
            if (j != target.end())
            {
                std::ostringstream status;
                status << "[getObjMap<Vector>] Duplicate key: '" 
                    << k << "'";
                throw Ionflux::ObjectBase::IFError(status.str());
            }
            target[k] = co0;
        }
        ee0 = ee0->NextSiblingElement();
    }
}

}

}

}

#include "geoutils/Vector2.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Vector2* createVector2(TiXmlElement* e0, const 
std::string& elementName)
{
    std::string en0(e0->Value());
    Vector2* o0 = 0;
    if (en0 == elementName)
    {
        // default (Vector2)
        o0 = Vector2::create();
        getVector2(e0, *o0, en0);
    } else
    {
        std::ostringstream status;
        status << "[createVector2] "
            << "Unexpected child element name: '" << en0 << "'";
        throw Ionflux::ObjectBase::IFError(status.str());
    }
    return o0;
}

void getVector2(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector2& target, const std::string& elementName)
{
    Ionflux::ObjectBase::XMLUtils::checkElementNameOrError(e0, 
        elementName, "getVector2");
    getVector(e0, target, elementName);
}

void getVector2(const std::string& data, Ionflux::GeoUtils::Vector2& target)
{
    TiXmlDocument d0;
    
    std::string d1(data);
    d1.append(1, ' ');
    if (!d0.Parse(d1.c_str(), 0, TIXML_ENCODING_UTF8))
        throw ("[getVector2] "
            "Unable to parse XML data.");
    TiXmlElement* m0 = 
        Ionflux::ObjectBase::XMLUtils::findElementByNameOrError(
            d0.RootElement(), 
            Ionflux::GeoUtils::Vector2::XML_ELEMENT_NAME);
    getVector2(m0, target);
}

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

template<>
void getObject0<Ionflux::GeoUtils::Vector2>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector2& target, const std::string& elementName)
{
    
    if (elementName.size() == 0)
        Ionflux::GeoUtils::XMLUtils::getVector2(e0, target);
    else
        Ionflux::GeoUtils::XMLUtils::getVector2(e0, target, elementName);
}

}

}

}

#include "geoutils/Vector3.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Vector3* createVector3(TiXmlElement* e0, const 
std::string& elementName)
{
    std::string en0(e0->Value());
    Vector3* o0 = 0;
    if (en0 == elementName)
    {
        // default (Vector3)
        o0 = Vector3::create();
        getVector3(e0, *o0, en0);
    } else
    {
        std::ostringstream status;
        status << "[createVector3] "
            << "Unexpected child element name: '" << en0 << "'";
        throw Ionflux::ObjectBase::IFError(status.str());
    }
    return o0;
}

void getVector3(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector3& target, const std::string& elementName)
{
    Ionflux::ObjectBase::XMLUtils::checkElementNameOrError(e0, 
        elementName, "getVector3");
    getVector(e0, target, elementName);
}

void getVector3(const std::string& data, Ionflux::GeoUtils::Vector3& target)
{
    TiXmlDocument d0;
    
    std::string d1(data);
    d1.append(1, ' ');
    if (!d0.Parse(d1.c_str(), 0, TIXML_ENCODING_UTF8))
        throw ("[getVector3] "
            "Unable to parse XML data.");
    TiXmlElement* m0 = 
        Ionflux::ObjectBase::XMLUtils::findElementByNameOrError(
            d0.RootElement(), 
            Ionflux::GeoUtils::Vector3::XML_ELEMENT_NAME);
    getVector3(m0, target);
}

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

template<>
void getObject0<Ionflux::GeoUtils::Vector3>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector3& target, const std::string& elementName)
{
    
    if (elementName.size() == 0)
        Ionflux::GeoUtils::XMLUtils::getVector3(e0, target);
    else
        Ionflux::GeoUtils::XMLUtils::getVector3(e0, target, elementName);
}

}

}

}

#include "geoutils/Vector4.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Vector4* createVector4(TiXmlElement* e0, const 
std::string& elementName)
{
    std::string en0(e0->Value());
    Vector4* o0 = 0;
    if (en0 == elementName)
    {
        // default (Vector4)
        o0 = Vector4::create();
        getVector4(e0, *o0, en0);
    } else
    {
        std::ostringstream status;
        status << "[createVector4] "
            << "Unexpected child element name: '" << en0 << "'";
        throw Ionflux::ObjectBase::IFError(status.str());
    }
    return o0;
}

void getVector4(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector4& target, const std::string& elementName)
{
    Ionflux::ObjectBase::XMLUtils::checkElementNameOrError(e0, 
        elementName, "getVector4");
    getVector(e0, target, elementName);
}

void getVector4(const std::string& data, Ionflux::GeoUtils::Vector4& target)
{
    TiXmlDocument d0;
    
    std::string d1(data);
    d1.append(1, ' ');
    if (!d0.Parse(d1.c_str(), 0, TIXML_ENCODING_UTF8))
        throw ("[getVector4] "
            "Unable to parse XML data.");
    TiXmlElement* m0 = 
        Ionflux::ObjectBase::XMLUtils::findElementByNameOrError(
            d0.RootElement(), 
            Ionflux::GeoUtils::Vector4::XML_ELEMENT_NAME);
    getVector4(m0, target);
}

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

template<>
void getObject0<Ionflux::GeoUtils::Vector4>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector4& target, const std::string& elementName)
{
    
    if (elementName.size() == 0)
        Ionflux::GeoUtils::XMLUtils::getVector4(e0, target);
    else
        Ionflux::GeoUtils::XMLUtils::getVector4(e0, target, elementName);
}

}

}

}

#include "geoutils/VectorSet.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::VectorSet* createVectorSet(TiXmlElement* e0, const 
std::string& elementName)
{
    std::string en0(e0->Value());
    VectorSet* o0 = 0;
    if (en0 == elementName)
    {
        // default (VectorSet)
        o0 = VectorSet::create();
        getVectorSet(e0, *o0, en0);
    } else
    if (en0 == FaceData::XML_ELEMENT_NAME)
    {
        // FaceData
        FaceData* o1 = FaceData::create();
        getFaceData(e0, *o1, en0);
        o0 = o1;
    } else
    {
        std::ostringstream status;
        status << "[createVectorSet] "
            << "Unexpected child element name: '" << en0 << "'";
        throw Ionflux::ObjectBase::IFError(status.str());
    }
    return o0;
}

void getVectorSet(TiXmlElement* e0, 
    Ionflux::GeoUtils::VectorSet& target, const std::string& elementName)
{
    Ionflux::ObjectBase::XMLUtils::checkElementNameOrError(e0, 
        elementName, "getVectorSet");
    Ionflux::ObjectBase::XMLUtils::getObject(e0, target);
    // Get child data.
    TiXmlElement* ce0 = e0->FirstChildElement();
    while (ce0 != 0)
    {
        std::string en0(ce0->Value());
        std::string pName = 
            Ionflux::ObjectBase::XMLUtils::getAttributeValue(
                ce0, "pname", true);
        // Property: vectors (vector[object])
        if ((pName == "vectors") 
            && (en0 == "vectorvec"))
        {
            std::vector<Ionflux::GeoUtils::Vector*> pv0;
            Ionflux::ObjectBase::XMLUtils::getObjVector<
                    Ionflux::GeoUtils::Vector, 
                    Ionflux::GeoUtils::Vector*>(ce0, pv0, 
                "vectorvec", 
                Ionflux::GeoUtils::Vector::XML_ELEMENT_NAME);
            target.addVectors(pv0);
        }
        ce0 = ce0->NextSiblingElement();
    }
}

void getVectorSet(const std::string& data, Ionflux::GeoUtils::VectorSet& target)
{
    TiXmlDocument d0;
    
    std::string d1(data);
    d1.append(1, ' ');
    if (!d0.Parse(d1.c_str(), 0, TIXML_ENCODING_UTF8))
        throw ("[getVectorSet] "
            "Unable to parse XML data.");
    TiXmlElement* m0 = 
        Ionflux::ObjectBase::XMLUtils::findElementByNameOrError(
            d0.RootElement(), 
            Ionflux::GeoUtils::VectorSet::XML_ELEMENT_NAME);
    getVectorSet(m0, target);
}

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

template<>
void getObject0<Ionflux::GeoUtils::VectorSet>(TiXmlElement* e0, 
    Ionflux::GeoUtils::VectorSet& target, const std::string& elementName)
{
    
    if (elementName.size() == 0)
        Ionflux::GeoUtils::XMLUtils::getVectorSet(e0, target);
    else
        Ionflux::GeoUtils::XMLUtils::getVectorSet(e0, target, elementName);
}

template<>
void getObjVector<Ionflux::GeoUtils::VectorSet,
    Ionflux::GeoUtils::VectorSet*>(TiXmlElement* e0, 
    std::vector<Ionflux::GeoUtils::VectorSet*>& target, 
    const std::string& elementName, 
    const std::string& childElementName)
{
    checkElementNameOrError(e0, elementName, 
        "getObjVector<VectorSet>");
    TiXmlElement* ce0 = e0->FirstChildElement();
    while (ce0 != 0)
    {
        // Iterate over vector entries.
        std::string en0(ce0->Value());
        if (en0 == childElementName)
        {
            // default (VectorSet)
            Ionflux::GeoUtils::VectorSet* co0 = 
                Ionflux::GeoUtils::VectorSet::create();
            getObject0(ce0, *co0, childElementName);
            target.push_back(co0);
        } else
        if (en0 == 
            FaceData::XML_ELEMENT_NAME)
        {
            // FaceData
            FaceData* co0 = 
                FaceData::create();
            getObject0(ce0, *co0, childElementName);
            target.push_back(co0);
        } else
        {
            std::ostringstream status;
            status << "[getObjVector<VectorSet>] "
                << "Unexpected child element name: '" << en0 << "'";
            throw Ionflux::ObjectBase::IFError(status.str());
        }
        ce0 = ce0->NextSiblingElement();
    }
}

template<>
void getObjMap<Ionflux::GeoUtils::VectorSet,
    Ionflux::GeoUtils::VectorSet*>(TiXmlElement* e0, 
    std::map<std::string, Ionflux::GeoUtils::VectorSet*>& target, 
    const std::string& elementName, 
    const std::string& childElementName)
{
    checkElementNameOrError(e0, elementName, "getObjMap<VectorSet>");
    TiXmlElement* ee0 = e0->FirstChildElement();
    while (ee0 != 0)
    {
        // Iterate over map entries.
        std::string en0(ee0->Value());
        if (en0 == "entry")
        {
            std::string k = getAttributeValue(ee0, "key", false);
            TiXmlElement* ce0 = ee0->FirstChildElement();
            if (ce0 == 0)
            {
                std::ostringstream status;
                status << "[getObjMap<VectorSet>] "
                    << "Missing value for key: '" << k << "'";
                throw Ionflux::ObjectBase::IFError(status.str());
            }
            std::string en1(ce0->Value());
            Ionflux::GeoUtils::VectorSet* co0 = 0;
            // Add an object of the appropriate class. 
            if (en1 == childElementName)
            {
                // default (VectorSet)
                co0 = Ionflux::GeoUtils::VectorSet::create();
                getObject0(ce0, *co0, childElementName);
            } else
            if (en1 == 
                FaceData::XML_ELEMENT_NAME)
            {
                // FaceData
                FaceData* co1 = 
                    FaceData::create();
                getObject0(ce0, *co0, childElementName);
                co0 = co1;
            } else
            {
                std::ostringstream status;
                status << "[getObjMap<VectorSet>] "
                    << "Unexpected child element name: '" << en1 << "'";
                throw Ionflux::ObjectBase::IFError(status.str());
            }
            typename std::map<std::string, 
                Ionflux::GeoUtils::VectorSet*>::iterator j = target.find(k);
            if (j != target.end())
            {
                std::ostringstream status;
                status << "[getObjMap<VectorSet>] Duplicate key: '" 
                    << k << "'";
                throw Ionflux::ObjectBase::IFError(status.str());
            }
            target[k] = co0;
        }
        ee0 = ee0->NextSiblingElement();
    }
}

}

}

}

#include "geoutils/FaceData.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::FaceData* createFaceData(TiXmlElement* e0, const 
std::string& elementName)
{
    std::string en0(e0->Value());
    FaceData* o0 = 0;
    if (en0 == elementName)
    {
        // default (FaceData)
        o0 = FaceData::create();
        getFaceData(e0, *o0, en0);
    } else
    {
        std::ostringstream status;
        status << "[createFaceData] "
            << "Unexpected child element name: '" << en0 << "'";
        throw Ionflux::ObjectBase::IFError(status.str());
    }
    return o0;
}

void getFaceData(TiXmlElement* e0, 
    Ionflux::GeoUtils::FaceData& target, const std::string& elementName)
{
    Ionflux::ObjectBase::XMLUtils::checkElementNameOrError(e0, 
        elementName, "getFaceData");
    getVectorSet(e0, target, elementName);
    // Get attribute data.
    std::string a0;
    // Property: dataType (integer)
    a0 = Ionflux::ObjectBase::XMLUtils::getAttributeValue(
        e0, "datatype", true);
    target.setDataType(::strtol(a0.c_str(), 0, 10));
}

void getFaceData(const std::string& data, Ionflux::GeoUtils::FaceData& target)
{
    TiXmlDocument d0;
    
    std::string d1(data);
    d1.append(1, ' ');
    if (!d0.Parse(d1.c_str(), 0, TIXML_ENCODING_UTF8))
        throw ("[getFaceData] "
            "Unable to parse XML data.");
    TiXmlElement* m0 = 
        Ionflux::ObjectBase::XMLUtils::findElementByNameOrError(
            d0.RootElement(), 
            Ionflux::GeoUtils::FaceData::XML_ELEMENT_NAME);
    getFaceData(m0, target);
}

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

template<>
void getObject0<Ionflux::GeoUtils::FaceData>(TiXmlElement* e0, 
    Ionflux::GeoUtils::FaceData& target, const std::string& elementName)
{
    
    if (elementName.size() == 0)
        Ionflux::GeoUtils::XMLUtils::getFaceData(e0, target);
    else
        Ionflux::GeoUtils::XMLUtils::getFaceData(e0, target, elementName);
}

}

}

}

#include "geoutils/VectorSetSet.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::VectorSetSet* createVectorSetSet(TiXmlElement* e0, const
std::string& elementName)
{
    std::string en0(e0->Value());
    VectorSetSet* o0 = 0;
    if (en0 == elementName)
    {
        // default (VectorSetSet)
        o0 = VectorSetSet::create();
        getVectorSetSet(e0, *o0, en0);
    } else
    {
        std::ostringstream status;
        status << "[createVectorSetSet] "
            << "Unexpected child element name: '" << en0 << "'";
        throw Ionflux::ObjectBase::IFError(status.str());
    }
    return o0;
}

void getVectorSetSet(TiXmlElement* e0, 
    Ionflux::GeoUtils::VectorSetSet& target, const std::string& 
elementName)
{
    Ionflux::ObjectBase::XMLUtils::checkElementNameOrError(e0, 
        elementName, "getVectorSetSet");
    Ionflux::ObjectBase::XMLUtils::getObject(e0, target);
    // Get child data.
    TiXmlElement* ce0 = e0->FirstChildElement();
    while (ce0 != 0)
    {
        std::string en0(ce0->Value());
        std::string pName = 
            Ionflux::ObjectBase::XMLUtils::getAttributeValue(
                ce0, "pname", true);
        // Property: vectorSets (vector[object])
        if ((pName == "vector_sets") 
            && (en0 == "vectorsetvec"))
        {
            std::vector<Ionflux::GeoUtils::VectorSet*> pv0;
            Ionflux::ObjectBase::XMLUtils::getObjVector<
                    Ionflux::GeoUtils::VectorSet, 
                    Ionflux::GeoUtils::VectorSet*>(ce0, pv0, 
                "vectorsetvec", 
                Ionflux::GeoUtils::VectorSet::XML_ELEMENT_NAME);
            target.addVectorSets(pv0);
        }
        ce0 = ce0->NextSiblingElement();
    }
}

void getVectorSetSet(const std::string& data, Ionflux::GeoUtils::VectorSetSet& target)
{
    TiXmlDocument d0;
    
    std::string d1(data);
    d1.append(1, ' ');
    if (!d0.Parse(d1.c_str(), 0, TIXML_ENCODING_UTF8))
        throw ("[getVectorSetSet] "
            "Unable to parse XML data.");
    TiXmlElement* m0 = 
        Ionflux::ObjectBase::XMLUtils::findElementByNameOrError(
            d0.RootElement(), 
            Ionflux::GeoUtils::VectorSetSet::XML_ELEMENT_NAME);
    getVectorSetSet(m0, target);
}

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

template<>
void getObject0<Ionflux::GeoUtils::VectorSetSet>(TiXmlElement* e0, 
    Ionflux::GeoUtils::VectorSetSet& target, const std::string& 
elementName)
{
    
    if (elementName.size() == 0)
        Ionflux::GeoUtils::XMLUtils::getVectorSetSet(e0, target);
    else
        Ionflux::GeoUtils::XMLUtils::getVectorSetSet(e0, target, elementName);
}

}

}

}

#include "geoutils/TransformableObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::TransformableObject* 
createTransformableObject(TiXmlElement* e0, const std::string& elementName)
{
    std::string en0(e0->Value());
    TransformableObject* o0 = 0;
    if (en0 == elementName)
    {
        throw Ionflux::ObjectBase::IFError(
            "[createTransformableObject] "
            "Cannot create instance of abstract class.");
    } else
    if (en0 == Vertex3::XML_ELEMENT_NAME)
    {
        // Vertex3
        Vertex3* o1 = Vertex3::create();
        getVertex3(e0, *o1, en0);
        o0 = o1;
    } else
    if (en0 == Vertex3Set::XML_ELEMENT_NAME)
    {
        // Vertex3Set
        Vertex3Set* o1 = Vertex3Set::create();
        getVertex3Set(e0, *o1, en0);
        o0 = o1;
    } else
    if (en0 == Face::XML_ELEMENT_NAME)
    {
        // Face
        Face* o1 = Face::create();
        getFace(e0, *o1, en0);
        o0 = o1;
    } else
    if (en0 == Mesh::XML_ELEMENT_NAME)
    {
        // Mesh
        Mesh* o1 = Mesh::create();
        getMesh(e0, *o1, en0);
        o0 = o1;
    } else
    {
        std::ostringstream status;
        status << "[createTransformableObject] "
            << "Unexpected child element name: '" << en0 << "'";
        throw Ionflux::ObjectBase::IFError(status.str());
    }
    return o0;
}

void getTransformableObject(TiXmlElement* e0, 
    Ionflux::GeoUtils::TransformableObject& target, const std::string& 
elementName)
{
    Ionflux::ObjectBase::XMLUtils::checkElementNameOrError(e0, 
        elementName, "getTransformableObject");
    Ionflux::ObjectBase::XMLUtils::getObject(e0, target);
}

void getTransformableObject(const std::string& data, Ionflux::GeoUtils::TransformableObject& target)
{
    TiXmlDocument d0;
    
    std::string d1(data);
    d1.append(1, ' ');
    if (!d0.Parse(d1.c_str(), 0, TIXML_ENCODING_UTF8))
        throw ("[getTransformableObject] "
            "Unable to parse XML data.");
    TiXmlElement* m0 = 
        Ionflux::ObjectBase::XMLUtils::findElementByNameOrError(
            d0.RootElement(), 
            Ionflux::GeoUtils::TransformableObject::XML_ELEMENT_NAME);
    getTransformableObject(m0, target);
}

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

template<>
void getObject0<Ionflux::GeoUtils::TransformableObject>(TiXmlElement* e0, 
    Ionflux::GeoUtils::TransformableObject& target, const std::string& 
elementName)
{
    
    if (elementName.size() == 0)
        Ionflux::GeoUtils::XMLUtils::getTransformableObject(e0, target);
    else
        Ionflux::GeoUtils::XMLUtils::getTransformableObject(e0, target, elementName);
}

template<>
void getObjVector<Ionflux::GeoUtils::TransformableObject,
    Ionflux::GeoUtils::TransformableObject*>(TiXmlElement* e0, 
    std::vector<Ionflux::GeoUtils::TransformableObject*>& target, 
    const std::string& elementName, 
    const std::string& childElementName)
{
    checkElementNameOrError(e0, elementName, 
        "getObjVector<TransformableObject>");
    TiXmlElement* ce0 = e0->FirstChildElement();
    while (ce0 != 0)
    {
        // Iterate over vector entries.
        std::string en0(ce0->Value());
        if (en0 == childElementName)
        {
            throw Ionflux::ObjectBase::IFError(
                "[getObjVector<TransformableObject>] "
                "Cannot create instance of abstract class.");
        } else
        if (en0 == 
            Vertex3::XML_ELEMENT_NAME)
        {
            // Vertex3
            Vertex3* co0 = 
                Vertex3::create();
            getObject0(ce0, *co0, childElementName);
            target.push_back(co0);
        } else
        if (en0 == 
            Vertex3Set::XML_ELEMENT_NAME)
        {
            // Vertex3Set
            Vertex3Set* co0 = 
                Vertex3Set::create();
            getObject0(ce0, *co0, childElementName);
            target.push_back(co0);
        } else
        if (en0 == 
            Face::XML_ELEMENT_NAME)
        {
            // Face
            Face* co0 = 
                Face::create();
            getObject0(ce0, *co0, childElementName);
            target.push_back(co0);
        } else
        if (en0 == 
            Mesh::XML_ELEMENT_NAME)
        {
            // Mesh
            Mesh* co0 = 
                Mesh::create();
            getObject0(ce0, *co0, childElementName);
            target.push_back(co0);
        } else
        {
            std::ostringstream status;
            status << "[getObjVector<TransformableObject>] "
                << "Unexpected child element name: '" << en0 << "'";
            throw Ionflux::ObjectBase::IFError(status.str());
        }
        ce0 = ce0->NextSiblingElement();
    }
}

template<>
void getObjMap<Ionflux::GeoUtils::TransformableObject,
    Ionflux::GeoUtils::TransformableObject*>(TiXmlElement* e0, 
    std::map<std::string, Ionflux::GeoUtils::TransformableObject*>& target, 
    const std::string& elementName, 
    const std::string& childElementName)
{
    checkElementNameOrError(e0, elementName, "getObjMap<TransformableObject>");
    TiXmlElement* ee0 = e0->FirstChildElement();
    while (ee0 != 0)
    {
        // Iterate over map entries.
        std::string en0(ee0->Value());
        if (en0 == "entry")
        {
            std::string k = getAttributeValue(ee0, "key", false);
            TiXmlElement* ce0 = ee0->FirstChildElement();
            if (ce0 == 0)
            {
                std::ostringstream status;
                status << "[getObjMap<TransformableObject>] "
                    << "Missing value for key: '" << k << "'";
                throw Ionflux::ObjectBase::IFError(status.str());
            }
            std::string en1(ce0->Value());
            Ionflux::GeoUtils::TransformableObject* co0 = 0;
            // Add an object of the appropriate class. 
            if (en1 == childElementName)
            {
                throw Ionflux::ObjectBase::IFError(
                    "[getObjVector<TransformableObject>] "
                    "Cannot create instance of abstract class.");
            } else
            if (en1 == 
                Vertex3::XML_ELEMENT_NAME)
            {
                // Vertex3
                Vertex3* co1 = 
                    Vertex3::create();
                getObject0(ce0, *co0, childElementName);
                co0 = co1;
            } else
            if (en1 == 
                Vertex3Set::XML_ELEMENT_NAME)
            {
                // Vertex3Set
                Vertex3Set* co1 = 
                    Vertex3Set::create();
                getObject0(ce0, *co0, childElementName);
                co0 = co1;
            } else
            if (en1 == 
                Face::XML_ELEMENT_NAME)
            {
                // Face
                Face* co1 = 
                    Face::create();
                getObject0(ce0, *co0, childElementName);
                co0 = co1;
            } else
            if (en1 == 
                Mesh::XML_ELEMENT_NAME)
            {
                // Mesh
                Mesh* co1 = 
                    Mesh::create();
                getObject0(ce0, *co0, childElementName);
                co0 = co1;
            } else
            {
                std::ostringstream status;
                status << "[getObjMap<TransformableObject>] "
                    << "Unexpected child element name: '" << en1 << "'";
                throw Ionflux::ObjectBase::IFError(status.str());
            }
            typename std::map<std::string, 
                Ionflux::GeoUtils::TransformableObject*>::iterator j = target.find(k);
            if (j != target.end())
            {
                std::ostringstream status;
                status << "[getObjMap<TransformableObject>] Duplicate key: '" 
                    << k << "'";
                throw Ionflux::ObjectBase::IFError(status.str());
            }
            target[k] = co0;
        }
        ee0 = ee0->NextSiblingElement();
    }
}

}

}

}

#include "geoutils/Vertex3.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Vertex3* createVertex3(TiXmlElement* e0, const 
std::string& elementName)
{
    std::string en0(e0->Value());
    Vertex3* o0 = 0;
    if (en0 == elementName)
    {
        // default (Vertex3)
        o0 = Vertex3::create();
        getVertex3(e0, *o0, en0);
    } else
    {
        std::ostringstream status;
        status << "[createVertex3] "
            << "Unexpected child element name: '" << en0 << "'";
        throw Ionflux::ObjectBase::IFError(status.str());
    }
    return o0;
}

void getVertex3(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vertex3& target, const std::string& elementName)
{
    Ionflux::ObjectBase::XMLUtils::checkElementNameOrError(e0, 
        elementName, "getVertex3");
    getTransformableObject(e0, target, elementName);
    // Get element attribute data.
    std::string a0;
    a0 = Ionflux::ObjectBase::XMLUtils::getAttributeValue(
        e0, "d", true);
    Ionflux::ObjectBase::DoubleVector dv0;
    Ionflux::ObjectBase::vectorFromList(a0, dv0);
    target.setCoords(dv0);
}

void getVertex3(const std::string& data, Ionflux::GeoUtils::Vertex3& target)
{
    TiXmlDocument d0;
    
    std::string d1(data);
    d1.append(1, ' ');
    if (!d0.Parse(d1.c_str(), 0, TIXML_ENCODING_UTF8))
        throw ("[getVertex3] "
            "Unable to parse XML data.");
    TiXmlElement* m0 = 
        Ionflux::ObjectBase::XMLUtils::findElementByNameOrError(
            d0.RootElement(), 
            Ionflux::GeoUtils::Vertex3::XML_ELEMENT_NAME);
    getVertex3(m0, target);
}

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

template<>
void getObject0<Ionflux::GeoUtils::Vertex3>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vertex3& target, const std::string& elementName)
{
    
    if (elementName.size() == 0)
        Ionflux::GeoUtils::XMLUtils::getVertex3(e0, target);
    else
        Ionflux::GeoUtils::XMLUtils::getVertex3(e0, target, elementName);
}

}

}

}

#include "geoutils/Vertex3Set.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Vertex3Set* createVertex3Set(TiXmlElement* e0, const 
std::string& elementName)
{
    std::string en0(e0->Value());
    Vertex3Set* o0 = 0;
    if (en0 == elementName)
    {
        // default (Vertex3Set)
        o0 = Vertex3Set::create();
        getVertex3Set(e0, *o0, en0);
    } else
    {
        std::ostringstream status;
        status << "[createVertex3Set] "
            << "Unexpected child element name: '" << en0 << "'";
        throw Ionflux::ObjectBase::IFError(status.str());
    }
    return o0;
}

void getVertex3Set(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vertex3Set& target, const std::string& elementName)
{
    Ionflux::ObjectBase::XMLUtils::checkElementNameOrError(e0, 
        elementName, "getVertex3Set");
    getTransformableObject(e0, target, elementName);
    // Get child data.
    TiXmlElement* ce0 = e0->FirstChildElement();
    while (ce0 != 0)
    {
        std::string en0(ce0->Value());
        std::string pName = 
            Ionflux::ObjectBase::XMLUtils::getAttributeValue(
                ce0, "pname", true);
        // Property: vertices (vector[object])
        if ((pName == "vertices") 
            && (en0 == "vert3vec"))
        {
            std::vector<Ionflux::GeoUtils::Vertex3*> pv0;
            Ionflux::ObjectBase::XMLUtils::getObjVector<
                    Ionflux::GeoUtils::Vertex3, 
                    Ionflux::GeoUtils::Vertex3*>(ce0, pv0, 
                "vert3vec", 
                Ionflux::GeoUtils::Vertex3::XML_ELEMENT_NAME);
            target.addVertices(pv0);
        }
        ce0 = ce0->NextSiblingElement();
    }
}

void getVertex3Set(const std::string& data, Ionflux::GeoUtils::Vertex3Set& target)
{
    TiXmlDocument d0;
    
    std::string d1(data);
    d1.append(1, ' ');
    if (!d0.Parse(d1.c_str(), 0, TIXML_ENCODING_UTF8))
        throw ("[getVertex3Set] "
            "Unable to parse XML data.");
    TiXmlElement* m0 = 
        Ionflux::ObjectBase::XMLUtils::findElementByNameOrError(
            d0.RootElement(), 
            Ionflux::GeoUtils::Vertex3Set::XML_ELEMENT_NAME);
    getVertex3Set(m0, target);
}

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

template<>
void getObject0<Ionflux::GeoUtils::Vertex3Set>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vertex3Set& target, const std::string& elementName)
{
    
    if (elementName.size() == 0)
        Ionflux::GeoUtils::XMLUtils::getVertex3Set(e0, target);
    else
        Ionflux::GeoUtils::XMLUtils::getVertex3Set(e0, target, elementName);
}

}

}

}

#include "geoutils/Face.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Face* createFace(TiXmlElement* e0, const std::string& 
elementName)
{
    std::string en0(e0->Value());
    Face* o0 = 0;
    if (en0 == elementName)
    {
        // default (Face)
        o0 = Face::create();
        getFace(e0, *o0, en0);
    } else
    {
        std::ostringstream status;
        status << "[createFace] "
            << "Unexpected child element name: '" << en0 << "'";
        throw Ionflux::ObjectBase::IFError(status.str());
    }
    return o0;
}

void getFace(TiXmlElement* e0, 
    Ionflux::GeoUtils::Face& target, const std::string& elementName)
{
    Ionflux::ObjectBase::XMLUtils::checkElementNameOrError(e0, 
        elementName, "getFace");
    getTransformableObject(e0, target, elementName);
    // Get child data.
    TiXmlElement* ce0 = e0->FirstChildElement();
    while (ce0 != 0)
    {
        std::string en0(ce0->Value());
        std::string pName = 
            Ionflux::ObjectBase::XMLUtils::getAttributeValue(
                ce0, "pname", true);
        // Property: vertices (vector[integer])
        if ((pName == "vertices") 
            && (en0 == "vec"))
        {
            Ionflux::ObjectBase::UIntVector pv0;
            Ionflux::ObjectBase::XMLUtils::getUIntVector(ce0, pv0);
            target.addVertices(pv0);
        }
        // Property: faceData (object)
        if (pName == "fds")
        {
        }
        ce0 = ce0->NextSiblingElement();
    }
}

void getFace(const std::string& data, Ionflux::GeoUtils::Face& target)
{
    TiXmlDocument d0;
    
    std::string d1(data);
    d1.append(1, ' ');
    if (!d0.Parse(d1.c_str(), 0, TIXML_ENCODING_UTF8))
        throw ("[getFace] "
            "Unable to parse XML data.");
    TiXmlElement* m0 = 
        Ionflux::ObjectBase::XMLUtils::findElementByNameOrError(
            d0.RootElement(), 
            Ionflux::GeoUtils::Face::XML_ELEMENT_NAME);
    getFace(m0, target);
}

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

template<>
void getObject0<Ionflux::GeoUtils::Face>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Face& target, const std::string& elementName)
{
    
    if (elementName.size() == 0)
        Ionflux::GeoUtils::XMLUtils::getFace(e0, target);
    else
        Ionflux::GeoUtils::XMLUtils::getFace(e0, target, elementName);
}

}

}

}

#include "geoutils/Mesh.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Mesh* createMesh(TiXmlElement* e0, const std::string& 
elementName)
{
    std::string en0(e0->Value());
    Mesh* o0 = 0;
    if (en0 == elementName)
    {
        // default (Mesh)
        o0 = Mesh::create();
        getMesh(e0, *o0, en0);
    } else
    {
        std::ostringstream status;
        status << "[createMesh] "
            << "Unexpected child element name: '" << en0 << "'";
        throw Ionflux::ObjectBase::IFError(status.str());
    }
    return o0;
}

void getMesh(TiXmlElement* e0, 
    Ionflux::GeoUtils::Mesh& target, const std::string& elementName)
{
    Ionflux::ObjectBase::XMLUtils::checkElementNameOrError(e0, 
        elementName, "getMesh");
    getTransformableObject(e0, target, elementName);
    // Get child data.
    TiXmlElement* ce0 = e0->FirstChildElement();
    while (ce0 != 0)
    {
        std::string en0(ce0->Value());
        std::string pName = 
            Ionflux::ObjectBase::XMLUtils::getAttributeValue(
                ce0, "pname", true);
        // Property: vertexSource (object)
        if (pName == "vertex_source")
        {
        }
        // Property: faces (vector[object])
        if ((pName == "faces") 
            && (en0 == "vec"))
        {
            std::vector<Ionflux::GeoUtils::Face*> pv0;
            Ionflux::ObjectBase::XMLUtils::getObjVector<
                    Ionflux::GeoUtils::Face, 
                    Ionflux::GeoUtils::Face*>(ce0, pv0, 
                "vec", 
                Ionflux::GeoUtils::Face::XML_ELEMENT_NAME);
            target.addFaces(pv0);
        }
        ce0 = ce0->NextSiblingElement();
    }
}

void getMesh(const std::string& data, Ionflux::GeoUtils::Mesh& target)
{
    TiXmlDocument d0;
    
    std::string d1(data);
    d1.append(1, ' ');
    if (!d0.Parse(d1.c_str(), 0, TIXML_ENCODING_UTF8))
        throw ("[getMesh] "
            "Unable to parse XML data.");
    TiXmlElement* m0 = 
        Ionflux::ObjectBase::XMLUtils::findElementByNameOrError(
            d0.RootElement(), 
            Ionflux::GeoUtils::Mesh::XML_ELEMENT_NAME);
    getMesh(m0, target);
}

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

template<>
void getObject0<Ionflux::GeoUtils::Mesh>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Mesh& target, const std::string& elementName)
{
    
    if (elementName.size() == 0)
        Ionflux::GeoUtils::XMLUtils::getMesh(e0, target);
    else
        Ionflux::GeoUtils::XMLUtils::getMesh(e0, target, elementName);
}

}

}

}


/** \file xmlutils.cpp
 * \brief XML utility functions (implementation).
 */
