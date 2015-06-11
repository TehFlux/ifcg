/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeVoxelizationProcessor.i     Node voxelization processor (interface).
 * ========================================================================== */
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
