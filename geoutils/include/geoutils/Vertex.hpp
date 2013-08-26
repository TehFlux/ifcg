#ifndef IONFLUX_GEOUTILS_VERTEX
#define IONFLUX_GEOUTILS_VERTEX
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vertex.hpp                      Mesh vertex (header).
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
#include "geoutils/Vertex3.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Vertex.
class VertexClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		VertexClassInfo();
		/// Destructor.
		virtual ~VertexClassInfo();
};

/** Mesh vertex.
 * \ingroup geoutils
 *
 * A vertex which can be used in a mesh. In addition to the vertex 
 * coordinates, this vertex class also supports a normal vector.
 */
class Vertex
: public Ionflux::GeoUtils::Vertex3
{
	private:
		
	protected:
		/// Normal vector.
		Ionflux::GeoUtils::Vector3 normal;
		
	public:
		/// Class information instance.
		static const VertexClassInfo vertexClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Vertex object.
		 */
		Vertex();
		
		/** Constructor.
		 *
		 * Construct new Vertex object.
		 *
		 * \param other Other object.
		 */
		Vertex(const Ionflux::GeoUtils::Vertex& other);
		
		/** Constructor.
		 *
		 * Construct new Vertex object.
		 *
		 * \param initX Element (X).
		 * \param initY Element (Y).
		 * \param initZ Element (Z).
		 * \param initNormal Normal vector.
		 */
		Vertex(double initX, double initY, double initZ, const 
		Ionflux::GeoUtils::Vector3& initNormal = 
		Ionflux::GeoUtils::Vector3::E_X);
		
		/** Constructor.
		 *
		 * Construct new Vertex object.
		 *
		 * \param initCoords Coordinate vector.
		 * \param initNormal Normal vector.
		 */
		Vertex(const Ionflux::ObjectBase::DoubleVector& initCoords, const 
		Ionflux::GeoUtils::Vector3& initNormal = 
		Ionflux::GeoUtils::Vector3::E_X);
		
		/** Constructor.
		 *
		 * Construct new Vertex object.
		 *
		 * \param initCoords Coordinate vector.
		 * \param initNormal Normal vector.
		 */
		Vertex(const Ionflux::GeoUtils::Vector3& initCoords, const 
		Ionflux::GeoUtils::Vector3& initNormal = 
		Ionflux::GeoUtils::Vector3::E_X);
		
		/** Destructor.
		 *
		 * Destruct Vertex object.
		 */
		virtual ~Vertex();
		
		/** Interpolate vertices.
		 *
		 * Interpolate the vertex coordinates and the coordinates of the other
		 * vertex using the specified parameter. The normal vector is also 
		 * interpolated.
		 *
		 * \param other Vertex.
		 * \param t Parameter.
		 * \param interpolator Interpolator.
		 *
		 * \return Interpolated vertex.
		 */
		virtual Ionflux::GeoUtils::Vertex interpolate(const 
		Ionflux::GeoUtils::Vertex& other, double t, 
		Ionflux::GeoUtils::Interpolator* interpolator = 0) const;
		
		/** Scale.
		 *
		 * Scale the object by the specified scale factors.
		 *
		 * \param s Vector of scale factors.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex& scale(const 
		Ionflux::GeoUtils::Vector3& s);
		
		/** Translate.
		 *
		 * Translate the object by the specified vector.
		 *
		 * \param t Translation vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex& translate(const 
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
		virtual Ionflux::GeoUtils::Vertex& rotate(double phi, 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
		
		/** Normalize.
		 *
		 * Normalize the object, i.e. scale to unit size.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex& normalize();
		
		/** Center.
		 *
		 * Center the object using the specified method and origin vector.
		 *
		 * \param method Centering method.
		 * \param origin Origin or offset vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex& 
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
		virtual Ionflux::GeoUtils::Vertex& transform(const 
		Ionflux::GeoUtils::Matrix4& matrix);
		
		/** Matrix transformation.
		 *
		 * Apply a transformation matrix to the object.
		 *
		 * \param matrix Transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex& transform(const 
		Ionflux::GeoUtils::Matrix3& matrix);
		
		/** Duplicate.
		 *
		 * Create an exact duplicate of the object. The duplicate is a new 
		 * object which must be managed by the caller.
		 *
		 * \return The duplicated object.
		 */
		virtual Ionflux::GeoUtils::Vertex& duplicate();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Create.
		 *
		 * Create a new vertex.
		 *
		 * \param newX Element (X).
		 * \param newY Element (Y).
		 * \param newZ Element (Z).
		 *
		 * \return New vertex.
		 */
		static Ionflux::GeoUtils::Vertex* create(double newX, double newY, double
		newZ);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Vertex& operator=(const 
		Ionflux::GeoUtils::Vertex& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Vertex* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Vertex* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Vertex* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get normal vector.
		 *
		 * \return Current value of normal vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getNormal() const;
		
		/** Set normal vector.
		 *
		 * Set new value of normal vector.
		 *
		 * \param newNormal New value of normal vector.
		 */
		virtual void setNormal(const Ionflux::GeoUtils::Vector3& newNormal);
};

}

}

/** \file Vertex.hpp
 * \brief Mesh vertex (header).
 */
#endif
