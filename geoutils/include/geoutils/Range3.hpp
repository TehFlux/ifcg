#ifndef IONFLUX_GEOUTILS_RANGE3
#define IONFLUX_GEOUTILS_RANGE3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Range3.hpp                      Range of values (3D) (header).
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
#include "geoutils/Range.hpp"
#include "geoutils/Vector2.hpp"
#include "geoutils/Vector3.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Line3;
class Vertex3Set;
class Mesh;

namespace XMLUtils
{

class Range3XMLFactory;

}

/// Class information for class Range3.
class Range3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Range3ClassInfo();
		/// Destructor.
		virtual ~Range3ClassInfo();
};

/** Range of values (3D).
 * \ingroup geoutils
 *
 * A range of values in three-dimensional space.
 */
class Range3
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Range (x).
		Ionflux::GeoUtils::Range x;
		/// Range (y).
		Ionflux::GeoUtils::Range y;
		/// Range (z).
		Ionflux::GeoUtils::Range z;
		
	public:
		/// Class information instance.
		static const Range3ClassInfo range3ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new Range3 object.
		 */
		Range3();
		
		/** Constructor.
		 *
		 * Construct new Range3 object.
		 *
		 * \param other Other object.
		 */
		Range3(const Ionflux::GeoUtils::Range3& other);
		
		/** Constructor.
		 *
		 * Construct new Range3 object.
		 *
		 * \param initCenter Center vector.
		 * \param initRadius Radius vector.
		 */
		Range3(const Ionflux::GeoUtils::Vector3& initCenter, const 
		Ionflux::GeoUtils::Vector3* initRadius = 0);
		
		/** Constructor.
		 *
		 * Construct new Range3 object.
		 *
		 * \param initX Range (x).
		 * \param initY Range (y).
		 * \param initZ Range (z).
		 */
		Range3(const Ionflux::GeoUtils::Range& initX, const 
		Ionflux::GeoUtils::Range& initY, const Ionflux::GeoUtils::Range& initZ);
		
		/** Constructor.
		 *
		 * Construct new Range3 object.
		 *
		 * \param rx Range (x).
		 * \param ry Range (y).
		 * \param rz Range (z).
		 */
		Range3(const Ionflux::GeoUtils::Vector2& rx, const 
		Ionflux::GeoUtils::Vector2& ry, const Ionflux::GeoUtils::Vector2& rz);
		
		/** Constructor.
		 *
		 * Construct new Range3 object.
		 *
		 * \param xMin Minimum value (X).
		 * \param xMax Maximum value (X).
		 * \param yMin Minimum value (Y).
		 * \param yMax Maximum value (Y).
		 * \param zMin Minimum value (Z).
		 * \param zMax Maximum value (Z).
		 */
		Range3(double xMin, double xMax, double yMin, double yMax, double zMin, 
		double zMax);
		
		/** Constructor.
		 *
		 * Construct new Range3 object.
		 *
		 * \param initMin Minimum vector.
		 * \param edgeLength Edge length.
		 */
		Range3(const Ionflux::GeoUtils::Vector3& initMin, double edgeLength);
		
		/** Destructor.
		 *
		 * Destruct Range3 object.
		 */
		virtual ~Range3();
		
		/** Extend range.
		 *
		 * Extend the range to contain the values from the specified range.
		 *
		 * \param other Range.
		 */
		virtual void extend(const Ionflux::GeoUtils::Range3& other);
		
		/** Extend range.
		 *
		 * Extend the range to contain the values from the specified vector.
		 *
		 * \param v Vector.
		 */
		virtual void extend(const Ionflux::GeoUtils::Vector3& v);
		
		/** Extend range.
		 *
		 * Extend (or shrink) the range by the specified radius delta.
		 *
		 * \param rd radius delta.
		 */
		virtual void extend(double rd);
		
		/** Get center.
		 *
		 * Get the center vector of the range.
		 *
		 * \return Center of the range.
		 */
		virtual Ionflux::GeoUtils::Vector3 getCenter() const;
		
		/** Get radius vector.
		 *
		 * Get the radius vector of the range.
		 *
		 * \return Radius vector of the range.
		 */
		virtual Ionflux::GeoUtils::Vector3 getRadius() const;
		
		/** Get extent.
		 *
		 * Get the extent of the range.
		 *
		 * \return Extent of the range.
		 */
		virtual Ionflux::GeoUtils::Vector3 getExtent() const;
		
		/** Get extent.
		 *
		 * Get the extent of the range on the specified axis.
		 *
		 * \param axis Axis.
		 *
		 * \return Extent of the range.
		 */
		virtual double getExtent(Ionflux::GeoUtils::AxisID axis) const;
		
		/** Get value.
		 *
		 * Get the vector inside the range corresponding to the parameters. 
		 * For each dimension, s = 0 returns the minimum value and s = 1 
		 * returns the maximum value for that dimension.
		 *
		 * \param v0 Parameter (0).
		 * \param v1 Parameter (1).
		 * \param v2 Parameter (2).
		 *
		 * \return Value from the range.
		 */
		virtual Ionflux::GeoUtils::Vector3 getValue(double v0, double v1, double 
		v2) const;
		
		/** Get value.
		 *
		 * Get the vector inside the range corresponding to the parameter 
		 * vector. For each dimension, s = 0 returns the minimum value and s =
		 * 1 returns the maximum value for that dimension.
		 *
		 * \param v Parameter vector.
		 *
		 * \return Value from the range.
		 */
		virtual Ionflux::GeoUtils::Vector3 getValue(const 
		Ionflux::GeoUtils::Vector3 v) const;
		
		/** Get minimum value.
		 *
		 * Get the minimum vector contained within the range.
		 *
		 * \return Minimum vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getRMin() const;
		
		/** Get maximum value.
		 *
		 * Get the maximum vector contained within the range.
		 *
		 * \return Maximum vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getRMax() const;
		
		/** Clamp vector.
		 *
		 * Clamp the vector to the range.
		 *
		 * \param v Vector.
		 *
		 * \return Clamped vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 clamp(const Ionflux::GeoUtils::Vector3
		v) const;
		
		/** Get value.
		 *
		 * Get the vector inside the range corresponding to the parameter 
		 * vector. For each dimension, s = 0 returns the minimum value and s =
		 * 1 returns the maximum value for that dimension. The result is 
		 * clamped to the range.
		 *
		 * \param v Vector.
		 *
		 * \return Clamped value from the range.
		 */
		virtual Ionflux::GeoUtils::Vector3 getClampedValue(const 
		Ionflux::GeoUtils::Vector3 v) const;
		
		/** Get range for specified axis.
		 *
		 * Get the range for the specified axis.
		 *
		 * \param axis Axis.
		 *
		 * \return Range.
		 */
		virtual Ionflux::GeoUtils::Range getAxisRange(Ionflux::GeoUtils::AxisID 
		axis) const;
		
		/** Set bounds.
		 *
		 * Set bounds of the range to a single point, as specified by the 
		 * vector.
		 *
		 * \param v Vector.
		 */
		virtual void setBounds(const Ionflux::GeoUtils::Vector3& v);
		
		/** Set bounds.
		 *
		 * Set bounds of the range to the bounds of another range.
		 *
		 * \param other Range.
		 */
		virtual void setBounds(const Ionflux::GeoUtils::Range3& other);
		
		/** Set bounds.
		 *
		 * Set bounds of the range to a single point, as specified by the 
		 * vector. If the optional \c r is specified, the range will be 
		 * extended using \c r as the radius vector.
		 *
		 * \param v Vector.
		 * \param r Radius vector.
		 */
		virtual void setBounds(const Ionflux::GeoUtils::Vector3& v, const 
		Ionflux::GeoUtils::Vector3* r);
		
		/** Set bounds.
		 *
		 * Set bounds of the range to include a box with the specified minimum
		 * vector and edge length.
		 *
		 * \param v Minimum vector.
		 * \param edgeLength Edge length.
		 */
		virtual void setBounds(const Ionflux::GeoUtils::Vector3& v, double 
		edgeLength);
		
		/** Compare ranges (per axis).
		 *
		 * Compares the ranges on each axis separately. See Range3::compare() 
		 * for details on the return values.
		 *
		 * \param other Range.
		 * \param t Tolerance.
		 *
		 * \return Result of the comparison.
		 */
		virtual Ionflux::GeoUtils::RangeCompResult3 compare3(const 
		Ionflux::GeoUtils::Range3& other, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
		
		/** Compare ranges.
		 *
		 * Returns RANGE_EQUAL if the ranges are equal within the tolerance, 
		 * i.e. they have the same rMin and rMax values in each dimension. 
		 * Returns RANGE_OTHER_CONTAINS if the range on which the method is 
		 * called is contained within the other range, and 
		 * RANGE_FIRST_CONTAINS if the other range is contained within the 
		 * range on which the method is called. Returns RANGE_OVERLAP if the 
		 * ranges overlap in some dimension. Returns RANGE_DISJOINT if the 
		 * ranges are disjoint.
		 *
		 * \param other Range.
		 * \param t Tolerance.
		 *
		 * \return Result of the comparison.
		 */
		virtual Ionflux::GeoUtils::RangeCompResult compare(const 
		Ionflux::GeoUtils::Range3& other, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
		
		/** Range check.
		 *
		 * Check whether the vector is contained in the range.
		 *
		 * \param v Vector.
		 * \param t Tolerance.
		 *
		 * \return \c true if the value is within the range, \c false otherwise.
		 */
		virtual bool isInRange(const Ionflux::GeoUtils::Vector3& v, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
		
		/** Intersect line.
		 *
		 * Calculate the intersection of the specified line with the bounding 
		 * plane pair of the range along the specified axis. The result is 
		 * stored in \c result.
		 *
		 * \param line Line.
		 * \param axis Axis.
		 * \param result Intersection result.
		 * \param t Tolerance.
		 *
		 * \return \c true if the line intersects the plane pair, \c false 
		 * otherwise.
		 */
		virtual bool intersect(const Ionflux::GeoUtils::Line3& line, 
		Ionflux::GeoUtils::AxisID axis, 
		Ionflux::GeoUtils::AAPlanePairIntersection& result, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
		
		/** Intersect line.
		 *
		 * Calculate the intersection of the specified line with the the 
		 * range. The result is stored in \c result.
		 *
		 * \param line Line.
		 * \param result Intersection result.
		 * \param t Tolerance.
		 *
		 * \return \c true if the line intersects the plane pair, \c false 
		 * otherwise.
		 */
		virtual bool intersect(const Ionflux::GeoUtils::Line3& line, 
		Ionflux::GeoUtils::AAPlanePairIntersection& result, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
		
		/** Get axis order.
		 *
		 * Get the order of the axes of the range. The longest axis will be 
		 * the first in the triple, followed by the next longest axis and the 
		 * smallest axis.
		 *
		 * \return Triple containing the axes ordered from longest to shortest.
		 */
		virtual Ionflux::GeoUtils::AxisTriple getAxisOrder() const;
		
		/** Get mesh.
		 *
		 * Get a mesh corresponding to the range. The new mesh will not be 
		 * referenced and must be managed by the caller.
		 *
		 * \return mesh.
		 */
		virtual Ionflux::GeoUtils::Mesh* getMesh() const;
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Range.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Range3& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Range.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Range3& other) const;
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
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
		virtual Ionflux::GeoUtils::Range3& operator=(const 
		Ionflux::GeoUtils::Range3& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Range3* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Range3* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Range3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Range3 object.
		 *
		 * \param initCenter Center vector.
		 * \param initRadius Radius vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Range3* create(const 
		Ionflux::GeoUtils::Vector3& initCenter, const Ionflux::GeoUtils::Vector3*
		initRadius = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Range3 object.
		 *
		 * \param initX Range (x).
		 * \param initY Range (y).
		 * \param initZ Range (z).
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Range3* create(const Ionflux::GeoUtils::Range& 
		initX, const Ionflux::GeoUtils::Range& initY, const 
		Ionflux::GeoUtils::Range& initZ, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Range3 object.
		 *
		 * \param rx Range (x).
		 * \param ry Range (y).
		 * \param rz Range (z).
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Range3* create(const 
		Ionflux::GeoUtils::Vector2& rx, const Ionflux::GeoUtils::Vector2& ry, 
		const Ionflux::GeoUtils::Vector2& rz, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Range3 object.
		 *
		 * \param xMin Minimum value (X).
		 * \param xMax Maximum value (X).
		 * \param yMin Minimum value (Y).
		 * \param yMax Maximum value (Y).
		 * \param zMin Minimum value (Z).
		 * \param zMax Maximum value (Z).
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Range3* create(double xMin, double xMax, double
		yMin, double yMax, double zMin, double zMax, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Range3 object.
		 *
		 * \param initMin Minimum vector.
		 * \param edgeLength Edge length.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Range3* create(const 
		Ionflux::GeoUtils::Vector3& initMin, double edgeLength, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
		virtual void loadFromXMLFile(const std::string& fileName);
        
        /** Get XML object factory
		 *
		 * Get the XML object factory singleton for the class.
		 * 
		 * return XML object factory
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		
		/** Get range (x).
		 *
		 * \return Current value of range (x).
		 */
		virtual Ionflux::GeoUtils::Range getX() const;
		
		/** Set range (x).
		 *
		 * Set new value of range (x).
		 *
		 * \param newX New value of range (x).
		 */
		virtual void setX(const Ionflux::GeoUtils::Range& newX);
		
		/** Get range (y).
		 *
		 * \return Current value of range (y).
		 */
		virtual Ionflux::GeoUtils::Range getY() const;
		
		/** Set range (y).
		 *
		 * Set new value of range (y).
		 *
		 * \param newY New value of range (y).
		 */
		virtual void setY(const Ionflux::GeoUtils::Range& newY);
		
		/** Get range (z).
		 *
		 * \return Current value of range (z).
		 */
		virtual Ionflux::GeoUtils::Range getZ() const;
		
		/** Set range (z).
		 *
		 * Set new value of range (z).
		 *
		 * \param newZ New value of range (z).
		 */
		virtual void setZ(const Ionflux::GeoUtils::Range& newZ);
};

}

}

/** \file Range3.hpp
 * \brief Range of values (3D) (header).
 */
#endif
