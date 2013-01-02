/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ColorBand.i                     Color band (interface).
 * =========================================================================

 * This file is part of Altjira - Ionflux' Image Processing Library.
 * 
 * Altjira - Ionflux' Image Processing Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
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
#include "altjira/ColorBand.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class ColorBandClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ColorBandClassInfo();
        virtual ~ColorBandClassInfo();
};

class ColorBand
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        ColorBand();
		ColorBand(const Ionflux::Altjira::ColorBand& other);
        ColorBand(Ionflux::Altjira::ColorStopVector initColorStops);
        virtual ~ColorBand();
        virtual void clear();
        virtual std::string getString() const;
        virtual void update();
        virtual void eval(double value, Ionflux::Altjira::FloatColor& 
        target);
        virtual void eval(double value, Ionflux::Altjira::ByteColor& 
        target);
        virtual void eval(double value, Ionflux::Altjira::Color& target);
        virtual Ionflux::Altjira::Color operator()(double value);
        static Ionflux::Altjira::ColorBand* rainbow();
        static Ionflux::Altjira::ColorBand* flame();
        static Ionflux::Altjira::ColorBand* ice();
        static Ionflux::Altjira::ColorBand* terrain();
        static Ionflux::Altjira::ColorBand* heat();
        static Ionflux::Altjira::ColorBand* glow(const 
        Ionflux::Altjira::Color& color, double maxL = 1.);
		virtual Ionflux::Altjira::ColorBand* copy() const;
		static Ionflux::Altjira::ColorBand* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::Altjira::ColorBand* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);        
        virtual unsigned int getNumColorStops() const;
        virtual Ionflux::Altjira::ColorStop getColorStop(unsigned int 
        elementIndex = 0) const;
		virtual int findColorStop(Ionflux::Altjira::ColorStop needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::Altjira::ColorStop>& getColorStops();
        virtual void addColorStop(Ionflux::Altjira::ColorStop addElement);        
        virtual void removeColorStop(Ionflux::Altjira::ColorStop 
        removeElement);
		virtual void removeColorStopIndex(unsigned int removeIndex);
		virtual void clearColorStops();
};

}

}
