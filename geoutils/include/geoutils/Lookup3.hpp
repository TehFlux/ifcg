#ifndef IONFLUX_GEOUTILS_LOOKUP3
#define IONFLUX_GEOUTILS_LOOKUP3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Lookup3.hpp                     Vector mapping: Lookup (header).
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
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Range.hpp"
#include "geoutils/Vector3Mapping.hpp"
#include "ifmapping/types.hpp"
#include "geoutils/Vector3Mapping.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace Mapping
{

/// Class information for class Lookup3.
class Lookup3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Lookup3ClassInfo();
		/// Destructor.
		virtual ~Lookup3ClassInfo();
};

/** Vector mapping: Lookup.
 * \ingroup geoutils
 *
 * A vector mapping that returns a value from a lookup table. The value of 
 * the parameter is used to select an entry from the table by scaling the 
 * parameter range [0...1] to the number of entries in the table. The table
 * can be either filled from a vector of values or from another mapping, 
 * which will be queried with values in the range [0...1] to obtain the 
 * values used to populate the table. If another lookup table is used as 
 * the source mapping with the exact same number of entries as the table to
 * be populated, the lookup table will become a copy of the source.
 */
class Lookup3
: public Ionflux::GeoUtils::Mapping::Vector3Mapping
{
	private:
		
	protected:
		/// Vector of entries.
		std::vector<Ionflux::GeoUtils::Vector3*> entries;
		/// Source mapping.
		Ionflux::GeoUtils::Mapping::Vector3Mapping* source;
		
	public:
		/// Default number of entries.
		static const unsigned int DEFAULT_NUM_ENTRIES;
		/// Clamp range.
		static const Ionflux::Mapping::Range CLAMP_RANGE;
		/// Class information instance.
		static const Lookup3ClassInfo lookup3ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Lookup3 object.
		 */
		Lookup3();
		
		/** Constructor.
		 *
		 * Construct new Lookup3 object.
		 *
		 * \param other Other object.
		 */
		Lookup3(const Ionflux::GeoUtils::Mapping::Lookup3& other);
		
		/** Constructor.
		 *
		 * Construct new Lookup3 object.
		 *
		 * \param initSource Source mapping.
		 * \param initNumEntries Number of entries.
		 */
		Lookup3(Ionflux::GeoUtils::Mapping::Vector3Mapping* initSource, unsigned 
		int initNumEntries = DEFAULT_NUM_ENTRIES);
		
		/** Destructor.
		 *
		 * Destruct Lookup3 object.
		 */
		virtual ~Lookup3();
		
		/** Update entries.
		 *
		 * Update the entries from the source function. The source function is
		 * called with evenly spaced parameters across the range [0...1] to 
		 * generate the specified number of entries for the lookup table. All 
		 * previously defined entries are removed.
		 *
		 * \param numEntries Number of Entries.
		 */
		virtual void update(unsigned int numEntries = DEFAULT_NUM_ENTRIES);
		
		/** Add entries.
		 *
		 * Add a number of entries from the specified vector. If there are not
		 * enough entries in the vector, reading entries resumes from the 
		 * beginning of the vector. If the number of entries specified as a 
		 * parameter is 0, the number of entries added will be equal to the 
		 * number of elements in the vector.
		 *
		 * \param newEntries Entries.
		 * \param numEntries Number of Entries.
		 */
		virtual void addEntries(const Ionflux::GeoUtils::Vector3Vector& 
		newEntries, unsigned int numEntries = 0);
		
		/** Evaluate the mapping.
		 *
		 * Evaluate the mapping with the specified parameter.
		 *
		 * \param value Value.
		 *
		 * \return Mapped value.
		 */
		virtual Ionflux::GeoUtils::Vector3 call(Ionflux::Mapping::MappingValue 
		value) const;
		
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
		virtual Ionflux::GeoUtils::Mapping::Lookup3& operator=(const 
		Ionflux::GeoUtils::Mapping::Lookup3& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Mapping::Lookup3* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Mapping::Lookup3* 
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
		static Ionflux::GeoUtils::Mapping::Lookup3* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get number of entries.
		 *
		 * \return Number of entries.
		 */
		virtual unsigned int getNumEntries() const;
		
		/** Get entry.
		 *
		 * Get the entry at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Entry at specified index.
		 */
		virtual Ionflux::GeoUtils::Vector3* getEntry(unsigned int elementIndex = 
		0) const;
		
		/** Find entry.
		 *
		 * Find the specified occurence of a entry.
		 *
		 * \param needle Entry to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the entry, or -1 if the entry cannot be found.
		 */
		virtual int findEntry(Ionflux::GeoUtils::Vector3* needle, unsigned int 
		occurence = 1) const;
        
		/** Get vector of entries.
		 *
		 * \return vector of entries.
		 */
		virtual std::vector<Ionflux::GeoUtils::Vector3*>& getEntries();
		
		/** Add entry.
		 *
		 * Add a entry.
		 *
		 * \param addElement Entry to be added.
		 */
		virtual void addEntry(Ionflux::GeoUtils::Vector3* addElement);
		
		/** Remove entry.
		 *
		 * Remove a entry.
		 *
		 * \param removeElement Entry to be removed.
		 */
		virtual void removeEntry(Ionflux::GeoUtils::Vector3* removeElement);
		
		/** Remove entry.
		 *
		 * Remove a entry.
		 *
		 * \param removeIndex Entry to be removed.
		 */
		virtual void removeEntryIndex(unsigned int removeIndex);
		
		/** Clear entries.
		 *
		 * Clear all entries.
		 */
		virtual void clearEntries();
		
		/** Get source mapping.
		 *
		 * \return Current value of source mapping.
		 */
		virtual Ionflux::GeoUtils::Mapping::Vector3Mapping* getSource() const;
		
		/** Set source mapping.
		 *
		 * Set new value of source mapping.
		 *
		 * \param newSource New value of source mapping.
		 */
		virtual void setSource(Ionflux::GeoUtils::Mapping::Vector3Mapping* 
		newSource);
};

}

}

}

/** \file Lookup3.hpp
 * \brief Vector mapping: Lookup (header).
 */
#endif
