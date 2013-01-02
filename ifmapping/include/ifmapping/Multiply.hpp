#ifndef IONFLUX_MAPPING_MULTIPLY
#define IONFLUX_MAPPING_MULTIPLY
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Multiply.hpp                    Multiply mapping (header).
 * =========================================================================
 *
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFMapping - Ionflux Mapping Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFMapping - Ionflux Mapping Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "ifmapping/types.hpp"
#include "ifmapping/Mapping.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class Multiply.
class MultiplyClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		MultiplyClassInfo();
		/// Destructor.
		virtual ~MultiplyClassInfo();
};

/** Multiply mapping.
 * \ingroup ifmapping
 *
 * Multiplies several mappings.
 */
class Multiply
: public Ionflux::Mapping::Mapping
{
	private:
		
	protected:
		/// Functions.
		std::vector<Ionflux::Mapping::Mapping*> funcs;
		
	public:
		/// Class information instance.
		static const MultiplyClassInfo multiplyClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Multiply object.
		 */
		Multiply();
		
		/** Constructor.
		 *
		 * Construct new Multiply object.
		 *
		 * \param other Other object.
		 */
		Multiply(const Ionflux::Mapping::Multiply& other);
		
		/** Constructor.
		 *
		 * Construct new Multiply object.
		 *
		 * \param initFuncs Source functions.
		 */
		Multiply(const Ionflux::Mapping::MappingVector& initFuncs);
		
		/** Destructor.
		 *
		 * Destruct Multiply object.
		 */
		virtual ~Multiply();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Call the mapping.
		 *
		 * Calls the mapping with the specified parameter.
		 *
		 * \param value Value.
		 *
		 * \return Mapped value.
		 */
		virtual Ionflux::Mapping::MappingValue 
		call(Ionflux::Mapping::MappingValue value) const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Mapping::Multiply& operator=(const 
		Ionflux::Mapping::Multiply& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::Multiply* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::Multiply* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::Mapping::Multiply* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get number of funcs.
		 *
		 * \return Number of funcs.
		 */
		virtual unsigned int getNumFuncs() const;
		
		/** Get func.
		 *
		 * Get the func at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Func at specified index.
		 */
		virtual Ionflux::Mapping::Mapping* getFunc(unsigned int elementIndex = 0)
		const;
		
		/** Find func.
		 *
		 * Find the specified occurence of a func.
		 *
		 * \param needle Func to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the func, or -1 if the func cannot be found.
		 */
		virtual int findFunc(Ionflux::Mapping::Mapping* needle, unsigned int 
		occurence = 1) const;
        
		/** Get functions.
		 *
		 * \return functions.
		 */
		virtual std::vector<Ionflux::Mapping::Mapping*>& getFuncs();
		
		/** Add func.
		 *
		 * Add a func.
		 *
		 * \param addElement Func to be added.
		 */
		virtual void addFunc(Ionflux::Mapping::Mapping* addElement);
		
		/** Remove func.
		 *
		 * Remove a func.
		 *
		 * \param removeElement Func to be removed.
		 */
		virtual void removeFunc(Ionflux::Mapping::Mapping* removeElement);
		
		/** Remove func.
		 *
		 * Remove a func.
		 *
		 * \param removeIndex Func to be removed.
		 */
		virtual void removeFuncIndex(unsigned int removeIndex);
		
		/** Clear funcs.
		 *
		 * Clear all funcs.
		 */
		virtual void clearFuncs();
};

}

}

/** \file Multiply.hpp
 * \brief Multiply mapping (header).
 */
#endif
