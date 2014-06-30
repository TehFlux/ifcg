/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Connection.cpp                  Connection (implementation).
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

#include "geoutils/Connection.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

ConnectionClassInfo::ConnectionClassInfo()
{
	name = "Connection";
	desc = "Connection";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

ConnectionClassInfo::~ConnectionClassInfo()
{
}

// run-time type information instance constants
const ConnectionClassInfo Connection::connectionClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Connection::CLASS_INFO = &Connection::connectionClassInfo;

Connection::Connection()
: connected(false), source(0), target(0), outputID(0), inputID(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Connection::Connection(const Ionflux::GeoUtils::TransformNodes::Connection& other)
: connected(false), source(0), target(0), outputID(0), inputID(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Connection::Connection(Ionflux::GeoUtils::TransformNodes::TransformNode* 
initSource, Ionflux::GeoUtils::TransformNodes::TransformNode* initTarget, 
unsigned int outputID, unsigned int inputID, bool connectLater)
: connected(false), source(0), target(0), outputID(0), inputID(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	connect(initSource, initTarget, outputID, inputID, connectLater);
}

Connection::~Connection()
{
	clear();
}

bool Connection::connect(Ionflux::GeoUtils::TransformNodes::TransformNode* 
newSource, Ionflux::GeoUtils::TransformNodes::TransformNode* newTarget, 
unsigned int newOutputID, unsigned int newInputID, bool connectLater)
{
	if (connected)
	{
	    /* If we are already connected, check if we need to establish 
	       a new connection. */
	    if ((newSource == source) 
	        && (newTarget == target) 
	        && (newOutputID == outputID) 
	        && (newInputID == inputID))
	        // Nothing to be done.
	        return true;
	    else
	        disconnect();
	} else
	if ((newSource == 0) 
	    && (newTarget == 0) 
	    && (source != 0) 
	    && (target != 0)) 
	{
	    /* We are already set up for a connection, use the existing 
	       configuration. */
	    newTarget = target;
	    newSource = source;
	    newOutputID = outputID;
	    newInputID = inputID;
	}
	if (newSource != source)
	{
	    // Source has changed.
	    source = newSource;
	}
	if (newTarget != target)
	{
	    // Target has changed.
	    target = newTarget;
	}
	outputID = newOutputID;
	inputID = newInputID;
	if ((connectLater) 
	    || (source == 0) 
	    || (target == 0))
	    // Done for now.
	    return false;
	// Establish the connection.
	if (inputID == INPUT_NEXT_FREE)
	    inputID = target->getNumInputs();
	target->setInput(createInputNodeSpec(source, outputID), inputID);
	connected = true;
	return true;
}

bool Connection::disconnect()
{
	if (!connected)
	    return true;
	if (target == 0)
	    return false;
	target->setInput(DEFAULT_INPUT_NODE_SPEC, inputID);
	connected = false;
	return true;
}

void Connection::clear()
{
	disconnect();
	source = 0;
	target = 0;
	outputID = 0;
	inputID = INPUT_NEXT_FREE;
}

bool Connection::isConnected()
{
	// TODO: Implementation.
	return connected;
}

std::string Connection::getString() const
{
	ostringstream status;
	status << getClassName() << "[";
	if (source != 0)
	    status << source->getString() << ":" << outputID;
	else
	    status << "none:" << outputID;
	if (connected)
	    status << " --> ";
	else
	    status << " -X- ";
	if (source != 0)
	    status << target->getString() << ":" << inputID;
	else
	    status << "none:" << inputID;
	status << "]";
	return status.str();
}

bool Connection::operator==(const 
Ionflux::GeoUtils::TransformNodes::Connection& other) const
{
	// TODO: Implementation.
	return (source == other.source) && (target == other.target) && (outputID == other.outputID) && (inputID == other.inputID);
}

bool Connection::operator!=(const 
Ionflux::GeoUtils::TransformNodes::Connection& other) const
{
	// TODO: Implementation.
	return !(*this == other);
}

bool Connection::check(Ionflux::GeoUtils::TransformNodes::TransformNode* 
checkSource, Ionflux::GeoUtils::TransformNodes::TransformNode* checkTarget,
unsigned int checkOutputID, unsigned int checkInputID)
{
	if (checkTarget == 0)
	    // Target node is null, nothing to check.
	    return false;
	InputNodeSpec s0 = checkTarget->getInput(checkInputID);
	if ((s0.node == 0) 
	    || (s0.node != checkSource))
	    // Source node mismatch.
	    return false;
	if (checkOutputID != s0.outputID)
	    // Output ID mismatch.
	    return false;
	return true;
}

Ionflux::GeoUtils::TransformNodes::TransformNode* Connection::getSource() 
const
{
    return source;
}

Ionflux::GeoUtils::TransformNodes::TransformNode* Connection::getTarget() 
const
{
    return target;
}

unsigned int Connection::getOutputID() const
{
    return outputID;
}

unsigned int Connection::getInputID() const
{
    return inputID;
}

Ionflux::GeoUtils::TransformNodes::Connection& Connection::operator=(const 
Ionflux::GeoUtils::TransformNodes::Connection& other)
{
    TransformNode* s0 = other.source;
    TransformNode* t0 = other.target;
    unsigned int o0 = other.outputID;
    unsigned int i0 = other.inputID;
    bool c0 = other.connected;
    clear();
    if (c0)
        connect(s0, t0, o0, i0);
    else
        connect(s0, t0, o0, i0, true);
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Connection* Connection::copy() const
{
    Connection* newConnection = 
        new Connection();
    *newConnection = *this;
    return newConnection;
}

Ionflux::GeoUtils::TransformNodes::Connection* 
Connection::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Connection*>(other);
}

unsigned int Connection::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file Connection.cpp
 * \brief Connection implementation.
 */
