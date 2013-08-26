#ifndef IONFLUX_GEOUTILS_BOXBOUNDSITEM
#define IONFLUX_GEOUTILS_BOXBOUNDSITEM
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BoxBoundsItem.hpp               Item with box bounds (header).
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

#include <set>
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Range.hpp"
#include "geoutils/Vector3.hpp"
#include "geoutils/Vertex3.hpp"
#include "geoutils/Polygon3.hpp"
#include "geoutils/Range3.hpp"
#include "geoutils/Plane3.hpp"
#include "geoutils/Sphere3.hpp"
#include "geoutils/Line3.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class BoxBoundsItem;

/// Class information for class BoxBoundsItem.
class BoxBoundsItemClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		BoxBoundsItemClassInfo();
		/// Destructor.
		virtual ~BoxBoundsItemClassInfo();
};

/** Item with box bounds.
 * \ingroup geoutils
 *
 * This class already supplies much of the bounding box functionality, but 
 * does not deal with other items that may be contained inside the bounding
 * box.
 */
class BoxBoundsItem
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Center vector.
		Ionflux::GeoUtils::Vector3 center;
		/// Radius vector.
		Ionflux::GeoUtils::Vector3 rVec;
		/// Item ID.
		std::string itemID;
		/// Bounds.
		Ionflux::GeoUtils::Range3 bounds;
		/// Radius.
		double radius;
		/// Vertex vector.
		std::vector<Ionflux::GeoUtils::Vertex3*> bVerts;
		/// Face vector.
		std::vector<Ionflux::GeoUtils::Polygon3*> bFaces;
		
	public:
		/// Class information instance.
		static const BoxBoundsItemClassInfo boxBoundsItemClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new BoxBoundsItem object.
		 */
		BoxBoundsItem();
		
		/** Constructor.
		 *
		 * Construct new BoxBoundsItem object.
		 *
		 * \param other Other object.
		 */
		BoxBoundsItem(const Ionflux::GeoUtils::BoxBoundsItem& other);
		
		/** Constructor.
		 *
		 * Construct new BoxBoundsItem object.
		 *
		 * \param initCenter Center vector.
		 * \param initRVec Radius vector.
		 * \param initItemID Item ID.
		 */
		BoxBoundsItem(const Ionflux::GeoUtils::Vector3& initCenter, const 
		Ionflux::GeoUtils::Vector3& initRVec = Ionflux::GeoUtils::Vector3::ZERO, 
		const std::string& initItemID = "");
		
		/** Destructor.
		 *
		 * Destruct BoxBoundsItem object.
		 */
		virtual ~BoxBoundsItem();
		
		/** Update bounds.
		 *
		 * After changes to the radius vector and center, this method should 
		 * be called to update the bounds of the object. This will also update
		 * the scalar radius value.
		 */
		virtual void updateBounds();
		
		/** Update radius and center.
		 *
		 * After changes to the bounds of the object, this method should be 
		 * called to update the radius and center of the object.
		 */
		virtual void updateRadiusAndCenter();
		
		/** Clear item.
		 *
		 * Clears the bounds data of the item.
		 */
		virtual void clear();
		
		/** Get vertices.
		 *
		 * Get the vertices of the bounding box in the global coordinate 
		 * system. Returns a list of vertices.
		 *
		 * \return Bounding box vertices..
		 */
		virtual Ionflux::GeoUtils::Vertex3Vector getBoxVertices();
		
		/** Get faces.
		 *
		 * Get the faces of the bounding box in the global coordinate system. 
		 * Returns a list of polygons.
		 *
		 * \return Bounding box faces..
		 */
		virtual Ionflux::GeoUtils::Polygon3Vector getBoxFaces();
		
		/** Check position relative to plane.
		 *
		 * Check the bounding box position relative to a plane. Returns 1 if 
		 * the bounding box is above the plane (in direction of the normal of 
		 * the plane), 0 if the box intersects the plane, and -1 if the 
		 * bounding box is below the plane.
		 *
		 * \param plane Plane.
		 * \param t Tolerance.
		 *
		 * \return Result of the test.
		 */
		virtual int checkPlane(const Ionflux::GeoUtils::Plane3& plane, double t =
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Check position relative to plane.
		 *
		 * Check the object position relative to a plane. Unlike checkPlane(),
		 * this function considers the inner structure of the object, not just
		 * its bounding box. This should be used by derived classes to provide
		 * more accurate information about plane intersection. Returns 1 if 
		 * the object is above the plane (in direction of the normal of the 
		 * plane), 0 if the object intersects the plane, and -1 if the object 
		 * is below the plane.
		 *
		 * \param plane Plane.
		 * \param t Tolerance.
		 *
		 * \return Result of the test.
		 */
		virtual int checkPlaneInner(const Ionflux::GeoUtils::Plane3& plane, 
		double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Check position relative to sphere.
		 *
		 * Check the bounding box position relative to a sphere. Returns 1 if 
		 * the bounding box is inside the sphere, 0 if the box intersects the 
		 * sphere, and -1 if the bounding box is outside the sphere.
		 *
		 * \param sphere Sphere.
		 * \param t Tolerance.
		 *
		 * \return Result of the test.
		 */
		virtual int checkSphere(const Ionflux::GeoUtils::Sphere3& sphere, double 
		t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Check position relative to sphere.
		 *
		 * Check the object position relative to a sphere. Unlike 
		 * checkSphere(), this function considers the inner structure of the 
		 * object, not just its bounding box. This should be used by derived 
		 * classes to provide more accurate information about sphere 
		 * intersection. Returns 1 if the object is inside the sphere, 0 if 
		 * the object intersects the sphere, and -1 if the object is outside 
		 * the sphere.
		 *
		 * \param sphere Sphere.
		 * \param t Tolerance.
		 *
		 * \return Result of the test.
		 */
		virtual int checkSphereInner(const Ionflux::GeoUtils::Sphere3& sphere, 
		double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Check line intersection.
		 *
		 * Check whether the specified line intersects the bounding box. 
		 * Returns \c true if the line intersects the bounding box, \c false 
		 * otherwise.
		 *
		 * \param line Line.
		 * \param t Tolerance.
		 *
		 * \return Result of the test.
		 */
		virtual bool checkLine(const Ionflux::GeoUtils::Line3& line, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Check line intersection.
		 *
		 * Check whether the specified line intersects the object. Unlike 
		 * checkLine(), this function considers the inner structure of the 
		 * object, not just its bounding box. This should be used by derived 
		 * classes to provide more accurate information about line 
		 * intersection. Returns \c true if the line intersects the object, \c
		 * false otherwise.
		 *
		 * \param line Line.
		 * \param t Tolerance.
		 *
		 * \return Result of the test.
		 */
		virtual bool checkLineInner(const Ionflux::GeoUtils::Line3& line, double 
		t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Compare ranges (per axis).
		 *
		 * Compares the ranges on each axis separately. See Range3::compare() 
		 * for details on the return values.
		 *
		 * \param other Box bounds item.
		 * \param t Tolerance.
		 *
		 * \return Result of the comparison.
		 */
		virtual Ionflux::GeoUtils::RangeCompResult3 compare3(const 
		Ionflux::GeoUtils::BoxBoundsItem& other, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
		
		/** Compare bounding boxes..
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
		 * \param other Box bounds item.
		 * \param t Tolerance.
		 *
		 * \return Result of the comparison.
		 */
		virtual Ionflux::GeoUtils::RangeCompResult compare(const 
		Ionflux::GeoUtils::BoxBoundsItem& other, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE) const;
		
		/** Check box intersection..
		 *
		 * Check whether the specified box intersects the bounding box. 
		 * Returns 1 if the bounding box is inside the other box, 0 if the 
		 * bounding box intersects the other box, and -1 if the bounding box 
		 * is outside the other box.
		 *
		 * \param other Box bounds item.
		 * \param t Tolerance.
		 *
		 * \return Result of the comparison.
		 */
		virtual int checkBox(const Ionflux::GeoUtils::BoxBoundsItem& other, 
		double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Check box intersection..
		 *
		 * Check whether the specified box intersects the object. Unlike 
		 * checkBox(), this function considers the inner structure of the 
		 * object, not just its bounding box. Returns 1 if the object is 
		 * inside the other box, 0 if the object intersects the other box, and
		 * -1 if the object is outside the other box.
		 *
		 * \param other Box bounds item.
		 * \param t Tolerance.
		 *
		 * \return Result of the comparison.
		 */
		virtual int checkBoxInner(const Ionflux::GeoUtils::BoxBoundsItem& other, 
		double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Check ray intersection.
		 *
		 * Check whether the specified ray intersects the bounding box. 
		 * Returns \c true if the ray intersects the bounding box, \c false 
		 * otherwise. The ray is specified as a line, where the ray is 
		 * supposed to start at point \c P and have direction \c U.
		 *
		 * \param ray Ray.
		 * \param t Tolerance.
		 *
		 * \return Result of the test.
		 */
		virtual bool checkRay(const Ionflux::GeoUtils::Line3& ray, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Check ray intersection.
		 *
		 * Check whether the specified ray intersects the object. Unlike 
		 * checkRay(), this function considers the inner structure of the 
		 * object, not just its bounding box. This should be used by derived 
		 * classes to provide more accurate information about line 
		 * intersection. Returns \c true if the ray intersects the object, \c 
		 * false otherwise. The ray is specified as a line, where the ray is 
		 * supposed to start at point \c P and have direction \c U.
		 *
		 * \param ray Ray.
		 * \param t Tolerance.
		 *
		 * \return Result of the test.
		 */
		virtual bool checkRayInner(const Ionflux::GeoUtils::Line3& ray, double t 
		= Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Box bounds item.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::BoxBoundsItem& other) 
		const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Box bounds item.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::BoxBoundsItem& other) 
		const;
		
		/** Get XML representation.
		 *
		 * Get an XML representation of the object.
		 *
		 * \return XML representation.
		 */
		virtual std::string getXML() const;
		
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
		virtual Ionflux::GeoUtils::BoxBoundsItem& operator=(const 
		Ionflux::GeoUtils::BoxBoundsItem& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::BoxBoundsItem* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::BoxBoundsItem* 
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
		static Ionflux::GeoUtils::BoxBoundsItem* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get center vector.
		 *
		 * \return Current value of center vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getCenter() const;
		
		/** Set center vector.
		 *
		 * Set new value of center vector.
		 *
		 * \param newCenter New value of center vector.
		 */
		virtual void setCenter(const Ionflux::GeoUtils::Vector3& newCenter);
		
		/** Get radius vector.
		 *
		 * \return Current value of radius vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getRVec() const;
		
		/** Set radius vector.
		 *
		 * Set new value of radius vector.
		 *
		 * \param newRVec New value of radius vector.
		 */
		virtual void setRVec(const Ionflux::GeoUtils::Vector3& newRVec);
		
		/** Get item ID.
		 *
		 * \return Current value of item ID.
		 */
		virtual std::string getItemID() const;
		
		/** Set item ID.
		 *
		 * Set new value of item ID.
		 *
		 * \param newItemID New value of item ID.
		 */
		virtual void setItemID(const std::string& newItemID);
		
		/** Get bounds.
		 *
		 * \return Current value of bounds.
		 */
		virtual Ionflux::GeoUtils::Range3 getBounds() const;
		
		/** Set bounds.
		 *
		 * Set new value of bounds.
		 *
		 * \param newBounds New value of bounds.
		 */
		virtual void setBounds(const Ionflux::GeoUtils::Range3& newBounds);
		
		/** Get radius.
		 *
		 * \return Current value of radius.
		 */
		virtual double getRadius() const;
		
		/** Set radius.
		 *
		 * Set new value of radius.
		 *
		 * \param newRadius New value of radius.
		 */
		virtual void setRadius(double newRadius);
		
		/** Get number of boxVertices.
		 *
		 * \return Number of boxVertices.
		 */
		virtual unsigned int getNumBoxVertices() const;
		
		/** Get boxVertex.
		 *
		 * Get the boxVertex at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return BoxVertex at specified index.
		 */
		virtual Ionflux::GeoUtils::Vertex3* getBoxVertex(unsigned int 
		elementIndex = 0) const;
		
		/** Find boxVertex.
		 *
		 * Find the specified occurence of a boxVertex.
		 *
		 * \param needle BoxVertex to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the boxVertex, or -1 if the boxVertex cannot be 
		 * found.
		 */
		virtual int findBoxVertex(Ionflux::GeoUtils::Vertex3* needle, unsigned 
		int occurence = 1) const;
		
		/** Add boxVertex.
		 *
		 * Add a boxVertex.
		 *
		 * \param addElement BoxVertex to be added.
		 */
		virtual void addBoxVertex(Ionflux::GeoUtils::Vertex3* addElement);
		
		/** Remove boxVertex.
		 *
		 * Remove a boxVertex.
		 *
		 * \param removeElement BoxVertex to be removed.
		 */
		virtual void removeBoxVertex(Ionflux::GeoUtils::Vertex3* removeElement);
		
		/** Remove boxVertex.
		 *
		 * Remove a boxVertex.
		 *
		 * \param removeIndex BoxVertex to be removed.
		 */
		virtual void removeBoxVertexIndex(unsigned int removeIndex);
		
		/** Clear boxVertices.
		 *
		 * Clear all boxVertices.
		 */
		virtual void clearBoxVertices();
		
		/** Get number of boxFaces.
		 *
		 * \return Number of boxFaces.
		 */
		virtual unsigned int getNumBoxFaces() const;
		
		/** Get boxFace.
		 *
		 * Get the boxFace at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return BoxFace at specified index.
		 */
		virtual Ionflux::GeoUtils::Polygon3* getBoxFace(unsigned int elementIndex
		= 0) const;
		
		/** Find boxFace.
		 *
		 * Find the specified occurence of a boxFace.
		 *
		 * \param needle BoxFace to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the boxFace, or -1 if the boxFace cannot be found.
		 */
		virtual int findBoxFace(Ionflux::GeoUtils::Polygon3* needle, unsigned int
		occurence = 1) const;
		
		/** Add boxFace.
		 *
		 * Add a boxFace.
		 *
		 * \param addElement BoxFace to be added.
		 */
		virtual void addBoxFace(Ionflux::GeoUtils::Polygon3* addElement);
		
		/** Remove boxFace.
		 *
		 * Remove a boxFace.
		 *
		 * \param removeElement BoxFace to be removed.
		 */
		virtual void removeBoxFace(Ionflux::GeoUtils::Polygon3* removeElement);
		
		/** Remove boxFace.
		 *
		 * Remove a boxFace.
		 *
		 * \param removeIndex BoxFace to be removed.
		 */
		virtual void removeBoxFaceIndex(unsigned int removeIndex);
		
		/** Clear boxFaces.
		 *
		 * Clear all boxFaces.
		 */
		virtual void clearBoxFaces();
};

}

}

/** \file BoxBoundsItem.hpp
 * \brief Item with box bounds (header).
 */
#endif
