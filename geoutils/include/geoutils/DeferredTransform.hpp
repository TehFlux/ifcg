#ifndef IONFLUX_GEOUTILS_DEFERREDTRANSFORM
#define IONFLUX_GEOUTILS_DEFERREDTRANSFORM
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * DeferredTransform.hpp           Deferred matrix transformation (header).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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

class Matrix4;
class Vector;
class VectorSet;

namespace XMLUtils
{

class DeferredTransformXMLFactory;

}

/// Class information for class DeferredTransform.
class DeferredTransformClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		DeferredTransformClassInfo();
		/// Destructor.
		virtual ~DeferredTransformClassInfo();
};

/** Deferred matrix transformation.
 * \ingroup geoutils
 *
 * A deferred matrix transformation object that can be used to accumulate 
 * matrix transformations that should be applied at a later point in time, 
 * or to track changes in a transformation. The deferred transformation 
 * object supports a general transformation matrix as well as additional 
 * view and image transformation matrices.
 */
class DeferredTransform
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Transformation matrix changed flag.
		bool transformChangedFlag;
		/// View/image transformation matrix changed flag.
		bool viChangedFlag;
		/// Use transformation matrix flag.
		bool useTransformFlag;
		/// Use view/image transformation matrix flag.
		bool useVIFlag;
		/// Transformation matrix.
		Ionflux::GeoUtils::Matrix4* transformMatrix;
		/// View matrix.
		Ionflux::GeoUtils::Matrix4* viewMatrix;
		/// Image matrix.
		Ionflux::GeoUtils::Matrix4* imageMatrix;
		/// Transformation matrix before last change.
		Ionflux::GeoUtils::Matrix4* lastTransformMatrix;
		/// View matrix before last change.
		Ionflux::GeoUtils::Matrix4* lastViewMatrix;
		/// Image matrix before last change.
		Ionflux::GeoUtils::Matrix4* lastImageMatrix;
		
	public:
		/// Comparison tolerance.
		static const double COMPARE_TOLERANCE;
		/// Class information instance.
		static const DeferredTransformClassInfo deferredTransformClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new DeferredTransform object.
		 */
		DeferredTransform();
		
		/** Constructor.
		 *
		 * Construct new DeferredTransform object.
		 *
		 * \param other Other object.
		 */
		DeferredTransform(const Ionflux::GeoUtils::DeferredTransform& other);
		
		/** Destructor.
		 *
		 * Destruct DeferredTransform object.
		 */
		virtual ~DeferredTransform();
		
		/** Reset transformation matrices.
		 *
		 * Make the current transformation matrix the last transformation 
		 * matrix and reset the changed flags.
		 */
		virtual void resetTransform();
		
		/** Reset transformation matrices.
		 *
		 * Make the current view/image transformation matrices the last 
		 * view/image transformation matrices and reset the changed flags.
		 */
		virtual void resetVI();
		
		/** Reset transformation matrices.
		 *
		 * Make the current transformation matrices the last transformation 
		 * matrices and reset the changed flags.
		 */
		virtual void reset();
		
		/** Clear.
		 *
		 * Clear the transformation matrices and flags.
		 */
		virtual void clear();
		
		/** Matrix transformation.
		 *
		 * Apply a transformation matrix to the object.
		 *
		 * \param matrix Transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::DeferredTransform& transform(const 
		Ionflux::GeoUtils::Matrix4& matrix);
		
		/** View/image transformation.
		 *
		 * Apply a view transformation matrix and an optional image 
		 * transformation matrix to the object.
		 *
		 * \param view View transformation matrix.
		 * \param image Image transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::DeferredTransform& transformVI(const 
		Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4* image
		= 0);
		
		/** Check transformation matrix status.
		 *
		 * Checks the transformation matrix. If it is equal to the unit matrix
		 * within the tolerance, use of the matrix for object transformations 
		 * will be disabled. If it is not equal to the unit matrix, check if 
		 * the transform has changed.
		 *
		 * \param t Tolerance.
		 *
		 * \return The result of the check.
		 */
		virtual bool checkTransform(double t = COMPARE_TOLERANCE);
		
		/** Check view/image transform status.
		 *
		 * Check the view/image transform matrices. If both are equal to the 
		 * unit matrix within the tolerance, use of the matrices for object 
		 * transformations will be disabled. If the matrices are not equal to 
		 * the unit matrix, check if the matrices have changed.
		 *
		 * \param t Tolerance.
		 *
		 * \return The result of the check.
		 */
		virtual bool checkVI(double t = COMPARE_TOLERANCE);
		
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
		virtual bool eq(const Ionflux::GeoUtils::DeferredTransform& other, double
		t = COMPARE_TOLERANCE) const;
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Deferred transformation.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::DeferredTransform& 
		other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Deferred transformation.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::DeferredTransform& 
		other) const;
		
		/** Get use transformation matrix flag.
		 *
		 * Get a boolean value that indicates whether the transformation 
		 * matrix should be applied.
		 *
		 * \return \c true if the transformation matrix should be applied, \c 
		 * false otherwise.
		 */
		virtual bool useTransform() const;
		
		/** Get use view/image transformation matrices flag.
		 *
		 * Get a boolean value that indicates whether the view/image 
		 * transformation matrices should be applied.
		 *
		 * \return \c true if the view/image transformation matrices should be 
		 * applied, \c false otherwise.
		 */
		virtual bool useVI() const;
		
		/** Get transformation matrix changed flag.
		 *
		 * Get a boolean value that indicates whether the transformation 
		 * matrix has changed since it was last checked.
		 *
		 * \return \c true if the transformation matrix has changed since the 
		 * last check, \c false otherwise.
		 */
		virtual bool transformChanged() const;
		
		/** Get view/image transformation matrices changed flag.
		 *
		 * Get a boolean value that indicates whether the view/image 
		 * transformation matrices have changed since they were last checked.
		 *
		 * \return \c true if the view/image transformation matrices have changed
		 * since the last check, \c false otherwise.
		 */
		virtual bool viChanged() const;
		
		/** Identity check.
		 *
		 * Check whether the deferred transformation is equivalent to the 
		 * identity transformation.
		 *
		 * \return \c true if the transformation is equivalent to the identity 
		 * transformation, \c false otherwise.
		 */
		virtual bool isIdentity() const;
		
		/** Apply transformation matrix.
		 *
		 * Apply the transformation matrix to a vector. If the optional \c 
		 * clearTransform argument is set to \c true, the transformation 
		 * matrix and flags will be cleared after the operation.
		 *
		 * \param v Vector.
		 * \param target Where to store the result.
		 * \param clearTransform Clear transform.
		 */
		virtual void applyTransform(const Ionflux::GeoUtils::Vector& v, 
		Ionflux::GeoUtils::Vector& target, bool clearTransform = true);
		
		/** Apply view/image transformation matrix.
		 *
		 * Apply the view/image transformation matrices to a vector. If the 
		 * optional \c clearTransform argument is set to \c true, the 
		 * view/image transformation matrices and flags will be cleared after 
		 * the operation.
		 *
		 * \param v Vector.
		 * \param target Where to store the result.
		 * \param clearTransform Clear transform.
		 */
		virtual void applyVI(const Ionflux::GeoUtils::Vector& v, 
		Ionflux::GeoUtils::Vector& target, bool clearTransform = true);
		
		/** Apply transformation matrix.
		 *
		 * Apply the transformation matrix to a vector set. If the optional \c
		 * clearTransform argument is set to \c true, the transformation 
		 * matrix and flags will be cleared after the operation.
		 *
		 * \param vectors Vector set.
		 * \param target Where to store the result vectors.
		 * \param clearTransform Clear transform.
		 */
		virtual void applyTransform(const Ionflux::GeoUtils::VectorSet& vectors, 
		Ionflux::GeoUtils::VectorSet& target, bool clearTransform = true);
		
		/** Apply view/image transformation matrix.
		 *
		 * Apply the view/image transformation matrices to a vector set. If 
		 * the optional \c clearTransform argument is set to \c true, the 
		 * view/image transformation matrices and flags will be cleared after 
		 * the operation.
		 *
		 * \param vectors Vector set.
		 * \param target Where to store the result.
		 * \param clearTransform Clear transform.
		 */
		virtual void applyVI(const Ionflux::GeoUtils::VectorSet& vectors, 
		Ionflux::GeoUtils::VectorSet& target, bool clearTransform = true);
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object
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
		virtual Ionflux::GeoUtils::DeferredTransform& operator=(const 
		Ionflux::GeoUtils::DeferredTransform& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::DeferredTransform* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::DeferredTransform* 
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
		static Ionflux::GeoUtils::DeferredTransform* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
		 * \param elementName element name
		 */
		virtual void loadFromXMLFile(const std::string& fileName, const 
		std::string& elementName = "");
        
        /** Get XML object factory
		 *
		 * Get the XML object factory singleton for the class.
		 * 
		 * return XML object factory
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		
		/** Get transformation matrix.
		 *
		 * \return Current value of transformation matrix.
		 */
		virtual Ionflux::GeoUtils::Matrix4* getTransformMatrix() const;
		
		/** Set transformation matrix.
		 *
		 * Set new value of transformation matrix.
		 *
		 * \param newTransformMatrix New value of transformation matrix.
		 */
		virtual void setTransformMatrix(Ionflux::GeoUtils::Matrix4* 
		newTransformMatrix);
		
		/** Get view matrix.
		 *
		 * \return Current value of view matrix.
		 */
		virtual Ionflux::GeoUtils::Matrix4* getViewMatrix() const;
		
		/** Set view matrix.
		 *
		 * Set new value of view matrix.
		 *
		 * \param newViewMatrix New value of view matrix.
		 */
		virtual void setViewMatrix(Ionflux::GeoUtils::Matrix4* newViewMatrix);
		
		/** Get image matrix.
		 *
		 * \return Current value of image matrix.
		 */
		virtual Ionflux::GeoUtils::Matrix4* getImageMatrix() const;
		
		/** Set image matrix.
		 *
		 * Set new value of image matrix.
		 *
		 * \param newImageMatrix New value of image matrix.
		 */
		virtual void setImageMatrix(Ionflux::GeoUtils::Matrix4* newImageMatrix);
		
		/** Get transformation matrix before last change.
		 *
		 * \return Current value of transformation matrix before last change.
		 */
		virtual Ionflux::GeoUtils::Matrix4* getLastTransformMatrix() const;
		
		/** Set transformation matrix before last change.
		 *
		 * Set new value of transformation matrix before last change.
		 *
		 * \param newLastTransformMatrix New value of transformation matrix 
		 * before last change.
		 */
		virtual void setLastTransformMatrix(Ionflux::GeoUtils::Matrix4* 
		newLastTransformMatrix);
		
		/** Get view matrix before last change.
		 *
		 * \return Current value of view matrix before last change.
		 */
		virtual Ionflux::GeoUtils::Matrix4* getLastViewMatrix() const;
		
		/** Set view matrix before last change.
		 *
		 * Set new value of view matrix before last change.
		 *
		 * \param newLastViewMatrix New value of view matrix before last change.
		 */
		virtual void setLastViewMatrix(Ionflux::GeoUtils::Matrix4* 
		newLastViewMatrix);
		
		/** Get image matrix before last change.
		 *
		 * \return Current value of image matrix before last change.
		 */
		virtual Ionflux::GeoUtils::Matrix4* getLastImageMatrix() const;
		
		/** Set image matrix before last change.
		 *
		 * Set new value of image matrix before last change.
		 *
		 * \param newLastImageMatrix New value of image matrix before last 
		 * change.
		 */
		virtual void setLastImageMatrix(Ionflux::GeoUtils::Matrix4* 
		newLastImageMatrix);
};

}

}

/** \file DeferredTransform.hpp
 * \brief Deferred matrix transformation (header).
 */
#endif
