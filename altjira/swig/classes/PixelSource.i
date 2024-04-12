/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PixelSource.i                   Pixel source (interface).
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
#include "altjira/PixelSource.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class PixelSourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PixelSourceClassInfo();
        virtual ~PixelSourceClassInfo();
};

class PixelSource
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        PixelSource();
		PixelSource(const Ionflux::Altjira::PixelSource& other);
        virtual ~PixelSource();
        virtual unsigned int getWidth() const = 0;
        virtual unsigned int getHeight() const = 0;
        virtual bool getPixel(unsigned int x, unsigned int y, 
        Ionflux::Altjira::ByteColor& color) const = 0;
        virtual bool getPixel(unsigned int x, unsigned int y, 
        Ionflux::Altjira::FloatColor& color) const = 0;
        virtual bool getPixel(unsigned int x, unsigned int y, 
        Ionflux::Altjira::Color& color) const = 0;
		static Ionflux::Altjira::PixelSource* 
		upcast(Ionflux::ObjectBase::IFObject* other);
};

}

}
