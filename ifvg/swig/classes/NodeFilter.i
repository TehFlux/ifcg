/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeFilter.i                    Node filter (interface).
 * ========================================================================== */
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
