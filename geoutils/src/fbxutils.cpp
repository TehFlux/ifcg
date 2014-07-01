/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * fbxutils.cpp                FBX utility functions.
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

#include <fbxsdk.h>
#include "geoutils/fbxutils.hpp"
#include "geoutils/fbxutils_private.hpp"
#include "geoutils/FBXNode.hpp"

namespace Ionflux
{

namespace GeoUtils
{

Ionflux::GeoUtils::FBXNodeAttributeType getFBXNodeAttributeType(
    FBXSDK_NAMESPACE::FbxNodeAttribute::EType attrType)
{
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eUnknown)
        return FBXNode::TYPE_UNKNOWN;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eNull)
        return FBXNode::TYPE_NULL;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eMarker)
        return FBXNode::TYPE_MARKER;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eSkeleton)
        return FBXNode::TYPE_SKELETON;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eMesh)
        return FBXNode::TYPE_MESH;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eNurbs)
        return FBXNode::TYPE_NURBS;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::ePatch)
        return FBXNode::TYPE_PATCH;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eCamera)
        return FBXNode::TYPE_CAMERA;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eCameraStereo)
        return FBXNode::TYPE_CAMERASTEREO;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eCameraSwitcher)
        return FBXNode::TYPE_CAMERASWITCHER;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eLight)
        return FBXNode::TYPE_LIGHT;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eOpticalReference)
        return FBXNode::TYPE_OPTICALREFERENCE;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eOpticalMarker)
        return FBXNode::TYPE_OPTICALMARKER;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eNurbsCurve)
        return FBXNode::TYPE_NURBSCURVE;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eTrimNurbsSurface)
        return FBXNode::TYPE_TRIMNURBSSURFACE;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eBoundary)
        return FBXNode::TYPE_BOUNDARY;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eNurbsSurface)
        return FBXNode::TYPE_NURBSSURFACE;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eShape)
        return FBXNode::TYPE_SHAPE;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eLODGroup)
        return FBXNode::TYPE_LODGROUP;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eSubDiv)
        return FBXNode::TYPE_SUBDIV;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eCachedEffect)
        return FBXNode::TYPE_CACHEDEFFECT;
    else
    if (attrType == FBXSDK_NAMESPACE::FbxNodeAttribute::eLine)
        return FBXNode::TYPE_LINE;
    return FBXNode::TYPE_UNKNOWN;
}

std::string getFBXNodeAttributeTypeString(
    Ionflux::GeoUtils::FBXNodeAttributeType attrType)
{
    if (attrType == FBXNode::TYPE_UNKNOWN)
        return "<unknown>";
    else
    if (attrType == FBXNode::TYPE_NULL)
        return "Null";
    else
    if (attrType == FBXNode::TYPE_MARKER)
        return "Marker";
    else
    if (attrType == FBXNode::TYPE_SKELETON)
        return "Skeleton";
    else
    if (attrType == FBXNode::TYPE_MESH)
        return "Mesh";
    else
    if (attrType == FBXNode::TYPE_NURBS)
        return "Nurbs";
    else
    if (attrType == FBXNode::TYPE_PATCH)
        return "Patch";
    else
    if (attrType == FBXNode::TYPE_CAMERA)
        return "Camera";
    else
    if (attrType == FBXNode::TYPE_CAMERASTEREO)
        return "CameraStereo";
    else
    if (attrType == FBXNode::TYPE_CAMERASWITCHER)
        return "CameraSwitcher";
    else
    if (attrType == FBXNode::TYPE_LIGHT)
        return "Light";
    else
    if (attrType == FBXNode::TYPE_OPTICALREFERENCE)
        return "OpticalReference";
    else
    if (attrType == FBXNode::TYPE_OPTICALMARKER)
        return "OpticalMarker";
    else
    if (attrType == FBXNode::TYPE_NURBSCURVE)
        return "NurbsCurve";
    else
    if (attrType == FBXNode::TYPE_TRIMNURBSSURFACE)
        return "TrimNurbsSurface";
    else
    if (attrType == FBXNode::TYPE_BOUNDARY)
        return "Boundary";
    else
    if (attrType == FBXNode::TYPE_NURBSSURFACE)
        return "NurbsSurface";
    else
    if (attrType == FBXNode::TYPE_SHAPE)
        return "Shape";
    else
    if (attrType == FBXNode::TYPE_LODGROUP)
        return "LODGroup";
    else
    if (attrType == FBXNode::TYPE_SUBDIV)
        return "SubDiv";
    else
    if (attrType == FBXNode::TYPE_CACHEDEFFECT)
        return "CachedEffect";
    else
    if (attrType == FBXNode::TYPE_LINE)
        return "Line";
    return "<unknown>";
}

Ionflux::GeoUtils::Vector3 getVector(FBXSDK_NAMESPACE::FbxDouble3 v)
{
    return Vector3(v[0], v[1], v[2]);
}

Ionflux::GeoUtils::Matrix4 getMatrix(FBXSDK_NAMESPACE::FbxAMatrix m)
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            result.setElement(i, j, m.Get(j, i));
        }
    return result;
}

}

}

/** \file fbxutils.cpp
 * \brief FBX utility functions (implementation).
 */
