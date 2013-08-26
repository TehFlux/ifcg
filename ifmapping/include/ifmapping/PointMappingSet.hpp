#ifndef IONFLUX_MAPPING_POINTMAPPINGSET
#define IONFLUX_MAPPING_POINTMAPPINGSET
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PointMappingSet.hpp             PointMappingSet (header).
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

class PointMapping;

/// Class information for class PointMappingSet.
class PointMappingSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		PointMappingSetClassInfo();
		/// Destructor.
		virtual ~PointMappingSetClassInfo();
};

/** Point mapping set.
 * \ingroup ifmapping
 *
 * A collection of point mappings.
 */
class PointMappingSet
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Mappings.
		std::vector<Ionflux::Mapping::PointMapping*> mappings;
		
	public:
		/// Class information instance.
		static const PointMappingSetClassInfo pointMappingSetClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new PointMappingSet object.
		 */
		PointMappingSet();
		
		/** Constructor.
		 *
		 * Construct new PointMappingSet object.
		 *
		 * \param other Other object.
		 */
		PointMappingSet(const Ionflux::Mapping::PointMappingSet& other);
		
		/** Constructor.
		 *
		 * Construct new PointMappingSet object.
		 *
		 * \param initMappings Mappings.
		 */
		PointMappingSet(const Ionflux::Mapping::PointMappingVector& 
		initMappings);
		
		/** Destructor.
		 *
		 * Destruct PointMappingSet object.
		 */
		virtual ~PointMappingSet();
		
		/** Add mappings.
		 *
		 * Add mappings from a vector of mappings.
		 *
		 * \param newMappings Mappings.
		 */
		virtual void addMappings(const Ionflux::Mapping::PointMappingVector& 
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
		virtual Ionflux::Mapping::PointMappingSet& operator=(const 
		Ionflux::Mapping::PointMappingSet& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::PointMappingSet* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::PointMappingSet* 
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
		static Ionflux::Mapping::PointMappingSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
		virtual Ionflux::Mapping::PointMapping* getMapping(unsigned int 
		elementIndex = 0) const;
		
		/** Find mapping.
		 *
		 * Find the specified occurence of a mapping.
		 *
		 * \param needle Mapping to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the mapping, or -1 if the mapping cannot be found.
		 */
		virtual int findMapping(Ionflux::Mapping::PointMapping* needle, unsigned 
		int occurence = 1) const;
        
		/** Get mappings.
		 *
		 * \return mappings.
		 */
		virtual std::vector<Ionflux::Mapping::PointMapping*>& getMappings();
		
		/** Add mapping.
		 *
		 * Add a mapping.
		 *
		 * \param addElement Mapping to be added.
		 */
		virtual void addMapping(Ionflux::Mapping::PointMapping* addElement);
		
		/** Remove mapping.
		 *
		 * Remove a mapping.
		 *
		 * \param removeElement Mapping to be removed.
		 */
		virtual void removeMapping(Ionflux::Mapping::PointMapping* 
		removeElement);
		
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

/** \file PointMappingSet.hpp
 * \brief PointMappingSet (header).
 */
#endif
