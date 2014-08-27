/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImagePattern.i                  Image pattern (interface).
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
#include "altjira/ImagePattern.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class Image;
class ColorBlender;

class ImagePatternClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ImagePatternClassInfo();
        virtual ~ImagePatternClassInfo();
};

class ImagePattern
: public Ionflux::Altjira::Pattern
{
    public:
        
        ImagePattern();
		ImagePattern(const Ionflux::Altjira::ImagePattern& other);
        ImagePattern(Ionflux::Altjira::Image* initImage, double initOffsetX
        = 0., double initOffsetY = 0.);
        virtual ~ImagePattern();
        virtual void clear();
        virtual void update();
        virtual std::string getString() const;
		virtual Ionflux::Altjira::ImagePattern* copy() const;
		static Ionflux::Altjira::ImagePattern* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Altjira::ImagePattern* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setImage(Ionflux::Altjira::Image* newImage);
        virtual Ionflux::Altjira::Image* getImage() const;
        virtual void setOffsetX(double newOffsetX);
        virtual double getOffsetX() const;
        virtual void setOffsetY(double newOffsetY);
        virtual double getOffsetY() const;
};

}

}
