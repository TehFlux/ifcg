#ifndef IONFLUX_GEOUTILS_LINE3
#define IONFLUX_GEOUTILS_LINE3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Line3.hpp                       Line (3D) (header).
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
#include "geoutils/Plane3.hpp"
#include "geoutils/Polygon3.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Line3.
class Line3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Line3ClassInfo();
		/// Destructor.
		virtual ~Line3ClassInfo();
};

/** Line (3D).
 * \ingroup geoutils
 *
 * A line in three-dimensional space.
 */
class Line3
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Position vector.
		Ionflux::GeoUtils::Vector3 p;
		/// Direction vector (u).
		Ionflux::GeoUtils::Vector3 u;
		
	public:
		/// X axis.
		static const Ionflux::GeoUtils::Line3 X;
		/// Y axis.
		static const Ionflux::GeoUtils::Line3 Y;
		/// Z axis.
		static const Ionflux::GeoUtils::Line3 Z;
		/// Class information instance.
		static const Line3ClassInfo line3ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Line3 object.
		 */
		Line3();
		
		/** Constructor.
		 *
		 * Construct new Line3 object.
		 *
		 * \param other Other object.
		 */
		Line3(const Ionflux::GeoUtils::Line3& other);
		
		/** Constructor.
		 *
		 * Construct new Line3 object.
		 *
		 * \param initP Position vector.
		 * \param initU Direction vector (u).
		 */
		Line3(const Ionflux::GeoUtils::Vector3& initP, const 
		Ionflux::GeoUtils::Vector3& initU);
		
		/** Destructor.
		 *
		 * Destruct Line3 object.
		 */
		virtual ~Line3();
		
		/** Intersect line.
		 *
		 * Calculate the intersection point of the line and another line.
		 *
		 * \param other Line.
		 * \param result Intersection point.
		 *
		 * \return \c true on success, \c false if no intersection exists.
		 */
		virtual bool intersect(const Ionflux::GeoUtils::Line3& other, 
		Ionflux::GeoUtils::Vector3& result) const;
		
		/** Intersect plane.
		 *
		 * Calculate the intersection point of the line and the plane.
		 *
		 * \param plane Plane.
		 * \param result Intersection point.
		 *
		 * \return \c true on success, \c false if no intersection exists.
		 */
		virtual bool intersect(const Ionflux::GeoUtils::Plane3& plane, 
		Ionflux::GeoUtils::Vector3& result) const;
		
		/** Polygon intersection test.
		 *
		 * Check for an intersection between the line and the plane defined by
		 * the first three vertices of the polygon. Returns \c true if the 
		 * intersection point is within the polygon. Returns \c false 
		 * otherwise. Throws GeoUtilsError if the polygon is not planar.
		 *
		 * \param poly Polygon.
		 * \param t Tolerance.
		 *
		 * \return Result of the intersection test.
		 */
		virtual bool intersectionInPoly(const Ionflux::GeoUtils::Polygon3& poly, 
		double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Line.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Line3& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Line.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Line3& other) const;
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Line3& operator=(const 
		Ionflux::GeoUtils::Line3& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Line3* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Line3* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Line3* create(Ionflux::ObjectBase::IFObject* 
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
};

}

}

/** \file Line3.hpp
 * \brief Line (3D) (header).
 */
#endif
