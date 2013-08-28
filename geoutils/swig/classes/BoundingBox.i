/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BoundingBox.i                   Bounding box (interface).
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
%{
#include "geoutils/BoundingBox.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class BoundingBoxClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BoundingBoxClassInfo();
        virtual ~BoundingBoxClassInfo();
};

class BoundingBox
: public Ionflux::GeoUtils::BoxBoundsItem
{
    public:
        
        BoundingBox();
		BoundingBox(const Ionflux::GeoUtils::BoundingBox& other);
        BoundingBox(const Ionflux::GeoUtils::Vector3& initCenter, const 
        Ionflux::GeoUtils::Vector3& initRVec = 
        Ionflux::GeoUtils::Vector3::ZERO, const std::string& initItemID = 
        "", int initLevel = 0, const Ionflux::GeoUtils::BoxBoundsItemSet* 
        initItems = 0, Ionflux::GeoUtils::BoundingBox* initParent = 0);
        virtual ~BoundingBox();
        virtual void update();
        virtual void clear();
        virtual bool addItem(Ionflux::GeoUtils::BoxBoundsItem* item, double
        maxRadius = 0.);
        virtual bool removeItem(Ionflux::GeoUtils::BoxBoundsItem* item, 
        bool update0 = true);
        virtual Ionflux::GeoUtils::BoxBoundsItemSet addItems(const 
        Ionflux::GeoUtils::BoxBoundsItemSet& newItems, unsigned int 
        maxItems = 0, double maxRadius = 0.);
        virtual unsigned int takeItems(Ionflux::GeoUtils::BoxBoundsItemSet&
        newItems, unsigned int maxItems = 0., double maxRadius = 0.);
        virtual Ionflux::GeoUtils::SplitTestResult splitTest(const 
        Ionflux::GeoUtils::Split& split, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual void updateBestSplit(const Ionflux::GeoUtils::SplitParams& 
        s, Ionflux::GeoUtils::SplitParams& best);
        virtual Ionflux::GeoUtils::Split* 
        getBestSplit(Ionflux::GeoUtils::SplitSet& splits, unsigned int 
        minItems = 0, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE, bool
        preferLongestAxis = false, double longestAxisTolerance = 0.1);
        virtual Ionflux::GeoUtils::SplitResult 
        split(Ionflux::GeoUtils::SplitSet& splits, bool recursive = false, 
        unsigned int minItems = 0, unsigned int maxLevel = 0, unsigned int 
        splitLevel = 0, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE, 
        bool preferLongestAxis = false, double longestAxisTolerance = 0.1);
        virtual Ionflux::GeoUtils::BoxBoundsItemSet 
        getItemsAbovePlane(Ionflux::GeoUtils::Plane3& plane, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::BoxBoundsItemSet 
        getItemsOnLine(Ionflux::GeoUtils::Line3& line, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::BoxBoundsItemSet 
        getItemsOnRay(Ionflux::GeoUtils::Line3& ray, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::BoxBoundsItemSet 
        getItemsInSphere(Ionflux::GeoUtils::Sphere3& sphere, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::BoxBoundsItemSet 
        getItemsInBox(Ionflux::GeoUtils::BoxBoundsItem& box, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::BoxBoundsItem* 
        getContainingLeaf(Ionflux::GeoUtils::BoxBoundsItem* item, double t 
        = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual void initFromSource(Ionflux::GeoUtils::ItemSource& source);
        virtual void getBoundingBoxes(Ionflux::GeoUtils::BoundingBoxSet& 
        target);
        virtual void getLeaves(Ionflux::GeoUtils::BoxBoundsItemSet& 
        target);
        virtual bool getItemPath(Ionflux::GeoUtils::BoxBoundsItem* item, 
        Ionflux::GeoUtils::BoundingBoxVector& target);
        virtual bool compareHierarchy(Ionflux::GeoUtils::BoundingBox& 
        other, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool validate(double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool operator==(const Ionflux::GeoUtils::BoundingBox& 
        other) const;
        virtual bool operator!=(const Ionflux::GeoUtils::BoundingBox& 
        other) const;
        virtual unsigned int getNumItems() const;
        virtual void getItems(Ionflux::GeoUtils::BoxBoundsItemSet& target) 
        const;
        virtual std::string getString() const;
        virtual void setChildIDs(const std::string& prefix, bool showLevel 
        = true, bool keepExisting = true, bool recursive = false, unsigned 
        int level = 0, unsigned int fieldWidth = 2);
        virtual std::string getXML() const;
        virtual void writeToFile(const std::string& fileName) const;
		virtual Ionflux::GeoUtils::BoundingBox* copy() const;
		static Ionflux::GeoUtils::BoundingBox* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::BoundingBox* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setLevel(int newLevel);
        virtual int getLevel() const;
        virtual void setParent(Ionflux::GeoUtils::BoundingBox* newParent);
        virtual Ionflux::GeoUtils::BoundingBox* getParent() const;
};

}

}
