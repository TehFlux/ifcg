#ifndef IONFLUX_GEOUTILS_FACEDATA
#define IONFLUX_GEOUTILS_FACEDATA
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FaceData.hpp                    Face data (header).
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
#include "geoutils/VectorSet.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class FaceData.
class FaceDataClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		FaceDataClassInfo();
		/// Destructor.
		virtual ~FaceDataClassInfo();
};

/** Face data.
 * \ingroup geoutils
 *
 * Data associated with a mesh face.
 */
class FaceData
: public Ionflux::GeoUtils::VectorSet
{
	private:
		
	protected:
		/// .
		Ionflux::GeoUtils::FaceDataTypeID dataType;
		
	public:
		/// Class information instance.
		static const FaceDataClassInfo faceDataClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new FaceData object.
		 */
		FaceData();
		
		/** Constructor.
		 *
		 * Construct new FaceData object.
		 *
		 * \param other Other object.
		 */
		FaceData(const Ionflux::GeoUtils::FaceData& other);
		
		/** Constructor.
		 *
		 * Construct new FaceData object.
		 *
		 * \param initVectors Vectors.
		 */
		FaceData(Ionflux::GeoUtils::VectorVector& initVectors);
		
		/** Destructor.
		 *
		 * Destruct FaceData object.
		 */
		virtual ~FaceData();
		
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
		virtual Ionflux::GeoUtils::FaceData& operator=(const 
		Ionflux::GeoUtils::FaceData& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::FaceData* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::FaceData* upcast(Ionflux::ObjectBase::IFObject*
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
		static Ionflux::GeoUtils::FaceData* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new FaceData object.
		 *
		 * \param initVectors Vectors.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::FaceData* 
		create(Ionflux::GeoUtils::VectorVector& initVectors, 
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
		
		/** Get .
		 *
		 * \return Current value of .
		 */
		virtual Ionflux::GeoUtils::FaceDataTypeID getDataType() const;
		
		/** Set .
		 *
		 * Set new value of .
		 *
		 * \param newDataType New value of .
		 */
		virtual void setDataType(Ionflux::GeoUtils::FaceDataTypeID newDataType);
};

}

}

/** \file FaceData.hpp
 * \brief Face data (header).
 */
#endif
