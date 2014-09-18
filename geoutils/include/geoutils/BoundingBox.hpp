#ifndef IONFLUX_GEOUTILS_BOUNDINGBOX
#define IONFLUX_GEOUTILS_BOUNDINGBOX
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BoundingBox.hpp                 Bounding box (header).
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
#include "geoutils/Split.hpp"
#include "geoutils/SplitSet.hpp"
#include "geoutils/ItemSource.hpp"
#include "geoutils/BoxBoundsItem.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class BoundingBox.
class BoundingBoxClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		BoundingBoxClassInfo();
		/// Destructor.
		virtual ~BoundingBoxClassInfo();
};

/** Bounding Box.
 * \ingroup geoutils
 *
 * A bounding box which can contain other BoxBoundsItems.
 */
class BoundingBox
: virtual public Ionflux::GeoUtils::BoxBoundsItem
{
	private:
		
	protected:
		/// Items.
		Ionflux::GeoUtils::BoxBoundsItemSet items;
		/// Level.
		int level;
		/// Parent.
		Ionflux::GeoUtils::BoundingBox* parent;
		
	public:
		/// Class information instance.
		static const BoundingBoxClassInfo boundingBoxClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new BoundingBox object.
		 */
		BoundingBox();
		
		/** Constructor.
		 *
		 * Construct new BoundingBox object.
		 *
		 * \param other Other object.
		 */
		BoundingBox(const Ionflux::GeoUtils::BoundingBox& other);
		
		/** Constructor.
		 *
		 * Construct new BoundingBox object.
		 *
		 * \param initCenter Center vector.
		 * \param initRVec Radius vector.
		 * \param initItemID Item ID.
		 * \param initLevel Level.
		 * \param initItems Items.
		 * \param initParent Parent.
		 */
		BoundingBox(const Ionflux::GeoUtils::Vector3& initCenter, const 
		Ionflux::GeoUtils::Vector3& initRVec = Ionflux::GeoUtils::Vector3::ZERO, 
		const std::string& initItemID = "", int initLevel = 0, const 
		Ionflux::GeoUtils::BoxBoundsItemSet* initItems = 0, 
		Ionflux::GeoUtils::BoundingBox* initParent = 0);
		
		/** Destructor.
		 *
		 * Destruct BoundingBox object.
		 */
		virtual ~BoundingBox();
		
		/** Update.
		 *
		 * Update all state according to the items contained in the bounding 
		 * box. If the bounding box has a parent, the parent will also be 
		 * updated to reflect the changes.
		 */
		virtual void update();
		
		/** Clear.
		 *
		 * Removes all items and resets state.
		 */
		virtual void clear();
		
		/** Add an item to the bounding box.
		 *
		 * The dimensions of the bounding box will be updated to reflect the 
		 * new bounds. If maxRadius is specified, the item will not be added 
		 * if adding the item would make the radius of the bounding box larger
		 * than maxRadius.
		 *
		 * \param item Box bounds item.
		 * \param maxRadius Maximum radius.
		 *
		 * \return \c true if the item has been added, \c false otherwise.
		 */
		virtual bool addItem(Ionflux::GeoUtils::BoxBoundsItem* item, double 
		maxRadius = 0.);
		
		/** Remove an item from the bounding box.
		 *
		 * Remove an item from the bounding box.
		 *
		 * \param item Box bounds item.
		 * \param update0 Update state according to changed elements.
		 *
		 * \return \c true if the item has been removed, \c false if the item is 
		 * not contained in the bounding box.
		 */
		virtual bool removeItem(Ionflux::GeoUtils::BoxBoundsItem* item, bool 
		update0 = true);
		
		/** Add items to the bounding box.
		 *
		 * Add items from the specified set to the bounding box. If maxItems 
		 * is specified, items will not be added if the number of items in the
		 * bounding box would exceed maxItems. If maxRadius is specified, 
		 * items will not be added if the radius of the bounding box would 
		 * exceed maxRadius.
		 *
		 * \param newItems Set of box bounds items.
		 * \param maxItems Maximum number of items.
		 * \param maxRadius Maximum radius.
		 *
		 * \return Set of items that have not been added.
		 */
		virtual Ionflux::GeoUtils::BoxBoundsItemSet addItems(const 
		Ionflux::GeoUtils::BoxBoundsItemSet& newItems, unsigned int maxItems = 0,
		double maxRadius = 0.);
		
		/** Add items to the bounding box.
		 *
		 * Add items from the specified set to the bounding box. This method 
		 * removes the items which are added to the bounding box from the 
		 * source set. If maxItems is specified, items will not be added if 
		 * the number of items in the bounding box would exceed maxItems. If 
		 * maxRadius is specified, items will not be added if the radius of 
		 * the bounding box would exceed maxRadius.
		 *
		 * \param newItems Set of box bounds items.
		 * \param maxItems Maximum number of items.
		 * \param maxRadius Maximum radius.
		 *
		 * \return Number of items that have been added.
		 */
		virtual unsigned int takeItems(Ionflux::GeoUtils::BoxBoundsItemSet& 
		newItems, unsigned int maxItems = 0., double maxRadius = 0.);
		
		/** Test bounding box split.
		 *
		 * Split the bounding box along the specified axis, but do not change 
		 * the actual structure of the bounding box contents. The split 
		 * parameter s is used to determine the position where the split 
		 * should occur. If s is 0.5, the split occurs at the center of the 
		 * axis. If 0 < s < 0.5, the split occurs in the lower coordinate half
		 * of the axis. If 0.5 > s > 0, the split occurs in the upper 
		 * coordinate half of the axis.
		 *
		 * \param split Split.
		 * \param t Tolerance.
		 *
		 * \return Test result.
		 */
		virtual Ionflux::GeoUtils::SplitTestResult splitTest(const 
		Ionflux::GeoUtils::Split& split, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Update best split.
		 *
		 * Compare the quality parameters of a split to the quality parameters
		 * of the best split as specified. If the split is better than the 
		 * best split, replace the best split with the specified split.
		 *
		 * \param s Split quality parameters.
		 * \param best Best split quality parameters.
		 */
		virtual void updateBestSplit(const Ionflux::GeoUtils::SplitParams& s, 
		Ionflux::GeoUtils::SplitParams& best);
		
		/** Determine best split.
		 *
		 * Tests all of the specified splits and returns the one where the 
		 * difference between item counts in both sets is minimal. Returns 0 
		 * if none of the splits results in two sets with at least minItems 
		 * items per set.
		 *
		 * \param splits Splits.
		 * \param minItems Minimum number of items per set.
		 * \param t Tolerance.
		 * \param preferLongestAxis Prefer split along longest axis..
		 * \param longestAxisTolerance Tolerance for preferring the longest 
		 * axis..
		 *
		 * \return Best split, or 0 if none of the splits is suitable.
		 */
		virtual Ionflux::GeoUtils::Split* 
		getBestSplit(Ionflux::GeoUtils::SplitSet& splits, unsigned int minItems =
		0, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE, bool 
		preferLongestAxis = false, double longestAxisTolerance = 0.1);
		
		/** Split bounding box.
		 *
		 * Split the bounding box along the specified axis. If the set of 
		 * splits contains multiple splits, the best split will be determined 
		 * and used. The split parameter s is used to determine the position 
		 * where the split should occur. If s is 0.5, the split occurs at the 
		 * center of the axis. If 0 < s < 0.5, the split occurs in the lower 
		 * coordinate half of the axis. If 0.5 > s > 0, the split occurs in 
		 * the upper coordinate half of the axis. If recursive is set to \c 
		 * true, the contained boxes will be split recursively until the split
		 * boxes contain either less than minItems items or maxLevel is 
		 * reached. If the split is successful, the split result contains two 
		 * bounding boxes, which are the new items contained in the bounding 
		 * box. The success flag of the split result will be set to \c false 
		 * if the box cannot be split because it does not contain any items, 
		 * or if one of the recursion limits is reached.
		 *
		 * \param splits Splits.
		 * \param recursive Split box hierarchy recursively.
		 * \param minItems Minimum number of items per set.
		 * \param maxLevel Maximum split depth.
		 * \param splitLevel Current split level.
		 * \param t Tolerance.
		 * \param preferLongestAxis Prefer split along longest axis..
		 * \param longestAxisTolerance Tolerance for preferring the longest 
		 * axis..
		 *
		 * \return Split result.
		 */
		virtual Ionflux::GeoUtils::SplitResult split(Ionflux::GeoUtils::SplitSet&
		splits, bool recursive = false, unsigned int minItems = 0, unsigned int 
		maxLevel = 0, unsigned int splitLevel = 0, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE, bool preferLongestAxis = false, 
		double longestAxisTolerance = 0.1);
		
		/** Get items above plane.
		 *
		 * Get the items which are above the specified plane (in direction of 
		 * the normal of the plane).
		 *
		 * \param plane Plane.
		 * \param t Tolerance.
		 *
		 * \return Set of items which are above the plane.
		 */
		virtual Ionflux::GeoUtils::BoxBoundsItemSet 
		getItemsAbovePlane(Ionflux::GeoUtils::Plane3& plane, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Get items which intersect line.
		 *
		 * Get the leaf items from the bounding box hierarchy which may be 
		 * intersected by the specified line. Returns a set of leaf items. For
		 * leaf items which do not have a checkLine method, it is up to the 
		 * caller to determine if there are actual intersections.
		 *
		 * \param line Line.
		 * \param t Tolerance.
		 *
		 * \return Set of items which are intersected by the line.
		 */
		virtual Ionflux::GeoUtils::BoxBoundsItemSet 
		getItemsOnLine(Ionflux::GeoUtils::Line3& line, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Get items which intersect ray.
		 *
		 * Get the leaf items from the bounding box hierarchy which may be 
		 * intersected by the specified ray. Returns a set of leaf items. For 
		 * leaf items which do not have a checkRay method, it is up to the 
		 * caller to determine if there are actual intersections. The ray is 
		 * specified as a line, where the ray is supposed to start at point \c
		 * P and have direction \c U.
		 *
		 * \param ray Ray.
		 * \param t Tolerance.
		 *
		 * \return Set of items which are intersected by the ray.
		 */
		virtual Ionflux::GeoUtils::BoxBoundsItemSet 
		getItemsOnRay(Ionflux::GeoUtils::Line3& ray, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Get items in sphere.
		 *
		 * Get the items which are inside the specified sphere.
		 *
		 * \param sphere Sphere.
		 * \param t Tolerance.
		 *
		 * \return Set of items which are inside the sphere.
		 */
		virtual Ionflux::GeoUtils::BoxBoundsItemSet 
		getItemsInSphere(Ionflux::GeoUtils::Sphere3& sphere, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Get items in box.
		 *
		 * Get the items which are inside the specified bounding box (which 
		 * can be simply a BoxBoundsItem). If a leaf item intersects the box, 
		 * it is also added to the result.
		 *
		 * \param box Box.
		 * \param t Tolerance.
		 *
		 * \return Set of items which are inside the box.
		 */
		virtual Ionflux::GeoUtils::BoxBoundsItemSet 
		getItemsInBox(Ionflux::GeoUtils::BoxBoundsItem& box, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Get containing leaf.
		 *
		 * Return the leaf item that contains the specified item, or 0 if none
		 * of the leaf items contains that item.
		 *
		 * \param item Item to search for.
		 * \param t Tolerance.
		 *
		 * \return Check result.
		 */
		virtual Ionflux::GeoUtils::BoxBoundsItem* 
		getContainingLeaf(Ionflux::GeoUtils::BoxBoundsItem* item, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Initialize hierarchy from source.
		 *
		 * Initialize the bounding box hierarchy from the specified source. 
		 * This walks through the hierarchy recursively and replaces 
		 * BoxBoundsItems with whatever is returned from calling the getItem 
		 * method on the source with the item ID of the BoxBoundsItem as an 
		 * argument.
		 *
		 * \param source Item source.
		 */
		virtual void initFromSource(Ionflux::GeoUtils::ItemSource& source);
		
		/** Get bounding boxes.
		 *
		 * Get the bounding boxes from the hierarchy of which the bounding box
		 * is the root.
		 *
		 * \param target Where to store the bounding boxes..
		 */
		virtual void getBoundingBoxes(Ionflux::GeoUtils::BoundingBoxSet& target);
		
		/** Get leaves.
		 *
		 * Get the leaf items from the hierarchy of which the bounding box is 
		 * the root.
		 *
		 * \param target Where to store the bounding boxes..
		 */
		virtual void getLeaves(Ionflux::GeoUtils::BoxBoundsItemSet& target);
		
		/** Get item path.
		 *
		 * Get the path for a leaf item in the hierarchy. Adds a list of  
		 * bounding boxes to the target vector, from bottom to top, which 
		 * contain the specified item. If the bounding box hierarchy does not 
		 * contain the item, the function returns \c false and the target 
		 * vector is not changed.
		 *
		 * \param item Item for which to get the path..
		 * \param target Where to store the bounding boxes..
		 *
		 * \return \c true if the bounding box hierarchy contains the item, \c 
		 * false otherwise.
		 */
		virtual bool getItemPath(Ionflux::GeoUtils::BoxBoundsItem* item, 
		Ionflux::GeoUtils::BoundingBoxVector& target);
		
		/** Compare bounding box hierarchies.
		 *
		 * Check whether the bounding box hierarchies are equal, i.e. they 
		 * contain equal bounding boxes and the same leaf items in each node.
		 *
		 * \param other Bounding box hierarchy root..
		 * \param t Tolerance.
		 *
		 * \return \c true if the bounding box hierarchies are equal, \c false 
		 * otherwise.
		 */
		virtual bool compareHierarchy(Ionflux::GeoUtils::BoundingBox& other, 
		double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Validate.
		 *
		 * Recursively check that all items are contained within the bounds. 
		 * Raises an excetion if this is not the case.
		 *
		 * \param t Tolerance.
		 *
		 * \return \c true if the bounding box hierarchy contains the item, \c 
		 * false otherwise.
		 */
		virtual bool validate(double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Bounding box.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::BoundingBox& other) 
		const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Bounding box.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::BoundingBox& other) 
		const;
		
		/** Get number of items.
		 *
		 * Get the number of items contained in the bounding box.
		 *
		 * \return Number of items.
		 */
		virtual unsigned int getNumItems() const;
		
		/** Get items.
		 *
		 * Get the items contained in the bounding box.
		 *
		 * \param target Where to store the items.
		 */
		virtual void getItems(Ionflux::GeoUtils::BoxBoundsItemSet& target) const;
		
		/** Set child item IDs.
		 *
		 * Set item IDs for the child objects of the bounding box. The ID will
		 * be constructed out of the prefix, a number, and optionally the 
		 * level.
		 *
		 * \param prefix Prefix.
		 * \param showLevel Show level.
		 * \param keepExisting Keep existing IDs.
		 * \param recursive Recursively set item IDs.
		 * \param level Level.
		 * \param fieldWidth Number field width.
		 */
		virtual void setChildIDs(const std::string& prefix, bool showLevel = 
		true, bool keepExisting = true, bool recursive = false, unsigned int 
		level = 0, unsigned int fieldWidth = 2);
		
		/** Get XML representation.
		 *
		 * Get an XML representation of the object.
		 *
		 * \return XML representation.
		 */
		virtual std::string getXML_legacy() const;
		
		/** Write to file.
		 *
		 * Write mesh data to a (XML) file.
		 *
		 * \param fileName .
		 */
		virtual void writeToFile(const std::string& fileName) const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::BoundingBox& operator=(const 
		Ionflux::GeoUtils::BoundingBox& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::BoundingBox* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::BoundingBox* 
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
		static Ionflux::GeoUtils::BoundingBox* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get level.
		 *
		 * \return Current value of level.
		 */
		virtual int getLevel() const;
		
		/** Set level.
		 *
		 * Set new value of level.
		 *
		 * \param newLevel New value of level.
		 */
		virtual void setLevel(int newLevel);
		
		/** Get parent.
		 *
		 * \return Current value of parent.
		 */
		virtual Ionflux::GeoUtils::BoundingBox* getParent() const;
		
		/** Set parent.
		 *
		 * Set new value of parent.
		 *
		 * \param newParent New value of parent.
		 */
		virtual void setParent(Ionflux::GeoUtils::BoundingBox* newParent);
};

}

}

/** \file BoundingBox.hpp
 * \brief Bounding box (header).
 */
#endif
