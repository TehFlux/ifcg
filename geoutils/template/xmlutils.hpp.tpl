#ifndef IONFLUX_GEOUTILS_XMLUTILS
#define IONFLUX_GEOUTILS_XMLUTILS
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * xmlutils.hpp                     XML utility functions (header).
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
#include <string>
#include "ifobject/types.hpp"
#include "ifobject/xmlutils.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Vertex3Set;
class Polygon3Set;
class Mesh;
class BoundingBox;

/**
 * Get polygons from SVG file.
 *
 * Extract polygons from SVG paths in the specified file. The polygons to be 
 * extracted are specified as a vector of element IDs.
 *
 * \param fileName File name.
 * \param elementIDs Element IDs.
 * \param target Where to store the polygons.
 */
void getSVGPolygons(const std::string& fileName, 
    const Ionflux::ObjectBase::StringVector& elementIDs, 
    Ionflux::GeoUtils::Polygon3Set& target);

/**
 * Get vertex set from XML file.
 *
 * Get a vertex set, identified by an element ID, from a certain XML file.
 *
 * \param fileName File name.
 * \param elementID Element ID.
 * \param target Vertex set to be initialized.
 */
void getVertex3Set_legacy(const std::string& fileName, const std::string& elementID, 
    Ionflux::GeoUtils::Vertex3Set& target);

/**
 * Get mesh from XML file.
 *
 * Get a mesh, identified by an element ID, from a certain XML file.
 *
 * \param fileName File name.
 * \param elementID Element ID.
 * \param target Mesh to be initialized.
 */
void getMesh_legacy(const std::string& fileName, const std::string& elementID, 
    Ionflux::GeoUtils::Mesh& target);

/**
 * Get bounding box hierarchy from XML file.
 *
 * Get a bounding box hierarchy, identified by an element ID, from a certain 
 * XML file.
 *
 * \param fileName File name.
 * \param elementID Element ID.
 * \param target bounding box to be initialized.
 */
void getBoundingBox(const std::string& fileName, const std::string& elementID, 
    Ionflux::GeoUtils::BoundingBox& target);

}

}

$Vector
$Vector2
$Vector3
$Vector4
$VectorSet
$VectorSetSet
$FaceData
$TransformableObject
$Vertex3
$Vertex3Set
$Face
$Mesh

/** \file xmlutils.hpp
 * \brief XML utility functions (header).
 */
#endif
