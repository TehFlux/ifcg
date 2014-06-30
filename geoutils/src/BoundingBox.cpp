/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BoundingBox.cpp                 Bounding box (implementation).
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

#include "geoutils/BoundingBox.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace GeoUtils
{

BoundingBoxClassInfo::BoundingBoxClassInfo()
{
	name = "BoundingBox";
	desc = "Bounding box";
}

BoundingBoxClassInfo::~BoundingBoxClassInfo()
{
}

// run-time type information instance constants
const BoundingBoxClassInfo BoundingBox::boundingBoxClassInfo;
const Ionflux::ObjectBase::IFClassInfo* BoundingBox::CLASS_INFO = &BoundingBox::boundingBoxClassInfo;

BoundingBox::BoundingBox()
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, Ionflux::GeoUtils::Vector3::ZERO, ""), level(0), parent(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

BoundingBox::BoundingBox(const Ionflux::GeoUtils::BoundingBox& other)
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, Ionflux::GeoUtils::Vector3::ZERO, ""), level(0), parent(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

BoundingBox::BoundingBox(const Ionflux::GeoUtils::Vector3& initCenter, 
const Ionflux::GeoUtils::Vector3& initRVec, const std::string& initItemID, 
int initLevel, const Ionflux::GeoUtils::BoxBoundsItemSet* initItems, 
Ionflux::GeoUtils::BoundingBox* initParent)
: Ionflux::GeoUtils::BoxBoundsItem(Ionflux::GeoUtils::Vector3::ZERO, 
Ionflux::GeoUtils::Vector3::ZERO, ""), level(initLevel), parent(initParent)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initItems != 0)
	    addItems(*initItems);
	updateBounds();
}

BoundingBox::~BoundingBox()
{
	// TODO: Nothing ATM. ;-)
}

void BoundingBox::update()
{
	if (items.size() == 0) 
	    return;
	bool e0 = true;
	for (BoxBoundsItemSet::iterator i = items.begin(); 
	    i != items.end(); i++)
	{
	    BoxBoundsItem* it = *i;
	    if (e0)
	    {
	        bounds.setBounds(it->getCenter());
	        e0 = false;
	    }
	    bounds.extend(it->getCenter() + it->getRVec());
	    bounds.extend(it->getCenter() - it->getRVec());
	}
	updateRadiusAndCenter();
	if (parent != 0)
	    parent->update();
}

void BoundingBox::clear()
{
	for (BoxBoundsItemSet::iterator i = items.begin(); 
	    i != items.end(); i++)
	    removeLocalRef(*i);
	items.clear();
	BoxBoundsItem::clear();
}

bool BoundingBox::addItem(Ionflux::GeoUtils::BoxBoundsItem* item, double 
maxRadius)
{
	if (item == 0)
	    throw GeoUtilsError("Attempt to add null item!");
	if (items.size() == 0)
	    bounds = item->getBounds();
	if (maxRadius > 0)
	{
	    Range3 b = bounds;
	    b.extend(item->getCenter() + item->getRVec());
	    b.extend(item->getCenter() - item->getRVec());
	    if (b.getRadius().norm() > maxRadius)
	        return false;
	}
	bounds.extend(item->getCenter() + item->getRVec());
	bounds.extend(item->getCenter() - item->getRVec());
	addLocalRef(item);
	BoundingBox* b0 = dynamic_cast<BoundingBox*>(item);
	if (b0 != 0)
	{
	    if (b0->getParent() == 0)
	        b0->setParent(this);
	    else
	    {
	        ostringstream status;
	        status << "Bounding box " << b0->getString() 
	            << " is already a child of " << b0->getParent()->getString() 
	            << ", parent entry will be left unchanged.";
	        log(IFLogMessage(status.str(), VL_WARNING, this, "addItem"));
	    }
	}
	items.insert(item);
	updateRadiusAndCenter();
	return true;
}

bool BoundingBox::removeItem(Ionflux::GeoUtils::BoxBoundsItem* item, bool 
update0)
{
	if (item == 0)
	    throw GeoUtilsError("Attempt to remove null item!");
	BoxBoundsItemSet::iterator i = items.find(item);
	if (i == items.end())
	    return false;
	BoundingBox* b0 = dynamic_cast<BoundingBox*>(item);
	if ((b0 != 0) && (b0->getParent() == this))
	    b0->setParent(0);
	items.erase(i);
	removeLocalRef(*i);
	if (update0)
	    update();
	return true;
}

Ionflux::GeoUtils::BoxBoundsItemSet BoundingBox::addItems(const 
Ionflux::GeoUtils::BoxBoundsItemSet& newItems, unsigned int maxItems, 
double maxRadius)
{
	Ionflux::GeoUtils::BoxBoundsItemSet remaining;
	for (BoxBoundsItemSet::iterator i = newItems.begin(); 
	    i != newItems.end(); i++)
	{
	    BoxBoundsItem* it = *i;
	    // Check for maximum number of items.
	    if ((maxItems > 0) 
	        && (items.size() >= maxItems))
	        remaining.insert(it);
	    else 
	    if (!addItem(it, maxRadius))
	        remaining.insert(it);
	}
	return remaining;
}

unsigned int BoundingBox::takeItems(Ionflux::GeoUtils::BoxBoundsItemSet& 
newItems, unsigned int maxItems, double maxRadius)
{
	unsigned int numTaken = 0;
	BoxBoundsItemSet putBack;
	bool finished = false;
	while ((newItems.size() > 0) 
	    && !finished)
	{
	    // Check for maximum number of items.
	    if ((maxItems > 0) 
	        && (items.size() >= maxItems)) 
	        finished = true;
	    else 
	    {
	        BoxBoundsItemSet::iterator i = newItems.begin();
	        BoxBoundsItem* it = *i;
	        newItems.erase(i);
	        if (addItem(it, maxRadius))
	            numTaken++;
	        else 
	            putBack.insert(it);
	    }
	}
	newItems.insert(putBack.begin(), putBack.end());
	return numTaken;
}

Ionflux::GeoUtils::SplitTestResult BoundingBox::splitTest(const 
Ionflux::GeoUtils::Split& split, double t)
{
	Ionflux::GeoUtils::SplitTestResult result;
	Range b = bounds.getAxisRange(split.getAxis());
	double sc = b.getValue(split.getS());
	for (BoxBoundsItemSet::iterator i = items.begin(); 
	    i != items.end(); i++)
	{
	    BoxBoundsItem* it = *i;
	    if (ltOrEq(it->getCenter()[split.getAxis()], sc, t))
	        result.items0.insert(it);
	    else 
	        result.items1.insert(it);
	}
	return result;
}

void BoundingBox::updateBestSplit(const Ionflux::GeoUtils::SplitParams& s, 
Ionflux::GeoUtils::SplitParams& best)
{
	/* <---- DEBUG ----- //
	ostringstream status;
	// ----- DEBUG ----> */
	if (best.split == 0) 
	{
	    best.split = s.split;
	    best.d = s.d;
	    best.r = s.r;
	}
	else 
	{
	    if (s.d < best.d)
	    {
	        best.split = s.split;
	        best.d = s.d;
	        best.r = s.r;
	    } else 
	    if (s.d == best.d)
	    {
	        // Take the split that is more balanced.
	        unsigned int d0 = ::abs(best.split->getS() - 0.5);
	        unsigned int d1 = ::abs(s.split->getS() - 0.5);
	        /* <---- DEBUG ----- //
	        status.str("");
	        status << "Testing balance for " << *(s.split) 
	            << ": (" << d0 << ", " << d1 << ") " << s.d;
	        log(IFLogMessage(status.str(), VL_DEBUG, this, 
	            "updateBestSplit"));
	        // ----- DEBUG ----> */
	        if (d1 < d0)
	        {
	            best.split = s.split;
	            best.d = s.d;
	            best.r = s.r;
	        }
	    }
	}
}

Ionflux::GeoUtils::Split* 
BoundingBox::getBestSplit(Ionflux::GeoUtils::SplitSet& splits, unsigned int
minItems, double t, bool preferLongestAxis, double longestAxisTolerance)
{
	SplitParams best;
	SplitParams prefAxisBest;
	best.split = 0;
	best.d = 0;
	best.r = 0;
	prefAxisBest.split = 0;
	prefAxisBest.d = 0;
	prefAxisBest.r = 0;
	AxisID prefAxis = bounds.getAxisOrder().a0;
	/* <---- DEBUG ----- //
	ostringstream status;
	// ----- DEBUG ----> */
	if (items.size() < (2 * minItems))
	{
	    /* <---- DEBUG ----- //
	    status.str("");
	    status << "Not enough items in box for splitting (n = " 
	        << items.size() << ", minItems = " << minItems << ").";
	    log(IFLogMessage(status.str(), VL_DEBUG, this, 
	        "getBestSplit"));
	    // ----- DEBUG ----> */
	    return 0;
	}
	for (unsigned int i = 0; i < splits.getNumSplits(); i++)
	{
	    Split* s = splits.getSplit(i);
	    SplitTestResult sr = splitTest(*s, t);
	    unsigned int n0 = sr.items0.size();
	    unsigned int n1 = sr.items1.size();
	    if ((n0 >= minItems) 
	        && (n1 >= minItems)) 
	    {
	        // Both sets have enough elements.
	        SplitParams sp0;
	        sp0.split = s;
	        sp0.d = ::abs(n0 - n1);
	        sp0.r = ::abs(1. - (static_cast<double>(n0) / n1));
	        /* <---- DEBUG ----- //
	        status.str("");
	        status << "Testing " << *s 
	            << ": (" << n0 << ", " << n1 << ") " << sp0.d;
	        log(IFLogMessage(status.str(), VL_DEBUG, this, 
	            "getBestSplit"));
	        // ----- DEBUG ----> */
	        updateBestSplit(sp0, best);
	        if (s->getAxis() == prefAxis)
	            // Update best split along preferred axis.
	            updateBestSplit(sp0, prefAxisBest);
	    } else 
	    {
	        /* <---- DEBUG ----- //
	        status.str("");
	        status << "Split " << s->getString() << ": (" << n0 << ", " 
	            << n1 << ") not usable (minItems = " << minItems << ").";
	        log(IFLogMessage(status.str(), VL_DEBUG, this, 
	            "getBestSplit"));
	        // ----- DEBUG ----> */
	    }
	}
	if (best.split != 0)
	{
	    /* <---- DEBUG ----- //
	    status.str("");
	    status << "Best split: (" << axisToString(best.split->getAxis()) 
	        << ") " << *(best.split) << " (r = " << best.r << ").";
	    log(IFLogMessage(status.str(), VL_DEBUG, this, "getBestSplit"));
	    // ----- DEBUG ----> */
	    if (prefAxisBest.split != 0)
	    {
	        /* <---- DEBUG ----- //
	        status.str("");
	        status << "Best split along preferred axis (" 
	            << axisToString(prefAxis) << "): " << *(prefAxisBest.split) 
	            << " (r = " << prefAxisBest.r << ").";
	        log(IFLogMessage(status.str(), VL_DEBUG, this, "getBestSplit"));
	        // ----- DEBUG ----> */
	        double r0 = 0.;
	        if (prefAxisBest.r != 0.)
	            r0 = ::abs(1. - best.r / prefAxisBest.r);
	        if (preferLongestAxis 
	            && (r0 <= longestAxisTolerance))
	        {
	            // Use the split along the preferred axis.
	            /* <---- DEBUG ----- //
	            status.str("");
	            status << "Using split along preferred axis (" 
	                << axisToString(prefAxis) << "): best.r = " << best.r 
	                << ", prefAxisBest.r = " << prefAxisBest.r << ", r0 = " 
	                << r0;
	            log(IFLogMessage(status.str(), VL_DEBUG, this, 
	                "getBestSplit"));
	            // ----- DEBUG ----> */
	            return prefAxisBest.split;
	        }
	    }
	    return best.split;
	}
	return 0;
}

Ionflux::GeoUtils::SplitResult 
BoundingBox::split(Ionflux::GeoUtils::SplitSet& splits, bool recursive, 
unsigned int minItems, unsigned int maxLevel, unsigned int splitLevel, 
double t, bool preferLongestAxis, double longestAxisTolerance)
{
	SplitResult result;
	// <---- DEBUG ----- //
	ostringstream status;
	// ----- DEBUG ----> */
	if (items.size() == 0)
	{
	    /* <---- DEBUG ----- //
	    status << "Nothing to split (level = " << splitLevel << ").";
	    log(IFLogMessage(status.str(), VL_DEBUG, this, "split"));
	    // ----- DEBUG ----> */
	    result.success = false;
	    return result;
	}
	if (recursive)
	{
	    // Check the abort conditions for recursive splitting.
	    if ((minItems > 0) 
	        && (items.size() <= minItems))
	    {
	        /* <---- DEBUG ----- //
	        status.str("");
	        status << "Not enough items for splitting (level = " 
	            << splitLevel << ").";
	        log(IFLogMessage(status.str(), VL_DEBUG, this, "split"));
	        // ----- DEBUG ----> */
	        result.success = false;
	        return result;
	    }
	    if ((maxLevel > 0) 
	        && (splitLevel >= maxLevel))
	    {
	        /* <---- DEBUG ----- //
	        status.str("");
	        status << "Maximum level reached (level = " 
	            << splitLevel << ").";
	        log(IFLogMessage(status.str(), VL_DEBUG, this, "split"));
	        // ----- DEBUG ----> */
	        result.success = false;
	        return result;
	    }
	}
	Split* split = 0;
	if (splits.getNumSplits() == 1)
	    split = splits.getSplit(0);
	else
	    split = getBestSplit(splits, minItems, t, preferLongestAxis, 
	        longestAxisTolerance);
	if (split == 0)
	{
	    // There is no split that does anything useful.
	    /* <---- DEBUG ----- //
	    status.str("");
	    status << "No suitable split (level = " 
	        << splitLevel << ").";
	    log(IFLogMessage(status.str(), VL_DEBUG, this, "split"));
	    // ----- DEBUG ----> */
	    result.success = false;
	    return result;
	}
	/* <---- DEBUG ----- //
	status.str("");
	status << "Splitting box with " << items.size() << " items using " 
	    << split->getString() << " (level = " << splitLevel << ").";
	log(IFLogMessage(status.str(), VL_DEBUG, this, "split"));
	// ----- DEBUG ----> */
	Range b = bounds.getAxisRange(split->getAxis());
	double sc = b.getValue(split->getS());
	result.boxes.b0 = new BoundingBox();
	if (result.boxes.b0 == 0)
	    throw GeoUtilsError("Could not allocate object.");
	result.boxes.b0->setLevel(splitLevel + 1);
	result.boxes.b1 = new BoundingBox();
	if (result.boxes.b1 == 0)
	    throw GeoUtilsError("Could not allocate object.");
	result.boxes.b1->setLevel(splitLevel + 1);
	for (BoxBoundsItemSet::iterator i = items.begin(); 
	    i != items.end(); i++)
	{
	    BoxBoundsItem* it = *i;
	    if (ltOrEq(it->getCenter()[split->getAxis()], sc, t))
	        result.boxes.b0->addItem(it);
	    else 
	        result.boxes.b1->addItem(it);
	}
	// <---- DEBUG ----- //
	BoundingBox* bx = 0;
	if (compare(*result.boxes.b0, t) != RANGE_FIRST_CONTAINS)
	    bx = result.boxes.b0;
	if (compare(*result.boxes.b1, t) != RANGE_FIRST_CONTAINS)
	    bx = result.boxes.b1;
	if (bx != 0)
	{
	    status.str("");
	    status << "Box not contained before splitting (" 
	        << rangeCompToString(compare(*bx, t)) << "): " << bx->getString() 
	        << " (" << getString() << "), [" 
	        << rangeCompToString3S(bounds.compare3(bx->getBounds())) << "].";
	    throw GeoUtilsError(status.str());
	}
	// ----- DEBUG ----> */
	if (recursive)
	{
	    // Split recursively.
	    result.boxes.b0->split(splits, recursive, minItems, maxLevel, 
	        splitLevel + 1, t, preferLongestAxis, longestAxisTolerance);
	    result.boxes.b1->split(splits, recursive, minItems, maxLevel, 
	        splitLevel + 1, t, preferLongestAxis, longestAxisTolerance);
	}
	// <---- DEBUG ----- //
	bx = 0;
	if (compare(*result.boxes.b0, t) != RANGE_FIRST_CONTAINS)
	    bx = result.boxes.b0;
	if (compare(*result.boxes.b1, t) != RANGE_FIRST_CONTAINS)
	    bx = result.boxes.b1;
	if (bx != 0)
	{
	    status.str("");
	    status << "Box not contained after splitting (" 
	        << compare(*bx, t) << "): " << bx->getString() << " (" 
	        << getString() << "), [" 
	        << rangeCompToString3S(bounds.compare3(bx->getBounds())) 
	        << "].";
	    throw GeoUtilsError(status.str());
	}
	// ----- DEBUG ----> */
	// Add the new boxes.
	clear();
	/* <---- DEBUG ----- //
	status.str("");
	status << "Adding box with " 
	    << result.boxes.b0->getNumItems() << " items.";
	log(IFLogMessage(status.str(), VL_DEBUG, this, "split"));
	// ----- DEBUG ----> */
	addItem(result.boxes.b0);
	/* <---- DEBUG ----- //
	status.str("");
	status << "Adding box with " 
	    << result.boxes.b1->getNumItems() << " items.";
	log(IFLogMessage(status.str(), VL_DEBUG, this, "split"));
	// ----- DEBUG ----> */
	addItem(result.boxes.b1);
	result.success = true;
	return result;
}

Ionflux::GeoUtils::BoxBoundsItemSet 
BoundingBox::getItemsAbovePlane(Ionflux::GeoUtils::Plane3& plane, double t)
{
	BoxBoundsItemSet result;
	int r = checkPlane(plane, t);
	if (r == 1)
	{
	    // Everything in this bounding box is above the plane.
	    result.insert(this);
	    return result;
	} else
	if (r == -1)
	{
	    // Nothing in this bounding box is above the plane.
	    return result;
	}
	if (items.size() == 0)
	    throw GeoUtilsError("Bounding box used as a leaf.");
	// There is some intersection, so we need to go into the details.
	for (BoxBoundsItemSet::iterator i = items.begin(); i != items.end(); i++)
	{
	    BoxBoundsItem* it = *i;
	    r = it->checkPlane(plane, t);
	    if (r == 1)
	        // The whole item is above the plane.
	        result.insert(it);
	    else
	    if (r == 0)
	    {
	        // There is some intersection.
	        BoundingBox* b0 = BoundingBox::upcast(it);
	        if (b0 != 0)
	        {
	            /* If this is a bounding box, check the items contained 
	               within recursively. */
	            BoxBoundsItemSet ts = b0->getItemsAbovePlane(plane, t);
	            result.insert(ts.begin(), ts.end());
	        } else
	        if (it->checkPlaneInner(plane, t) != -1)
	        {
	            // Leaf item, which is not a bounding box.
	            result.insert(it);
	        }
	    }
	}
	return result;
}

Ionflux::GeoUtils::BoxBoundsItemSet 
BoundingBox::getItemsOnLine(Ionflux::GeoUtils::Line3& line, double t)
{
	/* <---- DEBUG ----- //
	std::ostringstream status;
	std::cerr << "[BoundingBox::getItemsOnLine] this = " << this 
	    << ", level = " << level << ", bounds = " 
	    << bounds.getString() << std::endl;
	// ----- DEBUG ----> */
	BoxBoundsItemSet result;
	if (!checkLine(line, t))
	{
	    // If this bounding box is not intersected, nothing in it will be.
	    /* <---- DEBUG ----- //
	    std::cerr << "[BoundingBox::getItemsOnLine] this = " << this 
	        << ", level = " << level << ": no intersection" << std::endl;
	    // ----- DEBUG ----> */
	    return result;
	}
	if (items.size() == 0)
	    throw GeoUtilsError("Bounding box used as a leaf.");
	// There is some intersection, so we need to go into the details.
	for (BoxBoundsItemSet::iterator i = items.begin(); i != items.end(); i++)
	{
	    BoxBoundsItem* it = *i;
	    if (it->checkLine(line, t))
	    {
	        BoundingBox* b0 = dynamic_cast<BoundingBox*>(it);
	        if (b0 != 0)
	        {
	            // Bounding box is intersected, check contained items.
	            BoxBoundsItemSet ts = b0->getItemsOnLine(line, t);
	            result.insert(ts.begin(), ts.end());
	        } else
	        if (it->checkLineInner(line, t))
	        {
	            // Leaf item which intersects the line.
	            /* <---- DEBUG ----- //
	            std::cerr << "[BoundingBox::getItemsOnLine] this = " << this 
	                << ", level = " << level << ": leaf item intersected: " 
	                << it->getString() << std::endl;
	            // ----- DEBUG ----> */
	            result.insert(it);
	        }
	    }
	}
	return result;
}

Ionflux::GeoUtils::BoxBoundsItemSet 
BoundingBox::getItemsOnRay(Ionflux::GeoUtils::Line3& ray, double t)
{
	/* <---- DEBUG ----- //
	std::ostringstream status;
	std::cerr << "[BoundingBox::getItemsOnRay] this = " << this 
	    << ", level = " << level << ", bounds = " 
	    << bounds.getString() << std::endl;
	// ----- DEBUG ----> */
	BoxBoundsItemSet result;
	if (!checkRay(ray, t))
	{
	    // If this bounding box is not intersected, nothing in it will be.
	    /* <---- DEBUG ----- //
	    std::cerr << "[BoundingBox::getItemsOnRay] this = " << this 
	        << ", level = " << level << ": no intersection" << std::endl;
	    // ----- DEBUG ----> */
	    return result;
	}
	if (items.size() == 0)
	    throw GeoUtilsError("[BoundingBox::checkRay] "
	        "Bounding box used as a leaf.");
	// There is some intersection, so we need to go into the details.
	for (BoxBoundsItemSet::iterator i = items.begin(); i != items.end(); i++)
	{
	    BoxBoundsItem* it = *i;
	    if (it->checkRay(ray, t))
	    {
	        BoundingBox* b0 = dynamic_cast<BoundingBox*>(it);
	        if (b0 != 0)
	        {
	            // Bounding box is intersected, check contained items.
	            BoxBoundsItemSet ts = b0->getItemsOnRay(ray, t);
	            result.insert(ts.begin(), ts.end());
	        } else
	        if (it->checkRayInner(ray, t))
	        {
	            // Leaf item which intersects the ray.
	            /* <---- DEBUG ----- //
	            std::cerr << "[BoundingBox::getItemsOnRay] this = " << this 
	                << ", level = " << level << ": leaf item intersected: " 
	                << it->getString() << std::endl;
	            // ----- DEBUG ----> */
	            result.insert(it);
	        }
	    }
	}
	return result;
}

Ionflux::GeoUtils::BoxBoundsItemSet 
BoundingBox::getItemsInSphere(Ionflux::GeoUtils::Sphere3& sphere, double t)
{
	BoxBoundsItemSet result;
	int r = checkSphere(sphere, t);
	if (r == 1)
	{
	    // Everything in this bounding box is inside the sphere.
	    result.insert(this);
	    return result;
	} else
	if (r == -1)
	{
	    // Nothing in this bounding box is inside the sphere.
	    return result;
	}
	if (items.size() == 0)
	    throw GeoUtilsError("Bounding box used as a leaf.");
	// There is some intersection, so we need to go into the details.
	for (BoxBoundsItemSet::iterator i = items.begin(); i != items.end(); i++)
	{
	    BoxBoundsItem* it = *i;
	    r = it->checkSphere(sphere, t);
	    if (r == 1)
	        // The whole item is contained in the sphere.
	        result.insert(it);
	    else
	    if (r == 0)
	    {
	        // There is some intersection.
	        BoundingBox* b0 = BoundingBox::upcast(it);
	        if (b0 != 0)
	        {
	            // Bounding box is intersected, check contained items.
	            BoxBoundsItemSet ts = b0->getItemsInSphere(sphere, t);
	            result.insert(ts.begin(), ts.end());
	        } else
	        if (it->checkSphereInner(sphere, t) != -1)
	        {
	            // Leaf item which intersects the sphere.
	            result.insert(it);
	        }
	    }
	}
	return result;
}

Ionflux::GeoUtils::BoxBoundsItemSet 
BoundingBox::getItemsInBox(Ionflux::GeoUtils::BoxBoundsItem& box, double t)
{
	BoxBoundsItemSet result;
	int r = checkBox(box, t);
	/* <---- DEBUG ----- //
	std::ostringstream status;
	status << "[" << (*this) << "] checkBox result = " << r << " (box = " 
	    << box << ")";
	log(IFLogMessage(status.str(), VL_DEBUG, this, "getItemsInBox"));
	// ----- DEBUG ----> */
	if (r == 1)
	{
	    // Everything in this bounding box is inside the box.
	    result.insert(this);
	    return result;
	} else
	if (r == -1)
	{
	    // Nothing in this bounding box is inside the box.
	    return result;
	}
	if (items.size() == 0)
	    throw GeoUtilsError("Bounding box used as a leaf.");
	// There is some intersection, so we need to go into the details.
	for (BoxBoundsItemSet::iterator i = items.begin(); i != items.end(); i++)
	{
	    BoxBoundsItem* it = *i;
	    r = it->checkBox(box, t);
	    if (r == 1)
	        // The whole item is contained in the box.
	        result.insert(it);
	    else
	    if (r == 0)
	    {
	        // There is some intersection.
	        BoundingBox* b0 = BoundingBox::upcast(it);
	        if (b0 != 0)
	        {
	            // Bounding box is intersected, check contained items.
	            BoxBoundsItemSet ts = b0->getItemsInBox(box, t);
	            result.insert(ts.begin(), ts.end());
	        } else
	        if (it->checkBoxInner(box, t) != -1) 
	        {
	            // Leaf item which intersects the box.
	            result.insert(it);
	        }
	    }
	}
	return result;
}

Ionflux::GeoUtils::BoxBoundsItem* 
BoundingBox::getContainingLeaf(Ionflux::GeoUtils::BoxBoundsItem* item, 
double t)
{
	// <---- DEBUG ----- //
	ostringstream status;
	// ----- DEBUG ----> */
	RangeCompResult r = compare(*item, t);
	// <---- DEBUG ----- //
	status << "check: " << rangeCompToString(r);
	log(IFLogMessage(status.str(), VL_DEBUG, this, "getContainingLeaf"));
	// ----- DEBUG ----> */
	if ((r != RANGE_FIRST_CONTAINS)
	    && (r != RANGE_EQUAL))
	{
	    // This box does not contain the item.
	    return 0;
	}
	if (items.size() == 0)
	{
	    // This box contains the item.
	    return this;
	}
	// Check children.
	for (BoxBoundsItemSet::iterator i = items.begin(); i != items.end(); i++)
	{
	    BoxBoundsItem* it = *i;
	    r = it->compare(*item, t);
	    if ((r == RANGE_FIRST_CONTAINS)
	        || (r == RANGE_EQUAL))
	    {
	        // Child box contains the item.
	        BoxBoundsItem* rb = 0;
	        BoundingBox* b0 = dynamic_cast<BoundingBox*>(it);
	        if (b0 != 0)
	        {
	            // Check boxes recursively.
	            rb = b0->getContainingLeaf(item, t);
	        } else
	        {
	            // We have found the containing leaf item.
	            rb = it;
	        }
	        if (rb != 0)
	            return rb;
	    }
	}
	return this;
}

void BoundingBox::initFromSource(Ionflux::GeoUtils::ItemSource& source)
{
	BoxBoundsItemSet newItems;
	while (items.size() > 0)
	{
	    BoxBoundsItemSet::iterator i = items.begin();
	    BoxBoundsItem* it = *i;
	    removeItem(it, false);
	    BoundingBox* b0 = dynamic_cast<BoundingBox*>(it);
	    if (b0 != 0)
	    {
	        b0->initFromSource(source);
	        newItems.insert(it);
	    } else
	        newItems.insert(source.getItem(it->getItemID()));
	}
	for (BoxBoundsItemSet::iterator i = newItems.begin(); 
	    i != newItems.end(); i++)
	    addItem(*i);
}

void BoundingBox::getBoundingBoxes(Ionflux::GeoUtils::BoundingBoxSet& 
target)
{
	target.insert(this);
	for (BoxBoundsItemSet::iterator i = items.begin(); 
	    i != items.end(); i++)
	{
	    BoundingBox* b0 = dynamic_cast<BoundingBox*>(*i);
	    if (b0 != 0)
	        b0->getBoundingBoxes(target);
	}
}

void BoundingBox::getLeaves(Ionflux::GeoUtils::BoxBoundsItemSet& target)
{
	for (BoxBoundsItemSet::iterator i = items.begin(); 
	    i != items.end(); i++)
	{
	    BoundingBox* b0 = dynamic_cast<BoundingBox*>(*i);
	    if (b0 != 0)
	        b0->getLeaves(target);
	    else
	        target.insert(*i);
	}
}

bool BoundingBox::getItemPath(Ionflux::GeoUtils::BoxBoundsItem* item, 
Ionflux::GeoUtils::BoundingBoxVector& target)
{
	for (BoxBoundsItemSet::iterator i = items.begin(); 
	    i != items.end(); i++)
	{
	    if (*i == item)
	    {
	        /* We are the bottommost container of the item, no need to 
	           check any other boxes. */
	       target.push_back(this);
	       return true;
	    }
	    BoundingBox* b0 = dynamic_cast<BoundingBox*>(*i);
	    if (b0 != 0)
	    {
	        if (b0->getItemPath(item, target))
	        {
	            target.push_back(this);
	            return true;
	        }
	    }
	}
	return false;
}

bool BoundingBox::compareHierarchy(Ionflux::GeoUtils::BoundingBox& other, 
double t)
{
	// <---- DEBUG ----- //
	std::ostringstream msg;
	// ----- DEBUG ----> */
	if (compare(other, t) != RANGE_EQUAL)
	{
	    // <---- DEBUG ----- //
	    log(IFLogMessage("Root boxes of the hierarchy are not equal.", 
	        VL_DEBUG, this, "compareHierarchy"));
	    // ----- DEBUG ----> */
	    return false;
	}
	for (BoxBoundsItemSet::iterator i = items.begin(); 
	    i != items.end(); i++)
	{
	    BoxBoundsItem* it = *i;
	    BoxBoundsItem* matching = 0;
	    BoxBoundsItemSet otherItems = other.items;
	    BoundingBox* b0 = dynamic_cast<BoundingBox*>(it);
	    BoundingBox* b1 = 0;
	    while ((matching == 0) 
	        && (otherItems.size() > 0))
	    {
	        BoxBoundsItemSet::iterator k = otherItems.begin();
	        BoxBoundsItem* oi = *k;
	        b1 = dynamic_cast<BoundingBox*>(oi);
	        otherItems.erase(k);
	        if (it->compare(*oi, t) == RANGE_EQUAL)
	        {
	            /* If the current item is a leaf item, the matching 
	               item must be equal. If the current item is a bounding 
	               box, the matching item must be a bounding box as well. */
	            if (b0 == 0)
	            {
	                if (it == oi)
	                    matching = oi;
	            } else
	            {
	                if (b1 != 0)
	                    matching = oi;
	            }
	        }
	    }
	    if (matching == 0)
	    {
	        // <---- DEBUG ----- //
	        msg.str("");
	        msg << "No matching item found for " << *it << " [" 
	            << it << "] (comparing " << *this << " to " 
	            << other << ").";
	        log(IFLogMessage(msg.str(), VL_DEBUG, this, "compareHierarchy"));
	        log(IFLogMessage("Equality check results:", VL_DEBUG, this, 
	            "compareHierarchy"));
	        for (BoxBoundsItemSet::iterator j = other.items.begin(); 
	            j != other.items.end(); j++)
	        {
	            msg.str("");
	            msg << *(*j) << " [" << *j << "]: " << (it == *j);
	            log(IFLogMessage(msg.str(), VL_DEBUG, this, 
	"compareHierarchy"));
	        }
	        // ----- DEBUG ----> */
	        return false;
	    }
	    if (b0 != 0)
	    {
	        // We have a box with matching bounds, now go into the details.
	        if (b1 == 0)
	            throw GeoUtilsError("Matching bounding box is null!");
	        if (!b0->compareHierarchy(*b1, t))
	            return false;
	    }
	}
	// This level is equal for all practical purposes.
	return true;
}

bool BoundingBox::validate(double t)
{
	for (BoxBoundsItemSet::iterator i = items.begin(); 
	    i != items.end(); i++)
	{
	    if (compare(*(*i), t) != RANGE_FIRST_CONTAINS)
	    {
	        std::ostringstream msg;
	        msg << "Item not contained within bounding box: " << *(*i) 
	            << "(" << *this << ")";
	        throw GeoUtilsError(msg.str());
	    }
	    BoundingBox* b0 = dynamic_cast<BoundingBox*>(*i);
	    if (b0 != 0)
	        b0->validate(t);
	}
	return false;
}

bool BoundingBox::operator==(const Ionflux::GeoUtils::BoundingBox& other) 
const
{
	// TODO: Implementation.
	return compare(other, DEFAULT_TOLERANCE) == RANGE_EQUAL;
}

bool BoundingBox::operator!=(const Ionflux::GeoUtils::BoundingBox& other) 
const
{
	// TODO: Implementation.
	return !(*this == other);;
}

unsigned int BoundingBox::getNumItems() const
{
	// TODO: Implementation.
	return items.size();
}

void BoundingBox::getItems(Ionflux::GeoUtils::BoxBoundsItemSet& target) 
const
{
	target = items;
}

void BoundingBox::setChildIDs(const std::string& prefix, bool showLevel, 
bool keepExisting, bool recursive, unsigned int level, unsigned int 
fieldWidth)
{
	unsigned int k = 0;
	std::ostringstream c0;
	BoxBoundsItemSet::iterator i;
	for (i = items.begin(); i != items.end(); i++)
	{
	    BoxBoundsItem* it0 = *i;
	    BoundingBox* b0 = BoundingBox::upcast(it0);
	    if (!keepExisting 
	        || (it0->getItemID().size() == 0))
	    {
	        c0.str("");
	        c0 << prefix << "_" << setw(fieldWidth) << setfill('0') << k;
	        std::string prefix0 = c0.str();
	        if (showLevel)
	            c0 << "_" << setw(fieldWidth) << setfill('0') << level;
	        it0->setItemID(c0.str());
	        if (recursive && (b0 != 0))
	            b0->setChildIDs(prefix0, showLevel, keepExisting, 
	                true, level + 1, fieldWidth);
	    }
	    k++;
	}
}

std::string BoundingBox::getXML_legacy() const
{
	ostringstream d0;
	if (itemID.size() == 0)
	    throw GeoUtilsError("Item ID not set.");
	d0 << "<bbox id=\"" << itemID << "\" center=\"" << center[0] << "," 
	    << center[1] << "," << center[2] << "\" rvec=\"" << rVec[0] << "," 
	    << rVec[1] << "," << rVec[2] << "\"><items>";
	for (BoxBoundsItemSet::const_iterator i = items.begin(); 
	    i != items.end(); i++)
	    d0 << (*i)->getXML_legacy();
	d0 << "</items></bbox>";
	return d0.str();
}

void BoundingBox::writeToFile(const std::string& fileName) const
{
	ofstream f0;
	f0.open(fileName.c_str(), ios_base::out);
	f0 << XML_HEADER << getXML_legacy();
}

void BoundingBox::setLevel(int newLevel)
{
	level = newLevel;
}

int BoundingBox::getLevel() const
{
    return level;
}

void BoundingBox::setParent(Ionflux::GeoUtils::BoundingBox* newParent)
{
	parent = newParent;
}

Ionflux::GeoUtils::BoundingBox* BoundingBox::getParent() const
{
    return parent;
}

Ionflux::GeoUtils::BoundingBox& BoundingBox::operator=(const 
Ionflux::GeoUtils::BoundingBox& other)
{
    clear();
    center = other.center;
    rVec = other.rVec;
    level = other.level;
    parent = other.parent;
    addItems(other.items);
	return *this;
}

Ionflux::GeoUtils::BoundingBox* BoundingBox::copy() const
{
    BoundingBox* newBoundingBox = create();
    *newBoundingBox = *this;
    return newBoundingBox;
}

Ionflux::GeoUtils::BoundingBox* 
BoundingBox::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<BoundingBox*>(other);
}

Ionflux::GeoUtils::BoundingBox* 
BoundingBox::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    BoundingBox* newObject = new BoundingBox();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int BoundingBox::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file BoundingBox.cpp
 * \brief Bounding box implementation.
 */
