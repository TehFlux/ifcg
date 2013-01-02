#ifndef IONFLUX_GEOUTILS_TYPES
#define IONFLUX_GEOUTILS_TYPES
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * types.hpp                     Types.
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
#include <string>
#include <set>
#include <map>

namespace Ionflux
{

namespace GeoUtils
{

class Vertex2;
class Edge;
class Vertex3;
class Polygon3;

/// Vector of vertices (2D).
typedef std::vector<Ionflux::GeoUtils::Vertex2*> Vertex2Vector;
/// Vector of edges.
typedef std::vector<Ionflux::GeoUtils::Edge*> EdgeVector;
/// Vector of vertices (3D).
typedef std::vector<Ionflux::GeoUtils::Vertex3*> Vertex3Vector;
/// Vector of polygons (3D).
typedef std::vector<Ionflux::GeoUtils::Polygon3*> Polygon3Vector;
/// Dictionary.
typedef std::map<std::string, std::string> Dictionary;

/// Range comparison result.
typedef int RangeCompResult;

/// Range comparison result (3 elements).
struct RangeCompResult3
{
    /// X result.
    Ionflux::GeoUtils::RangeCompResult x;
    /// Y result.
    Ionflux::GeoUtils::RangeCompResult y;
    /// Z result.
    Ionflux::GeoUtils::RangeCompResult z;
};

/// Axis identifier.
typedef int AxisID;
/// Handedness identifier.
typedef int HandednessID;
/// Camera mode.
typedef int CameraMode;

/// Axis triple.
struct AxisTriple
{
    /// First axis.
    Ionflux::GeoUtils::AxisID a0;
    /// Second axis.
    Ionflux::GeoUtils::AxisID a1;
    /// Third axis.
    Ionflux::GeoUtils::AxisID a2;
};

class BoundingBox;

/// Pair of bounding boxes.
struct BoundingBoxPair
{
    /// First box.
    Ionflux::GeoUtils::BoundingBox* b0;
    /// Second box.
    Ionflux::GeoUtils::BoundingBox* b1;
};

class Split;

/// Vector of splits.
typedef std::vector<Ionflux::GeoUtils::Split*> SplitVector;

/// Result of a bounding box split operation.
struct SplitResult
{
    /// Split success flag.
    bool success;
    /// Bounding box pair.
    Ionflux::GeoUtils::BoundingBoxPair boxes;
};

/// Split quality parameters.
struct SplitParams
{
    /// Split.
    Ionflux::GeoUtils::Split* split;
    /// Difference.
    unsigned int d;
    /// Ratio.
    unsigned int r;
};

class BoxBoundsItem;

/// Set of box bounds items.
typedef std::set<Ionflux::GeoUtils::BoxBoundsItem*> BoxBoundsItemSet;
/// Vector of box bounds items.
typedef std::vector<Ionflux::GeoUtils::BoxBoundsItem*> BoxBoundsItemVector;
/// Set of bounding boxes.
typedef std::set<Ionflux::GeoUtils::BoundingBox*> BoundingBoxSet;
/// Vector of bounding boxes.
typedef std::vector<Ionflux::GeoUtils::BoundingBox*> BoundingBoxVector;

/// Result of a split test.
struct SplitTestResult
{
    /// First set of items.
    Ionflux::GeoUtils::BoxBoundsItemSet items0;
    /// Second set of items.
    Ionflux::GeoUtils::BoxBoundsItemSet items1;
};

/// Camera setup flags.
struct CameraSetupFlags
{
    /// Use direction vector.
    bool useDirection;
    /// Use right vector.
    bool useRight;
    /// Use up vector;
    bool useUp;
    /// Use look-at vector.
    bool useLookAt;
    /// Use sky vector;
    bool useSky;
    /// Use angle.
    bool useAngle;
    /// Use lens.
    bool useLens;
};

/// Texture coordinates.
struct TexCoords
{
    /// U coordinate.
    double u;
    /// V coordinate.
    double v;
};

/// Vector of texture coordinates.
typedef std::vector<Ionflux::GeoUtils::TexCoords> TexCoordsVector;

class Face;

/// Vector of faces.
typedef std::vector<Ionflux::GeoUtils::Face*> FaceVector;

/// Centering method.
typedef int CenteringMethod;

/// SVG shape type.
typedef int SVGShapeType;

/// SVG shape style.
struct SVGShapeStyle
{
    /// Fill color.
    std::string color;
    /// Fill opacity.
    double fillOpacity;
    /// Stroke color.
    std::string strokeColor;
    /// Stroke opacity.
    double strokeOpacity;
    /// Stroke width.
    double strokeWidth;
    /// Stroke miter limit.
    double strokeMiterLimit;
    /// Stroke dash array.
    std::string strokeDashArray;
    /// Shape type.
    Ionflux::GeoUtils::SVGShapeType shapeType;
    /// Close path.
    bool closePath;
};

/// Vector of SVG shape styles.
typedef std::vector<Ionflux::GeoUtils::SVGShapeStyle*> SVGShapeStyleVector;
/// String to SVG shape style map.
typedef std::map<std::string, Ionflux::GeoUtils::SVGShapeStyle*> 
    SVGShapeStyleStringMap;

class TransformableObject;
class TransformableGroup;
class Vector3;

/// Vector of transformable objects.
typedef std::vector<Ionflux::GeoUtils::TransformableObject*> 
    TransformableObjectVector;
/// Vector of 3-element vectors.
typedef std::vector<Ionflux::GeoUtils::Vector3*> Vector3Vector;
/// Vector of transformable groups.
typedef std::vector<Ionflux::GeoUtils::TransformableGroup*> 
    TransformableGroupVector;

/// SVG type.
typedef int SVGType;

/// Image source type.
typedef int ImageSourceType;
/// Image ID.
typedef std::string ImageID;

/// Matrix sampling method.
typedef int MatrixSamplingMethod;

namespace TransformNodes
{

class TransformNode;
class Connection;
class ParamControl;

/// Input node specification.
struct InputNodeSpec
{
    /// The node.
    Ionflux::GeoUtils::TransformNodes::TransformNode* node;
    /// Output ID.
    unsigned int outputID;
};

}

/// Vector of transform nodes.
typedef std::vector<Ionflux::GeoUtils::TransformNodes::TransformNode*> 
    TransformNodeVector;
/// Vector of input node specifications.
typedef std::vector<Ionflux::GeoUtils::TransformNodes::InputNodeSpec> 
    InputNodeSpecVector;
/// Vector of node connections.
typedef std::vector<Ionflux::GeoUtils::TransformNodes::Connection*> 
    ConnectionVector;
/// Vector of parameter control.
typedef std::vector<Ionflux::GeoUtils::TransformNodes::ParamControl*> 
    ParamControlVector;

namespace Mapping
{

class Vector3Mapping;

}

/// Vector of Vector3 mappings.
typedef std::vector<Ionflux::GeoUtils::Mapping::Vector3Mapping*> 
    Vector3MappingVector;

}

}

/** \file types.hpp
 * \brief Types (header).
 */
#endif
