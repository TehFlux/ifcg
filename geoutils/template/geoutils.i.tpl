%include <std_string.i>
%include <std_vector.i>
%include <std_set.i>
%include <exception.i>
%module CGeoUtils
%import "ifobject/ifobject.i"
%import "ifmapping/ifmapping.i"
%{
#include "geoutils/geoutils.hpp"
#include "ifmapping/ifmapping.hpp"
#include "ifmapping/xml_factories.hpp"
#include "ifobject/ifobjectbase.hpp"
#include <assert.h>
using namespace std;
%}

%exception {
    try
    {
        $$function
    } catch(Ionflux::GeoUtils::GeoUtilsError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch(Ionflux::Mapping::MappingError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch(Ionflux::ObjectBase::IFError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    }
}

namespace Ionflux
{

namespace GeoUtils
{

// types.hpp

class Vertex2;
class Edge;
class Vertex3;
class Polygon3;

typedef std::vector<Ionflux::GeoUtils::Vertex2*> Vertex2Vector;
typedef std::vector<Ionflux::GeoUtils::Edge*> EdgeVector;
typedef std::vector<Ionflux::GeoUtils::Vertex3*> Vertex3Vector;
typedef std::vector<Ionflux::GeoUtils::Polygon3*> Polygon3Vector;
typedef std::map<std::string, std::string> Dictionary;

typedef int RangeCompResult;

struct RangeCompResult3
{
    Ionflux::GeoUtils::RangeCompResult x;
    Ionflux::GeoUtils::RangeCompResult y;
    Ionflux::GeoUtils::RangeCompResult z;
};

typedef int AxisID;
typedef int HandednessID;
typedef int CameraMode;

struct AxisTriple
{
    Ionflux::GeoUtils::AxisID a0;
    Ionflux::GeoUtils::AxisID a1;
    Ionflux::GeoUtils::AxisID a2;
};

class BoundingBox;

struct BoundingBoxPair
{
    Ionflux::GeoUtils::BoundingBox* b0;
    Ionflux::GeoUtils::BoundingBox* b1;
};

class Split;

typedef std::vector<Ionflux::GeoUtils::Split*> SplitVector;

struct SplitResult
{
    bool success;
    Ionflux::GeoUtils::BoundingBoxPair boxes;
};

class BoxBoundsItem;

typedef std::set<Ionflux::GeoUtils::BoxBoundsItem*> BoxBoundsItemSet;
typedef std::vector<Ionflux::GeoUtils::BoxBoundsItem*> BoxBoundsItemVector;
typedef std::set<Ionflux::GeoUtils::BoundingBox*> BoundingBoxSet;
typedef std::vector<Ionflux::GeoUtils::BoundingBox*> BoundingBoxVector;

struct SplitTestResult
{
    Ionflux::GeoUtils::BoxBoundsItemSet items0;
    Ionflux::GeoUtils::BoxBoundsItemSet items1;
};

struct CameraSetupFlags
{
    bool useDirection;
    bool useRight;
    bool useUp;
    bool useLookAt;
    bool useSky;
    bool useAngle;
    bool useLens;
};

struct TexCoords
{
    double u;
    double v;
};

struct Color
{
    double red;
    double green;
    double blue;
    double alpha;
};

typedef std::vector<Ionflux::GeoUtils::TexCoords> TexCoordsVector;
typedef std::vector<Ionflux::GeoUtils::Color> ColorVector;

class NFace;
class Face;

typedef std::vector<Ionflux::GeoUtils::NFace*> NFaceVector;
typedef std::vector<Ionflux::GeoUtils::Face*> FaceVector;

typedef int CenteringMethod;

struct SVGShapeStyle
{
    std::string color;
    double fillOpacity;
    std::string strokeColor;
    double strokeOpacity;
    double strokeWidth;
    double strokeMiterLimit;
    std::string strokeDashArray;
    Ionflux::GeoUtils::SVGShapeType shapeType;
    bool closePath;
};

typedef std::vector<Ionflux::GeoUtils::SVGShapeStyle*> SVGShapeStyleVector;
typedef std::map<std::string, Ionflux::GeoUtils::SVGShapeStyle*> 
    SVGShapeStyleStringMap;

typedef int SVGShapeType;

class TransformableObject;

typedef std::vector<Ionflux::GeoUtils::TransformableObject*> 
    TransformableObjectVector;
typedef std::vector<Ionflux::GeoUtils::Vector3*> Vector3Vector;
typedef std::vector<Ionflux::GeoUtils::TransformableGroup*> 
    TransformableGroupVector;

typedef int SVGType;
typedef int ImageSourceType;
typedef std::string ImageID;

typedef int MatrixSamplingMethod;
typedef int QuadInterpolationTypeID;

namespace TransformNodes
{

class TransformNode;
class Connection;
class ParamControl;

struct InputNodeSpec
{
    Ionflux::GeoUtils::TransformNodes::TransformNode* node;
    unsigned int outputID;
};

}

typedef std::vector<Ionflux::GeoUtils::TransformNodes::TransformNode*> 
    TransformNodeVector;
typedef std::vector<Ionflux::GeoUtils::TransformNodes::InputNodeSpec> 
    InputNodeSpecVector;
typedef std::vector<Ionflux::GeoUtils::TransformNodes::Connection*> 
    ConnectionVector;
typedef std::vector<Ionflux::GeoUtils::TransformNodes::ParamControl*> 
    ParamControlVector;

class Vector;
class VectorSet;

typedef std::vector<Ionflux::GeoUtils::Vector*> VectorVector;
typedef std::vector<Ionflux::GeoUtils::VectorSet*> VectorSetVector;

typedef int FaceDataTypeID;

struct AAPlanePairIntersection
{
    bool valid;
    double tNear;
    double tFar;
};

typedef std::vector<Ionflux::GeoUtils::AAPlanePairIntersection> 
    AAPlanePairIntersectionVector;

typedef int NFaceTypeID;
typedef Ionflux::ObjectBase::UInt8 MeshTypeID;

typedef std::set<Ionflux::GeoUtils::Edge> EdgeObjSet;

// constants.hpp

const double DEFAULT_TOLERANCE = 1.0e-6;

const Ionflux::GeoUtils::AxisID AXIS_X = 0;
const Ionflux::GeoUtils::AxisID AXIS_Y = 1;
const Ionflux::GeoUtils::AxisID AXIS_Z = 2;
const Ionflux::GeoUtils::AxisID AXIS_W = 3;

const Ionflux::GeoUtils::HandednessID HANDEDNESS_LEFT = 0;
const Ionflux::GeoUtils::HandednessID HANDEDNESS_RIGHT = 1;

const Ionflux::GeoUtils::RangeCompResult RANGE_EQUAL = 0;
const Ionflux::GeoUtils::RangeCompResult RANGE_OTHER_CONTAINS = -1;
const Ionflux::GeoUtils::RangeCompResult RANGE_FIRST_CONTAINS = 1;
const Ionflux::GeoUtils::RangeCompResult RANGE_OVERLAP = 2;
const Ionflux::GeoUtils::RangeCompResult RANGE_DISJOINT = 3;

const std::string XML_HEADER = "<?xml version=\"1.0\" " 
    "encoding=\"UTF-8\" ?>\n";
const std::string SVG_DEFAULT_POLY_STYLE = 
    "style=\"fill:#20e045;fill-opacity:0.53333336;"
    "stroke:#0e1723;stroke-opacity:1;stroke-width:1;stroke-miterlimit:4;"
    "stroke-dasharray:none\"";
const std::string SVG_POLY_STYLE_TEMPLATE = 
"style=\"fill:{$$color};fill-opacity:{$$fillOpacity};"
    "stroke:{$$strokeColor};stroke-opacity:{$$strokeOpacity};"
    "stroke-width:{$$strokeWidth};stroke-miterlimit:{$$strokeMIterLimit};"
    "stroke-dasharray:{$$strokeDashArray}\"";
const std::string SVG_DEFAULT_HEADER = "<?xml version=\"1.0\""
    " encoding=\"UTF-8\" standalone=\"no\"?>\n"
    "<!-- Created with Inkscape (http://www.inkscape.org/) -->\n"
    "<svg\n"
    "   xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
    "   xmlns:cc=\"http://creativecommons.org/ns#\"\n"
    "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
    "   xmlns:svg=\"http://www.w3.org/2000/svg\"\n"
    "   xmlns=\"http://www.w3.org/2000/svg\"\n"
    "   xmlns:sodipodi=\"http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd\"\n"
    "   xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\"\n"
    "   width=\"1000px\"\n"
    "   height=\"1000px\"\n"
    "   id=\"svg2\">\n"
    "  <g\n"
    "     inkscape:label=\"Ebene 1\"\n"
    "     inkscape:groupmode=\"layer\"\n"
    "     id=\"layer1\">\n"
    "    <path\n"
    "       style=\"fill:none;fill-rule:evenodd;stroke:#707070;"
    "stroke-width:1;stroke-linecap:butt;stroke-linejoin:miter;"
    "stroke-opacity:1\"\n"
    "       d=\"M 500.5,0.5 L 500.5,1000.5\"\n"
    "       id=\"line01\" />\n"
    "    <path\n"
    "       style=\"fill:none;fill-rule:evenodd;stroke:#707070;"
    "stroke-width:1;stroke-linecap:butt;stroke-linejoin:miter;"
    "stroke-opacity:1\"\n"
    "       d=\"M 0.5,500.5 L 1000.5,500.5\"\n"
    "       id=\"line02\" />\n"
    "    <g transform=\"matrix(1, 0, 0, -1, 500, 500)\">\n";
const std::string SVG_DEFAULT_FOOTER = "    </g>\n"
    "  </g>\n"
    "</svg>";
const std::string SVG_TEMPLATE = "<?xml version=\"1.0\""
    " encoding=\"UTF-8\" standalone=\"no\"?>\n"
    "<!-- Created with Inkscape (http://www.inkscape.org/) -->\n"
    "<svg\n"
    "   xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
    "   xmlns:cc=\"http://creativecommons.org/ns#\"\n"
    "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
    "   xmlns:svg=\"http://www.w3.org/2000/svg\"\n"
    "   xmlns=\"http://www.w3.org/2000/svg\"\n"
    "   xmlns:sodipodi=\"http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd\"\n"
    "   xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\"\n"
    "   width=\"{$$width}px\"\n"
    "   height=\"{$$height}px\"\n"
    "   id=\"svg2\">\n"
    "  <g\n"
    "     inkscape:label=\"Ebene 1\"\n"
    "     inkscape:groupmode=\"layer\"\n"
    "     id=\"layer1\">\n"
    "    <g transform=\"matrix(1, 0, 0, -1, {$$originX}, {$$originY})\">\n"
    "      {$$data}"
    "    </g>\n"
    "  </g>\n"
    "</svg>";

const Ionflux::GeoUtils::TexCoords DEFAULT_TEX_COORDS = { 0., 0. };
const Ionflux::GeoUtils::VertexColor DEFAULT_VERTEX_COLOR = { 0., 0., 0., 1. };

const Ionflux::GeoUtils::CenteringMethod CENTER_BARYCENTER = 0;
const Ionflux::GeoUtils::CenteringMethod CENTER_BOUNDS = 1;
const Ionflux::GeoUtils::CenteringMethod CENTER_ORIGIN = 2;

const Ionflux::GeoUtils::SVGShapeStyle DEFAULT_SHAPE_STYLE = { 
    "#20e045", 0.533, "#0e1723", 1., 1., 4., "none"
};

const Ionflux::GeoUtils::SVGShapeType SHAPE_TYPE_POLYGON = 0;
const Ionflux::GeoUtils::SVGShapeType SHAPE_TYPE_PATH = 1;
const Ionflux::GeoUtils::SVGShapeType DEFAULT_SHAPE_TYPE = SHAPE_TYPE_POLYGON;

const unsigned int COORDINATE_NOT_SET = UINT_MAX;

const Ionflux::GeoUtils::MatrixSamplingMethod SAMPLE_AVERAGE = 0;
const Ionflux::GeoUtils::MatrixSamplingMethod SAMPLE_MULTIPLY = 1;

const Ionflux::GeoUtils::QuadInterpolationTypeID 
    QUAD_INTERPOLATION_SYMMETRIC = 0;
const Ionflux::GeoUtils::QuadInterpolationTypeID 
    QUAD_INTERPOLATION_BILINEAR = 1;

namespace TransformNodes
{

const unsigned int DEFAULT_MAX_NUM_INPUTS = 9999;
const unsigned int INPUT_NEXT_FREE = UINT_MAX;
const Ionflux::GeoUtils::TransformNodes::InputNodeSpec 
    DEFAULT_INPUT_NODE_SPEC = {0, 0};

}

// utils.hpp

class Vertex3;
class Vertex3Set;
class BoxBoundsItemCompare;

std::string rangeCompToString(Ionflux::GeoUtils::RangeCompResult r);
void rangeCompToString3(const Ionflux::GeoUtils::RangeCompResult3& r, 
    Ionflux::ObjectBase::StringVector& target);
std::string rangeCompToString3S(const Ionflux::GeoUtils::RangeCompResult3& r);
std::string axisToString(Ionflux::GeoUtils::AxisID a);
std::string axisToString3(Ionflux::GeoUtils::AxisTriple a);
std::string handednessToString(Ionflux::GeoUtils::HandednessID h);
std::string centeringMethodToString(Ionflux::GeoUtils::CenteringMethod m);
Ionflux::ObjectBase::IntVector createIntVector2(int x0, int x1);
Ionflux::ObjectBase::UIntVector createUIntVector2(unsigned int x0, 
    unsigned int x1);
Ionflux::ObjectBase::DoubleVector createDoubleVector2(double x0, double x1);
Ionflux::ObjectBase::IntVector createIntVector3(int x0, int x1, int x2);
Ionflux::ObjectBase::UIntVector createUIntVector3(unsigned int x0, 
    unsigned int x1, unsigned int x2);
Ionflux::ObjectBase::DoubleVector createDoubleVector3(double x0, double x1, 
    double x2);
Ionflux::ObjectBase::IntVector createIntVector4(int x0, int x1, 
    int x2, int x3);
Ionflux::ObjectBase::UIntVector createUIntVector4(unsigned int x0, 
    unsigned int x1, unsigned int x2, unsigned int x3);
Ionflux::ObjectBase::DoubleVector createDoubleVector4(double x0, double x1, 
    double x2, double x3);
void createIntVector3(int x0, int x1, int x2, 
    Ionflux::ObjectBase::IntVector& target);
void createIntVector4(int x0, int x1, int x2, int x3, 
    Ionflux::ObjectBase::IntVector& target);
void shiftInt(Ionflux::ObjectBase::IntVector& target, int offset);
bool lt(double v0, double v1, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
bool gt(double v0, double v1, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
bool eq(double v0, double v1, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
bool ltOrEq(double v0, double v1, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
bool gtOrEq(double v0, double v1, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
void explode(const std::string& bytes, const std::string& splitString, 
    Ionflux::ObjectBase::StringVector& result);
void extractSVGVertex(const std::string& rawData, 
    Ionflux::GeoUtils::Vertex3& target);
void extractSVGVertices(const std::string& rawData, 
    Ionflux::GeoUtils::Vertex3Set& target, bool closePath = true);
void extractXMLVertex(const std::string& rawData, 
    Ionflux::GeoUtils::Vertex3& target);
void extractXMLVertices(const std::string& rawData, 
    Ionflux::GeoUtils::Vertex3Set& target);
int findString(const std::string& haystack, 
    const std::string& needle, size_t startPos = 0, 
    char escapeChar = '\\');
std::string fillTag(const std::string& source, const std::string& tagName, 
    const std::string& replacement, const std::string& tagStart = "{$$", 
    const std::string& tagEnd = "}");
std::string fillTags(const std::string& source, 
    const Ionflux::GeoUtils::Dictionary& replacement, bool partial = false, 
    const std::string& tagStart = "{$$", const std::string& tagEnd = "}");
Ionflux::GeoUtils::SVGShapeStyle getSVGShapeStyle(
    const std::string& color = "#20e045", double fillOpacity = 0.533, 
    const std::string& strokeColor = "#0e1723", double strokeOpacity = 1., 
    double strokeWidth = 1., double strokeMiterLimit = 4, 
    const std::string& strokeDashArray = "none", 
    Ionflux::GeoUtils::SVGShapeType shapeType = 
    Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath = true);
std::string getSVGPolygonStyle(const std::string& color = "#20e045", 
    double fillOpacity = 0.533, const std::string& strokeColor = "#0e1723", 
    double strokeOpacity = 1., double strokeWidth = 1., 
    double strokeMiterLimit = 4, const std::string& strokeDashArray = "none", 
    const std::string& attrTemplate = SVG_POLY_STYLE_TEMPLATE);
std::string getSVGPolygonStyle(const Ionflux::GeoUtils::SVGShapeStyle& style, 
    const std::string& attrTemplate = SVG_POLY_STYLE_TEMPLATE);
std::string getSVGImage(const std::string& data, unsigned int width = 1000, 
    unsigned int height = 1000, int originX = 500, int originY = 500, 
    const std::string& svgTemplate = SVG_TEMPLATE);
unsigned int coordsToSeq(const Ionflux::ObjectBase::UIntVector& coords, 
    const Ionflux::ObjectBase::UIntVector& dimensions);
void seqToCoords(unsigned int seq, 
    const Ionflux::ObjectBase::UIntVector& dimensions, 
    Ionflux::ObjectBase::UIntVector& target);
void getCoordsRel(const Ionflux::ObjectBase::UIntVector& coords, 
    const Ionflux::ObjectBase::UIntVector& dimensions, 
    Ionflux::ObjectBase::DoubleVector& target);
void setToVector(const Ionflux::GeoUtils::BoxBoundsItemSet& bs,
    Ionflux::GeoUtils::BoxBoundsItemVector& bv);
void sort(Ionflux::GeoUtils::BoxBoundsItemVector& bv, 
    Ionflux::GeoUtils::BoxBoundsItemCompare* comp = 0);
bool operator==(const Ionflux::GeoUtils::Color& c0, 
    const Ionflux::GeoUtils::Color& c1);
bool operator!=(const Ionflux::GeoUtils::Color& c0, 
    const Ionflux::GeoUtils::Color& c1);
Ionflux::GeoUtils::Vector2 solveQuadraticEquation(
    double a, double b, double c);
int solveCubicEquation(double a, double b, double c, double d, 
    Ionflux::GeoUtils::Vector3& target);

namespace TransformNodes
{

Ionflux::GeoUtils::TransformNodes::InputNodeSpec createInputNodeSpec(
    Ionflux::GeoUtils::TransformNodes::TransformNode* node, 
    unsigned int outputID);

}

struct AAPlanePairIntersectionCompare
{
    bool operator()(const AAPlanePairIntersection& i0, 
        const AAPlanePairIntersection& i1);
};

std::string getAAPlanePairIntersectionValueString(
    const AAPlanePairIntersection& i0);

// xmlutils.hpp

void getSVGPolygons(const std::string& fileName, 
    const Ionflux::ObjectBase::StringVector& elementIDs, 
    Ionflux::GeoUtils::Polygon3Set& target);
void getBoundingBox(const std::string& fileName, const std::string& elementID, 
    Ionflux::GeoUtils::BoundingBox& target);

// Classes

%rename(mult2) operator*(double, const Ionflux::GeoUtils::Vector2&);
%rename(mult2x2) operator*(double, const Ionflux::GeoUtils::Matrix2&);
%rename(mult3) operator*(double, const Ionflux::GeoUtils::Vector3&);
%rename(mult4) operator*(double, const Ionflux::GeoUtils::Vector4&);
%rename(mult3x3) operator*(double, const Ionflux::GeoUtils::Matrix3&);
%rename(mult4x4) operator*(double, const Ionflux::GeoUtils::Matrix4&);
%rename(multN) operator*(double, const Ionflux::GeoUtils::VectorN&);

}

}

$Clock
$Range
$Vector
$Vector2
$Matrix
$Matrix2
$Vertex2
$Vector3
$Range3
$Vector4
$VectorN
$Matrix3
$Matrix4
$MatrixMN

namespace Ionflux
{

namespace GeoUtils
{

%extend Vertex2 {
    double __getitem__(int index)
    {
        return $$self->getCoord(index);
    }
    void __setitem__(int index, double value)
    {
        return $$self->setCoord(index, value);
    }
}

%extend Vector2 {
    double __getitem__(int index)
    {
        return $$self->getElement(index);
    }
    void __setitem__(int index, double value)
    {
        return $$self->setElement(index, value);
    }
}

%extend Vector3 {
    double __getitem__(int index)
    {
        return $$self->getElement(index);
    }
    void __setitem__(int index, double value)
    {
        return $$self->setElement(index, value);
    }
}

%extend Vector4 {
    double __getitem__(int index)
    {
        return $$self->getElement(index);
    }
    void __setitem__(int index, double value)
    {
        return $$self->setElement(index, value);
    }
}

%extend VectorN {
    double __getitem__(int index)
    {
        return $$self->getElement(index);
    }
    void __setitem__(int index, double value)
    {
        return $$self->setElement(index, value);
    }
}

}

}

$DeferredTransform
$TransformableObject
$TransformableGroup
$Edge

namespace Ionflux
{

namespace GeoUtils
{

%extend Edge {
    double __getitem__(int index)
    {
        return $$self->getVertex(index);
    }
    void __setitem__(int index, double value)
    {
        return $$self->setVertex(index, value);
    }
}

}

}

$Polygon2
$Hexagon2
$Interpolator
$LinearInterpolator
$Vertex3Set
$Vertex3

namespace Ionflux
{

namespace GeoUtils
{

%extend Vertex3 {
    double __getitem__(int index)
    {
        return $$self->getCoord(index);
    }
    void __setitem__(int index, double value)
    {
        return $$self->setCoord(index, value);
    }
}

}

}

$Plane3
$Polygon3
$Polygon3Compare
$Polygon3CompareAxis
$FaceCompare
$FaceCompareAxis
$ImageProperties
$SVGShapeStyleSource
$SVGShapeStyleMap
$SVGShapeStyleVectorSource
$SVGImageProperties
$Polygon3Set
$Line3
$Shape3
$Object3
$Sphere3
$BoxBoundsItem
$BoxBoundsItemCompare
$BoxBoundsItemCompareAxis
$BoxBoundsItemCompareDistanceVec3
$BoxBoundsItemCompareDistancePlane3
$ItemSource
$SplitSet
$BoundingBox
$Camera
$Vertex
$NFace
$NFaceSet
$Face
$Mesh
$Voxel
$Vector3Mapping
$Compose3
$Accept3
$AcceptLength3
$AcceptVolume3
$Lookup3
$Vector3MappingSet
$TransformNode
$Connection
$ParamControl
$TransformGraph
$WriteSVG
$Duplicate
$MatrixTransform
$Rotate
$Translate
$Scale
$Center
$Normalize
$Array
$Flatten
$Merge
$Explode
$Wrap
$Unwrap
$Iterate
$Source
$Cache
$Clone
$Batch
$Scatter
$VectorSet
$VectorSetSet
$FaceData

$VectorXMLFactory
$Vector2XMLFactory
$Vector3XMLFactory
$Vector4XMLFactory
$VectorNXMLFactory
$VectorSetXMLFactory
$VectorSetSetXMLFactory
$Object3XMLFactory
$MatrixXMLFactory
$Matrix2XMLFactory
$Matrix3XMLFactory
$Matrix4XMLFactory
$MatrixMNXMLFactory
$FaceDataXMLFactory
$DeferredTransformXMLFactory
$TransformableObjectXMLFactory
$Vertex2XMLFactory
$Vertex3XMLFactory
$Vertex3SetXMLFactory
$FaceXMLFactory
$EdgeXMLFactory
$MeshXMLFactory
$TransformableGroupXMLFactory
$Polygon3XMLFactory
$Polygon3SetXMLFactory
$Shape3XMLFactory
$CameraXMLFactory

%template(Vertex2Vector) std::vector<Ionflux::GeoUtils::Vertex2*>;
%template(EdgeVector) std::vector<Ionflux::GeoUtils::Edge*>;
%template(Vertex3Vector) std::vector<Ionflux::GeoUtils::Vertex3*>;
%template(Polygon3Vector) std::vector<Ionflux::GeoUtils::Polygon3*>;
%template(BoxBoundsItemSet) std::set<Ionflux::GeoUtils::BoxBoundsItem*>;
%template(BoxBoundsItemVector) std::vector<Ionflux::GeoUtils::BoxBoundsItem*>;
%template(BoundingBoxSet) std::set<Ionflux::GeoUtils::BoundingBox*>;
%template(BoundingBoxVector) std::vector<Ionflux::GeoUtils::BoundingBox*>;
%template(SplitVector) std::vector<Ionflux::GeoUtils::Split*>;
%template(TexCoordsVector) std::vector<Ionflux::GeoUtils::TexCoords>;
%template(GColorVector) std::vector<Ionflux::GeoUtils::Color>;
%template(Dictionary) std::map<std::string, std::string>;
%template(SVGShapeStyleVector) std::vector<Ionflux::GeoUtils::SVGShapeStyle*>;
%template(SVGShapeStyleStringMap) std::map<std::string, Ionflux::GeoUtils::SVGShapeStyle*>;
%template(TransformNodeVector) std::vector<Ionflux::GeoUtils::TransformNodes::TransformNode*>;
%template(InputNodeSpecVector) std::vector<Ionflux::GeoUtils::TransformNodes::InputNodeSpec>;
%template(Vector3Vector) std::vector<Ionflux::GeoUtils::Vector3*>;
%template(ParamControlVector) std::vector<Ionflux::GeoUtils::TransformNodes::ParamControl*>;
%template(VectorVector) std::vector<Ionflux::GeoUtils::Vector*>;
%template(VectorSetVector) std::vector<Ionflux::GeoUtils::VectorSet*>;
%template(NFaceVector) std::vector<Ionflux::GeoUtils::NFace*>;
%template(FaceVector) std::vector<Ionflux::GeoUtils::Face*>;
%template(EdgeObjSet) std::set<Ionflux::GeoUtils::Edge>;
%template(AAPlanePairIntersectionVector) std::vector<Ionflux::GeoUtils::AAPlanePairIntersection>;

