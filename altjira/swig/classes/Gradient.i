/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Gradient.i                      Gradient (interface).
 * =========================================================================
 * 
 * This file is part of Altjira - Ionflux' Image Processing Library.
 * 
 * Altjira - Ionflux' Image Processing Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
 * 
 * Altjira - Ionflux' Image Processing Library is distributed in the hope 
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Altjira - Ionflux' Image Processing Library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */
%{
#include "altjira/Gradient.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class GradientClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        GradientClassInfo();
        virtual ~GradientClassInfo();
};

class Gradient
: public Ionflux::Altjira::Pattern
{
    public:
        
        Gradient();
		Gradient(const Ionflux::Altjira::Gradient& other);
        virtual ~Gradient();
        virtual void addColorStop(double offset, const 
        Ionflux::Altjira::Color& color);
        virtual unsigned int getNumColorStops() const;
        virtual void setFromColorBand(Ionflux::Altjira::ColorBand& 
        colorBand, Ionflux::Mapping::Mapping* sampleFunc = 0, unsigned int 
        numSamples = 20);
        virtual std::string getString() const;
		virtual Ionflux::Altjira::Gradient* copy() const;
		static Ionflux::Altjira::Gradient* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Altjira::Gradient* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}
