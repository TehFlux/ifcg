/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeIOBEvalProcessor.i          Node inside/outside/boundary evaluation 
 * processor (interface).
 * ========================================================================== */
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
