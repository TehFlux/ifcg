#ifndef IONFLUX_ALTJIRA_IMAGESET
#define IONFLUX_ALTJIRA_IMAGESET
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ImageSet.hpp                    ImageSet (header).
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

#include "altjira/types.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Altjira
{

class Image;

/// Class information for class ImageSet.
class ImageSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ImageSetClassInfo();
		/// Destructor.
		virtual ~ImageSetClassInfo();
};

/** Image set.
 * \ingroup ifmapping
 *
 * A collection of images.
 */
class ImageSet
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Images.
		std::vector<Ionflux::Altjira::Image*> images;
		
	public:
		/// Class information instance.
		static const ImageSetClassInfo imageSetClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ImageSet object.
		 */
		ImageSet();
		
		/** Constructor.
		 *
		 * Construct new ImageSet object.
		 *
		 * \param other Other object.
		 */
		ImageSet(const Ionflux::Altjira::ImageSet& other);
		
		/** Constructor.
		 *
		 * Construct new ImageSet object.
		 *
		 * \param initImages Images.
		 */
		ImageSet(const Ionflux::Altjira::ImageVector& initImages);
		
		/** Destructor.
		 *
		 * Destruct ImageSet object.
		 */
		virtual ~ImageSet();
		
		/** Add images.
		 *
		 * Add mappings from a vector of images.
		 *
		 * \param newImages Images.
		 */
		virtual void addImages(const Ionflux::Altjira::ImageVector& newImages);
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::ImageSet& operator=(const 
		Ionflux::Altjira::ImageSet& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Altjira::ImageSet* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Altjira::ImageSet* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::Altjira::ImageSet* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get number of images.
		 *
		 * \return Number of images.
		 */
		virtual unsigned int getNumImages() const;
		
		/** Get image.
		 *
		 * Get the image at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Image at specified index.
		 */
		virtual Ionflux::Altjira::Image* getImage(unsigned int elementIndex = 0) 
		const;
		
		/** Find image.
		 *
		 * Find the specified occurence of a image.
		 *
		 * \param needle Image to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the image, or -1 if the image cannot be found.
		 */
		virtual int findImage(Ionflux::Altjira::Image* needle, unsigned int 
		occurence = 1) const;
        
		/** Get images.
		 *
		 * \return images.
		 */
		virtual std::vector<Ionflux::Altjira::Image*>& getImages();
		
		/** Add image.
		 *
		 * Add a image.
		 *
		 * \param addElement Image to be added.
		 */
		virtual void addImage(Ionflux::Altjira::Image* addElement);
		
		/** Remove image.
		 *
		 * Remove a image.
		 *
		 * \param removeElement Image to be removed.
		 */
		virtual void removeImage(Ionflux::Altjira::Image* removeElement);
		
		/** Remove image.
		 *
		 * Remove a image.
		 *
		 * \param removeIndex Image to be removed.
		 */
		virtual void removeImageIndex(unsigned int removeIndex);
		
		/** Clear images.
		 *
		 * Clear all images.
		 */
		virtual void clearImages();
};

}

}

/** \file ImageSet.hpp
 * \brief ImageSet (header).
 */
#endif
