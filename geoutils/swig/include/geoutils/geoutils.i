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


%{
#include "geoutils/Clock.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

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
		virtual Ionflux::GeoUtils::Clock* copy() const;
		static Ionflux::GeoUtils::Clock* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Clock* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
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
        virtual double getParam(double v) const;
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
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::Range* copy() const;
		static Ionflux::GeoUtils::Range* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Range* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
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


%{
#include "geoutils/Vector.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VectorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VectorClassInfo();
        virtual ~VectorClassInfo();
};

class Vector
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const unsigned int NUM_ELEMENTS;
        
        Vector();
		Vector(const Ionflux::GeoUtils::Vector& other);
        virtual ~Vector();
        virtual void cleanup();
        virtual void zero();
        virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
        newElements);
        virtual void setElements(const Ionflux::GeoUtils::Vector& other, 
        unsigned int sourceOffset = 0, unsigned int targetOffset = 0);
        virtual void setElements(double x0, double x1 = 0., double x2 = 0.,
        double x3 = 0., double x4 = 0., double x5 = 0., double x6 = 0., 
        double x7 = 0., double x8 = 0., double x9 = 0., double x10 = 0., 
        double x11 = 0., double x12 = 0.);
        virtual void getElements(Ionflux::ObjectBase::DoubleVector& target)
        const;
        virtual double getElement(unsigned int index) const;
        virtual void setElement(unsigned int index, double value);
        virtual bool eq(const Ionflux::GeoUtils::Vector& other, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual double dot(const Ionflux::GeoUtils::Vector& other) const;
        virtual double norm() const;
        virtual double length() const;
        virtual Ionflux::GeoUtils::Vector& normalizeIP();
        virtual Ionflux::GeoUtils::Vector& multiplyIP(double c);
        virtual Ionflux::GeoUtils::Vector& divideIP(double c);
        virtual Ionflux::GeoUtils::Vector& flipIP();
        virtual Ionflux::GeoUtils::Vector& multiplyIP(const 
        Ionflux::GeoUtils::Vector& other);
        virtual Ionflux::GeoUtils::Vector& subtractIP(const 
        Ionflux::GeoUtils::Vector& other);
        virtual Ionflux::GeoUtils::Vector& addIP(const 
        Ionflux::GeoUtils::Vector& other);
        virtual Ionflux::GeoUtils::Vector& roundIP(unsigned int numDecimals
        = 0);
        virtual bool operator==(const Ionflux::GeoUtils::Vector& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Vector& other) 
        const;
        virtual double operator*(const Ionflux::GeoUtils::Vector& other) 
        const;
        virtual unsigned int getNumElements() const;
        virtual void getElementSigns(Ionflux::ObjectBase::IntVector& 
        target) const;
        virtual void getElementSigns(Ionflux::GeoUtils::Vector& target) 
        const;
        virtual std::string getValueStringF(unsigned int fieldWidth = 5, 
        unsigned int precision = 3, const std::string& colSep = " ") const;
        virtual std::string getXMLAttributeDataValueString() const;
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Vector* copy() const;
		static Ionflux::GeoUtils::Vector* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Vector* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual bool serialize(std::string& target) const;
        virtual Ionflux::ObjectBase::DataSize deserialize(const std::string& source, int offset = 0);
        virtual bool serialize(Ionflux::ObjectBase::IFIOContext& ioCtx, bool addMagicWord = true) const;
        virtual Ionflux::ObjectBase::DataSize deserialize(Ionflux::ObjectBase::IFIOContext& ioCtx, Ionflux::ObjectBase::DataSize offset = Ionflux::ObjectBase::DATA_SIZE_INVALID, bool checkMagicWord = true);
        virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllable() const;
        virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllableBase() const;
};

}

}


%{
#include "geoutils/Vector2.hpp"
%}

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
: public Ionflux::GeoUtils::Vector
{
    public:
		static const unsigned int NUM_ELEMENTS;
		static const Ionflux::GeoUtils::Vector2 ZERO;
		static const Ionflux::GeoUtils::Vector2 E_X;
		static const Ionflux::GeoUtils::Vector2 E_Y;
        
        Vector2();
		Vector2(const Ionflux::GeoUtils::Vector2& other);
        Vector2(double initX0, double initX1);
        Vector2(const Ionflux::ObjectBase::DoubleVector& initElements0);
        virtual ~Vector2();
        virtual void setElements(double newX0, double newX1);
        virtual Ionflux::GeoUtils::Vector2 flip() const;
        virtual Ionflux::GeoUtils::Vector2 normalize() const;
        virtual Ionflux::GeoUtils::Vector2 project(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual Ionflux::GeoUtils::Vector2 ortho(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual Ionflux::GeoUtils::Vector2 swap() const;
        virtual Ionflux::GeoUtils::Vector2 multElements(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual Ionflux::GeoUtils::Vector2 operator+(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual Ionflux::GeoUtils::Vector2 operator-(const 
        Ionflux::GeoUtils::Vector2& other) const;
        virtual Ionflux::GeoUtils::Vector2 operator*(double c) const;
        virtual double operator*(const Ionflux::GeoUtils::Vector2& other) 
        const;
        virtual Ionflux::GeoUtils::Vector2 operator/(double c) const;
        virtual unsigned int getNumElements() const;
        static Ionflux::GeoUtils::Vector2 axis(Ionflux::GeoUtils::AxisID 
        axisID);
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Vector2* copy() const;
		static Ionflux::GeoUtils::Vector2* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Vector2* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Vector2* create(double initX0, double initX1, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Vector2* create(const 
		Ionflux::ObjectBase::DoubleVector& initElements0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setX0(double newX0);
        virtual double getX0() const;
        virtual void setX1(double newX1);
        virtual double getX1() const;
};

Ionflux::GeoUtils::Vector2 operator*(double c, const 
Ionflux::GeoUtils::Vector2& v);

}

}


%{
#include "geoutils/Matrix.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class MatrixClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MatrixClassInfo();
        virtual ~MatrixClassInfo();
};

class Matrix
: public Ionflux::GeoUtils::Vector
{
    public:
		static const unsigned int NUM_ROWS;
		static const unsigned int NUM_COLS;
        
        Matrix();
		Matrix(const Ionflux::GeoUtils::Matrix& other);
        virtual ~Matrix();
        virtual double getElement(unsigned int index) const;
        virtual double getElement(unsigned int rowIndex, unsigned int 
        colIndex) const;
        virtual void setElement(unsigned int index, double value);
        virtual void setElement(unsigned int rowIndex, unsigned int 
        colIndex, double value);
        virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
        newElements);
        virtual void setElements(const Ionflux::GeoUtils::Vector& 
        newElements, unsigned int sourceOffset = 0, unsigned int 
        targetOffset = 0);
        virtual void setElements(const Ionflux::GeoUtils::Matrix& other, 
        unsigned int sourceRowOffset = 0, unsigned int sourceColOffset = 0,
        unsigned int targetRowOffset = 0, unsigned int targetColOffset = 
        0);
        virtual void setElements(double x0, double x1 = 0., double x2 = 0.,
        double x3 = 0., double x4 = 0., double x5 = 0., double x6 = 0., 
        double x7 = 0., double x8 = 0., double x9 = 0., double x10 = 0., 
        double x11 = 0., double x12 = 0.);
        virtual void getRow(unsigned int rowIndex, 
        Ionflux::GeoUtils::Vector& target) const;
        virtual void getCol(unsigned int colIndex, 
        Ionflux::GeoUtils::Vector& target) const;
        virtual void setRow(unsigned int rowIndex, const 
        Ionflux::GeoUtils::Vector& v, unsigned int sourceOffset = 0, 
        unsigned int targetOffset = 0);
        virtual void setCol(unsigned int colIndex, const 
        Ionflux::GeoUtils::Vector& v, unsigned int sourceOffset = 0, 
        unsigned int targetOffset = 0);
        virtual void transposeIP();
        virtual double trace() const;
        virtual void transform(const Ionflux::GeoUtils::Vector& v, 
        Ionflux::GeoUtils::Vector& target) const;
        virtual void multiply(const Ionflux::GeoUtils::Matrix& other, 
        Ionflux::GeoUtils::Matrix& target) const;
        virtual void permuteRowsIP(const Ionflux::GeoUtils::Vector& p);
        virtual void permuteColsIP(const Ionflux::GeoUtils::Vector& p);
        virtual void setIdentity();
        virtual unsigned int getNumRows() const;
        virtual unsigned int getNumCols() const;
        virtual std::string getValueStringF(unsigned int fieldWidth = 5, 
        unsigned int precision = 3, const std::string& colSep = " ", const 
        std::string& rowSep = "\n", const std::string& rowPrefix = "") 
        const;
        virtual std::string getValueString() const;
        virtual unsigned int getNumElements() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Matrix* copy() const;
		static Ionflux::GeoUtils::Matrix* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Matrix* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}


%{
#include "geoutils/Matrix2.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Matrix2ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Matrix2ClassInfo();
        virtual ~Matrix2ClassInfo();
};

class Matrix2
: public Ionflux::GeoUtils::Matrix
{
    public:
		static const unsigned int NUM_ELEMENTS;
		static const unsigned int NUM_ROWS;
		static const unsigned int NUM_COLS;
		static const Ionflux::GeoUtils::Matrix2 ZERO;
		static const Ionflux::GeoUtils::Matrix2 UNIT;
        
        Matrix2();
		Matrix2(const Ionflux::GeoUtils::Matrix2& other);
        Matrix2(double initX00, double initX01, double initX10, double 
        initX11);
        Matrix2(const Ionflux::ObjectBase::DoubleVector& initElements0);
        virtual ~Matrix2();
        virtual Ionflux::GeoUtils::Matrix2 transpose() const;
        virtual Ionflux::GeoUtils::Matrix2 swapColumns() const;
        virtual Ionflux::GeoUtils::Vector2 solve(const 
        Ionflux::GeoUtils::Vector2& v) const;
        virtual Ionflux::GeoUtils::Matrix2 invert() const;
        virtual Ionflux::GeoUtils::Matrix2 operator*(const 
        Ionflux::GeoUtils::Matrix2& other) const;
        virtual Ionflux::GeoUtils::Vector2 operator*(const 
        Ionflux::GeoUtils::Vector2& v) const;
        virtual Ionflux::GeoUtils::Matrix2 operator*(double c) const;
        virtual Ionflux::GeoUtils::Matrix2 operator/(double c) const;
        virtual unsigned int getNumElements() const;
        virtual unsigned int getNumRows() const;
        virtual unsigned int getNumCols() const;
        static Ionflux::GeoUtils::Matrix2 scale(double sx = 1., double sy =
        1.);
        static Ionflux::GeoUtils::Matrix2 rotate(double phi = 0.);
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Matrix2* copy() const;
		static Ionflux::GeoUtils::Matrix2* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Matrix2* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Matrix2* create(double initX00, double initX01,
		double initX10, double initX11, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Matrix2* create(const 
		Ionflux::ObjectBase::DoubleVector& initElements0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setR0(const Ionflux::GeoUtils::Vector2& newR0);
        virtual Ionflux::GeoUtils::Vector2 getR0() const;
        virtual void setR1(const Ionflux::GeoUtils::Vector2& newR1);
        virtual Ionflux::GeoUtils::Vector2 getR1() const;
        virtual void setC0(const Ionflux::GeoUtils::Vector2& newC0);
        virtual Ionflux::GeoUtils::Vector2 getC0() const;
        virtual void setC1(const Ionflux::GeoUtils::Vector2& newC1);
        virtual Ionflux::GeoUtils::Vector2 getC1() const;
};

Ionflux::GeoUtils::Matrix2 operator*(double c, const 
Ionflux::GeoUtils::Matrix2& m);

}

}


%{
#include "geoutils/Vertex2.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Interpolator;
class Vertex2;

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
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Vertex2* copy() const;
		static Ionflux::GeoUtils::Vertex2* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Vertex2* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Vertex2* create(double initX, double initY, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Vertex2* create(const 
		Ionflux::ObjectBase::DoubleVector& initCoords, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Vertex2* create(const 
		Ionflux::GeoUtils::Vector2& initCoords, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setX(double newX);
        virtual double getX() const;
        virtual void setY(double newY);
        virtual double getY() const;
};

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
class Range;

class Vector3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vector3ClassInfo();
        virtual ~Vector3ClassInfo();
};

class Vector3
: public Ionflux::GeoUtils::Vector
{
    public:
		static const unsigned int NUM_ELEMENTS;
		static const Ionflux::GeoUtils::Vector3 ZERO;
		static const Ionflux::GeoUtils::Vector3 E_X;
		static const Ionflux::GeoUtils::Vector3 E_Y;
		static const Ionflux::GeoUtils::Vector3 E_Z;
		static const Ionflux::GeoUtils::Vector3 E_SUM;
        
        Vector3();
		Vector3(const Ionflux::GeoUtils::Vector3& other);
        Vector3(double initX0, double initX1, double initX2);
        Vector3(const Ionflux::ObjectBase::DoubleVector& initElements0);
        Vector3(const Ionflux::GeoUtils::Vector& initElements0);
        Vector3(const Ionflux::GeoUtils::Vector2& initElements0, double 
        initZ = 1.);
        Vector3(const Ionflux::Mapping::Point& initElements0);
        virtual ~Vector3();
        virtual void setElements(double newX0, double newX1, double newX2);
        virtual void setElements(const Ionflux::GeoUtils::Vector2& 
        newElements);
        virtual void setElements(const Ionflux::GeoUtils::Vector& other, 
        unsigned int sourceOffset = 0, unsigned int targetOffset = 0);
        virtual void setV2(const Ionflux::GeoUtils::Vector2& newElements, 
        double newZ = 1.);
        virtual void setElements(const Ionflux::Mapping::Point& 
        newElements);
        virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
        newElements);
        virtual Ionflux::GeoUtils::Vector3 flip() const;
        virtual Ionflux::GeoUtils::Vector3 normalize() const;
        virtual Ionflux::GeoUtils::Vector3 cross(const 
        Ionflux::GeoUtils::Vector3& other) const;
        virtual Ionflux::GeoUtils::Vector3 project(const 
        Ionflux::GeoUtils::Vector3& other) const;
        virtual Ionflux::GeoUtils::Vector3 ortho(const 
        Ionflux::GeoUtils::Vector3& other) const;
        virtual Ionflux::GeoUtils::Vector3 ortho() const;
        virtual double angleCos(const Ionflux::GeoUtils::Vector3& other) 
        const;
        virtual double angle(const Ionflux::GeoUtils::Vector3& other) 
        const;
        virtual double angle(const Ionflux::GeoUtils::Vector3& other, const
        Ionflux::GeoUtils::Vector3& axis0, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual Ionflux::GeoUtils::Vector3 slerp(const 
        Ionflux::GeoUtils::Vector3& other, double t) const;
        virtual Ionflux::GeoUtils::Vector3 permute(int px, int py, int pz) 
        const;
        virtual Ionflux::GeoUtils::Vector3 permute(const 
        Ionflux::ObjectBase::IntVector& p) const;
        virtual Ionflux::GeoUtils::Vector3 multElements(const 
        Ionflux::GeoUtils::Vector3& other) const;
        virtual Ionflux::GeoUtils::Vector3 interpolate(const 
        Ionflux::GeoUtils::Vector3& other, double t) const;
        virtual Ionflux::GeoUtils::AxisTriple getAxisOrder() const;
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
        virtual int findElement(double v, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual int findMatchingElements(const Ionflux::GeoUtils::Vector3& 
        other, Ionflux::ObjectBase::DoubleVector& target, const 
        Ionflux::GeoUtils::Range* range = 0, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Vector2 getV2() const;
        virtual Ionflux::Mapping::Point getPoint() const;
        virtual double distanceToPlane(const Ionflux::GeoUtils::Plane3& 
        plane) const;
        virtual unsigned int getNumElements() const;
        static Ionflux::GeoUtils::Vector3 axis(Ionflux::GeoUtils::AxisID 
        axisID);
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Vector3* copy() const;
		static Ionflux::GeoUtils::Vector3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Vector3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Vector3* create(double initX0, double initX1, 
		double initX2, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Vector3* create(const 
		Ionflux::ObjectBase::DoubleVector& initElements0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Vector3* create(const 
		Ionflux::GeoUtils::Vector& initElements0, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Vector3* create(const 
		Ionflux::GeoUtils::Vector2& initElements0, double initZ = 1., 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Vector3* create(const Ionflux::Mapping::Point& 
		initElements0, Ionflux::ObjectBase::IFObject* parentObject = 0);
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


%{
#include "geoutils/Range3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Line3;
class Vertex3Set;
class Mesh;

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
        Range3(const Ionflux::GeoUtils::Vector3& initMin, double 
        edgeLength);
        virtual ~Range3();
        virtual void extend(const Ionflux::GeoUtils::Range3& other);
        virtual void extend(const Ionflux::GeoUtils::Vector3& v);
        virtual void extend(double rd);
        virtual Ionflux::GeoUtils::Vector3 getCenter() const;
        virtual Ionflux::GeoUtils::Vector3 getRadius() const;
        virtual Ionflux::GeoUtils::Vector3 getExtent() const;
        virtual double getExtent(Ionflux::GeoUtils::AxisID axis) const;
        virtual Ionflux::GeoUtils::Vector3 getValue(double v0, double v1, 
        double v2) const;
        virtual Ionflux::GeoUtils::Vector3 getValue(const 
        Ionflux::GeoUtils::Vector3 v) const;
        virtual Ionflux::GeoUtils::Vector3 getRMin() const;
        virtual Ionflux::GeoUtils::Vector3 getRMax() const;
        virtual Ionflux::GeoUtils::Vector3 clamp(const 
        Ionflux::GeoUtils::Vector3 v) const;
        virtual Ionflux::GeoUtils::Vector3 getClampedValue(const 
        Ionflux::GeoUtils::Vector3 v) const;
        virtual Ionflux::GeoUtils::Range 
        getAxisRange(Ionflux::GeoUtils::AxisID axis) const;
        virtual void setBounds(const Ionflux::GeoUtils::Vector3& v);
        virtual void setBounds(const Ionflux::GeoUtils::Range3& other);
        virtual void setBounds(const Ionflux::GeoUtils::Vector3& v, const 
        Ionflux::GeoUtils::Vector3* r);
        virtual void setBounds(const Ionflux::GeoUtils::Vector3& v, double 
        edgeLength);
        virtual Ionflux::GeoUtils::RangeCompResult3 compare3(const 
        Ionflux::GeoUtils::Range3& other, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual Ionflux::GeoUtils::RangeCompResult compare(const 
        Ionflux::GeoUtils::Range3& other, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual bool isInRange(const Ionflux::GeoUtils::Vector3& v, double 
        t = Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual bool intersect(const Ionflux::GeoUtils::Line3& line, 
        Ionflux::GeoUtils::AxisID axis, 
        Ionflux::GeoUtils::AAPlanePairIntersection& result, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual bool intersect(const Ionflux::GeoUtils::Line3& line, 
        Ionflux::GeoUtils::AAPlanePairIntersection& result, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual Ionflux::GeoUtils::AxisTriple getAxisOrder() const;
        virtual Ionflux::GeoUtils::Mesh* getMesh() const;
        virtual bool operator==(const Ionflux::GeoUtils::Range3& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Range3& other) 
        const;
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Range3* copy() const;
		static Ionflux::GeoUtils::Range3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Range3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Range3* create(const 
		Ionflux::GeoUtils::Vector3& initCenter, const Ionflux::GeoUtils::Vector3*
		initRadius = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Range3* create(const Ionflux::GeoUtils::Range& 
		initX, const Ionflux::GeoUtils::Range& initY, const 
		Ionflux::GeoUtils::Range& initZ, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Range3* create(const 
		Ionflux::GeoUtils::Vector2& rx, const Ionflux::GeoUtils::Vector2& ry, 
		const Ionflux::GeoUtils::Vector2& rz, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Range3* create(double xMin, double xMax, double
		yMin, double yMax, double zMin, double zMax, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Range3* create(const 
		Ionflux::GeoUtils::Vector3& initMin, double edgeLength, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setX(const Ionflux::GeoUtils::Range& newX);
        virtual Ionflux::GeoUtils::Range getX() const;
        virtual void setY(const Ionflux::GeoUtils::Range& newY);
        virtual Ionflux::GeoUtils::Range getY() const;
        virtual void setZ(const Ionflux::GeoUtils::Range& newZ);
        virtual Ionflux::GeoUtils::Range getZ() const;
};

}

}


%{
#include "geoutils/Vector4.hpp"
%}

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
: public Ionflux::GeoUtils::Vector
{
    public:
		static const unsigned int NUM_ELEMENTS;
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
        Vector4(const Ionflux::ObjectBase::DoubleVector& initElements0);
        Vector4(const Ionflux::GeoUtils::Vector& initElements0);
        Vector4(const Ionflux::GeoUtils::Vector2& initElements0, double 
        initZ = 0., double initW = 1.);
        Vector4(const Ionflux::GeoUtils::Vector3& initElements0, double 
        initW = 1.);
        virtual ~Vector4();
        virtual void setElements(const Ionflux::GeoUtils::Vector2& 
        newElements);
        virtual void setElements(const Ionflux::GeoUtils::Vector3& 
        newElements);
        virtual void setV2(const Ionflux::GeoUtils::Vector2& newElements, 
        double newZ = 0., double newW = 1.);
        virtual void setElements(const Ionflux::GeoUtils::Vector& other, 
        unsigned int sourceOffset = 0, unsigned int targetOffset = 0);
        virtual void setElements(double x0, double x1 = 0., double x2 = 0.,
        double x3 = 0.);
        virtual void setV3(const Ionflux::GeoUtils::Vector3& newElements, 
        double newW = 1.);
        virtual Ionflux::GeoUtils::Vector4 flip() const;
        virtual Ionflux::GeoUtils::Vector4 normalize() const;
        virtual Ionflux::GeoUtils::Vector4 project(const 
        Ionflux::GeoUtils::Vector4& other) const;
        virtual Ionflux::GeoUtils::Vector4 ortho(const 
        Ionflux::GeoUtils::Vector4& other) const;
        virtual double angle(const Ionflux::GeoUtils::Vector4& other) 
        const;
        virtual Ionflux::GeoUtils::Vector4 slerp(const 
        Ionflux::GeoUtils::Vector4& other, double t) const;
        virtual Ionflux::GeoUtils::Vector4 permute(int px, int py, int pz, 
        int pw) const;
        virtual Ionflux::GeoUtils::Vector4 permute(const 
        Ionflux::ObjectBase::IntVector& p) const;
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
        virtual unsigned int getNumElements() const;
        static Ionflux::GeoUtils::Vector4 axis(Ionflux::GeoUtils::AxisID 
        axisID);
        static Ionflux::GeoUtils::Vector4 axisH(Ionflux::GeoUtils::AxisID 
        axisID);
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Vector4* copy() const;
		static Ionflux::GeoUtils::Vector4* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Vector4* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Vector4* create(double initX0, double initX1, 
		double initX2, double initX3, Ionflux::ObjectBase::IFObject* parentObject
		= 0);
		static Ionflux::GeoUtils::Vector4* create(const 
		Ionflux::ObjectBase::DoubleVector& initElements0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Vector4* create(const 
		Ionflux::GeoUtils::Vector& initElements0, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Vector4* create(const 
		Ionflux::GeoUtils::Vector2& initElements0, double initZ = 0., double 
		initW = 1., Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Vector4* create(const 
		Ionflux::GeoUtils::Vector3& initElements0, double initW = 1., 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setX0(double newX0);
        virtual double getX0() const;
        virtual void setX1(double newX1);
        virtual double getX1() const;
        virtual void setX2(double newX2);
        virtual double getX2() const;
        virtual void setX3(double newX3);
        virtual double getX3() const;
};

Ionflux::GeoUtils::Vector4 operator*(double c, const 
Ionflux::GeoUtils::Vector4& v);

}

}


%{
#include "geoutils/VectorN.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VectorNClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VectorNClassInfo();
        virtual ~VectorNClassInfo();
};

class VectorN
: public Ionflux::GeoUtils::Vector
{
    public:
        
        VectorN();
		VectorN(const Ionflux::GeoUtils::VectorN& other);
        VectorN(unsigned int initNumElements);
        VectorN(unsigned int initNumElements, double x0, double x1 = 0., 
        double x2 = 0., double x3 = 0., double x4 = 0., double x5 = 0., 
        double x6 = 0., double x7 = 0., double x8 = 0., double x9 = 0., 
        double x10 = 0., double x11 = 0., double x12 = 0.);
        virtual ~VectorN();
        virtual Ionflux::GeoUtils::VectorN interpolate(const 
        Ionflux::GeoUtils::VectorN& other, double t = 0.5, 
        Ionflux::GeoUtils::Interpolator* interp = 0);
        virtual Ionflux::GeoUtils::VectorN operator+(const 
        Ionflux::GeoUtils::VectorN& other) const;
        virtual Ionflux::GeoUtils::VectorN operator-(const 
        Ionflux::GeoUtils::VectorN& other) const;
        virtual Ionflux::GeoUtils::VectorN operator*(double c) const;
        virtual double operator*(const Ionflux::GeoUtils::VectorN& other) 
        const;
        virtual Ionflux::GeoUtils::VectorN operator/(double c) const;
        static Ionflux::GeoUtils::VectorN* sample(const 
        Ionflux::Mapping::Mapping& mapping, unsigned int numPoints, double 
        t0 = 0., double t1 = 1.);
        static Ionflux::GeoUtils::VectorN* linear(unsigned int numPoints, 
        double t0 = 0., double t1 = 1., Ionflux::Mapping::MappingValue 
        lower = 0., Ionflux::Mapping::MappingValue upper = 1., 
        Ionflux::Mapping::MappingValue scale = 1., 
        Ionflux::Mapping::MappingValue offset = 0.);
        static Ionflux::GeoUtils::VectorN* cubic(unsigned int numPoints, 
        double t0 = 0., double t1 = 1., Ionflux::Mapping::MappingValue 
        lower = 0., Ionflux::Mapping::MappingValue upper = 1.);
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::VectorN* copy() const;
		static Ionflux::GeoUtils::VectorN* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::VectorN* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::VectorN* create(unsigned int initNumElements, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::VectorN* create(unsigned int initNumElements, 
		double x0, double x1 = 0., double x2 = 0., double x3 = 0., double x4 = 
		0., double x5 = 0., double x6 = 0., double x7 = 0., double x8 = 0., 
		double x9 = 0., double x10 = 0., double x11 = 0., double x12 = 0., 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setNumElements(unsigned int newNumElements);
        virtual unsigned int getNumElements() const;
};

Ionflux::GeoUtils::VectorN operator*(double c, const 
Ionflux::GeoUtils::VectorN& v);

}

}


%{
#include "geoutils/Matrix3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Matrix3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Matrix3ClassInfo();
        virtual ~Matrix3ClassInfo();
};

class Matrix3
: public Ionflux::GeoUtils::Matrix
{
    public:
		static const unsigned int NUM_ELEMENTS;
		static const unsigned int NUM_ROWS;
		static const unsigned int NUM_COLS;
		static const Ionflux::GeoUtils::Matrix3 ZERO;
		static const Ionflux::GeoUtils::Matrix3 UNIT;
        
        Matrix3();
		Matrix3(const Ionflux::GeoUtils::Matrix3& other);
        Matrix3(double initX00, double initX01, double initX02, double 
        initX10, double initX11, double initX12, double initX20, double 
        initX21, double initX22);
        Matrix3(const Ionflux::ObjectBase::DoubleVector& initElements0);
        Matrix3(const Ionflux::GeoUtils::Matrix& initElements0);
        virtual ~Matrix3();
        virtual Ionflux::GeoUtils::Matrix3 transpose() const;
        virtual Ionflux::GeoUtils::Matrix3 permuteColumns(int px, int py, 
        int pz) const;
        virtual Ionflux::GeoUtils::Matrix3 permuteColumns(const 
        Ionflux::ObjectBase::IntVector& p) const;
        virtual Ionflux::GeoUtils::Vector3 solve(const 
        Ionflux::GeoUtils::Vector3& v) const;
        virtual Ionflux::GeoUtils::Matrix3 invert() const;
        virtual Ionflux::GeoUtils::Matrix3& multiplyLeft(const 
        Ionflux::GeoUtils::Matrix3& other);
        virtual Ionflux::GeoUtils::Matrix3& multiplyRight(const 
        Ionflux::GeoUtils::Matrix3& other);
        virtual Ionflux::GeoUtils::Matrix3 operator*(const 
        Ionflux::GeoUtils::Matrix3& other) const;
        virtual Ionflux::GeoUtils::Vector3 operator*(const 
        Ionflux::GeoUtils::Vector3& v) const;
        virtual Ionflux::GeoUtils::Matrix3 operator*(double c) const;
        virtual Ionflux::GeoUtils::Matrix3 operator/(double c) const;
        virtual Ionflux::GeoUtils::Matrix3 operator+(const 
        Ionflux::GeoUtils::Matrix3& other) const;
        virtual Ionflux::GeoUtils::Matrix3 operator-(const 
        Ionflux::GeoUtils::Matrix3& other) const;
        virtual void svd(Ionflux::GeoUtils::Matrix3& u, 
        Ionflux::GeoUtils::Vector3& s, Ionflux::GeoUtils::Matrix3& v) 
        const;
        virtual Ionflux::GeoUtils::Vector4 getAxisAngle(double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual unsigned int getNumElements() const;
        virtual unsigned int getNumRows() const;
        virtual unsigned int getNumCols() const;
        static Ionflux::GeoUtils::Matrix3 scale(double sx = 1., double sy =
        1., double sz = 1.);
        static Ionflux::GeoUtils::Matrix3 translate(double tx = 0., double 
        ty = 0.);
        static Ionflux::GeoUtils::Matrix3 rotate(double phi = 0., 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        static Ionflux::GeoUtils::Matrix3 crossProduct(const 
        Ionflux::GeoUtils::Vector3& v);
        static Ionflux::GeoUtils::Matrix3 rotate(double phi, const 
        Ionflux::GeoUtils::Vector3& axis);
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Matrix3* copy() const;
		static Ionflux::GeoUtils::Matrix3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Matrix3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Matrix3* create(double initX00, double initX01,
		double initX02, double initX10, double initX11, double initX12, double 
		initX20, double initX21, double initX22, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Matrix3* create(const 
		Ionflux::ObjectBase::DoubleVector& initElements0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Matrix3* create(const 
		Ionflux::GeoUtils::Matrix& initElements0, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
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

Ionflux::GeoUtils::Matrix3 operator*(double c, const 
Ionflux::GeoUtils::Matrix3& m);

}

}


%{
#include "geoutils/Matrix4.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Matrix4ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Matrix4ClassInfo();
        virtual ~Matrix4ClassInfo();
};

class Matrix4
: public Ionflux::GeoUtils::Matrix
{
    public:
		static const unsigned int NUM_ELEMENTS;
		static const unsigned int NUM_ROWS;
		static const unsigned int NUM_COLS;
		static const Ionflux::GeoUtils::Matrix4 ZERO;
		static const Ionflux::GeoUtils::Matrix4 UNIT;
        
        Matrix4();
		Matrix4(const Ionflux::GeoUtils::Matrix4& other);
        Matrix4(double initX00, double initX01, double initX02, double 
        initX03, double initX10, double initX11, double initX12, double 
        initX13, double initX20, double initX21, double initX22, double 
        initX23, double initX30, double initX31, double initX32, double 
        initX33);
        Matrix4(const Ionflux::ObjectBase::DoubleVector& initElements0);
        Matrix4(const Ionflux::GeoUtils::Matrix& initElements0);
        Matrix4(const Ionflux::GeoUtils::Matrix3& initElements0);
        virtual ~Matrix4();
        virtual void setElements(const Ionflux::GeoUtils::Matrix& other, 
        unsigned int sourceRowOffset = 0, unsigned int sourceColOffset = 0,
        unsigned int targetRowOffset = 0, unsigned int targetColOffset = 
        0);
        virtual void setM3x3(const Ionflux::GeoUtils::Matrix3& newElements,
        double newX33 = 1., double newX03 = 0., double newX13 = 0., double 
        newX23 = 0., double newX30 = 0., double newX31 = 0., double newX32 
        = 0.);
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
        virtual Ionflux::GeoUtils::Matrix4 operator*(const 
        Ionflux::GeoUtils::Matrix4& other) const;
        virtual Ionflux::GeoUtils::Vector4 operator*(const 
        Ionflux::GeoUtils::Vector4& v) const;
        virtual Ionflux::GeoUtils::Matrix4 operator*(double c) const;
        virtual Ionflux::GeoUtils::Matrix4 operator/(double c) const;
        virtual Ionflux::GeoUtils::Matrix3 getM3x3() const;
        virtual unsigned int getNumElements() const;
        virtual unsigned int getNumRows() const;
        virtual unsigned int getNumCols() const;
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
        Ionflux::GeoUtils::AxisID depthAxis = Ionflux::GeoUtils::AXIS_Z, 
        double near = 0., double far = 0.);
        static Ionflux::GeoUtils::Matrix4 openGLProjection(double near, 
        double far, double top, double bottom, double right, double left);
        static Ionflux::GeoUtils::Matrix4 imageTransform(double screenWidth
        = 1.33, double screenHeight = 1., double imageWidth = 800., double 
        imageHeight = 600., Ionflux::GeoUtils::AxisID upAxis = 
        Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID depthAxis = 
        Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID horizonAxis = 
        Ionflux::GeoUtils::AXIS_X);
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Matrix4* copy() const;
		static Ionflux::GeoUtils::Matrix4* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Matrix4* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Matrix4* create(double initX00, double initX01,
		double initX02, double initX03, double initX10, double initX11, double 
		initX12, double initX13, double initX20, double initX21, double initX22, 
		double initX23, double initX30, double initX31, double initX32, double 
		initX33, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Matrix4* create(const 
		Ionflux::ObjectBase::DoubleVector& initElements0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Matrix4* create(const 
		Ionflux::GeoUtils::Matrix& initElements0, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Matrix4* create(const 
		Ionflux::GeoUtils::Matrix3& initElements0, Ionflux::ObjectBase::IFObject*
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

Ionflux::GeoUtils::Matrix4 operator*(double c, const 
Ionflux::GeoUtils::Matrix4& m);

}

}


%{
#include "geoutils/MatrixMN.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VectorN;

class MatrixMNClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MatrixMNClassInfo();
        virtual ~MatrixMNClassInfo();
};

class MatrixMN
: public Ionflux::GeoUtils::Matrix
{
    public:
        
        MatrixMN();
		MatrixMN(const Ionflux::GeoUtils::MatrixMN& other);
        MatrixMN(unsigned int initNumRows, unsigned int initNumCols);
        MatrixMN(unsigned int initNumCols, unsigned int initNumRows, double
        x0, double x1 = 0., double x2 = 0., double x3 = 0., double x4 = 0.,
        double x5 = 0., double x6 = 0., double x7 = 0., double x8 = 0., 
        double x9 = 0., double x10 = 0., double x11 = 0., double x12 = 0.);
        virtual ~MatrixMN();
        virtual Ionflux::GeoUtils::MatrixMN transpose() const;
        virtual void qrDecomp(Ionflux::GeoUtils::MatrixMN& q, 
        Ionflux::GeoUtils::MatrixMN& r) const;
        virtual Ionflux::GeoUtils::VectorN solve(const 
        Ionflux::GeoUtils::VectorN& b) const;
        virtual Ionflux::GeoUtils::MatrixMN invert() const;
        virtual unsigned int getNumElements() const;
        static void qrSolve(const Ionflux::GeoUtils::MatrixMN& q, const 
        Ionflux::GeoUtils::MatrixMN& r, const Ionflux::GeoUtils::VectorN& 
        b, Ionflux::GeoUtils::VectorN& x);
        virtual Ionflux::GeoUtils::MatrixMN operator*(const 
        Ionflux::GeoUtils::Matrix& other) const;
        virtual Ionflux::GeoUtils::VectorN operator*(const 
        Ionflux::GeoUtils::VectorN& v) const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::MatrixMN* copy() const;
		static Ionflux::GeoUtils::MatrixMN* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::GeoUtils::MatrixMN* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::MatrixMN* create(unsigned int initNumRows, 
		unsigned int initNumCols, Ionflux::ObjectBase::IFObject* parentObject = 
		0);
		static Ionflux::GeoUtils::MatrixMN* create(unsigned int initNumCols, 
		unsigned int initNumRows, double x0, double x1 = 0., double x2 = 0., 
		double x3 = 0., double x4 = 0., double x5 = 0., double x6 = 0., double x7
		= 0., double x8 = 0., double x9 = 0., double x10 = 0., double x11 = 0., 
		double x12 = 0., Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setNumRows(unsigned int newNumRows);
        virtual unsigned int getNumRows() const;
        virtual void setNumCols(unsigned int newNumCols);
        virtual unsigned int getNumCols() const;
};

}

}


namespace Ionflux
{

namespace GeoUtils
{

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

%extend VectorN {
    double __getitem__(int index)
    {
        return $self->getElement(index);
    }
    void __setitem__(int index, double value)
    {
        return $self->setElement(index, value);
    }
}

}

}


%{
#include "geoutils/DeferredTransform.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Matrix4;
class Vector;
class VectorSet;

class DeferredTransformClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        DeferredTransformClassInfo();
        virtual ~DeferredTransformClassInfo();
};

class DeferredTransform
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const double COMPARE_TOLERANCE;
        
        DeferredTransform();
		DeferredTransform(const Ionflux::GeoUtils::DeferredTransform& other);
        virtual ~DeferredTransform();
        virtual void resetTransform();
        virtual void resetVI();
        virtual void reset();
        virtual void clear();
        virtual Ionflux::GeoUtils::DeferredTransform& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::DeferredTransform& transformVI(const 
        Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4*
        image = 0);
        virtual bool checkTransform(double t = COMPARE_TOLERANCE);
        virtual bool checkVI(double t = COMPARE_TOLERANCE);
        virtual bool eq(const Ionflux::GeoUtils::DeferredTransform& other, 
        double t = COMPARE_TOLERANCE) const;
        virtual bool operator==(const Ionflux::GeoUtils::DeferredTransform&
        other) const;
        virtual bool operator!=(const Ionflux::GeoUtils::DeferredTransform&
        other) const;
        virtual bool useTransform() const;
        virtual bool useVI() const;
        virtual bool transformChanged() const;
        virtual bool viChanged() const;
        virtual bool isIdentity() const;
        virtual void applyTransform(const Ionflux::GeoUtils::Vector& v, 
        Ionflux::GeoUtils::Vector& target, bool clearTransform = true);
        virtual void applyVI(const Ionflux::GeoUtils::Vector& v, 
        Ionflux::GeoUtils::Vector& target, bool clearTransform = true);
        virtual void applyTransform(const Ionflux::GeoUtils::VectorSet& 
        vectors, Ionflux::GeoUtils::VectorSet& target, bool clearTransform 
        = true);
        virtual void applyVI(const Ionflux::GeoUtils::VectorSet& vectors, 
        Ionflux::GeoUtils::VectorSet& target, bool clearTransform = true);
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::DeferredTransform* copy() const;
		static Ionflux::GeoUtils::DeferredTransform* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::DeferredTransform* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setTransformMatrix(Ionflux::GeoUtils::Matrix4* 
        newTransformMatrix);
        virtual Ionflux::GeoUtils::Matrix4* getTransformMatrix() const;
        virtual void setViewMatrix(Ionflux::GeoUtils::Matrix4* 
        newViewMatrix);
        virtual Ionflux::GeoUtils::Matrix4* getViewMatrix() const;
        virtual void setImageMatrix(Ionflux::GeoUtils::Matrix4* 
        newImageMatrix);
        virtual Ionflux::GeoUtils::Matrix4* getImageMatrix() const;
        virtual void setLastTransformMatrix(Ionflux::GeoUtils::Matrix4* 
        newLastTransformMatrix);
        virtual Ionflux::GeoUtils::Matrix4* getLastTransformMatrix() const;
        virtual void setLastViewMatrix(Ionflux::GeoUtils::Matrix4* 
        newLastViewMatrix);
        virtual Ionflux::GeoUtils::Matrix4* getLastViewMatrix() const;
        virtual void setLastImageMatrix(Ionflux::GeoUtils::Matrix4* 
        newLastImageMatrix);
        virtual Ionflux::GeoUtils::Matrix4* getLastImageMatrix() const;
};

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
        virtual void clearTransformations();
        virtual void clear();
        virtual void copyTransform(const 
        Ionflux::GeoUtils::TransformableObject& other);
        virtual void onTransformChanged();
        virtual void onVIChanged();
        virtual bool checkTransform(double t = 
        Ionflux::GeoUtils::DeferredTransform::COMPARE_TOLERANCE);
        virtual bool checkVI(double t = 
        Ionflux::GeoUtils::DeferredTransform::COMPARE_TOLERANCE);
        virtual Ionflux::GeoUtils::TransformableObject& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::TransformableObject& scale(double sx, 
        double sy = 1., double sz = 1.);
        virtual Ionflux::GeoUtils::TransformableObject& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::TransformableObject& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::TransformableObject& 
        swapAxes(Ionflux::GeoUtils::AxisID x = Ionflux::GeoUtils::AXIS_X, 
        Ionflux::GeoUtils::AxisID y = Ionflux::GeoUtils::AXIS_Y, 
        Ionflux::GeoUtils::AxisID z = Ionflux::GeoUtils::AXIS_Z, 
        Ionflux::GeoUtils::AxisID w = Ionflux::GeoUtils::AXIS_W);
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
        virtual bool useTransform() const;
        virtual bool useVI() const;
        virtual bool transformChanged() const;
        virtual bool viChanged() const;
        virtual Ionflux::GeoUtils::TransformableObject& duplicate();
        virtual Ionflux::GeoUtils::Matrix4* getTransformMatrix() const;
        virtual Ionflux::GeoUtils::Matrix4* getViewMatrix() const;
        virtual Ionflux::GeoUtils::Matrix4* getImageMatrix() const;
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::TransformableObject* copy() const;
		static Ionflux::GeoUtils::TransformableObject* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformableObject* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void 
        setDeferredTransform(Ionflux::GeoUtils::DeferredTransform* 
        newDeferredTransform);
        virtual Ionflux::GeoUtils::DeferredTransform* 
        getDeferredTransform() const;
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
        virtual void clear();
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
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::TransformableGroup* copy() const;
		static Ionflux::GeoUtils::TransformableGroup* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformableGroup* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;        
        virtual unsigned int getNumItems() const;
        virtual Ionflux::GeoUtils::TransformableObject* getItem(unsigned 
        int elementIndex = 0) const;
		virtual int findItem(Ionflux::GeoUtils::TransformableObject* needle, 
		unsigned int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::TransformableObject*>& 
        getItems();
        virtual void addItem(Ionflux::GeoUtils::TransformableObject* 
        addElement);
		virtual Ionflux::GeoUtils::TransformableObject* addItem();
		virtual void 
		addItems(std::vector<Ionflux::GeoUtils::TransformableObject*>& newItems);
		virtual void addItems(Ionflux::GeoUtils::TransformableGroup* newItems);        
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
        virtual void setVertices(int i0, int i1);
        virtual void getVertices(Ionflux::ObjectBase::IntVector& target) 
        const;
        virtual int getVertex(int index) const;
        virtual Ionflux::ObjectBase::IntVector getVector() const;
        virtual void setVertex(int index, int value);
        virtual void sort();
        virtual bool operator==(const Ionflux::GeoUtils::Edge& other) 
        const;
        virtual bool operator<(const Ionflux::GeoUtils::Edge& other) const;
        virtual bool operator!=(const Ionflux::GeoUtils::Edge& other) 
        const;
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Edge* copy() const;
		static Ionflux::GeoUtils::Edge* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Edge* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Edge* create(int initV0, int initV1, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Edge* create(const 
		Ionflux::ObjectBase::IntVector& initVertices, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
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
		static Ionflux::GeoUtils::LinearInterpolator* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::LinearInterpolator* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::LinearInterpolator* create(double initV0, 
		double initV1, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::LinearInterpolator* create(const 
		Ionflux::ObjectBase::DoubleVector& initValues, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
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
        virtual void addPoints(Ionflux::Mapping::PointSet& points);
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
        virtual std::string getValueString() const;
        virtual std::string getXMLData_legacy() const;
        virtual std::string getXML_legacy() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Vertex3Set* copy() const;
		static Ionflux::GeoUtils::Vertex3Set* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Vertex3Set* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Vertex3Set* 
		create(Ionflux::GeoUtils::Vertex3Vector& initVertices, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual bool serialize(std::string& target) const;
        virtual Ionflux::ObjectBase::DataSize deserialize(const std::string& source, int offset = 0);
        virtual bool serialize(Ionflux::ObjectBase::IFIOContext& ioCtx, bool addMagicWord = true) const;
        virtual Ionflux::ObjectBase::DataSize deserialize(Ionflux::ObjectBase::IFIOContext& ioCtx, Ionflux::ObjectBase::DataSize offset = Ionflux::ObjectBase::DATA_SIZE_INVALID, bool checkMagicWord = true);
        virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllable() const;
        virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllableBase() const;        
        virtual unsigned int getNumVertices() const;
        virtual Ionflux::GeoUtils::Vertex3* getVertex(unsigned int 
        elementIndex = 0) const;
		virtual int findVertex(Ionflux::GeoUtils::Vertex3* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Vertex3*>& getVertices();
        virtual void addVertex(Ionflux::GeoUtils::Vertex3* addElement);
		virtual Ionflux::GeoUtils::Vertex3* addVertex();
		virtual void addVertices(std::vector<Ionflux::GeoUtils::Vertex3*>& 
		newVertices);
		virtual void addVertices(Ionflux::GeoUtils::Vertex3Set* newVertices);        
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
        Vertex3(const Ionflux::GeoUtils::Vector4& initCoords);
        Vertex3(const Ionflux::Mapping::Point& initCoords);
        virtual ~Vertex3();
        virtual void setCoords(double newX, double newY, double newZ);
        virtual void setCoords(const Ionflux::ObjectBase::DoubleVector& 
        newCoords);
        virtual void setCoords(const Ionflux::GeoUtils::Vector3& 
        newCoords);
        virtual void setCoords(const Ionflux::GeoUtils::Vector4& 
        newCoords);
        virtual void getCoords(Ionflux::ObjectBase::DoubleVector& target) 
        const;
        virtual void setCoords(const Ionflux::Mapping::Point& newCoords);
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
        virtual Ionflux::Mapping::Point getPoint() const;
        virtual std::string getValueString() const;
        virtual std::string getXMLData_legacy() const;
        virtual std::string getXML_legacy() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Vertex3* copy() const;
		static Ionflux::GeoUtils::Vertex3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Vertex3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Vertex3* create(double initX, double initY, 
		double initZ, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Vertex3* create(const 
		Ionflux::ObjectBase::DoubleVector& initCoords, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Vertex3* create(const 
		Ionflux::GeoUtils::Vector3& initCoords, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Vertex3* create(const 
		Ionflux::GeoUtils::Vector4& initCoords, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::GeoUtils::Vertex3* create(const Ionflux::Mapping::Point& 
		initCoords, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual bool serialize(std::string& target) const;
        virtual Ionflux::ObjectBase::DataSize deserialize(const std::string& source, int offset = 0);
        virtual bool serialize(Ionflux::ObjectBase::IFIOContext& ioCtx, bool addMagicWord = true) const;
        virtual Ionflux::ObjectBase::DataSize deserialize(Ionflux::ObjectBase::IFIOContext& ioCtx, Ionflux::ObjectBase::DataSize offset = Ionflux::ObjectBase::DATA_SIZE_INVALID, bool checkMagicWord = true);
        virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllable() const;
        virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllableBase() const;
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
        virtual std::string getValueString() const;
        static const Ionflux::GeoUtils::Plane3& planeXY();
        static const Ionflux::GeoUtils::Plane3& planeYZ();
        static const Ionflux::GeoUtils::Plane3& planeZX();
        static Ionflux::GeoUtils::Plane3 createFromNormal(const 
        Ionflux::GeoUtils::Vector3& n, const Ionflux::GeoUtils::Vector3& t 
        = Ionflux::GeoUtils::Vector3::E_X, const 
        Ionflux::GeoUtils::Vector3& p = Ionflux::GeoUtils::Vector3::ZERO);
		virtual Ionflux::GeoUtils::Plane3* copy() const;
		static Ionflux::GeoUtils::Plane3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Plane3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
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
		static const Ionflux::GeoUtils::Range UV_RANGE;
        
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
        virtual void clearData();
        virtual void copyVertices();
        virtual Ionflux::GeoUtils::Edge* addEdge(int i0, int i1);
        virtual int createEdges(bool closePolygon = true);
        virtual Ionflux::GeoUtils::Plane3 getPlane(int v0 = 0, int v1 = 1, 
        int v2 = -1) const;
        virtual double getLength() const;
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
        virtual Ionflux::GeoUtils::Polygon3& scale(double sx, double sy = 
        1., double sz = 1.);
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
        virtual bool isTri();
        virtual bool isQuad();
        virtual void calculateUVCoefficients(const 
        Ionflux::GeoUtils::Vertex3& p, Ionflux::GeoUtils::Matrix4& target, 
        Ionflux::ObjectBase::IntVector* indices = 0, double s = 1.);
        virtual Ionflux::GeoUtils::Vector2 getUV(const 
        Ionflux::GeoUtils::Vertex3& p, Ionflux::ObjectBase::IntVector* 
        indices = 0, Ionflux::GeoUtils::QuadInterpolationTypeID 
        interpolationType = QUAD_INTERPOLATION_BILINEAR, double s = 1., 
        double t = DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Vertex3 getUVVertex(const 
        Ionflux::GeoUtils::Vector2& uv, Ionflux::ObjectBase::IntVector* 
        indices = 0, Ionflux::GeoUtils::QuadInterpolationTypeID 
        interpolationType = QUAD_INTERPOLATION_BILINEAR);
        virtual void initFromSpline(const Ionflux::Mapping::BezierSpline& 
        spline);
        virtual void sample(Ionflux::Mapping::PointMapping& mapping, 
        unsigned int numSamples = 20, double tMin = 0., double tMax = 1.);
        virtual void initFromSegment(Ionflux::Mapping::Segment& segment);
        virtual void createSpline(Ionflux::Mapping::BezierSpline& target);
        virtual void createSplineInterp(Ionflux::Mapping::BezierSpline& 
        target, double smoothness = 0.2);
        static Ionflux::GeoUtils::Polygon3* circle(unsigned int resolution 
        = 20);
        static Ionflux::GeoUtils::Polygon3* square();
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Polygon3* copy() const;
		static Ionflux::GeoUtils::Polygon3* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::GeoUtils::Polygon3* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Polygon3* 
		create(Ionflux::GeoUtils::Vertex3Vector* initVertices, 
		Ionflux::GeoUtils::EdgeVector* initEdges = 0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Polygon3* create(Ionflux::GeoUtils::Vertex3Set*
		initVertexSource, Ionflux::GeoUtils::EdgeVector* initEdges = 0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Polygon3* create(const 
		Ionflux::GeoUtils::Vertex3* v0, const Ionflux::GeoUtils::Vertex3* v1, 
		const Ionflux::GeoUtils::Vertex3* v2, const Ionflux::GeoUtils::Vertex3* 
		v3 = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
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
		virtual Ionflux::GeoUtils::Vertex3* addVertex();
		virtual void addVertices(std::vector<Ionflux::GeoUtils::Vertex3*>& 
		newVertices);
		virtual void addVertices(Ionflux::GeoUtils::Polygon3* newVertices);        
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
		virtual Ionflux::GeoUtils::Edge* addEdge();
		virtual void addEdges(std::vector<Ionflux::GeoUtils::Edge*>& newEdges);
		virtual void addEdges(Ionflux::GeoUtils::Polygon3* newEdges);        
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
		virtual unsigned int getMemSize() const;
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
		virtual unsigned int getMemSize() const;
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
		virtual unsigned int getMemSize() const;
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
		virtual unsigned int getMemSize() const;
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
		virtual unsigned int getMemSize() const;
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
		virtual unsigned int getMemSize() const;
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
		virtual unsigned int getMemSize() const;
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
		virtual unsigned int getMemSize() const;
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
		virtual unsigned int getMemSize() const;
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
        Polygon3Set(Ionflux::GeoUtils::Polygon3Vector& initPolygons);
        virtual ~Polygon3Set();
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual void applyTransform(bool recursive = false);
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
        virtual void writeSVG(Ionflux::GeoUtils::SVGImageProperties& 
        imageProperties, const std::string& elementIDPrefix = "polygon", 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y);
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
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Polygon3Set* copy() const;
		static Ionflux::GeoUtils::Polygon3Set* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Polygon3Set* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Polygon3Set* 
		create(Ionflux::GeoUtils::Polygon3Vector& initPolygons, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumPolygons() const;
        virtual Ionflux::GeoUtils::Polygon3* getPolygon(unsigned int 
        elementIndex = 0) const;
		virtual int findPolygon(Ionflux::GeoUtils::Polygon3* needle, unsigned int
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Polygon3*>& getPolygons();
        virtual void addPolygon(Ionflux::GeoUtils::Polygon3* addElement);
		virtual Ionflux::GeoUtils::Polygon3* addPolygon();
		virtual void addPolygons(std::vector<Ionflux::GeoUtils::Polygon3*>& 
		newPolygons);
		virtual void addPolygons(Ionflux::GeoUtils::Polygon3Set* newPolygons);        
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
: public Ionflux::Mapping::PointMapping
{
    public:
        
        Line3();
		Line3(const Ionflux::GeoUtils::Line3& other);
        Line3(const Ionflux::GeoUtils::Vector3& initP, const 
        Ionflux::GeoUtils::Vector3& initU);
        virtual ~Line3();
        virtual bool intersect(const Ionflux::GeoUtils::Line3& other, 
        Ionflux::GeoUtils::Vector3& result) const;
        virtual bool intersect(const Ionflux::GeoUtils::Plane3& plane, 
        Ionflux::GeoUtils::Vector3& result) const;
        virtual bool intersectionInPoly(const Ionflux::GeoUtils::Polygon3& 
        poly, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual bool operator==(const Ionflux::GeoUtils::Line3& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::Line3& other) 
        const;
        virtual Ionflux::GeoUtils::Vector3 eval(double value);
        virtual Ionflux::Mapping::Point call(Ionflux::Mapping::MappingValue
        value);
        virtual std::string getValueString() const;
        static const Ionflux::GeoUtils::Line3& axisX();
        static const Ionflux::GeoUtils::Line3& axisY();
        static const Ionflux::GeoUtils::Line3& axisZ();
		virtual Ionflux::GeoUtils::Line3* copy() const;
		static Ionflux::GeoUtils::Line3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Line3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Line3* create(const Ionflux::GeoUtils::Vector3&
		initP, const Ionflux::GeoUtils::Vector3& initU, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setP(const Ionflux::GeoUtils::Vector3& newP);
        virtual Ionflux::GeoUtils::Vector3 getP() const;
        virtual void setU(const Ionflux::GeoUtils::Vector3& newU);
        virtual Ionflux::GeoUtils::Vector3 getU() const;
};

}

}


%{
#include "geoutils/Shape3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Shape3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Shape3ClassInfo();
        virtual ~Shape3ClassInfo();
};

class Shape3
: virtual public Ionflux::GeoUtils::TransformableObject
{
    public:
        
        Shape3();
		Shape3(const Ionflux::GeoUtils::Shape3& other);
        virtual ~Shape3();
        virtual Ionflux::GeoUtils::Shape3& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Shape3& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Shape3& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Shape3& normalize();
        virtual Ionflux::GeoUtils::Shape3& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Shape3& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Shape3& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Shape3& transformVI(const 
        Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4*
        image = 0);
        virtual bool checkVertex(const Ionflux::GeoUtils::Vertex3& v, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
        virtual Ionflux::GeoUtils::Shape3& duplicate();
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Shape3* copy() const;
		static Ionflux::GeoUtils::Shape3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Shape3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
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

class Mesh;

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
        Object3(Ionflux::GeoUtils::Mesh* initMesh);
        virtual ~Object3();
        virtual void update();
        virtual void clear();
        virtual void applyTransform(bool recursive = false);
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
        virtual std::string getValueString() const;
        virtual Ionflux::GeoUtils::Object3& duplicate();
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Object3* copy() const;
		static Ionflux::GeoUtils::Object3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Object3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Object3* create(Ionflux::GeoUtils::Mesh* 
		initMesh, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setMesh(Ionflux::GeoUtils::Mesh* newMesh);
        virtual Ionflux::GeoUtils::Mesh* getMesh() const;
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
: public Ionflux::GeoUtils::Shape3
{
    public:
        
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
        virtual std::string getValueString() const;
        virtual Ionflux::GeoUtils::Sphere3& duplicate();
        static const Ionflux::GeoUtils::Sphere3& unit();
		virtual Ionflux::GeoUtils::Sphere3* copy() const;
		static Ionflux::GeoUtils::Sphere3* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Sphere3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
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
        virtual std::string getXML_legacy() const;
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::BoxBoundsItem* copy() const;
		static Ionflux::GeoUtils::BoxBoundsItem* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::BoxBoundsItem* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
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
		virtual unsigned int getMemSize() const;
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
		virtual unsigned int getMemSize() const;        
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
: virtual public Ionflux::GeoUtils::BoxBoundsItem
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
        virtual void setChildIDs(const std::string& prefix, bool showLevel 
        = true, bool keepExisting = true, bool recursive = false, unsigned 
        int level = 0, unsigned int fieldWidth = 2);
        virtual std::string getXML_legacy() const;
        virtual void writeToFile(const std::string& fileName) const;
		virtual Ionflux::GeoUtils::BoundingBox* copy() const;
		static Ionflux::GeoUtils::BoundingBox* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::BoundingBox* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
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
: virtual public Ionflux::GeoUtils::TransformableObject
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
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual void applyTransform(bool recursive = false);
        virtual void initVectors();
        virtual void setVectors(Ionflux::GeoUtils::Vector3 initLocation = 
        Ionflux::GeoUtils::Vector3::ZERO, Ionflux::GeoUtils::Vector3 
        initDirection = Ionflux::GeoUtils::Vector3::E_Z, 
        Ionflux::GeoUtils::Vector3 initLookAt = 
        Ionflux::GeoUtils::Vector3::E_Z, Ionflux::GeoUtils::Vector3 
        initRight = Ionflux::GeoUtils::Camera::DEFAULT_RIGHT, 
        Ionflux::GeoUtils::Vector3 initUp = 
        Ionflux::GeoUtils::Vector3::E_Y, Ionflux::GeoUtils::Vector3 initSky
        = Ionflux::GeoUtils::Vector3::E_Y);
        virtual void setDefault();
        virtual void validate(const Ionflux::GeoUtils::CameraSetupFlags* 
        newSetupFlags = 0, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Matrix4 getExtrinsicMatrix();
        virtual Ionflux::GeoUtils::Vector3 
        getEulerAngles(Ionflux::GeoUtils::HandednessID handedness = 
        Ionflux::GeoUtils::HANDEDNESS_RIGHT, Ionflux::GeoUtils::AxisID 
        upAxis = Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID 
        depthAxis = Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID 
        horizonAxis = Ionflux::GeoUtils::AXIS_X);
        virtual Ionflux::GeoUtils::Matrix4 
        getRotationMatrix(Ionflux::GeoUtils::HandednessID handedness = 
        Ionflux::GeoUtils::HANDEDNESS_RIGHT, Ionflux::GeoUtils::AxisID 
        upAxis = Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID 
        depthAxis = Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID 
        horizonAxis = Ionflux::GeoUtils::AXIS_X);
        virtual Ionflux::GeoUtils::Matrix4 getTranslationMatrix(bool 
        adjustLocation = 
        Ionflux::GeoUtils::Camera::DEFAULT_ADJUST_LOCATION);
        virtual Ionflux::GeoUtils::Matrix4 
        getPerspectiveMatrix(Ionflux::GeoUtils::AxisID depthAxis = 
        Ionflux::GeoUtils::AXIS_Z, double near = 0., double far = 0., 
        double dScale = 1.);
        virtual Ionflux::GeoUtils::Matrix4 
        getModelViewMatrix(Ionflux::GeoUtils::CameraMode mode = 
        Ionflux::GeoUtils::Camera::MODE_PERSPECTIVE, bool adjustLocation = 
        Ionflux::GeoUtils::Camera::DEFAULT_ADJUST_LOCATION, 
        Ionflux::GeoUtils::HandednessID handedness = 
        Ionflux::GeoUtils::HANDEDNESS_RIGHT, Ionflux::GeoUtils::AxisID 
        upAxis = Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID 
        depthAxis = Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID 
        horizonAxis = Ionflux::GeoUtils::AXIS_X, double near = 0., double 
        far = 0., double dScale = 1.);
        virtual void setOriginCam(double distance0 = 10., double pitch = 
        -30., double roll = 0., double yaw = 30., double aspectRatio = 1., 
        double d = 1., Ionflux::GeoUtils::AxisID upAxis = 
        Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID depthAxis = 
        Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID horizonAxis = 
        Ionflux::GeoUtils::AXIS_X, Ionflux::GeoUtils::AxisID pitchAxis = 
        Ionflux::GeoUtils::AXIS_X, Ionflux::GeoUtils::AxisID rollAxis = 
        Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID yawAxis = 
        Ionflux::GeoUtils::AXIS_Y);
        virtual std::string getValueString() const;
        static Ionflux::GeoUtils::CameraSetupFlags createSetupFlags(bool 
        useDirection = true, bool useRight = true, bool useUp = true, bool 
        useLookAt = false, bool useSky = false, bool useAngle = false, bool
        useLens = false);
        static double angleToD(double angle, double aspectRatio = 1., 
        double dScale = 1.);
        static double dToAngle(double d, double aspectRatio = 1., double 
        dScale = 1.);
        static double lensToAngle(double lens);
        static double angleToLens(double angle);
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Camera* copy() const;
		static Ionflux::GeoUtils::Camera* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Camera* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Camera* create(Ionflux::GeoUtils::Vector3 
		initLocation, Ionflux::GeoUtils::Vector3 initDirection = 
		Ionflux::GeoUtils::Vector3::E_Z, Ionflux::GeoUtils::Vector3 initLookAt = 
		Ionflux::GeoUtils::Vector3::E_Z, Ionflux::GeoUtils::Vector3 initRight = 
		Ionflux::GeoUtils::Camera::DEFAULT_RIGHT, Ionflux::GeoUtils::Vector3 
		initUp = Ionflux::GeoUtils::Vector3::E_Y, Ionflux::GeoUtils::Vector3 
		initSky = Ionflux::GeoUtils::Vector3::E_Y, double initAngle = 1., double 
		initLens = 24., Ionflux::GeoUtils::CameraSetupFlags initSetupFlags = 
		Ionflux::GeoUtils::Camera::DEFAULT_SETUP_FLAGS, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setLocation(Ionflux::GeoUtils::Vector3* newLocation);
        virtual Ionflux::GeoUtils::Vector3* getLocation() const;
        virtual void setDirection(Ionflux::GeoUtils::Vector3* 
        newDirection);
        virtual Ionflux::GeoUtils::Vector3* getDirection() const;
        virtual void setLookAt(Ionflux::GeoUtils::Vector3* newLookAt);
        virtual Ionflux::GeoUtils::Vector3* getLookAt() const;
        virtual void setRight(Ionflux::GeoUtils::Vector3* newRight);
        virtual Ionflux::GeoUtils::Vector3* getRight() const;
        virtual void setUp(Ionflux::GeoUtils::Vector3* newUp);
        virtual Ionflux::GeoUtils::Vector3* getUp() const;
        virtual void setSky(Ionflux::GeoUtils::Vector3* newSky);
        virtual Ionflux::GeoUtils::Vector3* getSky() const;
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
		virtual unsigned int getMemSize() const;
        virtual void setNormal(const Ionflux::GeoUtils::Vector3& 
        newNormal);
        virtual Ionflux::GeoUtils::Vector3 getNormal() const;
};

}

}


%{
#include "geoutils/NFace.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VectorSetSet;
class FaceData;
class NFaceSet;

class NFaceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NFaceClassInfo();
        virtual ~NFaceClassInfo();
};

class NFace
: virtual public Ionflux::GeoUtils::BoxBoundsItem, virtual public 
Ionflux::GeoUtils::TransformableObject
{
    public:
		static const unsigned int VERTEX_INDEX_NONE;
		static const Ionflux::GeoUtils::NFaceTypeID TYPE_FACE;
		static const Ionflux::GeoUtils::NFaceTypeID TYPE_EDGE;
        
        NFace();
		NFace(const Ionflux::GeoUtils::NFace& other);
        NFace(const Ionflux::ObjectBase::UIntVector* initVerts, 
        Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
        Ionflux::GeoUtils::FaceData* initUV = 0, 
        Ionflux::GeoUtils::FaceData* initVertexColors = 0);
        NFace(unsigned int v0, unsigned int v1, unsigned int v2 = 
        Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, unsigned int v3 = 
        Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, 
        Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
        Ionflux::GeoUtils::FaceData* initUV = 0, 
        Ionflux::GeoUtils::FaceData* initVertexColors = 0);
        virtual ~NFace();
        virtual void copyVertices();
        virtual void update();
        virtual void clearPolygon();
        virtual void clear();
        virtual void addVertices(unsigned int v0, unsigned int v1 = 
        Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, unsigned int v2 = 
        Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, unsigned int v3 = 
        Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE);
        virtual Ionflux::GeoUtils::VectorSet* 
        addFaceData(Ionflux::GeoUtils::FaceData* newFaceData);
        virtual Ionflux::GeoUtils::VectorSet* 
        addFaceData(Ionflux::GeoUtils::FaceDataTypeID dataType);
        virtual Ionflux::GeoUtils::VectorSet* 
        addFaceData(Ionflux::GeoUtils::FaceDataTypeID dataType, 
        Ionflux::GeoUtils::Vector* v0, Ionflux::GeoUtils::Vector* v1 = 0, 
        Ionflux::GeoUtils::Vector* v2 = 0, Ionflux::GeoUtils::Vector* v3 = 
        0);
        virtual Ionflux::GeoUtils::VectorSet* 
        addTexCoords(Ionflux::GeoUtils::Vector* v0, 
        Ionflux::GeoUtils::Vector* v1 = 0, Ionflux::GeoUtils::Vector* v2 = 
        0, Ionflux::GeoUtils::Vector* v3 = 0);
        virtual Ionflux::GeoUtils::VectorSet* 
        addVertexColors(Ionflux::GeoUtils::Vector* v0, 
        Ionflux::GeoUtils::Vector* v1 = 0, Ionflux::GeoUtils::Vector* v2 = 
        0, Ionflux::GeoUtils::Vector* v3 = 0);
        virtual Ionflux::GeoUtils::VectorSet* 
        addVertexNormals(Ionflux::GeoUtils::Vector* v0, 
        Ionflux::GeoUtils::Vector* v1 = 0, Ionflux::GeoUtils::Vector* v2 = 
        0, Ionflux::GeoUtils::Vector* v3 = 0);
        virtual void getFaceDataByType(Ionflux::GeoUtils::FaceDataTypeID 
        dataType, Ionflux::GeoUtils::VectorSetSet& target);
        virtual Ionflux::GeoUtils::FaceData* 
        getFaceDataByType0(Ionflux::GeoUtils::FaceDataTypeID dataType, 
        unsigned int index = 0);
        virtual void getTexCoords(Ionflux::GeoUtils::VectorSetSet& target);
        virtual Ionflux::GeoUtils::FaceData* getTexCoords0(unsigned int 
        index = 0);
        virtual void getVertexColors(Ionflux::GeoUtils::VectorSetSet& 
        target);
        virtual Ionflux::GeoUtils::FaceData* getVertexColors0(unsigned int 
        index = 0);
        virtual void getVertexNormals(Ionflux::GeoUtils::VectorSetSet& 
        target);
        virtual Ionflux::GeoUtils::FaceData* getVertexNormals0(unsigned int
        index = 0);
        virtual void getFaceDataByVertex(Ionflux::ObjectBase::UIntVector& 
        faceVertexIndices, Ionflux::GeoUtils::VectorSetSet& target);
        virtual Ionflux::GeoUtils::Polygon3* getPolygon();
        virtual bool checkLineInner(const Ionflux::GeoUtils::Line3& line, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkPlaneInner(const Ionflux::GeoUtils::Plane3& plane,
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkSphereInner(const Ionflux::GeoUtils::Sphere3& 
        sphere, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual int checkBoxInner(const Ionflux::GeoUtils::BoxBoundsItem& 
        other, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Vertex3* getVertexData(unsigned int 
        index) const;
        virtual bool isPlanar(double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool isEdge() const;
        virtual bool isTri() const;
        virtual bool isQuad() const;
        virtual void getEdge(Ionflux::GeoUtils::Edge& target) const;
        virtual Ionflux::GeoUtils::Edge getEdge0() const;
        virtual void applyVertexIndexOffset(int offset);
        virtual void getTris(Ionflux::GeoUtils::NFaceVector& target);
        virtual void getTris(Ionflux::GeoUtils::NFaceSet& target);
        virtual Ionflux::GeoUtils::NFaceVector getTris0();
        virtual void getEdges(Ionflux::GeoUtils::NFaceVector& target, bool 
        copyFaceData = true);
        virtual void getEdges(Ionflux::GeoUtils::NFaceSet& target, bool 
        copyFaceData = true);
        virtual double getArea();
        virtual bool operator==(const Ionflux::GeoUtils::NFace& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::NFace& other) 
        const;
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual Ionflux::GeoUtils::Range3 getBounds();
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::NFace& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::NFace& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::NFace& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::NFace& normalize();
        virtual Ionflux::GeoUtils::NFace& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::NFace& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::NFace& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::NFace& duplicate();
        virtual std::string getValueString() const;
        static std::string 
        getNFaceTypeIDString(Ionflux::GeoUtils::NFaceTypeID typeID);
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::NFace* copy() const;
		static Ionflux::GeoUtils::NFace* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::NFace* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::NFace* create(const 
		Ionflux::ObjectBase::UIntVector* initVerts, 
		Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
		Ionflux::GeoUtils::FaceData* initUV = 0, Ionflux::GeoUtils::FaceData* 
		initVertexColors = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::NFace* create(unsigned int v0, unsigned int v1,
		unsigned int v2 = Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, unsigned 
		int v3 = Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, 
		Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
		Ionflux::GeoUtils::FaceData* initUV = 0, Ionflux::GeoUtils::FaceData* 
		initVertexColors = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual bool serialize(std::string& target) const;
        virtual Ionflux::ObjectBase::DataSize deserialize(const std::string& source, int offset = 0);
        virtual bool serialize(Ionflux::ObjectBase::IFIOContext& ioCtx, bool addMagicWord = true) const;
        virtual Ionflux::ObjectBase::DataSize deserialize(Ionflux::ObjectBase::IFIOContext& ioCtx, Ionflux::ObjectBase::DataSize offset = Ionflux::ObjectBase::DATA_SIZE_INVALID, bool checkMagicWord = true);
        virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllable() const;
        virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllableBase() const;        
        virtual unsigned int getNumVertices() const;
        virtual unsigned int getVertex(unsigned int elementIndex = 0) 
        const;
		virtual int findVertex(unsigned int needle, unsigned int occurence = 1) 
		const;
        virtual std::vector<unsigned int>& getVertices();
        virtual void addVertex(unsigned int addElement);
		virtual unsigned int addVertex();
		virtual void addVertices(std::vector<unsigned int>& newVertices);
		virtual void addVertices(Ionflux::GeoUtils::NFace* newVertices);        
        virtual void removeVertex(unsigned int removeElement);
		virtual void removeVertexIndex(unsigned int removeIndex);
		virtual void clearVertices();
        virtual void setVertexSource(Ionflux::GeoUtils::Vertex3Set* 
        newVertexSource);
        virtual Ionflux::GeoUtils::Vertex3Set* getVertexSource() const;
        virtual void setFaceData(Ionflux::GeoUtils::VectorSetSet* 
        newFaceData);
        virtual Ionflux::GeoUtils::VectorSetSet* getFaceData() const;
};

}

}


%{
#include "geoutils/NFaceSet.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class NFace;

class NFaceSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NFaceSetClassInfo();
        virtual ~NFaceSetClassInfo();
};

class NFaceSet
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        NFaceSet();
		NFaceSet(const Ionflux::GeoUtils::NFaceSet& other);
        virtual ~NFaceSet();
        virtual bool isTriSet() const;
        virtual bool isQuadSet() const;
        virtual bool isEdgeSet() const;
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::NFaceSet* copy() const;
		static Ionflux::GeoUtils::NFaceSet* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::GeoUtils::NFaceSet* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		virtual unsigned int getMemSize() const;        
        virtual unsigned int getNumNFaces() const;
        virtual Ionflux::GeoUtils::NFace* getNFace(unsigned int 
        elementIndex = 0) const;
		virtual int findNFace(Ionflux::GeoUtils::NFace* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::NFace*>& getNFaces();
        virtual void addNFace(Ionflux::GeoUtils::NFace* addElement);
		virtual Ionflux::GeoUtils::NFace* addNFace();
		virtual void addNFaces(std::vector<Ionflux::GeoUtils::NFace*>& 
		newNFaces);
		virtual void addNFaces(Ionflux::GeoUtils::NFaceSet* newNFaces);        
        virtual void removeNFace(Ionflux::GeoUtils::NFace* removeElement);
		virtual void removeNFaceIndex(unsigned int removeIndex);
		virtual void clearNFaces();
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

class VectorSetSet;
class FaceData;
class NFaceSet;

class FaceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FaceClassInfo();
        virtual ~FaceClassInfo();
};

class Face
: public Ionflux::GeoUtils::NFace
{
    public:
        
        Face();
		Face(const Ionflux::GeoUtils::Face& other);
        Face(const Ionflux::ObjectBase::UIntVector* initVerts, 
        Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
        Ionflux::GeoUtils::FaceData* initUV = 0, 
        Ionflux::GeoUtils::FaceData* initVertexColors = 0);
        Face(unsigned int v0, unsigned int v1, unsigned int v2, unsigned 
        int v3 = Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, 
        Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
        Ionflux::GeoUtils::FaceData* initUV = 0, 
        Ionflux::GeoUtils::FaceData* initVertexColors = 0);
        virtual ~Face();
        virtual void update();
        virtual void clearTangentSpace();
        virtual void clear();
        virtual void setFaceVertexNormals(bool flip0 = false);
        virtual void setVertexColors(const Ionflux::GeoUtils::Vector4& 
        color);
        virtual Ionflux::GeoUtils::Vector3 getTangent();
        virtual Ionflux::GeoUtils::Vector3 getBinormal();
        virtual Ionflux::GeoUtils::Vector3 getNormal();
        virtual Ionflux::GeoUtils::Matrix3 getTangentBase();
        virtual void makePlanar(double p = 1., double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool isBackface(const Ionflux::GeoUtils::Vector3& front);
        virtual void getTris(Ionflux::GeoUtils::FaceVector& target);
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
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Face* copy() const;
		static Ionflux::GeoUtils::Face* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Face* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Face* create(const 
		Ionflux::ObjectBase::UIntVector* initVerts, 
		Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
		Ionflux::GeoUtils::FaceData* initUV = 0, Ionflux::GeoUtils::FaceData* 
		initVertexColors = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Face* create(unsigned int v0, unsigned int v1, 
		unsigned int v2, unsigned int v3 = 
		Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, 
		Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
		Ionflux::GeoUtils::FaceData* initUV = 0, Ionflux::GeoUtils::FaceData* 
		initVertexColors = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
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
: virtual public Ionflux::GeoUtils::BoxBoundsItem, virtual public 
Ionflux::GeoUtils::ItemSource, virtual public 
Ionflux::GeoUtils::TransformableObject
{
    public:
		static const std::string DEFAULT_ID;
		static const Ionflux::GeoUtils::MeshTypeID TYPE_UNDEFINED;
		static const Ionflux::GeoUtils::MeshTypeID TYPE_MIXED;
		static const Ionflux::GeoUtils::MeshTypeID TYPE_TRI;
		static const Ionflux::GeoUtils::MeshTypeID TYPE_QUAD;
        
        Mesh();
		Mesh(const Ionflux::GeoUtils::Mesh& other);
        Mesh(Ionflux::GeoUtils::Vertex3Vector* initVerts, const 
        Ionflux::GeoUtils::FaceVector* initFaces);
        Mesh(Ionflux::GeoUtils::Vertex3Set* initVertexSource, const 
        Ionflux::GeoUtils::FaceVector* initFaces);
        virtual ~Mesh();
        virtual Ionflux::GeoUtils::Range3 getBounds();
        virtual void copyVertices();
        virtual void update(bool updateFaces = true, bool updateEdges = 
        true);
        virtual void clear();
        virtual void clearData();
        virtual void setFaceIDs();
        virtual void setEdgeIDs();
        virtual Ionflux::GeoUtils::BoxBoundsItem* getItem(const 
        std::string& itemID);
        virtual Ionflux::GeoUtils::NFace* 
        getNFace(Ionflux::GeoUtils::NFaceTypeID typeID, unsigned int index)
        const;
        virtual unsigned int getNumNFaces(Ionflux::GeoUtils::NFaceTypeID 
        typeID) const;
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
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Mesh& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Mesh& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Mesh& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Mesh& swapAxes(Ionflux::GeoUtils::AxisID
        x = Ionflux::GeoUtils::AXIS_X, Ionflux::GeoUtils::AxisID y = 
        Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID z = 
        Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID w = 
        Ionflux::GeoUtils::AXIS_W);
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
        virtual void getFacePolygons(Ionflux::GeoUtils::Polygon3Set& 
        target);
        virtual void getEdgePolygons(Ionflux::GeoUtils::Polygon3Set& 
        target);
        virtual void removeBackfaces(const Ionflux::GeoUtils::Vector3& 
        front);
        virtual void sortFaces(Ionflux::GeoUtils::FaceCompare* compFunc = 
        0);
        virtual unsigned int makePlanar(const 
        Ionflux::ObjectBase::UIntVector& indices, unsigned int 
        maxIterations = 10000, double p = 1., double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual unsigned int makeTris();
        virtual void setFaceVertexNormals(bool flip0 = false);
        virtual void setFaceVertexColors(const Ionflux::GeoUtils::Vector4& 
        color);
        virtual Ionflux::GeoUtils::MeshTypeID getMeshType() const;
        virtual bool isTriMesh() const;
        virtual unsigned int createEdges();
        virtual void merge(Ionflux::GeoUtils::Mesh& other);
        virtual void writeOBJ(Ionflux::ObjectBase::IFIOContext& ioCtx, 
        unsigned int precision = 6, bool smoothShading = false);
        virtual std::string getValueString() const;
        static Ionflux::GeoUtils::Mesh* plane();
        static Ionflux::GeoUtils::Mesh* cube();
        static Ionflux::GeoUtils::Mesh* cylinder(unsigned int subDivs = 10,
        double length = 1., double radius = 0.5);
        static Ionflux::GeoUtils::Mesh* arrow(unsigned int subDivs = 10, 
        double length = 1., double radius = 0.005, double headLength = 0.1,
        double headRadius = 4.);
        static Ionflux::GeoUtils::Mesh* grid(unsigned int subDivsX = 10, 
        unsigned int subDivsY = 10);
        static Ionflux::GeoUtils::Mesh* fiber(unsigned int aSubDivs = 10, 
        unsigned int lSubDivs = 10, double length = 1., double radius = 
        0.05);
        static std::string 
        getMeshTypeIDString(Ionflux::GeoUtils::MeshTypeID typeID);
        static unsigned int 
        getNumVerticesPerFace(Ionflux::GeoUtils::MeshTypeID typeID);
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Mesh* copy() const;
		static Ionflux::GeoUtils::Mesh* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Mesh* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Mesh* create(Ionflux::GeoUtils::Vertex3Vector* 
		initVerts, const Ionflux::GeoUtils::FaceVector* initFaces, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Mesh* create(Ionflux::GeoUtils::Vertex3Set* 
		initVertexSource, const Ionflux::GeoUtils::FaceVector* initFaces, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
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
		virtual Ionflux::GeoUtils::Vertex3* addVertex();
		virtual void addVertices(std::vector<Ionflux::GeoUtils::Vertex3*>& 
		newVertices);
		virtual void addVertices(Ionflux::GeoUtils::Mesh* newVertices);        
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
		virtual Ionflux::GeoUtils::Face* addFace();
		virtual void addFaces(std::vector<Ionflux::GeoUtils::Face*>& newFaces);
		virtual void addFaces(Ionflux::GeoUtils::Mesh* newFaces);        
        virtual void removeFace(Ionflux::GeoUtils::Face* removeElement);
		virtual void removeFaceIndex(unsigned int removeIndex);
		virtual void clearFaces();        
        virtual unsigned int getNumEdges() const;
        virtual Ionflux::GeoUtils::NFace* getEdge(unsigned int elementIndex
        = 0) const;
		virtual int findEdge(Ionflux::GeoUtils::NFace* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::NFace*>& getEdges();
        virtual void addEdge(Ionflux::GeoUtils::NFace* addElement);
		virtual Ionflux::GeoUtils::NFace* addEdge();
		virtual void addEdges(std::vector<Ionflux::GeoUtils::NFace*>& newEdges);
		virtual void addEdges(Ionflux::GeoUtils::Mesh* newEdges);        
        virtual void removeEdge(Ionflux::GeoUtils::NFace* removeElement);
		virtual void removeEdgeIndex(unsigned int removeIndex);
		virtual void clearEdges();
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
		virtual unsigned int getMemSize() const;
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


%{
#include "geoutils/Vector3Mapping.hpp"
%}

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

}

}

}


%{
#include "geoutils/Compose3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

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
		virtual unsigned int getMemSize() const;
        virtual void setFuncX0(Ionflux::Mapping::Mapping* newFuncX0);
        virtual Ionflux::Mapping::Mapping* getFuncX0() const;
        virtual void setFuncX1(Ionflux::Mapping::Mapping* newFuncX1);
        virtual Ionflux::Mapping::Mapping* getFuncX1() const;
        virtual void setFuncX2(Ionflux::Mapping::Mapping* newFuncX2);
        virtual Ionflux::Mapping::Mapping* getFuncX2() const;
};

}

}

}


%{
#include "geoutils/Accept3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

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

}

}

}


%{
#include "geoutils/AcceptLength3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

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
		virtual Ionflux::GeoUtils::Mapping::AcceptLength3* copy() const;
		static Ionflux::GeoUtils::Mapping::AcceptLength3* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Mapping::AcceptLength3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setLengthRange(const Ionflux::GeoUtils::Range& 
        newLengthRange);
        virtual Ionflux::GeoUtils::Range getLengthRange() const;
};

}

}

}


%{
#include "geoutils/AcceptVolume3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

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
        initSource, Ionflux::GeoUtils::Shape3* initRefObject, 
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
		virtual unsigned int getMemSize() const;
        virtual void setRefObject(Ionflux::GeoUtils::Shape3* newRefObject);
        virtual Ionflux::GeoUtils::Shape3* getRefObject() const;
};

}

}

}


%{
#include "geoutils/Lookup3.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

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
		virtual Ionflux::GeoUtils::Mapping::Lookup3* copy() const;
		static Ionflux::GeoUtils::Mapping::Lookup3* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Mapping::Lookup3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;        
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

}

}


%{
#include "geoutils/Vector3MappingSet.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

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
		virtual Ionflux::GeoUtils::Vector3MappingSet* copy() const;
		static Ionflux::GeoUtils::Vector3MappingSet* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Vector3MappingSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;        
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

}

}


%{
#include "geoutils/TransformNode.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

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
		virtual Ionflux::GeoUtils::TransformNodes::TransformNode* copy() const;
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

}

}

}


%{
#include "geoutils/Connection.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

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
		virtual Ionflux::GeoUtils::TransformNodes::Connection* copy() const;
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
		virtual unsigned int getMemSize() const;
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


%{
#include "geoutils/TransformGraph.hpp"
%}

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
		virtual unsigned int getMemSize() const;        
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
		virtual unsigned int getMemSize() const;
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


%{
#include "geoutils/Duplicate.hpp"
%}

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
		virtual Ionflux::GeoUtils::TransformNodes::Duplicate* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Duplicate* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Duplicate* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		virtual void setParam(Ionflux::ObjectBase::IFParamID paramID, 
		Ionflux::Mapping::MappingValue paramValue);
		virtual Ionflux::Mapping::MappingValue 
		getParam(Ionflux::ObjectBase::IFParamID paramID);
        virtual void setNumDuplicates(unsigned int newNumDuplicates);
        virtual unsigned int getNumDuplicates() const;
        virtual void setNumDuplicatesParam(Ionflux::Mapping::MappingValue 
        newNumDuplicatesParam);
        virtual Ionflux::Mapping::MappingValue getNumDuplicatesParam() 
        const;
        virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
        virtual Ionflux::Mapping::Mapping* getFunc() const;
};

}

}

}


%{
#include "geoutils/MatrixTransform.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

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
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
        
        MatrixTransform();
		MatrixTransform(const Ionflux::GeoUtils::TransformNodes::MatrixTransform& other);
        MatrixTransform(const Ionflux::GeoUtils::Matrix4& initMatrix, const
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~MatrixTransform();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::MatrixTransform* copy() const;
		static Ionflux::GeoUtils::TransformNodes::MatrixTransform* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::MatrixTransform* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setMatrix(const Ionflux::GeoUtils::Matrix4& 
        newMatrix);
        virtual Ionflux::GeoUtils::Matrix4 getMatrix() const;
};

}

}

}


%{
#include "geoutils/Rotate.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

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
		virtual unsigned int getMemSize() const;
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

}

}

}


%{
#include "geoutils/Translate.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

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
		virtual Ionflux::GeoUtils::TransformNodes::Translate* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Translate* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Translate* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
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

}

}

}


%{
#include "geoutils/Scale.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

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
		virtual unsigned int getMemSize() const;
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

}

}

}


%{
#include "geoutils/Center.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

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
		virtual Ionflux::GeoUtils::TransformNodes::Center* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Center* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Center* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setOrigin(const Ionflux::GeoUtils::Vector3& 
        newOrigin);
        virtual Ionflux::GeoUtils::Vector3 getOrigin() const;
        virtual void setMethod(Ionflux::GeoUtils::CenteringMethod 
        newMethod);
        virtual Ionflux::GeoUtils::CenteringMethod getMethod() const;
};

}

}

}


%{
#include "geoutils/Normalize.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

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
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
        
        Normalize();
		Normalize(const Ionflux::GeoUtils::TransformNodes::Normalize& other);
        Normalize(const Ionflux::ObjectBase::IFObjectID& nodeID);
        virtual ~Normalize();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::Normalize* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Normalize* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Normalize* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/Array.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

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
		virtual Ionflux::GeoUtils::TransformNodes::Array* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Array* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Array* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
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

}

}

}


%{
#include "geoutils/Flatten.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

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
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
        
        Flatten();
		Flatten(const Ionflux::GeoUtils::TransformNodes::Flatten& other);
        Flatten(const Ionflux::ObjectBase::IFObjectID& nodeID);
        virtual ~Flatten();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::Flatten* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Flatten* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Flatten* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/Merge.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

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
    public:
		static const unsigned int INPUT_FIRST;
		static const unsigned int OUTPUT_TARGET;
        
        Merge();
		Merge(const Ionflux::GeoUtils::TransformNodes::Merge& other);
        Merge(const Ionflux::ObjectBase::IFObjectID& nodeID);
        virtual ~Merge();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::Merge* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Merge* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Merge* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/Explode.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

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
		virtual Ionflux::GeoUtils::TransformNodes::Explode* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Explode* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Explode* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setElementsPerGroup(unsigned int newElementsPerGroup);
        virtual unsigned int getElementsPerGroup() const;
};

}

}

}


%{
#include "geoutils/Wrap.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

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
    public:
		static const unsigned int INPUT_FIRST;
		static const unsigned int OUTPUT_TARGET;
        
        Wrap();
		Wrap(const Ionflux::GeoUtils::TransformNodes::Wrap& other);
        Wrap(const Ionflux::ObjectBase::IFObjectID& nodeID);
        virtual ~Wrap();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::Wrap* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Wrap* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Wrap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/Unwrap.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

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
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_FIRST;
        
        Unwrap();
		Unwrap(const Ionflux::GeoUtils::TransformNodes::Unwrap& other);
        Unwrap(const Ionflux::ObjectBase::IFObjectID& nodeID);
        virtual ~Unwrap();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::Unwrap* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Unwrap* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Unwrap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/Iterate.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

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
        virtual void updateInputs();
		virtual Ionflux::GeoUtils::TransformNodes::Iterate* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Iterate* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Iterate* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setNumIterations(unsigned int newNumIterations);
        virtual unsigned int getNumIterations() const;
};

}

}

}


%{
#include "geoutils/Source.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

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
    public:
		static const unsigned int OUTPUT_TARGET;
        
        Source();
		Source(const Ionflux::GeoUtils::TransformNodes::Source& other);
        Source(Ionflux::GeoUtils::TransformableGroup* initSource, const 
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Source();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::Source* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Source* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Source* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setSource(Ionflux::GeoUtils::TransformableGroup* 
        newSource);
        virtual Ionflux::GeoUtils::TransformableGroup* getSource() const;
};

}

}

}


%{
#include "geoutils/Cache.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

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
    public:
		static const unsigned int INPUT_SOURCE;
		static const unsigned int OUTPUT_TARGET;
        
        Cache();
		Cache(const Ionflux::GeoUtils::TransformNodes::Cache& other);
        Cache(const Ionflux::ObjectBase::IFObjectID& nodeID);
        virtual ~Cache();
        virtual std::string getString() const;
        virtual void cleanup();
        virtual void update();
		virtual Ionflux::GeoUtils::TransformNodes::Cache* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Cache* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Cache* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/Clone.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

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
		virtual Ionflux::GeoUtils::TransformNodes::Clone* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Clone* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Clone* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
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
		virtual unsigned int getMemSize() const;
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


%{
#include "geoutils/Scatter.hpp"
%}

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
        Ionflux::GeoUtils::Vector3::ZERO, Ionflux::GeoUtils::Shape3* 
        refObject = 0, Ionflux::Mapping::Mapping* sourceFuncX = 0, 
        Ionflux::Mapping::Mapping* sourceFuncY = 0, 
        Ionflux::Mapping::Mapping* sourceFuncZ = 0);
		virtual Ionflux::GeoUtils::TransformNodes::Scatter* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Scatter* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Scatter* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
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


%{
#include "geoutils/VectorSet.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Vector;

class VectorSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VectorSetClassInfo();
        virtual ~VectorSetClassInfo();
};

class VectorSet
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        VectorSet();
		VectorSet(const Ionflux::GeoUtils::VectorSet& other);
        VectorSet(Ionflux::GeoUtils::VectorVector& initVectors);
        virtual ~VectorSet();
        virtual void makeOrientationsConsistent(Ionflux::GeoUtils::Vector* 
        flipData = 0, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual void getCentroid(Ionflux::GeoUtils::Vector& target) const;
        virtual bool operator==(const Ionflux::GeoUtils::VectorSet& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::VectorSet& other) 
        const;
        virtual std::string getValueStringF(unsigned int fieldWidth = 5, 
        unsigned int precision = 3, const std::string& colSep = " ", const 
        std::string& rowSep = "\n", const std::string& rowPrefix = "") 
        const;
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::VectorSet* copy() const;
		static Ionflux::GeoUtils::VectorSet* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::VectorSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::VectorSet* 
		create(Ionflux::GeoUtils::VectorVector& initVectors, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumVectors() const;
        virtual Ionflux::GeoUtils::Vector* getVector(unsigned int 
        elementIndex = 0) const;
		virtual int findVector(Ionflux::GeoUtils::Vector* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Vector*>& getVectors();
        virtual void addVector(Ionflux::GeoUtils::Vector* addElement);
		virtual Ionflux::GeoUtils::Vector* addVector();
		virtual void addVectors(std::vector<Ionflux::GeoUtils::Vector*>& 
		newVectors);
		virtual void addVectors(Ionflux::GeoUtils::VectorSet* newVectors);        
        virtual void removeVector(Ionflux::GeoUtils::Vector* 
        removeElement);
		virtual void removeVectorIndex(unsigned int removeIndex);
		virtual void clearVectors();
};

}

}


%{
#include "geoutils/VectorSetSet.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VectorSet;

class VectorSetSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VectorSetSetClassInfo();
        virtual ~VectorSetSetClassInfo();
};

class VectorSetSet
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        VectorSetSet();
		VectorSetSet(const Ionflux::GeoUtils::VectorSetSet& other);
        VectorSetSet(Ionflux::GeoUtils::VectorSetVector& initVectorSets);
        virtual ~VectorSetSet();
        virtual bool operator==(const Ionflux::GeoUtils::VectorSetSet& 
        other) const;
        virtual bool operator!=(const Ionflux::GeoUtils::VectorSetSet& 
        other) const;
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::VectorSetSet* copy() const;
		static Ionflux::GeoUtils::VectorSetSet* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::VectorSetSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::VectorSetSet* 
		create(Ionflux::GeoUtils::VectorSetVector& initVectorSets, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumVectorSets() const;
        virtual Ionflux::GeoUtils::VectorSet* getVectorSet(unsigned int 
        elementIndex = 0) const;
		virtual int findVectorSet(Ionflux::GeoUtils::VectorSet* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::VectorSet*>& 
        getVectorSets();
        virtual void addVectorSet(Ionflux::GeoUtils::VectorSet* 
        addElement);
		virtual Ionflux::GeoUtils::VectorSet* addVectorSet();
		virtual void addVectorSets(std::vector<Ionflux::GeoUtils::VectorSet*>& 
		newVectorSets);
		virtual void addVectorSets(Ionflux::GeoUtils::VectorSetSet* 
		newVectorSets);        
        virtual void removeVectorSet(Ionflux::GeoUtils::VectorSet* 
        removeElement);
		virtual void removeVectorSetIndex(unsigned int removeIndex);
		virtual void clearVectorSets();
};

}

}


%{
#include "geoutils/FaceData.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class FaceDataClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FaceDataClassInfo();
        virtual ~FaceDataClassInfo();
};

class FaceData
: public Ionflux::GeoUtils::VectorSet
{
    public:
		static const Ionflux::GeoUtils::FaceDataTypeID TYPE_UNDEFINED;
		static const Ionflux::GeoUtils::FaceDataTypeID TYPE_TEX_COORD;
		static const Ionflux::GeoUtils::FaceDataTypeID TYPE_VERTEX_COLOR;
		static const Ionflux::GeoUtils::FaceDataTypeID TYPE_VERTEX_NORMAL;
        
        FaceData();
		FaceData(const Ionflux::GeoUtils::FaceData& other);
        FaceData(Ionflux::GeoUtils::VectorVector& initVectors, 
        Ionflux::GeoUtils::FaceDataTypeID initDataType = TYPE_UNDEFINED);
        FaceData(Ionflux::GeoUtils::FaceDataTypeID initDataType);
        virtual ~FaceData();
        virtual std::string getValueString() const;
        virtual bool hasType(Ionflux::GeoUtils::FaceDataTypeID typeID);
        static std::string 
        getTypeIDString(Ionflux::GeoUtils::FaceDataTypeID typeID);
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::FaceData* copy() const;
		static Ionflux::GeoUtils::FaceData* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::GeoUtils::FaceData* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::FaceData* 
		create(Ionflux::GeoUtils::VectorVector& initVectors, 
		Ionflux::GeoUtils::FaceDataTypeID initDataType = TYPE_UNDEFINED, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::FaceData* 
		create(Ionflux::GeoUtils::FaceDataTypeID initDataType, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setDataType(Ionflux::GeoUtils::FaceDataTypeID 
        newDataType);
        virtual Ionflux::GeoUtils::FaceDataTypeID getDataType() const;
};

}

}



%{
#include "geoutils/xmlio/VectorXMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class VectorXMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VectorXMLFactoryClassInfo();
        virtual ~VectorXMLFactoryClassInfo();
};

class VectorXMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        VectorXMLFactory();
		VectorXMLFactory(const Ionflux::GeoUtils::XMLUtils::VectorXMLFactory& other);
        virtual ~VectorXMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Vector& target, const std::string& elementName =
        "") const;
        virtual Ionflux::GeoUtils::Vector* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::VectorXMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::VectorXMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::VectorXMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/Vector2XMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class Vector2XMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vector2XMLFactoryClassInfo();
        virtual ~Vector2XMLFactoryClassInfo();
};

class Vector2XMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        Vector2XMLFactory();
		Vector2XMLFactory(const Ionflux::GeoUtils::XMLUtils::Vector2XMLFactory& other);
        virtual ~Vector2XMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Vector2& target, const std::string& elementName 
        = "") const;
        virtual Ionflux::GeoUtils::Vector2* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::Vector2XMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::Vector2XMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::Vector2XMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/Vector3XMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class Vector3XMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vector3XMLFactoryClassInfo();
        virtual ~Vector3XMLFactoryClassInfo();
};

class Vector3XMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        Vector3XMLFactory();
		Vector3XMLFactory(const Ionflux::GeoUtils::XMLUtils::Vector3XMLFactory& other);
        virtual ~Vector3XMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Vector3& target, const std::string& elementName 
        = "") const;
        virtual Ionflux::GeoUtils::Vector3* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::Vector3XMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::Vector3XMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::Vector3XMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/Vector4XMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class Vector4XMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vector4XMLFactoryClassInfo();
        virtual ~Vector4XMLFactoryClassInfo();
};

class Vector4XMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        Vector4XMLFactory();
		Vector4XMLFactory(const Ionflux::GeoUtils::XMLUtils::Vector4XMLFactory& other);
        virtual ~Vector4XMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Vector4& target, const std::string& elementName 
        = "") const;
        virtual Ionflux::GeoUtils::Vector4* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::Vector4XMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::Vector4XMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::Vector4XMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/VectorNXMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class VectorNXMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VectorNXMLFactoryClassInfo();
        virtual ~VectorNXMLFactoryClassInfo();
};

class VectorNXMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        VectorNXMLFactory();
		VectorNXMLFactory(const Ionflux::GeoUtils::XMLUtils::VectorNXMLFactory& other);
        virtual ~VectorNXMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::VectorN& target, const std::string& elementName 
        = "") const;
        virtual Ionflux::GeoUtils::VectorN* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::VectorNXMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::VectorNXMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::VectorNXMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/VectorSetXMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class VectorSetXMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VectorSetXMLFactoryClassInfo();
        virtual ~VectorSetXMLFactoryClassInfo();
};

class VectorSetXMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        VectorSetXMLFactory();
		VectorSetXMLFactory(const Ionflux::GeoUtils::XMLUtils::VectorSetXMLFactory& other);
        virtual ~VectorSetXMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::VectorSet& target, const std::string& 
        elementName = "") const;
        virtual Ionflux::GeoUtils::VectorSet* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::VectorSetXMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::VectorSetXMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::VectorSetXMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/VectorSetSetXMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class VectorSetSetXMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VectorSetSetXMLFactoryClassInfo();
        virtual ~VectorSetSetXMLFactoryClassInfo();
};

class VectorSetSetXMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        VectorSetSetXMLFactory();
		VectorSetSetXMLFactory(const Ionflux::GeoUtils::XMLUtils::VectorSetSetXMLFactory& other);
        virtual ~VectorSetSetXMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::VectorSetSet& target, const std::string& 
        elementName = "") const;
        virtual Ionflux::GeoUtils::VectorSetSet* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::VectorSetSetXMLFactory* copy() 
		const;
		static Ionflux::GeoUtils::XMLUtils::VectorSetSetXMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::VectorSetSetXMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/Object3XMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class Object3XMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Object3XMLFactoryClassInfo();
        virtual ~Object3XMLFactoryClassInfo();
};

class Object3XMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        Object3XMLFactory();
		Object3XMLFactory(const Ionflux::GeoUtils::XMLUtils::Object3XMLFactory& other);
        virtual ~Object3XMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Object3& target, const std::string& elementName 
        = "") const;
        virtual Ionflux::GeoUtils::Object3* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::Object3XMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::Object3XMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::Object3XMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/MatrixXMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class MatrixXMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MatrixXMLFactoryClassInfo();
        virtual ~MatrixXMLFactoryClassInfo();
};

class MatrixXMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        MatrixXMLFactory();
		MatrixXMLFactory(const Ionflux::GeoUtils::XMLUtils::MatrixXMLFactory& other);
        virtual ~MatrixXMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Matrix& target, const std::string& elementName =
        "") const;
        virtual Ionflux::GeoUtils::Matrix* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::MatrixXMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::MatrixXMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::MatrixXMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/Matrix2XMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class Matrix2XMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Matrix2XMLFactoryClassInfo();
        virtual ~Matrix2XMLFactoryClassInfo();
};

class Matrix2XMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        Matrix2XMLFactory();
		Matrix2XMLFactory(const Ionflux::GeoUtils::XMLUtils::Matrix2XMLFactory& other);
        virtual ~Matrix2XMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Matrix2& target, const std::string& elementName 
        = "") const;
        virtual Ionflux::GeoUtils::Matrix2* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::Matrix2XMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::Matrix2XMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::Matrix2XMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/Matrix3XMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class Matrix3XMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Matrix3XMLFactoryClassInfo();
        virtual ~Matrix3XMLFactoryClassInfo();
};

class Matrix3XMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        Matrix3XMLFactory();
		Matrix3XMLFactory(const Ionflux::GeoUtils::XMLUtils::Matrix3XMLFactory& other);
        virtual ~Matrix3XMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Matrix3& target, const std::string& elementName 
        = "") const;
        virtual Ionflux::GeoUtils::Matrix3* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::Matrix3XMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::Matrix3XMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::Matrix3XMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/Matrix4XMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class Matrix4XMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Matrix4XMLFactoryClassInfo();
        virtual ~Matrix4XMLFactoryClassInfo();
};

class Matrix4XMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        Matrix4XMLFactory();
		Matrix4XMLFactory(const Ionflux::GeoUtils::XMLUtils::Matrix4XMLFactory& other);
        virtual ~Matrix4XMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Matrix4& target, const std::string& elementName 
        = "") const;
        virtual Ionflux::GeoUtils::Matrix4* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::Matrix4XMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::Matrix4XMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::Matrix4XMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/MatrixMNXMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class MatrixMNXMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MatrixMNXMLFactoryClassInfo();
        virtual ~MatrixMNXMLFactoryClassInfo();
};

class MatrixMNXMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        MatrixMNXMLFactory();
		MatrixMNXMLFactory(const Ionflux::GeoUtils::XMLUtils::MatrixMNXMLFactory& other);
        virtual ~MatrixMNXMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::MatrixMN& target, const std::string& elementName
        = "") const;
        virtual Ionflux::GeoUtils::MatrixMN* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::MatrixMNXMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::MatrixMNXMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::MatrixMNXMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/FaceDataXMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class FaceDataXMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FaceDataXMLFactoryClassInfo();
        virtual ~FaceDataXMLFactoryClassInfo();
};

class FaceDataXMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        FaceDataXMLFactory();
		FaceDataXMLFactory(const Ionflux::GeoUtils::XMLUtils::FaceDataXMLFactory& other);
        virtual ~FaceDataXMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::FaceData& target, const std::string& elementName
        = "") const;
        virtual Ionflux::GeoUtils::FaceData* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::FaceDataXMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::FaceDataXMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::FaceDataXMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/DeferredTransformXMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class DeferredTransformXMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        DeferredTransformXMLFactoryClassInfo();
        virtual ~DeferredTransformXMLFactoryClassInfo();
};

class DeferredTransformXMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        DeferredTransformXMLFactory();
		DeferredTransformXMLFactory(const Ionflux::GeoUtils::XMLUtils::DeferredTransformXMLFactory& other);
        virtual ~DeferredTransformXMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::DeferredTransform& target, const std::string& 
        elementName = "") const;
        virtual Ionflux::GeoUtils::DeferredTransform* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::DeferredTransformXMLFactory* copy() 
		const;
		static Ionflux::GeoUtils::XMLUtils::DeferredTransformXMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::DeferredTransformXMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/TransformableObjectXMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class TransformableObjectXMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TransformableObjectXMLFactoryClassInfo();
        virtual ~TransformableObjectXMLFactoryClassInfo();
};

class TransformableObjectXMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        TransformableObjectXMLFactory();
		TransformableObjectXMLFactory(const Ionflux::GeoUtils::XMLUtils::TransformableObjectXMLFactory& other);
        virtual ~TransformableObjectXMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::TransformableObject& target, const std::string& 
        elementName = "") const;
        virtual Ionflux::GeoUtils::TransformableObject* createObject() 
        const;
		virtual Ionflux::GeoUtils::XMLUtils::TransformableObjectXMLFactory* 
		copy() const;
		static Ionflux::GeoUtils::XMLUtils::TransformableObjectXMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::TransformableObjectXMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/Vertex2XMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class Vertex2XMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vertex2XMLFactoryClassInfo();
        virtual ~Vertex2XMLFactoryClassInfo();
};

class Vertex2XMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        Vertex2XMLFactory();
		Vertex2XMLFactory(const Ionflux::GeoUtils::XMLUtils::Vertex2XMLFactory& other);
        virtual ~Vertex2XMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Vertex2& target, const std::string& elementName 
        = "") const;
        virtual Ionflux::GeoUtils::Vertex2* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::Vertex2XMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::Vertex2XMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::Vertex2XMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/Vertex3XMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class Vertex3XMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vertex3XMLFactoryClassInfo();
        virtual ~Vertex3XMLFactoryClassInfo();
};

class Vertex3XMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        Vertex3XMLFactory();
		Vertex3XMLFactory(const Ionflux::GeoUtils::XMLUtils::Vertex3XMLFactory& other);
        virtual ~Vertex3XMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Vertex3& target, const std::string& elementName 
        = "") const;
        virtual Ionflux::GeoUtils::Vertex3* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::Vertex3XMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::Vertex3XMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::Vertex3XMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/Vertex3SetXMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class Vertex3SetXMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vertex3SetXMLFactoryClassInfo();
        virtual ~Vertex3SetXMLFactoryClassInfo();
};

class Vertex3SetXMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        Vertex3SetXMLFactory();
		Vertex3SetXMLFactory(const Ionflux::GeoUtils::XMLUtils::Vertex3SetXMLFactory& other);
        virtual ~Vertex3SetXMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Vertex3Set& target, const std::string& 
        elementName = "") const;
        virtual Ionflux::GeoUtils::Vertex3Set* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::Vertex3SetXMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::Vertex3SetXMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::Vertex3SetXMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/FaceXMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class FaceXMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FaceXMLFactoryClassInfo();
        virtual ~FaceXMLFactoryClassInfo();
};

class FaceXMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        FaceXMLFactory();
		FaceXMLFactory(const Ionflux::GeoUtils::XMLUtils::FaceXMLFactory& other);
        virtual ~FaceXMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Face& target, const std::string& elementName = 
        "") const;
        virtual Ionflux::GeoUtils::Face* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::FaceXMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::FaceXMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::FaceXMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/EdgeXMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class EdgeXMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        EdgeXMLFactoryClassInfo();
        virtual ~EdgeXMLFactoryClassInfo();
};

class EdgeXMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        EdgeXMLFactory();
		EdgeXMLFactory(const Ionflux::GeoUtils::XMLUtils::EdgeXMLFactory& other);
        virtual ~EdgeXMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Edge& target, const std::string& elementName = 
        "") const;
        virtual Ionflux::GeoUtils::Edge* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::EdgeXMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::EdgeXMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::EdgeXMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/MeshXMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class MeshXMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MeshXMLFactoryClassInfo();
        virtual ~MeshXMLFactoryClassInfo();
};

class MeshXMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        MeshXMLFactory();
		MeshXMLFactory(const Ionflux::GeoUtils::XMLUtils::MeshXMLFactory& other);
        virtual ~MeshXMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Mesh& target, const std::string& elementName = 
        "") const;
        virtual Ionflux::GeoUtils::Mesh* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::MeshXMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::MeshXMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::MeshXMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/TransformableGroupXMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class TransformableGroupXMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TransformableGroupXMLFactoryClassInfo();
        virtual ~TransformableGroupXMLFactoryClassInfo();
};

class TransformableGroupXMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        TransformableGroupXMLFactory();
		TransformableGroupXMLFactory(const Ionflux::GeoUtils::XMLUtils::TransformableGroupXMLFactory& other);
        virtual ~TransformableGroupXMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::TransformableGroup& target, const std::string& 
        elementName = "") const;
        virtual Ionflux::GeoUtils::TransformableGroup* createObject() 
        const;
		virtual Ionflux::GeoUtils::XMLUtils::TransformableGroupXMLFactory* copy()
		const;
		static Ionflux::GeoUtils::XMLUtils::TransformableGroupXMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::TransformableGroupXMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/Polygon3XMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class Polygon3XMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Polygon3XMLFactoryClassInfo();
        virtual ~Polygon3XMLFactoryClassInfo();
};

class Polygon3XMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        Polygon3XMLFactory();
		Polygon3XMLFactory(const Ionflux::GeoUtils::XMLUtils::Polygon3XMLFactory& other);
        virtual ~Polygon3XMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Polygon3& target, const std::string& elementName
        = "") const;
        virtual Ionflux::GeoUtils::Polygon3* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::Polygon3XMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::Polygon3XMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::Polygon3XMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/Polygon3SetXMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class Polygon3SetXMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Polygon3SetXMLFactoryClassInfo();
        virtual ~Polygon3SetXMLFactoryClassInfo();
};

class Polygon3SetXMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        Polygon3SetXMLFactory();
		Polygon3SetXMLFactory(const Ionflux::GeoUtils::XMLUtils::Polygon3SetXMLFactory& other);
        virtual ~Polygon3SetXMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Polygon3Set& target, const std::string& 
        elementName = "") const;
        virtual Ionflux::GeoUtils::Polygon3Set* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::Polygon3SetXMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::Polygon3SetXMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::Polygon3SetXMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/Shape3XMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class Shape3XMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Shape3XMLFactoryClassInfo();
        virtual ~Shape3XMLFactoryClassInfo();
};

class Shape3XMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        Shape3XMLFactory();
		Shape3XMLFactory(const Ionflux::GeoUtils::XMLUtils::Shape3XMLFactory& other);
        virtual ~Shape3XMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Shape3& target, const std::string& elementName =
        "") const;
        virtual Ionflux::GeoUtils::Shape3* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::Shape3XMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::Shape3XMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::Shape3XMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%{
#include "geoutils/xmlio/CameraXMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class CameraXMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        CameraXMLFactoryClassInfo();
        virtual ~CameraXMLFactoryClassInfo();
};

class CameraXMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        CameraXMLFactory();
		CameraXMLFactory(const Ionflux::GeoUtils::XMLUtils::CameraXMLFactory& other);
        virtual ~CameraXMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::Camera& target, const std::string& elementName =
        "") const;
        virtual Ionflux::GeoUtils::Camera* createObject() const;
		virtual Ionflux::GeoUtils::XMLUtils::CameraXMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::CameraXMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::CameraXMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
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

