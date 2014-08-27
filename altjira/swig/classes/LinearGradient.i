/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * LinearGradient.i                Linear gradient (interface).
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
#include "altjira/LinearGradient.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class LinearGradientClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        LinearGradientClassInfo();
        virtual ~LinearGradientClassInfo();
};

class LinearGradient
: public Ionflux::Altjira::Gradient
{
    public:
        
        LinearGradient();
		LinearGradient(const Ionflux::Altjira::LinearGradient& other);
        LinearGradient(double x0, double y0, double x1, double y1);
        virtual ~LinearGradient();
        virtual void init(double x0, double y0, double x1, double y1);
        static Ionflux::Altjira::LinearGradient* create(double x0, double 
        y0, double x1, double y1);
		virtual Ionflux::Altjira::LinearGradient* copy() const;
		static Ionflux::Altjira::LinearGradient* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Altjira::LinearGradient* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}
