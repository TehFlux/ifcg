/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeProcessor.i                 Node processor (interface).
 * ========================================================================== */
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
