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



namespace Ionflux
{

namespace GeoUtils
{

class Vector;

namespace XMLUtils
{

void getVector(const std::string& data, Ionflux::GeoUtils::Vector& target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Vector2;

namespace XMLUtils
{

void getVector2(const std::string& data, Ionflux::GeoUtils::Vector2& 
target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Vector3;

namespace XMLUtils
{

void getVector3(const std::string& data, Ionflux::GeoUtils::Vector3& 
target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Vector4;

namespace XMLUtils
{

void getVector4(const std::string& data, Ionflux::GeoUtils::Vector4& 
target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class VectorSet;

namespace XMLUtils
{

void getVectorSet(const std::string& data, Ionflux::GeoUtils::VectorSet& 
target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class VectorSetSet;

namespace XMLUtils
{

void getVectorSetSet(const std::string& data, 
Ionflux::GeoUtils::VectorSetSet& target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Matrix;

namespace XMLUtils
{

void getMatrix(const std::string& data, Ionflux::GeoUtils::Matrix& target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Matrix2;

namespace XMLUtils
{

void getMatrix2(const std::string& data, Ionflux::GeoUtils::Matrix2& 
target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Matrix3;

namespace XMLUtils
{

void getMatrix3(const std::string& data, Ionflux::GeoUtils::Matrix3& 
target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Matrix4;

namespace XMLUtils
{

void getMatrix4(const std::string& data, Ionflux::GeoUtils::Matrix4& 
target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class FaceData;

namespace XMLUtils
{

void getFaceData(const std::string& data, Ionflux::GeoUtils::FaceData& 
target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class DeferredTransform;

namespace XMLUtils
{

void getDeferredTransform(const std::string& data, 
Ionflux::GeoUtils::DeferredTransform& target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class TransformableObject;

namespace XMLUtils
{

void getTransformableObject(const std::string& data, 
Ionflux::GeoUtils::TransformableObject& target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Vertex2;

namespace XMLUtils
{

void getVertex2(const std::string& data, Ionflux::GeoUtils::Vertex2& 
target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Vertex3;

namespace XMLUtils
{

void getVertex3(const std::string& data, Ionflux::GeoUtils::Vertex3& 
target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Vertex3Set;

namespace XMLUtils
{

void getVertex3Set(const std::string& data, Ionflux::GeoUtils::Vertex3Set& 
target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Face;

namespace XMLUtils
{

void getFace(const std::string& data, Ionflux::GeoUtils::Face& target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Edge;

namespace XMLUtils
{

void getEdge(const std::string& data, Ionflux::GeoUtils::Edge& target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Mesh;

namespace XMLUtils
{

void getMesh(const std::string& data, Ionflux::GeoUtils::Mesh& target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Object3;

namespace XMLUtils
{

void getObject3(const std::string& data, Ionflux::GeoUtils::Object3& 
target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class TransformableGroup;

namespace XMLUtils
{

void getTransformableGroup(const std::string& data, 
Ionflux::GeoUtils::TransformableGroup& target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Polygon3;

namespace XMLUtils
{

void getPolygon3(const std::string& data, Ionflux::GeoUtils::Polygon3& 
target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Polygon3Set;

namespace XMLUtils
{

void getPolygon3Set(const std::string& data, 
Ionflux::GeoUtils::Polygon3Set& target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Shape3;

namespace XMLUtils
{

void getShape3(const std::string& data, Ionflux::GeoUtils::Shape3& target);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Camera;

namespace XMLUtils
{

void getCamera(const std::string& data, Ionflux::GeoUtils::Camera& target);

}

}

}


/** \file xmlutils.hpp
 * \brief XML utility functions (header).
 */
#endif
