#ifndef IONFLUX_MAPPING_LOOKUP
#define IONFLUX_MAPPING_LOOKUP
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Lookup.hpp                      Lookup mapping (header).
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
#include "ifmapping/ChainableMapping.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class Lookup.
class LookupClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		LookupClassInfo();
		/// Destructor.
		virtual ~LookupClassInfo();
};

/** Lookup mapping.
 * \ingroup ifmapping
 *
 * A mapping that returns a value from a lookup table. The value of the 
 * parameter is used to select an entry from the table by scaling the 
 * parameter range [0...1] to the number of entries in the table. The table
 * can be either filled from a vector of values or from another mapping, 
 * which will be queried with values in the range [0...1] to obtain the 
 * values used to populate the table. If another lookup table is used as 
 * the source mapping with the exact same number of entries as the table to
 * be populated, the lookup table will become a copy of the source.
 */
class Lookup
: public Ionflux::Mapping::ChainableMapping
{
	private:
		
	protected:
		/// .
		std::vector<Ionflux::Mapping::MappingValue> entries;
		/// Source mapping.
		Ionflux::Mapping::Mapping* source;
		
	public:
		/// .
		static const unsigned int DEFAULT_NUM_ENTRIES;
		/// .
		static const Ionflux::Mapping::Range CLAMP_RANGE;
		/// Class information instance.
		static const LookupClassInfo lookupClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Lookup object.
		 */
		Lookup();
		
		/** Constructor.
		 *
		 * Construct new Lookup object.
		 *
		 * \param other Other object.
		 */
		Lookup(const Ionflux::Mapping::Lookup& other);
		
		/** Constructor.
		 *
		 * Construct new Lookup object.
		 *
		 * \param initSource Source mapping.
		 * \param initNumEntries Number of entries.
		 * \param initScale Scale factor.
		 * \param initOffset Offset.
		 * \param initFunc Parameter source mapping.
		 */
		Lookup(Ionflux::Mapping::Mapping* initSource, unsigned int initNumEntries
		= DEFAULT_NUM_ENTRIES, Ionflux::Mapping::MappingValue initScale = 0., 
		Ionflux::Mapping::MappingValue initOffset = 0., 
		Ionflux::Mapping::Mapping* initFunc = 0);
		
		/** Constructor.
		 *
		 * Construct new Lookup object.
		 *
		 * \param initEntries Entries.
		 * \param initNumEntries Number of entries.
		 * \param initSource Source mapping.
		 * \param initScale Scale factor.
		 * \param initOffset Offset.
		 * \param initFunc Parameter source mapping.
		 */
		Lookup(const Ionflux::Mapping::MappingValueVector& initEntries, unsigned 
		int initNumEntries = 0, Ionflux::Mapping::Mapping* initSource = 0, 
		Ionflux::Mapping::MappingValue initScale = 0., 
		Ionflux::Mapping::MappingValue initOffset = 0., 
		Ionflux::Mapping::Mapping* initFunc = 0);
		
		/** Destructor.
		 *
		 * Destruct Lookup object.
		 */
		virtual ~Lookup();
		
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
		virtual void addEntries(const Ionflux::Mapping::MappingValueVector& 
		newEntries, unsigned int numEntries = 0);
		
		/** Call the mapping.
		 *
		 * Calls the mapping with the specified parameter.
		 *
		 * \param value Value.
		 *
		 * \return Mapped value.
		 */
		virtual Ionflux::Mapping::MappingValue 
		callWithParam(Ionflux::Mapping::MappingValue value) const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Mapping::Lookup& operator=(const 
		Ionflux::Mapping::Lookup& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::Lookup* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::Lookup* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::Mapping::Lookup* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
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
		virtual Ionflux::Mapping::MappingValue getEntry(unsigned int elementIndex
		= 0) const;
		
		/** Find entry.
		 *
		 * Find the specified occurence of a entry.
		 *
		 * \param needle Entry to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the entry, or -1 if the entry cannot be found.
		 */
		virtual int findEntry(Ionflux::Mapping::MappingValue needle, unsigned int
		occurence = 1) const;
        
		/** Get .
		 *
		 * \return .
		 */
		virtual std::vector<Ionflux::Mapping::MappingValue>& getEntries();
		
		/** Add entry.
		 *
		 * Add a entry.
		 *
		 * \param addElement Entry to be added.
		 */
		virtual void addEntry(Ionflux::Mapping::MappingValue addElement);
		
		/** Remove entry.
		 *
		 * Remove a entry.
		 *
		 * \param removeElement Entry to be removed.
		 */
		virtual void removeEntry(Ionflux::Mapping::MappingValue removeElement);
		
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
		virtual Ionflux::Mapping::Mapping* getSource() const;
		
		/** Set source mapping.
		 *
		 * Set new value of source mapping.
		 *
		 * \param newSource New value of source mapping.
		 */
		virtual void setSource(Ionflux::Mapping::Mapping* newSource);
};

}

}

/** \file Lookup.hpp
 * \brief Lookup mapping (header).
 */
#endif
