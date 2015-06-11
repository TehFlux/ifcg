/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFVGError.i                     IFVG error (interface).
 * ========================================================================== */
%{
#include "ifvg/IFVGError.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class IFVGError
: public std::exception
{
    public:
        
        IFVGError();
		IFVGError(const Ionflux::VolGfx::IFVGError& other);
        IFVGError(const std::string& initReason);
        virtual ~IFVGError() throw();
        virtual std::string getString() const;
        virtual const char* what() const throw();
		virtual Ionflux::VolGfx::IFVGError* copy() const;
        virtual void setReason(const std::string& newReason);
        virtual std::string getReason() const;
};

}

}
