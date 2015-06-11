/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeIntersectionProcessor.i     Node intersection processor (interface).
 * ========================================================================== */
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
