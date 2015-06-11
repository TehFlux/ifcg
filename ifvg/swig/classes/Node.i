/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Node.i                          Voxel tree node (interface).
 * ========================================================================== */
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
