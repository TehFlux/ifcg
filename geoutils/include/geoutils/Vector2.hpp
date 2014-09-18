#ifndef IONFLUX_GEOUTILS_VECTOR2
#define IONFLUX_GEOUTILS_VECTOR2
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector2.hpp                     Vector (2 elements) (header).
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
#include "geoutils/Vector.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class Vector2XMLFactory;

}

/// Class information for class Vector2.
class Vector2ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Vector2ClassInfo();
		/// Destructor.
		virtual ~Vector2ClassInfo();
};

/** Vector (2 elements).
 * \ingroup geoutils
 *
 * A vector in two-dimensional space.
 */
class Vector2
: public Ionflux::GeoUtils::Vector
{
	private:
		
	protected:
		
	public:
		/// Number of elements.
		static const unsigned int NUM_ELEMENTS;
		/// Zero vector.
		static const Ionflux::GeoUtils::Vector2 ZERO;
		/// Unit vector (X).
		static const Ionflux::GeoUtils::Vector2 E_X;
		/// Unit vector (Y).
		static const Ionflux::GeoUtils::Vector2 E_Y;
		/// Class information instance.
		static const Vector2ClassInfo vector2ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new Vector2 object.
		 */
		Vector2();
		
		/** Constructor.
		 *
		 * Construct new Vector2 object.
		 *
		 * \param other Other object.
		 */
		Vector2(const Ionflux::GeoUtils::Vector2& other);
		
		/** Constructor.
		 *
		 * Construct new Vector2 object.
		 *
		 * \param initX0 Element (X0).
		 * \param initX1 Element (X1).
		 */
		Vector2(double initX0, double initX1);
		
		/** Constructor.
		 *
		 * Construct new Vector2 object.
		 *
		 * \param initElements0 Element vector.
		 */
		Vector2(const Ionflux::ObjectBase::DoubleVector& initElements0);
		
		/** Destructor.
		 *
		 * Destruct Vector2 object.
		 */
		virtual ~Vector2();
		
		/** Set elements.
		 *
		 * Set elements of the vector.
		 *
		 * \param newX0 Element (x0).
		 * \param newX1 Element (x1).
		 */
		virtual void setElements(double newX0, double newX1);
		
		/** Flip vector.
		 *
		 * Create a new vector which is equal to the original vector 
		 * multiplied by -1.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 flip() const;
		
		/** Normalize vector.
		 *
		 * Create a new vector which is equal to the normalized original 
		 * vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 normalize() const;
		
		/** Projection.
		 *
		 * Calculate the projection of another vector on the vector.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 project(const 
		Ionflux::GeoUtils::Vector2& other) const;
		
		/** Orthogonalize vector.
		 *
		 * Rotate the other vector (v1) within the plane defined by the 
		 * original vector (v0) and v1, so it is orthogonal to v0.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 ortho(const 
		Ionflux::GeoUtils::Vector2& other) const;
		
		/** Swap elements.
		 *
		 * Swap the elements of the vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 swap() const;
		
		/** Element-wise multiplication.
		 *
		 * Multiply the vectors element-wise.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 multElements(const 
		Ionflux::GeoUtils::Vector2& other) const;
		
		/** Add vectors.
		 *
		 * Add vectors.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 operator+(const 
		Ionflux::GeoUtils::Vector2& other) const;
		
		/** Subtract vectors.
		 *
		 * Subtract vectors.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 operator-(const 
		Ionflux::GeoUtils::Vector2& other) const;
		
		/** Multiply vector by scalar.
		 *
		 * Multiply vector by a scalar.
		 *
		 * \param c Scalar factor.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 operator*(double c) const;
		
		/** Multiply vectors (dot product).
		 *
		 * Multiply vectors (dot product).
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual double operator*(const Ionflux::GeoUtils::Vector2& other) const;
		
		/** Divide vector by scalar.
		 *
		 * Divide vector by a scalar.
		 *
		 * \param c Scalar factor.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector2 operator/(double c) const;
		
		/** Get number of elements.
		 *
		 * Get the number of elements in the vector
		 *
		 * \return Number of elements.
		 */
		virtual unsigned int getNumElements() const;
		
		/** Get axis direction vector.
		 *
		 * Get the direction vector for the specified axis.
		 *
		 * \param axisID Axis.
		 *
		 * \return Axis direction vector.
		 */
		static Ionflux::GeoUtils::Vector2 axis(Ionflux::GeoUtils::AxisID axisID);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Vector2& operator=(const 
		Ionflux::GeoUtils::Vector2& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Vector2* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Vector2* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Vector2* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Vector2 object.
		 *
		 * \param initX0 Element (X0).
		 * \param initX1 Element (X1).
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Vector2* create(double initX0, double initX1, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Vector2 object.
		 *
		 * \param initElements0 Element vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Vector2* create(const 
		Ionflux::ObjectBase::DoubleVector& initElements0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
        
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
		virtual void loadFromXMLFile(const std::string& fileName);
        
        /** Get XML object factory
		 *
		 * Get the XML object factory singleton for the class.
		 * 
		 * return XML object factory
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		
		/** Get element x0.
		 *
		 * \return Current value of element x0.
		 */
		virtual double getX0() const;
		
		/** Set element x0.
		 *
		 * Set new value of element x0.
		 *
		 * \param newX0 New value of element x0.
		 */
		virtual void setX0(double newX0);
		
		/** Get element x1.
		 *
		 * \return Current value of element x1.
		 */
		virtual double getX1() const;
		
		/** Set element x1.
		 *
		 * Set new value of element x1.
		 *
		 * \param newX1 New value of element x1.
		 */
		virtual void setX1(double newX1);
};

/** Multiply vector by scalar.
 *
 * Multiply vector by a scalar.
 *
 * \param c Scalar factor.
 * \param v Vector.
 *
 * \return Result of the calculation.
 */
Ionflux::GeoUtils::Vector2 operator*(double c, const 
Ionflux::GeoUtils::Vector2& v);

}

}

/** \file Vector2.hpp
 * \brief Vector (2 elements) (header).
 */
#endif
