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

void getVector(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector& target, const std::string& elementName = 
Ionflux::GeoUtils::Vector::XML_ELEMENT_NAME)
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

void getVector2(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector2& target, const std::string& elementName = 
Ionflux::GeoUtils::Vector2::XML_ELEMENT_NAME)
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

void getVector3(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector3& target, const std::string& elementName = 
Ionflux::GeoUtils::Vector3::XML_ELEMENT_NAME)
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

void getVector4(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector4& target, const std::string& elementName = 
Ionflux::GeoUtils::Vector4::XML_ELEMENT_NAME)
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

void getVectorSet(TiXmlElement* e0, 
    Ionflux::GeoUtils::VectorSet& target, const std::string& elementName = 
Ionflux::GeoUtils::VectorSet::XML_ELEMENT_NAME)
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
        if ((en0 == "vectorvec") 
            && (pName == "vectors"))
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

void getVectorSetSet(TiXmlElement* e0, 
    Ionflux::GeoUtils::VectorSetSet& target, const std::string& elementName
= Ionflux::GeoUtils::VectorSetSet::XML_ELEMENT_NAME)
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
        if ((en0 == "vectorsetvec") 
            && (pName == "vector_sets"))
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

#include "geoutils/FaceData.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

void getFaceData(TiXmlElement* e0, 
    Ionflux::GeoUtils::FaceData& target, const std::string& elementName = 
Ionflux::GeoUtils::FaceData::XML_ELEMENT_NAME)
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

#include "geoutils/TransformableObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

void getTransformableObject(TiXmlElement* e0, 
    Ionflux::GeoUtils::TransformableObject& target, const std::string& 
elementName = Ionflux::GeoUtils::TransformableObject::XML_ELEMENT_NAME)
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

void getVertex3(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vertex3& target, const std::string& elementName = 
Ionflux::GeoUtils::Vertex3::XML_ELEMENT_NAME)
{
    Ionflux::ObjectBase::XMLUtils::checkElementNameOrError(e0, 
        elementName, "getVertex3");
    getTransformableObject(e0, target, elementName);
    // Get attribute data.
    std::string a0;
    // Property: x (float)
    a0 = Ionflux::ObjectBase::XMLUtils::getAttributeValue(
        e0, "x", true);
    target.setX(::strtod(a0.c_str(), 0));
    // Property: y (float)
    a0 = Ionflux::ObjectBase::XMLUtils::getAttributeValue(
        e0, "y", true);
    target.setY(::strtod(a0.c_str(), 0));
    // Property: z (float)
    a0 = Ionflux::ObjectBase::XMLUtils::getAttributeValue(
        e0, "z", true);
    target.setZ(::strtod(a0.c_str(), 0));
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

void getVertex3Set(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vertex3Set& target, const std::string& elementName =
Ionflux::GeoUtils::Vertex3Set::XML_ELEMENT_NAME)
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
        if ((en0 == "vert3vec") 
            && (pName == "vertices"))
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

void getFace(TiXmlElement* e0, 
    Ionflux::GeoUtils::Face& target, const std::string& elementName = 
Ionflux::GeoUtils::Face::XML_ELEMENT_NAME)
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
        if ((en0 == "vec") 
            && (pName == "vertices"))
        {
            Ionflux::ObjectBase::UIntVector pv0;
            Ionflux::ObjectBase::XMLUtils::getUIntVector(ce0, pv0);
            target.addVertices(pv0);
        }
        // Property: faceData ()
        if ((en0 == "data") 
            && (pName == "fds"))
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

void getMesh(TiXmlElement* e0, 
    Ionflux::GeoUtils::Mesh& target, const std::string& elementName = 
Ionflux::GeoUtils::Mesh::XML_ELEMENT_NAME)
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
        if ((en0 == "prop") 
            && (pName == "vertex_source"))
        {
        }
        // Property: faces (vector[object])
        if ((en0 == "vec") 
            && (pName == "faces"))
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
