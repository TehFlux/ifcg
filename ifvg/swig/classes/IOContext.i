/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IOContext.i                     I/O Context (interface).
 * ========================================================================== */
%{
#include "ifvg/IOContext.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class IOContextClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        IOContextClassInfo();
        virtual ~IOContextClassInfo();
};

class IOContext
: public Ionflux::ObjectBase::IFIOContext
{
    public:
        
        IOContext();
		IOContext(const Ionflux::VolGfx::IOContext& other);
        virtual ~IOContext();
        virtual void clear();
        virtual void printDebugInfo(bool inputStreamVerbose = false, bool 
        outputStreamVerbose = false, bool poMapSerializedVerbose = false, 
        bool poMapCurrentVerbose = false);
        virtual std::string getValueString() const;
		virtual Ionflux::VolGfx::IOContext* copy() const;
		static Ionflux::VolGfx::IOContext* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::VolGfx::IOContext* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setRootNodeID(Ionflux::VolGfx::NodeID newRootNodeID);
        virtual Ionflux::VolGfx::NodeID getRootNodeID() const;
        virtual void setHeader(const 
        Ionflux::VolGfx::NodeImplHierarchyHeader& newHeader);
        virtual Ionflux::VolGfx::NodeImplHierarchyHeader getHeader() const;
};

}

}
