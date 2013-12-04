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
#include "geoutils/xmlio/VectorXMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Vector* createVector(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::Vector* co0 =
        Vector::upcast(
            Vector::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getVector(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector& target, const std::string& elementName)
{
    Vector::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getVector(const std::string& data, Ionflux::GeoUtils::Vector& target)
{
    Vector::getXMLObjectFactory()->initObject(data, target);
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
    
    Vector::getXMLObjectFactory()->initObject(
        e0, target, elementName);
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
        Ionflux::GeoUtils::Vector* co0 =
            Vector::upcast(
                Vector::getXMLObjectFactory()->createObject(
                    ce0, en0));
        target.push_back(co0);
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
            Ionflux::GeoUtils::Vector* co0 =
                Vector::upcast(
                    Vector::getXMLObjectFactory()->createObject(
                        ce0, en0));
            std::map<std::string, 
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
#include "geoutils/xmlio/Vector2XMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Vector2* createVector2(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::Vector2* co0 =
        Vector2::upcast(
            Vector2::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getVector2(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector2& target, const std::string& elementName)
{
    Vector2::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getVector2(const std::string& data, Ionflux::GeoUtils::Vector2& target)
{
    Vector2::getXMLObjectFactory()->initObject(data, target);
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
    
    Vector2::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/Vector3.hpp"
#include "geoutils/xmlio/Vector3XMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Vector3* createVector3(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::Vector3* co0 =
        Vector3::upcast(
            Vector3::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getVector3(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector3& target, const std::string& elementName)
{
    Vector3::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getVector3(const std::string& data, Ionflux::GeoUtils::Vector3& target)
{
    Vector3::getXMLObjectFactory()->initObject(data, target);
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
    
    Vector3::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/Vector4.hpp"
#include "geoutils/xmlio/Vector4XMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Vector4* createVector4(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::Vector4* co0 =
        Vector4::upcast(
            Vector4::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getVector4(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vector4& target, const std::string& elementName)
{
    Vector4::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getVector4(const std::string& data, Ionflux::GeoUtils::Vector4& target)
{
    Vector4::getXMLObjectFactory()->initObject(data, target);
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
    
    Vector4::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/VectorSet.hpp"
#include "geoutils/xmlio/VectorSetXMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::VectorSet* createVectorSet(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::VectorSet* co0 =
        VectorSet::upcast(
            VectorSet::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getVectorSet(TiXmlElement* e0, 
    Ionflux::GeoUtils::VectorSet& target, const std::string& elementName)
{
    VectorSet::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getVectorSet(const std::string& data, Ionflux::GeoUtils::VectorSet& target)
{
    VectorSet::getXMLObjectFactory()->initObject(data, target);
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
    
    VectorSet::getXMLObjectFactory()->initObject(
        e0, target, elementName);
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
        Ionflux::GeoUtils::VectorSet* co0 =
            VectorSet::upcast(
                VectorSet::getXMLObjectFactory()->createObject(
                    ce0, en0));
        target.push_back(co0);
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
            Ionflux::GeoUtils::VectorSet* co0 =
                VectorSet::upcast(
                    VectorSet::getXMLObjectFactory()->createObject(
                        ce0, en0));
            std::map<std::string, 
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
#include "geoutils/xmlio/FaceDataXMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::FaceData* createFaceData(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::FaceData* co0 =
        FaceData::upcast(
            FaceData::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getFaceData(TiXmlElement* e0, 
    Ionflux::GeoUtils::FaceData& target, const std::string& elementName)
{
    FaceData::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getFaceData(const std::string& data, Ionflux::GeoUtils::FaceData& target)
{
    FaceData::getXMLObjectFactory()->initObject(data, target);
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
    
    FaceData::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/VectorSetSet.hpp"
#include "geoutils/xmlio/VectorSetSetXMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::VectorSetSet* createVectorSetSet(TiXmlElement* e0, const
std::string& elementName)
{
    Ionflux::GeoUtils::VectorSetSet* co0 =
        VectorSetSet::upcast(
            VectorSetSet::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getVectorSetSet(TiXmlElement* e0, 
    Ionflux::GeoUtils::VectorSetSet& target, const std::string& 
elementName)
{
    VectorSetSet::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getVectorSetSet(const std::string& data, Ionflux::GeoUtils::VectorSetSet& target)
{
    VectorSetSet::getXMLObjectFactory()->initObject(data, target);
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
    
    VectorSetSet::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/Matrix.hpp"
#include "geoutils/xmlio/MatrixXMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Matrix* createMatrix(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::Matrix* co0 =
        Matrix::upcast(
            Matrix::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getMatrix(TiXmlElement* e0, 
    Ionflux::GeoUtils::Matrix& target, const std::string& elementName)
{
    Matrix::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getMatrix(const std::string& data, Ionflux::GeoUtils::Matrix& target)
{
    Matrix::getXMLObjectFactory()->initObject(data, target);
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
void getObject0<Ionflux::GeoUtils::Matrix>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Matrix& target, const std::string& elementName)
{
    
    Matrix::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

template<>
void getObjVector<Ionflux::GeoUtils::Matrix,
    Ionflux::GeoUtils::Matrix*>(TiXmlElement* e0, 
    std::vector<Ionflux::GeoUtils::Matrix*>& target, 
    const std::string& elementName, 
    const std::string& childElementName)
{
    checkElementNameOrError(e0, elementName, 
        "getObjVector<Matrix>");
    TiXmlElement* ce0 = e0->FirstChildElement();
    while (ce0 != 0)
    {
        // Iterate over vector entries.
        std::string en0(ce0->Value());
        Ionflux::GeoUtils::Matrix* co0 =
            Matrix::upcast(
                Matrix::getXMLObjectFactory()->createObject(
                    ce0, en0));
        target.push_back(co0);
        ce0 = ce0->NextSiblingElement();
    }
}

template<>
void getObjMap<Ionflux::GeoUtils::Matrix,
    Ionflux::GeoUtils::Matrix*>(TiXmlElement* e0, 
    std::map<std::string, Ionflux::GeoUtils::Matrix*>& target, 
    const std::string& elementName, 
    const std::string& childElementName)
{
    checkElementNameOrError(e0, elementName, "getObjMap<Matrix>");
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
                status << "[getObjMap<Matrix>] "
                    << "Missing value for key: '" << k << "'";
                throw Ionflux::ObjectBase::IFError(status.str());
            }
            std::string en1(ce0->Value());
            Ionflux::GeoUtils::Matrix* co0 =
                Matrix::upcast(
                    Matrix::getXMLObjectFactory()->createObject(
                        ce0, en0));
            std::map<std::string, 
                Ionflux::GeoUtils::Matrix*>::iterator j = target.find(k);
            if (j != target.end())
            {
                std::ostringstream status;
                status << "[getObjMap<Matrix>] Duplicate key: '" 
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

#include "geoutils/Matrix2.hpp"
#include "geoutils/xmlio/Matrix2XMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Matrix2* createMatrix2(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::Matrix2* co0 =
        Matrix2::upcast(
            Matrix2::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getMatrix2(TiXmlElement* e0, 
    Ionflux::GeoUtils::Matrix2& target, const std::string& elementName)
{
    Matrix2::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getMatrix2(const std::string& data, Ionflux::GeoUtils::Matrix2& target)
{
    Matrix2::getXMLObjectFactory()->initObject(data, target);
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
void getObject0<Ionflux::GeoUtils::Matrix2>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Matrix2& target, const std::string& elementName)
{
    
    Matrix2::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/Matrix3.hpp"
#include "geoutils/xmlio/Matrix3XMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Matrix3* createMatrix3(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::Matrix3* co0 =
        Matrix3::upcast(
            Matrix3::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getMatrix3(TiXmlElement* e0, 
    Ionflux::GeoUtils::Matrix3& target, const std::string& elementName)
{
    Matrix3::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getMatrix3(const std::string& data, Ionflux::GeoUtils::Matrix3& target)
{
    Matrix3::getXMLObjectFactory()->initObject(data, target);
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
void getObject0<Ionflux::GeoUtils::Matrix3>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Matrix3& target, const std::string& elementName)
{
    
    Matrix3::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/Matrix4.hpp"
#include "geoutils/xmlio/Matrix4XMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Matrix4* createMatrix4(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::Matrix4* co0 =
        Matrix4::upcast(
            Matrix4::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getMatrix4(TiXmlElement* e0, 
    Ionflux::GeoUtils::Matrix4& target, const std::string& elementName)
{
    Matrix4::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getMatrix4(const std::string& data, Ionflux::GeoUtils::Matrix4& target)
{
    Matrix4::getXMLObjectFactory()->initObject(data, target);
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
void getObject0<Ionflux::GeoUtils::Matrix4>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Matrix4& target, const std::string& elementName)
{
    
    Matrix4::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/DeferredTransform.hpp"
#include "geoutils/xmlio/DeferredTransformXMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::DeferredTransform* createDeferredTransform(TiXmlElement*
e0, const std::string& elementName)
{
    Ionflux::GeoUtils::DeferredTransform* co0 =
        DeferredTransform::upcast(
            DeferredTransform::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getDeferredTransform(TiXmlElement* e0, 
    Ionflux::GeoUtils::DeferredTransform& target, const std::string& 
elementName)
{
    DeferredTransform::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getDeferredTransform(const std::string& data, Ionflux::GeoUtils::DeferredTransform& target)
{
    DeferredTransform::getXMLObjectFactory()->initObject(data, target);
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
void getObject0<Ionflux::GeoUtils::DeferredTransform>(TiXmlElement* e0, 
    Ionflux::GeoUtils::DeferredTransform& target, const std::string& 
elementName)
{
    
    DeferredTransform::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/TransformableObject.hpp"
#include "geoutils/xmlio/TransformableObjectXMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::TransformableObject* 
createTransformableObject(TiXmlElement* e0, const std::string& elementName)
{
    Ionflux::GeoUtils::TransformableObject* co0 =
        TransformableObject::upcast(
            TransformableObject::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getTransformableObject(TiXmlElement* e0, 
    Ionflux::GeoUtils::TransformableObject& target, const std::string& 
elementName)
{
    TransformableObject::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getTransformableObject(const std::string& data, Ionflux::GeoUtils::TransformableObject& target)
{
    TransformableObject::getXMLObjectFactory()->initObject(data, target);
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
    
    TransformableObject::getXMLObjectFactory()->initObject(
        e0, target, elementName);
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
        Ionflux::GeoUtils::TransformableObject* co0 =
            TransformableObject::upcast(
                TransformableObject::getXMLObjectFactory()->createObject(
                    ce0, en0));
        target.push_back(co0);
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
            Ionflux::GeoUtils::TransformableObject* co0 =
                TransformableObject::upcast(
                    TransformableObject::getXMLObjectFactory()->createObject(
                        ce0, en0));
            std::map<std::string, 
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

#include "geoutils/Vertex2.hpp"
#include "geoutils/xmlio/Vertex2XMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Vertex2* createVertex2(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::Vertex2* co0 =
        Vertex2::upcast(
            Vertex2::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getVertex2(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vertex2& target, const std::string& elementName)
{
    Vertex2::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getVertex2(const std::string& data, Ionflux::GeoUtils::Vertex2& target)
{
    Vertex2::getXMLObjectFactory()->initObject(data, target);
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
void getObject0<Ionflux::GeoUtils::Vertex2>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vertex2& target, const std::string& elementName)
{
    
    Vertex2::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/Vertex3.hpp"
#include "geoutils/xmlio/Vertex3XMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Vertex3* createVertex3(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::Vertex3* co0 =
        Vertex3::upcast(
            Vertex3::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getVertex3(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vertex3& target, const std::string& elementName)
{
    Vertex3::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getVertex3(const std::string& data, Ionflux::GeoUtils::Vertex3& target)
{
    Vertex3::getXMLObjectFactory()->initObject(data, target);
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
    
    Vertex3::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/Vertex3Set.hpp"
#include "geoutils/xmlio/Vertex3SetXMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Vertex3Set* createVertex3Set(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::Vertex3Set* co0 =
        Vertex3Set::upcast(
            Vertex3Set::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getVertex3Set(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vertex3Set& target, const std::string& elementName)
{
    Vertex3Set::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getVertex3Set(const std::string& data, Ionflux::GeoUtils::Vertex3Set& target)
{
    Vertex3Set::getXMLObjectFactory()->initObject(data, target);
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
    
    Vertex3Set::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/Face.hpp"
#include "geoutils/xmlio/FaceXMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Face* createFace(TiXmlElement* e0, const std::string& 
elementName)
{
    Ionflux::GeoUtils::Face* co0 =
        Face::upcast(
            Face::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getFace(TiXmlElement* e0, 
    Ionflux::GeoUtils::Face& target, const std::string& elementName)
{
    Face::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getFace(const std::string& data, Ionflux::GeoUtils::Face& target)
{
    Face::getXMLObjectFactory()->initObject(data, target);
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
    
    Face::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/Edge.hpp"
#include "geoutils/xmlio/EdgeXMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Edge* createEdge(TiXmlElement* e0, const std::string& 
elementName)
{
    Ionflux::GeoUtils::Edge* co0 =
        Edge::upcast(
            Edge::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getEdge(TiXmlElement* e0, 
    Ionflux::GeoUtils::Edge& target, const std::string& elementName)
{
    Edge::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getEdge(const std::string& data, Ionflux::GeoUtils::Edge& target)
{
    Edge::getXMLObjectFactory()->initObject(data, target);
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
void getObject0<Ionflux::GeoUtils::Edge>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Edge& target, const std::string& elementName)
{
    
    Edge::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/Mesh.hpp"
#include "geoutils/xmlio/MeshXMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Mesh* createMesh(TiXmlElement* e0, const std::string& 
elementName)
{
    Ionflux::GeoUtils::Mesh* co0 =
        Mesh::upcast(
            Mesh::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getMesh(TiXmlElement* e0, 
    Ionflux::GeoUtils::Mesh& target, const std::string& elementName)
{
    Mesh::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getMesh(const std::string& data, Ionflux::GeoUtils::Mesh& target)
{
    Mesh::getXMLObjectFactory()->initObject(data, target);
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
    
    Mesh::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/Object3.hpp"
#include "geoutils/xmlio/Object3XMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Object3* createObject3(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::Object3* co0 =
        Object3::upcast(
            Object3::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getObject3(TiXmlElement* e0, 
    Ionflux::GeoUtils::Object3& target, const std::string& elementName)
{
    Object3::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getObject3(const std::string& data, Ionflux::GeoUtils::Object3& target)
{
    Object3::getXMLObjectFactory()->initObject(data, target);
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
void getObject0<Ionflux::GeoUtils::Object3>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Object3& target, const std::string& elementName)
{
    
    Object3::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/TransformableGroup.hpp"
#include "geoutils/xmlio/TransformableGroupXMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::TransformableGroup* 
createTransformableGroup(TiXmlElement* e0, const std::string& elementName)
{
    Ionflux::GeoUtils::TransformableGroup* co0 =
        TransformableGroup::upcast(
            TransformableGroup::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getTransformableGroup(TiXmlElement* e0, 
    Ionflux::GeoUtils::TransformableGroup& target, const std::string& 
elementName)
{
    TransformableGroup::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getTransformableGroup(const std::string& data, Ionflux::GeoUtils::TransformableGroup& target)
{
    TransformableGroup::getXMLObjectFactory()->initObject(data, target);
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
void getObject0<Ionflux::GeoUtils::TransformableGroup>(TiXmlElement* e0, 
    Ionflux::GeoUtils::TransformableGroup& target, const std::string& 
elementName)
{
    
    TransformableGroup::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/Polygon3.hpp"
#include "geoutils/xmlio/Polygon3XMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Polygon3* createPolygon3(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::Polygon3* co0 =
        Polygon3::upcast(
            Polygon3::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getPolygon3(TiXmlElement* e0, 
    Ionflux::GeoUtils::Polygon3& target, const std::string& elementName)
{
    Polygon3::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getPolygon3(const std::string& data, Ionflux::GeoUtils::Polygon3& target)
{
    Polygon3::getXMLObjectFactory()->initObject(data, target);
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
void getObject0<Ionflux::GeoUtils::Polygon3>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Polygon3& target, const std::string& elementName)
{
    
    Polygon3::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/Polygon3Set.hpp"
#include "geoutils/xmlio/Polygon3SetXMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Polygon3Set* createPolygon3Set(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::Polygon3Set* co0 =
        Polygon3Set::upcast(
            Polygon3Set::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getPolygon3Set(TiXmlElement* e0, 
    Ionflux::GeoUtils::Polygon3Set& target, const std::string& elementName)
{
    Polygon3Set::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getPolygon3Set(const std::string& data, Ionflux::GeoUtils::Polygon3Set& target)
{
    Polygon3Set::getXMLObjectFactory()->initObject(data, target);
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
void getObject0<Ionflux::GeoUtils::Polygon3Set>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Polygon3Set& target, const std::string& elementName)
{
    
    Polygon3Set::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/Shape3.hpp"
#include "geoutils/xmlio/Shape3XMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Shape3* createShape3(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::Shape3* co0 =
        Shape3::upcast(
            Shape3::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getShape3(TiXmlElement* e0, 
    Ionflux::GeoUtils::Shape3& target, const std::string& elementName)
{
    Shape3::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getShape3(const std::string& data, Ionflux::GeoUtils::Shape3& target)
{
    Shape3::getXMLObjectFactory()->initObject(data, target);
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
void getObject0<Ionflux::GeoUtils::Shape3>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Shape3& target, const std::string& elementName)
{
    
    Shape3::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}

#include "geoutils/Camera.hpp"
#include "geoutils/xmlio/CameraXMLFactory.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

Ionflux::GeoUtils::Camera* createCamera(TiXmlElement* e0, const 
std::string& elementName)
{
    Ionflux::GeoUtils::Camera* co0 =
        Camera::upcast(
            Camera::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
}

void getCamera(TiXmlElement* e0, 
    Ionflux::GeoUtils::Camera& target, const std::string& elementName)
{
    Camera::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
}

void getCamera(const std::string& data, Ionflux::GeoUtils::Camera& target)
{
    Camera::getXMLObjectFactory()->initObject(data, target);
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
void getObject0<Ionflux::GeoUtils::Camera>(TiXmlElement* e0, 
    Ionflux::GeoUtils::Camera& target, const std::string& elementName)
{
    
    Camera::getXMLObjectFactory()->initObject(
        e0, target, elementName);
}

}

}

}


/** \file xmlutils.cpp
 * \brief XML utility functions (implementation).
 */
