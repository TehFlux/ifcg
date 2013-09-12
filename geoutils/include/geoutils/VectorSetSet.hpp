#ifndef IONFLUX_GEOUTILS_VECTORSETSET
#define IONFLUX_GEOUTILS_VECTORSETSET
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * VectorSetSet.hpp                Set of vector sets (header).
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
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class VectorSet;

/// Class information for class VectorSetSet.
class VectorSetSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		VectorSetSetClassInfo();
		/// Destructor.
		virtual ~VectorSetSetClassInfo();
};

/** Set of vector sets.
 * \ingroup geoutils
 *
 * A set of vector sets.
 */
class VectorSetSet
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Vector of vector sets.
		std::vector<Ionflux::GeoUtils::VectorSet*> vectorSets;
		
	public:
		/// Class information instance.
		static const VectorSetSetClassInfo vectorSetSetClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new VectorSetSet object.
		 */
		VectorSetSet();
		
		/** Constructor.
		 *
		 * Construct new VectorSetSet object.
		 *
		 * \param other Other object.
		 */
		VectorSetSet(const Ionflux::GeoUtils::VectorSetSet& other);
		
		/** Constructor.
		 *
		 * Construct new VectorSetSet object.
		 *
		 * \param initVectorSets Vector sets.
		 */
		VectorSetSet(Ionflux::GeoUtils::VectorSetVector& initVectorSets);
		
		/** Destructor.
		 *
		 * Destruct VectorSetSet object.
		 */
		virtual ~VectorSetSet();
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Vector set.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::VectorSetSet& other) 
		const;
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Vector set set.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::VectorSetSet& other) 
		const;
		
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
		virtual Ionflux::GeoUtils::VectorSetSet& operator=(const 
		Ionflux::GeoUtils::VectorSetSet& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::VectorSetSet* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::VectorSetSet* 
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
		static Ionflux::GeoUtils::VectorSetSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new VectorSetSet object.
		 *
		 * \param initVectorSets Vector sets.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::VectorSetSet* 
		create(Ionflux::GeoUtils::VectorSetVector& initVectorSets, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Get XML element name.
		 *
		 * Get the XML element name for the object.
		 *
		 * \return XML element name
		 */
		std::string getXMLElementName() const;
        
		/** Get XML attribute data.
		 *
		 * Get a string containing the XML attributes of the object.
		 *
		 * \return XML attribute data
		 */
		std::string getXMLAttributeData() const;
        
        /** Get XML child data.
		 *
		 * Get the XML child data for the object.
		 *
		 * \param target Where to store the XML data.
		 * \param indentLevel Indentation level.
		 */
		void getXMLChildData(std::string& target, unsigned int indentLevel = 0) 
		const;
        
        /** Load from XML file.
		 *
		 * Initialize the object from an XML file.
		 *
		 * \param fileName file name
		 */
		void loadFromXMLFile(std::string& FileName);
		
		/** Get number of vectorSets.
		 *
		 * \return Number of vectorSets.
		 */
		virtual unsigned int getNumVectorSets() const;
		
		/** Get vectorSet.
		 *
		 * Get the vectorSet at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return VectorSet at specified index.
		 */
		virtual Ionflux::GeoUtils::VectorSet* getVectorSet(unsigned int 
		elementIndex = 0) const;
		
		/** Find vectorSet.
		 *
		 * Find the specified occurence of a vectorSet.
		 *
		 * \param needle VectorSet to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the vectorSet, or -1 if the vectorSet cannot be 
		 * found.
		 */
		virtual int findVectorSet(Ionflux::GeoUtils::VectorSet* needle, unsigned 
		int occurence = 1) const;
        
		/** Get vector of vector sets.
		 *
		 * \return vector of vector sets.
		 */
		virtual std::vector<Ionflux::GeoUtils::VectorSet*>& getVectorSets();
		
		/** Add vectorSet.
		 *
		 * Add a vectorSet.
		 *
		 * \param addElement VectorSet to be added.
		 */
		virtual void addVectorSet(Ionflux::GeoUtils::VectorSet* addElement);
		
		/** Create vectorSet.
		 *
		 * Create a new vectorSet which is managed by the vectorSet set.
		 *
		 * \return New vectorSet.
		 */
		virtual Ionflux::GeoUtils::VectorSet* addVectorSet();
		
		/** Add vectorSets.
		 *
		 * Add vectorSets from a vectorSet vector.
		 *
		 * \param newVectorSets vectorSets.
		 */
		virtual void addVectorSets(const 
		std::vector<Ionflux::GeoUtils::VectorSet*>& newVectorSets);
		
		/** Add vectorSets.
		 *
		 * Add vectorSets from a vectorSet set.
		 *
		 * \param newVectorSets vectorSets.
		 */
		virtual void addVectorSets(Ionflux::GeoUtils::VectorSetSet* 
		newVectorSets);
		
		/** Remove vectorSet.
		 *
		 * Remove a vectorSet.
		 *
		 * \param removeElement VectorSet to be removed.
		 */
		virtual void removeVectorSet(Ionflux::GeoUtils::VectorSet* 
		removeElement);
		
		/** Remove vectorSet.
		 *
		 * Remove a vectorSet.
		 *
		 * \param removeIndex VectorSet to be removed.
		 */
		virtual void removeVectorSetIndex(unsigned int removeIndex);
		
		/** Clear vectorSets.
		 *
		 * Clear all vectorSets.
		 */
		virtual void clearVectorSets();
};

}

}

/** \file VectorSetSet.hpp
 * \brief Set of vector sets (header).
 */
#endif
