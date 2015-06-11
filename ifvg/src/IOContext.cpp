/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IOContext.cpp                   I/O Context (implementation).
 * ========================================================================== */

#include "ifvg/IOContext.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "ifobject/utf8.hpp"
#include "ifvg/utils.hpp"
#include "ifvg/IFVGError.hpp"

using namespace std;

namespace Ionflux
{

namespace VolGfx
{

IOContextClassInfo::IOContextClassInfo()
{
	name = "IOContext";
	desc = "I/O Context";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFIOContext::CLASS_INFO);
}

IOContextClassInfo::~IOContextClassInfo()
{
}

// run-time type information instance constants
const IOContextClassInfo IOContext::iOContextClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IOContext::CLASS_INFO = &IOContext::iOContextClassInfo;

IOContext::IOContext()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	rootNodeID = createNodeID();
	header = createNodeImplHierarchyHeader();
}

IOContext::IOContext(const Ionflux::VolGfx::IOContext& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

IOContext::~IOContext()
{
	clear();
}

void IOContext::clear()
{
	Ionflux::ObjectBase::IFIOContext::clear();
	rootNodeID = createNodeID();
	header = createNodeImplHierarchyHeader();
}

void IOContext::printDebugInfo(bool inputStreamVerbose, bool 
outputStreamVerbose, bool poMapSerializedVerbose, bool poMapCurrentVerbose)
{
	Ionflux::ObjectBase::IFIOContext::printDebugInfo(inputStreamVerbose, 
	    outputStreamVerbose, poMapSerializedVerbose, poMapCurrentVerbose);
	std::cout << "root node: [" << getNodeIDString(rootNodeID) << "]" 
	    << std::endl;
	std::cout << "header:" << std::endl 
	    << "  poMapOffset = " << header.poMapOffset << std::endl
	    << "  implArrayStride = " << header.implArrayStride << std::endl
	    << "  implSize = " << header.implSize << std::endl
	    << "  dataImplSize = " << header.dataImplSize << std::endl
	    << "  dataValueSize = " 
	        << static_cast<unsigned int>(header.dataValueSize) 
	        << std::endl
	    << "  rootNodeDepth = " 
	        << static_cast<unsigned int>(header.rootNodeDepth) 
	        << std::endl
	    << "  rootNodePointer = " << header.rootNodePointer << std::endl;
}

std::string IOContext::getValueString() const
{
	std::ostringstream status;
	status << Ionflux::ObjectBase::IFIOContext::getValueString() 
	    << ", header: [" 
	    << getNodeImplHierarchyHeaderValueString(header) << "]" 
	    << ", root: (" << getNodeIDString(rootNodeID) << ")";
	return status.str();
}

void IOContext::setRootNodeID(Ionflux::VolGfx::NodeID newRootNodeID)
{
	rootNodeID = newRootNodeID;
}

Ionflux::VolGfx::NodeID IOContext::getRootNodeID() const
{
    return rootNodeID;
}

void IOContext::setHeader(const Ionflux::VolGfx::NodeImplHierarchyHeader& 
newHeader)
{
	header = newHeader;
}

Ionflux::VolGfx::NodeImplHierarchyHeader IOContext::getHeader() const
{
    return header;
}

Ionflux::VolGfx::IOContext& IOContext::operator=(const 
Ionflux::VolGfx::IOContext& other)
{
    if (this == &other)
        return *this;
    // NOTE: IOContext should not be copied.
	return *this;
}

Ionflux::VolGfx::IOContext* IOContext::copy() const
{
    IOContext* newIOContext = create();
    *newIOContext = *this;
    return newIOContext;
}

Ionflux::VolGfx::IOContext* 
IOContext::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<IOContext*>(other);
}

Ionflux::VolGfx::IOContext* 
IOContext::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    IOContext* newObject = new IOContext();
    if (newObject == 0)
    {
        throw IFVGError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int IOContext::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file IOContext.cpp
 * \brief I/O Context implementation.
 */
