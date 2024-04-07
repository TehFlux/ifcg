#ifndef IONFLUX_ALTJIRA_COLORSET
#define IONFLUX_ALTJIRA_COLORSET
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ColorSet.hpp                    Color set (header).
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

#include "altjira/types.hpp"
#include "altjira/constants.hpp"
#include "altjira/utils.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Altjira
{

class Color;

/// Class information for class ColorSet.
class ColorSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ColorSetClassInfo();
		/// Destructor.
		virtual ~ColorSetClassInfo();
};

/** Color set.
 * \ingroup geoutils
 *
 * A set of colors.
 */
class ColorSet
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Vector of colors.
		std::vector<Ionflux::Altjira::Color*> colors;
		
	public:
		/// Class information instance.
		static const ColorSetClassInfo colorSetClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ColorSet object.
		 */
		ColorSet();
		
		/** Constructor.
		 *
		 * Construct new ColorSet object.
		 *
		 * \param other Other object.
		 */
		ColorSet(const Ionflux::Altjira::ColorSet& other);
		
		/** Constructor.
		 *
		 * Construct new ColorSet object.
		 *
		 * \param initColors Colors.
		 */
		ColorSet(Ionflux::Altjira::ColorVector& initColors);
		
		/** Destructor.
		 *
		 * Destruct ColorSet object.
		 */
		virtual ~ColorSet();
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Color set.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::Altjira::ColorSet& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Color set.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::Altjira::ColorSet& other) const;
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::ColorSet& operator=(const 
		Ionflux::Altjira::ColorSet& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Altjira::ColorSet* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Altjira::ColorSet* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::Altjira::ColorSet* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new ColorSet object.
		 *
		 * \param initColors Colors.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Altjira::ColorSet* create(Ionflux::Altjira::ColorVector& 
		initColors, Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get number of colors.
		 *
		 * \return Number of colors.
		 */
		virtual unsigned int getNumColors() const;
		
		/** Get color.
		 *
		 * Get the color at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Color at specified index.
		 */
		virtual Ionflux::Altjira::Color* getColor(unsigned int elementIndex = 0) 
		const;
		
		/** Find color.
		 *
		 * Find the specified occurence of a color.
		 *
		 * \param needle Color to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the color, or -1 if the color cannot be found.
		 */
		virtual int findColor(Ionflux::Altjira::Color* needle, unsigned int 
		occurence = 1) const;
        
		/** Get vector of colors.
		 *
		 * \return vector of colors.
		 */
		virtual std::vector<Ionflux::Altjira::Color*>& getColors();
		
		/** Add color.
		 *
		 * Add a color.
		 *
		 * \param addElement Color to be added.
		 */
		virtual void addColor(Ionflux::Altjira::Color* addElement);
		
		/** Create color.
		 *
		 * Create a new color which is managed by the color set.
		 *
		 * \return New color.
		 */
		virtual Ionflux::Altjira::Color* addColor();
		
		/** Add colors.
		 *
		 * Add colors from a color vector.
		 *
		 * \param newColors colors.
		 */
		virtual void addColors(const std::vector<Ionflux::Altjira::Color*>& 
		newColors);
		
		/** Add colors.
		 *
		 * Add colors from a color set.
		 *
		 * \param newColors colors.
		 */
		virtual void addColors(Ionflux::Altjira::ColorSet* newColors);
		
		/** Remove color.
		 *
		 * Remove a color.
		 *
		 * \param removeElement Color to be removed.
		 */
		virtual void removeColor(Ionflux::Altjira::Color* removeElement);
		
		/** Remove color.
		 *
		 * Remove a color.
		 *
		 * \param removeIndex Color to be removed.
		 */
		virtual void removeColorIndex(unsigned int removeIndex);
		
		/** Clear colors.
		 *
		 * Clear all colors.
		 */
		virtual void clearColors();
};

}

}

/** \file ColorSet.hpp
 * \brief Color set (header).
 */
#endif
