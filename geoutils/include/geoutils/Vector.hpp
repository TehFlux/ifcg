#ifndef IONFLUX_GEOUTILS_VECTOR
#define IONFLUX_GEOUTILS_VECTOR
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector.hpp                      Vector (header).
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

#include "ifobject/types.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Vector.
class VectorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		VectorClassInfo();
		/// Destructor.
		virtual ~VectorClassInfo();
};

/** Vector.
 * \ingroup geoutils
 *
 * A numeric vector.
 */
class Vector
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Elements.
		double* elements;
		
		/** Initialize elements.
		 *
		 * Initialize the element array.
		 */
		virtual void initElements();
		
	public:
		/// Number of elements.
		static const unsigned int NUM_ELEMENTS;
		/// Class information instance.
		static const VectorClassInfo vectorClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new Vector object.
		 */
		Vector();
		
		/** Constructor.
		 *
		 * Construct new Vector object.
		 *
		 * \param other Other object.
		 */
		Vector(const Ionflux::GeoUtils::Vector& other);
		
		/** Destructor.
		 *
		 * Destruct Vector object.
		 */
		virtual ~Vector();
		
		/** Zero elements.
		 *
		 * Set elements to zero.
		 */
		virtual void zero();
		
		/** Set elements.
		 *
		 * Set elements from a vector of doubles. If the vector contains fewer
		 * than the required number of elements, the remaining elements will 
		 * be left alone.
		 *
		 * \param newElements Element vector.
		 */
		virtual void setElements(const Ionflux::ObjectBase::DoubleVector& 
		newElements);
		
		/** Get elements.
		 *
		 * Store the elements of the vector in a vector of doubles.
		 *
		 * \param target Target vector.
		 */
		virtual void getElements(Ionflux::ObjectBase::DoubleVector& target) 
		const;
		
		/** Get element.
		 *
		 * Get the element at the specified index.
		 *
		 * \param index Index.
		 *
		 * \return Element at the specified index.
		 */
		virtual double getElement(unsigned int index) const;
		
		/** Set element.
		 *
		 * Set the element at the specified index.
		 *
		 * \param index Index.
		 * \param value Value.
		 */
		virtual void setElement(unsigned int index, double value);
		
		/** Comparison (with tolerance): equal.
		 *
		 * Compare the vector with another vector using the specified 
		 * tolerance.
		 *
		 * \param other Vector.
		 * \param t Tolerance.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool eq(const Ionflux::GeoUtils::Vector& other, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
		
		/** Dot product.
		 *
		 * Calculate the dot product of this vector and another vector.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual double dot(const Ionflux::GeoUtils::Vector& other) const;
		
		/** Norm.
		 *
		 * Calculate the norm of this vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual double norm() const;
		
		/** Normalize (in-place).
		 *
		 * Normalize the vector (in-place).
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector& normalizeIP();
		
		/** Multiply (in-place).
		 *
		 * Multiply the vector by a scalar (in-place).
		 *
		 * \param c Value.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector& multiplyIP(double c);
		
		/** Divide (in-place).
		 *
		 * Divide the vector by a scalar (in-place).
		 *
		 * \param c Value.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector& divideIP(double c);
		
		/** Flip (in-place).
		 *
		 * Flip the vector (in-place).
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector& flipIP();
		
		/** Multiply (in-place).
		 *
		 * Multiply the elements in this vector by the elements from another 
		 * vector (in-place).
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector& multiplyIP(const 
		Ionflux::GeoUtils::Vector& other);
		
		/** Subtract (in-place).
		 *
		 * Subtract the elements from another vector from the elements in this
		 * vector (in-place).
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector& subtractIP(const 
		Ionflux::GeoUtils::Vector& other);
		
		/** Add (in-place).
		 *
		 * Add the elements from another vector to the elements in this vector
		 * (in-place).
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector& addIP(const Ionflux::GeoUtils::Vector&
		other);
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Vector& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Vector& other) const;
		
		/** Subscript operator.
		 *
		 * Subscript operator.
		 *
		 * \param index Index.
		 *
		 * \return Element at specified index.
		 */
		virtual double operator[](unsigned int index) const;
		
		/** Multiply vectors (dot product).
		 *
		 * Multiply vectors (dot product).
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual double operator*(const Ionflux::GeoUtils::Vector& other) const;
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Get number of elements.
		 *
		 * Get the number of elements in the vector
		 *
		 * \return Number of elements.
		 */
		virtual unsigned int getNumElements() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Vector& operator=(const 
		Ionflux::GeoUtils::Vector& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Vector* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Vector* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Vector* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
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
};

}

}

/** \file Vector.hpp
 * \brief Vector (header).
 */
#endif
