/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeFillProcessor.i             Node fill processor (interface).
 * ========================================================================== */
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
