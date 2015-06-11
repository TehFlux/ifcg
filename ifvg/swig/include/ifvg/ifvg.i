%include <std_string.i>
%include <std_vector.i>
%include <std_set.i>
%include <exception.i>
%module CIFVG
%import "ifobject/ifobject.i"
%import "ifmapping/ifmapping.i"
%import "altjira/altjira.i"
%import "altjira/altjiradraw.i"
%import "geoutils/geoutils.i"
%import "geoutils/altjirageoutils.i"
%{
#include "ifobject/ifobjectbase.hpp"
#include "ifmapping/ifmapping.hpp"
#include "altjira/altjira.hpp"
#include "altjira/altjiradraw.hpp"
#include "geoutils/geoutils.hpp"
#include "geoutils/altjirageoutils.hpp"
#include "ifvg/ifvg.hpp"
#include <assert.h>
using namespace std;
%}

%exception {
    try
    {
        $function
    } catch(Ionflux::VolGfx::IFVGError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch(Ionflux::GeoUtils::GeoUtilsError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch(Ionflux::Altjira::AltjiraError& e)
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

namespace VolGfx
{

// types.hpp

class Node;

typedef Ionflux::ObjectBase::UInt16 LocInt;
typedef std::bitset<16> NodeLoc;
typedef std::bitset<8> NodeChildMask;
typedef Ionflux::ObjectBase::UInt8 FaceMaskInt;

struct NodeLoc3
{
    Ionflux::VolGfx::NodeLoc x;
    Ionflux::VolGfx::NodeLoc y;
    Ionflux::VolGfx::NodeLoc z;
};

struct Region3
{
    Ionflux::VolGfx::NodeLoc3 l0;
    Ionflux::VolGfx::NodeLoc3 l1;
};

typedef Ionflux::ObjectBase::UInt8 NodeDataType;

typedef double NodeDataValue;

typedef void* NodeDataPointer;

struct NodeDataImpl
{
    Ionflux::VolGfx::NodeDataType type;
    NodeDataPointer data;
};

struct NodeImpl
{
    Ionflux::ObjectBase::UInt16 refCount;
    Ionflux::VolGfx::NodeLoc3 loc;
    Ionflux::VolGfx::NodeChildMask valid;
    Ionflux::VolGfx::NodeChildMask leaf;
    Ionflux::VolGfx::NodeImpl* parent;
    Ionflux::VolGfx::NodeDataImpl* data;
    Ionflux::VolGfx::NodeImpl* child;
};

typedef std::vector<Ionflux::VolGfx::NodeImpl*> NodeImplVector;
typedef std::vector<Ionflux::VolGfx::NodeDataImpl*> NodeDataImplVector;
typedef std::vector<Ionflux::VolGfx::Node*> NodeVector;

struct Cylinder
{
    Ionflux::GeoUtils::Vector3 center;
    Ionflux::GeoUtils::Vector3 direction;
    double length;
    double radius;
};

struct Plane
{
    Ionflux::GeoUtils::Vector3 p;
    Ionflux::GeoUtils::Vector3 normal;
};

struct Triangle
{
    Ionflux::GeoUtils::Vector3 v0;
    Ionflux::GeoUtils::Vector3 v1;
    Ionflux::GeoUtils::Vector3 v2;
};

typedef int SeparabilityID;

struct NodeID
{
    Ionflux::VolGfx::NodeLoc3 loc;
    int depth;
};

struct TriangleVoxelizationData
{
    double voxelSize;
    Ionflux::VolGfx::Triangle tri;
    Ionflux::VolGfx::Plane plane;
    Ionflux::VolGfx::SeparabilityID sep;
    double t;
    double r_c;
    Ionflux::VolGfx::Plane planeU;
    Ionflux::VolGfx::Plane planeL;
    Ionflux::VolGfx::Plane planeE0;
    Ionflux::VolGfx::Plane planeE1;
    Ionflux::VolGfx::Plane planeE2;
    Ionflux::VolGfx::Cylinder cylE0;
    Ionflux::VolGfx::Cylinder cylE1;
    Ionflux::VolGfx::Cylinder cylE2;
    Ionflux::VolGfx::NodeID node;
};

typedef int VoxelizationTargetID;

struct NodeImplHierarchyHeader
{
    Ionflux::ObjectBase::DataSize poMapOffset;
    Ionflux::ObjectBase::UInt16 implArrayStride;
    Ionflux::ObjectBase::UInt16 implSize;
    Ionflux::ObjectBase::UInt16 dataImplSize;
    Ionflux::ObjectBase::UInt8 dataValueSize;
    Ionflux::ObjectBase::UInt8 rootNodeDepth;
    Ionflux::ObjectBase::GenericPointer rootNodePointer;
};

typedef Ionflux::ObjectBase::UInt8 VoxelClassID;
typedef Ionflux::ObjectBase::UInt64 NodeProcessingResultID;

struct NodeIntersection
{
    Ionflux::GeoUtils::AAPlanePairIntersection intersection;
    Ionflux::VolGfx::NodeImpl* nodeImpl;
    int depth;
};

typedef std::vector<Ionflux::VolGfx::NodeIntersection> 
    NodeIntersectionVector;

struct VoxelClassColor
{
    Ionflux::VolGfx::VoxelClassID voxelClass;
    Ionflux::Altjira::Color* color;
};

typedef std::vector<Ionflux::VolGfx::VoxelClassColor> 
    VoxelClassColorVector;

typedef Ionflux::ObjectBase::Int16 ColorIndex;

struct VoxelDataIOB
{
    Ionflux::VolGfx::VoxelClassID voxelClass;
    Ionflux::ObjectBase::UInt16 numInts0;
    Ionflux::ObjectBase::UInt16 numInts1;
    Ionflux::ObjectBase::UInt16 votesInside;
    Ionflux::ObjectBase::UInt16 votesOutside;
    Ionflux::VolGfx::FaceMaskInt boundaryFaces;
    Ionflux::ObjectBase::UInt16 wallThicknessX;
    Ionflux::ObjectBase::UInt16 wallThicknessY;
    Ionflux::ObjectBase::UInt16 wallThicknessZ;
    Ionflux::VolGfx::ColorIndex color;
};

typedef Ionflux::ObjectBase::UInt8 LeafStatusID;
typedef Ionflux::ObjectBase::UInt8 MergePolicyID;

struct NodeIntersectionProcessingFlags
{
    bool directionBackward;
    bool enableBoundaryData;
    bool castVotes;
    bool enableRayStabbing;
    bool enableWallThickness;
};

// constants.hpp

const Ionflux::ObjectBase::UInt16 MAX_REF_COUNT = 65535;
const double DEFAULT_TOLERANCE = 1e-6;
const Ionflux::VolGfx::SeparabilityID SEPARABILITY_6 = 6;
const Ionflux::VolGfx::SeparabilityID SEPARABILITY_26 = 26;
const int DEPTH_UNSPECIFIED = -1;
const int COLOR_INDEX_UNSPECIFIED = -1;
const Ionflux::VolGfx::VoxelizationTargetID 
    VOXELIZATION_TARGET_DENSITY = 0;
const Ionflux::VolGfx::VoxelizationTargetID 
    VOXELIZATION_TARGET_COLOR_NORMAL = 1;
const Ionflux::VolGfx::VoxelizationTargetID 
    VOXELIZATION_TARGET_CLASS = 2;
const NodeDataValue DENSITY_EMPTY = 0.;
const NodeDataValue DENSITY_FILLED = 1.;

const Ionflux::ObjectBase::MagicSyllable MAGIC_SYLLABLE_BASE = 0x5647;

const Ionflux::VolGfx::VoxelClassID VOXEL_CLASS_UNDEFINED = 0;
const Ionflux::VolGfx::VoxelClassID VOXEL_CLASS_EMPTY = 1;
const Ionflux::VolGfx::VoxelClassID VOXEL_CLASS_FILLED = 2;
const Ionflux::VolGfx::VoxelClassID VOXEL_CLASS_INSIDE = 4;
const Ionflux::VolGfx::VoxelClassID VOXEL_CLASS_OUTSIDE = 8;
const Ionflux::VolGfx::VoxelClassID VOXEL_CLASS_BOUNDARY = 16;
const Ionflux::VolGfx::VoxelClassID VOXEL_CLASS_HIT = 32;

const Ionflux::VolGfx::FaceMaskInt FACE_UNDEFINED = 0;
const Ionflux::VolGfx::FaceMaskInt FACE_X0 = 1;
const Ionflux::VolGfx::FaceMaskInt FACE_X1 = 2;
const Ionflux::VolGfx::FaceMaskInt FACE_Y0 = 4;
const Ionflux::VolGfx::FaceMaskInt FACE_Y1 = 8;
const Ionflux::VolGfx::FaceMaskInt FACE_Z0 = 16;
const Ionflux::VolGfx::FaceMaskInt FACE_Z1 = 32;
const Ionflux::VolGfx::FaceMaskInt FACE_ALL = 63;

const Ionflux::VolGfx::LeafStatusID NODE_ANY = 0;
const Ionflux::VolGfx::LeafStatusID NODE_LEAF = 1;
const Ionflux::VolGfx::LeafStatusID NODE_NON_LEAF = 2;

const Ionflux::VolGfx::MergePolicyID MERGE_POLICY_KEEP_TARGET = 0;
const Ionflux::VolGfx::MergePolicyID MERGE_POLICY_TAKE_OVER_SOURCE = 1;

// utils.hpp

Ionflux::VolGfx::NodeLoc3 createLoc(Ionflux::VolGfx::NodeLoc x, 
    Ionflux::VolGfx::NodeLoc y, Ionflux::VolGfx::NodeLoc z);
Ionflux::VolGfx::Region3 createRegion(Ionflux::VolGfx::NodeLoc3 l0, 
    Ionflux::VolGfx::NodeLoc3 l1);
Ionflux::VolGfx::NodeID createNodeID(int depth = DEPTH_UNSPECIFIED, 
    const Ionflux::VolGfx::NodeLoc3* loc = 0);
Ionflux::VolGfx::NodeImplHierarchyHeader createNodeImplHierarchyHeader(
    Ionflux::ObjectBase::DataSize poMapOffset = 
        Ionflux::ObjectBase::DATA_SIZE_INVALID, 
    Ionflux::ObjectBase::UInt16 implArrayStride = 0, 
    Ionflux::ObjectBase::UInt16 implSize = 0, 
    Ionflux::ObjectBase::UInt16 dataImplSize = 0, 
    Ionflux::ObjectBase::UInt8 dataValueSize = 0, 
    Ionflux::ObjectBase::UInt8 rootNodeDepth = 0, 
    Ionflux::ObjectBase::GenericPointer rootNodePointer = 0);
Ionflux::VolGfx::NodeIntersection createNodeIntersection(
    const Ionflux::GeoUtils::AAPlanePairIntersection* intersection = 0, 
    Ionflux::VolGfx::NodeImpl* nodeImpl = 0, 
    int depth = DEPTH_UNSPECIFIED);
Ionflux::VolGfx::VoxelDataIOB createVoxelDataIOB(
    Ionflux::VolGfx::VoxelClassID voxelClass = VOXEL_CLASS_UNDEFINED, 
    Ionflux::ObjectBase::UInt16 numInts0 = 0, 
    Ionflux::ObjectBase::UInt16 numInts1 = 0,
    Ionflux::ObjectBase::UInt16 votesInside = 0, 
    Ionflux::ObjectBase::UInt16 votesOutside = 0, 
    Ionflux::VolGfx::FaceMaskInt boundaryFaces = FACE_UNDEFINED, 
    Ionflux::ObjectBase::UInt16 wallThicknessX = 0, 
    Ionflux::ObjectBase::UInt16 wallThicknessY = 0, 
    Ionflux::ObjectBase::UInt16 wallThicknessZ = 0, 
    Ionflux::VolGfx::ColorIndex color = COLOR_INDEX_UNSPECIFIED);
Ionflux::VolGfx::NodeIntersectionProcessingFlags 
    createNodeIntersectionProcessingFlags(
        bool directionBackward = false, bool enableBoundaryData = false, 
        bool castVotes = true, bool enableRayStabbing = false, 
        bool enableWallThickness = false);

std::string getLocString(const Ionflux::VolGfx::NodeLoc& loc);
std::string getLocString(const Ionflux::VolGfx::NodeLoc3& loc);
std::string getLocValueString(const Ionflux::VolGfx::NodeLoc& loc, 
    bool showCode = true, bool showIndex = false, 
    bool showVec = false, Ionflux::VolGfx::Context* context = 0);
std::string getLocValueString(const Ionflux::VolGfx::NodeLoc3& loc, 
    bool showMask = true, bool showIndex = false, 
    bool showVec = false, Ionflux::VolGfx::Context* context = 0);
std::string getRegionString(const Ionflux::VolGfx::Region3& region);
std::string getCylinderString(const Ionflux::VolGfx::Cylinder& c);
std::string getPlaneString(const Ionflux::VolGfx::Plane& p);
std::string getTriangleString(const Ionflux::VolGfx::Triangle& tri);
std::string getDepthString(int d);
std::string getNodeIDString(const Ionflux::VolGfx::NodeID& nodeID);
std::string getNodeIDValueString(const Ionflux::VolGfx::NodeID& nodeID, 
    bool showCode = true, bool showIndex = false, 
    bool showVec = false, Ionflux::VolGfx::Context* context = 0);
std::string getTriangleVoxelizationDataString(
    const Ionflux::VolGfx::TriangleVoxelizationData& d);
void printTriangleVoxelizationDataDebugInfo(
    const Ionflux::VolGfx::TriangleVoxelizationData& d);
std::string getNodeImplHierarchyHeaderValueString(
    const Ionflux::VolGfx::NodeImplHierarchyHeader& h);
std::string getVoxelizationTargetValueString(
    Ionflux::VolGfx::VoxelizationTargetID t);
std::string getVoxelClassValueString(Ionflux::VolGfx::VoxelClassID t);
std::string getNodeIntersectionValueString(
    Ionflux::VolGfx::Context& context, 
    const Ionflux::VolGfx::NodeIntersection& i0);
std::string getFaceMaskValueString(Ionflux::VolGfx::FaceMaskInt mask);
std::string getVoxelDataIOBValueString(
    const Ionflux::VolGfx::VoxelDataIOB& data);
std::string getLeafStatusValueString(Ionflux::VolGfx::LeafStatusID s);
std::string getMergePolicyValueString(Ionflux::VolGfx::MergePolicyID p);
std::string getFaceMaskValueString(Ionflux::VolGfx::FaceMaskInt mask);

double distanceToPlane(const Ionflux::GeoUtils::Vector3& v, 
    const Ionflux::VolGfx::Plane& p);
double distanceToSphere(const Ionflux::GeoUtils::Vector3& v, 
    const Ionflux::GeoUtils::Vector3& cs, double rs);
double distanceToCylinderSC(const Ionflux::GeoUtils::Vector3& v, 
    const Ionflux::VolGfx::Cylinder& c);
bool voxelizePointTest(
    const Ionflux::VolGfx::TriangleVoxelizationData& d, 
    const Ionflux::GeoUtils::Vector3& v);

void packVoxelClass(Ionflux::VolGfx::VoxelClassID c, 
    Ionflux::VolGfx::NodeDataPointer& target);
void unpackVoxelClass(Ionflux::VolGfx::NodeDataPointer source, 
    Ionflux::VolGfx::VoxelClassID& c);
void setVoxelClass(Ionflux::VolGfx::VoxelClassID c, 
    Ionflux::VolGfx::VoxelClassID& target, bool enable = true);
bool checkVoxelClass(Ionflux::VolGfx::VoxelClassID source, 
    Ionflux::VolGfx::VoxelClassID mask);

struct NodeIntersectionCompare
{
    bool operator()(const NodeIntersection& i0, 
        const NodeIntersection& i1);
};

Ionflux::Altjira::Color* getVoxelClassColor(
    const Ionflux::VolGfx::VoxelClassColorVector& colors, 
    Ionflux::VolGfx::VoxelClassID c);

Ionflux::VolGfx::NodeLoc clampLoc(
    const Ionflux::VolGfx::NodeLoc& loc, 
    const Ionflux::VolGfx::NodeLoc& rMin, 
    const Ionflux::VolGfx::NodeLoc& rMax);
Ionflux::VolGfx::NodeLoc3 clampLoc3(
    const Ionflux::VolGfx::NodeLoc3& loc, 
    const Ionflux::VolGfx::Region3& region);

bool checkFaceMask(Ionflux::VolGfx::FaceMaskInt source, 
    Ionflux::VolGfx::FaceMaskInt mask);
unsigned int getNumFacesSet(Ionflux::VolGfx::FaceMaskInt mask);

void setVertexAttributeTrianglePos(
    Ionflux::GeoUtils::VertexAttribute& target, 
    unsigned int elementIndex, const Ionflux::GeoUtils::Vector3& v0, 
    const Ionflux::GeoUtils::Vector3& v1, 
    const Ionflux::GeoUtils::Vector3& v2, bool reverse = false);

void setIOBDataWallThickness(Ionflux::VolGfx::VoxelDataIOB& data, 
    Ionflux::GeoUtils::AxisID axis, Ionflux::ObjectBase::UInt16 v);
Ionflux::ObjectBase::UInt16 getIOBDataWallThickness(
    const Ionflux::VolGfx::VoxelDataIOB& data, 
    Ionflux::GeoUtils::AxisID axis);
Ionflux::ObjectBase::UInt16 getIOBDataWallThicknessMin(
    const Ionflux::VolGfx::VoxelDataIOB& data, 
    Ionflux::GeoUtils::AxisID* axis = 0);

Ionflux::VolGfx::ColorIndex getColorIndex(
    Ionflux::ObjectBase::UInt16 v, 
    Ionflux::ObjectBase::UInt16 vMin, 
    Ionflux::ObjectBase::UInt16 vMax, 
    Ionflux::VolGfx::ColorIndex minColorIndex, 
    Ionflux::VolGfx::ColorIndex maxColorIndex);

// serialize.hpp

void pack(
    const Ionflux::VolGfx::NodeLoc& source, 
    std::string& target, bool append = true);
int unpack(const std::string& source, 
    Ionflux::VolGfx::NodeLoc& target, int offset = 0);
void pack(
    const Ionflux::VolGfx::NodeChildMask& source, 
    std::string& target, bool append = true);
int unpack(const std::string& source, 
    Ionflux::VolGfx::NodeChildMask& target, int offset = 0);
void pack(
    const Ionflux::VolGfx::NodeLoc3& source, 
    std::string& target, bool append = true);
int unpack(const std::string& source, 
    Ionflux::VolGfx::NodeLoc3& target, int offset = 0);
void pack(
    const Ionflux::VolGfx::NodeDataImpl& source, 
    std::string& target, bool append = true);
int unpack(const std::string& source, 
    Ionflux::VolGfx::NodeDataImpl& target, int offset = 0);
void pack(
    const Ionflux::VolGfx::NodeImpl& source, 
    std::string& target, bool append = true);
int unpack(const std::string& source, 
    Ionflux::VolGfx::NodeImpl& target, int offset = 0);
void pack(
    const Ionflux::VolGfx::VoxelDataIOB& source, 
    std::string& target, bool append = true);
Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    Ionflux::VolGfx::VoxelDataIOB& target, 
    Ionflux::ObjectBase::DataSize offset = 0);

}

}

// Classes


%{
#include "ifvg/Context.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class ContextClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ContextClassInfo();
        virtual ~ContextClassInfo();
};

class Context
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const int MAX_NUM_LEVELS;
		static const int DEFAULT_MAX_NUM_LEVELS;
		static const int DEFAULT_ORDER;
		static const double DEFAULT_BOX_INSET;
        
        Context();
		Context(const Ionflux::VolGfx::Context& other);
        Context(int initMaxNumLevels, int initOrder = DEFAULT_ORDER, double
        initScale = 1., double initTolerance = DEFAULT_TOLERANCE);
        virtual ~Context();
        virtual void clear();
        virtual void update();
        virtual Ionflux::VolGfx::NodeLoc createLoc(double v, bool 
        checkBounds0 = true);
        virtual Ionflux::VolGfx::NodeLoc3 createLoc(double x, double y, 
        double z, bool checkBounds0 = true);
        virtual Ionflux::VolGfx::NodeLoc3 createLoc(const 
        Ionflux::GeoUtils::Vector3& v, bool checkBounds0 = true);
        virtual Ionflux::VolGfx::NodeLoc3 createLoc(const 
        Ionflux::Mapping::Point& p, bool checkBounds0 = true);
        virtual Ionflux::VolGfx::Region3 createRegion(const 
        Ionflux::GeoUtils::Range3& r);
        virtual bool locEqual(const Ionflux::VolGfx::NodeLoc& loc0, const 
        Ionflux::VolGfx::NodeLoc& loc1, int maxDepth = DEPTH_UNSPECIFIED);
        virtual bool locEqual(const Ionflux::VolGfx::NodeLoc3& loc0, const 
        Ionflux::VolGfx::NodeLoc3& loc1, int maxDepth = DEPTH_UNSPECIFIED);
        virtual int getChildOrderIndex(const Ionflux::VolGfx::NodeLoc3& 
        loc, int depth) const;
        virtual int getCommonAncestorLevel(const Ionflux::VolGfx::NodeLoc3&
        loc0, const Ionflux::VolGfx::NodeLoc3& loc1, int maxDepth = 
        DEPTH_UNSPECIFIED) const;
        virtual int getCommonAncestorLevel(const Ionflux::VolGfx::Region3& 
        region, int maxDepth = DEPTH_UNSPECIFIED) const;
        virtual Ionflux::VolGfx::NodeLoc getDepthMask(int depth) const;
        virtual Ionflux::VolGfx::NodeLoc getLocMask(int depth);
        virtual double getVoxelSize(int depth = 0);
        virtual double getMinLeafSize();
        virtual void getLocation(const Ionflux::VolGfx::NodeLoc3& loc, 
        Ionflux::GeoUtils::Vector3& target);
        virtual Ionflux::GeoUtils::Vector3 getLocation0(const 
        Ionflux::VolGfx::NodeLoc3& loc);
        virtual void getVoxelLocation(const Ionflux::VolGfx::NodeLoc3& loc,
        int depth, Ionflux::GeoUtils::Vector3& target);
        virtual Ionflux::GeoUtils::Vector3 getVoxelLocation0(const 
        Ionflux::VolGfx::NodeLoc3& loc, int depth);
        virtual void getVoxelLocation(const Ionflux::VolGfx::NodeID& node, 
        Ionflux::GeoUtils::Vector3& target);
        virtual void getVoxelRange(const Ionflux::VolGfx::NodeLoc3& loc, 
        int depth, Ionflux::GeoUtils::Range3& target);
        virtual void getVoxelRange(Ionflux::VolGfx::NodeID node, 
        Ionflux::GeoUtils::Range3& target);
        virtual void getVoxelRegion(const Ionflux::VolGfx::NodeLoc3& loc, 
        int depth, Ionflux::VolGfx::Region3& target, bool 
        includeMaxBoundary = false);
        virtual void getVoxelRegion(Ionflux::VolGfx::NodeID node, 
        Ionflux::VolGfx::Region3& target, bool includeMaxBoundary = false);
        virtual bool checkLoc(const Ionflux::VolGfx::NodeLoc& loc, int 
        offset = 0);
        virtual bool checkLoc(const Ionflux::GeoUtils::Vector3& v);
        virtual bool checkLoc(const Ionflux::VolGfx::NodeLoc3& loc, int 
        offsetX = 0, int offsetY = 0, int offsetZ = 0);
        virtual bool checkRegion(const Ionflux::VolGfx::Region3& region, 
        int offsetX = 0, int offsetY = 0, int offsetZ = 0);
        virtual bool checkRange(const Ionflux::GeoUtils::Range3& range, 
        const Ionflux::VolGfx::NodeLoc3& loc, int depth);
        virtual bool checkRange(const Ionflux::GeoUtils::Range3& range, 
        Ionflux::VolGfx::NodeID node);
        virtual bool checkRange(const Ionflux::GeoUtils::Range3& range);
        virtual bool checkDepthRange(int depth, int minDepth = 
        DEPTH_UNSPECIFIED, int maxDepth = DEPTH_UNSPECIFIED);
        virtual void getContainingNode(const Ionflux::GeoUtils::Range3& 
        range, Ionflux::VolGfx::NodeID& target);
        virtual void initTriangleVoxelizationData(const 
        Ionflux::GeoUtils::Face& face, 
        Ionflux::VolGfx::TriangleVoxelizationData& target, 
        Ionflux::VolGfx::SeparabilityID sep = SEPARABILITY_26, int depth = 
        DEPTH_UNSPECIFIED, bool checkBounds0 = true);
        virtual void printDebugInfo() const;
        virtual void getVoxelMesh(Ionflux::VolGfx::NodeID node, 
        Ionflux::GeoUtils::Mesh& target, double boxInset = 
        DEFAULT_BOX_INSET, Ionflux::Altjira::ColorSet* colors = 0, unsigned
        int colorOffset = 0, int colorIndex = COLOR_INDEX_UNSPECIFIED);
        virtual void getVoxelVertexAttributes(Ionflux::VolGfx::NodeID node,
        Ionflux::GeoUtils::VertexAttribute* positionTarget = 0, 
        Ionflux::GeoUtils::VertexAttribute* colorTarget = 0, 
        Ionflux::GeoUtils::VertexAttribute* normalTarget = 0, 
        Ionflux::GeoUtils::NFaceTypeID nFaceType = 
        Ionflux::GeoUtils::NFace::TYPE_FACE, double boxInset = 
        DEFAULT_BOX_INSET, Ionflux::Altjira::Color* color = 0, 
        Ionflux::GeoUtils::Vector* positionOffset = 0, 
        Ionflux::GeoUtils::Vector* positionScale = 0, 
        Ionflux::VolGfx::FaceMaskInt faces = FACE_ALL, 
        Ionflux::VolGfx::FaceMaskInt flipNormals = FACE_UNDEFINED);
        virtual bool getIntersectionLoc(Ionflux::GeoUtils::Line3& line, 
        const Ionflux::GeoUtils::AAPlanePairIntersection& interData, 
        Ionflux::VolGfx::Region3& target, bool checkBounds0 = true);
        virtual bool getIntersectionLoc(const Ionflux::VolGfx::NodeID& 
        node, Ionflux::GeoUtils::Line3& line, const 
        Ionflux::GeoUtils::AAPlanePairIntersection& interData, 
        Ionflux::VolGfx::Region3& target, bool clampToNodeRegion = true, 
        bool includeMaxBoundary = false);
        virtual std::string getValueString() const;
        static Ionflux::GeoUtils::Vector3* getVoxelDiag(int index);
        static Ionflux::GeoUtils::Vector3* getVoxelDiag(int x, int y, int 
        z);
        static void cleanupVoxelDiag();
        static Ionflux::GeoUtils::Vector3* getMatchingVoxelDiag(const 
        Ionflux::GeoUtils::Vector3& v);
        static Ionflux::GeoUtils::Vector3* getVoxelNormal(int index);
        static Ionflux::GeoUtils::Vector3* getMatchingVoxelNormal(const 
        Ionflux::GeoUtils::Vector3& v);
        static void cleanupVoxelNormal();
        static void cleanup();
		virtual Ionflux::VolGfx::Context* copy() const;
		static Ionflux::VolGfx::Context* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::VolGfx::Context* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::VolGfx::Context* create(int initMaxNumLevels, int 
		initOrder = DEFAULT_ORDER, double initScale = 1., double initTolerance = 
		DEFAULT_TOLERANCE, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setMaxNumLevels(int newMaxNumLevels);
        virtual int getMaxNumLevels() const;
        virtual void setOrder(int newOrder);
        virtual int getOrder() const;
        virtual void setTolerance(double newTolerance);
        virtual double getTolerance() const;
        virtual void setValidBits(const Ionflux::VolGfx::NodeLoc& 
        newValidBits);
        virtual Ionflux::VolGfx::NodeLoc getValidBits() const;
        virtual int getMaxNumLeafChildNodesPerNode() const;
        virtual int getMaxNumLeafChildNodesPerDimension() const;
        virtual void setScale(double newScale);
        virtual double getScale() const;
};

}

}


%{
#include "ifvg/IOContext.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class IOContextClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        IOContextClassInfo();
        virtual ~IOContextClassInfo();
};

class IOContext
: public Ionflux::ObjectBase::IFIOContext
{
    public:
        
        IOContext();
		IOContext(const Ionflux::VolGfx::IOContext& other);
        virtual ~IOContext();
        virtual void clear();
        virtual void printDebugInfo(bool inputStreamVerbose = false, bool 
        outputStreamVerbose = false, bool poMapSerializedVerbose = false, 
        bool poMapCurrentVerbose = false);
        virtual std::string getValueString() const;
		virtual Ionflux::VolGfx::IOContext* copy() const;
		static Ionflux::VolGfx::IOContext* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::VolGfx::IOContext* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setRootNodeID(Ionflux::VolGfx::NodeID newRootNodeID);
        virtual Ionflux::VolGfx::NodeID getRootNodeID() const;
        virtual void setHeader(const 
        Ionflux::VolGfx::NodeImplHierarchyHeader& newHeader);
        virtual Ionflux::VolGfx::NodeImplHierarchyHeader getHeader() const;
};

}

}


%{
#include "ifvg/Node.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class NodeSet;
class IOContext;
class NodeProcessor;
class NodeFilter;
class NodeIntersectionProcessor;

class NodeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NodeClassInfo();
        virtual ~NodeClassInfo();
};

class Node
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_UNKNOWN;
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_NULL;
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_DENSITY;
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_COLOR_RGBA;
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_DISTANCE_8;
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_COLOR_NORMAL;
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_FACE_VEC;
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_VOXEL_CLASS;
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_VOXEL_IOB;
		static const Ionflux::VolGfx::NodeDataType DATA_TYPE_ANY_NOT_NULL;
		static const int CHILD_INDEX_INVALID;
		static const Ionflux::ObjectBase::MagicSyllable MAGIC_SYLLABLE_HEADER;
		static const Ionflux::ObjectBase::MagicSyllable MAGIC_SYLLABLE_ROOT;
		static const Ionflux::ObjectBase::MagicSyllable MAGIC_SYLLABLE_NODE;
		static const Ionflux::ObjectBase::MagicSyllable MAGIC_SYLLABLE_OFFSET_MAP;
		static const Ionflux::ObjectBase::MagicSyllable MAGIC_SYLLABLE_DATA;
		static const double DEFAULT_RAY_PLANE_OFFSET;
        
        Node();
		Node(const Ionflux::VolGfx::Node& other);
        Node(Ionflux::VolGfx::Context* initContext, 
        Ionflux::VolGfx::NodeImpl* initImpl = 0);
        virtual ~Node();
        virtual void clear() const;
        virtual Ionflux::VolGfx::Node* getParent() const;
        virtual void setChildNodes(const Ionflux::VolGfx::NodeVector& 
        newNodes) const;
        virtual void mergeChildNodes(const Ionflux::VolGfx::NodeImplVector&
        newNodes, bool fill0 = false) const;
        virtual void mergeChildNodes(const Ionflux::VolGfx::NodeVector& 
        newNodes, bool fill0 = false) const;
        virtual void setChildNodeByOrderIndex(Ionflux::VolGfx::Node* 
        newNode, int orderIndex) const;
        virtual void clearChildNodes(const Ionflux::VolGfx::NodeChildMask& 
        clearNodes) const;
        virtual unsigned int pruneEmpty(bool recursive = false) const;
        virtual void clearData() const;
        virtual void clearChildNodes() const;
        virtual void setData(Ionflux::VolGfx::NodeDataImpl* newData) const;
        virtual void setData(Ionflux::VolGfx::NodeDataType newType, const 
        Ionflux::ObjectBase::DoubleVector* newData = 0) const;
        virtual void clearLeafData() const;
        virtual int getNumChildNodes() const;
        virtual int fill(bool clearExisting = false, bool recursive = 
        false, int maxDepth = 0) const;
        virtual int getChildValidIndex(Ionflux::VolGfx::Node* n) const;
        virtual int getChildValidIndex(Ionflux::VolGfx::NodeImpl* 
        otherImpl) const;
        virtual int getChildValidIndex(int orderIndex) const;
        virtual int getChildOrderIndex(int index) const;
        virtual Ionflux::VolGfx::NodeLoc3 getChildLoc(int orderIndex) 
        const;
        virtual bool isLeafOrderChild(int orderIndex) const;
        virtual bool isLeafValidChild(int index) const;
        virtual bool isLeaf() const;
        virtual Ionflux::VolGfx::LeafStatusID getLeafStatus();
        virtual void update();
        virtual bool hasVoxelClassInfo();
        virtual Ionflux::VolGfx::VoxelClassID getVoxelClass();
        virtual bool hasVoxelClass(Ionflux::VolGfx::VoxelClassID mask);
        virtual Ionflux::VolGfx::VoxelClassID 
        setVoxelClass(Ionflux::VolGfx::VoxelClassID mask, bool enable = 
        true, Ionflux::VolGfx::NodeDataType createDataType = 
        DATA_TYPE_UNKNOWN);
        virtual unsigned int setVoxelClass0(Ionflux::VolGfx::VoxelClassID 
        mask, bool enable = true, Ionflux::VolGfx::NodeFilter* filter = 0, 
        bool recursive = true, Ionflux::VolGfx::NodeDataType createDataType
        = DATA_TYPE_UNKNOWN);
        virtual bool hasColorIndex();
        virtual Ionflux::VolGfx::ColorIndex getColorIndex();
        virtual Ionflux::VolGfx::ColorIndex 
        setColorIndex(Ionflux::VolGfx::ColorIndex color, 
        Ionflux::VolGfx::NodeDataType createDataType = DATA_TYPE_UNKNOWN);
        virtual unsigned int setColorIndex0(Ionflux::VolGfx::ColorIndex 
        color, Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = 
        true, Ionflux::VolGfx::NodeDataType createDataType = 
        DATA_TYPE_UNKNOWN);
        virtual Ionflux::VolGfx::Node* getChildByOrderIndex(int orderIndex,
        bool autoCreate = false) const;
        virtual Ionflux::VolGfx::Node* getChildByValidIndex(int index) 
        const;
        virtual Ionflux::VolGfx::Node* locateChild(const 
        Ionflux::VolGfx::NodeLoc3& loc, int maxDepth = DEPTH_UNSPECIFIED);
        virtual Ionflux::VolGfx::Node* locateChild(const 
        Ionflux::GeoUtils::Vector3& p, int maxDepth = DEPTH_UNSPECIFIED);
        virtual Ionflux::VolGfx::Node* locateRegion(const 
        Ionflux::VolGfx::Region3& region, int maxDepth = 
        DEPTH_UNSPECIFIED);
        virtual Ionflux::VolGfx::Node* locateRegion(const 
        Ionflux::GeoUtils::Range3& range, int maxDepth = 
        DEPTH_UNSPECIFIED);
        virtual Ionflux::VolGfx::Node* locateNode(const 
        Ionflux::VolGfx::NodeLoc3& loc, int maxDepth = DEPTH_UNSPECIFIED);
        virtual int getDepth() const;
        virtual int getMaxDepth() const;
        virtual Ionflux::VolGfx::Node* insertChild(const 
        Ionflux::VolGfx::NodeLoc3& loc, int depth = DEPTH_UNSPECIFIED, bool
        fill0 = false, bool fillTargetDepth0 = false);
        virtual Ionflux::VolGfx::Node* insertChild(const 
        Ionflux::GeoUtils::Vector3& p, int depth = DEPTH_UNSPECIFIED, bool 
        fill0 = false);
        virtual Ionflux::VolGfx::Node* insertChild(const 
        Ionflux::VolGfx::NodeID& nodeID, bool fill0 = false);
        virtual double getVoxelSize();
        virtual double getVoxelSizeLoc();
        virtual Ionflux::GeoUtils::Vector3 getLocation() const;
        virtual bool getNeighborLoc(int offsetX, int offsetY, int offsetZ, 
        Ionflux::VolGfx::NodeLoc3& target);
        virtual void getRange(Ionflux::GeoUtils::Range3& target) const;
        virtual bool getIntersectionLoc(Ionflux::GeoUtils::Line3& line, 
        const Ionflux::GeoUtils::AAPlanePairIntersection& interData, 
        Ionflux::VolGfx::Region3& target) const;
        virtual unsigned int find(Ionflux::VolGfx::NodeSet* target, 
        Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = true);
        virtual unsigned int process(Ionflux::VolGfx::NodeProcessor* 
        preProcessor, Ionflux::VolGfx::NodeFilter* filter = 0, 
        Ionflux::VolGfx::NodeProcessor* postProcessor = 0, bool recursive =
        true);
        virtual Ionflux::Altjira::Color* 
        getColor(Ionflux::Altjira::ColorSet* colors = 0, unsigned int 
        colorIndexOffset = 0, unsigned int colorIndexRange = 0, int 
        colorIndex = COLOR_INDEX_UNSPECIFIED, int leafColorIndex = 
        COLOR_INDEX_UNSPECIFIED, Ionflux::VolGfx::VoxelClassColorVector* 
        voxelClassColors = 0);
        virtual void getMesh(Ionflux::GeoUtils::Mesh& target, double 
        boxInset = Ionflux::VolGfx::Context::DEFAULT_BOX_INSET, 
        Ionflux::Altjira::ColorSet* colors = 0, unsigned int colorOffset = 
        0, unsigned int colorIndexOffset = 0, unsigned int colorIndexRange 
        = 0, int leafColorIndex = COLOR_INDEX_UNSPECIFIED, 
        Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = false);
        virtual void 
        getVertexAttributes(Ionflux::GeoUtils::VertexAttribute* 
        positionTarget = 0, Ionflux::GeoUtils::VertexAttribute* colorTarget
        = 0, Ionflux::GeoUtils::VertexAttribute* normalTarget = 0, 
        Ionflux::GeoUtils::NFaceTypeID nFaceType = 
        Ionflux::GeoUtils::NFace::TYPE_FACE, double boxInset = 
        Ionflux::VolGfx::Context::DEFAULT_BOX_INSET, 
        Ionflux::Altjira::ColorSet* colors = 0, unsigned int 
        colorIndexOffset = 0, unsigned int colorIndexRange = 0, int 
        colorIndex = COLOR_INDEX_UNSPECIFIED, int leafColorIndex = 
        COLOR_INDEX_UNSPECIFIED, Ionflux::VolGfx::VoxelClassColorVector* 
        voxelClassColors = 0, Ionflux::GeoUtils::Vector* positionOffset = 
        0, Ionflux::GeoUtils::Vector* positionScale = 0, 
        Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = false, 
        bool boundaryFacesOnly = false);
        virtual unsigned int getNumFaces(bool recursive = false);
        virtual bool voxelizeInsertFace(Ionflux::GeoUtils::Face* face, 
        Ionflux::VolGfx::SeparabilityID sep, bool fill0 = false);
        virtual unsigned int voxelizeInsertFaces(const 
        Ionflux::GeoUtils::Mesh& mesh, Ionflux::VolGfx::SeparabilityID sep,
        bool fill0 = false);
        virtual unsigned int voxelizeFaces(Ionflux::VolGfx::NodeProcessor* 
        processor, int targetDepth, Ionflux::VolGfx::SeparabilityID sep, 
        bool fillTargetDepth = false, bool pruneEmpty0 = false, 
        Ionflux::GeoUtils::FaceVector* faces0 = 0);
        virtual unsigned int getMemSize(bool recursive = false);
        virtual unsigned int getDataMemSize();
        virtual void serializeHierarchy(Ionflux::VolGfx::IOContext& 
        ioContext);
        virtual void deserialize(Ionflux::VolGfx::IOContext& ioContext, 
        Ionflux::ObjectBase::DataSize offset = 
        Ionflux::ObjectBase::DATA_SIZE_INVALID, 
        Ionflux::ObjectBase::MagicSyllable magicSyllable = 
        MAGIC_SYLLABLE_NODE, bool deserializeData = true, bool 
        zeroChildPointer = true, bool zeroParentPointer = true);
        virtual void deserializeHierarchy(Ionflux::VolGfx::IOContext& 
        ioContext, bool deserializeData = true, int maxDepth = 
        DEPTH_UNSPECIFIED);
        virtual bool intersectRay(const Ionflux::GeoUtils::Line3& ray, 
        Ionflux::VolGfx::NodeIntersection& target, double t = 
        DEFAULT_TOLERANCE);
        virtual unsigned int intersectRay(const Ionflux::GeoUtils::Line3& 
        ray, Ionflux::VolGfx::NodeIntersectionProcessor* processor = 0, 
        Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = true, 
        double t = DEFAULT_TOLERANCE, Ionflux::VolGfx::NodeIntersection* 
        pcIntersection = 0, bool fill0 = false, bool pruneEmpty0 = false);
        virtual unsigned int castRayGrid(const Ionflux::GeoUtils::Vector3& 
        rayOrigin, const Ionflux::GeoUtils::Vector3& rayDirection, const 
        Ionflux::GeoUtils::Vector3& originStepX, const 
        Ionflux::GeoUtils::Vector3& originStepY, unsigned int numRaysX, 
        unsigned int numRaysY, Ionflux::VolGfx::NodeIntersectionProcessor* 
        processor = 0, Ionflux::VolGfx::NodeFilter* filter = 0, bool 
        recursive = true, double t = DEFAULT_TOLERANCE, bool fill0 = false,
        bool pruneEmpty0 = false);
        virtual unsigned int castRayGrid(const Ionflux::GeoUtils::AxisID& 
        axis, int targetDepth = DEPTH_UNSPECIFIED, double planeOffset = 
        DEFAULT_RAY_PLANE_OFFSET, 
        Ionflux::VolGfx::NodeIntersectionProcessor* processor = 0, 
        Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = true, 
        double t = DEFAULT_TOLERANCE, bool fill0 = false, bool pruneEmpty0 
        = false);
        virtual unsigned int merge(Ionflux::VolGfx::Node& source, 
        Ionflux::VolGfx::MergePolicyID childPolicy = 
        MERGE_POLICY_KEEP_TARGET, Ionflux::VolGfx::MergePolicyID dataPolicy
        = MERGE_POLICY_KEEP_TARGET, Ionflux::VolGfx::NodeFilter* 
        sourceFilter = 0, Ionflux::VolGfx::NodeFilter* targetFilter = 0, 
        Ionflux::VolGfx::NodeFilter* sourceMergeFilter = 0, bool recursive 
        = true, bool fill0 = false);
        virtual void printDebugInfo(bool recursive = false, unsigned int 
        indentWidth = Ionflux::ObjectBase::DEFAULT_INDENT_WIDTH, char 
        indentChar = ' ', unsigned int depth = 0) const;
        virtual std::string getValueString() const;
        static std::string getDataTypeString(Ionflux::VolGfx::NodeDataType 
        t);
        static Ionflux::ObjectBase::DataSize 
        getDataTypeNumElements(Ionflux::VolGfx::NodeDataType t);
        static std::string 
        getDataValueString(Ionflux::VolGfx::NodeDataImpl* data);
        static Ionflux::VolGfx::NodeImpl* createImpl();
        static void copyImpl(Ionflux::VolGfx::NodeImpl& source, 
        Ionflux::VolGfx::NodeImpl& target, bool takeover = false);
        static Ionflux::ObjectBase::UInt16 
        refImpl(Ionflux::VolGfx::NodeImpl* otherImpl);
        static void clearDataImpl(Ionflux::VolGfx::NodeDataImpl* dataImpl);
        static void clearImpl(Ionflux::VolGfx::NodeImpl* otherImpl, bool 
        recursive = true, bool clearData = true, bool clearChildNodes = 
        true);
        static Ionflux::ObjectBase::UInt16 
        unrefImpl(Ionflux::VolGfx::NodeImpl* otherImpl);
        static Ionflux::VolGfx::Node* wrapImpl(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context);
        static void setImplParent(Ionflux::VolGfx::NodeImpl* otherImpl);
        static void updateImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context);
        static Ionflux::VolGfx::NodeDataImpl* 
        createDataImpl(Ionflux::VolGfx::NodeDataType t, const 
        Ionflux::ObjectBase::DoubleVector* newData = 0);
        static unsigned int 
        getDataImplMemSize(Ionflux::VolGfx::NodeDataImpl* dataImpl);
        static void setDataImplColorNormal(Ionflux::VolGfx::NodeDataImpl* 
        dataImpl, const Ionflux::Altjira::Color& color, const 
        Ionflux::GeoUtils::Vector3& normal);
        static Ionflux::VolGfx::NodeDataType 
        getImplDataType(Ionflux::VolGfx::NodeImpl* otherImpl);
        static bool hasImplDataType(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::NodeDataType dataType);
        static Ionflux::VolGfx::NodeDataImpl* 
        getImplData(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::NodeDataType dataType);
        static bool dataTypeHasVoxelClassInfo(Ionflux::VolGfx::NodeDataType
        dataType);
        static bool hasImplVoxelClassInfo(Ionflux::VolGfx::NodeImpl* 
        otherImpl);
        static Ionflux::VolGfx::VoxelClassID 
        getImplVoxelClass(Ionflux::VolGfx::NodeImpl* otherImpl);
        static bool hasImplVoxelClass(Ionflux::VolGfx::NodeImpl* otherImpl,
        Ionflux::VolGfx::VoxelClassID mask);
        static Ionflux::VolGfx::VoxelClassID 
        setImplVoxelClass(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::VoxelClassID mask, bool enable = true, 
        Ionflux::VolGfx::NodeDataType createDataType = DATA_TYPE_UNKNOWN);
        static unsigned int setImplVoxelClass(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, 
        Ionflux::VolGfx::VoxelClassID mask, bool enable = true, 
        Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = true, 
        Ionflux::VolGfx::NodeDataType createDataType = DATA_TYPE_UNKNOWN);
        static bool dataTypeHasColorIndex(Ionflux::VolGfx::NodeDataType 
        dataType);
        static bool hasImplColorIndex(Ionflux::VolGfx::NodeImpl* 
        otherImpl);
        static Ionflux::VolGfx::ColorIndex 
        getImplColorIndex(Ionflux::VolGfx::NodeImpl* otherImpl);
        static Ionflux::VolGfx::ColorIndex 
        setImplColorIndex(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::ColorIndex color, Ionflux::VolGfx::NodeDataType 
        createDataType = DATA_TYPE_UNKNOWN);
        static unsigned int setImplColorIndex(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, 
        Ionflux::VolGfx::ColorIndex color, Ionflux::VolGfx::NodeFilter* 
        filter = 0, bool recursive = true, Ionflux::VolGfx::NodeDataType 
        createDataType = DATA_TYPE_UNKNOWN);
        static Ionflux::VolGfx::FaceMaskInt 
        getImplBoundaryFaces(Ionflux::VolGfx::NodeImpl* otherImpl);
        static Ionflux::VolGfx::NodeImpl* 
        getImplParent(Ionflux::VolGfx::NodeImpl* otherImpl);
        static bool isImplLeaf(Ionflux::VolGfx::NodeImpl* otherImpl);
        static Ionflux::VolGfx::LeafStatusID 
        getImplLeafStatus(Ionflux::VolGfx::NodeImpl* otherImpl);
        static bool isImplLeafOrderChild(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, int orderIndex);
        static bool isImplLeafValidChild(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, int index);
        static int getImplDepth(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context);
        static int getImplMaxDepth(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context);
        static Ionflux::VolGfx::NodeID 
        getImplNodeID(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context);
        static int getImplChildValidIndex(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::NodeImpl* childImpl);
        static int getImplChildValidIndex(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, int orderIndex);
        static int getImplChildOrderIndex(Ionflux::VolGfx::NodeImpl* 
        otherImpl, const Ionflux::VolGfx::Context* context, int index);
        static int getImplChildOrderIndex(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::NodeImpl* childImpl);
        static Ionflux::VolGfx::NodeImpl* 
        getImplChildByOrderIndex(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, int orderIndex, bool autoCreate 
        = false, bool fill0 = false);
        static int getImplNumChildNodes(Ionflux::VolGfx::NodeImpl* 
        otherImpl);
        static Ionflux::VolGfx::NodeImpl* 
        getImplChildByValidIndex(Ionflux::VolGfx::NodeImpl* otherImpl, int 
        index);
        static Ionflux::VolGfx::NodeImpl* 
        locateImplChild(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, const Ionflux::VolGfx::NodeLoc3&
        loc, int maxDepth = DEPTH_UNSPECIFIED);
        static Ionflux::VolGfx::NodeImpl* 
        locateImplChild(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, const 
        Ionflux::GeoUtils::Vector3& p, int maxDepth = DEPTH_UNSPECIFIED);
        static Ionflux::VolGfx::NodeImpl* 
        insertImplChild(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, const Ionflux::VolGfx::NodeLoc3&
        loc, int depth = DEPTH_UNSPECIFIED, bool fill0 = false, bool 
        fillTargetDepth0 = false);
        static Ionflux::VolGfx::NodeImpl* 
        insertImplChild(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, const 
        Ionflux::GeoUtils::Vector3& p, int depth = DEPTH_UNSPECIFIED, bool 
        fill0 = false, bool fillTargetDepth0 = false);
        static Ionflux::VolGfx::NodeImpl* 
        insertImplChild(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, const Ionflux::VolGfx::NodeID& 
        nodeID, bool fill0 = false, bool fillTargetDepth0 = false);
        static void mergeImplChildNodes(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, const 
        Ionflux::VolGfx::NodeImplVector& newNodes, bool fill0 = false);
        static void setImplChildByOrderIndex(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, 
        Ionflux::VolGfx::NodeImpl* newNode, int orderIndex);
        static void setImplChildByValidIndex(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::NodeImpl* newImpl, int index);
        static void setImplChildNodes(Ionflux::VolGfx::NodeImpl* otherImpl,
        Ionflux::VolGfx::Context* context, const 
        Ionflux::VolGfx::NodeImplVector& newNodes);
        static void clearImplChildNodes(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, const 
        Ionflux::VolGfx::NodeChildMask& clearNodes);
        static unsigned int pruneEmptyImpl(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, bool recursive = 
        false);
        static int fillImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, bool clearExisting = false, bool
        recursive = false, int maxDepth = DEPTH_UNSPECIFIED);
        static Ionflux::VolGfx::NodeImpl* 
        locateImplRegion(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, const Ionflux::VolGfx::Region3& 
        region, int maxDepth = DEPTH_UNSPECIFIED);
        static Ionflux::VolGfx::NodeImpl* 
        locateImplNode(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, const Ionflux::VolGfx::NodeLoc3&
        loc, int maxDepth = DEPTH_UNSPECIFIED);
        static Ionflux::VolGfx::NodeLoc3 
        getImplChildLoc(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, int orderIndex);
        static double getImplVoxelSize(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context);
        static Ionflux::VolGfx::LocInt 
        getImplVoxelSizeLoc(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context);
        static bool getImplNeighborLoc(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, int offsetX, int 
        offsetY, int offsetZ, Ionflux::VolGfx::NodeLoc3& target);
        static Ionflux::GeoUtils::Vector3 
        getImplLocation(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context);
        static void getImplRange(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, Ionflux::GeoUtils::Range3& 
        target);
        static unsigned int findImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, Ionflux::VolGfx::NodeImplVector*
        target, Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = 
        true);
        static unsigned int processImpl(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, 
        Ionflux::VolGfx::NodeProcessor* preProcessor, 
        Ionflux::VolGfx::NodeFilter* filter = 0, 
        Ionflux::VolGfx::NodeProcessor* postProcessor = 0, bool recursive =
        true);
        static Ionflux::Altjira::Color* 
        getImplColor(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, Ionflux::Altjira::ColorSet* 
        colors = 0, unsigned int colorIndexOffset = 0, unsigned int 
        colorIndexRange = 0, int colorIndex = COLOR_INDEX_UNSPECIFIED, int 
        leafColorIndex = COLOR_INDEX_UNSPECIFIED, 
        Ionflux::VolGfx::VoxelClassColorVector* voxelClassColors = 0);
        static void getImplMesh(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, Ionflux::GeoUtils::Mesh& target,
        double boxInset = Ionflux::VolGfx::Context::DEFAULT_BOX_INSET, 
        Ionflux::Altjira::ColorSet* colors = 0, unsigned int 
        colorIndexOffset = 0, unsigned int colorIndexRange = 0, int 
        colorIndex = COLOR_INDEX_UNSPECIFIED, int leafColorIndex = 
        COLOR_INDEX_UNSPECIFIED, Ionflux::VolGfx::NodeFilter* filter = 0, 
        bool recursive = false);
        static void getImplVertexAttributes(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, 
        Ionflux::GeoUtils::VertexAttribute* positionTarget = 0, 
        Ionflux::GeoUtils::VertexAttribute* colorTarget = 0, 
        Ionflux::GeoUtils::VertexAttribute* normalTarget = 0, 
        Ionflux::GeoUtils::NFaceTypeID nFaceType = 
        Ionflux::GeoUtils::NFace::TYPE_FACE, double boxInset = 
        Ionflux::VolGfx::Context::DEFAULT_BOX_INSET, 
        Ionflux::Altjira::ColorSet* colors = 0, unsigned int 
        colorIndexOffset = 0, unsigned int colorIndexRange = 0, int 
        colorIndex = COLOR_INDEX_UNSPECIFIED, int leafColorIndex = 
        COLOR_INDEX_UNSPECIFIED, Ionflux::VolGfx::VoxelClassColorVector* 
        voxelClassColors = 0, Ionflux::GeoUtils::Vector* positionOffset = 
        0, Ionflux::GeoUtils::Vector* positionScale = 0, 
        Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = false, 
        bool boundaryFacesOnly = false);
        static unsigned int getImplNumFaces(Ionflux::VolGfx::NodeImpl* 
        otherImpl, bool recursive = false);
        static double getImplFaceColorNormal(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::Altjira::Color& targetColor, 
        Ionflux::GeoUtils::Vector3& targetNormal, bool recursive = false);
        static bool voxelizeImplInsertFace(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, 
        Ionflux::GeoUtils::Face* face, Ionflux::VolGfx::SeparabilityID sep,
        bool fill0 = false);
        static unsigned int 
        voxelizeImplInsertFaces(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, const Ionflux::GeoUtils::Mesh& 
        mesh, Ionflux::VolGfx::SeparabilityID sep, bool fill0 = false);
        static unsigned int voxelizeImplFaces(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, 
        Ionflux::VolGfx::NodeProcessor* processor, int targetDepth, 
        Ionflux::VolGfx::SeparabilityID sep, bool fillTargetDepth = false, 
        bool pruneEmpty0 = false, Ionflux::GeoUtils::FaceVector* faces0 = 
        0);
        static unsigned int getImplMemSize(Ionflux::VolGfx::NodeImpl* 
        otherImpl, bool recursive = false);
        static void serializeDataImpl(Ionflux::VolGfx::NodeDataImpl* 
        dataImpl, std::string& target);
        static Ionflux::ObjectBase::DataSize getDataValueSerializedSize();
        static Ionflux::ObjectBase::DataSize 
        getDataImplSerializedSize(Ionflux::VolGfx::NodeDataType t = 
        DATA_TYPE_NULL);
        static Ionflux::ObjectBase::DataSize 
        deserializeDataImpl(Ionflux::VolGfx::NodeDataImpl* dataImpl, const 
        std::string& source, Ionflux::ObjectBase::DataSize offset = 0);
        static void deserializeDataImpl(Ionflux::VolGfx::NodeDataImpl* 
        dataImpl, Ionflux::VolGfx::IOContext& ioContext, 
        Ionflux::ObjectBase::DataSize offset = 
        Ionflux::ObjectBase::DATA_SIZE_INVALID);
        static void serializeImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, std::string& target, 
        Ionflux::ObjectBase::MagicSyllable magicSyllable = 
        MAGIC_SYLLABLE_NODE);
        static void serializeImplChildNodes(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, 
        Ionflux::VolGfx::IOContext& ioContext, int minDepth = 1, int 
        maxDepth = DEPTH_UNSPECIFIED, bool recursive = true, bool 
        serializeData = true);
        static Ionflux::ObjectBase::DataSize 
        getImplSerializedSize(Ionflux::VolGfx::NodeDataType t = 
        DATA_TYPE_NULL);
        static void serializeImplHierarchy(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, 
        Ionflux::VolGfx::IOContext& ioContext);
        static Ionflux::ObjectBase::DataSize 
        getImplHierarchyHeaderSerializedSize();
        static Ionflux::ObjectBase::DataSize 
        deserializeImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, const std::string& source, 
        Ionflux::ObjectBase::DataSize offset = 0, 
        Ionflux::ObjectBase::MagicSyllable magicSyllable = 
        MAGIC_SYLLABLE_NODE);
        static void deserializeImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, Ionflux::VolGfx::IOContext& 
        ioContext, Ionflux::ObjectBase::DataSize offset = 
        Ionflux::ObjectBase::DATA_SIZE_INVALID, 
        Ionflux::ObjectBase::MagicSyllable magicSyllable = 
        MAGIC_SYLLABLE_NODE, bool deserializeData = true, bool 
        zeroChildPointer = true, bool zeroParentPointer = true);
        static void deserializeImplChildNodes(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, 
        Ionflux::VolGfx::IOContext& ioContext, 
        Ionflux::ObjectBase::GenericPointer childPointer, int maxDepth = 
        DEPTH_UNSPECIFIED, bool recursive = true, bool deserializeData = 
        true);
        static void deserializeImplChildNodes(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, 
        Ionflux::VolGfx::IOContext& ioContext, 
        Ionflux::ObjectBase::DataSize offset, 
        Ionflux::ObjectBase::MagicSyllable magicSyllable = 
        MAGIC_SYLLABLE_NODE, int maxDepth = DEPTH_UNSPECIFIED, bool 
        recursive = true, bool deserializeData = true);
        static void deserializeImplHierarchy(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, 
        Ionflux::VolGfx::IOContext& ioContext, bool deserializeData = true,
        int maxDepth = DEPTH_UNSPECIFIED);
        static Ionflux::ObjectBase::DataSize getImplArrayStride();
        static bool intersectRayImpl(Ionflux::VolGfx::NodeImpl* otherImpl, 
        Ionflux::VolGfx::Context* context, const Ionflux::GeoUtils::Line3& 
        ray, Ionflux::VolGfx::NodeIntersection& target, double t = 
        DEFAULT_TOLERANCE);
        static unsigned int intersectRayImpl(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, const 
        Ionflux::GeoUtils::Line3& ray, 
        Ionflux::VolGfx::NodeIntersectionProcessor* processor = 0, 
        Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = true, 
        double t = DEFAULT_TOLERANCE, const 
        Ionflux::VolGfx::NodeIntersection* pcIntersection = 0, bool fill0 =
        false, bool pruneEmpty0 = false);
        static unsigned int castRayGridImpl(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, const 
        Ionflux::GeoUtils::Vector3& rayOrigin, const 
        Ionflux::GeoUtils::Vector3& rayDirection, const 
        Ionflux::GeoUtils::Vector3& originStepX, const 
        Ionflux::GeoUtils::Vector3& originStepY, unsigned int numRaysX, 
        unsigned int numRaysY, Ionflux::VolGfx::NodeIntersectionProcessor* 
        processor = 0, Ionflux::VolGfx::NodeFilter* filter = 0, bool 
        recursive = true, double t = DEFAULT_TOLERANCE, bool fill0 = false,
        bool pruneEmpty0 = false);
        static unsigned int castRayGridImpl(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, const 
        Ionflux::GeoUtils::AxisID& axis, int targetDepth = 
        DEPTH_UNSPECIFIED, double planeOffset = DEFAULT_RAY_PLANE_OFFSET, 
        Ionflux::VolGfx::NodeIntersectionProcessor* processor = 0, 
        Ionflux::VolGfx::NodeFilter* filter = 0, bool recursive = true, 
        double t = DEFAULT_TOLERANCE, bool fill0 = false, bool pruneEmpty0 
        = false);
        static unsigned int mergeImpl(Ionflux::VolGfx::NodeImpl* 
        sourceImpl, Ionflux::VolGfx::NodeImpl* targetImpl, 
        Ionflux::VolGfx::Context* context, Ionflux::VolGfx::MergePolicyID 
        childPolicy = MERGE_POLICY_KEEP_TARGET, 
        Ionflux::VolGfx::MergePolicyID dataPolicy = 
        MERGE_POLICY_KEEP_TARGET, Ionflux::VolGfx::NodeFilter* sourceFilter
        = 0, Ionflux::VolGfx::NodeFilter* targetFilter = 0, 
        Ionflux::VolGfx::NodeFilter* sourceMergeFilter = 0, bool recursive 
        = true, bool fill0 = false);
        static std::string getImplValueString(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, bool showData = 
        true);
        static void printImplDebugInfo(Ionflux::VolGfx::NodeImpl* 
        otherImpl, Ionflux::VolGfx::Context* context, bool recursive = 
        false, unsigned int indentWidth = 
        Ionflux::ObjectBase::DEFAULT_INDENT_WIDTH, char indentChar = ' ', 
        unsigned int depth = 0);
		virtual Ionflux::VolGfx::Node* copy() const;
		static Ionflux::VolGfx::Node* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::VolGfx::Node* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::VolGfx::Node* create(Ionflux::VolGfx::Context* 
		initContext, Ionflux::VolGfx::NodeImpl* initImpl = 0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setImpl(Ionflux::VolGfx::NodeImpl* newImpl);
        virtual Ionflux::VolGfx::NodeImpl* getImpl() const;
        virtual void setContext(Ionflux::VolGfx::Context* newContext);
        virtual Ionflux::VolGfx::Context* getContext() const;
};

}

}


%{
#include "ifvg/NodeSet.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class Node;

class NodeSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NodeSetClassInfo();
        virtual ~NodeSetClassInfo();
};

class NodeSet
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        NodeSet();
		NodeSet(const Ionflux::VolGfx::NodeSet& other);
        virtual ~NodeSet();
        virtual std::string getValueString() const;
		virtual Ionflux::VolGfx::NodeSet* copy() const;
		static Ionflux::VolGfx::NodeSet* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::VolGfx::NodeSet* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;        
        virtual unsigned int getNumNodes() const;
        virtual Ionflux::VolGfx::Node* getNode(unsigned int elementIndex = 
        0) const;
		virtual int findNode(Ionflux::VolGfx::Node* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::VolGfx::Node*>& getNodes();
        virtual void addNode(Ionflux::VolGfx::Node* addElement);
		virtual Ionflux::VolGfx::Node* addNode();
		virtual void addNodes(std::vector<Ionflux::VolGfx::Node*>& newNodes);
		virtual void addNodes(Ionflux::VolGfx::NodeSet* newNodes);        
        virtual void removeNode(Ionflux::VolGfx::Node* removeElement);
		virtual void removeNodeIndex(unsigned int removeIndex);
		virtual void clearNodes();
};

}

}


%{
#include "ifvg/Mesh.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class MeshClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MeshClassInfo();
        virtual ~MeshClassInfo();
};

class Mesh
: public Ionflux::GeoUtils::Mesh
{
    public:
        
        Mesh();
		Mesh(const Ionflux::VolGfx::Mesh& other);
        Mesh(Ionflux::GeoUtils::Vertex3Vector* initVerts, const 
        Ionflux::GeoUtils::FaceVector* initFaces);
        Mesh(Ionflux::GeoUtils::Vertex3Set* initVertexSource, const 
        Ionflux::GeoUtils::FaceVector* initFaces);
        virtual ~Mesh();
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::VolGfx::Mesh* copy() const;
		static Ionflux::VolGfx::Mesh* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::VolGfx::Mesh* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::VolGfx::Mesh* create(Ionflux::GeoUtils::Vertex3Vector* 
		initVerts, const Ionflux::GeoUtils::FaceVector* initFaces, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::VolGfx::Mesh* create(Ionflux::GeoUtils::Vertex3Set* 
		initVertexSource, const Ionflux::GeoUtils::FaceVector* initFaces, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
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
#include "ifvg/NodeProcessor.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class Node;

class NodeProcessorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NodeProcessorClassInfo();
        virtual ~NodeProcessorClassInfo();
};

class NodeProcessor
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::VolGfx::NodeProcessingResultID RESULT_UNKNOWN;
		static const Ionflux::VolGfx::NodeProcessingResultID RESULT_OK;
		static const Ionflux::VolGfx::NodeProcessingResultID RESULT_FAILED;
        
        NodeProcessor();
		NodeProcessor(const Ionflux::VolGfx::NodeProcessor& other);
        virtual ~NodeProcessor();
        virtual Ionflux::VolGfx::NodeProcessingResultID 
        process(Ionflux::VolGfx::NodeImpl* nodeImpl, void* userData = 0);
        virtual Ionflux::VolGfx::NodeProcessingResultID 
        process(Ionflux::VolGfx::Node* node, void* userData = 0);
        virtual Ionflux::VolGfx::NodeProcessingResultID 
        operator()(Ionflux::VolGfx::NodeImpl* nodeImpl, void* userData = 
        0);
        virtual Ionflux::VolGfx::NodeProcessingResultID 
        operator()(Ionflux::VolGfx::Node* node, void* userData = 0);
        virtual std::string getValueString() const;
        static bool checkFlags(Ionflux::VolGfx::NodeProcessingResultID 
        result, Ionflux::VolGfx::NodeProcessingResultID flags);
		virtual Ionflux::VolGfx::NodeProcessor* copy() const;
		static Ionflux::VolGfx::NodeProcessor* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::VolGfx::NodeProcessor* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}


%{
#include "ifvg/ChainableNodeProcessor.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class Node;

class ChainableNodeProcessorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ChainableNodeProcessorClassInfo();
        virtual ~ChainableNodeProcessorClassInfo();
};

class ChainableNodeProcessor
: public Ionflux::VolGfx::NodeProcessor
{
    public:
		static const Ionflux::VolGfx::NodeProcessingResultID RESULT_FINISHED;
        
        ChainableNodeProcessor();
		ChainableNodeProcessor(const Ionflux::VolGfx::ChainableNodeProcessor& other);
        virtual ~ChainableNodeProcessor();
        virtual Ionflux::VolGfx::NodeProcessingResultID 
        process(Ionflux::VolGfx::NodeImpl* nodeImpl, void* userData = 0);
        virtual Ionflux::VolGfx::NodeProcessingResultID 
        process(Ionflux::VolGfx::Node* node, void* userData = 0);
        virtual std::string getValueString() const;
		virtual Ionflux::VolGfx::ChainableNodeProcessor* copy() const;
		static Ionflux::VolGfx::ChainableNodeProcessor* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::VolGfx::ChainableNodeProcessor* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setSource(Ionflux::VolGfx::NodeProcessor* newSource);
        virtual Ionflux::VolGfx::NodeProcessor* getSource() const;
};

}

}


%{
#include "ifvg/NodeFilter.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class Context;

class NodeFilterClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NodeFilterClassInfo();
        virtual ~NodeFilterClassInfo();
};

class NodeFilter
: public Ionflux::VolGfx::ChainableNodeProcessor
{
    public:
		static const Ionflux::VolGfx::NodeProcessingResultID RESULT_PASS;
        
        NodeFilter();
		NodeFilter(const Ionflux::VolGfx::NodeFilter& other);
        NodeFilter(Ionflux::VolGfx::Context* initContext, int initMinDepth 
        = DEPTH_UNSPECIFIED, int initMaxDepth = DEPTH_UNSPECIFIED, 
        Ionflux::VolGfx::LeafStatusID initLeafStatus = NODE_ANY, 
        Ionflux::VolGfx::NodeDataType initDataType = 
        Node::DATA_TYPE_UNKNOWN, Ionflux::VolGfx::VoxelClassID 
        initVoxelClass = VOXEL_CLASS_UNDEFINED, Ionflux::GeoUtils::Range3* 
        initRegion = 0);
        virtual ~NodeFilter();
        virtual bool filter(Ionflux::VolGfx::NodeImpl* nodeImpl, void* 
        userData = 0);
        virtual bool filter(Ionflux::VolGfx::Node* node, void* userData = 
        0);
        virtual void setDepthRange(int newMinDepth = DEPTH_UNSPECIFIED, int
        newMaxDepth = DEPTH_UNSPECIFIED);
        virtual std::string getValueString() const;
		virtual Ionflux::VolGfx::NodeFilter* copy() const;
		static Ionflux::VolGfx::NodeFilter* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::VolGfx::NodeFilter* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::VolGfx::NodeFilter* create(Ionflux::VolGfx::Context* 
		initContext, int initMinDepth = DEPTH_UNSPECIFIED, int initMaxDepth = 
		DEPTH_UNSPECIFIED, Ionflux::VolGfx::LeafStatusID initLeafStatus = 
		NODE_ANY, Ionflux::VolGfx::NodeDataType initDataType = 
		Node::DATA_TYPE_UNKNOWN, Ionflux::VolGfx::VoxelClassID initVoxelClass = 
		VOXEL_CLASS_UNDEFINED, Ionflux::GeoUtils::Range3* initRegion = 0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setContext(Ionflux::VolGfx::Context* newContext);
        virtual Ionflux::VolGfx::Context* getContext() const;
        virtual void setMinDepth(int newMinDepth);
        virtual int getMinDepth() const;
        virtual void setMaxDepth(int newMaxDepth);
        virtual int getMaxDepth() const;
        virtual void setLeafStatus(Ionflux::VolGfx::LeafStatusID 
        newLeafStatus);
        virtual Ionflux::VolGfx::LeafStatusID getLeafStatus() const;
        virtual void setDataType(Ionflux::VolGfx::NodeDataType 
        newDataType);
        virtual Ionflux::VolGfx::NodeDataType getDataType() const;
        virtual void setVoxelClass(Ionflux::VolGfx::VoxelClassID 
        newVoxelClass);
        virtual Ionflux::VolGfx::VoxelClassID getVoxelClass() const;
        virtual void setRegion(Ionflux::GeoUtils::Range3* newRegion);
        virtual Ionflux::GeoUtils::Range3* getRegion() const;
};

}

}


%{
#include "ifvg/NodeVoxelizationProcessor.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class Node;

class NodeVoxelizationProcessorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NodeVoxelizationProcessorClassInfo();
        virtual ~NodeVoxelizationProcessorClassInfo();
};

class NodeVoxelizationProcessor
: public Ionflux::VolGfx::ChainableNodeProcessor
{
    public:
        
        NodeVoxelizationProcessor();
		NodeVoxelizationProcessor(const Ionflux::VolGfx::NodeVoxelizationProcessor& other);
        virtual ~NodeVoxelizationProcessor();
        virtual std::string getValueString() const;
		virtual Ionflux::VolGfx::NodeVoxelizationProcessor* copy() const;
		static Ionflux::VolGfx::NodeVoxelizationProcessor* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::VolGfx::NodeVoxelizationProcessor* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setTarget(Ionflux::VolGfx::VoxelizationTargetID 
        newTarget);
        virtual Ionflux::VolGfx::VoxelizationTargetID getTarget() const;
};

}

}


%{
#include "ifvg/NodeIntersectionProcessor.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class Context;

class NodeIntersectionProcessorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NodeIntersectionProcessorClassInfo();
        virtual ~NodeIntersectionProcessorClassInfo();
};

class NodeIntersectionProcessor
: public Ionflux::VolGfx::ChainableNodeProcessor
{
    public:
        
        NodeIntersectionProcessor();
		NodeIntersectionProcessor(const Ionflux::VolGfx::NodeIntersectionProcessor& other);
        NodeIntersectionProcessor(Ionflux::VolGfx::Context* initContext, 
        Ionflux::VolGfx::NodeDataType initHitDataType = 
        Node::DATA_TYPE_UNKNOWN, Ionflux::VolGfx::VoxelClassID 
        initVoxelClassHit = VOXEL_CLASS_UNDEFINED, 
        Ionflux::VolGfx::LeafStatusID initLeafStatus = NODE_LEAF, 
        Ionflux::GeoUtils::Line3* initRay = 0, bool initEnableBoundaryData 
        = false, int initTargetDepth = DEPTH_UNSPECIFIED, bool 
        initFillNewIntersections = true, bool 
        initPruneEmptyNewIntersections = false, bool initEnableIOB = true, 
        bool initEnableRayStabbing = false, bool initEnableWallThickness = 
        false, Ionflux::VolGfx::VoxelClassID initVoxelClassFilled = 
        VOXEL_CLASS_FILLED, Ionflux::VolGfx::VoxelClassID 
        initVoxelClassInside = VOXEL_CLASS_INSIDE, 
        Ionflux::VolGfx::VoxelClassID initVoxelClassOutside = 
        VOXEL_CLASS_OUTSIDE, Ionflux::VolGfx::VoxelClassID 
        initVoxelClassBoundary = VOXEL_CLASS_BOUNDARY, double initTolerance
        = DEFAULT_TOLERANCE, unsigned int initMinWallThickness = 0, bool 
        initFillInsideOnly = true, unsigned int 
        initMaxNumWallThicknessPasses = 0);
        virtual ~NodeIntersectionProcessor();
        virtual void clear();
        virtual void begin();
        virtual void finish();
        virtual Ionflux::VolGfx::NodeProcessingResultID 
        processIntersection(const Ionflux::VolGfx::NodeIntersection& 
        newIntersection, void* userData = 0);
        virtual void 
        setIOBData(Ionflux::VolGfx::NodeIntersectionProcessingFlags* 
        processingFlags = 0);
        virtual void 
        processWallThickness(Ionflux::VolGfx::NodeIntersectionProcessingFlags*
        processingFlags = 0);
        virtual void 
        processBoundary(Ionflux::VolGfx::NodeIntersectionProcessingFlags* 
        processingFlags = 0);
        virtual unsigned int createIntersections(const 
        Ionflux::VolGfx::NodeIntersection& intersection0, 
        Ionflux::VolGfx::NodeIntersectionVector& newIntersections, bool 
        createNear = false, bool createFar = false);
        virtual std::string getValueString() const;
        static Ionflux::VolGfx::VoxelDataIOB* getIOBData(const 
        Ionflux::VolGfx::NodeIntersection& intersection0);
		virtual Ionflux::VolGfx::NodeIntersectionProcessor* copy() const;
		static Ionflux::VolGfx::NodeIntersectionProcessor* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::VolGfx::NodeIntersectionProcessor* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::VolGfx::NodeIntersectionProcessor* 
		create(Ionflux::VolGfx::Context* initContext, 
		Ionflux::VolGfx::NodeDataType initHitDataType = Node::DATA_TYPE_UNKNOWN, 
		Ionflux::VolGfx::VoxelClassID initVoxelClassHit = VOXEL_CLASS_UNDEFINED, 
		Ionflux::VolGfx::LeafStatusID initLeafStatus = NODE_LEAF, 
		Ionflux::GeoUtils::Line3* initRay = 0, bool initEnableBoundaryData = 
		false, int initTargetDepth = DEPTH_UNSPECIFIED, bool 
		initFillNewIntersections = true, bool initPruneEmptyNewIntersections = 
		false, bool initEnableIOB = true, bool initEnableRayStabbing = false, 
		bool initEnableWallThickness = false, Ionflux::VolGfx::VoxelClassID 
		initVoxelClassFilled = VOXEL_CLASS_FILLED, Ionflux::VolGfx::VoxelClassID 
		initVoxelClassInside = VOXEL_CLASS_INSIDE, Ionflux::VolGfx::VoxelClassID 
		initVoxelClassOutside = VOXEL_CLASS_OUTSIDE, 
		Ionflux::VolGfx::VoxelClassID initVoxelClassBoundary = 
		VOXEL_CLASS_BOUNDARY, double initTolerance = DEFAULT_TOLERANCE, unsigned 
		int initMinWallThickness = 0, bool initFillInsideOnly = true, unsigned 
		int initMaxNumWallThicknessPasses = 0, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);        
        virtual unsigned int getNumIntersections() const;
        virtual Ionflux::VolGfx::NodeIntersection getIntersection(unsigned 
        int elementIndex = 0) const;
		virtual int findIntersection(const Ionflux::VolGfx::NodeIntersection& 
		needle, unsigned int occurence = 1) const;
        virtual std::vector<Ionflux::VolGfx::NodeIntersection>& 
        getIntersections();
        virtual void addIntersection(const 
        Ionflux::VolGfx::NodeIntersection& addElement);
		virtual const Ionflux::VolGfx::NodeIntersection& addIntersection();
		virtual void 
		addIntersections(std::vector<Ionflux::VolGfx::NodeIntersection>& 
		newIntersections);
		virtual void addIntersections(Ionflux::VolGfx::NodeIntersectionProcessor*
		newIntersections);        
        virtual void removeIntersection(const 
        Ionflux::VolGfx::NodeIntersection& removeElement);
		virtual void removeIntersectionIndex(unsigned int removeIndex);
		virtual void clearIntersections();
        virtual void setContext(Ionflux::VolGfx::Context* newContext);
        virtual Ionflux::VolGfx::Context* getContext() const;
        virtual void setHitDataType(Ionflux::VolGfx::NodeDataType 
        newHitDataType);
        virtual Ionflux::VolGfx::NodeDataType getHitDataType() const;
        virtual void setVoxelClassHit(Ionflux::VolGfx::VoxelClassID 
        newVoxelClassHit);
        virtual Ionflux::VolGfx::VoxelClassID getVoxelClassHit() const;
        virtual void setLeafStatus(Ionflux::VolGfx::LeafStatusID 
        newLeafStatus);
        virtual Ionflux::VolGfx::LeafStatusID getLeafStatus() const;
        virtual void setRay(Ionflux::GeoUtils::Line3* newRay);
        virtual Ionflux::GeoUtils::Line3* getRay() const;
        virtual void setEnableBoundaryData(bool newEnableBoundaryData);
        virtual bool getEnableBoundaryData() const;
        virtual void setTargetDepth(int newTargetDepth);
        virtual int getTargetDepth() const;
        virtual void setFillNewIntersections(bool newFillNewIntersections);
        virtual bool getFillNewIntersections() const;
        virtual void setPruneEmptyNewIntersections(bool 
        newPruneEmptyNewIntersections);
        virtual bool getPruneEmptyNewIntersections() const;
        virtual void setEnableIOB(bool newEnableIOB);
        virtual bool getEnableIOB() const;
        virtual void setEnableRayStabbing(bool newEnableRayStabbing);
        virtual bool getEnableRayStabbing() const;
        virtual void setEnableWallThickness(bool newEnableWallThickness);
        virtual bool getEnableWallThickness() const;
        virtual void setVoxelClassFilled(Ionflux::VolGfx::VoxelClassID 
        newVoxelClassFilled);
        virtual Ionflux::VolGfx::VoxelClassID getVoxelClassFilled() const;
        virtual void setVoxelClassInside(Ionflux::VolGfx::VoxelClassID 
        newVoxelClassInside);
        virtual Ionflux::VolGfx::VoxelClassID getVoxelClassInside() const;
        virtual void setVoxelClassOutside(Ionflux::VolGfx::VoxelClassID 
        newVoxelClassOutside);
        virtual Ionflux::VolGfx::VoxelClassID getVoxelClassOutside() const;
        virtual void setVoxelClassBoundary(Ionflux::VolGfx::VoxelClassID 
        newVoxelClassBoundary);
        virtual Ionflux::VolGfx::VoxelClassID getVoxelClassBoundary() 
        const;
        virtual void setTolerance(double newTolerance);
        virtual double getTolerance() const;
        virtual Ionflux::GeoUtils::AxisID getRayAxis() const;
        virtual void setMinWallThickness(unsigned int newMinWallThickness);
        virtual unsigned int getMinWallThickness() const;
        virtual void setFillInsideOnly(bool newFillInsideOnly);
        virtual bool getFillInsideOnly() const;
        virtual void setMaxNumWallThicknessPasses(unsigned int 
        newMaxNumWallThicknessPasses);
        virtual unsigned int getMaxNumWallThicknessPasses() const;
};

}

}


%{
#include "ifvg/NodeFillProcessor.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class Context;

class NodeFillProcessorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NodeFillProcessorClassInfo();
        virtual ~NodeFillProcessorClassInfo();
};

class NodeFillProcessor
: public Ionflux::VolGfx::ChainableNodeProcessor
{
    public:
        
        NodeFillProcessor();
		NodeFillProcessor(const Ionflux::VolGfx::NodeFillProcessor& other);
        NodeFillProcessor(Ionflux::VolGfx::Context* initContext, bool 
        initClearExisting = false, bool initRecursive = false, int 
        initMaxDepth = DEPTH_UNSPECIFIED);
        virtual ~NodeFillProcessor();
        virtual std::string getValueString() const;
		virtual Ionflux::VolGfx::NodeFillProcessor* copy() const;
		static Ionflux::VolGfx::NodeFillProcessor* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::VolGfx::NodeFillProcessor* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::VolGfx::NodeFillProcessor* 
		create(Ionflux::VolGfx::Context* initContext, bool initClearExisting = 
		false, bool initRecursive = false, int initMaxDepth = DEPTH_UNSPECIFIED, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setContext(Ionflux::VolGfx::Context* newContext);
        virtual Ionflux::VolGfx::Context* getContext() const;
        virtual void setClearExisting(bool newClearExisting);
        virtual bool getClearExisting() const;
        virtual void setRecursive(bool newRecursive);
        virtual bool getRecursive() const;
        virtual void setMaxDepth(int newMaxDepth);
        virtual int getMaxDepth() const;
};

}

}


%{
#include "ifvg/NodeIOBEvalProcessor.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class Context;

class NodeIOBEvalProcessorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NodeIOBEvalProcessorClassInfo();
        virtual ~NodeIOBEvalProcessorClassInfo();
};

class NodeIOBEvalProcessor
: public Ionflux::VolGfx::ChainableNodeProcessor
{
    public:
		static const double DEFAULT_INSIDE_VOTE_THRESHOLD;
		static const unsigned int DEFAULT_INSIDE_MIN_VOTES;
        
        NodeIOBEvalProcessor();
		NodeIOBEvalProcessor(const Ionflux::VolGfx::NodeIOBEvalProcessor& other);
        NodeIOBEvalProcessor(Ionflux::VolGfx::Context* initContext, double 
        initInsideVoteThreshold = DEFAULT_INSIDE_VOTE_THRESHOLD, unsigned 
        int initInsideMinVotes = DEFAULT_INSIDE_MIN_VOTES, bool 
        initKeepExistingClassification = false, 
        Ionflux::VolGfx::VoxelClassID initVoxelClassInside = 
        VOXEL_CLASS_INSIDE, Ionflux::VolGfx::VoxelClassID 
        initVoxelClassOutside = VOXEL_CLASS_OUTSIDE);
        virtual ~NodeIOBEvalProcessor();
        virtual std::string getValueString() const;
		virtual Ionflux::VolGfx::NodeIOBEvalProcessor* copy() const;
		static Ionflux::VolGfx::NodeIOBEvalProcessor* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::VolGfx::NodeIOBEvalProcessor* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::VolGfx::NodeIOBEvalProcessor* 
		create(Ionflux::VolGfx::Context* initContext, double 
		initInsideVoteThreshold = DEFAULT_INSIDE_VOTE_THRESHOLD, unsigned int 
		initInsideMinVotes = DEFAULT_INSIDE_MIN_VOTES, bool 
		initKeepExistingClassification = false, Ionflux::VolGfx::VoxelClassID 
		initVoxelClassInside = VOXEL_CLASS_INSIDE, Ionflux::VolGfx::VoxelClassID 
		initVoxelClassOutside = VOXEL_CLASS_OUTSIDE, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setContext(Ionflux::VolGfx::Context* newContext);
        virtual Ionflux::VolGfx::Context* getContext() const;
        virtual void setInsideVoteThreshold(double newInsideVoteThreshold);
        virtual double getInsideVoteThreshold() const;
        virtual void setInsideMinVotes(unsigned int newInsideMinVotes);
        virtual unsigned int getInsideMinVotes() const;
        virtual void setKeepExistingClassification(bool 
        newKeepExistingClassification);
        virtual bool getKeepExistingClassification() const;
        virtual void setVoxelClassInside(Ionflux::VolGfx::VoxelClassID 
        newVoxelClassInside);
        virtual Ionflux::VolGfx::VoxelClassID getVoxelClassInside() const;
        virtual void setVoxelClassOutside(Ionflux::VolGfx::VoxelClassID 
        newVoxelClassOutside);
        virtual Ionflux::VolGfx::VoxelClassID getVoxelClassOutside() const;
};

}

}


%{
#include "ifvg/NodeIOBWallThicknessProcessor.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class Context;

class NodeIOBWallThicknessProcessorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NodeIOBWallThicknessProcessorClassInfo();
        virtual ~NodeIOBWallThicknessProcessorClassInfo();
};

class NodeIOBWallThicknessProcessor
: public Ionflux::VolGfx::ChainableNodeProcessor
{
    public:
        
        NodeIOBWallThicknessProcessor();
		NodeIOBWallThicknessProcessor(const Ionflux::VolGfx::NodeIOBWallThicknessProcessor& other);
        NodeIOBWallThicknessProcessor(Ionflux::VolGfx::Context* 
        initContext, Ionflux::VolGfx::ColorIndex initMinColorIndex = 
        COLOR_INDEX_UNSPECIFIED, Ionflux::VolGfx::ColorIndex 
        initMaxColorIndex = COLOR_INDEX_UNSPECIFIED, bool 
        initEnableScanWallThickness = true, Ionflux::ObjectBase::UInt16 
        initMinWallThickness = 0, Ionflux::ObjectBase::UInt16 
        initMaxWallThickness = 0);
        virtual ~NodeIOBWallThicknessProcessor();
        virtual std::string getValueString() const;
		virtual Ionflux::VolGfx::NodeIOBWallThicknessProcessor* copy() const;
		static Ionflux::VolGfx::NodeIOBWallThicknessProcessor* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::VolGfx::NodeIOBWallThicknessProcessor* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::VolGfx::NodeIOBWallThicknessProcessor* 
		create(Ionflux::VolGfx::Context* initContext, Ionflux::VolGfx::ColorIndex
		initMinColorIndex = COLOR_INDEX_UNSPECIFIED, Ionflux::VolGfx::ColorIndex 
		initMaxColorIndex = COLOR_INDEX_UNSPECIFIED, bool 
		initEnableScanWallThickness = true, Ionflux::ObjectBase::UInt16 
		initMinWallThickness = 0, Ionflux::ObjectBase::UInt16 
		initMaxWallThickness = 0, Ionflux::ObjectBase::IFObject* parentObject = 
		0);
        virtual void setContext(Ionflux::VolGfx::Context* newContext);
        virtual Ionflux::VolGfx::Context* getContext() const;
        virtual void setMinColorIndex(Ionflux::VolGfx::ColorIndex 
        newMinColorIndex);
        virtual Ionflux::VolGfx::ColorIndex getMinColorIndex() const;
        virtual void setMaxColorIndex(Ionflux::VolGfx::ColorIndex 
        newMaxColorIndex);
        virtual Ionflux::VolGfx::ColorIndex getMaxColorIndex() const;
        virtual void setEnableScanWallThickness(bool 
        newEnableScanWallThickness);
        virtual bool getEnableScanWallThickness() const;
        virtual void setMinWallThickness(Ionflux::ObjectBase::UInt16 
        newMinWallThickness);
        virtual Ionflux::ObjectBase::UInt16 getMinWallThickness() const;
        virtual void setMaxWallThickness(Ionflux::ObjectBase::UInt16 
        newMaxWallThickness);
        virtual Ionflux::ObjectBase::UInt16 getMaxWallThickness() const;
};

}

}


// Templates

%template(NodeImplVector) std::vector<Ionflux::VolGfx::NodeImpl*>;
%template(NodeDataImplVector) std::vector<Ionflux::VolGfx::NodeDataImpl*>;
%template(NodeVector) std::vector<Ionflux::VolGfx::Node*>;
%template(NodeIntersectionVector) 
    std::vector<Ionflux::VolGfx::NodeIntersection>;
%template(VoxelClassColorVector) 
    std::vector<Ionflux::VolGfx::VoxelClassColor>;

