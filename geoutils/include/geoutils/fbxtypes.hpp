#ifndef IONFLUX_GEOUTILS_FBX_TYPES
#define IONFLUX_GEOUTILS_FBX_TYPES
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * fbxtypes.hpp                     FBX types.
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

#include <vector>
#include <fbxsdk/fbxsdk_version.h>

namespace FBXSDK_NAMESPACE
{
 
class FbxManager;
class FbxScene;
class FbxNode;

}

namespace Ionflux
{

namespace GeoUtils
{

class FBXNode;

/// FBX node attribute type.
typedef int FBXNodeAttributeType;

/// Vector of FBX nodes.
typedef std::vector<Ionflux::GeoUtils::FBXNode*> FBXNodeVector;

}

}

/** \file types.hpp
 * \brief Types (header).
 */
#endif
