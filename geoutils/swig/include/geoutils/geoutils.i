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
#include "ifobject/ifobjectbase.hpp"
#include <assert.h>
using namespace std;
%}

%exception {
    try
    {
        $function
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

class Face;

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
"style=\"fill:{$color};fill-opacity:{$fillOpacity};"
    "stroke:{$strokeColor};stroke-opacity:{$strokeOpacity};"
    "stroke-width:{$strokeWidth};stroke-miterlimit:{$strokeMIterLimit};"
    "stroke-dasharray:{$strokeDashArray}\"";
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
    "   width=\"{$width}px\"\n"
    "   height=\"{$height}px\"\n"
    "   id=\"svg2\">\n"
    "  <g\n"
    "     inkscape:label=\"Ebene 1\"\n"
    "     inkscape:groupmode=\"layer\"\n"
    "     id=\"layer1\">\n"
    "    <g transform=\"matrix(1, 0, 0, -1, {$originX}, {$originY})\">\n"
    "      {$data}"
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
    const std::string& replacement, const std::string& tagStart = "{$", 
    const std::string& tagEnd = "}");
std::string fillTags(const std::string& source, 
    const Ionflux::GeoUtils::Dictionary& replacement, bool partial = false, 
    const std::string& tagStart = "{$", const std::string& tagEnd = "}");
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

namespace TransformNodes
{

Ionflux::GeoUtils::TransformNodes::InputNodeSpec createInputNodeSpec(
    Ionflux::GeoUtils::TransformNodes::TransformNode* node, 
    unsigned int outputID);

}

// xmlutils.hpp

std::string getAttrValue(const std::string& fileName, 
    const std::string& elementName, const std::string& elementID, 
    const std::string& attrName);
void getAttrValues(const std::string& fileName, 
    const std::string& elementName, const std::string& attrName, 
    const Ionflux::ObjectBase::StringVector& elementIDs, 
    Ionflux::ObjectBase::StringVector& target);
void getSVGPolygons(const std::string& fileName, 
    const Ionflux::ObjectBase::StringVector& elementIDs, 
    Ionflux::GeoUtils::Polygon3Set& target);
void getMesh(const std::string& fileName, const std::string& elementID, 
    Ionflux::GeoUtils::Mesh& target);
void getBoundingBox(const std::string& fileName, const std::string& elementID, 
    Ionflux::GeoUtils::BoundingBox& target);
void getVertex3Set(const std::string& fileName, const std::string& elementID, 
    Ionflux::GeoUtils::Vertex3Set& target);

// Classes

class ClockClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ClockClassInfo();
        virtual ~ClockClassInfo();
};

class Clock
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        Clock();
		Clock(const Ionflux::GeoUtils::Clock& other);
        virtual ~Clock();
        virtual std::string getString() const;
        virtual double getCurrentTime();
        virtual double start();
        virtual double stop();
		static Ionflux::GeoUtils::Clock* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Clock* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setStartTime(double newStartTime);
        virtual double getStartTime() const;
        virtual void setStopTime(double newStopTime);
        virtual double getStopTime() const;
        virtual double getElapsedTime() const;
};

}

}


%{
#include "geoutils/Range.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class RangeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        RangeClassInfo();
        virtual ~RangeClassInfo();
};

class Range
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Range();
		Range(const Ionflux::GeoUtils::Range& other);
        Range(double initRMin, double initRMax);
        virtual ~Range();
        virtual void extend(double value);
        virtual double getCenter() const;
        virtual double getRadius() const;
        virtual double getExtent() const;
        virtual double getValue(double s) const;
        virtual double clamp(double value) const;
        virtual double getClampedValue(double s) const;
        virtual Ionflux::GeoUtils::RangeCompResult compare(const 
        Ionflux::GeoUtils::Range& other, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual bool isInRange(double v, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual void setBounds(double rMinNew, double rMaxNew);
        virtual bool operator==(const Ionflux::GeoUtils::Range& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Range& other) 
        const;
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::Range* copy() const;
		static Ionflux::GeoUtils::Range* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Range* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setRMin(double newRMin);
        virtual double getRMin() const;
        virtual void setRMax(double newRMax);
        virtual double getRMax() const;
        virtual void setBounds(const Ionflux::ObjectBase::DoubleVector& 
        newBounds);
        virtual Ionflux::ObjectBase::DoubleVector getBounds() const;
};

}

}


namespace Ionflux
{

namespace GeoUtils
{

class Vector2ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vector2ClassInfo();
        virtual ~Vector2ClassInfo();
};

class Vector2
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::Vector2 ZERO;
		static const Ionflux::GeoUtils::Vector2 E_X;
		static const Ionflux::GeoUtils::Vector2 E_Y;
        
        Vector2();
		Vector2(const Ionflux::GeoUtils::Vector2& other);
        Vector2(double initX0, double initX1);
        Vector2(const Ionflux::ObjectBase::DoubleVector& initElements);
        virtual ~Vector2();
        virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
        newElements);
        virtual void getElements(Ionflux::ObjectBase::DoubleVector& target) 
        const;
        virtual double getElement(int index) const;
        virtual void setElement(int index, double value);
        virtual bool eq(const Ionflux::GeoUtils::Vector2& other, double t =
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Vector2 flip() const;
        virtual double norm() const;
        virtual Ionflux::GeoUtils::Vector2 normalize() const;
        virtual Ionflux::GeoUtils::Vector2 project(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual Ionflux::GeoUtils::Vector2 ortho(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual Ionflux::GeoUtils::Vector2 swap() const;
        virtual bool operator==(const Ionflux::GeoUtils::Vector2& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Vector2& other) 
        const;
        virtual Ionflux::GeoUtils::Vector2 operator+(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual Ionflux::GeoUtils::Vector2 operator-(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual double operator*(const Ionflux::GeoUtils::Vector2& other) 
        const;
        virtual Ionflux::GeoUtils::Vector2 operator*(double c) const;
        virtual Ionflux::GeoUtils::Vector2 operator/(double c) const;
        virtual std::string getString() const;
        static Ionflux::GeoUtils::Vector2 axis(Ionflux::GeoUtils::AxisID 
        axisID);
        virtual void setX0(double newX0);
        virtual double getX0() const;
        virtual void setX1(double newX1);
        virtual double getX1() const;
};

%extend Vector2 {
    double __getitem__(int index)
    {
        return $self->getElement(index);
    }
    void __setitem__(int index, double value)
    {
        return $self->setElement(index, value);
    }
}

%rename(mult2) operator*(double, const Ionflux::GeoUtils::Vector2&);

Ionflux::GeoUtils::Vector2 operator*(double c, const 
Ionflux::GeoUtils::Vector2& v);

class Matrix2ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Matrix2ClassInfo();
        virtual ~Matrix2ClassInfo();
};

class Matrix2
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::Matrix2 ZERO;
		static const Ionflux::GeoUtils::Matrix2 UNIT;
        
        Matrix2();
		Matrix2(const Ionflux::GeoUtils::Matrix2& other);
        Matrix2(double initX00, double initX01, double initX10, double 
        initX11);
        Matrix2(const Ionflux::ObjectBase::DoubleVector& initElements);
        virtual ~Matrix2();
        virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
        newElements);
        virtual void getElements(Ionflux::ObjectBase::DoubleVector& target) 
        const;
        virtual double getElement(int row, int column) const;
        virtual void setElement(int row, int column, double value);
        virtual bool eq(const Ionflux::GeoUtils::Matrix2& other, double t =
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Matrix2 transpose() const;
        virtual Ionflux::GeoUtils::Matrix2 swapColumns() const;
        virtual Ionflux::GeoUtils::Vector2 solve(const 
        Ionflux::GeoUtils::Vector2& v) const;
        virtual Ionflux::GeoUtils::Matrix2 invert() const;
        virtual bool operator==(const Ionflux::GeoUtils::Matrix2& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Matrix2& other) 
        const;
        virtual Ionflux::GeoUtils::Matrix2 operator*(const 
        Ionflux::GeoUtils::Matrix2& other) const;
        virtual Ionflux::GeoUtils::Vector2 operator*(const 
        Ionflux::GeoUtils::Vector2& v) const;
        virtual Ionflux::GeoUtils::Matrix2 operator*(double c) const;
        virtual Ionflux::GeoUtils::Matrix2 operator/(double c) const;
        virtual std::string getString() const;
        static Ionflux::GeoUtils::Matrix2 scale(double sx = 1., double sy =
        1.);
        static Ionflux::GeoUtils::Matrix2 rotate(double phi = 0.);
        virtual void setR0(const Ionflux::GeoUtils::Vector2& newR0);
        virtual Ionflux::GeoUtils::Vector2 getR0() const;
        virtual void setR1(const Ionflux::GeoUtils::Vector2& newR1);
        virtual Ionflux::GeoUtils::Vector2 getR1() const;
        virtual void setC0(const Ionflux::GeoUtils::Vector2& newC0);
        virtual Ionflux::GeoUtils::Vector2 getC0() const;
        virtual void setC1(const Ionflux::GeoUtils::Vector2& newC1);
        virtual Ionflux::GeoUtils::Vector2 getC1() const;
};

%rename(mult2x2) operator*(double, const Ionflux::GeoUtils::Matrix2&);

Ionflux::GeoUtils::Matrix2 operator*(double c, const 
Ionflux::GeoUtils::Matrix2& m);

class Interpolator;

class Vertex2;

typedef std::vector<Ionflux::GeoUtils::Vertex2*> Vertex2Vector;

class Vertex2ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vertex2ClassInfo();
        virtual ~Vertex2ClassInfo();
};

class Vertex2
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::Vertex2 ORIGIN;
        
        Vertex2();
		Vertex2(const Ionflux::GeoUtils::Vertex2& other);
        Vertex2(double initX, double initY);
        Vertex2(const Ionflux::ObjectBase::DoubleVector& initCoords);
        Vertex2(const Ionflux::GeoUtils::Vector2& initCoords);
        virtual ~Vertex2();
        virtual void setCoords(const Ionflux::ObjectBase::DoubleVector& 
        newCoords);
        virtual void setCoords(const Ionflux::GeoUtils::Vector2& 
        newCoords);
        virtual void getCoords(Ionflux::ObjectBase::DoubleVector& target) 
        const;
        virtual void getCoords(Ionflux::GeoUtils::Vector2& target) const;
        virtual double getCoord(int index) const;
        virtual Ionflux::GeoUtils::Vector2 getVector() const;
        virtual void setCoord(int index, double value);
        virtual Ionflux::GeoUtils::Vertex2 interpolate(const 
        Ionflux::GeoUtils::Vertex2& other, double t, 
        Ionflux::GeoUtils::Interpolator* interpolator = 0) const;
        virtual bool eq(const Ionflux::GeoUtils::Vertex2& other, double t =
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool operator==(const Ionflux::GeoUtils::Vertex2& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Vertex2& other) 
        const;
        virtual std::string getString() const;
        virtual void setX(double newX);
        virtual double getX() const;
        virtual void setY(double newY);
        virtual double getY() const;
};

%extend Vertex2 {
    double __getitem__(int index)
    {
        return $self->getCoord(index);
    }
    void __setitem__(int index, double value)
    {
        return $self->setCoord(index, value);
    }
}

}

}


%{
#include "geoutils/Vector3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Plane3;

class Vector3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vector3ClassInfo();
        virtual ~Vector3ClassInfo();
};

class Vector3
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::Vector3 ZERO;
		static const Ionflux::GeoUtils::Vector3 E_X;
		static const Ionflux::GeoUtils::Vector3 E_Y;
		static const Ionflux::GeoUtils::Vector3 E_Z;
		static const Ionflux::GeoUtils::Vector3 E_SUM;
        
        Vector3();
		Vector3(const Ionflux::GeoUtils::Vector3& other);
        Vector3(double initX0, double initX1, double initX2);
        Vector3(const Ionflux::ObjectBase::DoubleVector& initElements);
        Vector3(const Ionflux::GeoUtils::Vector2& initElements, double 
        initZ = 1.);
        virtual ~Vector3();
        virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
        newElements);
        virtual void setElements(double newX0, double newX1, double newX2);
        virtual void setElements(const Ionflux::GeoUtils::Vector2& 
        newElements);
        virtual void setV2(const Ionflux::GeoUtils::Vector2& newElements, 
        double newZ = 1.);
        virtual void getElements(Ionflux::ObjectBase::DoubleVector& target)
        const;
        virtual double getElement(int index) const;
        virtual void setElement(int index, double value);
        virtual bool eq(const Ionflux::GeoUtils::Vector3& other, double t =
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Vector3 flip() const;
        virtual double norm() const;
        virtual Ionflux::GeoUtils::Vector3 normalize() const;
        virtual Ionflux::GeoUtils::Vector3 cross(const 
        Ionflux::GeoUtils::Vector3& other) const;
        virtual Ionflux::GeoUtils::Vector3 project(const 
        Ionflux::GeoUtils::Vector3& other) const;
        virtual Ionflux::GeoUtils::Vector3 ortho(const 
        Ionflux::GeoUtils::Vector3& other) const;
        virtual Ionflux::GeoUtils::Vector3 ortho() const;
        virtual double angle(const Ionflux::GeoUtils::Vector3& other) 
        const;
        virtual Ionflux::GeoUtils::Vector3 permute(int px, int py, int pz) 
        const;
        virtual Ionflux::GeoUtils::Vector3 permute(const 
        Ionflux::ObjectBase::IntVector& p) const;
        virtual Ionflux::GeoUtils::Vector3 multElements(const 
        Ionflux::GeoUtils::Vector3& other) const;
        virtual Ionflux::GeoUtils::Vector3 interpolate(const 
        Ionflux::GeoUtils::Vector3& other, double t) const;
        virtual Ionflux::GeoUtils::AxisTriple getAxisOrder() const;
        virtual bool operator==(const Ionflux::GeoUtils::Vector3& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Vector3& other) 
        const;
        virtual Ionflux::GeoUtils::Vector3 operator+(const 
        Ionflux::GeoUtils::Vector3& other) const;
        virtual Ionflux::GeoUtils::Vector3 operator-(const 
        Ionflux::GeoUtils::Vector3& other) const;
        virtual double operator*(const Ionflux::GeoUtils::Vector3& other) 
        const;
        virtual Ionflux::GeoUtils::Vector3 operator*(double c) const;
        virtual Ionflux::GeoUtils::Vector3 operator/(double c) const;
        virtual Ionflux::GeoUtils::Vector3& operator+=(const 
        Ionflux::GeoUtils::Vector3& other);
        virtual Ionflux::GeoUtils::Vector3& operator-=(const 
        Ionflux::GeoUtils::Vector3& other);
        virtual Ionflux::GeoUtils::Vector2 getV2() const;
        virtual double distanceToPlane(const Ionflux::GeoUtils::Plane3& 
        plane) const;
        virtual std::string getString() const;
        static Ionflux::GeoUtils::Vector3 axis(Ionflux::GeoUtils::AxisID 
        axisID);
		virtual Ionflux::GeoUtils::Vector3* copy() const;
		static Ionflux::GeoUtils::Vector3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Vector3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setX0(double newX0);
        virtual double getX0() const;
        virtual void setX1(double newX1);
        virtual double getX1() const;
        virtual void setX2(double newX2);
        virtual double getX2() const;
};

Ionflux::GeoUtils::Vector3 operator*(double c, const 
Ionflux::GeoUtils::Vector3& v);

}

}


namespace Ionflux
{

namespace GeoUtils
{

%extend Vector3 {
    double __getitem__(int index)
    {
        return $self->getElement(index);
    }
    void __setitem__(int index, double value)
    {
        return $self->setElement(index, value);
    }
}

%rename(mult3) operator*(double, const Ionflux::GeoUtils::Vector3&);

Ionflux::GeoUtils::Vector3 operator*(double c, const 
Ionflux::GeoUtils::Vector3& v);

}

}


%{
#include "geoutils/Range3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Range3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Range3ClassInfo();
        virtual ~Range3ClassInfo();
};

class Range3
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Range3();
		Range3(const Ionflux::GeoUtils::Range3& other);
        Range3(const Ionflux::GeoUtils::Vector3& initCenter, const 
        Ionflux::GeoUtils::Vector3* initRadius = 0);
        Range3(const Ionflux::GeoUtils::Range& initX, const 
        Ionflux::GeoUtils::Range& initY, const Ionflux::GeoUtils::Range& 
        initZ);
        Range3(const Ionflux::GeoUtils::Vector2& rx, const 
        Ionflux::GeoUtils::Vector2& ry, const Ionflux::GeoUtils::Vector2& 
        rz);
        Range3(double xMin, double xMax, double yMin, double yMax, double 
        zMin, double zMax);
        virtual ~Range3();
        virtual void extend(const Ionflux::GeoUtils::Range3& other);
        virtual void extend(const Ionflux::GeoUtils::Vector3& v);
        virtual Ionflux::GeoUtils::Vector3 getCenter() const;
        virtual Ionflux::GeoUtils::Vector3 getRadius() const;
        virtual Ionflux::GeoUtils::Vector3 getExtent() const;
        virtual double getExtent(Ionflux::GeoUtils::AxisID axis) const;
        virtual Ionflux::GeoUtils::Vector3 getValue(const 
        Ionflux::GeoUtils::Vector3 v) const;
        virtual Ionflux::GeoUtils::Vector3 clamp(const 
        Ionflux::GeoUtils::Vector3 v) const;
        virtual Ionflux::GeoUtils::Vector3 getClampedValue(const 
        Ionflux::GeoUtils::Vector3 v) const;
        virtual Ionflux::GeoUtils::Range 
        getAxisRange(Ionflux::GeoUtils::AxisID axis) const;
        virtual void setBounds(const Ionflux::GeoUtils::Vector3& v);
        virtual void setBounds(const Ionflux::GeoUtils::Range3& other);
        virtual Ionflux::GeoUtils::RangeCompResult3 compare3(const 
        Ionflux::GeoUtils::Range3& other, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual Ionflux::GeoUtils::RangeCompResult compare(const 
        Ionflux::GeoUtils::Range3& other, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual bool isInRange(const Ionflux::GeoUtils::Vector3& v, double 
        t = Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual Ionflux::GeoUtils::AxisTriple getAxisOrder() const;
        virtual bool operator==(const Ionflux::GeoUtils::Range3& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Range3& other) 
        const;
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::Range3* copy() const;
		static Ionflux::GeoUtils::Range3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Range3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setX(const Ionflux::GeoUtils::Range& newX);
        virtual Ionflux::GeoUtils::Range getX() const;
        virtual void setY(const Ionflux::GeoUtils::Range& newY);
        virtual Ionflux::GeoUtils::Range getY() const;
        virtual void setZ(const Ionflux::GeoUtils::Range& newZ);
        virtual Ionflux::GeoUtils::Range getZ() const;
};

}

}


namespace Ionflux
{

namespace GeoUtils
{

class Vector4ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vector4ClassInfo();
        virtual ~Vector4ClassInfo();
};

class Vector4
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::Vector4 ZERO;
		static const Ionflux::GeoUtils::Vector4 E_X;
		static const Ionflux::GeoUtils::Vector4 E_Y;
		static const Ionflux::GeoUtils::Vector4 E_Z;
		static const Ionflux::GeoUtils::Vector4 E_W;
		static const Ionflux::GeoUtils::Vector4 H_ZERO;
		static const Ionflux::GeoUtils::Vector4 H_E_X;
		static const Ionflux::GeoUtils::Vector4 H_E_Y;
		static const Ionflux::GeoUtils::Vector4 H_E_Z;
        
        Vector4();
		Vector4(const Ionflux::GeoUtils::Vector4& other);
        Vector4(double initX0, double initX1, double initX2, double 
        initX3);
        Vector4(const Ionflux::ObjectBase::DoubleVector& initElements);
        Vector4(const Ionflux::GeoUtils::Vector2& initElements, double 
        initZ = 0., double initW = 1.);
        Vector4(const Ionflux::GeoUtils::Vector3& initElements, double 
        initW = 1.);
        virtual ~Vector4();
        virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
        newElements);
        virtual void setElements(const Ionflux::GeoUtils::Vector2& 
        newElements);
        virtual void setElements(const Ionflux::GeoUtils::Vector3& 
        newElements);
        virtual void setV2(const Ionflux::GeoUtils::Vector2& newElements, 
        double newZ = 0., double newW = 1.);
        virtual void setV3(const Ionflux::GeoUtils::Vector3& newElements, 
        double newW = 1.);
        virtual void getElements(Ionflux::ObjectBase::DoubleVector& target) 
        const;
        virtual double getElement(int index) const;
        virtual void setElement(int index, double value);
        virtual bool eq(const Ionflux::GeoUtils::Vector4& other, double t =
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Vector4 flip() const;
        virtual double norm() const;
        virtual Ionflux::GeoUtils::Vector4 normalize() const;
        virtual Ionflux::GeoUtils::Vector4 project(const 
        Ionflux::GeoUtils::Vector4& other) const;
        virtual Ionflux::GeoUtils::Vector4 ortho(const 
        Ionflux::GeoUtils::Vector4& other) const;
        virtual Ionflux::GeoUtils::Vector4 permute(int px, int py, int pz, 
        int pw) const;
        virtual Ionflux::GeoUtils::Vector4 permute(const 
        Ionflux::ObjectBase::IntVector& p) const;
        virtual bool operator==(const Ionflux::GeoUtils::Vector4& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Vector4& other) 
        const;
        virtual Ionflux::GeoUtils::Vector4 operator+(const 
        Ionflux::GeoUtils::Vector4& other) const;
        virtual Ionflux::GeoUtils::Vector4 operator-(const 
        Ionflux::GeoUtils::Vector4& other) const;
        virtual double operator*(const Ionflux::GeoUtils::Vector4& other) 
        const;
        virtual Ionflux::GeoUtils::Vector4 operator*(double c) const;
        virtual Ionflux::GeoUtils::Vector4 operator/(double c) const;
        virtual Ionflux::GeoUtils::Vector2 getV2() const;
        virtual Ionflux::GeoUtils::Vector3 getV3() const;
        virtual std::string getString() const;
        static Ionflux::GeoUtils::Vector4 axis(Ionflux::GeoUtils::AxisID 
        axisID);
        static Ionflux::GeoUtils::Vector4 axisH(Ionflux::GeoUtils::AxisID 
        axisID);
        virtual void setX0(double newX0);
        virtual double getX0() const;
        virtual void setX1(double newX1);
        virtual double getX1() const;
        virtual void setX2(double newX2);
        virtual double getX2() const;
        virtual void setX3(double newX3);
        virtual double getX3() const;
};

%extend Vector4 {
    double __getitem__(int index)
    {
        return $self->getElement(index);
    }
    void __setitem__(int index, double value)
    {
        return $self->setElement(index, value);
    }
}

%rename(mult4) operator*(double, const Ionflux::GeoUtils::Vector4&);

Ionflux::GeoUtils::Vector4 operator*(double c, const 
Ionflux::GeoUtils::Vector4& v);

class Matrix3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Matrix3ClassInfo();
        virtual ~Matrix3ClassInfo();
};

class Matrix3
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::Matrix3 ZERO;
		static const Ionflux::GeoUtils::Matrix3 UNIT;
        
        Matrix3();
		Matrix3(const Ionflux::GeoUtils::Matrix3& other);
        Matrix3(double initX00, double initX01, double initX02, double 
        initX10, double initX11, double initX12, double initX20, double 
        initX21, double initX22);
        Matrix3(const Ionflux::ObjectBase::DoubleVector& initElements);
        virtual ~Matrix3();
        virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
        newElements);
        virtual void getElements(Ionflux::ObjectBase::DoubleVector& target) 
        const;
        virtual double getElement(int row, int column) const;
        virtual void setElement(int row, int column, double value);
        virtual bool eq(const Ionflux::GeoUtils::Matrix3& other, double t =
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Matrix3 transpose() const;
        virtual Ionflux::GeoUtils::Matrix3 permuteColumns(int px, int py, 
        int pz) const;
        virtual Ionflux::GeoUtils::Matrix3 permuteColumns(const 
        Ionflux::ObjectBase::IntVector& p) const;
        virtual Ionflux::GeoUtils::Vector3 solve(const 
        Ionflux::GeoUtils::Vector3& v) const;
        virtual Ionflux::GeoUtils::Matrix3 invert() const;
        virtual bool operator==(const Ionflux::GeoUtils::Matrix3& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Matrix3& other) 
        const;
        virtual Ionflux::GeoUtils::Matrix3 operator*(const 
        Ionflux::GeoUtils::Matrix3& other) const;
        virtual Ionflux::GeoUtils::Vector3 operator*(const 
        Ionflux::GeoUtils::Vector3& v) const;
        virtual Ionflux::GeoUtils::Matrix3 operator*(double c) const;
        virtual Ionflux::GeoUtils::Matrix3 operator/(double c) const;
        virtual std::string getString() const;
        static Ionflux::GeoUtils::Matrix3 scale(double sx = 1., double sy =
        1., double sz = 1.);
        static Ionflux::GeoUtils::Matrix3 translate(double tx = 0., double 
        ty = 0.);
        static Ionflux::GeoUtils::Matrix3 rotate(double phi = 0., 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual void setR0(const Ionflux::GeoUtils::Vector3& newR0);
        virtual Ionflux::GeoUtils::Vector3 getR0() const;
        virtual void setR1(const Ionflux::GeoUtils::Vector3& newR1);
        virtual Ionflux::GeoUtils::Vector3 getR1() const;
        virtual void setR2(const Ionflux::GeoUtils::Vector3& newR2);
        virtual Ionflux::GeoUtils::Vector3 getR2() const;
        virtual void setC0(const Ionflux::GeoUtils::Vector3& newC0);
        virtual Ionflux::GeoUtils::Vector3 getC0() const;
        virtual void setC1(const Ionflux::GeoUtils::Vector3& newC1);
        virtual Ionflux::GeoUtils::Vector3 getC1() const;
        virtual void setC2(const Ionflux::GeoUtils::Vector3& newC2);
        virtual Ionflux::GeoUtils::Vector3 getC2() const;
};

%rename(mult3x3) operator*(double, const Ionflux::GeoUtils::Matrix3&);

Ionflux::GeoUtils::Matrix3 operator*(double c, const 
Ionflux::GeoUtils::Matrix3& m);

class Matrix4ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Matrix4ClassInfo();
        virtual ~Matrix4ClassInfo();
};

class Matrix4
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::Matrix4 ZERO;
		static const Ionflux::GeoUtils::Matrix4 UNIT;
		static const double COMPARE_TOLERANCE;
        
        Matrix4();
		Matrix4(const Ionflux::GeoUtils::Matrix4& other);
        Matrix4(double initX00, double initX01, double initX02, double 
        initX03, double initX10, double initX11, double initX12, double 
        initX13, double initX20, double initX21, double initX22, double 
        initX23, double initX30, double initX31, double initX32, double 
        initX33);
        Matrix4(const Ionflux::ObjectBase::DoubleVector& initElements);
        Matrix4(const Ionflux::GeoUtils::Matrix3& initElements);
        virtual ~Matrix4();
        virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
        newElements);
        virtual void setElements(const Ionflux::GeoUtils::Matrix3& 
        newElements);
        virtual void setM3x3(const Ionflux::GeoUtils::Matrix3& newElements,
        double newX33 = 1., double newX03 = 0., double newX13 = 0., double 
        newX23 = 0., double newX30 = 0., double newX31 = 0., double newX32 
        = 0.);
        virtual void getElements(Ionflux::ObjectBase::DoubleVector& target)
        const;
        virtual double getElement(int row, int column) const;
        virtual void setElement(int row, int column, double value);
        virtual bool eq(const Ionflux::GeoUtils::Matrix4& other, double t =
        COMPARE_TOLERANCE);
        virtual Ionflux::GeoUtils::Matrix4 transpose() const;
        virtual Ionflux::GeoUtils::Matrix4 permuteColumns(int px, int py, 
        int pz, int pw) const;
        virtual Ionflux::GeoUtils::Matrix4 permuteColumns(const 
        Ionflux::ObjectBase::IntVector& p) const;
        virtual Ionflux::GeoUtils::Matrix4 permuteRows(int px, int py, int 
        pz, int pw) const;
        virtual Ionflux::GeoUtils::Matrix4 permuteRows(const 
        Ionflux::ObjectBase::IntVector& p) const;
        virtual Ionflux::GeoUtils::Vector4 solve(const 
        Ionflux::GeoUtils::Vector4& v) const;
        virtual Ionflux::GeoUtils::Matrix4 invert() const;
        virtual Ionflux::GeoUtils::Matrix4& multiplyLeft(const 
        Ionflux::GeoUtils::Matrix4& other);
        virtual Ionflux::GeoUtils::Matrix4& multiplyRight(const 
        Ionflux::GeoUtils::Matrix4& other);
        virtual bool operator==(const Ionflux::GeoUtils::Matrix4& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Matrix4& other) 
        const;
        virtual Ionflux::GeoUtils::Matrix4 operator*(const 
        Ionflux::GeoUtils::Matrix4& other) const;
        virtual Ionflux::GeoUtils::Vector4 operator*(const 
        Ionflux::GeoUtils::Vector4& v) const;
        virtual Ionflux::GeoUtils::Matrix4 operator*(double c) const;
        virtual Ionflux::GeoUtils::Matrix4 operator/(double c) const;
        virtual Ionflux::GeoUtils::Matrix3 getM3x3() const;
        virtual std::string getString() const;
        static Ionflux::GeoUtils::Matrix4 scale(double sx = 1., double sy =
        1., double sz = 1., double sw = 1.);
        static Ionflux::GeoUtils::Matrix4 scale(const 
        Ionflux::GeoUtils::Vector3& s, double sw = 1.);
        static Ionflux::GeoUtils::Matrix4 scale(const 
        Ionflux::GeoUtils::Vector4& s);
        static Ionflux::GeoUtils::Matrix4 translate(double tx = 0., double 
        ty = 0., double tz = 0.);
        static Ionflux::GeoUtils::Matrix4 translate(const 
        Ionflux::GeoUtils::Vector3& t);
        static Ionflux::GeoUtils::Matrix4 rotate(double phi = 0., 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        static Ionflux::GeoUtils::Matrix4 
        swapAxes(Ionflux::GeoUtils::AxisID x = Ionflux::GeoUtils::AXIS_X, 
        Ionflux::GeoUtils::AxisID y = Ionflux::GeoUtils::AXIS_Y, 
        Ionflux::GeoUtils::AxisID z = Ionflux::GeoUtils::AXIS_Z, 
        Ionflux::GeoUtils::AxisID w = Ionflux::GeoUtils::AXIS_W);
        static Ionflux::GeoUtils::Matrix4 perspective(double d = 1., 
        Ionflux::GeoUtils::AxisID depthAxis = Ionflux::GeoUtils::AXIS_Y);
        static Ionflux::GeoUtils::Matrix4 imageTransform(double screenWidth
        = 1.33, double screenHeight = 1., double imageWidth = 800., double 
        imageHeight = 600., Ionflux::GeoUtils::AxisID upAxis = 
        Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID depthAxis = 
        Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID horizonAxis = 
        Ionflux::GeoUtils::AXIS_X);
		virtual Ionflux::GeoUtils::Matrix4* copy() const;
		static Ionflux::GeoUtils::Matrix4* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Matrix4* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setR0(const Ionflux::GeoUtils::Vector4& newR0);
        virtual Ionflux::GeoUtils::Vector4 getR0() const;
        virtual void setR1(const Ionflux::GeoUtils::Vector4& newR1);
        virtual Ionflux::GeoUtils::Vector4 getR1() const;
        virtual void setR2(const Ionflux::GeoUtils::Vector4& newR2);
        virtual Ionflux::GeoUtils::Vector4 getR2() const;
        virtual void setR3(const Ionflux::GeoUtils::Vector4& newR3);
        virtual Ionflux::GeoUtils::Vector4 getR3() const;
        virtual void setC0(const Ionflux::GeoUtils::Vector4& newC0);
        virtual Ionflux::GeoUtils::Vector4 getC0() const;
        virtual void setC1(const Ionflux::GeoUtils::Vector4& newC1);
        virtual Ionflux::GeoUtils::Vector4 getC1() const;
        virtual void setC2(const Ionflux::GeoUtils::Vector4& newC2);
        virtual Ionflux::GeoUtils::Vector4 getC2() const;
        virtual void setC3(const Ionflux::GeoUtils::Vector4& newC3);
        virtual Ionflux::GeoUtils::Vector4 getC3() const;
};

%rename(mult4x4) operator*(double, const Ionflux::GeoUtils::Matrix4&);

Ionflux::GeoUtils::Matrix4 operator*(double c, const 
Ionflux::GeoUtils::Matrix4& m);

}

}


%{
#include "geoutils/TransformableObject.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class TransformableObjectClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TransformableObjectClassInfo();
        virtual ~TransformableObjectClassInfo();
};

class TransformableObject
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        TransformableObject();
		TransformableObject(const Ionflux::GeoUtils::TransformableObject& other);
        virtual ~TransformableObject();
        virtual std::string getValueString() const;
        virtual void copyTransform(const 
        Ionflux::GeoUtils::TransformableObject& other);
        virtual void onTransformChanged();
        virtual void onVIChanged();
        virtual bool checkTransform(double t = 
        Ionflux::GeoUtils::Matrix4::COMPARE_TOLERANCE);
        virtual bool checkVI(double t = 
        Ionflux::GeoUtils::Matrix4::COMPARE_TOLERANCE);
        virtual Ionflux::GeoUtils::TransformableObject& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::TransformableObject& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::TransformableObject& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::TransformableObject& normalize();
        virtual Ionflux::GeoUtils::TransformableObject& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::TransformableObject& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::TransformableObject& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::TransformableObject& transformVI(const 
        Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4*
        image = 0);
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual Ionflux::GeoUtils::Range3 getBounds();
        virtual Ionflux::GeoUtils::TransformableObject& duplicate() = 0;
		static Ionflux::GeoUtils::TransformableObject* 
		upcast(Ionflux::ObjectBase::IFObject* other);
        virtual void setTransformMatrix(const Ionflux::GeoUtils::Matrix4& 
        newTransformMatrix);
        virtual Ionflux::GeoUtils::Matrix4 getTransformMatrix() const;
        virtual void setViewMatrix(const Ionflux::GeoUtils::Matrix4& 
        newViewMatrix);
        virtual Ionflux::GeoUtils::Matrix4 getViewMatrix() const;
        virtual void setImageMatrix(const Ionflux::GeoUtils::Matrix4& 
        newImageMatrix);
        virtual Ionflux::GeoUtils::Matrix4 getImageMatrix() const;
        virtual void setLastTransformMatrix(const 
        Ionflux::GeoUtils::Matrix4& newLastTransformMatrix);
        virtual Ionflux::GeoUtils::Matrix4 getLastTransformMatrix() const;
        virtual void setLastViewMatrix(const Ionflux::GeoUtils::Matrix4& 
        newLastViewMatrix);
        virtual Ionflux::GeoUtils::Matrix4 getLastViewMatrix() const;
        virtual void setLastImageMatrix(const Ionflux::GeoUtils::Matrix4& 
        newLastImageMatrix);
        virtual Ionflux::GeoUtils::Matrix4 getLastImageMatrix() const;
};

}

}


%{
#include "geoutils/TransformableGroup.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class TransformableGroupClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TransformableGroupClassInfo();
        virtual ~TransformableGroupClassInfo();
};

class TransformableGroup
: public Ionflux::GeoUtils::TransformableObject
{
    public:
        
        TransformableGroup();
		TransformableGroup(const Ionflux::GeoUtils::TransformableGroup& other);
        virtual ~TransformableGroup();
        virtual void recalculateBounds();
        virtual std::string getString() const;
        virtual void addItems(const 
        Ionflux::GeoUtils::TransformableObjectVector& newItems);
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Vector3 getBarycenter() const;
        virtual Ionflux::GeoUtils::TransformableGroup& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::TransformableGroup& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::TransformableGroup& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::TransformableGroup& normalize();
        virtual Ionflux::GeoUtils::TransformableGroup& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::TransformableGroup& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::TransformableGroup& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::TransformableGroup& transformVI(const 
        Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4*
        image = 0);
        virtual Ionflux::GeoUtils::TransformableGroup& duplicate();
        virtual Ionflux::GeoUtils::TransformableGroup& flatten();
        virtual void getLeafItems(Ionflux::GeoUtils::TransformableGroup& 
        target, unsigned int level = 0);
        virtual std::string getDebugInfo(bool expand = true, unsigned int 
        level = 0);
		virtual Ionflux::GeoUtils::TransformableGroup* copy() const;
		static Ionflux::GeoUtils::TransformableGroup* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformableGroup* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumItems() const;
        virtual Ionflux::GeoUtils::TransformableObject* getItem(unsigned 
        int elementIndex = 0) const;
		virtual int findItem(Ionflux::GeoUtils::TransformableObject* needle, 
		unsigned int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::TransformableObject*>& 
        getItems();
        virtual void addItem(Ionflux::GeoUtils::TransformableObject* 
        addElement);        
        virtual void removeItem(Ionflux::GeoUtils::TransformableObject* 
        removeElement);
		virtual void removeItemIndex(unsigned int removeIndex);
		virtual void clearItems();
};

}

}


%{
#include "geoutils/Edge.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Edge;

typedef std::vector<Ionflux::GeoUtils::Edge*> EdgeVector;

class EdgeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        EdgeClassInfo();
        virtual ~EdgeClassInfo();
};

class Edge
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Edge();
		Edge(const Ionflux::GeoUtils::Edge& other);
        Edge(int initV0, int initV1);
        Edge(const Ionflux::ObjectBase::IntVector& initVertices);
        virtual ~Edge();
        virtual void setVertices(const Ionflux::ObjectBase::IntVector& 
        newVertices);
        virtual void getVertices(Ionflux::ObjectBase::IntVector& target) 
        const;
        virtual double getVertex(int index) const;
        virtual Ionflux::ObjectBase::IntVector getVector() const;
        virtual void setVertex(int index, int value);
        virtual bool operator==(const Ionflux::GeoUtils::Edge& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Edge& other) 
        const;
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::Edge* copy() const;
		static Ionflux::GeoUtils::Edge* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Edge* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setV0(int newV0);
        virtual int getV0() const;
        virtual void setV1(int newV1);
        virtual int getV1() const;
};

}

}


namespace Ionflux
{

namespace GeoUtils
{

%extend Edge {
    double __getitem__(int index)
    {
        return $self->getVertex(index);
    }
    void __setitem__(int index, double value)
    {
        return $self->setVertex(index, value);
    }
}

}

}


%{
#include "geoutils/Polygon2.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Polygon2ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Polygon2ClassInfo();
        virtual ~Polygon2ClassInfo();
};

class Polygon2
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Polygon2();
		Polygon2(const Ionflux::GeoUtils::Polygon2& other);
        Polygon2(Ionflux::GeoUtils::Vertex2Vector* initVertices, 
        Ionflux::GeoUtils::EdgeVector* initEdges = 0);
        virtual ~Polygon2();
        virtual void addVertices(Ionflux::GeoUtils::Vertex2Vector& 
        newVertices);
        virtual void addEdges(Ionflux::GeoUtils::EdgeVector& newEdges);
        virtual int createEdges();
        virtual bool checkVertex(const Ionflux::GeoUtils::Vertex2& v, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::Polygon2* copy() const;        
        virtual unsigned int getNumVertices() const;
        virtual Ionflux::GeoUtils::Vertex2* getVertex(unsigned int 
        elementIndex = 0) const;
		virtual int findVertex(Ionflux::GeoUtils::Vertex2* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Vertex2*>& getVertices();
        virtual void addVertex(Ionflux::GeoUtils::Vertex2* addElement);        
        virtual void removeVertex(Ionflux::GeoUtils::Vertex2* 
        removeElement);
		virtual void removeVertexIndex(unsigned int removeIndex);
		virtual void clearVertices();        
        virtual unsigned int getNumEdges() const;
        virtual Ionflux::GeoUtils::Edge* getEdge(unsigned int elementIndex 
        = 0) const;
		virtual int findEdge(Ionflux::GeoUtils::Edge* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Edge*>& getEdges();
        virtual void addEdge(Ionflux::GeoUtils::Edge* addElement);        
        virtual void removeEdge(Ionflux::GeoUtils::Edge* removeElement);
		virtual void removeEdgeIndex(unsigned int removeIndex);
		virtual void clearEdges();
};

}

}


%{
#include "geoutils/Hexagon2.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Hexagon2ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Hexagon2ClassInfo();
        virtual ~Hexagon2ClassInfo();
};

class Hexagon2
: public Ionflux::GeoUtils::Polygon2
{
    public:
        
        Hexagon2();
		Hexagon2(const Ionflux::GeoUtils::Hexagon2& other);
        Hexagon2(double initBaseLength);
        virtual ~Hexagon2();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::Hexagon2* copy() const;
        virtual void setBaseLength(double newBaseLength);
        virtual double getBaseLength() const;
};

}

}


%{
#include "geoutils/Interpolator.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class InterpolatorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        InterpolatorClassInfo();
        virtual ~InterpolatorClassInfo();
};

class Interpolator
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Interpolator();
		Interpolator(const Ionflux::GeoUtils::Interpolator& other);
        Interpolator(double initV0, double initV1);
        Interpolator(const Ionflux::ObjectBase::DoubleVector& initValues);
        virtual ~Interpolator();
        virtual void setValues(double newV0, double newV1);
        virtual void setValues(const Ionflux::ObjectBase::DoubleVector& 
        newValues);
        virtual void getValues(Ionflux::ObjectBase::DoubleVector& target) 
        const;
        virtual double getValue(int index) const;
        virtual Ionflux::ObjectBase::DoubleVector getVector() const;
        virtual void setValue(int index, int value);
        virtual bool operator==(const Ionflux::GeoUtils::Interpolator& 
        other) const;
        virtual bool operator!=(const Ionflux::GeoUtils::Interpolator& 
        other) const;
        virtual double interpolate(double t = 0.5) const = 0;
        virtual double operator()(double t = 0.5) const;
        virtual std::string getString() const;
        virtual void setV0(double newV0);
        virtual double getV0() const;
        virtual void setV1(double newV1);
        virtual double getV1() const;
};

}

}


%{
#include "geoutils/LinearInterpolator.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class LinearInterpolatorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        LinearInterpolatorClassInfo();
        virtual ~LinearInterpolatorClassInfo();
};

class LinearInterpolator
: public Ionflux::GeoUtils::Interpolator
{
    public:
        
        LinearInterpolator();
		LinearInterpolator(const Ionflux::GeoUtils::LinearInterpolator& other);
        LinearInterpolator(double initV0, double initV1);
        LinearInterpolator(const Ionflux::ObjectBase::DoubleVector& 
        initValues);
        virtual ~LinearInterpolator();
        virtual double interpolate(double t = 0.5) const;
		virtual Ionflux::GeoUtils::LinearInterpolator* copy() const;
};

}

}


%{
#include "geoutils/Vertex3Set.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Vertex3;

class Vertex3SetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vertex3SetClassInfo();
        virtual ~Vertex3SetClassInfo();
};

class Vertex3Set
: public Ionflux::GeoUtils::TransformableObject
{
    public:
        
        Vertex3Set();
		Vertex3Set(const Ionflux::GeoUtils::Vertex3Set& other);
        Vertex3Set(Ionflux::GeoUtils::Vertex3Vector& initVertices);
        virtual ~Vertex3Set();
        virtual Ionflux::GeoUtils::Vertex3* addVertex();
        virtual void addVertices(Ionflux::GeoUtils::Vertex3Vector& 
        newVerts);
        virtual void addVertices(Ionflux::GeoUtils::Vertex3Set& newVerts);
        virtual std::string getValueString() const;
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Vertex3Set& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Vertex3Set& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Vertex3Set& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Vertex3Set& normalize();
        virtual Ionflux::GeoUtils::Vertex3Set& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Vertex3Set& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Vertex3Set& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Vertex3Set& transformVI(const 
        Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4*
        image = 0);
        virtual Ionflux::GeoUtils::Vertex3Set& duplicate();
        virtual Ionflux::GeoUtils::Matrix3 getCovariance();
        virtual Ionflux::GeoUtils::Matrix3 getPCABase();
        virtual Ionflux::GeoUtils::Plane3 getPlaneFit();
        virtual std::string getXMLData() const;
        virtual std::string getXML() const;
		virtual Ionflux::GeoUtils::Vertex3Set* copy() const;
		static Ionflux::GeoUtils::Vertex3Set* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Vertex3Set* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumVertices() const;
        virtual Ionflux::GeoUtils::Vertex3* getVertex(unsigned int 
        elementIndex = 0) const;
		virtual int findVertex(Ionflux::GeoUtils::Vertex3* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Vertex3*>& getVertices();
        virtual void addVertex(Ionflux::GeoUtils::Vertex3* addElement);        
        virtual void removeVertex(Ionflux::GeoUtils::Vertex3* 
        removeElement);
		virtual void removeVertexIndex(unsigned int removeIndex);
		virtual void clearVertices();
};

}

}


%{
#include "geoutils/Vertex3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Interpolator;
class Plane3;
class Vertex3;

class Vertex3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vertex3ClassInfo();
        virtual ~Vertex3ClassInfo();
};

class Vertex3
: public Ionflux::GeoUtils::TransformableObject
{
    public:
		static const Ionflux::GeoUtils::Vertex3 ORIGIN;
        
        Vertex3();
		Vertex3(const Ionflux::GeoUtils::Vertex3& other);
        Vertex3(double initX, double initY, double initZ);
        Vertex3(const Ionflux::ObjectBase::DoubleVector& initCoords);
        Vertex3(const Ionflux::GeoUtils::Vector3& initCoords);
        virtual ~Vertex3();
        virtual void setCoords(double newX, double newY, double newZ);
        virtual void setCoords(const Ionflux::ObjectBase::DoubleVector& 
        newCoords);
        virtual void setCoords(const Ionflux::GeoUtils::Vector3& 
        newCoords);
        virtual void getCoords(Ionflux::ObjectBase::DoubleVector& target) 
        const;
        virtual void getCoords(Ionflux::GeoUtils::Vector3& target) const;
        virtual double getCoord(int index) const;
        virtual Ionflux::GeoUtils::Vector3 getVector() const;
        virtual void setCoord(int index, double value);
        virtual Ionflux::GeoUtils::Vertex3 interpolate(const 
        Ionflux::GeoUtils::Vertex3& other, double t, 
        Ionflux::GeoUtils::Interpolator* interpolator = 0) const;
        virtual double distanceToPlane(const Ionflux::GeoUtils::Plane3& 
        plane) const;
        virtual bool eq(const Ionflux::GeoUtils::Vertex3& other, double t =
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool operator==(const Ionflux::GeoUtils::Vertex3& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Vertex3& other) 
        const;
        virtual Ionflux::GeoUtils::Vertex3& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Vertex3& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Vertex3& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Vertex3& normalize();
        virtual Ionflux::GeoUtils::Vertex3& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Vertex3& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual Ionflux::GeoUtils::Range3 getBounds();
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Vertex3& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Vertex3& transformVI(const 
        Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4*
        image = 0);
        virtual Ionflux::GeoUtils::Vertex3& duplicate();
        virtual std::string getValueString() const;
        static Ionflux::GeoUtils::Vertex3* create(double newX, double newY,
        double newZ);
        virtual std::string getXMLData() const;
        virtual std::string getXML() const;
		virtual Ionflux::GeoUtils::Vertex3* copy() const;
		static Ionflux::GeoUtils::Vertex3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Vertex3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setX(double newX);
        virtual double getX() const;
        virtual void setY(double newY);
        virtual double getY() const;
        virtual void setZ(double newZ);
        virtual double getZ() const;
};

}

}


namespace Ionflux
{

namespace GeoUtils
{

%extend Vertex3 {
    double __getitem__(int index)
    {
        return $self->getCoord(index);
    }
    void __setitem__(int index, double value)
    {
        return $self->setCoord(index, value);
    }
}

}

}


%{
#include "geoutils/Plane3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Plane3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Plane3ClassInfo();
        virtual ~Plane3ClassInfo();
};

class Plane3
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::Plane3 XY;
		static const Ionflux::GeoUtils::Plane3 YZ;
		static const Ionflux::GeoUtils::Plane3 ZX;
        
        Plane3();
		Plane3(const Ionflux::GeoUtils::Plane3& other);
        Plane3(const Ionflux::GeoUtils::Vector3& initP, const 
        Ionflux::GeoUtils::Vector3& initU, const 
        Ionflux::GeoUtils::Vector3& initV);
        virtual ~Plane3();
        virtual Ionflux::GeoUtils::Vector3 getTangent() const;
        virtual Ionflux::GeoUtils::Vector3 getBinormal() const;
        virtual Ionflux::GeoUtils::Vector3 getNormal() const;
        virtual Ionflux::GeoUtils::Matrix3 getTangentBase() const;
        virtual bool operator==(const Ionflux::GeoUtils::Plane3& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Plane3& other) 
        const;
        virtual std::string getString() const;
        static Ionflux::GeoUtils::Plane3 createFromNormal(const 
        Ionflux::GeoUtils::Vector3& n, const Ionflux::GeoUtils::Vector3& t 
        = Ionflux::GeoUtils::Vector3::E_X, const 
        Ionflux::GeoUtils::Vector3& p = Ionflux::GeoUtils::Vector3::ZERO);
		virtual Ionflux::GeoUtils::Plane3* copy() const;
        virtual void setP(const Ionflux::GeoUtils::Vector3& newP);
        virtual Ionflux::GeoUtils::Vector3 getP() const;
        virtual void setU(const Ionflux::GeoUtils::Vector3& newU);
        virtual Ionflux::GeoUtils::Vector3 getU() const;
        virtual void setV(const Ionflux::GeoUtils::Vector3& newV);
        virtual Ionflux::GeoUtils::Vector3 getV() const;
};

}

}


%{
#include "geoutils/Polygon3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Polygon3;

class Polygon3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Polygon3ClassInfo();
        virtual ~Polygon3ClassInfo();
};

class Polygon3
: public Ionflux::GeoUtils::TransformableObject
{
    public:
        
        Polygon3();
		Polygon3(const Ionflux::GeoUtils::Polygon3& other);
        Polygon3(Ionflux::GeoUtils::Vertex3Vector* initVertices, 
        Ionflux::GeoUtils::EdgeVector* initEdges = 0);
        Polygon3(Ionflux::GeoUtils::Vertex3Set* initVertexSource, 
        Ionflux::GeoUtils::EdgeVector* initEdges = 0);
        Polygon3(const Ionflux::GeoUtils::Vertex3* v0, const 
        Ionflux::GeoUtils::Vertex3* v1, const Ionflux::GeoUtils::Vertex3* 
        v2, const Ionflux::GeoUtils::Vertex3* v3 = 0);
        virtual ~Polygon3();
        virtual void copyVertices();
        virtual Ionflux::GeoUtils::Vertex3* addVertex();
        virtual void addVertices(Ionflux::GeoUtils::Vertex3Vector& 
        newVerts);
        virtual void addVertices(Ionflux::GeoUtils::Vertex3Set& newVerts);
        virtual Ionflux::GeoUtils::Edge* addEdge();
        virtual void addEdges(Ionflux::GeoUtils::EdgeVector& newEdges);
        virtual int createEdges();
        virtual Ionflux::GeoUtils::Plane3 getPlane(int v0 = 0, int v1 = 1, 
        int v2 = -1) const;
        virtual std::string getValueString() const;
        virtual std::string getSVG(const std::string& attrs = 
        SVG_DEFAULT_POLY_STYLE, const std::string& elementID = "polygon", 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y, 
        Ionflux::GeoUtils::SVGShapeType shapeType = 
        Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath = true);
        virtual std::string getSVG(const Ionflux::GeoUtils::SVGShapeStyle& 
        style, const std::string& elementID = "polygon", 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y, 
        Ionflux::GeoUtils::SVGShapeType shapeType = 
        Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath = true);
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Polygon3& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Polygon3& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Polygon3& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Polygon3& normalize();
        virtual Ionflux::GeoUtils::Polygon3& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Polygon3& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Polygon3& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Polygon3& duplicate();
        virtual bool isPlanar(double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual void getPolygon2(Ionflux::GeoUtils::Polygon2& target);
        static Ionflux::GeoUtils::Polygon3* square();
        static Ionflux::GeoUtils::Polygon3* circle(unsigned int resolution 
        = 20);
		virtual Ionflux::GeoUtils::Polygon3* copy() const;
		static Ionflux::GeoUtils::Polygon3* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::GeoUtils::Polygon3* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
        virtual void setVertexSource(Ionflux::GeoUtils::Vertex3Set* 
        newVertexSource);
        virtual Ionflux::GeoUtils::Vertex3Set* getVertexSource() const;        
        virtual unsigned int getNumVertices() const;
        virtual Ionflux::GeoUtils::Vertex3* getVertex(unsigned int 
        elementIndex = 0) const;
		virtual int findVertex(Ionflux::GeoUtils::Vertex3* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Vertex3*>& getVertices();
        virtual void addVertex(Ionflux::GeoUtils::Vertex3* addElement);        
        virtual void removeVertex(Ionflux::GeoUtils::Vertex3* 
        removeElement);
		virtual void removeVertexIndex(unsigned int removeIndex);
		virtual void clearVertices();        
        virtual unsigned int getNumEdges() const;
        virtual Ionflux::GeoUtils::Edge* getEdge(unsigned int elementIndex 
        = 0) const;
		virtual int findEdge(Ionflux::GeoUtils::Edge* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Edge*>& getEdges();
        virtual void addEdge(Ionflux::GeoUtils::Edge* addElement);        
        virtual void removeEdge(Ionflux::GeoUtils::Edge* removeElement);
		virtual void removeEdgeIndex(unsigned int removeIndex);
		virtual void clearEdges();
};

}

}


%{
#include "geoutils/Polygon3Compare.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Polygon3CompareClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Polygon3CompareClassInfo();
        virtual ~Polygon3CompareClassInfo();
};

class Polygon3Compare
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        Polygon3Compare();
		Polygon3Compare(const Ionflux::GeoUtils::Polygon3Compare& other);
        Polygon3Compare(bool initInvert, 
        Ionflux::GeoUtils::Polygon3Compare* initTarget = 0);
        virtual ~Polygon3Compare();
        virtual std::string getString() const;
        virtual bool operator()(Ionflux::GeoUtils::Polygon3* p0, 
        Ionflux::GeoUtils::Polygon3* p1);
        virtual bool compare(Ionflux::GeoUtils::Polygon3& p0, 
        Ionflux::GeoUtils::Polygon3& p1);
		virtual Ionflux::GeoUtils::Polygon3Compare* copy() const;
		static Ionflux::GeoUtils::Polygon3Compare* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Polygon3Compare* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setInvert(bool newInvert);
        virtual bool getInvert() const;
        virtual void setTarget(Ionflux::GeoUtils::Polygon3Compare* 
        newTarget);
        virtual Ionflux::GeoUtils::Polygon3Compare* getTarget() const;
};

}

}


%{
#include "geoutils/Polygon3CompareAxis.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Polygon3CompareAxisClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Polygon3CompareAxisClassInfo();
        virtual ~Polygon3CompareAxisClassInfo();
};

class Polygon3CompareAxis
: public Ionflux::GeoUtils::Polygon3Compare
{
    public:
        
        Polygon3CompareAxis();
		Polygon3CompareAxis(const Ionflux::GeoUtils::Polygon3CompareAxis& other);
        Polygon3CompareAxis(Ionflux::GeoUtils::AxisID initAxis, bool 
        initInvert = true);
        virtual ~Polygon3CompareAxis();
        virtual std::string getString() const;
        virtual bool compare(Ionflux::GeoUtils::Polygon3& p0, 
        Ionflux::GeoUtils::Polygon3& p1);
        static Ionflux::GeoUtils::Polygon3CompareAxis* 
        create(Ionflux::GeoUtils::AxisID initAxis, bool initInvert = true);
		virtual Ionflux::GeoUtils::Polygon3CompareAxis* copy() const;
		static Ionflux::GeoUtils::Polygon3CompareAxis* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Polygon3CompareAxis* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setAxis(Ionflux::GeoUtils::AxisID newAxis);
        virtual Ionflux::GeoUtils::AxisID getAxis() const;
};

}

}


%{
#include "geoutils/FaceCompare.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class FaceCompareClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FaceCompareClassInfo();
        virtual ~FaceCompareClassInfo();
};

class FaceCompare
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        FaceCompare();
		FaceCompare(const Ionflux::GeoUtils::FaceCompare& other);
        FaceCompare(bool initInvert, Ionflux::GeoUtils::FaceCompare* 
        initTarget = 0);
        virtual ~FaceCompare();
        virtual std::string getString() const;
        virtual bool operator()(Ionflux::GeoUtils::Face* f0, 
        Ionflux::GeoUtils::Face* f1);
        virtual bool compare(Ionflux::GeoUtils::Face& f0, 
        Ionflux::GeoUtils::Face& f1);
		virtual Ionflux::GeoUtils::FaceCompare* copy() const;
		static Ionflux::GeoUtils::FaceCompare* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::FaceCompare* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setInvert(bool newInvert);
        virtual bool getInvert() const;
        virtual void setTarget(Ionflux::GeoUtils::FaceCompare* newTarget);
        virtual Ionflux::GeoUtils::FaceCompare* getTarget() const;
};

}

}


%{
#include "geoutils/FaceCompareAxis.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class FaceCompareAxisClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FaceCompareAxisClassInfo();
        virtual ~FaceCompareAxisClassInfo();
};

class FaceCompareAxis
: public Ionflux::GeoUtils::FaceCompare
{
    public:
        
        FaceCompareAxis();
		FaceCompareAxis(const Ionflux::GeoUtils::FaceCompareAxis& other);
        FaceCompareAxis(Ionflux::GeoUtils::AxisID initAxis, bool initInvert
        = true);
        virtual ~FaceCompareAxis();
        virtual std::string getString() const;
        virtual bool compare(Ionflux::GeoUtils::Face& f0, 
        Ionflux::GeoUtils::Face& f1);
        static Ionflux::GeoUtils::FaceCompareAxis* 
        create(Ionflux::GeoUtils::AxisID initAxis, bool initInvert = true);
		virtual Ionflux::GeoUtils::FaceCompareAxis* copy() const;
		static Ionflux::GeoUtils::FaceCompareAxis* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::FaceCompareAxis* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setAxis(Ionflux::GeoUtils::AxisID newAxis);
        virtual Ionflux::GeoUtils::AxisID getAxis() const;
};

}

}


%{
#include "geoutils/ImageProperties.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class ImagePropertiesClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ImagePropertiesClassInfo();
        virtual ~ImagePropertiesClassInfo();
};

class ImageProperties
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
		static const unsigned int DEFAULT_WIDTH;
		static const unsigned int DEFAULT_HEIGHT;
		static const Ionflux::GeoUtils::Vector2 DEFAULT_ORIGIN;
        
        ImageProperties();
		ImageProperties(const Ionflux::GeoUtils::ImageProperties& other);
        virtual ~ImageProperties();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::ImageProperties* copy() const;
		static Ionflux::GeoUtils::ImageProperties* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::ImageProperties* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setFileName(const std::string& newFileName);
        virtual std::string getFileName() const;
        virtual void setWidth(unsigned int newWidth);
        virtual unsigned int getWidth() const;
        virtual void setHeight(unsigned int newHeight);
        virtual unsigned int getHeight() const;
        virtual void setOrigin(const Ionflux::GeoUtils::Vector2& 
        newOrigin);
        virtual Ionflux::GeoUtils::Vector2 getOrigin() const;
};

}

}


%{
#include "geoutils/SVGShapeStyleSource.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class SVGShapeStyleSourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SVGShapeStyleSourceClassInfo();
        virtual ~SVGShapeStyleSourceClassInfo();
};

class SVGShapeStyleSource
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        SVGShapeStyleSource();
		SVGShapeStyleSource(const Ionflux::GeoUtils::SVGShapeStyleSource& other);
        virtual ~SVGShapeStyleSource();
        virtual Ionflux::GeoUtils::SVGShapeStyle* getStyle(const 
        std::string& elementID);
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::SVGShapeStyleSource* copy() const;
		static Ionflux::GeoUtils::SVGShapeStyleSource* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::SVGShapeStyleSource* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setDefaultStyle(const 
        Ionflux::GeoUtils::SVGShapeStyle& newDefaultStyle);
        virtual Ionflux::GeoUtils::SVGShapeStyle getDefaultStyle() const;
};

}

}


%{
#include "geoutils/SVGShapeStyleMap.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class SVGShapeStyleMapClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SVGShapeStyleMapClassInfo();
        virtual ~SVGShapeStyleMapClassInfo();
};

class SVGShapeStyleMap
: public Ionflux::GeoUtils::SVGShapeStyleSource
{
    public:
        
        SVGShapeStyleMap();
		SVGShapeStyleMap(const Ionflux::GeoUtils::SVGShapeStyleMap& other);
        virtual ~SVGShapeStyleMap();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::SVGShapeStyleMap* copy() const;
		static Ionflux::GeoUtils::SVGShapeStyleMap* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::SVGShapeStyleMap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual unsigned int getNumStyles() const;
        virtual Ionflux::GeoUtils::SVGShapeStyle* getStyle(const 
        std::string& elementKey) const;

        virtual std::map<std::string, Ionflux::GeoUtils::SVGShapeStyle*>& 
        getStyles();
        virtual void addStyle(const std::string& elementKey, 
        Ionflux::GeoUtils::SVGShapeStyle* addElement);        
        virtual void removeStyle(const std::string& elementKey);
		virtual void clearStyles();
};

}

}


%{
#include "geoutils/SVGShapeStyleVectorSource.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class SVGShapeStyleVectorSourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SVGShapeStyleVectorSourceClassInfo();
        virtual ~SVGShapeStyleVectorSourceClassInfo();
};

class SVGShapeStyleVectorSource
: public Ionflux::GeoUtils::SVGShapeStyleSource
{
    public:
        
        SVGShapeStyleVectorSource();
		SVGShapeStyleVectorSource(const Ionflux::GeoUtils::SVGShapeStyleVectorSource& other);
        virtual ~SVGShapeStyleVectorSource();
        virtual Ionflux::GeoUtils::SVGShapeStyle* getStyle(const 
        std::string& elementID);
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::SVGShapeStyleVectorSource* copy() const;
		static Ionflux::GeoUtils::SVGShapeStyleVectorSource* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::SVGShapeStyleVectorSource* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setCurrentStyle(unsigned int newCurrentStyle);
        virtual unsigned int getCurrentStyle() const;        
        virtual unsigned int getNumStyles() const;
        virtual Ionflux::GeoUtils::SVGShapeStyle* getStyle(unsigned int 
        elementIndex = 0) const;
		virtual int findStyle(Ionflux::GeoUtils::SVGShapeStyle* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::SVGShapeStyle*>& 
        getStyles();
        virtual void addStyle(Ionflux::GeoUtils::SVGShapeStyle* 
        addElement);        
        virtual void removeStyle(Ionflux::GeoUtils::SVGShapeStyle* 
        removeElement);
		virtual void removeStyleIndex(unsigned int removeIndex);
		virtual void clearStyles();
};

}

}


%{
#include "geoutils/SVGImageProperties.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class SVGImagePropertiesClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SVGImagePropertiesClassInfo();
        virtual ~SVGImagePropertiesClassInfo();
};

class SVGImageProperties
: public Ionflux::GeoUtils::ImageProperties
{
    public:
        
        SVGImageProperties();
		SVGImageProperties(const Ionflux::GeoUtils::SVGImageProperties& other);
        SVGImageProperties(Ionflux::GeoUtils::SVGShapeStyleSource* 
        initStyleSource, const std::string& initSVGTemplate = 
        Ionflux::GeoUtils::SVG_TEMPLATE);
        virtual ~SVGImageProperties();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::SVGImageProperties* copy() const;
		static Ionflux::GeoUtils::SVGImageProperties* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::SVGImageProperties* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setStyleSource(Ionflux::GeoUtils::SVGShapeStyleSource*
        newStyleSource);
        virtual Ionflux::GeoUtils::SVGShapeStyleSource* getStyleSource() 
        const;
        virtual void setSvgTemplate(const std::string& newSvgTemplate);
        virtual std::string getSvgTemplate() const;
};

}

}


%{
#include "geoutils/Polygon3Set.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Polygon3;

class Polygon3SetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Polygon3SetClassInfo();
        virtual ~Polygon3SetClassInfo();
};

class Polygon3Set
: public Ionflux::GeoUtils::TransformableObject
{
    public:
		static const Ionflux::GeoUtils::Polygon3CompareAxis COMPARE_AXIS_X;
		static const Ionflux::GeoUtils::Polygon3CompareAxis COMPARE_AXIS_Y;
		static const Ionflux::GeoUtils::Polygon3CompareAxis COMPARE_AXIS_Z;
        
        Polygon3Set();
		Polygon3Set(const Ionflux::GeoUtils::Polygon3Set& other);
        virtual ~Polygon3Set();
        virtual Ionflux::GeoUtils::Polygon3* addPolygon();
        virtual void addPolygons(const Ionflux::GeoUtils::Polygon3Vector& 
        newPolygons);
        virtual void addPolygons(const Ionflux::GeoUtils::Polygon3Set& 
        newPolygons);
        virtual std::string getString() const;
        virtual std::string getSVG(const std::string& attrs = 
        SVG_DEFAULT_POLY_STYLE, const std::string& elementIDPrefix = 
        "polygon", Ionflux::GeoUtils::AxisID axis = 
        Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::SVGShapeType 
        shapeType = Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath =
        true);
        virtual std::string getSVG(const 
        Ionflux::GeoUtils::SVGShapeStyleVector& styles, const std::string& 
        elementIDPrefix = "polygon", Ionflux::GeoUtils::AxisID axis = 
        Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::SVGShapeType 
        shapeType = Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath =
        true);
        virtual std::string getSVG(Ionflux::GeoUtils::SVGImageProperties& 
        imageProperties, const std::string& elementIDPrefix = "polygon", 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y);
        virtual void writeSVG(const std::string& fileName, const 
        std::string& attrs = SVG_DEFAULT_POLY_STYLE, const std::string& 
        elementIDPrefix = "polygon", Ionflux::GeoUtils::AxisID axis = 
        Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::SVGShapeType 
        shapeType = Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath =
        true);
        virtual void writeSVG(const std::string& fileName, const 
        Ionflux::GeoUtils::SVGShapeStyleVector& styles, const std::string& 
        elementIDPrefix = "polygon", Ionflux::GeoUtils::AxisID axis = 
        Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::SVGShapeType 
        shapeType = Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath =
        true);
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual void writeSVG(Ionflux::GeoUtils::SVGImageProperties& 
        imageProperties, const std::string& elementIDPrefix = "polygon", 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y);
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Polygon3Set& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Polygon3Set& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Polygon3Set& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Polygon3Set& normalize();
        virtual Ionflux::GeoUtils::Polygon3Set& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Polygon3Set& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Polygon3Set& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Polygon3Set& transformVI(const 
        Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4*
        image = 0);
        virtual Ionflux::GeoUtils::Polygon3Set& duplicate();
        virtual void sort(Ionflux::GeoUtils::Polygon3Compare* compFunc = 
        0);
		virtual Ionflux::GeoUtils::Polygon3Set* copy() const;
		static Ionflux::GeoUtils::Polygon3Set* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Polygon3Set* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumPolygons() const;
        virtual Ionflux::GeoUtils::Polygon3* getPolygon(unsigned int 
        elementIndex = 0) const;
		virtual int findPolygon(Ionflux::GeoUtils::Polygon3* needle, unsigned int
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Polygon3*>& getPolygons();
        virtual void addPolygon(Ionflux::GeoUtils::Polygon3* addElement);        
        virtual void removePolygon(Ionflux::GeoUtils::Polygon3* 
        removeElement);
		virtual void removePolygonIndex(unsigned int removeIndex);
		virtual void clearPolygons();
};

}

}


%{
#include "geoutils/Line3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Line3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Line3ClassInfo();
        virtual ~Line3ClassInfo();
};

class Line3
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::Line3 X;
		static const Ionflux::GeoUtils::Line3 Y;
		static const Ionflux::GeoUtils::Line3 Z;
        
        Line3();
		Line3(const Ionflux::GeoUtils::Line3& other);
        Line3(const Ionflux::GeoUtils::Vector3& initP, const 
        Ionflux::GeoUtils::Vector3& initU);
        virtual ~Line3();
        virtual bool intersectPlane(const Ionflux::GeoUtils::Plane3& plane,
        Ionflux::GeoUtils::Vector3& result) const;
        virtual bool intersectionInPoly(const Ionflux::GeoUtils::Polygon3& 
        poly, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual bool operator==(const Ionflux::GeoUtils::Line3& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Line3& other) 
        const;
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::Line3* copy() const;
		static Ionflux::GeoUtils::Line3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Line3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setP(const Ionflux::GeoUtils::Vector3& newP);
        virtual Ionflux::GeoUtils::Vector3 getP() const;
        virtual void setU(const Ionflux::GeoUtils::Vector3& newU);
        virtual Ionflux::GeoUtils::Vector3 getU() const;
};

}

}


%{
#include "geoutils/Object3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Object3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Object3ClassInfo();
        virtual ~Object3ClassInfo();
};

class Object3
: public Ionflux::GeoUtils::TransformableObject
{
    public:
        
        Object3();
		Object3(const Ionflux::GeoUtils::Object3& other);
        virtual ~Object3();
        virtual Ionflux::GeoUtils::Object3& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Object3& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Object3& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Object3& normalize();
        virtual Ionflux::GeoUtils::Object3& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Object3& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Object3& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Object3& transformVI(const 
        Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4*
        image = 0);
        virtual bool checkVertex(const Ionflux::GeoUtils::Vertex3& v, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE) const = 0;
        virtual Ionflux::GeoUtils::Object3& duplicate() = 0;
		static Ionflux::GeoUtils::Object3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
};

}

}


%{
#include "geoutils/Sphere3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Sphere3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Sphere3ClassInfo();
        virtual ~Sphere3ClassInfo();
};

class Sphere3
: public Ionflux::GeoUtils::Object3
{
    public:
		static const Ionflux::GeoUtils::Sphere3 UNIT;
        
        Sphere3();
		Sphere3(const Ionflux::GeoUtils::Sphere3& other);
        Sphere3(const Ionflux::GeoUtils::Vector3& initP, double initR);
        virtual ~Sphere3();
        virtual Ionflux::GeoUtils::Vector3 getBarycenter() const;
        virtual Ionflux::GeoUtils::Range3 getBounds() const;
        virtual bool checkVertex(const Ionflux::GeoUtils::Vertex3& v, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual bool operator==(const Ionflux::GeoUtils::Sphere3& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Sphere3& other) 
        const;
        virtual std::string getString() const;
        virtual Ionflux::GeoUtils::Sphere3& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Sphere3& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Sphere3& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Sphere3& normalize();
        virtual Ionflux::GeoUtils::Sphere3& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Sphere3& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Sphere3& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Sphere3& transformVI(const 
        Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4*
        image = 0);
        virtual Ionflux::GeoUtils::Sphere3& duplicate();
		virtual Ionflux::GeoUtils::Sphere3* copy() const;
		static Ionflux::GeoUtils::Sphere3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Sphere3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setP(const Ionflux::GeoUtils::Vector3& newP);
        virtual Ionflux::GeoUtils::Vector3 getP() const;
        virtual void setR(double newR);
        virtual double getR() const;
};

}

}


%{
#include "geoutils/BoxBoundsItem.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class BoxBoundsItem;

class BoxBoundsItemClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BoxBoundsItemClassInfo();
        virtual ~BoxBoundsItemClassInfo();
};

class BoxBoundsItem
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        BoxBoundsItem();
		BoxBoundsItem(const Ionflux::GeoUtils::BoxBoundsItem& other);
        BoxBoundsItem(const Ionflux::GeoUtils::Vector3& initCenter, const 
        Ionflux::GeoUtils::Vector3& initRVec = 
        Ionflux::GeoUtils::Vector3::ZERO, const std::string& initItemID = 
        "");
        virtual ~BoxBoundsItem();
        virtual void updateBounds();
        virtual void updateRadiusAndCenter();
        virtual void clear();
        virtual Ionflux::GeoUtils::Vertex3Vector getBoxVertices();
        virtual Ionflux::GeoUtils::Polygon3Vector getBoxFaces();
        virtual int checkPlane(const Ionflux::GeoUtils::Plane3& plane, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkPlaneInner(const Ionflux::GeoUtils::Plane3& plane,
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkSphere(const Ionflux::GeoUtils::Sphere3& sphere, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkSphereInner(const Ionflux::GeoUtils::Sphere3& 
        sphere, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool checkLine(const Ionflux::GeoUtils::Line3& line, double
        t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool checkLineInner(const Ionflux::GeoUtils::Line3& line, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::RangeCompResult3 compare3(const 
        Ionflux::GeoUtils::BoxBoundsItem& other, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual Ionflux::GeoUtils::RangeCompResult compare(const 
        Ionflux::GeoUtils::BoxBoundsItem& other, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual int checkBox(const Ionflux::GeoUtils::BoxBoundsItem& other,
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkBoxInner(const Ionflux::GeoUtils::BoxBoundsItem& 
        other, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool checkRay(const Ionflux::GeoUtils::Line3& ray, double t
        = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool checkRayInner(const Ionflux::GeoUtils::Line3& ray, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool operator==(const Ionflux::GeoUtils::BoxBoundsItem& 
        other) const;
        virtual bool operator!=(const Ionflux::GeoUtils::BoxBoundsItem& 
        other) const;
        virtual std::string getXML() const;
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::BoxBoundsItem* copy() const;
		static Ionflux::GeoUtils::BoxBoundsItem* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::BoxBoundsItem* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setCenter(const Ionflux::GeoUtils::Vector3& 
        newCenter);
        virtual Ionflux::GeoUtils::Vector3 getCenter() const;
        virtual void setRVec(const Ionflux::GeoUtils::Vector3& newRVec);
        virtual Ionflux::GeoUtils::Vector3 getRVec() const;
        virtual void setItemID(const std::string& newItemID);
        virtual std::string getItemID() const;
        virtual void setBounds(const Ionflux::GeoUtils::Range3& newBounds);
        virtual Ionflux::GeoUtils::Range3 getBounds() const;
        virtual void setRadius(double newRadius);
        virtual double getRadius() const;        
        virtual unsigned int getNumBoxVertices() const;
        virtual Ionflux::GeoUtils::Vertex3* getBoxVertex(unsigned int 
        elementIndex = 0) const;
		virtual int findBoxVertex(Ionflux::GeoUtils::Vertex3* needle, unsigned 
		int occurence = 1) const;
        virtual void addBoxVertex(Ionflux::GeoUtils::Vertex3* addElement);        
        virtual void removeBoxVertex(Ionflux::GeoUtils::Vertex3* 
        removeElement);
		virtual void removeBoxVertexIndex(unsigned int removeIndex);
		virtual void clearBoxVertices();        
        virtual unsigned int getNumBoxFaces() const;
        virtual Ionflux::GeoUtils::Polygon3* getBoxFace(unsigned int 
        elementIndex = 0) const;
		virtual int findBoxFace(Ionflux::GeoUtils::Polygon3* needle, unsigned int
		occurence = 1) const;
        virtual void addBoxFace(Ionflux::GeoUtils::Polygon3* addElement);        
        virtual void removeBoxFace(Ionflux::GeoUtils::Polygon3* 
        removeElement);
		virtual void removeBoxFaceIndex(unsigned int removeIndex);
		virtual void clearBoxFaces();
};

}

}


%{
#include "geoutils/BoxBoundsItemCompare.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class BoxBoundsItemCompareClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BoxBoundsItemCompareClassInfo();
        virtual ~BoxBoundsItemCompareClassInfo();
};

class BoxBoundsItemCompare
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        BoxBoundsItemCompare();
		BoxBoundsItemCompare(const Ionflux::GeoUtils::BoxBoundsItemCompare& other);
        BoxBoundsItemCompare(bool initInvert, 
        Ionflux::GeoUtils::BoxBoundsItemCompare* initTarget = 0);
        virtual ~BoxBoundsItemCompare();
        virtual std::string getString() const;
        virtual bool operator()(Ionflux::GeoUtils::BoxBoundsItem* b0, 
        Ionflux::GeoUtils::BoxBoundsItem* b1);
        virtual bool compare(Ionflux::GeoUtils::BoxBoundsItem& b0, 
        Ionflux::GeoUtils::BoxBoundsItem& b1);
		virtual Ionflux::GeoUtils::BoxBoundsItemCompare* copy() const;
		static Ionflux::GeoUtils::BoxBoundsItemCompare* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::BoxBoundsItemCompare* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setInvert(bool newInvert);
        virtual bool getInvert() const;
        virtual void setTarget(Ionflux::GeoUtils::BoxBoundsItemCompare* 
        newTarget);
        virtual Ionflux::GeoUtils::BoxBoundsItemCompare* getTarget() const;
};

}

}


%{
#include "geoutils/BoxBoundsItemCompareAxis.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class BoxBoundsItemCompareAxis
: public Ionflux::GeoUtils::BoxBoundsItemCompare
{
    public:
        
        BoxBoundsItemCompareAxis();
		BoxBoundsItemCompareAxis(const Ionflux::GeoUtils::BoxBoundsItemCompareAxis& other);
        BoxBoundsItemCompareAxis(Ionflux::GeoUtils::AxisID initAxis, bool 
        initInvert = true);
        virtual ~BoxBoundsItemCompareAxis();
        virtual std::string getString() const;
        virtual bool compare(Ionflux::GeoUtils::BoxBoundsItem& b0, 
        Ionflux::GeoUtils::BoxBoundsItem& b1);
        static Ionflux::GeoUtils::BoxBoundsItemCompareAxis* 
        create(Ionflux::GeoUtils::AxisID initAxis, bool initInvert = true);
		virtual Ionflux::GeoUtils::BoxBoundsItemCompareAxis* copy() const;
		static Ionflux::GeoUtils::BoxBoundsItemCompareAxis* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::BoxBoundsItemCompareAxis* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setAxis(Ionflux::GeoUtils::AxisID newAxis);
        virtual Ionflux::GeoUtils::AxisID getAxis() const;
};

}

}


%{
#include "geoutils/BoxBoundsItemCompareDistanceVec3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class BoxBoundsItemCompareDistanceVec3
: public Ionflux::GeoUtils::BoxBoundsItemCompare
{
    public:
        
        BoxBoundsItemCompareDistanceVec3();
		BoxBoundsItemCompareDistanceVec3(const Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3& other);
        BoxBoundsItemCompareDistanceVec3(const Ionflux::GeoUtils::Vector3& 
        initReference, bool initInvert = false);
        virtual ~BoxBoundsItemCompareDistanceVec3();
        virtual std::string getString() const;
        virtual bool compare(Ionflux::GeoUtils::BoxBoundsItem& b0, 
        Ionflux::GeoUtils::BoxBoundsItem& b1);
        static Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3* 
        create(const Ionflux::GeoUtils::Vector3& initReference, bool 
        initInvert = false);
		virtual Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3* copy() 
		const;
		static Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::BoxBoundsItemCompareDistanceVec3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setReference(const Ionflux::GeoUtils::Vector3& 
        newReference);
        virtual Ionflux::GeoUtils::Vector3 getReference() const;
};

}

}


%{
#include "geoutils/BoxBoundsItemCompareDistancePlane3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class BoxBoundsItemCompareDistancePlane3
: public Ionflux::GeoUtils::BoxBoundsItemCompare
{
    public:
        
        BoxBoundsItemCompareDistancePlane3();
		BoxBoundsItemCompareDistancePlane3(const Ionflux::GeoUtils::BoxBoundsItemCompareDistancePlane3& other);
        BoxBoundsItemCompareDistancePlane3(const Ionflux::GeoUtils::Plane3&
        initReference, bool initInvert = false);
        virtual ~BoxBoundsItemCompareDistancePlane3();
        virtual std::string getString() const;
        virtual bool compare(Ionflux::GeoUtils::BoxBoundsItem& b0, 
        Ionflux::GeoUtils::BoxBoundsItem& b1);
        static Ionflux::GeoUtils::BoxBoundsItemCompareDistancePlane3* 
        create(const Ionflux::GeoUtils::Plane3& initReference, bool 
        initInvert = false);
		virtual Ionflux::GeoUtils::BoxBoundsItemCompareDistancePlane3* copy() 
		const;
		static Ionflux::GeoUtils::BoxBoundsItemCompareDistancePlane3* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::BoxBoundsItemCompareDistancePlane3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setReference(const Ionflux::GeoUtils::Plane3& 
        newReference);
        virtual Ionflux::GeoUtils::Plane3 getReference() const;
};

}

}


%{
#include "geoutils/ItemSource.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class BoxBoundsItem;

class ItemSourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ItemSourceClassInfo();
        virtual ~ItemSourceClassInfo();
};

class ItemSource
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        ItemSource();
		ItemSource(const Ionflux::GeoUtils::ItemSource& other);
        virtual ~ItemSource();
        virtual Ionflux::GeoUtils::BoxBoundsItem* getItem(const 
        std::string& itemID) = 0;
        virtual std::string getString() const;
};

}

}


%{
#include "geoutils/SplitSet.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class SplitSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SplitSetClassInfo();
        virtual ~SplitSetClassInfo();
};

class SplitSet
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        SplitSet();
		SplitSet(const Ionflux::GeoUtils::SplitSet& other);
        virtual ~SplitSet();
        virtual Ionflux::GeoUtils::SplitVector 
        addSplits(Ionflux::GeoUtils::AxisID axis, unsigned int num = 1);
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::SplitSet* copy() const;
		static Ionflux::GeoUtils::SplitSet* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::GeoUtils::SplitSet* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);        
        virtual unsigned int getNumSplits() const;
        virtual Ionflux::GeoUtils::Split* getSplit(unsigned int 
        elementIndex = 0) const;
		virtual int findSplit(Ionflux::GeoUtils::Split* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Split*>& getSplits();
        virtual void addSplit(Ionflux::GeoUtils::Split* addElement);        
        virtual void removeSplit(Ionflux::GeoUtils::Split* removeElement);
		virtual void removeSplitIndex(unsigned int removeIndex);
		virtual void clearSplits();
};

}

}


%{
#include "geoutils/BoundingBox.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class BoundingBoxClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BoundingBoxClassInfo();
        virtual ~BoundingBoxClassInfo();
};

class BoundingBox
: public Ionflux::GeoUtils::BoxBoundsItem
{
    public:
        
        BoundingBox();
		BoundingBox(const Ionflux::GeoUtils::BoundingBox& other);
        BoundingBox(const Ionflux::GeoUtils::Vector3& initCenter, const 
        Ionflux::GeoUtils::Vector3& initRVec = 
        Ionflux::GeoUtils::Vector3::ZERO, const std::string& initItemID = 
        "", int initLevel = 0, const Ionflux::GeoUtils::BoxBoundsItemSet* 
        initItems = 0, Ionflux::GeoUtils::BoundingBox* initParent = 0);
        virtual ~BoundingBox();
        virtual void update();
        virtual void clear();
        virtual bool addItem(Ionflux::GeoUtils::BoxBoundsItem* item, double
        maxRadius = 0.);
        virtual bool removeItem(Ionflux::GeoUtils::BoxBoundsItem* item, 
        bool update0 = true);
        virtual Ionflux::GeoUtils::BoxBoundsItemSet addItems(const 
        Ionflux::GeoUtils::BoxBoundsItemSet& newItems, unsigned int 
        maxItems = 0, double maxRadius = 0.);
        virtual unsigned int takeItems(Ionflux::GeoUtils::BoxBoundsItemSet&
        newItems, unsigned int maxItems = 0., double maxRadius = 0.);
        virtual Ionflux::GeoUtils::SplitTestResult splitTest(const 
        Ionflux::GeoUtils::Split& split, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual void updateBestSplit(const Ionflux::GeoUtils::SplitParams& 
        s, Ionflux::GeoUtils::SplitParams& best);
        virtual Ionflux::GeoUtils::Split* 
        getBestSplit(Ionflux::GeoUtils::SplitSet& splits, unsigned int 
        minItems = 0, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE, bool
        preferLongestAxis = false, double longestAxisTolerance = 0.1);
        virtual Ionflux::GeoUtils::SplitResult 
        split(Ionflux::GeoUtils::SplitSet& splits, bool recursive = false, 
        unsigned int minItems = 0, unsigned int maxLevel = 0, unsigned int 
        splitLevel = 0, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE, 
        bool preferLongestAxis = false, double longestAxisTolerance = 0.1);
        virtual Ionflux::GeoUtils::BoxBoundsItemSet 
        getItemsAbovePlane(Ionflux::GeoUtils::Plane3& plane, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::BoxBoundsItemSet 
        getItemsOnLine(Ionflux::GeoUtils::Line3& line, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::BoxBoundsItemSet 
        getItemsOnRay(Ionflux::GeoUtils::Line3& ray, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::BoxBoundsItemSet 
        getItemsInSphere(Ionflux::GeoUtils::Sphere3& sphere, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::BoxBoundsItemSet 
        getItemsInBox(Ionflux::GeoUtils::BoxBoundsItem& box, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::BoxBoundsItem* 
        getContainingLeaf(Ionflux::GeoUtils::BoxBoundsItem* item, double t 
        = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual void initFromSource(Ionflux::GeoUtils::ItemSource& source);
        virtual void getBoundingBoxes(Ionflux::GeoUtils::BoundingBoxSet& 
        target);
        virtual void getLeaves(Ionflux::GeoUtils::BoxBoundsItemSet& 
        target);
        virtual bool getItemPath(Ionflux::GeoUtils::BoxBoundsItem* item, 
        Ionflux::GeoUtils::BoundingBoxVector& target);
        virtual bool compareHierarchy(Ionflux::GeoUtils::BoundingBox& 
        other, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool validate(double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool operator==(const Ionflux::GeoUtils::BoundingBox& 
        other) const;
        virtual bool operator!=(const Ionflux::GeoUtils::BoundingBox& 
        other) const;
        virtual unsigned int getNumItems() const;
        virtual void getItems(Ionflux::GeoUtils::BoxBoundsItemSet& target) 
        const;
        virtual std::string getString() const;
        virtual void setChildIDs(const std::string& prefix, bool showLevel 
        = true, bool keepExisting = true, bool recursive = false, unsigned 
        int level = 0, unsigned int fieldWidth = 2);
        virtual std::string getXML() const;
        virtual void writeToFile(const std::string& fileName) const;
		virtual Ionflux::GeoUtils::BoundingBox* copy() const;
		static Ionflux::GeoUtils::BoundingBox* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::BoundingBox* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setLevel(int newLevel);
        virtual int getLevel() const;
        virtual void setParent(Ionflux::GeoUtils::BoundingBox* newParent);
        virtual Ionflux::GeoUtils::BoundingBox* getParent() const;
};

}

}


%{
#include "geoutils/Camera.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class CameraClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        CameraClassInfo();
        virtual ~CameraClassInfo();
};

class Camera
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::Vector3 DEFAULT_RIGHT;
		static const Ionflux::GeoUtils::CameraSetupFlags DEFAULT_SETUP_FLAGS;
		static const Ionflux::GeoUtils::CameraMode MODE_PERSPECTIVE;
		static const Ionflux::GeoUtils::CameraMode MODE_ORTHO;
		static const bool DEFAULT_ADJUST_LOCATION;
        
        Camera();
		Camera(const Ionflux::GeoUtils::Camera& other);
        Camera(Ionflux::GeoUtils::Vector3 initLocation, 
        Ionflux::GeoUtils::Vector3 initDirection = 
        Ionflux::GeoUtils::Vector3::E_Z, Ionflux::GeoUtils::Vector3 
        initLookAt = Ionflux::GeoUtils::Vector3::E_Z, 
        Ionflux::GeoUtils::Vector3 initRight = 
        Ionflux::GeoUtils::Camera::DEFAULT_RIGHT, 
        Ionflux::GeoUtils::Vector3 initUp = 
        Ionflux::GeoUtils::Vector3::E_Y, Ionflux::GeoUtils::Vector3 initSky
        = Ionflux::GeoUtils::Vector3::E_Y, double initAngle = 1., double 
        initLens = 24., Ionflux::GeoUtils::CameraSetupFlags initSetupFlags 
        = Ionflux::GeoUtils::Camera::DEFAULT_SETUP_FLAGS);
        virtual ~Camera();
        virtual void setDefault();
        virtual void validate(const Ionflux::GeoUtils::CameraSetupFlags* 
        newSetupFlags = 0, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Matrix4 
        getRotationMatrix(Ionflux::GeoUtils::HandednessID handedness = 
        Ionflux::GeoUtils::HANDEDNESS_RIGHT, Ionflux::GeoUtils::AxisID 
        upAxis = Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID 
        depthAxis = Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID 
        horizonAxis = Ionflux::GeoUtils::AXIS_X);
        virtual Ionflux::GeoUtils::Matrix4 getTranslationMatrix(bool 
        adjustLocation = 
        Ionflux::GeoUtils::Camera::DEFAULT_ADJUST_LOCATION);
        virtual Ionflux::GeoUtils::Matrix4 
        getPerspectiveMatrix(Ionflux::GeoUtils::AxisID depthAxis = 
        Ionflux::GeoUtils::AXIS_Y);
        virtual Ionflux::GeoUtils::Matrix4 
        getViewMatrix(Ionflux::GeoUtils::CameraMode mode = 
        Ionflux::GeoUtils::Camera::MODE_PERSPECTIVE, bool adjustLocation = 
        Ionflux::GeoUtils::Camera::DEFAULT_ADJUST_LOCATION, 
        Ionflux::GeoUtils::HandednessID handedness = 
        Ionflux::GeoUtils::HANDEDNESS_RIGHT, Ionflux::GeoUtils::AxisID 
        upAxis = Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID 
        depthAxis = Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID 
        horizonAxis = Ionflux::GeoUtils::AXIS_X);
        virtual void setOriginCam(double distance = 10., double rotX = 
        -30., double rotY = 0., double rotZ = 30.);
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::Camera* copy() const;
        virtual void setLocation(const Ionflux::GeoUtils::Vector3& 
        newLocation);
        virtual Ionflux::GeoUtils::Vector3 getLocation() const;
        virtual void setDirection(const Ionflux::GeoUtils::Vector3& 
        newDirection);
        virtual Ionflux::GeoUtils::Vector3 getDirection() const;
        virtual void setLookAt(const Ionflux::GeoUtils::Vector3& 
        newLookAt);
        virtual Ionflux::GeoUtils::Vector3 getLookAt() const;
        virtual void setRight(const Ionflux::GeoUtils::Vector3& newRight);
        virtual Ionflux::GeoUtils::Vector3 getRight() const;
        virtual void setUp(const Ionflux::GeoUtils::Vector3& newUp);
        virtual Ionflux::GeoUtils::Vector3 getUp() const;
        virtual void setSky(const Ionflux::GeoUtils::Vector3& newSky);
        virtual Ionflux::GeoUtils::Vector3 getSky() const;
        virtual void setAngle(double newAngle);
        virtual double getAngle() const;
        virtual void setLens(double newLens);
        virtual double getLens() const;
        virtual void setSetupFlags(const 
        Ionflux::GeoUtils::CameraSetupFlags& newSetupFlags);
        virtual Ionflux::GeoUtils::CameraSetupFlags getSetupFlags() const;
};

}

}


%{
#include "geoutils/Vertex.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VertexClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VertexClassInfo();
        virtual ~VertexClassInfo();
};

class Vertex
: public Ionflux::GeoUtils::Vertex3
{
    public:
        
        Vertex();
		Vertex(const Ionflux::GeoUtils::Vertex& other);
        Vertex(double initX, double initY, double initZ, const 
        Ionflux::GeoUtils::Vector3& initNormal = 
        Ionflux::GeoUtils::Vector3::E_X);
        Vertex(const Ionflux::ObjectBase::DoubleVector& initCoords, const 
        Ionflux::GeoUtils::Vector3& initNormal = 
        Ionflux::GeoUtils::Vector3::E_X);
        Vertex(const Ionflux::GeoUtils::Vector3& initCoords, const 
        Ionflux::GeoUtils::Vector3& initNormal = 
        Ionflux::GeoUtils::Vector3::E_X);
        virtual ~Vertex();
        virtual Ionflux::GeoUtils::Vertex interpolate(const 
        Ionflux::GeoUtils::Vertex& other, double t, 
        Ionflux::GeoUtils::Interpolator* interpolator = 0) const;
        virtual Ionflux::GeoUtils::Vertex& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Vertex& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Vertex& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Vertex& normalize();
        virtual Ionflux::GeoUtils::Vertex& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Vertex& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Vertex& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Vertex& duplicate();
        virtual std::string getString() const;
        static Ionflux::GeoUtils::Vertex* create(double newX, double newY, 
        double newZ);
		virtual Ionflux::GeoUtils::Vertex* copy() const;
		static Ionflux::GeoUtils::Vertex* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Vertex* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setNormal(const Ionflux::GeoUtils::Vector3& 
        newNormal);
        virtual Ionflux::GeoUtils::Vector3 getNormal() const;
};

}

}


%{
#include "geoutils/Face.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class FaceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FaceClassInfo();
        virtual ~FaceClassInfo();
};

class Face
: public Ionflux::GeoUtils::BoxBoundsItem, public 
Ionflux::GeoUtils::TransformableObject
{
    public:
		static const unsigned int VERTEX_INDEX_NONE;
        
        Face();
		Face(const Ionflux::GeoUtils::Face& other);
        Face(const Ionflux::ObjectBase::UIntVector* initVerts, 
        Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, const 
        Ionflux::GeoUtils::TexCoordsVector* initUV = 0, const 
        Ionflux::GeoUtils::ColorVector* initVertexColors = 0);
        Face(unsigned int v0, unsigned int v1, unsigned int v2, unsigned 
        int v3 = Ionflux::GeoUtils::Face::VERTEX_INDEX_NONE, 
        Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, const 
        Ionflux::GeoUtils::TexCoordsVector* initUV = 0, const 
        Ionflux::GeoUtils::ColorVector* initVertexColors = 0);
        virtual ~Face();
        virtual void copyVertices();
        virtual void update();
        virtual void clearTangentSpace();
        virtual void clearPolygon();
        virtual void clear();
        virtual void addVertices(unsigned int v0, unsigned int v1, unsigned
        int v2, unsigned int v3 = 
        Ionflux::GeoUtils::Face::VERTEX_INDEX_NONE);
        virtual void addVertices(const Ionflux::ObjectBase::UIntVector& 
        newVerts);
        virtual void addTexCoords(const Ionflux::GeoUtils::TexCoordsVector&
        newTexCoords);
        virtual void addVertexColors(const Ionflux::GeoUtils::ColorVector& 
        newVertexColors);
        virtual Ionflux::GeoUtils::Vector3 getTangent();
        virtual Ionflux::GeoUtils::Vector3 getBinormal();
        virtual Ionflux::GeoUtils::Vector3 getNormal();
        virtual Ionflux::GeoUtils::Matrix3 getTangentBase();
        virtual Ionflux::GeoUtils::Polygon3* getPolygon();
        virtual bool checkLineInner(const Ionflux::GeoUtils::Line3& line, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkPlaneInner(const Ionflux::GeoUtils::Plane3& plane,
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkSphereInner(const Ionflux::GeoUtils::Sphere3& 
        sphere, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkBoxInner(const Ionflux::GeoUtils::BoxBoundsItem& 
        other, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::FaceVector getTris();
        virtual bool isPlanar(double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual void makePlanar(double p = 1., double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool operator==(const Ionflux::GeoUtils::Face& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Face& other) 
        const;
        virtual std::string getString() const;
        virtual bool isBackface(const Ionflux::GeoUtils::Vector3& front);
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual Ionflux::GeoUtils::Range3 getBounds();
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Face& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Face& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Face& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Face& normalize();
        virtual Ionflux::GeoUtils::Face& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Face& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Face& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Face& duplicate();
        static Ionflux::GeoUtils::Face* create(unsigned int v0, unsigned 
        int v1, unsigned int v2, unsigned int v3 = 
        Ionflux::GeoUtils::Face::VERTEX_INDEX_NONE, 
        Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, const 
        Ionflux::GeoUtils::TexCoordsVector* initUV = 0);
        virtual std::string getXMLDataVertices() const;
        virtual std::string getXMLDataTexCoords() const;
        virtual std::string getXML() const;
        virtual void setFromXMLData(const std::string& vertexData, const 
        std::string& texCoordData);
		virtual Ionflux::GeoUtils::Face* copy() const;
		static Ionflux::GeoUtils::Face* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Face* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);        
        virtual unsigned int getNumVertices() const;
        virtual unsigned int getVertex(unsigned int elementIndex = 0) 
        const;
		virtual int findVertex(unsigned int needle, unsigned int occurence = 1) 
		const;
        virtual std::vector<unsigned int>& getVertices();
        virtual void addVertex(unsigned int addElement);        
        virtual void removeVertex(unsigned int removeElement);
		virtual void removeVertexIndex(unsigned int removeIndex);
		virtual void clearVertices();        
        virtual unsigned int getNumTexCoords() const;
        virtual Ionflux::GeoUtils::TexCoords getTexCoord(unsigned int 
        elementIndex = 0) const;
		virtual int findTexCoord(Ionflux::GeoUtils::TexCoords needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::TexCoords>& getTexCoords();
        virtual void addTexCoord(Ionflux::GeoUtils::TexCoords addElement);        
        virtual void removeTexCoord(Ionflux::GeoUtils::TexCoords 
        removeElement);
		virtual void removeTexCoordIndex(unsigned int removeIndex);
		virtual void clearTexCoords();        
        virtual unsigned int getNumVertexColors() const;
        virtual Ionflux::GeoUtils::Color getVertexColor(unsigned int 
        elementIndex = 0) const;
		virtual int findVertexColor(Ionflux::GeoUtils::Color needle, unsigned int
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Color>& getVertexColors();
        virtual void addVertexColor(Ionflux::GeoUtils::Color addElement);        
        virtual void removeVertexColor(Ionflux::GeoUtils::Color 
        removeElement);
		virtual void removeVertexColorIndex(unsigned int removeIndex);
		virtual void clearVertexColors();
        virtual void setVertexSource(Ionflux::GeoUtils::Vertex3Set* 
        newVertexSource);
        virtual Ionflux::GeoUtils::Vertex3Set* getVertexSource() const;
};

}

}


%{
#include "geoutils/Mesh.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class MeshClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MeshClassInfo();
        virtual ~MeshClassInfo();
};

class Mesh
: public Ionflux::GeoUtils::BoxBoundsItem, public 
Ionflux::GeoUtils::ItemSource, public 
Ionflux::GeoUtils::TransformableObject
{
    public:
		static const std::string DEFAULT_ID;
        
        Mesh();
		Mesh(const Ionflux::GeoUtils::Mesh& other);
        Mesh(Ionflux::GeoUtils::Vertex3Vector* initVerts, const 
        Ionflux::GeoUtils::FaceVector* initFaces);
        Mesh(Ionflux::GeoUtils::Vertex3Set* initVertexSource, const 
        Ionflux::GeoUtils::FaceVector* initFaces);
        virtual ~Mesh();
        virtual Ionflux::GeoUtils::Range3 getBounds();
        virtual void copyVertices();
        virtual Ionflux::GeoUtils::Vertex3* addVertex();
        virtual void addVertices(Ionflux::GeoUtils::Vertex3Vector& 
        newVerts);
        virtual void addVertices(Ionflux::GeoUtils::Vertex3Set& newVerts);
        virtual void update();
        virtual void clear();
        virtual void addFaces(const Ionflux::GeoUtils::FaceVector& 
        newFaces);
        virtual void setFaceIDs();
        virtual Ionflux::GeoUtils::BoxBoundsItem* getItem(const 
        std::string& itemID);
        virtual int checkPlaneInner(const Ionflux::GeoUtils::Plane3& plane,
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkSphereInner(const Ionflux::GeoUtils::Sphere3& 
        sphere, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool checkLineInner(const Ionflux::GeoUtils::Line3& line, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkBoxInner(const Ionflux::GeoUtils::BoxBoundsItem& 
        other, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool operator==(const Ionflux::GeoUtils::Mesh& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Mesh& other) 
        const;
        virtual std::string getString() const;
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Mesh& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Mesh& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Mesh& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Mesh& normalize();
        virtual Ionflux::GeoUtils::Mesh& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Mesh& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Mesh& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Mesh& duplicate();
        virtual void getPolygons(Ionflux::GeoUtils::Polygon3Set& target);
        virtual std::string getXML() const;
        virtual void writeToFile(const std::string& fileName) const;
        virtual void removeBackfaces(const Ionflux::GeoUtils::Vector3& 
        front);
        virtual void sortFaces(Ionflux::GeoUtils::FaceCompare* compFunc = 
        0);
        virtual unsigned int makePlanar(const 
        Ionflux::ObjectBase::UIntVector& indices, unsigned int 
        maxIterations = 10000, double p = 1., double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        static Ionflux::GeoUtils::Mesh* plane();
        static Ionflux::GeoUtils::Mesh* cube();
        static Ionflux::GeoUtils::Mesh* cylinder(unsigned int subDivs = 10,
        double length = 1., double radius = 0.5);
        static Ionflux::GeoUtils::Mesh* arrow(unsigned int subDivs = 10, 
        double length = 1., double radius = 0.005, double headLength = 0.1,
        double headRadius = 4.);
		virtual Ionflux::GeoUtils::Mesh* copy() const;
		static Ionflux::GeoUtils::Mesh* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Mesh* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setVertexSource(Ionflux::GeoUtils::Vertex3Set* 
        newVertexSource);
        virtual Ionflux::GeoUtils::Vertex3Set* getVertexSource() const;        
        virtual unsigned int getNumVertices() const;
        virtual Ionflux::GeoUtils::Vertex3* getVertex(unsigned int 
        elementIndex = 0) const;
		virtual int findVertex(Ionflux::GeoUtils::Vertex3* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Vertex3*>& getVertices();
        virtual void addVertex(Ionflux::GeoUtils::Vertex3* addElement);        
        virtual void removeVertex(Ionflux::GeoUtils::Vertex3* 
        removeElement);
		virtual void removeVertexIndex(unsigned int removeIndex);
		virtual void clearVertices();        
        virtual unsigned int getNumFaces() const;
        virtual Ionflux::GeoUtils::Face* getFace(unsigned int elementIndex 
        = 0) const;
		virtual int findFace(Ionflux::GeoUtils::Face* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Face*>& getFaces();
        virtual void addFace(Ionflux::GeoUtils::Face* addElement);        
        virtual void removeFace(Ionflux::GeoUtils::Face* removeElement);
		virtual void removeFaceIndex(unsigned int removeIndex);
		virtual void clearFaces();
};

}

}


%{
#include "geoutils/Voxel.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VoxelClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VoxelClassInfo();
        virtual ~VoxelClassInfo();
};

class Voxel
: public Ionflux::GeoUtils::BoxBoundsItem
{
    public:
        
        Voxel();
		Voxel(const Ionflux::GeoUtils::Voxel& other);
        Voxel(const Ionflux::GeoUtils::Vector3& initIndex, double 
        initEdgeLength = 1., const Ionflux::GeoUtils::Vector3& initOffset =
        Ionflux::GeoUtils::Vector3::ZERO);
        virtual ~Voxel();
        virtual void clear();
        virtual void initBounds();
        virtual std::string getString() const;
        static Ionflux::GeoUtils::Voxel* create(const 
        Ionflux::GeoUtils::Vector3& initIndex, double initEdgeLength = 1., 
        const Ionflux::GeoUtils::Vector3& initOffset = 
        Ionflux::GeoUtils::Vector3::ZERO);
        static void toVertexSet(Ionflux::GeoUtils::BoxBoundsItemSet& 
        source, Ionflux::GeoUtils::Vertex3Set& target);
		virtual Ionflux::GeoUtils::Voxel* copy() const;
		static Ionflux::GeoUtils::Voxel* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Voxel* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setIndex(const Ionflux::GeoUtils::Vector3& newIndex);
        virtual Ionflux::GeoUtils::Vector3 getIndex() const;
        virtual void setEdgeLength(double newEdgeLength);
        virtual double getEdgeLength() const;
        virtual void setOffset(const Ionflux::GeoUtils::Vector3& 
        newOffset);
        virtual Ionflux::GeoUtils::Vector3 getOffset() const;
};

}

}


namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

class Vector3MappingClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vector3MappingClassInfo();
        virtual ~Vector3MappingClassInfo();
};

class Vector3Mapping
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        Vector3Mapping();
		Vector3Mapping(const Ionflux::GeoUtils::Mapping::Vector3Mapping& other);
        virtual ~Vector3Mapping();
        virtual Ionflux::GeoUtils::Vector3 
        operator()(Ionflux::Mapping::MappingValue value) const;
        virtual Ionflux::GeoUtils::Vector3 
        call(Ionflux::Mapping::MappingValue value) const = 0;
        virtual std::string getString() const;
		static Ionflux::GeoUtils::Mapping::Vector3Mapping* 
		upcast(Ionflux::ObjectBase::IFObject* other);
};

class Compose3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Compose3ClassInfo();
        virtual ~Compose3ClassInfo();
};

class Compose3
: public Ionflux::GeoUtils::Mapping::Vector3Mapping
{
    public:
        
        Compose3();
		Compose3(const Ionflux::GeoUtils::Mapping::Compose3& other);
        Compose3(Ionflux::Mapping::Mapping* initFuncX0, 
        Ionflux::Mapping::Mapping* initFuncX1 = 0, 
        Ionflux::Mapping::Mapping* initFuncX2 = 0);
        virtual ~Compose3();
        virtual void setFuncs(Ionflux::Mapping::Mapping* newFuncX0 = 0, 
        Ionflux::Mapping::Mapping* newFuncX1 = 0, 
        Ionflux::Mapping::Mapping* newFuncX2 = 0);
        virtual void setFuncsEqual(Ionflux::Mapping::Mapping* newFunc = 0);
        virtual Ionflux::GeoUtils::Vector3 
        call(Ionflux::Mapping::MappingValue value) const;
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::Mapping::Compose3* copy() const;
		static Ionflux::GeoUtils::Mapping::Compose3* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Mapping::Compose3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setFuncX0(Ionflux::Mapping::Mapping* newFuncX0);
        virtual Ionflux::Mapping::Mapping* getFuncX0() const;
        virtual void setFuncX1(Ionflux::Mapping::Mapping* newFuncX1);
        virtual Ionflux::Mapping::Mapping* getFuncX1() const;
        virtual void setFuncX2(Ionflux::Mapping::Mapping* newFuncX2);
        virtual Ionflux::Mapping::Mapping* getFuncX2() const;
};

class Accept3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Accept3ClassInfo();
        virtual ~Accept3ClassInfo();
};

class Accept3
: public Ionflux::GeoUtils::Mapping::Vector3Mapping
{
    public:
        
        Accept3();
		Accept3(const Ionflux::GeoUtils::Mapping::Accept3& other);
        Accept3(Ionflux::GeoUtils::Mapping::Vector3Mapping* initSource, 
        Ionflux::Mapping::MappingValue initMaxIters = 
        Ionflux::Mapping::MAX_ITERATIONS);
        virtual ~Accept3();
        virtual Ionflux::GeoUtils::Vector3 
        call(Ionflux::Mapping::MappingValue value) const;
        virtual std::string getString() const;
        virtual bool checkCondition(const Ionflux::GeoUtils::Vector3& v) 
        const = 0;
		static Ionflux::GeoUtils::Mapping::Accept3* 
		upcast(Ionflux::ObjectBase::IFObject* other);
        virtual void setMaxIters(unsigned int newMaxIters);
        virtual unsigned int getMaxIters() const;
        virtual void setSource(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        newSource);
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* getSource() 
        const;
};

class AcceptLength3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        AcceptLength3ClassInfo();
        virtual ~AcceptLength3ClassInfo();
};

class AcceptLength3
: public Ionflux::GeoUtils::Mapping::Accept3
{
    public:
		static const Ionflux::GeoUtils::Range DEFAULT_LENGTH_RANGE;
        
        AcceptLength3();
		AcceptLength3(const Ionflux::GeoUtils::Mapping::AcceptLength3& other);
        AcceptLength3(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        initSource, const Ionflux::GeoUtils::Range& initLengthRange = 
        DEFAULT_LENGTH_RANGE, Ionflux::Mapping::MappingValue initMaxIters =
        Ionflux::Mapping::MAX_ITERATIONS);
        virtual ~AcceptLength3();
        virtual std::string getString() const;
        virtual bool checkCondition(const Ionflux::GeoUtils::Vector3& v) 
        const;
		static Ionflux::GeoUtils::Mapping::AcceptLength3* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Mapping::AcceptLength3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setLengthRange(const Ionflux::GeoUtils::Range& 
        newLengthRange);
        virtual Ionflux::GeoUtils::Range getLengthRange() const;
};

class AcceptVolume3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        AcceptVolume3ClassInfo();
        virtual ~AcceptVolume3ClassInfo();
};

class AcceptVolume3
: public Ionflux::GeoUtils::Mapping::Accept3
{
    public:
        
        AcceptVolume3();
		AcceptVolume3(const Ionflux::GeoUtils::Mapping::AcceptVolume3& other);
        AcceptVolume3(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        initSource, Ionflux::GeoUtils::Object3* initRefObject, 
        Ionflux::Mapping::MappingValue initMaxIters = 
        Ionflux::Mapping::MAX_ITERATIONS);
        virtual ~AcceptVolume3();
        virtual std::string getString() const;
        virtual bool checkCondition(const Ionflux::GeoUtils::Vector3& v) 
        const;
		virtual Ionflux::GeoUtils::Mapping::AcceptVolume3* copy() const;
		static Ionflux::GeoUtils::Mapping::AcceptVolume3* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Mapping::AcceptVolume3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setRefObject(Ionflux::GeoUtils::Object3* 
        newRefObject);
        virtual Ionflux::GeoUtils::Object3* getRefObject() const;
};

class Lookup3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Lookup3ClassInfo();
        virtual ~Lookup3ClassInfo();
};

class Lookup3
: public Ionflux::GeoUtils::Mapping::Vector3Mapping
{
    public:
		static const unsigned int DEFAULT_NUM_ENTRIES;
		static const Ionflux::Mapping::Range CLAMP_RANGE;
        
        Lookup3();
		Lookup3(const Ionflux::GeoUtils::Mapping::Lookup3& other);
        Lookup3(Ionflux::GeoUtils::Mapping::Vector3Mapping* initSource, 
        unsigned int initNumEntries = DEFAULT_NUM_ENTRIES);
        virtual ~Lookup3();
        virtual void update(unsigned int numEntries = DEFAULT_NUM_ENTRIES);
        virtual void addEntries(const Ionflux::GeoUtils::Vector3Vector& 
        newEntries, unsigned int numEntries = 0);
        virtual Ionflux::GeoUtils::Vector3 
        call(Ionflux::Mapping::MappingValue value) const;
        virtual std::string getString() const;
		static Ionflux::GeoUtils::Mapping::Lookup3* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Mapping::Lookup3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumEntries() const;
        virtual Ionflux::GeoUtils::Vector3* getEntry(unsigned int 
        elementIndex = 0) const;
		virtual int findEntry(Ionflux::GeoUtils::Vector3* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Vector3*>& getEntries();
        virtual void addEntry(Ionflux::GeoUtils::Vector3* addElement);        
        virtual void removeEntry(Ionflux::GeoUtils::Vector3* 
        removeElement);
		virtual void removeEntryIndex(unsigned int removeIndex);
        virtual void clearEntries();
        virtual void setSource(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        newSource);
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* getSource() 
        const;
};

}

class Vector3MappingSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vector3MappingSetClassInfo();
        virtual ~Vector3MappingSetClassInfo();
};

class Vector3MappingSet
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Vector3MappingSet();
		Vector3MappingSet(const Ionflux::GeoUtils::Vector3MappingSet& other);
        Vector3MappingSet(const Ionflux::GeoUtils::Vector3MappingVector& 
        initMappings);
        virtual ~Vector3MappingSet();
        virtual void addMappings(const 
        Ionflux::GeoUtils::Vector3MappingVector& newMappings);
        virtual std::string getString() const;
		static Ionflux::GeoUtils::Vector3MappingSet* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Vector3MappingSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumMappings() const;
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        getMapping(unsigned int elementIndex = 0) const;
		virtual int findMapping(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
		needle, unsigned int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Mapping::Vector3Mapping*>& 
        getMappings();
        virtual void addMapping(Ionflux::GeoUtils::Mapping::Vector3Mapping*
        addElement);        
        virtual void 
        removeMapping(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        removeElement);
		virtual void removeMappingIndex(unsigned int removeIndex);
        virtual void clearMappings();
};

namespace TransformNodes
{

class TransformNodeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TransformNodeClassInfo();
        virtual ~TransformNodeClassInfo();
};

class TransformNode
: virtual public Ionflux::ObjectBase::IFObject
{
    protected:
        // Required so SWIG knows this is an abstract class.
		virtual void process() = 0;
        
    public:
		static const unsigned int DEFAULT_LOOP_MAX;
        
        TransformNode();
		TransformNode(const Ionflux::GeoUtils::TransformNodes::TransformNode& other);
        TransformNode(const Ionflux::ObjectBase::IFObjectID& nodeID);
        virtual ~TransformNode();
        virtual void addInputs(const 
        Ionflux::GeoUtils::InputNodeSpecVector& newInputs);
        virtual void 
        getLinkedInputs(Ionflux::GeoUtils::TransformNodeVector& target);
        virtual void setInput(const 
        Ionflux::GeoUtils::TransformNodes::InputNodeSpec& newInput, 
        unsigned int inputID = INPUT_NEXT_FREE);
        virtual void clearInputCache();
        virtual void updateInputs();
        virtual void clearInputGroups();
        virtual void cleanup();
        virtual void update();
        virtual std::string getString() const;
        virtual std::string getDebugInfo(bool expand = true);
        virtual void enableDebugMode(bool newDebugMode = true, bool expand 
        = false);
		static Ionflux::GeoUtils::TransformNodes::TransformNode* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		virtual void setParam(Ionflux::ObjectBase::IFParamID paramID, 
		Ionflux::Mapping::MappingValue paramValue);
		virtual Ionflux::Mapping::MappingValue 
		getParam(Ionflux::ObjectBase::IFParamID paramID);        
        virtual unsigned int getNumInputs() const;
        virtual Ionflux::GeoUtils::TransformNodes::InputNodeSpec 
        getInput(unsigned int elementIndex = 0) const;
		virtual int findInput(Ionflux::GeoUtils::TransformNodes::InputNodeSpec 
		needle, unsigned int occurence = 1) const;
        virtual 
        std::vector<Ionflux::GeoUtils::TransformNodes::InputNodeSpec>& 
        getInputs();
        virtual void addInput(const 
        Ionflux::GeoUtils::TransformNodes::InputNodeSpec& addElement);        
        virtual void removeInput(const 
        Ionflux::GeoUtils::TransformNodes::InputNodeSpec& removeElement);
		virtual void removeInputIndex(unsigned int removeIndex);
        virtual void clearInputs();        
        virtual unsigned int getNumOutputs() const;
        virtual Ionflux::GeoUtils::TransformableGroup* getOutput(unsigned 
        int elementIndex = 0) const;
		virtual int findOutput(Ionflux::GeoUtils::TransformableGroup* needle, 
		unsigned int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::TransformableGroup*>& 
        getOutputs();
        virtual void addOutput(Ionflux::GeoUtils::TransformableGroup* 
        addElement);        
        virtual void removeOutput(Ionflux::GeoUtils::TransformableGroup* 
        removeElement);
		virtual void removeOutputIndex(unsigned int removeIndex);
        virtual void clearOutputs();
        virtual void setLoopMax(unsigned int newLoopMax);
        virtual unsigned int getLoopMax() const;
        virtual void setMaxNumInputs(unsigned int newMaxNumInputs);
        virtual unsigned int getMaxNumInputs() const;
        virtual void setUpdateCounter(unsigned int newUpdateCounter);
        virtual unsigned int getUpdateCounter() const;
};

class ConnectionClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ConnectionClassInfo();
        virtual ~ConnectionClassInfo();
};

class Connection
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        Connection();
		Connection(const Ionflux::GeoUtils::TransformNodes::Connection& other);
        Connection(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        initSource, Ionflux::GeoUtils::TransformNodes::TransformNode* 
        initTarget, unsigned int outputID = 0, unsigned int inputID = 
        INPUT_NEXT_FREE, bool connectLater = false);
        virtual ~Connection();
        virtual bool 
        connect(Ionflux::GeoUtils::TransformNodes::TransformNode* newSource
        = 0, Ionflux::GeoUtils::TransformNodes::TransformNode* newTarget = 
        0, unsigned int newOutputID = 0, unsigned int newInputID = 
        INPUT_NEXT_FREE, bool connectLater = false);
        virtual bool disconnect();
        virtual void clear();
        virtual bool isConnected();
        virtual std::string getString() const;
        virtual bool operator==(const 
        Ionflux::GeoUtils::TransformNodes::Connection& other) const;
        virtual bool operator!=(const 
        Ionflux::GeoUtils::TransformNodes::Connection& other) const;
        static bool check(Ionflux::GeoUtils::TransformNodes::TransformNode*
        checkSource, Ionflux::GeoUtils::TransformNodes::TransformNode* 
        checkTarget, unsigned int checkOutputID = 0, unsigned int 
        checkInputID = 0);
		static Ionflux::GeoUtils::TransformNodes::Connection* 
		upcast(Ionflux::ObjectBase::IFObject* other);
        virtual Ionflux::GeoUtils::TransformNodes::TransformNode* 
        getSource() const;
        virtual Ionflux::GeoUtils::TransformNodes::TransformNode* 
        getTarget() const;
        virtual unsigned int getOutputID() const;
        virtual unsigned int getInputID() const;
};

}

}

}


%{
#include "geoutils/ParamControl.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class ParamControlClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ParamControlClassInfo();
        virtual ~ParamControlClassInfo();
};

class ParamControl
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        ParamControl();
		ParamControl(const Ionflux::GeoUtils::TransformNodes::ParamControl& other);
        ParamControl(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        initNode, Ionflux::ObjectBase::IFParamID initParamID = "", 
        Ionflux::Mapping::Mapping* initFunc = 0, unsigned int initCoord = 
        COORDINATE_NOT_SET);
        virtual ~ParamControl();
        virtual void call(Ionflux::Mapping::MappingValue value) const;
        virtual void operator()(Ionflux::Mapping::MappingValue value) 
        const;
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::ParamControl* copy() const;
		static Ionflux::GeoUtils::TransformNodes::ParamControl* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::ParamControl* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void 
        setNode(Ionflux::GeoUtils::TransformNodes::TransformNode* newNode);
        virtual Ionflux::GeoUtils::TransformNodes::TransformNode* getNode()
        const;
        virtual void setParamID(const Ionflux::ObjectBase::IFParamID& 
        newParamID);
        virtual Ionflux::ObjectBase::IFParamID getParamID() const;
        virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
        virtual Ionflux::Mapping::Mapping* getFunc() const;
        virtual void setCoord(unsigned int newCoord);
        virtual unsigned int getCoord() const;
};

}

}

}


namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class TransformGraphClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TransformGraphClassInfo();
        virtual ~TransformGraphClassInfo();
};

class TransformGraph
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int NODE_INDEX_LAST;
        
        TransformGraph();
		TransformGraph(const Ionflux::GeoUtils::TransformNodes::TransformGraph& other);
        virtual ~TransformGraph();
        virtual void 
        addLinked(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        newNode);
        virtual void clear();
        virtual void addNodes(Ionflux::GeoUtils::TransformNodeVector& 
        newNodes);
        virtual Ionflux::GeoUtils::TransformNodes::Connection* 
        findConnection(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        source = 0, Ionflux::GeoUtils::TransformNodes::TransformNode* 
        target = 0, unsigned int outputID = 0, unsigned int inputID = 0, 
        bool connectLater = false);
        virtual bool 
        connect(Ionflux::GeoUtils::TransformNodes::TransformNode* source = 
        0, Ionflux::GeoUtils::TransformNodes::TransformNode* target = 0, 
        unsigned int outputID = 0, unsigned int inputID = INPUT_NEXT_FREE, 
        bool connectLater = false);
        virtual bool 
        disconnect(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        source, Ionflux::GeoUtils::TransformNodes::TransformNode* target, 
        unsigned int outputID = 0, unsigned int inputID = 0);
        virtual void chain(unsigned int first = 0, unsigned int last = 
        NODE_INDEX_LAST);
        virtual void 
        connectRange(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        source, Ionflux::GeoUtils::TransformNodes::TransformNode* target, 
        unsigned int numOutputSlots, unsigned int firstOutputID = 0, 
        unsigned int firstInputID = INPUT_NEXT_FREE);
        virtual void 
        connectFan(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        source, Ionflux::GeoUtils::TransformNodes::TransformNode* target, 
        unsigned int numInputSlots, unsigned int outputID = 0, unsigned int
        firstInputID = INPUT_NEXT_FREE);
        virtual void setIO(unsigned int sourceIndex = 0, unsigned int 
        drainIndex = NODE_INDEX_LAST);
        virtual std::string getString() const;
        virtual void addInputs(const 
        Ionflux::GeoUtils::InputNodeSpecVector& newInputs);
        virtual void 
        getLinkedInputs(Ionflux::GeoUtils::TransformNodeVector& target);
        virtual void setInput(const 
        Ionflux::GeoUtils::TransformNodes::InputNodeSpec& newInput, 
        unsigned int inputID = INPUT_NEXT_FREE);
        virtual void update();
		virtual Ionflux::GeoUtils::TransformNodes::TransformGraph* copy() const;
		static Ionflux::GeoUtils::TransformNodes::TransformGraph* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::TransformGraph* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumInputs() const;
        virtual Ionflux::GeoUtils::TransformNodes::InputNodeSpec 
        getInput(unsigned int elementIndex = 0) const;
		virtual int findInput(Ionflux::GeoUtils::TransformNodes::InputNodeSpec 
		needle, unsigned int occurence = 1) const;
        virtual 
        std::vector<Ionflux::GeoUtils::TransformNodes::InputNodeSpec>& 
        getInputs();
        virtual void addInput(const 
        Ionflux::GeoUtils::TransformNodes::InputNodeSpec& addElement);        
        virtual void removeInput(const 
        Ionflux::GeoUtils::TransformNodes::InputNodeSpec& removeElement);
		virtual void removeInputIndex(unsigned int removeIndex);
        virtual void clearInputs();        
        virtual unsigned int getNumOutputs() const;
        virtual Ionflux::GeoUtils::TransformableGroup* getOutput(unsigned 
        int elementIndex = 0) const;
		virtual int findOutput(Ionflux::GeoUtils::TransformableGroup* needle, 
		unsigned int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::TransformableGroup*>& 
        getOutputs();
        virtual void addOutput(Ionflux::GeoUtils::TransformableGroup* 
        addElement);        
        virtual void removeOutput(Ionflux::GeoUtils::TransformableGroup* 
        removeElement);
		virtual void removeOutputIndex(unsigned int removeIndex);
        virtual void clearOutputs();        
        virtual unsigned int getNumConnections() const;
        virtual Ionflux::GeoUtils::TransformNodes::Connection* 
        getConnection(unsigned int elementIndex = 0) const;
		virtual int findConnection(Ionflux::GeoUtils::TransformNodes::Connection*
		needle, unsigned int occurence = 1) const;
        virtual 
        std::vector<Ionflux::GeoUtils::TransformNodes::Connection*>& 
        getConnections();
        virtual void 
        addConnection(Ionflux::GeoUtils::TransformNodes::Connection* 
        addElement);        
        virtual void 
        removeConnection(Ionflux::GeoUtils::TransformNodes::Connection* 
        removeElement);
		virtual void removeConnectionIndex(unsigned int removeIndex);
        virtual void clearConnections();        
        virtual unsigned int getNumNodes() const;
        virtual Ionflux::GeoUtils::TransformNodes::TransformNode* 
        getNode(unsigned int elementIndex = 0) const;
		virtual int findNode(Ionflux::GeoUtils::TransformNodes::TransformNode* 
		needle, unsigned int occurence = 1) const;
        virtual 
        std::vector<Ionflux::GeoUtils::TransformNodes::TransformNode*>& 
        getNodes();
        virtual void 
        addNode(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        addElement);        
        virtual void 
        removeNode(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        removeElement);
		virtual void removeNodeIndex(unsigned int removeIndex);
        virtual void clearNodes();
        virtual void 
        setSource(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        newSource);
        virtual Ionflux::GeoUtils::TransformNodes::TransformNode* 
        getSource() const;
        virtual void 
        setDrain(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        newDrain);
        virtual Ionflux::GeoUtils::TransformNodes::TransformNode* 
        getDrain() const;
};

}

}

}


%{
#include "geoutils/WriteSVG.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class WriteSVGClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        WriteSVGClassInfo();
        virtual ~WriteSVGClassInfo();
};

class WriteSVG
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int INPUT_FIRST;
		static const unsigned int OUTPUT_COMPOSITE;
        
        WriteSVG();
		WriteSVG(const Ionflux::GeoUtils::TransformNodes::WriteSVG& other);
        WriteSVG(const std::string& initFileName, const std::string& 
        initElementIDPrefix = "polygon", Ionflux::GeoUtils::AxisID initAxis
        = Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::SVGShapeType 
        initShapeType = Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool 
        initClosePath = true, const Ionflux::GeoUtils::SVGShapeStyleVector*
        initStyles = 0, unsigned int initWidth = 1000, unsigned int 
        initHeight = 1000, unsigned int initOriginX = 500, unsigned int 
        initOriginY = 500, const std::string& initSVGTemplate = 
        Ionflux::GeoUtils::SVG_TEMPLATE, const 
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~WriteSVG();
        virtual std::string getString() const;
        virtual void addStyles(const 
        Ionflux::GeoUtils::SVGShapeStyleVector& newStyles);
		virtual Ionflux::GeoUtils::TransformNodes::WriteSVG* copy() const;
		static Ionflux::GeoUtils::TransformNodes::WriteSVG* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::WriteSVG* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setFileName(const std::string& newFileName);
        virtual std::string getFileName() const;        
        virtual unsigned int getNumStyles() const;
        virtual Ionflux::GeoUtils::SVGShapeStyle* getStyle(unsigned int 
        elementIndex = 0) const;
		virtual int findStyle(Ionflux::GeoUtils::SVGShapeStyle* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::SVGShapeStyle*>& 
        getStyles();
        virtual void addStyle(Ionflux::GeoUtils::SVGShapeStyle* 
        addElement);        
        virtual void removeStyle(Ionflux::GeoUtils::SVGShapeStyle* 
        removeElement);
		virtual void removeStyleIndex(unsigned int removeIndex);
		virtual void clearStyles();
        virtual void setElementIDPrefix(const std::string& 
        newElementIDPrefix);
        virtual std::string getElementIDPrefix() const;
        virtual void setAxis(Ionflux::GeoUtils::AxisID newAxis);
        virtual Ionflux::GeoUtils::AxisID getAxis() const;
        virtual void setShapeType(Ionflux::GeoUtils::SVGShapeType 
        newShapeType);
        virtual Ionflux::GeoUtils::SVGShapeType getShapeType() const;
        virtual void setClosePath(bool newClosePath);
        virtual bool getClosePath() const;
        virtual void setWidth(unsigned int newWidth);
        virtual unsigned int getWidth() const;
        virtual void setHeight(unsigned int newHeight);
        virtual unsigned int getHeight() const;
        virtual void setOriginX(unsigned int newOriginX);
        virtual unsigned int getOriginX() const;
        virtual void setOriginY(unsigned int newOriginY);
        virtual unsigned int getOriginY() const;
        virtual void setSvgTemplate(const std::string& newSvgTemplate);
        virtual std::string getSvgTemplate() const;
};

}

}

}


namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class DuplicateClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        DuplicateClassInfo();
        virtual ~DuplicateClassInfo();
};

class Duplicate
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
		static const unsigned int DEFAULT_NUM_DUPLICATES;
		static const Ionflux::Mapping::Range CLAMP_RANGE;
        
        Duplicate();
		Duplicate(const Ionflux::GeoUtils::TransformNodes::Duplicate& other);
        Duplicate(unsigned int initNumDuplicates, 
        Ionflux::Mapping::Mapping* initFunc = 0, const 
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Duplicate();
        virtual std::string getString() const;
		static Ionflux::GeoUtils::TransformNodes::Duplicate* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Duplicate* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setNumDuplicates(unsigned int newNumDuplicates);
        virtual unsigned int getNumDuplicates() const;
        virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
        virtual Ionflux::Mapping::Mapping* getFunc() const;
};

class MatrixTransformClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MatrixTransformClassInfo();
        virtual ~MatrixTransformClassInfo();
};

class MatrixTransform
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
        
        MatrixTransform();
		MatrixTransform(const Ionflux::GeoUtils::TransformNodes::MatrixTransform& other);
        MatrixTransform(const Ionflux::GeoUtils::Matrix4& initMatrix, const
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~MatrixTransform();
        virtual std::string getString() const;
		static Ionflux::GeoUtils::TransformNodes::MatrixTransform* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::MatrixTransform* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setMatrix(const Ionflux::GeoUtils::Matrix4& 
        newMatrix);
        virtual Ionflux::GeoUtils::Matrix4 getMatrix() const;
};

class RotateClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        RotateClassInfo();
        virtual ~RotateClassInfo();
};

class Rotate
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
		static const Ionflux::GeoUtils::Range DEFAULT_ANGLE_RANGE;
        
        Rotate();
		Rotate(const Ionflux::GeoUtils::TransformNodes::Rotate& other);
        Rotate(Ionflux::GeoUtils::AxisID initAxis, double initAngle = 0., 
        double deltaAngle = 0., Ionflux::Mapping::Mapping* initIndexFunc = 
        0, Ionflux::Mapping::Mapping* initDistanceFunc = 0, 
        Ionflux::GeoUtils::Range initIndexRange = DEFAULT_ANGLE_RANGE, 
        Ionflux::GeoUtils::Range initDistanceRange = DEFAULT_ANGLE_RANGE, 
        Ionflux::GeoUtils::CenteringMethod initCenteringMethod = 
        CENTER_ORIGIN, const Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Rotate();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::Rotate* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Rotate* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Rotate* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual void setParam(Ionflux::ObjectBase::IFParamID paramID, 
		Ionflux::Mapping::MappingValue paramValue);
		virtual Ionflux::Mapping::MappingValue 
		getParam(Ionflux::ObjectBase::IFParamID paramID);
        virtual void setAxis(Ionflux::GeoUtils::AxisID newAxis);
        virtual Ionflux::GeoUtils::AxisID getAxis() const;
        virtual void setAngle(Ionflux::Mapping::MappingValue newAngle);
        virtual Ionflux::Mapping::MappingValue getAngle() const;
        virtual void setDeltaAngle(Ionflux::Mapping::MappingValue 
        newDeltaAngle);
        virtual Ionflux::Mapping::MappingValue getDeltaAngle() const;
        virtual void setIndexFunc(Ionflux::Mapping::Mapping* newIndexFunc);
        virtual Ionflux::Mapping::Mapping* getIndexFunc() const;
        virtual void setDistanceFunc(Ionflux::Mapping::Mapping* 
        newDistanceFunc);
        virtual Ionflux::Mapping::Mapping* getDistanceFunc() const;
        virtual void setIndexRange(const Ionflux::GeoUtils::Range& 
        newIndexRange);
        virtual Ionflux::GeoUtils::Range getIndexRange() const;
        virtual void setDistanceRange(const Ionflux::GeoUtils::Range& 
        newDistanceRange);
        virtual Ionflux::GeoUtils::Range getDistanceRange() const;
        virtual void setCenteringMethod(Ionflux::GeoUtils::CenteringMethod 
        newCenteringMethod);
        virtual Ionflux::GeoUtils::CenteringMethod getCenteringMethod() 
        const;
};

class TranslateClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TranslateClassInfo();
        virtual ~TranslateClassInfo();
};

class Translate
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
        
        Translate();
		Translate(const Ionflux::GeoUtils::TransformNodes::Translate& other);
        Translate(const Ionflux::GeoUtils::Vector3& initOffset, 
        Ionflux::GeoUtils::Mapping::Vector3Mapping* initIndexFunc = 0, 
        Ionflux::GeoUtils::Mapping::Vector3Mapping* initDistanceFunc = 0, 
        const Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Translate();
        virtual std::string getString() const;
		static Ionflux::GeoUtils::TransformNodes::Translate* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Translate* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setOffset(const Ionflux::GeoUtils::Vector3& 
        newOffset);
        virtual Ionflux::GeoUtils::Vector3 getOffset() const;
        virtual void 
        setIndexFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        newIndexFunc);
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* getIndexFunc() 
        const;
        virtual void 
        setDistanceFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        newDistanceFunc);
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        getDistanceFunc() const;
};

class ScaleClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ScaleClassInfo();
        virtual ~ScaleClassInfo();
};

class Scale
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
        
        Scale();
		Scale(const Ionflux::GeoUtils::TransformNodes::Scale& other);
        Scale(const Ionflux::GeoUtils::Vector3& initScale, 
        Ionflux::GeoUtils::Mapping::Vector3Mapping* initIndexFunc = 0, 
        Ionflux::GeoUtils::Mapping::Vector3Mapping* initDistanceFunc = 0, 
        Ionflux::GeoUtils::CenteringMethod initCenteringMethod = 
        CENTER_ORIGIN, Ionflux::Mapping::MappingValue initScaleFactor = 1.,
        Ionflux::Mapping::MappingValue initDeltaScaleFactor = 0., const 
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Scale();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::Scale* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Scale* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Scale* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual void setParam(Ionflux::ObjectBase::IFParamID paramID, 
		Ionflux::Mapping::MappingValue paramValue);
		virtual Ionflux::Mapping::MappingValue 
		getParam(Ionflux::ObjectBase::IFParamID paramID);
        virtual void setScale(const Ionflux::GeoUtils::Vector3& newScale);
        virtual Ionflux::GeoUtils::Vector3 getScale() const;
        virtual void 
        setIndexFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        newIndexFunc);
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* getIndexFunc() 
        const;
        virtual void 
        setDistanceFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        newDistanceFunc);
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        getDistanceFunc() const;
        virtual void setCenteringMethod(Ionflux::GeoUtils::CenteringMethod 
        newCenteringMethod);
        virtual Ionflux::GeoUtils::CenteringMethod getCenteringMethod() 
        const;
        virtual void setScaleFactor(Ionflux::Mapping::MappingValue 
        newScaleFactor);
        virtual Ionflux::Mapping::MappingValue getScaleFactor() const;
        virtual void setDeltaScaleFactor(Ionflux::Mapping::MappingValue 
        newDeltaScaleFactor);
        virtual Ionflux::Mapping::MappingValue getDeltaScaleFactor() const;
};

class CenterClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        CenterClassInfo();
        virtual ~CenterClassInfo();
};

class Center
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
        
        Center();
		Center(const Ionflux::GeoUtils::TransformNodes::Center& other);
        Center(Ionflux::GeoUtils::CenteringMethod initMethod, const 
        Ionflux::GeoUtils::Vector3& initOrigin = GeoUtils::Vector3::ZERO, 
        const Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Center();
        virtual std::string getString() const;
		static Ionflux::GeoUtils::TransformNodes::Center* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Center* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setOrigin(const Ionflux::GeoUtils::Vector3& 
        newOrigin);
        virtual Ionflux::GeoUtils::Vector3 getOrigin() const;
        virtual void setMethod(Ionflux::GeoUtils::CenteringMethod 
        newMethod);
        virtual Ionflux::GeoUtils::CenteringMethod getMethod() const;
};

class NormalizeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NormalizeClassInfo();
        virtual ~NormalizeClassInfo();
};

class Normalize
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
        
        Normalize();
		Normalize(const Ionflux::GeoUtils::TransformNodes::Normalize& other);
        Normalize(const Ionflux::ObjectBase::IFObjectID& nodeID);
        virtual ~Normalize();
        virtual std::string getString() const;
		static Ionflux::GeoUtils::TransformNodes::Normalize* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Normalize* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

class ArrayClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ArrayClassInfo();
        virtual ~ArrayClassInfo();
};

class Array
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
		static const unsigned int DEFAULT_NUM_ROWS;
		static const unsigned int DEFAULT_NUM_COLUMNS;
		static const double DEFAULT_CELL_WIDTH;
		static const double DEFAULT_CELL_HEIGHT;
        
        Array();
		Array(const Ionflux::GeoUtils::TransformNodes::Array& other);
        Array(unsigned int initNumRows, unsigned int initNumColumns = 
        DEFAULT_NUM_COLUMNS, double initCellWidth = DEFAULT_CELL_WIDTH, 
        double initCellHeight = DEFAULT_CELL_HEIGHT, const 
        Ionflux::GeoUtils::Vector3& initOffset = GeoUtils::Vector3::ZERO, 
        const Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Array();
        virtual std::string getString() const;
		static Ionflux::GeoUtils::TransformNodes::Array* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Array* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setOffset(const Ionflux::GeoUtils::Vector3& 
        newOffset);
        virtual Ionflux::GeoUtils::Vector3 getOffset() const;
        virtual void setNumRows(unsigned int newNumRows);
        virtual unsigned int getNumRows() const;
        virtual void setNumColumns(unsigned int newNumColumns);
        virtual unsigned int getNumColumns() const;
        virtual void setCellWidth(double newCellWidth);
        virtual double getCellWidth() const;
        virtual void setCellHeight(double newCellHeight);
        virtual double getCellHeight() const;
};

class FlattenClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FlattenClassInfo();
        virtual ~FlattenClassInfo();
};

class Flatten
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
        
        Flatten();
		Flatten(const Ionflux::GeoUtils::TransformNodes::Flatten& other);
        Flatten(const Ionflux::ObjectBase::IFObjectID& nodeID);
        virtual ~Flatten();
        virtual std::string getString() const;
		static Ionflux::GeoUtils::TransformNodes::Flatten* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Flatten* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

class MergeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MergeClassInfo();
        virtual ~MergeClassInfo();
};

class Merge
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int INPUT_FIRST;
		static const unsigned int OUTPUT_TARGET;
        
        Merge();
		Merge(const Ionflux::GeoUtils::TransformNodes::Merge& other);
        Merge(const Ionflux::ObjectBase::IFObjectID& nodeID);
        virtual ~Merge();
        virtual std::string getString() const;
		static Ionflux::GeoUtils::TransformNodes::Merge* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Merge* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

class ExplodeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ExplodeClassInfo();
        virtual ~ExplodeClassInfo();
};

class Explode
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_FIRST;
		static const unsigned int DEFAULT_ELEMENTS_PER_GROUP;
        
        Explode();
		Explode(const Ionflux::GeoUtils::TransformNodes::Explode& other);
        Explode(unsigned int initElementsPerGroup, const 
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Explode();
        virtual std::string getString() const;
		static Ionflux::GeoUtils::TransformNodes::Explode* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Explode* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setElementsPerGroup(unsigned int newElementsPerGroup);
        virtual unsigned int getElementsPerGroup() const;
};

class WrapClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        WrapClassInfo();
        virtual ~WrapClassInfo();
};

class Wrap
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int INPUT_FIRST;
		static const unsigned int OUTPUT_TARGET;
        
        Wrap();
		Wrap(const Ionflux::GeoUtils::TransformNodes::Wrap& other);
        Wrap(const Ionflux::ObjectBase::IFObjectID& nodeID);
        virtual ~Wrap();
        virtual std::string getString() const;
		static Ionflux::GeoUtils::TransformNodes::Wrap* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Wrap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

class UnwrapClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        UnwrapClassInfo();
        virtual ~UnwrapClassInfo();
};

class Unwrap
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_FIRST;
        
        Unwrap();
		Unwrap(const Ionflux::GeoUtils::TransformNodes::Unwrap& other);
        Unwrap(const Ionflux::ObjectBase::IFObjectID& nodeID);
        virtual ~Unwrap();
        virtual std::string getString() const;
		static Ionflux::GeoUtils::TransformNodes::Unwrap* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Unwrap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

class IterateClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        IterateClassInfo();
        virtual ~IterateClassInfo();
};

class Iterate
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_FIRST;
		static const unsigned int DEFAULT_NUM_ITERATIONS;
        
        Iterate();
		Iterate(const Ionflux::GeoUtils::TransformNodes::Iterate& other);
        Iterate(unsigned int initNumIterations, const 
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Iterate();
        virtual std::string getString() const;
		static Ionflux::GeoUtils::TransformNodes::Iterate* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Iterate* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setNumIterations(unsigned int newNumIterations);
        virtual unsigned int getNumIterations() const;
};

class SourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SourceClassInfo();
        virtual ~SourceClassInfo();
};

class Source
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int OUTPUT_TARGET;
        
        Source();
		Source(const Ionflux::GeoUtils::TransformNodes::Source& other);
        Source(Ionflux::GeoUtils::TransformableGroup* initSource, const 
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Source();
        virtual std::string getString() const;
		static Ionflux::GeoUtils::TransformNodes::Source* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Source* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setSource(Ionflux::GeoUtils::TransformableGroup* 
        newSource);
        virtual Ionflux::GeoUtils::TransformableGroup* getSource() const;
};

class CacheClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        CacheClassInfo();
        virtual ~CacheClassInfo();
};

class Cache
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
        
        Cache();
		Cache(const Ionflux::GeoUtils::TransformNodes::Cache& other);
        Cache(const Ionflux::ObjectBase::IFObjectID& nodeID);
        virtual ~Cache();
        virtual std::string getString() const;
        virtual void update();
		static Ionflux::GeoUtils::TransformNodes::Cache* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Cache* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

class CloneClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        CloneClassInfo();
        virtual ~CloneClassInfo();
};

class Clone
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    protected:
        // Required so SWIG knows this is not an abstract class.
		virtual void process();
        
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_FIRST;
		static const unsigned int DEFAULT_NUM_CLONES;
        
        Clone();
		Clone(const Ionflux::GeoUtils::TransformNodes::Clone& other);
        Clone(unsigned int initNumClones, const 
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Clone();
        virtual std::string getString() const;
		static Ionflux::GeoUtils::TransformNodes::Clone* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Clone* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setNumClones(unsigned int newNumClones);
        virtual unsigned int getNumClones() const;
};

}

}

}


%{
#include "geoutils/Batch.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class BatchClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BatchClassInfo();
        virtual ~BatchClassInfo();
};

class Batch
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int INPUT_FIRST;
		static const unsigned int OUTPUT_FIRST;
		static const unsigned int DEFAULT_PROCESSOR_INPUT_ID;
        
        Batch();
		Batch(const Ionflux::GeoUtils::TransformNodes::Batch& other);
        Batch(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        initProcessor, unsigned int initProcessorInputID = 
        DEFAULT_PROCESSOR_INPUT_ID, const Ionflux::ObjectBase::IFObjectID& 
        nodeID = "");
        virtual ~Batch();
        virtual std::string getString() const;
        virtual void addControls(Ionflux::GeoUtils::ParamControlVector& 
        newControls);
		virtual Ionflux::GeoUtils::TransformNodes::Batch* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Batch* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Batch* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void 
        setProcessor(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        newProcessor);
        virtual Ionflux::GeoUtils::TransformNodes::TransformNode* 
        getProcessor() const;        
        virtual unsigned int getNumControls() const;
        virtual Ionflux::GeoUtils::TransformNodes::ParamControl* 
        getControl(unsigned int elementIndex = 0) const;
		virtual int findControl(Ionflux::GeoUtils::TransformNodes::ParamControl* 
		needle, unsigned int occurence = 1) const;
        virtual 
        std::vector<Ionflux::GeoUtils::TransformNodes::ParamControl*>& 
        getControls();
        virtual void 
        addControl(Ionflux::GeoUtils::TransformNodes::ParamControl* 
        addElement);        
        virtual void 
        removeControl(Ionflux::GeoUtils::TransformNodes::ParamControl* 
        removeElement);
		virtual void removeControlIndex(unsigned int removeIndex);
		virtual void clearControls();
        virtual void setProcessorInputID(unsigned int newProcessorInputID);
        virtual unsigned int getProcessorInputID() const;        
        virtual unsigned int getNumDimensions() const;
        virtual unsigned int getDimension(unsigned int elementIndex = 0) 
        const;
		virtual int findDimension(unsigned int needle, unsigned int occurence = 
		1) const;
        virtual std::vector<unsigned int>& getDimensions();
        virtual void addDimension(unsigned int addElement);        
        virtual void removeDimension(unsigned int removeElement);
		virtual void removeDimensionIndex(unsigned int removeIndex);
		virtual void clearDimensions();
};

}

}

}


namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class ScatterClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ScatterClassInfo();
        virtual ~ScatterClassInfo();
};

class Scatter
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
		static const unsigned int DEFAULT_NUM_LUT_ENTRIES;
		static const Ionflux::Mapping::Range OFFSET_INDEX_RANGE;
        
        Scatter();
		Scatter(const Ionflux::GeoUtils::TransformNodes::Scatter& other);
        Scatter(const Ionflux::GeoUtils::Vector3& initOffset, 
        Ionflux::GeoUtils::Mapping::Vector3Mapping* initOffsetFunc = 0, 
        Ionflux::Mapping::Mapping* initOffsetIndexFunc = 0, const 
        Ionflux::GeoUtils::Vector3& initOffsetScale = 
        GeoUtils::Vector3::E_SUM, Ionflux::Mapping::MappingValue 
        initOffsetScaleFactor = 1., Ionflux::Mapping::MappingValue 
        initOffsetDeltaScaleFactor = 0., Ionflux::Mapping::MappingValue 
        initOffsetIndexOffset = 0., Ionflux::Mapping::MappingValue 
        initOffsetIndexScale = 1., const Ionflux::GeoUtils::Vector3& 
        initElementScale = GeoUtils::Vector3::E_SUM, 
        Ionflux::Mapping::MappingValue initElementScaleFactor = 1., 
        Ionflux::Mapping::MappingValue initElementDeltaScaleFactor = 0., 
        Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        initElementScaleIndexFunc = 0, 
        Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        initElementScaleDistanceFunc = 0, 
        Ionflux::GeoUtils::CenteringMethod initCenteringMethod = 
        CENTER_BARYCENTER, const Ionflux::ObjectBase::IFObjectID& nodeID = 
        "");
        virtual ~Scatter();
        virtual std::string getString() const;
        static Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        createLUT(unsigned int numEntries = DEFAULT_NUM_LUT_ENTRIES, const 
        Ionflux::GeoUtils::Vector3& stdDev = 
        Ionflux::GeoUtils::Vector3::E_SUM, const 
        Ionflux::GeoUtils::Vector3& mean = 
        Ionflux::GeoUtils::Vector3::ZERO, Ionflux::GeoUtils::Object3* 
        refObject = 0, Ionflux::Mapping::Mapping* sourceFuncX = 0, 
        Ionflux::Mapping::Mapping* sourceFuncY = 0, 
        Ionflux::Mapping::Mapping* sourceFuncZ = 0);
		virtual Ionflux::GeoUtils::TransformNodes::Scatter* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Scatter* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Scatter* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual void setParam(Ionflux::ObjectBase::IFParamID paramID, 
		Ionflux::Mapping::MappingValue paramValue);
		virtual Ionflux::Mapping::MappingValue 
		getParam(Ionflux::ObjectBase::IFParamID paramID);
        virtual void setOffset(const Ionflux::GeoUtils::Vector3& 
        newOffset);
        virtual Ionflux::GeoUtils::Vector3 getOffset() const;
        virtual void 
        setOffsetFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        newOffsetFunc);
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* getOffsetFunc()
        const;
        virtual void setOffsetIndexFunc(Ionflux::Mapping::Mapping* 
        newOffsetIndexFunc);
        virtual Ionflux::Mapping::Mapping* getOffsetIndexFunc() const;
        virtual void setOffsetScale(const Ionflux::GeoUtils::Vector3& 
        newOffsetScale);
        virtual Ionflux::GeoUtils::Vector3 getOffsetScale() const;
        virtual void setOffsetScaleFactor(Ionflux::Mapping::MappingValue 
        newOffsetScaleFactor);
        virtual Ionflux::Mapping::MappingValue getOffsetScaleFactor() 
        const;
        virtual void 
        setOffsetDeltaScaleFactor(Ionflux::Mapping::MappingValue 
        newOffsetDeltaScaleFactor);
        virtual Ionflux::Mapping::MappingValue getOffsetDeltaScaleFactor() 
        const;
        virtual void setOffsetIndexOffset(Ionflux::Mapping::MappingValue 
        newOffsetIndexOffset);
        virtual Ionflux::Mapping::MappingValue getOffsetIndexOffset() 
        const;
        virtual void setOffsetIndexScale(Ionflux::Mapping::MappingValue 
        newOffsetIndexScale);
        virtual Ionflux::Mapping::MappingValue getOffsetIndexScale() const;
        virtual void setElementScale(const Ionflux::GeoUtils::Vector3& 
        newElementScale);
        virtual Ionflux::GeoUtils::Vector3 getElementScale() const;
        virtual void setElementScaleFactor(Ionflux::Mapping::MappingValue 
        newElementScaleFactor);
        virtual Ionflux::Mapping::MappingValue getElementScaleFactor() 
        const;
        virtual void 
        setElementDeltaScaleFactor(Ionflux::Mapping::MappingValue 
        newElementDeltaScaleFactor);
        virtual Ionflux::Mapping::MappingValue getElementDeltaScaleFactor()
        const;
        virtual void 
        setElementScaleIndexFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping*
        newElementScaleIndexFunc);
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        getElementScaleIndexFunc() const;
        virtual void 
        setElementScaleDistanceFunc(Ionflux::GeoUtils::Mapping::Vector3Mapping*
        newElementScaleDistanceFunc);
        virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* 
        getElementScaleDistanceFunc() const;
        virtual void setCenteringMethod(Ionflux::GeoUtils::CenteringMethod 
        newCenteringMethod);
        virtual Ionflux::GeoUtils::CenteringMethod getCenteringMethod() 
        const;
};

}

}

}

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
%template(ColorVector) std::vector<Ionflux::GeoUtils::Color>;
%template(Dictionary) std::map<std::string, std::string>;
%template(SVGShapeStyleVector) std::vector<Ionflux::GeoUtils::SVGShapeStyle*>;
%template(SVGShapeStyleStringMap) std::map<std::string, Ionflux::GeoUtils::SVGShapeStyle*>;
%template(TransformNodeVector) std::vector<Ionflux::GeoUtils::TransformNodes::TransformNode*>;
%template(InputNodeSpecVector) std::vector<Ionflux::GeoUtils::TransformNodes::InputNodeSpec>;
%template(Vector3Vector) std::vector<Ionflux::GeoUtils::Vector3*>;
%template(ParamControlVector) std::vector<Ionflux::GeoUtils::TransformNodes::ParamControl*>;
