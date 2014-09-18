#ifndef IONFLUX_GEOUTILS_TRANSFORMABLEOBJECT
#define IONFLUX_GEOUTILS_TRANSFORMABLEOBJECT
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TransformableObject.hpp         Transformable object (header).
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
#include "geoutils/Range3.hpp"
#include "geoutils/Vector3.hpp"
#include "geoutils/Matrix4.hpp"
#include "geoutils/DeferredTransform.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class TransformableObjectXMLFactory;

}

/// Class information for class TransformableObject.
class TransformableObjectClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		TransformableObjectClassInfo();
		/// Destructor.
		virtual ~TransformableObjectClassInfo();
};

/** Transformable object.
 * \ingroup geoutils
 *
 * Base class for objects that support basic transformations and can be 
 * part of a group of such objects.
 */
class TransformableObject
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Bounds cache.
		Ionflux::GeoUtils::Range3* boundsCache;
		/// Deferred transformation.
		Ionflux::GeoUtils::DeferredTransform* deferredTransform;
		
		/** recalculate bounds.
		 *
		 * Process a transform change.
		 */
		virtual void recalculateBounds();
		
		/** Process transform change.
		 *
		 * Process a transform change.
		 */
		virtual void processTransformChange();
		
	public:
		/// Class information instance.
		static const TransformableObjectClassInfo transformableObjectClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new TransformableObject object.
		 */
		TransformableObject();
		
		/** Constructor.
		 *
		 * Construct new TransformableObject object.
		 *
		 * \param other Other object.
		 */
		TransformableObject(const Ionflux::GeoUtils::TransformableObject& other);
		
		/** Destructor.
		 *
		 * Destruct TransformableObject object.
		 */
		virtual ~TransformableObject();
		
		/** Clear transformations.
		 *
		 * Clear the transformation matrices of the transformable object.
		 */
		virtual void clearTransformations();
		
		/** Clear.
		 *
		 * Clear the internal state of the transformable object.
		 */
		virtual void clear();
		
		/** copy transform.
		 *
		 * Copy the transformation matrices from another object.
		 *
		 * \param other Transformable object.
		 */
		virtual void copyTransform(const Ionflux::GeoUtils::TransformableObject& 
		other);
		
		/** Transform changed handler.
		 *
		 * This event handler is invoked when the transform matrix changes.
		 */
		virtual void onTransformChanged();
		
		/** Transform changed handler.
		 *
		 * This event handler is invoked when the view/image transform matrix 
		 * changes.
		 */
		virtual void onVIChanged();
		
		/** Check transform status.
		 *
		 * Check the transform matrix. If it is equal to the unit matrix 
		 * within the tolerance, use of the matrix for object transformations 
		 * will be disabled. If it is not equal to the unit matrix, check if 
		 * the transform has changed. If it has changed, call the 
		 * onTransformChanged() handler.
		 *
		 * \param t Tolerance.
		 *
		 * \return The result of the check.
		 */
		virtual bool checkTransform(double t = 
		Ionflux::GeoUtils::DeferredTransform::COMPARE_TOLERANCE);
		
		/** Check view/image transform status.
		 *
		 * Check the view/image transform matrices. If both are equal to the 
		 * unit matrix within the tolerance, use of the matrices for object 
		 * transformations will be disabled. If the matrices are not equal to 
		 * the unit matrix, check if the matrices have changed. If either 
		 * matrix has changed, call the onVIChanged() handler.
		 *
		 * \param t Tolerance.
		 *
		 * \return The result of the check.
		 */
		virtual bool checkVI(double t = 
		Ionflux::GeoUtils::DeferredTransform::COMPARE_TOLERANCE);
		
		/** Scale.
		 *
		 * Scale the object by the specified scale factors.
		 *
		 * \param s Vector of scale factors.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::TransformableObject& scale(const 
		Ionflux::GeoUtils::Vector3& s);
		
		/** Scale.
		 *
		 * Scale the object by the specified scale factors.
		 *
		 * \param sx Scale factor (X).
		 * \param sy Scale factor (Y).
		 * \param sz Scale factor (Z).
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::TransformableObject& scale(double sx, double 
		sy = 1., double sz = 1.);
		
		/** Translate.
		 *
		 * Translate the object by the specified vector.
		 *
		 * \param t Translation vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::TransformableObject& translate(const 
		Ionflux::GeoUtils::Vector3& t);
		
		/** Rotate.
		 *
		 * Rotate the object by the specified angle around the specified axis.
		 *
		 * \param phi Angle.
		 * \param axis Axis.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::TransformableObject& rotate(double phi, 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
		
		/** Swap axes.
		 *
		 * Swap axes.
		 *
		 * \param x Axis (x).
		 * \param y Axis (y).
		 * \param z Axis (z).
		 * \param w Axis (w).
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::TransformableObject& 
		swapAxes(Ionflux::GeoUtils::AxisID x = Ionflux::GeoUtils::AXIS_X, 
		Ionflux::GeoUtils::AxisID y = Ionflux::GeoUtils::AXIS_Y, 
		Ionflux::GeoUtils::AxisID z = Ionflux::GeoUtils::AXIS_Z, 
		Ionflux::GeoUtils::AxisID w = Ionflux::GeoUtils::AXIS_W);
		
		/** Normalize.
		 *
		 * Normalize the object, i.e. scale to unit size.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::TransformableObject& normalize();
		
		/** Center.
		 *
		 * Center the object using the specified method and origin vector.
		 *
		 * \param method Centering method.
		 * \param origin Origin or offset vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::TransformableObject& 
		center(Ionflux::GeoUtils::CenteringMethod method = 
		Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* origin 
		= 0);
		
		/** Matrix transformation.
		 *
		 * Apply a transformation matrix to the object.
		 *
		 * \param matrix Transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::TransformableObject& transform(const 
		Ionflux::GeoUtils::Matrix3& matrix);
		
		/** Matrix transformation.
		 *
		 * Apply a transformation matrix to the object.
		 *
		 * \param matrix Transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::TransformableObject& transform(const 
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
		virtual Ionflux::GeoUtils::TransformableObject& transformVI(const 
		Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4* image
		= 0);
		
		/** Apply transformations.
		 *
		 * Apply transformations that have been accumulated in the 
		 * transformation matrices. This can be used by derived classes that 
		 * have an internal structure to apply the transformations to that 
		 * internal structure.
		 *
		 * \param recursive Apply transformations recursively.
		 */
		virtual void applyTransform(bool recursive = false);
		
		/** Get barycenter.
		 *
		 * Get the barycenter vector for the transformable object.
		 *
		 * \return Barycenter vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getBarycenter();
		
		/** Get bounds.
		 *
		 * Get the bounds for the transformable object.
		 *
		 * \return Bounds.
		 */
		virtual Ionflux::GeoUtils::Range3 getBounds();
		
		/** Get use transformation matrix flag.
		 *
		 * Check whether the transformation matrix should be used.
		 *
		 * \return Value of the use transformation matrix flag.
		 */
		virtual bool useTransform() const;
		
		/** Get use view/image matrices flag.
		 *
		 * Check whether the view/image transformation matrices should be 
		 * used.
		 *
		 * \return Value of the use view/image transformation matrices flag.
		 */
		virtual bool useVI() const;
		
		/** Get transformation matrix changed flag.
		 *
		 * Check whether the transformation matrix has changed since the last 
		 * check.
		 *
		 * \return Value of the use transformation matrix flag.
		 */
		virtual bool transformChanged() const;
		
		/** Get view/image transformation matrix changed flag.
		 *
		 * Check whether the view/image transformation matrices have changed 
		 * since the last check.
		 *
		 * \return Value of the use view/image transformation matrices flag.
		 */
		virtual bool viChanged() const;
		
		/** Duplicate.
		 *
		 * Create an exact duplicate of the object. The duplicate is a new 
		 * object which must be managed by the caller.
		 *
		 * \return The duplicated object.
		 */
		virtual Ionflux::GeoUtils::TransformableObject& duplicate();
		
		/** Get transformation matrix.
		 *
		 * Get the current transformation matrix. If the deferred 
		 * transformation object is not set or the transformation matrix is 
		 * null, an exception is thrown.
		 *
		 * \return The current transformation matrix.
		 */
		virtual Ionflux::GeoUtils::Matrix4* getTransformMatrix() const;
		
		/** Get view transformation matrix.
		 *
		 * Get the current view transformation matrix. If the deferred 
		 * transformation object is not set or the view transformation matrix 
		 * is null, an exception is thrown.
		 *
		 * \return The current view transformation matrix.
		 */
		virtual Ionflux::GeoUtils::Matrix4* getViewMatrix() const;
		
		/** Get image transformation matrix.
		 *
		 * Get the current image transformation matrix. If the deferred 
		 * transformation object is not set, an exception is thrown. Since the
		 * image matrix is allowed to be zero, no exception is thrown if this 
		 * is the case.
		 *
		 * \return The current view transformation matrix.
		 */
		virtual Ionflux::GeoUtils::Matrix4* getImageMatrix() const;
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
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
		virtual Ionflux::GeoUtils::TransformableObject& operator=(const 
		Ionflux::GeoUtils::TransformableObject& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformableObject* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformableObject* 
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
		static Ionflux::GeoUtils::TransformableObject* 
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
		
		/** Get deferred transformation.
		 *
		 * \return Current value of deferred transformation.
		 */
		virtual Ionflux::GeoUtils::DeferredTransform* getDeferredTransform() 
		const;
		
		/** Set deferred transformation.
		 *
		 * Set new value of deferred transformation.
		 *
		 * \param newDeferredTransform New value of deferred transformation.
		 */
		virtual void setDeferredTransform(Ionflux::GeoUtils::DeferredTransform* 
		newDeferredTransform);
};

}

}

/** \file TransformableObject.hpp
 * \brief Transformable object (header).
 */
#endif
