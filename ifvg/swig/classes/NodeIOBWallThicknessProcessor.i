/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeIOBWallThicknessProcessor.i  Node inside/outside/boundary wall 
 * thickness processor (interface).
 * ========================================================================== */
%{
#include "ifvg/NodeIOBWallThicknessProcessor.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class Context;

class NodeIOBWallThicknessProcessorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NodeIOBWallThicknessProcessorClassInfo();
        virtual ~NodeIOBWallThicknessProcessorClassInfo();
};

class NodeIOBWallThicknessProcessor
: public Ionflux::VolGfx::ChainableNodeProcessor
{
    public:
        
        NodeIOBWallThicknessProcessor();
		NodeIOBWallThicknessProcessor(const Ionflux::VolGfx::NodeIOBWallThicknessProcessor& other);
        NodeIOBWallThicknessProcessor(Ionflux::VolGfx::Context* 
        initContext, Ionflux::VolGfx::ColorIndex initMinColorIndex = 
        COLOR_INDEX_UNSPECIFIED, Ionflux::VolGfx::ColorIndex 
        initMaxColorIndex = COLOR_INDEX_UNSPECIFIED, bool 
        initEnableScanWallThickness = true, Ionflux::ObjectBase::UInt16 
        initMinWallThickness = 0, Ionflux::ObjectBase::UInt16 
        initMaxWallThickness = 0);
        virtual ~NodeIOBWallThicknessProcessor();
        virtual std::string getValueString() const;
		virtual Ionflux::VolGfx::NodeIOBWallThicknessProcessor* copy() const;
		static Ionflux::VolGfx::NodeIOBWallThicknessProcessor* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::VolGfx::NodeIOBWallThicknessProcessor* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::VolGfx::NodeIOBWallThicknessProcessor* 
		create(Ionflux::VolGfx::Context* initContext, Ionflux::VolGfx::ColorIndex
		initMinColorIndex = COLOR_INDEX_UNSPECIFIED, Ionflux::VolGfx::ColorIndex 
		initMaxColorIndex = COLOR_INDEX_UNSPECIFIED, bool 
		initEnableScanWallThickness = true, Ionflux::ObjectBase::UInt16 
		initMinWallThickness = 0, Ionflux::ObjectBase::UInt16 
		initMaxWallThickness = 0, Ionflux::ObjectBase::IFObject* parentObject = 
		0);
        virtual void setContext(Ionflux::VolGfx::Context* newContext);
        virtual Ionflux::VolGfx::Context* getContext() const;
        virtual void setMinColorIndex(Ionflux::VolGfx::ColorIndex 
        newMinColorIndex);
        virtual Ionflux::VolGfx::ColorIndex getMinColorIndex() const;
        virtual void setMaxColorIndex(Ionflux::VolGfx::ColorIndex 
        newMaxColorIndex);
        virtual Ionflux::VolGfx::ColorIndex getMaxColorIndex() const;
        virtual void setEnableScanWallThickness(bool 
        newEnableScanWallThickness);
        virtual bool getEnableScanWallThickness() const;
        virtual void setMinWallThickness(Ionflux::ObjectBase::UInt16 
        newMinWallThickness);
        virtual Ionflux::ObjectBase::UInt16 getMinWallThickness() const;
        virtual void setMaxWallThickness(Ionflux::ObjectBase::UInt16 
        newMaxWallThickness);
        virtual Ionflux::ObjectBase::UInt16 getMaxWallThickness() const;
};

}

}
