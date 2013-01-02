#ifndef IONFLUX_GEOUTILS_VECTOR3MAPPINGSET
#define IONFLUX_GEOUTILS_VECTOR3MAPPINGSET
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector3MappingSet.hpp           Vector3MappingSet (header).
 * =========================================================================
 *
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * GeoUtils - Ionflux' Geometry Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with GeoUtils - Ionflux' Geometry Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "geoutils/types.hpp"
#include "geoutils/Vector3Mapping.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Vector3MappingSet.
class Vector3MappingSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Vector3MappingSetClassInfo();
		/// Destructor.
		virtual ~Vector3MappingSetClassInfo();
};

/** Point mapping set.
 * \ingroup ifmapping
 *
 * A collection of point mappings.
 */
class Vector3MappingSet
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Mappings.
		std::vector<Ionflux::GeoUtils::Mapping::Vector3Mapping*> mappings;
		
	public:
		/// Class information instance.
		static const Vector3MappingSetClassInfo vector3MappingSetClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Vector3MappingSet object.
		 */
		Vector3MappingSet();
		
		/** Constructor.
		 *
		 * Construct new Vector3MappingSet object.
		 *
		 * \param other Other object.
		 */
		Vector3MappingSet(const Ionflux::GeoUtils::Vector3MappingSet& other);
		
		/** Constructor.
		 *
		 * Construct new Vector3MappingSet object.
		 *
		 * \param initMappings Mappings.
		 */
		Vector3MappingSet(const Ionflux::GeoUtils::Vector3MappingVector& 
		initMappings);
		
		/** Destructor.
		 *
		 * Destruct Vector3MappingSet object.
		 */
		virtual ~Vector3MappingSet();
		
		/** Add mappings.
		 *
		 * Add mappings from a vector of mappings.
		 *
		 * \param newMappings Mappings.
		 */
		virtual void addMappings(const Ionflux::GeoUtils::Vector3MappingVector& 
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
		virtual Ionflux::GeoUtils::Vector3MappingSet& operator=(const 
		Ionflux::GeoUtils::Vector3MappingSet& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Vector3MappingSet* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Vector3MappingSet* 
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
		static Ionflux::GeoUtils::Vector3MappingSet* 
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
		virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* getMapping(unsigned 
		int elementIndex = 0) const;
		
		/** Find mapping.
		 *
		 * Find the specified occurence of a mapping.
		 *
		 * \param needle Mapping to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the mapping, or -1 if the mapping cannot be found.
		 */
		virtual int findMapping(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
		needle, unsigned int occurence = 1) const;
        
		/** Get mappings.
		 *
		 * \return mappings.
		 */
		virtual std::vector<Ionflux::GeoUtils::Mapping::Vector3Mapping*>& 
		getMappings();
		
		/** Add mapping.
		 *
		 * Add a mapping.
		 *
		 * \param addElement Mapping to be added.
		 */
		virtual void addMapping(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
		addElement);
		
		/** Remove mapping.
		 *
		 * Remove a mapping.
		 *
		 * \param removeElement Mapping to be removed.
		 */
		virtual void removeMapping(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
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

/** \file Vector3MappingSet.hpp
 * \brief Vector3MappingSet (header).
 */
#endif
