/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Batch.cpp                       Transform node: Batch (implementation).
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

#include "geoutils/Batch.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "geoutils/GeoUtilsError.hpp"
#include "ifmapping/utils.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;
using Ionflux::Mapping::defaultStr;

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

BatchClassInfo::BatchClassInfo()
{
	name = "Batch";
	desc = "Transform node: Batch";
}

BatchClassInfo::~BatchClassInfo()
{
}

// public member constants
const unsigned int Batch::INPUT_FIRST = 0;
const unsigned int Batch::OUTPUT_FIRST = 0;
const unsigned int Batch::DEFAULT_PROCESSOR_INPUT_ID = 0;

// run-time type information instance constants
const BatchClassInfo Batch::batchClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Batch::CLASS_INFO = &Batch::batchClassInfo;

Batch::Batch()
: source(0), processor(0), processorInputID(DEFAULT_PROCESSOR_INPUT_ID)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	source = Source::create();
	addLocalRef(source);
}

Batch::Batch(const Ionflux::GeoUtils::TransformNodes::Batch& other)
: source(0), processor(0), processorInputID(DEFAULT_PROCESSOR_INPUT_ID)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Batch::Batch(Ionflux::GeoUtils::TransformNodes::TransformNode* 
initProcessor, unsigned int initProcessorInputID, const 
Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID), source(0), processor(0), 
processorInputID(initProcessorInputID)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	source = Source::create();
	addLocalRef(source);
	setProcessor(initProcessor);
}

Batch::~Batch()
{
	clearControls();
	clearDimensions();
	// TODO: Nothing ATM. ;-)
}

void Batch::updateControls(Ionflux::Mapping::MappingValue value)
{
	for (ParamControlVector::const_iterator i = 
	    controls.begin(); i != controls.end(); i++)
	{
	    ParamControl* c0 = *i;
	    if (c0 == 0)
	        throw GeoUtilsError("[Batch::updateControls] "
	            "Parameter control is null!");
	    (*c0)(value);
	}
}

void Batch::updateControls(unsigned int index)
{
	double seqR = static_cast<double>(index) 
	    / (inputs.size() - 1);
	if (dimensions.size() == 0)
	{
	    // linear mode
	    updateControls(seqR);
	    return;
	}
	// array mode
	std::ostringstream status;
	Ionflux::ObjectBase::UIntVector coords;
	Ionflux::ObjectBase::DoubleVector coordsRel;
	seqToCoords(index, dimensions, coords);
	getCoordsRel(coords, dimensions, coordsRel);
	if (coordsRel.size() != coords.size())
	{
	    status << "[Batch::updateControls] " 
	        "Unexpected number of relative coordinates "
	        "(numCoordsRel = " << coordsRel.size() 
	        << ", numCoords = " << coords.size() << ")!";
	    throw GeoUtilsError(status.str());
	}
	for (ParamControlVector::const_iterator i = 
	    controls.begin(); i != controls.end(); i++)
	{
	    ParamControl* c0 = *i;
	    if (c0 == 0)
	        throw GeoUtilsError("[Batch::updateControls] "
	            "Parameter control is null!");
	    unsigned int ci0 = c0->getCoord();
	    if (ci0 == COORDINATE_NOT_SET)
	        // Use normalized sequence index to update parameter control.
	        (*c0)(seqR);
	    else
	    {
	        // Use normalized coordinate to update parameter control.
	        if (ci0 >= coordsRel.size())
	        {
	            status.str("");
	            status << "[Batch::updateControls] " 
	                "Parameter control has invalid coordinate index "
	                "(index = " << ci0 << ", numCoordsRel = " 
	                << coordsRel.size() << ", numDimensions = " 
	                << dimensions.size() << ", numCoords = " 
	                << coords.size() << ", " << (*c0) << ")!";
	            throw GeoUtilsError(status.str());
	        }
	        (*c0)(coordsRel[ci0]);
	    }
	}
}

void Batch::process()
{
	if (processor == 0)
	    throw GeoUtilsError("[Batch::process] Processor node not set.");
	clearInputGroups();
	// Process input groups.
	/* <---- DEBUG ----- //
	ostringstream message;
	message << "Number of inputs: " << inputs.size();
	log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	// ----- DEBUG ----> */
	unsigned int k = 0;
	for (Ionflux::GeoUtils::TransformableGroupVector::iterator i = 
	    inputCache.begin(); i != inputCache.end(); i++)
	{
	    if (controls.size() > 0)
	        updateControls(k);
	    TransformableGroup* o0 = *i;
	    /* Set up the processor node and run it. 
	       No need to duplicate the input group here since Source will 
	       do it. */
	    /* <---- DEBUG ----- //
	    message.str("");
	    message << "Number of elements in input group: " 
	        << o0->getNumItems() << ", bounds = " << o0->getBounds();
	    log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	    // ----- DEBUG ----> */
	    if (source == 0)
	        throw GeoUtilsError("Source is null!");
	    source->setSource(o0);
	    processor->setInput(createInputNodeSpec(source, 0), 
	        processorInputID);
	    processor->update();
	    for (unsigned int j = 0; j < processor->getNumOutputs(); j++)
	    {
	        TransformableGroup* g0 = processor->getOutput(j);
	        /* <---- DEBUG ----- //
	        message.str("");
	        message << "Number of elements in output group: " 
	            << g0->getNumItems() << ", bounds = " << g0->getBounds();
	        log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	        // ----- DEBUG ----> */
	        addOutput(g0);
	    }
	    processor->clearOutputs();
	    k++;
	}
	// Clear the link to the processor node.
	processor->setInput(createInputNodeSpec(0, 0), processorInputID);
	/* <---- DEBUG ----- //
	message.str("");
	message << "Number of outputs: " << outputs.size();
	log(IFLogMessage(message.str(), VL_DEBUG, this, "process"));
	// ----- DEBUG ----> */
}

std::string Batch::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") << "; ";
	if (processor != 0)
	    status << (*processor);
	else
	    status << "<none>";
	status << ":" << processorInputID << "]";
	return status.str();
}

void Batch::addControls(Ionflux::GeoUtils::ParamControlVector& newControls)
{
	for (ParamControlVector::iterator i = newControls.begin(); 
	    i != newControls.end(); i++)
	    addControl(*i);
}

void Batch::setProcessor(Ionflux::GeoUtils::TransformNodes::TransformNode* 
newProcessor)
{
	processor = newProcessor;
}

Ionflux::GeoUtils::TransformNodes::TransformNode* Batch::getProcessor() 
const
{
    return processor;
}

unsigned int Batch::getNumControls() const
{
    return controls.size();
}

Ionflux::GeoUtils::TransformNodes::ParamControl* Batch::getControl(unsigned
int elementIndex) const
{
    if (elementIndex < controls.size())
		return controls[elementIndex];
	return 0;
}

int Batch::findControl(Ionflux::GeoUtils::TransformNodes::ParamControl* 
needle, unsigned int occurence) const
{
    bool found = false;
	Ionflux::GeoUtils::TransformNodes::ParamControl* currentControl = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < controls.size()))
	{
		currentControl = controls[i];
		if (currentControl == needle)
        {
            if (occurence == 1)
			    found = true;
            else
                occurence--;
		} else
			i++;
	}
	if (found)
        return i;
	return -1;
}

std::vector<Ionflux::GeoUtils::TransformNodes::ParamControl*>& 
Batch::getControls()
{
    return controls;
}

void Batch::addControl(Ionflux::GeoUtils::TransformNodes::ParamControl* 
addElement)
{
	addLocalRef(addElement);
	controls.push_back(addElement);
}

void Batch::removeControl(Ionflux::GeoUtils::TransformNodes::ParamControl* 
removeElement)
{
    bool found = false;
	Ionflux::GeoUtils::TransformNodes::ParamControl* currentControl = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < controls.size()))
	{
		currentControl = controls[i];
		if (currentControl == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		controls.erase(controls.begin() + i);
		if (currentControl != 0)
			removeLocalRef(currentControl);
	}
}

void Batch::removeControlIndex(unsigned int removeIndex)
{
    if (removeIndex > controls.size())
        return;
	Ionflux::GeoUtils::TransformNodes::ParamControl* e0 = controls[removeIndex];
    controls.erase(controls.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void Batch::clearControls()
{
    std::vector<Ionflux::GeoUtils::TransformNodes::ParamControl*>::iterator i;
	for (i = controls.begin(); i != controls.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	controls.clear();
}

void Batch::setProcessorInputID(unsigned int newProcessorInputID)
{
	processorInputID = newProcessorInputID;
}

unsigned int Batch::getProcessorInputID() const
{
    return processorInputID;
}

unsigned int Batch::getNumDimensions() const
{
    return dimensions.size();
}

unsigned int Batch::getDimension(unsigned int elementIndex) const
{
    if (elementIndex < dimensions.size())
		return dimensions[elementIndex];
	return 0;
}

int Batch::findDimension(unsigned int needle, unsigned int occurence) const
{
    bool found = false;
	unsigned int currentDimension = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < dimensions.size()))
	{
		currentDimension = dimensions[i];
		if (currentDimension == needle)
        {
            if (occurence == 1)
			    found = true;
            else
                occurence--;
		} else
			i++;
	}
	if (found)
        return i;
	return -1;
}

std::vector<unsigned int>& Batch::getDimensions()
{
    return dimensions;
}

void Batch::addDimension(unsigned int addElement)
{
	dimensions.push_back(addElement);
}

void Batch::removeDimension(unsigned int removeElement)
{
    bool found = false;
	unsigned int currentDimension = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < dimensions.size()))
	{
		currentDimension = dimensions[i];
		if (currentDimension == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		dimensions.erase(dimensions.begin() + i);
	}
}

void Batch::removeDimensionIndex(unsigned int removeIndex)
{
    if (removeIndex > dimensions.size())
        return;
    dimensions.erase(dimensions.begin() + removeIndex);
}

void Batch::clearDimensions()
{
    dimensions.clear();
}

Ionflux::GeoUtils::TransformNodes::Batch& Batch::operator=(const 
Ionflux::GeoUtils::TransformNodes::Batch& other)
{
    TransformNode::operator=(other);
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Batch* Batch::copy() const
{
    Batch* newBatch = create();
    *newBatch = *this;
    return newBatch;
}

Ionflux::GeoUtils::TransformNodes::Batch* 
Batch::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Batch*>(other);
}

Ionflux::GeoUtils::TransformNodes::Batch* 
Batch::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Batch* newObject = new Batch();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

}

/** \file Batch.cpp
 * \brief Transform node: Batch implementation.
 */
