#ifndef IONFLUX_ALTJIRA_PATTERN
#define IONFLUX_ALTJIRA_PATTERN
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Pattern.hpp                     Pattern (header).
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

#include <cairo.h>
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Altjira
{

class Drawable;

/// Class information for class Pattern.
class PatternClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		PatternClassInfo();
		/// Destructor.
		virtual ~PatternClassInfo();
};

/** Pattern.
 * \ingroup geoutils
 *
 * A pattern to be used in drawing operations.
 */
class Pattern
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Cairo pattern.
		cairo_pattern_t* pattern;
		
		/** Transform.
		 *
		 * Transform the pattern coordinate system using the specified matrix.
		 *
		 * \param m Matrix.
		 */
		virtual void transform(cairo_matrix_t& m);
		
	public:
	    // Friend classes.
	    friend class Drawable;
	    
		/// Class information instance.
		static const PatternClassInfo patternClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Pattern object.
		 */
		Pattern();
		
		/** Constructor.
		 *
		 * Construct new Pattern object.
		 *
		 * \param other Other object.
		 */
		Pattern(const Ionflux::Altjira::Pattern& other);
		
		/** Destructor.
		 *
		 * Destruct Pattern object.
		 */
		virtual ~Pattern();
		
		/** Clear.
		 *
		 * Free resources associated with the pattern.
		 */
		virtual void clear();
		
		/** Translate.
		 *
		 * Translate the pattern coordinate origin.
		 *
		 * \param tx Translation (X).
		 * \param ty Translation (Y).
		 */
		virtual void translate(double tx, double ty);
		
		/** Scale.
		 *
		 * Scale the pattern coordinate system.
		 *
		 * \param sx Scale factor (X).
		 * \param sy Scale factor (Y).
		 */
		virtual void scale(double sx, double sy);
		
		/** Rotate.
		 *
		 * Rotate the pattern coordinate system.
		 *
		 * \param phi Rotation angle.
		 */
		virtual void rotate(double phi);
		
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
		virtual Ionflux::Altjira::Pattern& operator=(const 
		Ionflux::Altjira::Pattern& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Altjira::Pattern* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Altjira::Pattern* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::Altjira::Pattern* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
};

}

}

/** \file Pattern.hpp
 * \brief Pattern (header).
 */
#endif
