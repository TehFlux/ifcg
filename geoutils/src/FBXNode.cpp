/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FBXNode.cpp                     FBX Node (implementation).
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

#include "geoutils/FBXNode.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fbxsdk.h>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Matrix4.hpp"
#include "geoutils/Mesh.hpp"
#include "geoutils/Face.hpp"
#include "geoutils/Vertex3.hpp"
#include "geoutils/fbxutils.hpp"
#include "geoutils/fbxutils_private.hpp"

namespace Ionflux
{

namespace GeoUtils
{

FBXNodeClassInfo::FBXNodeClassInfo()
{
	name = "FBXNode";
	desc = "FBX Node";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

FBXNodeClassInfo::~FBXNodeClassInfo()
{
}

// public member constants
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_UNKNOWN = 0;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_NULL = 1;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_MARKER = 2;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_SKELETON = 3;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_MESH = 4;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_NURBS = 5;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_PATCH = 6;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_CAMERA = 7;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_CAMERASTEREO = 8;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_CAMERASWITCHER = 9;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_LIGHT = 10;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_OPTICALREFERENCE = 11;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_OPTICALMARKER = 12;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_NURBSCURVE = 13;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_TRIMNURBSSURFACE = 14;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_BOUNDARY = 15;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_NURBSSURFACE = 16;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_SHAPE = 17;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_LODGROUP = 18;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_SUBDIV = 19;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_CACHEDEFFECT = 20;
const Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::TYPE_LINE = 21;

// run-time type information instance constants
const FBXNodeClassInfo FBXNode::fBXNodeClassInfo;
const Ionflux::ObjectBase::IFClassInfo* FBXNode::CLASS_INFO = &FBXNode::fBXNodeClassInfo;

FBXNode::FBXNode()
: impl(0), transformMatrix(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

FBXNode::FBXNode(const Ionflux::GeoUtils::FBXNode& other)
: impl(0), transformMatrix(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

FBXNode::FBXNode(FBXSDK_NAMESPACE::FbxNode* initImpl)
: impl(0), transformMatrix(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initImpl != 0)
	    setImpl(initImpl);
}

FBXNode::~FBXNode()
{
	impl = 0;
}

void FBXNode::update()
{
	if (impl == 0)
	    return;
	Matrix4 M0(getMatrix(impl->EvaluateLocalTransform(FBXSDK_TIME_ZERO)));
	if (M0.eq(Matrix4::UNIT))
	{
	    if (transformMatrix != 0)
	        setTransformMatrix(0);
	    return;
	}
	Matrix4* m1 = transformMatrix;
	if (m1 == 0)
	{
	    m1 = Matrix4::create();
	    setTransformMatrix(m1);
	}
	m1->setElements(M0);
	/*
	Vector3 t0 = getVector(impl->LclTranslation.Get());
	Vector3 r0 = getVector(impl->LclRotation.Get());
	Vector3 s0 = getVector(impl->LclScaling.Get());
	if (t0.eq(Vector3::ZERO) 
	    && r0.eq(Vector3::ZERO) 
	    && s0.eq(Vector3::E_SUM))
	{
	    if (transformMatrix != 0)
	        setTransformMatrix(0);
	    return;
	}
	Matrix4* m0 = transformMatrix;
	if (m0 == 0)
	{
	    m0 = Matrix4::create();
	    setTransformMatrix(m0);
	}
	m0->setIdentity();
	if (!s0.eq(Vector3::E_SUM))
	{
	    Matrix4 S0(Matrix4::scale(s0));
	    m0->multiplyLeft(S0);
	}
	if (!r0.eq(Vector3::ZERO))
	{
	    Matrix4 R0(Matrix3::rotate(r0.norm(), r0.normalize()));
	    m0->multiplyLeft(R0);
	}
	if (!t0.eq(Vector3::ZERO))
	{
	    Matrix4 T0(Matrix4::translate(t0));
	    m0->multiplyLeft(T0);
	}
	*/
}

Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::getAttributeType() const
{
	if (impl == 0)
	    return TYPE_UNKNOWN;
	FbxNodeAttribute* attr0 = impl->GetNodeAttribute();
	if (attr0 == 0)
	    return TYPE_NULL;
	return getFBXNodeAttributeType(attr0->GetAttributeType());
}

std::string FBXNode::getName() const
{
	if (impl == 0)
	    return "";
	std::string result(impl->GetName());
	return result;
}

int FBXNode::getNumChildNodes() const
{
	if (impl == 0)
	    return 0;
	return impl->GetChildCount();
}

Ionflux::GeoUtils::FBXNode* FBXNode::getChildNode(int index) const
{
	if (impl == 0)
	    return 0;
	FbxNode* c0 = impl->GetChild(index);
	if (c0 == 0)
	    return 0;
	FBXNode* result = FBXNode::create(c0);
	return result;
}

void FBXNode::listChildNodes(bool recursive, unsigned int indentWidth, char
indentChar, unsigned int depth) const
{
	std::string indent = Ionflux::ObjectBase::getIndent(depth, 
	    indentWidth, indentChar);
	int numChildNodes = getNumChildNodes();
	for (int i = 0; i < numChildNodes; i++)
	{
	    FBXNode* n0 = getChildNode(i);
	    if (n0 != 0)
	    {
	        addLocalRef(n0);
	        std::cout << indent << "[" << n0->getValueString() << "]" 
	            << std::endl;
	        if (recursive)
	        {
	            n0->listChildNodes(true, indentWidth, indentChar, 
	                depth + 1);
	        }
	        removeLocalRef(n0);
	    }
	}
}

Ionflux::GeoUtils::FBXNode* FBXNode::findChildNodeByName(const std::string&
needle, bool recursive)
{
	if ((getName() == needle) 
	    || !recursive)
	    return this;
	int numChildNodes = getNumChildNodes();
	int i = 0;
	FBXNode* result = 0;
	while ((result == 0) 
	    && (i < numChildNodes))
	{
	    FBXNode* n0 = getChildNode(i);
	    if (n0 != 0)
	    {
	        result = n0->findChildNodeByName(needle, true);
	        if (n0 != result)
	            delete n0;
	    }
	    i++;
	}
	return result;
}

unsigned int FBXNode::getMesh(Ionflux::GeoUtils::Mesh& target, bool 
recursive, Ionflux::GeoUtils::Matrix4* localTransform, bool 
applyNodeTransform0) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, "getMesh", 
	    "Node implementation");
	FBXNodeAttributeType t0 = getAttributeType();
	if ((t0 != TYPE_MESH) 
	    && !recursive)
	    return 0;
	unsigned int numMeshes = 0;
	if (t0 == TYPE_MESH)
	{
	    // extract the mesh
	    FbxMesh* fbm0 = impl->GetMesh();
	    Ionflux::ObjectBase::nullPointerCheck(fbm0, this, "getMesh", 
	        "Mesh data");
	    int numVerts0 = fbm0->GetControlPointsCount();
	    int numFaces0 = fbm0->GetPolygonCount();
	    // <---- DEBUG ----- //
	    std::cerr << "[FBXNode::getMesh] DEBUG: "
	        "merging mesh '" << getName() << "': " << "numVerts = " 
	        << numVerts0 << ", numFaces = " << numFaces0 
	        << std::endl;
	    /* ----- DEBUG ----> */
	    Ionflux::GeoUtils::Mesh m0;
	    // vertices
	    for (int i = 0; i < numVerts0; i++)
	    {
	        FbxVector4 v0 = fbm0->GetControlPointAt(i);
	        Vertex3* cv = m0.addVertex();
	        cv->setCoords(v0[0], v0[1], v0[2]);
	    }
	    // faces
	    for (int i = 0; i < numFaces0; i++)
	    {
	        int n0 = fbm0->GetPolygonSize(i);
	        if (n0 < 0)
	        {
	            std::ostringstream status;
	            status << "Invalid polygon index (" << i << ").";
	            throw GeoUtilsError(getErrorString(status.str(), 
	                "getMesh"));
	        }
	        // <---- DEBUG ----- //
	        if (n0 > 4)
	        {
	            std::cerr << "[FBXNode::getMesh] DEBUG: "
	                "number of face vertices for face #" << i << ": " 
	                << n0 << std::endl;
	        }
	        /* ----- DEBUG ----> */
	        Face* cf = m0.addFace();
	        for (int j = 0; j < n0; j++)
	        {
	            int v0 = fbm0->GetPolygonVertex(i, j);
	            cf->addVertex(v0);
	        }
	    }
	    if (applyNodeTransform0)
	    {
	        // <---- DEBUG ----- //
	        m0.update();
	        Range3 bb0 = m0.getBounds();
	        Vector3 c0 = bb0.getCenter();
	        Vector3 e0 = bb0.getExtent();
	        std::cerr << "[FBXNode::getMesh] DEBUG: "
	            "mesh '" << getName() << "': transformMatrix = ";
	        if (transformMatrix != 0)
	        {
	            std::cerr << "[" << transformMatrix->getValueString() 
	                << "]";
	        } else
	            std::cerr << "<none>";
	        std::cerr << ", localTransform = ";
	        if ((localTransform != 0) 
	            && !localTransform->eq(Matrix4::UNIT))
	        {
	            std::cerr << "[" << localTransform->getValueString() 
	                << "]";
	        } else
	        if ((localTransform != 0) 
	            && localTransform->eq(Matrix4::UNIT))
	        {
	            std::cerr << "UNIT [" 
	                << localTransform->getValueString() << "]";
	        } else
	            std::cerr << "<none>";
	        std::cerr << ", bBox = [" << bb0.getValueString() 
	            << "], center = (" << c0.getValueString() 
	            << "), extent = (" << e0.getValueString() << ")";
	        std::cerr << std::endl;
	        // ----- DEBUG ----> */
	        if (transformMatrix != 0)
	        {
	            // apply transform of this node
	            m0.transform(*transformMatrix);
	        }
	        if ((localTransform != 0) 
	            && !localTransform->eq(Matrix4::UNIT))
	        {
	            // apply local transform
	            m0.transform(*localTransform);
	        }
	        m0.applyTransform(true);
	        // <---- DEBUG ----- //
	        m0.update();
	        bb0 = m0.getBounds();
	        c0 = bb0.getCenter();
	        e0 = bb0.getExtent();
	        std::cerr << "[FBXNode::getMesh] DEBUG: "
	            "mesh '" << getName() << "' after transform: "
	            << ", bBox = [" << bb0.getValueString() 
	            << "], center = (" << c0.getValueString() 
	            << "), extent = (" << e0.getValueString() << ")" 
	            << std::endl;
	        // ----- DEBUG ----> */
	    }
	    target.merge(m0);
	    numMeshes++;
	}
	if (!recursive)
	    return numMeshes;
	// determine local transformation for child meshes
	Matrix4 T0(Matrix4::UNIT);
	bool useLT = false;
	if (applyNodeTransform0)
	{
	    if (transformMatrix != 0)
	        T0.multiplyLeft(*transformMatrix);
	    if ((localTransform != 0) 
	        && !localTransform->eq(Matrix4::UNIT))
	        T0.multiplyLeft(*localTransform);
	    if (!T0.eq(Matrix4::UNIT))
	        useLT = true;
	}
	// <---- DEBUG ----- //
	if (useLT)
	{
	    std::cerr << "[FBXNode::getMesh] DEBUG: "
	        "node '" << getName() << "': local transformation: [" 
	        << T0.getValueString() << "]";
	    if (transformMatrix != 0)
	    {
	        std::cerr << ", transformMatrix = [" 
	            << transformMatrix->getValueString() << "]";
	    }
	    if (localTransform != 0)
	    {
	        std::cerr << ", localTransform = [" 
	            << localTransform->getValueString() << "]";
	    }
	    std::cerr << std::endl;
	}
	/* ----- DEBUG ----> */
	// recursively merge meshes
	int numChildNodes = getNumChildNodes();
	for (int i = 0; i < numChildNodes; i++)
	{
	    FBXNode* n0 = getChildNode(i);
	    if (n0 != 0)
	    {
	        addLocalRef(n0);
	        if (useLT)
	            numMeshes += n0->getMesh(target, true, &T0, 
	                applyNodeTransform0);
	        else
	            numMeshes += n0->getMesh(target, true, 0, 
	                applyNodeTransform0);
	        removeLocalRef(n0);
	    }
	}
	return numMeshes;
}

unsigned int FBXNode::dumpMesh(const std::string& targetPath, bool 
recursive, Ionflux::GeoUtils::Matrix4* localTransform, unsigned int 
startIndex, double scale0, bool applyNodeTransform0) const
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, "dumpMesh", 
	    "Node implementation");
	FBXNodeAttributeType t0 = getAttributeType();
	if ((t0 != TYPE_MESH) 
	    && !recursive)
	    return 0;
	unsigned int numMeshes = 0;
	if (t0 == TYPE_MESH)
	{
	    // extract the mesh
	    Mesh m0;
	    getMesh(m0, false, localTransform, applyNodeTransform0);
	    m0.update();
	    std::string nn0(getName());
	    std::ostringstream mn0;
	    if (nn0.size() == 0)
	        mn0 << "UnnamedNode_" << startIndex;
	    else
	        mn0 << nn0;
	    m0.setID(mn0.str());
	    if (scale0 != 1.)
	    {
	        Vector3 sv0(scale0, scale0, scale0);
	        m0.scale(sv0);
	    }
	    // <---- DEBUG ----- //
	    unsigned int nv0 = m0.getNumVertices();
	    unsigned int nf0 = m0.getNumFaces();
	    std::cerr << "[FBXNode::dumpMesh] DEBUG: "
	        "extracted mesh '" << mn0.str() << "': " << "numVerts = " 
	        << nv0 << ", numFaces = " << nf0 << std::endl;
	    /* ----- DEBUG ----> */
	    std::ostringstream fn0;
	    if (targetPath.size() > 0)
	        fn0 << targetPath << Ionflux::ObjectBase::DIR_SEPARATOR;
	    fn0 << std::setw(6) << std::setfill('0') << startIndex << "_" 
	        << mn0.str() << ".xml";
	    // <---- DEBUG ----- //
	    std::cerr << "[FBXNode::dumpMesh] DEBUG: "
	        "writing mesh to file '" << fn0.str() << "'..." << std::endl;
	    /* ----- DEBUG ----> */
	    m0.applyTransform(true);
	    m0.writeToXMLFile(fn0.str());
	    numMeshes++;
	}
	if (!recursive)
	    return numMeshes;
	// determine local transformation for child meshes
	Matrix4 T0(Matrix4::UNIT);
	bool useLT = false;
	if (applyNodeTransform0)
	{
	    if (transformMatrix != 0)
	        T0.multiplyLeft(*transformMatrix);
	    if ((localTransform != 0) 
	        && !localTransform->eq(Matrix4::UNIT))
	        T0.multiplyLeft(*localTransform);
	    if (!T0.eq(Matrix4::UNIT))
	        useLT = true;
	}
	// <---- DEBUG ----- //
	if (useLT)
	{
	    std::cerr << "[FBXNode::dumpMesh] DEBUG: "
	        "node '" << getName() << "': local transformation: [" 
	        << T0.getValueString() << "]";
	    if (transformMatrix != 0)
	    {
	        std::cerr << ", transformMatrix = [" 
	            << transformMatrix->getValueString() << "]";
	    }
	    if (localTransform != 0)
	    {
	        std::cerr << ", localTransform = [" 
	            << localTransform->getValueString() << "]";
	    }
	    std::cerr << std::endl;
	}
	/* ----- DEBUG ----> */
	// recursively dump meshes
	int numChildNodes = getNumChildNodes();
	for (int i = 0; i < numChildNodes; i++)
	{
	    FBXNode* n0 = getChildNode(i);
	    if (n0 != 0)
	    {
	        addLocalRef(n0);
	        unsigned int nm0 = 0;
	        if (useLT)
	            nm0 += n0->dumpMesh(targetPath, true, &T0, 
	                startIndex, scale0, applyNodeTransform0);
	        else
	            nm0 += n0->dumpMesh(targetPath, true, 0, 
	                startIndex, scale0, applyNodeTransform0);
	        startIndex += nm0;
	        numMeshes += nm0;
	        removeLocalRef(n0);
	    }
	}
	return numMeshes;
}

std::string FBXNode::getValueString() const
{
	std::ostringstream status;
	status << getFBXNodeAttributeTypeString(getAttributeType());
	std::string n0(getName());
	if (n0.size() > 0)
	    status << "; '" << n0 << "'";
	if (transformMatrix != 0)
	    status << "; [" << transformMatrix->getValueString() << "]";
	return status.str();
}

void FBXNode::setImpl(FBXSDK_NAMESPACE::FbxNode* newImpl)
{
	if (newImpl == impl)
	    return;
	impl = newImpl;
	update();
}

FBXSDK_NAMESPACE::FbxNode* FBXNode::getImpl() const
{
    return impl;
}

void FBXNode::setTransformMatrix(Ionflux::GeoUtils::Matrix4* 
newTransformMatrix)
{
	if (transformMatrix == newTransformMatrix)
		return;
    if (newTransformMatrix != 0)
        addLocalRef(newTransformMatrix);
	if (transformMatrix != 0)
		removeLocalRef(transformMatrix);
	transformMatrix = newTransformMatrix;
}

Ionflux::GeoUtils::Matrix4* FBXNode::getTransformMatrix() const
{
    return transformMatrix;
}

Ionflux::GeoUtils::FBXNode& FBXNode::operator=(const 
Ionflux::GeoUtils::FBXNode& other)
{
    if (this == &other)
        return *this;
    setImpl(other.impl);
	return *this;
}

Ionflux::GeoUtils::FBXNode* FBXNode::copy() const
{
    FBXNode* newFBXNode = create();
    *newFBXNode = *this;
    return newFBXNode;
}

Ionflux::GeoUtils::FBXNode* FBXNode::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<FBXNode*>(other);
}

Ionflux::GeoUtils::FBXNode* FBXNode::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    FBXNode* newObject = new FBXNode();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::FBXNode* FBXNode::create(FBXSDK_NAMESPACE::FbxNode* 
initImpl, Ionflux::ObjectBase::IFObject* parentObject)
{
    FBXNode* newObject = new FBXNode(initImpl);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int FBXNode::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file FBXNode.cpp
 * \brief FBX Node implementation.
 */
