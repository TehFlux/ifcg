#ifndef IONFLUX_GEOUTILS_SPHERE3
#define IONFLUX_GEOUTILS_SPHERE3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Sphere3.hpp                     Sphere (3D) (header).
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
#include "geoutils/Vector3.hpp"
#include "geoutils/Vertex3.hpp"
#include "geoutils/Matrix4.hpp"
#include "geoutils/Object3.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Sphere3.
class Sphere3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Sphere3ClassInfo();
		/// Destructor.
		virtual ~Sphere3ClassInfo();
};

/** Sphere (3D).
 * \ingroup geoutils
 *
 * A sphere in three-dimensional space.
 */
class Sphere3
: public Ionflux::GeoUtils::Object3
{
	private:
		
	protected:
		/// Position vector.
		Ionflux::GeoUtils::Vector3 p;
		/// Radius.
		double r;
		
	public:
		/// Unit sphere.
		static const Ionflux::GeoUtils::Sphere3 UNIT;
		/// Class information instance.
		static const Sphere3ClassInfo sphere3ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Sphere3 object.
		 */
		Sphere3();
		
		/** Constructor.
		 *
		 * Construct new Sphere3 object.
		 *
		 * \param other Other object.
		 */
		Sphere3(const Ionflux::GeoUtils::Sphere3& other);
		
		/** Constructor.
		 *
		 * Construct new Sphere3 object.
		 *
		 * \param initP Position vector.
		 * \param initR Radius.
		 */
		Sphere3(const Ionflux::GeoUtils::Vector3& initP, double initR);
		
		/** Destructor.
		 *
		 * Destruct Sphere3 object.
		 */
		virtual ~Sphere3();
		
		/** Get barycenter.
		 *
		 * Get the barycenter vector for the sphere.
		 *
		 * \return Barycenter vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getBarycenter() const;
		
		/** Get bounds.
		 *
		 * Get the bounds for the sphere.
		 *
		 * \return Bounds.
		 */
		virtual Ionflux::GeoUtils::Range3 getBounds() const;
		
		/** Check vertex.
		 *
		 * Check whether the specified vertex lies within the sphere.
		 *
		 * \param v Vertex.
		 * \param t Tolerance.
		 *
		 * \return Result of the check.
		 */
		virtual bool checkVertex(const Ionflux::GeoUtils::Vertex3& v, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Sphere.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Sphere3& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Sphere.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Sphere3& other) const;
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Scale.
		 *
		 * Scale the object by the specified scale factors.
		 *
		 * \param s Vector of scale factors.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Sphere3& scale(const 
		Ionflux::GeoUtils::Vector3& s);
		
		/** Translate.
		 *
		 * Translate the object by the specified vector.
		 *
		 * \param t Translation vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Sphere3& translate(const 
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
		virtual Ionflux::GeoUtils::Sphere3& rotate(double phi, 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
		
		/** Normalize.
		 *
		 * Normalize the object, i.e. scale to unit size.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Sphere3& normalize();
		
		/** Center.
		 *
		 * Center the object using the specified method and origin vector.
		 *
		 * \param method Centering method.
		 * \param origin Origin or offset vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Sphere3& 
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
		virtual Ionflux::GeoUtils::Sphere3& transform(const 
		Ionflux::GeoUtils::Matrix3& matrix);
		
		/** Matrix transformation.
		 *
		 * Apply a transformation matrix to the object.
		 *
		 * \param matrix Transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Sphere3& transform(const 
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
		virtual Ionflux::GeoUtils::Sphere3& transformVI(const 
		Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4* image
		= 0);
		
		/** Duplicate.
		 *
		 * Create an exact duplicate of the object. The duplicate is a new 
		 * object which must be managed by the caller.
		 *
		 * \return The duplicated object.
		 */
		virtual Ionflux::GeoUtils::Sphere3& duplicate();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Sphere3& operator=(const 
		Ionflux::GeoUtils::Sphere3& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Sphere3* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Sphere3* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Sphere3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get position vector.
		 *
		 * \return Current value of position vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getP() const;
		
		/** Set position vector.
		 *
		 * Set new value of position vector.
		 *
		 * \param newP New value of position vector.
		 */
		virtual void setP(const Ionflux::GeoUtils::Vector3& newP);
		
		/** Get radius.
		 *
		 * \return Current value of radius.
		 */
		virtual double getR() const;
		
		/** Set radius.
		 *
		 * Set new value of radius.
		 *
		 * \param newR New value of radius.
		 */
		virtual void setR(double newR);
};

}

}

/** \file Sphere3.hpp
 * \brief Sphere (3D) (header).
 */
#endif
