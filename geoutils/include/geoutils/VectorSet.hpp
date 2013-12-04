#ifndef IONFLUX_GEOUTILS_VECTORSET
#define IONFLUX_GEOUTILS_VECTORSET
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * VectorSet.hpp                   Vector set (header).
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

class Vector;

namespace XMLUtils
{

class VectorSetXMLFactory;

}

/// Class information for class VectorSet.
class VectorSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		VectorSetClassInfo();
		/// Destructor.
		virtual ~VectorSetClassInfo();
};

/** Vector set.
 * \ingroup geoutils
 *
 * A set of vectors.
 */
class VectorSet
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Vector of vectors.
		std::vector<Ionflux::GeoUtils::Vector*> vectors;
		
	public:
		/// Class information instance.
		static const VectorSetClassInfo vectorSetClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new VectorSet object.
		 */
		VectorSet();
		
		/** Constructor.
		 *
		 * Construct new VectorSet object.
		 *
		 * \param other Other object.
		 */
		VectorSet(const Ionflux::GeoUtils::VectorSet& other);
		
		/** Constructor.
		 *
		 * Construct new VectorSet object.
		 *
		 * \param initVectors Vectors.
		 */
		VectorSet(Ionflux::GeoUtils::VectorVector& initVectors);
		
		/** Destructor.
		 *
		 * Destruct VectorSet object.
		 */
		virtual ~VectorSet();
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Vector set.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::VectorSet& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Vector set.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::VectorSet& other) const;
		
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
		virtual Ionflux::GeoUtils::VectorSet& operator=(const 
		Ionflux::GeoUtils::VectorSet& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::VectorSet* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::VectorSet* 
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
		static Ionflux::GeoUtils::VectorSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new VectorSet object.
		 *
		 * \param initVectors Vectors.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::VectorSet* 
		create(Ionflux::GeoUtils::VectorVector& initVectors, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Get XML element name.
		 *
		 * Get the XML element name for the object.
		 *
		 * \return XML element name
		 */
		virtual std::string getXMLElementName() const;
        
		/** Get XML attribute data.
		 *
		 * Get a string containing the XML attributes of the object.
		 *
		 * \return XML attribute data
		 */
		virtual std::string getXMLAttributeData() const;
        
        /** Get XML child data.
		 *
		 * Get the XML child data for the object.
		 *
		 * \param target Where to store the XML data.
		 * \param indentLevel Indentation level.
		 */
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
        
        /** Load from XML file.
		 *
		 * Initialize the object from an XML file.
		 *
		 * \param fileName file name
		 */
		virtual void loadFromXMLFile(const std::string& FileName);
        
        /** Get XML object factory
		 *
		 * Get the XML object factory singleton for the class.
		 *
		 * \param fileName file name
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		
		/** Get number of vectors.
		 *
		 * \return Number of vectors.
		 */
		virtual unsigned int getNumVectors() const;
		
		/** Get vector.
		 *
		 * Get the vector at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Vector at specified index.
		 */
		virtual Ionflux::GeoUtils::Vector* getVector(unsigned int elementIndex = 
		0) const;
		
		/** Find vector.
		 *
		 * Find the specified occurence of a vector.
		 *
		 * \param needle Vector to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the vector, or -1 if the vector cannot be found.
		 */
		virtual int findVector(Ionflux::GeoUtils::Vector* needle, unsigned int 
		occurence = 1) const;
        
		/** Get vector of vectors.
		 *
		 * \return vector of vectors.
		 */
		virtual std::vector<Ionflux::GeoUtils::Vector*>& getVectors();
		
		/** Add vector.
		 *
		 * Add a vector.
		 *
		 * \param addElement Vector to be added.
		 */
		virtual void addVector(Ionflux::GeoUtils::Vector* addElement);
		
		/** Create vector.
		 *
		 * Create a new vector which is managed by the vector set.
		 *
		 * \return New vector.
		 */
		virtual Ionflux::GeoUtils::Vector* addVector();
		
		/** Add vectors.
		 *
		 * Add vectors from a vector vector.
		 *
		 * \param newVectors vectors.
		 */
		virtual void addVectors(const std::vector<Ionflux::GeoUtils::Vector*>& 
		newVectors);
		
		/** Add vectors.
		 *
		 * Add vectors from a vector set.
		 *
		 * \param newVectors vectors.
		 */
		virtual void addVectors(Ionflux::GeoUtils::VectorSet* newVectors);
		
		/** Remove vector.
		 *
		 * Remove a vector.
		 *
		 * \param removeElement Vector to be removed.
		 */
		virtual void removeVector(Ionflux::GeoUtils::Vector* removeElement);
		
		/** Remove vector.
		 *
		 * Remove a vector.
		 *
		 * \param removeIndex Vector to be removed.
		 */
		virtual void removeVectorIndex(unsigned int removeIndex);
		
		/** Clear vectors.
		 *
		 * Clear all vectors.
		 */
		virtual void clearVectors();
};

}

}

/** \file VectorSet.hpp
 * \brief Vector set (header).
 */
#endif
