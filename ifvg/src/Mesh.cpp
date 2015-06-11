/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Mesh.cpp                        Mesh (implementation).
 * ========================================================================== */

#include "ifvg/Mesh.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "geoutils/Vertex3Set.hpp"
#include "ifvg/utils.hpp"
#include "ifvg/IFVGError.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "ifvg/xmlutils.hpp"
#include "ifvg/xmlio/MeshXMLFactory.hpp"
#include "ifobject/objectutils.hpp"
#include "ifobject/serialize.hpp"
#include "ifobject/IFIOContext.hpp"

using Ionflux::ObjectBase::pack;
using Ionflux::ObjectBase::packObj;
using Ionflux::ObjectBase::unpack;
using Ionflux::ObjectBase::unpackObj;

using namespace std;

namespace Ionflux
{

namespace VolGfx
{

MeshClassInfo::MeshClassInfo()
{
	name = "Mesh";
	desc = "Mesh";
	baseClassInfo.push_back(Ionflux::GeoUtils::Mesh::CLASS_INFO);
}

MeshClassInfo::~MeshClassInfo()
{
}

// run-time type information instance constants
const MeshClassInfo Mesh::meshClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Mesh::CLASS_INFO = &Mesh::meshClassInfo;

const std::string Mesh::XML_ELEMENT_NAME = "vgmesh";

const Ionflux::ObjectBase::MagicSyllable Mesh::MAGIC_SYLLABLE_OBJECT = 0x4d45;

Mesh::Mesh()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Mesh::Mesh(const Ionflux::VolGfx::Mesh& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Mesh::Mesh(Ionflux::GeoUtils::Vertex3Vector* initVerts, const 
Ionflux::GeoUtils::FaceVector* initFaces)
: Ionflux::GeoUtils::Mesh(initVerts, initFaces)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Mesh::Mesh(Ionflux::GeoUtils::Vertex3Set* initVertexSource, const 
Ionflux::GeoUtils::FaceVector* initFaces)
: Ionflux::GeoUtils::Mesh(initVertexSource, initFaces)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Mesh::~Mesh()
{
	// TODO: Nothing ATM. ;-)
}

bool Mesh::serialize(std::string& target) const
{
	return true;
}

Ionflux::ObjectBase::DataSize Mesh::deserialize(const std::string& source, Ionflux::ObjectBase::DataSize offset)
{
	return offset;
}

bool Mesh::serialize(std::ostream& target, bool addMagicWord) const
{
    Ionflux::ObjectBase::IFObject::serialize(target, addMagicWord);
    // mesh type
    Ionflux::GeoUtils::MeshTypeID t0 = getMeshType();
    if ((t0 != Ionflux::GeoUtils::Mesh::TYPE_TRI) 
        && (t0 != Ionflux::GeoUtils::Mesh::TYPE_QUAD))
    {
        std::ostringstream status;
        status << "Unsupported mesh type for serialization (" 
            << getMeshTypeIDString(t0) << ", " << t0 << ").";
        throw IFVGError(getErrorString(status.str(), "serialize"));
    }
    Ionflux::ObjectBase::pack(t0, target);
    // vertices
    Ionflux::ObjectBase::UInt64 numVerts = getNumVertices();
    Ionflux::ObjectBase::pack(numVerts, target);
    for (unsigned int i = 0; 
        i < static_cast<unsigned int>(numVerts); i++)
    {
        Ionflux::GeoUtils::Vertex3* cv = 
            Ionflux::ObjectBase::nullPointerCheck(getVertex(i), 
                this, "serialize", "Vertex");
        cv->serialize(target, false);
    }
    // faces
    Ionflux::ObjectBase::UInt64 numFaces = getNumFaces();
    Ionflux::ObjectBase::pack(numFaces, target);
    unsigned int nfv0 = getNumVerticesPerFace(t0);
    for (unsigned int i = 0; 
        i < static_cast<unsigned int>(numFaces); i++)
    {
        Ionflux::GeoUtils::Face* cf = 
            Ionflux::ObjectBase::nullPointerCheck(getFace(i), 
                this, "serialize", "Face");
        for (unsigned int k = 0; k < nfv0; k++)
        {
            Ionflux::ObjectBase::UInt64 vi = cf->getVertex(k);
            Ionflux::ObjectBase::pack(vi, target);
        }
    }
	return true;
}

Ionflux::ObjectBase::DataSize Mesh::deserialize(std::istream& source, Ionflux::ObjectBase::DataSize offset, bool checkMagicWord)
{
    if (offset != Ionflux::ObjectBase::DATA_SIZE_INVALID)
    {
        source.seekg(offset);
        if (!source.good())
        {
            std::ostringstream status;
            status << "Invalid stream offset: " << offset;
            throw IFVGError(getErrorString(status.str(), "deserialize"));
        }
    }
    Ionflux::ObjectBase::IFObject::deserialize(source, 
        Ionflux::ObjectBase::DATA_SIZE_INVALID, checkMagicWord);
    // mesh type
    Ionflux::GeoUtils::MeshTypeID t0;
    Ionflux::ObjectBase::unpack(source, t0);
    if ((t0 != Ionflux::GeoUtils::Mesh::TYPE_TRI) 
        && (t0 != Ionflux::GeoUtils::Mesh::TYPE_QUAD))
    {
        std::ostringstream status;
        status << "Unsupported mesh type for deserialization (" 
            << getMeshTypeIDString(t0) << ", " << t0 << ").";
        throw IFVGError(getErrorString(status.str(), "deserialize"));
    }
    unsigned int nfv0 = getNumVerticesPerFace(t0);
    // vertices
    Ionflux::GeoUtils::Vertex3Vector v0;
    Ionflux::ObjectBase::unpackObjVec0(source, v0, 
        Ionflux::ObjectBase::DATA_SIZE_INVALID, false);
    unsigned int numVerts = v0.size();
    if (numVerts == 0)
        setVertexSource(0);
    else
    {
        setVertexSource(Ionflux::GeoUtils::Vertex3Set::create());
        addVertices(v0);
    }
    // faces
    clearFaces();
    Ionflux::ObjectBase::UInt64 numFaces;
    Ionflux::ObjectBase::unpack(source, numFaces);
    for (unsigned int i = 0; 
        i < static_cast<unsigned int>(numFaces); i++)
    {
        Ionflux::GeoUtils::Face* cf = addFace();
        for (unsigned int k = 0; k < nfv0; k++)
        {
            Ionflux::ObjectBase::UInt64 vi;
            Ionflux::ObjectBase::unpack(source, vi);
            cf->addVertex(static_cast<unsigned int>(vi));
        }
    }
    update(false, false);
	return source.tellg();
}

bool Mesh::serialize(Ionflux::ObjectBase::IFIOContext& ioCtx, bool addMagicWord) const
{
	std::ostream* os0 = Ionflux::ObjectBase::nullPointerCheck(
	    ioCtx.getOutputStream(), this, "serialize", "Output stream");
    return serialize(*os0, addMagicWord);
}

Ionflux::ObjectBase::DataSize Mesh::deserialize(Ionflux::ObjectBase::IFIOContext& ioCtx, Ionflux::ObjectBase::DataSize offset, bool checkMagicWord)
{
	std::istream* is0 = Ionflux::ObjectBase::nullPointerCheck(
	    ioCtx.getInputStream(), this, "deserialize", "Input stream");
    return deserialize(*is0, offset, checkMagicWord);
}

Ionflux::ObjectBase::MagicSyllable Mesh::getMagicSyllable() const
{
    return MAGIC_SYLLABLE_OBJECT;
}

Ionflux::ObjectBase::MagicSyllable Mesh::getMagicSyllableBase() const
{
    return MAGIC_SYLLABLE_BASE;
}

Ionflux::VolGfx::Mesh& Mesh::operator=(const Ionflux::VolGfx::Mesh& other)
{
    if (this == &other)
        return *this;
    Ionflux::GeoUtils::Mesh::operator=(other);
	return *this;
}

Ionflux::VolGfx::Mesh* Mesh::copy() const
{
    Mesh* newMesh = create();
    *newMesh = *this;
    return newMesh;
}

Ionflux::VolGfx::Mesh* Mesh::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Mesh*>(other);
}

Ionflux::VolGfx::Mesh* Mesh::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Mesh* newObject = new Mesh();
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::VolGfx::Mesh* Mesh::create(Ionflux::GeoUtils::Vertex3Vector* 
initVerts, const Ionflux::GeoUtils::FaceVector* initFaces, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Mesh* newObject = new Mesh(initVerts, initFaces);
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::VolGfx::Mesh* Mesh::create(Ionflux::GeoUtils::Vertex3Set* 
initVertexSource, const Ionflux::GeoUtils::FaceVector* initFaces, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Mesh* newObject = new Mesh(initVertexSource, initFaces);
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Mesh::getMemSize() const
{
    return sizeof *this;
}

std::string Mesh::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Mesh::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::GeoUtils::Mesh::getXMLAttributeData();
	return d0.str();
}

void Mesh::getXMLChildData(std::string& target, unsigned int indentLevel) 
const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::GeoUtils::Mesh::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void Mesh::loadFromXMLFile(const std::string& fileName, const std::string& 
elementName)
{
	std::string en0(elementName);
	if (en0.size() == 0)
	    en0 = getXMLElementName();
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, en0);
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
Mesh::getXMLObjectFactory()
{
	static Ionflux::VolGfx::XMLUtils::MeshXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::VolGfx::XMLUtils::MeshXMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 0;
        bFac = Ionflux::GeoUtils::Mesh::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file Mesh.cpp
 * \brief Mesh implementation.
 */
