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
        $$function
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

$Context
$IOContext
$Node
$NodeSet
$Mesh
$NodeProcessor
$ChainableNodeProcessor
$NodeFilter
$NodeVoxelizationProcessor
$NodeIntersectionProcessor
$NodeFillProcessor
$NodeIOBEvalProcessor
$NodeIOBWallThicknessProcessor

// Templates

%template(NodeImplVector) std::vector<Ionflux::VolGfx::NodeImpl*>;
%template(NodeDataImplVector) std::vector<Ionflux::VolGfx::NodeDataImpl*>;
%template(NodeVector) std::vector<Ionflux::VolGfx::Node*>;
%template(NodeIntersectionVector) 
    std::vector<Ionflux::VolGfx::NodeIntersection>;
%template(VoxelClassColorVector) 
    std::vector<Ionflux::VolGfx::VoxelClassColor>;

