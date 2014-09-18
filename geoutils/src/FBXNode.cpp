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
#include "geoutils/FBXNodeSet.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "geoutils/xmlutils.hpp"
#include "geoutils/xmlio/FBXNodeXMLFactory.hpp"

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

const std::string FBXNode::XML_ELEMENT_NAME = "fbxnode";

FBXNode::FBXNode()
: impl(0), localTransform(0), globalTransform(0), attributeType(TYPE_UNKNOWN), name(""), bounds(0), numVerts(0), numFaces(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

FBXNode::FBXNode(const Ionflux::GeoUtils::FBXNode& other)
: impl(0), localTransform(0), globalTransform(0), attributeType(TYPE_UNKNOWN), name(""), bounds(0), numVerts(0), numFaces(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

FBXNode::FBXNode(FBXSDK_NAMESPACE::FbxNode* initImpl)
: impl(0), localTransform(0), globalTransform(0), 
attributeType(TYPE_UNKNOWN), name(""), bounds(0), numVerts(0), numFaces(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initImpl != 0)
	    setImpl(initImpl);
}

FBXNode::~FBXNode()
{
	clearChildNodes();
	impl = 0;
}

void FBXNode::update()
{
	if (impl == 0)
	{
	    setAttributeType(TYPE_UNKNOWN);
	    setName("");
	    return;
	}
	setName(impl->GetName());
	FbxNodeAttribute* attr0 = impl->GetNodeAttribute();
	if (attr0 == 0)
	    setAttributeType(TYPE_NULL);
	else
	{
	    setAttributeType(getFBXNodeAttributeType(
	        attr0->GetAttributeType()));
	}
	updateTransformFBX();
}

int FBXNode::getNumChildNodesFBX() const
{
	if (impl == 0)
	    return 0;
	return impl->GetChildCount();
}

Ionflux::GeoUtils::FBXNode* FBXNode::getChildNodeFBX(int index) const
{
	if (impl == 0)
	    return 0;
	FbxNode* c0 = impl->GetChild(index);
	if (c0 == 0)
	    return 0;
	FBXNode* result = FBXNode::create(c0);
	return result;
}

void FBXNode::addChildNodesFBX(bool recursive)
{
	int n0 = getNumChildNodesFBX();
	for (int i = 0; i < n0; i++)
	{
	    Ionflux::GeoUtils::FBXNode* cn = getChildNodeFBX(i);
	    if (cn != 0)
	    {
	        /* <---- DEBUG ----- //
	        std::cerr << "[FBXNode::addChildNodesFBX] DEBUG: "
	            "adding child node: [" << cn->getValueString() << "]." 
	            << std::endl;
	        // ----- DEBUG ----> */
	        addChildNode(cn);
	        if (recursive)
	            cn->addChildNodesFBX(true);
	    }
	}
}

void FBXNode::listChildNodesFBX(bool recursive, unsigned int indentWidth, 
char indentChar, unsigned int depth) const
{
	std::string indent = Ionflux::ObjectBase::getIndent(depth, 
	    indentWidth, indentChar);
	int numChildNodes = getNumChildNodesFBX();
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
	            n0->listChildNodesFBX(true, indentWidth, indentChar, 
	                depth + 1);
	        }
	        removeLocalRef(n0);
	    }
	}
}

Ionflux::GeoUtils::FBXNode* FBXNode::findChildNodeByNameFBX(const 
std::string& needle, bool recursive)
{
	if ((getName() == needle) 
	    || !recursive)
	    return this;
	int numChildNodes = getNumChildNodesFBX();
	int i = 0;
	FBXNode* result = 0;
	while ((result == 0) 
	    && (i < numChildNodes))
	{
	    FBXNode* n0 = getChildNodeFBX(i);
	    if (n0 != 0)
	    {
	        result = n0->findChildNodeByNameFBX(needle, true);
	        if (n0 != result)
	            delete n0;
	    }
	    i++;
	}
	return result;
}

unsigned int FBXNode::getMesh(Ionflux::GeoUtils::Mesh& target, bool 
recursive, Ionflux::GeoUtils::Matrix4* localTransform0, bool 
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
	    /* <---- DEBUG ----- //
	    std::cerr << "[FBXNode::getMesh] DEBUG: "
	        "merging mesh '" << getName() << "': " << "numVerts = " 
	        << numVerts0 << ", numFaces = " << numFaces0 
	        << std::endl;
	    // ----- DEBUG ----> */
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
	        /* <---- DEBUG ----- //
	        if (n0 > 4)
	        {
	            std::cerr << "[FBXNode::getMesh] DEBUG: "
	                "number of face vertices for face #" << i << ": " 
	                << n0 << std::endl;
	        }
	        // ----- DEBUG ----> */
	        Face* cf = m0.addFace();
	        for (int j = 0; j < n0; j++)
	        {
	            int v0 = fbm0->GetPolygonVertex(i, j);
	            cf->addVertex(v0);
	        }
	    }
	    if (applyNodeTransform0)
	    {
	        /* <---- DEBUG ----- //
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
	        if ((localTransform0 != 0) 
	            && !localTransform0->eq(Matrix4::UNIT))
	        {
	            std::cerr << "[" << localTransform0->getValueString() 
	                << "]";
	        } else
	        if ((localTransform0 != 0) 
	            && localTransform0->eq(Matrix4::UNIT))
	        {
	            std::cerr << "UNIT [" 
	                << localTransform0->getValueString() << "]";
	        } else
	            std::cerr << "<none>";
	        std::cerr << ", bBox = [" << bb0.getValueString() 
	            << "], center = (" << c0.getValueString() 
	            << "), extent = (" << e0.getValueString() << ")";
	        std::cerr << std::endl;
	        // ----- DEBUG ----> */
	        if (localTransform != 0)
	        {
	            // apply transform of this node
	            m0.transform(*localTransform);
	        }
	        if ((localTransform0 != 0) 
	            && !localTransform0->eq(Matrix4::UNIT))
	        {
	            // apply local transform
	            m0.transform(*localTransform0);
	        }
	        m0.applyTransform(true);
	        /* <---- DEBUG ----- //
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
	    if (localTransform != 0)
	        T0.multiplyLeft(*localTransform);
	    if ((localTransform0 != 0) 
	        && !localTransform0->eq(Matrix4::UNIT))
	        T0.multiplyLeft(*localTransform0);
	    if (!T0.eq(Matrix4::UNIT))
	        useLT = true;
	}
	/* <---- DEBUG ----- //
	if (useLT)
	{
	    std::cerr << "[FBXNode::getMesh] DEBUG: "
	        "node '" << getName() << "': local transformation: [" 
	        << T0.getValueString() << "]";
	    if (localTransform != 0)
	    {
	        std::cerr << ", transformMatrix = [" 
	            << localTransform->getValueString() << "]";
	    }
	    if (localTransform0 != 0)
	    {
	        std::cerr << ", localTransform = [" 
	            << localTransform0->getValueString() << "]";
	    }
	    std::cerr << std::endl;
	}
	// ----- DEBUG ----> */
	// recursively merge meshes
	int numChildNodes = getNumChildNodesFBX();
	for (int i = 0; i < numChildNodes; i++)
	{
	    FBXNode* n0 = getChildNodeFBX(i);
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
recursive, Ionflux::GeoUtils::Matrix4* localTransform0, unsigned int 
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
	    getMesh(m0, false, localTransform0, applyNodeTransform0);
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
	    /* <---- DEBUG ----- //
	    unsigned int nv0 = m0.getNumVertices();
	    unsigned int nf0 = m0.getNumFaces();
	    std::cerr << "[FBXNode::dumpMesh] DEBUG: "
	        "extracted mesh '" << mn0.str() << "': " << "numVerts = " 
	        << nv0 << ", numFaces = " << nf0 << std::endl;
	    // ----- DEBUG ----> */
	    std::ostringstream fn0;
	    if (targetPath.size() > 0)
	        fn0 << targetPath << Ionflux::ObjectBase::DIR_SEPARATOR;
	    fn0 << std::setw(6) << std::setfill('0') << startIndex << "_" 
	        << mn0.str() << ".xml";
	    /* <---- DEBUG ----- //
	    std::cerr << "[FBXNode::dumpMesh] DEBUG: "
	        "writing mesh to file '" << fn0.str() << "'..." << std::endl;
	    // ----- DEBUG ----> */
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
	    if (localTransform != 0)
	        T0.multiplyLeft(*localTransform);
	    if ((localTransform0 != 0) 
	        && !localTransform0->eq(Matrix4::UNIT))
	        T0.multiplyLeft(*localTransform0);
	    if (!T0.eq(Matrix4::UNIT))
	        useLT = true;
	}
	/* <---- DEBUG ----- //
	if (useLT)
	{
	    std::cerr << "[FBXNode::dumpMesh] DEBUG: "
	        "node '" << getName() << "': local transformation: [" 
	        << T0.getValueString() << "]";
	    if (localTransform != 0)
	    {
	        std::cerr << ", transformMatrix = [" 
	            << localTransform->getValueString() << "]";
	    }
	    if (localTransform0 != 0)
	    {
	        std::cerr << ", localTransform = [" 
	            << localTransform0->getValueString() << "]";
	    }
	    std::cerr << std::endl;
	}
	// ----- DEBUG ----> */
	// recursively dump meshes
	int numChildNodes = getNumChildNodesFBX();
	for (int i = 0; i < numChildNodes; i++)
	{
	    FBXNode* n0 = getChildNodeFBX(i);
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

void FBXNode::updateTransformFBX(bool recursive, 
Ionflux::GeoUtils::Matrix4* localTransform0)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, "updateBoundsFBX", 
	    "Node implementation");
	// local transform
	Matrix4 M0(getMatrix(impl->EvaluateLocalTransform(FBXSDK_TIME_ZERO)));
	if (M0.eq(Matrix4::UNIT))
	{
	    if (localTransform != 0)
	        setLocalTransform(0);
	} else
	{
	    Matrix4* m1 = localTransform;
	    if (m1 == 0)
	    {
	        m1 = Matrix4::create();
	        setLocalTransform(m1);
	    }
	    m1->setElements(M0);
	}
	// global transform
	Matrix4* T0 = Matrix4::create();
	addLocalRef(T0);
	T0->setElements(Matrix4::UNIT);
	bool useLT = false;
	if (localTransform != 0)
	    T0->multiplyLeft(*localTransform);
	if ((localTransform0 != 0) 
	    && !localTransform0->eq(Matrix4::UNIT))
	    T0->multiplyLeft(*localTransform0);
	if (!T0->eq(Matrix4::UNIT))
	    useLT = true;
	if (useLT)
	    setGlobalTransform(T0);
	if (recursive)
	{
	    // process child nodes
	    int numChildNodes = getNumChildNodes();
	    for (int i = 0; i < numChildNodes; i++)
	    {
	        FBXNode* n0 = getChildNode(i);
	        if (n0 != 0)
	        {
	            if (useLT)
	                n0->updateTransformFBX(true, T0);
	            else
	                n0->updateTransformFBX(true);
	        }
	    }
	}
	removeLocalRef(T0);
}

Ionflux::GeoUtils::Range3* FBXNode::updateBoundsFBX(bool recursive, 
Ionflux::GeoUtils::Matrix4* localTransform0)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, "updateBoundsFBX", 
	    "Node implementation");
	FBXNodeAttributeType t0 = getAttributeType();
	if (t0 == TYPE_MESH)
	{
	    if (bounds == 0)
	        setBounds(Range3::create());
	    FbxMesh* fbm0 = impl->GetMesh();
	    Ionflux::ObjectBase::nullPointerCheck(fbm0, this, "updateBoundsFBX", 
	        "Mesh data");
	    int numVerts0 = fbm0->GetControlPointsCount();
	    for (int i = 0; i < numVerts0; i++)
	    {
	        FbxVector4 v0 = fbm0->GetControlPointAt(i);
	        Vertex3 cv;
	        cv.setCoords(v0[0], v0[1], v0[2]);
	        if (localTransform != 0)
	        {
	            // apply transformation of this node
	            cv.transform(*localTransform);
	        }
	        if ((localTransform0 != 0) 
	            && !localTransform0->eq(Matrix4::UNIT))
	        {
	            // apply local transformation
	            cv.transform(*localTransform0);
	        }
	        if (i == 0)
	            bounds->setBounds(cv.getVector());
	        else
	            bounds->extend(cv.getVector());
	    }
	    // <---- DEBUG ----- //
	    std::cerr << "[FBXNode::updateBoundsFBX] DEBUG: "
	        "node [" << getValueString() << "] bounds = [" 
	        << bounds->getValueString() << "]" << std::endl;
	    // ----- DEBUG ----> */
	} else
	{
	    if (bounds != 0)
	        setBounds(0);
	}
	if (!recursive)
	    return bounds;
	// determine local transformation for child nodes
	Matrix4 T0(Matrix4::UNIT);
	bool useLT = false;
	if (localTransform != 0)
	    T0.multiplyLeft(*localTransform);
	if ((localTransform0 != 0) 
	    && !localTransform0->eq(Matrix4::UNIT))
	    T0.multiplyLeft(*localTransform0);
	if (!T0.eq(Matrix4::UNIT))
	    useLT = true;
	// process child nodes
	int numChildNodes = getNumChildNodes();
	for (int i = 0; i < numChildNodes; i++)
	{
	    FBXNode* n0 = getChildNode(i);
	    if (n0 != 0)
	    {
	        if (useLT)
	            n0->updateBoundsFBX(true, &T0);
	        else
	            n0->updateBoundsFBX(true);
	    }
	}
	return bounds;
}

void FBXNode::updateMeshDataFBX(bool recursive)
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, "updateMeshDataFBX", 
	    "Node implementation");
	FBXNodeAttributeType t0 = getAttributeType();
	if (t0 == TYPE_MESH)
	{
	    FbxMesh* fbm0 = impl->GetMesh();
	    Ionflux::ObjectBase::nullPointerCheck(fbm0, this, "updateMeshDataFBX",
	
        "Mesh data");
	    setNumVerts(fbm0->GetControlPointsCount());
	    setNumFaces(fbm0->GetPolygonCount());
	    // <---- DEBUG ----- //
	    std::cerr << "[FBXNode::updateMeshDataFBX] DEBUG: "
	        "node [" << getValueString() << "] numVerts = " 
	        << numVerts << ", numFaces = " << numFaces << std::endl;
	    // ----- DEBUG ----> */
	} else
	{
	    setNumVerts(0);
	    setNumFaces(0);
	}
	if (recursive)
	{
	    int numChildNodes = getNumChildNodes();
	    for (int i = 0; i < numChildNodes; i++)
	    {
	        FBXNode* n0 = getChildNode(i);
	        if (n0 != 0)
	            n0->updateMeshDataFBX(true);
	    }
	}
}

bool FBXNode::getHierarchyBounds(Ionflux::GeoUtils::Range3& target, bool 
valid)
{
	if (bounds != 0)
	{
	    if (valid)
	        target.extend(*bounds);
	    else
	    {
	        target.setBounds(*bounds);
	        valid = true;
	    }
	}
	int numChildNodes = getNumChildNodes();
	for (int i = 0; i < numChildNodes; i++)
	{
	    FBXNode* n0 = getChildNode(i);
	    if (n0 != 0)
	    {
	        if (n0->getHierarchyBounds(target, valid))
	            valid = true;
	    }
	}
	return valid;
}

unsigned int FBXNode::getHierarchyNumVerts()
{
	unsigned int nv0 = getNumVerts();
	int numChildNodes = getNumChildNodes();
	for (int i = 0; i < numChildNodes; i++)
	{
	    FBXNode* n0 = getChildNode(i);
	    if (n0 != 0)
	        nv0 += n0->getHierarchyNumVerts();
	}
	return nv0;
}

unsigned int FBXNode::getHierarchyNumFaces()
{
	unsigned int nf0 = getNumFaces();
	int numChildNodes = getNumChildNodes();
	for (int i = 0; i < numChildNodes; i++)
	{
	    FBXNode* n0 = getChildNode(i);
	    if (n0 != 0)
	        nf0 += n0->getHierarchyNumFaces();
	}
	return nf0;
}

unsigned int FBXNode::assignNodeIDs(const std::string& prefix, unsigned int
width, char fillChar, unsigned int offset)
{
	std::ostringstream id0;
	id0 << prefix << std::setw(width) << std::setfill(fillChar) 
	    << std::right << offset;
	setID(id0.str());
	setIDNum(offset);
	offset += 1;
	int n0 = getNumChildNodes();
	for (int i = 0; i < n0; i++)
	{
	    Ionflux::GeoUtils::FBXNode* cn = getChildNode(i);
	    if (cn != 0)
	        offset = cn->assignNodeIDs(prefix, width, fillChar, offset);
	}
	return offset;
}

Ionflux::GeoUtils::FBXNode* FBXNode::findNodeByName(const std::string& 
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
	        result = n0->findNodeByName(needle, true);
	    i++;
	}
	return result;
}

Ionflux::GeoUtils::FBXNode* FBXNode::findNodeByID(const std::string& 
needle, bool recursive)
{
	if ((getID() == needle) 
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
	        result = n0->findNodeByID(needle, true);
	    i++;
	}
	return result;
}

unsigned int 
FBXNode::findNodesByAttributeType(Ionflux::GeoUtils::FBXNodeAttributeType 
t, Ionflux::GeoUtils::FBXNodeSet& target, bool recursive)
{
	unsigned int numNodes = 0;
	if (getAttributeType() == t)
	{
	    target.addNode(this);
	    numNodes++;
	}
	if (!recursive)
	    return numNodes;
	int n0 = getNumChildNodes();
	for (int i = 0; i < n0; i++)
	{
	    FBXNode* cn = getChildNode(i);
	    if (cn != 0)
	        numNodes += cn->findNodesByAttributeType(t, target, true);
	}
	return numNodes;
}

std::string FBXNode::getValueString() const
{
	std::ostringstream status;
	status << getFBXNodeAttributeTypeString(getAttributeType());
	std::string n0(getName());
	if (n0.size() > 0)
	    status << "; '" << n0 << "'";
	if (localTransform != 0)
	    status << "; local_t = [" 
	        << localTransform->getValueString() << "]";
	if (globalTransform != 0)
	    status << "; global_t = [" 
	        << globalTransform->getValueString() << "]";
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

void FBXNode::setLocalTransform(Ionflux::GeoUtils::Matrix4* 
newLocalTransform)
{
	if (localTransform == newLocalTransform)
		return;
    if (newLocalTransform != 0)
        addLocalRef(newLocalTransform);
	if (localTransform != 0)
		removeLocalRef(localTransform);
	localTransform = newLocalTransform;
}

Ionflux::GeoUtils::Matrix4* FBXNode::getLocalTransform() const
{
    return localTransform;
}

void FBXNode::setGlobalTransform(Ionflux::GeoUtils::Matrix4* 
newGlobalTransform)
{
	if (globalTransform == newGlobalTransform)
		return;
    if (newGlobalTransform != 0)
        addLocalRef(newGlobalTransform);
	if (globalTransform != 0)
		removeLocalRef(globalTransform);
	globalTransform = newGlobalTransform;
}

Ionflux::GeoUtils::Matrix4* FBXNode::getGlobalTransform() const
{
    return globalTransform;
}

unsigned int FBXNode::getNumChildNodes() const
{
    return childNodes.size();
}

Ionflux::GeoUtils::FBXNode* FBXNode::getChildNode(unsigned int 
elementIndex) const
{
    if (elementIndex < childNodes.size())
		return childNodes[elementIndex];
	return 0;
}

int FBXNode::findChildNode(Ionflux::GeoUtils::FBXNode* needle, unsigned int
occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::FBXNode* currentChildNode = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < childNodes.size()))
	{
		currentChildNode = childNodes[i];
		if (currentChildNode == needle)
        {
            if (occurence == 1)
			    found = true;
            else
                occurence--;
		} else
			i++;
	}
	if (found)
        return i;
	return -1;
}

std::vector<Ionflux::GeoUtils::FBXNode*>& FBXNode::getChildNodes()
{
    return childNodes;
}

void FBXNode::addChildNode(Ionflux::GeoUtils::FBXNode* addElement)
{
	addLocalRef(addElement);
	childNodes.push_back(addElement);
}

Ionflux::GeoUtils::FBXNode* FBXNode::addChildNode()
{
	Ionflux::GeoUtils::FBXNode* o0 = FBXNode::create();
	addChildNode(o0);
	return o0;
}

void FBXNode::addChildNodes(const std::vector<Ionflux::GeoUtils::FBXNode*>&
newChildNodes)
{
	for (std::vector<Ionflux::GeoUtils::FBXNode*>::const_iterator i = newChildNodes.begin(); 
	    i != newChildNodes.end(); i++)
	    addChildNode(*i);
}

void FBXNode::addChildNodes(Ionflux::GeoUtils::FBXNode* newChildNodes)
{
	for (unsigned int i = 0; 
	    i < newChildNodes->getNumChildNodes(); i++)
	    addChildNode(newChildNodes->getChildNode(i));
}

void FBXNode::removeChildNode(Ionflux::GeoUtils::FBXNode* removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::FBXNode* currentChildNode = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < childNodes.size()))
	{
		currentChildNode = childNodes[i];
		if (currentChildNode == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		childNodes.erase(childNodes.begin() + i);
		if (currentChildNode != 0)
			removeLocalRef(currentChildNode);
	}
}

void FBXNode::removeChildNodeIndex(unsigned int removeIndex)
{
    if (removeIndex > childNodes.size())
        return;
	Ionflux::GeoUtils::FBXNode* e0 = childNodes[removeIndex];
    childNodes.erase(childNodes.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void FBXNode::clearChildNodes()
{
    std::vector<Ionflux::GeoUtils::FBXNode*>::iterator i;
	for (i = childNodes.begin(); i != childNodes.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	childNodes.clear();
}

void FBXNode::setAttributeType(Ionflux::GeoUtils::FBXNodeAttributeType 
newAttributeType)
{
	attributeType = newAttributeType;
}

Ionflux::GeoUtils::FBXNodeAttributeType FBXNode::getAttributeType() const
{
    return attributeType;
}

void FBXNode::setName(const std::string& newName)
{
	name = newName;
}

std::string FBXNode::getName() const
{
    return name;
}

void FBXNode::setBounds(Ionflux::GeoUtils::Range3* newBounds)
{
	if (bounds == newBounds)
		return;
    if (newBounds != 0)
        addLocalRef(newBounds);
	if (bounds != 0)
		removeLocalRef(bounds);
	bounds = newBounds;
}

Ionflux::GeoUtils::Range3* FBXNode::getBounds() const
{
    return bounds;
}

void FBXNode::setNumVerts(unsigned int newNumVerts)
{
	numVerts = newNumVerts;
}

unsigned int FBXNode::getNumVerts() const
{
    return numVerts;
}

void FBXNode::setNumFaces(unsigned int newNumFaces)
{
	numFaces = newNumFaces;
}

unsigned int FBXNode::getNumFaces() const
{
    return numFaces;
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

std::string FBXNode::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string FBXNode::getXMLAttributeData() const
{
	std::ostringstream d0;
	d0 << Ionflux::ObjectBase::IFObject::getXMLAttributeData();
	if (d0.str().size() > 0)
	    d0 << " ";
	d0 << "attr_type=\"" << attributeType << "\"";
	if (d0.str().size() > 0)
	    d0 << " ";
	d0 << "fbx_name=\"" << 
    Ionflux::ObjectBase::XMLUtils::xmlEscape(name) << "\"";
	if (d0.str().size() > 0)
	    d0 << " ";
	d0 << "num_verts=\"" << numVerts << "\"";
	if (d0.str().size() > 0)
	    d0 << " ";
	d0 << "num_faces=\"" << numFaces << "\"";
	return d0.str();
}

void FBXNode::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::ObjectBase::IFObject::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	std::string iws0 = Ionflux::ObjectBase::getIndent(indentLevel);
	bool haveBCData = false;
	if (d0.str().size() > 0)
	    haveBCData = true;
	bool xcFirst = true;
    if (localTransform != 0)
    {
        if (!xcFirst || haveBCData)
            d0 << "\n";
	    d0 << localTransform->getXML0(indentLevel, "pname=\"local_t\"");
	    xcFirst = false;
    }
    if (globalTransform != 0)
    {
        if (!xcFirst || haveBCData)
            d0 << "\n";
	    d0 << globalTransform->getXML0(indentLevel, "pname=\"global_t\"");
	    xcFirst = false;
    }
	if (!xcFirst || haveBCData)
	    d0 << "\n";
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0(childNodes, "fbxnodevec", "", 
        indentLevel, "pname=\"child_nodes\"");
    xcFirst = false;
    if (bounds != 0)
    {
        if (!xcFirst || haveBCData)
            d0 << "\n";
	    d0 << bounds->getXML0(indentLevel, "pname=\"bounds\"");
	    xcFirst = false;
    }
	target = d0.str();
}

void FBXNode::loadFromXMLFile(const std::string& fileName, const 
std::string& elementName)
{
	std::string en0(elementName);
	if (en0.size() == 0)
	    en0 = getXMLElementName();
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, en0);
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
FBXNode::getXMLObjectFactory()
{
	static Ionflux::GeoUtils::XMLUtils::FBXNodeXMLFactory* fac0 = 0;
    if (fac0 == 0)
    {
        fac0 = Ionflux::GeoUtils::XMLUtils::FBXNodeXMLFactory::create();
        fac0->addRef();
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 
            IFObject::getXMLObjectFactory();
        bFac->addFactory(fac0);
    }
    return fac0;
}

}

}

/** \file FBXNode.cpp
 * \brief FBX Node implementation.
 */
