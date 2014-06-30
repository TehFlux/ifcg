#ifndef IONFLUX_GEOUTILS_OBJECT3
#define IONFLUX_GEOUTILS_OBJECT3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Object3.hpp                     Object (3D) (header).
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
#include "geoutils/TransformableObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Mesh;

namespace XMLUtils
{

class Object3XMLFactory;

}

/// Class information for class Object3.
class Object3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Object3ClassInfo();
		/// Destructor.
		virtual ~Object3ClassInfo();
};

/** Object (3D).
 * \ingroup geoutils
 *
 * An object in three-dimensional space that can be visualized using a 
 * mesh.
 */
class Object3
: public Ionflux::GeoUtils::TransformableObject
{
	private:
		
	protected:
		/// Mesh.
		Ionflux::GeoUtils::Mesh* mesh;
		
		/** Recalculate bounds.
		 *
		 * Recalculate the bounds for the object.
		 */
		virtual void recalculateBounds();
		
	public:
		/// Class information instance.
		static const Object3ClassInfo object3ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new Object3 object.
		 */
		Object3();
		
		/** Constructor.
		 *
		 * Construct new Object3 object.
		 *
		 * \param other Other object.
		 */
		Object3(const Ionflux::GeoUtils::Object3& other);
		
		/** Constructor.
		 *
		 * Construct new Object3 object.
		 *
		 * \param initMesh Mesh.
		 */
		Object3(Ionflux::GeoUtils::Mesh* initMesh);
		
		/** Destructor.
		 *
		 * Destruct Object3 object.
		 */
		virtual ~Object3();
		
		/** Update.
		 *
		 * Update all state.
		 */
		virtual void update();
		
		/** Clear.
		 *
		 * Removes all items and resets state.
		 */
		virtual void clear();
		
		/** Apply transformations.
		 *
		 * Apply transformations that have been accumulated in the 
		 * transformation matrices.
		 *
		 * \param recursive Apply transformations recursively.
		 */
		virtual void applyTransform(bool recursive = false);
		
		/** Scale.
		 *
		 * Scale the object by the specified scale factors.
		 *
		 * \param s Vector of scale factors.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Object3& scale(const 
		Ionflux::GeoUtils::Vector3& s);
		
		/** Translate.
		 *
		 * Translate the object by the specified vector.
		 *
		 * \param t Translation vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Object3& translate(const 
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
		virtual Ionflux::GeoUtils::Object3& rotate(double phi, 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
		
		/** Normalize.
		 *
		 * Normalize the object, i.e. scale to unit size.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Object3& normalize();
		
		/** Center.
		 *
		 * Center the object using the specified method and origin vector.
		 *
		 * \param method Centering method.
		 * \param origin Origin or offset vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Object3& 
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
		virtual Ionflux::GeoUtils::Object3& transform(const 
		Ionflux::GeoUtils::Matrix3& matrix);
		
		/** Matrix transformation.
		 *
		 * Apply a transformation matrix to the object.
		 *
		 * \param matrix Transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Object3& transform(const 
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
		virtual Ionflux::GeoUtils::Object3& transformVI(const 
		Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4* image
		= 0);
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Duplicate.
		 *
		 * Create an exact duplicate of the object. The duplicate is a new 
		 * object which must be managed by the caller.
		 *
		 * \return The duplicated object.
		 */
		virtual Ionflux::GeoUtils::Object3& duplicate();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Object3& operator=(const 
		Ionflux::GeoUtils::Object3& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Object3* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Object3* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Object3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Object3 object.
		 *
		 * \param initMesh Mesh.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Object3* create(Ionflux::GeoUtils::Mesh* 
		initMesh, Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
		virtual void loadFromXMLFile(const std::string& FileName);
        
        /** Get XML object factory
		 *
		 * Get the XML object factory singleton for the class.
		 *
		 * \param fileName file name
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		
		/** Get mesh.
		 *
		 * \return Current value of mesh.
		 */
		virtual Ionflux::GeoUtils::Mesh* getMesh() const;
		
		/** Set mesh.
		 *
		 * Set new value of mesh.
		 *
		 * \param newMesh New value of mesh.
		 */
		virtual void setMesh(Ionflux::GeoUtils::Mesh* newMesh);
};

}

}

/** \file Object3.hpp
 * \brief Object (3D) (header).
 */
#endif
