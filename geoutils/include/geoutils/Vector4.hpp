#ifndef IONFLUX_GEOUTILS_VECTOR4
#define IONFLUX_GEOUTILS_VECTOR4
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector4.hpp                     Vector (4 elements) (header).
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
#include "geoutils/utils.hpp"
#include "geoutils/Vector3.hpp"
#include "geoutils/Vector.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class Vector4XMLFactory;

}

/// Class information for class Vector4.
class Vector4ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Vector4ClassInfo();
		/// Destructor.
		virtual ~Vector4ClassInfo();
};

/** Vector (4 elements).
 * \ingroup geoutils
 *
 * A vector in four-dimensional space.
 */
class Vector4
: public Ionflux::GeoUtils::Vector
{
	private:
		
	protected:
		
	public:
		/// Number of elements.
		static const unsigned int NUM_ELEMENTS;
		/// Zero vector.
		static const Ionflux::GeoUtils::Vector4 ZERO;
		/// Unit vector (X).
		static const Ionflux::GeoUtils::Vector4 E_X;
		/// Unit vector (Y).
		static const Ionflux::GeoUtils::Vector4 E_Y;
		/// Unit vector (Z).
		static const Ionflux::GeoUtils::Vector4 E_Z;
		/// Unit vector (W).
		static const Ionflux::GeoUtils::Vector4 E_W;
		/// Zero vector (homogenous coordinates).
		static const Ionflux::GeoUtils::Vector4 H_ZERO;
		/// Unit vector (X, homogenous coordinates).
		static const Ionflux::GeoUtils::Vector4 H_E_X;
		/// Unit vector (Y, homogenous coordinates).
		static const Ionflux::GeoUtils::Vector4 H_E_Y;
		/// Unit vector (Z, homogenous coordinates).
		static const Ionflux::GeoUtils::Vector4 H_E_Z;
		/// Class information instance.
		static const Vector4ClassInfo vector4ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new Vector4 object.
		 */
		Vector4();
		
		/** Constructor.
		 *
		 * Construct new Vector4 object.
		 *
		 * \param other Other object.
		 */
		Vector4(const Ionflux::GeoUtils::Vector4& other);
		
		/** Constructor.
		 *
		 * Construct new Vector4 object.
		 *
		 * \param initX0 Element (X0).
		 * \param initX1 Element (X1).
		 * \param initX2 Element (X2).
		 * \param initX3 Element (X3).
		 */
		Vector4(double initX0, double initX1, double initX2, double initX3);
		
		/** Constructor.
		 *
		 * Construct new Vector4 object.
		 *
		 * \param initElements0 Element vector.
		 */
		Vector4(const Ionflux::ObjectBase::DoubleVector& initElements0);
		
		/** Constructor.
		 *
		 * Construct new Vector4 object.
		 *
		 * \param initElements0 Element vector.
		 * \param initZ Z coordinate.
		 * \param initW W coordinate.
		 */
		Vector4(const Ionflux::GeoUtils::Vector2& initElements0, double initZ = 
		0., double initW = 1.);
		
		/** Constructor.
		 *
		 * Construct new Vector4 object.
		 *
		 * \param initElements0 Element vector.
		 * \param initW W coordinate.
		 */
		Vector4(const Ionflux::GeoUtils::Vector3& initElements0, double initW = 
		1.);
		
		/** Destructor.
		 *
		 * Destruct Vector4 object.
		 */
		virtual ~Vector4();
		
		/** Set elements.
		 *
		 * Set elements from a 2-element vector. The Z and W-coordinates will 
		 * be left alone.
		 *
		 * \param newElements Element vector.
		 */
		virtual void setElements(const Ionflux::GeoUtils::Vector2& newElements);
		
		/** Set elements.
		 *
		 * Set elements from a 3-element vector. The W-coordinate will be left
		 * alone.
		 *
		 * \param newElements Element vector.
		 */
		virtual void setElements(const Ionflux::GeoUtils::Vector3& newElements);
		
		/** Set elements.
		 *
		 * Set elements from a 2-element vector. The Z and W-coordinates will 
		 * be set to the optional parameters (which default to 0 and 1).
		 *
		 * \param newElements Element vector.
		 * \param newZ Z coordinate.
		 * \param newW W coordinate.
		 */
		virtual void setV2(const Ionflux::GeoUtils::Vector2& newElements, double 
		newZ = 0., double newW = 1.);
		
		/** Set elements.
		 *
		 * Set elements from a 3-element vector. The W-coordinate will be set 
		 * to the optional second parameter (which defaults to 1).
		 *
		 * \param newElements Element vector.
		 * \param newW W coordinate.
		 */
		virtual void setV3(const Ionflux::GeoUtils::Vector3& newElements, double 
		newW = 1.);
		
		/** Flip vector.
		 *
		 * Create a new vector which is equal to the original vector 
		 * multiplied by -1.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector4 flip() const;
		
		/** Normalize vector.
		 *
		 * Create a new vector which is equal to the normalized original 
		 * vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector4 normalize() const;
		
		/** Projection.
		 *
		 * Calculate the projection of another vector on the vector.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector4 project(const 
		Ionflux::GeoUtils::Vector4& other) const;
		
		/** Orthogonalize vector.
		 *
		 * Rotate the other vector (v1) within the plane defined by the 
		 * original vector (v0) and v1, so it is orthogonal to v0.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector4 ortho(const 
		Ionflux::GeoUtils::Vector4& other) const;
		
		/** Calculate angle.
		 *
		 * Calculate the geometric angle between the two vectors.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual double angle(const Ionflux::GeoUtils::Vector4& other) const;
		
		/** Spherical linear interpolation.
		 *
		 * Interpolate vectors using spherical linear interpolation.
		 *
		 * \param other Vector.
		 * \param t Parameter.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector4 slerp(const 
		Ionflux::GeoUtils::Vector4& other, double t) const;
		
		/** Permute vector.
		 *
		 * Permute the vector using the specified permutation of indices.
		 *
		 * \param px Permutation (x).
		 * \param py Permutation (y).
		 * \param pz Permutation (z).
		 * \param pw Permutation (w).
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector4 permute(int px, int py, int pz, int 
		pw) const;
		
		/** Permute vector.
		 *
		 * Permute the vector using the specified permutation of indices.
		 *
		 * \param p Permutation.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector4 permute(const 
		Ionflux::ObjectBase::IntVector& p) const;
		
		/** Add vectors.
		 *
		 * Add vectors.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector4 operator+(const 
		Ionflux::GeoUtils::Vector4& other) const;
		
		/** Subtract vectors.
		 *
		 * Subtract vectors.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector4 operator-(const 
		Ionflux::GeoUtils::Vector4& other) const;
		
		/** Multiply vectors.
		 *
		 * Multiply vectors (dot product).
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual double operator*(const Ionflux::GeoUtils::Vector4& other) const;
		
		/** Multiply vector by scalar.
		 *
		 * Multiply vector by a scalar.
		 *
		 * \param c Scalar factor.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector4 operator*(double c) const;
		
		/** Divide vector by scalar.
		 *
		 * Divide vector by a scalar.
		 *
		 * \param c Scalar factor.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::Vector4 operator/(double c) const;
		
		/** Create 2-element vector.
		 *
		 * Create a 2-element vector without the Z and W coordinates.
		 *
		 * \return 2-element vector.
		 */
		virtual Ionflux::GeoUtils::Vector2 getV2() const;
		
		/** Create 3-element vector.
		 *
		 * Create a 3-element vector without the W coordinate.
		 *
		 * \return 3-element vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getV3() const;
		
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
		static Ionflux::GeoUtils::Vector4 axis(Ionflux::GeoUtils::AxisID axisID);
		
		/** Get axis direction vector (homogenous coordinates).
		 *
		 * Get the direction vector for the specified axis in homogenous 
		 * coordinates.
		 *
		 * \param axisID Axis.
		 *
		 * \return Axis direction vector.
		 */
		static Ionflux::GeoUtils::Vector4 axisH(Ionflux::GeoUtils::AxisID 
		axisID);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Vector4& operator=(const 
		Ionflux::GeoUtils::Vector4& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Vector4* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Vector4* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Vector4* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Vector4 object.
		 *
		 * \param initX0 Element (X0).
		 * \param initX1 Element (X1).
		 * \param initX2 Element (X2).
		 * \param initX3 Element (X3).
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Vector4* create(double initX0, double initX1, 
		double initX2, double initX3, Ionflux::ObjectBase::IFObject* parentObject
		= 0);
        
		/** Create instance.
		 *
		 * Create a new Vector4 object.
		 *
		 * \param initElements0 Element vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Vector4* create(const 
		Ionflux::ObjectBase::DoubleVector& initElements0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Vector4 object.
		 *
		 * \param initElements0 Element vector.
		 * \param initZ Z coordinate.
		 * \param initW W coordinate.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Vector4* create(const 
		Ionflux::GeoUtils::Vector2& initElements0, double initZ = 0., double 
		initW = 1., Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Vector4 object.
		 *
		 * \param initElements0 Element vector.
		 * \param initW W coordinate.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Vector4* create(const 
		Ionflux::GeoUtils::Vector3& initElements0, double initW = 1., 
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
		
		/** Get element x2.
		 *
		 * \return Current value of element x2.
		 */
		virtual double getX2() const;
		
		/** Set element x2.
		 *
		 * Set new value of element x2.
		 *
		 * \param newX2 New value of element x2.
		 */
		virtual void setX2(double newX2);
		
		/** Get element x3.
		 *
		 * \return Current value of element x3.
		 */
		virtual double getX3() const;
		
		/** Set element x3.
		 *
		 * Set new value of element x3.
		 *
		 * \param newX3 New value of element x3.
		 */
		virtual void setX3(double newX3);
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
Ionflux::GeoUtils::Vector4 operator*(double c, const 
Ionflux::GeoUtils::Vector4& v);

}

}

/** \file Vector4.hpp
 * \brief Vector (4 elements) (header).
 */
#endif
