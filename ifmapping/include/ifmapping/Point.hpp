#ifndef IONFLUX_MAPPING_POINT
#define IONFLUX_MAPPING_POINT
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Point.hpp                       Point (header).
 * =========================================================================
 *
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFMapping - Ionflux Mapping Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFMapping - Ionflux Mapping Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "ifobject/types.hpp"
#include "ifmapping/types.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class Point.
class PointClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		PointClassInfo();
		/// Destructor.
		virtual ~PointClassInfo();
};

/** Point.
 * \ingroup geoutils
 *
 * A point with three coordinates.
 */
class Point
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// X coordinate.
		Ionflux::Mapping::MappingValue x;
		/// Y coordinate.
		Ionflux::Mapping::MappingValue y;
		/// Z coordinate.
		Ionflux::Mapping::MappingValue z;
		
	public:
		/// Origin.
		static const Ionflux::Mapping::Point ORIGIN;
		/// Default standard deviation.
		static const Ionflux::Mapping::Point DEFAULT_STD_DEV;
		/// All ones.
		static const Ionflux::Mapping::Point ONES;
		/// Class information instance.
		static const PointClassInfo pointClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Point object.
		 */
		Point();
		
		/** Constructor.
		 *
		 * Construct new Point object.
		 *
		 * \param other Other object.
		 */
		Point(const Ionflux::Mapping::Point& other);
		
		/** Constructor.
		 *
		 * Construct new Point object.
		 *
		 * \param initX Element (X).
		 * \param initY Element (Y).
		 * \param initZ Element (Z).
		 */
		Point(Ionflux::Mapping::MappingValue initX, 
		Ionflux::Mapping::MappingValue initY, Ionflux::Mapping::MappingValue 
		initZ);
		
		/** Constructor.
		 *
		 * Construct new Point object.
		 *
		 * \param initCoords Coordinate vector.
		 */
		Point(const Ionflux::ObjectBase::DoubleVector& initCoords);
		
		/** Destructor.
		 *
		 * Destruct Point object.
		 */
		virtual ~Point();
		
		/** Set coordinates.
		 *
		 * Set coordinates from a vector of doubles. If the vector contains 
		 * fewer than the required number of coordinates, the remaining 
		 * coordinates will be left alone.
		 *
		 * \param newCoords Coordinate vector.
		 */
		virtual void setCoords(const Ionflux::ObjectBase::DoubleVector& 
		newCoords);
		
		/** Get coordinates.
		 *
		 * Store the coordinates of the vertex in a vector of doubles.
		 *
		 * \param target Target vector.
		 */
		virtual void getCoords(Ionflux::ObjectBase::DoubleVector& target) const;
		
		/** Get coordinate.
		 *
		 * Get the coordinate with the specified index.
		 *
		 * \param index Index.
		 *
		 * \return Element at the specified index.
		 */
		virtual Ionflux::Mapping::MappingValue getCoord(int index) const;
		
		/** Set coordinate.
		 *
		 * Set the coordinate with the specified index.
		 *
		 * \param index Index.
		 * \param value Value.
		 */
		virtual void setCoord(int index, Ionflux::Mapping::MappingValue value);
		
		/** Interpolate points.
		 *
		 * Linearly interpolate the point coordinates and the coordinates of 
		 * the other point using the specified parameter.
		 *
		 * \param other Point.
		 * \param t Parameter.
		 *
		 * \return Interpolated vertex.
		 */
		virtual Ionflux::Mapping::Point interpolate(const 
		Ionflux::Mapping::Point& other, Ionflux::Mapping::MappingValue t) const;
		
		/** Addition operator.
		 *
		 * Add a point offset.
		 *
		 * \param other Point.
		 *
		 * \return Result of the addition.
		 */
		virtual Ionflux::Mapping::Point operator+(const Ionflux::Mapping::Point& 
		other) const;
		
		/** Multiplication operator.
		 *
		 * Scale a point by factors taken from another point.
		 *
		 * \param other Point.
		 *
		 * \return Result of the multiplication.
		 */
		virtual Ionflux::Mapping::Point operator*(const Ionflux::Mapping::Point& 
		other) const;
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Point.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::Mapping::Point& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Point.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::Mapping::Point& other) const;
		
		/** Subscript operator.
		 *
		 * Subscript operator.
		 *
		 * \param index Index.
		 *
		 * \return Element at specified index.
		 */
		virtual Ionflux::Mapping::MappingValue operator[](int index) const;
		
		/** Get random point.
		 *
		 * Generate a random point.
		 *
		 * \return Random point.
		 */
		static Ionflux::Mapping::Point getRandom();
		
		/** Get random normal point.
		 *
		 * Generate a random point using a normal distribution for each 
		 * coordinate. The mean value and standard deviation to be used for 
		 * each coordinate can be specified as two points.
		 *
		 * \param mean Mean value.
		 * \param stdDev Standard deviation.
		 *
		 * \return Random point.
		 */
		static Ionflux::Mapping::Point getRandomNorm(const 
		Ionflux::Mapping::Point& mean = Ionflux::Mapping::Point::ORIGIN, const 
		Ionflux::Mapping::Point& stdDev = 
		Ionflux::Mapping::Point::DEFAULT_STD_DEV);
		
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
		virtual Ionflux::Mapping::Point& operator=(const Ionflux::Mapping::Point&
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::Point* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::Point* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::Mapping::Point* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get x coordinate.
		 *
		 * \return Current value of x coordinate.
		 */
		virtual Ionflux::Mapping::MappingValue getX() const;
		
		/** Set x coordinate.
		 *
		 * Set new value of x coordinate.
		 *
		 * \param newX New value of x coordinate.
		 */
		virtual void setX(Ionflux::Mapping::MappingValue newX);
		
		/** Get y coordinate.
		 *
		 * \return Current value of y coordinate.
		 */
		virtual Ionflux::Mapping::MappingValue getY() const;
		
		/** Set y coordinate.
		 *
		 * Set new value of y coordinate.
		 *
		 * \param newY New value of y coordinate.
		 */
		virtual void setY(Ionflux::Mapping::MappingValue newY);
		
		/** Get z coordinate.
		 *
		 * \return Current value of z coordinate.
		 */
		virtual Ionflux::Mapping::MappingValue getZ() const;
		
		/** Set z coordinate.
		 *
		 * Set new value of z coordinate.
		 *
		 * \param newZ New value of z coordinate.
		 */
		virtual void setZ(Ionflux::Mapping::MappingValue newZ);
};

}

}

/** \file Point.hpp
 * \brief Point (header).
 */
#endif
