#ifndef IONFLUX_VOLGFX_NODEIOBEVALPROCESSOR
#define IONFLUX_VOLGFX_NODEIOBEVALPROCESSOR
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeIOBEvalProcessor.hpp        Node inside/outside/boundary evaluation 
 * processor (header).
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

/// Class information for class NodeIOBEvalProcessor.
class NodeIOBEvalProcessorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		NodeIOBEvalProcessorClassInfo();
		/// Destructor.
		virtual ~NodeIOBEvalProcessorClassInfo();
};

/** Node inside/outside/boundary evaluation processor.
 * \ingroup ifvg
 *
 * A node processor that evaluates inside/outside/boundary data. Nodes will
 * be classified as inside/outside based on ray votes cast by one or more 
 * rays using NodeIntersectionProcessor::setIOBData().
 */
class NodeIOBEvalProcessor
: public Ionflux::VolGfx::ChainableNodeProcessor
{
	private:
		
	protected:
		/// Voxel tree context.
		Ionflux::VolGfx::Context* context;
		/// Threshold for 'inside' vote (as fraction of total votes).
		double insideVoteThreshold;
		/// Minimum votes for 'inside' classification.
		unsigned int insideMinVotes;
		/// Keep existing voxel classification.
		bool keepExistingClassification;
		/// voxel class for 'inside' voxels.
		Ionflux::VolGfx::VoxelClassID voxelClassInside;
		/// voxel class for 'outside' voxels.
		Ionflux::VolGfx::VoxelClassID voxelClassOutside;
		
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
		/// Default fractional threshold for 'inside' vote.
		static const double DEFAULT_INSIDE_VOTE_THRESHOLD;
		/// Default minimum votes for 'inside' classification.
		static const unsigned int DEFAULT_INSIDE_MIN_VOTES;
		/// Class information instance.
		static const NodeIOBEvalProcessorClassInfo nodeIOBEvalProcessorClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new NodeIOBEvalProcessor object.
		 */
		NodeIOBEvalProcessor();
		
		/** Constructor.
		 *
		 * Construct new NodeIOBEvalProcessor object.
		 *
		 * \param other Other object.
		 */
		NodeIOBEvalProcessor(const Ionflux::VolGfx::NodeIOBEvalProcessor& other);
		
		/** Constructor.
		 *
		 * Construct new NodeIOBEvalProcessor object.
		 *
		 * \param initContext Voxel tree context.
		 * \param initInsideVoteThreshold Threshold for 'inside' vote (as 
		 * fraction of total votes).
		 * \param initInsideMinVotes Minimum votes for 'inside' classification.
		 * \param initKeepExistingClassification Keep existing voxel 
		 * classification.
		 * \param initVoxelClassInside voxel class for 'inside' voxels.
		 * \param initVoxelClassOutside voxel class for 'outside' voxels.
		 */
		NodeIOBEvalProcessor(Ionflux::VolGfx::Context* initContext, double 
		initInsideVoteThreshold = DEFAULT_INSIDE_VOTE_THRESHOLD, unsigned int 
		initInsideMinVotes = DEFAULT_INSIDE_MIN_VOTES, bool 
		initKeepExistingClassification = false, Ionflux::VolGfx::VoxelClassID 
		initVoxelClassInside = VOXEL_CLASS_INSIDE, Ionflux::VolGfx::VoxelClassID 
		initVoxelClassOutside = VOXEL_CLASS_OUTSIDE);
		
		/** Destructor.
		 *
		 * Destruct NodeIOBEvalProcessor object.
		 */
		virtual ~NodeIOBEvalProcessor();
		
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
		virtual Ionflux::VolGfx::NodeIOBEvalProcessor& operator=(const 
		Ionflux::VolGfx::NodeIOBEvalProcessor& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::VolGfx::NodeIOBEvalProcessor* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::VolGfx::NodeIOBEvalProcessor* 
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
		static Ionflux::VolGfx::NodeIOBEvalProcessor* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new NodeIOBEvalProcessor object.
		 *
		 * \param initContext Voxel tree context.
		 * \param initInsideVoteThreshold Threshold for 'inside' vote (as 
		 * fraction of total votes).
		 * \param initInsideMinVotes Minimum votes for 'inside' classification.
		 * \param initKeepExistingClassification Keep existing voxel 
		 * classification.
		 * \param initVoxelClassInside voxel class for 'inside' voxels.
		 * \param initVoxelClassOutside voxel class for 'outside' voxels.
		 * \param parentObject Parent object.
		 */
		static Ionflux::VolGfx::NodeIOBEvalProcessor* 
		create(Ionflux::VolGfx::Context* initContext, double 
		initInsideVoteThreshold = DEFAULT_INSIDE_VOTE_THRESHOLD, unsigned int 
		initInsideMinVotes = DEFAULT_INSIDE_MIN_VOTES, bool 
		initKeepExistingClassification = false, Ionflux::VolGfx::VoxelClassID 
		initVoxelClassInside = VOXEL_CLASS_INSIDE, Ionflux::VolGfx::VoxelClassID 
		initVoxelClassOutside = VOXEL_CLASS_OUTSIDE, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
		
		/** Get threshold for 'inside' vote (as fraction of total votes).
		 *
		 * \return Current value of threshold for 'inside' vote (as fraction of 
		 * total votes).
		 */
		virtual double getInsideVoteThreshold() const;
		
		/** Set threshold for 'inside' vote (as fraction of total votes).
		 *
		 * Set new value of threshold for 'inside' vote (as fraction of total votes).
		 *
		 * \param newInsideVoteThreshold New value of threshold for 'inside' vote
		 * (as fraction of total votes).
		 */
		virtual void setInsideVoteThreshold(double newInsideVoteThreshold);
		
		/** Get minimum votes for 'inside' classification.
		 *
		 * \return Current value of minimum votes for 'inside' classification.
		 */
		virtual unsigned int getInsideMinVotes() const;
		
		/** Set minimum votes for 'inside' classification.
		 *
		 * Set new value of minimum votes for 'inside' classification.
		 *
		 * \param newInsideMinVotes New value of minimum votes for 'inside' 
		 * classification.
		 */
		virtual void setInsideMinVotes(unsigned int newInsideMinVotes);
		
		/** Get keep existing voxel classification.
		 *
		 * \return Current value of keep existing voxel classification.
		 */
		virtual bool getKeepExistingClassification() const;
		
		/** Set keep existing voxel classification.
		 *
		 * Set new value of keep existing voxel classification.
		 *
		 * \param newKeepExistingClassification New value of keep existing voxel 
		 * classification.
		 */
		virtual void setKeepExistingClassification(bool 
		newKeepExistingClassification);
		
		/** Get voxel class for 'inside' voxels.
		 *
		 * \return Current value of voxel class for 'inside' voxels.
		 */
		virtual Ionflux::VolGfx::VoxelClassID getVoxelClassInside() const;
		
		/** Set voxel class for 'inside' voxels.
		 *
		 * Set new value of voxel class for 'inside' voxels.
		 *
		 * \param newVoxelClassInside New value of voxel class for 'inside' 
		 * voxels.
		 */
		virtual void setVoxelClassInside(Ionflux::VolGfx::VoxelClassID 
		newVoxelClassInside);
		
		/** Get voxel class for 'outside' voxels.
		 *
		 * \return Current value of voxel class for 'outside' voxels.
		 */
		virtual Ionflux::VolGfx::VoxelClassID getVoxelClassOutside() const;
		
		/** Set voxel class for 'outside' voxels.
		 *
		 * Set new value of voxel class for 'outside' voxels.
		 *
		 * \param newVoxelClassOutside New value of voxel class for 'outside' 
		 * voxels.
		 */
		virtual void setVoxelClassOutside(Ionflux::VolGfx::VoxelClassID 
		newVoxelClassOutside);
};

}

}

/** \file NodeIOBEvalProcessor.hpp
 * \brief Node inside/outside/boundary evaluation processor (header).
 */
#endif
