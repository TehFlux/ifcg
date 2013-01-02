/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Pattern.i                       Pattern (interface).
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
#include "altjira/Pattern.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class Drawable;

class PatternClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PatternClassInfo();
        virtual ~PatternClassInfo();
};

class Pattern
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        Pattern();
		Pattern(const Ionflux::Altjira::Pattern& other);
        virtual ~Pattern();
        virtual void clear();
        virtual void translate(double tx, double ty);
        virtual void scale(double sx, double sy);
        virtual void rotate(double phi);
        virtual std::string getString() const;
		virtual Ionflux::Altjira::Pattern* copy() const;
		static Ionflux::Altjira::Pattern* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Altjira::Pattern* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

}

}
