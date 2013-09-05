#ifndef IONFLUX_GEOUTILS_XMLUTILS_PRIVATE
#define IONFLUX_GEOUTILS_XMLUTILS_PRIVATE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * xmlutils_private.hpp                  XML utility functions (header).
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

$Vector
$Vector2
$Vector3
$Vector4
$VectorSet
$FaceData

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Get object vector for polymorphic type VectorSet.
template<>
void getObjVector<Ionflux::GeoUtils::VectorSet,
    Ionflux::GeoUtils::VectorSet*>(TiXmlElement* e0, 
    std::vector<Ionflux::GeoUtils::VectorSet*>& target, 
    const std::string& elementName, 
    const std::string& childElementName);

}

}

}

$VectorSetSet
$TransformableObject
$Vertex3
$Vertex3Set
$Face
$Mesh

/** \file xmlutils_private.hpp
 * \brief XML utility functions (header).
 */
#endif
