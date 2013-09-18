#ifndef IONFLUX_GEOUTILS_SHAPE3
#define IONFLUX_GEOUTILS_SHAPE3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Shape3.hpp                      Shape (3D) (header).
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
#include "geoutils/Vertex3.hpp"
#include "geoutils/TransformableObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Shape3.
class Shape3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Shape3ClassInfo();
		/// Destructor.
		virtual ~Shape3ClassInfo();
};

/** Shape (3D).
 * \ingroup geoutils
 *
 * A shape in three-dimensional space.
 */
class Shape3
: virtual public Ionflux::GeoUtils::TransformableObject
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const Shape3ClassInfo shape3ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new Shape3 object.
		 */
		Shape3();
		
		/** Constructor.
		 *
		 * Construct new Shape3 object.
		 *
		 * \param other Other object.
		 */
		Shape3(const Ionflux::GeoUtils::Shape3& other);
		
		/** Destructor.
		 *
		 * Destruct Shape3 object.
		 */
		virtual ~Shape3();
		
		/** Scale.
		 *
		 * Scale the shape by the specified scale factors.
		 *
		 * \param s Vector of scale factors.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Shape3& scale(const 
		Ionflux::GeoUtils::Vector3& s);
		
		/** Translate.
		 *
		 * Translate the shape by the specified vector.
		 *
		 * \param t Translation vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Shape3& translate(const 
		Ionflux::GeoUtils::Vector3& t);
		
		/** Rotate.
		 *
		 * Rotate the shape by the specified angle around the specified axis.
		 *
		 * \param phi Angle.
		 * \param axis Axis.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Shape3& rotate(double phi, 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
		
		/** Normalize.
		 *
		 * Normalize the shape, i.e. scale to unit size.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Shape3& normalize();
		
		/** Center.
		 *
		 * Center the shape using the specified method and origin vector.
		 *
		 * \param method Centering method.
		 * \param origin Origin or offset vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Shape3& 
		center(Ionflux::GeoUtils::CenteringMethod method = 
		Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* origin 
		= 0);
		
		/** Matrix transformation.
		 *
		 * Apply a transformation matrix to the shape.
		 *
		 * \param matrix Transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Shape3& transform(const 
		Ionflux::GeoUtils::Matrix3& matrix);
		
		/** Matrix transformation.
		 *
		 * Apply a transformation matrix to the shape.
		 *
		 * \param matrix Transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Shape3& transform(const 
		Ionflux::GeoUtils::Matrix4& matrix);
		
		/** View/image transformation.
		 *
		 * Apply a view transformation matrix and an optional image 
		 * transformation matrix to the shape.
		 *
		 * \param view View transformation matrix.
		 * \param image Image transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Shape3& transformVI(const 
		Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4* image
		= 0);
		
		/** Check vertex.
		 *
		 * Check whether the specified vertex lies within the shape.
		 *
		 * \param v Vertex.
		 * \param t Tolerance.
		 *
		 * \return Result of the check.
		 */
		virtual bool checkVertex(const Ionflux::GeoUtils::Vertex3& v, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
		
		/** Duplicate.
		 *
		 * Create an exact duplicate of the shape. The duplicate is a new 
		 * object which must be managed by the caller.
		 *
		 * \return The duplicated object.
		 */
		virtual Ionflux::GeoUtils::Shape3& duplicate();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Shape3& operator=(const 
		Ionflux::GeoUtils::Shape3& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Shape3* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Shape3* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Shape3* create(Ionflux::ObjectBase::IFObject* 
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

/** \file Shape3.hpp
 * \brief Shape (3D) (header).
 */
#endif
