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
    Ionflux::GeoUtils::Vertex3Set& target);
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

$Range

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
        return $$self->getElement(index);
    }
    void __setitem__(int index, double value)
    {
        return $$self->setElement(index, value);
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
        return $$self->getCoord(index);
    }
    void __setitem__(int index, double value)
    {
        return $$self->setCoord(index, value);
    }
}

}

}

$Vector3

namespace Ionflux
{

namespace GeoUtils
{

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

%rename(mult3) operator*(double, const Ionflux::GeoUtils::Vector3&);

Ionflux::GeoUtils::Vector3 operator*(double c, const 
Ionflux::GeoUtils::Vector3& v);

}

}

$Range3

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
        return $$self->getElement(index);
    }
    void __setitem__(int index, double value)
    {
        return $$self->setElement(index, value);
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
$Face
$Mesh
$Voxel

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

$ParamControl

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

$WriteSVG

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

$Batch

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

