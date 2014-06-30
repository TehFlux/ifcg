#ifndef IONFLUX_MAPPING_MAPPINGSET
#define IONFLUX_MAPPING_MAPPINGSET
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * MappingSet.hpp                  MappingSet (header).
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
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Mapping
{

class Mapping;

/// Class information for class MappingSet.
class MappingSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		MappingSetClassInfo();
		/// Destructor.
		virtual ~MappingSetClassInfo();
};

/** Mapping set.
 * \ingroup ifmapping
 *
 * A collection of mappings.
 */
class MappingSet
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Mappings.
		std::vector<Ionflux::Mapping::Mapping*> mappings;
		
	public:
		/// Class information instance.
		static const MappingSetClassInfo mappingSetClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new MappingSet object.
		 */
		MappingSet();
		
		/** Constructor.
		 *
		 * Construct new MappingSet object.
		 *
		 * \param other Other object.
		 */
		MappingSet(const Ionflux::Mapping::MappingSet& other);
		
		/** Constructor.
		 *
		 * Construct new MappingSet object.
		 *
		 * \param initMappings Mappings.
		 */
		MappingSet(const Ionflux::Mapping::MappingVector& initMappings);
		
		/** Destructor.
		 *
		 * Destruct MappingSet object.
		 */
		virtual ~MappingSet();
		
		/** Add mappings.
		 *
		 * Add mappings from a vector of mappings.
		 *
		 * \param newMappings Mappings.
		 */
		virtual void addMappings(const Ionflux::Mapping::MappingVector& 
		newMappings);
		
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
		virtual Ionflux::Mapping::MappingSet& operator=(const 
		Ionflux::Mapping::MappingSet& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::MappingSet* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::MappingSet* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
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
		static Ionflux::Mapping::MappingSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get number of mappings.
		 *
		 * \return Number of mappings.
		 */
		virtual unsigned int getNumMappings() const;
		
		/** Get mapping.
		 *
		 * Get the mapping at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Mapping at specified index.
		 */
		virtual Ionflux::Mapping::Mapping* getMapping(unsigned int elementIndex =
		0) const;
		
		/** Find mapping.
		 *
		 * Find the specified occurence of a mapping.
		 *
		 * \param needle Mapping to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the mapping, or -1 if the mapping cannot be found.
		 */
		virtual int findMapping(Ionflux::Mapping::Mapping* needle, unsigned int 
		occurence = 1) const;
        
		/** Get mappings.
		 *
		 * \return mappings.
		 */
		virtual std::vector<Ionflux::Mapping::Mapping*>& getMappings();
		
		/** Add mapping.
		 *
		 * Add a mapping.
		 *
		 * \param addElement Mapping to be added.
		 */
		virtual void addMapping(Ionflux::Mapping::Mapping* addElement);
		
		/** Remove mapping.
		 *
		 * Remove a mapping.
		 *
		 * \param removeElement Mapping to be removed.
		 */
		virtual void removeMapping(Ionflux::Mapping::Mapping* removeElement);
		
		/** Remove mapping.
		 *
		 * Remove a mapping.
		 *
		 * \param removeIndex Mapping to be removed.
		 */
		virtual void removeMappingIndex(unsigned int removeIndex);
		
		/** Clear mappings.
		 *
		 * Clear all mappings.
		 */
		virtual void clearMappings();
};

}

}

/** \file MappingSet.hpp
 * \brief MappingSet (header).
 */
#endif
