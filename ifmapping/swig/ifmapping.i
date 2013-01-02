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
        $function
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


%{
#include "ifmapping/Piece.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class Mapping;

class PieceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PieceClassInfo();
        virtual ~PieceClassInfo();
};

class Piece
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Piece();
		Piece(const Ionflux::Mapping::Piece& other);
        Piece(Ionflux::Mapping::Mapping* initMapping, 
        Ionflux::Mapping::MappingValue initParam = 0.);
        virtual ~Piece();
        virtual std::string getString() const;
        static Ionflux::Mapping::Piece* create(Ionflux::Mapping::Mapping* 
        initMapping, Ionflux::Mapping::MappingValue initParam);
        static void createPieces(const Ionflux::Mapping::PointSet& points, 
        Ionflux::Mapping::PieceVector& target, const 
        Ionflux::Mapping::Point& offset = Ionflux::Mapping::Point::ORIGIN, 
        const Ionflux::Mapping::Point& scale = 
        Ionflux::Mapping::Point::ONES, bool addConstant = true);
		virtual Ionflux::Mapping::Piece* copy() const;
		static Ionflux::Mapping::Piece* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Piece* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setMapping(Ionflux::Mapping::Mapping* newMapping);
        virtual Ionflux::Mapping::Mapping* getMapping() const;
        virtual void setParam(Ionflux::Mapping::MappingValue newParam);
        virtual Ionflux::Mapping::MappingValue getParam() const;
};

}

}


%{
#include "ifmapping/Point.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class PointClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PointClassInfo();
        virtual ~PointClassInfo();
};

class Point
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Mapping::Point ORIGIN;
		static const Ionflux::Mapping::Point DEFAULT_STD_DEV;
		static const Ionflux::Mapping::Point ONES;
        
        Point();
		Point(const Ionflux::Mapping::Point& other);
        Point(Ionflux::Mapping::MappingValue initX, 
        Ionflux::Mapping::MappingValue initY, 
        Ionflux::Mapping::MappingValue initZ);
        Point(const Ionflux::ObjectBase::DoubleVector& initCoords);
        virtual ~Point();
        virtual void setCoords(const Ionflux::ObjectBase::DoubleVector& 
        newCoords);
        virtual void getCoords(Ionflux::ObjectBase::DoubleVector& target) 
        const;
        virtual Ionflux::Mapping::MappingValue getCoord(int index) const;
        virtual void setCoord(int index, Ionflux::Mapping::MappingValue 
        value);
        virtual Ionflux::Mapping::Point interpolate(const 
        Ionflux::Mapping::Point& other, Ionflux::Mapping::MappingValue t) 
        const;
        virtual Ionflux::Mapping::Point operator+(const 
        Ionflux::Mapping::Point& other) const;
        virtual Ionflux::Mapping::Point operator*(const 
        Ionflux::Mapping::Point& other) const;
        virtual bool operator==(const Ionflux::Mapping::Point& other) 
        const;
        virtual bool operator!=(const Ionflux::Mapping::Point& other) 
        const;
        static Ionflux::Mapping::Point getRandom();
        static Ionflux::Mapping::Point getRandomNorm(const 
        Ionflux::Mapping::Point& mean = Ionflux::Mapping::Point::ORIGIN, 
        const Ionflux::Mapping::Point& stdDev = 
        Ionflux::Mapping::Point::DEFAULT_STD_DEV);
        virtual std::string getString() const;
		virtual Ionflux::Mapping::Point* copy() const;
		static Ionflux::Mapping::Point* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Point* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setX(Ionflux::Mapping::MappingValue newX);
        virtual Ionflux::Mapping::MappingValue getX() const;
        virtual void setY(Ionflux::Mapping::MappingValue newY);
        virtual Ionflux::Mapping::MappingValue getY() const;
        virtual void setZ(Ionflux::Mapping::MappingValue newZ);
        virtual Ionflux::Mapping::MappingValue getZ() const;
};

}

}


namespace Ionflux
{

namespace Mapping
{

class PointSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PointSetClassInfo();
        virtual ~PointSetClassInfo();
};

class PointSet
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        PointSet();
		PointSet(const Ionflux::Mapping::PointSet& other);
        PointSet(const Ionflux::Mapping::PointVector& initPoints);
        virtual ~PointSet();
        virtual void addPoints(const Ionflux::Mapping::PointVector& 
        newPoints);
        virtual void addPoints(const Ionflux::Mapping::PointSet& other);
        virtual std::string getString() const;
		static Ionflux::Mapping::PointSet* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::PointSet* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);        
        virtual unsigned int getNumPoints() const;
        virtual Ionflux::Mapping::Point* getPoint(unsigned int elementIndex
        = 0) const;
		virtual int findPoint(Ionflux::Mapping::Point* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::Point*>& getPoints();
        virtual void addPoint(Ionflux::Mapping::Point* addElement);        
        virtual void removePoint(Ionflux::Mapping::Point* removeElement);
		virtual void removePointIndex(unsigned int removeIndex);
        virtual void clearPoints();
};

class MappingSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MappingSetClassInfo();
        virtual ~MappingSetClassInfo();
};

class MappingSet
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        MappingSet();
		MappingSet(const Ionflux::Mapping::MappingSet& other);
        MappingSet(const Ionflux::Mapping::MappingVector& initMappings);
        virtual ~MappingSet();
        virtual void addMappings(const Ionflux::Mapping::MappingVector& 
        newMappings);
        virtual std::string getString() const;
		static Ionflux::Mapping::MappingSet* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::MappingSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumMappings() const;
        virtual Ionflux::Mapping::Mapping* getMapping(unsigned int 
        elementIndex = 0) const;
		virtual int findMapping(Ionflux::Mapping::Mapping* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::Mapping*>& getMappings();
        virtual void addMapping(Ionflux::Mapping::Mapping* addElement);        
        virtual void removeMapping(Ionflux::Mapping::Mapping* 
        removeElement);
		virtual void removeMappingIndex(unsigned int removeIndex);
        virtual void clearMappings();
};

}

}


%{
#include "ifmapping/Mapping.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class MappingClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MappingClassInfo();
        virtual ~MappingClassInfo();
};

class Mapping
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Mapping();
        virtual ~Mapping();
        virtual Ionflux::Mapping::MappingValue 
        operator()(Ionflux::Mapping::MappingValue value) const;
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const = 0;
        virtual Ionflux::Mapping::Sample 
        sample(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::Mapping* upcast(Ionflux::ObjectBase::IFObject* 
		other);
};

}

}


%{
#include "ifmapping/ChainableMapping.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class ChainableMappingClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ChainableMappingClassInfo();
        virtual ~ChainableMappingClassInfo();
};

class ChainableMapping
: public Ionflux::Mapping::Mapping
{
    public:
        
        ChainableMapping();
		ChainableMapping(const Ionflux::Mapping::ChainableMapping& other);
        ChainableMapping(Ionflux::Mapping::Mapping* initFunc, 
        Ionflux::Mapping::MappingValue initScale = 1., 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::MappingValue initResultScale = 1., 
        Ionflux::Mapping::MappingValue initResultOffset = 0.);
        virtual ~ChainableMapping();
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const = 0;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const;
		static Ionflux::Mapping::ChainableMapping* 
		upcast(Ionflux::ObjectBase::IFObject* other);
        virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
        virtual Ionflux::Mapping::Mapping* getFunc() const;
        virtual void setScale(Ionflux::Mapping::MappingValue newScale);
        virtual Ionflux::Mapping::MappingValue getScale() const;
        virtual void setOffset(Ionflux::Mapping::MappingValue newOffset);
        virtual Ionflux::Mapping::MappingValue getOffset() const;
        virtual void setResultScale(Ionflux::Mapping::MappingValue 
        newResultScale);
        virtual Ionflux::Mapping::MappingValue getResultScale() const;
        virtual void setResultOffset(Ionflux::Mapping::MappingValue 
        newResultOffset);
        virtual Ionflux::Mapping::MappingValue getResultOffset() const;
};

}

}


%{
#include "ifmapping/PointMapping.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class PointMappingClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PointMappingClassInfo();
        virtual ~PointMappingClassInfo();
};

class PointMapping
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Mapping::MappingValue DEFAULT_PRECISION;
        
        PointMapping();
        virtual ~PointMapping();
        virtual Ionflux::Mapping::Point 
        evalCoord(Ionflux::Mapping::MappingValue value, 
        Ionflux::Mapping::CoordinateID coord = Ionflux::Mapping::C_X, 
        Ionflux::Mapping::MappingValue precision = 
        Ionflux::Mapping::PointMapping::DEFAULT_PRECISION);
        virtual Ionflux::Mapping::Point 
        operator()(Ionflux::Mapping::MappingValue value);
        virtual std::string getString() const;
        virtual Ionflux::Mapping::Point call(Ionflux::Mapping::MappingValue
        value) = 0;
		static Ionflux::Mapping::PointMapping* 
		upcast(Ionflux::ObjectBase::IFObject* other);
};

}

}


%{
#include "ifmapping/EvalCoord.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class EvalCoordClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        EvalCoordClassInfo();
        virtual ~EvalCoordClassInfo();
};

class EvalCoord
: public Ionflux::Mapping::PointMapping
{
    public:
        
        EvalCoord();
		EvalCoord(const Ionflux::Mapping::EvalCoord& other);
        EvalCoord(Ionflux::Mapping::PointMapping* initFunc, 
        Ionflux::Mapping::CoordinateID initCoord = Ionflux::Mapping::C_X, 
        Ionflux::Mapping::Point initOffset = 
        Ionflux::Mapping::Point::ORIGIN, Ionflux::Mapping::Point initScale 
        = Ionflux::Mapping::Point::ONES, Ionflux::Mapping::MappingValue 
        initParamOffset = 0., Ionflux::Mapping::MappingValue initParamScale
        = 1., Ionflux::Mapping::MappingValue initPrecision = 
        Ionflux::Mapping::PointMapping::DEFAULT_PRECISION);
        virtual ~EvalCoord();
        virtual std::string getString() const;
        virtual Ionflux::Mapping::Point call(Ionflux::Mapping::MappingValue
        value);
		virtual Ionflux::Mapping::EvalCoord* copy() const;
		static Ionflux::Mapping::EvalCoord* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::Mapping::EvalCoord* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
        virtual void setFunc(Ionflux::Mapping::PointMapping* newFunc);
        virtual Ionflux::Mapping::PointMapping* getFunc() const;
        virtual void setCoord(Ionflux::Mapping::CoordinateID newCoord);
        virtual Ionflux::Mapping::CoordinateID getCoord() const;
        virtual void setOffset(Ionflux::Mapping::Point newOffset);
        virtual Ionflux::Mapping::Point getOffset() const;
        virtual void setScale(Ionflux::Mapping::Point newScale);
        virtual Ionflux::Mapping::Point getScale() const;
        virtual void setParamOffset(Ionflux::Mapping::MappingValue 
        newParamOffset);
        virtual Ionflux::Mapping::MappingValue getParamOffset() const;
        virtual void setParamScale(Ionflux::Mapping::MappingValue 
        newParamScale);
        virtual Ionflux::Mapping::MappingValue getParamScale() const;
        virtual void setPrecision(Ionflux::Mapping::MappingValue 
        newPrecision);
        virtual Ionflux::Mapping::MappingValue getPrecision() const;
};

}

}


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


%{
#include "ifmapping/Linear.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class LinearClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        LinearClassInfo();
        virtual ~LinearClassInfo();
};

class Linear
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        Linear();
		Linear(const Ionflux::Mapping::Linear& other);
        Linear(Ionflux::Mapping::MappingValue initLower, 
        Ionflux::Mapping::MappingValue initUpper, 
        Ionflux::Mapping::MappingValue initScale = 1., 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~Linear();
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
        static Ionflux::Mapping::Linear* 
        create(Ionflux::Mapping::MappingValue initLower, 
        Ionflux::Mapping::MappingValue initUpper);
		virtual Ionflux::Mapping::Linear* copy() const;
		static Ionflux::Mapping::Linear* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Linear* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setLower(Ionflux::Mapping::MappingValue newLower);
        virtual Ionflux::Mapping::MappingValue getLower() const;
        virtual void setUpper(Ionflux::Mapping::MappingValue newUpper);
        virtual Ionflux::Mapping::MappingValue getUpper() const;
};

}

}


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


%{
#include "ifmapping/Count.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class CountClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        CountClassInfo();
        virtual ~CountClassInfo();
};

class Count
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        Count();
		Count(const Ionflux::Mapping::Count& other);
        Count(Ionflux::Mapping::MappingValue initAdjustment, 
        Ionflux::Mapping::MappingValue initCounter = 0., 
        Ionflux::Mapping::MappingValue initModulus = 0., 
        Ionflux::Mapping::MappingValue initScale = 0., 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~Count();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		virtual Ionflux::Mapping::Count* copy() const;
		static Ionflux::Mapping::Count* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Count* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setCounter(Ionflux::Mapping::MappingValue newCounter);
        virtual Ionflux::Mapping::MappingValue getCounter() const;
        virtual void setAdjustment(Ionflux::Mapping::MappingValue 
        newAdjustment);
        virtual Ionflux::Mapping::MappingValue getAdjustment() const;
        virtual void setModulus(Ionflux::Mapping::MappingValue newModulus);
        virtual Ionflux::Mapping::MappingValue getModulus() const;
};

}

}


%{
#include "ifmapping/Lookup.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class LookupClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        LookupClassInfo();
        virtual ~LookupClassInfo();
};

class Lookup
: public Ionflux::Mapping::ChainableMapping
{
    public:
		static const unsigned int DEFAULT_NUM_ENTRIES;
		static const Ionflux::Mapping::Range CLAMP_RANGE;
        
        Lookup();
		Lookup(const Ionflux::Mapping::Lookup& other);
        Lookup(Ionflux::Mapping::Mapping* initSource, unsigned int 
        initNumEntries = DEFAULT_NUM_ENTRIES, 
        Ionflux::Mapping::MappingValue initScale = 0., 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        Lookup(const Ionflux::Mapping::MappingValueVector& initEntries, 
        unsigned int initNumEntries = 0, Ionflux::Mapping::Mapping* 
        initSource = 0, Ionflux::Mapping::MappingValue initScale = 0., 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::Mapping* initFunc = 0);
        virtual ~Lookup();
        virtual void update(unsigned int numEntries = DEFAULT_NUM_ENTRIES);
        virtual void addEntries(const Ionflux::Mapping::MappingValueVector&
        newEntries, unsigned int numEntries = 0);
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
		virtual Ionflux::Mapping::Lookup* copy() const;
		static Ionflux::Mapping::Lookup* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Lookup* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);        
        virtual unsigned int getNumEntries() const;
        virtual Ionflux::Mapping::MappingValue getEntry(unsigned int 
        elementIndex = 0) const;
		virtual int findEntry(Ionflux::Mapping::MappingValue needle, unsigned int
		occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::MappingValue>& getEntries();
        virtual void addEntry(Ionflux::Mapping::MappingValue addElement);        
        virtual void removeEntry(Ionflux::Mapping::MappingValue 
        removeElement);
		virtual void removeEntryIndex(unsigned int removeIndex);
		virtual void clearEntries();
        virtual void setSource(Ionflux::Mapping::Mapping* newSource);
        virtual Ionflux::Mapping::Mapping* getSource() const;
};

}

}


%{
#include "ifmapping/Accept.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class AcceptClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        AcceptClassInfo();
        virtual ~AcceptClassInfo();
};

class Accept
: public Ionflux::Mapping::ChainableMapping
{
    public:
        
        Accept();
		Accept(const Ionflux::Mapping::Accept& other);
        Accept(Ionflux::Mapping::Mapping* initFunc, unsigned int 
        initMaxIters = MAX_ITERATIONS, Ionflux::Mapping::MappingValue 
        initScale = 1., Ionflux::Mapping::MappingValue initOffset = 0.);
        virtual ~Accept();
        virtual Ionflux::Mapping::MappingValue 
        callWithParam(Ionflux::Mapping::MappingValue value) const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const;
		virtual Ionflux::Mapping::Accept* copy() const;
		static Ionflux::Mapping::Accept* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::Accept* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setMaxIters(unsigned int newMaxIters);
        virtual unsigned int getMaxIters() const;
        virtual void setAcceptRange(const Ionflux::Mapping::Range& 
        newAcceptRange);
        virtual Ionflux::Mapping::Range getAcceptRange() const;
};

}

}


%{
#include "ifmapping/BezierCurve.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class BezierCurveClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BezierCurveClassInfo();
        virtual ~BezierCurveClassInfo();
};

class BezierCurve
: public Ionflux::Mapping::PointMapping, public Ionflux::Mapping::PointSet
{
    public:
        
        BezierCurve();
		BezierCurve(const Ionflux::Mapping::BezierCurve& other);
        BezierCurve(const Ionflux::Mapping::Point& initP0, const 
        Ionflux::Mapping::Point& initP1, const Ionflux::Mapping::Point& 
        initP2, const Ionflux::Mapping::Point& initP3);
        BezierCurve(const Ionflux::Mapping::PointVector& initPoints);
        BezierCurve(const Ionflux::Mapping::PointSet& initPoints);
        virtual ~BezierCurve();
        virtual void setControlPoints(const Ionflux::Mapping::PointVector& 
        newPoints);
        virtual void setControlPoints(const Ionflux::Mapping::PointSet& 
        newPoints);
        virtual std::string getString() const;
        virtual Ionflux::Mapping::Point call(Ionflux::Mapping::MappingValue
        value);
        virtual Ionflux::Mapping::BezierCurve interpolate(const 
        Ionflux::Mapping::BezierCurve& other, 
        Ionflux::Mapping::MappingValue t = 0.5) const;
		virtual Ionflux::Mapping::BezierCurve* copy() const;
		static Ionflux::Mapping::BezierCurve* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::BezierCurve* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setP0(const Ionflux::Mapping::Point& newP0);
        virtual Ionflux::Mapping::Point getP0() const;
        virtual void setP1(const Ionflux::Mapping::Point& newP1);
        virtual Ionflux::Mapping::Point getP1() const;
        virtual void setP2(const Ionflux::Mapping::Point& newP2);
        virtual Ionflux::Mapping::Point getP2() const;
        virtual void setP3(const Ionflux::Mapping::Point& newP3);
        virtual Ionflux::Mapping::Point getP3() const;
};

}

}


%{
#include "ifmapping/BezierSpline.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class BezierSplineClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BezierSplineClassInfo();
        virtual ~BezierSplineClassInfo();
};

class BezierSpline
: public Ionflux::Mapping::PointMapping
{
    public:
        
        BezierSpline();
		BezierSpline(const Ionflux::Mapping::BezierSpline& other);
        virtual ~BezierSpline();
        virtual void addSegments(const Ionflux::Mapping::BezierCurveVector&
        newCurves);
        virtual unsigned int getSegmentIndex(Ionflux::Mapping::MappingValue
        t) const;
        virtual void getPoints(Ionflux::Mapping::PointSet& target, 
        Ionflux::Mapping::MappingValue x0 = 0., 
        Ionflux::Mapping::MappingValue x1 = 1., unsigned int numPoints = 
        10, Ionflux::Mapping::CoordinateID coord = Ionflux::Mapping::C_X, 
        Ionflux::Mapping::MappingValue precision = 
        Ionflux::Mapping::PointMapping::DEFAULT_PRECISION);
        virtual void initFromSVG(const std::string& rawData);
        virtual Ionflux::Mapping::Point call(Ionflux::Mapping::MappingValue
        value);
        virtual Ionflux::Mapping::BezierSpline interpolate(const 
        Ionflux::Mapping::BezierSpline& other, 
        Ionflux::Mapping::MappingValue t = 0.5) const;
        virtual Ionflux::Mapping::Mapping* 
        createFunc(Ionflux::Mapping::MappingValue paramScale = 1., 
        Ionflux::Mapping::MappingValue paramOffset = 0., const 
        Ionflux::Mapping::Point& outputScale = 
        Ionflux::Mapping::Point::ONES, const Ionflux::Mapping::Point& 
        outputOffset = Ionflux::Mapping::Point::ORIGIN, 
        Ionflux::Mapping::CoordinateID inCoord = Ionflux::Mapping::C_X, 
        Ionflux::Mapping::CoordinateID outCoord = Ionflux::Mapping::C_Y);
        virtual std::string getString() const;
		virtual Ionflux::Mapping::BezierSpline* copy() const;
		static Ionflux::Mapping::BezierSpline* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::BezierSpline* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumSegments() const;
        virtual Ionflux::Mapping::BezierCurve* getSegment(unsigned int 
        elementIndex = 0) const;
		virtual int findSegment(Ionflux::Mapping::BezierCurve* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::BezierCurve*>& getSegments();
        virtual void addSegment(Ionflux::Mapping::BezierCurve* addElement);        
        virtual void removeSegment(Ionflux::Mapping::BezierCurve* 
        removeElement);
		virtual void removeSegmentIndex(unsigned int removeIndex);
		virtual void clearSegments();
};

}

}


%{
#include "ifmapping/PointCoord.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class PointCoordClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PointCoordClassInfo();
        virtual ~PointCoordClassInfo();
};

class PointCoord
: public Ionflux::Mapping::Mapping
{
    public:
        
        PointCoord();
		PointCoord(const Ionflux::Mapping::PointCoord& other);
        PointCoord(Ionflux::Mapping::PointMapping* initFunc, 
        Ionflux::Mapping::CoordinateID initCoord = Ionflux::Mapping::C_X, 
        Ionflux::Mapping::MappingValue initOffset = 0., 
        Ionflux::Mapping::MappingValue initScale = 1.);
        virtual ~PointCoord();
        virtual std::string getString() const;
        virtual Ionflux::Mapping::MappingValue 
        call(Ionflux::Mapping::MappingValue value) const;
		virtual Ionflux::Mapping::PointCoord* copy() const;
		static Ionflux::Mapping::PointCoord* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::PointCoord* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setFunc(Ionflux::Mapping::PointMapping* newFunc);
        virtual Ionflux::Mapping::PointMapping* getFunc() const;
        virtual void setCoord(Ionflux::Mapping::CoordinateID newCoord);
        virtual Ionflux::Mapping::CoordinateID getCoord() const;
        virtual void setOffset(Ionflux::Mapping::MappingValue newOffset);
        virtual Ionflux::Mapping::MappingValue getOffset() const;
        virtual void setScale(Ionflux::Mapping::MappingValue newScale);
        virtual Ionflux::Mapping::MappingValue getScale() const;
};

}

}


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

