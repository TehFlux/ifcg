/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * RadialGradient.i                Radial gradient (interface).
 * =========================================================================
 * 
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
#include "altjira/RadialGradient.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class RadialGradientClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        RadialGradientClassInfo();
        virtual ~RadialGradientClassInfo();
};

class RadialGradient
: public Ionflux::Altjira::Gradient
{
    public:
        
        RadialGradient();
		RadialGradient(const Ionflux::Altjira::RadialGradient& other);
        RadialGradient(double cx0, double cy0, double r0, double cx1, 
        double cy1, double r1);
        virtual ~RadialGradient();
        virtual void init(double cx0, double cy0, double r0, double cx1, 
        double cy1, double r1);
        static Ionflux::Altjira::RadialGradient* create(double cx0, double 
        cy0, double r0, double cx1, double cy1, double r1);
		virtual Ionflux::Altjira::RadialGradient* copy() const;
		static Ionflux::Altjira::RadialGradient* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Altjira::RadialGradient* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}
