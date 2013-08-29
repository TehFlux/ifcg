#ifndef IONFLUX_GEOUTILS_BATCH
#define IONFLUX_GEOUTILS_BATCH
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Batch.hpp                       Transform node: Batch (header).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * GeoUtils - Ionflux' Geometry Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with GeoUtils - Ionflux' Geometry Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Source.hpp"
#include "geoutils/ParamControl.hpp"
#include "geoutils/TransformNode.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

/// Class information for class Batch.
class BatchClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		BatchClassInfo();
		/// Destructor.
		virtual ~BatchClassInfo();
};

/** Transform node: Batch.
 * \ingroup geoutils
 *
 * Apply a processor transform node to all input groups in turn and add the
 * output groups of the processor node as output groups. It is possible to 
 * add dimensions to the Batch node. If this is done, the update() function
 * calculates the coordinates corresponding to the current index relative 
 * to the given dimensions and invokes any ParamControl objects on which a 
 * coordinate index is set with the coordinate (normalized to [0..1]) 
 * instead of the regular value. ParamControl objects on which no 
 * coordinate index is set are called with the regular (normalized) value.
 */
class Batch
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
	private:
		
	protected:
		/// Source node for the processor node.
		Ionflux::GeoUtils::TransformNodes::Source* source;
		/// Processor node.
		Ionflux::GeoUtils::TransformNodes::TransformNode* processor;
		/// Vector of parameter controls.
		std::vector<Ionflux::GeoUtils::TransformNodes::ParamControl*> controls;
		/// Input ID for the processor node.
		unsigned int processorInputID;
		/// Vector of dimensions.
		std::vector<unsigned int> dimensions;
		
		/** Update parameter controls.
		 *
		 * Update the parameter controls of this node with the specified 
		 * value.
		 *
		 * \param value Value.
		 */
		virtual void updateControls(Ionflux::Mapping::MappingValue value);
		
		/** Update parameter controls.
		 *
		 * Update the parameter controls of this node with the specified 
		 * sequence index.
		 *
		 * \param index Sequence index.
		 */
		virtual void updateControls(unsigned int index);
		
		/** Process inputs.
		 *
		 * Update the outputs of the node by processing the inputs. This 
		 * should be implemented by derived classes.
		 */
		virtual void process();
		
	public:
		/// Input ID: first.
		static const unsigned int INPUT_FIRST;
		/// Output ID: first.
		static const unsigned int OUTPUT_FIRST;
		/// Default input ID for the processor node.
		static const unsigned int DEFAULT_PROCESSOR_INPUT_ID;
		/// Class information instance.
		static const BatchClassInfo batchClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Batch object.
		 */
		Batch();
		
		/** Constructor.
		 *
		 * Construct new Batch object.
		 *
		 * \param other Other object.
		 */
		Batch(const Ionflux::GeoUtils::TransformNodes::Batch& other);
		
		/** Constructor.
		 *
		 * Construct new Batch object.
		 *
		 * \param initProcessor Processor node.
		 * \param initProcessorInputID Input ID for the processor node.
		 * \param nodeID Node ID.
		 */
		Batch(Ionflux::GeoUtils::TransformNodes::TransformNode* initProcessor, 
		unsigned int initProcessorInputID = DEFAULT_PROCESSOR_INPUT_ID, const 
		Ionflux::ObjectBase::IFObjectID& nodeID = "");
		
		/** Destructor.
		 *
		 * Destruct Batch object.
		 */
		virtual ~Batch();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Add parameter controls.
		 *
		 * Add parameter controls.
		 *
		 * \param newControls Parameter controls.
		 */
		virtual void addControls(Ionflux::GeoUtils::ParamControlVector& 
		newControls);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Batch& operator=(const 
		Ionflux::GeoUtils::TransformNodes::Batch& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Batch* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::Batch* 
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
		static Ionflux::GeoUtils::TransformNodes::Batch* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get processor node.
		 *
		 * \return Current value of processor node.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::TransformNode* getProcessor() 
		const;
		
		/** Set processor node.
		 *
		 * Set new value of processor node.
		 *
		 * \param newProcessor New value of processor node.
		 */
		virtual void 
		setProcessor(Ionflux::GeoUtils::TransformNodes::TransformNode* 
		newProcessor);
		
		/** Get number of controls.
		 *
		 * \return Number of controls.
		 */
		virtual unsigned int getNumControls() const;
		
		/** Get control.
		 *
		 * Get the control at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Control at specified index.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::ParamControl* 
		getControl(unsigned int elementIndex = 0) const;
		
		/** Find control.
		 *
		 * Find the specified occurence of a control.
		 *
		 * \param needle Control to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the control, or -1 if the control cannot be found.
		 */
		virtual int findControl(Ionflux::GeoUtils::TransformNodes::ParamControl* 
		needle, unsigned int occurence = 1) const;
        
		/** Get vector of parameter controls.
		 *
		 * \return vector of parameter controls.
		 */
		virtual std::vector<Ionflux::GeoUtils::TransformNodes::ParamControl*>& 
		getControls();
		
		/** Add control.
		 *
		 * Add a control.
		 *
		 * \param addElement Control to be added.
		 */
		virtual void addControl(Ionflux::GeoUtils::TransformNodes::ParamControl* 
		addElement);
		
		/** Remove control.
		 *
		 * Remove a control.
		 *
		 * \param removeElement Control to be removed.
		 */
		virtual void 
		removeControl(Ionflux::GeoUtils::TransformNodes::ParamControl* 
		removeElement);
		
		/** Remove control.
		 *
		 * Remove a control.
		 *
		 * \param removeIndex Control to be removed.
		 */
		virtual void removeControlIndex(unsigned int removeIndex);
		
		/** Clear controls.
		 *
		 * Clear all controls.
		 */
		virtual void clearControls();
		
		/** Get input ID for the processor node.
		 *
		 * \return Current value of input ID for the processor node.
		 */
		virtual unsigned int getProcessorInputID() const;
		
		/** Set input ID for the processor node.
		 *
		 * Set new value of input ID for the processor node.
		 *
		 * \param newProcessorInputID New value of input ID for the processor 
		 * node.
		 */
		virtual void setProcessorInputID(unsigned int newProcessorInputID);
		
		/** Get number of dimensions.
		 *
		 * \return Number of dimensions.
		 */
		virtual unsigned int getNumDimensions() const;
		
		/** Get dimension.
		 *
		 * Get the dimension at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Dimension at specified index.
		 */
		virtual unsigned int getDimension(unsigned int elementIndex = 0) const;
		
		/** Find dimension.
		 *
		 * Find the specified occurence of a dimension.
		 *
		 * \param needle Dimension to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the dimension, or -1 if the dimension cannot be 
		 * found.
		 */
		virtual int findDimension(unsigned int needle, unsigned int occurence = 
		1) const;
        
		/** Get vector of dimensions.
		 *
		 * \return vector of dimensions.
		 */
		virtual std::vector<unsigned int>& getDimensions();
		
		/** Add dimension.
		 *
		 * Add a dimension.
		 *
		 * \param addElement Dimension to be added.
		 */
		virtual void addDimension(unsigned int addElement);
		
		/** Remove dimension.
		 *
		 * Remove a dimension.
		 *
		 * \param removeElement Dimension to be removed.
		 */
		virtual void removeDimension(unsigned int removeElement);
		
		/** Remove dimension.
		 *
		 * Remove a dimension.
		 *
		 * \param removeIndex Dimension to be removed.
		 */
		virtual void removeDimensionIndex(unsigned int removeIndex);
		
		/** Clear dimensions.
		 *
		 * Clear all dimensions.
		 */
		virtual void clearDimensions();
};

}

}

}

/** \file Batch.hpp
 * \brief Transform node: Batch (header).
 */
#endif
