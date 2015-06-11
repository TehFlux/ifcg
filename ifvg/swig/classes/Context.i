/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Context.i                       Voxel tree context (interface).
 * ========================================================================== */
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
