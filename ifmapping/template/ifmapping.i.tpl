%include <std_string.i>
%include <std_map.i>
%include <std_set.i>
%include <std_pair.i>
%include <std_vector.i>
%module IFMapping
%import "ifobject/ifobject.i"
%{
#include "ifmapping/ifmapping.hpp"
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

// constants.hpp

const Ionflux::Mapping::CoordinateID C_X = 0;
const Ionflux::Mapping::CoordinateID C_Y = 1;
const Ionflux::Mapping::CoordinateID C_Z = 2;

const Ionflux::Mapping::Range DEFAULT_CLAMP_RANGE = { 0., 1. };

const unsigned int MAX_ITERATIONS = 10000;

const Ionflux::Mapping::MappingValue DEFAULT_TOLERANCE = 1e-6;

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
$EvalCoord

namespace Ionflux
{

namespace Mapping
{

class PointMappingSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PointMappingSetClassInfo();
        virtual ~PointMappingSetClassInfo();
};

class PointMappingSet
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        PointMappingSet();
		PointMappingSet(const Ionflux::Mapping::PointMappingSet& other);
        PointMappingSet(const Ionflux::Mapping::PointMappingVector& 
        initMappings);
        virtual ~PointMappingSet();
        virtual void addMappings(const 
        Ionflux::Mapping::PointMappingVector& newMappings);
        virtual std::string getString() const;
		static Ionflux::Mapping::PointMappingSet* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::PointMappingSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumMappings() const;
        virtual Ionflux::Mapping::PointMapping* getMapping(unsigned int 
        elementIndex = 0) const;
		virtual int findMapping(Ionflux::Mapping::PointMapping* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::PointMapping*>& 
        getMappings();
        virtual void addMapping(Ionflux::Mapping::PointMapping* 
        addElement);        
        virtual void removeMapping(Ionflux::Mapping::PointMapping* 
        removeElement);
		virtual void removeMappingIndex(unsigned int removeIndex);
        virtual void clearMappings();
};

class ConstantClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ConstantClassInfo();
        virtual ~ConstantClassInfo();
};

class Constant
: public Ionflux::Mapping::Mapping
{
    public:
        
        Constant();
		Constant(const Ionflux::Mapping::Constant& other);
        Constant(Ionflux::Mapping::MappingValue initConstValue);
        virtual ~Constant();
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::Constant* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Constant* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setConstValue(Ionflux::Mapping::MappingValue 
        newConstValue);
        virtual Ionflux::Mapping::MappingValue getConstValue() const;
};

}

}

$Linear

namespace Ionflux
{

namespace Mapping
{

class CubicClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        CubicClassInfo();
        virtual ~CubicClassInfo();
};

class Cubic
: public Ionflux::Mapping::Linear
{
    public:
        
        Cubic();
		Cubic(const Ionflux::Mapping::Cubic& other);
        Cubic(Ionflux::Mapping::MappingValue initLower, 
        Ionflux::Mapping::MappingValue initUpper);
        virtual ~Cubic();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::Cubic* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Cubic* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

class RescaleClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        RescaleClassInfo();
        virtual ~RescaleClassInfo();
};

class Rescale
: public Ionflux::Mapping::Mapping
{
    public:
        
        Rescale();
		Rescale(const Ionflux::Mapping::Rescale& other);
        Rescale(Ionflux::Mapping::Mapping* initFunc, const 
        Ionflux::Mapping::MappingValueVector* initArgs = 0);
        virtual ~Rescale();
        virtual void addArgs(const Ionflux::Mapping::MappingValueVector& 
        newArgs);
        virtual void findExtremePoints();
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::Rescale* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
        virtual Ionflux::Mapping::Mapping* getFunc() const;        
        virtual unsigned int getNumArgs() const;
        virtual Ionflux::Mapping::MappingValue getArg(unsigned int 
        elementIndex = 0) const;
		virtual int findArg(Ionflux::Mapping::MappingValue needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::MappingValue>& getArgs();
        virtual void addArg(Ionflux::Mapping::MappingValue addElement);        
        virtual void removeArg(Ionflux::Mapping::MappingValue 
        removeElement);
		virtual void removeArgIndex(unsigned int removeIndex);
        virtual void clearArgs();
};

class InverseFalloffClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        InverseFalloffClassInfo();
        virtual ~InverseFalloffClassInfo();
};

class InverseFalloff
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        InverseFalloff();
		InverseFalloff(const Ionflux::Mapping::InverseFalloff& other);
        InverseFalloff(double initExponent);
        virtual ~InverseFalloff();
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::InverseFalloff* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::InverseFalloff* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setExponent(Ionflux::Mapping::MappingValue 
        newExponent);
        virtual Ionflux::Mapping::MappingValue getExponent() const;
};

class PiecewiseClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PiecewiseClassInfo();
        virtual ~PiecewiseClassInfo();
};

class Piecewise
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        Piecewise();
		Piecewise(const Ionflux::Mapping::Piecewise& other);
        Piecewise(const Ionflux::Mapping::PieceVector& initPieces, 
        Ionflux::Mapping::Mapping* initFunc = 0, 
        Ionflux::Mapping::MappingValue initScale = 1., 
        Ionflux::Mapping::MappingValue initOffset = 0.);
        virtual ~Piecewise();
        virtual void addPieces(const Ionflux::Mapping::PieceVector& 
        newPieces);
        virtual Ionflux::Mapping::Piece 
        getPieceForT(Ionflux::Mapping::MappingValue t, 
        Ionflux::Mapping::MappingValue tolerance = 
        Ionflux::Mapping::DEFAULT_TOLERANCE) const;
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
        static Ionflux::Mapping::Piecewise* 
        sawtooth(Ionflux::Mapping::MappingValue freq = 1., 
        Ionflux::Mapping::MappingValue ampMin = 0., 
        Ionflux::Mapping::MappingValue ampMax = 1.);
        static Ionflux::Mapping::Piecewise* 
        step(Ionflux::Mapping::MappingValue numSteps = 1., 
        Ionflux::Mapping::MappingValue minValue = 0., 
        Ionflux::Mapping::MappingValue maxValue = 1.);
		static Ionflux::Mapping::Piecewise* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::Mapping::Piecewise* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);        
        virtual unsigned int getNumPieces() const;
        virtual Ionflux::Mapping::Piece* getPiece(unsigned int elementIndex
        = 0) const;
		virtual int findPiece(Ionflux::Mapping::Piece* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::Piece*>& getPieces();
        virtual void addPiece(Ionflux::Mapping::Piece* addElement);        
        virtual void removePiece(Ionflux::Mapping::Piece* removeElement);
		virtual void removePieceIndex(unsigned int removeIndex);
        virtual void clearPieces();
};

class MultiplyClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MultiplyClassInfo();
        virtual ~MultiplyClassInfo();
};

class Multiply
: public Ionflux::Mapping::Mapping
{
    public:
        
        Multiply();
		Multiply(const Ionflux::Mapping::Multiply& other);
        Multiply(const Ionflux::Mapping::MappingVector& initFuncs);
        virtual ~Multiply();
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::Multiply* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Multiply* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);        
        virtual unsigned int getNumFuncs() const;
        virtual Ionflux::Mapping::Mapping* getFunc(unsigned int 
        elementIndex = 0) const;
		virtual int findFunc(Ionflux::Mapping::Mapping* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::Mapping*>& getFuncs();
        virtual void addFunc(Ionflux::Mapping::Mapping* addElement);        
        virtual void removeFunc(Ionflux::Mapping::Mapping* removeElement);
		virtual void removeFuncIndex(unsigned int removeIndex);
        virtual void clearFuncs();
};


class LinearCombinationClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        LinearCombinationClassInfo();
        virtual ~LinearCombinationClassInfo();
};

class LinearCombination
: public Ionflux::Mapping::Mapping
{
    public:
        
        LinearCombination();
		LinearCombination(const Ionflux::Mapping::LinearCombination& other);
        LinearCombination(const Ionflux::Mapping::PieceVector& initPieces);
        virtual ~LinearCombination();
        virtual void addPieces(const Ionflux::Mapping::PieceVector& 
        newPieces);
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::LinearCombination* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::LinearCombination* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumPieces() const;
        virtual Ionflux::Mapping::Piece* getPiece(unsigned int elementIndex
        = 0) const;
		virtual int findPiece(Ionflux::Mapping::Piece* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::Piece*>& getPieces();
        virtual void addPiece(Ionflux::Mapping::Piece* addElement);        
        virtual void removePiece(Ionflux::Mapping::Piece* removeElement);
		virtual void removePieceIndex(unsigned int removeIndex);
        virtual void clearPieces();
};

class ChainClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ChainClassInfo();
        virtual ~ChainClassInfo();
};

class Chain
: public Ionflux::Mapping::Mapping
{
    public:
        
        Chain();
		Chain(const Ionflux::Mapping::Chain& other);
        Chain(const Ionflux::Mapping::MappingVector& initFuncs);
        virtual ~Chain();
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::Chain* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Chain* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);        
        virtual unsigned int getNumFuncs() const;
        virtual Ionflux::Mapping::Mapping* getFunc(unsigned int 
        elementIndex = 0) const;
		virtual int findFunc(Ionflux::Mapping::Mapping* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::Mapping*>& getFuncs();
        virtual void addFunc(Ionflux::Mapping::Mapping* addElement);        
        virtual void removeFunc(Ionflux::Mapping::Mapping* removeElement);
		virtual void removeFuncIndex(unsigned int removeIndex);
        virtual void clearFuncs();
};

class PowerClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PowerClassInfo();
        virtual ~PowerClassInfo();
};

class Power
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        Power();
		Power(const Ionflux::Mapping::Power& other);
        Power(int initExponent, Ionflux::Mapping::MappingValue initScale = 
        1., Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~Power();
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::Power* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Power* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setExponent(int newExponent);
        virtual int getExponent() const;
};

class ExpClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ExpClassInfo();
        virtual ~ExpClassInfo();
};

class Exp
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        Exp();
		Exp(const Ionflux::Mapping::Exp& other);
        Exp(Ionflux::Mapping::MappingValue initScale, 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~Exp();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::Exp* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Exp* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

class SinClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SinClassInfo();
        virtual ~SinClassInfo();
};

class Sin
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        Sin();
		Sin(const Ionflux::Mapping::Sin& other);
        Sin(Ionflux::Mapping::MappingValue initScale, 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~Sin();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::Sin* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Sin* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

class CosClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        CosClassInfo();
        virtual ~CosClassInfo();
};

class Cos
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        Cos();
		Cos(const Ionflux::Mapping::Cos& other);
        Cos(Ionflux::Mapping::MappingValue initScale, 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~Cos();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::Cos* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Cos* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

class TanClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TanClassInfo();
        virtual ~TanClassInfo();
};

class Tan
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        Tan();
		Tan(const Ionflux::Mapping::Tan& other);
        Tan(Ionflux::Mapping::MappingValue initScale, 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~Tan();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::Tan* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Tan* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

class ArcSinClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ArcSinClassInfo();
        virtual ~ArcSinClassInfo();
};

class ArcSin
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        ArcSin();
		ArcSin(const Ionflux::Mapping::ArcSin& other);
        ArcSin(Ionflux::Mapping::MappingValue initScale, 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~ArcSin();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::ArcSin* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::ArcSin* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

class ArcCosClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ArcCosClassInfo();
        virtual ~ArcCosClassInfo();
};

class ArcCos
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        ArcCos();
		ArcCos(const Ionflux::Mapping::ArcCos& other);
        ArcCos(Ionflux::Mapping::MappingValue initScale, 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~ArcCos();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::ArcCos* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::ArcCos* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

class ArcTanClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ArcTanClassInfo();
        virtual ~ArcTanClassInfo();
};

class ArcTan
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        ArcTan();
		ArcTan(const Ionflux::Mapping::ArcTan& other);
        ArcTan(Ionflux::Mapping::MappingValue initScale, 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~ArcTan();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::ArcTan* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::ArcTan* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

class PolynomialClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PolynomialClassInfo();
        virtual ~PolynomialClassInfo();
};

class Polynomial
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        Polynomial();
		Polynomial(const Ionflux::Mapping::Polynomial& other);
        Polynomial(const Ionflux::Mapping::MappingValueVector& 
        initCoefficients, Ionflux::Mapping::MappingValue initScale = 1., 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~Polynomial();
        virtual void addCoefficients(const 
        Ionflux::Mapping::MappingValueVector& newCoefficients);
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::Polynomial* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::Polynomial* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumCoefficients() const;
        virtual Ionflux::Mapping::MappingValue getCoefficient(unsigned int 
        elementIndex = 0) const;
		virtual int findCoefficient(Ionflux::Mapping::MappingValue needle, 
		unsigned int occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::MappingValue>& 
        getCoefficients();
        virtual void addCoefficient(Ionflux::Mapping::MappingValue 
        addElement);        
        virtual void removeCoefficient(Ionflux::Mapping::MappingValue 
        removeElement);
		virtual void removeCoefficientIndex(unsigned int removeIndex);
        virtual void clearCoefficients();
};

class RandomClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        RandomClassInfo();
        virtual ~RandomClassInfo();
};

class Random
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        Random();
		Random(const Ionflux::Mapping::Random& other);
        Random(Ionflux::Mapping::MappingValue initScale, 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~Random();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::Random* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Random* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

class RandomNormClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        RandomNormClassInfo();
        virtual ~RandomNormClassInfo();
};

class RandomNorm
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        RandomNorm();
		RandomNorm(const Ionflux::Mapping::RandomNorm& other);
        RandomNorm(Ionflux::Mapping::MappingValue initMean, 
        Ionflux::Mapping::MappingValue initStdDev = 1., 
        Ionflux::Mapping::MappingValue initScale = 1., 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~RandomNorm();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::RandomNorm* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::RandomNorm* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setMean(Ionflux::Mapping::MappingValue newMean);
        virtual Ionflux::Mapping::MappingValue getMean() const;
        virtual void setStdDev(Ionflux::Mapping::MappingValue newStdDev);
        virtual Ionflux::Mapping::MappingValue getStdDev() const;
};

class RandomDensityClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        RandomDensityClassInfo();
        virtual ~RandomDensityClassInfo();
};

class RandomDensity
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        RandomDensity();
		RandomDensity(const Ionflux::Mapping::RandomDensity& other);
        RandomDensity(Ionflux::Mapping::Mapping* initFunc, 
        Ionflux::Mapping::MappingValue initMaxIters = MAX_ITERATIONS, 
        Ionflux::Mapping::MappingValue initScale = 1., 
        Ionflux::Mapping::MappingValue initOffset = 0.);
        virtual ~RandomDensity();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::RandomDensity* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::RandomDensity* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setMaxIters(unsigned int newMaxIters);
        virtual unsigned int getMaxIters() const;
};

}

}

$Count
$Lookup
$Accept
$BezierCurve
$BezierSpline
$PointCoord

namespace Ionflux
{

namespace Mapping
{

class BezierSplineKeyClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BezierSplineKeyClassInfo();
        virtual ~BezierSplineKeyClassInfo();
};

class BezierSplineKey
: public Ionflux::Mapping::BezierSpline
{
    public:
        
        BezierSplineKey();
		BezierSplineKey(const Ionflux::Mapping::BezierSplineKey& other);
        BezierSplineKey(Ionflux::Mapping::MappingValue initT);
        BezierSplineKey(const Ionflux::Mapping::BezierSpline& initSpline, 
        Ionflux::Mapping::MappingValue initT);
        virtual ~BezierSplineKey();
        virtual std::string getString() const;
		static Ionflux::Mapping::BezierSplineKey* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::BezierSplineKey* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setT(Ionflux::Mapping::MappingValue newT);
        virtual Ionflux::Mapping::MappingValue getT() const;
};

class AnimatedSplineClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        AnimatedSplineClassInfo();
        virtual ~AnimatedSplineClassInfo();
};

class AnimatedSpline
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        AnimatedSpline();
		AnimatedSpline(const Ionflux::Mapping::AnimatedSpline& other);
        virtual ~AnimatedSpline();
        virtual void getShape(Ionflux::Mapping::MappingValue t, 
        Ionflux::Mapping::BezierSpline& target) const;
        virtual Ionflux::Mapping::BezierSpline 
        call(Ionflux::Mapping::MappingValue value) const;
        virtual std::string getString() const;        
        virtual unsigned int getNumKeys() const;
        virtual Ionflux::Mapping::BezierSplineKey* getKey(unsigned int 
        elementIndex = 0) const;
		virtual int findKey(Ionflux::Mapping::BezierSplineKey* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::BezierSplineKey*>& getKeys();
        virtual void addKey(Ionflux::Mapping::BezierSplineKey* addElement);        
        virtual void removeKey(Ionflux::Mapping::BezierSplineKey* 
        removeElement);
		virtual void removeKeyIndex(unsigned int removeIndex);
        virtual void clearKeys();
};

class RootFinderClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        RootFinderClassInfo();
        virtual ~RootFinderClassInfo();
};

class RootFinder
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        RootFinder();
		RootFinder(const Ionflux::Mapping::RootFinder& other);
        virtual ~RootFinder();
        virtual Ionflux::Mapping::MappingValue 
        compareSigns(Ionflux::Mapping::MappingValue a, 
        Ionflux::Mapping::MappingValue b) const;
        virtual void findStartIntervals(Ionflux::Mapping::RangeVector& 
        target, unsigned int samples = 101, Ionflux::Mapping::MappingValue 
        a = 0., Ionflux::Mapping::MappingValue b = 1.) const;
        virtual Ionflux::Mapping::Range findStartInterval(unsigned int 
        samples = 101, Ionflux::Mapping::MappingValue a = 0., 
        Ionflux::Mapping::MappingValue b = 1.) const;
        virtual Ionflux::Mapping::MappingValue 
        operator()(Ionflux::Mapping::MappingValue a = 0., 
        Ionflux::Mapping::MappingValue b = 0., 
        Ionflux::Mapping::MappingValue delta = 0.0001) const;
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        findRoot(Ionflux::Mapping::MappingValue a = 0., 
        Ionflux::Mapping::MappingValue b = 0., 
        Ionflux::Mapping::MappingValue delta = 0.0001) const = 0;
		static Ionflux::Mapping::RootFinder* 
		upcast(Ionflux::ObjectBase::IFObject* other);
        virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
        virtual Ionflux::Mapping::Mapping* getFunc() const;
};

class BisectionRootFinderClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BisectionRootFinderClassInfo();
        virtual ~BisectionRootFinderClassInfo();
};

class BisectionRootFinder
: public Ionflux::Mapping::RootFinder
{
    public:
        
        BisectionRootFinder();
		BisectionRootFinder(const Ionflux::Mapping::BisectionRootFinder& other);
        virtual ~BisectionRootFinder();
        virtual Ionflux::Mapping::MappingValue 
        findRoot(Ionflux::Mapping::MappingValue a = 0., 
        Ionflux::Mapping::MappingValue b = 0., 
        Ionflux::Mapping::MappingValue delta = 0.0001) const;
        virtual Ionflux::Mapping::MappingValue 
        findRoot(Ionflux::Mapping::MappingValue a, 
        Ionflux::Mapping::MappingValue b, Ionflux::Mapping::MappingValue 
        delta, unsigned int samples) const;
        virtual std::string getString() const;
		static Ionflux::Mapping::BisectionRootFinder* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::BisectionRootFinder* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

class SecantRootFinderClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SecantRootFinderClassInfo();
        virtual ~SecantRootFinderClassInfo();
};

class SecantRootFinder
: public Ionflux::Mapping::RootFinder
{
    public:
        
        SecantRootFinder();
		SecantRootFinder(const Ionflux::Mapping::SecantRootFinder& other);
        virtual ~SecantRootFinder();
        virtual Ionflux::Mapping::MappingValue 
        findRoot(Ionflux::Mapping::MappingValue a = 0., 
        Ionflux::Mapping::MappingValue b = 0., 
        Ionflux::Mapping::MappingValue delta = 0.0001) const;
        virtual Ionflux::Mapping::MappingValue 
        findRoot(Ionflux::Mapping::MappingValue a, 
        Ionflux::Mapping::MappingValue b, Ionflux::Mapping::MappingValue 
        delta, unsigned int maxIters, unsigned int i = 0) const;
        virtual std::string getString() const;
		static Ionflux::Mapping::SecantRootFinder* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::SecantRootFinder* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

class DekkerRootFinderClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        DekkerRootFinderClassInfo();
        virtual ~DekkerRootFinderClassInfo();
};

class DekkerRootFinder
: public Ionflux::Mapping::RootFinder
{
    public:
        
        DekkerRootFinder();
		DekkerRootFinder(const Ionflux::Mapping::DekkerRootFinder& other);
        virtual ~DekkerRootFinder();
        virtual Ionflux::Mapping::MappingValue 
        findRoot(Ionflux::Mapping::MappingValue a = 0., 
        Ionflux::Mapping::MappingValue b = 0., 
        Ionflux::Mapping::MappingValue delta = 0.0001) const;
        virtual Ionflux::Mapping::MappingValue 
        findRoot(Ionflux::Mapping::MappingValue a, 
        Ionflux::Mapping::MappingValue b, Ionflux::Mapping::MappingValue 
        delta, unsigned int samples, unsigned int maxIters = 50, unsigned 
        int i = 0) const;
        virtual std::string getString() const;
		static Ionflux::Mapping::DekkerRootFinder* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::DekkerRootFinder* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

class BrentLinearRootFinderClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BrentLinearRootFinderClassInfo();
        virtual ~BrentLinearRootFinderClassInfo();
};

class BrentLinearRootFinder
: public Ionflux::Mapping::RootFinder
{
    public:
        
        BrentLinearRootFinder();
		BrentLinearRootFinder(const Ionflux::Mapping::BrentLinearRootFinder& other);
        virtual ~BrentLinearRootFinder();
        virtual Ionflux::Mapping::MappingValue 
        findRoot(Ionflux::Mapping::MappingValue a = 0., 
        Ionflux::Mapping::MappingValue b = 0., 
        Ionflux::Mapping::MappingValue delta = 0.0001) const;
        virtual Ionflux::Mapping::MappingValue 
        findRoot(Ionflux::Mapping::MappingValue a, 
        Ionflux::Mapping::MappingValue b, Ionflux::Mapping::MappingValue 
        delta, Ionflux::Mapping::MappingValue tr0, unsigned int samples = 
        101, unsigned int maxIters = 50, unsigned int i = 0, bool 
        forceBisection = false, Ionflux::Mapping::MappingValue bPrev = 0.) 
        const;
        virtual std::string getString() const;
		static Ionflux::Mapping::BrentLinearRootFinder* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::BrentLinearRootFinder* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

%template(MappingVector) std::vector<Ionflux::Mapping::Mapping*>;
%template(PieceVector) std::vector<Ionflux::Mapping::Piece*>;
%template(PointVector) std::vector<Ionflux::Mapping::Point*>;
%template(RangeVector) std::vector<Ionflux::Mapping::Range>;
%template(BezierCurveVector) std::vector<Ionflux::Mapping::BezierCurve*>;
%template(BezierSplineVector) std::vector<Ionflux::Mapping::BezierSpline*>;
%template(BezierSplineKeyVector) std::vector<Ionflux::Mapping::BezierSplineKey*>;
%template(PointMappingVector) std::vector<Ionflux::Mapping::PointMapping*>;

