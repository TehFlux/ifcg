#ifndef IONFLUX_VOLGFX_NODEIOBWALLTHICKNESSPROCESSOR
#define IONFLUX_VOLGFX_NODEIOBWALLTHICKNESSPROCESSOR
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeIOBWallThicknessProcessor.hpp  Node inside/outside/boundary wall 
 * thickness processor (header).
 * ========================================================================== */

#include "ifvg/types.hpp"
#include "ifvg/constants.hpp"
#include "ifvg/Node.hpp"
#include "ifvg/ChainableNodeProcessor.hpp"

namespace Ionflux
{

namespace VolGfx
{

class Context;

/// Class information for class NodeIOBWallThicknessProcessor.
class NodeIOBWallThicknessProcessorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		NodeIOBWallThicknessProcessorClassInfo();
		/// Destructor.
		virtual ~NodeIOBWallThicknessProcessorClassInfo();
};

/** Node inside/outside/boundary wall thickness processor.
 * \ingroup ifvg
 *
 * A node processor that processes wall thickness values set on the voxel 
 * inside/outside/boundary data record. If the \c enableScanWallThickness 
 * flag is set, the node processor scans nodes for the minimum and maximum 
 * positive wall thickness values and sets the corresponding properties 
 * accordingly. Otherwise, if \c minColorIndex and \c maxColorIndex are 
 * both set (i.e. not equal to COLOR_INDEX_UNSPECIFIED), the node processor
 * assigns a color index to the IOB data record of each node according to 
 * its minimum wall thickness value. The color index for each node will be 
 * picked from the range defined by \c minWallThickness and \c 
 * maxWallThickness, according to the magnitude of the minimum wall 
 * thickness value for the node.
 */
class NodeIOBWallThicknessProcessor
: public Ionflux::VolGfx::ChainableNodeProcessor
{
	private:
		
	protected:
		/// Voxel tree context.
		Ionflux::VolGfx::Context* context;
		/// Minimum color index.
		Ionflux::VolGfx::ColorIndex minColorIndex;
		/// Maximum color index.
		Ionflux::VolGfx::ColorIndex maxColorIndex;
		/// Enable scanning of wall thickness range.
		bool enableScanWallThickness;
		/// Minimum wall thickness value.
		Ionflux::ObjectBase::UInt16 minWallThickness;
		/// Maximum wall thickness value.
		Ionflux::ObjectBase::UInt16 maxWallThickness;
		
		/** Process node implementation.
		 *
		 * Process a node implementation. \c userData is expected to contain a
		 * pointer to a NodeIntersection data record for \c nodeImpl.
		 *
		 * \param nodeImpl Node implementation.
		 * \param userData User data.
		 *
		 * \return result.
		 */
		virtual Ionflux::VolGfx::NodeProcessingResultID 
		processImpl(Ionflux::VolGfx::NodeImpl* nodeImpl, void* userData = 0);
		
	public:
		/// Class information instance.
		static const NodeIOBWallThicknessProcessorClassInfo nodeIOBWallThicknessProcessorClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new NodeIOBWallThicknessProcessor object.
		 */
		NodeIOBWallThicknessProcessor();
		
		/** Constructor.
		 *
		 * Construct new NodeIOBWallThicknessProcessor object.
		 *
		 * \param other Other object.
		 */
		NodeIOBWallThicknessProcessor(const Ionflux::VolGfx::NodeIOBWallThicknessProcessor& other);
		
		/** Constructor.
		 *
		 * Construct new NodeIOBWallThicknessProcessor object.
		 *
		 * \param initContext Voxel tree context.
		 * \param initMinColorIndex Minimum color index value.
		 * \param initMaxColorIndex Maximum color index value.
		 * \param initEnableScanWallThickness Enable scanning of wall thickness 
		 * range.
		 * \param initMinWallThickness Minimum wall thickness value.
		 * \param initMaxWallThickness Maximum wall thickness value.
		 */
		NodeIOBWallThicknessProcessor(Ionflux::VolGfx::Context* initContext, 
		Ionflux::VolGfx::ColorIndex initMinColorIndex = COLOR_INDEX_UNSPECIFIED, 
		Ionflux::VolGfx::ColorIndex initMaxColorIndex = COLOR_INDEX_UNSPECIFIED, 
		bool initEnableScanWallThickness = true, Ionflux::ObjectBase::UInt16 
		initMinWallThickness = 0, Ionflux::ObjectBase::UInt16 
		initMaxWallThickness = 0);
		
		/** Destructor.
		 *
		 * Destruct NodeIOBWallThicknessProcessor object.
		 */
		virtual ~NodeIOBWallThicknessProcessor();
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::VolGfx::NodeIOBWallThicknessProcessor& operator=(const 
		Ionflux::VolGfx::NodeIOBWallThicknessProcessor& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::VolGfx::NodeIOBWallThicknessProcessor* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::VolGfx::NodeIOBWallThicknessProcessor* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::VolGfx::NodeIOBWallThicknessProcessor* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new NodeIOBWallThicknessProcessor object.
		 *
		 * \param initContext Voxel tree context.
		 * \param initMinColorIndex Minimum color index value.
		 * \param initMaxColorIndex Maximum color index value.
		 * \param initEnableScanWallThickness Enable scanning of wall thickness 
		 * range.
		 * \param initMinWallThickness Minimum wall thickness value.
		 * \param initMaxWallThickness Maximum wall thickness value.
		 * \param parentObject Parent object.
		 */
		static Ionflux::VolGfx::NodeIOBWallThicknessProcessor* 
		create(Ionflux::VolGfx::Context* initContext, Ionflux::VolGfx::ColorIndex
		initMinColorIndex = COLOR_INDEX_UNSPECIFIED, Ionflux::VolGfx::ColorIndex 
		initMaxColorIndex = COLOR_INDEX_UNSPECIFIED, bool 
		initEnableScanWallThickness = true, Ionflux::ObjectBase::UInt16 
		initMinWallThickness = 0, Ionflux::ObjectBase::UInt16 
		initMaxWallThickness = 0, Ionflux::ObjectBase::IFObject* parentObject = 
		0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get voxel tree context.
		 *
		 * \return Current value of voxel tree context.
		 */
		virtual Ionflux::VolGfx::Context* getContext() const;
		
		/** Set voxel tree context.
		 *
		 * Set new value of voxel tree context.
		 *
		 * \param newContext New value of voxel tree context.
		 */
		virtual void setContext(Ionflux::VolGfx::Context* newContext);
		
		/** Get minimum color index.
		 *
		 * \return Current value of minimum color index.
		 */
		virtual Ionflux::VolGfx::ColorIndex getMinColorIndex() const;
		
		/** Set minimum color index.
		 *
		 * Set new value of minimum color index.
		 *
		 * \param newMinColorIndex New value of minimum color index.
		 */
		virtual void setMinColorIndex(Ionflux::VolGfx::ColorIndex 
		newMinColorIndex);
		
		/** Get maximum color index.
		 *
		 * \return Current value of maximum color index.
		 */
		virtual Ionflux::VolGfx::ColorIndex getMaxColorIndex() const;
		
		/** Set maximum color index.
		 *
		 * Set new value of maximum color index.
		 *
		 * \param newMaxColorIndex New value of maximum color index.
		 */
		virtual void setMaxColorIndex(Ionflux::VolGfx::ColorIndex 
		newMaxColorIndex);
		
		/** Get enable scanning of wall thickness range.
		 *
		 * \return Current value of enable scanning of wall thickness range.
		 */
		virtual bool getEnableScanWallThickness() const;
		
		/** Set enable scanning of wall thickness range.
		 *
		 * Set new value of enable scanning of wall thickness range.
		 *
		 * \param newEnableScanWallThickness New value of enable scanning of wall
		 * thickness range.
		 */
		virtual void setEnableScanWallThickness(bool newEnableScanWallThickness);
		
		/** Get minimum wall thickness value.
		 *
		 * \return Current value of minimum wall thickness value.
		 */
		virtual Ionflux::ObjectBase::UInt16 getMinWallThickness() const;
		
		/** Set minimum wall thickness value.
		 *
		 * Set new value of minimum wall thickness value.
		 *
		 * \param newMinWallThickness New value of minimum wall thickness value.
		 */
		virtual void setMinWallThickness(Ionflux::ObjectBase::UInt16 
		newMinWallThickness);
		
		/** Get maximum wall thickness value.
		 *
		 * \return Current value of maximum wall thickness value.
		 */
		virtual Ionflux::ObjectBase::UInt16 getMaxWallThickness() const;
		
		/** Set maximum wall thickness value.
		 *
		 * Set new value of maximum wall thickness value.
		 *
		 * \param newMaxWallThickness New value of maximum wall thickness value.
		 */
		virtual void setMaxWallThickness(Ionflux::ObjectBase::UInt16 
		newMaxWallThickness);
};

}

}

/** \file NodeIOBWallThicknessProcessor.hpp
 * \brief Node inside/outside/boundary wall thickness processor (header).
 */
#endif
