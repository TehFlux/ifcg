#ifndef IONFLUX_VOLGFX_IOCONTEXT
#define IONFLUX_VOLGFX_IOCONTEXT
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IOContext.hpp                   I/O Context (header).
 * ========================================================================== */

#include <iostream>
#include "ifobject/types.hpp"
#include "ifobject/constants.hpp"
#include "ifvg/types.hpp"
#include "ifvg/constants.hpp"
#include "ifobject/IFIOContext.hpp"

namespace Ionflux
{

namespace VolGfx
{

/// Class information for class IOContext.
class IOContextClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		IOContextClassInfo();
		/// Destructor.
		virtual ~IOContextClassInfo();
};

/** I/O Context.
 * \ingroup ifvg
 *
 * A context that collects data that is used for serializing and 
 * deserializing node data.
 */
class IOContext
: public Ionflux::ObjectBase::IFIOContext
{
	private:
		
	protected:
		/// root node ID.
		Ionflux::VolGfx::NodeID rootNodeID;
		/// node implementation hierarchy header.
		Ionflux::VolGfx::NodeImplHierarchyHeader header;
		
	public:
		/// Class information instance.
		static const IOContextClassInfo iOContextClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new IOContext object.
		 */
		IOContext();
		
		/** Constructor.
		 *
		 * Construct new IOContext object.
		 *
		 * \param other Other object.
		 */
		IOContext(const Ionflux::VolGfx::IOContext& other);
		
		/** Destructor.
		 *
		 * Destruct IOContext object.
		 */
		virtual ~IOContext();
		
		/** Clear.
		 *
		 * Clear the I/O context and release all associated resources.
		 */
		virtual void clear();
		
		/** Print debug information.
		 *
		 * Print debug information for the I/O context.
		 *
		 * \param inputStreamVerbose show verbose information on input stream.
		 * \param outputStreamVerbose show verbose information on output stream.
		 * \param poMapSerializedVerbose show verbose information on 
		 * pointer/offset map (serialized).
		 * \param poMapCurrentVerbose show verbose information on pointer/offset 
		 * map (current).
		 */
		virtual void printDebugInfo(bool inputStreamVerbose = false, bool 
		outputStreamVerbose = false, bool poMapSerializedVerbose = false, bool 
		poMapCurrentVerbose = false);
		
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
		virtual Ionflux::VolGfx::IOContext& operator=(const 
		Ionflux::VolGfx::IOContext& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::VolGfx::IOContext* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::VolGfx::IOContext* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		
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
		static Ionflux::VolGfx::IOContext* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get root node ID.
		 *
		 * \return Current value of root node ID.
		 */
		virtual Ionflux::VolGfx::NodeID getRootNodeID() const;
		
		/** Set root node ID.
		 *
		 * Set new value of root node ID.
		 *
		 * \param newRootNodeID New value of root node ID.
		 */
		virtual void setRootNodeID(Ionflux::VolGfx::NodeID newRootNodeID);
		
		/** Get node implementation hierarchy header.
		 *
		 * \return Current value of node implementation hierarchy header.
		 */
		virtual Ionflux::VolGfx::NodeImplHierarchyHeader getHeader() const;
		
		/** Set node implementation hierarchy header.
		 *
		 * Set new value of node implementation hierarchy header.
		 *
		 * \param newHeader New value of node implementation hierarchy header.
		 */
		virtual void setHeader(const Ionflux::VolGfx::NodeImplHierarchyHeader& 
		newHeader);
};

}

}

/** \file IOContext.hpp
 * \brief I/O Context (header).
 */
#endif
