/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ColorSet.i                      Color set (interface).
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
#include "altjira/ColorSet.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class Color;

class ColorSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ColorSetClassInfo();
        virtual ~ColorSetClassInfo();
};

class ColorSet
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        ColorSet();
		ColorSet(const Ionflux::Altjira::ColorSet& other);
        ColorSet(Ionflux::Altjira::ColorVector& initColors);
        virtual ~ColorSet();
        virtual bool operator==(const Ionflux::Altjira::ColorSet& other) 
        const;
        virtual bool operator!=(const Ionflux::Altjira::ColorSet& other) 
        const;
        virtual std::string getValueString() const;
		virtual Ionflux::Altjira::ColorSet* copy() const;
		static Ionflux::Altjira::ColorSet* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Altjira::ColorSet* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::Altjira::ColorSet* create(Ionflux::Altjira::ColorVector& 
		initColors, Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumColors() const;
        virtual Ionflux::Altjira::Color* getColor(unsigned int elementIndex
        = 0) const;
		virtual int findColor(Ionflux::Altjira::Color* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::Altjira::Color*>& getColors();
        virtual void addColor(Ionflux::Altjira::Color* addElement);
		virtual Ionflux::Altjira::Color* addColor();
		virtual void addColors(std::vector<Ionflux::Altjira::Color*>& newColors);
		virtual void addColors(Ionflux::Altjira::ColorSet* newColors);        
        virtual void removeColor(Ionflux::Altjira::Color* removeElement);
		virtual void removeColorIndex(unsigned int removeIndex);
		virtual void clearColors();
};

}

}
