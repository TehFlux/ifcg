/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImageSet.i                      ImageSet (interface).
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
#include "altjira/ImageSet.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class Image;

class ImageSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ImageSetClassInfo();
        virtual ~ImageSetClassInfo();
};

class ImageSet
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        ImageSet();
		ImageSet(const Ionflux::Altjira::ImageSet& other);
        ImageSet(const Ionflux::Altjira::ImageVector& initImages);
        virtual ~ImageSet();
        virtual void addImages(const Ionflux::Altjira::ImageVector& 
        newImages);
        virtual std::string getString() const;
		virtual Ionflux::Altjira::ImageSet* copy() const;
		static Ionflux::Altjira::ImageSet* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Altjira::ImageSet* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);        
        virtual unsigned int getNumImages() const;
        virtual Ionflux::Altjira::Image* getImage(unsigned int elementIndex
        = 0) const;
		virtual int findImage(Ionflux::Altjira::Image* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::Altjira::Image*>& getImages();
        virtual void addImage(Ionflux::Altjira::Image* addElement);        
        virtual void removeImage(Ionflux::Altjira::Image* removeElement);
		virtual void removeImageIndex(unsigned int removeIndex);
		virtual void clearImages();
};

}

}
