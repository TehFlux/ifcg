/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Iterate.cpp                     Transform node: Iterate 
 * (implementation).
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

#include "geoutils/Iterate.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "ifmapping/utils.hpp"
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;
using Ionflux::Mapping::defaultStr;

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

IterateClassInfo::IterateClassInfo()
{
	name = "Iterate";
	desc = "Transform node: Iterate";
}

IterateClassInfo::~IterateClassInfo()
{
}

// public member constants
const unsigned int Iterate::INPUT_SOURCE = 0;
const unsigned int Iterate::OUTPUT_FIRST = 0;
const unsigned int Iterate::DEFAULT_NUM_ITERATIONS = 1;

// run-time type information instance constants
const IterateClassInfo Iterate::iterateClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Iterate::CLASS_INFO = &Iterate::iterateClassInfo;

Iterate::Iterate()
: numIterations(DEFAULT_NUM_ITERATIONS)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Iterate::Iterate(const Ionflux::GeoUtils::TransformNodes::Iterate& other)
: numIterations(DEFAULT_NUM_ITERATIONS)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Iterate::Iterate(unsigned int initNumIterations, const 
Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID), numIterations(initNumIterations)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Iterate::~Iterate()
{
	// TODO: Nothing ATM. ;-)
}

void Iterate::process()
{
	if (inputs.size() < 1)
	    throw GeoUtilsError("No inputs defined.");
	InputNodeSpec i0 = inputs[INPUT_SOURCE];
	if (i0.node == 0)
	    throw GeoUtilsError("Input node not set.");
	if (numIterations == 0)
	    throw GeoUtilsError("Number of iterations must be positive.");
	// Process iterations.
	/* <---- DEBUG ----- //
	Ionflux::GeoUtils::Clock c0;
	double sourceUpdateTime = 0.;
	double duplicateTime = 0.;
	// ----- DEBUG ----> */
	for (unsigned int j = 0; j < numIterations; j++)
	{
	    /* <---- DEBUG ----- //
	    c0.start();
	    // ----- DEBUG ----> */
	    i0.node->update();
	    /* <---- DEBUG ----- //
	    c0.stop();
	    sourceUpdateTime += c0.getElapsedTime();
	    // ----- DEBUG ----> */
	    TransformableGroup* g0 = i0.node->getOutput(i0.outputID);
	    if (g0 == 0)
	    {
	        std::ostringstream message;
	        message << "Input node does not supply the specified "
	            "output (node = " << i0.node->getString() << ", outputID = " 
	            << i0.outputID << ").";
	        throw GeoUtilsError(message.str());
	    }
	    /* <---- DEBUG ----- //
	    c0.start();
	    // ----- DEBUG ----> */
	    addOutput(g0);
	    /* <---- DEBUG ----- //
	    c0.stop();
	    duplicateTime += c0.getElapsedTime();
	    // ----- DEBUG ----> */
	}
	/* <---- DEBUG ----- //
	c0.stop();
	std::ostringstream message;
	message << "sourceUpdateTime = " << (sourceUpdateTime / numIterations) 
	    << " secs, duplicateTime = " << (duplicateTime / numIterations);
	log(IFLogMessage(message.str(), VL_DEBUG, this, "update"));
	// ----- DEBUG ----> */
	i0.node->clearOutputs();
}

std::string Iterate::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") << "; " 
	    << numIterations << "]";
	return status.str();
}

void Iterate::updateInputs()
{
	/* Nothing to be done here. Input nodes will be updated in the 
	   process() method. */
}

void Iterate::setNumIterations(unsigned int newNumIterations)
{
	numIterations = newNumIterations;
}

unsigned int Iterate::getNumIterations() const
{
    return numIterations;
}

Ionflux::GeoUtils::TransformNodes::Iterate& Iterate::operator=(const 
Ionflux::GeoUtils::TransformNodes::Iterate& other)
{
    TransformNode::operator=(other);
    numIterations = other.numIterations;
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Iterate* Iterate::copy() const
{
    Iterate* newIterate = create();
    *newIterate = *this;
    return newIterate;
}

Ionflux::GeoUtils::TransformNodes::Iterate* 
Iterate::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Iterate*>(other);
}

Ionflux::GeoUtils::TransformNodes::Iterate* 
Iterate::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Iterate* newObject = new Iterate();
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

/** \file Iterate.cpp
 * \brief Transform node: Iterate implementation.
 */
