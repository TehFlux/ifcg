%include <std_string.i>
%include <std_map.i>
%include <std_set.i>
%include <std_pair.i>
%include <std_vector.i>
%module IFMapping
%import "ifobject/ifobject.i"
%{
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

namespace Mapping
{

// types.hpp

typedef double MappingValue;
typedef Ionflux::ObjectBase::DoubleVector MappingValueVector;
typedef unsigned int CoordinateID;

struct Range
{
	double lower;
	double upper;
};

typedef std::vector<Range> RangeVector;

class Point;
class Mapping;
class Piece;
class BezierCurve;
class BezierSpline;
class BezierSplineKey;
class PointMapping;

typedef std::vector<Ionflux::Mapping::Point*> PointVector;
typedef std::vector<Ionflux::Mapping::Mapping*> MappingVector;
typedef std::vector<Ionflux::Mapping::Piece*> PieceVector;
typedef std::vector<Ionflux::Mapping::PointMapping*> PointMappingVector;

struct Sample
{
    Ionflux::Mapping::MappingValue x;
    Ionflux::Mapping::MappingValue y;
    Ionflux::Mapping::MappingValue s;
    bool valid;
};

typedef std::vector<Ionflux::Mapping::BezierCurve*> BezierCurveVector;
typedef std::vector<Ionflux::Mapping::BezierSpline*> BezierSplineVector;
typedef std::vector<Ionflux::Mapping::BezierSplineKey*> BezierSplineKeyVector;
typedef std::vector<Ionflux::Mapping::Segment*> SegmentVector;

typedef int SamplingMode;
typedef int SearchMethod;

// constants.hpp

const Ionflux::Mapping::CoordinateID C_X = 0;
const Ionflux::Mapping::CoordinateID C_Y = 1;
const Ionflux::Mapping::CoordinateID C_Z = 2;

const Ionflux::Mapping::Range DEFAULT_CLAMP_RANGE = { 0., 1. };

const unsigned int MAX_ITERATIONS = 10000;

const Ionflux::Mapping::MappingValue DEFAULT_TOLERANCE = 1e-6;

const Ionflux::Mapping::SamplingMode SAMPLING_MODE_PARAM = 0;
const Ionflux::Mapping::SamplingMode SAMPLING_MODE_ARC_LENGTH = 1;
const Ionflux::Mapping::SamplingMode SAMPLING_MODE_POINT_COORD_X = 2;
const Ionflux::Mapping::SamplingMode SAMPLING_MODE_POINT_COORD_Y = 3;
const Ionflux::Mapping::SamplingMode SAMPLING_MODE_POINT_COORD_Z = 4;

const Ionflux::Mapping::SearchMethod SEARCH_LINEAR = 0;
const Ionflux::Mapping::SearchMethod SEARCH_BINARY = 1;

// utils.hpp

class BezierSpline;
class PointSet;

bool lt(Ionflux::Mapping::MappingValue v0, 
    Ionflux::Mapping::MappingValue v1, 
    Ionflux::Mapping::MappingValue t = Ionflux::Mapping::DEFAULT_TOLERANCE);
bool gt(Ionflux::Mapping::MappingValue v0, 
    Ionflux::Mapping::MappingValue v1, 
    Ionflux::Mapping::MappingValue t = Ionflux::Mapping::DEFAULT_TOLERANCE);
bool eq(Ionflux::Mapping::MappingValue v0, 
    Ionflux::Mapping::MappingValue v1, 
    Ionflux::Mapping::MappingValue t = Ionflux::Mapping::DEFAULT_TOLERANCE);
bool ltOrEq(Ionflux::Mapping::MappingValue v0, 
    Ionflux::Mapping::MappingValue v1, 
    Ionflux::Mapping::MappingValue t = Ionflux::Mapping::DEFAULT_TOLERANCE);
bool gtOrEq(Ionflux::Mapping::MappingValue v0, 
    Ionflux::Mapping::MappingValue v1, 
    Ionflux::Mapping::MappingValue t = Ionflux::Mapping::DEFAULT_TOLERANCE);

std::string coordToString(Ionflux::Mapping::CoordinateID coord);
std::string getSamplingModeString(Ionflux::Mapping::SamplingMode 
    samplingMode);
double clamp(double v, const Ionflux::Mapping::Range& r = 
    Ionflux::Mapping::DEFAULT_CLAMP_RANGE);
double wrap(double v, const Ionflux::Mapping::Range& r = 
    Ionflux::Mapping::DEFAULT_CLAMP_RANGE);
bool isInRange(const Ionflux::Mapping::Range& r, double v);

void updateSample(const Ionflux::Mapping::Sample current, 
    Ionflux::Mapping::Sample& previous, 
    const Ionflux::Mapping::Sample& other);

double sign(double v);
Ionflux::Mapping::MappingValue bernstein(
    const Ionflux::Mapping::MappingValueVector& c, 
    Ionflux::Mapping::MappingValue t, unsigned int n, unsigned int i);
Ionflux::Mapping::Point bezier(Ionflux::Mapping::MappingValue t, 
    const Ionflux::Mapping::PointVector& controlPoints);
void explode(const std::string& bytes, const std::string& splitString, 
    Ionflux::ObjectBase::StringVector& result);
void extractSVGPoint(const std::string& rawData, 
    Ionflux::Mapping::Point& target);
void extractSVGControlPoints(const std::string& rawData, 
    Ionflux::Mapping::PointSet& target);

void initRandom();
void initRandom(unsigned int seed);
void disposeRandom();
unsigned int getRandomInt();
double getRandomDouble();
double getRandomDoubleExc();
double getRandomNorm(double mean = 0., double stdDev = 1.);
Ionflux::Mapping::Point getRandomPoint();
Ionflux::Mapping::Point getRandomPointExc();
Ionflux::Mapping::Point getRandomPointNorm(double meanX = 0., 
    double stdDevX = 1., double meanY = 0., 
    double stdDevY = 1., double meanZ = 0., 
    double stdDevZ = 1.);

std::string defaultStr(const std::string& source, 
    const std::string& d = "<none>");

// xmlutils.hpp

std::string getAttrValue(const std::string& fileName, 
    const std::string& elementName, const std::string& elementID, 
    const std::string& attrName);
void getAttrValues(const std::string& fileName, 
    const std::string& elementName, const std::string& attrName, 
    const Ionflux::ObjectBase::StringVector& elementIDs, 
    Ionflux::ObjectBase::StringVector& target);
void getSVGBezierSplineFrames(const std::string& fileName, 
    const Ionflux::ObjectBase::StringVector& elementIDs, 
    Ionflux::Mapping::AnimatedSpline& target);

}

}

$Piece
$Point
$PointSet
$Mapping
$MappingSet
$ChainableMapping
$PointMapping
$PointSample
$Segment
$EvalCoord
$PointMappingSet
$Constant
$Linear
$Cubic
$Rescale
$InverseFalloff
$Piecewise
$Multiply
$LinearCombination
$Chain
$Power
$Exp
$Sin
$Cos
$Tan
$ArcSin
$ArcCos
$ArcTan
$Polynomial
$Random
$RandomNorm
$RandomDensity
$Count
$Lookup
$Accept
$BezierCurve
$BezierSpline
$PointCoord
$BezierSplineKey
$AnimatedSpline
$RootFinder
$BisectionRootFinder
$SecantRootFinder
$DekkerRootFinder
$BrentLinearRootFinder
$ArcLength

$PointXMLFactory
$PointSetXMLFactory
$PointMappingXMLFactory
$BezierCurveXMLFactory
$BezierSplineXMLFactory
$PointSampleXMLFactory
$SegmentXMLFactory

%template(MappingVector) std::vector<Ionflux::Mapping::Mapping*>;
%template(PieceVector) std::vector<Ionflux::Mapping::Piece*>;
%template(PointVector) std::vector<Ionflux::Mapping::Point*>;
%template(RangeVector) std::vector<Ionflux::Mapping::Range>;
%template(BezierCurveVector) std::vector<Ionflux::Mapping::BezierCurve*>;
%template(BezierSplineVector) std::vector<Ionflux::Mapping::BezierSpline*>;
%template(BezierSplineKeyVector) std::vector<Ionflux::Mapping::BezierSplineKey*>;
%template(PointMappingVector) std::vector<Ionflux::Mapping::PointMapping*>;
%template(SegmentVector) std::vector<Ionflux::Mapping::Segment*>;

