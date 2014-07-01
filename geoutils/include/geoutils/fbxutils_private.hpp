#ifndef IONFLUX_GEOUTILS_FBX_UTILS_PRIVATE
#define IONFLUX_GEOUTILS_FBX_UTILS_PRIVATE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * fbxutils_private.hpp                FBX utility functions (private).
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
#include "geoutils/Vector3.hpp"
#include "geoutils/Matrix4.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Get a node attribute type from an implementation value.
Ionflux::GeoUtils::FBXNodeAttributeType getFBXNodeAttributeType(
    FBXSDK_NAMESPACE::FbxNodeAttribute::EType attrType);

/// Convert an FBX vector to a GeoUtils vector (3D).
Ionflux::GeoUtils::Vector3 getVector(FBXSDK_NAMESPACE::FbxDouble3 v);

/// Convert an FBX matrix to a GeoUtils matrix (4x4).
Ionflux::GeoUtils::Matrix4 getMatrix(FBXSDK_NAMESPACE::FbxAMatrix m);

}

}

/** \file fbxutils_private.hpp
 * \brief FBX utility functions (private) (header).
 */
#endif
