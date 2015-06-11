/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ChainableNodeProcessor.i        Chainable node processor (interface).
 * ========================================================================== */
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
