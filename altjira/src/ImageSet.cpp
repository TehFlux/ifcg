/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImageSet.cpp                    ImageSet (implementation).
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

#include "altjira/ImageSet.hpp"
#include <sstream>
#include "altjira/AltjiraError.hpp"
#include "altjira/Image.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Altjira
{

ImageSetClassInfo::ImageSetClassInfo()
{
	name = "ImageSet";
	desc = "ImageSet";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

ImageSetClassInfo::~ImageSetClassInfo()
{
}

// run-time type information instance constants
const ImageSetClassInfo ImageSet::imageSetClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ImageSet::CLASS_INFO = &ImageSet::imageSetClassInfo;

ImageSet::ImageSet()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

ImageSet::ImageSet(const Ionflux::Altjira::ImageSet& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ImageSet::ImageSet(const Ionflux::Altjira::ImageVector& initImages)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addImages(initImages);
}

ImageSet::~ImageSet()
{
	clearImages();
	// TODO: Nothing ATM. ;-)
}

void ImageSet::addImages(const Ionflux::Altjira::ImageVector& newImages)
{
	for (ImageVector::const_iterator i = newImages.begin(); 
	    i != newImages.end(); i++)
	    addImage(*i);
}

std::string ImageSet::getString() const
{
	ostringstream state;
	state << getClassName();
	return state.str();
}

unsigned int ImageSet::getNumImages() const
{
    return images.size();
}

Ionflux::Altjira::Image* ImageSet::getImage(unsigned int elementIndex) 
const
{
    if (elementIndex < images.size())
		return images[elementIndex];
	return 0;
}

int ImageSet::findImage(Ionflux::Altjira::Image* needle, unsigned int 
occurence) const
{
    bool found = false;
	Ionflux::Altjira::Image* currentImage = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < images.size()))
	{
		currentImage = images[i];
		if (currentImage == needle)
        {
            if (occurence == 1)
			    found = true;
            else
                occurence--;
		} else
			i++;
	}
	if (found)
        return i;
	return -1;
}

std::vector<Ionflux::Altjira::Image*>& ImageSet::getImages()
{
    return images;
}

void ImageSet::addImage(Ionflux::Altjira::Image* addElement)
{
	addLocalRef(addElement);
	images.push_back(addElement);
}

void ImageSet::removeImage(Ionflux::Altjira::Image* removeElement)
{
    bool found = false;
	Ionflux::Altjira::Image* currentImage = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < images.size()))
	{
		currentImage = images[i];
		if (currentImage == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		images.erase(images.begin() + i);
		if (currentImage != 0)
			removeLocalRef(currentImage);
	}
}

void ImageSet::removeImageIndex(unsigned int removeIndex)
{
    if (removeIndex > images.size())
        return;
	Ionflux::Altjira::Image* e0 = images[removeIndex];
    images.erase(images.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void ImageSet::clearImages()
{
    std::vector<Ionflux::Altjira::Image*>::iterator i;
	for (i = images.begin(); i != images.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	images.clear();
}

Ionflux::Altjira::ImageSet& ImageSet::operator=(const 
Ionflux::Altjira::ImageSet& other)
{
    ImageVector v0;
    for (ImageVector::const_iterator i = other.images.begin(); 
        i != other.images.end(); i++)
    {
        addLocalRef(*i);
        v0.push_back(*i);
    }
    clearImages();
    for (ImageVector::const_iterator i = v0.begin(); 
        i != v0.end(); i++)
    {
        addImage(*i);
        removeLocalRef(*i);
    }
	return *this;
}

Ionflux::Altjira::ImageSet* ImageSet::copy() const
{
    ImageSet* newImageSet = create();
    *newImageSet = *this;
    return newImageSet;
}

Ionflux::Altjira::ImageSet* ImageSet::upcast(Ionflux::ObjectBase::IFObject*
other)
{
    return dynamic_cast<ImageSet*>(other);
}

Ionflux::Altjira::ImageSet* ImageSet::create(Ionflux::ObjectBase::IFObject*
parentObject)
{
    ImageSet* newObject = new ImageSet();
    if (newObject == 0)
    {
        throw AltjiraError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int ImageSet::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file ImageSet.cpp
 * \brief ImageSet implementation.
 */
