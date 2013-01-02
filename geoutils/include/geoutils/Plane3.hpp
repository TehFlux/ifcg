#ifndef IONFLUX_GEOUTILS_PLANE3
#define IONFLUX_GEOUTILS_PLANE3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Plane3.hpp                      Plane (3D) (header).
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
#include "geoutils/Matrix3.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Plane3.
class Plane3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Plane3ClassInfo();
		/// Destructor.
		virtual ~Plane3ClassInfo();
};

/** Plane (3D).
 * \ingroup geoutils
 *
 * A plane in three-dimensional space.
 */
class Plane3
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Position vector.
		Ionflux::GeoUtils::Vector3 p;
		/// Direction vector (u).
		Ionflux::GeoUtils::Vector3 u;
		/// Direction vector (v).
		Ionflux::GeoUtils::Vector3 v;
		
	public:
		/// XY plane.
		static const Ionflux::GeoUtils::Plane3 XY;
		/// YZ plane.
		static const Ionflux::GeoUtils::Plane3 YZ;
		/// ZX plane.
		static const Ionflux::GeoUtils::Plane3 ZX;
		/// Class information instance.
		static const Plane3ClassInfo plane3ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Plane3 object.
		 */
		Plane3();
		
		/** Constructor.
		 *
		 * Construct new Plane3 object.
		 *
		 * \param other Other object.
		 */
		Plane3(const Ionflux::GeoUtils::Plane3& other);
		
		/** Constructor.
		 *
		 * Construct new Plane3 object.
		 *
		 * \param initP Position vector.
		 * \param initU Direction vector (u).
		 * \param initV Direction vector (v).
		 */
		Plane3(const Ionflux::GeoUtils::Vector3& initP, const 
		Ionflux::GeoUtils::Vector3& initU, const Ionflux::GeoUtils::Vector3& 
		initV);
		
		/** Destructor.
		 *
		 * Destruct Plane3 object.
		 */
		virtual ~Plane3();
		
		/** Get tangent vector.
		 *
		 * Get the tangent vector of the plane.
		 *
		 * \return Tangent vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getTangent() const;
		
		/** Get binormal vector.
		 *
		 * Get the binormal vector of the plane.
		 *
		 * \return Binormal vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getBinormal() const;
		
		/** Get normal vector.
		 *
		 * Get the normal vector of the plane.
		 *
		 * \return Normal vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getNormal() const;
		
		/** Get tangent space base matrix.
		 *
		 * Calculate the (orthogonal) base matrix of the tangent space for the
		 * plane.
		 *
		 * \return Tangent space matrix.
		 */
		virtual Ionflux::GeoUtils::Matrix3 getTangentBase() const;
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Plane.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Plane3& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Plane.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Plane3& other) const;
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Create plane from normal vector.
		 *
		 * Create a plane from the specified normal vector. If a linearly 
		 * independent tangent vector is specified as well, that vector will 
		 * be orthonormalized and then used to construct the binormal vector. 
		 * If no tangent vector is specified or the tangent vector is not 
		 * linearly independent, the tangent and binormal will be determined 
		 * by the implementation.
		 *
		 * \param n Normal vector.
		 * \param t Tangent vector.
		 * \param p Position vector.
		 *
		 * \return Plane.
		 */
		static Ionflux::GeoUtils::Plane3 createFromNormal(const 
		Ionflux::GeoUtils::Vector3& n, const Ionflux::GeoUtils::Vector3& t = 
		Ionflux::GeoUtils::Vector3::E_X, const Ionflux::GeoUtils::Vector3& p = 
		Ionflux::GeoUtils::Vector3::ZERO);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Plane3& operator=(const 
		Ionflux::GeoUtils::Plane3& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Plane3* copy() const;
		
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
		
		/** Get direction vector (u).
		 *
		 * \return Current value of direction vector (u).
		 */
		virtual Ionflux::GeoUtils::Vector3 getU() const;
		
		/** Set direction vector (u).
		 *
		 * Set new value of direction vector (u).
		 *
		 * \param newU New value of direction vector (u).
		 */
		virtual void setU(const Ionflux::GeoUtils::Vector3& newU);
		
		/** Get direction vector (v).
		 *
		 * \return Current value of direction vector (v).
		 */
		virtual Ionflux::GeoUtils::Vector3 getV() const;
		
		/** Set direction vector (v).
		 *
		 * Set new value of direction vector (v).
		 *
		 * \param newV New value of direction vector (v).
		 */
		virtual void setV(const Ionflux::GeoUtils::Vector3& newV);
};

}

}

/** \file Plane3.hpp
 * \brief Plane (3D) (header).
 */
#endif
